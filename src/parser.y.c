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
#include <typedefs.h>
#include <symbolTable.h>

#define INT_TYPE 1
#define REAL_TYPE 2
#define BOOL_TYPE 3
#define CHAR_TYPE 4

int args_types[100];
int args_size;
int type_counter = 5;

extern int column_counter;

void yyerror(char* s) {
    fprintf(stderr, "%s at line-column: %d-%d\n", s , yylineno, column_counter);
    fprintf(stderr, "current token is: \"%s\"\n", yytext);
}

#line 94 "src/parser.y.c"

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
  YYSYMBOL_ATTRIB = 4,                     /* ATTRIB  */
  YYSYMBOL_SEMICOLON = 5,                  /* SEMICOLON  */
  YYSYMBOL_OR = 6,                         /* OR  */
  YYSYMBOL_AND = 7,                        /* AND  */
  YYSYMBOL_NEQ = 8,                        /* NEQ  */
  YYSYMBOL_EQ = 9,                         /* EQ  */
  YYSYMBOL_LESS = 10,                      /* LESS  */
  YYSYMBOL_GREATER = 11,                   /* GREATER  */
  YYSYMBOL_LEQ = 12,                       /* LEQ  */
  YYSYMBOL_GEQ = 13,                       /* GEQ  */
  YYSYMBOL_NOT = 14,                       /* NOT  */
  YYSYMBOL_PLUS = 15,                      /* PLUS  */
  YYSYMBOL_MINUS = 16,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 17,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 18,                    /* DIVIDE  */
  YYSYMBOL_MOD = 19,                       /* MOD  */
  YYSYMBOL_LPAR = 20,                      /* LPAR  */
  YYSYMBOL_RPAR = 21,                      /* RPAR  */
  YYSYMBOL_V_REAL = 22,                    /* V_REAL  */
  YYSYMBOL_V_BOOL = 23,                    /* V_BOOL  */
  YYSYMBOL_V_CHAR = 24,                    /* V_CHAR  */
  YYSYMBOL_V_STRING = 25,                  /* V_STRING  */
  YYSYMBOL_DOT = 26,                       /* DOT  */
  YYSYMBOL_LBRA = 27,                      /* LBRA  */
  YYSYMBOL_RBRA = 28,                      /* RBRA  */
  YYSYMBOL_TYPE = 29,                      /* TYPE  */
  YYSYMBOL_T_BOOL = 30,                    /* T_BOOL  */
  YYSYMBOL_T_INT = 31,                     /* T_INT  */
  YYSYMBOL_T_REAL = 32,                    /* T_REAL  */
  YYSYMBOL_T_CHAR = 33,                    /* T_CHAR  */
  YYSYMBOL_ARRAY = 34,                     /* ARRAY  */
  YYSYMBOL_OF = 35,                        /* OF  */
  YYSYMBOL_RECORD = 36,                    /* RECORD  */
  YYSYMBOL_END = 37,                       /* END  */
  YYSYMBOL_INTERVAL = 38,                  /* INTERVAL  */
  YYSYMBOL_COMMA = 39,                     /* COMMA  */
  YYSYMBOL_COLON = 40,                     /* COLON  */
  YYSYMBOL_PROCEDURE = 41,                 /* PROCEDURE  */
  YYSYMBOL_FUNCTION = 42,                  /* FUNCTION  */
  YYSYMBOL_VAR = 43,                       /* VAR  */
  YYSYMBOL_BEGIN_ = 44,                    /* BEGIN_  */
  YYSYMBOL_FOR = 45,                       /* FOR  */
  YYSYMBOL_TO = 46,                        /* TO  */
  YYSYMBOL_STEP = 47,                      /* STEP  */
  YYSYMBOL_LOOP = 48,                      /* LOOP  */
  YYSYMBOL_EXIT = 49,                      /* EXIT  */
  YYSYMBOL_WHEN = 50,                      /* WHEN  */
  YYSYMBOL_CONTINUE = 51,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 52,                     /* BREAK  */
  YYSYMBOL_IF = 53,                        /* IF  */
  YYSYMBOL_THEN = 54,                      /* THEN  */
  YYSYMBOL_ELSE = 55,                      /* ELSE  */
  YYSYMBOL_RETURN = 56,                    /* RETURN  */
  YYSYMBOL_REF = 57,                       /* REF  */
  YYSYMBOL_ID = 58,                        /* ID  */
  YYSYMBOL_V_INT = 59,                     /* V_INT  */
  YYSYMBOL_YYACCEPT = 60,                  /* $accept  */
  YYSYMBOL_Prog = 61,                      /* Prog  */
  YYSYMBOL_62_1 = 62,                      /* $@1  */
  YYSYMBOL_Decl = 63,                      /* Decl  */
  YYSYMBOL_Consts = 64,                    /* Consts  */
  YYSYMBOL_Vars = 65,                      /* Vars  */
  YYSYMBOL_Types = 66,                     /* Types  */
  YYSYMBOL_TypeDec = 67,                   /* TypeDec  */
  YYSYMBOL_Interval = 68,                  /* Interval  */
  YYSYMBOL_Fields = 69,                    /* Fields  */
  YYSYMBOL_SubProg = 70,                   /* SubProg  */
  YYSYMBOL_ProcedureDecl = 71,             /* ProcedureDecl  */
  YYSYMBOL_72_2 = 72,                      /* $@2  */
  YYSYMBOL_73_3 = 73,                      /* $@3  */
  YYSYMBOL_Parameters = 74,                /* Parameters  */
  YYSYMBOL_ParametersAux = 75,             /* ParametersAux  */
  YYSYMBOL_FunctionDecl = 76,              /* FunctionDecl  */
  YYSYMBOL_77_4 = 77,                      /* $@4  */
  YYSYMBOL_CmdBlock = 78,                  /* CmdBlock  */
  YYSYMBOL_Cmds = 79,                      /* Cmds  */
  YYSYMBOL_CmdAux = 80,                    /* CmdAux  */
  YYSYMBOL_AcessMemAddr = 81,              /* AcessMemAddr  */
  YYSYMBOL_CmdConditional = 82,            /* CmdConditional  */
  YYSYMBOL_CmdConditionalEnd = 83,         /* CmdConditionalEnd  */
  YYSYMBOL_CmdReturn = 84,                 /* CmdReturn  */
  YYSYMBOL_CmdReturnExp = 85,              /* CmdReturnExp  */
  YYSYMBOL_Exp = 86,                       /* Exp  */
  YYSYMBOL_Terms = 87,                     /* Terms  */
  YYSYMBOL_Comps = 88,                     /* Comps  */
  YYSYMBOL_Factor = 89,                    /* Factor  */
  YYSYMBOL_AriOp = 90,                     /* AriOp  */
  YYSYMBOL_AriOp2 = 91,                    /* AriOp2  */
  YYSYMBOL_Parenthesis = 92,               /* Parenthesis  */
  YYSYMBOL_UnaryExp = 93,                  /* UnaryExp  */
  YYSYMBOL_CastExp = 94,                   /* CastExp  */
  YYSYMBOL_SimpleExp = 95,                 /* SimpleExp  */
  YYSYMBOL_NumExp = 96,                    /* NumExp  */
  YYSYMBOL_Args = 97,                      /* Args  */
  YYSYMBOL_ArgsAux = 98                    /* ArgsAux  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   222

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  204

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   314


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
      55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    49,    49,    49,    57,    60,    72,    75,    76,    79,
      80,    83,    84,    85,    86,    87,    88,    89,    92,    93,
      96,    97,   100,   101,   102,   106,   106,   106,   114,   115,
     116,   120,   121,   125,   125,   132,   136,   137,   141,   146,
     147,   148,   149,   150,   157,   158,   163,   167,   170,   174,
     183,   192,   201,   202,   206,   212,   213,   217,   224,   228,
     235,   239,   252,   265,   274,   283,   292,   301,   305,   313,
     317,   326,   335,   339,   348,   357,   367,   371,   372,   376,
     383,   390,   394,   412,   430,   447,   464,   469,   470,   474,
     475,   476,   477,   478,   482,   483,   486,   487
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
  "\"end of file\"", "error", "\"invalid token\"", "CONST", "ATTRIB",
  "SEMICOLON", "OR", "AND", "NEQ", "EQ", "LESS", "GREATER", "LEQ", "GEQ",
  "NOT", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MOD", "LPAR", "RPAR",
  "V_REAL", "V_BOOL", "V_CHAR", "V_STRING", "DOT", "LBRA", "RBRA", "TYPE",
  "T_BOOL", "T_INT", "T_REAL", "T_CHAR", "ARRAY", "OF", "RECORD", "END",
  "INTERVAL", "COMMA", "COLON", "PROCEDURE", "FUNCTION", "VAR", "BEGIN_",
  "FOR", "TO", "STEP", "LOOP", "EXIT", "WHEN", "CONTINUE", "BREAK", "IF",
  "THEN", "ELSE", "RETURN", "REF", "ID", "V_INT", "$accept", "Prog", "$@1",
  "Decl", "Consts", "Vars", "Types", "TypeDec", "Interval", "Fields",
  "SubProg", "ProcedureDecl", "$@2", "$@3", "Parameters", "ParametersAux",
  "FunctionDecl", "$@4", "CmdBlock", "Cmds", "CmdAux", "AcessMemAddr",
  "CmdConditional", "CmdConditionalEnd", "CmdReturn", "CmdReturnExp",
  "Exp", "Terms", "Comps", "Factor", "AriOp", "AriOp2", "Parenthesis",
  "UnaryExp", "CastExp", "SimpleExp", "NumExp", "Args", "ArgsAux", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-135)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -135,    37,    40,  -135,   -18,    11,    20,    57,    52,  -135,
      39,    48,    42,    45,   104,   105,    53,    60,    52,    48,
      48,    54,    82,    82,    -8,  -135,  -135,  -135,  -135,  -135,
    -135,     6,    25,   114,  -135,   124,    83,    28,  -135,  -135,
    -135,  -135,  -135,   110,    72,    52,   108,  -135,  -135,    42,
      42,  -135,   101,   149,    88,  -135,  -135,    93,   141,   164,
    -135,  -135,  -135,    83,   137,  -135,  -135,   165,   166,   167,
     168,    21,    42,   127,    42,    40,    42,    42,    42,    42,
      42,    42,    42,    42,    54,    54,    54,    54,    54,    93,
      90,   104,    42,    -2,  -135,   184,  -135,   104,    42,  -135,
    -135,  -135,  -135,   169,   133,  -135,   189,  -135,   107,    61,
      61,    61,    61,  -135,     5,   174,  -135,    13,  -135,   114,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,    28,    28,  -135,
    -135,  -135,   192,    42,   161,   184,    11,  -135,   184,    42,
     159,   163,    20,   107,   143,   162,   182,  -135,  -135,  -135,
    -135,    42,  -135,  -135,  -135,    52,    14,  -135,   150,   176,
      30,    93,  -135,  -135,   185,   170,    93,   171,  -135,  -135,
      42,    11,  -135,   172,    42,   203,  -135,    93,   173,    93,
      12,  -135,    93,    15,   133,    11,   173,   107,  -135,  -135,
      42,  -135,    42,  -135,   204,  -135,  -135,    11,     4,  -135,
    -135,   208,  -135,  -135
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     6,     1,     0,     0,    10,     0,     8,     3,
       0,    24,     0,     0,     0,     0,     0,     0,     8,    24,
      24,     0,     0,     0,     0,    90,    91,    92,    93,    47,
      89,    88,     0,    58,    60,    67,    69,    72,    76,    77,
      81,    86,    87,     0,     0,     8,     0,    41,    42,     0,
      56,    39,     0,    36,     0,    40,    46,     0,     0,     0,
       4,    22,    23,    68,     0,    79,    80,     0,     0,     0,
       0,     0,    95,     0,     0,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    54,    55,    35,     0,     0,    11,
      12,    13,    14,     0,    21,    15,     0,    25,    30,     0,
       0,     0,     0,    78,    97,     0,    48,     0,     5,    57,
      59,    61,    62,    63,    64,    65,    66,    70,    71,    73,
      74,    75,     0,     0,     0,    45,     0,    37,    38,     0,
       0,     0,    10,    30,     0,     0,     0,    84,    82,    83,
      85,    95,    94,    50,    49,     8,     0,    44,    53,     0,
       0,     0,    17,     9,     0,     0,     0,     0,    96,     7,
       0,     0,    51,     0,     0,     0,    26,     0,    32,     0,
       0,    52,     0,    18,    21,     0,    32,    30,    28,    33,
       0,    16,     0,    20,     0,    29,    31,     0,     0,    19,
      27,     0,    43,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -135,  -135,  -135,  -135,   139,   -16,    73,   -86,    24,    33,
     156,  -135,  -135,  -135,  -134,    32,  -135,  -135,    -5,   -63,
    -135,    -9,  -135,  -135,  -135,  -135,   -11,   144,   142,    64,
     200,    98,   -15,  -135,   155,    62,  -135,    71,  -135
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     5,     6,    14,    11,   106,   159,   141,
      18,    19,   143,   185,   146,   188,    20,   197,    51,    52,
      53,    31,    55,   172,    56,    94,   114,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,   115,   152
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       9,    32,    60,   132,    76,    54,    21,    22,    23,   164,
      76,    76,    24,    71,    25,    26,    27,    28,    76,    76,
      76,    76,    67,    68,    69,    70,    72,    76,   134,    91,
      75,    76,    73,    74,   137,    90,    76,     3,    93,    95,
       7,   154,   113,     4,   151,    86,    87,    88,     8,    10,
      29,    30,   136,   196,   192,     8,    21,    22,    23,   190,
     170,    12,    24,   117,    25,    26,    27,    28,   174,    22,
      23,   129,   130,   131,    24,   175,    25,    26,    27,    28,
     178,   135,    54,    25,    26,    27,    28,   138,    54,    16,
      17,   186,    98,   189,   133,    13,   191,    15,    84,    85,
      29,    30,    64,    43,    25,    26,    27,    28,    72,    57,
      72,    58,    29,    30,    73,    74,    73,    74,    59,    29,
      30,    77,   156,    99,   100,   101,   102,   103,   160,   104,
      29,   158,    78,    79,    80,    81,    82,    83,    96,   169,
      29,    30,   121,   122,   123,   124,   125,   126,     8,    44,
      89,   105,    45,    46,    97,    47,    48,    49,    92,   180,
      50,   107,    29,   183,   144,   145,   181,    67,    68,    69,
      70,   147,   148,   149,   150,    61,    62,    65,    66,   198,
     194,   160,   127,   128,   108,   116,   109,   110,   111,   112,
      76,   140,   201,   202,   142,   153,   139,   155,   157,   161,
     162,   165,   166,   167,   173,   171,   176,   182,   184,   200,
     177,   179,   187,   203,   118,   163,   199,   193,   195,   120,
     119,    63,   168
};

static const yytype_uint8 yycheck[] =
{
       5,    12,    18,    89,     6,    14,    14,    15,    16,   143,
       6,     6,    20,    24,    22,    23,    24,    25,     6,     6,
       6,     6,    30,    31,    32,    33,    20,     6,    91,    45,
       5,     6,    26,    27,    97,    44,     6,     0,    49,    50,
      58,    28,    21,     3,    39,    17,    18,    19,    44,    29,
      58,    59,    54,   187,    39,    44,    14,    15,    16,    47,
      46,     4,    20,    74,    22,    23,    24,    25,    38,    15,
      16,    86,    87,    88,    20,   161,    22,    23,    24,    25,
     166,    92,    91,    22,    23,    24,    25,    98,    97,    41,
      42,   177,     4,   179,     4,    43,   182,    58,    15,    16,
      58,    59,    20,    58,    22,    23,    24,    25,    20,     4,
      20,    58,    58,    59,    26,    27,    26,    27,    58,    58,
      59,     7,   133,    30,    31,    32,    33,    34,   139,    36,
      58,   136,     8,     9,    10,    11,    12,    13,    37,   155,
      58,    59,    78,    79,    80,    81,    82,    83,    44,    45,
      40,    58,    48,    49,     5,    51,    52,    53,    50,   170,
      56,    20,    58,   174,    57,    58,   171,    30,    31,    32,
      33,   109,   110,   111,   112,    19,    20,    22,    23,   190,
     185,   192,    84,    85,    20,    58,    21,    21,    21,    21,
       6,    58,   197,   198,     5,    21,    27,     5,    37,    40,
      37,    58,    40,    21,    28,    55,    21,    35,     5,     5,
      40,    40,    39,     5,    75,   142,   192,   184,   186,    77,
      76,    21,   151
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    61,    62,     0,     3,    63,    64,    58,    44,    78,
      29,    66,     4,    43,    65,    58,    41,    42,    70,    71,
      76,    14,    15,    16,    20,    22,    23,    24,    25,    58,
      59,    81,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    58,    45,    48,    49,    51,    52,    53,
      56,    78,    79,    80,    81,    82,    84,     4,    58,    58,
      65,    70,    70,    90,    20,    94,    94,    30,    31,    32,
      33,    86,    20,    26,    27,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    15,    16,    17,    18,    19,    40,
      81,    65,    50,    86,    85,    86,    37,     5,     4,    30,
      31,    32,    33,    34,    36,    58,    67,    20,    20,    21,
      21,    21,    21,    21,    86,    97,    58,    86,    64,    87,
      88,    89,    89,    89,    89,    89,    89,    91,    91,    92,
      92,    92,    67,     4,    79,    86,    54,    79,    86,    27,
      58,    69,     5,    72,    57,    58,    74,    95,    95,    95,
      95,    39,    98,    21,    28,     5,    86,    37,    78,    68,
      86,    40,    37,    66,    74,    58,    40,    21,    97,    65,
      46,    55,    83,    28,    38,    67,    21,    40,    67,    40,
      86,    78,    35,    86,     5,    73,    67,    39,    75,    67,
      47,    67,    39,    69,    78,    75,    74,    77,    86,    68,
       5,    78,    78,     5
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    60,    62,    61,    63,    64,    64,    65,    65,    66,
      66,    67,    67,    67,    67,    67,    67,    67,    68,    68,
      69,    69,    70,    70,    70,    72,    73,    71,    74,    74,
      74,    75,    75,    77,    76,    78,    79,    79,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    81,    81,    81,
      81,    82,    83,    83,    84,    85,    85,    86,    86,    87,
      87,    88,    88,    88,    88,    88,    88,    88,    89,    89,
      90,    90,    90,    91,    91,    91,    91,    92,    92,    93,
      93,    93,    94,    94,    94,    94,    94,    95,    95,    96,
      96,    96,    96,    96,    97,    97,    98,    98
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     4,     6,     0,     6,     0,     6,
       0,     1,     1,     1,     1,     1,     6,     3,     3,     5,
       5,     0,     2,     2,     0,     0,     0,     9,     4,     5,
       0,     2,     0,     0,    10,     4,     1,     3,     3,     1,
       1,     1,     1,     9,     4,     3,     1,     1,     3,     4,
       4,     5,     2,     0,     2,     1,     0,     3,     1,     3,
       1,     3,     3,     3,     3,     3,     3,     1,     2,     1,
       3,     3,     1,     3,     3,     3,     1,     1,     3,     2,
       2,     1,     4,     4,     4,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     0,     2,     0
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
  case 2: /* $@1: %empty  */
