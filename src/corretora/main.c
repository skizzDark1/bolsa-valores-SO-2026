//
// Created by HP on 12/10/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bv/logs.h"  // Reutilizamos o mesmo módulo de logs que criámos!

// Valores por omissão
#define IP_PADRAO       "127.0.0.1"
#define PORTA_PADRAO    8080
#define NOME_PADRAO     "Corretora_A"
#define FICHEIRO_LOG    "corretora.log"

int main(int argc, char *argv[])
{
    const char *ip_servidor    = IP_PADRAO;
    int porta                  = PORTA_PADRAO;
    const char *nome_corretora = NOME_PADRAO;

    // 1. Validação dos argumentos: ./corretora [ip] [porta] [nome]
    if (argc > 4) {
        fprintf(stderr, "Uso correto: %s [ip_bolsa] [porta_bolsa] [nome_corretora]\n", argv[0]);
        fprintf(stderr, "Exemplo:     %s 127.0.0.1 8080 Millennium\n", argv[0]);
        return 1;
    }

    if (argc >= 2) {
        ip_servidor = argv[1];
    }

    if (argc >= 3) {
        porta = atoi(argv[2]);
        if (porta <= 1024 || porta > 65535) {
            fprintf(stderr, "ERRO: Porta inválida (%d). Escolha uma porta entre 1025 e 65535.\n", porta);
            return 1;
        }
    }

    if (argc == 4) {
        nome_corretora = argv[3];
    }

    // 2. Registo de logs e inicialização dos parâmetros
    log_registar(FICHEIRO_LOG, "=== Corretora '%s' a iniciar ===", nome_corretora);
    log_registar(FICHEIRO_LOG, "Configuração: Bolsa Alvo = %s:%d", ip_servidor, porta);

    printf("\n--- Corretora Inicializada com Sucesso ---\n");
    printf("Nome:  %s\n", nome_corretora);
    printf("Bolsa: %s na porta %d\n\n", ip_servidor, porta);

    log_registar(FICHEIRO_LOG, "=== Corretora terminada ===");

    return 0;
}