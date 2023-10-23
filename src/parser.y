%{
#include <stdio.h>
#include <lexer.l.h>
#include <symtab.h>
#include "exception.h"

int args_types[16];
char args_names[16][32];
short ref_flags[16];
size_t args_size;
int type_counter = 10;

int current_return_type = 0;

char functionName[256];

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
        int type;
        char* name;
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
                int size;
                int capacity[16];
                int starts[16];
                int ends[16];
                int dimensions;
            } array_data;
        };
    } type_info;
    struct {
        int size;
        int capacity[16];
        int starts[16];
        int ends[16];
        int dimensions;  
    } interval;
    

}

%token CONST ATTRIB SEMICOLON OR AND NEQ EQ LESS GREATER LEQ GEQ NOT PLUS MINUS MULTIPLY DIVIDE MOD LPAR RPAR DOT LBRA RBRA TYPE OF END INTERVAL COMMA COLON PROCEDURE FUNCTION VAR BEGIN_ FOR TO STEP LOOP EXIT WHEN CONTINUE BREAK IF THEN ELSE RETURN REF PRINT READ

%token <info> ID V_INT V_REAL V_BOOL V_CHAR V_STRING 
%token <type_info> T_BOOL T_INT T_REAL T_CHAR T_STRING ARRAY RECORD

%type <info> NumExp SimpleExp CastExp UnaryExp Parenthesis AriOp2 AriOp Factor Comps Terms Exp CmdReturnExp AcessMemAddr Args CmdPrint
%type <type_info> TypeDec 
%type <interval> Interval


%start Prog 

%%

Prog : 
    {
        pushScope();
    } 
    Decl CmdBlock {
        // TODO free das tabelas
        #ifdef DEBUG
        printf(
            "\n\nFreeing stack and symbol tables.\n"
        );
        #endif
        freeScopes();
    }
;
Decl : 
    Consts Types Vars SubProg {}
