#include "f_colors.h"
#include "f_printf.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "f_putstr.h"

int	main(void)
{
	int		fds[2];
	char	buf[32];
	ssize_t	n;
	int		failed;

	failed = 0;
	if (pipe(fds) != 0)
		return (1);
	f_putstr_fd("hello", fds[1]);
	f_putstr_fd("", fds[1]);
	f_putstr_fd(NULL, fds[1]);
	f_putstr_fd(" world", fds[1]);
	close(fds[1]);
	n = read(fds[0], buf, sizeof(buf) - 1);
	close(fds[0]);
	if (n < 0)
		n = 0;
	buf[n] = '\0';
	if (strcmp(buf, "hello world") != 0)
		do { f_printf("\033[93mtest_f_putstr.c| > \033[0mFAIL: expected output \"hello world\", got \"%s\"\n", buf); failed++; } while (0);
	f_putstr("\n[f_putstr works]\n");
	f_printf(BRIGHT_YELLOW "\033[93mtest_f_putstr.c| > \033[0m%d failed" RESET "\n", failed);
	return (failed != 0);
}
