#ifndef CODE_GENERATION_H
#define CODE_GENERATION_H

typedef enum COMMANDS {
    C_VAR,
    C_ATTRIB,
    C_IF,
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
    C_NOT,
    C_MINUS,
    C_PLUS,
    C_PRINT,
    C_READ
} COMMANDS;

typedef struct CommandEntry {
	char * result;
	char * op1;
	char * op2;
	int operator;
} CommandEntry;

void new_command(int operator, char * result,char * op1,char * op2);

char* get_c_type(int type_id);

void generate_cmd(CommandEntry * entry);




#endif // CODE_GENERATION_H