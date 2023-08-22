#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

// TODO: Usar alocação dinamica para o tamanho da tabela
#define MAXNUMSYMBOLS 100

// TODO: Mover SymbolEntry e logica da tabela de simbolos para outro arquivo
typedef struct SymbolEntry {
    char *name;
    int type;
} SymbolEntry;

extern SymbolEntry symbol_table[MAXNUMSYMBOLS]; // Tabela de símbolos (tamanho máximo de 100)
extern int numSymbols;

void initializeSymbolTable();
void addSymbol(const char *symbol_name, const int token_class);

#endif // SYMBOLTABLE_H