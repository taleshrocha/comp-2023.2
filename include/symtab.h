#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h> 
#include <stdlib.h>

typedef enum E_TYPE {
  E_UNDEFINED,
  E_INT,
  E_REAL,
  E_CHAR,
  E_BOOL,
  E_STRING,
  E_ARRAY,
  E_RECORD,
  E_FUNCTION,
  E_PROCEDURE
} E_TYPE;

typedef enum EntryKind {
  K_VARIABLE,
  K_SUBPROGRAM,
  K_ARRAY,
  K_RECORD,
  K_SIMPLETYPE
  
} EntryKind;

typedef struct Variable
{
    int is_constant;
    int is_subprog_var;
    int type;
    union Value {
        int v_int;
        int v_bool;
        double v_real;
        char v_char;
        char* v_string;
    } value;
    
} Variable;

typedef struct SubProgram
{
    int return_type;
    char params_names[16][32];
    int params_types[16];
    short ref_flags[16];
    size_t params_size;
} SubProgram;

typedef struct Record {
	int type_id;
    char field_names[16][32];
    int field_types[16];
    int n_fields;

}Record;

//type type2 := type1;
typedef struct SimpleType {
    int type_id; //identificador unico do tipo (contador)
   	int inner_type;	//tipo dos valores armazenados

}SimpleType;



typedef struct Array
{
	int type_id;
    int inner_type;
    int capacity; // capacidade do array
    int start;   // começo do intervalo
    int end;	  // final do intervalo
} Array;



/*   Entry of Symbol Table   */
typedef struct Symbol_Entry
{
    char *    name;
    EntryKind symbol_type;
    int reference;
    union 
    {
        Variable    v_data;
        Array	    a_data;
        Record      r_data;
        SubProgram  sp_data;
        SimpleType  s_data;
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

Symbol_Entry * getSubProgram(char * functionName);
int getFunctionReturnType(Symbol_Table * symbolTable, char * functionName);

Symbol_Entry * insertSymbol(Symbol_Table * symbolTable, Symbol_Entry * symbol);
Symbol_Entry * searchSymbol(Symbol_Table * symbolTable, char * name, int flag);
int searchType(char * name);
Symbol_Entry * searchRecordType(int type_id);
Symbol_Entry * searchArrayType(int type_id);
void printCurrentScope(Symbol_Table * symbolTable);

Symbol_Table * getCurrentScope();
void pushScope();
void popScope();
void freeScopes();
void freeScope();

char* type_name(int type_id);

char* get_c_type(int type_id);
#endif
