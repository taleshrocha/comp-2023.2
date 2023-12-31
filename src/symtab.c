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
    if(symbol->symbol_type == K_SUBPROGRAM){
        return symbol->data.sp_data.return_type;
    }
    return -1;
}

Symbol_Entry * getSubProgram(char * subprogname) {
    Symbol_Table* scope = getCurrentScope();
    while(scope->parent != NULL){
        scope = scope->parent;
    }
    for (size_t i = 0; i < scope->symbol_size; i++){
        Symbol_Entry* symbol = scope->symbols[i];
        if (symbol == NULL) {
            printf("subprogram %s not found!", subprogname);
        } else if(symbol->symbol_type == K_SUBPROGRAM && strcmp(subprogname, symbol->name) == 0){
            return symbol;
        }
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

int searchType(char * name) {
    Symbol_Table* scope = getCurrentScope();
    while(scope->parent != NULL){
        scope = scope->parent;
    }
    for (size_t i = 0; i < scope->symbol_size; i++){
        Symbol_Entry* symbol = scope->symbols[i];
        if(strcmp(name, symbol->name) == 0) {
            if(symbol->symbol_type == K_RECORD){
                return symbol->data.r_data.type_id;
            } else if(symbol->symbol_type == K_ARRAY){
                return symbol->data.a_data.type_id;
            } else if(symbol->symbol_type == K_SIMPLETYPE){
                return symbol->data.s_data.inner_type;
            }
        }
    }
    return 0;
}

Symbol_Entry* searchRecordType(int type_id) {
    Symbol_Table* scope = getCurrentScope();
    while(scope->parent != NULL){
        scope = scope->parent;
    }
    for (size_t i = 0; i < scope->symbol_size; i++){
        Symbol_Entry* symbol = scope->symbols[i];
        if(symbol->symbol_type == K_RECORD){
            if(symbol->data.r_data.type_id == type_id){
                return symbol;
            }
        }
    }
    return NULL;
}

Symbol_Entry* searchArrayType(int type_id) {
    Symbol_Table* scope = getCurrentScope();
    while(scope->parent != NULL){
        scope = scope->parent;
    }
    for (size_t i = 0; i < scope->symbol_size; i++){
        Symbol_Entry* symbol = scope->symbols[i];
        if(symbol->symbol_type == K_ARRAY){
            if(symbol->data.a_data.type_id == type_id){
                return symbol;
            }
        }
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
            symbolTable->symbols[i]->symbol_type
        );
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
        free(scope->symbols[i]->name); //TODO: Problema aqui - free(): invalid pointer
        free(scope->symbols[i]);
    }
    free(scope->symbols);
    #ifdef DEBUG
    printf("freescope!\n");
    #endif
}


char* type_name(int type_id) {
	Symbol_Entry* type = NULL;
    switch (type_id) {
        case E_UNDEFINED:
            return "undefined";
        case E_INT:
            return "int";
        case E_REAL:
            return "real";
        case E_CHAR:
            return "char";
        case E_STRING:
            return "string";
        case E_BOOL:    
            return "bool";
        case E_ARRAY:   
            return "array";
        case E_RECORD:  
            return "record";
        case E_FUNCTION:
            return "function";
        case E_PROCEDURE:
            return "procedure";
        default:
            type = searchRecordType(type_id);
            if (type != NULL){
                return type->name;
            }
            type = searchArrayType(type_id);
            if (type != NULL){
                return type->name;
            }
            return "Type not found!";
    }
}

char* get_c_type(int type_id) {
	Symbol_Entry* type = NULL;
    switch (type_id) {
        case E_INT:
            return "int";
        case E_REAL:
            return "float";
        case E_CHAR:
            return "char";
        case E_STRING:
            return "char*";
        case E_BOOL:    
            return "bool";
        default:
            type = searchRecordType(type_id);
            if (type != NULL){
                return type->name;
            }
            //TODO: Verificar este caso
            type = searchArrayType(type_id);
            if (type != NULL){
                return type->name;
            }
            return "__ERROR__";
    }
}