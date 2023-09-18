#include <stdio.h>
#include <stdlib.h>
#include "recursiveParser.h"
#include "terminalDefines.h"
#include "symbolTable.h"
#include "lexer.h"


int getNextToken(){
  return yylex();
}

int lookahead = -1;

void initializeParsing(){
	lookahead = getNextToken();
	Prog();
}


void error(int token){
	printf("error() - Syntax error. Lookahead did not match the current token. Line : %d\n", yylineno);
	printf("Expected token %d-%s but found %d-%s.\n", token, terminal_mapping[token-1], lookahead, terminal_mapping[lookahead-1]);
}


void eat(int token){
	printf("token %d-%s\n", token, terminal_mapping[token-1]);
	if(token == lookahead){
    printf("\nMatch! - Token: %d\n\n", lookahead);
		lookahead = getNextToken();
	}
	else{
		error(token);
	}
	
}

void Prog(){
  printf("Entrei - Prog()\n");
	switch (lookahead){
        case CONST: 	Decl(); CmdBlock(); break;
        case TYPE:      Decl(); CmdBlock(); break;
        case PROCEDURE: Decl(); CmdBlock(); break;
        case FUNCTION: 	Decl(); CmdBlock(); break;
        case VAR: 	    Decl(); CmdBlock(); break;
        case _BEGIN: 	Decl(); CmdBlock(); break;	
        default:        printf("Syntax error. Grammar Rule: Prog. Line : %d\n", yylineno);
    }
}

void Decl(){
  printf("Entrei - Decl()\n");
	switch (lookahead){
        case CONST: 	Consts(); Types(); SubProg(); Vars(); break;
	    case TYPE: 	    Consts(); Types(); SubProg(); Vars(); break;
        case PROCEDURE: Consts(); Types(); SubProg(); Vars(); break;
        case FUNCTION: 	Consts(); Types(); SubProg(); Vars(); break;
        case VAR: 	    Consts(); Types(); SubProg(); Vars(); break;
        case _BEGIN: 	Consts(); Types(); SubProg(); Vars(); break;
        default:        printf("Syntax error. Grammar Rule: Decl. Line : %d\n", yylineno);
    }
}


void Consts(){
  printf("Entrei - Consts()\n");
	switch (lookahead){
		case CONST:		eat(CONST); eat(ID); eat(ATTRIB); Exp(); eat(SEMICOLON); Consts(); break;
		case TYPE:		break; //lambda - search on FOLLOW. removing Consts from stack...
		case PROCEDURE: break; //lambda - search on FOLLOW. removing Consts from stack...
		case FUNCTION: 	break; //lambda - search on FOLLOW. removing Consts from stack...
		case VAR: 		break; //lambda - search on FOLLOW. removing Consts from stack...
		case _BEGIN: 	break; //lambda - search on FOLLOW. removing Consts from stack...
		default: 		printf("Syntax error. Grammar Rule: Consts. Line : %d\n", yylineno);
	}
}

void Exp(){
  printf("Entrei - Exp()\n");
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
        default:        printf("Syntax error. Grammar Rule: Exp. Line : %d\n", yylineno);
    }
}

void Exp_(){
  printf("Entrei - Exp_()\n");
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
		default: 		printf("Syntax error. Grammar Rule: Exp_. Line : %d\n", yylineno);
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
		default: 		printf("Syntax error. Grammar Rule: Terms. Line : %d\n", yylineno);
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
		default:		printf("Syntax error. Grammar Rule: Terms_. Line : %d\n", yylineno);
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
		default: 		printf("Syntax error. Grammar Rule: Comps. Line : %d\n", yylineno);
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
		default: 		printf("Syntax error. Grammar Rule: Comps_. Line : %d\n", yylineno);
	}
}

