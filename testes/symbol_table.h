#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

void initializeSymbolTable();
void addSymbol(const char *symbol_name, const int token_class);
void printFirst10Entries();

#endif