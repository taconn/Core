#include "f_malloc.h"
#include "f_strlen.h"
#include "f_strdup.h"

char	*f_strdup(const char *s)
{
	char	*copy;
	int		len;
	int		i;

	len = f_strlen(s);
	copy = f_malloc((size_t)len + 1);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[len] = '\0';
	return (copy);
}
