/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

#include <stdio.h>
#include <lexer.l.h>

extern struct Node;

extern int column_counter;

void yyerror(char* s) {
    fprintf(stderr, "%s at line-column: %d-%d\n", s , yylineno, column_counter);
    fprintf(stderr, "current token is: \"%s\"\n", yytext);
}

#line 85 "src/parser.y.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.y.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONST = 3,                      /* CONST  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_ATTRIB = 5,                     /* ATTRIB  */
  YYSYMBOL_SEMICOLON = 6,                  /* SEMICOLON  */
  YYSYMBOL_OR = 7,                         /* OR  */
  YYSYMBOL_AND = 8,                        /* AND  */
  YYSYMBOL_NEQ = 9,                        /* NEQ  */
  YYSYMBOL_EQ = 10,                        /* EQ  */
  YYSYMBOL_LESS = 11,                      /* LESS  */
  YYSYMBOL_GREATER = 12,                   /* GREATER  */
  YYSYMBOL_LEQ = 13,                       /* LEQ  */
  YYSYMBOL_GEQ = 14,                       /* GEQ  */
  YYSYMBOL_NOT = 15,                       /* NOT  */
  YYSYMBOL_PLUS = 16,                      /* PLUS  */
  YYSYMBOL_MINUS = 17,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 18,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 19,                    /* DIVIDE  */
  YYSYMBOL_MOD = 20,                       /* MOD  */
  YYSYMBOL_LPAR = 21,                      /* LPAR  */
  YYSYMBOL_RPAR = 22,                      /* RPAR  */
  YYSYMBOL_V_INT = 23,                     /* V_INT  */
  YYSYMBOL_V_REAL = 24,                    /* V_REAL  */
  YYSYMBOL_V_BOOL = 25,                    /* V_BOOL  */
  YYSYMBOL_V_CHAR = 26,                    /* V_CHAR  */
  YYSYMBOL_V_STRING = 27,                  /* V_STRING  */
  YYSYMBOL_DOT = 28,                       /* DOT  */
  YYSYMBOL_LBRA = 29,                      /* LBRA  */
  YYSYMBOL_RBRA = 30,                      /* RBRA  */
  YYSYMBOL_TYPE = 31,                      /* TYPE  */
  YYSYMBOL_T_BOOL = 32,                    /* T_BOOL  */
  YYSYMBOL_T_INT = 33,                     /* T_INT  */
  YYSYMBOL_T_REAL = 34,                    /* T_REAL  */
  YYSYMBOL_T_CHAR = 35,                    /* T_CHAR  */
  YYSYMBOL_ARRAY = 36,                     /* ARRAY  */
  YYSYMBOL_OF = 37,                        /* OF  */
  YYSYMBOL_RECORD = 38,                    /* RECORD  */
  YYSYMBOL_END = 39,                       /* END  */
  YYSYMBOL_INTERVAL = 40,                  /* INTERVAL  */
  YYSYMBOL_COMMA = 41,                     /* COMMA  */
  YYSYMBOL_COLON = 42,                     /* COLON  */
  YYSYMBOL_PROCEDURE = 43,                 /* PROCEDURE  */
  YYSYMBOL_FUNCTION = 44,                  /* FUNCTION  */
  YYSYMBOL_VAR = 45,                       /* VAR  */
  YYSYMBOL_BEGIN_ = 46,                    /* BEGIN_  */
  YYSYMBOL_FOR = 47,                       /* FOR  */
  YYSYMBOL_TO = 48,                        /* TO  */
  YYSYMBOL_STEP = 49,                      /* STEP  */
  YYSYMBOL_LOOP = 50,                      /* LOOP  */
  YYSYMBOL_EXIT = 51,                      /* EXIT  */
  YYSYMBOL_WHEN = 52,                      /* WHEN  */
  YYSYMBOL_CONTINUE = 53,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 54,                     /* BREAK  */
  YYSYMBOL_IF = 55,                        /* IF  */
  YYSYMBOL_THEN = 56,                      /* THEN  */
  YYSYMBOL_ELSE = 57,                      /* ELSE  */
  YYSYMBOL_RETURN = 58,                    /* RETURN  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_Prog = 60,                      /* Prog  */
  YYSYMBOL_Decl = 61,                      /* Decl  */
  YYSYMBOL_Consts = 62,                    /* Consts  */
  YYSYMBOL_Vars = 63,                      /* Vars  */
  YYSYMBOL_Types = 64,                     /* Types  */
  YYSYMBOL_TypeDec = 65,                   /* TypeDec  */
  YYSYMBOL_Interval = 66,                  /* Interval  */
  YYSYMBOL_Fields = 67,                    /* Fields  */
  YYSYMBOL_SubProg = 68,                   /* SubProg  */
  YYSYMBOL_ProcedureDecl = 69,             /* ProcedureDecl  */
  YYSYMBOL_Parameters = 70,                /* Parameters  */
  YYSYMBOL_ParametersAux = 71,             /* ParametersAux  */
  YYSYMBOL_FunctionDecl = 72,              /* FunctionDecl  */
  YYSYMBOL_CmdBlock = 73,                  /* CmdBlock  */
  YYSYMBOL_Cmds = 74,                      /* Cmds  */
  YYSYMBOL_CmdAux = 75,                    /* CmdAux  */
  YYSYMBOL_CmdAux_ = 76,                   /* CmdAux_  */
  YYSYMBOL_AcessMemAddr = 77,              /* AcessMemAddr  */
  YYSYMBOL_CmdConditional = 78,            /* CmdConditional  */
  YYSYMBOL_CmdConditionalEnd = 79,         /* CmdConditionalEnd  */
  YYSYMBOL_CmdReturn = 80,                 /* CmdReturn  */
  YYSYMBOL_CmdReturnExp = 81,              /* CmdReturnExp  */
  YYSYMBOL_Exp = 82,                       /* Exp  */
  YYSYMBOL_Terms = 83,                     /* Terms  */
  YYSYMBOL_Comps = 84,                     /* Comps  */
  YYSYMBOL_Factor = 85,                    /* Factor  */
  YYSYMBOL_AriOp = 86,                     /* AriOp  */
  YYSYMBOL_AriOp2 = 87,                    /* AriOp2  */
  YYSYMBOL_Parenthesis = 88,               /* Parenthesis  */
  YYSYMBOL_UnaryExp = 89,                  /* UnaryExp  */
  YYSYMBOL_SimpleExp = 90,                 /* SimpleExp  */
  YYSYMBOL_NumExp = 91,                    /* NumExp  */
  YYSYMBOL_Args = 92,                      /* Args  */
  YYSYMBOL_ArgsAux = 93                    /* ArgsAux  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   180

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  182

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   313


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    40,    40,    43,    46,    47,    50,    51,    54,    55,
      58,    59,    60,    61,    62,    63,    64,    67,    68,    71,
      72,    75,    76,    77,    81,    85,    86,    90,    91,    95,
      99,   103,   104,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   119,   120,   125,   126,   127,   128,   132,   136,
     137,   141,   145,   146,   150,   151,   155,   156,   160,   161,
     162,   163,   164,   165,   166,   170,   171,   175,   176,   177,
     181,   194,   195,   196,   200,   201,   205,   206,   207,   211,
     212,   216,   217,   218,   219,   220,   224,   225,   228,   229
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CONST", "ID",
  "ATTRIB", "SEMICOLON", "OR", "AND", "NEQ", "EQ", "LESS", "GREATER",
  "LEQ", "GEQ", "NOT", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MOD",
  "LPAR", "RPAR", "V_INT", "V_REAL", "V_BOOL", "V_CHAR", "V_STRING", "DOT",
  "LBRA", "RBRA", "TYPE", "T_BOOL", "T_INT", "T_REAL", "T_CHAR", "ARRAY",
  "OF", "RECORD", "END", "INTERVAL", "COMMA", "COLON", "PROCEDURE",
  "FUNCTION", "VAR", "BEGIN_", "FOR", "TO", "STEP", "LOOP", "EXIT", "WHEN",
  "CONTINUE", "BREAK", "IF", "THEN", "ELSE", "RETURN", "$accept", "Prog",
  "Decl", "Consts", "Vars", "Types", "TypeDec", "Interval", "Fields",
  "SubProg", "ProcedureDecl", "Parameters", "ParametersAux",
  "FunctionDecl", "CmdBlock", "Cmds", "CmdAux", "CmdAux_", "AcessMemAddr",
  "CmdConditional", "CmdConditionalEnd", "CmdReturn", "CmdReturnExp",
  "Exp", "Terms", "Comps", "Factor", "AriOp", "AriOp2", "Parenthesis",
  "UnaryExp", "SimpleExp", "NumExp", "Args", "ArgsAux", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-97)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,    16,    26,   -16,    13,    57,   -97,    40,   -97,    67,
     -27,     8,    89,     0,    60,    91,   116,    40,   -27,   -27,
     -97,    73,    80,    80,     8,   -97,   -97,   -97,   -97,   -97,
      45,    62,    71,   -97,   117,    75,    90,   -97,   -97,   -97,
     -97,    79,   118,    40,    72,   -97,   -97,     8,     8,   -97,
      99,   133,    59,   -97,   -97,     7,   119,   120,   -97,   -97,
     -97,    75,   -97,   -97,    56,     8,   138,     8,     4,     8,
       8,     8,     8,     8,     8,     8,     8,    73,    73,    73,
      73,    73,     7,   140,     0,     8,     3,   -97,   136,   -97,
       0,     8,   -97,   -97,   -97,   -97,   -97,   -97,   121,   142,
     143,   147,   147,   -97,    15,   131,   -97,     6,   -97,    71,
     -97,   -97,   -97,   -97,   -97,   -97,   -97,    90,    90,   -97,
     -97,   -97,   148,     8,   122,   136,   -16,   -97,   136,     8,
     113,   124,    13,   114,   135,   137,     8,   -97,   -97,   -97,
      40,     1,   -97,   101,   130,    12,     7,   -97,   -97,     7,
     -16,   123,   -97,   -97,     8,   -16,   -97,   129,     8,   161,
     128,   164,     7,    11,   -97,     7,    20,   142,   147,   -97,
     -97,   -16,     8,   -97,     8,   -97,   -97,   165,     2,   -97,
     -97,   -97
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     0,     9,     0,     1,     7,     2,     0,
      23,     0,     0,     0,     0,     0,     0,     7,    23,    23,
      44,     0,     0,     0,     0,    81,    82,    83,    84,    85,
      80,     0,    55,    57,    64,    66,    69,    73,    74,    78,
      79,     0,     0,     7,     0,    36,    37,     0,    53,    34,
       0,    31,    43,    35,    41,     0,     0,     0,     3,    21,
      22,    65,    76,    77,     0,    87,     0,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    52,    30,
       0,     0,    33,    14,    10,    11,    12,    13,     0,    20,
       0,    26,    26,    75,    89,     0,    45,     0,     4,    54,
      56,    58,    59,    60,    61,    62,    63,    67,    68,    70,
      71,    72,     0,     0,     0,    40,     0,    32,    42,     0,
       0,     0,     9,     0,     0,     0,    87,    86,    47,    46,
       7,     0,    39,    50,     0,     0,     0,    16,     8,     0,
       0,     0,    88,     6,     0,     0,    48,     0,     0,     0,
      28,     0,     0,     0,    49,     0,    17,    20,    26,    25,
      24,     0,     0,    15,     0,    19,    27,     0,     0,    18,
      29,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -97,   -97,   -97,   104,   -15,    41,   -79,     5,     9,    83,
     -97,   -96,   -97,   -97,    -3,   -69,   -97,   -97,    -8,   -97,
     -97,   -97,   -97,   -10,   105,   107,    61,   157,    34,    35,
     -97,    95,   -97,    44,   -97
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    13,    10,   100,   144,   131,    17,
      18,   134,   169,    19,    49,    50,    51,    92,    30,    53,
     156,    54,    87,   104,    32,    33,    34,    35,    36,    37,
      38,    39,    40,   105,   137
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       8,    31,    58,   122,    20,    52,   135,     1,    69,    69,
      69,    93,    20,    69,    64,   124,    15,    16,    69,    69,
       5,   127,    69,    21,    22,    23,     6,    69,    84,    24,
       7,    25,    26,    27,    28,    29,   139,    86,    88,    94,
      95,    96,    97,    98,     9,    99,     7,    42,     7,   154,
      43,    44,   158,    45,    46,    47,   136,   107,    48,   126,
     172,   174,    11,    69,    91,    55,    65,   159,    68,    69,
     160,    14,   176,    66,    67,   125,    52,    20,   103,    70,
      65,   128,    52,   171,    20,    12,   173,    66,    67,    22,
      23,    77,    78,    41,    24,    56,    25,    26,    27,    28,
      29,    59,    60,    25,    26,    27,    28,    29,    79,    80,
      81,   117,   118,   141,   119,   120,   121,    62,    63,   145,
      57,    82,    83,   143,    85,   153,    71,    72,    73,    74,
      75,    76,   111,   112,   113,   114,   115,   116,    89,    90,
     101,   102,   106,    69,   163,   123,   130,   161,   166,   132,
     129,   133,   164,   138,   140,   146,   149,   150,   155,   151,
     157,   142,   178,   147,   145,   162,   165,   167,   177,   168,
     170,   180,   108,   148,   109,   181,   175,   110,    61,   179,
     152
};

static const yytype_uint8 yycheck[] =
{
       3,    11,    17,    82,     4,    13,   102,     3,     7,     7,
       7,     4,     4,     7,    24,    84,    43,    44,     7,     7,
       4,    90,     7,    15,    16,    17,     0,     7,    43,    21,
      46,    23,    24,    25,    26,    27,    30,    47,    48,    32,
      33,    34,    35,    36,    31,    38,    46,    47,    46,    48,
      50,    51,    40,    53,    54,    55,    41,    67,    58,    56,
      49,    41,     5,     7,     5,     5,    21,   146,     6,     7,
     149,     4,   168,    28,    29,    85,    84,     4,    22,     8,
      21,    91,    90,   162,     4,    45,   165,    28,    29,    16,
      17,    16,    17,     4,    21,     4,    23,    24,    25,    26,
      27,    18,    19,    23,    24,    25,    26,    27,    18,    19,
      20,    77,    78,   123,    79,    80,    81,    22,    23,   129,
       4,    42,     4,   126,    52,   140,     9,    10,    11,    12,
      13,    14,    71,    72,    73,    74,    75,    76,    39,     6,
      21,    21,     4,     7,   154,     5,     4,   150,   158,     6,
      29,     4,   155,    22,     6,    42,    42,    22,    57,    22,
      30,    39,   172,    39,   174,    42,    37,     6,   171,    41,
       6,     6,    68,   132,    69,   178,   167,    70,    21,   174,
     136
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    60,    61,    62,     4,     0,    46,    73,    31,
      64,     5,    45,    63,     4,    43,    44,    68,    69,    72,
       4,    15,    16,    17,    21,    23,    24,    25,    26,    27,
      77,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,     4,    47,    50,    51,    53,    54,    55,    58,    73,
      74,    75,    77,    78,    80,     5,     4,     4,    63,    68,
      68,    86,    90,    90,    82,    21,    28,    29,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    16,    17,    18,
      19,    20,    42,     4,    63,    52,    82,    81,    82,    39,
       6,     5,    76,     4,    32,    33,    34,    35,    36,    38,
      65,    21,    21,    22,    82,    92,     4,    82,    62,    83,
      84,    85,    85,    85,    85,    85,    85,    87,    87,    88,
      88,    88,    65,     5,    74,    82,    56,    74,    82,    29,
       4,    67,     6,     4,    70,    70,    41,    93,    22,    30,
       6,    82,    39,    73,    66,    82,    42,    39,    64,    42,
      22,    22,    92,    63,    48,    57,    79,    30,    40,    65,
      65,    73,    42,    82,    73,    37,    82,     6,    41,    71,
       6,    65,    49,    65,    41,    67,    70,    73,    82,    66,
       6,    73
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    61,    62,    62,    63,    63,    64,    64,
      65,    65,    65,    65,    65,    65,    65,    66,    66,    67,
      67,    68,    68,    68,    69,    70,    70,    71,    71,    72,
      73,    74,    74,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    76,    76,    77,    77,    77,    77,    78,    79,
      79,    80,    81,    81,    82,    82,    83,    83,    84,    84,
      84,    84,    84,    84,    84,    85,    85,    86,    86,    86,
      87,    87,    87,    87,    88,    88,    89,    89,    89,    90,
      90,    91,    91,    91,    91,    91,    92,    92,    93,    93
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     6,     0,     6,     0,     6,     0,
       1,     1,     1,     1,     1,     6,     3,     3,     5,     5,
       0,     2,     2,     0,     7,     4,     0,     2,     0,     9,
       4,     1,     3,     2,     1,     1,     1,     1,     9,     4,
       3,     1,     2,     0,     1,     3,     4,     4,     5,     2,
       0,     2,     1,     0,     3,     1,     3,     1,     3,     3,
       3,     3,     3,     3,     1,     2,     1,     3,     3,     1,
       3,     3,     3,     1,     1,     3,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     0,     2,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Prog: Decl CmdBlock  */
