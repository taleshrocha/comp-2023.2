%{
#include <stdio.h>
#include <lexer.l.h>
#include <typedefs.h>
#include <symbolTable.h>
#include <symtab.h>

#define INT_TYPE 1
#define REAL_TYPE 2
#define BOOL_TYPE 3
#define CHAR_TYPE 4
#define STRING_TYPE 5
#define FUNCTION_TYPE 6
#define PROCEDURE_TYPE 7

int args_types[100];
char args_names[100][100];
int args_size;
int type_counter = 5;

extern int column_counter;

void yyerror(char* s) {
    fprintf(stderr, "%s at line-column: %d-%d\n", s , yylineno, column_counter);
    fprintf(stderr, "current token is: \"%s\"\n", yytext);
}

%}

%union {
    struct {
        int type;
        char* name;
        union {
            int v_int;
            int v_bool;
            double v_real;
            char v_char;
            char* v_string;
        } value;
        char* lexemes;
    } info;
}

%token CONST ATTRIB SEMICOLON OR AND NEQ EQ LESS GREATER LEQ GEQ NOT PLUS MINUS MULTIPLY DIVIDE MOD LPAR RPAR DOT LBRA RBRA TYPE T_BOOL T_INT T_REAL T_CHAR ARRAY OF RECORD END INTERVAL COMMA COLON PROCEDURE FUNCTION VAR BEGIN_ FOR TO STEP LOOP EXIT WHEN CONTINUE BREAK IF THEN ELSE RETURN REF

%token <info> ID V_INT V_REAL V_BOOL V_CHAR V_STRING

%type <info> NumExp SimpleExp UnaryExp Parenthesis AriOp2 AriOp Factor Comps Terms Exp CastExp CmdReturnExp AcessMemAddr Args TypeDec

%start Prog 

%%

Prog : 
    {
        initializeStackOfScopes();
        createSymbolTable(NULL);
    } 
    Decl CmdBlock {
        // TODO free das tabelas
        #ifdef DEBUG
        printf(
            "\n\nFreeing stack and symbol tables.\n"
        );
        #endif
        freeStackOfScopes();
    }
;
Decl : 
    Consts Types SubProg Vars {}
;
Consts :
    CONST ID ATTRIB Exp SEMICOLON {
        Symbol_Entry * newSymbol = malloc (sizeof(Symbol_Entry));
        newSymbol->name = $2.name;
        newSymbol->symbol_type = 0;

        Variable var_data;
        var_data.is_constant = 1;
        var_data.type = $4.type;
        switch ($4.type) {
            case INT_TYPE:
                var_data.value.v_int = $4.value.v_int;
                break;
            case REAL_TYPE:
                var_data.value.v_real = $4.value.v_real;
                break;
            case BOOL_TYPE:
                var_data.value.v_bool = $4.value.v_bool;
                break;
            case CHAR_TYPE:
                var_data.value.v_char = $4.value.v_char;
                break;
            case STRING_TYPE:
                var_data.value.v_string = $4.value.v_string;
                break;
            default:
                printf("Constant value type not known.");
                exit(1); //TODO: tratar melhor este caso.
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
        newSymbol->symbol_type = 0;

        Variable var_data;
        var_data.type = $4.type;
        var_data.is_constant = 0;
        switch ($4.type) {
            case INT_TYPE:
                var_data.value.v_int = $4.value.v_int;
                break;
            case REAL_TYPE:
                var_data.value.v_real = $4.value.v_real;
                break;
            case BOOL_TYPE:
                var_data.value.v_bool = $4.value.v_bool;
                break;
            case CHAR_TYPE:
                var_data.value.v_char = $4.value.v_char;
                break;
            case STRING_TYPE:
                var_data.value.v_string = $4.value.v_string;
                break;
            default:
                exit(1); //TODO: tratar melhor este caso.
        }
        newSymbol->data.v_data = var_data;

        insertSymbol(getCurrentScope(), newSymbol);
        #ifdef DEBUG
        printCurrentScope(getCurrentScope());
        #endif
    } Vars
|   {/*printf("end of vars\n");*/}/* NOTHING */
;
Types :
    TYPE ID ATTRIB TypeDec SEMICOLON Types {}
|   /* NOTHING */
;
TypeDec :
    T_BOOL {$$.type = BOOL_TYPE;}
|   T_INT  {$$.type = INT_TYPE;}
|   T_REAL {$$.type = REAL_TYPE;}
|   T_CHAR {$$.type = CHAR_TYPE;}
|   ID     {$$.type = 0 /*TODO*/;}
|   ARRAY LBRA Interval RBRA OF TypeDec  {}
|   RECORD Fields END {}
;
Interval :
    Exp INTERVAL Exp {}
|   Exp INTERVAL Exp COMMA Interval {}
;
Fields :
    ID COLON TypeDec SEMICOLON Fields {}
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
        newSymbol->symbol_type = 1;

        Procedure procedure;
        #ifdef DEBUG
        printf("\nPARAMETROS IDENTIFICADOS - PROCEDURE: %s\n", $2.name);
        #endif
        for(int i = 0; i < args_size; i++){
            procedure.params[i] = args_types[i];
            #ifdef DEBUG
            printf(
                "\tParam %d Type: %d\n", 
                i+1, args_types[i]
            );
            #endif
        }
        procedure.params_size = args_size;
        //args_size=0;// Comentado para nao ser zerado 
                        //- ainda falta inserir os parametros na tabela de simbolos do procedimento

        newSymbol->data.p_data = procedure;

        // criar registro na tabela
        insertSymbol(getCurrentScope(), newSymbol);
        
    } CmdBlock SEMICOLON
    {
        #ifdef DEBUG
        printf("\n\t End of Procedure...\n");
        #endif
    }
