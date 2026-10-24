LIB_DIR = ../library
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIB_DIR) -include f_colors.h

SRC = $(wildcard test_*.c)
BIN = $(SRC:.c=)

all: $(BIN)
	@for t in $(BIN); do ./$$t || exit 1; done

lib:
	@$(MAKE) -C $(LIB_DIR)

test_%: test_%.c lib
	$(CC) $(CFLAGS) $< -L$(LIB_DIR) -lcore -o $@

clean:
	rm -f $(BIN)

.PHONY: all lib clean
