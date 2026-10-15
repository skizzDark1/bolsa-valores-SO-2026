//
// Created by HP on 14/10/2026.
//

#ifndef BOLSA_ORDEM_H
#define BOLSA_ORDEM_H

#include "../bv/empresas.h"

// Tipos de Ordem possíveis
typedef enum {
    ORDEM_COMPRA = 'C',
    ORDEM_VENDA  = 'V'
} TipoOrdem;

// Estrutura de uma Ordem conforme pedido no enunciado (Secção 3.1.3)
typedef struct {
    TipoOrdem tipo;              // 'C' (Compra) ou 'V' (Venda)
    char      corretora_id[32];  // Ex: "Millennium", "CaixaInvest"
    char      investidor_id[32]; // Ex: "Investidor_1", "User123"
    char      empresa[32];       // Ex: "Galp", "EDP"
    int       quantidade;        // Quantidade de ações pretendida
    double    preco;             // Preço pretendido por ação
} Ordem;

// Função obrigatória da 1ª Fase:
// Valida a ordem e regista no log se é válida ou o motivo pelo qual foi rejeitada.
// Devolve 1 se válida, 0 se inválida.
int ordem_validar(const Ordem *ordem, const TabelaEmpresas *tabela, const char *ficheiro_log);


#endif //BOLSA_ORDEM_H
