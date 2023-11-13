%{
#include <stdio.h>
#include <stdbool.h>
#include "lexer.l.h"
#include "symtab.h"
#include "exception.h"
#include "code_generation.h"

extern int command_counter;
extern CommandEntry commands[100];

int args_types[16];
char args_names[16][32];
short ref_flags[16];
size_t args_size;
int type_counter = 10;

char temp_vars[256][10];
int temp_var_count;

char temp_flags[256][10];
int temp_flag_count;

char loop_flags[256][10];
int loop_flag_count;

char exit_labels[256][10];
int exit_labels_count;

int current_return_type = 0;

char functionName[256];

char temp_name[256];

extern int column_counter;
char message[256];

void yyerror(char* s, ...) {
    va_list vars;
    va_start(vars, s);
    sprintf(message, "%s at line %d - column %d\n", s, yylineno, column_counter);
    printMessage(ERROR, message, vars);
    va_end(vars);
}

%}

%union {
    struct {
        char* var;
        int type;
        char* name;
        char label[10];
        int is_constant;
        union {
            int v_int;
            int v_bool;
            double v_real;
            char v_char;
            char* v_string;
        } value;
    } info;
    struct {
        int type;
        char* name;
        short to_rename;
        union {
            struct {
                char field_names[16][32];
                int field_types[16];
                int n_fields;
            } record_data;
            struct {
                int inner_type;
                int capacity;
                int start;
                int end;
            } array_data;
        };
    } type_info;
    struct {
        int capacity;
        int start;
        int end;
    } interval;

}

%token CONST ATTRIB SEMICOLON OR AND NEQ EQ LESS GREATER LEQ GEQ NOT PLUS MINUS MULTIPLY DIVIDE MOD LPAR RPAR DOT LBRA RBRA TYPE OF END INTERVAL COMMA COLON PROCEDURE FUNCTION VAR BEGIN_ FOR TO STEP LOOP EXIT WHEN CONTINUE BREAK IF THEN ELSE RETURN REF PRINT READ

%token <info> ID V_INT V_REAL V_BOOL V_CHAR V_STRING 
%token <type_info> T_BOOL T_INT T_REAL T_CHAR T_STRING ARRAY RECORD

%type <info> NumExp SimpleExp CastExp UnaryExp Parenthesis AriOp2 AriOp Factor Comps Terms Exp CmdReturnExp AcessMemAddr Args CmdPrint
%type <type_info> TypeDec 
%type <interval> Interval

%type  PrintArgs


%start Prog 

%%

Prog : 
    {
        pushScope();
        printf("#include <stdio.h>\n");
        printf("#include <stdbool.h>\n");
        printf("#include <stdlib.h>\n\n");
    } 
    Decl {
        
        printf("int main() {\n");
        } CmdBlock {
        // TODO free das tabelas
        #ifdef DEBUG
        printf(
            "\n\nFreeing stack and symbol tables.\n"
        );
        #endif
        freeScopes();
        for(int i = 0; i < command_counter; i++) {
            generate_cmd(&commands[i]);
        }
        printf("return 0;\n");
        printf("}\n");

    }
;
Decl : 
    Consts Types Vars SubProg {}
;
Consts :
    CONST ID ATTRIB Exp SEMICOLON {
        commit_commands();
        if (!$4.is_constant) {
            printf("Expression %s must be constant", $4.name);
        }
        Symbol_Entry * newSymbol = malloc(sizeof(Symbol_Entry));
        newSymbol->name = $2.name;
        newSymbol->symbol_type = K_VARIABLE;

        Variable var_data;
        var_data.is_constant = 1;
        var_data.type = $4.type;

        // printf("%s %s;\n", get_c_type($4.type), $2.name);
        new_command(C_VAR, NULL, strdup(get_c_type($4.type)), strdup($2.name));
        switch ($4.type) {
            case E_INT:
                var_data.value.v_int = $4.value.v_int;
                // printf("%s = %d;\n", $2.name, $4.value.v_int);
                sprintf(temp_name, "%d", $4.value.v_int);
                new_command(C_ATTRIB, strdup($2.name), strdup(temp_name), NULL);
                break;
            case E_REAL:
                var_data.value.v_real = $4.value.v_real;
                // printf("%s = %f;\n", $2.name, $4.value.v_real);
                sprintf(temp_name, "%f", $4.value.v_real);
                new_command(C_ATTRIB, strdup($2.name), strdup(temp_name), NULL);
                break;
            case E_BOOL:
                var_data.value.v_bool = $4.value.v_bool;
                // printf("%s = %d;\n", $2.name, $4.value.v_bool);
                sprintf(temp_name, "%d", $4.value.v_bool);
                new_command(C_ATTRIB, strdup($2.name), strdup(temp_name), NULL);
                break;
            case E_CHAR:
                var_data.value.v_char = $4.value.v_char;
                // printf("%s = %c;\n", $2.name, $4.value.v_char);
                sprintf(temp_name, "%c", $4.value.v_char);
                new_command(C_ATTRIB, strdup($2.name), strdup(temp_name), NULL);
                break;
            case E_STRING:
                var_data.value.v_string = $4.value.v_string;
                // printf("%s = %s;\n", $2.name, $4.value.v_string);
                new_command(C_ATTRIB, strdup($2.name), strdup($4.value.v_string), NULL);
                break;
        }
        newSymbol->data.v_data = var_data;
        insertSymbol(getCurrentScope(), newSymbol);
        #ifdef DEBUG
        printCurrentScope(getCurrentScope());
        #endif
        

    } Consts
