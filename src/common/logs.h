#ifndef BOLSA_LOGS_H
#define BOLSA_LOGS_H

// Categoria de cada mensagem de log
typedef enum {
    NIVEL_LOG,      // funcionamento normal (arranque, empresas carregadas, ordem válida)
    NIVEL_WARNING,  // algo correu mal mas o programa continua (linha ignorada, ordem rejeitada)
    NIVEL_ERROR     // falha grave, normalmente o programa termina (ficheiro não abre, sem memória)
} NivelLog;

// Regista uma mensagem com timestamp e categoria no ficheiro indicado e no terminal.
// Funciona como o printf: podemos passar variáveis!
// Exemplo: log_registar("bv.log", NIVEL_LOG, "%d empresas carregadas", total);
int log_registar(const char *ficheiro_log, NivelLog nivel, const char *formato, ...);

#endif //BOLSA_LOGS_H
