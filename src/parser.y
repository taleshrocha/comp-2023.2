%{
#include <stdio.h>
%}

%token CONST ID ATTRIB SEMICOLON OR AND NEQ EQ LESS GREATER LEQ GEQ NOT PLUS MINUS MULTIPLY DIVIDE MOD LPAR RPAR V_INT V_REAL V_BOOL V_CHAR V_STRING DOT LBRA RBRA TYPE T_BOOL T_INT T_REAL T_CHAR ARRAY OF RECORD END INTERVAL COMMA COLON PROCEDURE FUNCTION VAR BEGIN_ FOR TO STEP LOOP EXIT WHEN CONTINUE BREAK IF THEN ELSE RETURN    
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD

%start Prog 

%%

Prog : 
        Decl CmdBlock                          {}
;
Decl : 
        Consts Types SubProg Vars              {}
;
Consts :
        CONST ID ATTRIB Exp SEMICOLON Consts          {}
|       /* NOTHING */
;
Vars : 
        VAR ID COLON TypeDec SEMICOLON Vars            {}
|       /* NOTHING */
;
Types :
        TYPE ID ATTRIB TypeDec SEMICOLON Types        {}
|       /* NOTHING */
;
TypeDec :
        T_BOOL
|       T_INT
|       T_REAL
|       T_CHAR
|       ID
|       ARRAY LBRA Interval RBRA OF TypeDec 
|       RECORD Fields END
;
Interval :
        Exp INTERVAL Exp
|       Exp INTERVAL Exp COMMA Interval
;
Fields :
        ID COLON TypeDec SEMICOLON Fields
|       /* NOTHING */
;
SubProg : 
        ProcedureDecl SubProg
|       FunctionDecl SubProg
|       /* NOTHING */
;

ProcedureDecl :
        PROCEDURE ID LPAR Parameters RPAR CmdBlock SEMICOLON
;

Parameters:
        ID COLON TypeDec ParametersAux
|       /* NOTHING */
;

ParametersAux:
        COMMA Parameters
|       /* NOTHING */
;

FunctionDecl:
        FUNCTION ID LPAR Parameters RPAR COLON TypeDec CmdBlock SEMICOLON
;

CmdBlock :
        BEGIN_ Vars Cmds END
;

Cmds:
        CmdAux
|       CmdAux SEMICOLON Cmds
;

CmdAux:
        AcessMemAddr CmdAux_
|       CmdBlock
|       CmdConditional
|       CONTINUE
|       BREAK
|       FOR ID ATTRIB Exp TO Exp STEP Exp CmdBlock
|       LOOP Vars Cmds END
|       EXIT WHEN Exp
|       CmdReturn
;

CmdAux_ : ATTRIB Exp
|       /* NOTHING */
;


AcessMemAddr: 
        ID
|       AcessMemAddr DOT ID
|       AcessMemAddr LBRA Exp RBRA
|       AcessMemAddr LPAR Args RPAR
;

CmdConditional:
        IF Exp THEN CmdBlock CmdConditionalEnd
;

CmdConditionalEnd:
        ELSE CmdBlock
|       /* NOTHING */
;

CmdReturn:
        RETURN CmdReturnExp
;

CmdReturnExp:
        Exp
|       /* NOTHING */
;

Exp:
        Exp OR Terms
|       Terms
;

Terms:
        Terms AND Comps
|       Comps
;

Comps: 
        Factor NEQ Factor
|       Factor EQ Factor 
|       Factor LESS Factor
|       Factor GREATER Factor 
|       Factor LEQ Factor
|       Factor GEQ Factor 
|       Factor 
;

Factor:
        NOT AriOp
|       AriOp
;

AriOp:
        AriOp PLUS AriOp2
|       AriOp MINUS AriOp2
|       AriOp2
;

AriOp2:
        AriOp2 MULTIPLY Parenthesis
|       AriOp2 DIVIDE Parenthesis
|       AriOp2 MOD Parenthesis
|       Parenthesis
;

Parenthesis:
        UnaryExp
|       LPAR Exp RPAR 
;

UnaryExp:
        PLUS SimpleExp
|       MINUS SimpleExp
|       SimpleExp
;

SimpleExp:
    NumExp
|   AcessMemAddr
;

NumExp:
        V_INT
|       V_REAL
|       V_BOOL
|       V_CHAR
|       V_STRING
;

Args : 
        Exp ArgsAux
|       /* NOTHING */
;

ArgsAux : COMMA Args
|       /* NOTHING */
;

%%

void yyerror(char * s)
/* yacc error handler */
{  
 fprintf (stderr, "%s\n", s);
}
  
int main(void)
 {
 return yyparse();
 }