#include <stdio.h>
#include <string.h>
#include "../../comp-2023.2/include/symtab.h"

int get_function_return_type(Symbol_Table * symbolTable, char * functionName){
    Symbol_Entry * symbol = search_symbol(symbolTable, functionName);
    if(symbol->type == 2){ //TODO: substituir '2' por FUNCTION_TYPE
        return symbol->data.f_data.return_type;
    }
    return NULL;
}

Function * get_function_symbol(Symbol_Table * symbolTable, char * functionName){
    Symbol_Entry * symbol = search_symbol(symbolTable, functionName);
    if(symbol->type == 2){ //TODO: substituir '2' por FUNCTION_TYPE
        return &(symbol->data.f_data);
    }
    return NULL;
}

Symbol_Table * create_symbol_table(Symbol_Table * parent, int scope){
    Symbol_Table * symtab = malloc (sizeof (Symbol_Table));

    symtab->scope = scope;
    symtab->parent = parent;
    symtab->symbol_head = NULL;

    return symtab;
}

/*
    Search symbol by name in the symbol table
*/
Symbol_Entry * search_symbol(Symbol_Table * symbolTable, char * name){
    if(symbolTable == NULL){
        return NULL; //symbol not found by name
    }

    Symbol_Entry * curr = symbolTable->symbol_head;
    if(curr == NULL)
        return search_symbol(symbolTable->parent, name); //lookup on the parent scope

    while(curr->next != NULL) {
        if(strcmp(name, curr->name) == 0){
            return curr;
        }
        curr = curr->next;
    }

    return search_symbol(symbolTable->parent, name); //lookup on the parent scope
}

Symbol_Entry * get_last_symbol_in_table(Symbol_Table * symbolTable){
    Symbol_Entry * curr = symbolTable->symbol_head;
    if(curr == NULL)
        return NULL;

    while(curr->next != NULL) curr = curr->next;
    return curr;
}

void insert_symbol(Symbol_Table * symbolTable, Symbol_Entry symbol){    
    if(search_symbol(symbolTable, symbol.name) != NULL){
        printf("Symbol '%s' is already present in the symbol table.", symbol.name);
        return NULL;
    }

    Symbol_Entry * last_entry = get_last_symbol_in_table(symbolTable);
    if(last_entry == NULL)
        symbolTable->symbol_head = &symbol;
    else
        last_entry->next = &symbol;
}