#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define SYMBOL_TABLE_INITIAL_SIZE 100

typedef struct SymbolEntry {
    char *name;
    int class;
} SymbolEntry;

extern SymbolEntry * symbol_table; // Tabela de símbolos (tamanho inicial: 100)
extern int numSymbols;

void initializeSymbolTable();
void addSymbol(const char *symbol_name, const int token_class);
void printFirst10Entries();

#endif // SYMBOLTABLE_H
