#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f_strlen.h"

#define TESTS 10000
#define MAX_LEN 200

static void	fill_random(char *buf, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		buf[i] = (char)(rand() % 255 + 1);
		i++;
	}
	buf[len] = '\0';
}

int	main(void)
{
	char	buf[MAX_LEN + 1];
	int		len;
	int		got;
	int		expected;
	int		i;
	int		failed;

	srand(42);
	failed = 0;
	i = 0;
	while (i < TESTS)
	{
		len = rand() % (MAX_LEN + 1);
		fill_random(buf, len);
		got = f_strlen(buf);
		expected = (int)strlen(buf);
		if (got != expected)
		{
			printf("KO  len=%d, expected %d, got %d\n", len, expected, got);
			failed++;
		}
		i++;
	}
	printf("%d tests, %d failed\n", TESTS, failed);
	return (failed != 0);
}
