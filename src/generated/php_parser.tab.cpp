
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
#define yyparse         PHP_parse
#define yylex           PHP_lex
#define yyerror         PHP_error
#define yylval          PHP_lval
#define yychar          PHP_char
#define yydebug         PHP_debug
#define yynerrs         PHP_nerrs


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 8 "src/generated_src/php_parser.ypp"

	#include <assert.h>
	#include <typeinfo>
	#include "AST.h"
	using namespace AST;
	#include "cmdline.h"
	#include "lib/Integer.h"
	#include "lib/String.h"
	#include "lib/error.h"
	#include "parsing/PHP_context.h"

	extern struct gengetopt_args_info args_info;

	/*
	 * Some semantic checks
	 */

	Variable* expect_variable (Expr* node)
	{
		if (node && !isa<Variable> (node))
			phc_error("Variable name expected", node);
			
		return dyc<Variable> (node);
	}

	Expr* expect_variable_or_method_invocation (Expr* node)
	{
		if(node
			&& !isa<Variable> (node)
			&& !isa<Method_invocation> (node))
			phc_error("Variable name or method invocation expected", node);
			
		return node;
	}

	/*
	 * Define macro to add line numbers and comments to nodes
	 */
	#define NEW(class, args)\
		dynamic_cast<class*>(copy_state(new class args, context))
	
	Node* copy_state(Node* node, PHP_context* context)
	{
		node->attrs->set("phc.line_number", new Integer(context->source_line));
		node->attrs->set("phc.filename", context->filename->clone());
		if(context->starts_line)
			node->attrs->set_true("phc.unparser.starts_line");

		Commented_node* cnode;
		cnode = dynamic_cast<Commented_node*>(node);
		if(cnode)
		{
			List<String*>* cmnts = cnode->get_comments();
			cmnts->push_back_all(&context->last_comments);
			context->last_comments.clear();
			context->last_commented_node = cnode;
		}
		
		STRING* str;
		str = dynamic_cast<STRING*>(node);
		if(str && context->heredoc_attr != NULL)
		{
			str->attrs->set("phc.unparser.heredoc_id", context->heredoc_attr);
			context->heredoc_attr = NULL;
		}

		return node;
	}

	void PHP_error(PHP_context* context, const char* s)
	{
		phc_error(s, context->filename, context->source_line, 0);
	}

	/* Return a new list of statements, containing a single statement */
	static List<Statement*>* wrap(Statement* statement)
	{
		statement->attrs->set_true("phc.unparser.is_wrapped");
		List<Statement*>* result = new List<Statement*>;
		result->push_back(statement);
		return result;
	}

#define ERR_FOREACH_KEY_REF "Key element cannot be a reference"


/* Line 189 of yacc.c  */
#line 168 "src/generated/php_parser.tab.cpp"

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
#line 95 "src/generated_src/php_parser.ypp"

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
#line 377 "src/generated/php_parser.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */

/* Line 264 of yacc.c  */
#line 151 "src/generated_src/php_parser.ypp"

	int PHP_lex(YYSTYPE* yylval, void* scanner);
	#define scanner context->scanner


