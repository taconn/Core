#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f_strcmp.h"

#define TESTS 10000
#define MAX_LEN 5

static int	sign(int x)
{
	return ((x > 0) - (x < 0));
}

static void	fill(char *buf)
{
	static const char	alphabet[3] = {'a', 'b', (char)200};
	int					len;
	int					i;

	len = rand() % (MAX_LEN + 1);
	i = 0;
	while (i < len)
	{
		buf[i] = alphabet[rand() % 3];
		i++;
	}
	buf[len] = '\0';
}

static int	check(const char *a, const char *b)
{
	if (sign(f_strcmp(a, b)) == sign(strcmp(a, b)))
		return (0);
	printf("KO  \"%s\" vs \"%s\"\n", a, b);
	return (1);
}

int	main(void)
{
	char	a[MAX_LEN + 1];
	char	b[MAX_LEN + 1];
	int		failed;
	int		i;

	failed = 0;
	failed += check("", "");
	failed += check("a", "");
	failed += check("", "a");
	failed += check("abc", "abc");
	failed += check("abc", "abd");
	failed += check("abd", "abc");
	failed += check("abc", "abcd");
	failed += check("abcd", "abc");
	failed += check("\377", "a");
	srand(42);
	i = 0;
	while (i < TESTS)
	{
		fill(a);
		fill(b);
		failed += check(a, b);
		i++;
	}
	printf("%d tests, %d failed\n", TESTS + 9, failed);
	return (failed != 0);
}
