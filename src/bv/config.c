#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "../common/util.h"

// Valores padrão caso o utilizador não passe argumentos
#define FICHEIRO_DADOS_PADRAO "bvdata.txt"
#define FICHEIRO_LOG_PADRAO   "bv.log"
#define PORTA_PADRAO          8080

int config_ler_argumentos(int argc, char *argv[], ConfigBV *cfg)
{
    cfg->ficheiro_dados = FICHEIRO_DADOS_PADRAO;
    cfg->ficheiro_log   = FICHEIRO_LOG_PADRAO;
    cfg->porta          = PORTA_PADRAO;

    if (argc > 3) {
        fprintf(stderr, "Uso correto: %s [ficheiro_dados] [porta_tcp]\n", argv[0]);
        fprintf(stderr, "Exemplo:     %s bvdata.txt 8080\n", argv[0]);
        return -1;
    }

    if (argc >= 2) {
        cfg->ficheiro_dados = argv[1];
    }

    if (argc == 3) {
        cfg->porta = atoi(argv[2]);
        if (!porta_valida(cfg->porta)) {
            fprintf(stderr, "ERRO: Porta inválida (%s). Escolha uma porta entre 1024 e 65535.\n", argv[2]);
            return -1;
        }
    }

    return 0;
}