#line 40 "src/parser.y"
                      {}
#line 1289 "src/parser.y.c"
    break;

  case 3: /* Decl: Consts Types SubProg Vars  */
#line 43 "src/parser.y"
                                  {}
#line 1295 "src/parser.y.c"
    break;

  case 4: /* Consts: CONST ID ATTRIB Exp SEMICOLON Consts  */
#line 46 "src/parser.y"
                                             {}
#line 1301 "src/parser.y.c"
    break;

  case 6: /* Vars: VAR ID COLON TypeDec SEMICOLON Vars  */
#line 50 "src/parser.y"
                                            {}
#line 1307 "src/parser.y.c"
    break;

  case 8: /* Types: TYPE ID ATTRIB TypeDec SEMICOLON Types  */
#line 54 "src/parser.y"
                                               {}
#line 1313 "src/parser.y.c"
    break;

  case 10: /* TypeDec: T_BOOL  */
#line 58 "src/parser.y"
               {}
#line 1319 "src/parser.y.c"
    break;

  case 11: /* TypeDec: T_INT  */
#line 59 "src/parser.y"
              {}
#line 1325 "src/parser.y.c"
    break;

  case 12: /* TypeDec: T_REAL  */
#line 60 "src/parser.y"
               {}
#line 1331 "src/parser.y.c"
    break;

  case 13: /* TypeDec: T_CHAR  */
