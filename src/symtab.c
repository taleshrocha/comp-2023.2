#include <stdio.h>
#include <string.h>
#include "symtab.h"

#define SYMTAB_INITIAL_SYMBOLS_CAPACITY 32
#define SYMTAB_INITIAL_CHILDREN_CAPACITY 16

Symbol_Table *current_scope = NULL;

Symbol_Table * getCurrentScope(){
    return current_scope;
}

int getFunctionReturnType(Symbol_Table * symbolTable, char * functionName){
    Symbol_Entry * symbol = searchSymbol(symbolTable, functionName, 0);
    if(symbol->symbol_type == 2){ //TODO: substituir '2' por FUNCTION_TYPE
        return symbol->data.f_data.return_type;
    }
    return -1;
}

Function * getFunctionSymbol(Symbol_Table * symbolTable, char * functionName){
    Symbol_Entry * symbol = searchSymbol(symbolTable, functionName, 0);
    if(symbol->symbol_type == 2){ //TODO: substituir '2' por FUNCTION_TYPE
        return &(symbol->data.f_data);
    }
    return NULL;
}

void pushScope(){
    Symbol_Table * scope = malloc (sizeof (Symbol_Table));

    scope->parent = current_scope;
    scope->children = (Symbol_Table **)malloc(sizeof(Symbol_Table*) * SYMTAB_INITIAL_CHILDREN_CAPACITY);
    scope->children_capacity = SYMTAB_INITIAL_CHILDREN_CAPACITY;
    scope->children_size = 0;
    if (current_scope != NULL) {
        if(current_scope->children_size == current_scope->children_capacity) {
            increaseSymbolTableChildren(current_scope);
        }
        current_scope->children[current_scope->children_size++] = scope;
    }
    scope->symbols = (Symbol_Entry **)malloc(sizeof(Symbol_Entry*) * SYMTAB_INITIAL_SYMBOLS_CAPACITY);
    scope->symbol_capacity = SYMTAB_INITIAL_SYMBOLS_CAPACITY;
    scope->symbol_size = 0;

    current_scope = scope;
}

void increaseSymbolTableChildren(Symbol_Table * symbolTable) {
    size_t newCapacity = symbolTable->children_capacity * 2;
    Symbol_Table** newChildren = (Symbol_Table **)malloc(sizeof(Symbol_Table*) * newCapacity);

    if(newChildren == NULL){
        printf("\nError: could not increase Symbol Table children size. No free memory available.\n");
        exit(1);
    }

    for (size_t i = 0; i < symbolTable->children_size; i++){
        newChildren[i] = symbolTable->children[i];
    }

    symbolTable->children_capacity = newCapacity;
    free(symbolTable->children);
    symbolTable->children = newChildren;
}



/*  Search symbol by name   */
Symbol_Entry * searchSymbol(Symbol_Table * symbolTable, char * name, int flag){
    if(symbolTable == NULL) {
        return NULL; //symbol not found by name
    }

    if(symbolTable->symbol_size == 0 && flag) {
        return searchSymbol(symbolTable->parent, name, flag); //lookup on the parent scope
    }

    for (size_t i = 0; i < symbolTable->symbol_size; i++){
        Symbol_Entry* symbol = symbolTable->symbols[i];
        if(strcmp(name, symbol->name) == 0){
            return symbolTable->symbols[i];
        }
    }
    if (flag) {
        return searchSymbol(symbolTable->parent, name, flag); //lookup on the parent scope
    }
    return NULL;
}

/*  Increase capacity of symbols list   */
void increaseSymbolTableSize(Symbol_Table * symbolTable){

    size_t newCapacity = symbolTable->symbol_capacity * 2;
    Symbol_Entry** newSymbols = (Symbol_Entry **)malloc(sizeof(Symbol_Entry*) * newCapacity);

    if(newSymbols == NULL){
        printf("\nError: could not increase Symbol Table. No free memory available.\n");
        exit(1);
    }

    for (size_t i = 0; i < symbolTable->symbol_size; i++){
        newSymbols[i] = symbolTable->symbols[i];
    }

    symbolTable->symbol_capacity = newCapacity;
    free(symbolTable->symbols);
    symbolTable->symbols = newSymbols;
}

Symbol_Entry * insertSymbol(Symbol_Table * symbolTable, Symbol_Entry * symbol){
    Symbol_Entry * searchResult = searchSymbol(symbolTable, symbol->name, 0);
    if(searchResult != NULL){
        printf("\nSymbol '%s' is already present in the symbol table.\n", symbol->name);
        free(symbol->name);
        free(symbol);
        return searchResult;
    }

    if(symbolTable->symbol_size == symbolTable->symbol_capacity){
        increaseSymbolTableSize(symbolTable);
    }
    symbolTable->symbols[symbolTable->symbol_size++] = symbol;
    return symbol;
}

void printCurrentScope(Symbol_Table * symbolTable){
    if(symbolTable->symbol_size == 0){
        printf("No symbols in the current scope.\n");
        return;
    }
    
    printf("\n\n\t Symbol Table - Current Scope\n");
    for (size_t i = 0; i < symbolTable->symbol_size; i++)
    {
        printf(
            "%ld. Name: %s. Type: %d\n",
            i, 
            symbolTable->symbols[i]->name,
            symbolTable->symbols[i]->symbol_type);
    }
    printf("\n");
}

void popScope(){
    if(current_scope == NULL){
        printf("\nError: no scope to pop.\n");
    }
    current_scope = current_scope->parent;
}

void freeScopes() {
    #ifdef DEBUG
    printf("apagando!\n");
    #endif
    while(current_scope->parent != NULL){
        current_scope = current_scope->parent;
    }
    freeScope(current_scope);
    free(current_scope);
}

void freeScope(Symbol_Table * scope) {
    for (size_t i = 0; i < scope->children_size; i++){
        freeScope(scope->children[i]);
        free(scope->children[i]);
    }
    free(scope->children);
    for (size_t i = 0; i < scope->symbol_size; i++){
        free(scope->symbols[i]->name);
        free(scope->symbols[i]);
    }
    free(scope->symbols);
    #ifdef DEBUG
    printf("freescope!\n");
    #endif
}