#line 49 "src/parser.y"
    {
        printf("batata\n");
    }
#line 1322 "src/parser.y.c"
    break;

  case 3: /* Prog: $@1 Decl CmdBlock  */
#line 52 "src/parser.y"
                  {
        printf("cenoura\n");
    }
#line 1330 "src/parser.y.c"
    break;

  case 4: /* Decl: Consts Types SubProg Vars  */
#line 57 "src/parser.y"
                              {}
#line 1336 "src/parser.y.c"
    break;

  case 5: /* Consts: CONST ID ATTRIB Exp SEMICOLON Consts  */
#line 60 "src/parser.y"
                                         {
        ValueData data;
        switch ((yyvsp[-2].info).type) {
            case INT_TYPE:
                data.v_int = (yyvsp[-2].info).value.v_int;
                break;
        }
        printf("type: %d\n", (yyvsp[-2].info).type);
        printf("value: %d\n", data.v_int);
        addConstant((yyvsp[-4].info).name, (yyvsp[-2].info).type, data);

    }
#line 1353 "src/parser.y.c"
    break;

  case 7: /* Vars: VAR ID COLON TypeDec SEMICOLON Vars  */
#line 75 "src/parser.y"
                                        {}
#line 1359 "src/parser.y.c"
    break;

  case 9: /* Types: TYPE ID ATTRIB TypeDec SEMICOLON Types  */