;
Consts :
    CONST ID ATTRIB Exp SEMICOLON {
        if (!$4.is_constant) {
            yyerror("Expression %s must be constant", $4.name);
        }
        Symbol_Entry * newSymbol = malloc(sizeof(Symbol_Entry));
        newSymbol->name = $2.name;
        newSymbol->symbol_type = K_VARIABLE;

        Variable var_data;
        var_data.is_constant = 1;
        var_data.type = $4.type;
        switch ($4.type) {
            case E_INT:
                var_data.value.v_int = $4.value.v_int;
                break;
            case E_REAL:
                var_data.value.v_real = $4.value.v_real;
                break;
            case E_BOOL:
                var_data.value.v_bool = $4.value.v_bool;
                break;
            case E_CHAR:
                var_data.value.v_char = $4.value.v_char;
                break;
            case E_STRING:
                var_data.value.v_string = $4.value.v_string;
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
    } Vars
|   {/*printf("end of vars\n");*/}/* NOTHING */
;
Types :
    TYPE ID ATTRIB TypeDec SEMICOLON {

        if ($4.to_rename == 0){ 
            Symbol_Entry * newSymbol = malloc(sizeof(Symbol_Entry));
            newSymbol->symbol_type = K_SIMPLETYPE;
            SimpleType data;
            data.inner_type = $4.type;
            newSymbol->name = strdup($2.name);
            newSymbol->data.s_data = data;
            data.type_id 	= 	type_counter++;
        	insertSymbol(getCurrentScope(), newSymbol);
        } else {
            Symbol_Entry* entry = searchSymbol(getCurrentScope(), $4.name, 1);
            free(entry->name);
            entry->name = $2.name;
        }

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
        data.dimensions = 	$3.dimensions;
        data.type_id 	= 	type_counter++;
        $$.type = data.type_id;
        newSymbol->name = (char*) malloc(sizeof(char) * 32);
        sprintf(newSymbol->name, "ARRAY %d", data.type_id);
        $$.name = strdup(newSymbol->name);
        $$.to_rename = 1;
        data.size = 1;
        for (int i = 0; i < $3.dimensions; i++) {
            data.capacity[i] = $3.capacity[i];
            data.starts[i] = $3.starts[i];
            data.ends[i] = $3.ends[i];
            data.size *= data.capacity[i];
        }
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
            $$.dimensions = 1;
            if($3.value.v_int - $1.value.v_int <= 0){
            	yyerror("intervals cannot be negative.");
            }
            $$.capacity[0] = $3.value.v_int - $1.value.v_int;
            $$.starts[0] = $1.value.v_int;
            $$.ends[0] = $3.value.v_int;
        } else {
            yyerror("intervals can only be defined with integer values.");
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
        free($1.name);
        free($3.name);
    } ParametersAux
|   REF ID COLON TypeDec {
        strcpy(args_names[args_size], $2.name);
        ref_flags[args_size] = 1; 
        args_types[args_size++] = $4.type; 
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
        if ($1.type > 9) {
            yyerror("Type of '%s' ('%s') cannot be assigned directly.", $1.name, type_name($1.type));
        }
        if ($3.type > 9) {
            yyerror("Type of '%s' ('%s') cannot be assigned to a variable.", $3.name, type_name($3.type));
        }
        if($1.type != $3.type){
            yyerror(
                "Type of '%s' ('%s') is different from the type of the value assigned ('%s').",
                $1.name, type_name($1.type), type_name($3.type)
            );
        }
        free($1.name);
        free($3.name);
    }
|   CmdBlock {}
|   CmdConditional {}
|   CONTINUE {}
|   BREAK {}
|   FOR AcessMemAddr ATTRIB Exp TO Exp STEP Exp CmdBlock {
        if ($2.type != E_INT) {
            yyerror("Type of '%s' must be int.", $2.name);
        }
        if ($4.type != E_INT) {
            yyerror("Type of '%s' must be int.", $4.name);
        }
        if ($6.type != E_INT) {
            yyerror("Type of '%s' must be int.", $6.name);
        }
        if ($8.type != E_INT) {
            yyerror("Type of '%s' must be int.", $8.name);
        }
    }
|   LOOP {pushScope();} Vars Cmds END {popScope();}
|   EXIT WHEN Exp { 
        if ($3.type != E_BOOL) {
            yyerror("Type of '%s' must be boolean.", $3.name);
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
            yyerror("Symbol '%s' not found.", $1.name);
        } else {
            switch(entry->symbol_type) {
                case 0:
                    $$.type = entry->data.v_data.type;
                    $$.is_constant = entry->data.v_data.is_constant;
                    if ($$.is_constant) {
                        switch ($$.type) {
                            case E_INT:
                                $$.value.v_int = entry->data.v_data.value.v_int;
                                break;
                            case E_REAL:
                                $$.value.v_real = entry->data.v_data.value.v_real;
                                break;
                            case E_BOOL:
                                $$.value.v_bool = entry->data.v_data.value.v_bool;
                                break;
                            case E_CHAR:
                                $$.value.v_char = entry->data.v_data.value.v_char;
                                break;
                            case E_STRING:
                                $$.value.v_string = entry->data.v_data.value.v_string;
                                break;
                        }
                    }
                    break;
                default:
                    yyerror("Identifier %s is not a variable or constant!", $1.name);
            }
        }
        $$.name = $1.name;
    }
|   AcessMemAddr DOT ID {
        Symbol_Entry* entry = searchRecordType($1.type);
        if(entry == NULL){
            yyerror("Symbol '%s' not a record, its type is %d.", $1.name, $1.type);
        } else {
            for(int i = 0; i < entry->data.r_data.n_fields; i++){
                if(strcmp(entry->data.r_data.field_names[i], $3.name) == 0){
                    $$.type = entry->data.r_data.field_types[i];
                    $$.is_constant = $1.is_constant;
                }
            }
        }
        $$.name = $1.name; // todo: concatenar $1.name e $3.name
        free($3.name); // todo remover esse free?
    }

|   AcessMemAddr LBRA Exp RBRA {
        Symbol_Entry* entry = searchArrayType($1.type);
        if(entry == NULL){
            yyerror("Symbol '%s' not an array, its type is %s.", $1.name, type_name($1.type));
        } else {
            $$.type = entry->data.a_data.inner_type;
            if ($3.type != E_INT) {
                yyerror("Expression used to access position of array is not an integer, is of type %s", type_name($3.type));
            }
        }
        $$.name = $1.name; // TODO: concatenar $1.name e $3.name
        free($3.name); // TODO remover esse free?
    }
|   ID LPAR {args_size=0;} Args RPAR {
    Symbol_Entry* entry = getSubProgram($1.name);
    if (entry == NULL) {
        yyerror("Symbol '%s' not found.", $1.name);
    } else {
        if (entry->data.sp_data.return_type != -1) {
            $$.type = entry->data.sp_data.return_type;
        }
        if (entry->data.sp_data.params_size == args_size) {
            for (size_t i = 0; i < entry->data.sp_data.params_size; i++) {
                if (args_types[i] != entry->data.sp_data.params_types[i]) {
                    yyerror("Type of parameter %s is %s but was expected to be %s.", args_names[i], type_name(args_types[i]), type_name(entry->data.sp_data.params_types[i]));
                }
            }
        } else {
            yyerror("Wrong number of parameters. %ld parameters expected, %ld given", entry->data.sp_data.params_size, args_size);
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
        if ($2.type != E_BOOL) {
            yyerror("Result type of expression in IF statement should be boolean, but was os type %s", type_name($2.type));
        }
    } THEN CmdBlock CmdConditionalEnd
;

CmdConditionalEnd:
    ELSE CmdBlock {}
|   /* NOTHING */ {}
;

CmdReturn:
    RETURN CmdReturnExp {
        if (current_return_type != 0 && current_return_type != $2.type) {
            yyerror("Error: Return type is %s but was expected to be %s.", type_name($2.type), type_name(current_return_type));
        }

        if(strcmp(functionName, "") != 0){
            
            Symbol_Entry * functionSymbol = searchSymbol(getCurrentScope(), functionName, 1);
            if(functionSymbol != NULL){
                if(functionSymbol->data.sp_data.return_type != $2.type){
                    yyerror(
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
        if ($3.type != E_STRING) {
            yyerror("First argument of print must be of type string");
        } else {
            // printf("%s\n", $3.value.v_string);
        }
        args_types[args_size] = $3.type;
        strcpy(args_names[args_size], $3.name);
        args_size++;
    } PrintArgs RPAR {
        args_size = 0;
    }
;

PrintArgs:
    COMMA Exp {
        args_types[args_size] = $2.type;
        strcpy(args_names[args_size], $2.name);
        args_size++;
}   PrintArgs
|   /* NOTHING */ {}
;

CmdRead:
    READ LPAR AcessMemAddr RPAR {
        if ($3.type != E_STRING) {
            yyerror("%s must be of type String, but is of type %s", $3.name, type_name($3.type));
        }
        if ($3.is_constant) {
            yyerror("\"%s\" cannot be a constant", $3.name);
        }
    }
;

Exp:
    Exp OR Terms {
        if ($1.type == E_BOOL && $3.type == E_BOOL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_bool || $3.value.v_bool;
        } else {
            yyerror("OR operation must be between bool values, but was between %s and %s", type_name($1.type), type_name($3.type));
        }
        $$.is_constant = $1.is_constant && $3.is_constant;
    }
|   Terms {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
}
;

Terms:
    Terms AND Comps {
        if ($1.type == E_BOOL && $3.type == E_BOOL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_bool && $3.value.v_bool;
        } else {
            yyerror("AND operation must be between bool values, but was between %s and %s", type_name($1.type), type_name($3.type));
        }
        $$.is_constant = $1.is_constant && $3.is_constant;
    }
|   Comps {
        $$.type = $1.type;
        $$.name = $1.name;
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
            yyerror("Incompatible type for '!=' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        $$.is_constant = $1.is_constant && $3.is_constant;
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
            yyerror("Incompatible type for '==' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        $$.is_constant = $1.is_constant && $3.is_constant;
    }
|   Factor LESS Factor {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_int < $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_real < $3.value.v_real;
        } else {
            yyerror("Incompatible type for '<' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        $$.is_constant = $1.is_constant && $3.is_constant;
    }
|   Factor GREATER Factor  {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_int > $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_real > $3.value.v_real;
        } else {
            yyerror("Incompatible type for '>' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        $$.is_constant = $1.is_constant && $3.is_constant;
    }
|   Factor LEQ Factor {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_int <= $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_real <= $3.value.v_real;
        } else {
            yyerror("Incompatible type for '<=' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        $$.is_constant = $1.is_constant && $3.is_constant;
    }
|   Factor GEQ Factor  {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_int >= $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
            $$.value.v_bool = $1.value.v_real >= $3.value.v_real;
        } else {
            yyerror("Incompatible type for '>=' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        $$.is_constant = $1.is_constant && $3.is_constant;
    }
|   Factor  {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
        
}
;

Factor:
    NOT AriOp {
        if ($2.type == E_BOOL ) {
            $$.type = E_BOOL;
            $$.value.v_bool = !$2.value.v_bool;
        } else {
            yyerror("Incompatible type for '!' operation between %s (%s)", $2.name, type_name($2.type));
        }
        $$.is_constant = $2.is_constant;
    }
|   AriOp {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
        
}
;

AriOp:
    AriOp PLUS AriOp2 {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = $1.value.v_int + $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = $1.value.v_real + $3.value.v_real;
        } else {
            yyerror("Incompatible type for '+' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        $$.is_constant = $1.is_constant && $3.is_constant;
    }
|   AriOp MINUS AriOp2 {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = $1.value.v_int - $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = $1.value.v_real - $3.value.v_real;
        } else {
            yyerror("Incompatible type for '-' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        $$.is_constant = $1.is_constant && $3.is_constant;
    }
|   AriOp2 {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
}
;

AriOp2:
    AriOp2 MULTIPLY Parenthesis {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = $1.value.v_int * $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = $1.value.v_real * $3.value.v_real;
        } else {
            yyerror("Incompatible type for '*' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        // $$.name = strcat() // TODO
        $$.is_constant = $1.is_constant && $3.is_constant;
    }
|   AriOp2 DIVIDE Parenthesis {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = $1.value.v_int / $3.value.v_int;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = $1.value.v_real / $3.value.v_real;
        } else {
            yyerror("Incompatible type for '/' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
        }
        $$.is_constant = $1.is_constant && $3.is_constant;
    }
|   AriOp2 MOD Parenthesis {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = $1.value.v_int % $3.value.v_int;
        } else {
            yyerror("Incompatible type. - AriOp2 \n");
        }
        $$.is_constant = $1.is_constant && $3.is_constant;
    }
|   Parenthesis {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
        
}
;

Parenthesis:
    UnaryExp {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
        
}
|   LPAR Exp RPAR {
        $$.type = $2.type;
        $$.name = $2.name;
        $$.is_constant = $2.is_constant;
        $$.value = $2.value;
}
;

UnaryExp:
    PLUS CastExp { 
        if ($2.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = + $2.value.v_int;
        } else if ($2.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = + $2.value.v_real;
        } else { 
            yyerror("Incompatible type. - UnaryExp \n");
        }
        $$.is_constant = $2.is_constant;
    }
|   MINUS CastExp { 
        if ($2.type == E_INT) {
            $$.type = E_INT;
            $$.value.v_int = - $2.value.v_int;
        } else if ($2.type == E_REAL) {
            $$.type = E_REAL;
            $$.value.v_real = - $2.value.v_real;
        } else { 
            yyerror("Incompatible type. - UnaryExp \n");
        }
        $$.is_constant = $2.is_constant;
        
    }
|   CastExp {
        $$.type = $1.type;
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
            yyerror("string cannot be converted to int!\n");
        }
        $$.is_constant = $4.is_constant;
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
            yyerror("string cannot be converted to real!\n");
        }
        $$.is_constant = $4.is_constant;
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
            yyerror("char cannot be converted to bool!");
        }
        if ($4.type == E_STRING) {
            yyerror("string cannot be converted to bool!");
        }
        $$.is_constant = $4.is_constant;
}
|   LPAR T_CHAR RPAR Parenthesis      {
    if ($4.type == E_INT) {
        yyerror("int cannot be converted to char!");
    }
    if ($4.type == E_REAL) {
        yyerror("real cannot be converted to char!");
    }
    if ($4.type == E_BOOL) {
        yyerror("bool cannot be converted to char!");
    }
    if ($4.type == E_CHAR) {
        $$.type = E_CHAR;
        $$.value.v_char = $4.value.v_char;
    }
    if ($4.type == E_STRING) {
        yyerror("string cannot be converted to char!");
    }
    $$.is_constant = $4.is_constant;
}
|   LPAR T_STRING RPAR Parenthesis      {
    if ($4.type == E_INT) {
        $$.type = E_STRING;
    }
    if ($4.type == E_REAL) {
        $$.type = E_STRING;
    }
    if ($4.type == E_BOOL) {
        $$.type = E_STRING;
    }
    if ($4.type == E_CHAR) {
        $$.type = E_STRING;
    }
    if ($4.type == E_STRING) {
        $$.type = E_STRING;
    }
    $$.is_constant = $4.is_constant;
}
|   SimpleExp                       {
    $$.type = $1.type;
    $$.name = $1.name;
    $$.is_constant = $1.is_constant;
    $$.value = $1.value;
    
}

SimpleExp:
    NumExp {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
        
}
|   AcessMemAddr {
        $$.type = $1.type;
        $$.name = $1.name;
        $$.is_constant = $1.is_constant;
        $$.value = $1.value;
}
;

NumExp:
    V_INT    {
        $$.type = E_INT;
        $$.value.v_int = $1.value.v_int;
        $$.name = $1.name;
        $$.is_constant = 1;
        
}
|   V_REAL   {
        $$.type = E_REAL;
        $$.value.v_real = $1.value.v_real;
        $$.name = $1.name;
        $$.is_constant = 1;
}
|   V_BOOL   {
        $$.type = E_BOOL;
        $$.value.v_bool = $1.value.v_bool;
        $$.name = $1.name;
        $$.is_constant = 1;
}
|   V_CHAR   {
        $$.type = E_CHAR;
        $$.value.v_char = $1.value.v_char;
        $$.name = $1.name;
        $$.is_constant = 1;
}
|   V_STRING {
        $$.type = E_STRING;
        $$.value.v_string = $1.value.v_string;
        $$.name = $1.name;
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
    if (result == 0) {
        printf("parsing was successful\n");
    } else if (result == 1) {
        printf("parsing failed because of invalid input\n");
    } else if (result == 2) {
        printf("parsing failed due to memory exhaustion\n");
    } else {
        printf("other parsing error: %d\n", result);
    }
    if (argc == 2) {
        fclose(yyin);
    }
    yylex_destroy();
    return 0;
}
