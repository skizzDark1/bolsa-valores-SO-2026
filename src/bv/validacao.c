//
// Created by vitorcalisto on 10/15/26.
//

#include <stddef.h>
#include "../common/logs.h"
#include "validacao.h"
int ordem_validar(const Ordem *ordem, const TabelaEmpresas *tabela, const char *ficheiro_log)
{
    if (ordem == NULL || tabela == NULL) {
        log_registar(ficheiro_log, NIVEL_ERROR,"ERRO VALIDAÇÃO: Ordem ou Tabela nula.");
        return 0;
    }

    const char *str_tipo = (ordem->tipo == ORDEM_COMPRA) ? "COMPRA" : "VENDA";

    // 1. Validação do Tipo (apenas Compra ou Venda)
    if (ordem->tipo != ORDEM_COMPRA && ordem->tipo != ORDEM_VENDA) {
        log_registar(ficheiro_log,NIVEL_WARNING,
            "[ORDEM REJEITADA] Tipo inválido ('%c') de %s:%s.",
            ordem->tipo, ordem->corretora_id, ordem->investidor_id);
        return 0;
    }

    // 2. Validação da Quantidade (tem de ser positiva)
    if (ordem->quantidade <= 0) {
        log_registar(ficheiro_log,NIVEL_WARNING,
            "[ORDEM REJEITADA] Quantidade inválida (%d) na ordem de %s por %s:%s.",
            ordem->quantidade, str_tipo, ordem->corretora_id, ordem->investidor_id);
        return 0;
    }

    // 3. Validação do Preço (tem de ser estritamente positivo)
    if (ordem->preco <= 0.0) {
        log_registar(ficheiro_log,NIVEL_WARNING,
            "[ORDEM REJEITADA] Preço incoerente (%.2f) na ordem de %s por %s:%s.",
            ordem->preco, str_tipo, ordem->corretora_id, ordem->investidor_id);
        return 0;
    }

    // 4. Validação da Empresa (tem de existir na Tabela de Cotações)
    if (!empresas_existe(tabela, ordem->empresa)) {
        log_registar(ficheiro_log,NIVEL_WARNING,
            "[ORDEM REJEITADA] Empresa '%s' não existe na Bolsa (Ordem de %s:%s).",
            ordem->empresa, ordem->corretora_id, ordem->investidor_id);
        return 0;
    }

    // Se passou todos os testes, a ordem é válida!
    log_registar(ficheiro_log,NIVEL_LOG,
        "[ORDEM VÁLIDA] %s | %s:%s | Empresa: %s | Qtd: %d | Preço: %.2f EUR",
        str_tipo, ordem->corretora_id, ordem->investidor_id,
        ordem->empresa, ordem->quantidade, ordem->preco);

    return 1;
}