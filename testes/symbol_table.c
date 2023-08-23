//TODO: Mover SymbolEntry e logica da tabela de simbolos para outro arquivo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

struct SymbolEntry {
    char *name;
    int class;
};

//Dynamic array
struct SymbolEntry * symbol_table;
size_t maxNumSymbols = SYMBOL_TABLE_INITIAL_SIZE;
int numSymbols = 0;

void initializeSymbolTable(){
    symbol_table = (struct SymbolEntry *) malloc(maxNumSymbols * sizeof(struct SymbolEntry));
    int i = 0;
    while(i < maxNumSymbols){
      symbol_table[i++].name = "";
    }
}

void addSymbol(const char * symbol_name, const int token_class){
    //TODO: Analisar abordagem O(1) usando hashtable com chave string sendo unica (ex.: lexema+escopo)
    for (size_t i = 0; i < numSymbols; i++)
    {
        if(strcmp(symbol_table[i].name, symbol_name) == 0){
            printf("Ja existe um token na tabela de simbolos com o lexema \"%s\".\n\n", symbol_name);
            return;
        }
    }
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

void increaseTableSize(){

    //Memory allocation (doubling symbol_table current size)
    struct SymbolEntry * new_symbol_table = (struct SymbolEntry *) malloc(2 * maxNumSymbols * sizeof(struct SymbolEntry));
    
    if (new_symbol_table == NULL) {
        printf("Error: could not increase Symbol Table. No free memory available.\n");
        exit(1);
    }

    //Deep copy
    for (size_t i = 0; i < maxNumSymbols; i++)
    {
        new_symbol_table[i].name = symbol_table[i].name;
        new_symbol_table[i].class = symbol_table[i].class;
    }

    maxNumSymbols = maxNumSymbols * 2;

    free(symbol_table);
    symbol_table = new_symbol_table;
}