;

Parameters:
    ID COLON TypeDec ParametersAux { 
        strcpy(args_names[args_size], $1.name);
        args_types[args_size++] = $3.type; 
    }
|   REF ID COLON TypeDec ParametersAux { args_types[args_size++] = $4.type; }
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
        newSymbol->symbol_type = 2;

        Function function;
        #ifdef DEBUG
        printf("Return type: %d\n", $8.type);
        #endif
        function.return_type = $8.type;
        #ifdef DEBUG
        printf("\nPARAMETROS IDENTIFICADOS - FUNCTION: %s\n", $2.name);
        #endif
        for(int i = 0; i < args_size; i++){
            function.params[i] = args_types[i];
            #ifdef DEBUG
            printf(
                "\tParam %d Type: %d\n", 
                i+1, args_types[i]
            );
            #endif
        }

        function.params_size = args_size;
        newSymbol->data.f_data = function;

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
        createSymbolTable(getCurrentScope());
        if(args_size > 0 && args_size < 101){
            for(int i = 0; i < args_size; i++){
                Symbol_Entry * newSymbol = malloc (sizeof(Symbol_Entry));
                newSymbol->name = args_names[i];
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
    AcessMemAddr ATTRIB Exp {
        Symbol_Entry * symbol = searchSymbol(getCurrentScope(), $1.name);
        if(symbol == NULL){
            printf("Error: symbol '%s' not found.\n", $1.name);
        } else if (symbol->symbol_type != 0) {
            printf(
                "Error: value cannot be assigned to '%s'. Is not a variable",
                $1.name
            );
        } else {
            switch (symbol->data.v_data.type){
                case INT_TYPE:
                case REAL_TYPE:
                case CHAR_TYPE:
                case STRING_TYPE:
                case BOOL_TYPE:
                    if(symbol->data.v_data.is_constant == 1){
                        printf(
                            "Error: The value of '%s' cannot be changed. Reason: constant.\n",
                            symbol->name
                        );
                    }
                    break;
            }
        }
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
        if ($3.type != BOOL_TYPE) {
            // TODO: error
        }
    }
|   CmdReturn {}
;

AcessMemAddr: 
    ID {
        Symbol_Table* tabela = getCurrentScope();
        Symbol_Entry* entry = searchSymbol(tabela, $1.name);
        switch(entry->symbol_type) {
            case 0:
                $$.type = entry->data.v_data.type;
                break;
            default:
                printf("Not a variable or constant!");
        }
    }
|   AcessMemAddr DOT ID {
        //TODO  
    }

|   AcessMemAddr LBRA Exp RBRA {
        if ($3.type == INT_TYPE) {
            $$.type = $3.type;
        } else {
            printf("ERROR - AcessMemAddr\n");
        }
        // garantir q AcessMemAddr é um array
        // acessar o tipo do conteudo array e atribuir esse tipo para AcessMemAddr
    }
|   AcessMemAddr LPAR Args RPAR {
    // TODO: comparar args com os parametros da tabela de simbolo do função AcessMemAddr 
    // desalocar a memoria de args após o uso
    // atribuir o tipo retornado pela função ao AcessMemAddr
    // {args_size=0;}
    }
;

CmdConditional:
    IF Exp THEN CmdBlock CmdConditionalEnd {
        if ($2.type != BOOL_TYPE) {
            printf("CmdConditional - exp: %s\n", $2.lexemes);
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
    Exp { $$.type = $1.type; $$.lexemes = $1.lexemes;}
|   /* NOTHING */ { $$.type = -1;}
;

Exp:
    Exp OR Terms {
        if ($1.type == BOOL_TYPE && $3.type == BOOL_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. - Exp \n");
        }
    }
|   Terms { $$.type = $1.type; $$.lexemes = $1.lexemes; }
;

Terms:
    Terms AND Comps {
        if ($1.type == BOOL_TYPE && $3.type == BOOL_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. - Terms\n");
        }
    }
|   Comps { $$.type = $1.type; $$.lexemes = $1.lexemes;}
;

Comps: 
    Factor NEQ Factor {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == BOOL_TYPE && $3.type == BOOL_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == CHAR_TYPE && $3.type == CHAR_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. - Comps \n");
        }
    }
|   Factor EQ Factor  {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == BOOL_TYPE && $3.type == BOOL_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == CHAR_TYPE && $3.type == CHAR_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("lexemes: %s and %s\n", $1.lexemes, $3.lexemes);
            printf("types: %d and %d - %d\n", $1.type, $3.type, EQ);
            printf("ERROR! Incompatible type. - Comps \n");
        }
    }
|   Factor LESS Factor {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. - Comps \n");
        }
    }
|   Factor GREATER Factor  {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. - Comps \n");
        }
    }
