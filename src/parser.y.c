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

#define INT_TYPE 1
#define REAL_TYPE 2
#define BOOL_TYPE 3
#define CHAR_TYPE 4

int args_types[100];
int args_size;
int type_counter = 5;

Node* createNode(int identifier, Node* children) {
    // TODO
    return NULL;
}

extern int column_counter;

void yyerror(char* s) {
    fprintf(stderr, "%s at line-column: %d-%d\n", s , yylineno, column_counter);
    fprintf(stderr, "current token is: \"%s\"\n", yytext);
}

#line 98 "src/parser.y.c"

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
  YYSYMBOL_REF = 59,                       /* REF  */
  YYSYMBOL_YYACCEPT = 60,                  /* $accept  */
  YYSYMBOL_Prog = 61,                      /* Prog  */
  YYSYMBOL_Decl = 62,                      /* Decl  */
  YYSYMBOL_Consts = 63,                    /* Consts  */
  YYSYMBOL_Vars = 64,                      /* Vars  */
  YYSYMBOL_Types = 65,                     /* Types  */
  YYSYMBOL_TypeDec = 66,                   /* TypeDec  */
  YYSYMBOL_Interval = 67,                  /* Interval  */
  YYSYMBOL_Fields = 68,                    /* Fields  */
  YYSYMBOL_SubProg = 69,                   /* SubProg  */
  YYSYMBOL_ProcedureDecl = 70,             /* ProcedureDecl  */
  YYSYMBOL_71_1 = 71,                      /* $@1  */
  YYSYMBOL_72_2 = 72,                      /* $@2  */
  YYSYMBOL_Parameters = 73,                /* Parameters  */
  YYSYMBOL_ParametersAux = 74,             /* ParametersAux  */
  YYSYMBOL_FunctionDecl = 75,              /* FunctionDecl  */
  YYSYMBOL_76_3 = 76,                      /* $@3  */
  YYSYMBOL_CmdBlock = 77,                  /* CmdBlock  */
  YYSYMBOL_Cmds = 78,                      /* Cmds  */
  YYSYMBOL_CmdAux = 79,                    /* CmdAux  */
  YYSYMBOL_AcessMemAddr = 80,              /* AcessMemAddr  */
  YYSYMBOL_CmdConditional = 81,            /* CmdConditional  */
  YYSYMBOL_CmdConditionalEnd = 82,         /* CmdConditionalEnd  */
  YYSYMBOL_CmdReturn = 83,                 /* CmdReturn  */
  YYSYMBOL_CmdReturnExp = 84,              /* CmdReturnExp  */
  YYSYMBOL_Exp = 85,                       /* Exp  */
  YYSYMBOL_Terms = 86,                     /* Terms  */
  YYSYMBOL_Comps = 87,                     /* Comps  */
  YYSYMBOL_Factor = 88,                    /* Factor  */
  YYSYMBOL_AriOp = 89,                     /* AriOp  */
  YYSYMBOL_AriOp2 = 90,                    /* AriOp2  */
  YYSYMBOL_Parenthesis = 91,               /* Parenthesis  */
  YYSYMBOL_UnaryExp = 92,                  /* UnaryExp  */
  YYSYMBOL_CastExp = 93,                   /* CastExp  */
  YYSYMBOL_SimpleExp = 94,                 /* SimpleExp  */
  YYSYMBOL_NumExp = 95,                    /* NumExp  */
  YYSYMBOL_Args = 96,                      /* Args  */
  YYSYMBOL_ArgsAux = 97                    /* ArgsAux  */
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
#define YYLAST   224

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  203

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
       0,    52,    52,    55,    58,    61,    64,    65,    68,    69,
      72,    73,    74,    75,    76,    77,    78,    81,    82,    85,
      86,    89,    90,    91,    95,    95,    95,   103,   104,   105,
     109,   110,   114,   114,   121,   125,   126,   130,   135,   136,
     137,   138,   139,   146,   147,   152,   156,   159,   163,   172,
     181,   190,   191,   195,   201,   202,   206,   213,   217,   224,
     228,   241,   254,   263,   272,   281,   290,   294,   302,   306,
     315,   324,   328,   337,   346,   356,   360,   361,   365,   372,
     379,   383,   401,   419,   436,   453,   458,   459,   463,   464,
     465,   466,   467,   471,   472,   475,   476
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
  "CONTINUE", "BREAK", "IF", "THEN", "ELSE", "RETURN", "REF", "$accept",
  "Prog", "Decl", "Consts", "Vars", "Types", "TypeDec", "Interval",
  "Fields", "SubProg", "ProcedureDecl", "$@1", "$@2", "Parameters",
  "ParametersAux", "FunctionDecl", "$@3", "CmdBlock", "Cmds", "CmdAux",
  "AcessMemAddr", "CmdConditional", "CmdConditionalEnd", "CmdReturn",
  "CmdReturnExp", "Exp", "Terms", "Comps", "Factor", "AriOp", "AriOp2",
  "Parenthesis", "UnaryExp", "CastExp", "SimpleExp", "NumExp", "Args",
  "ArgsAux", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-138)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      27,     6,    38,    -5,    13,    58,  -138,    25,  -138,    83,
      37,   118,    91,     3,    95,   100,   120,    25,    37,    37,
    -138,   132,   147,   147,    82,  -138,  -138,  -138,  -138,  -138,
      -8,    70,   117,  -138,   186,    68,    54,  -138,  -138,  -138,
    -138,  -138,    84,   123,    25,    76,  -138,  -138,   118,   118,
    -138,    92,   131,    14,  -138,  -138,    33,   109,   119,  -138,
    -138,  -138,    68,    78,  -138,  -138,   125,   128,   130,   139,
       9,   118,   142,   118,    27,   118,   118,   118,   118,   118,
     118,   118,   118,   132,   132,   132,   132,   132,    33,    73,
       3,   118,     4,  -138,   155,  -138,     3,   118,  -138,  -138,
    -138,  -138,  -138,   134,   150,   160,  -138,     0,   161,   161,
     161,   161,  -138,     5,   153,  -138,    15,  -138,   117,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,    54,    54,  -138,  -138,
    -138,   163,   118,   137,   155,    -5,  -138,   155,   118,   135,
     140,    13,     0,   136,   179,   167,  -138,  -138,  -138,  -138,
     118,  -138,  -138,  -138,    25,     7,  -138,   133,   162,    22,
      33,  -138,  -138,   169,    33,   165,   166,  -138,  -138,   118,
      -5,  -138,   172,   118,   204,  -138,   170,    33,    33,     2,
    -138,    33,    11,   150,    -5,     0,  -138,   170,  -138,   118,
    -138,   118,  -138,   206,  -138,  -138,    -5,     1,  -138,  -138,
     207,  -138,  -138
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     0,     9,     0,     1,     7,     2,     0,
      23,     0,     0,     0,     0,     0,     0,     7,    23,    23,
      46,     0,     0,     0,     0,    88,    89,    90,    91,    92,
      87,     0,    57,    59,    66,    68,    71,    75,    76,    80,
      85,    86,     0,     0,     7,     0,    40,    41,     0,    55,
      38,     0,    35,     0,    39,    45,     0,     0,     0,     3,
      21,    22,    67,     0,    78,    79,     0,     0,     0,     0,
       0,    94,     0,     0,     5,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    53,    54,    34,     0,     0,    14,    10,
      11,    12,    13,     0,    20,     0,    24,    29,     0,     0,
       0,     0,    77,    96,     0,    47,     0,     4,    56,    58,
      60,    61,    62,    63,    64,    65,    69,    70,    72,    73,
      74,     0,     0,     0,    44,     0,    36,    37,     0,     0,
       0,     9,    29,     0,     0,     0,    83,    81,    82,    84,
      94,    93,    49,    48,     7,     0,    43,    52,     0,     0,
       0,    16,     8,     0,     0,     0,     0,    95,     6,     0,
       0,    50,     0,     0,     0,    25,    31,     0,     0,     0,
      51,     0,    17,    20,     0,    29,    27,    31,    32,     0,
      15,     0,    19,     0,    30,    28,     0,     0,    18,    26,
       0,    42,    33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -138,  -138,  -138,   141,   -16,    75,   -85,    23,    34,    72,
    -138,  -138,  -138,  -137,    31,  -138,  -138,    -3,   -73,  -138,
      -7,  -138,  -138,  -138,  -138,    -9,   144,   145,   124,   199,
      35,   -53,  -138,    98,   -84,  -138,    74,  -138
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    13,    10,   105,   158,   140,    17,
      18,   142,   184,   145,   186,    19,   196,    50,    51,    52,
      30,    54,   171,    55,    93,   113,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,   114,   151
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       8,    59,    31,   131,   143,   163,    53,    20,    75,    75,
       5,    75,    75,    71,    75,    70,    75,   133,    75,    97,
      72,    73,    75,   136,   146,   147,   148,   149,    90,    75,
       1,   112,   128,   129,   130,    71,    89,    98,     6,    92,
      94,     7,    72,    73,     9,   153,   150,     7,   194,     7,
      43,   189,   191,    44,    45,   169,    46,    47,    48,   144,
     135,    49,   173,    11,   116,    99,   100,   101,   102,   103,
      12,   104,    85,    86,    87,   174,    74,    75,   132,   176,
      15,    16,   134,    53,    83,    84,    20,    14,   137,    53,
      60,    61,   187,   188,    71,    42,   190,    21,    22,    23,
      56,    72,    73,    24,    57,    25,    26,    27,    28,    29,
      66,    67,    68,    69,    66,    67,    68,    69,   126,   127,
      64,    65,    20,   155,    58,    76,    88,    20,    91,   159,
     106,    95,   157,    21,    22,    23,    20,    96,   168,    24,
     107,    25,    26,    27,    28,    29,   115,   108,    22,    23,
     109,    20,   110,    24,   139,    25,    26,    27,    28,    29,
     179,   111,    75,   138,   182,    20,   141,   180,    63,   154,
      25,    26,    27,    28,    29,   152,   156,   160,   164,   161,
     197,   193,   159,   165,    25,    26,    27,    28,    29,   166,
     170,   175,   172,   200,   201,    77,    78,    79,    80,    81,
      82,   120,   121,   122,   123,   124,   125,   177,   178,   181,
     183,   185,   199,   202,   198,   117,   162,   192,   195,   118,
      62,   119,     0,     0,   167
};

