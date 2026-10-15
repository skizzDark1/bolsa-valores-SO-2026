//
// Created by JP on 12/10/2026.
//

#ifndef BOLSA_LOGS_H
#define BOLSA_LOGS_H

// Regista uma mensagem com timestamp no ficheiro indicado.
// Funciona como o printf: podemos passar variáveis!
// Exemplo: log_registar("bv.log", "%d empresas carregadas", total);
int log_registar(const char *ficheiro_log, const char *formato, ...);

#endif //BOLSA_LOGS_H
