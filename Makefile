CC = gcc
CFLAGS = -Wall -Wextra -g

bv: src/bv/main.c src/bv/empresas.c src/bv/empresas.h
	$(CC) $(CFLAGS) -o bv src/bv/main.c src/bv/empresas.c

clean:
	rm -f bv

.PHONY: clean