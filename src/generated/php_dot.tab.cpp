
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         PHP_dot_parse
#define yylex           PHP_dot_lex
#define yyerror         PHP_dot_error
#define yylval          PHP_dot_lval
#define yychar          PHP_dot_char
#define yydebug         PHP_dot_debug
#define yynerrs         PHP_dot_nerrs


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 8 "src/generated_src/php_dot.ypp"

	#include <assert.h>
	#include <typeinfo>
	#include "AST.h"
	using namespace AST;
	#include "cmdline.h"
	#include "lib/Integer.h"
	#include "lib/String.h"
	#include "lib/error.h"
	#include "lib/escape.h"
	#include "parsing/PHP_context.h"

	void PHP_dot_error(PHP_context* context, const char* s)
	{
		phc_error(s, context->filename, context->source_line, 0);
	}

	const char* format (String* str)
	{
		stringstream ss;
		ss
		<< '\\' << '\"'
		<< *(escape_DOT (str, 20))
		<< '\\' << '\"'
		;

		return ss.str().c_str ();
	}

	const char* strval (AST::Source_rep* rep)
	{
		return format (rep->get_source_rep ());
	}

	const char* strval (Integer* rep)
	{
		return format (s(lexical_cast<string> (rep->value())));
	}

	const char* strval (String* rep)
	{
		return format (rep);
	}


	// Global state to generate DOT node identifiers
	Integer* node = new Integer(0);


/* Line 189 of yacc.c  */
#line 131 "src/generated/php_dot.tab.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     K_AND = 258,
     K_OR = 259,
     K_XOR = 260,
     K___FILE__ = 261,
     K_EXCEPTION = 262,
     K___LINE__ = 263,
     K_ARRAY = 264,
     K_AS = 265,
     K_BREAK = 266,
     K_CASE = 267,
     K_CLASS = 268,
     K_CONST = 269,
     K_CONTINUE = 270,
     K_DECLARE = 271,
     K_DEFAULT = 272,
     K_DIE = 273,
     K_DO = 274,
     K_ECHO = 275,
     K_ELSE = 276,
     K_ELSEIF = 277,
     K_EMPTY = 278,
     K_ENDDECLARE = 279,
     K_ENDFOR = 280,
     K_ENDFOREACH = 281,
     K_ENDIF = 282,
     K_ENDSWITCH = 283,
     K_ENDWHILE = 284,
     K_EVAL = 285,
     K_EXIT = 286,
     K_EXTENDS = 287,
     K_FOR = 288,
     K_FOREACH = 289,
     K_FUNCTION = 290,
     K_GLOBAL = 291,
     K_IF = 292,
     K_INCLUDE = 293,
     K_INCLUDE_ONCE = 294,
     K_INSTANCEOF = 295,
     K_ISSET = 296,
     K_LIST = 297,
     K_NEW = 298,
     K_PRINT = 299,
     K_REQUIRE = 300,
     K_REQUIRE_ONCE = 301,
     K_RETURN = 302,
     K_STATIC = 303,
     K_SWITCH = 304,
     K_UNSET = 305,
     K_USE = 306,
     K_VAR = 307,
     K_WHILE = 308,
     K___FUNCTION__ = 309,
     K___CLASS__ = 310,
     K___METHOD__ = 311,
     K_FINAL = 312,
     K_PHP_USER_FILTER = 313,
     K_INTERFACE = 314,
     K_IMPLEMENTS = 315,
     K_PUBLIC = 316,
     K_PRIVATE = 317,
     K_PROTECTED = 318,
     K_ABSTRACT = 319,
     K_CLONE = 320,
     K_TRY = 321,
     K_CATCH = 322,
     K_THROW = 323,
     K_CFUNCTION = 324,
     K_OLD_FUNCTION = 325,
     K_HALT_COMPILER = 326,
     C_TRUE = 327,
     C_FALSE = 328,
     C_NULL = 329,
     O_EQEQ = 330,
     O_EQEQEQ = 331,
     O_NOTEQ = 332,
     O_NOTEQEQ = 333,
     O_LE = 334,
     O_GE = 335,
     O_INC = 336,
     O_DEC = 337,
     O_DOUBLEARROW = 338,
     O_SINGLEARROW = 339,
     O_SL = 340,
     O_SR = 341,
     O_COLONCOLON = 342,
     O_LOGICOR = 343,
     O_LOGICAND = 344,
     O_PLUSEQ = 345,
     O_MINUSEQ = 346,
     O_MULEQ = 347,
     O_DIVEQ = 348,
     O_CONCATEQ = 349,
     O_MODEQ = 350,
     O_ANDEQ = 351,
     O_OREQ = 352,
     O_XOREQ = 353,
     O_SLEQ = 354,
     O_SREQ = 355,
     O_MAGIC_CONCAT = 356,
     CAST_INT = 357,
     CAST_REAL = 358,
     CAST_STRING = 359,
     CAST_ARRAY = 360,
     CAST_OBJECT = 361,
     CAST_BOOL = 362,
     CAST_UNSET = 363,
     T_STRING = 364,
     IDENT = 365,
     VARIABLE = 366,
     T_INT = 367,
     T_REAL = 368,
     INLINE_HTML = 369,
     INVALID_TOKEN = 370
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 58 "src/generated_src/php_dot.ypp"

	Integer* node;
	Object* object;
	List<AST::Statement*>* list_ast_statement;
	List<AST::Catch*>* list_ast_catch;
	AST::Catch* ast_catch;
	List<AST::Variable*>* list_ast_variable;
	AST::Variable* ast_variable;
	AST::STRING* token_string;
	AST::Method* ast_method;
	Integer* integer;
	AST::Class_def* ast_class_def;
	AST::CLASS_NAME* token_class_name;
	AST::Interface_def* ast_interface_def;
	List<AST::INTERFACE_NAME*>* list_token_interface_name;
	List<AST::Directive*>* list_ast_directive;
	List<AST::Switch_case*>* switch_ast_case_list;
	AST::If* ast_if;
	List<AST::Formal_parameter*>* list_ast_formal_parameter;
	AST::Type* ast_type;
	List<AST::Variable_name*>* list_ast_variable_name;
	AST::Variable_name* ast_variable_name;
	List<AST::Member*>* list_ast_member;
	AST::Attr_mod* ast_attr_mod;
	AST::Method_mod* ast_method_mod;
	AST::Expr* ast_expr;
	AST::Method_invocation* ast_method_invocation;
	AST::Class_name* class_name;
	AST::Constant* ast_constant;
	List<AST::Array_elem*>* list_ast_array_elem;
	List<AST::Expr*>* list_ast_expr;
	AST::Nested_list_elements* ast_nested_list_elements;
	AST::List_element* ast_list_element;
	String* string;
	List<AST::Actual_parameter*>* list_ast_actual_parameter;
	AST::Class_name* ast_class_name;
	List<AST::Switch_case*>* list_ast_switch_case;
	AST::Switch_case* ast_switch_case;
	AST::Try* ast_try;
	AST::Declare* ast_declare;
	AST::Foreach* ast_foreach;
	AST::Switch* ast_switch;
	AST::For* ast_for;
	AST::Do* ast_do;
	AST::While* ast_while;
	AST::Statement* ast_statement;
	AST::INT* token_int;
	AST::OP* token_op;
	AST::REAL* token_real;
	AST::BOOL* token_bool;
	AST::NIL* token_null;
	List<AST::Name_with_default*>* list_ast_name_with_default;
	AST::Member* ast_member;
	AST::Attribute* ast_attribute;
	AST::New* ast_new;



/* Line 214 of yacc.c  */
#line 341 "src/generated/php_dot.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */

/* Line 264 of yacc.c  */
#line 115 "src/generated_src/php_dot.ypp"

	int PHP_lex(YYSTYPE* yylval, void* scanner);
	int PHP_dot_lex(YYSTYPE* yylval, void* scanner) 
	{
		return(PHP_lex(yylval, scanner));
	}

	#define scanner context->scanner