/* Line 264 of yacc.c  */
#line 395 "src/generated/php_parser.tab.cpp"

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
#define YYLAST   5884

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  142
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  120
/* YYNRULES -- Number of rules.  */
#define YYNRULES  356
/* YYNRULES -- Number of states.  */
#define YYNSTATES  692

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
     242,   243,   252,   253,   254,   264,   271,   273,   276,   279,
     280,   283,   285,   286,   289,   290,   293,   295,   299,   300,
     303,   305,   308,   310,   315,   317,   322,   324,   329,   333,
     339,   343,   348,   353,   359,   360,   366,   371,   373,   375,
     377,   382,   383,   390,   391,   399,   400,   403,   404,   408,
     410,   411,   414,   418,   424,   429,   434,   440,   448,   455,
     456,   458,   460,   462,   463,   465,   467,   470,   474,   478,
     483,   487,   489,   491,   494,   499,   503,   509,   511,   515,
     518,   519,   523,   526,   527,   528,   539,   541,   543,   545,
     547,   548,   550,   552,   555,   557,   559,   561,   563,   565,
     567,   571,   577,   579,   583,   589,   594,   598,   600,   601,
     603,   607,   609,   616,   620,   625,   632,   636,   639,   643,
     647,   651,   655,   659,   663,   667,   671,   675,   679,   683,
     686,   689,   692,   695,   699,   703,   707,   711,   715,   719,
     723,   727,   731,   736,   740,   744,   748,   752,   756,   760,
     764,   767,   770,   773,   776,   780,   784,   788,   792,   796,
     800,   804,   808,   812,   816,   822,   824,   827,   830,   833,
     836,   839,   842,   845,   848,   851,   854,   856,   861,   864,
     869,   876,   883,   888,   890,   892,   894,   899,   901,   904,
     905,   908,   909,   912,   916,   917,   921,   923,   925,   927,
     929,   931,   933,   935,   937,   939,   941,   943,   945,   947,
     950,   953,   958,   960,   964,   966,   968,   970,   971,   974,
     975,   977,   983,   987,   991,   993,   995,   997,   999,  1001,
    1003,  1006,  1008,  1011,  1013,  1017,  1021,  1022,  1024,  1027,
    1031,  1033,  1035,  1037,  1040,  1042,  1047,  1052,  1054,  1056,
    1061,  1062,  1064,  1066,  1068,  1073,  1078,  1080,  1082,  1086,
    1088,  1091,  1095,  1097,  1099,  1104,  1105,  1106,  1109,  1115,
    1119,  1123,  1125,  1132,  1137,  1142,  1145,  1150,  1155,  1158,
    1161,  1166,  1169,  1172,  1174,  1178,  1182
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
      -1,    17,    -1,   261,    -1,   149,   135,   235,   136,   148,
     193,   195,    -1,   149,   135,   235,   136,   132,   146,   194,
     196,    27,   137,    -1,   152,   135,   235,   136,   192,    -1,
     153,   148,    53,   135,   235,   136,   137,    -1,   154,   135,
     217,   137,   217,   137,   217,   136,   185,    -1,   155,   135,
     235,   136,   189,    -1,    11,   137,    -1,    11,   235,   137,
      -1,    15,   137,    -1,    15,   235,   137,    -1,    47,   137,
      -1,    47,   219,   137,    -1,    47,   239,   137,    -1,    36,
     202,   137,    -1,    48,   204,   137,    -1,    20,   216,   137,
      -1,   114,    -1,   235,   137,    -1,    51,   168,   137,    -1,
      50,   135,   166,   136,   137,    -1,   151,   135,   239,    10,
     184,   183,   136,   186,    -1,   151,   135,   219,    10,   237,
     183,   136,   186,    -1,   156,   135,   188,   136,   187,    -1,
     137,    -1,   157,   261,   158,   135,   221,   111,   136,   261,
     163,    -1,    68,   235,   137,    -1,   164,    -1,    -1,   165,
      -1,   164,   165,    -1,   158,   135,   221,   111,   136,   261,
      -1,   167,    -1,   166,   116,   167,    -1,   239,    -1,   109,
      -1,   135,   109,   136,    -1,   172,    -1,   174,    -1,    -1,
     118,    -1,    -1,   159,   171,   110,   173,   135,   197,   136,
     261,    -1,    -1,    -1,   177,   110,   175,   178,   181,   138,
     205,   139,   176,    -1,   179,   110,   180,   138,   205,   139,
      -1,    13,    -1,    64,    13,    -1,    57,    13,    -1,    -1,
      32,   221,    -1,    59,    -1,    -1,    32,   182,    -1,    -1,
      60,   182,    -1,   221,    -1,   182,   116,   221,    -1,    -1,
      83,   184,    -1,   237,    -1,   118,   237,    -1,   148,    -1,
     132,   146,    25,   137,    -1,   148,    -1,   132,   146,    26,
     137,    -1,   148,    -1,   132,   146,    24,   137,    -1,   110,
     130,   229,    -1,   188,   116,   110,   130,   229,    -1,   138,
     190,   139,    -1,   138,   137,   190,   139,    -1,   132,   190,
      28,   137,    -1,   132,   137,   190,    28,   137,    -1,    -1,
     190,   160,   235,   191,   146,    -1,   190,   161,   191,   146,
      -1,   132,    -1,   137,    -1,   148,    -1,   132,   146,    29,
     137,    -1,    -1,   193,   150,   135,   235,   136,   148,    -1,
      -1,   194,   150,   135,   235,   136,   132,   146,    -1,    -1,
      21,   148,    -1,    -1,    21,   132,   146,    -1,   198,    -1,
      -1,   199,   111,    -1,   199,   118,   111,    -1,   199,   118,
     111,   130,   229,    -1,   199,   111,   130,   229,    -1,   198,
     116,   199,   111,    -1,   198,   116,   199,   118,   111,    -1,
     198,   116,   199,   118,   111,   130,   229,    -1,   198,   116,
     199,   111,   130,   229,    -1,    -1,   110,    -1,     9,    -1,
     201,    -1,    -1,   219,    -1,   239,    -1,   118,   237,    -1,
     201,   116,   219,    -1,   201,   116,   239,    -1,   201,   116,
     118,   237,    -1,   202,   116,   203,    -1,   203,    -1,   111,
      -1,   140,   236,    -1,   140,   138,   235,   139,    -1,   204,
     116,   111,    -1,   204,   116,   111,   130,   229,    -1,   111,
      -1,   111,   130,   229,    -1,   205,   206,    -1,    -1,   210,
     214,   137,    -1,   215,   137,    -1,    -1,    -1,   211,   159,
     171,   110,   207,   135,   197,   136,   209,   208,    -1,   137,
      -1,   261,    -1,   212,    -1,    52,    -1,    -1,   212,    -1,
     213,    -1,   212,   213,    -1,    61,    -1,    63,    -1,    62,
      -1,    48,    -1,    64,    -1,    57,    -1,   214,   116,   111,
      -1,   214,   116,   111,   130,   229,    -1,   111,    -1,   111,
     130,   229,    -1,   215,   116,   110,   130,   229,    -1,    14,
     110,   130,   229,    -1,   216,   116,   235,    -1,   235,    -1,
      -1,   218,    -1,   218,   116,   235,    -1,   235,    -1,    42,
     135,   254,   136,   130,   235,    -1,   239,   130,   235,    -1,
     239,   130,   118,   239,    -1,   239,   130,   118,    43,   222,
     227,    -1,    43,   222,   227,    -1,    65,   235,    -1,   239,
      90,   235,    -1,   239,    91,   235,    -1,   239,    92,   235,
      -1,   239,    93,   235,    -1,   239,    94,   235,    -1,   239,
      95,   235,    -1,   239,    96,   235,    -1,   239,    97,   235,
      -1,   239,    98,   235,    -1,   239,    99,   235,    -1,   239,
     100,   235,    -1,   238,    81,    -1,    81,   238,    -1,   238,
      82,    -1,    82,   238,    -1,   235,    88,   235,    -1,   235,
      89,   235,    -1,   235,     4,   235,    -1,   235,     3,   235,
      -1,   235,     5,   235,    -1,   235,   117,   235,    -1,   235,
     118,   235,    -1,   235,   119,   235,    -1,   235,   120,   235,
      -1,   235,   101,   235,   139,    -1,   235,   121,   235,    -1,
     235,   122,   235,    -1,   235,   123,   235,    -1,   235,   124,
     235,    -1,   235,   125,   235,    -1,   235,    85,   235,    -1,
     235,    86,   235,    -1,   121,   235,    -1,   122,   235,    -1,
     126,   235,    -1,   127,   235,    -1,   235,    76,   235,    -1,
     235,    78,   235,    -1,   235,    75,   235,    -1,   235,    77,
     235,    -1,   235,   128,   235,    -1,   235,    79,   235,    -1,
     235,   129,   235,    -1,   235,    80,   235,    -1,   235,    40,
     222,    -1,   135,   235,   136,    -1,   235,   131,   235,   132,
     235,    -1,   258,    -1,   102,   235,    -1,   103,   235,    -1,
     104,   235,    -1,   105,   235,    -1,   106,   235,    -1,   107,
     235,    -1,   108,   235,    -1,    31,   226,    -1,    18,   226,
      -1,   133,   235,    -1,   231,    -1,     9,   135,   256,   136,
      -1,    44,   235,    -1,   110,   135,   200,   136,    -1,   221,
      87,   110,   135,   200,   136,    -1,   221,    87,   243,   135,
     200,   136,    -1,   243,   135,   200,   136,    -1,   110,    -1,
     110,    -1,   223,    -1,   246,    84,   250,   224,    -1,   246,
      -1,   224,   225,    -1,    -1,    84,   250,    -1,    -1,   135,
     136,    -1,   135,   235,   136,    -1,    -1,   135,   200,   136,
      -1,   112,    -1,   113,    -1,   109,    -1,    73,    -1,    72,
      -1,    74,    -1,     8,    -1,     6,    -1,    55,    -1,    56,
      -1,    54,    -1,   228,    -1,   110,    -1,   121,   229,    -1,
     122,   229,    -1,     9,   135,   232,   136,    -1,   230,    -1,
     110,    87,   110,    -1,   110,    -1,   260,    -1,   228,    -1,
      -1,   234,   233,    -1,    -1,   116,    -1,   234,   116,   229,
      83,   229,    -1,   234,   116,   229,    -1,   229,    83,   229,
      -1,   229,    -1,   236,    -1,   219,    -1,   239,    -1,   239,
      -1,   239,    -1,   245,   240,    -1,   245,    -1,   240,   241,
      -1,   241,    -1,    84,   250,   242,    -1,   135,   200,   136,
      -1,    -1,   247,    -1,   253,   247,    -1,   221,    87,   243,
      -1,   246,    -1,   220,    -1,   247,    -1,   253,   247,    -1,
     244,    -1,   247,   134,   249,   141,    -1,   247,   138,   235,
     139,    -1,   248,    -1,   111,    -1,   140,   138,   235,   139,
      -1,    -1,   235,    -1,   251,    -1,   243,    -1,   251,   134,
     249,   141,    -1,   251,   138,   235,   139,    -1,   252,    -1,
     110,    -1,   138,   235,   139,    -1,   140,    -1,   253,   140,
      -1,   254,   116,   255,    -1,   255,    -1,   239,    -1,    42,
     135,   254,   136,    -1,    -1,    -1,   257,   233,    -1,   257,
     116,   235,    83,   235,    -1,   257,   116,   235,    -1,   235,
      83,   235,    -1,   235,    -1,   257,   116,   235,    83,   118,
     237,    -1,   257,   116,   118,   237,    -1,   235,    83,   118,
     237,    -1,   118,   237,    -1,    41,   135,   259,   136,    -1,
      23,   135,   239,   136,    -1,    38,   235,    -1,    39,   235,
      -1,    30,   135,   235,   136,    -1,    45,   235,    -1,    46,
     235,    -1,   239,    -1,   259,   116,   239,    -1,   221,    87,
     110,    -1,   138,   146,   139,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   454,   454,   467,   477,   483,   487,   491,   495,   505,
     511,   517,   521,   525,   529,   536,   547,   554,   561,   568,
     575,   582,   589,   596,   603,   610,   617,   624,   631,   639,
     643,   676,   701,   708,   715,   724,   731,   735,   739,   743,
     747,   751,   755,   759,   763,   767,   778,   788,   792,   799,
     807,   832,   858,   865,   869,   886,   893,   898,   905,   912,
     921,   934,   940,   948,   955,   959,   966,   973,   981,   984,
     991,   991,  1004,  1004,  1004,  1015,  1038,  1043,  1048,  1057,
    1060,  1067,  1075,  1078,  1089,  1092,  1099,  1109,  1120,  1123,
    1130,  1134,  1142,  1146,  1153,  1157,  1164,  1168,  1175,  1185,
    1196,  1200,  1204,  1208,  1216,  1219,  1228,  1243,  1244,  1248,
    1252,  1260,  1263,  1300,  1303,  1333,  1336,  1347,  1350,  1357,
    1362,  1372,  1383,  1394,  1405,  1416,  1424,  1432,  1440,  1452,
    1455,  1460,  1468,  1473,  1479,  1485,  1491,  1497,  1502,  1507,
    1515,  1520,  1530,  1534,  1538,  1546,  1552,  1558,  1565,  1575,
    1581,  1587,  1591,  1595,  1595,  1595,  1608,  1613,  1620,  1629,
    1637,  1640,  1647,  1651,  1658,  1662,  1666,  1670,  1674,  1678,
    1685,  1691,  1697,  1704,  1714,  1721,  1743,  1748,  1757,  1760,
    1770,  1775,  1782,  1786,  1790,  1794,  1799,  1804,  1809,  1814,
    1819,  1824,  1829,  1834,  1839,  1844,  1849,  1854,  1859,  1864,
    1868,  1872,  1876,  1880,  1885,  1890,  1895,  1900,  1905,  1910,
    1915,  1920,  1925,  1936,  1941,  1946,  1951,  1956,  1961,  1966,
    1971,  1976,  1980,  1984,  1988,  1993,  1998,  2003,  2008,  2013,
    2018,  2023,  2028,  2032,  2038,  2042,  2046,  2050,  2054,  2058,
    2062,  2066,  2070,  2074,  2078,  2084,  2088,  2092,  2096,  2104,
    2118,  2124,  2128,  2135,  2143,  2149,  2160,  2173,  2180,  2186,
    2193,  2204,  2215,  2226,  2243,  2249,  2256,  2260,  2264,  2268,
    2272,  2276,  2280,  2284,  2288,  2292,  2296,  2303,  2307,  2312,
    2317,  2321,  2325,  2332,  2342,  2348,  2352,  2360,  2363,  2372,
    2374,  2378,  2385,  2392,  2400,  2411,  2415,  2422,  2429,  2436,
    2460,  2492,  2503,  2509,  2538,  2576,  2581,  2587,  2591,  2603,
    2611,  2615,  2622,  2626,  2635,  2642,  2647,  2655,  2662,  2667,
    2676,  2679,  2686,  2690,  2702,  2707,  2715,  2725,  2730,  2741,
    2745,  2753,  2759,  2772,  2776,  2781,  2788,  2791,  2801,  2808,
    2815,  2823,  2831,  2839,  2847,  2856,  2868,  2873,  2877,  2882,
    2887,  2891,  2896,  2904,  2911,  2919,  2932
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
  "unticked_function_declaration_statement", "$@1",
  "unticked_class_declaration_statement", "$@2", "$@3", "class_entry_type",
  "extends_from", "interface_entry", "interface_extends_list",
  "implements_list", "interface_list", "foreach_optional_arg",
  "foreach_variable", "for_statement", "foreach_statement",
  "declare_statement", "declare_list", "switch_case_list", "case_list",
  "case_separator", "while_statement", "elseif_list", "new_elseif_list",
  "else_single", "new_else_single", "parameter_list",
  "non_empty_parameter_list", "optional_class_type",
  "function_call_parameter_list", "non_empty_function_call_parameter_list",
  "global_var_list", "global_var", "static_var_list",
  "class_statement_list", "class_statement", "$@4", "$@5", "method_body",
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
     173,   172,   175,   176,   174,   174,   177,   177,   177,   178,
     178,   179,   180,   180,   181,   181,   182,   182,   183,   183,
     184,   184,   185,   185,   186,   186,   187,   187,   188,   188,
     189,   189,   189,   189,   190,   190,   190,   191,   191,   192,
     192,   193,   193,   194,   194,   195,   195,   196,   196,   197,
     197,   198,   198,   198,   198,   198,   198,   198,   198,   199,
     199,   199,   200,   200,   201,   201,   201,   201,   201,   201,
     202,   202,   203,   203,   203,   204,   204,   204,   204,   205,
     205,   206,   206,   207,   208,   206,   209,   209,   210,   210,
     211,   211,   212,   212,   213,   213,   213,   213,   213,   213,
     214,   214,   214,   214,   215,   215,   216,   216,   217,   217,
     218,   218,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   220,
     220,   220,   220,   221,   222,   222,   223,   223,   224,   224,
     225,   226,   226,   226,   227,   227,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   229,   229,   229,
     229,   229,   229,   230,   231,   231,   231,   232,   232,   233,
     233,   234,   234,   234,   234,   235,   235,   236,   237,   238,
     239,   239,   240,   240,   241,   242,   242,   243,   243,   244,
     245,   245,   246,   246,   246,   247,   247,   247,   248,   248,
     249,   249,   250,   250,   251,   251,   251,   252,   252,   253,
     253,   254,   254,   255,   255,   255,   256,   256,   257,   257,
     257,   257,   257,   257,   257,   257,   258,   258,   258,   258,
     258,   258,   258,   259,   259,   260,   261
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
       0,     8,     0,     0,     9,     6,     1,     2,     2,     0,
       2,     1,     0,     2,     0,     2,     1,     3,     0,     2,
       1,     2,     1,     4,     1,     4,     1,     4,     3,     5,
       3,     4,     4,     5,     0,     5,     4,     1,     1,     1,
       4,     0,     6,     0,     7,     0,     2,     0,     3,     1,
       0,     2,     3,     5,     4,     4,     5,     7,     6,     0,
       1,     1,     1,     0,     1,     1,     2,     3,     3,     4,
       3,     1,     1,     2,     4,     3,     5,     1,     3,     2,
       0,     3,     2,     0,     0,    10,     1,     1,     1,     1,
       0,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       3,     5,     1,     3,     5,     4,     3,     1,     0,     1,
       3,     1,     6,     3,     4,     6,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     5,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     4,     2,     4,
       6,     6,     4,     1,     1,     1,     4,     1,     2,     0,
       2,     0,     2,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     4,     1,     3,     1,     1,     1,     0,     2,     0,
       1,     5,     3,     3,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     3,     3,     0,     1,     2,     3,
       1,     1,     1,     2,     1,     4,     4,     1,     1,     4,
       0,     1,     1,     1,     4,     4,     1,     1,     3,     1,
       2,     3,     1,     1,     4,     0,     0,     2,     5,     3,
       3,     1,     6,     4,     4,     2,     4,     4,     2,     2,
       4,     2,     2,     1,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     2,     1,   273,   272,     0,     0,    76,     0,
      23,   261,    20,     0,     0,     0,   261,    21,    18,    26,
       0,    16,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,     0,     0,    19,   276,   274,   275,     0,
      81,     0,     0,    24,     0,     0,   270,   269,   271,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   268,   284,
     318,   266,   267,    46,     0,     0,     0,     0,     0,     0,
      53,    10,   329,     3,     5,     0,     0,     0,     0,     0,
       0,     0,     0,    68,    15,     6,     7,    66,    67,     0,
       0,   296,   311,     0,   286,   246,     0,   295,     0,   297,
       0,   314,   301,   310,   312,   317,     0,   235,   285,    29,
     336,    36,     0,    38,     0,     0,   244,     0,   177,     0,
       0,   243,   142,     0,     0,   141,   348,   349,     0,   335,
     254,     0,   264,   255,   257,   312,     0,   248,   351,   352,
      40,   296,     0,   297,   147,     0,     0,    64,     0,     0,
      78,    77,   187,     0,     0,   253,     0,   200,   299,   202,
     236,   237,   238,   239,   240,   241,   242,   133,   220,   221,
     222,   223,   245,     0,     0,     0,     0,     0,     0,     0,
     178,     0,     0,     0,    69,     0,    72,    82,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    47,   199,   201,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   133,     0,   300,   303,   320,     0,   330,   313,     0,
     341,     0,   289,    37,    39,   262,     0,     0,    45,     0,
       0,     0,   143,   297,     0,    43,   353,     0,     0,   333,
       0,   332,     0,   133,   186,     0,   313,    41,    42,     0,
       0,    44,     0,    61,    63,     0,    48,    55,     0,     0,
       0,     0,   132,   296,   297,   233,     0,   356,     9,    11,
      12,    13,     0,     0,   296,   297,     0,     0,     0,   179,
     181,     0,     0,     0,    25,     0,    70,    79,     0,     0,
     355,   309,   307,     0,   206,   205,   207,   232,   226,   224,
     227,   225,   229,   231,   218,   219,   203,   204,     0,   208,
     209,   210,   211,   213,   214,   215,   216,   217,   228,   230,
       0,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,     0,   183,     0,   327,     0,   323,   306,   322,
     326,   302,   321,     0,     0,   345,   298,     0,   247,   290,
     337,   263,   176,   347,   350,     0,   140,     0,   346,   335,
     335,     0,   309,     0,   259,     0,   278,     0,     0,   277,
     148,   282,   145,     0,     0,    65,     8,     0,   136,   249,
       0,     0,   319,     0,     0,     0,     0,     0,   178,     0,
       0,     0,     0,     0,     0,     0,     0,    84,   253,    83,
      86,   150,   133,   133,   308,   212,     0,     0,   184,   252,
       0,   133,   304,   320,     0,   315,   316,     0,   340,     0,
     339,   144,   354,     0,   331,     0,   265,   256,   287,     0,
     279,   280,     0,    62,    49,     0,   296,   297,     0,    10,
     111,    88,     0,    88,    90,    10,   109,    32,     0,     0,
     180,   104,   104,    35,    98,     0,    10,    96,    52,     0,
     129,    80,     0,     0,     0,   160,     0,     0,   234,   264,
     328,     0,     0,     0,   344,   343,     0,   334,   182,     0,
     258,   294,     0,   289,   283,   146,   139,    14,   113,   115,
       0,     0,    91,     0,     0,     0,   178,   104,     0,   104,
       0,     0,     0,     0,   131,   130,     0,   119,     0,    85,
     150,    87,     0,   167,   159,   169,   164,   166,   165,   168,
      75,   149,     0,     0,   158,   162,     0,   250,   251,   185,
     305,   324,   325,     0,   338,   260,     0,   281,   290,   288,
     117,     0,    17,     0,    30,    89,     0,     0,     0,    33,
       0,     0,    27,    28,     0,     0,     0,     0,   100,    99,
       0,     0,     0,   129,   121,     0,   160,     0,   172,     0,
      68,   163,     0,   152,   342,   293,   292,     0,     0,     0,
     116,     0,    10,    94,    51,    50,   110,     0,     0,   102,
       0,   107,   108,    10,   101,    97,    57,    71,     0,     0,
     122,    73,     0,     0,     0,   151,     0,     0,     0,    10,
       0,     0,     0,     0,    10,    92,    34,   103,    10,   106,
       0,    54,    56,    58,   125,     0,   124,     0,    74,   175,
     173,   170,   153,     0,   291,   118,     0,    31,     0,     0,
       0,   105,     0,    59,     0,   126,   123,     0,     0,   174,
       0,   112,    95,     0,     0,   128,     0,   171,   129,    10,
      93,     0,   127,     0,   114,     0,     0,    60,   156,   154,
     157,   155
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    73,   174,   288,   289,    75,   563,    76,
      77,    78,    79,    80,    81,    82,   640,    83,   575,   576,
      84,   641,   642,   643,   272,   273,   149,   290,   291,   185,
      87,   415,    88,   307,   648,    89,   417,    90,   309,   483,
     419,   511,   463,   636,   604,   478,   303,   473,   518,   613,
     467,   509,   560,   564,   599,   526,   527,   528,   281,   282,
     124,   125,   145,   485,   541,   668,   691,   689,   542,   543,
     544,   545,   589,   546,   117,   298,   299,    91,    92,    93,
     132,   133,   447,   500,   116,   264,    94,   390,   391,    95,
     502,   370,   503,    96,    97,   464,    98,    99,   233,   234,
     432,   100,   101,   102,   103,   104,   105,   363,   358,   359,
     360,   106,   260,   261,   241,   242,   107,   257,   108,   109
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -449
static const yytype_int16 yypact[] =
{
    -449,    53,  1906,  -449,  -449,  -449,   -98,  2948,  -449,  3059,
    -449,   -34,  -449,  4169,    15,    20,   -34,  -449,  -449,  -449,
     -84,  -449,  4169,  4169,    56,    59,   -21,  4169,  4169,  4169,
    3170,   -61,  -449,    80,   -60,  -449,  -449,  -449,  -449,   140,
    -449,   172,  4169,  -449,  4169,    84,  -449,  -449,  -449,   -14,
     -14,  4169,  4169,  4169,  4169,  4169,  4169,  4169,  -449,   -68,
    -449,  -449,  -449,  -449,  4169,  4169,  4169,  4169,  4169,  4169,
    -449,  -449,    87,  -449,  -449,    93,    95,   106,  2837,   110,
     114,   117,   116,    79,  -449,  -449,  -449,  -449,  -449,   146,
     159,  -449,  -449,   184,  -449,  -449,  4307,  -449,    18,   841,
     135,  -449,   188,  -449,    89,  -449,   -81,  -449,  -449,  -449,
    3281,  -449,  4373,  -449,  4436,  3392,  -449,   -32,  5339,   -14,
    4169,  -449,  -449,   -78,    33,  -449,  5339,  5339,   -14,    -3,
     191,   193,   149,  -449,   197,   -23,   -81,  5461,  5339,  5339,
    -449,   138,  5339,   503,   156,    40,   -14,  -449,   178,   151,
    -449,  -449,  -449,  4502,   153,   155,   205,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  3503,   -11,   -11,
     251,  -449,  -449,  4565,  1239,  4169,  4169,  4169,  4169,   240,
    4169,  4169,   185,   229,  -449,   187,  -449,   266,    12,  4169,
    4169,  4169,   -21,  4169,  4169,  4169,  4169,  4169,  4169,  4169,
    4169,  4169,  4169,  4169,  4169,  4169,  4169,  4169,  4169,  4169,
    4169,  4169,  4169,  4169,  4169,  4169,  -449,  -449,  -449,  4169,
    4169,  4169,  4169,  4169,  4169,  4169,  4169,  4169,  4169,  4169,
    3614,  3503,   -47,   188,  -449,  4169,  4169,    87,    99,   -14,
    5210,   163,   186,  -449,  -449,  -449,  4631,  4169,  -449,   164,
    4694,  4169,  -449,  -449,   -84,  -449,  -449,   -85,   168,  -449,
     -48,  -449,   -71,  3503,  -449,   -47,   -23,  -449,  -449,   717,
     194,  -449,    11,  -449,  -449,   170,  -449,  -449,   167,    34,
     -14,   174,   192,    62,   647,  -449,   177,  -449,  -449,  -449,
    -449,  -449,   681,  4760,   303,   241,  4823,   179,   180,   203,
    5339,  4889,   195,    63,  -449,   189,  -449,   284,   218,   206,
     207,   208,   -23,   -81,  5461,  5404,   491,  -449,  5726,  5726,
    5726,  5726,   428,   428,    37,    37,  5573,  5628,   829,  5640,
    5755,  5695,   -11,   -11,   -11,   251,   251,   251,   428,   428,
    5147,  5461,  5461,  5461,  5461,  5461,  5461,  5461,  5461,  5461,
    5461,  5461,   -31,  5461,   190,  -449,  4169,  -449,   210,    58,
    -449,  -449,  5339,   209,   916,  -449,  -449,  3725,  -449,  3836,
    -449,  -449,  5339,  -449,  -449,   982,  -449,   -14,  -449,    -3,
      -3,   199,  -449,   211,  -449,   213,   259,   717,   717,  -449,
    -449,  -449,   219,   -14,   214,  -449,  -449,   207,  -449,  -449,
    3947,   220,  -449,  2172,   -14,   -66,  2305,  4169,  4169,  4169,
     -46,   717,   243,  2438,   218,   223,   218,   299,  -449,   244,
    -449,  -449,  3503,  3503,   -23,  -449,  4169,   -21,  -449,  -449,
    1047,  3503,  -449,  4169,  4169,  -449,  -449,   -14,  5339,   -14,
    5277,  -449,  -449,    72,  -449,  4169,  -449,   277,   717,   252,
    -449,  -449,   717,  -449,  -449,   -14,    73,   762,   226,  -449,
    -449,   281,   -14,   281,  -449,  -449,  -449,  -449,  4952,   228,
    5339,   230,   232,  -449,  -449,   236,  -449,  -449,  -449,   262,
       0,  -449,   218,   239,   218,     9,   234,   238,  5518,   149,
    -449,   242,   245,  1112,  -449,  -449,  4058,  -449,  5461,   -47,
    -449,   300,   254,   271,  -449,  -449,  -449,  -449,  2039,   181,
     -66,   256,  -449,   257,  1374,   258,  4169,  -449,   183,  -449,
       3,   717,  1507,   260,  -449,  -449,   261,   272,   -75,   244,
    -449,  -449,   289,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,   283,   372,   200,  -449,    47,  -449,  -449,  -449,
    -449,  -449,  -449,   -14,  5339,  -449,   717,  -449,   717,  -449,
     217,  2837,  -449,   278,  -449,  -449,  2571,  2571,   282,  -449,
     285,   204,  -449,  -449,   286,  4169,  -119,     4,  -449,  -449,
     287,   116,   116,    25,   288,   311,    68,   295,   296,    50,
      79,  -449,   321,  -449,  -449,  -449,   349,   301,   305,   407,
    -449,  4169,  -449,  -449,  -449,  -449,  -449,  2704,   298,  -449,
    4243,  -449,  -449,  -449,  -449,  -449,   229,  -449,    28,   717,
     313,  -449,   717,   717,   330,  -449,   335,   316,   717,  -449,
    4169,   312,  5018,  1640,  -449,  -449,  -449,  -449,  -449,  2039,
     315,  -449,   229,  -449,   318,   340,  -449,   717,  -449,  -449,
    -449,   322,  -449,   717,  -449,  2039,  5081,  -449,  2837,   317,
    1773,  2039,   218,  -449,   717,   323,  -449,   717,   320,  -449,
     324,  -449,  -449,   325,   347,  -449,   717,  -449,     0,  -449,
    -449,   327,  -449,   328,  2039,   116,   121,  -449,  -449,  -449,
    -449,  -449
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -449,  -449,  -449,  -449,  -448,  -449,    -2,  -449,   -99,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,   290,   -77,  -449,  -449,
    -449,  -449,  -449,  -177,  -449,    76,  -449,   469,   470,  -120,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
      -8,    13,   -28,  -449,   -89,  -449,  -449,  -449,  -434,  -131,
    -449,  -449,  -449,  -449,  -449,  -195,  -449,   -97,  -205,  -449,
    -449,   235,  -449,   -42,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,   -52,  -449,  -449,  -449,  -398,  -449,    16,  -449,   -25,
    -187,  -449,  -449,  -449,   477,    -5,  -247,  -346,  -449,  -449,
    -449,    -4,  -449,   468,   377,  -233,   216,     5,  -449,   268,
    -449,  -184,  -449,  -449,   -24,   -19,  -449,    71,  -257,  -449,
    -449,   -12,   126,   129,  -449,  -449,  -449,  -449,  -449,   -79
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -309
static const yytype_int16 yytable[] =
{
      74,   131,   134,   183,   311,   317,   365,   135,   384,   524,
     469,   508,   427,   611,   136,   572,   572,   514,   612,  -253,
     573,   573,   389,   532,   156,   156,   354,   122,   522,   192,
      60,   377,   155,    60,   524,   143,   584,   110,   520,   258,
      60,   450,   451,   585,   155,    60,   141,   398,   357,   147,
     144,   378,   462,     3,   158,   158,   123,   533,   383,   237,
     251,   534,    72,   355,    60,   474,   535,   167,   380,    72,
     536,   537,   538,   539,    72,   148,   179,   192,   382,   155,
      60,   357,   532,   571,   247,   577,   471,   238,   381,   130,
      60,   356,   472,    72,   156,   311,   155,    60,   156,   217,
     218,   115,   501,   156,   156,   248,   505,   155,    60,    72,
     525,   235,   210,   211,   212,   236,   533,   266,   570,    72,
     534,   156,   310,    60,   249,   535,    72,   393,   253,   536,
     537,   538,   539,   256,   259,   525,  -120,    72,   203,   644,
     389,   389,   578,   614,   397,    60,   645,   394,   540,   254,
     119,   274,    72,   150,   633,   120,   270,   207,   208,   209,
     210,   211,   212,   592,   389,   639,   624,   131,   134,   312,
     255,   461,   284,   135,    72,   579,   313,   271,  -134,   412,
     136,   655,   295,   283,   593,   151,   660,   625,   380,  -137,
     661,   128,   433,   294,   129,   572,   434,   184,  -134,   413,
     573,   389,   561,   562,   494,   389,   495,   621,   497,  -137,
     595,   574,   596,   312,   156,   146,   572,   486,   487,   154,
     313,   573,   506,   235,  -307,   175,   491,   236,   176,   512,
     177,   684,   608,   235,  -308,  -161,   284,   236,   597,   562,
     489,   178,   555,   312,   366,   180,   312,   283,   533,   181,
     313,   405,   182,   313,    71,   156,   186,   535,   688,    71,
     312,   536,   537,   538,   539,   157,   159,   313,   284,   187,
     231,   188,   232,   646,   389,   267,   649,   650,  -253,   283,
     262,   265,   654,   420,   263,   366,   269,   275,   276,   278,
     167,   192,   279,   297,   424,   302,   304,   306,   308,   368,
     373,   666,   369,   379,   396,   392,   395,   669,   400,   389,
     399,   389,   401,   404,   407,   357,   416,   408,   675,   409,
     594,   677,  -299,  -299,   414,   411,   429,   156,   418,   445,
     682,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   422,   423,   421,   431,   449,   446,   448,   452,
     435,   454,   156,   475,   156,   156,   458,   428,   480,   482,
     484,   499,   504,   507,   510,   516,   521,   517,   156,   519,
     547,   230,   389,   523,   548,   389,   389,   530,   550,   156,
     156,   389,   442,   556,   259,   259,   551,   558,   583,   479,
     557,   481,   566,   567,   588,   569,   581,   582,   274,   587,
     389,   460,   131,   134,   466,   457,   389,    19,   135,   366,
     366,   477,   156,   601,   156,   136,   456,   389,   619,   606,
     389,   607,   620,   609,   615,   622,   623,   284,   284,   389,
     156,   627,   628,   629,   631,   637,   284,   156,   283,   283,
     630,   651,   366,   647,   366,   652,   653,   283,   664,   657,
     662,   665,   667,   676,   672,   678,   679,   420,   681,   531,
     366,   598,   680,   685,   686,   663,   590,   366,   192,   453,
     626,    85,    86,   305,   529,   112,   513,   114,   605,   638,
     312,   118,   565,   683,   549,   156,   618,   313,   586,   376,
     126,   127,   591,   121,   189,   137,   138,   139,   142,   559,
     252,   361,   616,   617,   492,   443,     0,  -309,  -309,   444,
     152,     0,   153,   199,   200,   366,     0,     0,     0,   160,
     161,   162,   163,   164,   165,   166,     0,     0,   156,   203,
       0,   192,   168,   169,   170,   171,   172,   173,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   207,   208,
     209,   210,   211,   212,     0,     0,  -309,  -309,   366,   600,
       0,     0,     0,     0,   603,   603,   193,   194,   195,   196,
     197,   198,     0,     0,     0,     0,   199,   200,   240,   201,
     202,     0,     0,   246,  -299,  -299,     0,     0,   250,     0,
       0,     0,   203,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,     0,   635,   687,   690,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,     0,   213,
     214,     0,   215,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   230,     0,   142,     0,   674,     0,     0,
     268,     0,     0,   292,   293,   142,   296,     0,   300,   301,
       0,     0,     0,     0,     0,     0,   671,   314,   315,   316,
       0,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   189,   190,   191,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   353,   142,
       0,     0,     0,   362,   364,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   372,     0,     0,     0,   375,
       0,   192,     0,     4,     0,     5,   385,     0,  -299,  -299,
       0,   142,     0,     0,     0,     0,     0,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,     0,     0,
       0,     0,     0,     0,     0,     0,   193,   194,   195,   196,
     197,   198,     0,  -135,     0,     0,   199,   200,     0,   201,
     202,    36,    37,    38,     0,     0,     0,   230,     0,     0,
       0,     0,   203,  -135,     0,     0,     0,     0,     0,    46,
      47,    48,     0,     0,     0,     0,     0,     0,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,     0,   213,
     214,     0,   215,     0,     0,     0,     0,     0,     0,     0,
     402,     0,     0,     0,   430,     0,    58,   386,     0,    61,
      62,     0,   189,   190,   191,   438,     0,   440,   387,   388,
       0,     0,     0,  -299,  -299,     0,     0,     0,     0,     0,
       0,     0,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,     0,     0,     0,     0,     0,   142,   192,
       0,     0,     0,     0,     0,   468,   300,   470,  -138,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     142,   142,   230,     0,   488,     0,     0,     0,  -138,   142,
       0,   362,   493,     0,   193,   194,   195,   196,   197,   198,
       0,     0,     0,   498,   199,   200,     0,   201,   202,   189,
     190,   191,  -299,  -299,     0,     0,     0,     0,     0,     0,
     203,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,     0,     0,     0,     0,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,   192,   213,   214,     0,
     215,     0,     0,     0,   554,     0,     0,     0,   425,     0,
       0,   230,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   300,   189,   190,   191,     0,     0,
       0,   193,   194,   195,   196,   197,   198,     0,     0,     0,
       0,   199,   200,     0,   201,   202,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   203,     0,     0,
       0,     0,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,   610,   213,   214,     0,   215,     0,     0,
     189,   190,   191,     0,     0,   436,     0,   193,   194,   195,
     196,   197,   198,     0,     0,     0,     0,   199,   200,   632,
     201,   202,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   203,     0,     0,     0,   192,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   656,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,     0,
     213,   214,     0,   215,     0,   189,   190,   191,     0,     0,
       0,   441,   193,   194,   195,   196,   197,   198,     0,     0,
       0,     0,   199,   200,     0,   201,   202,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   203,     0,
       0,     0,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   204,   205,   206,   207,   208,   209,
     210,   211,   212,     0,     0,   213,   214,     0,   215,     0,
       0,     0,     0,     0,     0,     0,   490,   193,   194,   195,
     196,   197,   198,     0,     0,     0,     0,   199,   200,     0,
     201,   202,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   203,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,     0,
     213,   214,     0,   215,     0,     4,     0,     5,     6,     0,
       7,   552,     8,     0,     9,    10,     0,    11,    12,    13,
       0,     0,    14,     0,     0,     0,     0,     0,     0,    15,
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
       0,     0,    68,     0,    69,     0,    70,    71,   287,    72,
       4,     0,     5,     6,     0,     7,     0,     8,     0,     9,
      10,     0,    11,    12,    13,     0,     0,    14,     0,     0,
       0,     0,     0,   568,    15,    16,     0,    17,    18,    19,
      20,    21,    22,    23,     0,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,     0,    35,    36,    37,
      38,    39,     0,    40,     0,     0,     0,     0,    41,    42,
      43,     0,    44,     0,     0,   286,    46,    47,    48,     0,
       0,     0,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,     0,
       0,     0,     0,     0,     0,    64,    65,     0,     0,     0,
      66,    67,     0,     0,     0,     0,     0,    68,     0,    69,
       0,    70,    71,     4,    72,     5,     6,     0,     7,     0,
       8,     0,     9,    10,     0,    11,    12,    13,     0,     0,
      14,   580,     0,     0,     0,     0,     0,    15,    16,     0,
      17,    18,    19,    20,    21,    22,    23,     0,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,     0,
      35,    36,    37,    38,    39,     0,    40,     0,     0,     0,
       0,    41,    42,    43,     0,    44,     0,     0,   286,    46,
      47,    48,     0,     0,     0,     0,     0,     0,    49,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,     0,     0,     0,     0,     0,     0,    64,    65,
       0,     0,     0,    66,    67,     0,     0,     0,     0,     0,
      68,     0,    69,     0,    70,    71,     4,    72,     5,     6,
       0,     7,     0,     8,     0,     9,    10,     0,    11,    12,
      13,     0,     0,    14,     0,     0,   659,     0,     0,     0,
      15,    16,     0,    17,    18,    19,    20,    21,    22,    23,
       0,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,     0,    35,    36,    37,    38,    39,     0,    40,
       0,     0,     0,     0,    41,    42,    43,     0,    44,     0,
       0,   286,    46,    47,    48,     0,     0,     0,     0,     0,
       0,    49,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,     0,     0,     0,     0,     0,
       0,    64,    65,     0,     0,     0,    66,    67,     0,     0,
       0,     0,     0,    68,     0,    69,     0,    70,    71,     4,
      72,     5,     6,     0,     7,     0,     8,     0,     9,    10,
       0,    11,    12,    13,     0,     0,    14,     0,   673,     0,
       0,     0,     0,    15,    16,     0,    17,    18,    19,    20,
      21,    22,    23,     0,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,     0,    35,    36,    37,    38,
      39,     0,    40,     0,     0,     0,     0,    41,    42,    43,
       0,    44,     0,     0,   286,    46,    47,    48,     0,     0,
       0,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,     0,     0,
       0,     0,     0,     0,    64,    65,     0,     0,     0,    66,
      67,     0,     0,     0,     0,     0,    68,     0,    69,     0,
      70,    71,     4,    72,     5,     6,     0,     7,     0,     8,
       0,     9,    10,     0,    11,    12,    13,     0,     0,    14,
       0,     0,     0,     0,     0,     0,    15,    16,     0,    17,
      18,    19,    20,    21,    22,    23,     0,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,     0,    35,
      36,    37,    38,    39,     0,    40,     0,     0,     0,     0,
      41,    42,    43,     0,    44,     0,     0,    45,    46,    47,
      48,     0,     0,     0,     0,     0,     0,    49,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     0,     0,     0,     0,     0,     0,    64,    65,     0,
       0,     0,    66,    67,     0,     0,     0,     0,     0,    68,
       0,    69,     0,    70,    71,     4,    72,     5,     6,     0,
       7,     0,     8,     0,     9,    10,     0,    11,    12,    13,
       0,     0,    14,     0,     0,     0,     0,     0,     0,    15,
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
       5,     6,     0,     7,     0,     0,     0,     9,    10,     0,
      11,    12,    13,     0,     0,    14,     0,     0,     0,     0,
       0,     0,    15,    16,     0,    17,    18,     0,    20,    21,
      22,    23,     0,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,     0,    35,    36,    37,    38,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    43,     0,
      44,     0,     0,     0,    46,    47,    48,     0,     0,     0,
       0,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,     0,     0,     0,
       0,     0,     0,    64,    65,     0,     0,     0,    66,    67,
       0,     0,     0,     0,   459,    68,     0,    69,     0,    70,
      71,     4,    72,     5,     6,     0,     7,     0,     0,     0,
       9,    10,     0,    11,    12,    13,     0,     0,    14,     0,
       0,     0,     0,     0,     0,    15,    16,     0,    17,    18,
       0,    20,    21,    22,    23,     0,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,     0,    35,    36,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
      42,    43,     0,    44,     0,     0,     0,    46,    47,    48,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
       0,     0,     0,     0,     0,     0,    64,    65,     0,     0,
       0,    66,    67,     0,     0,     0,     0,   465,    68,     0,
      69,     0,    70,    71,     4,    72,     5,     6,     0,     7,
       0,     0,     0,     9,    10,     0,    11,    12,    13,     0,
       0,    14,     0,     0,     0,     0,     0,     0,    15,    16,
       0,    17,    18,     0,    20,    21,    22,    23,     0,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
       0,    35,    36,    37,    38,     0,     0,     0,     0,     0,
       0,     0,     0,    42,    43,     0,    44,     0,     0,     0,
      46,    47,    48,     0,     0,     0,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,     0,     0,     0,     0,     0,     0,    64,
      65,     0,     0,     0,    66,    67,     0,     0,     0,     0,
     476,    68,     0,    69,     0,    70,    71,     4,    72,     5,
       6,     0,     7,     0,     0,     0,     9,    10,     0,    11,
      12,    13,     0,     0,    14,     0,     0,     0,     0,     0,
       0,    15,    16,     0,    17,    18,     0,    20,    21,    22,
      23,     0,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,     0,    35,    36,    37,    38,     0,     0,
       0,     0,     0,     0,     0,     0,    42,    43,     0,    44,
       0,     0,     0,    46,    47,    48,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,     0,     0,     0,     0,
       0,     0,    64,    65,     0,     0,     0,    66,    67,     0,
       0,     0,     0,   602,    68,     0,    69,     0,    70,    71,
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
      66,    67,     0,     0,     0,     0,   634,    68,     0,    69,
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
      62,    63,     0,     0,     4,     0,     5,     6,    64,    65,
       0,     0,     0,    66,    67,     0,    11,     0,     0,     0,
      68,    14,    69,     0,    70,    71,     0,    72,    15,    16,
       0,     0,     0,     0,     0,     0,    22,    23,     0,    24,
      25,    26,    27,    28,    29,     0,     0,     0,     0,     0,
       0,     0,    36,    37,    38,     0,     0,     0,     0,     0,
       0,     0,     0,    42,     0,     0,     0,     0,     0,     0,
      46,    47,    48,     0,     0,     0,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,     0,     0,     0,     4,     0,     5,     6,    64,
      65,     0,     0,     0,    66,    67,     0,    11,     0,     0,
       0,    68,    14,    69,     0,   111,     0,     0,    72,    15,
      16,     0,     0,     0,     0,     0,     0,    22,    23,     0,
      24,    25,    26,    27,    28,    29,     0,     0,     0,     0,
       0,     0,     0,    36,    37,    38,     0,     0,     0,     0,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,     0,     0,     0,     4,     0,     5,     6,
      64,    65,     0,     0,     0,    66,    67,     0,    11,     0,
       0,     0,    68,    14,    69,     0,   113,     0,     0,    72,
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
       0,     0,     0,    68,    14,    69,     0,   140,     0,     0,
      72,    15,    16,     0,     0,     0,     0,     0,     0,    22,
      23,     0,    24,    25,    26,    27,    28,    29,     0,     0,
       0,     0,     0,     0,     0,    36,    37,    38,     0,     0,
       0,     0,     0,     0,     0,     0,    42,     0,     0,     0,
       0,     0,     0,    46,    47,    48,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,     0,     0,     0,     4,   239,
       5,     6,    64,    65,     0,     0,     0,    66,    67,     0,
      11,     0,     0,     0,    68,    14,    69,     0,     0,     0,
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
       0,    11,     0,     0,     0,    68,    14,    69,   245,     0,
       0,     0,    72,    15,    16,     0,     0,     0,     0,     0,
       0,    22,    23,     0,    24,    25,    26,    27,    28,    29,
       0,     0,     0,     0,     0,     0,     0,    36,    37,    38,
       0,     0,     0,     0,     0,     0,     0,     0,    42,     0,
       0,     0,     0,     0,     0,    46,    47,    48,     0,     0,
       0,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,     0,     0,     0,
       4,   280,     5,     6,    64,    65,     0,     0,     0,    66,
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
       0,     4,   352,     5,     6,    64,    65,     0,     0,     0,
      66,    67,     0,    11,     0,     0,     0,    68,    14,    69,
       0,     0,     0,     0,    72,    15,    16,     0,     0,     0,
       0,     0,     0,    22,    23,     0,    24,    25,    26,    27,
      28,    29,     0,     0,     0,     0,     0,     0,     0,    36,
      37,    38,     0,     0,     0,     0,     0,     0,     0,     0,
      42,     0,     0,     0,     0,     0,     0,    46,    47,    48,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,     0,
       0,     0,     4,   437,     5,     6,    64,    65,     0,     0,
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
       0,     0,     0,     4,   439,     5,     6,    64,    65,     0,
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
      62,     0,     0,     0,     4,   455,     5,     6,    64,    65,
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
      61,    62,     0,     0,     0,     4,   553,     5,     6,    64,
      65,     0,     0,     0,    66,    67,     0,    11,     0,     0,
       0,    68,    14,    69,     0,     0,     0,     0,    72,    15,
      16,     0,     0,     0,     0,     0,     0,    22,    23,     0,
      24,    25,    26,    27,    28,    29,     0,     0,     0,     0,
       0,     0,     0,    36,    37,    38,     0,     0,     0,     0,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,    46,    47,    48,     0,     0,   189,   190,   191,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,   192,     0,     0,     0,     0,     0,     0,
      64,    65,     0,     0,     0,    66,    67,     0,     0,     0,
       0,     0,    68,     0,    69,     0,     0,     0,     0,    72,
     189,   190,   191,     0,     0,     0,     0,     0,   193,   194,
     195,   196,   197,   198,     0,     0,     0,     0,   199,   200,
       0,   201,   202,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   203,     0,     0,   192,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
       0,   213,   214,     0,   215,   611,   189,   190,   191,     0,
     612,     0,   193,   194,   195,   196,   197,   198,     0,     0,
       0,     0,   199,   200,     0,   201,   202,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   203,     0,
       0,     0,     0,   192,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   204,   205,   206,   207,   208,   209,
     210,   211,   212,     0,     0,   213,   214,     0,   215,   189,
     190,   191,     0,     0,   216,     0,     0,     0,   193,   194,
     195,   196,   197,   198,     0,     0,     0,     0,   199,   200,
       0,   201,   202,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   203,     0,   192,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
       0,   213,   214,     0,   215,   189,   190,   191,     0,     0,
     243,   193,   194,   195,   196,   197,   198,     0,     0,     0,
       0,   199,   200,     0,   201,   202,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   203,     0,     0,
       0,     0,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   204,   205,   206,   207,   208,   209,   210,
     211,   212,     0,     0,   213,   214,     0,   215,   189,   190,
     191,     0,     0,   244,     0,     0,     0,   193,   194,   195,
     196,   197,   198,     0,     0,     0,     0,   199,   200,     0,
     201,   202,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   203,     0,   192,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,     0,
     213,   214,     0,   215,   189,   190,   191,     0,     0,   277,
     193,   194,   195,   196,   197,   198,     0,     0,     0,     0,
     199,   200,     0,   201,   202,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   203,     0,     0,     0,
       0,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   204,   205,   206,   207,   208,   209,   210,   211,
     212,     0,     0,   213,   214,     0,   215,   189,   190,   191,
       0,   285,     0,     0,     0,     0,   193,   194,   195,   196,
     197,   198,     0,     0,     0,     0,   199,   200,     0,   201,
     202,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   203,     0,   192,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,     0,   213,
     214,     0,   215,   189,   190,   191,     0,   371,     0,   193,
     194,   195,   196,   197,   198,     0,     0,     0,     0,   199,
     200,     0,   201,   202,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   203,     0,     0,     0,     0,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,     0,   213,   214,     0,   215,   189,   190,   191,     0,
     374,     0,     0,     0,     0,   193,   194,   195,   196,   197,
     198,     0,     0,     0,     0,   199,   200,     0,   201,   202,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   203,     0,   192,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   204,   205,   206,
     207,   208,   209,   210,   211,   212,     0,     0,   213,   214,
       0,   215,   189,   190,   191,     0,   403,     0,   193,   194,
     195,   196,   197,   198,     0,     0,     0,     0,   199,   200,
       0,   201,   202,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   203,     0,     0,     0,     0,   192,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
       0,   213,   214,     0,   215,   189,   190,   191,     0,   406,
       0,     0,     0,     0,   193,   194,   195,   196,   197,   198,
       0,     0,     0,     0,   199,   200,     0,   201,   202,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     203,     0,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,     0,   213,   214,     0,
     215,   189,   190,   191,     0,   410,     0,   193,   194,   195,
     196,   197,   198,     0,     0,     0,     0,   199,   200,     0,
     201,   202,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   203,     0,     0,     0,     0,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   204,
     205,   206,   207,   208,   209,   210,   211,   212,     0,     0,
     213,   214,     0,   215,   189,   190,   191,     0,   515,     0,
       0,     0,     0,   193,   194,   195,   196,   197,   198,     0,
       0,     0,     0,   199,   200,     0,   201,   202,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   203,
       0,   192,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,     0,   213,   214,     0,   215,
     189,   190,   191,     0,   658,     0,   193,   194,   195,   196,
     197,   198,     0,     0,     0,     0,   199,   200,     0,   201,
     202,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   203,     0,     0,     0,     0,   192,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,     0,   213,
     214,     0,   215,   189,   190,   191,     0,   670,     0,     0,
       0,     0,   193,   194,   195,   196,   197,   198,     0,     0,
       0,     0,   199,   200,     0,   201,   202,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   203,     0,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   204,   205,   206,   207,   208,   209,
     210,   211,   212,     0,     0,   213,   214,     0,   215,   426,
     189,   190,   191,     0,     0,   193,   194,   195,   196,   197,
     198,     0,     0,   367,     0,   199,   200,     0,   201,   202,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   203,     0,     0,     0,     0,     0,   192,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   204,   205,   206,
     207,   208,   209,   210,   211,   212,     0,     0,   213,   214,
       0,   215,   189,   190,   191,     0,     0,     0,     0,     0,
       0,     0,   193,   194,   195,   196,   197,   198,     0,     0,
     496,     0,   199,   200,     0,   201,   202,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   203,   192,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   204,   205,   206,   207,   208,   209,
     210,   211,   212,     0,     0,   213,   214,   189,   215,   191,
       0,     0,     0,     0,   193,   194,   195,   196,   197,   198,
       0,     0,     0,     0,   199,   200,     0,   201,   202,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     203,     0,     0,     0,   192,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   204,   205,   206,   207,
     208,   209,   210,   211,   212,     0,     0,   213,   214,     0,
     215,     0,     0,     0,     0,     0,     0,     0,     0,   193,
     194,   195,   196,   197,   198,     0,     0,     0,     0,   199,
     200,     0,   201,   202,     0,     0,     0,     0,     0,     0,
       0,   192,     0,     0,     0,   203,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
       0,     0,   213,   214,     0,   215,   193,   194,   195,   196,
     197,   198,     0,     0,     0,     0,   199,   200,     0,   201,
     202,     0,     0,     0,     0,     0,     0,     0,   192,     0,
       0,     0,   203,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,     0,   213,
     214,     0,   215,   193,   194,   195,   196,   197,   198,     0,
       0,     0,     0,   199,   200,     0,   201,   202,     0,     0,
       0,     0,     0,   192,     0,     0,     0,     0,     0,   203,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,     0,   213,   214,   193,   194,
     195,   196,   197,   198,     0,     0,     0,     0,   199,   200,
       0,     0,   202,     0,     0,     0,     0,     0,   192,     0,
       0,     0,     0,     0,   203,     0,     0,     0,     0,     0,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     204,   205,   206,   207,   208,   209,   210,   211,   212,     0,
       0,   213,   214,   193,   194,   195,   196,   197,   198,     0,
       0,     0,     0,   199,   200,   193,   194,   195,   196,   197,
     198,     0,     0,     0,     0,   199,   200,     0,     0,   203,
       0,     0,     0,     0,     0,   192,     0,     0,     0,     0,
       0,   203,     0,     0,     0,   204,   205,   206,   207,   208,
     209,   210,   211,   212,     0,     0,   213,   214,   205,   206,
     207,   208,   209,   210,   211,   212,   192,     0,   213,   214,
     193,   194,   195,   196,   197,   198,     0,     0,     0,     0,
     199,   200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   192,   203,     0,     0,     0,
       0,  -309,  -309,  -309,  -309,   197,   198,     0,     0,     0,
       0,   199,   200,   205,     0,   207,   208,   209,   210,   211,
     212,     0,     0,   213,   214,     0,     0,   203,     0,     0,
     193,   194,   195,   196,   197,   198,     0,     0,     0,     0,
     199,   200,     0,     0,     0,     0,   207,   208,   209,   210,
     211,   212,     0,     0,   213,   214,   203,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   207,   208,   209,   210,   211,
     212,     0,     0,   213,   214
};

static const yytype_int16 yycheck[] =
{
       2,    26,    26,    82,   188,   192,   239,    26,   265,     9,
     408,   459,    43,   132,    26,    12,    12,   465,   137,    87,
      17,    17,   269,    14,    49,    50,   231,   111,   476,    40,
     111,   116,   110,   111,     9,    30,   111,   135,   472,    42,
     111,   387,   388,   118,   110,   111,    30,   280,   232,   109,
     111,   136,   118,     0,    49,    50,   140,    48,   263,   140,
     138,    52,   140,   110,   111,   411,    57,   135,   116,   140,
      61,    62,    63,    64,   140,   135,    78,    40,   262,   110,
     111,   265,    14,   517,   116,   519,   132,   106,   136,   110,
     111,   138,   138,   140,   119,   279,   110,   111,   123,    81,
      82,   135,   448,   128,   129,   137,   452,   110,   111,   140,
     110,   134,   123,   124,   125,   138,    48,   136,   516,   140,
      52,   146,   110,   111,   119,    57,   140,   116,   123,    61,
      62,    63,    64,   128,   129,   110,   136,   140,   101,   111,
     387,   388,   139,   139,   110,   111,   118,   136,   139,   116,
     135,   146,   140,    13,   602,   135,   116,   120,   121,   122,
     123,   124,   125,   116,   411,   613,   116,   192,   192,   188,
     137,   404,   167,   192,   140,   521,   188,   137,   116,   116,
     192,   629,   177,   167,   137,    13,   634,   137,   116,   116,
     638,   135,   134,   177,   135,    12,   138,   118,   136,   136,
      17,   448,    21,    22,   437,   452,   439,   139,   136,   136,
     556,    28,   558,   232,   239,   135,    12,   422,   423,   135,
     232,    17,   455,   134,   135,   138,   431,   138,   135,   462,
     135,   679,    28,   134,   135,    35,   231,   138,    21,    22,
     427,   135,   499,   262,   239,   135,   265,   231,    48,   135,
     262,    10,   135,   265,   138,   280,   110,    57,   137,   138,
     279,    61,    62,    63,    64,    49,    50,   279,   263,   110,
     135,    87,    84,   619,   521,   137,   622,   623,    87,   263,
      87,    84,   628,   308,   135,   280,   130,   109,   137,   136,
     135,    40,    87,    53,   313,   110,    67,   110,    32,   136,
     136,   647,   116,   135,   137,   111,   136,   653,   116,   556,
     136,   558,   135,    10,   135,   499,    32,   137,   664,   116,
     553,   667,    81,    82,   135,   130,   136,   352,   110,   130,
     676,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   135,   135,   138,   135,    87,   136,   135,   130,
     141,   137,   377,   110,   379,   380,   136,   352,   135,    60,
     116,    84,   110,   137,    83,   137,   130,   137,   393,   137,
     136,   130,   619,   111,   136,   622,   623,   138,   136,   404,
     405,   628,   377,    83,   379,   380,   141,   116,   116,   414,
     136,   416,   136,   136,   111,   137,   136,   136,   393,   110,
     647,   403,   427,   427,   406,   400,   653,    35,   427,   404,
     405,   413,   437,   135,   439,   427,   400,   664,   130,   137,
     667,   136,   111,   137,   137,   130,   130,   422,   423,   676,
     455,   110,    83,   132,    27,   137,   431,   462,   422,   423,
     135,   111,   437,   130,   439,   110,   130,   431,   130,   137,
     135,   111,   130,   130,   137,   135,   132,   482,   111,   484,
     455,   560,   137,   136,   136,   642,   543,   462,    40,   393,
     590,     2,     2,   183,   482,     7,   463,     9,   567,   610,
     499,    13,   510,   678,   489,   510,   583,   499,   530,   254,
      22,    23,   544,    16,     3,    27,    28,    29,    30,   503,
     123,   233,   581,   582,   433,   379,    -1,    79,    80,   380,
      42,    -1,    44,    85,    86,   510,    -1,    -1,    -1,    51,
      52,    53,    54,    55,    56,    57,    -1,    -1,   553,   101,
      -1,    40,    64,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,   121,
     122,   123,   124,   125,    -1,    -1,   128,   129,   553,   561,
      -1,    -1,    -1,    -1,   566,   567,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,   110,    88,
      89,    -1,    -1,   115,    81,    82,    -1,    -1,   120,    -1,
      -1,    -1,   101,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,   607,   685,   686,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    -1,    -1,   128,
     129,    -1,   131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   130,    -1,   167,    -1,   662,    -1,    -1,
     137,    -1,    -1,   175,   176,   177,   178,    -1,   180,   181,
      -1,    -1,    -1,    -1,    -1,    -1,   658,   189,   190,   191,
      -1,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,     3,     4,     5,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
      -1,    -1,    -1,   235,   236,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   247,    -1,    -1,    -1,   251,
      -1,    40,    -1,     6,    -1,     8,     9,    -1,    81,    82,
      -1,   263,    -1,    -1,    -1,    -1,    -1,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    80,    -1,   116,    -1,    -1,    85,    86,    -1,    88,
      89,    54,    55,    56,    -1,    -1,    -1,   130,    -1,    -1,
      -1,    -1,   101,   136,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    -1,    -1,   128,
     129,    -1,   131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,    -1,    -1,   356,    -1,   109,   110,    -1,   112,
     113,    -1,     3,     4,     5,   367,    -1,   369,   121,   122,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,    -1,    -1,    -1,    -1,    -1,   400,    40,
      -1,    -1,    -1,    -1,    -1,   407,   408,   409,   116,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     422,   423,   130,    -1,   426,    -1,    -1,    -1,   136,   431,
      -1,   433,   434,    -1,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,   445,    85,    86,    -1,    88,    89,     3,
       4,     5,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,    -1,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   122,   123,   124,   125,    -1,    40,   128,   129,    -1,
     131,    -1,    -1,    -1,   496,    -1,    -1,    -1,   139,    -1,
      -1,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   516,     3,     4,     5,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,   119,   120,   121,   122,   123,
     124,   125,    -1,   575,   128,   129,    -1,   131,    -1,    -1,
       3,     4,     5,    -1,    -1,   139,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,   601,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   630,   117,
     118,   119,   120,   121,   122,   123,   124,   125,    -1,    -1,
     128,   129,    -1,   131,    -1,     3,     4,     5,    -1,    -1,
      -1,   139,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,   125,    -1,    -1,   128,   129,    -1,   131,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   139,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,   125,    -1,    -1,
     128,   129,    -1,   131,    -1,     6,    -1,     8,     9,    -1,
      11,   139,    13,    -1,    15,    16,    -1,    18,    19,    20,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
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
      -1,    -1,   133,    -1,   135,    -1,   137,   138,   139,   140,
       6,    -1,     8,     9,    -1,    11,    -1,    13,    -1,    15,
      16,    -1,    18,    19,    20,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    54,    55,
      56,    57,    -1,    59,    -1,    -1,    -1,    -1,    64,    65,
      66,    -1,    68,    -1,    -1,    71,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,    -1,
      -1,    -1,    -1,    -1,    -1,   121,   122,    -1,    -1,    -1,
     126,   127,    -1,    -1,    -1,    -1,    -1,   133,    -1,   135,
      -1,   137,   138,     6,   140,     8,     9,    -1,    11,    -1,
      13,    -1,    15,    16,    -1,    18,    19,    20,    -1,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      33,    34,    35,    36,    37,    38,    39,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    -1,    59,    -1,    -1,    -1,
      -1,    64,    65,    66,    -1,    68,    -1,    -1,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,
      -1,    -1,    -1,   126,   127,    -1,    -1,    -1,    -1,    -1,
     133,    -1,   135,    -1,   137,   138,     6,   140,     8,     9,
      -1,    11,    -1,    13,    -1,    15,    16,    -1,    18,    19,
      20,    -1,    -1,    23,    -1,    -1,    26,    -1,    -1,    -1,
      30,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    -1,    53,    54,    55,    56,    57,    -1,    59,
      -1,    -1,    -1,    -1,    64,    65,    66,    -1,    68,    -1,
      -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,    -1,    -1,    -1,    -1,    -1,
      -1,   121,   122,    -1,    -1,    -1,   126,   127,    -1,    -1,
      -1,    -1,    -1,   133,    -1,   135,    -1,   137,   138,     6,
     140,     8,     9,    -1,    11,    -1,    13,    -1,    15,    16,
      -1,    18,    19,    20,    -1,    -1,    23,    -1,    25,    -1,
      -1,    -1,    -1,    30,    31,    -1,    33,    34,    35,    36,
      37,    38,    39,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    -1,    53,    54,    55,    56,
      57,    -1,    59,    -1,    -1,    -1,    -1,    64,    65,    66,
      -1,    68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    -1,    -1,
      -1,    -1,    -1,    -1,   121,   122,    -1,    -1,    -1,   126,
     127,    -1,    -1,    -1,    -1,    -1,   133,    -1,   135,    -1,
     137,   138,     6,   140,     8,     9,    -1,    11,    -1,    13,
      -1,    15,    16,    -1,    18,    19,    20,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    33,
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
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
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
       8,     9,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,
      18,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    33,    34,    -1,    36,    37,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    -1,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,
      68,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,    -1,    -1,    -1,
      -1,    -1,    -1,   121,   122,    -1,    -1,    -1,   126,   127,
      -1,    -1,    -1,    -1,   132,   133,    -1,   135,    -1,   137,
     138,     6,   140,     8,     9,    -1,    11,    -1,    -1,    -1,
      15,    16,    -1,    18,    19,    20,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    33,    34,
      -1,    36,    37,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    -1,    68,    -1,    -1,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
      -1,    -1,    -1,    -1,    -1,    -1,   121,   122,    -1,    -1,
      -1,   126,   127,    -1,    -1,    -1,    -1,   132,   133,    -1,
     135,    -1,   137,   138,     6,   140,     8,     9,    -1,    11,
      -1,    -1,    -1,    15,    16,    -1,    18,    19,    20,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,    33,    34,    -1,    36,    37,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    -1,    68,    -1,    -1,    -1,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,   121,
     122,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,    -1,
     132,   133,    -1,   135,    -1,   137,   138,     6,   140,     8,
       9,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    -1,    33,    34,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,    68,
      -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,    -1,    -1,    -1,    -1,
      -1,    -1,   121,   122,    -1,    -1,    -1,   126,   127,    -1,
      -1,    -1,    -1,   132,   133,    -1,   135,    -1,   137,   138,
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
     113,   114,    -1,    -1,     6,    -1,     8,     9,   121,   122,
      -1,    -1,    -1,   126,   127,    -1,    18,    -1,    -1,    -1,
     133,    23,   135,    -1,   137,   138,    -1,   140,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,    -1,    -1,    -1,     6,    -1,     8,     9,   121,
     122,    -1,    -1,    -1,   126,   127,    -1,    18,    -1,    -1,
      -1,   133,    23,   135,    -1,   137,    -1,    -1,   140,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,    -1,    -1,    -1,     6,    -1,     8,     9,
     121,   122,    -1,    -1,    -1,   126,   127,    -1,    18,    -1,
      -1,    -1,   133,    23,   135,    -1,   137,    -1,    -1,   140,
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
     109,   110,   111,   112,   113,    -1,    -1,    -1,     6,   118,
       8,     9,   121,   122,    -1,    -1,    -1,   126,   127,    -1,
      18,    -1,    -1,    -1,   133,    23,   135,    -1,    -1,    -1,
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
      -1,    18,    -1,    -1,    -1,   133,    23,   135,   136,    -1,
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
      -1,     6,   118,     8,     9,   121,   122,    -1,    -1,    -1,
     126,   127,    -1,    18,    -1,    -1,    -1,   133,    23,   135,
      -1,    -1,    -1,    -1,   140,    30,    31,    -1,    -1,    -1,
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
      -1,    72,    73,    74,    -1,    -1,     3,     4,     5,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,    40,    -1,    -1,    -1,    -1,    -1,    -1,
     121,   122,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,
      -1,    -1,   133,    -1,   135,    -1,    -1,    -1,    -1,   140,
       3,     4,     5,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,   125,    -1,
      -1,   128,   129,    -1,   131,   132,     3,     4,     5,    -1,
     137,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,   125,    -1,    -1,   128,   129,    -1,   131,     3,
       4,     5,    -1,    -1,   137,    -1,    -1,    -1,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,
      -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,   125,    -1,
      -1,   128,   129,    -1,   131,     3,     4,     5,    -1,    -1,
     137,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,   119,   120,   121,   122,   123,
     124,   125,    -1,    -1,   128,   129,    -1,   131,     3,     4,
       5,    -1,    -1,   137,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,   125,    -1,    -1,
     128,   129,    -1,   131,     3,     4,     5,    -1,    -1,   137,
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
     131,     3,     4,     5,    -1,   136,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,   125,    -1,    -1,
     128,   129,    -1,   131,     3,     4,     5,    -1,   136,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,   125,    -1,    -1,   128,   129,    -1,   131,
       3,     4,     5,    -1,   136,    -1,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   101,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    -1,    -1,   128,
     129,    -1,   131,     3,     4,     5,    -1,   136,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,   125,    -1,    -1,   128,   129,    -1,   131,   132,
       3,     4,     5,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    83,    -1,    85,    86,    -1,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,   125,    -1,    -1,   128,   129,
      -1,   131,     3,     4,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      83,    -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,   125,    -1,    -1,   128,   129,     3,   131,     5,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    -1,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   122,   123,   124,   125,    -1,    -1,   128,   129,    -1,
     131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      -1,    -1,   128,   129,    -1,   131,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    -1,    -1,   128,
     129,    -1,   131,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,   125,    -1,    -1,   128,   129,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,   125,    -1,
      -1,   128,   129,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    85,    86,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,   101,
      -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,   125,    -1,    -1,   128,   129,   118,   119,
     120,   121,   122,   123,   124,   125,    40,    -1,   128,   129,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,   101,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,   118,    -1,   120,   121,   122,   123,   124,
     125,    -1,    -1,   128,   129,    -1,    -1,   101,    -1,    -1,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    -1,    -1,    -1,    -1,   120,   121,   122,   123,
     124,   125,    -1,    -1,   128,   129,   101,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,   121,   122,   123,   124,
     125,    -1,    -1,   128,   129
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
     155,   156,   157,   159,   162,   169,   170,   172,   174,   177,
     179,   219,   220,   221,   228,   231,   235,   236,   238,   239,
     243,   244,   245,   246,   247,   248,   253,   258,   260,   261,
     135,   137,   235,   137,   235,   135,   226,   216,   235,   135,
     135,   226,   111,   140,   202,   203,   235,   235,   135,   135,
     110,   221,   222,   223,   246,   247,   253,   235,   235,   235,
     137,   219,   235,   239,   111,   204,   135,   109,   135,   168,
      13,    13,   235,   235,   135,   110,   221,   238,   239,   238,
     235,   235,   235,   235,   235,   235,   235,   135,   235,   235,
     235,   235,   235,   235,   146,   138,   135,   135,   135,   148,
     135,   135,   135,   261,   118,   171,   110,   110,    87,     3,
       4,     5,    40,    75,    76,    77,    78,    79,    80,    85,
      86,    88,    89,   101,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   128,   129,   131,   137,    81,    82,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     130,   135,    84,   240,   241,   134,   138,   140,   247,   118,
     235,   256,   257,   137,   137,   136,   235,   116,   137,   239,
     235,   138,   236,   239,   116,   137,   239,   259,    42,   239,
     254,   255,    87,   135,   227,    84,   247,   137,   137,   130,
     116,   137,   166,   167,   239,   109,   137,   137,   136,    87,
     118,   200,   201,   219,   239,   136,    71,   139,   147,   148,
     169,   170,   235,   235,   219,   239,   235,    53,   217,   218,
     235,   235,   110,   188,    67,   158,   110,   175,    32,   180,
     110,   243,   247,   253,   235,   235,   235,   222,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   118,   235,   200,   110,   138,   243,   250,   251,
     252,   241,   235,   249,   235,   237,   239,    83,   136,   116,
     233,   136,   235,   136,   136,   235,   203,   116,   136,   135,
     116,   136,   243,   200,   250,     9,   110,   121,   122,   228,
     229,   230,   111,   116,   136,   136,   137,   110,   237,   136,
     116,   135,   139,   136,    10,    10,   136,   135,   137,   116,
     136,   130,   116,   136,   135,   173,    32,   178,   110,   182,
     221,   138,   135,   135,   247,   139,   132,    43,   239,   136,
     235,   135,   242,   134,   138,   141,   139,   118,   235,   118,
     235,   139,   239,   254,   255,   130,   136,   224,   135,    87,
     229,   229,   130,   167,   137,   118,   219,   239,   136,   132,
     148,   237,   118,   184,   237,   132,   148,   192,   235,   217,
     235,   132,   138,   189,   229,   110,   132,   148,   187,   221,
     135,   221,    60,   181,   116,   205,   200,   200,   235,   222,
     139,   200,   249,   235,   237,   237,    83,   136,   235,    84,
     225,   229,   232,   234,   110,   229,   237,   137,   146,   193,
      83,   183,   237,   183,   146,   136,   137,   137,   190,   137,
     190,   130,   146,   111,     9,   110,   197,   198,   199,   182,
     138,   221,    14,    48,    52,    57,    61,    62,    63,    64,
     139,   206,   210,   211,   212,   213,   215,   136,   136,   227,
     136,   141,   139,   118,   235,   250,    83,   136,   116,   233,
     194,    21,    22,   150,   195,   184,   136,   136,    29,   137,
     217,   190,    12,    17,    28,   160,   161,   190,   139,   229,
      24,   136,   136,   116,   111,   118,   205,   110,   111,   214,
     159,   213,   116,   137,   237,   229,   229,    21,   150,   196,
     148,   135,   132,   148,   186,   186,   137,   136,    28,   137,
     235,   132,   137,   191,   139,   137,   261,   261,   199,   130,
     111,   139,   130,   130,   116,   137,   171,   110,    83,   132,
     135,    27,   235,   146,   132,   148,   185,   137,   191,   146,
     158,   163,   164,   165,   111,   118,   229,   130,   176,   229,
     229,   111,   110,   130,   229,   146,   235,   137,   136,    26,
     146,   146,   135,   165,   130,   111,   229,   130,   207,   229,
     136,   148,   137,    25,   221,   229,   130,   229,   135,   132,
     137,   111,   229,   197,   146,   136,   136,   261,   137,   209,
     261,   208
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
#line 455 "src/generated_src/php_parser.ypp"
    {
			// If there are any remaining comments, add them as a NOP
			if(!context->last_comments.empty())
				(yyvsp[(1) - (1)].list_ast_statement)->push_back(NEW(Nop, ()));
	
			context->php_script = new PHP_script((yyvsp[(1) - (1)].list_ast_statement));
      if(context->hash_bang != NULL)
        context->php_script->attrs->set("phc.unparser.hash_bang", context->hash_bang);
		;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 468 "src/generated_src/php_parser.ypp"
    {
			// is_wrapped attribute is not necessary on top-level statements
			if(!(yyvsp[(2) - (2)].list_ast_statement)->empty())
				(yyvsp[(2) - (2)].list_ast_statement)->front()->attrs->erase("phc.unparser.is_wrapped");

			(yyvsp[(1) - (2)].list_ast_statement)->push_back_all((yyvsp[(2) - (2)].list_ast_statement));
			(yyval.list_ast_statement) = (yyvsp[(1) - (2)].list_ast_statement);
		;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 477 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<Statement*>;
		;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 484 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 488 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (1)].ast_method));
		;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 492 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (1)].ast_statement));
		;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 496 "src/generated_src/php_parser.ypp"
    {
			assert(0);
		;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 506 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_statement)->push_back_all((yyvsp[(2) - (2)].list_ast_statement));
			(yyval.list_ast_statement) = (yyvsp[(1) - (2)].list_ast_statement);
		;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 511 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<Statement*>;
		;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 518 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 522 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (1)].ast_method));
		;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 526 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (1)].ast_statement));
		;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 530 "src/generated_src/php_parser.ypp"
    {
			assert(0);
		;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 537 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 548 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_if) = NEW(If, (NULL, NULL, NULL));
		;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 555 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_if) = NEW(If, (NULL, NULL, NULL));
		;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 562 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_foreach) = NEW(Foreach, (NULL, NULL, false, NULL, NULL));
		;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 569 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_while) = NEW(While, (NULL, NULL));
		;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 576 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_do) = NEW(Do, (NULL, NULL));
		;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 583 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_for) = NEW(For, (NULL, NULL, NULL, NULL));
		;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 590 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_switch) = NEW(Switch, (NULL, NULL));
		;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 597 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_declare) = NEW(Declare, (NULL, NULL));
		;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 604 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_try) = NEW(Try, (NULL, NULL));
		;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 611 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_catch) = NEW(Catch, (NULL, NULL, NULL));
		;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 618 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method) = NEW(Method, (NULL, NULL));
		;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 625 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_switch_case) = NEW(Switch_case, (NULL, NULL));
		;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 632 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_switch_case) = NEW(Switch_case, (NULL, NULL));
		;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 640 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 644 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (7)].ast_if)->expr = (yyvsp[(3) - (7)].ast_expr);
			(yyvsp[(1) - (7)].ast_if)->iftrue = (yyvsp[(5) - (7)].list_ast_statement);
			
			if((yyvsp[(6) - (7)].ast_if))
			{
				List<Statement*>* new_false = new List<Statement*>;
				new_false->push_back((yyvsp[(6) - (7)].ast_if));
				
				/* 
				 * Nest the $6 part
				 *
				 * We must add it to the most deeply nested if we can find
				 * Note that _if_ any of the nested ifs (elseifs) has a false
				 * branch, then this consists of a single instruction, an If*.
				 * So, the dynamic_cast is guaranteed to succeed.
				 *
				 * This is similar to the code in elseif_list. 
				 */ 
				while(!(yyvsp[(6) - (7)].ast_if)->iffalse->empty())
					(yyvsp[(6) - (7)].ast_if) = dynamic_cast<If*>((yyvsp[(6) - (7)].ast_if)->iffalse->front());
				(yyvsp[(6) - (7)].ast_if)->iffalse = (yyvsp[(7) - (7)].list_ast_statement);
				
				(yyvsp[(1) - (7)].ast_if)->iffalse = new_false;
			}
			else
			{
				(yyvsp[(1) - (7)].ast_if)->iffalse = (yyvsp[(7) - (7)].list_ast_statement);
			}

			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (7)].ast_if));
		;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 677 "src/generated_src/php_parser.ypp"
    {
			// Duplication of logic above for K_IF.
			
			(yyvsp[(1) - (10)].ast_if)->expr = (yyvsp[(3) - (10)].ast_expr);
			(yyvsp[(1) - (10)].ast_if)->iftrue = (yyvsp[(6) - (10)].list_ast_statement);
		
			if((yyvsp[(7) - (10)].ast_if))
			{
				List<Statement*>* new_false = new List<Statement*>;
				new_false->push_back((yyvsp[(7) - (10)].ast_if));

				while(!(yyvsp[(7) - (10)].ast_if)->iffalse->empty())
					(yyvsp[(7) - (10)].ast_if) = dynamic_cast<If*>((yyvsp[(7) - (10)].ast_if)->iffalse->front());
				(yyvsp[(7) - (10)].ast_if)->iffalse = (yyvsp[(8) - (10)].list_ast_statement);
				
				(yyvsp[(1) - (10)].ast_if)->iffalse = new_false;
			}
			else
			{
				(yyvsp[(1) - (10)].ast_if)->iffalse = (yyvsp[(8) - (10)].list_ast_statement);
			}
	
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (10)].ast_if));
		;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 702 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (5)].ast_while)->expr = (yyvsp[(3) - (5)].ast_expr);
			(yyvsp[(1) - (5)].ast_while)->statements = (yyvsp[(5) - (5)].list_ast_statement);

			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (5)].ast_while));
		;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 709 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (7)].ast_do)->statements = (yyvsp[(2) - (7)].list_ast_statement);
			(yyvsp[(1) - (7)].ast_do)->expr = (yyvsp[(5) - (7)].ast_expr);
			
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (7)].ast_do));
		;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 716 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (9)].ast_for)->init = (yyvsp[(3) - (9)].ast_expr);
			(yyvsp[(1) - (9)].ast_for)->cond = (yyvsp[(5) - (9)].ast_expr);
			(yyvsp[(1) - (9)].ast_for)->incr = (yyvsp[(7) - (9)].ast_expr);
			(yyvsp[(1) - (9)].ast_for)->statements = (yyvsp[(9) - (9)].list_ast_statement);
			
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (9)].ast_for));
		;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 725 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (5)].ast_switch)->expr = (yyvsp[(3) - (5)].ast_expr);
			(yyvsp[(1) - (5)].ast_switch)->switch_cases = (yyvsp[(5) - (5)].list_ast_switch_case);
			
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (5)].ast_switch));
		;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 732 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Break, (NULL)));
		;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 736 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Break, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 740 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Continue, (NULL)));
		;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 744 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Continue, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 748 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Return, (NULL)));
		;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 752 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Return, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 756 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Return, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 760 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Global, ((yyvsp[(2) - (3)].list_ast_variable_name))));
		;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 764 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Static_declaration, ((yyvsp[(2) - (3)].list_ast_name_with_default))));
		;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 768 "src/generated_src/php_parser.ypp"
    {
			Method_invocation* inv;
			inv = NEW(Method_invocation,
				( NULL // target
				, NEW(METHOD_NAME, (new String("echo")))
				, (yyvsp[(2) - (3)].list_ast_actual_parameter)));
				
			inv->attrs->set_true("phc.unparser.no_brackets");
			(yyval.list_ast_statement) = wrap (NEW(Eval_expr, (inv)));
		;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 779 "src/generated_src/php_parser.ypp"
    {
			STRING* scalar = NEW(STRING, ((yyvsp[(1) - (1)].string), (yyvsp[(1) - (1)].string)));
			Expr* fn = NEW(Method_invocation, ("echo", scalar));
			Eval_expr* eval_expr = NEW(Eval_expr, (fn));

			eval_expr->attrs->set_true("phc.unparser.is_inline_html");

			(yyval.list_ast_statement) = wrap(eval_expr);
		;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 789 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Eval_expr, ((yyvsp[(1) - (2)].ast_expr))));
		;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 793 "src/generated_src/php_parser.ypp"
    {
			Method_invocation* fn;
			fn = NEW(Method_invocation, ("use", (yyvsp[(2) - (3)].token_string)));
			fn->attrs->set_true("phc.unparser.no_brackets");
			(yyval.list_ast_statement) = wrap(NEW(Eval_expr, (fn)));
		;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 800 "src/generated_src/php_parser.ypp"
    {
			Method_invocation* fn;
			METHOD_NAME* unset;
			unset = new METHOD_NAME(new String("unset"));
			fn = NEW(Method_invocation, (NULL, unset, (yyvsp[(3) - (5)].list_ast_actual_parameter)));
			(yyval.list_ast_statement) = wrap(NEW(Eval_expr, (fn)));
		;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 808 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (8)].ast_foreach)->expr = (yyvsp[(3) - (8)].ast_expr);
			(yyvsp[(1) - (8)].ast_foreach)->statements = (yyvsp[(8) - (8)].list_ast_statement);
	
			if((yyvsp[(6) - (8)].ast_variable))
			{
				if((yyvsp[(5) - (8)].ast_variable)->attrs->is_true("phc.parser.is_ref"))
				{
					phc_error(ERR_FOREACH_KEY_REF, (yyvsp[(5) - (8)].ast_variable));
				}
			
				(yyvsp[(1) - (8)].ast_foreach)->key = (yyvsp[(5) - (8)].ast_variable);
				(yyvsp[(1) - (8)].ast_foreach)->is_ref = (yyvsp[(6) - (8)].ast_variable)->attrs->is_true("phc.parser.is_ref");
				(yyvsp[(1) - (8)].ast_foreach)->val = (yyvsp[(6) - (8)].ast_variable);
			}
			else
			{
				(yyvsp[(1) - (8)].ast_foreach)->key = NULL;
				(yyvsp[(1) - (8)].ast_foreach)->is_ref = (yyvsp[(5) - (8)].ast_variable)->attrs->is_true("phc.parser.is_ref");
				(yyvsp[(1) - (8)].ast_foreach)->val = (yyvsp[(5) - (8)].ast_variable);
			}

			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (8)].ast_foreach));
		;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 833 "src/generated_src/php_parser.ypp"
    {
			// Duplication of the logic in the previous rule
			(yyvsp[(1) - (8)].ast_foreach)->expr = (yyvsp[(3) - (8)].ast_expr);
			(yyvsp[(1) - (8)].ast_foreach)->statements = (yyvsp[(8) - (8)].list_ast_statement);
	
			if((yyvsp[(6) - (8)].ast_variable))
			{
				if((yyvsp[(5) - (8)].ast_expr)->attrs->is_true("phc.parser.is_ref"))
				{
					phc_error(ERR_FOREACH_KEY_REF, (yyvsp[(5) - (8)].ast_expr));
				}
			
				(yyvsp[(1) - (8)].ast_foreach)->key = expect_variable((yyvsp[(5) - (8)].ast_expr));
				(yyvsp[(1) - (8)].ast_foreach)->is_ref = (yyvsp[(6) - (8)].ast_variable)->attrs->is_true("phc.parser.is_ref");
				(yyvsp[(1) - (8)].ast_foreach)->val = (yyvsp[(6) - (8)].ast_variable);
			}
			else
			{
				(yyvsp[(1) - (8)].ast_foreach)->key = NULL;
				(yyvsp[(1) - (8)].ast_foreach)->is_ref = (yyvsp[(5) - (8)].ast_expr)->attrs->is_true("phc.parser.is_ref");
				(yyvsp[(1) - (8)].ast_foreach)->val = expect_variable((yyvsp[(5) - (8)].ast_expr));
			}

			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (8)].ast_foreach));
		;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 859 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (5)].ast_declare)->directives = (yyvsp[(3) - (5)].list_ast_directive);
			(yyvsp[(1) - (5)].ast_declare)->statements = (yyvsp[(5) - (5)].list_ast_statement);

			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (5)].ast_declare));
		;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 866 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Nop, ()));
		;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 870 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* var = new VARIABLE_NAME((yyvsp[(6) - (9)].string));
			
			(yyvsp[(3) - (9)].ast_catch)->class_name = (yyvsp[(5) - (9)].token_class_name);
			(yyvsp[(3) - (9)].ast_catch)->variable_name = var;
			(yyvsp[(3) - (9)].ast_catch)->statements = (yyvsp[(8) - (9)].list_ast_statement);

			List<Catch*>* all_catches = new List<Catch*>;
			all_catches->push_back((yyvsp[(3) - (9)].ast_catch));
			all_catches->push_back_all((yyvsp[(9) - (9)].list_ast_catch));
		
			(yyvsp[(1) - (9)].ast_try)->statements = (yyvsp[(2) - (9)].list_ast_statement);
			(yyvsp[(1) - (9)].ast_try)->catches = all_catches;
		
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (9)].ast_try));
		;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 887 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Throw, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 894 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_catch) = (yyvsp[(1) - (1)].list_ast_catch);
		;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 898 "src/generated_src/php_parser.ypp"
    {
			List<Catch*>* catches = new List<Catch*>;
			(yyval.list_ast_catch) = catches;
		;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 906 "src/generated_src/php_parser.ypp"
    {
			List<Catch*>* catches = new List<Catch*>;
			catches->push_back((yyvsp[(1) - (1)].ast_catch));
			
			(yyval.list_ast_catch) = catches;
		;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 913 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_catch)->push_back((yyvsp[(2) - (2)].ast_catch));
			
			(yyval.list_ast_catch) = (yyvsp[(1) - (2)].list_ast_catch);
		;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 922 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* var = new VARIABLE_NAME((yyvsp[(4) - (6)].string));
			
			(yyvsp[(1) - (6)].ast_catch)->class_name = (yyvsp[(3) - (6)].token_class_name);
			(yyvsp[(1) - (6)].ast_catch)->variable_name = var;
			(yyvsp[(1) - (6)].ast_catch)->statements = (yyvsp[(6) - (6)].list_ast_statement);
			
			(yyval.ast_catch) = (yyvsp[(1) - (6)].ast_catch);
		;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 935 "src/generated_src/php_parser.ypp"
    {
			List<Actual_parameter*>* vars = new List<Actual_parameter*>;
			vars->push_back(new Actual_parameter(false, (yyvsp[(1) - (1)].ast_variable)));
			(yyval.list_ast_actual_parameter) = vars;
		;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 941 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back(new Actual_parameter(false, (yyvsp[(3) - (3)].ast_variable)));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 949 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = expect_variable((yyvsp[(1) - (1)].ast_expr));
		;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 956 "src/generated_src/php_parser.ypp"
    {
			(yyval.token_string) = (yyvsp[(1) - (1)].token_string);
		;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 960 "src/generated_src/php_parser.ypp"
    {
			(yyval.token_string) = (yyvsp[(2) - (3)].token_string);
		;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 967 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method) = (yyvsp[(1) - (1)].ast_method);
		;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 974 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_statement) = (yyvsp[(1) - (1)].ast_statement);
		;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 981 "src/generated_src/php_parser.ypp"
    {
			(yyval.integer) = new Integer(0);
		;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 985 "src/generated_src/php_parser.ypp"
    {
			(yyval.integer) = new Integer(1);
		;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 991 "src/generated_src/php_parser.ypp"
    {context->current_method = dynamic_cast<String*>((yyvsp[(3) - (3)].string));;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 992 "src/generated_src/php_parser.ypp"
    {
			METHOD_NAME* name = new METHOD_NAME((yyvsp[(3) - (8)].string));
		
			Signature* signature = NEW(Signature, (new Method_mod(), (yyvsp[(2) - (8)].integer)->value(), name, (yyvsp[(6) - (8)].list_ast_formal_parameter)));
			(yyvsp[(1) - (8)].ast_method)->signature = signature;
			(yyvsp[(1) - (8)].ast_method)->statements = (yyvsp[(8) - (8)].list_ast_statement);

			(yyval.ast_method) = (yyvsp[(1) - (8)].ast_method);
		;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1004 "src/generated_src/php_parser.ypp"
    {context->current_class = dynamic_cast<String*>((yyvsp[(2) - (2)].string));;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1004 "src/generated_src/php_parser.ypp"
    {context->current_class = new String ();;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1005 "src/generated_src/php_parser.ypp"
    {
			CLASS_NAME* name = NEW (CLASS_NAME, (yyvsp[(2) - (9)].string));

			(yyvsp[(1) - (9)].ast_class_def)->class_name = name;
			(yyvsp[(1) - (9)].ast_class_def)->extends = (yyvsp[(4) - (9)].token_class_name);
			(yyvsp[(1) - (9)].ast_class_def)->implements = (yyvsp[(5) - (9)].list_token_interface_name);
			(yyvsp[(1) - (9)].ast_class_def)->members = (yyvsp[(7) - (9)].list_ast_member);

			(yyval.ast_statement) = (yyvsp[(1) - (9)].ast_class_def);
		;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1016 "src/generated_src/php_parser.ypp"
    {
			INTERFACE_NAME* name = new INTERFACE_NAME((yyvsp[(2) - (6)].string));

			(yyvsp[(1) - (6)].ast_interface_def)->interface_name = name;
			(yyvsp[(1) - (6)].ast_interface_def)->extends = (yyvsp[(3) - (6)].list_token_interface_name);
			(yyvsp[(1) - (6)].ast_interface_def)->members = (yyvsp[(5) - (6)].list_ast_member);
			
			(yyval.ast_statement) = (yyvsp[(1) - (6)].ast_interface_def);
		;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1039 "src/generated_src/php_parser.ypp"
    {
			Class_mod* mod = NEW(Class_mod, (false, false));
			(yyval.ast_class_def) = NEW(Class_def, (mod));
		;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1044 "src/generated_src/php_parser.ypp"
    {
			Class_mod* mod = NEW(Class_mod, (true, false));
			(yyval.ast_class_def) = NEW(Class_def, (mod));
		;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1049 "src/generated_src/php_parser.ypp"
    {
			Class_mod* mod = NEW(Class_mod, (false, true));
			(yyval.ast_class_def) = NEW(Class_def, (mod));
		;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1057 "src/generated_src/php_parser.ypp"
    {
			(yyval.token_class_name) = NULL;
		;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 1061 "src/generated_src/php_parser.ypp"
    {
			(yyval.token_class_name) = (yyvsp[(2) - (2)].token_class_name);
		;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 1068 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_interface_def) = NEW(Interface_def, (NULL, NULL, NULL));
		;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 1075 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_token_interface_name) = new List<INTERFACE_NAME*>;
		;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1079 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_token_interface_name) = (yyvsp[(2) - (2)].list_token_interface_name);
		;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1089 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_token_interface_name) = new List<INTERFACE_NAME*>;
		;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1093 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_token_interface_name) = (yyvsp[(2) - (2)].list_token_interface_name);
		;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1100 "src/generated_src/php_parser.ypp"
    {
			INTERFACE_NAME* ifn = NEW(INTERFACE_NAME, ((yyvsp[(1) - (1)].token_class_name)->value));
		
			List<INTERFACE_NAME*>* names;
			names = new List<INTERFACE_NAME*>;
			names->push_back(ifn);
			
			(yyval.list_token_interface_name) = names;
		;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1110 "src/generated_src/php_parser.ypp"
    {
			INTERFACE_NAME* ifn = NEW(INTERFACE_NAME, ((yyvsp[(3) - (3)].token_class_name)->value));
			(yyvsp[(1) - (3)].list_token_interface_name)->push_back(ifn);
			
			(yyval.list_token_interface_name) = (yyvsp[(1) - (3)].list_token_interface_name);
		;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 1120 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = NULL;
		;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 1124 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(2) - (2)].ast_variable);
		;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 1131 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = expect_variable((yyvsp[(1) - (1)].ast_expr));
		;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 1135 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (2)].ast_expr)->attrs->set_true("phc.parser.is_ref");
			(yyval.ast_variable) = expect_variable((yyvsp[(2) - (2)].ast_expr));
		;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 1143 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 1147 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (4)].list_ast_statement);
		;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1154 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1158 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (4)].list_ast_statement);
		;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1165 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1169 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (4)].list_ast_statement);
		;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 1176 "src/generated_src/php_parser.ypp"
    {
			DIRECTIVE_NAME* name = NEW (DIRECTIVE_NAME, ((yyvsp[(1) - (3)].string)));

			List<Directive*>* dirs = new List<Directive*>;
			Directive* dir = NEW(Directive, (name, (yyvsp[(3) - (3)].ast_expr)));
			
			dirs->push_back(dir);
			(yyval.list_ast_directive) = dirs;
		;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 1186 "src/generated_src/php_parser.ypp"
    {
			DIRECTIVE_NAME* name = NEW (DIRECTIVE_NAME, ((yyvsp[(3) - (5)].string)));
			
			Directive* dir = NEW(Directive, (name, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].list_ast_directive)->push_back(dir);
			(yyval.list_ast_directive) = (yyvsp[(1) - (5)].list_ast_directive);
		;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1197 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = (yyvsp[(2) - (3)].list_ast_switch_case);
		;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1201 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = (yyvsp[(3) - (4)].list_ast_switch_case);
		;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1205 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = (yyvsp[(2) - (4)].list_ast_switch_case);
		;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1209 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = (yyvsp[(3) - (5)].list_ast_switch_case);
		;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1216 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = new List<Switch_case*>;
		;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1220 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (5)].ast_switch_case)->statements = (yyvsp[(5) - (5)].list_ast_statement);
			(yyvsp[(2) - (5)].ast_switch_case)->expr = (yyvsp[(3) - (5)].ast_expr);
			
			(yyvsp[(1) - (5)].list_ast_switch_case)->push_back((yyvsp[(2) - (5)].ast_switch_case));
			
			(yyval.list_ast_switch_case) = (yyvsp[(1) - (5)].list_ast_switch_case);
		;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1229 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (4)].ast_switch_case)->statements = (yyvsp[(4) - (4)].list_ast_statement);
			(yyvsp[(2) - (4)].ast_switch_case)->expr = NULL;
			
			(yyvsp[(1) - (4)].list_ast_switch_case)->push_back((yyvsp[(2) - (4)].ast_switch_case));
			
			(yyval.list_ast_switch_case) = (yyvsp[(1) - (4)].list_ast_switch_case);
		;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1249 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1253 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (4)].list_ast_statement);
		;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1260 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_if) = NULL;
		;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1264 "src/generated_src/php_parser.ypp"
    {
			List<Statement*>* empty = new List<Statement*>;
			
			(yyvsp[(2) - (6)].ast_if)->expr = (yyvsp[(4) - (6)].ast_expr);
			(yyvsp[(2) - (6)].ast_if)->iftrue = (yyvsp[(6) - (6)].list_ast_statement);
			(yyvsp[(2) - (6)].ast_if)->iffalse = empty;
			(yyvsp[(2) - (6)].ast_if)->attrs->set_true("phc.unparser.is_elseif");

			if((yyvsp[(1) - (6)].ast_if))
			{
				List<Statement*>* iffalse = new List<Statement*>;
				iffalse->push_back((yyvsp[(2) - (6)].ast_if));
				
				/*
				 * Nest the $1.
				 * This is similar to the code in unticked_statement for K_IF.
				 */
				If* p = (yyvsp[(1) - (6)].ast_if);
				while(!p->iffalse->empty())
					p = dynamic_cast<If*>(p->iffalse->front());
				p->iffalse = iffalse;
						
				(yyval.ast_if) = (yyvsp[(1) - (6)].ast_if);
			}
			else
			{
				(yyval.ast_if) = (yyvsp[(2) - (6)].ast_if);
			}
		;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1300 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_if) = NULL;
		;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1304 "src/generated_src/php_parser.ypp"
    {
			List<Statement*>* empty = new List<Statement*>;
			
			(yyvsp[(2) - (7)].ast_if)->expr = (yyvsp[(4) - (7)].ast_expr);
			(yyvsp[(2) - (7)].ast_if)->iftrue = (yyvsp[(7) - (7)].list_ast_statement);
			(yyvsp[(2) - (7)].ast_if)->iffalse = empty;
			(yyvsp[(2) - (7)].ast_if)->attrs->set_true("phc.unparser.is_elseif");

			if((yyvsp[(1) - (7)].ast_if))
			{
				List<Statement*>* iffalse = new List<Statement*>;
				iffalse->push_back((yyvsp[(2) - (7)].ast_if));
				
				If* p = (yyvsp[(1) - (7)].ast_if);
				while(!p->iffalse->empty())
					p = dynamic_cast<If*>(p->iffalse->front());
				p->iffalse = iffalse;
						
				(yyval.ast_if) = (yyvsp[(1) - (7)].ast_if);
			}
			else
			{
				(yyval.ast_if) = (yyvsp[(2) - (7)].ast_if);
			}
		;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1333 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<Statement*>;
		;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1337 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (2)].list_ast_statement);
		;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1347 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<Statement*>;
		;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1351 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(3) - (3)].list_ast_statement);
		;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1358 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (1)].list_ast_formal_parameter);
		;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1362 "src/generated_src/php_parser.ypp"
    {
			List<Formal_parameter*>* params = new List<Formal_parameter*>;
			(yyval.list_ast_formal_parameter) = params;
		;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1373 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(2) - (2)].string));
			
			List<Formal_parameter*>* params;
			
			params = new List<Formal_parameter*>;
			params->push_back(NEW(Formal_parameter, ((yyvsp[(1) - (2)].ast_type), name)));
			
			(yyval.list_ast_formal_parameter) = params;
		;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1384 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(3) - (3)].string));
			
			List<Formal_parameter*>* params;
			
			params = new List<Formal_parameter*>;
			params->push_back(NEW(Formal_parameter, ((yyvsp[(1) - (3)].ast_type), true, name)));
			
			(yyval.list_ast_formal_parameter) = params;
		;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1395 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(3) - (5)].string));
			
			List<Formal_parameter*>* params;
			
			params = new List<Formal_parameter*>;
			params->push_back(NEW(Formal_parameter, ((yyvsp[(1) - (5)].ast_type), true, NEW(Name_with_default, (name, (yyvsp[(5) - (5)].ast_expr))))));
			
			(yyval.list_ast_formal_parameter) = params;
		;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1406 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(2) - (4)].string));
			
			List<Formal_parameter*>* params;
			
			params = new List<Formal_parameter*>;
			params->push_back(NEW(Formal_parameter, ((yyvsp[(1) - (4)].ast_type), false, NEW(Name_with_default, (name, (yyvsp[(4) - (4)].ast_expr))))));
			
			(yyval.list_ast_formal_parameter) = params;
		;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1417 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(4) - (4)].string));
			
			(yyvsp[(1) - (4)].list_ast_formal_parameter)->push_back(NEW(Formal_parameter, ((yyvsp[(3) - (4)].ast_type), name)));
			
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (4)].list_ast_formal_parameter);
		;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1425 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(5) - (5)].string));
			
			(yyvsp[(1) - (5)].list_ast_formal_parameter)->push_back(NEW(Formal_parameter, ((yyvsp[(3) - (5)].ast_type), true, name)));
			
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (5)].list_ast_formal_parameter);
		;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1433 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(5) - (7)].string));
			
			(yyvsp[(1) - (7)].list_ast_formal_parameter)->push_back(NEW(Formal_parameter, ((yyvsp[(3) - (7)].ast_type), true, NEW(Name_with_default, (name, (yyvsp[(7) - (7)].ast_expr))))));
			
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (7)].list_ast_formal_parameter);
		;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1441 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(4) - (6)].string));
			
			(yyvsp[(1) - (6)].list_ast_formal_parameter)->push_back(NEW(Formal_parameter, ((yyvsp[(3) - (6)].ast_type), false, NEW(Name_with_default, (name, (yyvsp[(6) - (6)].ast_expr))))));
			
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (6)].list_ast_formal_parameter);
		;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1452 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_type) = NEW(Type, (NULL));
		;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1456 "src/generated_src/php_parser.ypp"
    {
			CLASS_NAME* class_name = NEW (CLASS_NAME, (yyvsp[(1) - (1)].string));
			(yyval.ast_type) = NEW(Type, (class_name));
		;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1461 "src/generated_src/php_parser.ypp"
    {
			CLASS_NAME* class_name = new CLASS_NAME(new String ("array"));
			(yyval.ast_type) = NEW(Type, (class_name));
		;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1469 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (1)].list_ast_actual_parameter);
		;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1473 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = new List<Actual_parameter*>;
		;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1480 "src/generated_src/php_parser.ypp"
    {
			List<Actual_parameter*>* list = new List<Actual_parameter*>;
			list->push_back(NEW(Actual_parameter, (false, (yyvsp[(1) - (1)].ast_expr))));
			(yyval.list_ast_actual_parameter) = list;
		;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1486 "src/generated_src/php_parser.ypp"
    {
			List<Actual_parameter*>* list = new List<Actual_parameter*>;
			list->push_back(NEW(Actual_parameter, (false, (yyvsp[(1) - (1)].ast_expr))));
			(yyval.list_ast_actual_parameter) = list;
		;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1492 "src/generated_src/php_parser.ypp"
    {
			List<Actual_parameter*>* list = new List<Actual_parameter*>;
			list->push_back(NEW(Actual_parameter, (true, (yyvsp[(2) - (2)].ast_expr))));
			(yyval.list_ast_actual_parameter) = list;
		;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1498 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back(NEW(Actual_parameter, (false, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1503 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back(NEW(Actual_parameter, (false, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1508 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (4)].list_ast_actual_parameter)->push_back(NEW(Actual_parameter, (true, (yyvsp[(4) - (4)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (4)].list_ast_actual_parameter);
		;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1516 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_variable_name)->push_back((yyvsp[(3) - (3)].ast_variable_name));
			(yyval.list_ast_variable_name) = (yyvsp[(1) - (3)].list_ast_variable_name);
		;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1521 "src/generated_src/php_parser.ypp"
    {
			List<Variable_name*>* list = new List<Variable_name*>;
			list->push_back((yyvsp[(1) - (1)].ast_variable_name));
			
			(yyval.list_ast_variable_name) = list;
		;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1531 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable_name) = NEW(VARIABLE_NAME, ((yyvsp[(1) - (1)].string)));
		;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1535 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable_name) = NEW(Reflection, ((yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1539 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(3) - (4)].ast_expr)->attrs->set_true("phc.unparser.needs_user_curlies");
			(yyval.ast_variable_name) = NEW(Reflection, ((yyvsp[(3) - (4)].ast_expr)));
		;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1547 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(3) - (3)].string));
			(yyvsp[(1) - (3)].list_ast_name_with_default)->push_back(NEW(Name_with_default, (name, NULL)));
			(yyval.list_ast_name_with_default) = (yyvsp[(1) - (3)].list_ast_name_with_default);
		;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1553 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(3) - (5)].string));
			(yyvsp[(1) - (5)].list_ast_name_with_default)->push_back(NEW(Name_with_default, (name, (yyvsp[(5) - (5)].ast_expr))));
			(yyval.list_ast_name_with_default) = (yyvsp[(1) - (5)].list_ast_name_with_default);
		;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1559 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(1) - (1)].string));
			List<Name_with_default*>* list = new List<Name_with_default*>;
			list->push_back(NEW(Name_with_default, (name, NULL)));
			(yyval.list_ast_name_with_default) = list;
		;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1566 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(1) - (3)].string));
			List<Name_with_default*>* list = new List<Name_with_default*>;
			list->push_back(NEW(Name_with_default, (name, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_name_with_default) = list;
		;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1576 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_member)->push_back((yyvsp[(2) - (2)].ast_member));
			(yyval.list_ast_member) = (yyvsp[(1) - (2)].list_ast_member);
		;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1581 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_member) = new List<Member*>;
		;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1588 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_member) = NEW(Attribute, ((yyvsp[(1) - (3)].ast_attr_mod), (yyvsp[(2) - (3)].list_ast_name_with_default)));
		;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1592 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_member) = (yyvsp[(1) - (2)].ast_attribute);
		;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1595 "src/generated_src/php_parser.ypp"
    {context->current_method = dynamic_cast<String*>((yyvsp[(4) - (4)].string));;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1595 "src/generated_src/php_parser.ypp"
    {context->current_method = new String;;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1596 "src/generated_src/php_parser.ypp"
    {
			METHOD_NAME* name = new METHOD_NAME((yyvsp[(4) - (10)].string));
		
			Signature* signature = NEW(Signature, ((yyvsp[(1) - (10)].ast_method_mod), (yyvsp[(3) - (10)].integer)->value(), name, (yyvsp[(7) - (10)].list_ast_formal_parameter)));
			
			(yyvsp[(2) - (10)].ast_method)->signature = signature;
			(yyvsp[(2) - (10)].ast_method)->statements = (yyvsp[(9) - (10)].list_ast_statement);
			(yyval.ast_member) = (yyvsp[(2) - (10)].ast_method);
		;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1609 "src/generated_src/php_parser.ypp"
    {
			// Abstract method
			(yyval.list_ast_statement) = NULL;
		;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1614 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1621 "src/generated_src/php_parser.ypp"
    {
			if((yyvsp[(1) - (1)].ast_method_mod)->is_abstract)
			{
				phc_error("Cannot declare variables to be abstract", (yyvsp[(1) - (1)].ast_method_mod));
			}

			(yyval.ast_attr_mod) = NEW(Attr_mod, ((yyvsp[(1) - (1)].ast_method_mod)));
		;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1630 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_attr_mod) = NEW(Attr_mod, (false, false, false, false, false));
		;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1637 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = new Method_mod();
		;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1641 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = (yyvsp[(1) - (1)].ast_method_mod);
		;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1648 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = (yyvsp[(1) - (1)].ast_method_mod);
		;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1652 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = NEW(Method_mod, ((yyvsp[(1) - (2)].ast_method_mod), (yyvsp[(2) - (2)].ast_method_mod)));
		;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1659 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = Method_mod::new_PUBLIC();
		;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1663 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = Method_mod::new_PROTECTED();
		;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1667 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = Method_mod::new_PRIVATE();
		;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1671 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = Method_mod::new_STATIC();
		;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1675 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = Method_mod::new_ABSTRACT();
		;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1679 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = Method_mod::new_FINAL();
		;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1686 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(3) - (3)].string));
			(yyvsp[(1) - (3)].list_ast_name_with_default)->push_back(NEW(Name_with_default, (name, NULL)));
			(yyval.list_ast_name_with_default) = (yyvsp[(1) - (3)].list_ast_name_with_default);
		;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1692 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(3) - (5)].string));
			(yyvsp[(1) - (5)].list_ast_name_with_default)->push_back(NEW(Name_with_default, (name, (yyvsp[(5) - (5)].ast_expr))));
			(yyval.list_ast_name_with_default) = (yyvsp[(1) - (5)].list_ast_name_with_default);
		;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1698 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(1) - (1)].string));
			List<Name_with_default*>* vars = new List<Name_with_default*>;
			vars->push_back(NEW(Name_with_default, (name, NULL)));
			(yyval.list_ast_name_with_default) = vars;
		;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1705 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(1) - (3)].string));
			List<Name_with_default*>* vars = new List<Name_with_default*>;
			vars->push_back(NEW(Name_with_default, (name, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_name_with_default) = vars;
		;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1715 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(3) - (5)].string));
			Name_with_default* var = NEW(Name_with_default, (name, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].ast_attribute)->vars->push_back(var);
			(yyval.ast_attribute) = (yyvsp[(1) - (5)].ast_attribute);
		;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1722 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(2) - (4)].string));
			List<Name_with_default*>* vars = new List<Name_with_default*>;

			Attr_mod* attr_mod = Attr_mod::new_CONST();
			Name_with_default* var = NEW(Name_with_default, (name, (yyvsp[(4) - (4)].ast_expr)));
			vars->push_back(var);

			(yyval.ast_attribute) = NEW(Attribute, (attr_mod, vars));
		;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1744 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back (NEW (Actual_parameter, (false, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1749 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = new List<Actual_parameter*>;
			(yyval.list_ast_actual_parameter)->push_back(NEW(Actual_parameter, (false, (yyvsp[(1) - (1)].ast_expr))));
		;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1757 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NULL;
		;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1761 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr)
		;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1771 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1776 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1783 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(List_assignment, ((yyvsp[(3) - (6)].ast_nested_list_elements)->list_elements, (yyvsp[(6) - (6)].ast_expr)));
		;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1787 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Assignment, (expect_variable((yyvsp[(1) - (3)].ast_expr)), false, (yyvsp[(3) - (3)].ast_expr)));
		;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1791 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Assignment, (expect_variable((yyvsp[(1) - (4)].ast_expr)), true, (yyvsp[(4) - (4)].ast_expr)));
		;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1795 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(6) - (6)].ast_new)->class_name = (yyvsp[(5) - (6)].ast_class_name);
			(yyval.ast_expr) = NEW(Assignment, (expect_variable((yyvsp[(1) - (6)].ast_expr)), true, (yyvsp[(6) - (6)].ast_new)));
		;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1800 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(3) - (3)].ast_new)->class_name = (yyvsp[(2) - (3)].ast_class_name);
			(yyval.ast_expr) = (yyvsp[(3) - (3)].ast_new);
		;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1805 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Method_invocation, ("clone", (yyvsp[(2) - (2)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1810 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "+", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1815 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "-", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1820 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "*", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1825 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "/", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1830 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, ".", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1835 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "%", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1840 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "&", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1845 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "|", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1850 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "^", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1855 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "<<", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1860 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, ">>", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1865 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Post_op, (expect_variable((yyvsp[(1) - (2)].ast_expr)), "++"));
		;}
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1869 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Pre_op, (expect_variable((yyvsp[(2) - (2)].ast_expr)), "++"));
		;}
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1873 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Post_op, (expect_variable((yyvsp[(1) - (2)].ast_expr)), "--"));
		;}
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1877 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Pre_op, (expect_variable((yyvsp[(2) - (2)].ast_expr)), "--"));
		;}
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1881 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1886 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1891 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1896 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1901 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1906 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1911 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1916 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1921 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1926 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (4)].ast_expr), (yyvsp[(2) - (4)].token_op), expect_variable_or_method_invocation ((yyvsp[(3) - (4)].ast_expr))));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");

			/*
			 * Interface with the lexer: return to in-string state 
			 */

			context->return_to_complex_syntax();
		;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1937 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1942 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1947 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1952 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1957 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1962 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1967 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1972 "src/generated_src/php_parser.ypp"
    {
			// We ignore unary plus
			(yyval.ast_expr) = (yyvsp[(2) - (2)].ast_expr);
		;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1977 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Unary_op, ((yyvsp[(1) - (2)].token_op), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1981 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Unary_op, ((yyvsp[(1) - (2)].token_op), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1985 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Unary_op, ((yyvsp[(1) - (2)].token_op), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1989 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1994 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1999 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 2004 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 2009 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 2014 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 2019 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 2024 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 2029 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Instanceof, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_class_name)));
		;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 2033 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (3)].ast_expr)->attrs->set_true("phc.unparser.needs_user_brackets");
			
			(yyval.ast_expr) = (yyvsp[(2) - (3)].ast_expr);
		;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 2039 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Conditional_expr, ((yyvsp[(1) - (5)].ast_expr), (yyvsp[(3) - (5)].ast_expr), (yyvsp[(5) - (5)].ast_expr)));
		;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 2043 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_method_invocation);
		;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 2047 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("int", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 2051 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("real", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 2055 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("string", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 2059 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("array", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 2063 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("object", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 2067 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("bool", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 2071 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("unset", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 2075 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(2) - (2)].ast_method_invocation);
		;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 2079 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(2) - (2)].ast_method_invocation);
      delete (yyvsp[(2) - (2)].ast_method_invocation)->method_name;
			(yyvsp[(2) - (2)].ast_method_invocation)->method_name = new METHOD_NAME(new String("die"));
		;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 2085 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Ignore_errors, ((yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 2089 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 2093 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Array, ((yyvsp[(3) - (4)].list_ast_array_elem)));
		;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 2097 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Method_invocation, ("print", (yyvsp[(2) - (2)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 2105 "src/generated_src/php_parser.ypp"
    {
			METHOD_NAME* fn;

			if(*(yyvsp[(1) - (4)].string) == "`")
				fn = new METHOD_NAME(new String("shell_exec"));
			else
				fn = new METHOD_NAME((yyvsp[(1) - (4)].string));
		
			(yyval.ast_method_invocation) = NEW(Method_invocation, (NULL, fn, (yyvsp[(3) - (4)].list_ast_actual_parameter)));

			if(*(yyvsp[(1) - (4)].string) == "`")
				(yyval.ast_method_invocation)->attrs->set_true("phc.unparser.is_backticked");
		;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 2119 "src/generated_src/php_parser.ypp"
    {
			METHOD_NAME* fn = new METHOD_NAME((yyvsp[(3) - (6)].string));

			(yyval.ast_method_invocation) = NEW(Method_invocation, ((yyvsp[(1) - (6)].token_class_name), fn, (yyvsp[(5) - (6)].list_ast_actual_parameter)));
		;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 2125 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ((yyvsp[(1) - (6)].token_class_name), NEW(Reflection, ((yyvsp[(3) - (6)].ast_variable))), (yyvsp[(5) - (6)].list_ast_actual_parameter)));
		;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 2129 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, (NULL, NEW(Reflection, ((yyvsp[(1) - (4)].ast_variable))), (yyvsp[(3) - (4)].list_ast_actual_parameter)));
		;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 2136 "src/generated_src/php_parser.ypp"
    {
			CLASS_NAME* name = NEW (CLASS_NAME, (yyvsp[(1) - (1)].string));
			(yyval.token_class_name) = name;
		;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 2144 "src/generated_src/php_parser.ypp"
    {
			CLASS_NAME* name = NEW (CLASS_NAME, (yyvsp[(1) - (1)].string));

			(yyval.ast_class_name) = name;
		;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 2150 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_class_name) = NEW(Reflection, ((yyvsp[(1) - (1)].ast_variable)));
		;}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 2161 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(3) - (4)].ast_variable)->target = (yyvsp[(1) - (4)].ast_variable);

			List<Variable*>::const_iterator i;
			for(i = (yyvsp[(4) - (4)].list_ast_variable)->begin(); i != (yyvsp[(4) - (4)].list_ast_variable)->end(); i++)
			{
				(*i)->target = (yyvsp[(3) - (4)].ast_variable);
				(yyvsp[(3) - (4)].ast_variable) = *i;
			}
			
			(yyval.ast_variable) = (yyvsp[(3) - (4)].ast_variable);
		;}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 2174 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 2181 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_variable)->push_back((yyvsp[(2) - (2)].ast_variable));
			(yyval.list_ast_variable) = (yyvsp[(1) - (2)].list_ast_variable);
		;}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 2186 "src/generated_src/php_parser.ypp"
    {
			List<Variable*>* vars = new List<Variable*>;
			(yyval.list_ast_variable) = vars;
		;}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 2194 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(2) - (2)].ast_variable);
		;}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 2204 "src/generated_src/php_parser.ypp"
    {
			Expr* expr = NEW(INT, (0L));
			Actual_parameter* arg = NEW(Actual_parameter, (false, expr));
			arg->attrs->set_true("phc.unparser.is_default");
			(yyval.ast_method_invocation) = NEW(Method_invocation,
				( NULL
				, new METHOD_NAME(new String("exit"))
				, new List<Actual_parameter*>(arg)
				));
			(yyval.ast_method_invocation)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 2216 "src/generated_src/php_parser.ypp"
    {
			Expr* expr = NEW(INT, (0L));
			Actual_parameter* arg = NEW(Actual_parameter, (false, expr));
			arg->attrs->set_true("phc.unparser.is_default");
			(yyval.ast_method_invocation) = NEW(Method_invocation,
				( NULL
				, new METHOD_NAME(new String("exit"))
				, new List<Actual_parameter*>(arg)
				));
		;}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 2227 "src/generated_src/php_parser.ypp"
    {
			Actual_parameter* arg = NEW(Actual_parameter, (false, (yyvsp[(2) - (3)].ast_expr)));
			(yyval.ast_method_invocation) = NEW(Method_invocation,
				( NULL
				, new METHOD_NAME(new String("exit"))
				, new List<Actual_parameter*>(arg)
				));
		;}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 2243 "src/generated_src/php_parser.ypp"
    {
			List<Actual_parameter*>* args = new List<Actual_parameter*>;
			
			(yyval.ast_new) = NEW(New, (NULL, args));
			(yyval.ast_new)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 2250 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_new) = NEW(New, (NULL, (yyvsp[(2) - (3)].list_ast_actual_parameter)));
		;}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 2257 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_int);
		;}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 2261 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_real);
		;}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 2265 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_string);
		;}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 2269 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_bool);
		;}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 2273 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_bool);
		;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 2277 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_null);
		;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 2281 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_int);
		;}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 2285 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_string);
		;}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 2289 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_string);
		;}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 2293 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_string);
		;}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 2297 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_string);
		;}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 2304 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 2308 "src/generated_src/php_parser.ypp"
    {
			CONSTANT_NAME* name = new CONSTANT_NAME((yyvsp[(1) - (1)].string));
			(yyval.ast_expr) = NEW(Constant, (NULL, name));
		;}
    break;

  case 279:

