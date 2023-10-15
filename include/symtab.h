#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h> 
#include <stdlib.h>

typedef enum EntryKind {
  K_VARIABLE,
  K_FUNCTION,
  K_PROCEDURE,
  K_TYPE
} EntryKind;

typedef struct Variable
{
    int is_constant;
    int type;
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
    size_t params_size;
} Function;

typedef struct Type
{
    // record
    char field_names[100][100];
    int field_types[100];
    int n_fields;
    // array
    int inner_type;
    int size;
    int capacity[100];
    int starts[100];
    int ends[100];
    int dimensions;  

    // info
    EntryKind type_kind;

} Type;

typedef struct Procedure
{
    int params[100];
    size_t params_size;
} Procedure;

/*   Entry of Symbol Table   */
typedef struct Symbol_Entry
{
    char *    name;
    EntryKind symbol_type;
    union 
    {
        Variable    v_data;
        Type        t_data;
        Function    f_data;
        Procedure   p_data;
    } data;
} Symbol_Entry;

/*   Symbol Table (SCOPE)   */
typedef struct Symbol_Table
{
    Symbol_Entry ** symbols; //simbolos definidos no escopo atual - array dinamico
    size_t symbol_size;
    size_t symbol_capacity;
    struct Symbol_Table * parent;  //utilizar para busca de simbolo no "escopo-pai"
    struct Symbol_Table ** children;  
    size_t children_size;
    size_t children_capacity;

} Symbol_Table;




void increaseSymbolTableSize(Symbol_Table * symbolTable);
void increaseSymbolTableChildren(Symbol_Table * symbolTable);

Function * getFunctionSymbol(Symbol_Table * symbolTable, char * functionName);
int getFunctionReturnType(Symbol_Table * symbolTable, char * functionName);

Symbol_Entry * insertSymbol(Symbol_Table * symbolTable, Symbol_Entry * symbol);
Symbol_Entry * searchSymbol(Symbol_Table * symbolTable, char * name, int flag);

void printCurrentScope(Symbol_Table * symbolTable);

Symbol_Table * getCurrentScope();
void pushScope();
void popScope();
void freeScopes();
void freeScope();

#endif