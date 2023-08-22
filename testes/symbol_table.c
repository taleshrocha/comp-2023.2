//TODO: Mover SymbolEntry e logica da tabela de simbolos para outro arquivo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
struct SymbolEntry {
    char *name;
    int class;
};

struct SymbolEntry symbol_table[100];
int maxNumSymbols = 100;
int numSymbols = 0;

void initializeSymbolTable(){
    int i = 0;
    while(i < maxNumSymbols){
      symbol_table[i++].name = "";
    }
}

void addSymbol(const char * symbol_name, const int token_class){
    //TODO: Tratar duplicacao
    //TODO: Analisar abordagem O(1) usando hashtable com chave string sendo unica (ex.: lexema+escopo)
    int pos = numSymbols++;
    symbol_table[pos].name = strdup(symbol_name);
    symbol_table[pos].class = token_class;
}

void printFirst10Entries(){
    printf("\n\n\tTABELA DE SIMBOLOS (10 primeiros)\n");
    for(int i = 0; i < 10; i++){
        printf("TokenName: %s \t TokenClass: %d \n", symbol_table[i].name, symbol_table[i].class);
    }
}