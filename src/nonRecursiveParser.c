#include "nonRecursiveParser.h"
#include "symbolTable.h"
#include "lexer.h"

int capacity = 1000;
int curr_size = 0;

int matrix[45][56][10] = {
    /*00 Prog*/              {{Decl, CmdBlock,-1,-1,-1,-1,-1,-1,-1,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {Decl, CmdBlock,-1,-1,-1,-1,-1,-1,-1,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {Decl, CmdBlock,-1,-1,-1,-1,-1,-1,-1,-1}, {Decl, CmdBlock,-1,-1,-1,-1,-1,-1,-1,-1}, {Decl, CmdBlock,-1,-1,-1,-1,-1,-1,-1,-1}, {Decl, CmdBlock,-1,-1,-1,-1,-1,-1,-1,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*01 Decl*/              {{Consts, Types, SubProg, Vars,-1,-1,-1,-1,-1,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {Consts, Types, SubProg, Vars,-1,-1,-1,-1,-1,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {Consts, Types, SubProg, Vars,-1,-1,-1,-1,-1,-1}, {Consts, Types, SubProg, Vars,-1,-1,-1,-1,-1,-1}, {Consts, Types, SubProg, Vars,-1,-1,-1,-1,-1,-1}, {Consts, Types, SubProg, Vars,-1,-1,-1,-1,-1,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*02 Consts*/            {{CONST, ID, ATTRIB, Exp, SEMICOLON, Consts,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {-1}, {-1}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*03 Exp*/               {{0}, {Terms, Exp_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {Terms, Exp_,-1}, {Terms, Exp_,-1}, {Terms, Exp_,-1}, {0}, {0}, {0}, {Terms, Exp_,-1}, {0}, {Terms, Exp_,-1}, {Terms, Exp_,-1}, {Terms, Exp_,-1}, {Terms, Exp_,-1}, {Terms, Exp_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*04 Exp_*/              {{0}, {0}, {0}, {-1}, {OR, Terms, Exp_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {-1}, {-1}, {0}, {0}, {0}, {0}, {-1}, {0}, {-1}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}},
    /*05 Terms*/             {{0}, {Comps, Terms_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {Comps, Terms_,-1}, {Comps, Terms_,-1}, {Comps, Terms_,-1}, {0}, {0}, {0}, {Comps, Terms_,-1}, {0}, {Comps, Terms_,-1}, {Comps, Terms_,-1}, {Comps, Terms_,-1}, {Comps, Terms_,-1}, {Comps, Terms_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*06 Terms_*/            {{0}, {0}, {0}, {-1}, {-1}, {AND, Comps, Terms_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {-1}, {-1}, {0}, {0}, {0}, {0}, {-1}, {0}, {-1}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}},
    /*07 Comps*/             {{0}, {Factor, Comps_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {Factor, Comps_,-1}, {Factor, Comps_,-1}, {Factor, Comps_,-1}, {0}, {0}, {0}, {Factor, Comps_,-1}, {0}, {Factor, Comps_,-1}, {Factor, Comps_,-1}, {Factor, Comps_,-1}, {Factor, Comps_,-1}, {Factor, Comps_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*08 Comps_*/            {{0}, {0}, {0}, {-1}, {-1}, {-1}, {NEQ, Factor,-1}, {EQ, Factor,-1}, {LESS, Factor,-1}, {GREATER, Factor,-1}, {LEQ, Factor,-1}, {GEQ, Factor,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {-1}, {-1}, {0}, {0}, {0}, {0}, {-1}, {0}, {-1}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}},
    /*09 Factor*/            {{0}, {AriOp,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {! AriOp,-1}, {AriOp,-1}, {AriOp,-1}, {0}, {0}, {0}, {AriOp,-1}, {0}, {AriOp,-1}, {AriOp,-1}, {AriOp,-1}, {AriOp,-1}, {AriOp,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*10 AriOp*/             {{0}, {AriOp2, AriOp_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {AriOp2, AriOp_,-1}, {AriOp2, AriOp_,-1}, {0}, {0}, {0}, {AriOp2, AriOp_,-1}, {0}, {AriOp2, AriOp_,-1}, {AriOp2, AriOp_,-1}, {AriOp2, AriOp_,-1}, {AriOp2, AriOp_,-1}, {AriOp2, AriOp_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*11 AriOp_*/            {{0}, {0}, {0}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {0}, {+ AriOp2, AriOp_,-1}, {- AriOp2, AriOp_,-1}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {-1}, {-1}, {0}, {0}, {0}, {0}, {-1}, {0}, {-1}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}},
    /*12 AriOp2*/            {{0}, {Parenthesis, AriOp2_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {Parenthesis, AriOp2_,-1}, {Parenthesis, AriOp2_,-1}, {0}, {0}, {0}, {Parenthesis, AriOp2_,-1}, {0}, {Parenthesis, AriOp2_,-1}, {Parenthesis, AriOp2_,-1}, {Parenthesis, AriOp2_,-1}, {Parenthesis, AriOp2_,-1}, {Parenthesis, AriOp2_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*13 AriOp2_*/           {{0}, {0}, {0}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {0}, {-1}, {-1}, {MULTIPLY, Parenthesis, AriOp2_,-1}, {DIVIDE, Parenthesis, AriOp2_,-1}, {MOD, Parenthesis, AriOp2_,-1}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {-1}, {-1}, {0}, {0}, {0}, {0}, {-1}, {0}, {-1}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}},
    /*14 Parenthesis*/       {{0}, {UnaryExp,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {UnaryExp,-1}, {UnaryExp,-1}, {0}, {0}, {0}, {LPAR, Exp, RPAR,-1}, {0}, {UnaryExp,-1}, {UnaryExp,-1}, {UnaryExp,-1}, {UnaryExp,-1}, {UnaryExp,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*15 UnaryExp*/          {{0}, {SimpleExp,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {PLUS, UnaryExp,-1}, {MINUS, UnaryExp,-1}, {0}, {0}, {0}, {0}, {0}, {SimpleExp,-1}, {SimpleExp,-1}, {SimpleExp,-1}, {SimpleExp,-1}, {SimpleExp,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*16 SimpleExp*/         {{0}, {AcessMemAddr,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {NumExp,-1}, {NumExp,-1}, {NumExp,-1}, {NumExp,-1}, {NumExp,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*17 NumExp*/            {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {V_INT,-1}, {V_REAL,-1}, {V_BOOL,-1}, {V_CHAR,-1}, {V_STRING,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*18 AcessMemAddr*/      {{0}, {ID, AcessMemAddr_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*19 AcessMemAddr_*/     {{0}, {0}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {0}, {-1}, {-1}, {-1}, {-1}, {-1}, {LPAR, Args, RPAR, AcessMemAddr_,-1}, {-1}, {0}, {0}, {0}, {0}, {0}, {DOT, ID, AcessMemAddr_,-1}, {LBRA, Exp, RBRA, AcessMemAddr_,-1}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {-1}, {-1}, {0}, {0}, {0}, {0}, {-1}, {0}, {-1}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}},
    /*20 Types*/             {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {TYPE, ID, ATTRIB, TypeDec, SEMICOLON, Types,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {-1}, {-1}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*21 TypeDec*/           {{0}, {ID,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {T_BOOL,-1}, {T_INT,-1}, {T_REAL,-1}, {T_CHAR,-1}, {ARRAY, LBRA, Interval, RBRA, OF, TypeDec,-1}, {0}, {RECORD, Fields, END,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*22 Interval*/          {{0}, {Exp, INTERVAL, Exp, Interval_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {Exp, INTERVAL, Exp, Interval_,-1}, {Exp, INTERVAL, Exp, Interval_,-1}, {Exp, INTERVAL, Exp, Interval_,-1}, {0}, {0}, {0}, {Exp, INTERVAL, Exp, Interval_,-1}, {0}, {Exp, INTERVAL, Exp, Interval_,-1}, {Exp, INTERVAL, Exp, Interval_,-1}, {Exp, INTERVAL, Exp, Interval_,-1}, {Exp, INTERVAL, Exp, Interval_,-1}, {Exp, INTERVAL, Exp, Interval_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*23 Interval_*/         {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {COMMA, Interval,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*24 Fields*/            {{0}, {ID, COLON, TypeDec, SEMICOLON, Fields,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*25 SubProg*/           {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {ProcedureDecl, SubProg,-1}, {FunctionDecl, SubProg,-1}, {-1}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*26 ProcedureDecl*/     {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {PROCEDURE, ID, LPAR, Parameters, RPAR, CmdBlock, SEMICOLON,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*27 FunctionDecl*/      {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {FUNCTION, ID, LPAR, Parameters, RPAR, COLON, TypeDec, CmdBlock, SEMICOLON,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*28 Parameters*/        {{0}, {ParametersAux,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*29 ParametersAux*/     {{0}, {ID, COLON, TypeDec, ParametersAux_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*30 ParametersAux_*/    {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {COMMA, ParametersAux,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*31 Vars*/              {{0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {VAR, ID, COLON, TypeDec, SEMICOLON, Vars,-1}, {-1}, {-1}, {0}, {0}, {-1}, {-1}, {0}, {-1}, {-1}, {-1}, {0}, {0}, {-1}},
    /*32 CmdBlock*/          {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {_BEGIN, Vars, Cmds, END,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*33 Cmds*/              {{0}, {CmdAux, Cmds_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {CmdAux, Cmds_,-1}, {CmdAux, Cmds_,-1}, {0}, {0}, {CmdAux, Cmds_,-1}, {CmdAux, Cmds_,-1}, {0}, {CmdAux, Cmds_,-1}, {CmdAux, Cmds_,-1}, {CmdAux, Cmds_,-1}, {0}, {0}, {CmdAux, Cmds_, -1}},
    /*34 Cmds_*/             {{0}, {0}, {0}, {SEMICOLON, Cmds,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*35 CmdAux*/            {{0}, {AcessMemAddr, CmdAux_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {CmdBlock,-1}, {FOR, ID, ATTRIB, Exp, TO, Exp, STEP, Exp, CmdBlock,-1}, {0}, {0}, {LOOP, Vars, Cmds, END,-1}, {EXIT, WHEN, Exp,-1}, {0}, {CONTINUE,-1}, {BREAK,-1}, {CmdConditional,-1}, {0}, {0}, {CmdReturn, -1}},
    /*36 CmdAux_*/           {{0}, {0}, {ATTRIB, Exp,-1}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*37 CmdConditional*/    {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {IF, Exp, THEN, CmdBlock, CmdConditionalEnd,-1}, {0}, {0}, {0}},
    /*38 CmdConditionalEnd*/ {{0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {ELSE, CmdBlock,-1}, {0}},
    /*39 CmdReturn*/         {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {RETURN, CmdReturnExp, -1}},
    /*40 CmdReturnExp*/      {{0}, {Exp,-1}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {Exp,-1}, {Exp,-1}, {Exp,-1}, {0}, {0}, {0}, {Exp,-1}, {0}, {Exp,-1}, {Exp,-1}, {Exp,-1}, {Exp,-1}, {Exp,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*41 Args*/              {{0}, {ArgsAux,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {ArgsAux,-1}, {ArgsAux,-1}, {ArgsAux,-1}, {0}, {0}, {0}, {ArgsAux,-1}, {-1}, {ArgsAux,-1}, {ArgsAux,-1}, {ArgsAux,-1}, {ArgsAux,-1}, {ArgsAux,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*42 ArgsAux*/           {{0}, {Exp, ArgsAux_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {Exp, ArgsAux_,-1}, {Exp, ArgsAux_,-1}, {Exp, ArgsAux_,-1}, {0}, {0}, {0}, {Exp, ArgsAux_,-1}, {0}, {Exp, ArgsAux_,-1}, {Exp, ArgsAux_,-1}, {Exp, ArgsAux_,-1}, {Exp, ArgsAux_,-1}, {Exp, ArgsAux_,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
    /*43 ArgsAux_*/          {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {COMMA, ArgsAux,-1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}},
};

int *stack;

void initialize_stack() {
  stack = (int*)malloc(sizeof(int) * capacity);
  push(EndOfInput);
  push(Prog);
}

void print_stack() {
  for(int i = 0; i < curr_size; i++) {
      char* s;
      if (stack[i] == 0) {
        s = "EndOfInput";
      } else if (stack[i] < 100) {
          s = terminal_mapping[stack[i]-1];
      } else {
          s = non_terminal_mapping[stack[i]-100];
      }
      printf("%d-%s ", stack[i], s);
  }
  printf("\n");
}

int pop() { return stack[--curr_size]; }

int peek() { return stack[curr_size-1]; }

void push(int value) {
  if (curr_size == capacity) {
    capacity = capacity * 2;
    int* new_stack = (int*)malloc(sizeof(int) * capacity);
    memcpy(new_stack, stack, sizeof(int) * curr_size);
    free(stack);
    stack = new_stack;
  }
  stack[curr_size++] = value;
}

int* get_symbols(int nt, int t) { 
  // printf("nt: %d, t: %d\n", nt, t);
  // printf("values\n");
  // for (size_t i = 0; i < 10; i++)
  // {
  //   printf("%d ", matrix[nt][t][i]);
  // }
  // printf("\n");
  return matrix[nt][t]; }

void insert_symbols(int* symbols) {
  int i = 0;
  while (i < 10 && symbols[i] != -1) {
    ++i;
  }
  --i;
  while (i > -1) {
    // printf("symbol: %d inserted \n", symbols[i]);
    push(symbols[i]);
    --i;
  }
}

void error() {
  printf("line %d -- column %d \n", yylineno, column_counter);
  printf("Erro!\n");  //TODO: Implementar
}

int main() {
  initializeSymbolTable();
  printf("starting!...\n");
  initialize_stack();
  int current_terminal = yylex(); 
  // int current_symbol = pop();
  while (peek() != EndOfInput) {
    printf("%d-%s ::: ", current_terminal, terminal_mapping[current_terminal-1]);
    print_stack();
    // print_stack();
    // printf("symbol: %d-%s is not terminal\n", peek(), non_terminal_mapping[peek()-100]);
    // printf("current token is %d-%s\n", current_terminal, terminal_mapping[current_terminal-1]);
    if (peek() == current_terminal) {
      current_terminal = yylex(); 
      pop();
    } else if (peek() < 100) {
        printf("symbol: %d-%s is terminal\n", peek(), terminal_mapping[peek()-1]);
        error();
        destroySymbolTable();
        yylex_destroy();
        return -1;
    } else if (get_symbols(peek()-100, current_terminal-1)[0] == 0) {
        printf("symbol: %d-%s is not terminal\n", peek(), non_terminal_mapping[peek()-100]);
        printf("current token is %d-%s\n", current_terminal, terminal_mapping[current_terminal-1]);
        printf("Invalid terminal!\n");
        error();
        destroySymbolTable();
        yylex_destroy();
        return -1;
    } else {
        // printf("symbol: %d-%s is not terminal\n", peek(), non_terminal_mapping[peek()-100]);
        // printf("current token is %d-%s\n", current_terminal, terminal_mapping[current_terminal-1]);
        int v = peek();
        pop();
        insert_symbols(get_symbols(v-100, current_terminal-1));
    }
  }
  if (current_terminal != EndOfInput) {
    printf("current token is %d-%s\n", current_terminal, terminal_mapping[current_terminal-1]);
    printf("error\n");
  }
  printf("end of input! Finalizing!\n");
  destroySymbolTable();
  yylex_destroy();
  
  return 0;
}
