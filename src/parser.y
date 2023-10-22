%{
#include <stdio.h>
#include <lexer.l.h>
#include <typedefs.h>
#include <symtab.h>
#include "exception.h"

int args_types[16];
char args_names[16][32];
size_t args_size;
int type_counter = 10;

//	gambi para guardar o nome de um tipo
char * temp;
int flag = 0;

extern int column_counter;
char* message;

void yyerror(char* s, ...) {
    va_list vars;
    va_start(vars, s);
    printMessage(ERROR, "%s at line %d - column %d\n", s , yylineno, column_counter, vars);
    va_end(vars);
    // fprintf(stderr, "%s at line %d - column %d\n", s , yylineno, column_counter);
    // fprintf(stderr, "current token is: \"%s\"\n", yytext);
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

%token CONST ATTRIB SEMICOLON OR AND NEQ EQ LESS GREATER LEQ GEQ NOT PLUS MINUS MULTIPLY DIVIDE MOD LPAR RPAR DOT LBRA RBRA TYPE OF END INTERVAL COMMA COLON PROCEDURE FUNCTION VAR BEGIN_ FOR TO STEP LOOP EXIT WHEN CONTINUE BREAK IF THEN ELSE RETURN REF PRINT QUOTE

%token <info> ID V_INT V_REAL V_BOOL V_CHAR V_STRING 
%token <type_info> T_BOOL T_INT T_REAL T_CHAR ARRAY RECORD

%type <info> NumExp SimpleExp UnaryExp Parenthesis AriOp2 AriOp Factor Comps Terms Exp CastExp CmdReturnExp AcessMemAddr Args CmdPrint
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
            case E_ARRAY:
                // TODO
                var_data.value.v_string = $4.value.v_string;
                break;
        }
        newSymbol->data.v_data = var_data;
        insertSymbol(getCurrentScope(), newSymbol);
        #ifdef DEBUG
        printCurrentScope(getCurrentScope());
        #endif
        free($4.name);
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
    TYPE ID {temp = $2.name; flag = 1;} ATTRIB TypeDec SEMICOLON {
        //Symbol_Entry * newSymbol = malloc(sizeof(Symbol_Entry));
        //newSymbol->name = $2.name;
        //newSymbol->symbol_type = K_TYPE;
        //Type t_data;
        //t_data.type_kind = $4.type;

        // // switch (type_kind)

        //insertSymbol(getCurrentScope(), newSymbol);

        #ifdef DEBUG
        printCurrentScope(getCurrentScope());
        #endif

        // free($2.name);
        flag = 0;
        
    } Types
|   /* NOTHING */
;



TypeDec :
    T_BOOL {$$.type = E_BOOL; $$.name = $1.name;}
|   T_INT  {$$.type = E_INT; $$.name = $1.name;}
|   T_REAL {$$.type = E_REAL; $$.name = $1.name;}
|   T_CHAR {$$.type = E_CHAR; $$.name = $1.name;}
|   ID     {
        $$.name = $1.name;
        $$.type = searchType($$.name);
    }
|   ARRAY LBRA Interval RBRA OF TypeDec  {
		
		Symbol_Entry * newSymbol = malloc(sizeof(Symbol_Entry));
        newSymbol->symbol_type = K_ARRAY;
        Array data;
        data.inner_type =	$6.type;
        data.dimensions = 	$3.dimensions;
        data.type_id 	= 	type_counter++;
        $$.type = data.type_id;
        if(flag == 1){
        	newSymbol->name = temp;	
        } else {
            newSymbol->name = (char*) malloc(sizeof(char) * 32);
            sprintf(newSymbol->name, "ARRAY %d", data.type_id);
        }
        data.size = 1;
        for (int i = 0; i < $3.dimensions; i++) {
            data.capacity[i] = $3.capacity[i];
            data.starts[i] = $3.starts[i];
            data.ends[i] = $3.ends[i];
            data.size *= data.capacity[i];
        }
        newSymbol->data.a_data = data;
        insertSymbol(getCurrentScope(), newSymbol);
        
        // printf("dimensions: %d\n", $$.array_data.dimensions);
        // printf("size: %d\n", $$.array_data.size);
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
        if(flag == 1){
        	newSymbol->name = temp;	
        } else {
            newSymbol->name = (char*) malloc(sizeof(char) * 32);
            sprintf(newSymbol->name, "RECORD %d", data.type_id);
        }
        newSymbol->data.r_data = data;
        insertSymbol(getCurrentScope(), newSymbol);
        args_size=0;
    }
;
Interval :
    Exp INTERVAL Exp {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.dimensions = 1;
            if($3.value.v_int - $1.value.v_int <= 0){
            	yyerror("erro: valor do intervalo eh negativo.\n");
            }
            $$.capacity[0] = $3.value.v_int - $1.value.v_int;
            $$.starts[0] = $1.value.v_int;
            $$.ends[0] = $3.value.v_int;
        } else {
            yyerror("deu ruim");
        }
        free($1.name);
        free($3.name);
    }