#line 79 "src/parser.y"
                                           {}
#line 1365 "src/parser.y.c"
    break;

  case 11: /* TypeDec: T_BOOL  */
#line 83 "src/parser.y"
           {(yyval.info).type = BOOL_TYPE;}
#line 1371 "src/parser.y.c"
    break;

  case 12: /* TypeDec: T_INT  */
#line 84 "src/parser.y"
           {(yyval.info).type = INT_TYPE;}
#line 1377 "src/parser.y.c"
    break;

  case 13: /* TypeDec: T_REAL  */
#line 85 "src/parser.y"
           {(yyval.info).type = REAL_TYPE;}
#line 1383 "src/parser.y.c"
    break;

  case 14: /* TypeDec: T_CHAR  */
#line 86 "src/parser.y"
           {(yyval.info).type = CHAR_TYPE;}
#line 1389 "src/parser.y.c"
    break;

  case 15: /* TypeDec: ID  */
#line 87 "src/parser.y"
           {(yyval.info).type = 0 /*TODO*/;}
#line 1395 "src/parser.y.c"
    break;

  case 16: /* TypeDec: ARRAY LBRA Interval RBRA OF TypeDec  */
#line 88 "src/parser.y"
                                         {}
#line 1401 "src/parser.y.c"
    break;

  case 17: /* TypeDec: RECORD Fields END  */