|   Factor LEQ Factor {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. - Comps \n");
        }
    }
|   Factor GEQ Factor  {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. - Comps \n");
        }
    }
|   Factor  { $$.type = $1.type; $$.lexemes = $1.lexemes;}
;

Factor:
    NOT AriOp {
        if ($2.type == BOOL_TYPE ) {
            $$.type = BOOL_TYPE;
            $$.value.v_bool = !$2.value.v_bool;
        } else {
            printf("ERROR! Incompatible type. - Factor \n");
        }
    }
|   AriOp { $$.type = $1.type; $$.lexemes = $1.lexemes; }
;

AriOp:
    AriOp PLUS AriOp2 {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = INT_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. - AriOp \n");
        }
    }
|   AriOp MINUS AriOp2 {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = INT_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. - AriOp \n");
        }
    }
|   AriOp2 { $$.type = $1.type; $$.lexemes = $1.lexemes;}
;

AriOp2:
    AriOp2 MULTIPLY Parenthesis {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = INT_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. - AriOp2 \n");
        }
    }
|   AriOp2 DIVIDE Parenthesis {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = INT_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. - AriOp2 \n");
        }
    }
|   AriOp2 MOD Parenthesis {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = INT_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            // TODO
            printf("TODO. \n");
        } else {
            printf("ERROR! Incompatible type. - AriOp2 \n");
        }
    }
|   Parenthesis { $$.type = $1.type; $$.lexemes = $1.lexemes;}
;

Parenthesis:
    UnaryExp { $$.type = $1.type; $$.lexemes = $1.lexemes;}
|   LPAR Exp RPAR { $$.type = $2.type; }
;

UnaryExp:
    PLUS CastExp { 
        if ($2.type == INT_TYPE || $2.type == REAL_TYPE) {
            $$.type = $2.type;
        } else { 
            printf("ERROR! Incompatible type. - UnaryExp \n");
        }
    }
