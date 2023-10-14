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

/*   Entry of Symbol Table   */
typedef struct Symbol_Entry
{
    char *  name;
    int     type;
    union 
    {
        Function    f_data;
        Procedure   p_data;
        Variable    v_data;
    } data;
} Symbol_Entry;

/*   Symbol Table (SCOPE)   */
typedef struct Symbol_Table
{
    Symbol_Entry * symbols; //simbolos definidos no escopo atual - array dinamico
    size_t size;
    size_t capacity;
    struct Symbol_Table * parent;  //utilizar para busca de simbolo no "escopo-pai"

} Symbol_Table;




void increaseSymbolTableSize(Symbol_Table * symbolTable);

Function * getFunctionSymbol(Symbol_Table * symbolTable, char * functionName);
int getFunctionReturnType(Symbol_Table * symbolTable, char * functionName);

Symbol_Table * createSymbolTable(Symbol_Table * parent);
Symbol_Entry * insertSymbol(Symbol_Table * symbolTable, Symbol_Entry * symbol);
Symbol_Entry * searchSymbol(Symbol_Table * symbolTable, char * name);

void printCurrentScope(Symbol_Table * symbolTable);

Symbol_Table * getCurrentScope();
Symbol_Table * pushScope(Symbol_Table * scope);
Symbol_Table * popScope();

#endif