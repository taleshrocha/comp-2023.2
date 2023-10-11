%{
#include <stdio.h>
#include <lexer.l.h>
#include <typedefs.h>

#define INT_TYPE 1
#define REAL_TYPE 2
#define BOOL_TYPE 3
#define CHAR_TYPE 4

int args_types[100];
int args_size;
int type_counter = 5;

Node* createNode(int identifier, Node* children) {
    // TODO
    return NULL;
}

extern int column_counter;

void yyerror(char* s) {
    fprintf(stderr, "%s at line-column: %d-%d\n", s , yylineno, column_counter);
    fprintf(stderr, "current token is: \"%s\"\n", yytext);
}
%}

%token CONST ID ATTRIB SEMICOLON OR AND NEQ EQ LESS GREATER LEQ GEQ NOT PLUS MINUS MULTIPLY DIVIDE MOD LPAR RPAR V_INT V_REAL V_BOOL V_CHAR V_STRING DOT LBRA RBRA TYPE T_BOOL T_INT T_REAL T_CHAR ARRAY OF RECORD END INTERVAL COMMA COLON PROCEDURE FUNCTION VAR BEGIN_ FOR TO STEP LOOP EXIT WHEN CONTINUE BREAK IF THEN ELSE RETURN REF

%union {
    struct {
        int type;
        char* name;
        ValueData;
        struct Node* tree;
    } info;
}

%start Prog 

%type <info> NumExp SimpleExp UnaryExp Parenthesis AriOp2 AriOp Factor Comps Terms Exp CastExp CmdReturnExp AcessMemAddr Args TypeDec

%%

Prog : 
    Decl CmdBlock {}
;
Decl : 
    Consts Types SubProg Vars {}
;
Consts :
    CONST ID ATTRIB Exp SEMICOLON Consts {
        addConstant($2.name, $4.type, $4.value)
    }
|   /* NOTHING */
;
Vars : 
    VAR ID COLON TypeDec SEMICOLON Vars {}
|   /* NOTHING */
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
        // inserir na tabela
        // zerar argsize
        // 
    } CmdBlock SEMICOLON
;

Parameters:
    ID COLON TypeDec ParametersAux { args_types[args_size++] = $3.type; }
|   REF ID COLON TypeDec ParametersAux { args_types[args_size++] = $4.type; }
|   /* NOTHING */ {}
;

ParametersAux:
    COMMA Parameters { }
|   /* NOTHING */ {}
;

FunctionDecl:
    FUNCTION ID LPAR Parameters RPAR COLON TypeDec {
        // criar registro na tabela para def
        // apagar os dados de parametros após salvar a função na tabela de simbolos
    } CmdBlock SEMICOLON
;

CmdBlock :
    BEGIN_ Vars Cmds END {}
;

Cmds:
    CmdAux {}
|   CmdAux SEMICOLON Cmds {}
;