void Factor(){
	switch (lookahead){
		case ID: 		AriOp(); 	break;
		case NOT: 		eat(NOT);	AriOp(); 	break;
		case PLUS:		AriOp();	break;
		case MINUS:		AriOp();	break;
		case LPAR: 		AriOp(); 	break;
		case V_INT: 	AriOp(); 	break;
		case V_REAL: 	AriOp(); 	break;
		case V_BOOL: 	AriOp(); 	break;
		case V_CHAR: 	AriOp(); 	break;
		case V_STRING: 	AriOp(); 	break;
		default: 		printf("Syntax error. Grammar Rule: Factor. Line : %d\n", yylineno);
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
		default: 		printf("Syntax error. Grammar Rule: AriOp. Line : %d\n", yylineno);
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
		default: 		printf("Syntax error. Grammar Rule: AriOp_. Line : %d\n", yylineno);
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
		default: 		printf("Syntax error. Grammar Rule: AriOp2. Line : %d\n", yylineno);
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
		default: 		printf("Syntax error. Grammar Rule: AriOp2_. Line : %d\n", yylineno);
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
		default: 		printf("Syntax error. Grammar Rule: Parenthesis. Line : %d\n", yylineno);
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
		default: 		printf("Syntax error. Grammar Rule: UnaryExp. Line : %d\n", yylineno);
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
		default: 		printf("Syntax error. Grammar Rule: SimpleExp. Line : %d\n", yylineno);
	}
}

void NumExp(){
	switch (lookahead){
		case V_INT: 	eat(V_INT); 		break;
		case V_REAL: 	eat(V_REAL);  		break;
		case V_CHAR: 	eat(V_CHAR);  		break;
		case V_BOOL: 	eat(V_BOOL); 		break;
		case V_STRING: 	eat(V_STRING); 		break;
		default: 		printf("Syntax error. Grammar Rule: NumExp. Line : %d\n", yylineno);
	}
}

void AcessMemAddr(){
	switch (lookahead){
		case ID: 	eat(ID); AcessMemAddr_(); break;
		default: 	printf("Syntax error. Grammar Rule: AcessMemAddr. Line : %d\n", yylineno);
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
		default: 		printf("Syntax error. Grammar Rule: AcessMemAddr_. Line : %d\n", yylineno);
	}
}


void Types(){
  printf("Entrei - Types()\n");
	switch (lookahead){
		case TYPE: 		eat(TYPE); eat(ID); eat(ATTRIB); TypeDec(); eat(SEMICOLON); Types(); break;
		case PROCEDURE: break;
		case FUNCTION: 	break;
		case VAR: 		break;
		case _BEGIN: 	break;
		default: 		printf("Syntax error. Grammar Rule: Types. Line : %d\n", yylineno);
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
		default: 		printf("Syntax error. Grammar Rule: TypeDec. Line: %d\n", yylineno);
	}

}

void Interval(){
	switch (lookahead){
		case ID: 		Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case NOT: 		Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case PLUS: 		Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case MINUS: 	Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case LPAR: 		Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case V_INT: 	Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case V_BOOL: 	Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case V_REAL: 	Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case V_CHAR: 	Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		case V_STRING: 	Exp(); eat(INTERVAL); Exp(); Interval_(); break;
		default: 		printf("Syntax error. Grammar Rule: Interval. Line: %d\n", yylineno);
	}

}

void Interval_(){
	switch (lookahead){
		case RBRA: 		break;
		case COMMA: 	eat(COMMA); Interval(); break;
		default: 		printf("Syntax error. Grammar Rule: Interval_. Line: %d\n", yylineno);
	}
}

void Fields(){
	switch (lookahead){
		case ID:  	eat(ID); eat(COLON); TypeDec(); eat(SEMICOLON); Fields(); break;
		case END: 	break;
		default: 	printf("Syntax error. Grammar Rule: Fields. Line: %d\n", yylineno);
	}
}

void SubProg(){
	switch (lookahead){
		case PROCEDURE: 	ProcedureDecl();	SubProg(); 	break;
		case FUNCTION: 		FunctionDecl(); 	SubProg(); 	break;
		case VAR: 			break;
		case _BEGIN: 		break;
		default: 			printf("Syntax error. Grammar Rule: SubProg. Line: %d\n", yylineno);
	}
}

void ProcedureDecl(){
	switch (lookahead){
		case PROCEDURE: 	eat(PROCEDURE); eat(ID); eat(LPAR); Parameters(); eat(RPAR); CmdBlock(); eat(SEMICOLON); break;
		default: 			printf("Syntax error. Grammar Rule: ProcedureDecl. Line : %d\n", yylineno);
	}
}

