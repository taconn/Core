#include "f_colors.h"
#include "f_printf.h"
#include <stdio.h>
#include <string.h>
#include "f_malloc.h"
#include "f_strjoin.h"

int	main(void)
{
	char	*s;
	int		failed;

	failed = 0;
	s = f_strjoin("foo", "bar");
	if (s == NULL || strcmp(s, "foobar") != 0)
		do { f_printf("\033[93mtest_f_strjoin.c| > \033[0mFAIL: check at line %d\n", __LINE__); failed++; } while (0);
	f_free(s);
	s = f_strjoin("", "bar");
	if (s == NULL || strcmp(s, "bar") != 0)
		do { f_printf("\033[93mtest_f_strjoin.c| > \033[0mFAIL: check at line %d\n", __LINE__); failed++; } while (0);
	f_free(s);
	s = f_strjoin("foo", "");
	if (s == NULL || strcmp(s, "foo") != 0)
		do { f_printf("\033[93mtest_f_strjoin.c| > \033[0mFAIL: check at line %d\n", __LINE__); failed++; } while (0);
	f_free(s);
	s = f_strjoin("", "");
	if (s == NULL || s[0] != '\0')
		do { f_printf("\033[93mtest_f_strjoin.c| > \033[0mFAIL: check at line %d\n", __LINE__); failed++; } while (0);
	f_free(s);
	if (f_strjoin(NULL, "x") != NULL || f_strjoin("x", NULL) != NULL)
		do { f_printf("\033[93mtest_f_strjoin.c| > \033[0mFAIL: check at line %d\n", __LINE__); failed++; } while (0);
	f_printf(BRIGHT_YELLOW "\033[93mtest_f_strjoin.c| > \033[0m%d failed" RESET "\n", failed);
	return (failed != 0);
}
