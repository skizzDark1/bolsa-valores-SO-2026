//
// Created by vitorcalisto on 10/14/26.
//

#ifndef BOLSA_CONFIG_H
#define BOLSA_CONFIG_H
typedef struct {
    const char *ficheiro_dados;
    const char *ficheiro_log;
    int porta;
} ConfigBV;

int config_ler_argumentos(int argc, char *argv[], ConfigBV *cfg);
#endif //BOLSA_CONFIG_H