|   Exp INTERVAL Exp COMMA Interval {
        if ($1.type == E_INT && $3.type == E_INT) {
            if($3.value.v_int - $1.value.v_int <= 0){
            	yyerror("erro: valor do intervalo eh negativo.\n");
            }
            $$.dimensions = $5.dimensions+1;
            for (int i = 0; i < $5.dimensions; i++) {
                $$.capacity[i] = $5.capacity[i];
            	$$.starts[i] = $5.starts[i];
            	$$.ends[i] = $5.ends[i];
            }
            $$.capacity[$$.dimensions-1] = $3.value.v_int - $1.value.v_int;
            $$.starts[$$.dimensions-1] = $1.value.v_int;
            $$.ends[$$.dimensions-1] = $3.value.v_int;
        } else {
            yyerror("deu ruim");
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
        printf("\nPARAMETROS IDENTIFICADOS - PROCEDURE: %s\n", $2.name);
        #endif
        for(size_t i = 0; i < args_size; i++){
            procedure.params[i] = args_types[i];
            #ifdef DEBUG
            printf(
                "\tParam %ld Type: %d\n", 
                i+1, args_types[i]
            );
            #endif
        }
        procedure.params_size = args_size;
        procedure.return_type = -1;
        printf("params_size: %ld\n", procedure.params_size);
        printf("params_size: %ld\n", args_size);
        //args_size=0;// Comentado para nao ser zerado 
                        //- inserir os parametros na tabela de simbolos do procedimento

        newSymbol->data.sp_data = procedure;

        // criar registro na tabela
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
        args_types[args_size++] = $3.type; 
        free($1.name);
        free($3.name);
    } ParametersAux
|   REF ID COLON TypeDec { args_types[args_size++] = $4.type; } 
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
        printf("\nPARAMETROS IDENTIFICADOS - FUNCTION: %s\n", $2.name);
        #endif
        for(size_t i = 0; i < args_size; i++){
            function.params[i] = args_types[i];
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

        // apagar os dados de parametros após salvar a função na tabela de simbolos
        //args_size=0; // Comentado para nao ser zerado 
                        //- ainda falta inserir os parametros na tabela de simbolos da funcao
    } CmdBlock SEMICOLON
    {
        #ifdef DEBUG
        printf("\n\t End of Function...\n");
        #endif
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
        if($1.type != $3.type){
            printf(
                "Error: Type of '%s' is different from the type of the value assigned.\n",
                $1.name
            );
        } else {
            // TODO
        }
        free($1.name);
        free($3.name);
    }
|   CmdBlock {}
|   CmdConditional {}
|   CONTINUE {}
|   BREAK {}
|   FOR AcessMemAddr ATTRIB Exp TO Exp STEP Exp CmdBlock {
        if ($2.type == $4.type && $6.type == $8.type && $2.type == $6.type) {
            // TODO
        } else {
            printf("ERROR");
        }
    }
|   LOOP Vars Cmds END {}
|   EXIT WHEN Exp { 
        if ($3.type != E_BOOL) {
            // TODO: error
        }
    }
|   CmdReturn {}
|   CmdPrint {}
;

AcessMemAddr: 
    ID {
        Symbol_Table* tabela = getCurrentScope();
        Symbol_Entry* entry = searchSymbol(tabela, $1.name, true);
        if(entry == NULL){
            printf("Error: symbol '%s' not found.\n", $1.name);
        } else {
            switch(entry->symbol_type) {
                case 0:
                    $$.type = entry->data.v_data.type;
                    $$.is_constant = entry->data.v_data.is_constant;
                    break;
                default:
                    printf("Not a variable or constant!");
            }
        }
        $$.name = $1.name;
    }
|   AcessMemAddr DOT ID {
        Symbol_Entry* entry = searchRecordType($1.type);
        if(entry == NULL){
            printf("Error: symbol '%s' not a record, type is %d.\n", $1.name, $1.type);
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
        $$.type = entry->data.a_data.inner_type;
        if(entry == NULL){
            printf("Error: symbol '%s' not an array, type is %d.\n", $1.name, $1.type);
        } else {
            if ($3.type != E_INT) {
                printf("ERROR - Expression not result in integer value\n");
            }
        }
        $$.name = $1.name; // todo: concatenar $1.name e $3.name
        free($3.name); // todo remover esse free?
    }
|   ID LPAR {args_size=0;} Args RPAR {
    Symbol_Entry* entry = getSubProgram($1.name);
    if (entry->data.sp_data.return_type != -1) {
        $$.type = entry->data.sp_data.return_type;
    }
    printf("encontrei essa função %s\n", entry->name);
    printf("parameters %ld %ld\n", entry->data.sp_data.params_size, args_size);
    if (entry->data.sp_data.params_size == args_size) {
        for (size_t i = 0; i < entry->data.sp_data.params_size; i++) {
            if (args_types[i] != entry->data.sp_data.params[i]) {
                printf("ERROR - Type of parameter %s is %s but was expected to be %s.\n", args_names[i], type_name(args_types[i]), type_name(entry->data.sp_data.params[i]));
            }
        }
    } else {
        printf("ERROR - Wrong number of parameters. %ld parameters expected, %ld given\n", entry->data.sp_data.params_size, args_size);
    }
    // TODO: comparar args com os parametros da tabela de simbolo do função AcessMemAddr 
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
    IF Exp THEN CmdBlock CmdConditionalEnd {
        if ($2.type != E_BOOL) {
            printf("CmdConditional - exp: %s\n", $2.name);
            printf("ERROR");
            // TODO
        }
    }
;

CmdConditionalEnd:
    ELSE CmdBlock {}
|   /* NOTHING */ {}
;

CmdReturn:
    RETURN CmdReturnExp {
        // TODO busca na tabela para tipo compativel 
    }
;

CmdReturnExp:
    Exp { $$.type = $1.type; $$.name = $1.name;}
|   /* NOTHING */ { $$.type = -1;}
;

CmdPrint:
    PRINT LPAR Exp RPAR {
        if ($3.type != E_STRING) {
            printf("ERROR - Expression not result in string value\n");
        } else {
            printf("%s\n", $3.value.v_string);
        }
    }
| {}
;



/* 

PrintArgs:
    PrintArgs COMMA PrintArg
;

PrintArg:
    V_STRING {
        $$ = create_print_arg(STRING, $1.value.v_string);
    }
    | 
    ;
*/

Exp:
    Exp OR Terms {
        if ($1.type == E_BOOL && $3.type == E_BOOL) {
            $$.type = E_BOOL;
        } else {
            yyerror("ERROR! Incompatible type. - Exp \n");
        }
    }
|   Terms { $$.type = $1.type; $$.name = $1.name; }
;

Terms:
    Terms AND Comps {
        if ($1.type == E_BOOL && $3.type == E_BOOL) {
            $$.type = E_BOOL;
        } else {
            yyerror("ERROR! Incompatible type. - Terms\n");
        }
    }
|   Comps { $$.type = $1.type; $$.name = $1.name;}
;

Comps: 
    Factor NEQ Factor {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
        } else if ($1.type == E_BOOL && $3.type == E_BOOL) {
            $$.type = E_BOOL;
        } else if ($1.type == E_CHAR && $3.type == E_CHAR) {
            $$.type = E_BOOL;
        } else {
            yyerror("ERROR! Incompatible type for '!=' operation");
        }
    }
|   Factor EQ Factor  {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
        } else if ($1.type == E_BOOL && $3.type == E_BOOL) {
            $$.type = E_BOOL;
        } else if ($1.type == E_CHAR && $3.type == E_CHAR) {
            $$.type = E_BOOL;
        } else {
            sprintf(message, "ERROR! Incompatible type for '==' operation between %s (%s) and %s (%s)", $1.name, type_name($1.type), $3.name, type_name($3.type));
            yyerror(message);
        }
    }
|   Factor LESS Factor {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
        } else {
            yyerror("ERROR! Incompatible type for '<' operation");
        }
    }
