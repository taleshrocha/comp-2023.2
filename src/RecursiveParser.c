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
    //TODO: integrate with lexer.
    //return yylex();
    return 0;
}

int lookahead = -1;

void initializeParsing(){
	lookahead = getNextToken();
	Prog();
}


void error(){
	printf("error() - Syntax error. Lookahead did not match the current token.");
}


void eat(int token){
	if(token == lookahead){
		lookahead = getNextToken();
	}
	else{
		error();
	}
	
}

void Prog(){
	switch (lookahead){
        case CONST: 	Decl(); CmdBlock(); break;
        case TYPE:      Decl(); CmdBlock(); break;
        case PROCEDURE: Decl(); CmdBlock(); break;
        case FUNCTION: 	Decl(); CmdBlock(); break;
        case VAR: 	    Decl(); CmdBlock(); break;
        case _BEGIN: 	Decl(); CmdBlock(); break;	
        default:        printf("Syntax error.");
    }
}

void Decl(){
	switch (lookahead){
        case CONST: 	Consts(); Types(); SubProg(); Vars(); break;
	    case TYPE: 	    Consts(); Types(); SubProg(); Vars(); break;
        case PROCEDURE: Consts(); Types(); SubProg(); Vars(); break;
        case FUNCTION: 	Consts(); Types(); SubProg(); Vars(); break;
        case VAR: 	    Consts(); Types(); SubProg(); Vars(); break;
        case _BEGIN: 	Consts(); Types(); SubProg(); Vars(); break;
        default:        printf("Syntax error.");
    }
}


void Consts(){
	switch (lookahead){
		case CONST:		eat(CONST); eat(ID); eat(ATTRIB); Exp(); eat(SEMICOLON); Consts(); break;
		case TYPE:		break; //lambda - search on FOLLOW. removing Consts from stack...
		case PROCEDURE: break; //lambda - search on FOLLOW. removing Consts from stack...
		case FUNCTION: 	break; //lambda - search on FOLLOW. removing Consts from stack...
		case VAR: 		break; //lambda - search on FOLLOW. removing Consts from stack...
		case _BEGIN: 	break; //lambda - search on FOLLOW. removing Consts from stack...
		default: 		printf("Syntax error.");
	}
}

void Exp(){
	switch (lookahead){
        case ID: 	    Terms(); Exp_(); break;
        case NOT: 	    Terms(); Exp_(); break;
        case PLUS: 	    Terms(); Exp_(); break;
        case MINUS: 	Terms(); Exp_(); break;
        case LPAR: 	    Terms(); Exp_(); break;
        case V_INT: 	Terms(); Exp_(); break;
        case V_CHAR: 	Terms(); Exp_(); break;
        case V_REAL: 	Terms(); Exp_(); break;
        case V_BOOL: 	Terms(); Exp_(); break;
        case V_STRING: 	Terms(); Exp_(); break;
        default:        printf("Syntax error.");
    }
}

void Exp_(){
	switch (lookahead){
		case SEMICOLON:	break; //lambda - search on FOLLOW
		case RPAR:		break; //lambda - search on FOLLOW
		case RBRA:		break; //lambda - search on FOLLOW
		case END:		break; //lambda - search on FOLLOW
		case INTERVAL:	break; //lambda - search on FOLLOW
		case COMMA:		break; //lambda - search on FOLLOW
		case _BEGIN:	break; //lambda - search on FOLLOW
		case TO:		break; //lambda - search on FOLLOW
		case STEP:		break; //lambda - search on FOLLOW
		case THEN:		break; //lambda - search on FOLLOW
		case OR: 		eat(OR); Terms(); Exp_(); break;
		default: 		printf("Syntax error.");
	}
}

void Terms(){
	switch (lookahead){
		case ID:		Comps(); Terms_(); break;
		case NOT:		Comps(); Terms_(); break;
		case PLUS:		Comps(); Terms_(); break;
		case MINUS:		Comps(); Terms_(); break;
		case LPAR: 		Comps(); Terms_(); break;
		case V_INT: 	Comps(); Terms_(); break;
		case V_CHAR: 	Comps(); Terms_(); break;
		case V_REAL: 	Comps(); Terms_(); break;
		case V_BOOL: 	Comps(); Terms_(); break;
		case V_STRING: 	Comps(); Terms_(); break;
		default: 		printf("Syntax error.");
	}
}

void Terms_(){
	switch (lookahead){
		case SEMICOLON:	break;
		case OR: 		break;
		case AND: 		eat(AND); Comps(); Terms_(); break;
		case RPAR:		break;
		case RBRA:		break;
		case END: 		break;
		case INTERVAL:	break;
		case COMMA:		break;
		case _BEGIN:	break;
		case TO:		break;
		case STEP:		break;
		case THEN:		break;
		default:		printf("Syntax error.");
	}
}

