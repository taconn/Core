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
		failed++;
	if (c <= b || c >= a + 1000)
		failed++;
	printf("%d failed\n", failed);
	return (failed != 0);
}
