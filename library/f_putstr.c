#include <unistd.h>
#include "f_strlen.h"
#include "f_putstr.h"

void	f_putstr_fd(const char *s, int fd)
{
	if (s == NULL)
		return ;
	if (write(fd, s, (size_t)f_strlen(s)) < 0)
		return ;
}

void	f_putstr(const char *s)
{
	f_putstr_fd(s, 1);
}
