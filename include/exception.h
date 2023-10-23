#ifndef EXCEPTION_H
#define EXCEPTION_H
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

void printMessage(enum MessageType messageType, const char *message, va_list vars);

#endif // EXCEPTION_H