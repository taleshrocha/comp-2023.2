#ifndef CODE_GENERATION_H
#define CODE_GENERATION_H

#include "symtab.h"

typedef enum COMMANDS {
    C_VAR,
    C_ATTRIB,
    C_IF,
    C_IFN,
    C_GOTO,
    C_LABEL,
    C_ADD,
    C_SUBTRACT,
    C_MULTIPLICATE,
    C_DIVIDE,
    C_MODULE,
    C_GREATER,
    C_LESSER,
    C_GEQ,
    C_LEQ,
    C_EQ,
    C_NEQ,
    C_CAST,
    C_CAST_INT_STRING,
    C_CAST_REAL_STRING,
    C_CAST_CHAR_STRING,
    C_CAST_BOOL_STRING,
    C_NOT,
    C_MINUS,
    C_PLUS,
    C_PRINT,
    C_READ,
    C_TYPE,
    C_FUNCTION,
} COMMANDS;

typedef struct CommandEntry {
	char * result;
	char * op1;
	char * op2;
	int operator;
} CommandEntry;

void new_command(int operator, char * result,char * op1,char * op2);

void new_command_bufferized(int operator, char * result,char * op1,char * op2);

void commit_commands();
char* create_label(char c);

char* get_c_type(int type_id);

void generate_cmd(CommandEntry * entry);

void create_command(Symbol_Entry * symbol);

void getTestTable(char * name);


#endif // CODE_GENERATION_H
