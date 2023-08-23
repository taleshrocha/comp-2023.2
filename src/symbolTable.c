#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "typedefs.h"
#include "symbolTable.h"

size_t maxNumSymbols = SYMBOL_TABLE_INITIAL_SIZE;
//Dynamic array
SymbolEntry * symbol_table;
size_t numSymbols = 0;
TokenData yylval;

void initializeSymbolTable(){
    symbol_table = (SymbolEntry *) malloc(maxNumSymbols * sizeof(SymbolEntry));
}

unsigned int addSymbol(const char* name){
    //TODO: Analisar abordagem O(1) usando hashtable com chave string sendo unica (ex.: lexema+escopo)
    for (size_t i = 0; i < numSymbols; i++)
    {
        if(strcmp(symbol_table[i].name, name) == 0){
            printf("Ja existe um token na tabela de simbolos com o lexema \"%s\".\n\n", name);
            return i;
        }
    }
    if(numSymbols == maxNumSymbols){
        increaseTableSize();
    }
    
    int pos = numSymbols++;
    symbol_table[pos].name = strdup(name);
    return pos;
}


void printFirst10Entries(){
    printf("\n\n\tTABELA DE SIMBOLOS (10 primeiros)\n");
    for(int i = 0; i < 10; i++){
        printf("TokenName: %s \t TokenClass: %d \n", symbol_table[i].name, symbol_table[i].type);
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
        new_symbol_table[i].type = symbol_table[i].type;
    }

    maxNumSymbols = maxNumSymbols * 2;

    free(symbol_table);
    symbol_table = new_symbol_table;
}
