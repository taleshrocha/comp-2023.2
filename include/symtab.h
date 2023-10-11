#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h> 
#include <stdlib.h>

typedef struct Variable
{
    int is_constant;
    union Value {
        int v_int;
        int v_bool;
        double v_real;
        char v_char;
        char* v_string;
    } value;
    
} Variable;

typedef struct Function
{
    int return_type;
    int params[100];
    int params_size;
} Function;

typedef struct Procedure
{
    int params[100];
    int params_size;
} Procedure;

typedef struct Symbol_Entry
{
    char *  name;
    int     type;
    union 
    {
        Function    f_data;
        Procedure   p_data;
        Variable    v_data;
    }data;
    struct Symbol_Entry * next;
} Symbol_Entry;


typedef struct Symbol_Table
{
    int scope;
    Symbol_Entry * symbol_head; //simbolos definidos no escopo atual
    struct Symbol_Table * parent;  //utilizar para busca de simbolo no "escopo-pai"

} Symbol_Table;

Function * get_function_symbol(Symbol_Table * symbolTable, char * functionName);
int get_function_return_type(Symbol_Table * symbolTable, char * functionName);

Symbol_Table * create_symbol_table(Symbol_Table * parent, int scope);
void insert_symbol(Symbol_Table * symbolTable, Symbol_Entry symbol);
Symbol_Entry * search_symbol(Symbol_Table * symbolTable, char * name);
Symbol_Entry * get_last_symbol_in_table(Symbol_Table * symbolTable);

#endif