#line 61 "src/parser.y"
               {}
#line 1337 "src/parser.y.c"
    break;

  case 14: /* TypeDec: ID  */
#line 62 "src/parser.y"
           {}
#line 1343 "src/parser.y.c"
    break;

  case 15: /* TypeDec: ARRAY LBRA Interval RBRA OF TypeDec  */
#line 63 "src/parser.y"
                                             {}
#line 1349 "src/parser.y.c"
    break;

  case 16: /* TypeDec: RECORD Fields END  */
#line 64 "src/parser.y"
                          {}
#line 1355 "src/parser.y.c"
    break;

  case 17: /* Interval: Exp INTERVAL Exp  */
#line 67 "src/parser.y"
                         {}
#line 1361 "src/parser.y.c"
    break;

  case 18: /* Interval: Exp INTERVAL Exp COMMA Interval  */
#line 68 "src/parser.y"
                                        {}
#line 1367 "src/parser.y.c"
    break;

  case 19: /* Fields: ID COLON TypeDec SEMICOLON Fields  */
#line 71 "src/parser.y"
                                          {}
#line 1373 "src/parser.y.c"
    break;

  case 20: /* Fields: %empty  */
#line 72 "src/parser.y"
                      {}
#line 1379 "src/parser.y.c"
    break;

  case 21: /* SubProg: ProcedureDecl SubProg  */
