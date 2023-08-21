%{
#include<stdio.h>

#define ID 1  //Identifier token


#define T_INT 3
#define T_REAL 4
#define T_CHAR 5
#define T_BOOL 6

#define V_INT 7
#define V_CHAR 8
#define V_BOOL 9
#define V_REAL 10

#define EQ 11
#define LEQ 12
#define GEQ 13
#define GE 14
#define LE 15
#define NEQ 16

#define PLUS 17
#define MINUS 18
#define DIVIDE 19
#define MULTIPLY 20
#define MOD 21

#define LOOP 22
#define IF 23
#define ELSE 24
#define ELSIF 25
#define BEGIN 26
#define END 27


%}

low    [a-z]
upp    [A-Z]
number [0-9]
letter (low|upper|\_)*
ID     (letter)(letter|number)*

%option noyywrap

%%

"int" {return T_INT;}
"real" {return T_REAL;}
"bool" {return T_BOOL;}
"char" {return T_CHAR;}


"True" | "False"	{return V_BOOL;}
{number}{number}+ {return V_INT;}


">" {return GE;}
"<" {return LE;}
">=" {return GEQ;}
"<=" {return LEQ;}
"==" {return EQ;}
"!=" {return NEQ;}

"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MULTIPLY;}
"/" {return DIVIDE;}
"%" {return MOD;}


"if" {return IF;}
"else" {return ELSE;}
"elsif" {return ELSIF;}
"loop" {return LOOP;}
"begin" {return BEGIN;}
"end" {return END;}

{ID}  return ID;


%%

int main()
{
  int token = -1;
  while (token != 0) {
      token = yylex();
      printf("token: %d\n", token);
  }
  return 0;
}