/* Line 264 of yacc.c  */
#line 364 "src/generated/php_dot.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5755

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  142
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  115
/* YYNRULES -- Number of rules.  */
#define YYNRULES  351
/* YYNRULES -- Number of states.  */
#define YYNSTATES  687

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   370

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   126,     2,     2,   140,   125,   118,     2,
     135,   136,   123,   121,   116,   122,   120,   124,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   132,   137,
     128,   130,   129,   131,   133,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   134,     2,   141,   119,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   138,   117,   139,   127,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    11,    13,    15,    20,
      23,    24,    26,    28,    30,    35,    37,    39,    41,    43,
      45,    47,    49,    51,    53,    55,    57,    59,    61,    63,
      65,    73,    84,    90,    98,   108,   114,   117,   121,   124,
     128,   131,   135,   139,   143,   147,   151,   153,   156,   160,
     166,   175,   184,   190,   192,   202,   206,   208,   209,   211,
     214,   221,   223,   227,   229,   231,   235,   237,   239,   240,
     242,   250,   258,   265,   267,   270,   273,   274,   277,   279,
     280,   283,   284,   287,   289,   293,   294,   297,   299,   302,
     304,   309,   311,   316,   318,   323,   327,   333,   337,   342,
     347,   353,   354,   360,   365,   367,   369,   371,   376,   377,
     384,   385,   393,   394,   397,   398,   402,   404,   405,   408,
     412,   418,   423,   428,   434,   442,   449,   450,   452,   454,
     456,   457,   459,   461,   464,   468,   472,   477,   481,   483,
     485,   488,   493,   497,   503,   505,   509,   512,   513,   517,
     520,   529,   531,   533,   535,   537,   538,   540,   542,   545,
     547,   549,   551,   553,   555,   557,   561,   567,   569,   573,
     579,   584,   588,   590,   591,   593,   597,   599,   606,   610,
     615,   622,   626,   629,   633,   637,   641,   645,   649,   653,
     657,   661,   665,   669,   673,   676,   679,   682,   685,   689,
     693,   697,   701,   705,   709,   713,   717,   721,   726,   730,
     734,   738,   742,   746,   750,   754,   757,   760,   763,   766,
     770,   774,   778,   782,   786,   790,   794,   798,   802,   806,
     812,   814,   817,   820,   823,   826,   829,   832,   835,   838,
     841,   844,   846,   851,   854,   859,   866,   873,   878,   880,
     882,   884,   889,   891,   894,   895,   898,   899,   902,   906,
     907,   911,   913,   915,   917,   919,   921,   923,   925,   927,
     929,   931,   933,   935,   937,   940,   943,   948,   950,   954,
     956,   958,   960,   961,   964,   965,   967,   973,   977,   981,
     983,   985,   987,   989,   991,   993,   996,   998,  1001,  1003,
    1007,  1011,  1012,  1014,  1017,  1021,  1023,  1025,  1027,  1030,
    1032,  1037,  1042,  1044,  1046,  1051,  1052,  1054,  1056,  1058,
    1063,  1068,  1070,  1072,  1076,  1078,  1081,  1085,  1087,  1089,
    1094,  1095,  1096,  1099,  1105,  1109,  1113,  1115,  1122,  1127,
    1132,  1135,  1140,  1145,  1148,  1151,  1156,  1159,  1162,  1164,
    1168,  1172
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     143,     0,    -1,   144,    -1,   144,   145,    -1,    -1,   148,
      -1,   169,    -1,   170,    -1,    71,   135,   136,   137,    -1,
     146,   147,    -1,    -1,   148,    -1,   169,    -1,   170,    -1,
      71,   135,   136,   137,    -1,   162,    -1,    37,    -1,    22,
      -1,    34,    -1,    53,    -1,    19,    -1,    33,    -1,    49,
      -1,    16,    -1,    66,    -1,    67,    -1,    35,    -1,    12,
      -1,    17,    -1,   256,    -1,   149,   135,   230,   136,   148,
     190,   192,    -1,   149,   135,   230,   136,   132,   146,   191,
     193,    27,   137,    -1,   152,   135,   230,   136,   189,    -1,
     153,   148,    53,   135,   230,   136,   137,    -1,   154,   135,
     212,   137,   212,   137,   212,   136,   182,    -1,   155,   135,
     230,   136,   186,    -1,    11,   137,    -1,    11,   230,   137,
      -1,    15,   137,    -1,    15,   230,   137,    -1,    47,   137,
      -1,    47,   214,   137,    -1,    47,   234,   137,    -1,    36,
     199,   137,    -1,    48,   201,   137,    -1,    20,   211,   137,
      -1,   114,    -1,   230,   137,    -1,    51,   168,   137,    -1,
      50,   135,   166,   136,   137,    -1,   151,   135,   234,    10,
     181,   180,   136,   183,    -1,   151,   135,   214,    10,   232,
     180,   136,   183,    -1,   156,   135,   185,   136,   184,    -1,
     137,    -1,   157,   256,   158,   135,   216,   111,   136,   256,
     163,    -1,    68,   230,   137,    -1,   164,    -1,    -1,   165,
      -1,   164,   165,    -1,   158,   135,   216,   111,   136,   256,
      -1,   167,    -1,   166,   116,   167,    -1,   234,    -1,   109,
      -1,   135,   109,   136,    -1,   172,    -1,   173,    -1,    -1,
     118,    -1,   159,   171,   110,   135,   194,   136,   256,    -1,
     174,   110,   175,   178,   138,   202,   139,    -1,   176,   110,
     177,   138,   202,   139,    -1,    13,    -1,    64,    13,    -1,
      57,    13,    -1,    -1,    32,   216,    -1,    59,    -1,    -1,
      32,   179,    -1,    -1,    60,   179,    -1,   216,    -1,   179,
     116,   216,    -1,    -1,    83,   181,    -1,   232,    -1,   118,
     232,    -1,   148,    -1,   132,   146,    25,   137,    -1,   148,
      -1,   132,   146,    26,   137,    -1,   148,    -1,   132,   146,
      24,   137,    -1,   110,   130,   224,    -1,   185,   116,   110,
     130,   224,    -1,   138,   187,   139,    -1,   138,   137,   187,
     139,    -1,   132,   187,    28,   137,    -1,   132,   137,   187,
      28,   137,    -1,    -1,   187,   160,   230,   188,   146,    -1,
     187,   161,   188,   146,    -1,   132,    -1,   137,    -1,   148,
      -1,   132,   146,    29,   137,    -1,    -1,   190,   150,   135,
     230,   136,   148,    -1,    -1,   191,   150,   135,   230,   136,
     132,   146,    -1,    -1,    21,   148,    -1,    -1,    21,   132,
     146,    -1,   195,    -1,    -1,   196,   111,    -1,   196,   118,
     111,    -1,   196,   118,   111,   130,   224,    -1,   196,   111,
     130,   224,    -1,   195,   116,   196,   111,    -1,   195,   116,
     196,   118,   111,    -1,   195,   116,   196,   118,   111,   130,
     224,    -1,   195,   116,   196,   111,   130,   224,    -1,    -1,
     110,    -1,     9,    -1,   198,    -1,    -1,   214,    -1,   234,
      -1,   118,   232,    -1,   198,   116,   214,    -1,   198,   116,
     234,    -1,   198,   116,   118,   232,    -1,   199,   116,   200,
      -1,   200,    -1,   111,    -1,   140,   231,    -1,   140,   138,
     230,   139,    -1,   201,   116,   111,    -1,   201,   116,   111,
     130,   224,    -1,   111,    -1,   111,   130,   224,    -1,   202,
     203,    -1,    -1,   205,   209,   137,    -1,   210,   137,    -1,
     206,   159,   171,   110,   135,   194,   136,   204,    -1,   137,
      -1,   256,    -1,   207,    -1,    52,    -1,    -1,   207,    -1,
     208,    -1,   207,   208,    -1,    61,    -1,    63,    -1,    62,
      -1,    48,    -1,    64,    -1,    57,    -1,   209,   116,   111,
      -1,   209,   116,   111,   130,   224,    -1,   111,    -1,   111,
     130,   224,    -1,   210,   116,   110,   130,   224,    -1,    14,
     110,   130,   224,    -1,   211,   116,   230,    -1,   230,    -1,
      -1,   213,    -1,   213,   116,   230,    -1,   230,    -1,    42,
     135,   249,   136,   130,   230,    -1,   234,   130,   230,    -1,
     234,   130,   118,   234,    -1,   234,   130,   118,    43,   217,
     222,    -1,    43,   217,   222,    -1,    65,   230,    -1,   234,
      90,   230,    -1,   234,    91,   230,    -1,   234,    92,   230,
      -1,   234,    93,   230,    -1,   234,    94,   230,    -1,   234,
      95,   230,    -1,   234,    96,   230,    -1,   234,    97,   230,
      -1,   234,    98,   230,    -1,   234,    99,   230,    -1,   234,
     100,   230,    -1,   233,    81,    -1,    81,   233,    -1,   233,
      82,    -1,    82,   233,    -1,   230,    88,   230,    -1,   230,
      89,   230,    -1,   230,     4,   230,    -1,   230,     3,   230,
      -1,   230,     5,   230,    -1,   230,   117,   230,    -1,   230,
     118,   230,    -1,   230,   119,   230,    -1,   230,   120,   230,
      -1,   230,   101,   230,   139,    -1,   230,   121,   230,    -1,
     230,   122,   230,    -1,   230,   123,   230,    -1,   230,   124,
     230,    -1,   230,   125,   230,    -1,   230,    85,   230,    -1,
     230,    86,   230,    -1,   121,   230,    -1,   122,   230,    -1,
     126,   230,    -1,   127,   230,    -1,   230,    76,   230,    -1,
     230,    78,   230,    -1,   230,    75,   230,    -1,   230,    77,
     230,    -1,   230,   128,   230,    -1,   230,    79,   230,    -1,
     230,   129,   230,    -1,   230,    80,   230,    -1,   230,    40,
     217,    -1,   135,   230,   136,    -1,   230,   131,   230,   132,
     230,    -1,   253,    -1,   102,   230,    -1,   103,   230,    -1,
     104,   230,    -1,   105,   230,    -1,   106,   230,    -1,   107,
     230,    -1,   108,   230,    -1,    31,   221,    -1,    18,   221,
      -1,   133,   230,    -1,   226,    -1,     9,   135,   251,   136,
      -1,    44,   230,    -1,   110,   135,   197,   136,    -1,   216,
      87,   110,   135,   197,   136,    -1,   216,    87,   238,   135,
     197,   136,    -1,   238,   135,   197,   136,    -1,   110,    -1,
     110,    -1,   218,    -1,   241,    84,   245,   219,    -1,   241,
      -1,   219,   220,    -1,    -1,    84,   245,    -1,    -1,   135,
     136,    -1,   135,   230,   136,    -1,    -1,   135,   197,   136,
      -1,   112,    -1,   113,    -1,   109,    -1,    73,    -1,    72,
      -1,    74,    -1,     8,    -1,     6,    -1,    55,    -1,    56,
      -1,    54,    -1,   223,    -1,   110,    -1,   121,   224,    -1,
     122,   224,    -1,     9,   135,   227,   136,    -1,   225,    -1,
     110,    87,   110,    -1,   110,    -1,   255,    -1,   223,    -1,
      -1,   229,   228,    -1,    -1,   116,    -1,   229,   116,   224,
      83,   224,    -1,   229,   116,   224,    -1,   224,    83,   224,
      -1,   224,    -1,   231,    -1,   214,    -1,   234,    -1,   234,
      -1,   234,    -1,   240,   235,    -1,   240,    -1,   235,   236,
      -1,   236,    -1,    84,   245,   237,    -1,   135,   197,   136,
      -1,    -1,   242,    -1,   248,   242,    -1,   216,    87,   238,
      -1,   241,    -1,   215,    -1,   242,    -1,   248,   242,    -1,
     239,    -1,   242,   134,   244,   141,    -1,   242,   138,   230,
     139,    -1,   243,    -1,   111,    -1,   140,   138,   230,   139,
      -1,    -1,   230,    -1,   246,    -1,   238,    -1,   246,   134,
     244,   141,    -1,   246,   138,   230,   139,    -1,   247,    -1,
     110,    -1,   138,   230,   139,    -1,   140,    -1,   248,   140,
      -1,   249,   116,   250,    -1,   250,    -1,   234,    -1,    42,
     135,   249,   136,    -1,    -1,    -1,   252,   228,    -1,   252,
     116,   230,    83,   230,    -1,   252,   116,   230,    -1,   230,
      83,   230,    -1,   230,    -1,   252,   116,   230,    83,   118,
     232,    -1,   252,   116,   118,   232,    -1,   230,    83,   118,
     232,    -1,   118,   232,    -1,    41,   135,   254,   136,    -1,
      23,   135,   234,   136,    -1,    38,   230,    -1,    39,   230,
      -1,    30,   135,   230,   136,    -1,    45,   230,    -1,    46,
     230,    -1,   234,    -1,   254,   116,   234,    -1,   216,    87,
     110,    -1,   138,   146,   139,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   426,   426,   436,   445,   455,   462,   469,   476,   496,
     505,   515,   522,   529,   536,   553,   567,   578,   589,   600,
     611,   622,   633,   644,   655,   666,   677,   688,   699,   711,
     718,   733,   754,   767,   784,   803,   816,   826,   837,   847,
     858,   868,   879,   890,   901,   912,   923,   931,   940,   951,
     966,   983,  1000,  1013,  1021,  1039,  1053,  1061,  1071,  1078,
    1089,  1107,  1114,  1127,  1137,  1145,  1160,  1170,  1181,  1188,
    1199,  1218,  1234,  1252,  1260,  1270,  1284,  1291,  1303,  1315,
    1322,  1335,  1342,  1354,  1361,  1375,  1382,  1394,  1401,  1413,
    1420,  1436,  1443,  1459,  1466,  1482,  1493,  1510,  1521,  1534,
    1547,  1566,  1573,  1584,  1600,  1608,  1618,  1625,  1642,  1649,
    1670,  1677,  1697,  1704,  1720,  1727,  1741,  1749,  1762,  1771,
    1782,  1796,  1808,  1820,  1834,  1851,  1870,  1877,  1885,  1896,
    1904,  1914,  1921,  1928,  1937,  1947,  1957,  1972,  1982,  1992,
    2000,  2009,  2025,  2036,  2050,  2058,  2072,  2081,  2091,  2101,
    2110,  2130,  2138,  2148,  2155,  2167,  2174,  2184,  2191,  2202,
    2210,  2218,  2226,  2234,  2242,  2253,  2264,  2278,  2286,  2300,
    2314,  2330,  2340,  2351,  2358,  2368,  2378,  2388,  2404,  2414,
    2426,  2441,  2451,  2460,  2470,  2480,  2490,  2500,  2510,  2520,
    2530,  2540,  2550,  2560,  2570,  2579,  2588,  2597,  2606,  2616,
    2626,  2636,  2646,  2656,  2666,  2676,  2686,  2696,  2713,  2723,
    2733,  2743,  2753,  2763,  2773,  2783,  2792,  2801,  2810,  2819,
    2829,  2839,  2849,  2859,  2869,  2879,  2889,  2899,  2909,  2920,
    2933,  2940,  2949,  2958,  2967,  2976,  2985,  2994,  3003,  3012,
    3021,  3030,  3037,  3050,  3062,  3075,  3091,  3106,  3121,  3132,
    3140,  3150,  3161,  3171,  3180,  3190,  3203,  3210,  3220,  3235,
    3242,  3256,  3264,  3272,  3280,  3288,  3296,  3304,  3312,  3320,
    3328,  3336,  3347,  3354,  3362,  3371,  3380,  3393,  3403,  3418,
    3426,  3433,  3444,  3451,  3466,  3473,  3483,  3496,  3506,  3516,
    3526,  3533,  3543,  3553,  3563,  3590,  3598,  3612,  3620,  3630,
    3643,  3655,  3665,  3672,  3683,  3696,  3703,  3713,  3720,  3728,
    3738,  3750,  3762,  3772,  3780,  3797,  3804,  3814,  3821,  3834,
    3846,  3858,  3871,  3879,  3893,  3901,  3913,  3923,  3932,  3939,
    3953,  3964,  3971,  3985,  3998,  4008,  4018,  4025,  4040,  4052,
    4064,  4076,  4089,  4102,  4111,  4120,  4133,  4142,  4154,  4161,
    4174,  4192
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_AND", "K_OR", "K_XOR", "K___FILE__",
  "K_EXCEPTION", "K___LINE__", "K_ARRAY", "K_AS", "K_BREAK", "K_CASE",
  "K_CLASS", "K_CONST", "K_CONTINUE", "K_DECLARE", "K_DEFAULT", "K_DIE",
  "K_DO", "K_ECHO", "K_ELSE", "K_ELSEIF", "K_EMPTY", "K_ENDDECLARE",
  "K_ENDFOR", "K_ENDFOREACH", "K_ENDIF", "K_ENDSWITCH", "K_ENDWHILE",
  "K_EVAL", "K_EXIT", "K_EXTENDS", "K_FOR", "K_FOREACH", "K_FUNCTION",
  "K_GLOBAL", "K_IF", "K_INCLUDE", "K_INCLUDE_ONCE", "K_INSTANCEOF",
  "K_ISSET", "K_LIST", "K_NEW", "K_PRINT", "K_REQUIRE", "K_REQUIRE_ONCE",
  "K_RETURN", "K_STATIC", "K_SWITCH", "K_UNSET", "K_USE", "K_VAR",
  "K_WHILE", "K___FUNCTION__", "K___CLASS__", "K___METHOD__", "K_FINAL",
  "K_PHP_USER_FILTER", "K_INTERFACE", "K_IMPLEMENTS", "K_PUBLIC",
  "K_PRIVATE", "K_PROTECTED", "K_ABSTRACT", "K_CLONE", "K_TRY", "K_CATCH",
  "K_THROW", "K_CFUNCTION", "K_OLD_FUNCTION", "K_HALT_COMPILER", "C_TRUE",
  "C_FALSE", "C_NULL", "O_EQEQ", "O_EQEQEQ", "O_NOTEQ", "O_NOTEQEQ",
  "O_LE", "O_GE", "O_INC", "O_DEC", "O_DOUBLEARROW", "O_SINGLEARROW",
  "O_SL", "O_SR", "O_COLONCOLON", "O_LOGICOR", "O_LOGICAND", "O_PLUSEQ",
  "O_MINUSEQ", "O_MULEQ", "O_DIVEQ", "O_CONCATEQ", "O_MODEQ", "O_ANDEQ",
  "O_OREQ", "O_XOREQ", "O_SLEQ", "O_SREQ", "O_MAGIC_CONCAT", "CAST_INT",
  "CAST_REAL", "CAST_STRING", "CAST_ARRAY", "CAST_OBJECT", "CAST_BOOL",
  "CAST_UNSET", "T_STRING", "IDENT", "VARIABLE", "T_INT", "T_REAL",
  "INLINE_HTML", "INVALID_TOKEN", "','", "'|'", "'&'", "'^'", "'.'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'!'", "'~'", "'<'", "'>'", "'='", "'?'",
  "':'", "'@'", "'['", "'('", "')'", "';'", "'{'", "'}'", "'$'", "']'",
  "$accept", "start", "top_statement_list", "top_statement",
  "inner_statement_list", "inner_statement", "statement", "keyword_if",
  "keyword_elseif", "keyword_foreach", "keyword_while", "keyword_do",
  "keyword_for", "keyword_switch", "keyword_declare", "keyword_try",
  "keyword_catch", "keyword_function", "keyword_case", "keyword_default",
  "unticked_statement", "additional_catches",
  "non_empty_additional_catches", "additional_catch", "unset_variables",
  "unset_variable", "use_filename", "function_declaration_statement",
  "class_declaration_statement", "is_reference",
  "unticked_function_declaration_statement",
  "unticked_class_declaration_statement", "class_entry_type",
  "extends_from", "interface_entry", "interface_extends_list",
  "implements_list", "interface_list", "foreach_optional_arg",
  "foreach_variable", "for_statement", "foreach_statement",
  "declare_statement", "declare_list", "switch_case_list", "case_list",
  "case_separator", "while_statement", "elseif_list", "new_elseif_list",
  "else_single", "new_else_single", "parameter_list",
  "non_empty_parameter_list", "optional_class_type",
  "function_call_parameter_list", "non_empty_function_call_parameter_list",
  "global_var_list", "global_var", "static_var_list",
  "class_statement_list", "class_statement", "method_body",
  "variable_modifiers", "method_modifiers", "non_empty_member_modifiers",
  "member_modifier", "class_variable_declaration",
  "class_constant_declaration", "echo_expr_list", "for_expr",
  "non_empty_for_expr", "expr_without_variable", "function_call",
  "fully_qualified_class_name", "class_name_reference",
  "dynamic_class_name_reference", "dynamic_class_name_variable_properties",
  "dynamic_class_name_variable_property", "exit_expr", "ctor_arguments",
  "common_scalar", "static_scalar", "static_class_constant", "scalar",
  "static_array_pair_list", "possible_comma",
  "non_empty_static_array_pair_list", "expr", "r_variable", "w_variable",
  "rw_variable", "variable", "variable_properties", "variable_property",
  "method_or_not", "variable_without_objects", "static_member",
  "base_variable_with_function_calls", "base_variable",
  "reference_variable", "compound_variable", "dim_offset",
  "object_property", "object_dim_list", "variable_name",
  "simple_indirect_reference", "assignment_list",
  "assignment_list_element", "array_pair_list",
  "non_empty_array_pair_list", "internal_functions_in_yacc",
  "isset_variables", "class_constant", "block", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,    44,   124,    38,    94,
      46,    43,    45,    42,    47,    37,    33,   126,    60,    62,
      61,    63,    58,    64,    91,    40,    41,    59,   123,   125,
      36,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   142,   143,   144,   144,   145,   145,   145,   145,   146,
     146,   147,   147,   147,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   163,   163,   164,   164,
     165,   166,   166,   167,   168,   168,   169,   170,   171,   171,
     172,   173,   173,   174,   174,   174,   175,   175,   176,   177,
     177,   178,   178,   179,   179,   180,   180,   181,   181,   182,
     182,   183,   183,   184,   184,   185,   185,   186,   186,   186,
     186,   187,   187,   187,   188,   188,   189,   189,   190,   190,
     191,   191,   192,   192,   193,   193,   194,   194,   195,   195,
     195,   195,   195,   195,   195,   195,   196,   196,   196,   197,
     197,   198,   198,   198,   198,   198,   198,   199,   199,   200,
     200,   200,   201,   201,   201,   201,   202,   202,   203,   203,
     203,   204,   204,   205,   205,   206,   206,   207,   207,   208,
     208,   208,   208,   208,   208,   209,   209,   209,   209,   210,
     210,   211,   211,   212,   212,   213,   213,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   215,   215,   215,   215,   216,   217,
     217,   218,   218,   219,   219,   220,   221,   221,   221,   222,
     222,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   224,   224,   224,   224,   224,   224,   225,   226,
     226,   226,   227,   227,   228,   228,   229,   229,   229,   229,
     230,   230,   231,   232,   233,   234,   234,   235,   235,   236,
     237,   237,   238,   238,   239,   240,   240,   241,   241,   241,
     242,   242,   242,   243,   243,   244,   244,   245,   245,   246,
     246,   246,   247,   247,   248,   248,   249,   249,   250,   250,
     250,   251,   251,   252,   252,   252,   252,   252,   252,   252,
     252,   253,   253,   253,   253,   253,   253,   253,   254,   254,
     255,   256
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     4,     2,
       0,     1,     1,     1,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       7,    10,     5,     7,     9,     5,     2,     3,     2,     3,
       2,     3,     3,     3,     3,     3,     1,     2,     3,     5,
       8,     8,     5,     1,     9,     3,     1,     0,     1,     2,
       6,     1,     3,     1,     1,     3,     1,     1,     0,     1,
       7,     7,     6,     1,     2,     2,     0,     2,     1,     0,
       2,     0,     2,     1,     3,     0,     2,     1,     2,     1,
       4,     1,     4,     1,     4,     3,     5,     3,     4,     4,
       5,     0,     5,     4,     1,     1,     1,     4,     0,     6,
       0,     7,     0,     2,     0,     3,     1,     0,     2,     3,
       5,     4,     4,     5,     7,     6,     0,     1,     1,     1,
       0,     1,     1,     2,     3,     3,     4,     3,     1,     1,
       2,     4,     3,     5,     1,     3,     2,     0,     3,     2,
       8,     1,     1,     1,     1,     0,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     3,     5,     1,     3,     5,
       4,     3,     1,     0,     1,     3,     1,     6,     3,     4,
       6,     3,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     5,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     1,     4,     2,     4,     6,     6,     4,     1,     1,
       1,     4,     1,     2,     0,     2,     0,     2,     3,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     4,     1,     3,     1,
       1,     1,     0,     2,     0,     1,     5,     3,     3,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     1,     3,
       3,     0,     1,     2,     3,     1,     1,     1,     2,     1,
       4,     4,     1,     1,     4,     0,     1,     1,     1,     4,
       4,     1,     1,     3,     1,     2,     3,     1,     1,     4,
       0,     0,     2,     5,     3,     3,     1,     6,     4,     4,
       2,     4,     4,     2,     2,     4,     2,     2,     1,     3,
       3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     2,     1,   268,   267,     0,     0,    73,     0,
      23,   256,    20,     0,     0,     0,   256,    21,    18,    26,
       0,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,     0,     0,    19,   271,   269,   270,     0,
      78,     0,     0,    24,     0,     0,   265,   264,   266,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   263,   279,
     313,   261,   262,    46,     0,     0,     0,     0,     0,     0,
      53,    10,   324,     3,     5,     0,     0,     0,     0,     0,
       0,     0,     0,    68,    15,     6,     7,    66,    67,     0,
       0,   291,   306,     0,   281,   241,     0,   290,     0,   292,
       0,   309,   296,   305,   307,   312,     0,   230,   280,    29,
     331,    36,     0,    38,     0,     0,   239,     0,   172,     0,
       0,   238,   139,     0,     0,   138,   343,   344,     0,   330,
     249,     0,   259,   250,   252,   307,     0,   243,   346,   347,
      40,   291,     0,   292,   144,     0,     0,    64,     0,     0,
      75,    74,   182,     0,     0,   248,     0,   195,   294,   197,
     231,   232,   233,   234,   235,   236,   237,   130,   215,   216,
     217,   218,   240,     0,     0,     0,     0,     0,     0,     0,
     173,     0,     0,     0,    69,     0,    76,    79,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    47,   194,   196,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   130,     0,   295,   298,   315,     0,   325,   308,     0,
     336,     0,   284,    37,    39,   257,     0,     0,    45,     0,
       0,     0,   140,   292,     0,    43,   348,     0,     0,   328,
       0,   327,     0,   130,   181,     0,   308,    41,    42,     0,
       0,    44,     0,    61,    63,     0,    48,    55,     0,     0,
       0,     0,   129,   291,   292,   228,     0,   351,     9,    11,
      12,    13,     0,     0,   291,   292,     0,     0,     0,   174,
     176,     0,     0,     0,    25,     0,     0,     0,    81,     0,
       0,   350,   304,   302,     0,   201,   200,   202,   227,   221,
     219,   222,   220,   224,   226,   213,   214,   198,   199,     0,
     203,   204,   205,   206,   208,   209,   210,   211,   212,   223,
     225,     0,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,     0,   178,     0,   322,     0,   318,   301,
     317,   321,   297,   316,     0,     0,   340,   293,     0,   242,
     285,   332,   258,   171,   342,   345,     0,   137,     0,   341,
     330,   330,     0,   304,     0,   254,     0,   273,     0,     0,
     272,   145,   277,   142,     0,     0,    65,     8,     0,   133,
     244,     0,     0,   314,     0,     0,     0,     0,     0,   173,
       0,     0,     0,     0,     0,     0,   126,   248,    77,     0,
       0,    80,    83,   147,   130,   130,   303,   207,     0,     0,
     179,   247,     0,   130,   299,   315,     0,   310,   311,     0,
     335,     0,   334,   141,   349,     0,   326,     0,   260,   251,
     282,     0,   274,   275,     0,    62,    49,     0,   291,   292,
       0,    10,   108,    85,     0,    85,    87,    10,   106,    32,
       0,     0,   175,   101,   101,    35,    95,     0,    10,    93,
      52,     0,   128,   127,     0,   116,     0,    82,   147,     0,
     155,     0,     0,   229,   259,   323,     0,     0,     0,   339,
     338,     0,   329,   177,     0,   253,   289,     0,   284,   278,
     143,   136,    14,   110,   112,     0,     0,    88,     0,     0,
       0,   173,   101,     0,   101,     0,     0,     0,     0,     0,
     126,   118,     0,   155,    84,     0,   162,   154,   164,   159,
     161,   160,   163,    72,   146,     0,     0,   153,   157,     0,
     245,   246,   180,   300,   319,   320,     0,   333,   255,     0,
     276,   285,   283,   114,     0,    17,     0,    30,    86,     0,
       0,     0,    33,     0,     0,    27,    28,     0,     0,     0,
       0,    97,    96,     0,     0,    70,     0,     0,   119,    71,
       0,   167,     0,    68,   158,     0,   149,   337,   288,   287,
       0,     0,     0,   113,     0,    10,    91,    51,    50,   107,
       0,     0,    99,     0,   104,   105,    10,    98,    94,    57,
     122,     0,   121,     0,     0,     0,     0,   148,     0,     0,
       0,    10,     0,     0,     0,     0,    10,    89,    34,   100,
      10,   103,     0,    54,    56,    58,     0,   123,   120,   170,
     168,   165,     0,     0,   286,   115,     0,    31,     0,     0,
       0,   102,     0,    59,   125,     0,     0,   126,   169,     0,
     109,    92,     0,     0,   124,   166,     0,    10,    90,     0,
       0,   111,     0,   151,   150,   152,    60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    73,   174,   288,   289,    75,   566,    76,
      77,    78,    79,    80,    81,    82,   642,    83,   578,   579,
      84,   643,   644,   645,   272,   273,   149,   290,   291,   185,
      87,    88,    89,   308,    90,   310,   420,   421,   516,   465,
     638,   607,   480,   303,   475,   523,   616,   469,   514,   563,
     567,   602,   484,   485,   486,   281,   282,   124,   125,   145,
     490,   544,   684,   545,   546,   547,   548,   592,   549,   117,
     298,   299,    91,    92,    93,   132,   133,   449,   505,   116,
     264,    94,   391,   392,    95,   507,   371,   508,    96,    97,
     466,    98,    99,   233,   234,   434,   100,   101,   102,   103,
     104,   105,   364,   359,   360,   361,   106,   260,   261,   241,
     242,   107,   257,   108,   109
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -451
static const yytype_int16 yypact[] =
{
    -451,    32,  1898,  -451,  -451,  -451,   -87,  2940,  -451,  3051,
    -451,   -84,  -451,  4161,   -45,   -26,   -84,  -451,  -451,  -451,
     -88,  -451,  4161,  4161,   -11,     7,   -81,  4161,  4161,  4161,
    3162,    -9,  -451,    30,   -82,  -451,  -451,  -451,  -451,   178,
    -451,   180,  4161,  -451,  4161,    72,  -451,  -451,  -451,   -14,
     -14,  4161,  4161,  4161,  4161,  4161,  4161,  4161,  -451,   -61,
    -451,  -451,  -451,  -451,  4161,  4161,  4161,  4161,  4161,  4161,
    -451,  -451,    60,  -451,  -451,   101,   118,   122,  2829,   123,
     126,   127,   128,   146,  -451,  -451,  -451,  -451,  -451,   155,
     157,  -451,  -451,   184,  -451,  -451,  4299,  -451,    51,  1055,
     137,  -451,   189,  -451,    54,  -451,   -76,  -451,  -451,  -451,
    3273,  -451,  4365,  -451,  4428,  3384,  -451,   -74,  5331,   -14,
    4161,  -451,  -451,   -65,    -6,  -451,  5331,  5331,   -14,    -5,
     187,   190,   141,  -451,   194,    42,   -76,  5511,  5331,  5331,
    -451,   142,  5331,  1118,   151,    40,   -14,  -451,   176,   149,
    -451,  -451,  -451,  4494,   152,   154,   203,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,  3495,    28,    28,
     247,  -451,  -451,  4557,  1231,  4161,  4161,  4161,  4161,   240,
    4161,  4161,   185,   232,  -451,   191,   268,   270,    -3,  4161,
    4161,  4161,   -81,  4161,  4161,  4161,  4161,  4161,  4161,  4161,
    4161,  4161,  4161,  4161,  4161,  4161,  4161,  4161,  4161,  4161,
    4161,  4161,  4161,  4161,  4161,  4161,  -451,  -451,  -451,  4161,
    4161,  4161,  4161,  4161,  4161,  4161,  4161,  4161,  4161,  4161,
    3606,  3495,   -49,   189,  -451,  4161,  4161,    60,    82,   -14,
    5202,   167,   192,  -451,  -451,  -451,  4623,  4161,  -451,   171,
    4686,  4161,  -451,  -451,   -88,  -451,  -451,   -96,   174,  -451,
     -78,  -451,   -23,  3495,  -451,   -49,    42,  -451,  -451,   497,
     201,  -451,    18,  -451,  -451,   177,  -451,  -451,   193,    38,
     -14,   195,   211,    59,   925,  -451,   197,  -451,  -451,  -451,
    -451,  -451,   682,  4752,   319,   224,  4815,   198,   199,   218,
    5331,  4881,   205,    83,  -451,   202,   210,   228,   286,   228,
     209,   213,   216,    42,   -76,  5511,  5396,  5454,  -451,  5425,
    5425,  5425,  5425,   502,   502,    37,    37,  5568,   668,   843,
     264,  5626,  5597,    28,    28,    28,   247,   247,   247,   502,
     502,  5139,  5511,  5511,  5511,  5511,  5511,  5511,  5511,  5511,
    5511,  5511,  5511,   -28,  5511,   221,  -451,  4161,  -451,   223,
     103,  -451,  -451,  5331,   219,   909,  -451,  -451,  3717,  -451,
    3828,  -451,  -451,  5331,  -451,  -451,   974,  -451,   -14,  -451,
      -5,    -5,   222,  -451,   225,  -451,   227,   272,   497,   497,
    -451,  -451,  -451,   233,   -14,   229,  -451,  -451,   213,  -451,
    -451,  3939,   231,  -451,  2164,   -14,   -18,  2297,  4161,  4161,
    4161,    12,   497,   254,  2430,   228,     3,  -451,  -451,   228,
     234,   255,  -451,  -451,  3495,  3495,    42,  -451,  4161,   -81,
    -451,  -451,  1039,  3495,  -451,  4161,  4161,  -451,  -451,   -14,
    5331,   -14,  5269,  -451,  -451,    85,  -451,  4161,  -451,   289,
     497,   265,  -451,  -451,   497,  -451,  -451,   -14,    99,   990,
     237,  -451,  -451,   293,   -14,   293,  -451,  -451,  -451,  -451,
    4944,   241,  5331,   242,   259,  -451,  -451,   261,  -451,  -451,
    -451,   266,  -451,  -451,   263,   284,   -75,   255,  -451,   228,
       8,   277,   279,   739,   141,  -451,   281,   267,  1104,  -451,
    -451,  4050,  -451,  5511,   -49,  -451,   323,   283,   304,  -451,
    -451,  -451,  -451,  2031,   207,   -18,   288,  -451,   290,  1366,
     291,  4161,  -451,    27,  -451,     2,   497,  1499,   294,   128,
       9,   295,   316,    66,  -451,   321,  -451,  -451,  -451,  -451,
    -451,  -451,  -451,  -451,  -451,   322,   399,   161,  -451,    48,
    -451,  -451,  -451,  -451,  -451,  -451,   -14,  5331,  -451,   497,
    -451,   497,  -451,   217,  2829,  -451,   300,  -451,  -451,  2563,
    2563,   299,  -451,   301,   235,  -451,  -451,   303,  4161,   -17,
       4,  -451,  -451,   306,   128,  -451,   -33,   497,   308,  -451,
     317,   318,    63,   146,  -451,   336,  -451,  -451,  -451,   368,
     320,   324,   427,  -451,  4161,  -451,  -451,  -451,  -451,  -451,
    2696,   325,  -451,  4235,  -451,  -451,  -451,  -451,  -451,   232,
     327,   344,  -451,   497,   497,   497,   349,  -451,   351,   333,
     497,  -451,  4161,   331,  5010,  1632,  -451,  -451,  -451,  -451,
    -451,  2031,   334,  -451,   232,  -451,   497,   340,  -451,  -451,
    -451,   341,   338,   497,  -451,  2031,  5073,  -451,  2829,   342,
    1765,  2031,   228,  -451,  -451,   497,   497,     3,  -451,   343,
    -451,  -451,   346,   366,  -451,  -451,   350,  -451,  -451,   353,
      45,  2031,   128,  -451,  -451,  -451,  -451
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -451,  -451,  -451,  -451,  -450,  -451,    -2,  -451,   -83,  -451,
    -451,  -451,  -451,  -451,  -451,  -451,   310,   -59,  -451,  -451,
    -451,  -451,  -451,  -150,  -451,   106,  -451,   499,   500,   -79,
    -451,  -451,  -451,  -451,  -451,  -451,  -451,    90,    47,     0,
    -451,   -60,  -451,  -451,  -451,  -443,   -97,  -451,  -451,  -451,
    -451,  -451,  -149,  -451,   -13,  -222,  -451,  -451,   273,  -451,
      31,  -451,  -451,  -451,  -451,  -451,    -8,  -451,  -451,  -451,
    -396,  -451,    20,  -451,   -25,  -189,  -451,  -451,  -451,   512,
      35,  -158,  -355,  -451,  -451,  -451,    22,  -451,   469,   417,
    -231,   200,    17,  -451,   311,  -451,  -178,  -451,  -451,   -22,
     -20,  -451,   108,  -260,  -451,  -451,   -19,   165,   160,  -451,
    -451,  -451,  -451,  -451,   -80
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -304
static const yytype_int16 yytable[] =
{
      74,   131,   183,   318,   134,   385,   135,   136,   366,   355,
     312,   513,   482,   471,   575,   429,   575,   519,   482,   576,
     378,   576,   535,   122,   156,   156,  -248,   147,   527,   130,
      60,   525,     3,   452,   453,    60,   531,   258,   381,   575,
     379,   384,   247,   532,   576,   155,    60,   143,   110,   399,
     141,   115,   123,   148,   358,   577,   536,   476,   382,    72,
     537,   356,    60,   248,   237,   538,   158,   158,   192,   539,
     540,   541,   542,   251,   167,    72,   179,   192,   620,   574,
     535,   580,   155,    60,   383,   621,   238,   358,    60,   357,
     119,    72,   155,    60,   156,   506,   155,    60,   156,   510,
     464,   312,   144,   156,   156,   155,    60,   311,    60,   120,
     254,   390,    72,   483,   536,   614,   266,    72,   537,   483,
     615,   156,    72,   538,   128,   573,    72,   539,   540,   541,
     542,   255,   217,   218,   394,    72,   249,    72,   203,  -117,
     253,   581,   129,   617,   473,   256,   259,   543,   398,    60,
     474,   210,   211,   212,   395,   635,   270,   207,   208,   209,
     210,   211,   212,   274,   595,   146,   641,   131,   313,   314,
     134,   582,   135,   136,   463,  -131,   235,   271,    72,   626,
     236,   655,   683,    71,   284,   596,   660,   283,   235,  -302,
     661,   150,   236,   151,   295,  -131,  -156,   294,   175,   413,
     627,   381,   491,   492,   598,   589,   599,   154,   499,   536,
     500,   496,   313,   314,   156,  -134,   235,  -303,   538,   414,
     236,   502,   539,   540,   541,   542,   511,   681,   564,   565,
     390,   390,   622,   517,   406,  -134,   176,   435,   600,   565,
     494,   436,   313,   314,   558,   313,   314,   575,   284,   157,
     159,   283,   576,   177,   390,   156,   367,   178,   180,   313,
     314,   181,   182,   611,   184,   186,    71,   187,   648,   649,
     650,   188,   231,   232,  -248,   654,   263,   262,   265,   267,
     284,   269,   418,   283,   422,   275,   276,   192,   278,   167,
     279,   664,   390,   297,   426,   302,   390,   367,   668,   304,
     307,   306,   309,   369,   192,  -294,  -294,   374,   370,   380,
     674,   675,   393,   396,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   597,   358,   401,   156,   405,
     397,   400,   402,   408,   410,   412,   409,   415,   417,   193,
     194,   195,   196,   197,   198,   416,   419,   423,   424,   199,
     200,   425,   447,   156,   230,   156,   156,   431,   433,   451,
     437,   448,   450,   454,   477,   203,   456,   460,   390,   156,
     430,   489,   488,   504,   512,   509,   515,   528,   521,   522,
     156,   156,   205,   206,   207,   208,   209,   210,   211,   212,
     481,   526,   213,   214,   422,   444,   524,   259,   259,   529,
     530,   390,   462,   390,   131,   468,   559,   134,   554,   135,
     136,   274,   479,   550,   156,   551,   156,   553,   459,   560,
     561,   458,   367,   367,   569,   587,   570,   588,   572,   390,
     584,   590,   156,   591,    19,   604,   609,   610,   623,   156,
     612,   284,   284,   618,   283,   283,   629,   624,   625,   585,
     284,   630,   631,   283,   633,   647,   367,   646,   367,   632,
     651,   652,   639,   653,   534,   390,   390,   390,   657,   662,
     665,   666,   390,   667,   367,   677,   112,   679,   114,   671,
     601,   367,   118,   678,   313,   314,   680,   593,   390,   682,
     156,   126,   127,   305,   663,   390,   137,   138,   139,   142,
     455,    85,    86,     4,   619,     5,   386,   390,   390,   487,
     608,   152,   518,   153,   628,   568,   640,   586,   676,   533,
     160,   161,   162,   163,   164,   165,   166,   377,   121,   552,
     562,   156,   367,   168,   169,   170,   171,   172,   173,   594,
     252,   446,   192,   497,   362,   445,     0,     0,     0,     0,
       0,    36,    37,    38,     0,     0,     0,     0,     0,     0,
       0,     0,   603,     0,     0,     0,     0,   606,   606,    46,
      47,    48,     0,   367,     0,     0,     0,     0,     0,   240,
       0,  -304,  -304,     0,   246,     0,     0,   199,   200,   250,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     685,     0,   686,   203,     0,     0,    58,   387,   637,    61,
      62,     0,     0,     0,     0,     0,     0,     0,   388,   389,
       0,     0,   207,   208,   209,   210,   211,   212,     0,     0,
    -304,  -304,     0,     0,     0,     0,   142,   673,     0,     0,
       0,     0,     0,     0,   292,   293,   142,   296,     0,   300,
     301,     0,     0,     0,     0,     0,   670,     0,   315,   316,
     317,     0,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   189,   190,   191,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   354,
     142,     0,     0,     0,   363,   365,     0,     0,   192,     0,
       0,     0,     0,     0,     0,     0,   373,     0,     0,     0,
     376,     0,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   142,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   193,   194,   195,   196,   197,   198,     0,
       0,     0,     0,   199,   200,     0,     0,   193,   194,   195,
     196,   197,   198,     0,     0,     0,     0,   199,   200,   203,
     201,   202,     0,     0,     0,     0,     0,     0,     0,   192,
       0,     0,     0,   203,     0,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,     0,   213,   214,     0,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,     0,
     213,   214,     0,   215,   193,   194,   195,   196,   197,   198,
       0,   403,     0,     0,   199,   200,   432,   201,   202,     0,
       0,     0,     0,     0,     0,     0,     0,   440,     0,   442,
     203,     0,     0,     0,     0,     0,   189,   190,   191,     0,
       0,     0,     0,     0,     0,     0,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,     0,   213,   214,     0,
     142,     0,     0,     0,     0,     0,     0,   470,   300,   472,
       0,     0,     0,   192,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   142,   142,     0,     0,   493,     0,     0,
       0,     0,   142,     0,   363,   498,     0,     0,     0,     0,
       0,     0,   189,   190,   191,     0,   503,     0,   193,   194,
     195,   196,   197,   198,     0,     0,     0,     0,   199,   200,
       0,   201,   202,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   203,     0,     0,     0,     0,   192,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
     557,   213,   214,     0,   215,     0,     0,   189,   190,   191,
       0,     0,   427,     0,   193,   194,   195,   196,   197,   198,
     300,     0,     0,     0,   199,   200,     0,   201,   202,     0,
       0,     0,     0,     0,     0,     0,  -294,  -294,     0,     0,
     203,     0,     0,     0,   192,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,     0,   213,   214,     0,
     215,  -132,   189,   190,   191,     0,     0,   613,   438,   193,
     194,   195,   196,   197,   198,   230,     0,     0,     0,   199,
     200,  -132,   201,   202,     0,     0,     0,     0,     0,     0,
       0,  -294,  -294,   634,     0,   203,     0,     0,     0,   192,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,   656,   213,   214,     0,   215,  -135,   189,   190,   191,
       0,     0,     0,   443,   193,   194,   195,   196,   197,   198,
     230,     0,     0,     0,   199,   200,  -135,   201,   202,     0,
       0,     0,     0,     0,     0,     0,  -294,  -294,     0,     0,
     203,     0,     0,     0,   192,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,     0,   213,   214,     0,
     215,     0,     0,     0,     0,     0,     0,     0,   495,   193,
     194,   195,   196,   197,   198,   230,     0,     0,     0,   199,
     200,     0,   201,   202,     0,     0,     0,     0,     0,  -294,
    -294,     0,     0,     0,     0,   203,     0,     0,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,     0,
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,     0,   213,   214,     0,   215,     0,     4,     0,     5,
       6,     0,     7,   555,     8,     0,     9,    10,   230,    11,
      12,    13,     0,     0,    14,   268,     0,     0,     0,     0,
       0,    15,    16,     0,    17,    18,    19,    20,    21,    22,
      23,     0,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,     0,    35,    36,    37,    38,    39,     0,
      40,     0,     0,     0,     0,    41,    42,    43,     0,    44,
       0,     0,   286,    46,    47,    48,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,     0,     0,     0,     0,
       0,     0,    64,    65,     0,     0,     0,    66,    67,     0,
       0,     0,     0,     0,    68,     0,    69,     0,    70,    71,
     287,    72,     4,     0,     5,     6,     0,     7,     0,     8,
       0,     9,    10,     0,    11,    12,    13,     0,     0,    14,
       0,     0,     0,     0,     0,   571,    15,    16,     0,    17,
      18,    19,    20,    21,    22,    23,     0,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,     0,    35,
      36,    37,    38,    39,     0,    40,     0,     0,     0,     0,
      41,    42,    43,     0,    44,     0,     0,   286,    46,    47,
      48,     0,     0,     0,     0,     0,     0,    49,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     0,     0,     0,     0,     0,     0,    64,    65,     0,
       0,     0,    66,    67,     0,     0,     0,     0,     0,    68,
       0,    69,     0,    70,    71,     4,    72,     5,     6,     0,
       7,     0,     8,     0,     9,    10,     0,    11,    12,    13,
       0,     0,    14,   583,     0,     0,     0,     0,     0,    15,
      16,     0,    17,    18,    19,    20,    21,    22,    23,     0,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,     0,    35,    36,    37,    38,    39,     0,    40,     0,
       0,     0,     0,    41,    42,    43,     0,    44,     0,     0,
     286,    46,    47,    48,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,     0,     0,     0,     0,     0,     0,
      64,    65,     0,     0,     0,    66,    67,     0,     0,     0,
       0,     0,    68,     0,    69,     0,    70,    71,     4,    72,
       5,     6,     0,     7,     0,     8,     0,     9,    10,     0,
      11,    12,    13,     0,     0,    14,     0,     0,   659,     0,
       0,     0,    15,    16,     0,    17,    18,    19,    20,    21,
      22,    23,     0,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,     0,    35,    36,    37,    38,    39,
       0,    40,     0,     0,     0,     0,    41,    42,    43,     0,
      44,     0,     0,   286,    46,    47,    48,     0,     0,     0,
       0,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,     0,     0,     0,
       0,     0,     0,    64,    65,     0,     0,     0,    66,    67,
       0,     0,     0,     0,     0,    68,     0,    69,     0,    70,
      71,     4,    72,     5,     6,     0,     7,     0,     8,     0,
       9,    10,     0,    11,    12,    13,     0,     0,    14,     0,
     672,     0,     0,     0,     0,    15,    16,     0,    17,    18,
      19,    20,    21,    22,    23,     0,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,     0,    35,    36,
      37,    38,    39,     0,    40,     0,     0,     0,     0,    41,
      42,    43,     0,    44,     0,     0,   286,    46,    47,    48,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
       0,     0,     0,     0,     0,     0,    64,    65,     0,     0,
       0,    66,    67,     0,     0,     0,     0,     0,    68,     0,
      69,     0,    70,    71,     4,    72,     5,     6,     0,     7,
       0,     8,     0,     9,    10,     0,    11,    12,    13,     0,
       0,    14,     0,     0,     0,     0,     0,     0,    15,    16,
       0,    17,    18,    19,    20,    21,    22,    23,     0,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
       0,    35,    36,    37,    38,    39,     0,    40,     0,     0,
       0,     0,    41,    42,    43,     0,    44,     0,     0,    45,
      46,    47,    48,     0,     0,     0,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,     0,     0,     0,     0,     0,     0,    64,
      65,     0,     0,     0,    66,    67,     0,     0,     0,     0,
       0,    68,     0,    69,     0,    70,    71,     4,    72,     5,
       6,     0,     7,     0,     8,     0,     9,    10,     0,    11,
      12,    13,     0,     0,    14,     0,     0,     0,     0,     0,
       0,    15,    16,     0,    17,    18,    19,    20,    21,    22,
      23,     0,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,     0,    35,    36,    37,    38,    39,     0,
      40,     0,     0,     0,     0,    41,    42,    43,     0,    44,
       0,     0,   286,    46,    47,    48,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,     0,     0,     0,     0,
       0,     0,    64,    65,     0,     0,     0,    66,    67,     0,
       0,     0,     0,     0,    68,     0,    69,     0,    70,    71,
       4,    72,     5,     6,     0,     7,     0,     0,     0,     9,
      10,     0,    11,    12,    13,     0,     0,    14,     0,     0,
       0,     0,     0,     0,    15,    16,     0,    17,    18,     0,
      20,    21,    22,    23,     0,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,     0,    35,    36,    37,
      38,     0,     0,     0,     0,     0,     0,     0,     0,    42,
      43,     0,    44,     0,     0,     0,    46,    47,    48,     0,
       0,     0,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,     0,
       0,     0,     0,     0,     0,    64,    65,     0,     0,     0,
      66,    67,     0,     0,     0,     0,   461,    68,     0,    69,
       0,    70,    71,     4,    72,     5,     6,     0,     7,     0,
       0,     0,     9,    10,     0,    11,    12,    13,     0,     0,
      14,     0,     0,     0,     0,     0,     0,    15,    16,     0,
      17,    18,     0,    20,    21,    22,    23,     0,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,     0,
      35,    36,    37,    38,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    43,     0,    44,     0,     0,     0,    46,
      47,    48,     0,     0,     0,     0,     0,     0,    49,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,     0,     0,     0,     0,     0,     0,    64,    65,
       0,     0,     0,    66,    67,     0,     0,     0,     0,   467,
      68,     0,    69,     0,    70,    71,     4,    72,     5,     6,
       0,     7,     0,     0,     0,     9,    10,     0,    11,    12,
      13,     0,     0,    14,     0,     0,     0,     0,     0,     0,
      15,    16,     0,    17,    18,     0,    20,    21,    22,    23,
       0,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,     0,    35,    36,    37,    38,     0,     0,     0,
       0,     0,     0,     0,     0,    42,    43,     0,    44,     0,
       0,     0,    46,    47,    48,     0,     0,     0,     0,     0,
       0,    49,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,     0,     0,     0,     0,     0,
       0,    64,    65,     0,     0,     0,    66,    67,     0,     0,
       0,     0,   478,    68,     0,    69,     0,    70,    71,     4,
      72,     5,     6,     0,     7,     0,     0,     0,     9,    10,
       0,    11,    12,    13,     0,     0,    14,     0,     0,     0,
       0,     0,     0,    15,    16,     0,    17,    18,     0,    20,
      21,    22,    23,     0,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,     0,    35,    36,    37,    38,
       0,     0,     0,     0,     0,     0,     0,     0,    42,    43,
       0,    44,     0,     0,     0,    46,    47,    48,     0,     0,
       0,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,     0,     0,
       0,     0,     0,     0,    64,    65,     0,     0,     0,    66,
      67,     0,     0,     0,     0,   605,    68,     0,    69,     0,
      70,    71,     4,    72,     5,     6,     0,     7,     0,     0,
       0,     9,    10,     0,    11,    12,    13,     0,     0,    14,
       0,     0,     0,     0,     0,     0,    15,    16,     0,    17,
      18,     0,    20,    21,    22,    23,     0,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,     0,    35,
      36,    37,    38,     0,     0,     0,     0,     0,     0,     0,
       0,    42,    43,     0,    44,     0,     0,     0,    46,    47,
      48,     0,     0,     0,     0,     0,     0,    49,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     0,     0,     0,     0,     0,     0,    64,    65,     0,
       0,     0,    66,    67,     0,     0,     0,     0,   636,    68,
       0,    69,     0,    70,    71,     4,    72,     5,     6,     0,
       7,     0,     0,     0,     9,    10,     0,    11,    12,    13,
       0,     0,    14,     0,     0,     0,     0,     0,     0,    15,
      16,     0,    17,    18,     0,    20,    21,    22,    23,     0,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,     0,    35,    36,    37,    38,     0,     0,     0,     0,
       0,     0,     0,     0,    42,    43,     0,    44,     0,     0,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,     0,     0,     4,     0,     5,     6,
      64,    65,     0,     0,     0,    66,    67,     0,    11,     0,
       0,     0,    68,    14,    69,     0,    70,    71,     0,    72,
      15,    16,     0,     0,     0,     0,     0,     0,    22,    23,
       0,    24,    25,    26,    27,    28,    29,     0,     0,     0,
       0,     0,     0,     0,    36,    37,    38,     0,     0,     0,
       0,     0,     0,     0,     0,    42,     0,     0,     0,     0,
       0,     0,    46,    47,    48,     0,     0,     0,     0,     0,
       0,    49,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,     0,     0,     0,     4,     0,     5,
       6,    64,    65,     0,     0,     0,    66,    67,     0,    11,
       0,     0,     0,    68,    14,    69,     0,   111,     0,     0,
      72,    15,    16,     0,     0,     0,     0,     0,     0,    22,
      23,     0,    24,    25,    26,    27,    28,    29,     0,     0,
       0,     0,     0,     0,     0,    36,    37,    38,     0,     0,
       0,     0,     0,     0,     0,     0,    42,     0,     0,     0,
       0,     0,     0,    46,    47,    48,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,     0,     0,     0,     4,     0,
       5,     6,    64,    65,     0,     0,     0,    66,    67,     0,
      11,     0,     0,     0,    68,    14,    69,     0,   113,     0,
       0,    72,    15,    16,     0,     0,     0,     0,     0,     0,
      22,    23,     0,    24,    25,    26,    27,    28,    29,     0,
       0,     0,     0,     0,     0,     0,    36,    37,    38,     0,
       0,     0,     0,     0,     0,     0,     0,    42,     0,     0,
       0,     0,     0,     0,    46,    47,    48,     0,     0,     0,
       0,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,     0,     0,     0,     4,
       0,     5,     6,    64,    65,     0,     0,     0,    66,    67,
       0,    11,     0,     0,     0,    68,    14,    69,     0,   140,
       0,     0,    72,    15,    16,     0,     0,     0,     0,     0,
       0,    22,    23,     0,    24,    25,    26,    27,    28,    29,
       0,     0,     0,     0,     0,     0,     0,    36,    37,    38,
       0,     0,     0,     0,     0,     0,     0,     0,    42,     0,
       0,     0,     0,     0,     0,    46,    47,    48,     0,     0,
       0,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,     0,     0,     0,
       4,   239,     5,     6,    64,    65,     0,     0,     0,    66,
      67,     0,    11,     0,     0,     0,    68,    14,    69,     0,
       0,     0,     0,    72,    15,    16,     0,     0,     0,     0,
       0,     0,    22,    23,     0,    24,    25,    26,    27,    28,
      29,     0,     0,     0,     0,     0,     0,     0,    36,    37,
      38,     0,     0,     0,     0,     0,     0,     0,     0,    42,
       0,     0,     0,     0,     0,     0,    46,    47,    48,     0,
       0,     0,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,     0,     0,
       0,     4,     0,     5,     6,    64,    65,     0,     0,     0,
      66,    67,     0,    11,     0,     0,     0,    68,    14,    69,
     245,     0,     0,     0,    72,    15,    16,     0,     0,     0,
       0,     0,     0,    22,    23,     0,    24,    25,    26,    27,
      28,    29,     0,     0,     0,     0,     0,     0,     0,    36,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
      42,     0,     0,     0,     0,     0,     0,    46,    47,    48,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,     0,
       0,     0,     4,   280,     5,     6,    64,    65,     0,     0,
       0,    66,    67,     0,    11,     0,     0,     0,    68,    14,
      69,     0,     0,     0,     0,    72,    15,    16,     0,     0,
       0,     0,     0,     0,    22,    23,     0,    24,    25,    26,
      27,    28,    29,     0,     0,     0,     0,     0,     0,     0,
      36,    37,    38,     0,     0,     0,     0,     0,     0,     0,
       0,    42,     0,     0,     0,     0,     0,     0,    46,    47,
      48,     0,     0,     0,     0,     0,     0,    49,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
       0,     0,     0,     4,   353,     5,     6,    64,    65,     0,
       0,     0,    66,    67,     0,    11,     0,     0,     0,    68,
      14,    69,     0,     0,     0,     0,    72,    15,    16,     0,
       0,     0,     0,     0,     0,    22,    23,     0,    24,    25,
      26,    27,    28,    29,     0,     0,     0,     0,     0,     0,
       0,    36,    37,    38,     0,     0,     0,     0,     0,     0,
       0,     0,    42,     0,     0,     0,     0,     0,     0,    46,
      47,    48,     0,     0,     0,     0,     0,     0,    49,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,     0,     0,     0,     4,   439,     5,     6,    64,    65,
       0,     0,     0,    66,    67,     0,    11,     0,     0,     0,
      68,    14,    69,     0,     0,     0,     0,    72,    15,    16,
       0,     0,     0,     0,     0,     0,    22,    23,     0,    24,
      25,    26,    27,    28,    29,     0,     0,     0,     0,     0,
       0,     0,    36,    37,    38,     0,     0,     0,     0,     0,
       0,     0,     0,    42,     0,     0,     0,     0,     0,     0,
      46,    47,    48,     0,     0,     0,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,     0,     0,     0,     4,   441,     5,     6,    64,
      65,     0,     0,     0,    66,    67,     0,    11,     0,     0,
       0,    68,    14,    69,     0,     0,     0,     0,    72,    15,
      16,     0,     0,     0,     0,     0,     0,    22,    23,     0,
      24,    25,    26,    27,    28,    29,     0,     0,     0,     0,
       0,     0,     0,    36,    37,    38,     0,     0,     0,     0,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,     0,     0,     0,     4,   457,     5,     6,
      64,    65,     0,     0,     0,    66,    67,     0,    11,     0,
       0,     0,    68,    14,    69,     0,     0,     0,     0,    72,
      15,    16,     0,     0,     0,     0,     0,     0,    22,    23,
       0,    24,    25,    26,    27,    28,    29,     0,     0,     0,
       0,     0,     0,     0,    36,    37,    38,     0,     0,     0,
       0,     0,     0,     0,     0,    42,     0,     0,     0,     0,
       0,     0,    46,    47,    48,     0,     0,     0,     0,     0,
       0,    49,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,     0,     0,     0,     4,   556,     5,
       6,    64,    65,     0,     0,     0,    66,    67,     0,    11,
       0,     0,     0,    68,    14,    69,     0,     0,     0,     0,
      72,    15,    16,     0,     0,     0,     0,     0,     0,    22,
      23,     0,    24,    25,    26,    27,    28,    29,     0,     0,
       0,     0,     0,     0,     0,    36,    37,    38,     0,     0,
       0,     0,     0,     0,     0,     0,    42,     0,     0,     0,
       0,     0,     0,    46,    47,    48,     0,     0,   189,   190,
     191,     0,    49,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,   192,     0,     0,     0,     0,
       0,     0,    64,    65,     0,     0,     0,    66,    67,     0,
       0,     0,     0,     0,    68,     0,    69,     0,     0,     0,
       0,    72,   189,   190,   191,     0,     0,     0,     0,     0,
     193,   194,   195,   196,   197,   198,     0,     0,     0,     0,
     199,   200,     0,   201,   202,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   203,     0,     0,   192,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   204,   205,   206,   207,   208,   209,   210,   211,
     212,     0,     0,   213,   214,     0,   215,   614,   189,   190,
     191,     0,   615,     0,   193,   194,   195,   196,   197,   198,
       0,     0,     0,     0,   199,   200,     0,   201,   202,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     203,     0,     0,     0,     0,   192,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,     0,   213,   214,     0,
     215,   189,   190,   191,     0,     0,   216,     0,     0,     0,
     193,   194,   195,   196,   197,   198,     0,     0,     0,     0,
     199,   200,     0,   201,   202,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   203,     0,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   204,   205,   206,   207,   208,   209,   210,   211,
     212,     0,     0,   213,   214,     0,   215,   189,   190,   191,
       0,     0,   243,   193,   194,   195,   196,   197,   198,     0,
       0,     0,     0,   199,   200,     0,   201,   202,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   203,
       0,     0,     0,     0,   192,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,     0,   213,   214,     0,   215,
     189,   190,   191,     0,     0,   244,     0,     0,     0,   193,
     194,   195,   196,   197,   198,     0,     0,     0,     0,   199,
     200,     0,   201,   202,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   203,     0,   192,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,     0,   213,   214,     0,   215,   189,   190,   191,     0,
       0,   277,   193,   194,   195,   196,   197,   198,     0,     0,
       0,     0,   199,   200,     0,   201,   202,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   203,     0,
       0,     0,     0,   192,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   204,   205,   206,   207,   208,   209,
     210,   211,   212,     0,     0,   213,   214,     0,   215,   189,
     190,   191,     0,   285,     0,     0,     0,     0,   193,   194,
     195,   196,   197,   198,     0,     0,     0,     0,   199,   200,
       0,   201,   202,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   203,     0,   192,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
       0,   213,   214,     0,   215,   189,   190,   191,     0,   372,
       0,   193,   194,   195,   196,   197,   198,     0,     0,     0,
       0,   199,   200,     0,   201,   202,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   203,     0,     0,
       0,     0,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,     0,   213,   214,     0,   215,   189,   190,
     191,     0,   375,     0,     0,     0,     0,   193,   194,   195,
     196,   197,   198,     0,     0,     0,     0,   199,   200,     0,
     201,   202,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   203,     0,   192,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,     0,
     213,   214,     0,   215,   189,   190,   191,     0,   404,     0,
     193,   194,   195,   196,   197,   198,     0,     0,     0,     0,
     199,   200,     0,   201,   202,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   203,     0,     0,     0,
       0,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   204,   205,   206,   207,   208,   209,   210,   211,
     212,     0,     0,   213,   214,     0,   215,   189,   190,   191,
       0,   407,     0,     0,     0,     0,   193,   194,   195,   196,
     197,   198,     0,     0,     0,     0,   199,   200,     0,   201,
     202,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   203,     0,   192,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,     0,   213,
     214,     0,   215,   189,   190,   191,     0,   411,     0,   193,
     194,   195,   196,   197,   198,     0,     0,     0,     0,   199,
     200,     0,   201,   202,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   203,     0,     0,     0,     0,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,     0,   213,   214,     0,   215,   189,   190,   191,     0,
     520,     0,     0,     0,     0,   193,   194,   195,   196,   197,
     198,     0,     0,     0,     0,   199,   200,     0,   201,   202,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   203,     0,   192,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   204,   205,   206,
     207,   208,   209,   210,   211,   212,     0,     0,   213,   214,
       0,   215,   189,   190,   191,     0,   658,     0,   193,   194,
     195,   196,   197,   198,     0,     0,     0,     0,   199,   200,
       0,   201,   202,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   203,     0,     0,     0,     0,   192,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
       0,   213,   214,     0,   215,   189,   190,   191,     0,   669,
       0,     0,     0,     0,   193,   194,   195,   196,   197,   198,
       0,     0,     0,     0,   199,   200,     0,   201,   202,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     203,     0,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,     0,   213,   214,     0,
     215,   428,   189,   190,   191,     0,     0,   193,   194,   195,
     196,   197,   198,     0,     0,   368,     0,   199,   200,     0,
     201,   202,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   203,     0,     0,     0,     0,     0,   192,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,     0,
     213,   214,     0,   215,   189,   190,   191,     0,     0,     0,
       0,     0,     0,     0,   193,   194,   195,   196,   197,   198,
       0,     0,   501,     0,   199,   200,     0,   201,   202,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     203,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,     0,   213,   214,   189,
     215,   191,     0,     0,     0,     0,   193,   194,   195,   196,
     197,   198,     0,     0,     0,     0,   199,   200,     0,   201,
     202,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   203,     0,     0,     0,   192,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   189,     0,   213,
     214,     0,   215,     0,     0,   192,     0,     0,     0,     0,
       0,   193,   194,   195,   196,   197,   198,     0,     0,     0,
       0,   199,   200,     0,   201,   202,     0,     0,     0,     0,
       0,     0,     0,     0,   192,     0,     0,   203,     0,     0,
    -304,  -304,  -304,  -304,   197,   198,     0,     0,     0,     0,
     199,   200,     0,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,     0,   213,   214,   203,   215,     0,   193,
     194,   195,   196,   197,   198,     0,     0,     0,     0,   199,
     200,     0,   201,   202,     0,   207,   208,   209,   210,   211,
     212,   192,     0,   213,   214,   203,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,     0,   213,   214,     0,   215,   193,   194,   195,   196,
     197,   198,     0,     0,     0,     0,   199,   200,     0,   201,
     202,     0,     0,     0,     0,     0,     0,     0,   192,     0,
       0,     0,   203,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   192,     0,   213,
     214,     0,   215,   193,   194,   195,   196,   197,   198,     0,
       0,     0,     0,   199,   200,     0,     0,   202,     0,     0,
       0,     0,     0,     0,     0,     0,   192,     0,     0,   203,
       0,     0,   193,   194,   195,   196,   197,   198,     0,     0,
       0,     0,   199,   200,     0,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,     0,   213,   214,   203,     0,
       0,   193,   194,   195,   196,   197,   198,     0,     0,     0,
       0,   199,   200,     0,     0,   205,     0,   207,   208,   209,
     210,   211,   212,     0,     0,   213,   214,   203,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   207,   208,   209,   210,
     211,   212,     0,     0,   213,   214
};

static const yytype_int16 yycheck[] =
{
       2,    26,    82,   192,    26,   265,    26,    26,   239,   231,
     188,   461,     9,   409,    12,    43,    12,   467,     9,    17,
     116,    17,    14,   111,    49,    50,    87,   109,   478,   110,
     111,   474,     0,   388,   389,   111,   111,    42,   116,    12,
     136,   263,   116,   118,    17,   110,   111,    30,   135,   280,
      30,   135,   140,   135,   232,    28,    48,   412,   136,   140,
      52,   110,   111,   137,   140,    57,    49,    50,    40,    61,
      62,    63,    64,   138,   135,   140,    78,    40,   111,   522,
      14,   524,   110,   111,   262,   118,   106,   265,   111,   138,
     135,   140,   110,   111,   119,   450,   110,   111,   123,   454,
     118,   279,   111,   128,   129,   110,   111,   110,   111,   135,
     116,   269,   140,   110,    48,   132,   136,   140,    52,   110,
     137,   146,   140,    57,   135,   521,   140,    61,    62,    63,
      64,   137,    81,    82,   116,   140,   119,   140,   101,   136,
     123,   139,   135,   139,   132,   128,   129,   139,   110,   111,
     138,   123,   124,   125,   136,   605,   116,   120,   121,   122,
     123,   124,   125,   146,   116,   135,   616,   192,   188,   188,
     192,   526,   192,   192,   405,   116,   134,   137,   140,   116,
     138,   631,   137,   138,   167,   137,   636,   167,   134,   135,
     640,    13,   138,    13,   177,   136,    35,   177,   138,   116,
     137,   116,   424,   425,   559,   139,   561,   135,   439,    48,
     441,   433,   232,   232,   239,   116,   134,   135,    57,   136,
     138,   136,    61,    62,    63,    64,   457,   677,    21,    22,
     388,   389,   587,   464,    10,   136,   135,   134,    21,    22,
     429,   138,   262,   262,   504,   265,   265,    12,   231,    49,
      50,   231,    17,   135,   412,   280,   239,   135,   135,   279,
     279,   135,   135,    28,   118,   110,   138,   110,   623,   624,
     625,    87,   135,    84,    87,   630,   135,    87,    84,   137,
     263,   130,   307,   263,   309,   109,   137,    40,   136,   135,
      87,   646,   450,    53,   314,   110,   454,   280,   653,    67,
      32,   110,    32,   136,    40,    81,    82,   136,   116,   135,
     665,   666,   111,   136,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   556,   504,   116,   353,    10,
     137,   136,   135,   135,   116,   130,   137,   135,   110,    75,
      76,    77,    78,    79,    80,   135,    60,   138,   135,    85,
      86,   135,   130,   378,   130,   380,   381,   136,   135,    87,
     141,   136,   135,   130,   110,   101,   137,   136,   526,   394,
     353,   116,   138,    84,   137,   110,    83,   111,   137,   137,
     405,   406,   118,   119,   120,   121,   122,   123,   124,   125,
     415,   130,   128,   129,   419,   378,   137,   380,   381,   136,
     116,   559,   404,   561,   429,   407,    83,   429,   141,   429,
     429,   394,   414,   136,   439,   136,   441,   136,   401,   136,
     116,   401,   405,   406,   136,   130,   136,   111,   137,   587,
     136,   110,   457,   111,    35,   135,   137,   136,   130,   464,
     137,   424,   425,   137,   424,   425,   110,   130,   130,   529,
     433,    83,   132,   433,    27,   111,   439,   130,   441,   135,
     111,   110,   137,   130,   489,   623,   624,   625,   137,   135,
     130,   130,   630,   135,   457,   132,     7,   111,     9,   137,
     563,   464,    13,   137,   504,   504,   136,   546,   646,   136,
     515,    22,    23,   183,   644,   653,    27,    28,    29,    30,
     394,     2,     2,     6,   584,     8,     9,   665,   666,   419,
     570,    42,   465,    44,   593,   515,   613,   530,   667,   488,
      51,    52,    53,    54,    55,    56,    57,   254,    16,   494,
     508,   556,   515,    64,    65,    66,    67,    68,    69,   547,
     123,   381,    40,   435,   233,   380,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   564,    -1,    -1,    -1,    -1,   569,   570,    72,
      73,    74,    -1,   556,    -1,    -1,    -1,    -1,    -1,   110,
      -1,    79,    80,    -1,   115,    -1,    -1,    85,    86,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     680,    -1,   682,   101,    -1,    -1,   109,   110,   610,   112,
     113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,
      -1,    -1,   120,   121,   122,   123,   124,   125,    -1,    -1,
     128,   129,    -1,    -1,    -1,    -1,   167,   662,    -1,    -1,
      -1,    -1,    -1,    -1,   175,   176,   177,   178,    -1,   180,
     181,    -1,    -1,    -1,    -1,    -1,   658,    -1,   189,   190,
     191,    -1,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,     3,     4,     5,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,    -1,    -1,    -1,   235,   236,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,
     251,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   263,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    85,    86,    -1,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,   101,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,   101,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,   125,    -1,    -1,   128,   129,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,   125,    -1,    -1,
     128,   129,    -1,   131,    75,    76,    77,    78,    79,    80,
      -1,   139,    -1,    -1,    85,    86,   357,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   368,    -1,   370,
     101,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   122,   123,   124,   125,    -1,    -1,   128,   129,    -1,
     401,    -1,    -1,    -1,    -1,    -1,    -1,   408,   409,   410,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   424,   425,    -1,    -1,   428,    -1,    -1,
      -1,    -1,   433,    -1,   435,   436,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,   447,    -1,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,   125,    -1,
     501,   128,   129,    -1,   131,    -1,    -1,     3,     4,     5,
      -1,    -1,   139,    -1,    75,    76,    77,    78,    79,    80,
     521,    -1,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
     101,    -1,    -1,    -1,    40,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   117,   118,   119,   120,
     121,   122,   123,   124,   125,    -1,    -1,   128,   129,    -1,
     131,   116,     3,     4,     5,    -1,    -1,   578,   139,    75,
      76,    77,    78,    79,    80,   130,    -1,    -1,    -1,    85,
      86,   136,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,   604,    -1,   101,    -1,    -1,    -1,    40,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      -1,   632,   128,   129,    -1,   131,   116,     3,     4,     5,
      -1,    -1,    -1,   139,    75,    76,    77,    78,    79,    80,
     130,    -1,    -1,    -1,    85,    86,   136,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
     101,    -1,    -1,    -1,    40,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   117,   118,   119,   120,
     121,   122,   123,   124,   125,    -1,    -1,   128,   129,    -1,
     131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    75,
      76,    77,    78,    79,    80,   130,    -1,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,   101,    -1,    -1,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    -1,
      -1,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      -1,    -1,   128,   129,    -1,   131,    -1,     6,    -1,     8,
       9,    -1,    11,   139,    13,    -1,    15,    16,   130,    18,
      19,    20,    -1,    -1,    23,   137,    -1,    -1,    -1,    -1,
      -1,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    -1,
      59,    -1,    -1,    -1,    -1,    64,    65,    66,    -1,    68,
      -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,    -1,    -1,    -1,    -1,
      -1,    -1,   121,   122,    -1,    -1,    -1,   126,   127,    -1,
      -1,    -1,    -1,    -1,   133,    -1,   135,    -1,   137,   138,
     139,   140,     6,    -1,     8,     9,    -1,    11,    -1,    13,
      -1,    15,    16,    -1,    18,    19,    20,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,    33,
      34,    35,    36,    37,    38,    39,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    -1,    53,
      54,    55,    56,    57,    -1,    59,    -1,    -1,    -1,    -1,
      64,    65,    66,    -1,    68,    -1,    -1,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,    -1,
      -1,    -1,   126,   127,    -1,    -1,    -1,    -1,    -1,   133,
      -1,   135,    -1,   137,   138,     6,   140,     8,     9,    -1,
      11,    -1,    13,    -1,    15,    16,    -1,    18,    19,    20,
      -1,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,    33,    34,    35,    36,    37,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    -1,    53,    54,    55,    56,    57,    -1,    59,    -1,
      -1,    -1,    -1,    64,    65,    66,    -1,    68,    -1,    -1,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,
     121,   122,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,
      -1,    -1,   133,    -1,   135,    -1,   137,   138,     6,   140,
       8,     9,    -1,    11,    -1,    13,    -1,    15,    16,    -1,
      18,    19,    20,    -1,    -1,    23,    -1,    -1,    26,    -1,
      -1,    -1,    30,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    -1,    53,    54,    55,    56,    57,
      -1,    59,    -1,    -1,    -1,    -1,    64,    65,    66,    -1,
      68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,    -1,    -1,    -1,
      -1,    -1,    -1,   121,   122,    -1,    -1,    -1,   126,   127,
      -1,    -1,    -1,    -1,    -1,   133,    -1,   135,    -1,   137,
     138,     6,   140,     8,     9,    -1,    11,    -1,    13,    -1,
      15,    16,    -1,    18,    19,    20,    -1,    -1,    23,    -1,
      25,    -1,    -1,    -1,    -1,    30,    31,    -1,    33,    34,
      35,    36,    37,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    -1,    59,    -1,    -1,    -1,    -1,    64,
      65,    66,    -1,    68,    -1,    -1,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
      -1,    -1,    -1,    -1,    -1,    -1,   121,   122,    -1,    -1,
      -1,   126,   127,    -1,    -1,    -1,    -1,    -1,   133,    -1,
     135,    -1,   137,   138,     6,   140,     8,     9,    -1,    11,
      -1,    13,    -1,    15,    16,    -1,    18,    19,    20,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,    33,    34,    35,    36,    37,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    54,    55,    56,    57,    -1,    59,    -1,    -1,
      -1,    -1,    64,    65,    66,    -1,    68,    -1,    -1,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,   121,
     122,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,    -1,
      -1,   133,    -1,   135,    -1,   137,   138,     6,   140,     8,
       9,    -1,    11,    -1,    13,    -1,    15,    16,    -1,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    -1,
      59,    -1,    -1,    -1,    -1,    64,    65,    66,    -1,    68,
      -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,    -1,    -1,    -1,    -1,
      -1,    -1,   121,   122,    -1,    -1,    -1,   126,   127,    -1,
      -1,    -1,    -1,    -1,   133,    -1,   135,    -1,   137,   138,
       6,   140,     8,     9,    -1,    11,    -1,    -1,    -1,    15,
      16,    -1,    18,    19,    20,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    -1,    33,    34,    -1,
      36,    37,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    -1,    68,    -1,    -1,    -1,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,    -1,
      -1,    -1,    -1,    -1,    -1,   121,   122,    -1,    -1,    -1,
     126,   127,    -1,    -1,    -1,    -1,   132,   133,    -1,   135,
      -1,   137,   138,     6,   140,     8,     9,    -1,    11,    -1,
      -1,    -1,    15,    16,    -1,    18,    19,    20,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      33,    34,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    -1,    68,    -1,    -1,    -1,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,
      -1,    -1,    -1,   126,   127,    -1,    -1,    -1,    -1,   132,
     133,    -1,   135,    -1,   137,   138,     6,   140,     8,     9,
      -1,    11,    -1,    -1,    -1,    15,    16,    -1,    18,    19,
      20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    -1,    33,    34,    -1,    36,    37,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    -1,    53,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    -1,    68,    -1,
      -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,    -1,    -1,    -1,    -1,    -1,
      -1,   121,   122,    -1,    -1,    -1,   126,   127,    -1,    -1,
      -1,    -1,   132,   133,    -1,   135,    -1,   137,   138,     6,
     140,     8,     9,    -1,    11,    -1,    -1,    -1,    15,    16,
      -1,    18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    -1,    33,    34,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    -1,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      -1,    68,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    -1,    -1,
      -1,    -1,    -1,    -1,   121,   122,    -1,    -1,    -1,   126,
     127,    -1,    -1,    -1,    -1,   132,   133,    -1,   135,    -1,
     137,   138,     6,   140,     8,     9,    -1,    11,    -1,    -1,
      -1,    15,    16,    -1,    18,    19,    20,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    33,
      34,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    -1,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    -1,    68,    -1,    -1,    -1,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,    -1,
      -1,    -1,   126,   127,    -1,    -1,    -1,    -1,   132,   133,
      -1,   135,    -1,   137,   138,     6,   140,     8,     9,    -1,
      11,    -1,    -1,    -1,    15,    16,    -1,    18,    19,    20,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,    33,    34,    -1,    36,    37,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    -1,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    -1,    68,    -1,    -1,
      -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,    -1,    -1,     6,    -1,     8,     9,
     121,   122,    -1,    -1,    -1,   126,   127,    -1,    18,    -1,
      -1,    -1,   133,    23,   135,    -1,   137,   138,    -1,   140,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,    -1,    -1,    -1,     6,    -1,     8,
       9,   121,   122,    -1,    -1,    -1,   126,   127,    -1,    18,
      -1,    -1,    -1,   133,    23,   135,    -1,   137,    -1,    -1,
     140,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    -1,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    -1,    -1,    -1,     6,    -1,
       8,     9,   121,   122,    -1,    -1,    -1,   126,   127,    -1,
      18,    -1,    -1,    -1,   133,    23,   135,    -1,   137,    -1,
      -1,   140,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,    -1,    -1,    -1,     6,
      -1,     8,     9,   121,   122,    -1,    -1,    -1,   126,   127,
      -1,    18,    -1,    -1,    -1,   133,    23,   135,    -1,   137,
      -1,    -1,   140,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    -1,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,    -1,    -1,    -1,
       6,   118,     8,     9,   121,   122,    -1,    -1,    -1,   126,
     127,    -1,    18,    -1,    -1,    -1,   133,    23,   135,    -1,
      -1,    -1,    -1,   140,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,    -1,    -1,
      -1,     6,    -1,     8,     9,   121,   122,    -1,    -1,    -1,
     126,   127,    -1,    18,    -1,    -1,    -1,   133,    23,   135,
     136,    -1,    -1,    -1,   140,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,    -1,
      -1,    -1,     6,   118,     8,     9,   121,   122,    -1,    -1,
      -1,   126,   127,    -1,    18,    -1,    -1,    -1,   133,    23,
     135,    -1,    -1,    -1,    -1,   140,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    -1,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
      -1,    -1,    -1,     6,   118,     8,     9,   121,   122,    -1,
      -1,    -1,   126,   127,    -1,    18,    -1,    -1,    -1,   133,
      23,   135,    -1,    -1,    -1,    -1,   140,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    -1,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,    -1,    -1,    -1,     6,   118,     8,     9,   121,   122,
      -1,    -1,    -1,   126,   127,    -1,    18,    -1,    -1,    -1,
     133,    23,   135,    -1,    -1,    -1,    -1,   140,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,    -1,    -1,    -1,     6,   118,     8,     9,   121,
     122,    -1,    -1,    -1,   126,   127,    -1,    18,    -1,    -1,
      -1,   133,    23,   135,    -1,    -1,    -1,    -1,   140,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,    -1,    -1,    -1,     6,   118,     8,     9,
     121,   122,    -1,    -1,    -1,   126,   127,    -1,    18,    -1,
      -1,    -1,   133,    23,   135,    -1,    -1,    -1,    -1,   140,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,    -1,    -1,    -1,     6,   118,     8,
       9,   121,   122,    -1,    -1,    -1,   126,   127,    -1,    18,
      -1,    -1,    -1,   133,    23,   135,    -1,    -1,    -1,    -1,
     140,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    -1,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    -1,    -1,     3,     4,
       5,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    40,    -1,    -1,    -1,    -1,
      -1,    -1,   121,   122,    -1,    -1,    -1,   126,   127,    -1,
      -1,    -1,    -1,    -1,   133,    -1,   135,    -1,    -1,    -1,
      -1,   140,     3,     4,     5,    -1,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
     125,    -1,    -1,   128,   129,    -1,   131,   132,     3,     4,
       5,    -1,   137,    -1,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   122,   123,   124,   125,    -1,    -1,   128,   129,    -1,
     131,     3,     4,     5,    -1,    -1,   137,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
     125,    -1,    -1,   128,   129,    -1,   131,     3,     4,     5,
      -1,    -1,   137,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,   125,    -1,    -1,   128,   129,    -1,   131,
       3,     4,     5,    -1,    -1,   137,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      -1,    -1,   128,   129,    -1,   131,     3,     4,     5,    -1,
      -1,   137,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,   125,    -1,    -1,   128,   129,    -1,   131,     3,
       4,     5,    -1,   136,    -1,    -1,    -1,    -1,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,   125,    -1,
      -1,   128,   129,    -1,   131,     3,     4,     5,    -1,   136,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,   119,   120,   121,   122,   123,
     124,   125,    -1,    -1,   128,   129,    -1,   131,     3,     4,
       5,    -1,   136,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,   125,    -1,    -1,
     128,   129,    -1,   131,     3,     4,     5,    -1,   136,    -1,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
     125,    -1,    -1,   128,   129,    -1,   131,     3,     4,     5,
      -1,   136,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   101,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    -1,    -1,   128,
     129,    -1,   131,     3,     4,     5,    -1,   136,    -1,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      -1,    -1,   128,   129,    -1,   131,     3,     4,     5,    -1,
     136,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,   125,    -1,    -1,   128,   129,
      -1,   131,     3,     4,     5,    -1,   136,    -1,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,   125,    -1,
      -1,   128,   129,    -1,   131,     3,     4,     5,    -1,   136,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   122,   123,   124,   125,    -1,    -1,   128,   129,    -1,
     131,   132,     3,     4,     5,    -1,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    83,    -1,    85,    86,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,   125,    -1,    -1,
     128,   129,    -1,   131,     3,     4,     5,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      -1,    -1,    83,    -1,    85,    86,    -1,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   122,   123,   124,   125,    -1,    -1,   128,   129,     3,
     131,     5,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   101,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,   125,     3,    -1,   128,
     129,    -1,   131,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,   101,    -1,    -1,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    -1,   117,   118,   119,   120,   121,   122,   123,
     124,   125,    -1,    -1,   128,   129,   101,   131,    -1,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,   120,   121,   122,   123,   124,
     125,    40,    -1,   128,   129,   101,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      -1,    -1,   128,   129,    -1,   131,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    40,    -1,   128,
     129,    -1,   131,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    85,    86,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,   101,
      -1,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    85,    86,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,   125,    -1,    -1,   128,   129,   101,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    -1,    -1,   118,    -1,   120,   121,   122,
     123,   124,   125,    -1,    -1,   128,   129,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   120,   121,   122,   123,
     124,   125,    -1,    -1,   128,   129
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   143,   144,     0,     6,     8,     9,    11,    13,    15,
      16,    18,    19,    20,    23,    30,    31,    33,    34,    35,
      36,    37,    38,    39,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    53,    54,    55,    56,    57,
      59,    64,    65,    66,    68,    71,    72,    73,    74,    81,
      82,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   121,   122,   126,   127,   133,   135,
     137,   138,   140,   145,   148,   149,   151,   152,   153,   154,
     155,   156,   157,   159,   162,   169,   170,   172,   173,   174,
     176,   214,   215,   216,   223,   226,   230,   231,   233,   234,
     238,   239,   240,   241,   242,   243,   248,   253,   255,   256,
     135,   137,   230,   137,   230,   135,   221,   211,   230,   135,
     135,   221,   111,   140,   199,   200,   230,   230,   135,   135,
     110,   216,   217,   218,   241,   242,   248,   230,   230,   230,
     137,   214,   230,   234,   111,   201,   135,   109,   135,   168,
      13,    13,   230,   230,   135,   110,   216,   233,   234,   233,
     230,   230,   230,   230,   230,   230,   230,   135,   230,   230,
     230,   230,   230,   230,   146,   138,   135,   135,   135,   148,
     135,   135,   135,   256,   118,   171,   110,   110,    87,     3,
       4,     5,    40,    75,    76,    77,    78,    79,    80,    85,
      86,    88,    89,   101,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   128,   129,   131,   137,    81,    82,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     130,   135,    84,   235,   236,   134,   138,   140,   242,   118,
     230,   251,   252,   137,   137,   136,   230,   116,   137,   234,
     230,   138,   231,   234,   116,   137,   234,   254,    42,   234,
     249,   250,    87,   135,   222,    84,   242,   137,   137,   130,
     116,   137,   166,   167,   234,   109,   137,   137,   136,    87,
     118,   197,   198,   214,   234,   136,    71,   139,   147,   148,
     169,   170,   230,   230,   214,   234,   230,    53,   212,   213,
     230,   230,   110,   185,    67,   158,   110,    32,   175,    32,
     177,   110,   238,   242,   248,   230,   230,   230,   217,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   118,   230,   197,   110,   138,   238,   245,
     246,   247,   236,   230,   244,   230,   232,   234,    83,   136,
     116,   228,   136,   230,   136,   136,   230,   200,   116,   136,
     135,   116,   136,   238,   197,   245,     9,   110,   121,   122,
     223,   224,   225,   111,   116,   136,   136,   137,   110,   232,
     136,   116,   135,   139,   136,    10,    10,   136,   135,   137,
     116,   136,   130,   116,   136,   135,   135,   110,   216,    60,
     178,   179,   216,   138,   135,   135,   242,   139,   132,    43,
     234,   136,   230,   135,   237,   134,   138,   141,   139,   118,
     230,   118,   230,   139,   234,   249,   250,   130,   136,   219,
     135,    87,   224,   224,   130,   167,   137,   118,   214,   234,
     136,   132,   148,   232,   118,   181,   232,   132,   148,   189,
     230,   212,   230,   132,   138,   186,   224,   110,   132,   148,
     184,   216,     9,   110,   194,   195,   196,   179,   138,   116,
     202,   197,   197,   230,   217,   139,   197,   244,   230,   232,
     232,    83,   136,   230,    84,   220,   224,   227,   229,   110,
     224,   232,   137,   146,   190,    83,   180,   232,   180,   146,
     136,   137,   137,   187,   137,   187,   130,   146,   111,   136,
     116,   111,   118,   202,   216,    14,    48,    52,    57,    61,
      62,    63,    64,   139,   203,   205,   206,   207,   208,   210,
     136,   136,   222,   136,   141,   139,   118,   230,   245,    83,
     136,   116,   228,   191,    21,    22,   150,   192,   181,   136,
     136,    29,   137,   212,   187,    12,    17,    28,   160,   161,
     187,   139,   224,    24,   136,   256,   196,   130,   111,   139,
     110,   111,   209,   159,   208,   116,   137,   232,   224,   224,
      21,   150,   193,   148,   135,   132,   148,   183,   183,   137,
     136,    28,   137,   230,   132,   137,   188,   139,   137,   256,
     111,   118,   224,   130,   130,   130,   116,   137,   171,   110,
      83,   132,   135,    27,   230,   146,   132,   148,   182,   137,
     188,   146,   158,   163,   164,   165,   130,   111,   224,   224,
     224,   111,   110,   130,   224,   146,   230,   137,   136,    26,
     146,   146,   135,   165,   224,   130,   130,   135,   224,   136,
     148,   137,    25,   216,   224,   224,   194,   132,   137,   111,
     136,   146,   136,   137,   204,   256,   256
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (context, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, scanner)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, context); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, 
			PHP_context* context
)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, context)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    
			PHP_context* context
