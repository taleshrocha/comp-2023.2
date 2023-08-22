%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "defines.h"
  #include "symbol_table.c"

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
"bool"        {addSymbol(yytext, T_BOOL); return T_BOOL;}
"int"         {addSymbol(yytext, T_INT); return T_INT;}
"real"        {addSymbol(yytext, T_REAL); return T_REAL;}
"char"        {addSymbol(yytext, T_CHAR); return T_CHAR;}

"true" | "false"	{addSymbol(yytext, V_BOOL); return V_BOOL;}
">"         {addSymbol(yytext, (int) '>'); return '>';}
"<"         {addSymbol(yytext, (int) '<'); return '<';}
">="        {addSymbol(yytext, GEQ); return GEQ;}
"<="        {addSymbol(yytext, LEQ); return LEQ;}
"=="        {addSymbol(yytext, EQ); return EQ;}
"!="        {addSymbol(yytext, NEQ); return NEQ;}

"+"         {addSymbol(yytext, (int) '+'); return '+';}
"-"         {addSymbol(yytext, (int) '-'); return '-';}
"*"         {addSymbol(yytext, (int) '*'); return '*';}
"/"         {addSymbol(yytext, (int) '/'); return '/';}
"%"         {addSymbol(yytext, (int) '%'); return '%';}

"!"         {addSymbol(yytext, (int) '!'); return '!';}
"&&"        {addSymbol(yytext, AND); return AND;}
"||"        {addSymbol(yytext, OR); return OR;}


"("         {addSymbol(yytext, (int) '('); return '(';}
")"         {addSymbol(yytext, (int) ')'); return ')';}
"["         {addSymbol(yytext, (int) '['); return '[';}
"]"         {addSymbol(yytext, (int) ']'); return ']';}

"const"     {addSymbol(yytext, CONST); return CONST;}
"if"        {addSymbol(yytext, IF); return IF;}
"else"      {addSymbol(yytext, ELSE); return ELSE;}
"elsif"     {addSymbol(yytext, ELSIF); return ELSIF;}
"loop"      {addSymbol(yytext, LOOP); return LOOP;}
"begin"     {addSymbol(yytext, _BEGIN); return _BEGIN;}
"end"       {addSymbol(yytext, END); return END;}

"function"  {addSymbol(yytext, FUNCTION); return FUNCTION;}
"procedure" {addSymbol(yytext, PROCEDURE); return PROCEDURE;}

"return"    {addSymbol(yytext, RETURN); return RETURN;}
"break"     {addSymbol(yytext, BREAK); return BREAK;}
"continue"  {addSymbol(yytext, CONTINUE); return CONTINUE;}
"record"    {addSymbol(yytext, RECORD); return RECORD;}
"of"        {addSymbol(yytext, OF); return OF;}

"/."        {addSymbol(yytext, (int) '.'); return '.';}
","         {addSymbol(yytext, (int) ','); return ',';}
":"         {addSymbol(yytext, (int) ':'); return ':';}
";"         {addSymbol(yytext, (int) ';'); return ';';}
"{"         {addSymbol(yytext, (int) '{'); return '{';}
"}"         {addSymbol(yytext, (int) '}'); return '}';}

"type"      {addSymbol(yytext, TYPE); return TYPE;}
"array"     {addSymbol(yytext, ARRAY); return ARRAY;}
"exit"      {addSymbol(yytext, EXIT); return EXIT;}
"when"      {addSymbol(yytext, WHEN); return WHEN;}
"to"        {addSymbol(yytext, TO); return TO;}
"step"      {addSymbol(yytext, STEP); return STEP;}
"then"      {addSymbol(yytext, THEN); return THEN;}

":="        {addSymbol(yytext, ATTRIB); return ATTRIB;}

{number}+(\.{number}+)?(E[+-]?{number}+)?

{identificador}                             {addSymbol(yytext, ID); return ID;}
[+-]?{number}+(E[+-]?{number}+)?            {addSymbol(yytext, V_INT); return V_INT;}
[+-]?{number}+\.{number}+(E[+-]?{number}+)? {addSymbol(yytext, V_REAL); return V_REAL;}
\'.\'                                       {addSymbol(yytext, V_CHAR); return V_CHAR;}


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
