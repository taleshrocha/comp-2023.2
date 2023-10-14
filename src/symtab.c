#include <stdio.h>
#include <string.h>
#include "../../comp-2023.2/include/symtab.h"

#define SYMTAB_INITIAL_CAPACITY 50

int getFunctionReturnType(Symbol_Table * symbolTable, char * functionName){
    Symbol_Entry * symbol = searchSymbol(symbolTable, functionName);
    if(symbol->type == 2){ //TODO: substituir '2' por FUNCTION_TYPE
        return symbol->data.f_data.return_type;
    }
    return -1;
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
    
    //push(symtab);
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
        printf("\nError: could not increase Symbol Table. No free memory available.\n");
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
    Symbol_Entry * searchResult = searchSymbol(symbolTable, symbol->name);
    if(searchResult != NULL){
        printf("\nSymbol '%s' is already present in the symbol table.\n", symbol->name);
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
        printf("No symbols in the current scope.\n");
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

Symbol_Table **stack;
size_t stack_size = 0;
size_t stack_capacity = SYMTAB_INITIAL_CAPACITY;

void initializeStackOfScopes(){
    stack = malloc(sizeof(Symbol_Table*) * stack_capacity);
}

Symbol_Table * getCurrentScope(){
    return stack[stack_size-1];
}

void increaseStack(){
    size_t newCapacity = stack_capacity * 2;
    Symbol_Table **newStack = malloc(sizeof(Symbol_Table*) * newCapacity);

    if(newStack == NULL){
        printf("\nError: could not increase stack of scopes. No free memory available.\n");
        exit(1);
    }

    for (size_t i = 0; i < stack_capacity; i++) {
        newStack[i] = stack[i];
    }

    free(stack); //TODO: Verificar isso depois
    stack = newStack;
    stack_capacity = newCapacity;
}

Symbol_Table * pushScope(Symbol_Table * scope){
    if(stack_size == stack_capacity){
        increaseStack();
    }

    stack[stack_size++]=scope;
}

Symbol_Table * popScope(){
    //TODO: free?
    return stack[--stack_size];
}

void freeStackOfScopes(){
    free(stack); //TODO: Verificar isso depois
}