/* Line 1455 of yacc.c  */
#line 2313 "src/generated_src/php_parser.ypp"
    {
			// We simply ignore the +
			(yyval.ast_expr) = (yyvsp[(2) - (2)].ast_expr);
		;}
    break;

  case 280:

/* Line 1455 of yacc.c  */
#line 2318 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Unary_op, ((yyvsp[(2) - (2)].ast_expr), "-"));
		;}
    break;

  case 281:

/* Line 1455 of yacc.c  */
#line 2322 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Array, ((yyvsp[(3) - (4)].list_ast_array_elem)));
		;}
    break;

  case 282:

/* Line 1455 of yacc.c  */
#line 2326 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_constant);
		;}
    break;

  case 283:

/* Line 1455 of yacc.c  */
#line 2333 "src/generated_src/php_parser.ypp"
    {
			CLASS_NAME* class_name = NEW (CLASS_NAME, (yyvsp[(1) - (3)].string));
			CONSTANT_NAME* constant = new CONSTANT_NAME((yyvsp[(3) - (3)].string));
			
			(yyval.ast_constant) = NEW(Constant, (class_name, constant));
		;}
    break;

  case 284:

/* Line 1455 of yacc.c  */
#line 2343 "src/generated_src/php_parser.ypp"
    {
			CONSTANT_NAME* name = new CONSTANT_NAME((yyvsp[(1) - (1)].string));

			(yyval.ast_expr) = NEW(Constant, (NULL, name));
		;}
    break;

  case 285:

