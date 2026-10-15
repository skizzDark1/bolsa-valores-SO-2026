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
    if (empresas_guardar("bvdata.txt", &empresas) == 0) {
        printf("bvdata.txt guardado.\n");
    }

    tabela_libertar(&empresas);
    return 0;
}