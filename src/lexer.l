%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "parser.y.h"
  #include "symbolTable.h"
  int column_counter;
%}

%option noinput nounput
%option noyywrap
%option yylineno

number          [0-9]
letter          [a-zA-Z\_]
delim           [ \t]
ws              {delim}+
newline         [\n]+
identificador   {letter}({letter}|{number})*

%%

"{"([^}]|\n)*"}"   {/* Ignorar tudo entre "{" e "}" */}
"--".*		  {/* Ignorar tudo após "--" até o final da linha */}

{ws}          {column_counter += strlen(yytext);}
{newline}     {column_counter = 0;} 
"bool"        {column_counter += strlen(yytext); return T_BOOL;}
"int"         {column_counter += strlen(yytext); return T_INT;}
"real"        {column_counter += strlen(yytext); return T_REAL;}
"char"        {column_counter += strlen(yytext); return T_CHAR;}

":="        {column_counter += strlen(yytext); return ATTRIB;}

">"         {column_counter += strlen(yytext); return GREATER;}
"<"         {column_counter += strlen(yytext); return LESS;}
">="        {column_counter += strlen(yytext); return GEQ;}
"<="        {column_counter += strlen(yytext); return LEQ;}
"=="        {column_counter += strlen(yytext); return EQ;}
"!="        {column_counter += strlen(yytext); return NEQ;}

"+"         {column_counter += strlen(yytext); return PLUS;}
"-"         {column_counter += strlen(yytext); return MINUS;}
"*"         {column_counter += strlen(yytext); return MULTIPLY;}
"/"         {column_counter += strlen(yytext); return DIVIDE;}
"%"         {column_counter += strlen(yytext); return MOD;}

"!"         {column_counter += strlen(yytext); return NOT;}
"&&"        {column_counter += strlen(yytext); return AND;}
"||"        {column_counter += strlen(yytext); return OR;}


"("         {column_counter += strlen(yytext); return LPAR;}
")"         {column_counter += strlen(yytext); return RPAR;}
"["         {column_counter += strlen(yytext); return LBRA;}
"]"         {column_counter += strlen(yytext); return RBRA;}

"\.\."      {column_counter += strlen(yytext); return INTERVAL;}
"\."        {column_counter += strlen(yytext); return DOT;}
","         {column_counter += strlen(yytext); return COMMA;}
":"         {column_counter += strlen(yytext); return COLON;}
";"         {column_counter += strlen(yytext); return SEMICOLON;}

"const"     {column_counter += strlen(yytext); return CONST;}
"var"	      {column_counter += strlen(yytext); return VAR;}
"ref"	      {column_counter += strlen(yytext); return REF;}
"if"        {column_counter += strlen(yytext); return IF;}
"else"      {column_counter += strlen(yytext); return ELSE;}
"loop"      {column_counter += strlen(yytext); return LOOP;}
"for"       {column_counter += strlen(yytext); return FOR;}
"begin"     {column_counter += strlen(yytext); return BEGIN_;}
"end"       {column_counter += strlen(yytext); return END;}

"function"  {column_counter += strlen(yytext); return FUNCTION;}
"procedure" {column_counter += strlen(yytext); return PROCEDURE;}

"return"    {column_counter += strlen(yytext); return RETURN;}
"break"     {column_counter += strlen(yytext); return BREAK;}
"continue"  {column_counter += strlen(yytext); return CONTINUE;}
"record"    {column_counter += strlen(yytext); return RECORD;}
"array"     {column_counter += strlen(yytext); return ARRAY;}
"of"        {column_counter += strlen(yytext); return OF;}

"type"      {column_counter += strlen(yytext); return TYPE;}
"exit"      {column_counter += strlen(yytext); return EXIT;}
"when"      {column_counter += strlen(yytext); return WHEN;}
"to"        {column_counter += strlen(yytext); return TO;}
"step"      {column_counter += strlen(yytext); return STEP;}
"then"      {column_counter += strlen(yytext); return THEN;}

"true"|"false"	                          {
                                              // // yylval.bool_value = yytext[0] == 't' ? true : false;
                                              column_counter += strlen(yytext);
                                              return V_BOOL;
                                          }


{number}+(E[+-]?{number}+)?            {
                                              // yylval.int_value = atoi(yytext);
                                              column_counter += strlen(yytext);
                                              return V_INT;
                                            }

{number}+\.{number}+(E[+-]?{number}+)? {
                                              // yylval.real_value = strtof(yytext, NULL);
                                              column_counter += strlen(yytext);
                                              return V_REAL;
                                            }

\'.\'                                       {
                                              //printf("minha string legal: %s\n", yytext);
                                              // yylval.char_value = yytext[1];
                                              column_counter += strlen(yytext);
                                              return V_CHAR;
                                            }
\".*\"                                      {
                                              // yylval.string_value = strdup(yytext+1);
                                              // yylval.string_value[yyleng-2] = '\0';
                                              column_counter += strlen(yytext);
                                              return V_STRING; // ?? como indicar uma string?
                                            }

{identificador}                             {
                                            //  // yylval.id_index = addSymbol(yytext);
                                              column_counter += strlen(yytext);
                                              return ID;
                                            }

.                                           {
                                              column_counter += strlen(yytext);
                                              printf("ERROR! %s \n", yytext);
                                            }

%%


char terminal_mapping[56][16] = {
    "CONST",    "ID",       "ATTRIB",   "SEMICOLON", "OR",        "AND",
    "NEQ",      "EQ",       "LESS",     "GREATER",   "LEQ",       "GEQ",
    "NOT",      "PLUS",     "MINUS",    "MULTIPLY",  "DIVIDE",    "MOD",
    "LPAR",     "RPAR",     "V_INT",    "V_REAL",    "V_BOOL",    "V_CHAR",
    "V_STRING", "DOT",      "LBRA",     "RBRA",      "TYPE",      "T_BOOL",
    "T_INT",    "T_REAL",   "T_CHAR",   "ARRAY",     "OF",        "RECORD",
    "END",      "INTERVAL", "COMMA",    "COLON",     "PROCEDURE", "FUNCTION",
    "VAR",      "BEGIN_",   "FOR",      "TO",        "STEP",      "LOOP",
    "EXIT",     "WHEN",     "CONTINUE", "BREAK",     "IF",        "THEN",
    "ELSE",     "RETURN", "REF"};

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