/* Line 1455 of yacc.c  */
#line 2349 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_constant);
		;}
    break;

  case 286:

/* Line 1455 of yacc.c  */
#line 2353 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 287:

/* Line 1455 of yacc.c  */
#line 2360 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_array_elem) = new List<Array_elem*>;
		;}
    break;

  case 288:

/* Line 1455 of yacc.c  */
#line 2364 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (2)].list_ast_array_elem);
		;}
    break;

  case 291:

/* Line 1455 of yacc.c  */
#line 2379 "src/generated_src/php_parser.ypp"
    {
			Array_elem* elem = NEW(Array_elem, ((yyvsp[(3) - (5)].ast_expr), false, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].list_ast_array_elem)->push_back(elem);

			(yyval.list_ast_array_elem) = (yyvsp[(1) - (5)].list_ast_array_elem);
		;}
    break;

  case 292:

/* Line 1455 of yacc.c  */
#line 2386 "src/generated_src/php_parser.ypp"
    {
			Array_elem* elem = NEW(Array_elem, (NULL, false, (yyvsp[(3) - (3)].ast_expr)));
			(yyvsp[(1) - (3)].list_ast_array_elem)->push_back(elem);
			
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (3)].list_ast_array_elem);
		;}
    break;

  case 293:

/* Line 1455 of yacc.c  */
#line 2393 "src/generated_src/php_parser.ypp"
    {
			List<Array_elem*>* list = new List<Array_elem*>;
			Array_elem* elem = NEW(Array_elem, ((yyvsp[(1) - (3)].ast_expr), false, (yyvsp[(3) - (3)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 294:

/* Line 1455 of yacc.c  */
#line 2401 "src/generated_src/php_parser.ypp"
    {
			List<Array_elem*>* list = new List<Array_elem*>;
			Array_elem* elem = NEW(Array_elem, (NULL, false, (yyvsp[(1) - (1)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 295:

/* Line 1455 of yacc.c  */
#line 2412 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 296:

/* Line 1455 of yacc.c  */
#line 2416 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 297:

/* Line 1455 of yacc.c  */
#line 2423 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 298:

/* Line 1455 of yacc.c  */
#line 2430 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 299:

/* Line 1455 of yacc.c  */
#line 2437 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 300:

/* Line 1455 of yacc.c  */
#line 2461 "src/generated_src/php_parser.ypp"
    {
			List<Expr*>::iterator i;
			for(i = (yyvsp[(2) - (2)].list_ast_expr)->begin(); i != (yyvsp[(2) - (2)].list_ast_expr)->end(); i++)
			{
				Variable* var = dynamic_cast<Variable*>(*i);
				Method_invocation* fn = dynamic_cast<Method_invocation*>(*i);

				if(var)
				{
					var->target = (yyvsp[(1) - (2)].ast_expr);
					
					List<Actual_parameter*>* function_params = dynamic_cast<List<Actual_parameter*>*>(var->attrs->get("phc.parser.function_params"));
	
					if(function_params)
					{
						(yyvsp[(1) - (2)].ast_expr) = NEW(Method_invocation, (NULL, NEW(Reflection,(var)), function_params));
					}
					else
					{
						(yyvsp[(1) - (2)].ast_expr) = var;
					}
				}
				else
				{
					fn->target = (yyvsp[(1) - (2)].ast_expr);
					(yyvsp[(1) - (2)].ast_expr) = fn;
				}
			}

			(yyval.ast_expr) = (yyvsp[(1) - (2)].ast_expr);
		;}
    break;

  case 301:

/* Line 1455 of yacc.c  */
#line 2493 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 302:

/* Line 1455 of yacc.c  */
#line 2504 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_expr)->push_back((yyvsp[(2) - (2)].ast_expr));
			
			(yyval.list_ast_expr) = (yyvsp[(1) - (2)].list_ast_expr);
		;}
    break;

  case 303:

/* Line 1455 of yacc.c  */
#line 2510 "src/generated_src/php_parser.ypp"
    {
			List<Expr*>* props = new List<Expr*>;
			props->push_back((yyvsp[(1) - (1)].ast_expr));
			
			(yyval.list_ast_expr) = props;
		;}
    break;

  case 304:

/* Line 1455 of yacc.c  */
#line 2539 "src/generated_src/php_parser.ypp"
    {
			if((yyvsp[(3) - (3)].list_ast_actual_parameter))
			{
				if((yyvsp[(2) - (3)].ast_variable)->array_indices->empty())
				{
					VARIABLE_NAME* vn = dynamic_cast<VARIABLE_NAME*>((yyvsp[(2) - (3)].ast_variable)->variable_name);
				
					if(vn)
					{
						METHOD_NAME* fn;
						
						fn = NEW(METHOD_NAME, (vn->value));
						(yyval.ast_expr) = NEW(Method_invocation, (NULL, fn, (yyvsp[(3) - (3)].list_ast_actual_parameter)));
					}
					else
					{
						Reflection* fn;

						fn = dynamic_cast<Reflection*>((yyvsp[(2) - (3)].ast_variable)->variable_name);
						assert(fn);
						(yyval.ast_expr) = NEW(Method_invocation, (NULL, fn, (yyvsp[(3) - (3)].list_ast_actual_parameter)));
					}
				}
				else
				{
					(yyvsp[(2) - (3)].ast_variable)->attrs->set("phc.parser.function_params", (yyvsp[(3) - (3)].list_ast_actual_parameter));
					(yyval.ast_expr) = (yyvsp[(2) - (3)].ast_variable);
				}
			}
			else
			{
				(yyval.ast_expr) = (yyvsp[(2) - (3)].ast_variable);
			}
		;}
    break;

  case 305:

/* Line 1455 of yacc.c  */
#line 2577 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = (yyvsp[(2) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 306:

/* Line 1455 of yacc.c  */
#line 2581 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = NULL;
		;}
    break;

  case 307:

/* Line 1455 of yacc.c  */
#line 2588 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 308:

/* Line 1455 of yacc.c  */
#line 2592 "src/generated_src/php_parser.ypp"
    {
			for(long i = 0; i < (yyvsp[(1) - (2)].integer)->value(); i++)
			{
				(yyvsp[(2) - (2)].ast_variable) = NEW(Variable, (NEW(Reflection, ((yyvsp[(2) - (2)].ast_variable)))));
			}
			
			(yyval.ast_variable) = (yyvsp[(2) - (2)].ast_variable);
		;}
    break;

  case 309:

/* Line 1455 of yacc.c  */
#line 2604 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(3) - (3)].ast_variable)->target = (yyvsp[(1) - (3)].token_class_name);
			(yyval.ast_variable) = (yyvsp[(3) - (3)].ast_variable);
		;}
    break;

  case 310:

/* Line 1455 of yacc.c  */
#line 2612 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 311:

/* Line 1455 of yacc.c  */
#line 2616 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_method_invocation);
		;}
    break;

  case 312:

/* Line 1455 of yacc.c  */
#line 2623 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 313:

/* Line 1455 of yacc.c  */
#line 2627 "src/generated_src/php_parser.ypp"
    {
			for(long i = 0; i < (yyvsp[(1) - (2)].integer)->value(); i++)
			{
				(yyvsp[(2) - (2)].ast_variable) = NEW(Variable, (NEW(Reflection, ((yyvsp[(2) - (2)].ast_variable)))));
			}

			(yyval.ast_variable) = (yyvsp[(2) - (2)].ast_variable);
		;}
    break;

  case 314:

/* Line 1455 of yacc.c  */
#line 2636 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 315:

/* Line 1455 of yacc.c  */
#line 2643 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (4)].ast_variable)->array_indices->push_back((yyvsp[(3) - (4)].ast_expr));
			(yyval.ast_variable) = (yyvsp[(1) - (4)].ast_variable);
		;}
    break;

  case 316:

/* Line 1455 of yacc.c  */
#line 2648 "src/generated_src/php_parser.ypp"
    {
			if((yyvsp[(3) - (4)].ast_expr) != NULL)
				(yyvsp[(3) - (4)].ast_expr)->attrs->set_true("phc.unparser.index_curlies");

			(yyvsp[(1) - (4)].ast_variable)->array_indices->push_back((yyvsp[(3) - (4)].ast_expr));
			(yyval.ast_variable) = (yyvsp[(1) - (4)].ast_variable);
		;}
    break;

  case 317:

/* Line 1455 of yacc.c  */
#line 2656 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = NEW(Variable, ((yyvsp[(1) - (1)].ast_variable_name)));
		;}
    break;

  case 318:

/* Line 1455 of yacc.c  */
#line 2663 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* var = new VARIABLE_NAME((yyvsp[(1) - (1)].string));
			(yyval.ast_variable_name) = var;
		;}
    break;

  case 319:

/* Line 1455 of yacc.c  */
#line 2668 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(3) - (4)].ast_expr)->attrs->set_true("phc.unparser.needs_user_curlies");
			(yyval.ast_variable_name) = NEW(Reflection, ((yyvsp[(3) - (4)].ast_expr)));
		;}
    break;

  case 320:

/* Line 1455 of yacc.c  */
#line 2676 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NULL;
		;}
    break;

  case 321:

/* Line 1455 of yacc.c  */
#line 2680 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 322:

/* Line 1455 of yacc.c  */
#line 2687 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 323:

/* Line 1455 of yacc.c  */
#line 2691 "src/generated_src/php_parser.ypp"
    {
			// This is a "normal" variable (which includes a $), i.e. $x->$y
			// So, we need to add a level of indirection
			(yyval.ast_variable) = NEW(Variable, (NEW(Reflection, ((yyvsp[(1) - (1)].ast_variable)))));
		;}
    break;

  case 324:

/* Line 1455 of yacc.c  */
#line 2703 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (4)].ast_variable)->array_indices->push_back((yyvsp[(3) - (4)].ast_expr));
			(yyval.ast_variable) = (yyvsp[(1) - (4)].ast_variable);
		;}
    break;

  case 325:

