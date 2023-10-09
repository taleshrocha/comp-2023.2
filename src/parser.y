%{
#include <stdio.h>
#include <lexer.l.h>
#include <typedefs.h>

extern struct Node;

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
%token CONST ID ATTRIB SEMICOLON OR AND NEQ EQ LESS GREATER LEQ GEQ NOT PLUS MINUS MULTIPLY DIVIDE MOD LPAR RPAR V_INT V_REAL V_BOOL V_CHAR V_STRING DOT LBRA RBRA TYPE T_BOOL T_INT T_REAL T_CHAR ARRAY OF RECORD END INTERVAL COMMA COLON PROCEDURE FUNCTION VAR BEGIN_ FOR TO STEP LOOP EXIT WHEN CONTINUE BREAK IF THEN ELSE RETURN REF

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
        } val;
        struct Node* tree;
    } info;
}

%start Prog 

%type <info> NumExp SimpleExp UnaryExp Parenthesis AriOp2 AriOp Factor Comps Terms Exp CastExp CmdReturnExp AcessMemAddr CmdAux

%%

Prog : 
    Decl CmdBlock {}
;
Decl : 
    Consts Types SubProg Vars {}
;
Consts :
    CONST ID ATTRIB Exp SEMICOLON Consts {}
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
    T_BOOL {}
|   T_INT {}
|   T_REAL {}
|   T_CHAR {}
|   ID {}
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
    PROCEDURE ID LPAR Parameters RPAR CmdBlock SEMICOLON {}
;

Parameters:
    ID COLON TypeDec ParametersAux {}
    REF ID COLON TypeDec ParametersAux {}
|   /* NOTHING */ {}
;

ParametersAux:
    COMMA Parameters {}
|   /* NOTHING */ {}
;

FunctionDecl:
    FUNCTION ID LPAR Parameters RPAR COLON TypeDec CmdBlock SEMICOLON {}
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
        if ($$.type != $2.type) {
            // TODO: ERROR
        }
    }
|   CmdBlock {}
|   CmdConditional {}
|   CONTINUE {}
|   BREAK {}
|   FOR AcessMemAddr ATTRIB Exp TO Exp STEP Exp CmdBlock {




    }
|   LOOP Vars Cmds END {}
|   EXIT WHEN Exp {}
|   CmdReturn {}
;

AcessMemAddr: 
    ID {
        //TODO
    }
|   AcessMemAddr DOT ID {}
|   AcessMemAddr LBRA Exp RBRA {
        if ($3.type == T_INT) {
            $$.type = $3.type;
        } else {
            printf("ERROR");
        }
}
|   AcessMemAddr LPAR Args RPAR {}
;

