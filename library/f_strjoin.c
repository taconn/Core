#include "f_malloc.h"
#include "f_strlen.h"
#include "f_strjoin.h"

char	*f_strjoin(const char *a, const char *b)
{
	char	*res;
	int		len_a;
	int		len_b;
	int		i;

	if (a == NULL || b == NULL)
		return (NULL);
	len_a = f_strlen(a);
	len_b = f_strlen(b);
	res = f_malloc((size_t)len_a + (size_t)len_b + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len_a)
	{
		res[i] = a[i];
		i++;
	}
	i = 0;
	while (i < len_b)
	{
		res[len_a + i] = b[i];
		i++;
	}
	res[len_a + len_b] = '\0';
	return (res);
}