static const yytype_int16 yycheck[] =
{
       3,    17,    11,    88,     4,   142,    13,     4,     7,     7,
       4,     7,     7,    21,     7,    24,     7,    90,     7,     5,
      28,    29,     7,    96,   108,   109,   110,   111,    44,     7,
       3,    22,    85,    86,    87,    21,    43,     4,     0,    48,
      49,    46,    28,    29,    31,    30,    41,    46,   185,    46,
      47,    49,    41,    50,    51,    48,    53,    54,    55,    59,
      56,    58,    40,     5,    73,    32,    33,    34,    35,    36,
      45,    38,    18,    19,    20,   160,     6,     7,     5,   164,
      43,    44,    91,    90,    16,    17,     4,     4,    97,    96,
      18,    19,   177,   178,    21,     4,   181,    15,    16,    17,
       5,    28,    29,    21,     4,    23,    24,    25,    26,    27,
      32,    33,    34,    35,    32,    33,    34,    35,    83,    84,
      22,    23,     4,   132,     4,     8,    42,     4,    52,   138,
      21,    39,   135,    15,    16,    17,     4,     6,   154,    21,
      21,    23,    24,    25,    26,    27,     4,    22,    16,    17,
      22,     4,    22,    21,     4,    23,    24,    25,    26,    27,
     169,    22,     7,    29,   173,     4,     6,   170,    21,     6,
      23,    24,    25,    26,    27,    22,    39,    42,    42,    39,
     189,   184,   191,     4,    23,    24,    25,    26,    27,    22,
      57,    22,    30,   196,   197,     9,    10,    11,    12,    13,
      14,    77,    78,    79,    80,    81,    82,    42,    42,    37,
       6,    41,     6,     6,   191,    74,   141,   183,   187,    75,
      21,    76,    -1,    -1,   150
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    61,    62,    63,     4,     0,    46,    77,    31,
      65,     5,    45,    64,     4,    43,    44,    69,    70,    75,
       4,    15,    16,    17,    21,    23,    24,    25,    26,    27,
      80,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,     4,    47,    50,    51,    53,    54,    55,    58,
      77,    78,    79,    80,    81,    83,     5,     4,     4,    64,
      69,    69,    89,    21,    93,    93,    32,    33,    34,    35,
      85,    21,    28,    29,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    16,    17,    18,    19,    20,    42,    80,
      64,    52,    85,    84,    85,    39,     6,     5,     4,    32,
      33,    34,    35,    36,    38,    66,    21,    21,    22,    22,
      22,    22,    22,    85,    96,     4,    85,    63,    86,    87,
      88,    88,    88,    88,    88,    88,    90,    90,    91,    91,
      91,    66,     5,    78,    85,    56,    78,    85,    29,     4,
      68,     6,    71,     4,    59,    73,    94,    94,    94,    94,
      41,    97,    22,    30,     6,    85,    39,    77,    67,    85,
      42,    39,    65,    73,    42,     4,    22,    96,    64,    48,
      57,    82,    30,    40,    66,    22,    66,    42,    42,    85,
      77,    37,    85,     6,    72,    41,    74,    66,    66,    49,
      66,    41,    68,    77,    73,    74,    76,    85,    67,     6,
      77,    77,     6
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    60,    61,    62,    63,    63,    64,    64,    65,    65,
      66,    66,    66,    66,    66,    66,    66,    67,    67,    68,
      68,    69,    69,    69,    71,    72,    70,    73,    73,    73,
      74,    74,    76,    75,    77,    78,    78,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    80,    80,    80,    80,
      81,    82,    82,    83,    84,    84,    85,    85,    86,    86,
      87,    87,    87,    87,    87,    87,    87,    88,    88,    89,
      89,    89,    90,    90,    90,    90,    91,    91,    92,    92,
      92,    93,    93,    93,    93,    93,    94,    94,    95,    95,
      95,    95,    95,    96,    96,    97,    97
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     6,     0,     6,     0,     6,     0,
       1,     1,     1,     1,     1,     6,     3,     3,     5,     5,
       0,     2,     2,     0,     0,     0,     9,     4,     5,     0,
       2,     0,     0,    10,     4,     1,     3,     3,     1,     1,
       1,     1,     9,     4,     3,     1,     1,     3,     4,     4,
       5,     2,     0,     2,     1,     0,     3,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     1,     2,     1,     3,
       3,     1,     3,     3,     3,     1,     1,     3,     2,     2,
       1,     4,     4,     4,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     0,     2,     0
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
#line 52 "src/parser.y"
                  {}
#line 1324 "src/parser.y.c"
    break;

  case 3: /* Decl: Consts Types SubProg Vars  */
#line 55 "src/parser.y"
                              {}
#line 1330 "src/parser.y.c"
    break;

  case 4: /* Consts: CONST ID ATTRIB Exp SEMICOLON Consts  */
#line 58 "src/parser.y"
                                         {

    }
#line 1338 "src/parser.y.c"
    break;

  case 6: /* Vars: VAR ID COLON TypeDec SEMICOLON Vars  */
#line 64 "src/parser.y"
                                        {}
#line 1344 "src/parser.y.c"
    break;

  case 8: /* Types: TYPE ID ATTRIB TypeDec SEMICOLON Types  */
#line 68 "src/parser.y"
                                           {}
#line 1350 "src/parser.y.c"
    break;

  case 10: /* TypeDec: T_BOOL  */
#line 72 "src/parser.y"
           {(yyval.info).type = BOOL_TYPE;}
#line 1356 "src/parser.y.c"
    break;

  case 11: /* TypeDec: T_INT  */
#line 73 "src/parser.y"
           {(yyval.info).type = INT_TYPE;}
#line 1362 "src/parser.y.c"
    break;

  case 12: /* TypeDec: T_REAL  */
#line 74 "src/parser.y"
           {(yyval.info).type = REAL_TYPE;}
#line 1368 "src/parser.y.c"
    break;

  case 13: /* TypeDec: T_CHAR  */
#line 75 "src/parser.y"
           {(yyval.info).type = CHAR_TYPE;}
#line 1374 "src/parser.y.c"
    break;

  case 14: /* TypeDec: ID  */
#line 76 "src/parser.y"
           {(yyval.info).type = 0 /*TODO*/;}
#line 1380 "src/parser.y.c"
    break;

  case 15: /* TypeDec: ARRAY LBRA Interval RBRA OF TypeDec  */
#line 77 "src/parser.y"
                                         {}
#line 1386 "src/parser.y.c"
    break;

  case 16: /* TypeDec: RECORD Fields END  */
#line 78 "src/parser.y"
                      {}
#line 1392 "src/parser.y.c"
    break;

  case 17: /* Interval: Exp INTERVAL Exp  */
#line 81 "src/parser.y"
                     {}
#line 1398 "src/parser.y.c"
    break;

  case 18: /* Interval: Exp INTERVAL Exp COMMA Interval  */
#line 82 "src/parser.y"
                                    {}
#line 1404 "src/parser.y.c"
    break;

  case 19: /* Fields: ID COLON TypeDec SEMICOLON Fields  */
#line 85 "src/parser.y"
                                      {}
#line 1410 "src/parser.y.c"
    break;

  case 20: /* Fields: %empty  */
#line 86 "src/parser.y"
                  {}
#line 1416 "src/parser.y.c"
    break;

  case 21: /* SubProg: ProcedureDecl SubProg  */
#line 89 "src/parser.y"
                          {}
#line 1422 "src/parser.y.c"
    break;

  case 22: /* SubProg: FunctionDecl SubProg  */
#line 90 "src/parser.y"
                         {}
#line 1428 "src/parser.y.c"
    break;

  case 23: /* SubProg: %empty  */
#line 91 "src/parser.y"
                  {}
#line 1434 "src/parser.y.c"
    break;

  case 24: /* $@1: %empty  */
#line 95 "src/parser.y"
                      {args_size=0;}
#line 1440 "src/parser.y.c"
    break;

  case 25: /* $@2: %empty  */
#line 95 "src/parser.y"
                                                     {
        // inserir na tabela
        // zerar argsize
        // 
    }
#line 1450 "src/parser.y.c"
    break;

  case 27: /* Parameters: ID COLON TypeDec ParametersAux  */
#line 103 "src/parser.y"
                                   { args_types[args_size++] = (yyvsp[-1].info).type; }
#line 1456 "src/parser.y.c"
    break;

  case 28: /* Parameters: REF ID COLON TypeDec ParametersAux  */
#line 104 "src/parser.y"
                                       { args_types[args_size++] = (yyvsp[-1].info).type; }
#line 1462 "src/parser.y.c"
    break;

  case 29: /* Parameters: %empty  */
#line 105 "src/parser.y"
                  {}
#line 1468 "src/parser.y.c"
    break;

  case 30: /* ParametersAux: COMMA Parameters  */
#line 109 "src/parser.y"
                     { }
#line 1474 "src/parser.y.c"
    break;

  case 31: /* ParametersAux: %empty  */
#line 110 "src/parser.y"
                  {}
#line 1480 "src/parser.y.c"
    break;

  case 32: /* $@3: %empty  */
#line 114 "src/parser.y"
                                                   {
        // criar registro na tabela para def
        // apagar os dados de parametros após salvar a função na tabela de simbolos
    }
#line 1489 "src/parser.y.c"
    break;

  case 34: /* CmdBlock: BEGIN_ Vars Cmds END  */
#line 121 "src/parser.y"
                         {}
#line 1495 "src/parser.y.c"
    break;

  case 35: /* Cmds: CmdAux  */
#line 125 "src/parser.y"
           {}
#line 1501 "src/parser.y.c"
    break;

  case 36: /* Cmds: CmdAux SEMICOLON Cmds  */
#line 126 "src/parser.y"
                          {}
#line 1507 "src/parser.y.c"
    break;

  case 37: /* CmdAux: AcessMemAddr ATTRIB Exp  */
#line 130 "src/parser.y"
                            {
        if ((yyvsp[-2].info).type != (yyvsp[0].info).type) {
            // TODO: ERROR
        }
    }
#line 1517 "src/parser.y.c"
    break;

  case 38: /* CmdAux: CmdBlock  */
#line 135 "src/parser.y"
             {}
#line 1523 "src/parser.y.c"
    break;

  case 39: /* CmdAux: CmdConditional  */
#line 136 "src/parser.y"
                   {}
#line 1529 "src/parser.y.c"
    break;

  case 40: /* CmdAux: CONTINUE  */
#line 137 "src/parser.y"
             {}
#line 1535 "src/parser.y.c"
    break;

  case 41: /* CmdAux: BREAK  */
#line 138 "src/parser.y"
          {}
#line 1541 "src/parser.y.c"
    break;

  case 42: /* CmdAux: FOR AcessMemAddr ATTRIB Exp TO Exp STEP Exp CmdBlock  */
#line 139 "src/parser.y"
                                                         {
        if ((yyvsp[-7].info).type == (yyvsp[-5].info).type && (yyvsp[-3].info).type == (yyvsp[-1].info).type && (yyvsp[-7].info).type == (yyvsp[-3].info).type) {
            // TODO
        } else {
            printf("ERROR");
        }
    }
#line 1553 "src/parser.y.c"
    break;

  case 43: /* CmdAux: LOOP Vars Cmds END  */
#line 146 "src/parser.y"
                       {}
#line 1559 "src/parser.y.c"
    break;

  case 44: /* CmdAux: EXIT WHEN Exp  */
#line 147 "src/parser.y"
                  { 
        if ((yyvsp[0].info).type != BOOL_TYPE) {
            // TODO: error
        }
    }
#line 1569 "src/parser.y.c"
    break;

  case 45: /* CmdAux: CmdReturn  */
#line 152 "src/parser.y"
              {}
#line 1575 "src/parser.y.c"
    break;

  case 46: /* AcessMemAddr: ID  */
#line 156 "src/parser.y"
       {
        //TODO
    }
#line 1583 "src/parser.y.c"
    break;

  case 47: /* AcessMemAddr: AcessMemAddr DOT ID  */
#line 159 "src/parser.y"
                        {
        //TODO  
    }
#line 1591 "src/parser.y.c"
    break;

  case 48: /* AcessMemAddr: AcessMemAddr LBRA Exp RBRA  */
#line 163 "src/parser.y"
                               {
        if ((yyvsp[-1].info).type == INT_TYPE) {
            (yyval.info).type = (yyvsp[-1].info).type;
        } else {
            printf("ERROR");
        }
        // garantir q AcessMemAddr é um array
        // acessar o tipo do conteudo array e atribuir esse tipo para AcessMemAddr
    }
#line 1605 "src/parser.y.c"
    break;

  case 49: /* AcessMemAddr: AcessMemAddr LPAR Args RPAR  */
#line 172 "src/parser.y"
                                {
    // TODO: comparar args com os parametros da tabela de simbolo do função AcessMemAddr 
    // desalocar a memoria de args após o uso
    // atribuir o tipo retornado pela função ao AcessMemAddr
    // {args_size=0;}
    }
#line 1616 "src/parser.y.c"
    break;

  case 50: /* CmdConditional: IF Exp THEN CmdBlock CmdConditionalEnd  */
#line 181 "src/parser.y"
                                           {
        if ((yyvsp[-3].info).type != BOOL_TYPE) {
            printf("ERROR");
            // TODO
        }
    }
#line 1627 "src/parser.y.c"
    break;

  case 51: /* CmdConditionalEnd: ELSE CmdBlock  */
#line 190 "src/parser.y"
                  {}
#line 1633 "src/parser.y.c"
    break;

  case 52: /* CmdConditionalEnd: %empty  */
#line 191 "src/parser.y"
                  {}
#line 1639 "src/parser.y.c"
    break;

  case 53: /* CmdReturn: RETURN CmdReturnExp  */
#line 195 "src/parser.y"
                        {
        // TODO busca na tabela para tipo compativel 
    }
#line 1647 "src/parser.y.c"
    break;

  case 54: /* CmdReturnExp: Exp  */
#line 201 "src/parser.y"
        { (yyval.info).type = (yyvsp[0].info).type; }
#line 1653 "src/parser.y.c"
    break;

  case 55: /* CmdReturnExp: %empty  */
#line 202 "src/parser.y"
                  { (yyval.info).type = -1;}
#line 1659 "src/parser.y.c"
    break;

  case 56: /* Exp: Exp OR Terms  */
#line 206 "src/parser.y"
                 {
        if ((yyvsp[-2].info).type == BOOL_TYPE && (yyvsp[0].info).type == BOOL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1671 "src/parser.y.c"
    break;

  case 57: /* Exp: Terms  */
#line 213 "src/parser.y"
          { (yyval.info).type = (yyvsp[0].info).type; }
#line 1677 "src/parser.y.c"
    break;

  case 58: /* Terms: Terms AND Comps  */
#line 217 "src/parser.y"
                    {
        if ((yyvsp[-2].info).type == BOOL_TYPE && (yyvsp[0].info).type == BOOL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1689 "src/parser.y.c"
    break;

  case 59: /* Terms: Comps  */
#line 224 "src/parser.y"
          { (yyval.info).type = (yyvsp[0].info).type; }
#line 1695 "src/parser.y.c"
    break;

  case 60: /* Comps: Factor NEQ Factor  */
#line 228 "src/parser.y"
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
#line 1713 "src/parser.y.c"
    break;

  case 61: /* Comps: Factor EQ Factor  */
#line 241 "src/parser.y"
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
#line 1731 "src/parser.y.c"
    break;

  case 62: /* Comps: Factor LESS Factor  */
#line 254 "src/parser.y"
                       {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1745 "src/parser.y.c"
    break;

  case 63: /* Comps: Factor GREATER Factor  */
#line 263 "src/parser.y"
                           {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1759 "src/parser.y.c"
    break;

  case 64: /* Comps: Factor LEQ Factor  */
#line 272 "src/parser.y"
                      {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1773 "src/parser.y.c"
    break;

  case 65: /* Comps: Factor GEQ Factor  */
#line 281 "src/parser.y"
                       {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = BOOL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1787 "src/parser.y.c"
    break;

  case 66: /* Comps: Factor  */
#line 290 "src/parser.y"
            { (yyval.info).type = (yyvsp[0].info).type; }
#line 1793 "src/parser.y.c"
    break;

  case 67: /* Factor: NOT AriOp  */
#line 294 "src/parser.y"
              {
        if ((yyvsp[0].info).type == BOOL_TYPE ) {
            (yyval.info).type = BOOL_TYPE;
            (yyval.info).v_bool = !(yyvsp[0].info).v_bool;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1806 "src/parser.y.c"
    break;

  case 68: /* Factor: AriOp  */
#line 302 "src/parser.y"
          { (yyval.info).type = (yyvsp[0].info).type; }
#line 1812 "src/parser.y.c"
    break;

  case 69: /* AriOp: AriOp PLUS AriOp2  */
#line 306 "src/parser.y"
                      {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = INT_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1826 "src/parser.y.c"
    break;

  case 70: /* AriOp: AriOp MINUS AriOp2  */
#line 315 "src/parser.y"
                       {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = INT_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1840 "src/parser.y.c"
    break;

  case 71: /* AriOp: AriOp2  */
#line 324 "src/parser.y"
           { (yyval.info).type = (yyvsp[0].info).type; }
#line 1846 "src/parser.y.c"
    break;

  case 72: /* AriOp2: AriOp2 MULTIPLY Parenthesis  */
#line 328 "src/parser.y"
                                {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = INT_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1860 "src/parser.y.c"
    break;

  case 73: /* AriOp2: AriOp2 DIVIDE Parenthesis  */
#line 337 "src/parser.y"
                              {
        if ((yyvsp[-2].info).type == INT_TYPE && (yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type = INT_TYPE;
        } else if ((yyvsp[-2].info).type == REAL_TYPE && (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = REAL_TYPE;
        } else {
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1874 "src/parser.y.c"
    break;

  case 74: /* AriOp2: AriOp2 MOD Parenthesis  */
#line 346 "src/parser.y"
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
#line 1889 "src/parser.y.c"
    break;

  case 75: /* AriOp2: Parenthesis  */
#line 356 "src/parser.y"
                { (yyval.info).type = (yyvsp[0].info).type; }
#line 1895 "src/parser.y.c"
    break;

  case 76: /* Parenthesis: UnaryExp  */
#line 360 "src/parser.y"
             { (yyval.info).type = (yyvsp[0].info).type; }
#line 1901 "src/parser.y.c"
    break;

  case 77: /* Parenthesis: LPAR Exp RPAR  */
#line 361 "src/parser.y"
                  { (yyval.info).type = (yyvsp[-1].info).type; }
#line 1907 "src/parser.y.c"
    break;

  case 78: /* UnaryExp: PLUS CastExp  */
#line 365 "src/parser.y"
                 { 
        if ((yyvsp[0].info).type == INT_TYPE || (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = (yyvsp[0].info).type;
        } else { 
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1919 "src/parser.y.c"
    break;

  case 79: /* UnaryExp: MINUS CastExp  */
#line 372 "src/parser.y"
                  { 
        if ((yyvsp[0].info).type == INT_TYPE || (yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type = (yyvsp[0].info).type;
        } else { 
            printf("ERROR! Incompatible type. \n");
        }
    }
#line 1931 "src/parser.y.c"
    break;

  case 80: /* UnaryExp: CastExp  */
#line 379 "src/parser.y"
            { (yyval.info).type = (yyvsp[0].info).type; }
#line 1937 "src/parser.y.c"
    break;

  case 81: /* CastExp: LPAR T_INT RPAR SimpleExp  */
#line 383 "src/parser.y"
                                    {
        if ((yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type == INT_TYPE;
            (yyval.info).v_int = (yyvsp[0].info).v_int;
        }
        if ((yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type == INT_TYPE;
            (yyval.info).v_int = (yyvsp[0].info).v_real;
        }
        if ((yyvsp[0].info).type == BOOL_TYPE) {
            (yyval.info).type == INT_TYPE;
            (yyval.info).v_int = (yyvsp[0].info).v_bool;
        }
        if ((yyvsp[0].info).type == CHAR_TYPE) {
            (yyval.info).type == INT_TYPE;
            (yyval.info).v_int = (yyvsp[0].info).v_char;
        }
    }
#line 1960 "src/parser.y.c"
    break;

  case 82: /* CastExp: LPAR T_REAL RPAR SimpleExp  */
#line 401 "src/parser.y"
                                    {
        if ((yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type == REAL_TYPE;
            (yyval.info).v_real = (yyvsp[0].info).v_int;
        }
        if ((yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type == REAL_TYPE;
            (yyval.info).v_real = (yyvsp[0].info).v_real;
        }
        if ((yyvsp[0].info).type == BOOL_TYPE) {
            (yyval.info).type == REAL_TYPE;
            (yyval.info).v_real = (yyvsp[0].info).v_bool;
        }
        if ((yyvsp[0].info).type == CHAR_TYPE) {
            (yyval.info).type == REAL_TYPE;
            (yyval.info).v_real = (yyvsp[0].info).v_char;
        }
}
#line 1983 "src/parser.y.c"
    break;

  case 83: /* CastExp: LPAR T_BOOL RPAR SimpleExp  */
#line 419 "src/parser.y"
                                    {
        if ((yyvsp[0].info).type == INT_TYPE) {
            (yyval.info).type == BOOL_TYPE;
            (yyval.info).v_bool = (yyvsp[0].info).v_int > 0;
        }
        if ((yyvsp[0].info).type == REAL_TYPE) {
            (yyval.info).type == BOOL_TYPE;
            (yyval.info).v_bool = (yyvsp[0].info).v_real > 0.0;
        }
        if ((yyvsp[0].info).type == BOOL_TYPE) {
            (yyval.info).type == BOOL_TYPE;
            (yyval.info).v_bool = (yyvsp[0].info).v_bool;
        }
        if ((yyvsp[0].info).type == CHAR_TYPE) {
            printf("char para bool pode não!\n");
        }
}
#line 2005 "src/parser.y.c"
    break;

  case 84: /* CastExp: LPAR T_CHAR RPAR SimpleExp  */
#line 436 "src/parser.y"
                                    {
    if ((yyvsp[0].info).type == INT_TYPE) {
        (yyval.info).type == CHAR_TYPE;
        // TODO If
        (yyval.info).v_char = (yyvsp[0].info).v_int;
    }
    if ((yyvsp[0].info).type == REAL_TYPE) {
        printf("real para char pode não!\n");
    }
    if ((yyvsp[0].info).type == BOOL_TYPE) {
        printf("bool para char pode não!\n");
    }
    if ((yyvsp[0].info).type == CHAR_TYPE) {
        (yyval.info).type == CHAR_TYPE;
        (yyval.info).v_char = (yyvsp[0].info).v_char;
    }
}
#line 2027 "src/parser.y.c"
    break;

  case 85: /* CastExp: SimpleExp  */
#line 453 "src/parser.y"
                                    {
    (yyval.info).type = (yyvsp[0].info).type;
}
#line 2035 "src/parser.y.c"
    break;

  case 86: /* SimpleExp: NumExp  */
#line 458 "src/parser.y"
           { (yyval.info).type = (yyvsp[0].info).type; }
#line 2041 "src/parser.y.c"
    break;

  case 87: /* SimpleExp: AcessMemAddr  */
#line 459 "src/parser.y"
                 { (yyval.info).type = (yyvsp[0].info).type; }
#line 2047 "src/parser.y.c"
    break;

  case 88: /* NumExp: V_INT  */
#line 463 "src/parser.y"
             { (yyval.info).type = INT_TYPE;  }
#line 2053 "src/parser.y.c"
    break;

  case 89: /* NumExp: V_REAL  */
#line 464 "src/parser.y"
             { (yyval.info).type = REAL_TYPE; }
#line 2059 "src/parser.y.c"
    break;

  case 90: /* NumExp: V_BOOL  */
#line 465 "src/parser.y"
             { (yyval.info).type = BOOL_TYPE; }
#line 2065 "src/parser.y.c"
    break;

  case 91: /* NumExp: V_CHAR  */
#line 466 "src/parser.y"
             { (yyval.info).type = CHAR_TYPE; }
#line 2071 "src/parser.y.c"
    break;

  case 92: /* NumExp: V_STRING  */
#line 467 "src/parser.y"
             { (yyval.info).type = ARRAY; /*TODO*/}
#line 2077 "src/parser.y.c"
    break;

  case 93: /* Args: Exp ArgsAux  */
#line 471 "src/parser.y"
                {}
#line 2083 "src/parser.y.c"
    break;

  case 94: /* Args: %empty  */
#line 472 "src/parser.y"
                  {}
#line 2089 "src/parser.y.c"
    break;

  case 95: /* ArgsAux: COMMA Args  */
#line 475 "src/parser.y"
                     {}
#line 2095 "src/parser.y.c"
    break;

  case 96: /* ArgsAux: %empty  */
#line 476 "src/parser.y"
                  {}
#line 2101 "src/parser.y.c"
    break;


#line 2105 "src/parser.y.c"

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

#line 479 "src/parser.y"

  
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
