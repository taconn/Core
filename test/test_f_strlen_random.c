#include "f_colors.h"
#include "f_printf.h"
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
			f_printf("KO  len=%d, expected %d, got %d\n", len, expected, got);
			do { f_printf("\033[93mtest_f_strlen_random.c| > \033[0mFAIL: check at line %d\n", __LINE__); failed++; } while (0);
		}
		i++;
	}
	f_printf(BRIGHT_YELLOW "\033[93mtest_f_strlen_random.c| > \033[0m%d tests, %d failed" RESET "\n", TESTS, failed);
	return (failed != 0);
}
