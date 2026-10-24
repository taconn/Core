#include "f_colors.h"
#include "f_printf.h"
#include <stdio.h>
#include "f_malloc.h"

int	main(void)
{
	char	*a;
	char	*b;
	char	*c;
	int		failed;

	failed = 0;
	a = f_malloc(1000);
	f_free(a);
	b = f_malloc(100);
	c = f_malloc(100);
	if (b != a)
		do { f_printf("\033[93mtest_f_malloc_split.c| > \033[0mFAIL: check at line %d\n", __LINE__); failed++; } while (0);
	if (c <= b || c >= a + 1000)
		do { f_printf("\033[93mtest_f_malloc_split.c| > \033[0mFAIL: check at line %d\n", __LINE__); failed++; } while (0);
	f_printf(BRIGHT_YELLOW "\033[93mtest_f_malloc_split.c| > \033[0m%d failed" RESET "\n", failed);
	return (failed != 0);
}