|   /* NOTHING */
;
Vars : 
    VAR ID COLON TypeDec SEMICOLON {
        Symbol_Entry * newSymbol = malloc (sizeof(Symbol_Entry));
        newSymbol->name = $2.name;
        newSymbol->symbol_type = K_VARIABLE;

        Variable var_data;
        var_data.type = $4.type;
        var_data.is_constant = 0;
        newSymbol->data.v_data = var_data;

        insertSymbol(getCurrentScope(), newSymbol);

        #ifdef DEBUG
        printCurrentScope(getCurrentScope());
        #endif

        free($4.name);

        new_command(C_VAR, NULL, strdup(get_c_type($4.type)), strdup($2.name));
        switch ($4.type) {
            case E_INT:
                // printf("%s = %d;\n", $2.name, 0);
                new_command(C_ATTRIB, strdup($2.name), "0", NULL);
                break;
            case E_REAL:
                // printf("%s = %f;\n", $2.name, 0.0);
                new_command(C_ATTRIB, strdup($2.name), "0.0", NULL);
                break;
            case E_BOOL:
                // printf("%s = %d;\n", $2.name, 1);
                new_command(C_ATTRIB, strdup($2.name), "false", NULL);
                break;
            case E_CHAR:
                // printf("%s = %s;\n", $2.name, "''");
                new_command(C_ATTRIB, strdup($2.name), "''", NULL);
                break;
            case E_STRING:
                // printf("%s = %s;\n", $2.name, "\"\"");
                new_command(C_ATTRIB, strdup($2.name), "malloc(sizeof(char)*100)", NULL);
                // TODO:
                // to_free_later(strdup($2.name));
                break;
        }
    } Vars
|   {/*printf("end of vars\n");*/}/* NOTHING */
;
Types :
    TYPE ID ATTRIB TypeDec SEMICOLON {
	    Symbol_Entry* entry = NULL;
        if ($4.to_rename == 0){ 
            entry = malloc(sizeof(Symbol_Entry));
            entry->symbol_type = K_SIMPLETYPE;
            SimpleType data;
            data.inner_type = $4.type;
            entry->name = strdup($2.name);
            entry->data.s_data = data;
            data.type_id 	= 	type_counter++;
        	insertSymbol(getCurrentScope(), entry);
        } else {
            entry = searchSymbol(getCurrentScope(), $4.name, 1);
            free(entry->name);
            entry->name = $2.name;
        }

	    create_command(entry);
        
        #ifdef DEBUG
        printCurrentScope(getCurrentScope());
        #endif
    } Types
|   /* NOTHING */
;

TypeDec :
    T_BOOL {
        $$.type = E_BOOL;
        $$.name = $1.name;
        $$.to_rename = 0;
    }
|   T_INT  {
        $$.type = E_INT;
        $$.name = $1.name;
        $$.to_rename = 0;
    }
|   T_REAL {
        $$.type = E_REAL;
        $$.name = $1.name;
        $$.to_rename = 0;
    }
|   T_STRING {
        $$.type = E_STRING;
        $$.name = $1.name;
        $$.to_rename = 0;
    }
|   T_CHAR {
        $$.type = E_CHAR;
        $$.name = $1.name;
        $$.to_rename = 0;
    }
|   ID     {
        $$.name = $1.name;
        $$.type = searchType($$.name);
        $$.to_rename = 0;
    }
|   ARRAY LBRA Interval RBRA OF TypeDec  {
		
		Symbol_Entry * newSymbol = malloc(sizeof(Symbol_Entry));
        newSymbol->symbol_type = K_ARRAY;
        Array data;
        data.inner_type =	$6.type;
        data.type_id 	= 	type_counter++;
        $$.type = data.type_id;
        newSymbol->name = (char*) malloc(sizeof(char) * 32);
        sprintf(newSymbol->name, "ARRAY %d", data.type_id);
        $$.name = strdup(newSymbol->name);
        $$.to_rename = 1;
        data.capacity = $3.capacity;
        data.start = $3.start;
        data.end = $3.end;
        newSymbol->data.a_data = data;
        Symbol_Table* scope = getCurrentScope();
        while(scope->parent != NULL){
            scope = scope->parent;
        }
        insertSymbol(scope, newSymbol);
        free($6.name);
    }
|   RECORD {args_size=0;} Fields END {
		Symbol_Entry * newSymbol = malloc(sizeof(Symbol_Entry));
        newSymbol->symbol_type = K_RECORD;
        Record data;
	
        for(size_t i = 0; i < args_size; i++){
        	data.field_types[i] = args_types[i];
            strcpy(data.field_names[i], args_names[i]);
        }
        data.n_fields 	= args_size;
        data.type_id 	= type_counter++;
        $$.type = data.type_id;

        newSymbol->name = (char*) malloc(sizeof(char) * 32);

        sprintf(newSymbol->name, "RECORD %d", data.type_id);
        $$.name = strdup(newSymbol->name);
        $$.to_rename = 1;
        newSymbol->data.r_data = data;
        Symbol_Table* scope = getCurrentScope();
        while(scope->parent != NULL){
            scope = scope->parent;
        }
        insertSymbol(scope, newSymbol);
        args_size=0;
    }
;
Interval :
    Exp INTERVAL Exp {
        if ($1.type == E_INT && $3.type == E_INT) {
            if($3.value.v_int - $1.value.v_int <= 0){
            	printf("intervals cannot be negative.");
            }
            $$.capacity = $3.value.v_int - $1.value.v_int;
            $$.start = $1.value.v_int;
            $$.end = $3.value.v_int;
        } else {
            printf("intervals can only be defined with integer values.");
        }
        free($1.name);
        free($3.name);
    }
;
Fields :
    ID COLON TypeDec {
    	args_types[args_size] = $3.type;
        strcpy(args_names[args_size], $1.name);
        free($1.name);
        free($3.name);
    	args_size++;

        // Checagem de campos com mesmo nome
        for(size_t i = 0; i < args_size; i++){
            for(size_t j = i+1; j < args_size; j++){
                if(strcmp(args_names[i], args_names[j]) == 0){
                    printf(
                        "duplicate member %s.\n",
                        args_names[i]
                    );
                }
            }
        }
    } SEMICOLON Fields {}
|   /* NOTHING */ {}
;
SubProg : 
    ProcedureDecl SubProg {}
|   FunctionDecl SubProg {}
|   /* NOTHING */ {}
;

