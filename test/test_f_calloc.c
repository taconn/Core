
#include "f_colors.h"
#include "f_printf.h"
#include "f_calloc.h"
#include "f_malloc.h"
#include <stdint.h>
#include <stdint.h>

int	main(void)
{
	char	*a;
	char	*b;
	int		failed;
	int		i;

	failed = 0;
	a = f_malloc(64);
	if (a != NULL)
            f_free(a);
        b = f_calloc(8, 8);
	if (b == NULL)
	{
		f_printf("\033[93mtest_f_calloc.c| > \033[0m\033[31m[FAIL]\033[0m Allocation: f_calloc returned NULL\n");
		failed++;
	}
	else
		f_printf("\033[93mtest_f_calloc.c| > \033[0m\033[32m[OK]\033[0m Allocation\n");
	i = 0;
	if (b != NULL)
	{
		while (i < 64)
		{
			if (b[i] != 0)
			{
				f_printf("\033[93mtest_f_calloc.c| > \033[0m\033[31m[FAIL]\033[0m Zero initialization: byte %d is not zero\n", i);
				failed++;
				break ;
			}
			i++;
		}
		if (i == 64)
			f_printf("\033[93mtest_f_calloc.c| > \033[0m\033[32m[OK]\033[0m Zero initialization\n");
	}
	if (f_calloc(SIZE_MAX, 2) != NULL)
	{
		f_printf("\033[93mtest_f_calloc.c| > \033[0m\033[31m[FAIL]\033[0m Overflow: expected NULL for SIZE_MAX * 2\n");
		failed++;
	}
	else
		f_printf("\033[93mtest_f_calloc.c| > \033[0m\033[32m[OK]\033[0m Overflow protection\n");
	if (f_calloc(0, 5) != NULL)
	{
		f_printf("\033[93mtest_f_calloc.c| > \033[0m\033[31m[FAIL]\033[0m Zero-size allocation: expected NULL\n");
		failed++;
	}
	else
		f_printf("\033[93mtest_f_calloc.c| > \033[0m\033[32m[OK]\033[0m Zero-size allocation\n");
	if (b != NULL && b != a)
		f_free(b);
	if (failed == 0)
		f_printf("\033[93mtest_f_calloc.c| > \033[0m\033[32m[OK] All f_calloc checks passed\033[0m\n");
	else
		f_printf("\033[93mtest_f_calloc.c| > \033[0m\033[31m[FAIL] %d f_calloc check(s) failed\033[0m\n", failed);
	return (failed != 0);
}
