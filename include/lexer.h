#ifndef LEXER_H
#define LEXER_H

extern int column_counter;
extern int yylineno;

extern int yylex();
extern int yylex_destroy();
extern char terminal_mapping[56][16];
extern char non_terminal_mapping[44][32];

#endif // LEXER_H