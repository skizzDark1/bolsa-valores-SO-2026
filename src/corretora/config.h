//
// Created by vitorcalisto on 10/14/26.
//

#ifndef CONFIG_CORRETORA_H
#define CONFIG_CORRETORA_H

typedef struct {
    const char *ip_bolsa;
    int         porta_bolsa;
    const char *nome;
    const char *ficheiro_log;
} ConfigCorretora;

// Preenche cfg com os valores por omissão e os argumentos da linha de comandos.
// Devolve 0 se correu bem, -1 se os argumentos são inválidos.
int config_ler_argumentos(int argc, char *argv[], ConfigCorretora *cfg);

#endif
