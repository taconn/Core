#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include "f_colors.h"
#include "f_printf.h"

#define MAX_ENTRIES 1024
#define CYAN "\033[36m"
#define RESET "\033[0m"
#define SELECTED "\033[7m"

typedef struct s_entry
{
    char name[NAME_MAX + 1];
    int is_dir;
}   t_entry;

static struct termios old_term;

static void restore_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_term);
}

static int setup_terminal(void)
{
    struct termios new_term;

    if (tcgetattr(STDIN_FILENO, &old_term) == -1)
        return (-1);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    new_term.c_cc[VMIN] = 1;
    new_term.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term) == -1)
        return (-1);
    return (0);
}

static int load_directory(const char *path, t_entry *entries)
{
    DIR *dir;
    struct dirent *item;
    struct stat info;
    char fullpath[PATH_MAX];
    int count;

    dir = opendir(path);
    if (dir == NULL)
        return (-1);
    count = 0;
    while ((item = readdir(dir)) != NULL && count < MAX_ENTRIES)
    {
        if (snprintf(fullpath, sizeof(fullpath), "%s/%s",
                path, item->d_name) >= (int)sizeof(fullpath))
            continue;
        if (stat(fullpath, &info) == -1)
            continue;
        snprintf(entries[count].name, sizeof(entries[count].name),
            "%s", item->d_name);
        entries[count].is_dir = S_ISDIR(info.st_mode);
        count++;
    }
    closedir(dir);
    return (count);
}

static void go_back(char *path)
{
    char *slash;

    slash = strrchr(path, '/');
    if (slash == NULL)
        return;
    if (slash == path)
        path[1] = '\0';
    else
        *slash = '\0';
}


static void draw(const char *path, t_entry *entries,
    int count, int selected)
{
    int i;

    fflush(stdout);
    write(STDOUT_FILENO, "\033[2J\033[H", 7);
    f_printf("\033[36m");
    f_printf("===================================\n");
    f_printf("  ██████╗  ██████╗ ██████╗ ███████╗\n");
    f_printf(" ██╔════╝ ██╔═══██╗██╔══██╗██╔════╝\n");
    f_printf(" ██║      ██║   ██║██████╔╝█████╗  \n");
    f_printf(" ██║      ██║   ██║██╔══██╗██╔══╝  \n");
    f_printf(" ╚██████╗ ╚██████╔╝██║  ██║███████╗\n");
    f_printf("  ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚══════╝\n");
    f_printf("===================================\n");
    f_printf("\033[0m\n");

    f_printf("Path: %s\n\n", path);

    i = 0;
    while (i < count)
    {
        if (i == selected)
            f_printf("\033[7m");

        if (entries[i].is_dir)
            f_printf("\033[36m[DIR]  %s\033[0m\n",
                entries[i].name);
        else
            f_printf("[FILE] %s\n", entries[i].name);

        if (i == selected)
            f_printf("\033[0m");
        i++;
    }

    f_printf("\033[36m");
    f_printf("===================================");
    f_printf("\nup/down: move | enter: open | bckspc: back | q: quit | t : terminal\n");
    f_printf("___________________________________________________________________");
    fflush(stdout);
}


static int open_file(const char *path)
{
    pid_t pid;
    int status;

    restore_terminal();
    fflush(stdout);
    pid = fork();
    if (pid == 0)
    {
        execlp("nano", "nano", path, (char *)NULL);
        perror("nano");
        _exit(127);
    }
    if (pid < 0)
        perror("fork");
    else
        waitpid(pid, &status, 0);
    if (setup_terminal() == -1)
        return (-1);
    return (0);
}



static void run_command(const char *path)
{
    char command[1024];

    restore_terminal();

    while (1)
    {
        f_printf("\033[0m");
        f_printf(BRIGHT_WHITE "\n%s" RESET"\n", path);
        f_printf(BRIGHT_WHITE "'mq' for exit" RESET "\n");
        f_printf("> ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "mq") == 0)
            break;

        if (command[0] == '\0')
            continue;

        if (chdir(path) == -1)
        {
            perror("chdir");
            continue;
        }

        system(command);
    }

    if (setup_terminal() == -1)
        perror("setup_terminal");
}

int main(void)
{
    char path[PATH_MAX];
    char nextpath[PATH_MAX];
    t_entry *entries;
    int count;
    int selected;
    int running;
    int key;
    char sequence[2];
    struct stat info;

    if (getcwd(path, sizeof(path)) == NULL)
        return (1);
    entries = malloc(sizeof(t_entry) * MAX_ENTRIES);
    if (entries == NULL)
        return (1);
    if (setup_terminal() == -1)
    {
        free(entries);
        perror("terminal");
        return (1);
    }
    atexit(restore_terminal);
    selected = 0;
    running = 1;
    while (running)
    {
        count = load_directory(path, entries);
        if (count < 0)
        {
            restore_terminal();
            perror("Cannot open directory");
            break;
        }
        if (selected >= count)
            selected = count - 1;
        if (selected < 0)
            selected = 0;
        draw(path, entries, count, selected);
        key = getchar();
        if (key == 'q' || key == 'Q')
    running = 0;
else if (key == 't' || key == 'T')
    run_command(path);
        else if (key == 27)
        {
            sequence[0] = getchar();
            sequence[1] = getchar();
            if (sequence[0] == '[' && sequence[1] == 'A'
                && selected > 0)
                selected--;
            else if (sequence[0] == '[' && sequence[1] == 'B'
                && selected < count - 1)
                selected++;
        }
        else if (key == 127 || key == 8)
        {
            go_back(path);
            selected = 0;
        }
        else if ((key == '\n' || key == '\r') && count > 0)
        {
            if (entries[selected].is_dir)
            {
                if (strcmp(entries[selected].name, "..") == 0)
                    go_back(path);
                else if (strcmp(entries[selected].name, ".") != 0)
                {
                    if (snprintf(nextpath, sizeof(nextpath),
                            "%s/%s", path, entries[selected].name)
                            < (int)sizeof(nextpath)
                        && stat(nextpath, &info) == 0
                        && S_ISDIR(info.st_mode))
                        strcpy(path, nextpath);
                }
                selected = 0;
            }
            else
            {
                if (snprintf(nextpath, sizeof(nextpath), "%s/%s",
                        path, entries[selected].name)
                        < (int)sizeof(nextpath))
                    open_file(nextpath);
            }
        }
    }
    free(entries);
    f_printf("\033[0m\033[2J\033[H");
    return (0);
}
