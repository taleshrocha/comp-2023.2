#ifndef RECURSIVEPARSER_H
#define RECURSIVEPARSER_H

//Função para comunicação com o Lexer.
int getNextToken();

extern int lookahead;

// Funções para análise sintática
void Prog();
void Decl();
void Consts();
void Exp();
void Exp_();
void Terms();
void Terms_();
void Comps();
void Comps_();
void Factor();
void AriOp();
void AriOp_();
void AriOp2();
void AriOp2_();
void Parenthesis();
void UnaryExp();
void SimpleExp();
void NumExp();
void AcessMemAddr();
void AcessMemAddr_();
void Types();
void TypeDec();
void Interval();
void Interval_();
void Fields();
void SubProg();
void ProcedureDecl();
void FunctionDecl();
void Parameters();
void ParametersAux();
void ParametersAux_();
void Vars();
void CmdBlock();
void Cmds();
void Cmds_();
void CmdAux();
void CmdAux_();
void CmdConditional();
void CmdConditionalEnd();
void CmdReturn();
void CmdReturnExp();
void Args();
void ArgsAux();
void ArgsAux_();

#endif