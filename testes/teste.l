%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "defines.h"

  //TODO: Mover SymbolEntry e logica da tabela de simbolos para outro arquivo
  struct SymbolEntry {
    char *name;
    int class;
  };

  struct SymbolEntry symbol_table[100]; // Tabela de símbolos (tamanho máximo de 100)
  int maxNumSymbols = 100;
  int numSymbols = 0;

  void initializeSymbolTable(){
    int i = 0;
    while(i < maxNumSymbols){
      symbol_table[i++].name = "";
    }
  }

  void addSymbol(const char * symbol_name, const int token_class){
    //TODO: Tratar duplicacao
    //TODO: Analisar abordagem usando hashtable
    int pos = numSymbols++;
    symbol_table[pos].name = strdup(symbol_name);
    symbol_table[pos].class = token_class;
  }

%}

low    [a-z]
upp    [A-Z]
number [0-9]
letter [a-z|A-Z|\_]*
delim         [ \t\n]
ws            {delim}+

%%

{ws}          {/* No action and no returne*/}
"bool"      {printf("I'm here."); addSymbol(yytext, T_BOOL); return T_BOOL;}
"int"       {return T_INT;}
"real"      {return T_REAL;}
"char"      {return T_CHAR;}

"true" | "false"	{return V_BOOL;}
">" {return '>';}
"<" {return '<';}
">=" {return GEQ;}
"<=" {return LEQ;}
"==" {return EQ;}
"!=" {return NEQ;}

"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
"%" {return '%';}

"!" {return '!';}
"&&" {return AND;}
"||" {return OR;}


"(" {return '(';}
")" {return ')';}
"[" {return '[';}
"]" {return ']';}

"const" {return CONST;}
"if" {return IF;}
"else" {return ELSE;}
"elsif" {return ELSIF;}
"loop" {return LOOP;}
"begin" {return _BEGIN;}
"end" {return END;}

"function" {return FUNCTION;}
"procedure" {return PROCEDURE;}

"return" {return RETURN;}
"break" {return BREAK;}
"continue" {return CONTINUE;}
"record" {return RECORD;}
"of" {return OF;}

"/." {return '.';}
"," {return ',';}
":" {return ':';}
";" {return ';';}
"{" {return '{';}
"}" {return '}';}

"type" {return TYPE;}
"array" {return ARRAY;}
"exit" {return EXIT;}
"when" {return WHEN;}
"to" {return TO;}
"step" {return STEP;}
"then" {return THEN;}

":=" {return ATTRIB;}

{number}+(\.{number}+)?(E[+-]?{number}+)?

{letter}({letter}|{number})*  {printf("ID: %s\n", yytext); addSymbol(yytext, ID); return ID;}
[+-]?{number}+(E[+-]?{number}+)? {return V_INT;}
[+-]?{number}+\.{number}+(E[+-]?{number}+)? {return V_REAL;}
\'.\' {return V_CHAR;}

(.)* {printf("ERROR: %s", yytext);}

%%

int main()
{
  initializeSymbolTable();
  printf("\n\n");
  int token = -1;
  while (token != 0) {
      token = yylex();
      printf("token: %d\n", token);
  }
  for(int i = 0; i < 100; i++){
    printf("Token: %s \t TokenClass: %d \n", symbol_table[i].name, symbol_table[i].class);
  }
  return 0;
}
