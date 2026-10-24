#include <stdint.h>
#include <unistd.h>
#include "f_malloc.h"

#define ALIGNMENT 16
#define ALIGN(x) (((x) + ALIGNMENT - 1) & ~((size_t)ALIGNMENT - 1))

typedef struct s_block
{
	size_t			size;
	int				is_free;
	struct s_block	*next;
}	t_block;

#define HEADER_SIZE ALIGN(sizeof(t_block))

static t_block	*g_head = NULL;

static t_block	*find_free(size_t size)
{
	t_block	*cur;

	cur = g_head;
	while (cur)
	{
		if (cur->is_free && cur->size >= size)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

static t_block	*request_space(size_t size)
{
	t_block	*block;
	t_block	*last;
	void	*mem;

	mem = sbrk((intptr_t)(HEADER_SIZE + size));
	if (mem == (void *)-1)
		return (NULL);
	block = (t_block *)mem;
	block->size = size;
	block->is_free = 0;
	block->next = NULL;
	if (g_head == NULL)
		g_head = block;
	else
	{
		last = g_head;
		while (last->next)
			last = last->next;
		last->next = block;
	}
	return (block);
}

static void	split_block(t_block *block, size_t size)
{
	t_block	*rest;

	if (block->size < size + HEADER_SIZE + ALIGNMENT)
		return ;
	rest = (t_block *)((char *)block + HEADER_SIZE + size);
	rest->size = block->size - size - HEADER_SIZE;
	rest->is_free = 1;
	rest->next = block->next;
	block->size = size;
	block->next = rest;
}

void	*f_malloc(size_t size)
{
	t_block	*block;

	if (size == 0)
		return (NULL);
	size = ALIGN(size);
	block = find_free(size);
	if (block)
	{
		split_block(block, size);
		block->is_free = 0;
	}
	else
		block = request_space(size);
	if (block == NULL)
		return (NULL);
	return ((char *)block + HEADER_SIZE);
}

static void	merge_free(void)
{
	t_block	*cur;

	cur = g_head;
	while (cur && cur->next)
	{
		if (cur->is_free && cur->next->is_free
			&& (char *)cur + HEADER_SIZE + cur->size == (char *)cur->next)
		{
			cur->size += HEADER_SIZE + cur->next->size;
			cur->next = cur->next->next;
		}
		else
			cur = cur->next;
	}
}

void	f_free(void *ptr)
{
	t_block	*block;

	if (ptr == NULL)
		return ;
	block = (t_block *)((char *)ptr - HEADER_SIZE);
	block->is_free = 1;
	merge_free();
}

void	*f_realloc(void *ptr, size_t size)
{
	t_block			*block;
	void			*new_ptr;
	unsigned char	*src;
	unsigned char	*dst;
	size_t			i;

	if (ptr == NULL)
		return (f_malloc(size));
	if (size == 0)
	{
		f_free(ptr);
		return (NULL);
	}
	block = (t_block *)((char *)ptr - HEADER_SIZE);
	if (block->size >= size)
		return (ptr);
	new_ptr = f_malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	src = ptr;
	dst = new_ptr;
	i = 0;
	while (i < block->size)
	{
		dst[i] = src[i];
		i++;
	}
	f_free(ptr);
	return (new_ptr);
}
