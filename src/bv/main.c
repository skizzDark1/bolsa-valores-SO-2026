//
// Created by vitorcalisto on 10/10/26.
//
#include <stdio.h>
#include "empresas.h"

int main(void)
{
    TabelaEmpresas empresas;
    tabela_iniciar(&empresas);

    if (empresas_carregar("bvdata.txt", &empresas) < 0) {
        tabela_libertar(&empresas);
        return 1;
    }

    printf("%d empresas carregadas (capacidade %d):\n",
           empresas.n, empresas.capacidade);
    empresas_imprimir(&empresas);

    tabela_libertar(&empresas);
    return 0;
}