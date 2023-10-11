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
    ATTRIB = 259,                  /* ATTRIB  */
    SEMICOLON = 260,               /* SEMICOLON  */
    OR = 261,                      /* OR  */
    AND = 262,                     /* AND  */
    NEQ = 263,                     /* NEQ  */
    EQ = 264,                      /* EQ  */
    LESS = 265,                    /* LESS  */
    GREATER = 266,                 /* GREATER  */
    LEQ = 267,                     /* LEQ  */
    GEQ = 268,                     /* GEQ  */
    NOT = 269,                     /* NOT  */
    PLUS = 270,                    /* PLUS  */
    MINUS = 271,                   /* MINUS  */
    MULTIPLY = 272,                /* MULTIPLY  */
    DIVIDE = 273,                  /* DIVIDE  */
    MOD = 274,                     /* MOD  */
    LPAR = 275,                    /* LPAR  */
    RPAR = 276,                    /* RPAR  */
    V_REAL = 277,                  /* V_REAL  */
    V_BOOL = 278,                  /* V_BOOL  */
    V_CHAR = 279,                  /* V_CHAR  */
    V_STRING = 280,                /* V_STRING  */
    DOT = 281,                     /* DOT  */
    LBRA = 282,                    /* LBRA  */
    RBRA = 283,                    /* RBRA  */
    TYPE = 284,                    /* TYPE  */
    T_BOOL = 285,                  /* T_BOOL  */
    T_INT = 286,                   /* T_INT  */
    T_REAL = 287,                  /* T_REAL  */
    T_CHAR = 288,                  /* T_CHAR  */
    ARRAY = 289,                   /* ARRAY  */
    OF = 290,                      /* OF  */
    RECORD = 291,                  /* RECORD  */
    END = 292,                     /* END  */
    INTERVAL = 293,                /* INTERVAL  */
    COMMA = 294,                   /* COMMA  */
    COLON = 295,                   /* COLON  */
    PROCEDURE = 296,               /* PROCEDURE  */
    FUNCTION = 297,                /* FUNCTION  */
    VAR = 298,                     /* VAR  */
    BEGIN_ = 299,                  /* BEGIN_  */
    FOR = 300,                     /* FOR  */
    TO = 301,                      /* TO  */
    STEP = 302,                    /* STEP  */
    LOOP = 303,                    /* LOOP  */
    EXIT = 304,                    /* EXIT  */
    WHEN = 305,                    /* WHEN  */
    CONTINUE = 306,                /* CONTINUE  */
    BREAK = 307,                   /* BREAK  */
    IF = 308,                      /* IF  */
    THEN = 309,                    /* THEN  */
    ELSE = 310,                    /* ELSE  */
    RETURN = 311,                  /* RETURN  */
    REF = 312,                     /* REF  */
    ID = 313,                      /* ID  */
    V_INT = 314                    /* V_INT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define CONST 258
#define ATTRIB 259
#define SEMICOLON 260
#define OR 261
#define AND 262
#define NEQ 263
#define EQ 264
#define LESS 265
#define GREATER 266
#define LEQ 267
#define GEQ 268
#define NOT 269
#define PLUS 270
#define MINUS 271
#define MULTIPLY 272
#define DIVIDE 273
#define MOD 274
#define LPAR 275
#define RPAR 276
#define V_REAL 277
#define V_BOOL 278
#define V_CHAR 279
#define V_STRING 280
#define DOT 281
#define LBRA 282
#define RBRA 283
#define TYPE 284
#define T_BOOL 285
#define T_INT 286
#define T_REAL 287
#define T_CHAR 288
#define ARRAY 289
#define OF 290
#define RECORD 291
#define END 292
#define INTERVAL 293
#define COMMA 294
#define COLON 295
#define PROCEDURE 296
#define FUNCTION 297
#define VAR 298
#define BEGIN_ 299
#define FOR 300
#define TO 301
#define STEP 302
#define LOOP 303
#define EXIT 304
#define WHEN 305
#define CONTINUE 306
#define BREAK 307
#define IF 308
#define THEN 309
#define ELSE 310
#define RETURN 311
#define REF 312
#define ID 313
#define V_INT 314

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "src/parser.y"

    struct {
        int type;
        char* name;
        union {
            int v_int;
            int v_bool;
            double v_real;
            char v_char;
            char* v_string;
        } value;
    } info;

#line 199 "src/parser.y.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_Y_H_INCLUDED  */
