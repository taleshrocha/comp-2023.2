%{
#include <stdio.h>
#include <lexer.l.h>

extern struct Node;

extern int column_counter;

void yyerror(char* s) {
    fprintf(stderr, "%s at line-column: %d-%d\n", s , yylineno, column_counter);
    fprintf(stderr, "current token is: \"%s\"\n", yytext);
}
%}

%token CONST ID ATTRIB SEMICOLON OR AND NEQ EQ LESS GREATER LEQ GEQ NOT PLUS MINUS MULTIPLY DIVIDE MOD LPAR RPAR V_INT V_REAL V_BOOL V_CHAR V_STRING DOT LBRA RBRA TYPE T_BOOL T_INT T_REAL T_CHAR ARRAY OF RECORD END INTERVAL COMMA COLON PROCEDURE FUNCTION VAR BEGIN_ FOR TO STEP LOOP EXIT WHEN CONTINUE BREAK IF THEN ELSE RETURN    

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

%type <info> NumExp SimpleExp UnaryExp Parenthesis AriOp2 AriOp Factor Comps Terms Exp

%%

Prog : 
        Decl CmdBlock {}
;
Decl : 
        Consts Types SubProg Vars {}
;
Consts :
        CONST ID ATTRIB Exp SEMICOLON Consts {}
|       /* NOTHING */
;
Vars : 
        VAR ID COLON TypeDec SEMICOLON Vars {}
|       /* NOTHING */
;
Types :
        TYPE ID ATTRIB TypeDec SEMICOLON Types {}
|       /* NOTHING */
;
TypeDec :
        T_BOOL {}
|       T_INT {}
|       T_REAL {}
|       T_CHAR {}
|       ID {}
|       ARRAY LBRA Interval RBRA OF TypeDec  {}
|       RECORD Fields END {}
;
Interval :
        Exp INTERVAL Exp {}
|       Exp INTERVAL Exp COMMA Interval {}
;
Fields :
        ID COLON TypeDec SEMICOLON Fields {}
|       /* NOTHING */ {}
;
SubProg : 
        ProcedureDecl SubProg {}
|       FunctionDecl SubProg {}
|       /* NOTHING */ {}
;

ProcedureDecl :
        PROCEDURE ID LPAR Parameters RPAR CmdBlock SEMICOLON {}
;

Parameters:
        ID COLON TypeDec ParametersAux {}
|       /* NOTHING */ {}
;

ParametersAux:
        COMMA Parameters {}
|       /* NOTHING */ {}
;

FunctionDecl:
        FUNCTION ID LPAR Parameters RPAR COLON TypeDec CmdBlock SEMICOLON {}
;

CmdBlock :
        BEGIN_ Vars Cmds END {}
;

Cmds:
        CmdAux {}
|       CmdAux SEMICOLON Cmds {}
;

CmdAux:
        AcessMemAddr CmdAux_ {}
|       CmdBlock {}
|       CmdConditional {}
|       CONTINUE {}
|       BREAK {}
|       FOR ID ATTRIB Exp TO Exp STEP Exp CmdBlock {}
|       LOOP Vars Cmds END {}
|       EXIT WHEN Exp {}
|       CmdReturn {}
;

CmdAux_ : ATTRIB Exp {}
|       /* NOTHING */ {}
;


AcessMemAddr: 
        ID {}
|       AcessMemAddr DOT ID {}
|       AcessMemAddr LBRA Exp RBRA {}
|       AcessMemAddr LPAR Args RPAR {}
;

CmdConditional:
        IF Exp THEN CmdBlock CmdConditionalEnd {}
;

CmdConditionalEnd:
        ELSE CmdBlock {}
|       /* NOTHING */ {}
;

CmdReturn:
        RETURN CmdReturnExp {}
;

CmdReturnExp:
        Exp {}
|       /* NOTHING */ {}
;

Exp:
        Exp OR Terms {}
|       Terms {}
;

Terms:
        Terms AND Comps {}
|       Comps {}
;

Comps: 
        Factor NEQ Factor {}
|       Factor EQ Factor  {}
|       Factor LESS Factor {}
|       Factor GREATER Factor  {}
|       Factor LEQ Factor {}
|       Factor GEQ Factor  {}
|       Factor  {}
;

Factor:
        NOT AriOp {}
|       AriOp {}
;

AriOp:
        AriOp PLUS AriOp2 {}
|       AriOp MINUS AriOp2 {}
|       AriOp2 {}
;

AriOp2:
        AriOp2 MULTIPLY Parenthesis {
            if ($1.type == T_INT && $3.type == T_INT) {
                $$.type = T_INT;
            } else if ($1.type == T_INT && $3.type == T_REAL) {
                $$.type = T_REAL;
            } else if ($1.type == T_REAL && $3.type == T_INT) {
                $$.type = T_REAL;
            } else if ($1.type == T_REAL && $3.type == T_REAL) {
                $$.type = T_REAL;
            } else {
                printf("ERROR! Incompatible type. \n");
            }
        }
|       AriOp2 DIVIDE Parenthesis {
            if ($1.type == T_INT && $3.type == T_INT) {
                $$.type = T_INT;
            } else if ($1.type == T_INT && $3.type == T_REAL) {
                $$.type = T_REAL;
            } else if ($1.type == T_REAL && $3.type == T_INT) {
                $$.type = T_REAL;
            } else if ($1.type == T_REAL && $3.type == T_REAL) {
                $$.type = T_REAL;
            } else {
                printf("ERROR! Incompatible type. \n");
            }
        }
|       AriOp2 MOD Parenthesis {
            if ($1.type == T_INT && $3.type == T_INT) {
                $$.type = T_INT;
            } else if ($1.type == T_INT && $3.type == T_REAL) {
                $$.type = T_REAL;
            } else if ($1.type == T_REAL && $3.type == T_INT) {
                $$.type = T_REAL;
            } else if ($1.type == T_REAL && $3.type == T_REAL) {
                $$.type = T_REAL;
            } else {
                printf("ERROR! Incompatible type. \n");
            }
        }
|       Parenthesis { $$.type = $1.type; }
;

Parenthesis:
        UnaryExp { $$.type = $1.type; }
|       LPAR Exp RPAR { $$.type = $2.type; }
;

UnaryExp:
        PLUS SimpleExp { $$.type = $2.type; }
|       MINUS SimpleExp { $$.type = $2.type; }
|       SimpleExp { $$.type = $1.type; }
;

SimpleExp:
    NumExp { $$.type = $1.type; }
|   AcessMemAddr {}
;

NumExp:
        V_INT    { $$.type = T_INT;  }
|       V_REAL   { $$.type = T_REAL; }
|       V_BOOL   { $$.type = T_BOOL; }
|       V_CHAR   { $$.type = T_CHAR; }
|       V_STRING { $$.type = ARRAY; /*TODO*/}
;

Args : 
        Exp ArgsAux {}
|       /* NOTHING */ {}
;

ArgsAux : COMMA Args {}
|       /* NOTHING */ {}
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
