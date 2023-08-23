%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "defines.h"
  #include "symbolTable.h"

%}

low             [a-z]
upp             [A-Z]
number          [0-9]
letter          [a-z|A-Z|\_]*
delim           [ \t\n]
ws              {delim}+
identificador 	{letter}({letter}|{number})*

%%

{ws}          {/* No action and no returne*/}
"bool"        {return T_BOOL;}
"int"         {return T_INT;}
"real"        {return T_REAL;}
"char"        {return T_CHAR;}

"true" | "false"	{return V_BOOL;}
">"         {return '>';}
"<"         {return '<';}
">="        {return GEQ;}
"<="        {return LEQ;}
"=="        {return EQ;}
"!="        {return NEQ;}

"+"         {return '+';}
"-"         {return '-';}
"*"         {return '*';}
"/"         {return '/';}
"%"         {return '%';}

"!"         {return '!';}
"&&"        {return AND;}
"||"        {return OR;}


"("         {return '(';}
")"         {return ')';}
"["         {return '[';}
"]"         {return ']';}

"const"     {return CONST;}
"if"        {return IF;}
"else"      {return ELSE;}
"elsif"     {return ELSIF;}
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

"/."        {return '.';}
","         {return ',';}
":"         {return ':';}
";"         {return ';';}
"{"         {return '{';}
"}"         {return '}';}

"type"      {return TYPE;}
"array"     {return ARRAY;}
"exit"      {return EXIT;}
"when"      {return WHEN;}
"to"        {return TO;}
"step"      {return STEP;}
"then"      {return THEN;}

":="        {return ATTRIB;}

{number}+(\.{number}+)?(E[+-]?{number}+)?

{identificador}                             {addSymbol(yytext, ID); return ID;}
[+-]?{number}+(E[+-]?{number}+)?            {return V_INT;}
[+-]?{number}+\.{number}+(E[+-]?{number}+)? {return V_REAL;}
\'.\'                                       {return V_CHAR;}


%%


int main()
{
  printf("\nInicializando tabela de simbolos...\n");
  initializeSymbolTable();
  printf("Iniciando leitura de tokens...\n\n");
  int token = -1;
  while (token != 0) {
      token = yylex();
      printf("token lido: %d\n", token);
  }
  printf("\nLeitura de tokens finalizada.\n");
  printFirst10Entries();
  
  return 0;
}