#line 89 "src/parser.y"
                      {}
#line 1407 "src/parser.y.c"
    break;

  case 18: /* Interval: Exp INTERVAL Exp  */
#line 92 "src/parser.y"
                     {}
#line 1413 "src/parser.y.c"
    break;

  case 19: /* Interval: Exp INTERVAL Exp COMMA Interval  */
#line 93 "src/parser.y"
                                    {}
#line 1419 "src/parser.y.c"
    break;

  case 20: /* Fields: ID COLON TypeDec SEMICOLON Fields  */
#line 96 "src/parser.y"
                                      {}
#line 1425 "src/parser.y.c"
    break;

  case 21: /* Fields: %empty  */
#line 97 "src/parser.y"
                  {}
#line 1431 "src/parser.y.c"
    break;

  case 22: /* SubProg: ProcedureDecl SubProg  */
#line 100 "src/parser.y"
                          {}
#line 1437 "src/parser.y.c"
    break;

  case 23: /* SubProg: FunctionDecl SubProg  */
#line 101 "src/parser.y"
                         {}
#line 1443 "src/parser.y.c"
    break;

  case 24: /* SubProg: %empty  */
#line 102 "src/parser.y"
                  {}
#line 1449 "src/parser.y.c"
    break;

  case 25: /* $@2: %empty  */
