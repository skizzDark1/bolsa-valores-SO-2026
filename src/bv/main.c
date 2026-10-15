//
// Created by vitorcalisto on 10/10/26.
// Alterado em 12/10 por JP
//
#include <stdio.h>
#include <stdlib.h>
#include "empresas.h"
#include "../common/logs.h"
#include "../common/ordem.h" // <--- Adiciona este include
#include "config.h"

int main(int argc, char *argv[])
{
    ConfigBV cfg;
    if (config_ler_argumentos(argc, argv, &cfg) != 0) {
        return 1;
    }

    log_registar(cfg.ficheiro_log, "=== Bolsa de Valores a iniciar ===");
    log_registar(cfg.ficheiro_log, "Configuração: Ficheiro de dados='%s' | Porta TCP=%d",
                 cfg.ficheiro_dados, cfg.porta);

    TabelaEmpresas empresas;
    tabela_iniciar(&empresas);

    if (empresas_carregar(cfg.ficheiro_dados, &empresas) < 0) {
        log_registar(cfg.ficheiro_log, "ERRO: Falha ao carregar '%s'", cfg.ficheiro_dados);
        tabela_libertar(&empresas);
        return 1;
    }

    log_registar(cfg.ficheiro_log, "Sucesso: %d empresas carregadas para a memória", empresas.n);

    printf("%d empresas carregadas (capacidade %d):\n", empresas.n, empresas.capacidade);
    empresas_imprimir(&empresas);
    printf("\n");

    // ==============================================================
    // REQUISITO DA 1ª FASE: Demonstração da Validação de Ordens
    // ==============================================================
    log_registar(cfg.ficheiro_log, "--- A iniciar testes de validação de ordens ---");

    // 1. Ordem Válida (Galp existe no ficheiro bvdata.txt)
    Ordem o1 = { .tipo = ORDEM_COMPRA, .corretora_id = "Corretora_A",
                 .investidor_id = "Inv_1", .empresa = "Galp",
                 .quantidade = 100, .preco = 14.50 };
    ordem_validar(&o1, &empresas, cfg.ficheiro_log);

    // 2. Ordem Inválida: Empresa que NÃO existe na bolsa
    Ordem o2 = { .tipo = ORDEM_COMPRA, .corretora_id = "Corretora_A",
                 .investidor_id = "Inv_2", .empresa = "Google",
                 .quantidade = 50, .preco = 150.00 };
    ordem_validar(&o2, &empresas, cfg.ficheiro_log);

    // 3. Ordem Inválida: Quantidade e Preço incoerentes
    Ordem o3 = { .tipo = ORDEM_VENDA, .corretora_id = "Corretora_B",
                 .investidor_id = "Inv_3", .empresa = "EDP",
                 .quantidade = -10, .preco = -2.50 };
    ordem_validar(&o3, &empresas, cfg.ficheiro_log);

    printf("\n");

    // Guarda de volta
    if (empresas_guardar(cfg.ficheiro_dados, &empresas) == 0) {
        log_registar(cfg.ficheiro_log, "Ficheiro '%s' atualizado/guardado com sucesso", cfg.ficheiro_dados);
    }

    tabela_libertar(&empresas);
    log_registar(cfg.ficheiro_log, "=== Bolsa de Valores terminada com sucesso ===");
    return 0;
}