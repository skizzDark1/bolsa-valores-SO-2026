CC = gcc
CFLAGS = -Wall -Wextra -g

COMUM = src/common/logs.c src/common/util.c
COMUM_H = src/common/logs.h src/common/util.h

all: bv corretora

bv: src/bv/main.c src/bv/empresas.c src/bv/config.c src/bv/empresas.h src/bv/config.h $(COMUM) $(COMUM_H)
	$(CC) $(CFLAGS) -o bv src/bv/main.c src/bv/empresas.c src/bv/config.c $(COMUM)

corretora: src/corretora/main.c src/corretora/config.c src/corretora/config.h $(COMUM) $(COMUM_H)
	$(CC) $(CFLAGS) -o corretora src/corretora/main.c src/corretora/config.c $(COMUM)

clean:
	rm -f bv corretora *.log *.tmp

.PHONY: all clean