#line 106 "src/parser.y"
                      {args_size=0;}
#line 1455 "src/parser.y.c"
    break;

  case 26: /* $@3: %empty  */
#line 106 "src/parser.y"
                                                     {
        // inserir na tabela
        // zerar argsize
        // 
    }
#line 1465 "src/parser.y.c"
    break;

  case 28: /* Parameters: ID COLON TypeDec ParametersAux  */
#line 114 "src/parser.y"
                                   { args_types[args_size++] = (yyvsp[-1].info).type; }
#line 1471 "src/parser.y.c"
    break;

  case 29: /* Parameters: REF ID COLON TypeDec ParametersAux  */
#line 115 "src/parser.y"
                                       { args_types[args_size++] = (yyvsp[-1].info).type; }
#line 1477 "src/parser.y.c"
    break;

  case 30: /* Parameters: %empty  */
#line 116 "src/parser.y"
                  {}
#line 1483 "src/parser.y.c"
    break;

  case 31: /* ParametersAux: COMMA Parameters  */
#line 120 "src/parser.y"
                     { }
#line 1489 "src/parser.y.c"
    break;

  case 32: /* ParametersAux: %empty  */
#line 121 "src/parser.y"
                  {}
#line 1495 "src/parser.y.c"
    break;

  case 33: /* $@4: %empty  */
#line 125 "src/parser.y"
                                                   {
        // criar registro na tabela para def
        // apagar os dados de parametros após salvar a função na tabela de simbolos
    }
#line 1504 "src/parser.y.c"
    break;

  case 35: /* CmdBlock: BEGIN_ Vars Cmds END  */
#line 132 "src/parser.y"
                         {}
#line 1510 "src/parser.y.c"
    break;

  case 36: /* Cmds: CmdAux  */
#line 136 "src/parser.y"
           {}
#line 1516 "src/parser.y.c"
    break;

  case 37: /* Cmds: CmdAux SEMICOLON Cmds  */
#line 137 "src/parser.y"
                          {}
#line 1522 "src/parser.y.c"
    break;

  case 38: /* CmdAux: AcessMemAddr ATTRIB Exp  */