ProcedureDecl :
    PROCEDURE ID LPAR {args_size=0;} Parameters RPAR {
        #ifdef DEBUG
        printf("\n\tProcessing procedure...\n\n");
        #endif
        Symbol_Entry * newSymbol = malloc (sizeof(Symbol_Entry));

        #ifdef DEBUG
        printf("Procedure name: %s\n", $2.name);
        #endif
        newSymbol->name = $2.name;
        newSymbol->symbol_type = K_SUBPROGRAM;

        SubProgram procedure;
        #ifdef DEBUG
        printf("\nIDENTIFIED PARAMETERS - PROCEDURE: %s\n", $2.name);
        #endif

        for(size_t i = 0; i < args_size; i++){
            procedure.params_types[i] = args_types[i];
            strcpy(procedure.params_names[i], args_names[i]);
            procedure.ref_flags[i] = ref_flags[i];
            #ifdef DEBUG
            printf(
                "\tParam %ld Type: %d\n", 
                i+1, args_types[i]
            );
            #endif
        }
        procedure.params_size = args_size;
        procedure.return_type = 0;

        newSymbol->data.sp_data = procedure;

        insertSymbol(getCurrentScope(), newSymbol);
        
    } CmdBlock SEMICOLON
    {
        // #ifdef DEBUG
        // printf("\n\t End of Procedure...\n");
        // #endif
    }
;

Parameters:
    ID COLON TypeDec { 
        strcpy(args_names[args_size], $1.name);
        ref_flags[args_size] = 0; 
        args_types[args_size++] = $3.type; 

        // Checagem de parametros com mesmo nome
        for(size_t i = 0; i < args_size; i++){
            for(size_t j = i+1; j < args_size; j++){
                if(strcmp(args_names[i], args_names[j]) == 0){
                    printf(
                        "duplicate parameter %s.\n",
                        args_names[i]
                    );
                }
            }
        }

        free($1.name);
        free($3.name);
    } ParametersAux
|   REF ID COLON TypeDec {
        strcpy(args_names[args_size], $2.name);
        ref_flags[args_size] = 1; 
        args_types[args_size++] = $4.type;

        // Checagem de parametros com mesmo nome
        for(size_t i = 0; i < args_size; i++){
            for(size_t j = i+1; j < args_size; j++){
                if(strcmp(args_names[i], args_names[j]) == 0){
                    printf(
                        "duplicate parameter %s.\n",
                        args_names[i]
                    );
                }
            }
        }

        free($2.name);
        free($4.name);
    } ParametersAux
|   /* NOTHING */ {}
;

ParametersAux:
    COMMA Parameters { }
|   /* NOTHING */ {}
;

FunctionDecl:
    FUNCTION ID LPAR {args_size=0;} Parameters RPAR COLON TypeDec {
        #ifdef DEBUG
        printf("\n\tProcessing function...\n\n");
        #endif
        Symbol_Entry * newSymbol = malloc (sizeof(Symbol_Entry));
        #ifdef DEBUG
        printf("Function name: %s\n", $2.name);
        #endif
        newSymbol->name = $2.name;
        newSymbol->symbol_type = K_SUBPROGRAM;

        SubProgram function;
        #ifdef DEBUG
        printf("Return type: %d\n", $8.type);
        #endif
        function.return_type = $8.type;
        #ifdef DEBUG
        printf("\nIDENTIFIED PARAMETERS - FUNCTION: %s\n", $2.name);
        #endif

        for(size_t i = 0; i < args_size; i++){
            function.params_types[i] = args_types[i];
            strcpy(function.params_names[i], args_names[i]);
            function.ref_flags[i] = ref_flags[i];
            #ifdef DEBUG
            printf(
                "\tParam %ld Type: %d\n", 
                i+1, args_types[i]
            );
            #endif
        }

        function.params_size = args_size;
        newSymbol->data.sp_data = function;

        // criar registro na tabela
        insertSymbol(getCurrentScope(), newSymbol);
        strcpy(functionName, $2.name);
        // apagar os dados de parametros após salvar a função na tabela de simbolos
        //args_size=0; // Comentado para nao ser zerado 
                        //- ainda falta inserir os parametros na tabela de simbolos da funcao
        current_return_type = function.return_type;
    } CmdBlock SEMICOLON
    {
        current_return_type = 0;
        #ifdef DEBUG
        printf("\n\t End of Function...\n");
        #endif
        strcpy(functionName, "");
    }
;

CmdBlock :
    BEGIN_ {
        #ifdef DEBUG
        printCurrentScope(getCurrentScope());
        #endif
        pushScope();
        if(args_size > 0 && args_size < 101){
            for(size_t i = 0; i < args_size; i++){
                Symbol_Entry * newSymbol = malloc (sizeof(Symbol_Entry));
                newSymbol->name = strdup(args_names[i]);
                newSymbol->symbol_type = 0;

                Variable var_data;
                var_data.type = args_types[i];
                var_data.is_constant = 0;
                newSymbol->data.v_data = var_data;

                // criar registro na tabela
                insertSymbol(getCurrentScope(), newSymbol);
            }
            args_size=0;
        }
    } Vars Cmds 
    END {
        #ifdef DEBUG
        printCurrentScope(getCurrentScope());
        #endif
        popScope();  //Leaving scope, returning to the last scope (which is the parent scope)
    }
;

Cmds:
    CmdAux {}
|   CmdAux SEMICOLON Cmds {}
;

CmdAux:
    AcessMemAddr
|   AcessMemAddr ATTRIB Exp {
        commit_commands();
        if ($1.type > 9) {
            printf("Type of '%s' ('%s') cannot be assigned directly.", $1.name, type_name($1.type));
        }
        if ($3.type > 9) {
            printf("Type of '%s' ('%s') cannot be assigned to a variable.", $3.name, type_name($3.type));
        }
        if($1.type != $3.type){
            printf(
                "Type of '%s' ('%s') is different from the type of the value assigned ('%s').",
                $1.name, type_name($1.type), type_name($3.type)
            );
        }
        
        new_command(C_ATTRIB, strdup($1.var), strdup($3.var), NULL);

        if ($1.name != NULL) {
            free($1.name);
            $1.name = NULL;
        }
        if ($3.name != NULL) {
            free($3.name);
            $3.name = NULL;
        }
    }
