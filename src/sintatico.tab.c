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
#line 4 "../src/sintatico.y"

#include <stdio.h>
#include <stdlib.h> // exit, EXIT_FAILURE
#include <stdbool.h> // tipo bool
#include <assert.h> // assert macro
#include <errno.h>
#include <string.h>
#include "tree/tree.h"

#include "log_info/logging.h"
#include "utils/user_input.h"
#include "utils/utils.h"

#define LOGI(...) cmmLog (LOG_TYPE_INFO, SINTATIC_ANALYSIS, __VA_ARGS__)
#define LOGE(...) cmmLog (LOG_TYPE_ERROR, SINTATIC_ANALYSIS, __VA_ARGS__)
#define MAX_SIZE 1000

extern FILE *yyin;
extern int yylex();
extern char* yytext;
extern int yyleng;

char buffer[256]; /// utilizado para armazenar temporariamente trechos de tokens

int num_tabs = 0;

treeNode sintax_tree[MAX_SIZE];
int sintax_tree_size = 0;

uint8_t is_open_block = 0; /// conta a quantidade de {}
uint8_t is_open_expression = 0; /// conta a quantidade de ()

bool have_error = false; /// guarda se houve algum erro durante a execução do processo

void yyerror(const char *s);

/**
 * @brief Últimas verificações léxicas após terminado o input de tokens
 *
 * @pre leitura de tokens encerrada
 * @post deixa a variável global have_error em seu estado final
 */
void lastVerify(const char * filename);
/**
 * @brief Função chamada ao encerrar o programa,
 * informando o usuário e realizando as limpezas necessárias
 *
 * Deve ser passada para função atexit
 * @pre leitura de tokens encerrada
 * @post deixa a variável global have_error em seu estado final
 */
void exitFunction(void);

#define ADD(TEXT) add(sintax_tree + sintax_tree_size, TEXT, num_tabs); sintax_tree_size++;

#line 127 "../src/sintatico.tab.c"

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

