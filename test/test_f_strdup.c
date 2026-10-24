#include "f_colors.h"
#include "f_printf.h"
#include <stdio.h>
#include <string.h>
#include "f_malloc.h"
#include "f_strdup.h"

int	main(void)
{
	char	original[] = "hello";
	char	*copy;
	char	*empty;
	int		failed;

	failed = 0;
	copy = f_strdup(original);
	if (copy == NULL || copy == original || strcmp(copy, "hello") != 0)
		do { f_printf("\033[93mtest_f_strdup.c| > \033[0mFAIL: check at line %d\n", __LINE__); failed++; } while (0);
	original[0] = 'J';
	if (strcmp(copy, "hello") != 0)
		do { f_printf("\033[93mtest_f_strdup.c| > \033[0mFAIL: check at line %d\n", __LINE__); failed++; } while (0);
	empty = f_strdup("");
	if (empty == NULL || empty[0] != '\0')
		do { f_printf("\033[93mtest_f_strdup.c| > \033[0mFAIL: check at line %d\n", __LINE__); failed++; } while (0);
	f_free(copy);
	f_free(empty);
	f_printf(BRIGHT_YELLOW "\033[93mtest_f_strdup.c| > \033[0m%d failed" RESET "\n", failed);
	return (failed != 0);
}
