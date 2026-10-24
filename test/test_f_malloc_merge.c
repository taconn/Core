#include "f_printf.h"
#include <stdio.h>
#include "f_malloc.h"

int	main(void)
{
	char	*a;
	char	*b;
	char	*c;
	char	*d;
	int		failed;

	failed = 0;
	a = f_malloc(100);
	b = f_malloc(100);
	c = f_malloc(100);
	f_free(a);
	f_free(b);
	d = f_malloc(200);
	if (d != a)
		do { f_printf("\033[93mtest_f_malloc_merge.c| > \033[0mFAIL: check at line %d\n", __LINE__); failed++; } while (0);
	f_free(d);
	f_free(c);
	f_printf("\033[93m \033[93mtest_f_malloc_merge.c| > \033[0m%d failed\033[0m\n", failed);
	return (failed != 0);
}