void FunctionDecl(){
	switch (lookahead){
			//FunctionDecl ::= function Id ( Parameters ) : TypeDec CmdBlock ;
		case FUNCTION: 		eat(FUNCTION); eat(ID); eat(LPAR); Parameters(); eat(RPAR); eat(COLON); TypeDec(); CmdBlock(); eat(SEMICOLON); break;
		default: 			printf("Syntax error. Grammar Rule: FunctionDecl. Line : %d\n", yylineno);
	}
}

void Parameters(){
	switch (lookahead){
		case ID: 		ParametersAux(); break;
		case RPAR: 		break;
		default: 		printf("Syntax error. Grammar Rule: Parameters. Line : %d\n", yylineno);
	}
}

void ParametersAux(){
	switch (lookahead){
			//ParametersAux ::= Id : TypeDec ParametersAux_
		case ID: 		eat(ID); eat(COLON); TypeDec(); ParametersAux_(); break;
		default: 		printf("Syntax error. Grammar rule: ParametersAux. Line : %d\n", yylineno);
	}
}

void ParametersAux_(){
	switch (lookahead){
		case RPAR: 		break;
		case COMMA: 	eat(COMMA); ParametersAux(); break;
		default: 		printf("Syntax error. Grammar rule: ParametersAux_. Line : %d\n", yylineno);
	}
}

void Vars(){
	switch (lookahead){
		case ID: 		break;
		case VAR: 		eat(VAR); eat(ID); eat(COLON); TypeDec(); eat(SEMICOLON); Vars(); break; 
		case _BEGIN: 	break;
		case FOR:		break;
		case LOOP:		break;
		case EXIT:		break;
		case CONTINUE:	break;
		case IF:		break;
		case RETURN:	break;
		default: 		printf("Syntax error. Grammar rule: Vars. Line: %d. Curr token: %d\n", yylineno, lookahead);
	}
}

void CmdBlock(){
  printf("Entrei - CmdBlock()\n");
	switch (lookahead){
		case _BEGIN: 	eat(_BEGIN); Vars(); Cmds(); eat(END); break; 
		default: 		printf("Syntax error. Grammar rule: CmdBlock. Line : %d\n", yylineno);
	}
}

void Cmds(){
	switch (lookahead){
		case ID: 		CmdAux(); Cmds_(); break;
		case _BEGIN: 	CmdAux(); Cmds_(); break;
		case FOR: 		CmdAux(); Cmds_(); break;
		case LOOP: 		CmdAux(); Cmds_(); break;
		case EXIT: 		CmdAux(); Cmds_(); break;
		case CONTINUE: 	CmdAux(); Cmds_(); break;
		case IF: 		CmdAux(); Cmds_(); break;
		case RETURN: 	CmdAux(); Cmds_(); break;
		default: 		printf("Syntax error. Grammar rule: Cmds. Line: %d. Curr token: %d\n", yylineno, lookahead); 
	}
}

void Cmds_(){
	switch (lookahead){
		case SEMICOLON: eat(SEMICOLON); Cmds(); break;
		case END: 		break;
		default: 		printf("Syntax error. Grammar rule: Cmds_. Line : %d\n", yylineno);
	}
}

void CmdAux(){
	switch (lookahead){
		case ID: 		AcessMemAddr(); 	CmdAux_(); 	break;
		case _BEGIN: 	CmdBlock(); 		break;
		case FOR: 		eat(FOR); 			eat(ID); 	eat(ATTRIB); 	Exp(); 		eat(TO); Exp(); eat(STEP); Exp(); CmdBlock(); break;
		case LOOP: 		eat(LOOP); 			Vars(); 	Cmds(); 		eat(END); 	break; 
		case EXIT: 		eat(EXIT); 			eat(WHEN); 	Exp(); 			break; 
		case CONTINUE:	eat(CONTINUE);		break;
		case IF:		CmdConditional();	break;
		case RETURN:	CmdReturn();		break;
		case BREAK: 	eat(BREAK); 		break;
		default: 		printf("Syntax error. Grammar rule: CmdAux. Line : %d\n", yylineno);
	}
}

