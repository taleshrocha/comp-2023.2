#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "typedefs.h"
#include <stdbool.h>

#define SYMBOL_TABLE_INITIAL_SIZE 100

#define SCOPE_LEVEL 0

// extern TokenData yylval;

typedef union ValueData {
    int v_int;
    int v_bool;
    double v_real;
    char v_char;
    char* v_string;
} ValueData;

void initializeSymbolTable();
unsigned int addSymbol(const char *name);
unsigned int addConstant(const char* name, int type, ValueData data);
void printFirst10Entries();
void increaseTableSize();
void destroySymbolTable();
void showFullTable();
void increaseScopeLevel();
void decreaseScopeLevel();
#endif  // SYMBOLTABLE_H