|   Factor GREATER Factor  {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
        } else {
            yyerror("ERROR! Incompatible type for '>' operation");
        }
    }
|   Factor LEQ Factor {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
        } else {
            yyerror("ERROR! Incompatible type for '<=' operation");
        }
    }
|   Factor GEQ Factor  {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_BOOL;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_BOOL;
        } else {
            yyerror("ERROR! Incompatible type for '>=' operation");
        }
    }
|   Factor  { $$.type = $1.type; $$.name = $1.name;}
;

Factor:
    NOT AriOp {
        if ($2.type == E_BOOL ) {
            $$.type = E_BOOL;
            $$.value.v_bool = !$2.value.v_bool;
        } else {
            yyerror("ERROR! Incompatible type for '!' operation");
        }
    }
|   AriOp { $$.type = $1.type; $$.name = $1.name; }
;

AriOp:
    AriOp PLUS AriOp2 {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_REAL;
        } else {
            yyerror("ERROR! Incompatible type for '+' operation");
        }
    }
|   AriOp MINUS AriOp2 {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_REAL;
        } else {
            yyerror("ERROR! Incompatible type for '-' operation");
        }
    }
|   AriOp2 { $$.type = $1.type; $$.name = $1.name;}
;

AriOp2:
    AriOp2 MULTIPLY Parenthesis {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_REAL;
        } else {
            yyerror("ERROR! Incompatible type for '*' operation");
        }
        // $$.name = strcat() // TODO

    }