void Comps(){
	switch (lookahead){
		case ID: 		Factor(); Comps_(); break;
		case NOT: 		Factor(); Comps_(); break;
		case PLUS: 		Factor(); Comps_(); break;
		case MINUS: 	Factor(); Comps_(); break;
		case LPAR: 		Factor(); Comps_(); break;
		case V_INT: 	Factor(); Comps_(); break;
		case V_REAL: 	Factor(); Comps_(); break;
		case V_BOOL: 	Factor(); Comps_(); break;
		case V_CHAR: 	Factor(); Comps_(); break;
		case V_STRING: 	Factor(); Comps_(); break;
		default: 		printf("Syntax error.");
	}
}

void Comps_(){
	switch (lookahead){
		case SEMICOLON: break;
		case OR: 		break;
		case AND: 		break;
		case NEQ:		eat(NEQ); 		Factor(); break;
		case EQ:		eat(EQ); 		Factor(); break;
		case GREATER:	eat(GREATER); 	Factor(); break;
		case LESS:		eat(LESS); 		Factor(); break;
		case LEQ:		eat(LEQ); 		Factor(); break;
		case GEQ:		eat(GEQ); 		Factor(); break;
		case RPAR:		break;
		case RBRA:		break;
		case INTERVAL:	break;
		case END:		break;
		case COMMA:		break;
		case _BEGIN: 	break;
		case TO:		break;
		case STEP:		break;
		case THEN:		break;
		default: 		printf("Syntax error.");
	}
}

void Factor(){
	switch (lookahead){
		case ID: 		AriOp(); 	break;
		case NEQ: 		eat(NEQ); 	break;
		case PLUS:		AriOp();	break;
		case MINUS:		AriOp();	break;
		case LPAR: 		AriOp(); 	break;
		case V_INT: 	AriOp(); 	break;
		case V_REAL: 	AriOp(); 	break;
		case V_BOOL: 	AriOp(); 	break;
		case V_CHAR: 	AriOp(); 	break;
		case V_STRING: 	AriOp(); 	break;
		default: 		printf("Syntax error.");
	}
}


void AriOp(){
	switch (lookahead){
		case ID:		AriOp2(); AriOp_(); break;
		case PLUS:		AriOp2(); AriOp_(); break;
		case MINUS:		AriOp2(); AriOp_(); break;
		case LPAR: 		AriOp2(); AriOp_(); break;
		case V_INT: 	AriOp2(); AriOp_(); break;
		case V_REAL: 	AriOp2(); AriOp_(); break;
		case V_BOOL: 	AriOp2(); AriOp_(); break;
		case V_CHAR: 	AriOp2(); AriOp_(); break;
		case V_STRING: 	AriOp2(); AriOp_(); break;
		default: 		printf("Syntax error.");
	}
}


void AriOp_(){
	switch (lookahead){
		case SEMICOLON: break;
		case OR: 		break;
		case AND: 		break;
		case NEQ: 		break;
		case EQ: 		break;
		case LESS: 		break;
		case GREATER: 	break;
		case LEQ: 		break;
		case GEQ: 		break;
		case PLUS:		eat(PLUS); 	AriOp2(); AriOp_(); break;
		case MINUS:		eat(MINUS); AriOp2(); AriOp_(); break;
		case RPAR:		break;
		case RBRA:		break;
		case END:		break;
		case INTERVAL: 	break;
		case COMMA:		break;
		case _BEGIN:	break;
		case TO:		break;
		case STEP:		break;
		case THEN:		break;
		default: 		printf("Syntax error.");
	}

}

void AriOp2(){
	switch (lookahead){
		case ID: 		Parenthesis(); AriOp2_(); break;
		case PLUS: 		Parenthesis(); AriOp2_(); break;
		case MINUS: 	Parenthesis(); AriOp2_(); break;
		case LPAR: 		Parenthesis(); AriOp2_(); break;
		case V_INT: 	Parenthesis(); AriOp2_(); break;
		case V_REAL: 	Parenthesis(); AriOp2_(); break;
		case V_CHAR: 	Parenthesis(); AriOp2_(); break;
		case V_BOOL: 	Parenthesis(); AriOp2_(); break;
		case V_STRING: 	Parenthesis(); AriOp2_(); break;
		default: 		printf("Syntax error.");
	}
}


void AriOp2_(){
	switch (lookahead){
		case SEMICOLON: break;
		case OR: 		break;
		case AND: 		break;
		case NEQ: 		break;
		case EQ: 		break;
		case LESS: 		break;
		case GREATER: 	break;
		case LEQ: 		break;
		case GEQ: 		break;
		case PLUS:		break;
		case MINUS:		break;
		case MULTIPLY: 	eat(MULTIPLY); 	Parenthesis(); AriOp2_(); break;
		case DIVIDE: 	eat(DIVIDE); 	Parenthesis(); AriOp2_(); break;
		case MOD: 		eat(MOD); 		Parenthesis(); AriOp2_(); break;
		case RPAR:		break;
		case RBRA:		break;
		case END:		break;
		case INTERVAL: 	break;
		case COMMA:		break;
		case _BEGIN:	break;
		case TO:		break;
		case STEP:		break;
		case THEN:		break;
		default: 		printf("Syntax error.");
	}
}