/* Line 1455 of yacc.c  */
#line 2708 "src/generated_src/php_parser.ypp"
    {
			if((yyvsp[(3) - (4)].ast_expr) != NULL)
				(yyvsp[(3) - (4)].ast_expr)->attrs->set_true("phc.unparser.index_curlies");

			(yyvsp[(1) - (4)].ast_variable)->array_indices->push_back((yyvsp[(3) - (4)].ast_expr));
			(yyval.ast_variable) = (yyvsp[(1) - (4)].ast_variable);
		;}
    break;

  case 326:

/* Line 1455 of yacc.c  */
#line 2716 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = NEW(Variable, ((yyvsp[(1) - (1)].ast_variable_name)));
		;}
    break;

  case 327:

/* Line 1455 of yacc.c  */
#line 2726 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* var = new VARIABLE_NAME((yyvsp[(1) - (1)].string));
			(yyval.ast_variable_name) = var;
		;}
    break;

  case 328:

/* Line 1455 of yacc.c  */
#line 2731 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (3)].ast_expr)->attrs->set_true("phc.unparser.needs_user_curlies");
			(yyval.ast_variable_name) = NEW(Reflection, ((yyvsp[(2) - (3)].ast_expr)));
		;}
    break;

  case 329:

/* Line 1455 of yacc.c  */
#line 2742 "src/generated_src/php_parser.ypp"
    {
			(yyval.integer) = new Integer(1);
		;}
    break;

  case 330:

/* Line 1455 of yacc.c  */
#line 2746 "src/generated_src/php_parser.ypp"
    {
			(*(yyvsp[(1) - (2)].integer))++;
			(yyval.integer) = (yyvsp[(1) - (2)].integer);
		;}
    break;

  case 331:

/* Line 1455 of yacc.c  */
#line 2754 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].ast_nested_list_elements)->list_elements->push_back((yyvsp[(3) - (3)].ast_list_element));
			
			(yyval.ast_nested_list_elements) = (yyvsp[(1) - (3)].ast_nested_list_elements);
		;}
    break;

  case 332:

/* Line 1455 of yacc.c  */
#line 2760 "src/generated_src/php_parser.ypp"
    {
			List<List_element*>* elements = new List<List_element*>;
			elements->push_back((yyvsp[(1) - (1)].ast_list_element));
			
			(yyval.ast_nested_list_elements) = NEW(Nested_list_elements, (elements));
		;}
    break;

  case 333:

/* Line 1455 of yacc.c  */
#line 2773 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_list_element) = expect_variable((yyvsp[(1) - (1)].ast_expr));
		;}
    break;

  case 334:

/* Line 1455 of yacc.c  */
#line 2777 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_list_element) = (yyvsp[(3) - (4)].ast_nested_list_elements);
		;}
    break;

  case 335:

/* Line 1455 of yacc.c  */
#line 2781 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_list_element) = NULL;
		;}
    break;

  case 336:

/* Line 1455 of yacc.c  */
#line 2788 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_array_elem) = new List<Array_elem*>;
		;}
    break;

  case 337:

/* Line 1455 of yacc.c  */
#line 2792 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (2)].list_ast_array_elem);
		;}
    break;

  case 338:

/* Line 1455 of yacc.c  */
#line 2802 "src/generated_src/php_parser.ypp"
    {
			Array_elem* elem = NEW(Array_elem, ((yyvsp[(3) - (5)].ast_expr), false, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].list_ast_array_elem)->push_back(elem);

			(yyval.list_ast_array_elem) = (yyvsp[(1) - (5)].list_ast_array_elem);
		;}
    break;

  case 339:

/* Line 1455 of yacc.c  */
#line 2809 "src/generated_src/php_parser.ypp"
    {
			Array_elem* elem = NEW(Array_elem, (NULL, false, (yyvsp[(3) - (3)].ast_expr)));
			(yyvsp[(1) - (3)].list_ast_array_elem)->push_back(elem);
			
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (3)].list_ast_array_elem);
		;}
    break;

  case 340:

/* Line 1455 of yacc.c  */
#line 2816 "src/generated_src/php_parser.ypp"
    {
			List<Array_elem*>* list = new List<Array_elem*>;
			Array_elem* elem = NEW(Array_elem, ((yyvsp[(1) - (3)].ast_expr), false, (yyvsp[(3) - (3)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 341:

/* Line 1455 of yacc.c  */
#line 2824 "src/generated_src/php_parser.ypp"
    {
			List<Array_elem*>* list = new List<Array_elem*>;
			Array_elem* elem = NEW(Array_elem, (NULL, false, (yyvsp[(1) - (1)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 342:

/* Line 1455 of yacc.c  */
#line 2832 "src/generated_src/php_parser.ypp"
    {
			Array_elem* elem = 
				NEW(Array_elem, ((yyvsp[(3) - (6)].ast_expr), true, (yyvsp[(6) - (6)].ast_expr)));
			(yyvsp[(1) - (6)].list_ast_array_elem)->push_back(elem);

			(yyval.list_ast_array_elem) = (yyvsp[(1) - (6)].list_ast_array_elem);
		;}
    break;

  case 343:

/* Line 1455 of yacc.c  */
#line 2840 "src/generated_src/php_parser.ypp"
    {
			Array_elem* elem = 
				NEW(Array_elem, (NULL, true, (yyvsp[(4) - (4)].ast_expr)));
			(yyvsp[(1) - (4)].list_ast_array_elem)->push_back(elem);
			
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (4)].list_ast_array_elem);
		;}
    break;

  case 344:

/* Line 1455 of yacc.c  */
#line 2848 "src/generated_src/php_parser.ypp"
    {
			List<Array_elem*>* list = new List<Array_elem*>;
			Array_elem* elem = 
				NEW(Array_elem, ((yyvsp[(1) - (4)].ast_expr), true, (yyvsp[(4) - (4)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 345:

/* Line 1455 of yacc.c  */
#line 2857 "src/generated_src/php_parser.ypp"
    {
			List<Array_elem*>* list = new List<Array_elem*>;
			Array_elem* elem = 
				NEW(Array_elem, (NULL, true, (yyvsp[(2) - (2)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 346:

/* Line 1455 of yacc.c  */
#line 2869 "src/generated_src/php_parser.ypp"
    {
			METHOD_NAME* fn = NEW(METHOD_NAME, (new String("isset")));
			(yyval.ast_method_invocation) = NEW(Method_invocation, (NULL, fn, (yyvsp[(3) - (4)].list_ast_actual_parameter)));
		;}
    break;

  case 347:

/* Line 1455 of yacc.c  */
#line 2874 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ("empty", (yyvsp[(3) - (4)].ast_expr)));
		;}
    break;

  case 348:

/* Line 1455 of yacc.c  */
#line 2878 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ("include", (yyvsp[(2) - (2)].ast_expr)));
			(yyval.ast_method_invocation)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 349:

/* Line 1455 of yacc.c  */
#line 2883 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ("include_once", (yyvsp[(2) - (2)].ast_expr)));
			(yyval.ast_method_invocation)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 350:

/* Line 1455 of yacc.c  */
#line 2888 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ("eval", (yyvsp[(3) - (4)].ast_expr)));
		;}
    break;

  case 351:

/* Line 1455 of yacc.c  */
#line 2892 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ("require", (yyvsp[(2) - (2)].ast_expr)));
			(yyval.ast_method_invocation)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 352:

/* Line 1455 of yacc.c  */
#line 2897 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ("require_once", (yyvsp[(2) - (2)].ast_expr)));
			(yyval.ast_method_invocation)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 353:

/* Line 1455 of yacc.c  */
#line 2905 "src/generated_src/php_parser.ypp"
    {
			List<Actual_parameter*>* params = new List<Actual_parameter*>;
			
			params->push_back(NEW(Actual_parameter, (false, (yyvsp[(1) - (1)].ast_expr))));
			(yyval.list_ast_actual_parameter) = params;
		;}
    break;

  case 354:

/* Line 1455 of yacc.c  */
#line 2912 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back(NEW(Actual_parameter, (false, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 355:

/* Line 1455 of yacc.c  */
#line 2920 "src/generated_src/php_parser.ypp"
    {
			CONSTANT_NAME* constant = new CONSTANT_NAME((yyvsp[(3) - (3)].string));

			(yyval.ast_constant) = NEW(Constant, ((yyvsp[(1) - (3)].token_class_name), constant));
		;}
    break;

  case 356:

/* Line 1455 of yacc.c  */
#line 2933 "src/generated_src/php_parser.ypp"
    {
			// If there are any remaining comments, add them as a NOP
			if(!context->last_comments.empty())
				(yyvsp[(2) - (3)].list_ast_statement)->push_back(NEW(Nop, ()));

			if(!(yyvsp[(2) - (3)].list_ast_statement)->empty())
				(yyvsp[(2) - (3)].list_ast_statement)->front()->attrs->erase("phc.unparser.is_wrapped");

			(yyval.list_ast_statement) = (yyvsp[(2) - (3)].list_ast_statement);
		;}
    break;



/* Line 1455 of yacc.c  */
#line 7143 "src/generated/php_parser.tab.cpp"
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