#include "sintatico.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_PREPROCESSOR_COMMAND = 3, /* TOKEN_PREPROCESSOR_COMMAND  */
  YYSYMBOL_TOKEN_KEYWORD_IF = 4,           /* TOKEN_KEYWORD_IF  */
  YYSYMBOL_TOKEN_KEYWORD_ELSE = 5,         /* TOKEN_KEYWORD_ELSE  */
  YYSYMBOL_TOKEN_KEYWORD_FOR = 6,          /* TOKEN_KEYWORD_FOR  */
  YYSYMBOL_TOKEN_KEYWORD_WHILE = 7,        /* TOKEN_KEYWORD_WHILE  */
  YYSYMBOL_TOKEN_KEYWORD_RETURN = 8,       /* TOKEN_KEYWORD_RETURN  */
  YYSYMBOL_TOKEN_KEYWORD_STRUCT = 9,       /* TOKEN_KEYWORD_STRUCT  */
  YYSYMBOL_TOKEN_KEYWORD_CONST = 10,       /* TOKEN_KEYWORD_CONST  */
  YYSYMBOL_TOKEN_DATA_TYPE_INT = 11,       /* TOKEN_DATA_TYPE_INT  */
  YYSYMBOL_TOKEN_DATA_TYPE_FLOAT = 12,     /* TOKEN_DATA_TYPE_FLOAT  */
  YYSYMBOL_TOKEN_DATA_TYPE_CHAR = 13,      /* TOKEN_DATA_TYPE_CHAR  */
  YYSYMBOL_TOKEN_DATA_TYPE_VOID = 14,      /* TOKEN_DATA_TYPE_VOID  */
  YYSYMBOL_TOKEN_ASSIGNMENT = 15,          /* TOKEN_ASSIGNMENT  */
  YYSYMBOL_TOKEN_ARITHMETIC_OPERATOR = 16, /* TOKEN_ARITHMETIC_OPERATOR  */
  YYSYMBOL_TOKEN_RELATIONAL_OPERATOR = 17, /* TOKEN_RELATIONAL_OPERATOR  */
  YYSYMBOL_TOKEN_END_EXP = 18,             /* TOKEN_END_EXP  */
  YYSYMBOL_TOKEN_BLOCK_BEGIN = 19,         /* TOKEN_BLOCK_BEGIN  */
  YYSYMBOL_TOKEN_BLOCK_END = 20,           /* TOKEN_BLOCK_END  */
  YYSYMBOL_TOKEN_PARENTESEIS_BEGIN = 21,   /* TOKEN_PARENTESEIS_BEGIN  */
  YYSYMBOL_TOKEN_PARENTESEIS_END = 22,     /* TOKEN_PARENTESEIS_END  */
  YYSYMBOL_TOKEN_INTEGER_LITERAL = 23,     /* TOKEN_INTEGER_LITERAL  */
  YYSYMBOL_TOKEN_FLOAT_LITERAL = 24,       /* TOKEN_FLOAT_LITERAL  */
  YYSYMBOL_TOKEN_STRING_LITERAL = 25,      /* TOKEN_STRING_LITERAL  */
  YYSYMBOL_TOKEN_CHAR_LITERAL = 26,        /* TOKEN_CHAR_LITERAL  */
  YYSYMBOL_TOKEN_ID = 27,                  /* TOKEN_ID  */
  YYSYMBOL_YYACCEPT = 28,                  /* $accept  */
  YYSYMBOL_add_tab = 29,                   /* add_tab  */
  YYSYMBOL_rm_tab = 30,                    /* rm_tab  */
  YYSYMBOL_programa_token = 31,            /* programa_token  */
  YYSYMBOL_definition_token = 32,          /* definition_token  */
  YYSYMBOL_variable_token = 33,            /* variable_token  */
  YYSYMBOL_function_token = 34,            /* function_token  */
  YYSYMBOL_assignment_token = 35,          /* assignment_token  */
  YYSYMBOL_data_type_token = 36,           /* data_type_token  */
  YYSYMBOL_literal_token = 37,             /* literal_token  */
  YYSYMBOL_if_token = 38,                  /* if_token  */
  YYSYMBOL_else_token = 39,                /* else_token  */
  YYSYMBOL_for_token = 40,                 /* for_token  */
  YYSYMBOL_while_token = 41,               /* while_token  */
  YYSYMBOL_programa = 42,                  /* programa  */
  YYSYMBOL_data_type = 43,                 /* data_type  */
  YYSYMBOL_keyword = 44,                   /* keyword  */
  YYSYMBOL_segure_token = 45,              /* segure_token  */
  YYSYMBOL_literal = 46,                   /* literal  */
  YYSYMBOL_definition = 47,                /* definition  */
  YYSYMBOL_definition_variable_function = 48, /* definition_variable_function  */
  YYSYMBOL_complete_variable = 49,         /* complete_variable  */
  YYSYMBOL_variable = 50,                  /* variable  */
  YYSYMBOL_function = 51,                  /* function  */
  YYSYMBOL_exp = 52,                       /* exp  */
  YYSYMBOL_for = 53,                       /* for  */
  YYSYMBOL_while = 54,                     /* while  */
  YYSYMBOL_atribuition = 55,               /* atribuition  */
  YYSYMBOL_value = 56,                     /* value  */
  YYSYMBOL_math_expression = 57,           /* math_expression  */
  YYSYMBOL_ifel = 58,                      /* ifel  */
  YYSYMBOL_conditional = 59                /* conditional  */
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   159

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   282


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
      25,    26,    27
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    91,    91,    93,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   107,   108,   109,   113,   114,
     115,   116,   117,   118,   119,   123,   124,   125,   126,   127,
     128,   129,   133,   134,   135,   139,   140,   141,   142,   145,
     149,   150,   154,   158,   159,   160,   164,   165,   166,   169,
     170,   171,   172,   173,   174,   179,   180,   181,   185,   186,
     190,   194,   195,   196,   199,   200,   201,   202,   206,   207,
     208,   212,   213
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
  "\"end of file\"", "error", "\"invalid token\"",
  "TOKEN_PREPROCESSOR_COMMAND", "TOKEN_KEYWORD_IF", "TOKEN_KEYWORD_ELSE",
  "TOKEN_KEYWORD_FOR", "TOKEN_KEYWORD_WHILE", "TOKEN_KEYWORD_RETURN",
  "TOKEN_KEYWORD_STRUCT", "TOKEN_KEYWORD_CONST", "TOKEN_DATA_TYPE_INT",
  "TOKEN_DATA_TYPE_FLOAT", "TOKEN_DATA_TYPE_CHAR", "TOKEN_DATA_TYPE_VOID",
  "TOKEN_ASSIGNMENT", "TOKEN_ARITHMETIC_OPERATOR",
  "TOKEN_RELATIONAL_OPERATOR", "TOKEN_END_EXP", "TOKEN_BLOCK_BEGIN",
  "TOKEN_BLOCK_END", "TOKEN_PARENTESEIS_BEGIN", "TOKEN_PARENTESEIS_END",
  "TOKEN_INTEGER_LITERAL", "TOKEN_FLOAT_LITERAL", "TOKEN_STRING_LITERAL",
  "TOKEN_CHAR_LITERAL", "TOKEN_ID", "$accept", "add_tab", "rm_tab",
  "programa_token", "definition_token", "variable_token", "function_token",
  "assignment_token", "data_type_token", "literal_token", "if_token",
  "else_token", "for_token", "while_token", "programa", "data_type",
  "keyword", "segure_token", "literal", "definition",
  "definition_variable_function", "complete_variable", "variable",
  "function", "exp", "for", "while", "atribuition", "value",
  "math_expression", "ifel", "conditional", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-102)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-50)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       1,  -102,    30,    36,  -102,  -102,  -102,  -102,     1,  -102,
       1,  -102,  -102,    13,  -102,    57,     8,   106,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,
    -102,  -102,    75,    21,  -102,  -102,  -102,  -102,    35,  -102,
    -102,  -102,    90,    39,  -102,  -102,    59,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,  -102,     5,
    -102,  -102,  -102,    37,  -102,    62,    90,  -102,  -102,  -102,
    -102,    48,    37,    63,    37,    37,    37,    37,    88,  -102,
    -102,    76,    80,   109,   114,    75,  -102,  -102,  -102,  -102,
    -102,  -102,  -102,  -102,  -102,  -102,  -102,   108,   103,   105,
     107,  -102,  -102,  -102,  -102,  -102,    31,    78,    98,    78,
      31,  -102,  -102,  -102,  -102,   104,   110,   111,   112,   113,
     115,    11,    31,  -102,    78,   117,    78,    78,   120,    31,
     116,  -102,  -102,    37,   122,   123,    37,   116,   124,    31,
      31,   125,  -102,    40,    43,  -102,   129,   127,   128,  -102,
    -102,    37,    37,   137,   132,   133,   130,  -102,  -102,    37,
    -102,  -102,   134,  -102,  -102
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     2,     0,     5,     1,     3,     2,     3,     4,     9,
       4,    16,     2,     0,    17,     0,     6,     0,     3,     3,
       3,     3,     2,     2,     3,     3,     3,     3,    18,    19,
      20,    24,     2,     0,    39,    21,    22,    23,     0,    45,
       8,     3,     9,     0,     3,    44,     0,    40,    25,    26,
      28,    29,    30,    31,    27,    34,    33,    32,    48,     0,
      41,    10,    46,     0,     2,     0,     9,     2,     2,     2,
       2,     0,     0,     0,     0,     0,     0,     0,     0,     3,
      57,     0,     0,     0,     0,     2,    50,    47,    53,    54,
      51,    52,     3,     3,     3,     3,    43,     0,     0,     0,
       0,    42,    35,    36,    38,    37,    64,     0,     9,     0,
      64,    62,    63,    61,    65,     0,    71,     0,     0,     0,
       0,     0,    64,     3,     0,     0,     0,     0,     0,    64,
      67,    60,    72,     0,     0,     0,     0,    66,     0,    64,
      64,     0,     3,     0,     0,     3,    68,     0,     0,    58,
       2,     0,     0,     0,     0,     0,     0,     3,     3,     0,
      56,    55,     0,     3,    69
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -102,     9,    -7,  -102,  -102,  -102,  -102,    89,  -102,  -102,
    -102,  -102,  -102,  -102,    96,    -6,  -102,    77,  -102,  -102,
    -102,    47,    72,  -102,   -70,  -102,  -102,    50,   -17,   -94,
    -102,  -101
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    40,     8,     1,     6,    22,    23,    67,    12,    64,
      68,   150,    69,    70,     2,    71,    57,    58,    65,     7,
      24,    72,    41,    44,    73,    74,    75,    76,   114,   115,
      77,   117
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      10,   -15,    86,    13,    88,    89,    90,    91,   120,    -7,
       3,    28,    29,    30,    31,     9,   121,    34,    35,    36,
      37,    15,    42,    62,    63,   134,   135,   122,   130,    -7,
       4,    32,    33,   129,    47,   137,    56,    60,    66,     5,
      16,   -11,    43,   -13,   -14,   143,   144,    -9,    -9,    -9,
      -9,    -9,   110,    45,   111,   112,   122,   -49,   113,   122,
      56,    59,   147,   138,    -8,   148,   141,    17,    18,    19,
      20,    21,    96,    78,    61,    85,    81,    82,    83,    84,
      79,   154,   155,    87,    98,   102,   103,   104,   105,   162,
     116,    38,   116,    39,    48,    49,    50,    51,    52,    53,
      54,   111,   112,    97,    11,   113,    14,   132,    55,   116,
     116,    92,    93,    94,    95,    99,   131,    25,    26,    27,
     122,   100,   123,   106,   107,    -8,   108,   124,   109,    46,
     126,   127,   122,   125,   -12,   146,   133,   128,   149,   136,
     139,   140,   156,    80,   142,   145,   151,   152,     0,   159,
     160,   161,   157,   158,   163,   118,   164,   101,   119,   153
};

