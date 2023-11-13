#include <stdio.h>
#include "code_generation.h"
#include "symtab.h"
#include <stdio.h>
#include <string.h>
#include <exception.h>
#include <stdint.h>

CommandEntry buffer_commands[100];
int buffer_counter = 0;

CommandEntry commands[100];
// CommandEntry* commands = malloc(sizeof(CommandEntry)*100);
int command_counter = 0;
// char** label_list = malloc(sizeof(*char)*100);
// int label_counter = 0;

int temp_var_counter = 0;
int short_circuit_label_counter = 0;

static int labels_counter[256] = {0};
/*
On = OR (curto circuito)
An = AND (curto circuito)
In = IF-ELSE
Cn = SUBPROGRAM CALL
Rn = SUBPROGRAM RETURN

in = int temp variable
fn = float temp variable
bn = boolean temp variable
cn = char temp variable
sn = string temp variable
*/
static char labels[1024][8];
static int counter  = 0;

int top = -1;

typedef struct {
	uintptr_t memoryAddress;
	int variables[10];
	int localVariables[10];
} Register;

Register Stack[100]; // Tamanho da pilha (100)

void pushRegister(Register registro) {
	if (top < 99) { // Ajustar o tamanho da pilha
		Stack[++top] = registro;
	} else {
		printMessage(ERROR, "Segmentation Fault. Core dumped!");
	}
}

Register popRegister(Register registro) {
	if(top >= 0) {
		return Stack[top--];
	} else {
		printMessage(ERROR, "Stack empty");
        return registro;

	}
    return registro;
}


void create_Register(Register* reg_temp, char ** registro) {
    reg_temp->memoryAddress = (uintptr_t)registro;
    printMessage(SUCCESS, "Registro de memória criado: %d \n", reg_temp->memoryAddress);
}

    // TODO depois que alcançarmos a funções e procedimentos, precisamos pegar o endereço de memória e colocar na Stack;
    // asm("movl $1f, %0" : "=r" (enderecoDeRetorno));
    // asm("jmp funcaoSecundaria");

void new_command(int operator, char * result,char * op1,char * op2) {
	commands[command_counter].result = result;
	commands[command_counter].operator = operator;
	commands[command_counter].op1 = op1;
	commands[command_counter].op2 = op2;
    command_counter++;
}

void new_command_bufferized(int operator, char * result,char * op1,char * op2) {
	buffer_commands[buffer_counter].result = result;
	buffer_commands[buffer_counter].operator = operator;
	buffer_commands[buffer_counter].op1 = op1;
	buffer_commands[buffer_counter].op2 = op2;
    buffer_counter++;
}

void commit_commands() {
    for(int i = 0; i < buffer_counter; i++) {
        new_command(buffer_commands[i].operator, buffer_commands[i].result, buffer_commands[i].op1, buffer_commands[i].op2);
    }
    buffer_counter = 0;
}

char* create_label(char c) {
    sprintf(labels[counter], "%c%d", c, labels_counter[(int)c]++);
    return labels[counter++];
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
            // Register temp;
            // create_Register(&temp, &entry->result);
			break;
		// branching
        case C_IF: 
            printf("if (%s) goto %s;\n", entry->op1, entry->op2);
            break;
        case C_IFN: 
            printf("if (!%s) goto %s;\n", entry->op1, entry->op2);
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
            printf("scanf(\"%%s\", %s);\n", entry->result);
			break;
        // Comandos de coerção
        case C_CAST:
            printf("%s = (%s) %s;\n", entry->result, entry->op1, entry->op2);
            break;
	}

}


void create_command(Symbol_Entry * symbol){

	char* command = calloc(sizeof(char), 1000);

	switch(symbol->symbol_type){
		
		case K_RECORD: 
			strcat(command, "typedef struct ");
			strcat(command, symbol->name);
			strcat(command, " {\n");
			for(int i = 0; i < symbol->data.r_data.n_fields; i++){
                strcat(command, "\t");
                strcat(command, get_c_type(symbol->data.r_data.field_types[i]));
				strcat(command, " ");
				strcat(command, symbol->data.r_data.field_names[i]);
				strcat(command, ";\n");	
			}
			strcat(command,"} ");
			strcat(command, symbol->name);
			strcat(command, ";\n\n");
			break;
		case K_VARIABLE: 
            break;
        case K_SUBPROGRAM: 
            break;
        case K_ARRAY: 
            strcat(command, "typedef ");
            strcat(command, get_c_type(symbol->data.a_data.inner_type));
            strcat(command, " ");
			strcat(command, symbol->name);
			strcat(command, "[");
            char str[10];
            sprintf(str, "%d", symbol->data.a_data.capacity);
			strcat(command, str);
			strcat(command, "]");
			strcat(command, ";\n\n");
            break;
        case K_SIMPLETYPE: 
            break;


	}
	printf("%s\n",command);
	new_command(C_TYPE, strdup(command), "", "");

}
