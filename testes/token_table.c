#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token_table.h"

//TODO: TokenEntry attributes based on the category
struct TokenEntry {
    
    //Token Category - eg:ID, V_INT, IF, LOOP, FUNCTION.
    int category;

    //Literals
    char * string_value;
    char char_value;
    float float_value;
    int int_value;

    //ID - row number in SymbolTable
    size_t symbol_table_key;
};


struct TokenEntry * token_table;
size_t maxNumTokens = TOKEN_TABLE_INITIAL_SIZE;
int numTokens = 0;


void initializeTokenTable(){
    int i = 0;
    while(i < maxNumTokens){
      token_table[i++].category = -1;
    }
}

void addToken(const int token_category, const int attribute){

}

void printFirst10Entries(){
    printf("\n\n\tTABELA DE TOKENS (10 primeiros)\n");
    for(int i = 0; i < 10; i++){
        printf("TokenCategory: %s\n", token_table[i].category);
    }
}

void increaseTableSize(){

    //Memory allocation (doubling token_table current size)
    struct TokenEntry * new_token_table = (struct TokenEntry *) malloc(2 * numTokens * sizeof(struct TokenEntry));
    
    if (new_token_table == NULL) {
        printf("Error: could not increase Symbol Table. No free memory available.\n");
        return;
    }

    //Deep copy
    for (size_t i = 0; i < numTokens; i++)
    {
        new_token_table[i].category = token_table[i].category;
        //TODO: Deep copy - remaining attributes
    }

    maxNumTokens = maxNumTokens * 2;

    free(token_table);
    token_table = new_token_table;
}