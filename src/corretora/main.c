//
// Created by HP on 12/10/2026.
//

#include <stdio.h>
#include "config.h"
#include "../common/logs.h"

// Valores por omissão
#define IP_PADRAO       "127.0.0.1"
#define PORTA_PADRAO    8080
#define NOME_PADRAO     "Corretora_A"
#define FICHEIRO_LOG    "corretora.log"

int main(int argc, char *argv[])
{
    ConfigCorretora cfg;
    if (config_ler_argumentos(argc, argv, &cfg) != 0) {
        return 1;
    }

    // 2. Registo de logs e inicialização dos parâmetros
    log_registar(cfg.ficheiro_log,NIVEL_LOG, "=== Corretora '%s' a iniciar ===", cfg.nome);
    log_registar(cfg.ficheiro_log, NIVEL_LOG,"Configuração: Bolsa Alvo = %s:%d", cfg.ip_bolsa, cfg.porta_bolsa);

    printf("\n--- Corretora Inicializada com Sucesso ---\n");
    printf("Nome:  %s\n", cfg.nome);
    printf("Bolsa: %s na porta %d\n\n", cfg.ip_bolsa, cfg.porta_bolsa);

    log_registar(cfg.ficheiro_log, NIVEL_LOG,"=== Corretora terminada ===");

    return 0;
}