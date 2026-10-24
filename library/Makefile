NAME = libcore.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = f_add.c f_strcpy.c f_strcmp.c f_strlen.c f_malloc.c f_calloc.c f_strdup.c f_strjoin.c f_putstr.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
