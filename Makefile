CC = gcc
CFLAGS = -Wall -Wextra -g

# O comando 'make' ou 'make all' agora compila os dois executáveis: bv e corretora
all: bv corretora

# Compila o Servidor (Bolsa de Valores)
bv: src/bv/main.c src/bv/empresas.c src/bv/empresas.h src/bv/logs.c src/bv/logs.h
	$(CC) $(CFLAGS) -o bv src/bv/main.c src/bv/empresas.c src/bv/logs.c

# Compila o Cliente (Corretora)
corretora: src/corretora/main.c src/bv/logs.c src/bv/logs.h
	$(CC) $(CFLAGS) -o corretora src/corretora/main.c src/bv/logs.c

clean:
	rm -f bv corretora *.log *.tmp

.PHONY: all clean