static const yytype_int16 yycheck[] =
{
       7,     0,    72,     9,    74,    75,    76,    77,   109,     1,
       1,    18,    19,    20,    21,     6,   110,    24,    25,    26,
      27,    12,     1,    18,    19,   126,   127,    16,   122,    21,
       0,    22,    23,    22,    41,   129,    42,    44,     1,     3,
      27,     4,    21,     6,     7,   139,   140,    10,    11,    12,
      13,    14,    21,    18,    23,    24,    16,    20,    27,    16,
      66,    22,    22,   133,    27,    22,   136,    10,    11,    12,
      13,    14,    79,    64,    15,    27,    67,    68,    69,    70,
      18,   151,   152,    20,     4,    92,    93,    94,    95,   159,
     107,    16,   109,    18,     4,     5,     6,     7,     8,     9,
      10,    23,    24,    27,     8,    27,    10,   124,    18,   126,
     127,    23,    24,    25,    26,     6,   123,    11,    12,    13,
      16,     7,    18,    15,    21,    27,    21,    17,    21,    40,
      18,    18,    16,    22,     5,   142,    19,    22,   145,    19,
      18,    18,     5,    66,    20,    20,    19,    19,    -1,    19,
     157,   158,    20,    20,    20,   108,   163,    85,   108,   150
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    31,    42,    29,     0,     3,    32,    47,    30,    29,
      30,    42,    36,    43,    42,    29,    27,    10,    11,    12,
      13,    14,    33,    34,    48,    11,    12,    13,    30,    30,
      30,    30,    29,    29,    30,    30,    30,    30,    16,    18,
      29,    50,     1,    21,    51,    18,    35,    30,     4,     5,
       6,     7,     8,     9,    10,    18,    43,    44,    45,    22,
      30,    15,    18,    19,    37,    46,     1,    35,    38,    40,
      41,    43,    49,    52,    53,    54,    55,    58,    29,    18,
      45,    29,    29,    29,    29,    27,    52,    20,    52,    52,
      52,    52,    23,    24,    25,    26,    30,    27,     4,     6,
       7,    50,    30,    30,    30,    30,    15,    21,    21,    21,
      21,    23,    24,    27,    56,    57,    56,    59,    49,    55,
      59,    57,    16,    18,    17,    22,    18,    18,    22,    22,
      57,    30,    56,    19,    59,    59,    19,    57,    52,    18,
      18,    52,    20,    57,    57,    20,    30,    22,    22,    30,
      39,    19,    19,    29,    52,    52,     5,    20,    20,    19,
      30,    30,    52,    20,    30
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    42,    42,    43,    43,
      43,    43,    43,    43,    43,    44,    44,    44,    44,    44,
      44,    44,    45,    45,    45,    46,    46,    46,    46,    47,
      48,    48,    49,    50,    50,    50,    51,    51,    51,    52,
      52,    52,    52,    52,    52,    53,    53,    53,    54,    54,
      55,    56,    56,    56,    57,    57,    57,    57,    58,    58,
      58,    59,    59
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     5,     4,     4,
       4,     5,     5,     5,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     4,     4,     6,
       4,     4,     3,     6,     2,     1,     3,     5,     2,     0,
       2,     2,     2,     2,     2,    14,    14,     2,    10,     2,
       7,     1,     1,     1,     0,     1,     4,     3,    10,    17,
       2,     1,     3
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
  case 2: /* add_tab: %empty  */
#line 91 "../src/sintatico.y"
         {num_tabs++;}
#line 1282 "../src/sintatico.tab.c"
    break;

  case 3: /* rm_tab: %empty  */
#line 93 "../src/sintatico.y"
        {num_tabs--;}
#line 1288 "../src/sintatico.tab.c"
    break;

  case 4: /* programa_token: %empty  */
#line 95 "../src/sintatico.y"
                {ADD("programa");}
#line 1294 "../src/sintatico.tab.c"
    break;

  case 5: /* definition_token: %empty  */
#line 96 "../src/sintatico.y"
                  {ADD("definition");}
#line 1300 "../src/sintatico.tab.c"
    break;

  case 6: /* variable_token: %empty  */
#line 97 "../src/sintatico.y"
                {ADD("variable");}
#line 1306 "../src/sintatico.tab.c"
    break;

  case 7: /* function_token: %empty  */
#line 98 "../src/sintatico.y"
                {ADD("function");}
#line 1312 "../src/sintatico.tab.c"
    break;

  case 8: /* assignment_token: %empty  */
#line 99 "../src/sintatico.y"
                  {ADD("assignment");}
#line 1318 "../src/sintatico.tab.c"
    break;

  case 9: /* data_type_token: %empty  */
#line 100 "../src/sintatico.y"
                 {ADD("data type");}
#line 1324 "../src/sintatico.tab.c"
    break;

  case 10: /* literal_token: %empty  */
#line 101 "../src/sintatico.y"
               {ADD("literal");}
#line 1330 "../src/sintatico.tab.c"
    break;

  case 11: /* if_token: %empty  */
#line 102 "../src/sintatico.y"
          {ADD("if");}
#line 1336 "../src/sintatico.tab.c"
    break;

  case 12: /* else_token: %empty  */
#line 103 "../src/sintatico.y"
            {ADD("else");}
#line 1342 "../src/sintatico.tab.c"
    break;

  case 13: /* for_token: %empty  */
#line 104 "../src/sintatico.y"
           {ADD("for");}
#line 1348 "../src/sintatico.tab.c"
    break;

  case 14: /* while_token: %empty  */
#line 105 "../src/sintatico.y"
             {ADD("while");}
#line 1354 "../src/sintatico.tab.c"
    break;


#line 1358 "../src/sintatico.tab.c"

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

#line 216 "../src/sintatico.y"

void yyerror(const char *s) {
    LOGE("Token [%s] inesperado", yytext);
}

void lastVerify(const char * filename) {
    if (is_open_block) {
        LOGE("Fim do programa antes de fechar o escopo {...");
    }
    if (is_open_expression > 0) {
        LOGE("Fim do programa antes de fechar a expressão (...");
    }
    printf (
        "\n%s ao compilar o arquivo [%s]\n",
        have_error? "Falha" : "Sucesso",
        filename
    );
}

void exitFunction(void) {
    // não foi usado printf devido a possíveis falhas
    puts("Encerrando o compilador c--");
}

/// função main copiada para o main.c
int main(int argc, char * const argv[]) {
    // garante que o usuário passou 0 ou 1 argumentos
    assert(0 < argc && argc < 3);
    // configura função chamada ao sair do programa
    atexit(exitFunction);

    char *filename; /// caminho para o arquivo a ser analisado
    if (argc == 2) {
        filename = argv[1];
    }else {
        filename = getFilenameFromUser();
    }
    FILE *file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) {
        printf("Falha ao abrir o arquivo de entrada\n");
        return EXIT_FAILURE;
    }
    yyin = file_ptr;

    yyparse();
    lastVerify(filename);
    if (!have_error) {
        const char prefix[] = "arvores_";
        const int size = strlen(prefix) + strlen(filename);
        char out_file_name[size + 1];
        strcpy(out_file_name, prefix);
        strcat(out_file_name, filename);
        FILE *file = fopen(out_file_name, "w");
        if (!fopen) {
            printf("Falha ao abrir arquivo %s\n", out_file_name);
            exit(EXIT_FAILURE);
        }
        print(file, sintax_tree, sintax_tree_size);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