|   CmdBlock {}
|   CmdConditional {}
|   CONTINUE {
        if (exit_labels_count <= 0) {
            printf("Continue must be inside a loop.\n");
        } else {
            new_command(C_GOTO, NULL, loop_flags[loop_flag_count-1], NULL);
        }
}
|   BREAK {
        if (exit_labels_count <= 0) {
            printf("Break must be inside a loop.\n");
        } else {
            new_command(C_GOTO, NULL, exit_labels[exit_labels_count-1], NULL);
        }
}
|   FOR AcessMemAddr ATTRIB Exp TO {
        commit_commands();
        new_command(C_ATTRIB, strdup($2.var), strdup($4.var), NULL);
        char* label1 = create_label('L');
        char* label2 = create_label('E');
        char* label3 = create_label('C');
        strcpy(loop_flags[loop_flag_count++], label1);
        strcpy(loop_flags[loop_flag_count++], label3);
        strcpy(exit_labels[exit_labels_count++], label2);
} Exp {
    commit_commands();
    char* temp_var = create_label('b');
    new_command(C_LABEL, NULL, strdup(loop_flags[loop_flag_count-2]), NULL);
    new_command(C_VAR, NULL, "bool", strdup(temp_var));
    new_command(C_GREATER, strdup(temp_var), strdup($2.var), strdup($7.var));
    new_command(C_IF, NULL, strdup(temp_var), strdup(exit_labels[exit_labels_count-1]));
} 
STEP Exp CmdBlock {
        new_command(C_LABEL, NULL, strdup(loop_flags[--loop_flag_count]), NULL);
        commit_commands();
        new_command(C_ADD, strdup($2.var), strdup($2.var), strdup($10.var));
        new_command(C_GOTO, NULL, loop_flags[--loop_flag_count], NULL);
        new_command(C_LABEL, NULL, strdup(exit_labels[--exit_labels_count]), NULL);
        if ($2.type != E_INT) {
            printf("Type of '%s' must be int.", $2.name);
        }
        if ($4.type != E_INT) {
            printf("Type of '%s' must be int.", $4.name);
        }
        if ($7.type != E_INT) {
            printf("Type of '%s' must be int.", $7.name);
        }
        if ($10.type != E_INT) {
            printf("Type of '%s' must be int.", $10.name);
        }

    }
|   LOOP {pushScope();} Vars {
        char* label1 = create_label('L');
        char* label2 = create_label('E');
        strcpy(loop_flags[loop_flag_count++], label1);
        strcpy(exit_labels[exit_labels_count++], label2);
        new_command(C_LABEL, NULL, strdup(label1), NULL);
        
} Cmds {
    new_command(C_GOTO, NULL, strdup(loop_flags[--loop_flag_count]), NULL);
} END {
    new_command(C_LABEL, NULL, strdup(exit_labels[--exit_labels_count]), NULL);
    popScope();
}
|   EXIT WHEN Exp { 
        commit_commands();
        if ($3.type != E_BOOL) {
            printf("Type of '%s' must be boolean.", $3.name);
        } else {
            if (exit_labels_count <= 0) {
                printf("Exit when must be inside a loop.\n");
            } else {
                new_command(C_IF, NULL, strdup($3.var), exit_labels[exit_labels_count-1]);
            }
        }
    }
|   CmdReturn {}
|   CmdPrint {}
|   CmdRead {}
;

AcessMemAddr: 
    ID {
        Symbol_Table* tabela = getCurrentScope();
        Symbol_Entry* entry = searchSymbol(tabela, $1.name, 1);
        if(entry == NULL){
            printf("Symbol '%s' not found.", $1.name);
        } else {
            switch(entry->symbol_type) {
                case 0:
                    $$.type = entry->data.v_data.type;
                    $$.is_constant = entry->data.v_data.is_constant;
                    if ($$.is_constant) {
                        switch ($$.type) {
                            case E_INT:
                                $$.value.v_int = entry->data.v_data.value.v_int;
                                sprintf(temp_name, "%d", $$.value.v_int);
                                $$.var = strdup(temp_name);
                                break;
                            case E_REAL:
                                $$.value.v_real = entry->data.v_data.value.v_real;
                                sprintf(temp_name, "%d", $$.value.v_int);
                                $$.var = strdup(temp_name);
                                break;
                            case E_BOOL:
                                $$.value.v_bool = entry->data.v_data.value.v_bool;
                                sprintf(temp_name, "%d", $$.value.v_int);
                                $$.var = strdup(temp_name);
                                break;
                            case E_CHAR:
                                $$.value.v_char = entry->data.v_data.value.v_char;
                                sprintf(temp_name, "%d", $$.value.v_int);
                                $$.var = strdup(temp_name);
                                break;
                            case E_STRING:
                                $$.value.v_string = entry->data.v_data.value.v_string;
                                sprintf(temp_name, "%d", $$.value.v_int);
                                $$.var = strdup(temp_name);
                                break;
                        }
                    } else {
                        $$.var = $1.name;
                    }
                    break;
                default:
                    printf("Identifier %s is not a variable or constant!", $1.name);
            }
        }
        $$.name = $1.name;
    }
|   AcessMemAddr DOT ID {
        Symbol_Entry* entry = searchRecordType($1.type);
        if(entry == NULL){
            printf("Symbol '%s' not a record, its type is %d.", $1.name, $1.type);
        } else {
            bool found = false;
            for(int i = 0; i < entry->data.r_data.n_fields; i++){
                if(strcmp(entry->data.r_data.field_names[i], $3.name) == 0){
                    $$.type = entry->data.r_data.field_types[i];
                    $$.is_constant = $1.is_constant;
                    found = true;
                    break;
                }
            }
            if (!found){
                $$.type = E_UNDEFINED;
                printf("campo não encontrado\n");
                // TODO: adicionar erro
            }
        }
        $$.name = strdup($1.name); // todo: concatenar $1.name e $3.name
        // FIX: correção para geração de codigo - comando atribuição envolvendo struct
        char*temp;
        if(strlen($$.var) > 0){
            temp=strdup($$.var);
            strcat(temp, ".");
            strcat(temp, strdup($3.name));
        }
        else{
            temp=strdup($1.name);
            strcat(temp, ".");
            strcat(temp, strdup($3.name));
        }

        $$.var = strdup(temp);
        // free(temp);
        // free($3.name); // todo remover esse free?
    }

|   AcessMemAddr LBRA Exp RBRA {
        commit_commands();
        Symbol_Entry* entry = searchArrayType($1.type);
        if(entry == NULL){
            printf("Symbol '%s' not an array, its type is %s.", $1.name, type_name($1.type));
        } else {
            $$.type = entry->data.a_data.inner_type;
            if ($3.type != E_INT) {
                printf("Expression used to access position of array is not an integer, is of type %s", type_name($3.type));
            }
        }
        $$.name = $1.name; // TODO: concatenar $1.name e $3.name
        free($3.name); // TODO remover esse free?
    }