#line 75 "src/parser.y"
                              {}
#line 1385 "src/parser.y.c"
    break;

  case 22: /* SubProg: FunctionDecl SubProg  */
#line 76 "src/parser.y"
                             {}
#line 1391 "src/parser.y.c"
    break;

  case 23: /* SubProg: %empty  */
#line 77 "src/parser.y"
                      {}
#line 1397 "src/parser.y.c"
    break;

  case 24: /* ProcedureDecl: PROCEDURE ID LPAR Parameters RPAR CmdBlock SEMICOLON  */
#line 81 "src/parser.y"
                                                             {}
#line 1403 "src/parser.y.c"
    break;

  case 25: /* Parameters: ID COLON TypeDec ParametersAux  */
#line 85 "src/parser.y"
                                       {}
#line 1409 "src/parser.y.c"
    break;

  case 26: /* Parameters: %empty  */
#line 86 "src/parser.y"
                      {}
#line 1415 "src/parser.y.c"
    break;

  case 27: /* ParametersAux: COMMA Parameters  */
#line 90 "src/parser.y"
                         {}
#line 1421 "src/parser.y.c"
    break;

  case 28: /* ParametersAux: %empty  */
#line 91 "src/parser.y"
                      {}
#line 1427 "src/parser.y.c"
    break;

  case 29: /* FunctionDecl: FUNCTION ID LPAR Parameters RPAR COLON TypeDec CmdBlock SEMICOLON  */
