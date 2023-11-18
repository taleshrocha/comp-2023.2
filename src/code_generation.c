#include <stdio.h>
#include "code_generation.h"
#include "symtab.h"
#include <stdio.h>
#include <string.h>
#include <exception.h>
#include <stdint.h>

CommandEntry vars_commands[100];
int var_counter = 0;

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
            printf("\t%s %s;\n", entry->op1, entry->op2);
			break;
        // atribuição de valor simples
		case C_ATTRIB: 
            printf("\t%s = %s;\n", entry->result, entry->op1);
            // Register temp;
            // create_Register(&temp, &entry->result);
			break;
		// branching
        case C_IF: 
            printf("\tif (%s) goto %s;\n", entry->op1, entry->op2);
            break;
        case C_IFN: 
            printf("\tif (!%s) goto %s;\n", entry->op1, entry->op2);
            break;
		case C_GOTO:
            printf("\tgoto %s;\n\n", entry->op1);
            break;
		case C_LABEL:
            printf("%s:\n\n", entry->op1);
            break;
        // Operadores aritméticos
        case C_ADD:
            printf("\t%s = %s + %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_SUBTRACT:
            printf("\t%s = %s - %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_MULTIPLICATE:
            printf("\t%s = %s * %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_DIVIDE:
            printf("\t%s = %s / %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_MODULE:
            printf("\t%s = %s %% %s;\n", entry->result, entry->op1, entry->op2);
			break;
        // Operadores relacionais
        case C_GREATER:
            printf("\t%s = %s > %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_LESSER:
            printf("\t%s = %s < %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_GEQ:
            printf("\t%s = %s >= %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_LEQ:
            printf("\t%s = %s <= %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_EQ:
            printf("\t%s = %s == %s;\n", entry->result, entry->op1, entry->op2);
			break;
        case C_NEQ:
            printf("\t%s = %s != %s;\n", entry->result, entry->op1, entry->op2);
			break;
        // Operadores unários
        case C_NOT:
            printf("\t%s = !%s;\n", entry->result, entry->op1);
			break;
        case C_MINUS:
            printf("\t%s = -%s;\n", entry->result, entry->op1);
			break;
        case C_PLUS:
            printf("\t%s = +%s;\n", entry->result, entry->op1);
			break;
        // Comandos de entrada e saida
        case C_PRINT:
            printf("\tprintf(%s%s);\n", entry->op1, entry->op2);
			break;
        case C_READ:
            printf("\tscanf(\"%%s\", %s);\n", entry->result);
			break;
        // Comandos de coerção
        case C_CAST:
            printf("\t%s = (%s) %s;\n", entry->result, entry->op1, entry->op2);
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
            for (size_t i = 0; i < symbol->data.sp_data.params_size; i++){
                strcat(command, get_c_type(symbol->data.sp_data.params_types[i]));
                if (symbol->data.sp_data.ref_flags[i]) {
                    strcat(command, "*");
                }
                strcat(command, " ");
                strcat(command, symbol->name);
                strcat(command, "_");
                strcat(command, symbol->data.sp_data.params_names[i]);
                strcat(command, "[100];\n");
            }
            
            if (symbol->data.sp_data.return_type != 0) {
                strcat(command, get_c_type(symbol->data.sp_data.return_type));
                strcat(command, " ");
                strcat(command, symbol->name);
                strcat(command, "_return_value[100];\n");
            }

            // return control
            strcat(command, "int ");
            strcat(command, symbol->name);
            strcat(command, "_return_control[100];\n");            

            //stack control
            strcat(command, "int ");
            strcat(command, symbol->name);
            strcat(command, "_stack_control;\n");

            // call control
            strcat(command, "int ");
            strcat(command, symbol->name);
            strcat(command, "_call_control;\n");

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
            // strcat(command, "typedef ");
            // strcat(command, get_c_type(symbol->data.s_data.inner_type));
            // strcat(command, " ");
			// strcat(command, symbol->name);
			// strcat(command, ";\n\n");
            break;
	}
	printf("%s\n",command);
	new_command(C_TYPE, strdup(command), "", "");

}


void generate_return_control() {
    Symbol_Table* scope = getCurrentScope();
    while(scope->parent != NULL){
        scope = scope->parent;
    }
    for (size_t i = 0; i < scope->symbol_size; i++){
        Symbol_Entry* symbol = scope->symbols[i];
        if(symbol->symbol_type == K_SUBPROGRAM){
            printf("\t%s_return:\n", symbol->name);
            printf("switch (%s_stack_control) {\ncase 0:\n", symbol->name);
            printf("switch (%s_call_control) {\n", symbol->name);
            for(int i = 0; i < symbol->data.sp_data.num_calls; i++){
                printf("case %d:\n", i);
                printf("goto %s_%d;\n", symbol->name, i);

            }
            // printf("}\ndefault:\n%s_stack_control--;\ngoto %s_rec;\n}\n", symbol->name, symbol->name);
            printf("}\n}\n");
        }
    }
    
}