|   ID LPAR {args_size=0;} Args RPAR {
    Symbol_Entry* entry = getSubProgram($1.name);
    if (entry == NULL) {
        printf("Symbol '%s' not found.", $1.name);
    } else {
        if (entry->data.sp_data.return_type != -1) {
            $$.type = entry->data.sp_data.return_type;
        }
        if (entry->data.sp_data.params_size == args_size) {
            for (size_t i = 0; i < entry->data.sp_data.params_size; i++) {
                if (args_types[i] != entry->data.sp_data.params_types[i]) {
                    printf("Type of parameter %s is %s but was expected to be %s.", args_names[i], type_name(args_types[i]), type_name(entry->data.sp_data.params_types[i]));
                }
            }
        } else {
            printf("Wrong number of parameters. %ld parameters expected, %ld given", entry->data.sp_data.params_size, args_size);
        }
    }
    args_size=0;
}
;

Args : 
    Exp {
        args_types[args_size++] = $1.type; 
        free($1.name);
    } ArgsAux
|   /* NOTHING */ {}
;

ArgsAux : COMMA Args {}
|   /* NOTHING */ {}
;

CmdConditional:
    IF Exp {
        commit_commands();
        if ($2.type != E_BOOL) {
            printf("Result type of expression in IF statement should be boolean, but was os type %s", type_name($2.type));
        }
        char* label1 = create_label('I');
        char* label2 = create_label('I');
        char* label3 = create_label('I');
        new_command(C_IF, NULL, strdup($2.var), label1);
        new_command(C_GOTO, NULL, label2, NULL);
        new_command(C_LABEL, NULL, strdup(label1), NULL);
        strcpy(temp_flags[temp_flag_count++], label3);
        strcpy(temp_flags[temp_flag_count++], label2);
        strcpy(temp_flags[temp_flag_count++], label3);

    } THEN CmdBlock {
        new_command(C_GOTO, NULL, strdup(temp_flags[--temp_flag_count]), NULL);
        new_command(C_LABEL, NULL, strdup(temp_flags[--temp_flag_count]), NULL);
    } CmdConditionalEnd {
        new_command(C_LABEL, NULL, strdup(temp_flags[--temp_flag_count]), NULL);
    }
;

CmdConditionalEnd:
    ELSE CmdBlock {}
|   /* NOTHING */ {}
;

CmdReturn:
    RETURN CmdReturnExp {
        if (current_return_type != 0 && current_return_type != $2.type) {
            printf("Error: Return type is %s but was expected to be %s.", type_name($2.type), type_name(current_return_type));
        }

        if(strcmp(functionName, "") != 0){
            
            Symbol_Entry * functionSymbol = searchSymbol(getCurrentScope(), functionName, 1);
            if(functionSymbol != NULL){
                if(functionSymbol->data.sp_data.return_type != $2.type){
                    printf(
                        "Type of the return value is not compatible with the '%s' function's return type.\nType %s was expected, but type %s was found.",
                        functionSymbol->name,
                        type_name(functionSymbol->data.sp_data.return_type), 
                        type_name($2.type)
                    );
                }
            }
        }
    }
;

CmdReturnExp:
    Exp { $$.type = $1.type; $$.name = $1.name;}
|   /* NOTHING */ { $$.type = 0;}
;

CmdPrint:
    PRINT LPAR Exp {
        commit_commands();
        if ($3.type != E_STRING) {
            printf("First argument of print must be of type string");
        } else {

        }
    } PrintArgs {
        char* pch = strstr ($3.name,"%r");
        if (pch != NULL)
            memcpy(pch,"%f",2);
        temp_name[0] = '\0';
        for(size_t i = 0; i < args_size; i++){
            strcat(temp_name, ",");
            strcat(temp_name, args_names[i]);
        }
        new_command(C_PRINT, NULL, strdup($3.name), strdup(temp_name));
    } RPAR {
        args_size = 0;
    }
;

PrintArgs:
    COMMA Exp {
        args_types[args_size] = $2.type;
        strcpy(args_names[args_size], $2.name);
        args_size++;
}   PrintArgs
|   /* NOTHING */ {
}
;

CmdRead:
    READ LPAR AcessMemAddr RPAR {
        if ($3.type != E_STRING) {
            printf("%s must be of type String, but is of type %s", $3.name, type_name($3.type));
        }
        if ($3.is_constant) {
            printf("\"%s\" cannot be a constant", $3.name);
        }
        new_command(C_READ, strdup($3.name), NULL, NULL);
    }
;

Exp:
    Terms OR {
        if ($1.type != E_BOOL){
            printf("OR operation must be between bool values but the first arg is %s", type_name($1.type));
        // } else if (!$1.is_constant) {
        } else {
            char* temp_var = create_label('b');
            new_command_bufferized(C_VAR, NULL, "bool", temp_var);
            strcpy(temp_vars[temp_var_count++], temp_var);
            char* label1 = create_label('O');
            new_command_bufferized(C_IF, NULL, strdup($1.var), label1);
            strcpy(temp_flags[temp_flag_count++], label1);
        }
    }
    Exp {
        if ($4.type != E_BOOL){
            printf("OR operation must be between bool values but the first arg is %s", type_name($4.type));
        // } else if (!$4.is_constant) {
        } else  {
            int pos1 = --temp_var_count;
            int pos2 = --temp_flag_count;

            char* label2 = create_label('O');
            new_command_bufferized(C_ATTRIB, strdup(temp_vars[pos1]), strdup($4.var), NULL);
            new_command_bufferized(C_GOTO, NULL, label2, NULL);
            new_command_bufferized(C_LABEL, NULL, strdup(temp_flags[pos2]), NULL);
            new_command_bufferized(C_ATTRIB, strdup(temp_vars[pos1]), strdup($1.var), NULL);
            new_command_bufferized(C_LABEL, NULL, label2, NULL);
            $$.var = strdup(temp_vars[pos1]);
        }
        $$.is_constant = $1.is_constant && $4.is_constant;
        if ($$.is_constant) {
            $$.value.v_bool = $1.value.v_bool || $4.value.v_bool;
        }
        strcpy($$.name, $1.name);
        strcat($$.name, " || ");
        strcat($$.name, $4.name);
    }
