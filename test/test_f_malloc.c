
#include "f_colors.h"
#include "f_printf.h"
#include "f_malloc.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*a;
	char	*b;
	char	*c;
	int		failed;

	failed = 0;
	a = f_malloc(10);
	b = f_malloc(100);
	if (a == NULL || b == NULL || a == b)
	{
		f_printf("\033[93mtest_f_malloc.c| > \033[0m\033[31m[FAIL]\033[0m Allocation: expected distinct non-NULL pointers\n");
		failed++;
	}
	else
	{
		strcpy(a, "hello");
		strcpy(b, "world");
		if (strcmp(a, "hello") != 0 || strcmp(b, "world") != 0)
		{
			f_printf("\033[93mtest_f_malloc.c| > \033[0m\033[31m[FAIL]\033[0m Memory read/write: data mismatch\n");
			failed++;
		}
		else
			f_printf("\033[93mtest_f_malloc.c| > \033[0m\033[32m[OK]\033[0m Memory read/write\n");
	}
	if (a != NULL)
		f_free(a);
	c = f_malloc(8);
	if (a != NULL && c != a)
	{
		f_printf("\033[93mtest_f_malloc.c| > \033[0m\033[31m[FAIL]\033[0m Memory reuse: freed block was not reused\n");
		failed++;
	}
	else if (a != NULL)
		f_printf("\033[93mtest_f_malloc.c| > \033[0m\033[32m[OK]\033[0m Memory reuse\n");
	if (b != NULL)
		f_free(b);
	if (c != NULL)
		f_free(c);
	if (f_malloc(0) != NULL)
	{
		f_printf("\033[93mtest_f_malloc.c| > \033[0m\033[31m[FAIL]\033[0m Zero-size allocation: expected NULL\n");
		failed++;
	}
	else
		f_printf("\033[93mtest_f_malloc.c| > \033[0m\033[32m[OK]\033[0m Zero-size allocation\n");
	if (failed == 0)
		f_printf("\033[93mtest_f_malloc.c| > \033[0m\033[32m[OK] All f_malloc checks passed\033[0m\n");
	else
		f_printf("\033[93mtest_f_malloc.c| > \033[0m\033[31m[FAIL] %d f_malloc check(s) failed\033[0m\n", failed);
	return (failed != 0);
}
