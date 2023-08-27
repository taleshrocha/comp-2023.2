#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stdbool.h>

#include "typedefs.h"

#define SYMBOL_TABLE_INITIAL_SIZE 100

extern SymbolEntry *symbol_table;  // Tabela de símbolos (tamanho inicial: 100)
extern TokenData yylval;

void initializeSymbolTable();
unsigned int addSymbol(const char *name);
void printFirst10Entries();
void increaseTableSize();
void destroySymbolTable();
void showFullTable();
#endif  // SYMBOLTABLE_H