#line 95 "src/parser.y"
                                                                          {}
#line 1433 "src/parser.y.c"
    break;

  case 30: /* CmdBlock: BEGIN_ Vars Cmds END  */
#line 99 "src/parser.y"
                             {}
#line 1439 "src/parser.y.c"
    break;

  case 31: /* Cmds: CmdAux  */
#line 103 "src/parser.y"
               {}
#line 1445 "src/parser.y.c"
    break;

  case 32: /* Cmds: CmdAux SEMICOLON Cmds  */
#line 104 "src/parser.y"
                              {}
#line 1451 "src/parser.y.c"
    break;

  case 33: /* CmdAux: AcessMemAddr CmdAux_  */
#line 108 "src/parser.y"
                             {}
#line 1457 "src/parser.y.c"
    break;

  case 34: /* CmdAux: CmdBlock  */
#line 109 "src/parser.y"
                 {}
#line 1463 "src/parser.y.c"
    break;

  case 35: /* CmdAux: CmdConditional  */
#line 110 "src/parser.y"
                       {}
#line 1469 "src/parser.y.c"
    break;

  case 36: /* CmdAux: CONTINUE  */
#line 111 "src/parser.y"
                 {}
#line 1475 "src/parser.y.c"
    break;

  case 37: /* CmdAux: BREAK  */