|   AriOp2 DIVIDE Parenthesis {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            $$.type = E_REAL;
        } else {
            yyerror("ERROR! Incompatible type for '/' operation");
        }
    }
|   AriOp2 MOD Parenthesis {
        if ($1.type == E_INT && $3.type == E_INT) {
            $$.type = E_INT;
        } else if ($1.type == E_REAL && $3.type == E_REAL) {
            // TODO
            yyerror("ERROR! Incompatible type. - AriOp2 \n");
        } else {
            yyerror("ERROR! Incompatible type. - AriOp2 \n");
        }
    }
|   Parenthesis { $$.type = $1.type; $$.name = $1.name;}
;

Parenthesis:
    UnaryExp { $$.type = $1.type; $$.name = $1.name;}
|   LPAR Exp RPAR { $$.type = $2.type; }
;

UnaryExp:
    PLUS CastExp { 
        if ($2.type == E_INT || $2.type == E_REAL) {
            $$.type = $2.type;
        } else { 
            yyerror("ERROR! Incompatible type. - UnaryExp \n");
        }
    }
|   MINUS CastExp { 
        if ($2.type == E_INT || $2.type == E_REAL) {
            $$.type = $2.type;
        } else { 
            yyerror("ERROR! Incompatible type. - UnaryExp \n");
        }
    }
|   CastExp { $$.type = $1.type; $$.name = $1.name;}
;

CastExp:
    LPAR T_INT RPAR SimpleExp       {
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
    }
|   LPAR T_REAL RPAR SimpleExp      {
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
}
|   LPAR T_BOOL RPAR SimpleExp      {
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
            yyerror("char para bool pode não!\n");
        }
}
|   LPAR T_CHAR RPAR SimpleExp      {
    if ($4.type == E_INT) {
        $$.type = E_CHAR;
        // TODO If
        $$.value.v_char = $4.value.v_int;
    }
    if ($4.type == E_REAL) {
        yyerror("real para char pode não!\n");
    }
    if ($4.type == E_BOOL) {
        yyerror("bool para char pode não!\n");
    }
    if ($4.type == E_CHAR) {
        $$.type = E_CHAR;
        $$.value.v_char = $4.value.v_char;
    }
}
|   SimpleExp                       {
    $$.type = $1.type;
    $$.name = $1.name;
}

SimpleExp:
    NumExp { $$.type = $1.type; $$.name = $1.name;}
|   AcessMemAddr { $$.type = $1.type; $$.name = $1.name;}
;

NumExp:
    V_INT    { $$.type = E_INT; $$.value.v_int = $1.value.v_int; $$.name = $1.name;}
|   V_REAL   { $$.type = E_REAL; $$.value.v_real = $1.value.v_real; $$.name = $1.name;}
|   V_BOOL   { $$.type = E_BOOL; $$.value.v_bool = $1.value.v_bool; $$.name = $1.name;}
|   V_CHAR   { $$.type = E_CHAR; $$.value.v_char = $1.value.v_char; $$.name = $1.name;}
|   V_STRING { $$.type = ARRAY; /*TODO*/}
;

%%
  
int main(int argc, char const *argv[])
{
    if (argc == 2) {
        yyin=fopen(argv[1],"r");
    }
    message = malloc(sizeof(char) * 256);
    int result = yyparse();
    free(message);
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
