#include <stdio.h>
#include <stdlib.h>
#include "recursiveParser.h"

#define ID 1
#define CONST 2
#define T_INT 3
#define T_REAL 4
#define T_CHAR 5
#define T_BOOL 6

#define V_INT 7
#define V_CHAR 8
#define V_BOOL 9
#define V_REAL 10
#define V_STRING 11

#define EQ 12
#define LEQ 13
#define GEQ 14
#define GREATER 15
#define LESS 16
#define NEQ 17

#define PLUS 18
#define MINUS 19
#define DIVIDE 20
#define MULTIPLY 21
#define MOD 22


#define LOOP 23
#define IF 24
#define ELSE 25
//#define ELSIF 26   --- REMOVIDO POR NAO ESTAR NA GRAMATICA
#define _BEGIN 26
#define END 27

#define AND 28
#define NOT 29
#define OR 30

#define TYPE 31
#define ARRAY 32
#define EXIT 33
#define WHEN 34
#define TO 35
#define STEP 36
#define THEN 37
#define ATTRIB 38 //Atribuicao


#define FUNCTION 39
#define PROCEDURE 40
#define RETURN 41
//#define BREAK 43      REMOVIDO POR NAO ESTAR NA GRAMATICA
#define CONTINUE 42
#define RECORD 43
#define OF 44
#define VAR 45

#define LPAR 46 // (
#define RPAR 47 // )
#define LBRA 48 //Left bracket [
#define RBRA 49 //right bracket ]

#define DOT 50
#define COMMA 51
#define SEMICOLON 52
#define COLON 53

#define FOR 54
#define INTERVAL 55 //Corresponds to '..'
/*
	Missing: $								
*/


int getNextToken(){
    //TODO: realizar integração
    //return yylex();
    return 0;
}

int lookahead = -1;


/*
TODO: Tratar ocorrência de erros sintáticos.
Retornar -1 ou executar exit(-1)? 
*/

//Prog -> Decl CmdBlock
void Prog(){
    Decl();
    CmdBlock();
}

//Decl -> Consts Types SubProg Vars
void Decl(){
    Consts();
    Types();
    SubProg();
    Vars();
}


//Consts -> const Id := Exp ; Consts
//Consts -> ''
void Consts(){
    if(lookahead == CONST){
        lookahead = getNextToken();
        if(lookahead == ID){
            lookahead = getNextToken();
            if(lookahead == ATTRIB){
                Exp();
                lookahead = getNextToken();
                if(lookahead == SEMICOLON){
                    Consts();
                }
                else{
                    printf("Syntax error! Expected ';'\n");
                }
            }
            else
                printf("Syntax error! Expected ':='\n");
        }else{
            printf("Syntax error! Expected an identifier\n");
        }
    }
    else{
        //printf("Syntax error! Expected 'const'\n");
        return; //Lambda ('')
    }
}

void Exp(){
    Terms();
    Exp_();
}

//Exp_ -> || Terms Exp_  
//Exp_ -> ''
void Exp_(){
    if(lookahead == OR){
        Terms();
        Exp_();
    }
    else{
        return; //Lambda ('')
    }
}

void Terms(){
    Comps();
    Terms_();
}

//Exp_ -> || Terms Exp_  
//Exp_ -> ''
void Terms_(){
    if(lookahead == AND){
        Comps();
        Terms_();
    }
    else{
        return; //Lambda ('')
    }
}

void Comps(){
    Factor();
    Comps_();
}

void Comps_(){
    if(lookahead == NEQ || 
    lookahead == EQ || 
    lookahead == GREATER ||
    lookahead == LESS || 
    lookahead == GEQ || 
    lookahead == LEQ ){
        Factor();
        return;
    }
    return; //Lamda
}

void Factor(){
    if(lookahead == NOT){
        AriOp();
        return;
    }
    AriOp();
}

void AriOp(){
    AriOp2();
    AriOp_();
}

void AriOp_(){
    if( lookahead == PLUS ||
        lookahead == MINUS){
        AriOp2();
        AriOp_();
        return;
    }
}

void AriOp2(){
    Parenthesis();
    AriOp2_();
}

void AriOp2_(){
    if( lookahead == MULTIPLY ||
        lookahead == DIVIDE ||
        lookahead == MOD){
        Parenthesis();
        AriOp2_();
        return;
    }
    //Lambda ('')
}

void Parenthesis(){
    if(lookahead == LPAR){
        Exp();
        lookahead = getNextToken();
        if(lookahead == RPAR){
            return;
        }
        else{
            printf("Syntax error! Expected ')'\n");
        }
    }
    else{
        UnaryExp();
    }
}

void UnaryExp(){
    if( lookahead == PLUS ||
        lookahead == MINUS){
        UnaryExp();
        return;
    }
    SimpleExp();
}

int isNumExp(int token){
    if(lookahead == V_INT ||
        lookahead == V_CHAR ||
        lookahead == V_BOOL ||
        lookahead == V_STRING ||
        lookahead == V_REAL){
        return 1;
    }
    else{
        return 0;
    }
}

