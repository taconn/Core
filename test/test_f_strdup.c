#include <stdio.h>
#include <string.h>
#include "f_malloc.h"
#include "f_strdup.h"

int	main(void)
{
	char	original[] = "hello";
	char	*copy;
	char	*empty;
	int		failed;

	failed = 0;
	copy = f_strdup(original);
	if (copy == NULL || copy == original || strcmp(copy, "hello") != 0)
		failed++;
	original[0] = 'J';
	if (strcmp(copy, "hello") != 0)
		failed++;
	empty = f_strdup("");
	if (empty == NULL || empty[0] != '\0')
		failed++;
	f_free(copy);
	f_free(empty);
	printf("%d failed\n", failed);
	return (failed != 0);
}