CmdAux:
    AcessMemAddr ATTRIB Exp {
        if ($1.type != $3.type) {
            // TODO: ERROR
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
        //TODO
    }
|   AcessMemAddr DOT ID {
        //TODO  
    }

|   AcessMemAddr LBRA Exp RBRA {
        if ($3.type == INT_TYPE) {
            $$.type = $3.type;
        } else {
            printf("ERROR");
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
    Exp { $$.type = $1.type; }
|   /* NOTHING */ { $$.type = -1;}
;

Exp:
    Exp OR Terms {
        if ($1.type == BOOL_TYPE && $3.type == BOOL_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Terms { $$.type = $1.type; }
;

Terms:
    Terms AND Comps {
        if ($1.type == BOOL_TYPE && $3.type == BOOL_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Comps { $$.type = $1.type; }
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
            printf("ERROR! Incompatible type. \n");
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
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Factor LESS Factor {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Factor GREATER Factor  {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Factor LEQ Factor {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Factor GEQ Factor  {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = BOOL_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Factor  { $$.type = $1.type; }
;

Factor:
    NOT AriOp {
        if ($2.type == BOOL_TYPE ) {
            $$.type = BOOL_TYPE;
            $$.v_bool = !$2.v_bool;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   AriOp { $$.type = $1.type; }
;

AriOp:
    AriOp PLUS AriOp2 {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = INT_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   AriOp MINUS AriOp2 {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = INT_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   AriOp2 { $$.type = $1.type; }
;

AriOp2:
    AriOp2 MULTIPLY Parenthesis {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = INT_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   AriOp2 DIVIDE Parenthesis {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = INT_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            $$.type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   AriOp2 MOD Parenthesis {
        if ($1.type == INT_TYPE && $3.type == INT_TYPE) {
            $$.type = INT_TYPE;
        } else if ($1.type == REAL_TYPE && $3.type == REAL_TYPE) {
            // TODO
            printf("TODO. \n");
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Parenthesis { $$.type = $1.type; }
;

Parenthesis:
    UnaryExp { $$.type = $1.type; }
|   LPAR Exp RPAR { $$.type = $2.type; }
;

UnaryExp:
    PLUS CastExp { 
        if ($2.type == INT_TYPE || $2.type == REAL_TYPE) {
            $$.type = $2.type;
        } else { 
            printf("ERROR! Incompatible type. \n");
        }
    }
|   MINUS CastExp { 
        if ($2.type == INT_TYPE || $2.type == REAL_TYPE) {
            $$.type = $2.type;
        } else { 
            printf("ERROR! Incompatible type. \n");
        }
    }
|   CastExp { $$.type = $1.type; }
;

CastExp:
    LPAR T_INT RPAR SimpleExp       {
        if ($4.type == INT_TYPE) {
            $$.type == INT_TYPE;
            $$.v_int = $4.v_int;
        }
        if ($4.type == REAL_TYPE) {
            $$.type == INT_TYPE;
            $$.v_int = $4.v_real;
        }
        if ($4.type == BOOL_TYPE) {
            $$.type == INT_TYPE;
            $$.v_int = $4.v_bool;
        }
        if ($4.type == CHAR_TYPE) {
            $$.type == INT_TYPE;
            $$.v_int = $4.v_char;
        }
    }
|   LPAR T_REAL RPAR SimpleExp      {
        if ($4.type == INT_TYPE) {
            $$.type == REAL_TYPE;
            $$.v_real = $4.v_int;
        }
        if ($4.type == REAL_TYPE) {
            $$.type == REAL_TYPE;
            $$.v_real = $4.v_real;
        }
        if ($4.type == BOOL_TYPE) {
            $$.type == REAL_TYPE;
            $$.v_real = $4.v_bool;
        }
        if ($4.type == CHAR_TYPE) {
            $$.type == REAL_TYPE;
            $$.v_real = $4.v_char;
        }
}
|   LPAR T_BOOL RPAR SimpleExp      {
        if ($4.type == INT_TYPE) {
            $$.type == BOOL_TYPE;
            $$.v_bool = $4.v_int > 0;
        }
        if ($4.type == REAL_TYPE) {
            $$.type == BOOL_TYPE;
            $$.v_bool = $4.v_real > 0.0;
        }
        if ($4.type == BOOL_TYPE) {
            $$.type == BOOL_TYPE;
            $$.v_bool = $4.v_bool;
        }
        if ($4.type == CHAR_TYPE) {
            printf("char para bool pode não!\n");
        }
}
|   LPAR T_CHAR RPAR SimpleExp      {
    if ($4.type == INT_TYPE) {
        $$.type == CHAR_TYPE;
        // TODO If
        $$.v_char = $4.v_int;
    }
    if ($4.type == REAL_TYPE) {
        printf("real para char pode não!\n");
    }
    if ($4.type == BOOL_TYPE) {
        printf("bool para char pode não!\n");
    }
    if ($4.type == CHAR_TYPE) {
        $$.type == CHAR_TYPE;
        $$.v_char = $4.v_char;
    }
}
|   SimpleExp                       {
    $$.type = $1.type;
}

SimpleExp:
    NumExp { $$.type = $1.type; }
|   AcessMemAddr { $$.type = $1.type; }
;

NumExp:
    V_INT    { $$.type = INT_TYPE;  }
|   V_REAL   { $$.type = REAL_TYPE; }
|   V_BOOL   { $$.type = BOOL_TYPE; }
|   V_CHAR   { $$.type = CHAR_TYPE; }
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
