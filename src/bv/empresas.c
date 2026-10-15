//
// Created by vitorcalisto on 10/10/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "empresas.h"
#include "../common/logs.h"


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

// Verifica se os valores de uma empresa lida do ficheiro são coerentes.
// Devolve NULL se estiver tudo bem, ou o motivo pelo qual deve ser ignorada.
static const char *empresa_motivo_invalida(const Empresa *e, const TabelaEmpresas *t)
{
    if (e->acoes_por_colocar < 0) return "ações por colocar negativas";
    if (e->valor_nominal <= 0)    return "valor nominal tem de ser positivo";
    if (e->cotacao <= 0)          return "cotação tem de ser positiva";
    if (empresas_existe(t, e->nome)) return "empresa repetida";
    return NULL;
}
int empresas_carregar(const char *ficheiro, TabelaEmpresas *t, const char *ficheiro_log)
{
    FILE *f = fopen(ficheiro, "r");
    if (f == NULL) {
        log_registar(ficheiro_log, "ERRO: não consegui abrir '%s'", ficheiro);
        return -1;
    }

    char linha[256];
    int num_linha = 0;
    while (fgets(linha, sizeof(linha), f) != NULL) {
        num_linha++;
        Empresa e;
        char extra;
        int lidos = sscanf(linha, "%31s %d %lf %lf %c",
                           e.nome, &e.acoes_por_colocar,
                           &e.valor_nominal, &e.cotacao, &extra);
        const char *motivo = empresa_motivo_invalida(&e, t);
        if (motivo != NULL) {
            log_registar(ficheiro_log, "Linha %d ignorada (%s): '%s'", num_linha, motivo, e.nome);
            continue;
        }
        if (lidos == 4) {
            if (tabela_adicionar(t, e) != 0) {
                log_registar(ficheiro_log, "ERRO: sem memória ao carregar empresas");
                fclose(f);
                return -1;
            }
        } else {
            linha[strcspn(linha, "\n")] = '\0';
            log_registar(ficheiro_log, "Linha %d ignorada (formato inválido): '%s'", num_linha, linha);
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

int empresas_existe(const TabelaEmpresas *t, const char *nome)
{
    if (t == NULL || nome == NULL) return 0;

    for (int i = 0; i < t->n; i++) {
        if (strcmp(t->dados[i].nome, nome) == 0) {
            return 1; // Encontrou!
        }
    }
    return 0; // Não existe
}