void SimpleExp(){
    if(isNumExp(lookahead) == 1){
        return;
    }else{
        AcessMemAddr();
    }
}


// void NumExp(){

// }

void AcessMemAddr(){
    if(lookahead == ID){
        AcessMemAddr_();
    }else{
        printf("Syntax error! Expected an identifier\n");
    }
    
    
}

/*
AcessMemAddr_ -> . Id AcessMemAddr_
AcessMemAddr_ -> [ Exp ] AcessMemAddr_
AcessMemAddr_ -> ( Args ) AcessMemAddr_
AcessMemAddr_ -> ''
*/
void AcessMemAddr_(){
    if(lookahead == DOT){
        lookahead = getNextToken();
        if(lookahead == ID){
            AcessMemAddr_();
            return;
        }
        else{
            printf("Syntax error! Expected an identifier\n");
        }
    }
    else if(lookahead == LBRA){
        Exp();
        lookahead = getNextToken();
        if(lookahead == RBRA){
            AcessMemAddr_();
            return;
        }
        else{
            printf("Syntax error! Expected ']'\n");
        }
    }
    else if(lookahead == LPAR){
        Args();
        lookahead = getNextToken();
        if(lookahead == RPAR){
            AcessMemAddr_();
            return;
        }
        else{
            printf("Syntax error! Expected ')'\n");
        }
    }
    return; //Lambda ('')
}

/*
Types -> type Id := TypeDec ; Types
Types -> ''
*/
void Types(){
    if(lookahead == TYPE){
        lookahead = getNextToken();
        if(lookahead == ID){
            lookahead = getNextToken();
            if(lookahead == ATTRIB){
                TypeDec();
                lookahead = getNextToken();
                if(lookahead == SEMICOLON){
                    Types();
                }else{
                    printf("Syntax error! Expected ';'\n");
                }
            }else{
                printf("Syntax error! Expected ':='\n");
            }
        }
        else{
            printf("Syntax error! Expected an identifier\n");
        }
    }
    // else{
    //     printf("Syntax error! Expected 'type'\n");
    // }
    return; //Lambda ('')
    
}

void TypeDec(){
    if(lookahead == T_BOOL || lookahead == T_INT ||
        lookahead == T_REAL || lookahead == T_CHAR ||
        lookahead == ID){
        return;
    }
    else if (lookahead == ARRAY){
        lookahead = getNextToken();
        if(lookahead == LBRA){
            Interval();
            lookahead = getNextToken();
            if(lookahead == RBRA){
                lookahead = getNextToken();
                if(lookahead == OF){
                    TypeDec();
                    return;
                }else{
                    printf("Syntax error! Expected 'of'\n");
                }
            }else{
                printf("Syntax error! Expected ']'\n");
            }
        }else{
            printf("Syntax error! Expected '['\n");
        }
    }
    else if(lookahead == RECORD){
        Fields();
        lookahead = getNextToken();
        if(lookahead == END){
            return;
        }
        else{
            printf("Syntax error! Expected 'end'\n");
        }
    }else{
        printf("Syntax error! Expected 'bool', 'int', 'real', 'char', 'Id', 'array' or 'record'\n");
    }
    
}

void Interval(){
    Exp();
    if(lookahead == INTERVAL){
        Exp();
        Interval_();
    }
    else{
        printf("Syntax error! Expected '..'\n");
    }
}

void Interval_(){
    if(lookahead == COMMA){
        Interval();
        return;
    }
    return; //Lambda ('')
}

void Fields(){
    if(lookahead == ID){
        lookahead = getNextToken();
        if (lookahead == COLON)
        {
            TypeDec();
            lookahead = getNextToken();
            if(lookahead == SEMICOLON){
                Fields();
                return;
            }else{
                printf("Syntax error! Expected ';'\n");
            }
        }else{
            printf("Syntax error! Expected ':'\n");
        }
    }
    return; //Lambda ('')
}


/*
SubProg -> ProcedureDecl SubProg
SubProg -> FunctionDecl SubProg
SubProg -> ''
*/
void SubProg(){
    //Tive que fazer uma verificacao da primeira keyword 
    //  das regras ProcedureDecl e FunctionDecl para a distincao
    if(lookahead == PROCEDURE){
        ProcedureDecl();
        SubProg();
    }
    else if(lookahead == FUNCTION){
        FunctionDecl();
        SubProg();
    }
    else{
        //Lambda ('')
    }
}

void ProcedureDecl(){
    if(lookahead == PROCEDURE){
        if(lookahead == ID){
            lookahead = getNextToken();
            if(lookahead == LPAR){
                Parameters();
                lookahead = getNextToken();
                if(lookahead == RPAR){
                    CmdBlock();
                    return;
                }else{
                    printf("Syntax error! Expected ')'\n");
                }
            }
            else{
                printf("Syntax error! Expected '('\n");
            }
        }else{
            printf("Syntax error! Expected an identifier (procedure id)\n");
        }
    }
    else{
        printf("Syntax error! Expected 'procedure'\n");
    }
}