#line 112 "src/parser.y"
              {}
#line 1481 "src/parser.y.c"
    break;

  case 38: /* CmdAux: FOR ID ATTRIB Exp TO Exp STEP Exp CmdBlock  */
#line 113 "src/parser.y"
                                                   {}
#line 1487 "src/parser.y.c"
    break;

  case 39: /* CmdAux: LOOP Vars Cmds END  */
#line 114 "src/parser.y"
                           {}
#line 1493 "src/parser.y.c"
    break;

  case 40: /* CmdAux: EXIT WHEN Exp  */
#line 115 "src/parser.y"
                      {}
#line 1499 "src/parser.y.c"
    break;

  case 41: /* CmdAux: CmdReturn  */
#line 116 "src/parser.y"
                  {}
#line 1505 "src/parser.y.c"
    break;

  case 42: /* CmdAux_: ATTRIB Exp  */
#line 119 "src/parser.y"
                     {}
#line 1511 "src/parser.y.c"
    break;

  case 43: /* CmdAux_: %empty  */
#line 120 "src/parser.y"
                      {}
#line 1517 "src/parser.y.c"
    break;

  case 44: /* AcessMemAddr: ID  */
#line 125 "src/parser.y"
           {}
#line 1523 "src/parser.y.c"
    break;

  case 45: /* AcessMemAddr: AcessMemAddr DOT ID  */
#line 126 "src/parser.y"
                            {}
#line 1529 "src/parser.y.c"
    break;

  case 46: /* AcessMemAddr: AcessMemAddr LBRA Exp RBRA  */
#line 127 "src/parser.y"
                                   {}
#line 1535 "src/parser.y.c"
    break;

  case 47: /* AcessMemAddr: AcessMemAddr LPAR Args RPAR  */
#line 128 "src/parser.y"
                                    {}
#line 1541 "src/parser.y.c"
    break;

  case 48: /* CmdConditional: IF Exp THEN CmdBlock CmdConditionalEnd  */
#line 132 "src/parser.y"
                                               {}
