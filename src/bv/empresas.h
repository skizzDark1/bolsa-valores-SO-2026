//
// Created by vitorcalisto on 10/10/26.
//

#ifndef EMPRESAS_H
#define EMPRESAS_H

typedef struct {
    char   nome[32];
    int    acoes_por_colocar;
    double valor_nominal;
    double cotacao;
} Empresa;

typedef struct {
    Empresa *dados;       // array dinâmico de empresas
    int      n;           // quantas empresas estão guardadas
    int      capacidade;  // quantas cabem antes de ter de crescer
} TabelaEmpresas;

void tabela_iniciar(TabelaEmpresas *t);
int  tabela_adicionar(TabelaEmpresas *t, Empresa e);
void tabela_libertar(TabelaEmpresas *t);

int  empresas_carregar(const char *ficheiro, TabelaEmpresas *t, const char *ficheiro_log);
void empresas_imprimir(const TabelaEmpresas *t);
int  empresas_guardar(const char *ficheiro, const TabelaEmpresas *t);

// Devolve 1 se a empresa existe na tabela, 0 se não existir
int empresas_existe(const TabelaEmpresas *t, const char *nome);

#endif