#line 141 "src/parser.y"
                            {
        if ((yyvsp[-2].info).type != (yyvsp[0].info).type) {
            // TODO: ERROR
        }
    }
#line 1532 "src/parser.y.c"
    break;

  case 39: /* CmdAux: CmdBlock  */
#line 146 "src/parser.y"
             {}
#line 1538 "src/parser.y.c"
    break;

  case 40: /* CmdAux: CmdConditional  */
#line 147 "src/parser.y"
                   {}
#line 1544 "src/parser.y.c"
    break;

  case 41: /* CmdAux: CONTINUE  */
#line 148 "src/parser.y"
             {}
#line 1550 "src/parser.y.c"
    break;

  case 42: /* CmdAux: BREAK  */
#line 149 "src/parser.y"
          {}
#line 1556 "src/parser.y.c"
    break;

  case 43: /* CmdAux: FOR AcessMemAddr ATTRIB Exp TO Exp STEP Exp CmdBlock  */
#line 150 "src/parser.y"
                                                         {
        if ((yyvsp[-7].info).type == (yyvsp[-5].info).type && (yyvsp[-3].info).type == (yyvsp[-1].info).type && (yyvsp[-7].info).type == (yyvsp[-3].info).type) {
            // TODO
        } else {
            printf("ERROR");
        }
    }
#line 1568 "src/parser.y.c"
    break;

  case 44: /* CmdAux: LOOP Vars Cmds END  */
#line 157 "src/parser.y"
                       {}
#line 1574 "src/parser.y.c"
    break;

  case 45: /* CmdAux: EXIT WHEN Exp  */
#line 158 "src/parser.y"
                  { 
        if ((yyvsp[0].info).type != BOOL_TYPE) {
            // TODO: error
        }
    }
#line 1584 "src/parser.y.c"
    break;

  case 46: /* CmdAux: CmdReturn  */
#line 163 "src/parser.y"
              {}
#line 1590 "src/parser.y.c"
    break;

  case 47: /* AcessMemAddr: ID  */
#line 167 "src/parser.y"
       {
        //TODO
    }
#line 1598 "src/parser.y.c"
    break;

  case 48: /* AcessMemAddr: AcessMemAddr DOT ID  */
#line 170 "src/parser.y"
                        {
        //TODO  
    }
#line 1606 "src/parser.y.c"
    break;

  case 49: /* AcessMemAddr: AcessMemAddr LBRA Exp RBRA  */
#line 174 "src/parser.y"
                               {
        if ((yyvsp[-1].info).type == INT_TYPE) {
            (yyval.info).type = (yyvsp[-1].info).type;
        } else {
            printf("ERROR");
        }
        // garantir q AcessMemAddr é um array
        // acessar o tipo do conteudo array e atribuir esse tipo para AcessMemAddr
    }
#line 1620 "src/parser.y.c"
    break;

  case 50: /* AcessMemAddr: AcessMemAddr LPAR Args RPAR  */
#line 183 "src/parser.y"
                                {
    // TODO: comparar args com os parametros da tabela de simbolo do função AcessMemAddr 
    // desalocar a memoria de args após o uso
    // atribuir o tipo retornado pela função ao AcessMemAddr
    // {args_size=0;}
    }
#line 1631 "src/parser.y.c"
    break;

  case 51: /* CmdConditional: IF Exp THEN CmdBlock CmdConditionalEnd  */
#line 192 "src/parser.y"
                                           {
        if ((yyvsp[-3].info).type != BOOL_TYPE) {
            printf("ERROR");
            // TODO
        }
    }
#line 1642 "src/parser.y.c"
    break;

  case 52: /* CmdConditionalEnd: ELSE CmdBlock  */
#line 201 "src/parser.y"
                  {}
#line 1648 "src/parser.y.c"
    break;

  case 53: /* CmdConditionalEnd: %empty  */
#line 202 "src/parser.y"
                  {}
#line 1654 "src/parser.y.c"
    break;

  case 54: /* CmdReturn: RETURN CmdReturnExp  */
#line 206 "src/parser.y"
                        {
        // TODO busca na tabela para tipo compativel 
    }
#line 1662 "src/parser.y.c"
    break;

  case 55: /* CmdReturnExp: Exp  */
#line 212 "src/parser.y"
        { (yyval.info).type = (yyvsp[0].info).type; }
#line 1668 "src/parser.y.c"
    break;

  case 56: /* CmdReturnExp: %empty  */
#line 213 "src/parser.y"
                  { (yyval.info).type = -1;}
#line 1674 "src/parser.y.c"
    break;

  case 57: /* Exp: Exp OR Terms  */