#line 1547 "src/parser.y.c"
    break;

  case 49: /* CmdConditionalEnd: ELSE CmdBlock  */
#line 136 "src/parser.y"
                      {}
#line 1553 "src/parser.y.c"
    break;

  case 50: /* CmdConditionalEnd: %empty  */
#line 137 "src/parser.y"
                      {}
#line 1559 "src/parser.y.c"
    break;

  case 51: /* CmdReturn: RETURN CmdReturnExp  */
#line 141 "src/parser.y"
                            {}
#line 1565 "src/parser.y.c"
    break;

  case 52: /* CmdReturnExp: Exp  */
#line 145 "src/parser.y"
            {}
#line 1571 "src/parser.y.c"
    break;

  case 53: /* CmdReturnExp: %empty  */
#line 146 "src/parser.y"
                      {}
#line 1577 "src/parser.y.c"
    break;

  case 54: /* Exp: Exp OR Terms  */
#line 150 "src/parser.y"
                     {}
#line 1583 "src/parser.y.c"
    break;

  case 55: /* Exp: Terms  */
#line 151 "src/parser.y"
              {}
#line 1589 "src/parser.y.c"
    break;

  case 56: /* Terms: Terms AND Comps  */
#line 155 "src/parser.y"
                        {}
#line 1595 "src/parser.y.c"
    break;

  case 57: /* Terms: Comps  */
#line 156 "src/parser.y"
              {}
#line 1601 "src/parser.y.c"
    break;

  case 58: /* Comps: Factor NEQ Factor  */
#line 160 "src/parser.y"
                          {}
#line 1607 "src/parser.y.c"
    break;

  case 59: /* Comps: Factor EQ Factor  */
#line 161 "src/parser.y"
                          {}
#line 1613 "src/parser.y.c"
    break;

  case 60: /* Comps: Factor LESS Factor  */
#line 162 "src/parser.y"
                           {}
#line 1619 "src/parser.y.c"
    break;

  case 61: /* Comps: Factor GREATER Factor  */
#line 163 "src/parser.y"
                               {}
#line 1625 "src/parser.y.c"
    break;

  case 62: /* Comps: Factor LEQ Factor  */
#line 164 "src/parser.y"
                          {}
#line 1631 "src/parser.y.c"
    break;

  case 63: /* Comps: Factor GEQ Factor  */
#line 165 "src/parser.y"
                           {}
#line 1637 "src/parser.y.c"
    break;

  case 64: /* Comps: Factor  */
#line 166 "src/parser.y"
                {}
#line 1643 "src/parser.y.c"
    break;

  case 65: /* Factor: NOT AriOp  */
#line 170 "src/parser.y"
                  {}
#line 1649 "src/parser.y.c"
    break;

  case 66: /* Factor: AriOp  */
#line 171 "src/parser.y"
              {}
#line 1655 "src/parser.y.c"
    break;

  case 67: /* AriOp: AriOp PLUS AriOp2  */
#line 175 "src/parser.y"
                          {}
#line 1661 "src/parser.y.c"
    break;

  case 68: /* AriOp: AriOp MINUS AriOp2  */
#line 176 "src/parser.y"
                           {}
#line 1667 "src/parser.y.c"
    break;

  case 69: /* AriOp: AriOp2  */
#line 177 "src/parser.y"
               {}
#line 1673 "src/parser.y.c"
    break;

  case 70: /* AriOp2: AriOp2 MULTIPLY Parenthesis  */
#line 181 "src/parser.y"
                                    {
        if ((yyvsp[-2].info).type == T_INT && (yyvsp[0].info).type == T_INT) {
            (yyval.info).type = T_INT;
        } else if ((yyvsp[-2].info).type == T_INT && (yyvsp[0].info).type == T_REAL) {
            (yyval.info).type = T_REAL;
        } else if ((yyvsp[-2].info).type == T_REAL && (yyvsp[0].info).type == T_INT) {
            (yyval.info).type = T_REAL;
        } else if ((yyvsp[-2].info).type == T_REAL && (yyvsp[0].info).type == T_REAL) {
            (yyval.info).type = T_REAL;
        } else {
            printf("ERROR! TODO...\n");
        }
        }
#line 1691 "src/parser.y.c"
    break;

  case 71: /* AriOp2: AriOp2 DIVIDE Parenthesis  */