|   MINUS CastExp { 
        if ($2.type == INT_TYPE || $2.type == REAL_TYPE) {
            $$.type = $2.type;
        } else { 
            printf("ERROR! Incompatible type. - UnaryExp \n");
        }
    }
|   CastExp { $$.type = $1.type; $$.lexemes = $1.lexemes;}
;

CastExp:
    LPAR T_INT RPAR SimpleExp       {
        if ($4.type == INT_TYPE) {
            $$.type = INT_TYPE;
            $$.value.v_int = $4.value.v_int;
        }
        if ($4.type == REAL_TYPE) {
            $$.type = INT_TYPE;
            $$.value.v_int = $4.value.v_real;
        }
        if ($4.type == BOOL_TYPE) {
            $$.type = INT_TYPE;
            $$.value.v_int = $4.value.v_bool;
        }
        if ($4.type == CHAR_TYPE) {
            $$.type = INT_TYPE;
            $$.value.v_int = $4.value.v_char;
        }
    }
|   LPAR T_REAL RPAR SimpleExp      {
        if ($4.type == INT_TYPE) {
            $$.type = REAL_TYPE;
            $$.value.v_real = $4.value.v_int;
        }
        if ($4.type == REAL_TYPE) {
            $$.type = REAL_TYPE;
            $$.value.v_real = $4.value.v_real;
        }
        if ($4.type == BOOL_TYPE) {
            $$.type = REAL_TYPE;
            $$.value.v_real = $4.value.v_bool;
        }
        if ($4.type == CHAR_TYPE) {
            $$.type = REAL_TYPE;
            $$.value.v_real = $4.value.v_char;
        }
}
|   LPAR T_BOOL RPAR SimpleExp      {
        if ($4.type == INT_TYPE) {
            $$.type = BOOL_TYPE;
            $$.value.v_bool = $4.value.v_int > 0;
        }
        if ($4.type == REAL_TYPE) {
            $$.type = BOOL_TYPE;
            $$.value.v_bool = $4.value.v_real > 0.0;
        }
        if ($4.type == BOOL_TYPE) {
            $$.type = BOOL_TYPE;
            $$.value.v_bool = $4.value.v_bool;
        }
        if ($4.type == CHAR_TYPE) {
            printf("char para bool pode não!\n");
        }
}
|   LPAR T_CHAR RPAR SimpleExp      {
    if ($4.type == INT_TYPE) {
        $$.type = CHAR_TYPE;
        // TODO If
        $$.value.v_char = $4.value.v_int;
    }
    if ($4.type == REAL_TYPE) {
        printf("real para char pode não!\n");
    }
    if ($4.type == BOOL_TYPE) {
        printf("bool para char pode não!\n");
    }
    if ($4.type == CHAR_TYPE) {
        $$.type = CHAR_TYPE;
        $$.value.v_char = $4.value.v_char;
    }
}
|   SimpleExp                       {
    $$.type = $1.type;
    $$.lexemes = $1.lexemes;
}

SimpleExp:
    NumExp { $$.type = $1.type; $$.lexemes = $1.lexemes;}
|   AcessMemAddr { $$.type = $1.type; $$.lexemes = $1.lexemes;}
;

NumExp:
    V_INT    { $$.type = INT_TYPE; $$.value.v_int = $1.value.v_int; $$.lexemes = $1.lexemes;}
|   V_REAL   { $$.type = REAL_TYPE; $$.value.v_real = $1.value.v_real; $$.lexemes = $1.lexemes;}
|   V_BOOL   { $$.type = BOOL_TYPE; $$.value.v_bool = $1.value.v_bool; $$.lexemes = $1.lexemes;}
|   V_CHAR   { $$.type = CHAR_TYPE; $$.value.v_char = $1.value.v_char; $$.lexemes = $1.lexemes;}
|   V_STRING { $$.type = ARRAY; /*TODO*/}
;

Args : 
    Exp ArgsAux {}
|   /* NOTHING */ {}
;

ArgsAux : COMMA Args {}
|   /* NOTHING */ {}
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
    return 0;
}
