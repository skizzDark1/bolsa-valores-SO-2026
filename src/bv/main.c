//
// Created by vitorcalisto on 10/10/26.
// Alterado em 12/10 por JP
//
#include <stdio.h>
#include <stdlib.h>  //vamos usar o atoi
#include "empresas.h"
#include "../common/logs.h"
#include "config.h"

// Valores padrão caso o utilizador não passe argumentos
#define FICHEIRO_DADOS_PADRAO "bvdata.txt"
#define FICHEIRO_LOG_PADRAO   "bv.log"
#define PORTA_PADRAO          8080

int main(int argc, char *argv[])
{
    // 1. Ler a configuração (valores por omissão + argumentos)
    ConfigBV cfg;
    if (config_ler_argumentos(argc, argv, &cfg) != 0) {
        return 1;
    }

    // 2. Início dos Registos de Log
    log_registar(cfg.ficheiro_log, "=== Bolsa de Valores a iniciar ===");
    log_registar(cfg.ficheiro_log, "Configuração: Ficheiro de dados='%s' | Porta TCP=%d",
                 cfg.ficheiro_dados, cfg.porta);

    // 3. Inicializar e carregar a tabela de empresas
    TabelaEmpresas empresas;
    tabela_iniciar(&empresas);

    if (empresas_carregar(cfg.ficheiro_dados, &empresas) < 0) {
        log_registar(cfg.ficheiro_log, "ERRO: Falha ao carregar '%s'", cfg.ficheiro_dados);
        tabela_libertar(&empresas);
        return 1;
    }

    log_registar(cfg.ficheiro_log, "Sucesso: %d empresas carregadas para a memória", empresas.n);

    // Mostra as empresas no ecrã
    printf("%d empresas carregadas (capacidade %d):\n", empresas.n, empresas.capacidade);
    empresas_imprimir(&empresas);
    printf("\n");

    // 4. Guarda de volta (garantia de consistência)
    if (empresas_guardar(cfg.ficheiro_dados, &empresas) == 0) {
        log_registar(cfg.ficheiro_log, "Ficheiro '%s' atualizado/guardado com sucesso", cfg.ficheiro_dados);
    }

    tabela_libertar(&empresas);
    log_registar(cfg.ficheiro_log, "=== Bolsa de Valores terminada com sucesso ===");
    return 0;
}