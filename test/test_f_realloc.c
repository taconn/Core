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
	a = f_realloc(NULL, 10);
	if (a == NULL)
		failed++;
	strcpy(a, "hello");
	b = f_realloc(a, 5);
	if (b != a)
		failed++;
	c = f_realloc(b, 500);
	if (c == NULL || strcmp(c, "hello") != 0)
		failed++;
	if (f_realloc(c, 0) != NULL)
		failed++;
	printf("%d failed\n", failed);
	return (failed != 0);
}
