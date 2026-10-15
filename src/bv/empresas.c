//
// Created by vitorcalisto on 10/10/26.
//

#include <stdio.h>
#include <stdlib.h>
#include "empresas.h"

void tabela_iniciar(TabelaEmpresas *t)
{
    t->dados = NULL;
    t->n = 0;
    t->capacidade = 0;
}

int tabela_adicionar(TabelaEmpresas *t, Empresa e)
{
    if (t->n == t->capacidade) {
        int nova_cap = (t->capacidade == 0) ? 4 : t->capacidade * 2;
        Empresa *novo = realloc(t->dados, nova_cap * sizeof(Empresa));
        if (novo == NULL) {
            return -1;
        }
        t->dados = novo;
        t->capacidade = nova_cap;
    }
    t->dados[t->n] = e;
    t->n++;
    return 0;
}

void tabela_libertar(TabelaEmpresas *t)
{
    free(t->dados);
    tabela_iniciar(t);
}

int empresas_carregar(const char *ficheiro, TabelaEmpresas *t)
{
    FILE *f = fopen(ficheiro, "r");
    if (f == NULL) {
        printf("Erro: não consegui abrir %s\n", ficheiro);
        return -1;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), f) != NULL) {
        Empresa e;
        char extra;
        int lidos = sscanf(linha, "%31s %d %lf %lf %c",
                           e.nome, &e.acoes_por_colocar,
                           &e.valor_nominal, &e.cotacao, &extra);
        if (lidos == 4) {
            if (tabela_adicionar(t, e) != 0) {
                printf("Erro: sem memória\n");
                fclose(f);
                return -1;
            }
        } else {
            printf("Linha ignorada: %s", linha);
        }
    }

    fclose(f);
    return t->n;
}

void empresas_imprimir(const TabelaEmpresas *t)
{
    for (int i = 0; i < t->n; i++) {
        printf("%-10s %8d %6.2f %6.2f\n",
               t->dados[i].nome, t->dados[i].acoes_por_colocar,
               t->dados[i].valor_nominal, t->dados[i].cotacao);
    }
}
int empresas_guardar(const char *ficheiro, const TabelaEmpresas *t)
{
    char temporario[256];
    snprintf(temporario, sizeof(temporario), "%s.tmp", ficheiro);

    FILE *f = fopen(temporario, "w");
    if (f == NULL) {
        printf("Erro: não consegui criar %s\n", temporario);
        return -1;
    }

    for (int i = 0; i < t->n; i++) {
        fprintf(f, "%s %d %.2f %.2f\n",
                t->dados[i].nome, t->dados[i].acoes_por_colocar,
                t->dados[i].valor_nominal, t->dados[i].cotacao);
    }

    if (fclose(f) != 0) {
        printf("Erro ao escrever %s\n", temporario);
        return -1;
    }

    if (rename(temporario, ficheiro) != 0) {
        printf("Erro: não consegui substituir %s\n", ficheiro);
        return -1;
    }
    return 0;
}