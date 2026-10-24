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
		failed++;
	f_free(d);
	f_free(c);
	printf("%d failed\n", failed);
	return (failed != 0);
}