void FunctionDecl(){
    if(lookahead == FUNCTION){
        if(lookahead == ID){
            lookahead = getNextToken();
            if(lookahead == LPAR){
                Parameters();
                lookahead = getNextToken();
                if(lookahead == RPAR){
                    lookahead = getNextToken();
                    if(lookahead == COLON){
                        TypeDec();
                        CmdBlock();
                        lookahead = getNextToken();
                        if(lookahead == SEMICOLON){
                            return;
                        }
                        else{
                            printf("Syntax error! Expected ';'\n");
                        }
                    }else{
                        printf("Syntax error! Expected ':'\n");
                    }
                }else{
                    printf("Syntax error! Expected ')'\n");
                }
            }
            else{
                printf("Syntax error! Expected '('\n");
            }
        }else{
            printf("Syntax error! Expected an identifier (function id)\n");
        }
    }else{
        printf("Syntax error! Expected 'function'\n");
    }
}

void Parameters(){
    if(lookahead == ID){
        ParametersAux();
    }else{
        return; //lambda
    }
}

void ParametersAux(){
    if(lookahead == ID){
        lookahead = getNextToken();
        if(lookahead == COLON){
            TypeDec();
            ParametersAux_();
            return;
        }else{
            printf("Syntax error! Expected ':'");
        }
    }else{
        printf("Syntax error! Expected an identifier\n");
    }
}

void ParametersAux_(){
    if(lookahead == COMMA){
        ParametersAux();
        return; //end of rule ParametersAux_ -> , ParametersAux
    }
    return; //lambda
}

void Vars(){
    if(lookahead == VAR){
        lookahead = getNextToken();
        if(lookahead == ID){
            lookahead = getNextToken();
            if(lookahead == COLON){
                TypeDec();
                lookahead = getNextToken();
                if(lookahead == SEMICOLON){
                    Vars();
                    return;
                }else{
                    printf("Syntax error! Expected ';'\n");
                }
            }else{
                printf("Syntax error! Expected ':'\n");
            }
        }else{
            printf("Syntax error! Expected an identifier\n");
        }
    }
    else{
        return; //lambda
    }
}

void CmdBlock(){
    if(lookahead == _BEGIN){
        Vars();
        Cmds();
        lookahead = getNextToken();
        if(lookahead == END){
            return;
        }else{
            printf("Syntax error! Expected 'end'\n");
        }
    }else{
        printf("Syntax error! Expected 'begin'\n");
    }
}

void Cmds(){
    CmdAux();
    Cmds_();
}

void Cmds_(){
    if(lookahead == SEMICOLON){
        Cmds();
    }
    return; //lambda
}

void CmdAux(){
    if(lookahead == CONTINUE){
        return;
    }
    else if(lookahead == EXIT){
        lookahead = getNextToken();
        if(lookahead == WHEN){
            Exp();
            return;
        }else{
            printf("Syntax error! Expected 'when'\n");
        }
    }
    else if(lookahead == FOR){
        lookahead = getNextToken();
        if(lookahead == ID){
            lookahead = getNextToken();
            if(lookahead == ATTRIB){
                Exp();
                lookahead = getNextToken();
                if(lookahead == TO){
                    Exp();
                    lookahead = getNextToken();
                    if(lookahead == STEP){
                        Exp();
                        CmdBlock();
                        return;
                    }else{
                        printf("Syntax error! Expected 'step'\n");
                    }
                }else{
                    printf("Syntax error! Expected 'to'\n");
                }
            }else{
                printf("Syntax error! Expected ':='\n");
            }
            
        }else{
            printf("Syntax error! Expected an identifier\n");
        }
    }
    //TODO: Backtracking (tentativa e erro) para os seguintes casos:
    AcessMemAddr(); CmdAux_();
    CmdBlock();
    CmdConditional();
    CmdReturn();
}

void CmdAux_(){
    if(lookahead == ATTRIB){
        Exp();
    }
    return; //Lambda
}

void CmdConditional(){
    if(lookahead == IF){
        Exp();
        lookahead == getNextToken();
        if(lookahead == THEN){
            CmdBlock();
            CmdConditionalEnd();
            return;
        }
    }else{
        printf("Syntax error! Expected 'if'\n");
    }
}

void CmdConditionalEnd(){
    if(lookahead == ELSE){
        CmdBlock();
    }
    return; //lambda
}

void CmdReturn(){
    if(lookahead == RETURN){
        CmdReturnExp();
    }
    else{
        printf("Syntax error! Expected 'return'\n");
    }
}

void CmdReturnExp(){
    //TODO: Analisar este caso. Backtracking em caso de erro.
        //Usar primeiramente o Exp. Se der erro, considerar o lambda
}

void Args(){
    //TODO: Analisar este caso. Backtracking em caso de erro.
        //Usar primeiramente o ArgsAux. Se der erro, considerar o lambda
}

void ArgsAux(){
    Exp();
    ArgsAux_();
}

void ArgsAux_(){
    if(lookahead == COMMA){
        ArgsAux();
    }
    return; //lambda
}