//
// Created by vitorcalisto on 10/10/26.
// Alterado em 12/10 por JP
//
#include <stdio.h>
#include <stdlib.h>  //vamos usar o atoi
#include "empresas.h"
#include "logs.h"

// Valores padrão caso o utilizador não passe argumentos
#define FICHEIRO_DADOS_PADRAO "bvdata.txt"
#define FICHEIRO_LOG_PADRAO   "bv.log"
#define PORTA_PADRAO          8080

int main(int argc, char *argv[])
{
    const char *ficheiro_dados = FICHEIRO_DADOS_PADRAO;
    const char *ficheiro_log   = FICHEIRO_LOG_PADRAO;
    int porta = PORTA_PADRAO;

    // 1. Validação dos argumentos da linha de comandos
    if (argc > 3) {
        fprintf(stderr, "Uso correto: %s [ficheiro_dados] [porta_tcp]\n", argv[0]);
        fprintf(stderr, "Exemplo:     %s bvdata.txt 8080\n", argv[0]);
        return 1;
    }

    if (argc >= 2) {
        ficheiro_dados = argv[1]; // O utilizador escolheu o ficheiro
    }

    if (argc == 3) {
        porta = atoi(argv[2]);    // atoi converte texto em número inteiro
        if (porta <= 1024 || porta > 65535) {
            fprintf(stderr, "ERRO: Porta inválida (%d). Escolha uma porta entre 1025 e 65535.\n", porta);
            return 1;
        }
    }

    // 2. Início dos Registos de Log
    log_registar("bv.log", "=== Bolsa de Valores a iniciar ===");
    log_registar(ficheiro_log, "Configuração: Ficheiro de dados='%s' | Porta TCP=%d", ficheiro_dados, porta);

    // 3. Inicializar e carregar a tabela de empresas
    TabelaEmpresas empresas;
    tabela_iniciar(&empresas);

    if (empresas_carregar("bvdata.txt", &empresas) < 0) {
        log_registar("bv.log", "ERRO: Falha ao carregar bvdata.txt");
        tabela_libertar(&empresas);
        return 1;
    }

    log_registar("bv.log", "Sucesso: %d empresas carregadas para a memória", empresas.n);

    // Mostra as empresas no ecrã
    printf("%d empresas carregadas (capacidade %d):\n", empresas.n, empresas.capacidade);
    empresas_imprimir(&empresas);
    printf("\n");

    // Guarda de volta (garantia de consistência)
    if (empresas_guardar(ficheiro_dados, &empresas) == 0) {
        log_registar(ficheiro_log, "Ficheiro '%s' atualizado/guardado com sucesso", ficheiro_dados);
    }

    tabela_libertar(&empresas);
    log_registar("bv.log", "=== Bolsa de Valores terminada com sucesso ===");
    return 0;
}