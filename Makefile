
.PHONY: all library test clean fclean re

all: library test

library:
	$(MAKE) -C library

test: library
	$(MAKE) -C test

clean:
	$(MAKE) -C library clean
	$(MAKE) -C test clean

fclean:
	$(MAKE) -C library fclean
	$(MAKE) -C test clean

re: fclean all