#line 194 "src/parser.y"
                                  {}
#line 1697 "src/parser.y.c"
    break;

  case 72: /* AriOp2: AriOp2 MOD Parenthesis  */
#line 195 "src/parser.y"
                               {}
#line 1703 "src/parser.y.c"
    break;

  case 73: /* AriOp2: Parenthesis  */
#line 196 "src/parser.y"
                    { (yyval.info).type = (yyvsp[0].info).type; }
#line 1709 "src/parser.y.c"
    break;

  case 74: /* Parenthesis: UnaryExp  */
#line 200 "src/parser.y"
                 { (yyval.info).type = (yyvsp[0].info).type; }
#line 1715 "src/parser.y.c"
    break;

  case 75: /* Parenthesis: LPAR Exp RPAR  */
#line 201 "src/parser.y"
                      { (yyval.info).type = (yyvsp[-1].info).type; }
#line 1721 "src/parser.y.c"
    break;

  case 76: /* UnaryExp: PLUS SimpleExp  */
#line 205 "src/parser.y"
                       { (yyval.info).type = (yyvsp[0].info).type; }
#line 1727 "src/parser.y.c"
    break;

  case 77: /* UnaryExp: MINUS SimpleExp  */
#line 206 "src/parser.y"
                        { (yyval.info).type = (yyvsp[0].info).type; }
#line 1733 "src/parser.y.c"
    break;

  case 78: /* UnaryExp: SimpleExp  */
#line 207 "src/parser.y"
                  { (yyval.info).type = (yyvsp[0].info).type; }
#line 1739 "src/parser.y.c"
    break;

  case 79: /* SimpleExp: NumExp  */
#line 211 "src/parser.y"
           { (yyval.info).type = (yyvsp[0].info).type; }
#line 1745 "src/parser.y.c"
    break;

  case 80: /* SimpleExp: AcessMemAddr  */
#line 212 "src/parser.y"
                 {}
#line 1751 "src/parser.y.c"
    break;

  case 81: /* NumExp: V_INT  */
#line 216 "src/parser.y"
                 { (yyval.info).type = T_INT;  }
#line 1757 "src/parser.y.c"
    break;

  case 82: /* NumExp: V_REAL  */
#line 217 "src/parser.y"
                 { (yyval.info).type = T_REAL; }
#line 1763 "src/parser.y.c"
    break;

  case 83: /* NumExp: V_BOOL  */
#line 218 "src/parser.y"
                 { (yyval.info).type = T_BOOL; }
#line 1769 "src/parser.y.c"
    break;

  case 84: /* NumExp: V_CHAR  */
#line 219 "src/parser.y"
                 { (yyval.info).type = T_CHAR; }
#line 1775 "src/parser.y.c"
    break;

  case 85: /* NumExp: V_STRING  */
#line 220 "src/parser.y"
                 { (yyval.info).type = ARRAY; /*TODO*/}
#line 1781 "src/parser.y.c"
    break;

  case 86: /* Args: Exp ArgsAux  */
#line 224 "src/parser.y"
                    {}
#line 1787 "src/parser.y.c"
    break;

  case 87: /* Args: %empty  */
#line 225 "src/parser.y"
                      {}
#line 1793 "src/parser.y.c"
    break;

  case 88: /* ArgsAux: COMMA Args  */
#line 228 "src/parser.y"
                     {}
#line 1799 "src/parser.y.c"
    break;

  case 89: /* ArgsAux: %empty  */
#line 229 "src/parser.y"
                      {}
#line 1805 "src/parser.y.c"
    break;


#line 1809 "src/parser.y.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 232 "src/parser.y"

  
int main(int argc, char const *argv[])
{
    if (argc == 2) {
        yyin=fopen(argv[1],"r");
    }
    int result = yyparse();
    if (result == 0) {
        printf("parsing was successful\n");
    } else if (result == 1) {
        printf("parsing failed because of invalid input\n");
    } else if (result == 2) {
        printf("parsing failed due to memory exhaustion\n");
    } else {
        printf("other parsing error: %d\n", result);
    }
    if (argc == 2) {
        fclose(yyin);
    }
    return 0;
}
