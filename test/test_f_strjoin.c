#include <stdio.h>
#include <string.h>
#include "f_malloc.h"
#include "f_strjoin.h"

int	main(void)
{
	char	*s;
	int		failed;

	failed = 0;
	s = f_strjoin("foo", "bar");
	if (s == NULL || strcmp(s, "foobar") != 0)
		failed++;
	f_free(s);
	s = f_strjoin("", "bar");
	if (s == NULL || strcmp(s, "bar") != 0)
		failed++;
	f_free(s);
	s = f_strjoin("foo", "");
	if (s == NULL || strcmp(s, "foo") != 0)
		failed++;
	f_free(s);
	s = f_strjoin("", "");
	if (s == NULL || s[0] != '\0')
		failed++;
	f_free(s);
	if (f_strjoin(NULL, "x") != NULL || f_strjoin("x", NULL) != NULL)
		failed++;
	printf("%d failed\n", failed);
	return (failed != 0);
}
