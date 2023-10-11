#include <stdio.h>
#include <stdarg.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

enum MessageType {
    SUCCESS,
    ERROR,
    WARNING
};

void printMessage(enum MessageType messageType, const char *message, ...) {
    va_list vars;
    va_start(vars, message);
    // Esses printf irão apenas definir a cor da mensagem
    switch (messageType) {
        case SUCCESS:
            printf(ANSI_COLOR_GREEN);
            break;
        case ERROR:
            printf(ANSI_COLOR_RED);
            break;
        case WARNING:
            printf(ANSI_COLOR_YELLOW);
            break;
        default:
            printf(ANSI_COLOR_RED);
            break;
    }

    vprintf(message, vars);
    printf(ANSI_COLOR_RESET);
    
    va_end(vars);
}
/*
(Lembrar de adicionar o enum)
Exemplos de uso:

    int x = 15, nive = 5555;
    printMessage(SUCCESS, "Sua gambiarra deu certo! %d\n", x);
    printMessage(ERROR, "Sua gambiarra não deu certo :( verifique seu código novamente ! %d %c\n", 15, 'c');
    printMessage(WARNING, "Sua gambiarra foi mais ou menos, checa essa parada aí irmão %d %s \n", nive, "String teste \n"); 
*/