#line 217 "src/parser.y"
                 {
        if ((yyvsp[-2].info).type == BOOL_TYPE && (yyvsp[0].info).type == BOOL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1686 "src/parser.y.c"
    break;

  case 58: /* Exp: Terms  */
#line 224 "src/parser.y"
          { (yyval.info).type = (yyvsp[0].info).type; }
#line 1692 "src/parser.y.c"
    break;

  case 59: /* Terms: Terms AND Comps  */
#line 228 "src/parser.y"
                    {
        if ((yyvsp[-2].info).type == BOOL_TYPE && (yyvsp[0].info).type == BOOL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1704 "src/parser.y.c"
    break;

  case 60: /* Terms: Comps  */
#line 235 "src/parser.y"
          { (yyval.info).type = (yyvsp[0].info).type; }
#line 1710 "src/parser.y.c"
    break;

  case 61: /* Comps: Factor NEQ Factor  */
#line 239 "src/parser.y"
                      {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == BOOL_TYPE && (yyvsp[0].info).type == BOOL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == CHAR_TYPE && (yyvsp[0].info).type == CHAR_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1728 "src/parser.y.c"
    break;

  case 62: /* Comps: Factor EQ Factor  */
#line 252 "src/parser.y"
                      {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == BOOL_TYPE && (yyvsp[0].info).type == BOOL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == CHAR_TYPE && (yyvsp[0].info).type == CHAR_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1746 "src/parser.y.c"
    break;

  case 63: /* Comps: Factor LESS Factor  */
#line 265 "src/parser.y"
                       {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1760 "src/parser.y.c"
    break;

  case 64: /* Comps: Factor GREATER Factor  */
#line 274 "src/parser.y"
                           {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1774 "src/parser.y.c"
    break;

  case 65: /* Comps: Factor LEQ Factor  */
#line 283 "src/parser.y"
                      {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1788 "src/parser.y.c"
    break;

  case 66: /* Comps: Factor GEQ Factor  */
#line 292 "src/parser.y"
                       {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1802 "src/parser.y.c"
    break;

  case 67: /* Comps: Factor  */
#line 301 "src/parser.y"
            { (yyval.info).type = (yyvsp[0].info).type; }
#line 1808 "src/parser.y.c"
    break;

  case 68: /* Factor: NOT AriOp  */
#line 305 "src/parser.y"
              {
        if ((yyvsp[0].info).type == BOOL_TYPE ) {
            (yyval.info).type = BOOL_TYPE;
            (yyval.info).value.v_bool = !(yyvsp[0].info).value.v_bool;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1821 "src/parser.y.c"
    break;

  case 69: /* Factor: AriOp  */
#line 313 "src/parser.y"
          { (yyval.info).type = (yyvsp[0].info).type; }
#line 1827 "src/parser.y.c"
    break;

  case 70: /* AriOp: AriOp PLUS AriOp2  */
#line 317 "src/parser.y"
                      {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = INT_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1841 "src/parser.y.c"
    break;

  case 71: /* AriOp: AriOp MINUS AriOp2  */
#line 326 "src/parser.y"
                       {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = INT_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1855 "src/parser.y.c"
    break;

  case 72: /* AriOp: AriOp2  */
#line 335 "src/parser.y"
           { (yyval.info).type = (yyvsp[0].info).type; }
#line 1861 "src/parser.y.c"
    break;

  case 73: /* AriOp2: AriOp2 MULTIPLY Parenthesis  */
#line 339 "src/parser.y"
                                {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = INT_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1875 "src/parser.y.c"
    break;

  case 74: /* AriOp2: AriOp2 DIVIDE Parenthesis  */
#line 348 "src/parser.y"
                              {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = INT_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1889 "src/parser.y.c"
    break;

  case 75: /* AriOp2: AriOp2 MOD Parenthesis  */
#line 357 "src/parser.y"
                           {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = INT_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            // TODO
            printf("TODO. \n");
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1904 "src/parser.y.c"
    break;

  case 76: /* AriOp2: Parenthesis  */
#line 367 "src/parser.y"
                { (yyval.info).type = (yyvsp[0].info).type; }
#line 1910 "src/parser.y.c"
    break;

  case 77: /* Parenthesis: UnaryExp  */
#line 371 "src/parser.y"
             { (yyval.info).type = (yyvsp[0].info).type; }
#line 1916 "src/parser.y.c"
    break;

  case 78: /* Parenthesis: LPAR Exp RPAR  */
#line 372 "src/parser.y"
                  { (yyval.info).type = (yyvsp[-1].info).type; }
#line 1922 "src/parser.y.c"
    break;

  case 79: /* UnaryExp: PLUS CastExp  */
#line 376 "src/parser.y"
                 { 
        if ((yyvsp[0].info).type == INT_TYPE || (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = (yyvsp[0].info).type;
        } else { 
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1934 "src/parser.y.c"
    break;

  case 80: /* UnaryExp: MINUS CastExp  */
#line 383 "src/parser.y"
                  { 
        if ((yyvsp[0].info).type == INT_TYPE || (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = (yyvsp[0].info).type;
        } else { 
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1946 "src/parser.y.c"
    break;

  case 81: /* UnaryExp: CastExp  */
#line 390 "src/parser.y"
            { (yyval.info).type = (yyvsp[0].info).type; }
#line 1952 "src/parser.y.c"
    break;

  case 82: /* CastExp: LPAR T_INT RPAR SimpleExp  */
#line 394 "src/parser.y"
                                    {
        if ((yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = INT_TYPE;
            (yyval.info).value.v_int = (yyvsp[0].info).value.v_int;
        }
        if ((yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = INT_TYPE;
            (yyval.info).value.v_int = (yyvsp[0].info).value.v_real;
        }
        if ((yyvsp[0].info).type == BOOL_TYPE) {
            (yyval.info).type = INT_TYPE;
            (yyval.info).value.v_int = (yyvsp[0].info).value.v_bool;
        }
        if ((yyvsp[0].info).type == CHAR_TYPE) {
            (yyval.info).type = INT_TYPE;
            (yyval.info).value.v_int = (yyvsp[0].info).value.v_char;
        }
    }
#line 1975 "src/parser.y.c"
    break;

  case 83: /* CastExp: LPAR T_REAL RPAR SimpleExp  */
#line 412 "src/parser.y"
                                    {
        if ((yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = REAL_TYPE;
            (yyval.info).value.v_real = (yyvsp[0].info).value.v_int;
        }
        if ((yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = REAL_TYPE;
            (yyval.info).value.v_real = (yyvsp[0].info).value.v_real;
        }
        if ((yyvsp[0].info).type == BOOL_TYPE) {
            (yyval.info).type = REAL_TYPE;
            (yyval.info).value.v_real = (yyvsp[0].info).value.v_bool;
        }
        if ((yyvsp[0].info).type == CHAR_TYPE) {
            (yyval.info).type = REAL_TYPE;
            (yyval.info).value.v_real = (yyvsp[0].info).value.v_char;
        }
}
#line 1998 "src/parser.y.c"
    break;

  case 84: /* CastExp: LPAR T_BOOL RPAR SimpleExp  */
#line 430 "src/parser.y"
                                    {
        if ((yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = BOOL_TYPE;
            (yyval.info).value.v_bool = (yyvsp[0].info).value.v_int > 0;
        }
        if ((yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
            (yyval.info).value.v_bool = (yyvsp[0].info).value.v_real > 0.0;
        }
        if ((yyvsp[0].info).type == BOOL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
            (yyval.info).value.v_bool = (yyvsp[0].info).value.v_bool;
        }
        if ((yyvsp[0].info).type == CHAR_TYPE) {
            printf("char para bool pode não!\n");
        }
}
#line 2020 "src/parser.y.c"
    break;

  case 85: /* CastExp: LPAR T_CHAR RPAR SimpleExp  */
#line 447 "src/parser.y"
                                    {
    if ((yyvsp[0].info).type == INT_TYPE) {
        (yyval.info).type = CHAR_TYPE;
        // TODO If
        (yyval.info).value.v_char = (yyvsp[0].info).value.v_int;
    }
    if ((yyvsp[0].info).type == REAL_TYPE) {
        printf("real para char pode não!\n");
    }
    if ((yyvsp[0].info).type == BOOL_TYPE) {
        printf("bool para char pode não!\n");
    }
    if ((yyvsp[0].info).type == CHAR_TYPE) {
        (yyval.info).type = CHAR_TYPE;
        (yyval.info).value.v_char = (yyvsp[0].info).value.v_char;
    }
}
#line 2042 "src/parser.y.c"
    break;

  case 86: /* CastExp: SimpleExp  */
#line 464 "src/parser.y"
                                    {
    (yyval.info).type = (yyvsp[0].info).type;
}
#line 2050 "src/parser.y.c"
    break;

  case 87: /* SimpleExp: NumExp  */
#line 469 "src/parser.y"
           { (yyval.info).type = (yyvsp[0].info).type; }
#line 2056 "src/parser.y.c"
    break;

  case 88: /* SimpleExp: AcessMemAddr  */
#line 470 "src/parser.y"
                 { (yyval.info).type = (yyvsp[0].info).type; }
#line 2062 "src/parser.y.c"
    break;

  case 89: /* NumExp: V_INT  */
#line 474 "src/parser.y"
             { (yyval.info).type = INT_TYPE; (yyval.info).value.v_int = (yyvsp[0].info).value.v_int; }
#line 2068 "src/parser.y.c"
    break;

  case 90: /* NumExp: V_REAL  */
#line 475 "src/parser.y"
             { (yyval.info).type = REAL_TYPE; }
#line 2074 "src/parser.y.c"
    break;

  case 91: /* NumExp: V_BOOL  */
#line 476 "src/parser.y"
             { (yyval.info).type = BOOL_TYPE; }
#line 2080 "src/parser.y.c"
    break;

  case 92: /* NumExp: V_CHAR  */
#line 477 "src/parser.y"
             { (yyval.info).type = CHAR_TYPE; }
#line 2086 "src/parser.y.c"
    break;

  case 93: /* NumExp: V_STRING  */
#line 478 "src/parser.y"
             { (yyval.info).type = ARRAY; /*TODO*/}
#line 2092 "src/parser.y.c"
    break;

  case 94: /* Args: Exp ArgsAux  */
#line 482 "src/parser.y"
                {}
#line 2098 "src/parser.y.c"
    break;

  case 95: /* Args: %empty  */
#line 483 "src/parser.y"
                  {}
#line 2104 "src/parser.y.c"
    break;

  case 96: /* ArgsAux: COMMA Args  */
#line 486 "src/parser.y"
                     {}
#line 2110 "src/parser.y.c"
    break;

  case 97: /* ArgsAux: %empty  */
#line 487 "src/parser.y"
                  {}
#line 2116 "src/parser.y.c"
    break;


#line 2120 "src/parser.y.c"

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

#line 490 "src/parser.y"

  
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
