#include <stdio.h>
#include <string.h>
#include "f_malloc.h"

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
		failed++;
	strcpy(a, "hello");
	strcpy(b, "world");
	if (strcmp(a, "hello") != 0 || strcmp(b, "world") != 0)
		failed++;
	f_free(a);
	c = f_malloc(8);
	if (c != a)
		failed++;
	f_free(b);
	f_free(c);
	if (f_malloc(0) != NULL)
		failed++;
	printf("%d failed\n", failed);
	return (failed != 0);
}
