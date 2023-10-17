#include "exception.h"

void printMessage(enum MessageType messageType, const char *message, ...) {
    va_list vars;
    va_start(vars, message);
    // Esses printf irão apenas definir a cor da mensagem
    switch (messageType) {
        case SUCCESS:
            fprintf(stderr, ANSI_COLOR_GREEN);
            break;
        case ERROR:
            fprintf(stderr, ANSI_COLOR_RED);
            break;
        case WARNING:
            fprintf(stderr, ANSI_COLOR_YELLOW);
            break;
        default:
            fprintf(stderr, ANSI_COLOR_RED);
            break;
    }

    vfprintf(stderr, message, vars);
    fprintf(stderr, ANSI_COLOR_RESET);
    
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