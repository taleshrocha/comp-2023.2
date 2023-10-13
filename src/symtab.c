#include <stdio.h>
#include <string.h>
#include "../../comp-2023.2/include/symtab.h"

#define SYMTAB_INITIAL_CAPACITY 50

int get_function_return_type(Symbol_Table * symbolTable, char * functionName){
    Symbol_Entry * symbol = searchSymbol(symbolTable, functionName);
    if(symbol->type == 2){ //TODO: substituir '2' por FUNCTION_TYPE
        return symbol->data.f_data.return_type;
    }
    return NULL;
}

Function * getFunctionSymbol(Symbol_Table * symbolTable, char * functionName){
    Symbol_Entry * symbol = searchSymbol(symbolTable, functionName);
    if(symbol->type == 2){ //TODO: substituir '2' por FUNCTION_TYPE
        return &(symbol->data.f_data);
    }
    return NULL;
}

Symbol_Table * createSymbolTable(Symbol_Table * parent){
    Symbol_Table * symtab = malloc (sizeof (Symbol_Table));

    symtab->parent = parent;
    symtab->symbols = (Symbol_Entry *)malloc(sizeof(Symbol_Entry) * SYMTAB_INITIAL_CAPACITY);
    symtab->capacity = SYMTAB_INITIAL_CAPACITY;
    symtab->size = 0;
    
    return symtab;
}

/*  Search symbol by name   */
Symbol_Entry * searchSymbol(Symbol_Table * symbolTable, char * name){
    if(symbolTable == NULL){
        return NULL; //symbol not found by name
    }

    if(symbolTable->size == 0){
        return searchSymbol(symbolTable->parent, name); //lookup on the parent scope
    }

    for (size_t i = 0; i < symbolTable->size; i++){
        Symbol_Entry symbol = symbolTable->symbols[i];
        if(strcmp(name, symbol.name) == 0){
            return &symbolTable->symbols[i];
        }
    }

    return searchSymbol(symbolTable->parent, name); //lookup on the parent scope
}

/*  Increase capacity of symbols list   */
void increaseSymbolTableSize(Symbol_Table * symbolTable){

    size_t newCapacity = symbolTable->capacity * 2;
    Symbol_Entry *newSymbols = (Symbol_Entry *)malloc(sizeof(Symbol_Entry) * newCapacity);

    if(newSymbols == NULL){
        printf("Error: could not increase Symbol Table. No free memory available.\n");
        exit(1);
    }

    for (size_t i = 0; i < symbolTable->size; i++){
        newSymbols[i].data = symbolTable->symbols[i].data;
        newSymbols[i].name = symbolTable->symbols[i].name;
        newSymbols[i].type = symbolTable->symbols[i].type;
    }

    symbolTable->capacity = newCapacity;
    free(symbolTable->symbols);
    symbolTable->symbols = newSymbols;
}

Symbol_Entry * insertSymbol(Symbol_Table * symbolTable, Symbol_Entry * symbol){   
    Symbol_Entry * searchResult = searchSymbol(symbolTable, symbol->name) ; 
    if(searchResult != NULL){
        printf("Symbol '%s' is already present in the symbol table.", symbol->name);
        return searchResult;
    }

    if(symbolTable->size == symbolTable->capacity){
        increaseSymbolTableSize(symbolTable);
    }
    symbolTable->symbols[symbolTable->size++] = *symbol;
    return symbol;
}

void printCurrentScope(Symbol_Table * symbolTable){
    if(symbolTable->size == 0){
        printf("No symbols in the current scope.");
        return;
    }
    
    printf("\n\n\t Symbol Table - Current Scope\n");
    for (size_t i = 0; i < symbolTable->size; i++)
    {
        printf(
            "%ld. Name: %s. Type: %d\n",
            i, 
            symbolTable->symbols[i].name,
            symbolTable->symbols[i].type);
    }
    printf("\n");
}