;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (context);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, 
			PHP_context* context
)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, context)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    
			PHP_context* context
;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, context);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, 
			PHP_context* context
)
#else
static void
yy_reduce_print (yyvsp, yyrule, context)
    YYSTYPE *yyvsp;
    int yyrule;
    
			PHP_context* context
;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , context);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, context); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, 
			PHP_context* context
)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, context)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    
			PHP_context* context
;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (context);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (
			PHP_context* context
);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (
			PHP_context* context
)
#else
int
yyparse (context)
    
			PHP_context* context
;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 427 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"start\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 437 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"top_statement_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 445 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"top_statement_list\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 456 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"top_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 463 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"top_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 470 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"top_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 477 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"top_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_HALT_COMPILER\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld [label=\"';'\"];\n", node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+4);
			(yyval.integer) = node;
			node = new Integer(node->value() + 5);
		;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 497 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"inner_statement_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 505 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"inner_statement_list\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 516 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"inner_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 523 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"inner_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 530 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"inner_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 537 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"inner_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_HALT_COMPILER\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld [label=\"';'\"];\n", node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+4);
			(yyval.integer) = node;
			node = new Integer(node->value() + 5);
		;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 554 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 568 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_if\"];\n", node->value());
			printf("node_%ld [label=\"K_IF\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 579 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_elseif\"];\n", node->value());
			printf("node_%ld [label=\"K_ELSEIF\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 590 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_foreach\"];\n", node->value());
			printf("node_%ld [label=\"K_FOREACH\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 601 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_while\"];\n", node->value());
			printf("node_%ld [label=\"K_WHILE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 612 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_do\"];\n", node->value());
			printf("node_%ld [label=\"K_DO\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 623 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_for\"];\n", node->value());
			printf("node_%ld [label=\"K_FOR\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 634 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_switch\"];\n", node->value());
			printf("node_%ld [label=\"K_SWITCH\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 645 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_declare\"];\n", node->value());
			printf("node_%ld [label=\"K_DECLARE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 656 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_try\"];\n", node->value());
			printf("node_%ld [label=\"K_TRY\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 667 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_catch\"];\n", node->value());
			printf("node_%ld [label=\"K_CATCH\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 678 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_function\"];\n", node->value());
			printf("node_%ld [label=\"K_FUNCTION\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 689 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_case\"];\n", node->value());
			printf("node_%ld [label=\"K_CASE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 700 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"keyword_default\"];\n", node->value());
			printf("node_%ld [label=\"K_DEFAULT\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 712 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 719 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (7)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (7)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (7)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(6) - (7)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(7) - (7)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 734 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (10)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (10)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"':'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(6) - (10)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(7) - (10)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(8) - (10)].integer)->value());
			printf("node_%ld [label=\"K_ENDIF\"];\n", node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+4);
			printf("node_%ld [label=\"';'\"];\n", node->value()+5);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+5);
			(yyval.integer) = node;
			node = new Integer(node->value() + 6);
		;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 755 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (5)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (5)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 768 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (7)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (7)].integer)->value());
			printf("node_%ld [label=\"K_WHILE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (7)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld [label=\"';'\"];\n", node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+4);
			(yyval.integer) = node;
			node = new Integer(node->value() + 5);
		;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 785 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (9)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (9)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (9)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(7) - (9)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(9) - (9)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 5);
		;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 804 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (5)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (5)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 817 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_BREAK\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 827 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_BREAK\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 838 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_CONTINUE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 848 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_CONTINUE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 859 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_RETURN\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 869 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_RETURN\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 880 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_RETURN\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 891 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_GLOBAL\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 902 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_STATIC\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 913 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_ECHO\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 924 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"INLINE_HTML: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 932 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 941 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_USE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 952 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_UNSET\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (5)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld [label=\"';'\"];\n", node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+4);
			(yyval.integer) = node;
			node = new Integer(node->value() + 5);
		;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 967 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (8)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (8)].integer)->value());
			printf("node_%ld [label=\"K_AS\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (8)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(6) - (8)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(8) - (8)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 984 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (8)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (8)].integer)->value());
			printf("node_%ld [label=\"K_AS\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (8)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(6) - (8)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(8) - (8)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 1001 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (5)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (5)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 1014 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 1022 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (9)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (9)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (9)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (9)].integer)->value());
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+2, strval ((yyvsp[(5) - (9)].integer)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(8) - (9)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(9) - (9)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 1040 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_statement\"];\n", node->value());
			printf("node_%ld [label=\"K_THROW\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 1054 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"additional_catches\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 1061 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"additional_catches\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 1072 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_additional_catches\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 1079 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_additional_catches\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 1090 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"additional_catch\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (6)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (6)].integer)->value());
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+2, strval ((yyvsp[(4) - (6)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(6) - (6)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 1108 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unset_variables\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 1115 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unset_variables\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 1128 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unset_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1138 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"use_filename\"];\n", node->value());
			printf("node_%ld [label=\"STRING: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].token_string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1146 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"use_filename\"];\n", node->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"STRING: %s\"];\n", node->value()+2, strval ((yyvsp[(2) - (3)].token_string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 1161 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"function_declaration_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1171 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_declaration_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1181 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"is_reference\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1189 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"is_reference\"];\n", node->value());
			printf("node_%ld [label=\"'&'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1200 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_function_declaration_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (7)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (7)].integer)->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(3) - (7)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (7)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(7) - (7)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 1219 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_class_declaration_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (7)].integer)->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(2) - (7)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (7)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(4) - (7)].integer)->value());
			printf("node_%ld [label=\"'{'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(6) - (7)].integer)->value());
			printf("node_%ld [label=\"'}'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1235 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"unticked_class_declaration_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (6)].integer)->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(2) - (6)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (6)].integer)->value());
			printf("node_%ld [label=\"'{'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (6)].integer)->value());
			printf("node_%ld [label=\"'}'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1253 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_entry_type\"];\n", node->value());
			printf("node_%ld [label=\"K_CLASS\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1261 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_entry_type\"];\n", node->value());
			printf("node_%ld [label=\"K_ABSTRACT\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"K_CLASS\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1271 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_entry_type\"];\n", node->value());
			printf("node_%ld [label=\"K_FINAL\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"K_CLASS\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1284 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"extends_from\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1292 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"extends_from\"];\n", node->value());
			printf("node_%ld [label=\"K_EXTENDS\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1304 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"interface_entry\"];\n", node->value());
			printf("node_%ld [label=\"K_INTERFACE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1315 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"interface_extends_list\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 1323 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"interface_extends_list\"];\n", node->value());
			printf("node_%ld [label=\"K_EXTENDS\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1335 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"implements_list\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1343 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"implements_list\"];\n", node->value());
			printf("node_%ld [label=\"K_IMPLEMENTS\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1355 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"interface_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1362 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"interface_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1375 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"foreach_optional_arg\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1383 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"foreach_optional_arg\"];\n", node->value());
			printf("node_%ld [label=\"O_DOUBLEARROW\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1395 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"foreach_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1402 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"foreach_variable\"];\n", node->value());
			printf("node_%ld [label=\"'&'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1414 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"for_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1421 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"for_statement\"];\n", node->value());
			printf("node_%ld [label=\"':'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (4)].integer)->value());
			printf("node_%ld [label=\"K_ENDFOR\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"';'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1437 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"foreach_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1444 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"foreach_statement\"];\n", node->value());
			printf("node_%ld [label=\"':'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (4)].integer)->value());
			printf("node_%ld [label=\"K_ENDFOREACH\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"';'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1460 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"declare_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1467 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"declare_statement\"];\n", node->value());
			printf("node_%ld [label=\"':'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (4)].integer)->value());
			printf("node_%ld [label=\"K_ENDDECLARE\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"';'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1483 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"declare_list\"];\n", node->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (3)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'='\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1494 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"declare_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+2, strval ((yyvsp[(3) - (5)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"'='\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (5)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1511 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"switch_case_list\"];\n", node->value());
			printf("node_%ld [label=\"'{'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"'}'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1522 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"switch_case_list\"];\n", node->value());
			printf("node_%ld [label=\"'{'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"'}'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1535 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"switch_case_list\"];\n", node->value());
			printf("node_%ld [label=\"':'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (4)].integer)->value());
			printf("node_%ld [label=\"K_ENDSWITCH\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"';'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1548 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"switch_case_list\"];\n", node->value());
			printf("node_%ld [label=\"':'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"';'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (5)].integer)->value());
			printf("node_%ld [label=\"K_ENDSWITCH\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld [label=\"';'\"];\n", node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+4);
			(yyval.integer) = node;
			node = new Integer(node->value() + 5);
		;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1566 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"case_list\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1574 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"case_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (5)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (5)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(4) - (5)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (5)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1585 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"case_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (4)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(4) - (4)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1601 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"case_separator\"];\n", node->value());
			printf("node_%ld [label=\"':'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1609 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"case_separator\"];\n", node->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1619 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"while_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1626 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"while_statement\"];\n", node->value());
			printf("node_%ld [label=\"':'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (4)].integer)->value());
			printf("node_%ld [label=\"K_ENDWHILE\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"';'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1642 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"elseif_list\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1650 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"elseif_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (6)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (6)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(4) - (6)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(6) - (6)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1670 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"new_elseif_list\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1678 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"new_elseif_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (7)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (7)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(4) - (7)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"':'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(7) - (7)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1697 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"else_single\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1705 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"else_single\"];\n", node->value());
			printf("node_%ld [label=\"K_ELSE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1720 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"new_else_single\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1728 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"new_else_single\"];\n", node->value());
			printf("node_%ld [label=\"K_ELSE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"':'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1742 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1749 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"parameter_list\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1763 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+1, strval ((yyvsp[(2) - (2)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1772 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'&'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+2, strval ((yyvsp[(3) - (3)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1783 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld [label=\"'&'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+2, strval ((yyvsp[(3) - (5)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"'='\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (5)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1797 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+1, strval ((yyvsp[(2) - (4)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'='\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(4) - (4)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1809 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+2, strval ((yyvsp[(4) - (4)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1821 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (5)].integer)->value());
			printf("node_%ld [label=\"'&'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+3, strval ((yyvsp[(5) - (5)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1835 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (7)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (7)].integer)->value());
			printf("node_%ld [label=\"'&'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+3, strval ((yyvsp[(5) - (7)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld [label=\"'='\"];\n", node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(7) - (7)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 5);
		;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1852 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (6)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (6)].integer)->value());
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+2, strval ((yyvsp[(4) - (6)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"'='\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(6) - (6)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1870 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"optional_class_type\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1878 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"optional_class_type\"];\n", node->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1886 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"optional_class_type\"];\n", node->value());
			printf("node_%ld [label=\"K_ARRAY\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1897 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"function_call_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1904 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"function_call_parameter_list\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1915 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_function_call_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1922 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_function_call_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1929 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_function_call_parameter_list\"];\n", node->value());
			printf("node_%ld [label=\"'&'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1938 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_function_call_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1948 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_function_call_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1958 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_function_call_parameter_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'&'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(4) - (4)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1973 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"global_var_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1983 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"global_var_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1993 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"global_var\"];\n", node->value());
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 2001 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"global_var\"];\n", node->value());
			printf("node_%ld [label=\"'$'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 2010 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"global_var\"];\n", node->value());
			printf("node_%ld [label=\"'$'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'{'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"'}'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 2026 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_var_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+2, strval ((yyvsp[(3) - (3)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 2037 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_var_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+2, strval ((yyvsp[(3) - (5)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"'='\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (5)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 2051 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_var_list\"];\n", node->value());
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 2059 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_var_list\"];\n", node->value());
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (3)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'='\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 2073 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_statement_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 2081 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_statement_list\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 2092 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 2102 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 2111 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_statement\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (8)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (8)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (8)].integer)->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(4) - (8)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(6) - (8)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(8) - (8)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 2131 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"method_body\"];\n", node->value());
			printf("node_%ld [label=\"';'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 2139 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"method_body\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 2149 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"variable_modifiers\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 2156 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"variable_modifiers\"];\n", node->value());
			printf("node_%ld [label=\"K_VAR\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 2167 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"method_modifiers\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 2175 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"method_modifiers\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 2185 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_member_modifiers\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 2192 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_member_modifiers\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 2203 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"member_modifier\"];\n", node->value());
			printf("node_%ld [label=\"K_PUBLIC\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 2211 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"member_modifier\"];\n", node->value());
			printf("node_%ld [label=\"K_PROTECTED\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 2219 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"member_modifier\"];\n", node->value());
			printf("node_%ld [label=\"K_PRIVATE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 2227 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"member_modifier\"];\n", node->value());
			printf("node_%ld [label=\"K_STATIC\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 2235 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"member_modifier\"];\n", node->value());
			printf("node_%ld [label=\"K_ABSTRACT\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 2243 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"member_modifier\"];\n", node->value());
			printf("node_%ld [label=\"K_FINAL\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 2254 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_variable_declaration\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+2, strval ((yyvsp[(3) - (3)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 2265 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_variable_declaration\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+2, strval ((yyvsp[(3) - (5)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"'='\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (5)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 2279 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_variable_declaration\"];\n", node->value());
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 2287 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_variable_declaration\"];\n", node->value());
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (3)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'='\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 2301 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_constant_declaration\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+2, strval ((yyvsp[(3) - (5)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"'='\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (5)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 2315 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_constant_declaration\"];\n", node->value());
			printf("node_%ld [label=\"K_CONST\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+2, strval ((yyvsp[(2) - (4)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"'='\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(4) - (4)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 2331 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"echo_expr_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 2341 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"echo_expr_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 2351 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"for_expr\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 2359 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"for_expr\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 2369 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_for_expr\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 2379 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_for_expr\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 2389 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"K_LIST\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (6)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld [label=\"'='\"];\n", node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(6) - (6)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 5);
		;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 2405 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'='\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 2415 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"'='\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'&'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(4) - (4)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 2427 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (6)].integer)->value());
			printf("node_%ld [label=\"'='\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'&'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"K_NEW\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (6)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(6) - (6)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 2442 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"K_NEW\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 2452 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"K_CLONE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 2461 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_PLUSEQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 2471 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_MINUSEQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 2481 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_MULEQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 2491 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_DIVEQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 2501 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_CONCATEQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 2511 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_MODEQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 2521 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_ANDEQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 2531 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_OREQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 2541 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_XOREQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 2551 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_SLEQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 2561 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_SREQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 2571 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld [label=\"O_INC\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 2580 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"O_INC\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 2589 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld [label=\"O_DEC\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 2598 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"O_DEC\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 2607 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_LOGICOR\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 2617 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_LOGICAND\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 2627 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"K_OR\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 2637 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"K_AND\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 2647 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"K_XOR\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 2657 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'|'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 2667 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'&'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 2677 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'^'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 2687 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'.'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 2697 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"O_MAGIC_CONCAT\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"'}'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
			/*
			 * Interface with the lexer: return to in-string state 
			 */

			context->return_to_complex_syntax();
		;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 2714 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'+'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 2724 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'-'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 2734 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'*'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 2744 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'/'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 2754 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'%%'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 2764 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_SL\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 2774 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_SR\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 2784 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"'+'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 2793 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"'-'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 2802 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"'!'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 2811 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"'~'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 2820 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_EQEQEQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 2830 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_NOTEQEQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 2840 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_EQEQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 2850 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_NOTEQ\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 2860 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'<'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 2870 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_LE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 2880 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"'>'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 2890 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_GE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 2900 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"K_INSTANCEOF\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 2910 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 2921 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld [label=\"'?'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (5)].integer)->value());
			printf("node_%ld [label=\"':'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (5)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 2934 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 2941 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"CAST_INT\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 2950 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"CAST_REAL\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 2959 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"CAST_STRING\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 2968 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"CAST_ARRAY\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 2977 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"CAST_OBJECT\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 2986 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"CAST_BOOL\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 2995 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"CAST_UNSET\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 3004 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"K_EXIT\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 3013 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"K_DIE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 3022 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"'@'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 3031 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 3038 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"K_ARRAY\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 3051 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr_without_variable\"];\n", node->value());
			printf("node_%ld [label=\"K_PRINT\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 3063 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"function_call\"];\n", node->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (4)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 3076 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"function_call\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (6)].integer)->value());
			printf("node_%ld [label=\"O_COLONCOLON\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+2, strval ((yyvsp[(3) - (6)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"'('\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (6)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+4);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+4);
			(yyval.integer) = node;
			node = new Integer(node->value() + 5);
		;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 3092 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"function_call\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (6)].integer)->value());
			printf("node_%ld [label=\"O_COLONCOLON\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (6)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (6)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 3107 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"function_call\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 3122 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"fully_qualified_class_name\"];\n", node->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 3133 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_name_reference\"];\n", node->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 3141 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_name_reference\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 3151 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"dynamic_class_name_reference\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"O_SINGLEARROW\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(4) - (4)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 3162 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"dynamic_class_name_reference\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 3172 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"dynamic_class_name_variable_properties\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 3180 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"dynamic_class_name_variable_properties\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 3191 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"dynamic_class_name_variable_property\"];\n", node->value());
			printf("node_%ld [label=\"O_SINGLEARROW\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 3203 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"exit_expr\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 3211 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"exit_expr\"];\n", node->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 3221 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"exit_expr\"];\n", node->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 3235 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"ctor_arguments\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 3243 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"ctor_arguments\"];\n", node->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 3257 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"common_scalar\"];\n", node->value());
			printf("node_%ld [label=\"INT: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].token_int)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 3265 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"common_scalar\"];\n", node->value());
			printf("node_%ld [label=\"REAL: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].token_real)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 3273 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"common_scalar\"];\n", node->value());
			printf("node_%ld [label=\"STRING: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].token_string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 3281 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"common_scalar\"];\n", node->value());
			printf("node_%ld [label=\"C_FALSE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 3289 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"common_scalar\"];\n", node->value());
			printf("node_%ld [label=\"C_TRUE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 3297 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"common_scalar\"];\n", node->value());
			printf("node_%ld [label=\"C_NULL\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 3305 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"common_scalar\"];\n", node->value());
			printf("node_%ld [label=\"K___LINE__\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 3313 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"common_scalar\"];\n", node->value());
			printf("node_%ld [label=\"K___FILE__\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 3321 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"common_scalar\"];\n", node->value());
			printf("node_%ld [label=\"K___CLASS__\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 3329 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"common_scalar\"];\n", node->value());
			printf("node_%ld [label=\"K___METHOD__\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 3337 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"common_scalar\"];\n", node->value());
			printf("node_%ld [label=\"K___FUNCTION__\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 3348 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_scalar\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 3355 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_scalar\"];\n", node->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 3363 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_scalar\"];\n", node->value());
			printf("node_%ld [label=\"'+'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 3372 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_scalar\"];\n", node->value());
			printf("node_%ld [label=\"'-'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 3381 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_scalar\"];\n", node->value());
			printf("node_%ld [label=\"K_ARRAY\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 3394 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_scalar\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 3404 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_class_constant\"];\n", node->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (3)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"O_COLONCOLON\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+3, strval ((yyvsp[(3) - (3)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 3419 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"scalar\"];\n", node->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 3427 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"scalar\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 3434 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"scalar\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 3444 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_array_pair_list\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 3452 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 3466 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"possible_comma\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 3474 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"possible_comma\"];\n", node->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 3484 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_static_array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (5)].integer)->value());
			printf("node_%ld [label=\"O_DOUBLEARROW\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (5)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 3497 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_static_array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 3507 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_static_array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_DOUBLEARROW\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 289:

/* Line 1455 of yacc.c  */
#line 3517 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_static_array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 290:

/* Line 1455 of yacc.c  */
#line 3527 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 3534 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"expr\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 3544 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"r_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 3554 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"w_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 3564 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"rw_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 3591 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 3599 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 3613 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"variable_properties\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 3621 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"variable_properties\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 3631 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"variable_property\"];\n", node->value());
			printf("node_%ld [label=\"O_SINGLEARROW\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 3644 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"method_or_not\"];\n", node->value());
			printf("node_%ld [label=\"'('\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 3655 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"method_or_not\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 3666 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"variable_without_objects\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 3673 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"variable_without_objects\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 3684 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"static_member\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_COLONCOLON\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 3697 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"base_variable_with_function_calls\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 3704 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"base_variable_with_function_calls\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 3714 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"base_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 3721 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"base_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 3729 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"base_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 3739 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"reference_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"'['\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"']'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 3751 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"reference_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"'{'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"'}'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 3763 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"reference_variable\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 3773 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"compound_variable\"];\n", node->value());
			printf("node_%ld [label=\"VARIABLE: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 3781 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"compound_variable\"];\n", node->value());
			printf("node_%ld [label=\"'$'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'{'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"'}'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 3797 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"dim_offset\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 3805 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"dim_offset\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 3815 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"object_property\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 3822 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"object_property\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 3835 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"object_dim_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"'['\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"']'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 3847 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"object_dim_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"'{'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"'}'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 3859 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"object_dim_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 3872 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"variable_name\"];\n", node->value());
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+1, strval ((yyvsp[(1) - (1)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 3880 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"variable_name\"];\n", node->value());
			printf("node_%ld [label=\"'{'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"'}'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 3894 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"simple_indirect_reference\"];\n", node->value());
			printf("node_%ld [label=\"'$'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 3902 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"simple_indirect_reference\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld [label=\"'$'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 3914 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"assignment_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 3924 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"assignment_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 3933 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"assignment_list_element\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 3940 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"assignment_list_element\"];\n", node->value());
			printf("node_%ld [label=\"K_LIST\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 3953 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"assignment_list_element\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 3964 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"array_pair_list\"];\n", node->value());
			printf("node_%ld [label=\"epsilon\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 3972 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (2)].integer)->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 3986 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (5)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (5)].integer)->value());
			printf("node_%ld [label=\"O_DOUBLEARROW\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(5) - (5)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 3999 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 4009 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_DOUBLEARROW\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 4019 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 4026 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (6)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (6)].integer)->value());
			printf("node_%ld [label=\"O_DOUBLEARROW\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld [label=\"'&'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(6) - (6)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 4041 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'&'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(4) - (4)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 4053 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_array_pair_list\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (4)].integer)->value());
			printf("node_%ld [label=\"O_DOUBLEARROW\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'&'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(4) - (4)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 4065 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"non_empty_array_pair_list\"];\n", node->value());
			printf("node_%ld [label=\"'&'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 4077 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"internal_functions_in_yacc\"];\n", node->value());
			printf("node_%ld [label=\"K_ISSET\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 4090 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"internal_functions_in_yacc\"];\n", node->value());
			printf("node_%ld [label=\"K_EMPTY\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 4103 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"internal_functions_in_yacc\"];\n", node->value());
			printf("node_%ld [label=\"K_INCLUDE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 4112 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"internal_functions_in_yacc\"];\n", node->value());
			printf("node_%ld [label=\"K_INCLUDE_ONCE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 4121 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"internal_functions_in_yacc\"];\n", node->value());
			printf("node_%ld [label=\"K_EVAL\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"'('\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (4)].integer)->value());
			printf("node_%ld [label=\"')'\"];\n", node->value()+3);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+3);
			(yyval.integer) = node;
			node = new Integer(node->value() + 4);
		;}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 4134 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"internal_functions_in_yacc\"];\n", node->value());
			printf("node_%ld [label=\"K_REQUIRE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 4143 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"internal_functions_in_yacc\"];\n", node->value());
			printf("node_%ld [label=\"K_REQUIRE_ONCE\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (2)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 4155 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"isset_variables\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (1)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 1);
		;}
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 4162 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"isset_variables\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"','\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(3) - (3)].integer)->value());
			(yyval.integer) = node;
			node = new Integer(node->value() + 2);
		;}
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 4175 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"class_constant\"];\n", node->value());
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(1) - (3)].integer)->value());
			printf("node_%ld [label=\"O_COLONCOLON\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld [label=\"IDENT: %s\"];\n", node->value()+2, strval ((yyvsp[(3) - (3)].string)));
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 4193 "src/generated_src/php_dot.ypp"
    {
			printf("node_%ld [label=\"block\"];\n", node->value());
			printf("node_%ld [label=\"'{'\"];\n", node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+1);
			printf("node_%ld->node_%ld;\n", node->value(), (yyvsp[(2) - (3)].integer)->value());
			printf("node_%ld [label=\"'}'\"];\n", node->value()+2);
			printf("node_%ld->node_%ld;\n", node->value(), node->value()+2);
			(yyval.integer) = node;
			node = new Integer(node->value() + 3);
		;}
    break;



/* Line 1455 of yacc.c  */
#line 8422 "src/generated/php_dot.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (context, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (context, yymsg);
	  }
	else
	  {
	    yyerror (context, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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
		      yytoken, &yylval, context);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp, context);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (context, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, context);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, context);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



