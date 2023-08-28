%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "defines.h"
  #include "typedefs.h"
  #include "symbolTable.h"

%}

%option noyywrap

low             [a-z]
upp             [A-Z]
number          [0-9]
letter          [a-z|A-Z|\_]*
delim           [ \t\n]
ws              {delim}+
identificador 	{letter}({letter}|{number})*

%%

"{"([^}]|\n)*"}"   {/* Ignorar tudo entre "{" e "}" */}
"--".*		  {/* Ignorar tudo após "--" até o final da linha */}

{ws}          {/* No action and no returne*/}
"bool"        {return T_BOOL;}
"int"         {return T_INT;}
"real"        {return T_REAL;}
"char"        {return T_CHAR;}

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

"\."        {return '.';}
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
                                              printf("minha string legal: %s\n", yytext);
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
      switch (token) {
        case ID:
          printf("id na posição: %d da symbol table\n", yylval.id_index);
          break;
        case V_BOOL:
          printf("bool com valor: %s\n", yylval.bool_value ? "true" : "false");
          break;
        case V_INT:
          printf("int com valor: %d\n", yylval.int_value);
          break;
        case V_REAL:
          printf("real com valor: %f\n", yylval.real_value);
          break;
        case V_CHAR:
          printf("char com valor: %c\n", yylval.char_value);
          break;
        case V_STRING:
          printf("string com valor: %s\n", yylval.string_value);
          free(yylval.string_value);
          break;
        default:
          printf("sem valor associado\n");
          break;
      }
  }
  printf("\nLeitura de tokens finalizada.\n");
  printFirst10Entries();
  

  destroySymbolTable();
  printf("\ntabela de simbolos destruida.\n");
  yylex_destroy();
  return 0;
}
