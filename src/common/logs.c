//
// Created by JP on 12/10/2026.
//

#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include "logs.h"

int log_registar(const char *ficheiro_log, const char *formato, ...)
{
    // 1. Abre o ficheiro em modo "a" (append = acrescenta ao final)
    FILE *f = fopen(ficheiro_log, "a");
    if (f == NULL) {
        perror("Erro ao abrir ficheiro de log");
        return -1;
    }

    // 2. Calcula a data e hora atual (Timestamp)
    time_t agora = time(NULL);
    struct tm *info = localtime(&agora);
    char timestamp[32];
    // Formato: [AAAA-MM-DD HH:MM:SS]
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", info);

    // 3. Escreve o timestamp no ficheiro (e mostra também no terminal)
    fprintf(f, "%s ", timestamp);
    printf("%s [LOG] ", timestamp); // Mostra também na consola

    // 4. Processa os argumentos variáveis (como o printf faz)
    va_list args1, args2;
    va_start(args1, formato);
    va_copy(args2, args1);

    vfprintf(f, formato, args1);       // Escreve no ficheiro
    vfprintf(stdout, formato, args2);  // Mostra na consola
    fprintf(f, "\n");
    printf("\n");

    va_end(args1);
    va_end(args2);

    // 5. Fecha e garante que ficou gravado no disco
    fclose(f);
    return 0;
}