void Parenthesis(){
	switch (lookahead){
		case ID: 		UnaryExp();	break;
		case PLUS: 		UnaryExp();	break;
		case MINUS: 	UnaryExp();	break;
		case LPAR:		eat(LPAR);	Exp();	eat(RPAR); break;
		case V_INT: 	UnaryExp(); 	break;
		case V_REAL: 	UnaryExp();  	break;
		case V_CHAR: 	UnaryExp();  	break;
		case V_BOOL: 	UnaryExp(); 	break;
		case V_STRING: 	UnaryExp(); 	break;
		default: 		printf("Syntax error.");
	}
}

void UnaryExp(){
	switch (lookahead){
		case ID: 		SimpleExp();	break;
		case PLUS:		eat(PLUS); 		UnaryExp();	break;
		case MINUS: 	eat(MINUS);		UnaryExp();	break;
		case V_INT: 	SimpleExp(); 	break;
		case V_REAL: 	SimpleExp();  	break;
		case V_CHAR: 	SimpleExp();  	break;
		case V_BOOL: 	SimpleExp(); 	break;
		case V_STRING: 	SimpleExp(); 	break;
		default: 		printf("Syntax error.");
	}
}

void SimpleExp(){
	switch (lookahead){
		case ID: 		AcessMemAddr(); break;
		case V_INT: 	NumExp(); 		break;
		case V_REAL: 	NumExp();  		break;
		case V_CHAR: 	NumExp();  		break;
		case V_BOOL: 	NumExp(); 		break;
		case V_STRING: 	NumExp(); 		break;
		default: 		printf("Syntax error.");
	}
}

void NumExp(){
	switch (lookahead){
		case V_INT: 	eat(V_INT); 		break;
		case V_REAL: 	eat(V_REAL);  		break;
		case V_CHAR: 	eat(V_CHAR);  		break;
		case V_BOOL: 	eat(V_BOOL); 		break;
		case V_STRING: 	eat(V_STRING); 		break;
		default: 		printf("Syntax error.");
	}
}

void AcessMemAddr(){
	switch (lookahead){
		case ID: 	eat(ID); AcessMemAddr_(); break;
		default: 	printf("Syntax error.");
	}
}

void AcessMemAddr_(){
	switch (lookahead){
		case ATTRIB:	break;
		case SEMICOLON:	break;
		case OR:		break;
		case AND:		break;
		case NEQ:		break;
		case EQ: 		break;
		case LESS: 		break;
		case GREATER: 	break;
		case LEQ: 		break;
		case GEQ: 		break;
		case PLUS: 		break;
		case MINUS: 	break;
		case MULTIPLY: 	break;
		case DIVIDE: 	break;
		case MOD: 		break;
		case LPAR:		eat(LPAR); 	Args(); 	eat(RPAR); AcessMemAddr_(); break;
		case RPAR:		break;
		case DOT:		eat(DOT); 	eat(ID); 	AcessMemAddr_(); break;
		case LBRA:		eat(LBRA); 	Exp(); 		eat(RBRA); AcessMemAddr_(); break;
		case RBRA:		break;
		case END:		break;
		case INTERVAL:	break;
		case COMMA:		break;
		case _BEGIN:	break;
		case TO:		break;
		case STEP:		break;
		case THEN:		break;
		default: 		printf("Syntax error.");
	}
}


void Types(){
	switch (lookahead){
		case TYPE: 		eat(TYPE); eat(ID); eat(ATTRIB); TypeDec(); eat(SEMICOLON); Types(); break;
		case PROCEDURE: break;
		case FUNCTION: 	break;
		case VAR: 		break;
		case _BEGIN: 	break;
		default: 		printf("Syntax error.");
	}

}

void TypeDec(){
	switch (lookahead){
		case ID: 		eat(ID); 		break;
		case T_INT: 	eat(T_INT); 	break;
		case T_REAL: 	eat(T_REAL); 	break;
		case T_BOOL: 	eat(T_BOOL); 	break;
		case T_CHAR: 	eat(T_CHAR); 	break;
		case ARRAY: 	eat(ARRAY); 	eat(LBRA); Interval(); eat(RBRA); eat(OF); TypeDec(); break;
		case RECORD:	eat(RECORD); 	Fields();  eat(END); break;
		default: 		printf("Syntax error.");
	}

}

void Interval(){
	switch (lookahead){
		case ID: 		Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case NEQ: 		Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case PLUS: 		Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case MINUS: 	Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case LPAR: 		Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case V_INT: 	Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case V_BOOL: 	Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case V_REAL: 	Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case V_CHAR: 	Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case V_STRING: 	Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		default: 		printf("Syntax error.");
	}

}

void Interval_(){
	switch (lookahead){
		case RBRA: 		break;
		case COMMA: 	eat(COMMA); Interval(); break;
		default: 		printf("Syntax error.");
	}
}

void Fields(){
	switch (lookahead){
		case ID:  	eat(ID); eat(COLON); TypeDec(); eat(SEMICOLON); Fields(); break;
		case END: 	break;
		default: 	printf("Syntax error.");
	}
}

