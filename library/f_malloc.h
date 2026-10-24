#ifndef F_MALLOC_H
# define F_MALLOC_H

# include <stddef.h>

void	*f_malloc(size_t size);
void	f_free(void *ptr);
void	*f_realloc(void *ptr, size_t size);

#endif
