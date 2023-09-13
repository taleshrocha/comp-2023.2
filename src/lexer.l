%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "defines.h"
  #include "typedefs.h"
  #include "symbolTable.h"
  #include "tableParser.h"
%}

%option noyywrap

low             [a-z]
upp             [A-Z]
number          [0-9]
letter          [a-zA-Z\_]
delim           [ \t\n]
ws              {delim}+
identificador   {letter}({letter}|{number})*

%%

"{"([^}]|\n)*"}"   {/* Ignorar tudo entre "{" e "}" */}
"--".*		  {/* Ignorar tudo após "--" até o final da linha */}

{ws}          {/* No action and no returne*/}
"bool"        {return T_BOOL;}
"int"         {return T_INT;}
"real"        {return T_REAL;}
"char"        {return T_CHAR;}

">"         {return GREATER;}
"<"         {return LESS;}
">="        {return GEQ;}
"<="        {return LEQ;}
"=="        {return EQ;}
"!="        {return NEQ;}

"+"         {return PLUS;}
"-"         {return MINUS;}
"*"         {return MULTIPLY;}
"/"         {return DIVIDE;}
"%"         {return MOD;}

"!"         {return NOT;}
"&&"        {return AND;}
"||"        {return OR;}


"("         {return LPAR;}
")"         {return RPAR;}
"["         {return LBRA;}
"]"         {return RBRA;}

"const"     {return CONST;}
"var"	      {return VAR;}
"if"        {return IF;}
"else"      {return ELSE;}
"loop"      {return LOOP;}
"begin"     {return _BEGIN;}
"end"       {return END;}

"function"  {return FUNCTION;}
"procedure" {return PROCEDURE;}

"return"    {return RETURN;}
"break"     {return BREAK;}
"continue"  {return CONTINUE;}
"record"    {return RECORD;}
"of"        {return OF;}

"\."        {return DOT;}
","         {return COMMA;}
":"         {return COLON;}
";"         {return SEMICOLON;}

"type"      {return TYPE;}
"array"     {return ARRAY;}
"exit"      {return EXIT;}
"when"      {return WHEN;}
"to"        {return TO;}
"step"      {return STEP;}
"then"      {return THEN;}

":="        {return ATTRIB;}

"true"|"false"	                          {
                                              yylval.bool_value = yytext[0] == 't' ? true : false;
                                              return V_BOOL;
                                            }


[+-]?{number}+(E[+-]?{number}+)?            {
                                              yylval.int_value = atoi(yytext);
                                              return V_INT;
                                            }

[+-]?{number}+\.{number}+(E[+-]?{number}+)? {
                                              yylval.real_value = strtof(yytext, NULL);
                                              return V_REAL;
                                            }

\'.\'                                       {
                                              //printf("minha string legal: %s\n", yytext);
                                              yylval.char_value = yytext[1];
                                              return V_CHAR;
                                            }
\".*\"                                      {
                                              yylval.string_value = strdup(yytext+1);
                                              yylval.string_value[yyleng-2] = '\0';
                                              printf("yyleng: %d\n", yyleng);
                                              return V_STRING; // ?? como indicar uma string?
                                            }

{identificador}                             {
                                              yylval.id_index = addSymbol(yytext);
                                              return ID;
                                            }

.        {printf("ERROR! %s \n", yytext);}

%%


char terminal_mapping[56][16] = {
    "CONST",    "ID",       "ATTRIB",   "SEMICOLON", "OR",        "AND",
    "NEQ",      "EQ",       "LESS",     "GREATER",   "LEQ",       "GEQ",
    "NOT",      "PLUS",     "MINUS",    "MULTIPLY",  "DIVIDE",    "MOD",
    "LPAR",     "RPAR",     "V_INT",    "V_REAL",    "V_BOOL",    "V_CHAR",
    "V_STRING", "DOT",      "LBRA",     "RBRA",      "TYPE",      "T_BOOL",
    "T_INT",    "T_REAL",   "T_CHAR",   "ARRAY",     "OF",        "RECORD",
    "END",      "INTERVAL", "COMMA",    "COLON",     "PROCEDURE", "FUNCTION",
    "VAR",      "_BEGIN",   "FOR",      "TO",        "STEP",      "LOOP",
    "EXIT",     "WHEN",     "CONTINUE", "BREAK",     "IF",        "THEN",
    "ELSE",     "RETURN"};

char non_terminal_mapping[44][32] = {"Prog",
                                     "Decl",
                                     "Consts",
                                     "Exp",
                                     "Exp_",
                                     "Terms",
                                     "Terms_",
                                     "Comps",
                                     "Comps_",
                                     "Factor",
                                     "AriOp",
                                     "AriOp_",
                                     "AriOp2",
                                     "AriOp2_",
                                     "Parenthesis",
                                     "UnaryExp",
                                     "SimpleExp",
                                     "NumExp",
                                     "AcessMemAddr",
                                     "AcessMemAddr_",
                                     "Types",
                                     "TypeDec",
                                     "Interval",
                                     "Interval_",
                                     "Fields",
                                     "SubProg",
                                     "ProcedureDecl",
                                     "FunctionDecl",
                                     "Parameters",
                                     "ParametersAux",
                                     "ParametersAux_",
                                     "Vars",
                                     "CmdBlock",
                                     "Cmds",
                                     "Cmds_",
                                     "CmdAux",
                                     "CmdAux_",
                                     "CmdConditional",
                                     "CmdConditionalEnd",
                                     "CmdReturn",
                                     "CmdReturnExp",
                                     "Args",
                                     "ArgsAux",
                                     "ArgsAux_"};

int main() {
  initializeSymbolTable();
  printf("starting!...\n");
  initialize_stack();
  int current_terminal = yylex(); 
  int current_symbol = pop();
  while (current_symbol != EndOfInput) {
    if (current_symbol == current_terminal) {
      current_terminal = yylex(); 
    //   current_symbol = pop();
    } else if (current_symbol < 100) {
        // printf("symbol: %d-%s is terminal\n", current_symbol, terminal_mapping[current_symbol-1]);
        error();
        destroySymbolTable();
        yylex_destroy();
        return -1;
    } else if (get_symbols(current_symbol-100, current_terminal-1)[0] == 0) {
        // printf("symbol: %d-%s is not terminal\n", current_symbol, non_terminal_mapping[current_symbol-100]);
        // printf("current token is %d-%s\n", current_terminal, terminal_mapping[current_terminal-1]);
        // printf("Invalid terminal!\n");
        error();
        destroySymbolTable();
        yylex_destroy();
        return -1;
    } else {
        // printf("symbol: %d-%s is not terminal\n", current_symbol, non_terminal_mapping[current_symbol-100]);
        // printf("current token is %d-%s\n", current_terminal, terminal_mapping[current_terminal-1]);
        insert_symbols(get_symbols(current_symbol-100, current_terminal-1));
    }
    current_symbol = pop();
  }
  printf("end of input! Finalizing!\n");
  destroySymbolTable();
  yylex_destroy();
  
  return 0;
}