|   Terms {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.var = $1.var;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
};

Terms:
    Comps AND {
        if ($1.type != E_BOOL){
            printf("OR operation must be between bool values but the first arg is %s", type_name($1.type));
        } else {
            char* temp_var = create_label('b');
            new_command_bufferized(C_VAR, NULL, "bool", temp_var);
            strcpy(temp_vars[temp_var_count++], temp_var);
            char* label1 = create_label('A');
            new_command_bufferized(C_IFN, NULL, strdup($1.var), label1);
            strcpy(temp_flags[temp_flag_count++], label1);
        }
    }
    Terms {
        if ($4.type != E_BOOL){
            printf("OR operation must be between bool values but the first arg is %s", type_name($4.type));
        } else {
            int pos1 = --temp_var_count;
            int pos2 = --temp_flag_count;

            char* label2 = create_label('A');
            new_command_bufferized(C_ATTRIB, strdup(temp_vars[pos1]), strdup($4.var), NULL);
            new_command_bufferized(C_GOTO, NULL, label2, NULL);
            new_command_bufferized(C_LABEL, NULL, strdup(temp_flags[pos2]), NULL);
            new_command_bufferized(C_ATTRIB, strdup(temp_vars[pos1]), strdup($1.var), NULL);
            new_command_bufferized(C_LABEL, NULL, label2, NULL);
            $$.var = strdup(temp_vars[pos1]);
        }
        $$.is_constant = $1.is_constant && $4.is_constant;
        strcpy($$.name, $1.name);
        strcat($$.name, " && ");
        strcat($$.name, $4.name);
        
    }
|   Comps {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.var = $1.var;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
    }
;

