//
// Created by vitorcalisto on 10/14/26.
//

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "../common/util.h"

// Valores padrão caso o utilizador não passe argumentos
#define IP_PADRAO           "127.0.0.1"
#define PORTA_PADRAO        8080
#define NOME_PADRAO         "Corretora_A"
#define FICHEIRO_LOG_PADRAO "corretora.log"

int config_ler_argumentos(int argc, char *argv[], ConfigCorretora *cfg)
{
    cfg->ip_bolsa     = IP_PADRAO;
    cfg->porta_bolsa  = PORTA_PADRAO;
    cfg->nome         = NOME_PADRAO;
    cfg->ficheiro_log = FICHEIRO_LOG_PADRAO;

    if (argc > 4) {
        fprintf(stderr, "Uso correto: %s [ip_bolsa] [porta_bolsa] [nome_corretora]\n", argv[0]);
        fprintf(stderr, "Exemplo:     %s 127.0.0.1 8080 Millennium\n", argv[0]);
        return -1;
    }

    if (argc >= 2) {
        cfg->ip_bolsa = argv[1];
    }

    if (argc >= 3) {
        cfg->porta_bolsa = atoi(argv[2]);
        if (!porta_valida(cfg->porta_bolsa)) {
            fprintf(stderr, "ERRO: Porta inválida (%s). Escolha uma porta entre 1024 e 65535.\n", argv[2]);
            return -1;
        }
    }

    if (argc == 4) {
        cfg->nome = argv[3];
    }

    return 0;
}