void CmdAux_(){
	switch (lookahead){
		case ATTRIB: 	eat(ATTRIB); Exp(); break;
		case SEMICOLON:	break;
		case END: 		break;
		default: 		printf("Syntax error. Grammar rule: CmdAux_. Line : %d\n", yylineno);
	}
}

void CmdConditional(){
	switch (lookahead){
		case IF: 	eat(IF); Exp(); eat(THEN); CmdBlock(); CmdConditionalEnd(); break;
		default: 	printf("Syntax error. Grammar rule: CmdConditional\n");
	}
}

void CmdConditionalEnd(){
	switch (lookahead){
		case SEMICOLON: 	break;
		case END: 			break;
		case ELSE: 			eat(ELSE); CmdBlock(); break;
		default: 			printf("Syntax error. Grammar rule: CmdConditionalEnd. Line : %d\n", yylineno);
	}
}

void CmdReturn(){
	switch (lookahead){
		case RETURN: 	eat(RETURN); CmdReturnExp(); break;
		default: 		printf("Syntax error. Grammar rule: CmdReturn. Line : %d\n", yylineno);
	}
}

void CmdReturnExp(){
	switch (lookahead){
		case ID: 		Exp(); break;
		case SEMICOLON:	break;
		case NOT:		Exp(); break;
		case PLUS:		Exp(); break;
		case MINUS:		Exp(); break;
		case LPAR:		Exp(); break;
		case V_INT: 	Exp(); break;
		case V_REAL: 	Exp(); break;
		case V_BOOL: 	Exp(); break;
		case V_CHAR: 	Exp(); break;
		case V_STRING: 	Exp(); break;
		case END:		break;
		default: 		printf("Syntax error. Grammar rule: CmdReturnExp. Line : %d\n", yylineno);
	}
}

void Args(){
	printf("entrei no args\n");
	switch (lookahead){
		case ID: 		ArgsAux(); break;
		case NOT: 		ArgsAux(); break;
		case PLUS: 		ArgsAux(); break;
		case MINUS: 	ArgsAux(); break;
		case LPAR: 		ArgsAux(); break;
		case V_INT: 	ArgsAux(); break;
		case V_REAL: 	ArgsAux(); break;
		case V_BOOL: 	ArgsAux(); break;
		case V_CHAR: 	ArgsAux(); break;
		case V_STRING: 	ArgsAux(); break;	
		case RPAR: 		break;
		default: 		printf("Syntax error. Grammar rule: Args. Line : %d\n", yylineno);
	}
}

void ArgsAux(){
	switch (lookahead){
		case ID:  		Exp(); 			ArgsAux_();     break;
		case NOT:  		Exp(); 			ArgsAux_();     break;
		case PLUS:  	Exp(); 			ArgsAux_();     break;
		case MINUS:  	Exp(); 			ArgsAux_();     break;
		case LPAR:  	Exp(); 			ArgsAux_();     break;
		case V_INT: 	Exp(); 			ArgsAux_(); 	break;
		case V_REAL: 	Exp(); 			ArgsAux_(); 	break;
		case V_BOOL: 	Exp(); 			ArgsAux_(); 	break;
		case V_CHAR: 	Exp(); 			ArgsAux_(); 	break;
		case V_STRING: 	Exp(); 			ArgsAux_(); 	break;
		default: 		printf("Syntax error. Grammar rule: ArgsAux.  Line : %d\n", yylineno);
	}
}

void ArgsAux_(){
	switch (lookahead){
		case RPAR: 		break;
		case COMMA: 	eat(COMMA); ArgsAux(); break;
		default: 		printf("Syntax error. Grammar rule: ArgsAux_.  Line : %d\n", yylineno);
	}
}

int main()
{
	initializeSymbolTable();
  lookahead = yylex();

  if (lookahead != 0) {
      printf("Parsing initialized.\n");
      Prog();    
  }

  

  printf("\n\nFinishing...\n");
  yylex_destroy();
  
  return 0;
}