Comps: 
    Factor NEQ Factor {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_int != $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_real != $3.value.v_real;
        } else if ($1.type == E_BOOL && $3.type == E_BOOL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_bool != $3.value.v_bool;
        } else if ($1.type == E_CHAR && $3.type == E_CHAR) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_char != $3.value.v_char;
        }else if($1.type == E_STRING && $3.type == E_STRING){
            $$.type = E_BOOL;
            $$.value.v_bool = strcmp($1.value.v_string, $3.value.v_string) != 0;
        } else {
            printf("Incompatible type for '!=' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        char* temp_var = create_label('b');
        new_command_bufferized(C_VAR, NULL, "bool", temp_var);
        new_command_bufferized(C_NEQ, strdup(temp_var), strdup($1.var), strdup($3.var));
        $$.var = strdup(temp_var);

        $$.is_constant = $1.is_constant && $3.is_constant;
        strcpy($$.name, $1.name);
        strcat($$.name, " != ");
        strcat($$.name, $3.name);
        
    }
|   Factor EQ Factor  {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_int == $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_real == $3.value.v_real;
        } else if ($1.type == E_BOOL && $3.type == E_BOOL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_bool == $3.value.v_bool;
        } else if ($1.type == E_CHAR && $3.type == E_CHAR) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_char == $3.value.v_char;
        }else if($1.type == E_STRING && $3.type == E_STRING){
            $$.type = E_BOOL;
            $$.value.v_bool = strcmp($1.value.v_string, $3.value.v_string) == 0;
        } else {
            printf("Incompatible type for '==' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        char* temp_var = create_label('b');
        new_command_bufferized(C_VAR, NULL, "bool", temp_var);
        new_command_bufferized(C_EQ, strdup(temp_var), strdup($1.var), strdup($3.var));
        $$.var = strdup(temp_var);
        $$.is_constant = $1.is_constant && $3.is_constant;
        strcpy($$.name, $1.name);
        strcat($$.name, " == ");
        strcat($$.name, $3.name);
        
    }
|   Factor LESS Factor {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_int < $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_real < $3.value.v_real;
        } else {
            printf("Incompatible type for '<' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        char* temp_var = create_label('b');
        new_command_bufferized(C_VAR, NULL, "bool", temp_var);
        new_command_bufferized(C_LESSER, strdup(temp_var), strdup($1.var), strdup($3.var));
        $$.var = strdup(temp_var);
        $$.is_constant = $1.is_constant && $3.is_constant;
        strcpy($$.name, $1.name);
        strcat($$.name, " < ");
        strcat($$.name, $3.name);
        
    }
|   Factor GREATER Factor  {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_int > $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_real > $3.value.v_real;
        } else {
            printf("Incompatible type for '>' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        char* temp_var = create_label('b');
        new_command_bufferized(C_VAR, NULL, "bool", temp_var);
        new_command_bufferized(C_GREATER, strdup(temp_var), strdup($1.var), strdup($3.var));
        $$.var = strdup(temp_var);
        $$.is_constant = $1.is_constant && $3.is_constant;
        strcpy($$.name, $1.name);
        strcat($$.name, " > ");
        strcat($$.name, $3.name);
        
    }
|   Factor LEQ Factor {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_int <= $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_real <= $3.value.v_real;
        } else {
            printf("Incompatible type for '<=' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        char* temp_var = create_label('b');
        new_command_bufferized(C_VAR, NULL, "bool", temp_var);
        new_command_bufferized(C_LEQ, strdup(temp_var), strdup($1.var), strdup($3.var));
        $$.var = strdup(temp_var);
        $$.is_constant = $1.is_constant && $3.is_constant;
        strcpy($$.name, $1.name);
        strcat($$.name, " <= ");
        strcat($$.name, $3.name);
        
    }
|   Factor GEQ Factor  {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_int >= $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_real >= $3.value.v_real;
        } else {
            printf("Incompatible type for '>=' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        char* temp_var = create_label('b');
        new_command_bufferized(C_VAR, NULL, "bool", temp_var);
        new_command_bufferized(C_GEQ, strdup(temp_var), strdup($1.var), strdup($3.var));
        $$.var = strdup(temp_var);
        $$.is_constant = $1.is_constant && $3.is_constant;
        strcpy($$.name, $1.name);
        strcat($$.name, " >= ");
        strcat($$.name, $3.name);
        
    }
|   Factor  {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.var = $1.var;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
}
;

Factor:
    NOT AriOp {
        if ($2.type == E_BOOL ) {
            $$.type = E_BOOL;
            $$.value.v_bool = !$2.value.v_bool;
            char* temp_var = create_label('b');
            new_command_bufferized(C_VAR, NULL, "bool", temp_var);
            new_command_bufferized(C_NOT, strdup(temp_var), strdup($2.var), NULL);
            $$.var = strdup(temp_var);
        } else {
            printf("Incompatible type for '!' operation between %s (%s)", $2.name, type_name($2.type));
        }
        $$.is_constant = $2.is_constant;
        strcpy($$.name, " ! ");
        strcat($$.name, $2.name);
        
    }
|   AriOp {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.var = $1.var;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
}
;

AriOp:
    AriOp PLUS AriOp2 {
        char* temp_var;
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = $1.value.v_int + $3.value.v_int;
            temp_var = create_label('i');
            new_command_bufferized(C_VAR, NULL, "int", temp_var);
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = $1.value.v_real + $3.value.v_real;
            temp_var = create_label('f');
            new_command_bufferized(C_VAR, NULL, "float", temp_var);
        } else {
            printf("Incompatible type for '+' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        new_command_bufferized(C_ADD, strdup(temp_var), strdup($1.var), strdup($3.var));
        $$.var = strdup(temp_var);
        $$.is_constant = $1.is_constant && $3.is_constant;
        strcpy($$.name, $1.name);
        strcat($$.name, " + ");
        strcat($$.name, $3.name);
        
    }
|   AriOp MINUS AriOp2 {
        char* temp_var;
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = $1.value.v_int - $3.value.v_int;
            temp_var = create_label('i');
            new_command_bufferized(C_VAR, NULL, "int", temp_var);
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = $1.value.v_real - $3.value.v_real;
            temp_var = create_label('f');
            new_command_bufferized(C_VAR, NULL, "float", temp_var);
        } else {
            printf("Incompatible type for '-' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        new_command_bufferized(C_SUBTRACT, strdup(temp_var), strdup($1.var), strdup($3.var));
        $$.var = strdup(temp_var);
        $$.is_constant = $1.is_constant && $3.is_constant;
        strcpy($$.name, $1.name);
        strcat($$.name, " - ");
        strcat($$.name, $3.name);
        
    }
|   AriOp2 {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.var = $1.var;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
}
;

AriOp2:
    AriOp2 MULTIPLY Parenthesis {
        char* temp_var;
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = $1.value.v_int * $3.value.v_int;
            temp_var = create_label('i');
            new_command_bufferized(C_VAR, NULL, "int", temp_var);
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = $1.value.v_real * $3.value.v_real;
            temp_var = create_label('f');
            new_command_bufferized(C_VAR, NULL, "float", temp_var);
        } else {
            printf("Incompatible type for '*' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        new_command_bufferized(C_MULTIPLICATE, strdup(temp_var), strdup($1.var), strdup($3.var));
        $$.var = strdup(temp_var);
        $$.is_constant = $1.is_constant && $3.is_constant;
        strcpy($$.name, $1.name);
        strcat($$.name, " * ");
        strcat($$.name, $3.name);
        
    }
|   AriOp2 DIVIDE Parenthesis {
        char* temp_var;
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = $1.value.v_int / $3.value.v_int;
            temp_var = create_label('i');
            new_command_bufferized(C_VAR, NULL, "int", temp_var);
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = $1.value.v_real / $3.value.v_real;
            temp_var = create_label('f');
            new_command_bufferized(C_VAR, NULL, "float", temp_var);
        } else {
            printf("Incompatible type for '/' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        new_command_bufferized(C_DIVIDE, strdup(temp_var), strdup($1.var), strdup($3.var));
        $$.var = strdup(temp_var);
        $$.is_constant = $1.is_constant && $3.is_constant;
        strcpy($$.name, $1.name);
        strcat($$.name, " / ");
        strcat($$.name, $3.name);
        
    }
|   AriOp2 MOD Parenthesis {
        char* temp_var;
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = $1.value.v_int % $3.value.v_int;
            temp_var = create_label('i');
            new_command_bufferized(C_VAR, NULL, "int", temp_var);
        } else {
            printf("Incompatible type. - AriOp2 \n");
        }
        new_command_bufferized(C_MODULE, strdup(temp_var), strdup($1.var), strdup($3.var));
        $$.var = strdup(temp_var);
        $$.is_constant = $1.is_constant && $3.is_constant;
        strcpy($$.name, $1.name);
        strcat($$.name, " % ");
        strcat($$.name, $3.name);
        
    }
|   Parenthesis {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.var = $1.var;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
}
;

Parenthesis:
    UnaryExp {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.var = $1.var;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
        
}
|   LPAR Exp RPAR {
        $$.type = $2.type;
        $$.name = $2.name;
        $$.var = $2.var;
        $$.is_constant = $2.is_constant;
        $$.value = $2.value;
        strcpy($$.name, "(");
        strcat($$.name, $2.name);
        strcat($$.name, ")");
        
}
;

UnaryExp:
    PLUS Parenthesis { 
        char* temp_var;
        if ($2.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = + $2.value.v_int;
            temp_var = create_label('i');
            new_command_bufferized(C_VAR, NULL, "int", temp_var);
        } else if ($2.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = + $2.value.v_real;
            temp_var = create_label('f');
            new_command_bufferized(C_VAR, NULL, "float", temp_var);
        } else { 
            printf("Incompatible type. - UnaryExp \n");
        }
        new_command_bufferized(C_PLUS, strdup(temp_var), strdup($2.var), NULL);
        $$.var = strdup(temp_var);
        $$.is_constant = $2.is_constant;
        strcpy($$.name,"+");
        strcat($$.name, $2.name);
        
    }
|   MINUS Parenthesis { 
        char* temp_var;
        if ($2.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = - $2.value.v_int;
            temp_var = create_label('i');
            new_command_bufferized(C_VAR, NULL, "int", temp_var);
        } else if ($2.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = - $2.value.v_real;
            temp_var = create_label('f');
            new_command_bufferized(C_VAR, NULL, "float", temp_var);
        } else { 
            printf("Incompatible type. - UnaryExp \n");
        }
        new_command_bufferized(C_MINUS, strdup(temp_var), strdup($2.var), NULL);
        $$.var = strdup(temp_var);
        $$.is_constant = $2.is_constant;
        strcpy($$.name,"-");
        strcat($$.name, $2.name);
        
        
    }
|   CastExp {
        $$.type = $1.type;
        $$.var = $1.var;
        $$.name = $1.name;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
}
;

CastExp:
    LPAR T_INT RPAR Parenthesis       {
        if ($4.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = $4.value.v_int;
        }
        if ($4.type == E_REAL) {
            $$.type = E_INT;
            $$.value.v_int = $4.value.v_real;
        }
        if ($4.type == E_BOOL) {
            $$.type = E_INT;
            $$.value.v_int = $4.value.v_bool;
        }
        if ($4.type == E_CHAR) {
            $$.type = E_INT;
            $$.value.v_int = $4.value.v_char;
        }
        if ($4.type == E_STRING) {
            printf("string cannot be converted to int!\n");
        }
        char* temp_var = create_label('i');
        new_command_bufferized(C_VAR, NULL, "int", temp_var);
        new_command_bufferized(C_CAST, temp_var, "int", $4.var);
        $$.var = strdup(temp_var);
        $$.is_constant = $4.is_constant;
        $$.name = strdup("(int) ");
        strcat($$.name, $4.name);
    }
|   LPAR T_REAL RPAR Parenthesis      {
        if ($4.type == E_INT) {
            $$.type = E_REAL;
            $$.value.v_real = $4.value.v_int;
        }
        if ($4.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = $4.value.v_real;
        }
        if ($4.type == E_BOOL) {
            $$.type = E_REAL;
            $$.value.v_real = $4.value.v_bool;
        }
        if ($4.type == E_CHAR) {
            $$.type = E_REAL;
            $$.value.v_real = $4.value.v_char;
        }
        if ($4.type == E_STRING) {
            printf("string cannot be converted to real!\n");
        }
        char* temp_var = create_label('f');
        new_command_bufferized(C_VAR, NULL, "float", temp_var);
        new_command_bufferized(C_CAST, temp_var, "float", $4.var);
        $$.var = strdup(temp_var);
        $$.is_constant = $4.is_constant;
        $$.name = strdup("(float) ");
        strcat($$.name, $4.name);
}
|   LPAR T_BOOL RPAR Parenthesis      {
        if ($4.type == E_INT) {
            $$.type = E_BOOL;
            $$.value.v_bool = $4.value.v_int > 0;
        }
        if ($4.type == E_REAL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $4.value.v_real > 0.0;
        }
        if ($4.type == E_BOOL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $4.value.v_bool;
        }
        if ($4.type == E_CHAR) {
            printf("char cannot be converted to bool!");
        }
        if ($4.type == E_STRING) {
            printf("string cannot be converted to bool!");
        }
        char* temp_var = create_label('b');
        new_command_bufferized(C_VAR, NULL, "bool", temp_var);
        new_command_bufferized(C_CAST, temp_var, "bool", $4.var);
        $$.is_constant = $4.is_constant;
        $$.name = strdup("(bool) ");
        strcat($$.name, $4.name);
}
|   LPAR T_CHAR RPAR Parenthesis      {
    if ($4.type == E_INT) {
        printf("int cannot be converted to char!");
    }
    if ($4.type == E_REAL) {
        printf("real cannot be converted to char!");
    }
    if ($4.type == E_BOOL) {
        printf("bool cannot be converted to char!");
    }
    if ($4.type == E_CHAR) {
        $$.type = E_CHAR;
        $$.value.v_char = $4.value.v_char;
        $$.var = $4.var;
    }
    if ($4.type == E_STRING) {
        printf("string cannot be converted to char!");
    }
    $$.is_constant = $4.is_constant;
    $$.name = strdup("(char) ");
    strcat($$.name, $4.name);
}
|   LPAR T_STRING RPAR Parenthesis      {
    printf("Can't convert anything to string!");
    // if ($4.type == E_INT) {
    //     $$.type = E_STRING;
    // }
    // if ($4.type == E_REAL) {
    //     $$.type = E_STRING;
    // }
    // if ($4.type == E_BOOL) {
    //     $$.type = E_STRING;
    // }
    // if ($4.type == E_CHAR) {
    //     $$.type = E_STRING;
    // }
    // if ($4.type == E_STRING) {
    //     $$.type = E_STRING;
    //     $$.var = $4.var;
    // }
    $$.is_constant = $4.is_constant;
    $$.name = strdup("(string) ");
    $$.var = $4.var;
    strcat($$.name, $4.name);
}
|   SimpleExp {
    $$.type = $1.type;
    $$.name = $1.name;
    $$.var = $1.var;
    $$.is_constant = $1.is_constant;
    $$.value = $1.value;
    
}

SimpleExp:
    NumExp {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.var = strdup($1.var);
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
}
|   AcessMemAddr {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.var = $1.var;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
}
;

NumExp:
    V_INT    {
        $$.type = E_INT;
        $$.value.v_int = $1.value.v_int;
        $$.name = $1.name;
        $$.var = $1.name;
        $$.is_constant = 1;
}
|   V_REAL   {
        $$.type = E_REAL;
        $$.value.v_real = $1.value.v_real;
        $$.name = $1.name;
        $$.var = $1.name;
        $$.is_constant = 1;
}
|   V_BOOL   {
        $$.type = E_BOOL;
        $$.value.v_bool = $1.value.v_bool;
        $$.name = $1.name;
        $$.var = $1.name;
        $$.is_constant = 1;
}
|   V_CHAR   {
        $$.type = E_CHAR;
        $$.value.v_char = $1.value.v_char;
        $$.name = $1.name;
        $$.var = $1.name;
        $$.is_constant = 1;
}
|   V_STRING {
        $$.type = E_STRING;
        $$.value.v_string = $1.value.v_string;
        $$.name = $1.name;
        $$.var = $1.name;
        $$.is_constant = 1;
}
;

%%
  
int main(int argc, char const *argv[])
{
    if (argc == 2) {
        yyin=fopen(argv[1],"r");
    }
    int result = yyparse();
    if (result != 0) {
        printf("DEU RUIM");
    }
    /* if (result == 0) {
        printf("parsing was successful\n");
    } else if (result == 1) {
        printf("parsing failed because of invalid input\n");
    } else if (result == 2) {
        printf("parsing failed due to memory exhaustion\n");
    } else {
        printf("other parsing error: %d\n", result);
    } */
    if (argc == 2) {
        fclose(yyin);
    }
    yylex_destroy();
    return 0;
}
