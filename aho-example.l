%{
#define IF 0
#define THEN 1
#define ELSE 2
%}

/* Regular definitions */
delim         [ \t\n]
ws            {delim}+
letter        [A-Za-z]
digit         [0-9]
id            {letter}({letter}|{digit})*
number        {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

%%

{ws}          {/* No action and no returne*/}
if            {return(IF);}
then          {return(THEN);}
else          {return(ELSE);}
{id}          {yylval = (int) installID(); return(ID);}
{number}      {yylval = (int) installNum(); return(NUMBER);}
"<"           {yylval = LT; return(RELOP);}
"<="          {yylval = LE; return(RELOP);}
"="           {yylval = EQ; return(RELOP);}
"<>"          {yylval = NE; return(RELOP);}
">"           {yylval = GT; return(RELOP);}
">="          {yylval = GE; return(RELOP);}

%%

int installID() {
  /* function to install the lexeme, whose first character is pointed to by 
     yytext, and whose length is yyleng, into the symbol table and return a 
     pointer thereto */ 
}

int installNum() {
  /* similar to installID, but puts numer- ical constants into a separate 
     table */ 
}
