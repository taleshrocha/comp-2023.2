#include <stdio.h>
#include "code_generation.h"

CommandEntry commands[100];
// CommandEntry* commands = malloc(sizeof(CommandEntry)*100);
int command_counter = 0;
// char** label_list = malloc(sizeof(*char)*100);
// int label_counter = 0;

int temp_var_counter = 0;
int short_circuit_label_counter = 0;

void new_command(int operator, char * result,char * op1,char * op2) {
	commands[command_counter].result = result;
	commands[command_counter].operator = operator;
	commands[command_counter].op1 = op1;
	commands[command_counter].op2 = op2;
    command_counter++;
}

void generate_cmd(CommandEntry * entry){
	switch(entry->operator){
        // criação de variável
		case C_VAR: 
            printf("%s %s;\n", entry->op1, entry->op2);
			break;
        // atribuição de valor simples
		case C_ATTRIB: 
            printf("%s = %s;\n", entry->result, entry->op1);
			break;
		// branching
        case C_IF: 
            printf("if %s goto %s;\n", entry->op1, entry->op2);
            break;
		case C_GOTO:
            printf("goto %s;\n", entry->op1);
            break;
		case C_LABEL:
            printf("%s:\n", entry->op1);
            break;
        // Operadores aritméticos
        case C_ADD:
            printf("%s = %s + %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_SUBTRACT:
            printf("%s = %s - %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_MULTIPLICATE:
            printf("%s = %s * %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_DIVIDE:
            printf("%s = %s / %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_MODULE:
            printf("%s = %s %% %s;\n", entry->result, entry->op1, entry->op2);
			break;
        // Operadores relacionais
        case C_GREATER:
            printf("%s = %s > %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_LESSER:
            printf("%s = %s < %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_GEQ:
            printf("%s = %s >= %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_LEQ:
            printf("%s = %s <= %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_EQ:
            printf("%s = %s == %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_NEQ:
            printf("%s = %s != %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_CAST:
            printf("%s = (%s) %s;\n", entry->result, entry->op1, entry->op2);
			break;
        // Operadores unários
        case C_NOT:
            printf("%s = !%s;\n", entry->result, entry->op1);
			break;
        case C_MINUS:
            printf("%s = -%s;\n", entry->result, entry->op1);
			break;
        case C_PLUS:
            printf("%s = +%s;\n", entry->result, entry->op1);
			break;
        // Comandos de entrada e saida
        case C_PRINT:
            printf("printf(%s%s);\n", entry->op1, entry->op2);
			break;
        case C_READ:
            printf("scanf(\"%%s\", &%s);\n", entry->result);
			break;
	}
}


