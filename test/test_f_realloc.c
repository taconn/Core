#include "f_colors.h"
#include "f_printf.h"
#include "f_malloc.h"
#include <string.h>

int	main(void)
{
	char	*a;
	char	*b;
	char	*c;
	int		failed;

	failed = 0;
	a = f_realloc(NULL, 10);
	if (a == NULL)
	{
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[31m[FAIL]\033[0m Initial allocation: expected non-NULL pointer\n");
		failed++;
	}
	else
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[32m[OK]\033[0m Initial allocation\n");
	if (a == NULL)
		return (1);
	strcpy(a, "hello");
	b = f_realloc(a, 5);
	if (b == NULL)
	{
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[31m[FAIL]\033[0m Shrinking: returned NULL\n");
		f_free(a);
		return (1);
	}
	else
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[32m[OK]\033[0m Shrinking allocation\n");
	if (strcmp(b, "hello") != 0)
	{
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[31m[FAIL]\033[0m Data preservation after shrinking\n");
		failed++;
	}
	else
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[32m[OK]\033[0m Data preservation after shrinking\n");
	c = f_realloc(b, 500);
	if (c == NULL)
	{
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[31m[FAIL]\033[0m Growing: returned NULL\n");
		f_free(b);
		return (1);
	}
	if (strcmp(c, "hello") != 0)
	{
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[31m[FAIL]\033[0m Data preservation after growing\n");
		failed++;
	}
	else
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[32m[OK]\033[0m Data preservation after growing\n");
	if (f_realloc(c, 0) != NULL)
	{
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[31m[FAIL]\033[0m Zero-size realloc: expected NULL\n");
		failed++;
	}
	else
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[32m[OK]\033[0m Zero-size realloc\n");
	if (failed == 0)
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[32m[OK] All f_realloc checks passed\033[0m\n");
	else
		f_printf("\033[93mtest_f_realloc.c| > \033[0m\033[31m[FAIL] %d f_realloc check(s) failed\033[0m\n", failed);
	return (failed != 0);
}
