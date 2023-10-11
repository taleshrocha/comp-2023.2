/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_Y_H_INCLUDED
# define YY_YY_SRC_PARSER_Y_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CONST = 258,                   /* CONST  */
    ID = 259,                      /* ID  */
    ATTRIB = 260,                  /* ATTRIB  */
    SEMICOLON = 261,               /* SEMICOLON  */
    OR = 262,                      /* OR  */
    AND = 263,                     /* AND  */
    NEQ = 264,                     /* NEQ  */
    EQ = 265,                      /* EQ  */
    LESS = 266,                    /* LESS  */
    GREATER = 267,                 /* GREATER  */
    LEQ = 268,                     /* LEQ  */
    GEQ = 269,                     /* GEQ  */
    NOT = 270,                     /* NOT  */
    PLUS = 271,                    /* PLUS  */
    MINUS = 272,                   /* MINUS  */
    MULTIPLY = 273,                /* MULTIPLY  */
    DIVIDE = 274,                  /* DIVIDE  */
    MOD = 275,                     /* MOD  */
    LPAR = 276,                    /* LPAR  */
    RPAR = 277,                    /* RPAR  */
    V_INT = 278,                   /* V_INT  */
    V_REAL = 279,                  /* V_REAL  */
    V_BOOL = 280,                  /* V_BOOL  */
    V_CHAR = 281,                  /* V_CHAR  */
    V_STRING = 282,                /* V_STRING  */
    DOT = 283,                     /* DOT  */
    LBRA = 284,                    /* LBRA  */
    RBRA = 285,                    /* RBRA  */
    TYPE = 286,                    /* TYPE  */
    T_BOOL = 287,                  /* T_BOOL  */
    T_INT = 288,                   /* T_INT  */
    T_REAL = 289,                  /* T_REAL  */
    T_CHAR = 290,                  /* T_CHAR  */
    ARRAY = 291,                   /* ARRAY  */
    OF = 292,                      /* OF  */
    RECORD = 293,                  /* RECORD  */
    END = 294,                     /* END  */
    INTERVAL = 295,                /* INTERVAL  */
    COMMA = 296,                   /* COMMA  */
    COLON = 297,                   /* COLON  */
    PROCEDURE = 298,               /* PROCEDURE  */
    FUNCTION = 299,                /* FUNCTION  */
    VAR = 300,                     /* VAR  */
    BEGIN_ = 301,                  /* BEGIN_  */
    FOR = 302,                     /* FOR  */
    TO = 303,                      /* TO  */
    STEP = 304,                    /* STEP  */
    LOOP = 305,                    /* LOOP  */
    EXIT = 306,                    /* EXIT  */
    WHEN = 307,                    /* WHEN  */
    CONTINUE = 308,                /* CONTINUE  */
    BREAK = 309,                   /* BREAK  */
    IF = 310,                      /* IF  */
    THEN = 311,                    /* THEN  */
    ELSE = 312,                    /* ELSE  */
    RETURN = 313,                  /* RETURN  */
    REF = 314                      /* REF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define CONST 258
#define ID 259
#define ATTRIB 260
#define SEMICOLON 261
#define OR 262
#define AND 263
#define NEQ 264
#define EQ 265
#define LESS 266
#define GREATER 267
#define LEQ 268
#define GEQ 269
#define NOT 270
#define PLUS 271
#define MINUS 272
#define MULTIPLY 273
#define DIVIDE 274
#define MOD 275
#define LPAR 276
#define RPAR 277
#define V_INT 278
#define V_REAL 279
#define V_BOOL 280
#define V_CHAR 281
#define V_STRING 282
#define DOT 283
#define LBRA 284
#define RBRA 285
#define TYPE 286
#define T_BOOL 287
#define T_INT 288
#define T_REAL 289
#define T_CHAR 290
#define ARRAY 291
#define OF 292
#define RECORD 293
#define END 294
#define INTERVAL 295
#define COMMA 296
#define COLON 297
#define PROCEDURE 298
#define FUNCTION 299
#define VAR 300
#define BEGIN_ 301
#define FOR 302
#define TO 303
#define STEP 304
#define LOOP 305
#define EXIT 306
#define WHEN 307
#define CONTINUE 308
#define BREAK 309
#define IF 310
#define THEN 311
#define ELSE 312
#define RETURN 313
#define REF 314

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 30 "src/parser.y"

    struct {
        int type;
        char* name;
        union {
            int v_int;
            int v_bool;
            double v_real;
            char v_char;
            char* v_string;
        };
        struct Node* tree;
    } info;

#line 200 "src/parser.y.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_Y_H_INCLUDED  */
