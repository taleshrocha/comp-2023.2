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