CmdConditional:
    IF Exp THEN CmdBlock CmdConditionalEnd {
        if ($2.type != T_BOOL) {
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
        // TODO lookup tipo da função/proc mais próxima
    }
;

CmdReturnExp:
    Exp { $$.type = $1.type; }
|   /* NOTHING */ {}
;

Exp:
    Exp OR Terms {
        if ($1.type == T_BOOL && $3.type == T_BOOL) {
            $$.type = T_BOOL;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Terms { $$.type = $1.type; }
;

Terms:
    Terms AND Comps {
        if ($1.type == T_BOOL && $3.type == T_BOOL) {
            $$.type = T_BOOL;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Comps { $$.type = $1.type; }
;

Comps: 
    Factor NEQ Factor {
        if ($1.type == T_INT && $3.type == T_INT) {
            $$.type = T_BOOL;
        } else if ($1.type == T_REAL && $3.type == T_REAL) {
            $$.type = T_BOOL;
        } else if ($1.type == T_BOOL && $3.type == T_BOOL) {
            $$.type = T_BOOL;
        } else if ($1.type == T_CHAR && $3.type == T_CHAR) {
            $$.type = T_BOOL;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Factor EQ Factor  {
        if ($1.type == T_INT && $3.type == T_INT) {
            $$.type = T_BOOL;
        } else if ($1.type == T_REAL && $3.type == T_REAL) {
            $$.type = T_BOOL;
        } else if ($1.type == T_BOOL && $3.type == T_BOOL) {
            $$.type = T_BOOL;
        } else if ($1.type == T_CHAR && $3.type == T_CHAR) {
            $$.type = T_BOOL;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Factor LESS Factor {
        if ($1.type == T_INT && $3.type == T_INT) {
            $$.type = T_BOOL;
        } else if ($1.type == T_REAL && $3.type == T_REAL) {
            $$.type = T_BOOL;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Factor GREATER Factor  {
        if ($1.type == T_INT && $3.type == T_INT) {
            $$.type = T_BOOL;
        } else if ($1.type == T_REAL && $3.type == T_REAL) {
            $$.type = T_BOOL;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Factor LEQ Factor {
        if ($1.type == T_INT && $3.type == T_INT) {
            $$.type = T_BOOL;
        } else if ($1.type == T_REAL && $3.type == T_REAL) {
            $$.type = T_BOOL;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Factor GEQ Factor  {
        if ($1.type == T_INT && $3.type == T_INT) {
            $$.type = T_BOOL;
        } else if ($1.type == T_REAL && $3.type == T_REAL) {
            $$.type = T_BOOL;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   Factor  { $$.type = $1.type; }
;

Factor:
    NOT AriOp {
        if ($2.type == T_BOOL ) {
            $$.type = T_BOOL;
            $$.val = !$2.val;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   AriOp { $$.type = $1.type; }
;

AriOp:
    AriOp PLUS AriOp2 {
        if ($1.type == T_INT && $3.type == T_INT) {
            $$.type = T_INT;
        } else if ($1.type == T_REAL && $3.type == T_REAL) {
            $$.type = T_REAL;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   AriOp MINUS AriOp2 {
        if ($1.type == T_INT && $3.type == T_INT) {
            $$.type = T_INT;
        } else if ($1.type == T_REAL && $3.type == T_REAL) {
            $$.type = T_REAL;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   AriOp2 { $$.type = $1.type; }
;

AriOp2:
    AriOp2 MULTIPLY Parenthesis {
        if ($1.type == T_INT && $3.type == T_INT) {
            $$.type = T_INT;
        } else if ($1.type == T_REAL && $3.type == T_REAL) {
            $$.type = T_REAL;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   AriOp2 DIVIDE Parenthesis {
        if ($1.type == T_INT && $3.type == T_INT) {
            $$.type = T_INT;
        } else if ($1.type == T_REAL && $3.type == T_REAL) {
            $$.type = T_REAL;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
|   AriOp2 MOD Parenthesis {
        if ($1.type == T_INT && $3.type == T_INT) {
            $$.type = T_INT;
        } else if ($1.type == T_REAL && $3.type == T_REAL) {
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
        if ($1.type == INT || $1.type == REAL) {
            $$.type = $1.type;
        } else { 
            printf("ERROR! Incompatible type. \n");
        }
    }
|   MINUS CastExp { 
        if ($1.type == INT || $1.type == REAL) {
            $$.type = $1.type;
        } else { 
            printf("ERROR! Incompatible type. \n");
        }
    }
|   CastExp { $$.type = $1.type; }
;

CastExp:
    LPAR T_INT RPAR SimpleExp       {
        if ($4.type == T_INT) {
            $$.type == T_INT;
            $$.val = $4.val;
        }
        if ($4.type == T_REAL) {
            $$.type == T_INT;
            $$.val = $4.val;
        }
        if ($4.type == T_BOOL) {
            $$.type == T_INT;
            $$.val = $4.val;
        }
        if ($4.type == T_CHAR) {
            $$.type == T_INT;
            $$.val = $4.val;
        }
    }
|   LPAR T_REAL RPAR SimpleExp      {
        if ($4.type == T_INT) {
            $$.type == T_REAL;
            $$.val = $4.val;
        }
        if ($4.type == T_REAL) {
            $$.type == T_REAL;
            $$.val = $4.val;
        }
        if ($4.type == T_BOOL) {
            $$.type == T_REAL;
            $$.val = $4.val;
        }
        if ($4.type == T_CHAR) {
            $$.type == T_REAL;
            $$.val = $4.val;
        }
}
|   LPAR T_BOOL RPAR SimpleExp      {
        if ($4.type == T_INT) {
            $$.type == T_BOOL;
            $$.val = $4.val > 0;
        }
        if ($4.type == T_REAL) {
            $$.type == T_BOOL;
            $$.val = $4.val > 0.0;
        }
        if ($4.type == T_BOOL) {
            $$.type == T_BOOL;
            $$.val = $4.val;
        }
        if ($4.type == T_CHAR) {
            printf("char para bool pode não!\n");
        }
}
|   LPAR T_CHAR RPAR SimpleExp      {
    if ($4.type == T_INT) {
        $$.type == T_CHAR;
        // TODO If
        $$.val = $4.val;
    }
    if ($4.type == T_REAL) {
        printf("real para char pode não!\n");
    }
    if ($4.type == T_BOOL) {
        printf("bool para char pode não!\n");
    }
    if ($4.type == T_CHAR) {
        $$.type == T_CHAR;
        $$.val = $4.val;
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
    V_INT    { $$.type = T_INT;  }
|   V_REAL   { $$.type = T_REAL; }
|   V_BOOL   { $$.type = T_BOOL; }
|   V_CHAR   { $$.type = T_CHAR; }
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
