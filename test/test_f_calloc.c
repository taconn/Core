#include <stdio.h>
#include <stdint.h>
#include "f_malloc.h"
#include "f_calloc.h"

int	main(void)
{
	char	*a;
	char	*b;
	int		i;
	int		failed;

	failed = 0;
	a = f_malloc(64);
	i = 0;
	while (i < 64)
	{
		a[i] = 'x';
		i++;
	}
	f_free(a);
	b = f_calloc(8, 8);
	if (b != a)
		failed++;
	i = 0;
	while (i < 64)
	{
		if (b[i] != 0)
			failed++;
		i++;
	}
	if (f_calloc(SIZE_MAX, 2) != NULL)
		failed++;
	if (f_calloc(0, 5) != NULL)
		failed++;
	f_free(b);
	printf("\033[93mtest_f_calloc.c %d failed\033[0m\n", failed);
	return (failed != 0);
}
