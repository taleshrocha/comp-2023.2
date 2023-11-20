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
int variable = 0;
#define MAX_PARAMS 16 

Register Stack[100]; // Tamanho da pilha (100)


void pushRegister(Register registro) {
	if (top < 99) { // Ajustar o tamanho da pilha
		getScope(&registro);
		Stack[++top] = registro;
		printMessage(SUCCESS, "Registro salvo na stack. \n|Memory Address: %d \n", registro.memoryAddress); 
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

void getStack(char * name) {
    Symbol_Entry* entry = getSubProgram(name);
    if(entry != NULL){
        printf("Function Name: %s \n", entry->name);
        for(size_t i = 0; i < sizeof(entry->data.sp_data.params_size); i++) {
            if(entry->data.sp_data.params_types[i] != 0) {
                printf("Params names: %s \n", entry->data.sp_data.params_names[i]);
                printf("Params types: %d \n", entry->data.sp_data.params_types[i]);
                printf("Ref flags: %d \n", entry->data.sp_data.ref_flags[i]);
            }
        }
    }
}

void getParams(int start) {
    for(int i = 0; i < 16; i++) {
        if(strcmp(Stack[start].params[i], "") != 0) {
            printf("Params saved: %s | type: [%d] | ref: [%d] \n", Stack[start].params[i], Stack[start].paramsType[i], Stack[start].ref_flags[i]);
        }
    }
}

void getLocalVariables(int start) {
	for(int i = 0; i < 16; i++) {
		if(strcmp(Stack[start].localVariables[i], "") != 0) {
			printf("Local variable [%s] | Type [%d] \n", Stack[start].localVariables[i], Stack[start].localTypes[i]);
		}
	}
}


void printSavedFunction(char * name) {
    printf("Checking function saved: %s \n", name);
    for(int i = 0; i < 16; i ++) {
		if(strcmp(Stack[i].functionNames[0], name) == 0) {
			printf("Function name saved: %s \n", Stack[i].functionNames[0]);
			printf("Return type saved: %d \n", Stack[i].functionReturn);
			getParams(i);
			getLocalVariables(i);
		}
    }
}

Register getRegister(char * name) {
	Register nullRegister;
	for(int i = 0; i < 5; i++) {
		if(strcmp(Stack[i].functionNames[0], name) == 0) {
			return Stack[i];
		}
	}
	return nullRegister;
}

int count_aa = 0;

void getScope(Register * temp) {
	Symbol_Table * scope = getCurrentScope();
	Symbol_Table* children = scope->children[count_aa++];
	for(int i = 0; i < children->symbol_size; i++) {
		snprintf(temp->localVariables[i], sizeof(temp->localVariables[i]), "%s", children->symbols[i]->name);
		temp->localTypes[i] = children->symbols[i]->data.v_data.type;
	}
}

void printRegister() {
	printf("Printing Register: \n");
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < Stack[i].sizeofVariables; j++) {
			printf("Name: %s [stack: %d | pos: %d]\n", Stack[i].variables[j], i, j);
            getStack(Stack[i].variables[j]);
		}
	}
}



void createRegister(Register* reg_temp, char ** registro, char * name) {
    reg_temp->memoryAddress = (uintptr_t)registro;
    reg_temp->variables[reg_temp->sizeofVariables] = name;
    Symbol_Entry* entry = getSubProgram(name);
    // reg_temp->functionNames[reg_temp->sizeofVariables] = name;
    snprintf(reg_temp->functionNames[reg_temp->sizeofVariables], sizeof(reg_temp->functionNames[reg_temp->sizeofVariables]), "%s", name);
    if (entry != NULL) {
        size_t paramIndex = 0;
        for (size_t i = 0; i < entry->data.sp_data.params_size; ++i) {
            const char* paramName = entry->data.sp_data.params_names[i];
            if (paramName[0] != '\0') {
                snprintf(reg_temp->params[paramIndex], sizeof(reg_temp->params[paramIndex]), "%s", paramName);
                reg_temp->paramsType[paramIndex] = entry->data.sp_data.params_types[i];
                reg_temp->ref_flags[paramIndex] = entry->data.sp_data.ref_flags[i];
                paramIndex++;
                if (paramIndex >= MAX_PARAMS) {
                    break;
                }
            }
        }
        reg_temp->functionReturn = entry->data.sp_data.return_type;
    } else {
        printMessage(ERROR, "Subprogram not found: %s\n", name);
    }
    printMessage(SUCCESS, "Registro de memória criado: %d \n", reg_temp->memoryAddress);
    printMessage(SUCCESS, "Nome de variável salvo: %s \n", reg_temp->variables[variable]);
    reg_temp->sizeofVariables++;
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
        case C_FUNCTION:
            break;
	}
	// printRegister();
}

Register temp;
Register returnTemp;
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
            temp.sizeofVariables = 0;
            printf("RECEIVED: %s \n", symbol->name);
            createRegister(&temp, &symbol->name, symbol->name);
            pushRegister(temp);
            printSavedFunction(symbol->name);
            returnTemp = getRegister(symbol->name);
            printf("NAME OF RETURNED FUNCTION: %s \n", returnTemp.functionNames[0]); 
            //printSavedFunction(returnTemp.functionNames[0]); checar se a função foi retornada corretamente
            break;
        case K_ARRAY: 
            break;
        case K_SIMPLETYPE: 
            break;


	}
	printf("%s\n",command);
	new_command(C_TYPE, strdup(command), "", "");

}

