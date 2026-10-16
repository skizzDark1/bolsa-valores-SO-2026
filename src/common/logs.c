#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include "logs.h"

static const char *nivel_texto(NivelLog nivel)
{
    switch (nivel) {
    case NIVEL_WARNING: return "WARNING";
    case NIVEL_ERROR:   return "ERROR";
    default:            return "LOG";
    }
}

int log_registar(const char *ficheiro_log, NivelLog nivel, const char *formato, ...)
{
    // 1. Abre o ficheiro em modo "a" (append = acrescenta ao final)
    FILE *f = fopen(ficheiro_log, "a");
    if (f == NULL) {
        perror("Erro ao abrir ficheiro de log");
        return -1;
    }

    // 2. Data e hora atual: [AAAA-MM-DD HH:MM:SS]
    time_t agora = time(NULL);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", localtime(&agora));

    // 3. Prefixo igual no ficheiro e no terminal: [data] [CATEGORIA]
    const char *categoria = nivel_texto(nivel);
    fprintf(f, "%s [%s] ", timestamp, categoria);
    printf("%s [%s] ", timestamp, categoria);

    // 4. Mensagem com argumentos variáveis (como o printf)
    va_list args1, args2;
    va_start(args1, formato);
    va_copy(args2, args1);
    vfprintf(f, formato, args1);
    vprintf(formato, args2);
    va_end(args1);
    va_end(args2);

    fprintf(f, "\n");
    printf("\n");

    fclose(f);
    return 0;
}
