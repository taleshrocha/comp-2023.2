#include <stdio.h>
#include <stdio.h>
#include <string.h>

#include "symbolTable.h"

SymbolEntry symbol_table[MAXNUMSYMBOLS]; // Tabela de símbolos (tamanho máximo de 100)
int numSymbols = 0;

void initializeSymbolTable() {
    int i = 0;
    while (i < MAXNUMSYMBOLS)
    {
        symbol_table[i++].name = "";
    }
}

void addSymbol(const char *symbol_name, const int token_type) {
    // TODO: Tratar duplicacao
    // TODO: Analisar abordagem usando hashtable
    int pos = numSymbols++;
    symbol_table[pos].name = strdup(symbol_name);
    symbol_table[pos].type = token_type;
}