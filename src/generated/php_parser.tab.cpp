/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse PHP_parse
#define yylex   PHP_lex
#define yyerror PHP_error
#define yylval  PHP_lval
#define yychar  PHP_char
#define yydebug PHP_debug
#define yynerrs PHP_nerrs


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
     STRING = 364,
     IDENT = 365,
     VARIABLE = 366,
     INT = 367,
     REAL = 368,
     INLINE_HTML = 369,
     INVALID_TOKEN = 370
   };
#endif
/* Tokens.  */
#define K_AND 258
#define K_OR 259
#define K_XOR 260
#define K___FILE__ 261
#define K_EXCEPTION 262
#define K___LINE__ 263
#define K_ARRAY 264
#define K_AS 265
#define K_BREAK 266
#define K_CASE 267
#define K_CLASS 268
#define K_CONST 269
#define K_CONTINUE 270
#define K_DECLARE 271
#define K_DEFAULT 272
#define K_DIE 273
#define K_DO 274
#define K_ECHO 275
#define K_ELSE 276
#define K_ELSEIF 277
#define K_EMPTY 278
#define K_ENDDECLARE 279
#define K_ENDFOR 280
#define K_ENDFOREACH 281
#define K_ENDIF 282
#define K_ENDSWITCH 283
#define K_ENDWHILE 284
#define K_EVAL 285
#define K_EXIT 286
#define K_EXTENDS 287
#define K_FOR 288
#define K_FOREACH 289
#define K_FUNCTION 290
#define K_GLOBAL 291
#define K_IF 292
#define K_INCLUDE 293
#define K_INCLUDE_ONCE 294
#define K_INSTANCEOF 295
#define K_ISSET 296
#define K_LIST 297
#define K_NEW 298
#define K_PRINT 299
#define K_REQUIRE 300
#define K_REQUIRE_ONCE 301
#define K_RETURN 302
#define K_STATIC 303
#define K_SWITCH 304
#define K_UNSET 305
#define K_USE 306
#define K_VAR 307
#define K_WHILE 308
#define K___FUNCTION__ 309
#define K___CLASS__ 310
#define K___METHOD__ 311
#define K_FINAL 312
#define K_PHP_USER_FILTER 313
#define K_INTERFACE 314
#define K_IMPLEMENTS 315
#define K_PUBLIC 316
#define K_PRIVATE 317
#define K_PROTECTED 318
#define K_ABSTRACT 319
#define K_CLONE 320
#define K_TRY 321
#define K_CATCH 322
#define K_THROW 323
#define K_CFUNCTION 324
#define K_OLD_FUNCTION 325
#define K_HALT_COMPILER 326
#define C_TRUE 327
#define C_FALSE 328
#define C_NULL 329
#define O_EQEQ 330
#define O_EQEQEQ 331
#define O_NOTEQ 332
#define O_NOTEQEQ 333
#define O_LE 334
#define O_GE 335
#define O_INC 336
#define O_DEC 337
#define O_DOUBLEARROW 338
#define O_SINGLEARROW 339
#define O_SL 340
#define O_SR 341
#define O_COLONCOLON 342
#define O_LOGICOR 343
#define O_LOGICAND 344
#define O_PLUSEQ 345
#define O_MINUSEQ 346
#define O_MULEQ 347
#define O_DIVEQ 348
#define O_CONCATEQ 349
#define O_MODEQ 350
#define O_ANDEQ 351
#define O_OREQ 352
#define O_XOREQ 353
#define O_SLEQ 354
#define O_SREQ 355
#define O_MAGIC_CONCAT 356
#define CAST_INT 357
#define CAST_REAL 358
#define CAST_STRING 359
#define CAST_ARRAY 360
#define CAST_OBJECT 361
#define CAST_BOOL 362
#define CAST_UNSET 363
#define STRING 364
#define IDENT 365
#define VARIABLE 366
#define INT 367
#define REAL 368
#define INLINE_HTML 369
#define INVALID_TOKEN 370




/* Copy the first part of user declarations.  */
#line 8 "src/generated_src/php_parser.ypp"

	#include <assert.h>
	#include <typeinfo>
	#include "AST.h"
	#include "cmdline.h"
	#include "lib/Integer.h"
	#include "lib/String.h"
	#include "lib/error.h"
	#include "parsing/PHP_context.h"

	extern struct gengetopt_args_info args_info;

	/*
	 * Some semantic checks
	 */

	AST_variable* expect_variable(AST_expr* node)
	{
		AST_variable* var = dynamic_cast<AST_variable*>(node);
		
		if(var == NULL && node != NULL)
			phc_error(ERR_EXPECT_VAR, node->get_filename(), node->get_line_number()); \
			
		return var;
	}

	/*
	 * Define macro to add line numbers and comments to nodes
	 */
	#define NEW(class, args)\
		dynamic_cast<class*>(copy_state(new class args, context))
	
	AST_node* copy_state(AST_node* node, PHP_context* context)
	{
		node->attrs->set("phc.line_number", new Integer(context->source_line));
		node->attrs->set("phc.filename", context->filename->clone());
		if(context->starts_line)
			node->attrs->set("phc.unparser.starts_line", new Boolean(true));

		AST_commented_node* cnode;
		cnode = dynamic_cast<AST_commented_node*>(node);
		if(cnode)
		{
			List<String*>* cmnts = cnode->get_comments();
			cmnts->push_back_all(&context->last_comments);
			context->last_comments.clear();
			context->last_commented_node = cnode;
		}

		return node;
	}

	void PHP_error(PHP_context* context, const char* s)
	{
		phc_error(ERR_BISON, context->filename, context->source_line, s);
	}

	/* Return a new list of statements, containing a single statement */
	static List<AST_statement*>* wrap(AST_statement* statement)
	{
		List<AST_statement*>* result = new List<AST_statement*>;
		result->push_back(statement);
		return result;
	}


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 75 "src/generated_src/php_parser.ypp"
{
	Object* object;
	List<AST_statement*>* list_ast_statement;
	List<AST_catch*>* list_ast_catch;
	AST_catch* ast_catch;
	List<AST_variable*>* list_ast_variable;
	AST_variable* ast_variable;
	Token_string* token_string;
	AST_method* ast_method;
	Integer* integer;
	AST_class_def* ast_class_def;
	Token_class_name* token_class_name;
	AST_interface_def* ast_interface_def;
	List<Token_interface_name*>* list_token_interface_name;
	List<AST_directive*>* list_ast_directive;
	List<AST_switch_case*>* switch_ast_case_list;
	AST_if* ast_if;
	List<AST_formal_parameter*>* list_ast_formal_parameter;
	AST_type* ast_type;
	List<AST_variable_name*>* list_ast_variable_name;
	AST_variable_name* ast_variable_name;
	List<AST_member*>* list_ast_member;
	AST_attr_mod* ast_attr_mod;
	AST_method_mod* ast_method_mod;
	AST_expr* ast_expr;
	AST_method_invocation* ast_method_invocation;
	AST_class_name* class_name;
	AST_constant* ast_constant;
	List<AST_array_elem*>* list_ast_array_elem;
	List<AST_expr*>* list_ast_expr;
	AST_list_elements* ast_list_elements;
	AST_list_element* ast_list_element;
	String* string;
	List<AST_actual_parameter*>* list_ast_actual_parameter;
	AST_class_name* ast_class_name;
	List<AST_switch_case*>* list_ast_switch_case;
	AST_switch_case* ast_switch_case;
	AST_try* ast_try;
	AST_declare* ast_declare;
	AST_foreach* ast_foreach;
	AST_switch* ast_switch;
	AST_for* ast_for;
	AST_do* ast_do;
	AST_while* ast_while;
	AST_statement* ast_statement;
	Token_int* token_int;
	Token_op* token_op;
}
/* Line 187 of yacc.c.  */
#line 449 "src/generated/php_parser.tab.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 124 "src/generated_src/php_parser.ypp"

	int PHP_lex(YYSTYPE* yylval, void* scanner);
	#define scanner context->scanner


/* Line 216 of yacc.c.  */
#line 466 "src/generated/php_parser.tab.cpp"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5810

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  142
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  118
/* YYNRULES -- Number of rules.  */
#define YYNRULES  353
/* YYNRULES -- Number of states.  */
#define YYNSTATES  688

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
       2,     2,     2,   131,     2,     2,   140,   130,   123,     2,
     135,   136,   128,   126,   117,   127,   116,   129,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   120,   137,
     124,   118,   125,   119,   133,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   134,     2,   141,   122,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   138,   121,   139,   132,     2,     2,     2,
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
     242,   243,   252,   253,   262,   269,   271,   274,   277,   278,
     281,   283,   284,   287,   288,   291,   293,   297,   298,   301,
     303,   306,   308,   313,   315,   320,   322,   327,   331,   337,
     341,   346,   351,   357,   358,   364,   369,   371,   373,   375,
     380,   381,   388,   389,   397,   398,   401,   402,   406,   408,
     409,   412,   416,   422,   427,   432,   438,   446,   453,   454,
     456,   458,   460,   461,   463,   465,   468,   472,   476,   481,
     485,   487,   489,   492,   497,   501,   507,   509,   513,   516,
     517,   521,   524,   525,   535,   537,   539,   541,   543,   544,
     546,   548,   551,   553,   555,   557,   559,   561,   563,   567,
     573,   575,   579,   585,   590,   594,   596,   597,   599,   603,
     605,   612,   616,   621,   628,   632,   635,   639,   643,   647,
     651,   655,   659,   663,   667,   671,   675,   679,   682,   685,
     688,   691,   695,   699,   703,   707,   711,   715,   719,   723,
     727,   732,   736,   740,   744,   748,   752,   756,   760,   763,
     766,   769,   772,   776,   780,   784,   788,   792,   796,   800,
     804,   808,   812,   818,   820,   823,   826,   829,   832,   835,
     838,   841,   844,   847,   849,   854,   857,   862,   869,   876,
     881,   883,   885,   887,   892,   894,   897,   898,   901,   902,
     905,   909,   910,   914,   916,   918,   920,   922,   924,   926,
     928,   930,   932,   934,   936,   938,   940,   943,   946,   951,
     953,   957,   959,   961,   963,   964,   967,   968,   970,   976,
     980,   984,   986,   988,   990,   992,   994,   996,   999,  1001,
    1004,  1006,  1010,  1014,  1015,  1017,  1020,  1024,  1026,  1028,
    1030,  1033,  1035,  1040,  1045,  1047,  1049,  1054,  1055,  1057,
    1059,  1061,  1066,  1071,  1073,  1075,  1079,  1081,  1084,  1088,
    1090,  1092,  1097,  1098,  1099,  1102,  1108,  1112,  1116,  1118,
    1125,  1130,  1135,  1138,  1143,  1148,  1151,  1154,  1159,  1162,
    1165,  1167,  1171,  1175
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
      -1,    17,    -1,   259,    -1,   149,   135,   233,   136,   148,
     192,   194,    -1,   149,   135,   233,   136,   120,   146,   193,
     195,    27,   137,    -1,   152,   135,   233,   136,   191,    -1,
     153,   148,    53,   135,   233,   136,   137,    -1,   154,   135,
     215,   137,   215,   137,   215,   136,   184,    -1,   155,   135,
     233,   136,   188,    -1,    11,   137,    -1,    11,   233,   137,
      -1,    15,   137,    -1,    15,   233,   137,    -1,    47,   137,
      -1,    47,   217,   137,    -1,    47,   237,   137,    -1,    36,
     201,   137,    -1,    48,   203,   137,    -1,    20,   214,   137,
      -1,   114,    -1,   233,   137,    -1,    51,   168,   137,    -1,
      50,   135,   166,   136,   137,    -1,   151,   135,   237,    10,
     183,   182,   136,   185,    -1,   151,   135,   217,    10,   235,
     182,   136,   185,    -1,   156,   135,   187,   136,   186,    -1,
     137,    -1,   157,   259,   158,   135,   219,   111,   136,   259,
     163,    -1,    68,   233,   137,    -1,   164,    -1,    -1,   165,
      -1,   164,   165,    -1,   158,   135,   219,   111,   136,   259,
      -1,   167,    -1,   166,   117,   167,    -1,   237,    -1,   109,
      -1,   135,   109,   136,    -1,   172,    -1,   174,    -1,    -1,
     123,    -1,    -1,   159,   171,   110,   173,   135,   196,   136,
     259,    -1,    -1,   176,   110,   175,   177,   180,   138,   204,
     139,    -1,   178,   110,   179,   138,   204,   139,    -1,    13,
      -1,    64,    13,    -1,    57,    13,    -1,    -1,    32,   219,
      -1,    59,    -1,    -1,    32,   181,    -1,    -1,    60,   181,
      -1,   219,    -1,   181,   117,   219,    -1,    -1,    83,   183,
      -1,   235,    -1,   123,   235,    -1,   148,    -1,   120,   146,
      25,   137,    -1,   148,    -1,   120,   146,    26,   137,    -1,
     148,    -1,   120,   146,    24,   137,    -1,   110,   118,   227,
      -1,   187,   117,   110,   118,   227,    -1,   138,   189,   139,
      -1,   138,   137,   189,   139,    -1,   120,   189,    28,   137,
      -1,   120,   137,   189,    28,   137,    -1,    -1,   189,   160,
     233,   190,   146,    -1,   189,   161,   190,   146,    -1,   120,
      -1,   137,    -1,   148,    -1,   120,   146,    29,   137,    -1,
      -1,   192,   150,   135,   233,   136,   148,    -1,    -1,   193,
     150,   135,   233,   136,   120,   146,    -1,    -1,    21,   148,
      -1,    -1,    21,   120,   146,    -1,   197,    -1,    -1,   198,
     111,    -1,   198,   123,   111,    -1,   198,   123,   111,   118,
     227,    -1,   198,   111,   118,   227,    -1,   197,   117,   198,
     111,    -1,   197,   117,   198,   123,   111,    -1,   197,   117,
     198,   123,   111,   118,   227,    -1,   197,   117,   198,   111,
     118,   227,    -1,    -1,   110,    -1,     9,    -1,   200,    -1,
      -1,   217,    -1,   237,    -1,   123,   235,    -1,   200,   117,
     217,    -1,   200,   117,   237,    -1,   200,   117,   123,   235,
      -1,   201,   117,   202,    -1,   202,    -1,   111,    -1,   140,
     234,    -1,   140,   138,   233,   139,    -1,   203,   117,   111,
      -1,   203,   117,   111,   118,   227,    -1,   111,    -1,   111,
     118,   227,    -1,   204,   205,    -1,    -1,   208,   212,   137,
      -1,   213,   137,    -1,    -1,   209,   159,   171,   110,   206,
     135,   196,   136,   207,    -1,   137,    -1,   259,    -1,   210,
      -1,    52,    -1,    -1,   210,    -1,   211,    -1,   210,   211,
      -1,    61,    -1,    63,    -1,    62,    -1,    48,    -1,    64,
      -1,    57,    -1,   212,   117,   111,    -1,   212,   117,   111,
     118,   227,    -1,   111,    -1,   111,   118,   227,    -1,   213,
     117,   110,   118,   227,    -1,    14,   110,   118,   227,    -1,
     214,   117,   233,    -1,   233,    -1,    -1,   216,    -1,   216,
     117,   233,    -1,   233,    -1,    42,   135,   252,   136,   118,
     233,    -1,   237,   118,   233,    -1,   237,   118,   123,   237,
      -1,   237,   118,   123,    43,   220,   225,    -1,    43,   220,
     225,    -1,    65,   233,    -1,   237,    90,   233,    -1,   237,
      91,   233,    -1,   237,    92,   233,    -1,   237,    93,   233,
      -1,   237,    94,   233,    -1,   237,    95,   233,    -1,   237,
      96,   233,    -1,   237,    97,   233,    -1,   237,    98,   233,
      -1,   237,    99,   233,    -1,   237,   100,   233,    -1,   236,
      81,    -1,    81,   236,    -1,   236,    82,    -1,    82,   236,
      -1,   233,    88,   233,    -1,   233,    89,   233,    -1,   233,
       4,   233,    -1,   233,     3,   233,    -1,   233,     5,   233,
      -1,   233,   121,   233,    -1,   233,   123,   233,    -1,   233,
     122,   233,    -1,   233,   116,   233,    -1,   233,   101,   233,
     139,    -1,   233,   126,   233,    -1,   233,   127,   233,    -1,
     233,   128,   233,    -1,   233,   129,   233,    -1,   233,   130,
     233,    -1,   233,    85,   233,    -1,   233,    86,   233,    -1,
     126,   233,    -1,   127,   233,    -1,   131,   233,    -1,   132,
     233,    -1,   233,    76,   233,    -1,   233,    78,   233,    -1,
     233,    75,   233,    -1,   233,    77,   233,    -1,   233,   124,
     233,    -1,   233,    79,   233,    -1,   233,   125,   233,    -1,
     233,    80,   233,    -1,   233,    40,   220,    -1,   135,   233,
     136,    -1,   233,   119,   233,   120,   233,    -1,   256,    -1,
     102,   233,    -1,   103,   233,    -1,   104,   233,    -1,   105,
     233,    -1,   106,   233,    -1,   107,   233,    -1,   108,   233,
      -1,    31,   224,    -1,   133,   233,    -1,   229,    -1,     9,
     135,   254,   136,    -1,    44,   233,    -1,   110,   135,   199,
     136,    -1,   219,    87,   110,   135,   199,   136,    -1,   219,
      87,   241,   135,   199,   136,    -1,   241,   135,   199,   136,
      -1,   110,    -1,   110,    -1,   221,    -1,   244,    84,   248,
     222,    -1,   244,    -1,   222,   223,    -1,    -1,    84,   248,
      -1,    -1,   135,   136,    -1,   135,   233,   136,    -1,    -1,
     135,   199,   136,    -1,   112,    -1,   113,    -1,   109,    -1,
      73,    -1,    72,    -1,    74,    -1,     8,    -1,     6,    -1,
      55,    -1,    56,    -1,    54,    -1,   226,    -1,   110,    -1,
     126,   227,    -1,   127,   227,    -1,     9,   135,   230,   136,
      -1,   228,    -1,   110,    87,   110,    -1,   110,    -1,   258,
      -1,   226,    -1,    -1,   232,   231,    -1,    -1,   117,    -1,
     232,   117,   227,    83,   227,    -1,   232,   117,   227,    -1,
     227,    83,   227,    -1,   227,    -1,   234,    -1,   217,    -1,
     237,    -1,   237,    -1,   237,    -1,   243,   238,    -1,   243,
      -1,   238,   239,    -1,   239,    -1,    84,   248,   240,    -1,
     135,   199,   136,    -1,    -1,   245,    -1,   251,   245,    -1,
     219,    87,   241,    -1,   244,    -1,   218,    -1,   245,    -1,
     251,   245,    -1,   242,    -1,   245,   134,   247,   141,    -1,
     245,   138,   233,   139,    -1,   246,    -1,   111,    -1,   140,
     138,   233,   139,    -1,    -1,   233,    -1,   249,    -1,   241,
      -1,   249,   134,   247,   141,    -1,   249,   138,   233,   139,
      -1,   250,    -1,   110,    -1,   138,   233,   139,    -1,   140,
      -1,   251,   140,    -1,   252,   117,   253,    -1,   253,    -1,
     237,    -1,    42,   135,   252,   136,    -1,    -1,    -1,   255,
     231,    -1,   255,   117,   233,    83,   233,    -1,   255,   117,
     233,    -1,   233,    83,   233,    -1,   233,    -1,   255,   117,
     233,    83,   123,   235,    -1,   255,   117,   123,   235,    -1,
     233,    83,   123,   235,    -1,   123,   235,    -1,    41,   135,
     257,   136,    -1,    23,   135,   237,   136,    -1,    38,   233,
      -1,    39,   233,    -1,    30,   135,   233,   136,    -1,    45,
     233,    -1,    46,   233,    -1,   237,    -1,   257,   117,   237,
      -1,   219,    87,   110,    -1,   138,   146,   139,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   426,   426,   437,   443,   449,   453,   457,   461,   471,
     477,   483,   487,   491,   495,   502,   513,   520,   527,   534,
     541,   548,   555,   562,   569,   576,   583,   590,   597,   605,
     609,   642,   667,   674,   681,   690,   697,   701,   705,   709,
     713,   717,   721,   725,   743,   747,   751,   758,   762,   768,
     778,   803,   829,   836,   840,   857,   864,   869,   876,   883,
     892,   905,   911,   919,   926,   930,   937,   944,   952,   955,
     962,   962,   975,   975,   986,  1009,  1014,  1019,  1028,  1031,
    1038,  1046,  1049,  1060,  1063,  1070,  1080,  1091,  1094,  1101,
    1105,  1113,  1117,  1124,  1128,  1135,  1139,  1146,  1156,  1167,
    1171,  1175,  1179,  1187,  1190,  1199,  1214,  1215,  1219,  1223,
    1231,  1234,  1271,  1274,  1304,  1307,  1318,  1321,  1328,  1333,
    1343,  1354,  1365,  1376,  1387,  1395,  1403,  1411,  1423,  1426,
    1431,  1438,  1443,  1449,  1455,  1461,  1467,  1472,  1477,  1485,
    1490,  1500,  1505,  1509,  1517,  1526,  1535,  1545,  1558,  1565,
    1571,  1583,  1587,  1587,  1603,  1608,  1615,  1624,  1632,  1635,
    1642,  1646,  1653,  1657,  1661,  1665,  1669,  1673,  1680,  1689,
    1698,  1708,  1721,  1730,  1746,  1753,  1766,  1769,  1779,  1783,
    1790,  1794,  1798,  1802,  1806,  1810,  1814,  1825,  1836,  1847,
    1858,  1869,  1880,  1891,  1902,  1913,  1924,  1935,  1939,  1943,
    1947,  1951,  1955,  1959,  1963,  1967,  1971,  1975,  1979,  1983,
    1987,  1997,  2001,  2005,  2009,  2013,  2017,  2021,  2025,  2030,
    2034,  2038,  2042,  2046,  2050,  2054,  2058,  2062,  2066,  2070,
    2074,  2078,  2084,  2088,  2092,  2096,  2100,  2104,  2108,  2112,
    2116,  2120,  2124,  2128,  2132,  2136,  2143,  2149,  2155,  2159,
    2166,  2174,  2180,  2191,  2204,  2211,  2217,  2224,  2235,  2238,
    2242,  2250,  2255,  2262,  2266,  2270,  2274,  2278,  2282,  2286,
    2290,  2294,  2298,  2302,  2309,  2313,  2318,  2323,  2327,  2331,
    2338,  2348,  2354,  2358,  2366,  2369,  2378,  2380,  2384,  2391,
    2398,  2406,  2417,  2421,  2428,  2435,  2442,  2466,  2498,  2509,
    2515,  2544,  2582,  2587,  2593,  2597,  2609,  2617,  2621,  2628,
    2632,  2641,  2648,  2653,  2661,  2668,  2673,  2682,  2685,  2692,
    2696,  2708,  2713,  2721,  2731,  2736,  2747,  2751,  2759,  2765,
    2778,  2782,  2787,  2794,  2797,  2807,  2814,  2821,  2829,  2837,
    2845,  2853,  2862,  2874,  2879,  2883,  2887,  2891,  2895,  2899,
    2906,  2913,  2921,  2934
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
  "CAST_UNSET", "STRING", "IDENT", "VARIABLE", "INT", "REAL",
  "INLINE_HTML", "INVALID_TOKEN", "'.'", "','", "'='", "'?'", "':'", "'|'",
  "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'",
  "'~'", "'@'", "'['", "'('", "')'", "';'", "'{'", "'}'", "'$'", "']'",
  "$accept", "start", "top_statement_list", "top_statement",
  "inner_statement_list", "inner_statement", "statement", "keyword_if",
  "keyword_elseif", "keyword_foreach", "keyword_while", "keyword_do",
  "keyword_for", "keyword_switch", "keyword_declare", "keyword_try",
  "keyword_catch", "keyword_function", "keyword_case", "keyword_default",
  "unticked_statement", "additional_catches",
  "non_empty_additional_catches", "additional_catch", "unset_variables",
  "unset_variable", "use_filename", "function_declaration_statement",
  "class_declaration_statement", "is_reference",
  "unticked_function_declaration_statement", "@1",
  "unticked_class_declaration_statement", "@2", "class_entry_type",
  "extends_from", "interface_entry", "interface_extends_list",
  "implements_list", "interface_list", "foreach_optional_arg",
  "foreach_variable", "for_statement", "foreach_statement",
  "declare_statement", "declare_list", "switch_case_list", "case_list",
  "case_separator", "while_statement", "elseif_list", "new_elseif_list",
  "else_single", "new_else_single", "parameter_list",
  "non_empty_parameter_list", "optional_class_type",
  "function_call_parameter_list", "non_empty_function_call_parameter_list",
  "global_var_list", "global_var", "static_var_list",
  "class_statement_list", "class_statement", "@3", "method_body",
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
     365,   366,   367,   368,   369,   370,    46,    44,    61,    63,
      58,   124,    94,    38,    60,    62,    43,    45,    42,    47,
      37,    33,   126,    64,    91,    40,    41,    59,   123,   125,
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
     173,   172,   175,   174,   174,   176,   176,   176,   177,   177,
     178,   179,   179,   180,   180,   181,   181,   182,   182,   183,
     183,   184,   184,   185,   185,   186,   186,   187,   187,   188,
     188,   188,   188,   189,   189,   189,   190,   190,   191,   191,
     192,   192,   193,   193,   194,   194,   195,   195,   196,   196,
     197,   197,   197,   197,   197,   197,   197,   197,   198,   198,
     198,   199,   199,   200,   200,   200,   200,   200,   200,   201,
     201,   202,   202,   202,   203,   203,   203,   203,   204,   204,
     205,   205,   206,   205,   207,   207,   208,   208,   209,   209,
     210,   210,   211,   211,   211,   211,   211,   211,   212,   212,
     212,   212,   213,   213,   214,   214,   215,   215,   216,   216,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,   217,   217,   217,   217,   217,   218,   218,   218,   218,
     219,   220,   220,   221,   221,   222,   222,   223,   224,   224,
     224,   225,   225,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   227,   227,   227,   227,   227,   227,
     228,   229,   229,   229,   230,   230,   231,   231,   232,   232,
     232,   232,   233,   233,   234,   235,   236,   237,   237,   238,
     238,   239,   240,   240,   241,   241,   242,   243,   243,   244,
     244,   244,   245,   245,   245,   246,   246,   247,   247,   248,
     248,   249,   249,   249,   250,   250,   251,   251,   252,   252,
     253,   253,   253,   254,   254,   255,   255,   255,   255,   255,
     255,   255,   255,   256,   256,   256,   256,   256,   256,   256,
     257,   257,   258,   259
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
       0,     8,     0,     8,     6,     1,     2,     2,     0,     2,
       1,     0,     2,     0,     2,     1,     3,     0,     2,     1,
       2,     1,     4,     1,     4,     1,     4,     3,     5,     3,
       4,     4,     5,     0,     5,     4,     1,     1,     1,     4,
       0,     6,     0,     7,     0,     2,     0,     3,     1,     0,
       2,     3,     5,     4,     4,     5,     7,     6,     0,     1,
       1,     1,     0,     1,     1,     2,     3,     3,     4,     3,
       1,     1,     2,     4,     3,     5,     1,     3,     2,     0,
       3,     2,     0,     9,     1,     1,     1,     1,     0,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     3,     5,
       1,     3,     5,     4,     3,     1,     0,     1,     3,     1,
       6,     3,     4,     6,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     5,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     4,     2,     4,     6,     6,     4,
       1,     1,     1,     4,     1,     2,     0,     2,     0,     2,
       3,     0,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     4,     1,
       3,     1,     1,     1,     0,     2,     0,     1,     5,     3,
       3,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     3,     3,     0,     1,     2,     3,     1,     1,     1,
       2,     1,     4,     4,     1,     1,     4,     0,     1,     1,
       1,     4,     4,     1,     1,     3,     1,     2,     3,     1,
       1,     4,     0,     0,     2,     5,     3,     3,     1,     6,
       4,     4,     2,     4,     4,     2,     2,     4,     2,     2,
       1,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     2,     1,   270,   269,     0,     0,    75,     0,
      23,    20,     0,     0,     0,   258,    21,    18,    26,     0,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,     0,     0,    19,   273,   271,   272,     0,    80,
       0,     0,    24,     0,     0,   267,   266,   268,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   265,   281,   315,
     263,   264,    46,     0,     0,     0,     0,     0,     0,    53,
      10,   326,     3,     5,     0,     0,     0,     0,     0,     0,
       0,     0,    68,    15,     6,     7,    66,    67,     0,     0,
     293,   308,     0,   283,   243,     0,   292,     0,   294,     0,
     311,   298,   307,   309,   314,     0,   233,   282,    29,   333,
      36,     0,    38,     0,     0,   175,     0,     0,     0,   241,
     141,     0,     0,   140,   345,   346,     0,   332,   251,     0,
     261,   252,   254,   309,     0,   245,   348,   349,    40,   293,
       0,   294,   146,     0,     0,    64,     0,     0,    77,    76,
     185,     0,     0,   250,     0,   198,   296,   200,   234,   235,
     236,   237,   238,   239,   240,   132,   218,   219,   220,   221,
     242,     0,     0,     0,     0,     0,     0,     0,   176,     0,
       0,     0,    69,     0,    72,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    47,   197,   199,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   132,
       0,   297,   300,   317,     0,   327,   310,     0,   338,     0,
     286,    37,    39,     0,    45,     0,     0,   259,     0,     0,
     142,   294,     0,    43,   350,     0,     0,   330,     0,   329,
       0,   132,   184,     0,   310,    41,    42,     0,     0,    44,
       0,    61,    63,     0,    48,    55,     0,     0,     0,     0,
     131,   293,   294,   231,     0,   353,     9,    11,    12,    13,
       0,     0,   293,   294,     0,     0,     0,   177,   179,     0,
       0,     0,    25,     0,    70,    78,     0,     0,   352,   306,
     304,     0,   204,   203,   205,   230,   224,   222,   225,   223,
     227,   229,   216,   217,   201,   202,     0,   209,     0,   206,
     208,   207,   226,   228,   211,   212,   213,   214,   215,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
       0,   181,     0,   324,     0,   320,   303,   319,   323,   299,
     318,     0,     0,   342,   295,     0,   244,   287,   334,   174,
     344,   347,   260,     0,   139,     0,   343,   332,   332,     0,
     306,     0,   256,     0,   275,     0,     0,   274,   147,   279,
     144,     0,     0,    65,     8,     0,   135,   246,     0,     0,
     316,     0,     0,     0,     0,     0,   176,     0,     0,     0,
       0,     0,     0,     0,     0,    83,   250,    82,    85,   149,
     132,   132,   305,   210,     0,     0,   182,   249,     0,   132,
     301,   317,     0,   312,   313,     0,   337,     0,   336,   143,
     351,     0,   328,     0,   262,   253,   284,     0,   276,   277,
       0,    62,    49,     0,   293,   294,     0,    10,   110,    87,
       0,    87,    89,    10,   108,    32,     0,     0,   178,   103,
     103,    35,    97,     0,    10,    95,    52,     0,   128,    79,
       0,     0,     0,   158,     0,     0,   232,   261,   325,     0,
       0,     0,   341,   340,     0,   331,   180,     0,   255,   291,
       0,   286,   280,   145,   138,    14,   112,   114,     0,     0,
      90,     0,     0,     0,   176,   103,     0,   103,     0,     0,
       0,     0,   130,   129,     0,   118,     0,    84,   149,    86,
       0,   165,   157,   167,   162,   164,   163,   166,    74,   148,
       0,     0,   156,   160,     0,   247,   248,   183,   302,   321,
     322,     0,   335,   257,     0,   278,   287,   285,   116,     0,
      17,     0,    30,    88,     0,     0,     0,    33,     0,     0,
      27,    28,     0,     0,     0,     0,    99,    98,     0,     0,
       0,   128,   120,     0,   158,     0,   170,     0,    68,   161,
       0,   151,   339,   290,   289,     0,     0,     0,   115,     0,
      10,    93,    51,    50,   109,     0,     0,   101,     0,   106,
     107,    10,   100,    96,    57,    71,     0,     0,   121,    73,
       0,     0,     0,   150,     0,     0,     0,    10,     0,     0,
       0,     0,    10,    91,    34,   102,    10,   105,     0,    54,
      56,    58,   124,     0,   123,     0,   173,   171,   168,   152,
       0,   288,   117,     0,    31,     0,     0,     0,   104,     0,
      59,     0,   125,   122,     0,     0,   172,     0,   111,    94,
       0,     0,   127,     0,   169,   128,    10,    92,     0,   126,
       0,   113,     0,     0,    60,   154,   153,   155
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    72,   172,   286,   287,    74,   561,    75,
      76,    77,    78,    79,    80,    81,   638,    82,   573,   574,
      83,   639,   640,   641,   270,   271,   147,   288,   289,   183,
      86,   413,    87,   305,    88,   415,    89,   307,   481,   417,
     509,   461,   634,   602,   476,   301,   471,   516,   611,   465,
     507,   558,   562,   597,   524,   525,   526,   279,   280,   122,
     123,   143,   483,   539,   665,   686,   540,   541,   542,   543,
     587,   544,   114,   296,   297,    90,    91,    92,   130,   131,
     445,   498,   119,   262,    93,   388,   389,    94,   500,   368,
     501,    95,    96,   462,    97,    98,   231,   232,   430,    99,
     100,   101,   102,   103,   104,   361,   356,   357,   358,   105,
     258,   259,   239,   240,   106,   255,   107,   108
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -448
static const yytype_int16 yypact[] =
{
    -448,    39,  1907,  -448,  -448,  -448,   -90,  2949,  -448,  3060,
    -448,  -448,  4170,   -53,   -45,   -39,  -448,  -448,  -448,   -57,
    -448,  4170,  4170,   -36,   -13,   -76,  4170,  4170,  4170,  3171,
     -64,  -448,    -8,   -72,  -448,  -448,  -448,  -448,    91,  -448,
     152,  4170,  -448,  4170,    35,  -448,  -448,  -448,    -3,    -3,
    4170,  4170,  4170,  4170,  4170,  4170,  4170,  -448,   -75,  -448,
    -448,  -448,  -448,  4170,  4170,  4170,  4170,  4170,  4170,  -448,
    -448,    49,  -448,  -448,    63,    66,    69,  2838,    72,    74,
      79,    52,    95,  -448,  -448,  -448,  -448,  -448,   120,   126,
    -448,  -448,   155,  -448,  -448,  4308,  -448,     7,   243,   108,
    -448,   161,  -448,    68,  -448,   -34,  -448,  -448,  -448,  3282,
    -448,  4372,  -448,  4436,   -81,  5332,    -3,  4170,  3393,  -448,
    -448,   -88,   -46,  -448,  5332,  5332,    -3,   -16,   159,   164,
     115,  -448,   173,    58,   -34,  5516,  5332,  5332,  -448,   123,
    5332,   639,   143,   -44,    -3,  -448,   154,   128,  -448,  -448,
    -448,  4500,   141,   129,   182,  -448,  -448,  -448,  -448,  -448,
    -448,  -448,  -448,  -448,  -448,  3504,   -12,   -12,   238,  -448,
    -448,  4564,  1240,  4170,  4170,  4170,  4170,   226,  4170,  4170,
     175,   216,  -448,   176,  -448,   255,    15,  4170,  4170,  4170,
     -76,  4170,  4170,  4170,  4170,  4170,  4170,  4170,  4170,  4170,
    4170,  4170,  4170,  4170,  4170,  4170,  4170,  4170,  4170,  4170,
    4170,  4170,  4170,  4170,  -448,  -448,  -448,  4170,  4170,  4170,
    4170,  4170,  4170,  4170,  4170,  4170,  4170,  4170,  3615,  3504,
     -68,   161,  -448,  4170,  4170,    49,   100,    -3,  5140,   153,
     171,  -448,  -448,  4170,  -448,   162,  4628,  -448,  4692,  4170,
    -448,  -448,   -57,  -448,  -448,   -87,   165,  -448,   -71,  -448,
     -31,  3504,  -448,   -68,    58,  -448,  -448,   247,   193,  -448,
      26,  -448,  -448,   169,  -448,  -448,   170,    28,    -3,   178,
     189,    37,   840,  -448,   180,  -448,  -448,  -448,  -448,  -448,
     721,  4756,   306,   496,  4820,   187,   186,   200,  5332,  4884,
     209,    41,  -448,   194,  -448,   300,   234,   207,   211,   212,
      58,   -34,  5516,  5396,  5460,  -448,  5663,  5663,  5663,  5663,
     146,   146,   183,   183,  5589,  5607,   826,   -12,  5204,  5364,
    1082,  5680,   146,   146,   -12,   -12,   238,   238,   238,  5516,
    5516,  5516,  5516,  5516,  5516,  5516,  5516,  5516,  5516,  5516,
     -10,  5516,   213,  -448,  4170,  -448,   215,    78,  -448,  -448,
    5332,   214,   920,  -448,  -448,  3726,  -448,  3837,  -448,  5332,
    -448,  -448,  -448,   985,  -448,    -3,  -448,   -16,   -16,   230,
    -448,   222,  -448,   217,   275,   247,   247,  -448,  -448,  -448,
     245,    -3,   227,  -448,  -448,   211,  -448,  -448,  3948,   229,
    -448,  2173,    -3,   -79,  2306,  4170,  4170,  4170,   -33,   247,
     256,  2439,   234,   235,   234,   308,  -448,   252,  -448,  -448,
    3504,  3504,    58,  -448,  4170,   -76,  -448,  -448,  1050,  3504,
    -448,  4170,  4170,  -448,  -448,    -3,  5332,    -3,  5268,  -448,
    -448,    55,  -448,  4170,  -448,   287,   247,   262,  -448,  -448,
     247,  -448,  -448,    -3,    61,  1238,   239,  -448,  -448,   292,
      -3,   292,  -448,  -448,  -448,  -448,  4948,   240,  5332,   244,
     246,  -448,  -448,   264,  -448,  -448,  -448,   273,     0,  -448,
     234,   248,   234,     5,   249,   251,  5533,   115,  -448,   253,
     257,  1115,  -448,  -448,  4059,  -448,  5516,   -68,  -448,   309,
     260,   276,  -448,  -448,  -448,  -448,  2040,    92,   -79,   261,
    -448,   267,  1375,   278,  4170,  -448,   133,  -448,     1,   247,
    1508,   274,  -448,  -448,   280,   295,    65,   252,  -448,  -448,
     310,  -448,  -448,  -448,  -448,  -448,  -448,  -448,  -448,  -448,
     307,   387,   233,  -448,    -6,  -448,  -448,  -448,  -448,  -448,
    -448,    -3,  5332,  -448,   247,  -448,   247,  -448,   127,  2838,
    -448,   288,  -448,  -448,  2572,  2572,   289,  -448,   291,   135,
    -448,  -448,   293,  4170,   -82,     3,  -448,  -448,   294,    52,
      52,     2,   316,   314,    71,   319,   323,     4,    95,  -448,
     332,  -448,  -448,  -448,   360,   324,   311,   418,  -448,  4170,
    -448,  -448,  -448,  -448,  -448,  2705,   312,  -448,  4244,  -448,
    -448,  -448,  -448,  -448,   216,  -448,    70,   247,   334,  -448,
     247,   247,   342,  -448,   344,   337,   247,  -448,  4170,   320,
    5012,  1641,  -448,  -448,  -448,  -448,  -448,  2040,   325,  -448,
     216,  -448,   343,   351,  -448,   247,  -448,  -448,   345,  -448,
     247,  -448,  2040,  5076,  -448,  2838,   327,  1774,  2040,   234,
    -448,   247,   348,  -448,   247,   333,  -448,   349,  -448,  -448,
     335,   359,  -448,   247,  -448,     0,  -448,  -448,   339,  -448,
     341,  2040,    52,    84,  -448,  -448,  -448,  -448
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -448,  -448,  -448,  -448,  -447,  -448,    -2,  -448,   -85,  -448,
    -448,  -448,  -448,  -448,  -448,  -448,   290,   -61,  -448,  -448,
    -448,  -448,  -448,  -159,  -448,    94,  -448,   480,   485,   -97,
    -448,  -448,  -448,  -448,  -448,  -448,  -448,  -448,  -448,    12,
      36,    -9,  -448,   -67,  -448,  -448,  -448,  -441,  -108,  -448,
    -448,  -448,  -448,  -448,  -172,  -448,   -77,  -221,  -448,  -448,
     259,  -448,   -23,  -448,  -448,  -448,  -448,  -448,  -448,   -35,
    -448,  -448,  -448,  -385,  -448,    19,  -448,   -24,  -188,  -448,
    -448,  -448,  -448,    22,  -226,   163,  -448,  -448,  -448,    11,
    -448,   467,   392,  -220,   179,    30,  -448,   283,  -448,  -179,
    -448,  -448,   -21,   -19,  -448,    85,  -258,  -448,  -448,   -11,
     138,   147,  -448,  -448,  -448,  -448,  -448,   -78
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -306
static const yytype_int16 yytable[] =
{
      73,   129,   315,   181,   132,   382,   133,   309,   352,   522,
     506,   522,  -250,   570,   134,   570,   512,   363,   571,   530,
     571,   467,   153,    59,   154,   154,   256,   520,   190,   518,
     375,   153,    59,   425,   128,    59,   243,   145,   609,     3,
     381,   387,   353,    59,   460,   109,   378,   142,   139,   376,
     249,   355,    71,   531,   120,   610,   244,   532,   396,   141,
     165,    71,   533,   146,    71,   379,   534,   535,   536,   537,
     354,   252,    71,   268,   569,   177,   575,    59,   156,   156,
      59,   380,   116,   121,   355,   530,   236,   469,   215,   216,
     117,   253,   154,   269,   153,    59,   118,   154,   309,   126,
     153,    59,   154,   154,   148,   470,   235,   153,    59,    71,
     523,   590,   523,   559,   560,   264,   211,   212,   213,   531,
     154,   622,   127,   532,    71,   308,    59,   144,   533,   568,
      71,   591,   534,   535,   536,   537,  -119,    71,   395,    59,
     576,   623,   612,   391,   538,   570,   245,   570,   595,   560,
     571,   251,   571,   631,  -133,    71,   254,   257,   410,   387,
     387,   572,   392,   606,   637,   149,   129,   310,    71,   132,
     152,   133,   378,  -133,   272,   311,   582,   411,  -136,   134,
     652,   642,   459,   387,   281,   657,   190,   173,   583,   658,
      70,   495,   233,   643,   292,   282,   234,  -136,   174,   484,
     485,   175,   233,  -304,   176,   293,   234,   178,   489,   179,
     619,   310,   431,   154,   180,   492,   432,   493,   182,   311,
     387,   685,    70,   190,   387,  -306,  -306,   155,   157,   681,
     184,   197,   198,   504,   233,  -305,   185,   487,   234,   553,
     510,   310,   186,   229,   310,   230,  -250,   201,   281,   311,
     261,   260,   311,     4,   154,     5,   383,   263,   310,   282,
     265,   267,   202,   273,   165,   274,   311,   364,  -159,   277,
    -306,  -306,   209,   210,   211,   212,   213,   276,   190,   295,
     281,   531,   418,   302,   201,   300,   304,   306,   367,   366,
     533,   282,   422,   387,   534,   535,   536,   537,   370,   202,
     377,    35,    36,    37,   390,   393,   398,   394,   364,   209,
     210,   211,   212,   213,   397,   399,   402,   407,   355,    45,
      46,    47,   405,   406,  -296,  -296,   154,   409,   387,   412,
     387,   592,   414,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   416,   419,   420,   421,   443,   427,
     429,   154,   446,   154,   154,   433,    57,   384,   444,    60,
      61,   228,   447,   450,   452,   456,   473,   154,   480,   482,
     478,   497,   502,   385,   386,   508,   505,   514,   154,   154,
     426,   515,   519,   517,   521,   545,   528,   546,   477,   548,
     479,   387,   554,   556,   387,   387,   555,   564,   549,   458,
     387,   129,   464,   565,   132,   440,   133,   257,   257,   475,
     579,   154,   581,   154,   134,   567,   580,   454,   586,   387,
     585,   272,    18,   599,   387,   618,   604,   605,   455,   154,
     607,   613,   364,   364,   617,   387,   154,   620,   387,   281,
     281,   621,   625,   626,   627,   629,   628,   387,   281,   635,
     282,   282,   645,   648,   649,   650,   418,   654,   529,   282,
     659,   661,   662,   664,   669,   364,   673,   364,   675,   676,
     678,   303,   677,   596,   111,   682,   113,   683,   310,   115,
     588,   660,    84,   364,   154,   451,   311,    85,   124,   125,
     364,   624,   527,   135,   136,   137,   140,   511,   603,   563,
     636,   614,   615,   680,   616,   584,   403,   589,   150,   547,
     151,   374,   557,   250,   359,   441,   490,   158,   159,   160,
     161,   162,   163,   164,     0,   442,     0,   154,     0,     0,
     166,   167,   168,   169,   170,   171,     0,     0,   364,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   448,   449,
       0,     0,     0,     0,     0,     0,     0,   598,     0,     0,
       0,     0,   601,   601,     0,     0,     0,     0,     0,     0,
       0,     0,   472,     0,     0,     0,   238,  -296,  -296,     0,
       0,   364,     0,     0,   246,   248,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,     0,     0,     0,
       0,     0,     0,   633,   684,   687,     0,     0,     0,   499,
       0,     0,     0,   503,   228,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   140,     0,     0,   671,     0,     0,     0,     0,
     290,   291,   140,   294,     0,   298,   299,     0,     0,     0,
       0,     0,     0,   668,   312,   313,   314,     0,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,     0,   577,     0,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   351,   140,     0,     0,     0,
     360,   362,     0,     0,     0,     0,     0,     0,     0,     0,
     369,     0,     0,     0,     0,     0,   373,   593,     0,   594,
    -296,  -296,     0,     0,   187,   188,   189,     0,   140,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   228,     0,     0,
       0,   190,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   266,     0,     0,     0,
     644,     0,     0,   646,   647,     0,     0,     0,     0,   651,
       0,     0,     0,     0,     0,     0,   191,   192,   193,   194,
     195,   196,     0,     0,     0,     0,   197,   198,   663,   199,
     200,     0,     0,   666,     0,     0,     0,     0,     0,     0,
       0,   428,   201,     0,   672,     0,     0,   674,     0,   187,
     188,   189,   436,     0,   438,     0,   679,   202,     0,     0,
     203,     0,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,     0,     0,     0,     0,     0,     0,     0,     0,
     400,     0,     0,     0,     0,   140,   190,     0,     0,     0,
       0,     0,   466,   298,   468,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   140,   140,     0,
       0,   486,     0,     0,     0,     0,   140,     0,   360,   491,
       0,   191,   192,   193,   194,   195,   196,     0,     0,     0,
     496,   197,   198,     0,   199,   200,     0,     0,     0,     0,
       0,  -296,  -296,   187,   188,   189,     0,   201,     0,     0,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,     0,   202,     0,     0,   203,     0,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,  -134,   228,     0,
     190,   552,     0,     0,     0,   423,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -134,     0,     0,     0,
       0,   298,     0,     0,     0,     0,     0,     0,   187,   188,
     189,     0,     0,     0,     0,   191,   192,   193,   194,   195,
     196,     0,     0,     0,     0,   197,   198,     0,   199,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,     0,     0,     0,   190,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   202,     0,     0,   203,
     608,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,     0,     0,   187,   188,   189,     0,     0,     0,   434,
     191,   192,   193,   194,   195,   196,   630,     0,     0,     0,
     197,   198,     0,   199,   200,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   201,     0,     0,     0,
     190,     0,     0,     0,     0,   653,     0,     0,     0,     0,
       0,   202,     0,     0,   203,     0,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,     0,     0,   187,   188,
     189,     0,   190,     0,   439,   191,   192,   193,   194,   195,
     196,     0,     0,     0,     0,   197,   198,     0,   199,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,     0,     0,     0,   190,     0,   191,   192,   193,
     194,   195,   196,     0,     0,     0,   202,   197,   198,   203,
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,     0,     0,   201,     0,     0,     0,     0,     0,   488,
     191,   192,   193,   194,   195,   196,     0,     0,   202,     0,
     197,   198,     0,   199,   200,   206,   207,   208,   209,   210,
     211,   212,   213,     0,     0,     0,   201,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   202,     0,     0,   203,     0,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,     4,     0,     5,     6,
       0,     7,     0,     8,   550,     9,    10,     0,     0,    11,
      12,     0,     0,    13,     0,     0,     0,     0,     0,     0,
      14,    15,     0,    16,    17,    18,    19,    20,    21,    22,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     0,    34,    35,    36,    37,    38,     0,    39,
       0,     0,     0,     0,    40,    41,    42,     0,    43,     0,
       0,   284,    45,    46,    47,     0,     0,     0,     0,  -296,
    -296,    48,    49,     0,     0,     0,     0,     0,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,     0,
       0,     0,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,  -137,   228,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    64,     0,     0,
       0,    65,    66,    67,  -137,    68,     0,    69,    70,   285,
      71,     4,     0,     5,     6,     0,     7,     0,     8,     0,
       9,    10,     0,     0,    11,    12,     0,     0,    13,     0,
       0,     0,     0,     0,   566,    14,    15,     0,    16,    17,
      18,    19,    20,    21,    22,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,    34,    35,
      36,    37,    38,     0,    39,     0,     0,     0,     0,    40,
      41,    42,     0,    43,     0,     0,   284,    45,    46,    47,
       0,     0,     0,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    63,    64,     0,     0,     0,    65,    66,    67,     0,
      68,     0,    69,    70,     4,    71,     5,     6,     0,     7,
       0,     8,     0,     9,    10,     0,     0,    11,    12,     0,
       0,    13,   578,     0,     0,     0,     0,     0,    14,    15,
       0,    16,    17,    18,    19,    20,    21,    22,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       0,    34,    35,    36,    37,    38,     0,    39,     0,     0,
       0,     0,    40,    41,    42,     0,    43,     0,     0,   284,
      45,    46,    47,     0,     0,     0,     0,     0,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    63,    64,     0,     0,     0,    65,
      66,    67,     0,    68,     0,    69,    70,     4,    71,     5,
       6,     0,     7,     0,     8,     0,     9,    10,     0,     0,
      11,    12,     0,     0,    13,     0,     0,   656,     0,     0,
       0,    14,    15,     0,    16,    17,    18,    19,    20,    21,
      22,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,    34,    35,    36,    37,    38,     0,
      39,     0,     0,     0,     0,    40,    41,    42,     0,    43,
       0,     0,   284,    45,    46,    47,     0,     0,     0,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    63,    64,     0,
       0,     0,    65,    66,    67,     0,    68,     0,    69,    70,
       4,    71,     5,     6,     0,     7,     0,     8,     0,     9,
      10,     0,     0,    11,    12,     0,     0,    13,     0,   670,
       0,     0,     0,     0,    14,    15,     0,    16,    17,    18,
      19,    20,    21,    22,     0,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     0,    34,    35,    36,
      37,    38,     0,    39,     0,     0,     0,     0,    40,    41,
      42,     0,    43,     0,     0,   284,    45,    46,    47,     0,
       0,     0,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      63,    64,     0,     0,     0,    65,    66,    67,     0,    68,
       0,    69,    70,     4,    71,     5,     6,     0,     7,     0,
       8,     0,     9,    10,     0,     0,    11,    12,     0,     0,
      13,     0,     0,     0,     0,     0,     0,    14,    15,     0,
      16,    17,    18,    19,    20,    21,    22,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     0,
      34,    35,    36,    37,    38,     0,    39,     0,     0,     0,
       0,    40,    41,    42,     0,    43,     0,     0,    44,    45,
      46,    47,     0,     0,     0,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    63,    64,     0,     0,     0,    65,    66,
      67,     0,    68,     0,    69,    70,     4,    71,     5,     6,
       0,     7,     0,     8,     0,     9,    10,     0,     0,    11,
      12,     0,     0,    13,     0,     0,     0,     0,     0,     0,
      14,    15,     0,    16,    17,    18,    19,    20,    21,    22,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     0,    34,    35,    36,    37,    38,     0,    39,
       0,     0,     0,     0,    40,    41,    42,     0,    43,     0,
       0,   284,    45,    46,    47,     0,     0,     0,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    64,     0,     0,
       0,    65,    66,    67,     0,    68,     0,    69,    70,     4,
      71,     5,     6,     0,     7,     0,     0,     0,     9,    10,
       0,     0,    11,    12,     0,     0,    13,     0,     0,     0,
       0,     0,     0,    14,    15,     0,    16,    17,     0,    19,
      20,    21,    22,     0,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,     0,    34,    35,    36,    37,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    42,
       0,    43,     0,     0,     0,    45,    46,    47,     0,     0,
       0,     0,     0,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,     0,     0,
       0,     0,     0,   457,     0,     0,     0,     0,     0,    63,
      64,     0,     0,     0,    65,    66,    67,     0,    68,     0,
      69,    70,     4,    71,     5,     6,     0,     7,     0,     0,
       0,     9,    10,     0,     0,    11,    12,     0,     0,    13,
       0,     0,     0,     0,     0,     0,    14,    15,     0,    16,
      17,     0,    19,    20,    21,    22,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     0,    34,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
       0,    41,    42,     0,    43,     0,     0,     0,    45,    46,
      47,     0,     0,     0,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,     0,     0,     0,     0,     0,   463,     0,     0,     0,
       0,     0,    63,    64,     0,     0,     0,    65,    66,    67,
       0,    68,     0,    69,    70,     4,    71,     5,     6,     0,
       7,     0,     0,     0,     9,    10,     0,     0,    11,    12,
       0,     0,    13,     0,     0,     0,     0,     0,     0,    14,
      15,     0,    16,    17,     0,    19,    20,    21,    22,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     0,    34,    35,    36,    37,     0,     0,     0,     0,
       0,     0,     0,     0,    41,    42,     0,    43,     0,     0,
       0,    45,    46,    47,     0,     0,     0,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,     0,     0,     0,     0,     0,   474,
       0,     0,     0,     0,     0,    63,    64,     0,     0,     0,
      65,    66,    67,     0,    68,     0,    69,    70,     4,    71,
       5,     6,     0,     7,     0,     0,     0,     9,    10,     0,
       0,    11,    12,     0,     0,    13,     0,     0,     0,     0,
       0,     0,    14,    15,     0,    16,    17,     0,    19,    20,
      21,    22,     0,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,     0,    34,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    42,     0,
      43,     0,     0,     0,    45,    46,    47,     0,     0,     0,
       0,     0,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,     0,     0,     0,
       0,     0,   600,     0,     0,     0,     0,     0,    63,    64,
       0,     0,     0,    65,    66,    67,     0,    68,     0,    69,
      70,     4,    71,     5,     6,     0,     7,     0,     0,     0,
       9,    10,     0,     0,    11,    12,     0,     0,    13,     0,
       0,     0,     0,     0,     0,    14,    15,     0,    16,    17,
       0,    19,    20,    21,    22,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,    34,    35,
      36,    37,     0,     0,     0,     0,     0,     0,     0,     0,
      41,    42,     0,    43,     0,     0,     0,    45,    46,    47,
       0,     0,     0,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
       0,     0,     0,     0,     0,   632,     0,     0,     0,     0,
       0,    63,    64,     0,     0,     0,    65,    66,    67,     0,
      68,     0,    69,    70,     4,    71,     5,     6,     0,     7,
       0,     0,     0,     9,    10,     0,     0,    11,    12,     0,
       0,    13,     0,     0,     0,     0,     0,     0,    14,    15,
       0,    16,    17,     0,    19,    20,    21,    22,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       0,    34,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,     0,    41,    42,     0,    43,     0,     0,     0,
      45,    46,    47,     0,     0,     0,     0,     0,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,     0,     0,     4,     0,     5,     6,     0,
       0,     0,     0,     0,    63,    64,     0,     0,     0,    65,
      66,    67,    13,    68,     0,    69,    70,     0,    71,    14,
      15,     0,     0,     0,     0,     0,     0,    21,    22,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,     0,     0,    35,    36,    37,     0,     0,     0,     0,
       0,     0,     0,     0,    41,     0,     0,     0,     0,     0,
       0,    45,    46,    47,     0,     0,     0,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,     0,     0,     0,     4,     0,     5,     6,
       0,     0,     0,     0,     0,    63,    64,     0,     0,     0,
      65,    66,    67,    13,    68,     0,   110,     0,     0,    71,
      14,    15,     0,     0,     0,     0,     0,     0,    21,    22,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,    41,     0,     0,     0,     0,
       0,     0,    45,    46,    47,     0,     0,     0,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,     0,     0,     0,     4,     0,     5,
       6,     0,     0,     0,     0,     0,    63,    64,     0,     0,
       0,    65,    66,    67,    13,    68,     0,   112,     0,     0,
      71,    14,    15,     0,     0,     0,     0,     0,     0,    21,
      22,     0,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,     0,     0,     0,    35,    36,    37,     0,     0,
       0,     0,     0,     0,     0,     0,    41,     0,     0,     0,
       0,     0,     0,    45,    46,    47,     0,     0,     0,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,     0,     0,     0,     4,     0,
       5,     6,     0,     0,     0,     0,     0,    63,    64,     0,
       0,     0,    65,    66,    67,    13,    68,     0,   138,     0,
       0,    71,    14,    15,     0,     0,     0,     0,     0,     0,
      21,    22,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,    41,     0,     0,
       0,     0,     0,     0,    45,    46,    47,     0,     0,     0,
       0,     0,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,     0,     0,     0,     4,
       0,     5,     6,     0,     0,   237,     0,     0,    63,    64,
       0,     0,     0,    65,    66,    67,    13,    68,     0,     0,
       0,     0,    71,    14,    15,     0,     0,     0,     0,     0,
       0,    21,    22,     0,    23,    24,    25,    26,    27,    28,
       0,     0,     0,     0,     0,     0,     0,    35,    36,    37,
       0,     0,     0,     0,     0,     0,     0,     0,    41,     0,
       0,     0,     0,     0,     0,    45,    46,    47,     0,     0,
       0,     0,     0,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,     0,     0,     0,
       4,     0,     5,     6,     0,     0,     0,     0,     0,    63,
      64,     0,     0,     0,    65,    66,    67,    13,    68,   247,
       0,     0,     0,    71,    14,    15,     0,     0,     0,     0,
       0,     0,    21,    22,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,     0,     0,     0,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,    41,
       0,     0,     0,     0,     0,     0,    45,    46,    47,     0,
       0,     0,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,     0,     0,
       0,     4,     0,     5,     6,     0,     0,   278,     0,     0,
      63,    64,     0,     0,     0,    65,    66,    67,    13,    68,
       0,     0,     0,     0,    71,    14,    15,     0,     0,     0,
       0,     0,     0,    21,    22,     0,    23,    24,    25,    26,
      27,    28,     0,     0,     0,     0,     0,     0,     0,    35,
      36,    37,     0,     0,     0,     0,     0,     0,     0,     0,
      41,     0,     0,     0,     0,     0,     0,    45,    46,    47,
       0,     0,     0,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,     0,
       0,     0,     4,     0,     5,     6,     0,     0,   350,     0,
       0,    63,    64,     0,     0,     0,    65,    66,    67,    13,
      68,     0,     0,     0,     0,    71,    14,    15,     0,     0,
       0,     0,     0,     0,    21,    22,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,     0,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
       0,    41,     0,     0,     0,     0,     0,     0,    45,    46,
      47,     0,     0,     0,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
       0,     0,     0,     4,     0,     5,     6,     0,     0,   435,
       0,     0,    63,    64,     0,     0,     0,    65,    66,    67,
      13,    68,     0,     0,     0,     0,    71,    14,    15,     0,
       0,     0,     0,     0,     0,    21,    22,     0,    23,    24,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
       0,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,     0,    41,     0,     0,     0,     0,     0,     0,    45,
      46,    47,     0,     0,     0,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,     0,     0,     0,     4,     0,     5,     6,     0,     0,
     437,     0,     0,    63,    64,     0,     0,     0,    65,    66,
      67,    13,    68,     0,     0,     0,     0,    71,    14,    15,
       0,     0,     0,     0,     0,     0,    21,    22,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,     0,    41,     0,     0,     0,     0,     0,     0,
      45,    46,    47,     0,     0,     0,     0,     0,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,     0,     0,     0,     4,     0,     5,     6,     0,
       0,   453,     0,     0,    63,    64,     0,     0,     0,    65,
      66,    67,    13,    68,     0,     0,     0,     0,    71,    14,
      15,     0,     0,     0,     0,     0,     0,    21,    22,     0,
      23,    24,    25,    26,    27,    28,     0,     0,     0,     0,
       0,     0,     0,    35,    36,    37,     0,     0,     0,     0,
       0,     0,     0,     0,    41,     0,     0,     0,     0,     0,
       0,    45,    46,    47,     0,     0,     0,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,     0,     0,     0,     4,     0,     5,     6,
       0,     0,   551,     0,     0,    63,    64,     0,     0,     0,
      65,    66,    67,    13,    68,     0,     0,     0,     0,    71,
      14,    15,     0,     0,     0,     0,     0,     0,    21,    22,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,    41,     0,     0,     0,     0,
       0,     0,    45,    46,    47,     0,     0,   187,   188,   189,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,   190,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    64,     0,     0,
       0,    65,    66,    67,     0,    68,     0,     0,     0,     0,
      71,   187,   188,   189,     0,     0,     0,     0,     0,   191,
     192,   193,   194,   195,   196,     0,     0,     0,     0,   197,
     198,     0,   199,   200,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   201,     0,     0,   190,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     202,     0,     0,   203,   609,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   187,   188,   189,     0,     0,
       0,   610,     0,   191,   192,   193,   194,   195,   196,     0,
       0,     0,     0,   197,   198,     0,   199,   200,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
       0,     0,   190,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   202,     0,     0,   203,     0,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   187,
     188,   189,     0,     0,     0,   214,     0,   191,   192,   193,
     194,   195,   196,     0,     0,     0,     0,   197,   198,     0,
     199,   200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,     0,     0,   190,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   202,     0,
       0,   203,     0,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   187,   188,   189,     0,     0,     0,   241,
       0,   191,   192,   193,   194,   195,   196,     0,     0,     0,
       0,   197,   198,     0,   199,   200,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   201,     0,     0,
     190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   202,     0,     0,   203,     0,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   187,   188,   189,
       0,     0,     0,   242,     0,   191,   192,   193,   194,   195,
     196,     0,     0,     0,     0,   197,   198,     0,   199,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,     0,     0,   190,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   202,     0,     0,   203,
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   187,   188,   189,     0,     0,     0,   275,     0,   191,
     192,   193,   194,   195,   196,     0,     0,     0,     0,   197,
     198,     0,   199,   200,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   201,     0,     0,   190,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     202,     0,     0,   203,     0,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   187,   188,   189,     0,     0,
     283,     0,     0,   191,   192,   193,   194,   195,   196,     0,
       0,     0,     0,   197,   198,     0,   199,   200,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
       0,     0,   190,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   202,     0,     0,   203,     0,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   187,
     188,   189,     0,     0,   371,     0,     0,   191,   192,   193,
     194,   195,   196,     0,     0,     0,     0,   197,   198,     0,
     199,   200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,     0,     0,   190,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   202,     0,
       0,   203,     0,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   187,   188,   189,     0,     0,   372,     0,
       0,   191,   192,   193,   194,   195,   196,     0,     0,     0,
       0,   197,   198,     0,   199,   200,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   201,     0,     0,
     190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   202,     0,     0,   203,     0,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   187,   188,   189,
       0,     0,   401,     0,     0,   191,   192,   193,   194,   195,
     196,     0,     0,     0,     0,   197,   198,     0,   199,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,     0,     0,   190,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   202,     0,     0,   203,
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   187,   188,   189,     0,     0,   404,     0,     0,   191,
     192,   193,   194,   195,   196,     0,     0,     0,     0,   197,
     198,     0,   199,   200,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   201,     0,     0,   190,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     202,     0,     0,   203,     0,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   187,   188,   189,     0,     0,
     408,     0,     0,   191,   192,   193,   194,   195,   196,     0,
       0,     0,     0,   197,   198,     0,   199,   200,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
       0,     0,   190,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   202,     0,     0,   203,     0,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   187,
     188,   189,     0,     0,   513,     0,     0,   191,   192,   193,
     194,   195,   196,     0,     0,     0,     0,   197,   198,     0,
     199,   200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,     0,     0,   190,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   202,     0,
       0,   203,     0,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   187,   188,   189,     0,     0,   655,     0,
       0,   191,   192,   193,   194,   195,   196,     0,     0,     0,
       0,   197,   198,     0,   199,   200,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   201,     0,     0,
     190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   202,     0,     0,   203,     0,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   187,   188,   189,
       0,     0,   667,     0,     0,   191,   192,   193,   194,   195,
     196,     0,     0,   365,     0,   197,   198,     0,   199,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,     0,     0,   190,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   202,     0,     0,   203,
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   187,   188,   189,     0,     0,     0,     0,     0,   191,
     192,   193,   194,   195,   196,     0,     0,     0,     0,   197,
     198,     0,   199,   200,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   201,     0,     0,   190,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     202,     0,     0,   203,   424,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   187,   188,   189,     0,     0,
       0,     0,     0,   191,   192,   193,   194,   195,   196,     0,
       0,   494,     0,   197,   198,     0,   199,   200,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
       0,     0,   190,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   202,     0,     0,   203,     0,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   187,
       0,   189,     0,     0,   190,     0,     0,   191,   192,   193,
     194,   195,   196,     0,     0,     0,     0,   197,   198,     0,
     199,   200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,     0,     0,   190,     0,     0,   191,
     192,   193,   194,   195,   196,     0,     0,     0,   202,   197,
     198,   203,     0,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   187,     0,   201,     0,     0,     0,     0,
       0,   191,   192,   193,   194,   195,   196,     0,     0,     0,
     202,   197,   198,     0,   199,   200,   205,   206,   207,   208,
     209,   210,   211,   212,   213,     0,     0,   201,     0,     0,
     190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   202,     0,     0,   203,     0,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,     0,     0,     0,
       0,     0,     0,     0,     0,   191,   192,   193,   194,   195,
     196,     0,     0,     0,     0,   197,   198,     0,   199,   200,
       0,     0,     0,     0,     0,     0,   190,     0,     0,     0,
       0,   201,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   190,     0,     0,   202,     0,     0,   203,
       0,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   191,   192,   193,   194,   195,   196,     0,     0,     0,
       0,   197,   198,     0,   199,   200,     0,     0,   191,   192,
     193,   194,   195,   196,     0,     0,     0,   201,   197,   198,
       0,   199,   200,     0,     0,     0,     0,     0,     0,   190,
       0,     0,   202,     0,   201,   203,     0,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   190,     0,   202,
       0,     0,     0,     0,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   191,   192,   193,   194,   195,   196,
       0,     0,     0,     0,   197,   198,     0,     0,   200,     0,
       0,     0,   191,   192,   193,   194,   195,   196,     0,     0,
     201,     0,   197,   198,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   190,     0,   202,     0,     0,   201,     0,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     190,     0,     0,   202,     0,     0,     0,     0,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,  -306,  -306,
    -306,  -306,   195,   196,     0,     0,     0,     0,   197,   198,
       0,     0,     0,     0,     0,   191,   192,   193,   194,   195,
     196,     0,     0,     0,   201,   197,   198,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   202,
       0,   201,     0,     0,     0,     0,     0,   207,   208,   209,
     210,   211,   212,   213,     0,     0,   202,     0,     0,     0,
       0,     0,     0,     0,   207,   208,   209,   210,   211,   212,
     213
};

static const yytype_int16 yycheck[] =
{
       2,    25,   190,    81,    25,   263,    25,   186,   229,     9,
     457,     9,    87,    12,    25,    12,   463,   237,    17,    14,
      17,   406,   110,   111,    48,    49,    42,   474,    40,   470,
     117,   110,   111,    43,   110,   111,   117,   109,   120,     0,
     261,   267,   110,   111,   123,   135,   117,   111,    29,   136,
     138,   230,   140,    48,   111,   137,   137,    52,   278,    29,
     135,   140,    57,   135,   140,   136,    61,    62,    63,    64,
     138,   117,   140,   117,   515,    77,   517,   111,    48,    49,
     111,   260,   135,   140,   263,    14,   105,   120,    81,    82,
     135,   137,   116,   137,   110,   111,   135,   121,   277,   135,
     110,   111,   126,   127,    13,   138,   140,   110,   111,   140,
     110,   117,   110,    21,    22,   134,   128,   129,   130,    48,
     144,   117,   135,    52,   140,   110,   111,   135,    57,   514,
     140,   137,    61,    62,    63,    64,   136,   140,   110,   111,
     139,   137,   139,   117,   139,    12,   116,    12,    21,    22,
      17,   121,    17,   600,   117,   140,   126,   127,   117,   385,
     386,    28,   136,    28,   611,    13,   190,   186,   140,   190,
     135,   190,   117,   136,   144,   186,   111,   136,   117,   190,
     627,   111,   402,   409,   165,   632,    40,   138,   123,   636,
     138,   136,   134,   123,   175,   165,   138,   136,   135,   420,
     421,   135,   134,   135,   135,   175,   138,   135,   429,   135,
     139,   230,   134,   237,   135,   435,   138,   437,   123,   230,
     446,   137,   138,    40,   450,    79,    80,    48,    49,   676,
     110,    85,    86,   453,   134,   135,   110,   425,   138,   497,
     460,   260,    87,   135,   263,    84,    87,   101,   229,   260,
     135,    87,   263,     6,   278,     8,     9,    84,   277,   229,
     137,   118,   116,   109,   135,   137,   277,   237,    35,    87,
     124,   125,   126,   127,   128,   129,   130,   136,    40,    53,
     261,    48,   306,    67,   101,   110,   110,    32,   117,   136,
      57,   261,   311,   519,    61,    62,    63,    64,   136,   116,
     135,    54,    55,    56,   111,   136,   117,   137,   278,   126,
     127,   128,   129,   130,   136,   135,    10,   117,   497,    72,
      73,    74,   135,   137,    81,    82,   350,   118,   554,   135,
     556,   551,    32,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   110,   138,   135,   135,   118,   136,
     135,   375,   135,   377,   378,   141,   109,   110,   136,   112,
     113,   118,    87,   118,   137,   136,   110,   391,    60,   117,
     135,    84,   110,   126,   127,    83,   137,   137,   402,   403,
     350,   137,   118,   137,   111,   136,   138,   136,   412,   136,
     414,   617,    83,   117,   620,   621,   136,   136,   141,   401,
     626,   425,   404,   136,   425,   375,   425,   377,   378,   411,
     136,   435,   117,   437,   425,   137,   136,   398,   111,   645,
     110,   391,    35,   135,   650,   111,   137,   136,   398,   453,
     137,   137,   402,   403,   118,   661,   460,   118,   664,   420,
     421,   118,   110,    83,   120,    27,   135,   673,   429,   137,
     420,   421,   118,   111,   110,   118,   480,   137,   482,   429,
     135,   118,   111,   118,   137,   435,   118,   437,   135,   120,
     111,   181,   137,   558,     7,   136,     9,   136,   497,    12,
     541,   640,     2,   453,   508,   391,   497,     2,    21,    22,
     460,   588,   480,    26,    27,    28,    29,   461,   565,   508,
     608,   579,   580,   675,   581,   528,    10,   542,    41,   487,
      43,   252,   501,   121,   231,   377,   431,    50,    51,    52,
      53,    54,    55,    56,    -1,   378,    -1,   551,    -1,    -1,
      63,    64,    65,    66,    67,    68,    -1,    -1,   508,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   385,   386,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   559,    -1,    -1,
      -1,    -1,   564,   565,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   409,    -1,    -1,    -1,   109,    81,    82,    -1,
      -1,   551,    -1,    -1,   117,   118,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    -1,    -1,    -1,
      -1,    -1,    -1,   605,   682,   683,    -1,    -1,    -1,   446,
      -1,    -1,    -1,   450,   118,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   165,    -1,    -1,   659,    -1,    -1,    -1,    -1,
     173,   174,   175,   176,    -1,   178,   179,    -1,    -1,    -1,
      -1,    -1,    -1,   655,   187,   188,   189,    -1,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,    -1,   519,    -1,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,    -1,    -1,    -1,
     233,   234,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     243,    -1,    -1,    -1,    -1,    -1,   249,   554,    -1,   556,
      81,    82,    -1,    -1,     3,     4,     5,    -1,   261,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   137,    -1,    -1,    -1,
     617,    -1,    -1,   620,   621,    -1,    -1,    -1,    -1,   626,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,   645,    88,
      89,    -1,    -1,   650,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   354,   101,    -1,   661,    -1,    -1,   664,    -1,     3,
       4,     5,   365,    -1,   367,    -1,   673,   116,    -1,    -1,
     119,    -1,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,    -1,    -1,    -1,   398,    40,    -1,    -1,    -1,
      -1,    -1,   405,   406,   407,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   420,   421,    -1,
      -1,   424,    -1,    -1,    -1,    -1,   429,    -1,   431,   432,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
     443,    85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,
      -1,    81,    82,     3,     4,     5,    -1,   101,    -1,    -1,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,    -1,   116,    -1,    -1,   119,    -1,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   117,   118,    -1,
      40,   494,    -1,    -1,    -1,   139,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   136,    -1,    -1,    -1,
      -1,   514,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,   119,
     573,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,    -1,    -1,     3,     4,     5,    -1,    -1,    -1,   139,
      75,    76,    77,    78,    79,    80,   599,    -1,    -1,    -1,
      85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,   628,    -1,    -1,    -1,    -1,
      -1,   116,    -1,    -1,   119,    -1,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,    -1,    -1,     3,     4,
       5,    -1,    40,    -1,   139,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    -1,    40,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,   116,    85,    86,   119,
      -1,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,   139,
      75,    76,    77,    78,    79,    80,    -1,    -1,   116,    -1,
      85,    86,    -1,    88,    89,   123,   124,   125,   126,   127,
     128,   129,   130,    -1,    -1,    -1,   101,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   116,    -1,    -1,   119,    -1,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,     6,    -1,     8,     9,
      -1,    11,    -1,    13,   139,    15,    16,    -1,    -1,    19,
      20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    -1,    53,    54,    55,    56,    57,    -1,    59,
      -1,    -1,    -1,    -1,    64,    65,    66,    -1,    68,    -1,
      -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,    81,
      82,    81,    82,    -1,    -1,    -1,    -1,    -1,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   117,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   126,   127,    -1,    -1,
      -1,   131,   132,   133,   136,   135,    -1,   137,   138,   139,
     140,     6,    -1,     8,     9,    -1,    11,    -1,    13,    -1,
      15,    16,    -1,    -1,    19,    20,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    -1,    33,    34,
      35,    36,    37,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    57,    -1,    59,    -1,    -1,    -1,    -1,    64,
      65,    66,    -1,    68,    -1,    -1,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   126,   127,    -1,    -1,    -1,   131,   132,   133,    -1,
     135,    -1,   137,   138,     6,   140,     8,     9,    -1,    11,
      -1,    13,    -1,    15,    16,    -1,    -1,    19,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,    33,    34,    35,    36,    37,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    54,    55,    56,    57,    -1,    59,    -1,    -1,
      -1,    -1,    64,    65,    66,    -1,    68,    -1,    -1,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,   131,
     132,   133,    -1,   135,    -1,   137,   138,     6,   140,     8,
       9,    -1,    11,    -1,    13,    -1,    15,    16,    -1,    -1,
      19,    20,    -1,    -1,    23,    -1,    -1,    26,    -1,    -1,
      -1,    30,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    55,    56,    57,    -1,
      59,    -1,    -1,    -1,    -1,    64,    65,    66,    -1,    68,
      -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,   127,    -1,
      -1,    -1,   131,   132,   133,    -1,   135,    -1,   137,   138,
       6,   140,     8,     9,    -1,    11,    -1,    13,    -1,    15,
      16,    -1,    -1,    19,    20,    -1,    -1,    23,    -1,    25,
      -1,    -1,    -1,    -1,    30,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    54,    55,
      56,    57,    -1,    59,    -1,    -1,    -1,    -1,    64,    65,
      66,    -1,    68,    -1,    -1,    71,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     126,   127,    -1,    -1,    -1,   131,   132,   133,    -1,   135,
      -1,   137,   138,     6,   140,     8,     9,    -1,    11,    -1,
      13,    -1,    15,    16,    -1,    -1,    19,    20,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      33,    34,    35,    36,    37,    38,    39,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    54,    55,    56,    57,    -1,    59,    -1,    -1,    -1,
      -1,    64,    65,    66,    -1,    68,    -1,    -1,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   126,   127,    -1,    -1,    -1,   131,   132,
     133,    -1,   135,    -1,   137,   138,     6,   140,     8,     9,
      -1,    11,    -1,    13,    -1,    15,    16,    -1,    -1,    19,
      20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    -1,    53,    54,    55,    56,    57,    -1,    59,
      -1,    -1,    -1,    -1,    64,    65,    66,    -1,    68,    -1,
      -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   126,   127,    -1,    -1,
      -1,   131,   132,   133,    -1,   135,    -1,   137,   138,     6,
     140,     8,     9,    -1,    11,    -1,    -1,    -1,    15,    16,
      -1,    -1,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    -1,    33,    34,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    -1,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      -1,    68,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    -1,    -1,
      -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,
     127,    -1,    -1,    -1,   131,   132,   133,    -1,   135,    -1,
     137,   138,     6,   140,     8,     9,    -1,    11,    -1,    -1,
      -1,    15,    16,    -1,    -1,    19,    20,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    33,
      34,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    -1,    53,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    -1,    68,    -1,    -1,    -1,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,    -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,
      -1,    -1,   126,   127,    -1,    -1,    -1,   131,   132,   133,
      -1,   135,    -1,   137,   138,     6,   140,     8,     9,    -1,
      11,    -1,    -1,    -1,    15,    16,    -1,    -1,    19,    20,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,    33,    34,    -1,    36,    37,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    -1,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    -1,    68,    -1,    -1,
      -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,    -1,    -1,    -1,    -1,    -1,   120,
      -1,    -1,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,
     131,   132,   133,    -1,   135,    -1,   137,   138,     6,   140,
       8,     9,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,
      -1,    19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    33,    34,    -1,    36,    37,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    -1,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    -1,
      68,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,    -1,    -1,    -1,
      -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,   126,   127,
      -1,    -1,    -1,   131,   132,   133,    -1,   135,    -1,   137,
     138,     6,   140,     8,     9,    -1,    11,    -1,    -1,    -1,
      15,    16,    -1,    -1,    19,    20,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    33,    34,
      -1,    36,    37,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    -1,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    -1,    68,    -1,    -1,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
      -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,    -1,
      -1,   126,   127,    -1,    -1,    -1,   131,   132,   133,    -1,
     135,    -1,   137,   138,     6,   140,     8,     9,    -1,    11,
      -1,    -1,    -1,    15,    16,    -1,    -1,    19,    20,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,    33,    34,    -1,    36,    37,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    -1,    68,    -1,    -1,    -1,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,    -1,    -1,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,   131,
     132,   133,    23,   135,    -1,   137,   138,    -1,   140,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,    -1,    -1,    -1,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,
     131,   132,   133,    23,   135,    -1,   137,    -1,    -1,   140,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,    -1,    -1,    -1,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,   126,   127,    -1,    -1,
      -1,   131,   132,   133,    23,   135,    -1,   137,    -1,    -1,
     140,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    -1,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    -1,    -1,    -1,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,   126,   127,    -1,
      -1,    -1,   131,   132,   133,    23,   135,    -1,   137,    -1,
      -1,   140,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,    -1,    -1,    -1,     6,
      -1,     8,     9,    -1,    -1,   123,    -1,    -1,   126,   127,
      -1,    -1,    -1,   131,   132,   133,    23,   135,    -1,    -1,
      -1,    -1,   140,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    -1,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,    -1,    -1,    -1,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,   126,
     127,    -1,    -1,    -1,   131,   132,   133,    23,   135,   136,
      -1,    -1,    -1,   140,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,    -1,    -1,
      -1,     6,    -1,     8,     9,    -1,    -1,   123,    -1,    -1,
     126,   127,    -1,    -1,    -1,   131,   132,   133,    23,   135,
      -1,    -1,    -1,    -1,   140,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,    -1,
      -1,    -1,     6,    -1,     8,     9,    -1,    -1,   123,    -1,
      -1,   126,   127,    -1,    -1,    -1,   131,   132,   133,    23,
     135,    -1,    -1,    -1,    -1,   140,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    -1,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
      -1,    -1,    -1,     6,    -1,     8,     9,    -1,    -1,   123,
      -1,    -1,   126,   127,    -1,    -1,    -1,   131,   132,   133,
      23,   135,    -1,    -1,    -1,    -1,   140,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    -1,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,    -1,    -1,    -1,     6,    -1,     8,     9,    -1,    -1,
     123,    -1,    -1,   126,   127,    -1,    -1,    -1,   131,   132,
     133,    23,   135,    -1,    -1,    -1,    -1,   140,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,    -1,    -1,    -1,     6,    -1,     8,     9,    -1,
      -1,   123,    -1,    -1,   126,   127,    -1,    -1,    -1,   131,
     132,   133,    23,   135,    -1,    -1,    -1,    -1,   140,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,    -1,    -1,    -1,     6,    -1,     8,     9,
      -1,    -1,   123,    -1,    -1,   126,   127,    -1,    -1,    -1,
     131,   132,   133,    23,   135,    -1,    -1,    -1,    -1,   140,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    -1,    -1,     3,     4,     5,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   126,   127,    -1,    -1,
      -1,   131,   132,   133,    -1,   135,    -1,    -1,    -1,    -1,
     140,     3,     4,     5,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     116,    -1,    -1,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,     3,     4,     5,    -1,    -1,
      -1,   137,    -1,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,   119,    -1,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,     3,
       4,     5,    -1,    -1,    -1,   137,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,
      -1,   119,    -1,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,     3,     4,     5,    -1,    -1,    -1,   137,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,    -1,    -1,   119,    -1,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,     3,     4,     5,
      -1,    -1,    -1,   137,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,   119,
      -1,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,     3,     4,     5,    -1,    -1,    -1,   137,    -1,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     116,    -1,    -1,   119,    -1,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,     3,     4,     5,    -1,    -1,
     136,    -1,    -1,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,   119,    -1,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,     3,
       4,     5,    -1,    -1,   136,    -1,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,
      -1,   119,    -1,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,     3,     4,     5,    -1,    -1,   136,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,    -1,    -1,   119,    -1,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,     3,     4,     5,
      -1,    -1,   136,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,   119,
      -1,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,     3,     4,     5,    -1,    -1,   136,    -1,    -1,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     116,    -1,    -1,   119,    -1,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,     3,     4,     5,    -1,    -1,
     136,    -1,    -1,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,   119,    -1,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,     3,
       4,     5,    -1,    -1,   136,    -1,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,
      -1,   119,    -1,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,     3,     4,     5,    -1,    -1,   136,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,    -1,    -1,   119,    -1,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,     3,     4,     5,
      -1,    -1,   136,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    83,    -1,    85,    86,    -1,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,   119,
      -1,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,     3,     4,     5,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     116,    -1,    -1,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,     3,     4,     5,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    -1,
      -1,    83,    -1,    85,    86,    -1,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,   119,    -1,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,     3,
      -1,     5,    -1,    -1,    40,    -1,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    40,    -1,    -1,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,   116,    85,
      86,   119,    -1,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,     3,    -1,   101,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
     116,    85,    86,    -1,    88,    89,   122,   123,   124,   125,
     126,   127,   128,   129,   130,    -1,    -1,   101,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,    -1,    -1,   119,    -1,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,   116,    -1,    -1,   119,
      -1,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    -1,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,   101,    85,    86,
      -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,   116,    -1,   101,   119,    -1,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,    40,    -1,   116,
      -1,    -1,    -1,    -1,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    89,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
     101,    -1,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,   116,    -1,    -1,   101,    -1,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
      40,    -1,    -1,   116,    -1,    -1,    -1,    -1,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,   101,    85,    86,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,
      -1,   101,    -1,    -1,    -1,    -1,    -1,   124,   125,   126,
     127,   128,   129,   130,    -1,    -1,   116,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,   125,   126,   127,   128,   129,
     130
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   143,   144,     0,     6,     8,     9,    11,    13,    15,
      16,    19,    20,    23,    30,    31,    33,    34,    35,    36,
      37,    38,    39,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    53,    54,    55,    56,    57,    59,
      64,    65,    66,    68,    71,    72,    73,    74,    81,    82,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   126,   127,   131,   132,   133,   135,   137,
     138,   140,   145,   148,   149,   151,   152,   153,   154,   155,
     156,   157,   159,   162,   169,   170,   172,   174,   176,   178,
     217,   218,   219,   226,   229,   233,   234,   236,   237,   241,
     242,   243,   244,   245,   246,   251,   256,   258,   259,   135,
     137,   233,   137,   233,   214,   233,   135,   135,   135,   224,
     111,   140,   201,   202,   233,   233,   135,   135,   110,   219,
     220,   221,   244,   245,   251,   233,   233,   233,   137,   217,
     233,   237,   111,   203,   135,   109,   135,   168,    13,    13,
     233,   233,   135,   110,   219,   236,   237,   236,   233,   233,
     233,   233,   233,   233,   233,   135,   233,   233,   233,   233,
     233,   233,   146,   138,   135,   135,   135,   148,   135,   135,
     135,   259,   123,   171,   110,   110,    87,     3,     4,     5,
      40,    75,    76,    77,    78,    79,    80,    85,    86,    88,
      89,   101,   116,   119,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   137,    81,    82,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   118,   135,
      84,   238,   239,   134,   138,   140,   245,   123,   233,   254,
     255,   137,   137,   117,   137,   237,   233,   136,   233,   138,
     234,   237,   117,   137,   237,   257,    42,   237,   252,   253,
      87,   135,   225,    84,   245,   137,   137,   118,   117,   137,
     166,   167,   237,   109,   137,   137,   136,    87,   123,   199,
     200,   217,   237,   136,    71,   139,   147,   148,   169,   170,
     233,   233,   217,   237,   233,    53,   215,   216,   233,   233,
     110,   187,    67,   158,   110,   175,    32,   179,   110,   241,
     245,   251,   233,   233,   233,   220,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     123,   233,   199,   110,   138,   241,   248,   249,   250,   239,
     233,   247,   233,   235,   237,    83,   136,   117,   231,   233,
     136,   136,   136,   233,   202,   117,   136,   135,   117,   136,
     241,   199,   248,     9,   110,   126,   127,   226,   227,   228,
     111,   117,   136,   136,   137,   110,   235,   136,   117,   135,
     139,   136,    10,    10,   136,   135,   137,   117,   136,   118,
     117,   136,   135,   173,    32,   177,   110,   181,   219,   138,
     135,   135,   245,   139,   120,    43,   237,   136,   233,   135,
     240,   134,   138,   141,   139,   123,   233,   123,   233,   139,
     237,   252,   253,   118,   136,   222,   135,    87,   227,   227,
     118,   167,   137,   123,   217,   237,   136,   120,   148,   235,
     123,   183,   235,   120,   148,   191,   233,   215,   233,   120,
     138,   188,   227,   110,   120,   148,   186,   219,   135,   219,
      60,   180,   117,   204,   199,   199,   233,   220,   139,   199,
     247,   233,   235,   235,    83,   136,   233,    84,   223,   227,
     230,   232,   110,   227,   235,   137,   146,   192,    83,   182,
     235,   182,   146,   136,   137,   137,   189,   137,   189,   118,
     146,   111,     9,   110,   196,   197,   198,   181,   138,   219,
      14,    48,    52,    57,    61,    62,    63,    64,   139,   205,
     208,   209,   210,   211,   213,   136,   136,   225,   136,   141,
     139,   123,   233,   248,    83,   136,   117,   231,   193,    21,
      22,   150,   194,   183,   136,   136,    29,   137,   215,   189,
      12,    17,    28,   160,   161,   189,   139,   227,    24,   136,
     136,   117,   111,   123,   204,   110,   111,   212,   159,   211,
     117,   137,   235,   227,   227,    21,   150,   195,   148,   135,
     120,   148,   185,   185,   137,   136,    28,   137,   233,   120,
     137,   190,   139,   137,   259,   259,   198,   118,   111,   139,
     118,   118,   117,   137,   171,   110,    83,   120,   135,    27,
     233,   146,   120,   148,   184,   137,   190,   146,   158,   163,
     164,   165,   111,   123,   227,   118,   227,   227,   111,   110,
     118,   227,   146,   233,   137,   136,    26,   146,   146,   135,
     165,   118,   111,   227,   118,   206,   227,   136,   148,   137,
      25,   219,   227,   118,   227,   135,   120,   137,   111,   227,
     196,   146,   136,   136,   259,   137,   207,   259
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , context);
      fprintf (stderr, "\n");
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






/*----------.
| yyparse.  |
`----------*/

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
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 427 "src/generated_src/php_parser.ypp"
    {
			// If there are any remaining comments, add them as a NOP
			if(!context->last_comments.empty())
				(yyvsp[(1) - (1)].list_ast_statement)->push_back(NEW(AST_nop, ()));
	
			context->php_script = new AST_php_script((yyvsp[(1) - (1)].list_ast_statement));	
		;}
    break;

  case 3:
#line 438 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_statement)->push_back_all((yyvsp[(2) - (2)].list_ast_statement));
			(yyval.list_ast_statement) = (yyvsp[(1) - (2)].list_ast_statement);
		;}
    break;

  case 4:
#line 443 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<AST_statement*>;
		;}
    break;

  case 5:
#line 450 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement); 
		;}
    break;

  case 6:
#line 454 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (1)].ast_method));
		;}
    break;

  case 7:
#line 458 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (1)].ast_statement));
		;}
    break;

  case 8:
#line 462 "src/generated_src/php_parser.ypp"
    {
			assert(0);
		;}
    break;

  case 9:
#line 472 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_statement)->push_back_all((yyvsp[(2) - (2)].list_ast_statement));
			(yyval.list_ast_statement) = (yyvsp[(1) - (2)].list_ast_statement);
		;}
    break;

  case 10:
#line 477 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<AST_statement*>;
		;}
    break;

  case 11:
#line 484 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 12:
#line 488 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (1)].ast_method));
		;}
    break;

  case 13:
#line 492 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (1)].ast_statement));
		;}
    break;

  case 14:
#line 496 "src/generated_src/php_parser.ypp"
    {
			assert(0);
		;}
    break;

  case 15:
#line 503 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 16:
#line 514 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_if) = NEW(AST_if, (NULL, NULL, NULL));
		;}
    break;

  case 17:
#line 521 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_if) = NEW(AST_if, (NULL, NULL, NULL));
		;}
    break;

  case 18:
#line 528 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_foreach) = NEW(AST_foreach, (NULL, NULL, false, NULL, NULL));
		;}
    break;

  case 19:
#line 535 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_while) = NEW(AST_while, (NULL, NULL));
		;}
    break;

  case 20:
#line 542 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_do) = NEW(AST_do, (NULL, NULL));
		;}
    break;

  case 21:
#line 549 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_for) = NEW(AST_for, (NULL, NULL, NULL, NULL));
		;}
    break;

  case 22:
#line 556 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_switch) = NEW(AST_switch, (NULL, NULL));
		;}
    break;

  case 23:
#line 563 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_declare) = NEW(AST_declare, (NULL, NULL));
		;}
    break;

  case 24:
#line 570 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_try) = NEW(AST_try, (NULL, NULL));
		;}
    break;

  case 25:
#line 577 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_catch) = NEW(AST_catch, (NULL, NULL, NULL));
		;}
    break;

  case 26:
#line 584 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method) = NEW(AST_method, (NULL, NULL));
		;}
    break;

  case 27:
#line 591 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_switch_case) = NEW(AST_switch_case, (NULL, NULL));
		;}
    break;

  case 28:
#line 598 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_switch_case) = NEW(AST_switch_case, (NULL, NULL));
		;}
    break;

  case 29:
#line 606 "src/generated_src/php_parser.ypp"
    { 
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 30:
#line 610 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (7)].ast_if)->expr = (yyvsp[(3) - (7)].ast_expr);
			(yyvsp[(1) - (7)].ast_if)->iftrue = (yyvsp[(5) - (7)].list_ast_statement);
			
			if((yyvsp[(6) - (7)].ast_if))
			{
				List<AST_statement*>* new_false = new List<AST_statement*>;
				new_false->push_back((yyvsp[(6) - (7)].ast_if));
				
				/* 
				 * Nest the $6 part
				 *
				 * We must add it to the most deeply nested if we can find
				 * Note that _if_ any of the nested ifs (elseifs) has a false
				 * branch, then this consists of a single instruction, an AST_if*.
				 * So, the dynamic_cast is guaranteed to succeed.
				 *
				 * This is similar to the code in elseif_list. 
				 */ 
				while(!(yyvsp[(6) - (7)].ast_if)->iffalse->empty())
					(yyvsp[(6) - (7)].ast_if) = dynamic_cast<AST_if*>((yyvsp[(6) - (7)].ast_if)->iffalse->front());
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
#line 643 "src/generated_src/php_parser.ypp"
    {
			// Duplication of logic above for K_IF.
			
			(yyvsp[(1) - (10)].ast_if)->expr = (yyvsp[(3) - (10)].ast_expr);
			(yyvsp[(1) - (10)].ast_if)->iftrue = (yyvsp[(6) - (10)].list_ast_statement);
		
			if((yyvsp[(7) - (10)].ast_if))
			{
				List<AST_statement*>* new_false = new List<AST_statement*>;
				new_false->push_back((yyvsp[(7) - (10)].ast_if));

				while(!(yyvsp[(7) - (10)].ast_if)->iffalse->empty())
					(yyvsp[(7) - (10)].ast_if) = dynamic_cast<AST_if*>((yyvsp[(7) - (10)].ast_if)->iffalse->front());
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
#line 668 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (5)].ast_while)->expr = (yyvsp[(3) - (5)].ast_expr);
			(yyvsp[(1) - (5)].ast_while)->statements = (yyvsp[(5) - (5)].list_ast_statement);

			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (5)].ast_while));
		;}
    break;

  case 33:
#line 675 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (7)].ast_do)->statements = (yyvsp[(2) - (7)].list_ast_statement);
			(yyvsp[(1) - (7)].ast_do)->expr = (yyvsp[(5) - (7)].ast_expr);
			
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (7)].ast_do));
		;}
    break;

  case 34:
#line 682 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (9)].ast_for)->init = (yyvsp[(3) - (9)].ast_expr);
			(yyvsp[(1) - (9)].ast_for)->cond = (yyvsp[(5) - (9)].ast_expr);
			(yyvsp[(1) - (9)].ast_for)->incr = (yyvsp[(7) - (9)].ast_expr);
			(yyvsp[(1) - (9)].ast_for)->statements = (yyvsp[(9) - (9)].list_ast_statement);
			
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (9)].ast_for));
		;}
    break;

  case 35:
#line 691 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (5)].ast_switch)->expr = (yyvsp[(3) - (5)].ast_expr);
			(yyvsp[(1) - (5)].ast_switch)->switch_cases = (yyvsp[(5) - (5)].list_ast_switch_case);
			
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (5)].ast_switch));
		;}
    break;

  case 36:
#line 698 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(AST_break, (NULL)));
		;}
    break;

  case 37:
#line 702 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(AST_break, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 38:
#line 706 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(AST_continue, (NULL)));
		;}
    break;

  case 39:
#line 710 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(AST_continue, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 40:
#line 714 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(AST_return, (NULL)));
		;}
    break;

  case 41:
#line 718 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(AST_return, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 42:
#line 722 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(AST_return, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 43:
#line 726 "src/generated_src/php_parser.ypp"
    {
			List<AST_statement*>* globals = new List<AST_statement*>;
			List<AST_variable_name*>::const_iterator i;
			
			for(i = (yyvsp[(2) - (3)].list_ast_variable_name)->begin(); i != (yyvsp[(2) - (3)].list_ast_variable_name)->end(); i++)
			{
				AST_variable* gv = NEW(AST_variable, (*i)); // global var
				gv->target = NEW(Token_class_name, (new String("%MAIN%")));
				AST_variable_name* iclone = (*i)->clone();
				AST_variable* lv = NEW(AST_variable, (iclone)); // local var
				AST_assignment* gd = NEW(AST_assignment, (lv, true, gv)); // global declaration
				gd->attrs->set("phc.unparser.is_global_stmt", new Boolean(true));
				globals->push_back(NEW(AST_eval_expr, (gd)));
			}
		
			(yyval.list_ast_statement) = globals;
		;}
    break;

  case 44:
#line 744 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (3)].list_ast_statement);
		;}
    break;

  case 45:
#line 748 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (3)].list_ast_statement);
		;}
    break;

  case 46:
#line 752 "src/generated_src/php_parser.ypp"
    {
			Token_string* scalar = NEW(Token_string, ((yyvsp[(1) - (1)].string), (yyvsp[(1) - (1)].string)));
			AST_expr* fn = NEW(AST_method_invocation, ("echo", scalar));
	
			(yyval.list_ast_statement) = wrap(NEW(AST_eval_expr, (fn)));
		;}
    break;

  case 47:
#line 759 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(AST_eval_expr, ((yyvsp[(1) - (2)].ast_expr))));
		;}
    break;

  case 48:
#line 763 "src/generated_src/php_parser.ypp"
    {
			AST_method_invocation* fn = NEW(AST_method_invocation, ("use", (yyvsp[(2) - (3)].token_string)));
			
			(yyval.list_ast_statement) = wrap(NEW(AST_eval_expr, (fn)));
		;}
    break;

  case 49:
#line 769 "src/generated_src/php_parser.ypp"
    {
			List<AST_statement*>* statements = new List<AST_statement*>;
			List<AST_variable*>::const_iterator i;
			
			for(i = (yyvsp[(3) - (5)].list_ast_variable)->begin(); i != (yyvsp[(3) - (5)].list_ast_variable)->end(); i++)
				statements->push_back(NEW(AST_unset, (*i)));

			(yyval.list_ast_statement) = statements;
		;}
    break;

  case 50:
#line 779 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (8)].ast_foreach)->expr = (yyvsp[(3) - (8)].ast_expr);
			(yyvsp[(1) - (8)].ast_foreach)->statements = (yyvsp[(8) - (8)].list_ast_statement);
	
			if((yyvsp[(6) - (8)].ast_variable))
			{
				if((yyvsp[(5) - (8)].ast_variable)->attrs->is_true("phc.parser.is_ref"))
				{
					phc_error(ERR_FOREACH_KEY_REF, (yyvsp[(5) - (8)].ast_variable)->get_filename(), (yyvsp[(5) - (8)].ast_variable)->get_line_number());
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
#line 804 "src/generated_src/php_parser.ypp"
    { 
			// Duplication of the logic in the previous rule
			(yyvsp[(1) - (8)].ast_foreach)->expr = (yyvsp[(3) - (8)].ast_expr);
			(yyvsp[(1) - (8)].ast_foreach)->statements = (yyvsp[(8) - (8)].list_ast_statement);
	
			if((yyvsp[(6) - (8)].ast_variable))
			{
				if((yyvsp[(5) - (8)].ast_expr)->attrs->is_true("phc.parser.is_ref"))
				{
					phc_error(ERR_FOREACH_KEY_REF, (yyvsp[(5) - (8)].ast_expr)->get_filename(), (yyvsp[(5) - (8)].ast_expr)->get_line_number());
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
#line 830 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (5)].ast_declare)->directives = (yyvsp[(3) - (5)].list_ast_directive);
			(yyvsp[(1) - (5)].ast_declare)->statements = (yyvsp[(5) - (5)].list_ast_statement);

			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (5)].ast_declare));
		;}
    break;

  case 53:
#line 837 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<AST_statement*>;
		;}
    break;

  case 54:
#line 841 "src/generated_src/php_parser.ypp"
    { 
			Token_variable_name* var = new Token_variable_name((yyvsp[(6) - (9)].string));
			
			(yyvsp[(3) - (9)].ast_catch)->class_name = (yyvsp[(5) - (9)].token_class_name);
			(yyvsp[(3) - (9)].ast_catch)->variable_name = var;
			(yyvsp[(3) - (9)].ast_catch)->statements = (yyvsp[(8) - (9)].list_ast_statement);

			List<AST_catch*>* all_catches = new List<AST_catch*>;
			all_catches->push_back((yyvsp[(3) - (9)].ast_catch));
			all_catches->push_back_all((yyvsp[(9) - (9)].list_ast_catch));
		
			(yyvsp[(1) - (9)].ast_try)->statements = (yyvsp[(2) - (9)].list_ast_statement);
			(yyvsp[(1) - (9)].ast_try)->catches = all_catches;
		
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (9)].ast_try));
		;}
    break;

  case 55:
#line 858 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(AST_throw, ((yyvsp[(2) - (3)].ast_expr)))); 
		;}
    break;

  case 56:
#line 865 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_catch) = (yyvsp[(1) - (1)].list_ast_catch);
		;}
    break;

  case 57:
#line 869 "src/generated_src/php_parser.ypp"
    {
			List<AST_catch*>* catches = new List<AST_catch*>;
			(yyval.list_ast_catch) = catches; 
		;}
    break;

  case 58:
#line 877 "src/generated_src/php_parser.ypp"
    {
			List<AST_catch*>* catches = new List<AST_catch*>;
			catches->push_back((yyvsp[(1) - (1)].ast_catch));
			
			(yyval.list_ast_catch) = catches;
		;}
    break;

  case 59:
#line 884 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_catch)->push_back((yyvsp[(2) - (2)].ast_catch));
			
			(yyval.list_ast_catch) = (yyvsp[(1) - (2)].list_ast_catch); 
		;}
    break;

  case 60:
#line 893 "src/generated_src/php_parser.ypp"
    {
			Token_variable_name* var = new Token_variable_name((yyvsp[(4) - (6)].string));
			
			(yyvsp[(1) - (6)].ast_catch)->class_name = (yyvsp[(3) - (6)].token_class_name);
			(yyvsp[(1) - (6)].ast_catch)->variable_name = var;
			(yyvsp[(1) - (6)].ast_catch)->statements = (yyvsp[(6) - (6)].list_ast_statement);
			
			(yyval.ast_catch) = (yyvsp[(1) - (6)].ast_catch); 
		;}
    break;

  case 61:
#line 906 "src/generated_src/php_parser.ypp"
    {
			List<AST_variable*>* vars = new List<AST_variable*>;
			vars->push_back((yyvsp[(1) - (1)].ast_variable));
			(yyval.list_ast_variable) = vars;
		;}
    break;

  case 62:
#line 912 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_variable)->push_back((yyvsp[(3) - (3)].ast_variable));
			(yyval.list_ast_variable) = (yyvsp[(1) - (3)].list_ast_variable); 
		;}
    break;

  case 63:
#line 920 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = expect_variable((yyvsp[(1) - (1)].ast_expr));
		;}
    break;

  case 64:
#line 927 "src/generated_src/php_parser.ypp"
    {
			(yyval.token_string) = (yyvsp[(1) - (1)].token_string);	
		;}
    break;

  case 65:
#line 931 "src/generated_src/php_parser.ypp"
    {
			(yyval.token_string) = (yyvsp[(2) - (3)].token_string);	
		;}
    break;

  case 66:
#line 938 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method) = (yyvsp[(1) - (1)].ast_method);
		;}
    break;

  case 67:
#line 945 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_statement) = (yyvsp[(1) - (1)].ast_statement);
		;}
    break;

  case 68:
#line 952 "src/generated_src/php_parser.ypp"
    {
			(yyval.integer) = new Integer(0);
		;}
    break;

  case 69:
#line 956 "src/generated_src/php_parser.ypp"
    {
			(yyval.integer) = new Integer(1);
		;}
    break;

  case 70:
#line 962 "src/generated_src/php_parser.ypp"
    {context->current_method = dynamic_cast<String*>((yyvsp[(3) - (3)].string));;}
    break;

  case 71:
#line 963 "src/generated_src/php_parser.ypp"
    {
			Token_method_name* name = new Token_method_name((yyvsp[(3) - (8)].string));
		
			AST_signature* signature = NEW(AST_signature, (new AST_method_mod(), (yyvsp[(2) - (8)].integer)->value(), name, (yyvsp[(6) - (8)].list_ast_formal_parameter)));
			(yyvsp[(1) - (8)].ast_method)->signature = signature;
			(yyvsp[(1) - (8)].ast_method)->statements = (yyvsp[(8) - (8)].list_ast_statement);

			(yyval.ast_method) = (yyvsp[(1) - (8)].ast_method);
		;}
    break;

  case 72:
#line 975 "src/generated_src/php_parser.ypp"
    {context->current_class = dynamic_cast<String*>((yyvsp[(2) - (2)].string));;}
    break;

  case 73:
#line 976 "src/generated_src/php_parser.ypp"
    { 
			Token_class_name* name = new Token_class_name((yyvsp[(2) - (8)].string));

			(yyvsp[(1) - (8)].ast_class_def)->class_name = name;
			(yyvsp[(1) - (8)].ast_class_def)->extends = (yyvsp[(4) - (8)].token_class_name);
			(yyvsp[(1) - (8)].ast_class_def)->implements = (yyvsp[(5) - (8)].list_token_interface_name);
			(yyvsp[(1) - (8)].ast_class_def)->members = (yyvsp[(7) - (8)].list_ast_member);

			(yyval.ast_statement) = (yyvsp[(1) - (8)].ast_class_def);
		;}
    break;

  case 74:
#line 987 "src/generated_src/php_parser.ypp"
    {
			Token_interface_name* name = new Token_interface_name((yyvsp[(2) - (6)].string));

			(yyvsp[(1) - (6)].ast_interface_def)->interface_name = name;
			(yyvsp[(1) - (6)].ast_interface_def)->extends = (yyvsp[(3) - (6)].list_token_interface_name);
			(yyvsp[(1) - (6)].ast_interface_def)->members = (yyvsp[(5) - (6)].list_ast_member);
			
			(yyval.ast_statement) = (yyvsp[(1) - (6)].ast_interface_def);
		;}
    break;

  case 75:
#line 1010 "src/generated_src/php_parser.ypp"
    { 
			AST_class_mod* mod = NEW(AST_class_mod, (false, false));
			(yyval.ast_class_def) = NEW(AST_class_def, (mod));
		;}
    break;

  case 76:
#line 1015 "src/generated_src/php_parser.ypp"
    { 
			AST_class_mod* mod = NEW(AST_class_mod, (true, false)); 
			(yyval.ast_class_def) = NEW(AST_class_def, (mod));
		;}
    break;

  case 77:
#line 1020 "src/generated_src/php_parser.ypp"
    { 
			AST_class_mod* mod = NEW(AST_class_mod, (false, true)); 
			(yyval.ast_class_def) = NEW(AST_class_def, (mod));
		;}
    break;

  case 78:
#line 1028 "src/generated_src/php_parser.ypp"
    {
			(yyval.token_class_name) = NULL;
		;}
    break;

  case 79:
#line 1032 "src/generated_src/php_parser.ypp"
    {
			(yyval.token_class_name) = (yyvsp[(2) - (2)].token_class_name);
		;}
    break;

  case 80:
#line 1039 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_interface_def) = NEW(AST_interface_def, (NULL, NULL, NULL));
		;}
    break;

  case 81:
#line 1046 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_token_interface_name) = new List<Token_interface_name*>;
		;}
    break;

  case 82:
#line 1050 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_token_interface_name) = (yyvsp[(2) - (2)].list_token_interface_name);
		;}
    break;

  case 83:
#line 1060 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_token_interface_name) = new List<Token_interface_name*>;
		;}
    break;

  case 84:
#line 1064 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_token_interface_name) = (yyvsp[(2) - (2)].list_token_interface_name);
		;}
    break;

  case 85:
#line 1071 "src/generated_src/php_parser.ypp"
    {
			Token_interface_name* ifn = NEW(Token_interface_name, ((yyvsp[(1) - (1)].token_class_name)->value));
		
			List<Token_interface_name*>* names;
			names = new List<Token_interface_name*>;
			names->push_back(ifn);
			
			(yyval.list_token_interface_name) = names;
		;}
    break;

  case 86:
#line 1081 "src/generated_src/php_parser.ypp"
    {
			Token_interface_name* ifn = NEW(Token_interface_name, ((yyvsp[(3) - (3)].token_class_name)->value));
			(yyvsp[(1) - (3)].list_token_interface_name)->push_back(ifn);
			
			(yyval.list_token_interface_name) = (yyvsp[(1) - (3)].list_token_interface_name);
		;}
    break;

  case 87:
#line 1091 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = NULL;
		;}
    break;

  case 88:
#line 1095 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(2) - (2)].ast_variable);
		;}
    break;

  case 89:
#line 1102 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = expect_variable((yyvsp[(1) - (1)].ast_expr));
		;}
    break;

  case 90:
#line 1106 "src/generated_src/php_parser.ypp"
    { 
			(yyvsp[(2) - (2)].ast_expr)->attrs->set("phc.parser.is_ref", new Boolean(true));
			(yyval.ast_variable) = expect_variable((yyvsp[(2) - (2)].ast_expr)); 
		;}
    break;

  case 91:
#line 1114 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 92:
#line 1118 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (4)].list_ast_statement);
		;}
    break;

  case 93:
#line 1125 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 94:
#line 1129 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (4)].list_ast_statement);
		;}
    break;

  case 95:
#line 1136 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 96:
#line 1140 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (4)].list_ast_statement);
		;}
    break;

  case 97:
#line 1147 "src/generated_src/php_parser.ypp"
    {
			Token_directive_name* name = new Token_directive_name((yyvsp[(1) - (3)].string));

			List<AST_directive*>* dirs = new List<AST_directive*>;
			AST_directive* dir = NEW(AST_directive, (name, (yyvsp[(3) - (3)].ast_expr)));
			
			dirs->push_back(dir);
			(yyval.list_ast_directive) = dirs;
		;}
    break;

  case 98:
#line 1157 "src/generated_src/php_parser.ypp"
    {
			Token_directive_name* name = new Token_directive_name((yyvsp[(3) - (5)].string));	
			
			AST_directive* dir = NEW(AST_directive, (name, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].list_ast_directive)->push_back(dir);
			(yyval.list_ast_directive) = (yyvsp[(1) - (5)].list_ast_directive);
		;}
    break;

  case 99:
#line 1168 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = (yyvsp[(2) - (3)].list_ast_switch_case);
		;}
    break;

  case 100:
#line 1172 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = (yyvsp[(3) - (4)].list_ast_switch_case);
		;}
    break;

  case 101:
#line 1176 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = (yyvsp[(2) - (4)].list_ast_switch_case);
		;}
    break;

  case 102:
#line 1180 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = (yyvsp[(3) - (5)].list_ast_switch_case);
		;}
    break;

  case 103:
#line 1187 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = new List<AST_switch_case*>;
		;}
    break;

  case 104:
#line 1191 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (5)].ast_switch_case)->statements = (yyvsp[(5) - (5)].list_ast_statement);
			(yyvsp[(2) - (5)].ast_switch_case)->expr = (yyvsp[(3) - (5)].ast_expr);
			
			(yyvsp[(1) - (5)].list_ast_switch_case)->push_back((yyvsp[(2) - (5)].ast_switch_case));
			
			(yyval.list_ast_switch_case) = (yyvsp[(1) - (5)].list_ast_switch_case);
		;}
    break;

  case 105:
#line 1200 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (4)].ast_switch_case)->statements = (yyvsp[(4) - (4)].list_ast_statement);
			(yyvsp[(2) - (4)].ast_switch_case)->expr = NULL;
			
			(yyvsp[(1) - (4)].list_ast_switch_case)->push_back((yyvsp[(2) - (4)].ast_switch_case));
			
			(yyval.list_ast_switch_case) = (yyvsp[(1) - (4)].list_ast_switch_case);
		;}
    break;

  case 108:
#line 1220 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 109:
#line 1224 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (4)].list_ast_statement);
		;}
    break;

  case 110:
#line 1231 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_if) = NULL;
		;}
    break;

  case 111:
#line 1235 "src/generated_src/php_parser.ypp"
    {
			List<AST_statement*>* empty = new List<AST_statement*>;
			
			(yyvsp[(2) - (6)].ast_if)->expr = (yyvsp[(4) - (6)].ast_expr);
			(yyvsp[(2) - (6)].ast_if)->iftrue = (yyvsp[(6) - (6)].list_ast_statement);
			(yyvsp[(2) - (6)].ast_if)->iffalse = empty;
			(yyvsp[(2) - (6)].ast_if)->attrs->set("phc.unparser.is_elseif", new Boolean(true));

			if((yyvsp[(1) - (6)].ast_if))
			{
				List<AST_statement*>* iffalse = new List<AST_statement*>;
				iffalse->push_back((yyvsp[(2) - (6)].ast_if));
				
				/*
				 * Nest the $1.
				 * This is similar to the code in unticked_statement for K_IF.
				 */
				AST_if* p = (yyvsp[(1) - (6)].ast_if);
				while(!p->iffalse->empty())
					p = dynamic_cast<AST_if*>(p->iffalse->front());
				p->iffalse = iffalse;		
						
				(yyval.ast_if) = (yyvsp[(1) - (6)].ast_if);
			}
			else
			{
				(yyval.ast_if) = (yyvsp[(2) - (6)].ast_if);
			}
		;}
    break;

  case 112:
#line 1271 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_if) = NULL;
		;}
    break;

  case 113:
#line 1275 "src/generated_src/php_parser.ypp"
    {
			List<AST_statement*>* empty = new List<AST_statement*>;
			
			(yyvsp[(2) - (7)].ast_if)->expr = (yyvsp[(4) - (7)].ast_expr);
			(yyvsp[(2) - (7)].ast_if)->iftrue = (yyvsp[(7) - (7)].list_ast_statement);
			(yyvsp[(2) - (7)].ast_if)->iffalse = empty;
			(yyvsp[(2) - (7)].ast_if)->attrs->set("phc.unparser.is_elseif", new Boolean(true));

			if((yyvsp[(1) - (7)].ast_if))
			{
				List<AST_statement*>* iffalse = new List<AST_statement*>;
				iffalse->push_back((yyvsp[(2) - (7)].ast_if));
				
				AST_if* p = (yyvsp[(1) - (7)].ast_if);
				while(!p->iffalse->empty())
					p = dynamic_cast<AST_if*>(p->iffalse->front());
				p->iffalse = iffalse;		
						
				(yyval.ast_if) = (yyvsp[(1) - (7)].ast_if);
			}
			else
			{
				(yyval.ast_if) = (yyvsp[(2) - (7)].ast_if);
			}
		;}
    break;

  case 114:
#line 1304 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<AST_statement*>;
		;}
    break;

  case 115:
#line 1308 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (2)].list_ast_statement);
		;}
    break;

  case 116:
#line 1318 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<AST_statement*>;
		;}
    break;

  case 117:
#line 1322 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(3) - (3)].list_ast_statement);
		;}
    break;

  case 118:
#line 1329 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (1)].list_ast_formal_parameter);
		;}
    break;

  case 119:
#line 1333 "src/generated_src/php_parser.ypp"
    { 
			List<AST_formal_parameter*>* params = new List<AST_formal_parameter*>;
			(yyval.list_ast_formal_parameter) = params;
		;}
    break;

  case 120:
#line 1344 "src/generated_src/php_parser.ypp"
    { 
			Token_variable_name* name = new Token_variable_name((yyvsp[(2) - (2)].string));
			
			List<AST_formal_parameter*>* params;
			
			params = new List<AST_formal_parameter*>;
			params->push_back(NEW(AST_formal_parameter, ((yyvsp[(1) - (2)].ast_type), name)));
			
			(yyval.list_ast_formal_parameter) = params; 
		;}
    break;

  case 121:
#line 1355 "src/generated_src/php_parser.ypp"
    { 
			Token_variable_name* name = new Token_variable_name((yyvsp[(3) - (3)].string));
			
			List<AST_formal_parameter*>* params;
			
			params = new List<AST_formal_parameter*>;
			params->push_back(NEW(AST_formal_parameter, ((yyvsp[(1) - (3)].ast_type), true, name)));
			
			(yyval.list_ast_formal_parameter) = params; 
		;}
    break;

  case 122:
#line 1366 "src/generated_src/php_parser.ypp"
    { 
			Token_variable_name* name = new Token_variable_name((yyvsp[(3) - (5)].string));
			
			List<AST_formal_parameter*>* params;
			
			params = new List<AST_formal_parameter*>;
			params->push_back(NEW(AST_formal_parameter, ((yyvsp[(1) - (5)].ast_type), true, name, (yyvsp[(5) - (5)].ast_expr))));
			
			(yyval.list_ast_formal_parameter) = params; 
		;}
    break;

  case 123:
#line 1377 "src/generated_src/php_parser.ypp"
    { 
			Token_variable_name* name = new Token_variable_name((yyvsp[(2) - (4)].string));
			
			List<AST_formal_parameter*>* params;
			
			params = new List<AST_formal_parameter*>;
			params->push_back(NEW(AST_formal_parameter, ((yyvsp[(1) - (4)].ast_type), false, name, (yyvsp[(4) - (4)].ast_expr))));
			
			(yyval.list_ast_formal_parameter) = params; 
		;}
    break;

  case 124:
#line 1388 "src/generated_src/php_parser.ypp"
    { 
			Token_variable_name* name = new Token_variable_name((yyvsp[(4) - (4)].string));
			
			(yyvsp[(1) - (4)].list_ast_formal_parameter)->push_back(NEW(AST_formal_parameter, ((yyvsp[(3) - (4)].ast_type), name)));
			
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (4)].list_ast_formal_parameter); 
		;}
    break;

  case 125:
#line 1396 "src/generated_src/php_parser.ypp"
    { 
			Token_variable_name* name = new Token_variable_name((yyvsp[(5) - (5)].string));
			
			(yyvsp[(1) - (5)].list_ast_formal_parameter)->push_back(NEW(AST_formal_parameter, ((yyvsp[(3) - (5)].ast_type), true, name)));
			
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (5)].list_ast_formal_parameter); 
		;}
    break;

  case 126:
#line 1404 "src/generated_src/php_parser.ypp"
    { 
			Token_variable_name* name = new Token_variable_name((yyvsp[(5) - (7)].string));
			
			(yyvsp[(1) - (7)].list_ast_formal_parameter)->push_back(NEW(AST_formal_parameter, ((yyvsp[(3) - (7)].ast_type), true, name, (yyvsp[(7) - (7)].ast_expr))));
			
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (7)].list_ast_formal_parameter); 
		;}
    break;

  case 127:
#line 1412 "src/generated_src/php_parser.ypp"
    { 
			Token_variable_name* name = new Token_variable_name((yyvsp[(4) - (6)].string));
			
			(yyvsp[(1) - (6)].list_ast_formal_parameter)->push_back(NEW(AST_formal_parameter, ((yyvsp[(3) - (6)].ast_type), false, name, (yyvsp[(6) - (6)].ast_expr))));
			
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (6)].list_ast_formal_parameter); 
		;}
    break;

  case 128:
#line 1423 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_type) = NEW(AST_type, (false, NULL));
		;}
    break;

  case 129:
#line 1427 "src/generated_src/php_parser.ypp"
    { 
			Token_class_name* class_name = new Token_class_name((yyvsp[(1) - (1)].string));
			(yyval.ast_type) = NEW(AST_type, (false, class_name)); 
		;}
    break;

  case 130:
#line 1432 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_type) = NEW(AST_type, (true, NULL));
		;}
    break;

  case 131:
#line 1439 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (1)].list_ast_actual_parameter);
		;}
    break;

  case 132:
#line 1443 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = new List<AST_actual_parameter*>;
		;}
    break;

  case 133:
#line 1450 "src/generated_src/php_parser.ypp"
    {
			List<AST_actual_parameter*>* list = new List<AST_actual_parameter*>;
			list->push_back(NEW(AST_actual_parameter, (false, (yyvsp[(1) - (1)].ast_expr))));
			(yyval.list_ast_actual_parameter) = list;
		;}
    break;

  case 134:
#line 1456 "src/generated_src/php_parser.ypp"
    {
			List<AST_actual_parameter*>* list = new List<AST_actual_parameter*>;
			list->push_back(NEW(AST_actual_parameter, (false, (yyvsp[(1) - (1)].ast_expr))));
			(yyval.list_ast_actual_parameter) = list;
		;}
    break;

  case 135:
#line 1462 "src/generated_src/php_parser.ypp"
    {
			List<AST_actual_parameter*>* list = new List<AST_actual_parameter*>;
			list->push_back(NEW(AST_actual_parameter, (true, (yyvsp[(2) - (2)].ast_expr))));
			(yyval.list_ast_actual_parameter) = list; 
		;}
    break;

  case 136:
#line 1468 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back(NEW(AST_actual_parameter, (false, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 137:
#line 1473 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back(NEW(AST_actual_parameter, (false, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 138:
#line 1478 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (4)].list_ast_actual_parameter)->push_back(NEW(AST_actual_parameter, (true, (yyvsp[(4) - (4)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (4)].list_ast_actual_parameter); 
		;}
    break;

  case 139:
#line 1486 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_variable_name)->push_back((yyvsp[(3) - (3)].ast_variable_name));
			(yyval.list_ast_variable_name) = (yyvsp[(1) - (3)].list_ast_variable_name);
		;}
    break;

  case 140:
#line 1491 "src/generated_src/php_parser.ypp"
    {
			List<AST_variable_name*>* list = new List<AST_variable_name*>;
			list->push_back((yyvsp[(1) - (1)].ast_variable_name));
			
			(yyval.list_ast_variable_name) = list;
		;}
    break;

  case 141:
#line 1501 "src/generated_src/php_parser.ypp"
    {
			Token_variable_name* var = new Token_variable_name((yyvsp[(1) - (1)].string));
			(yyval.ast_variable_name) = var; 
		;}
    break;

  case 142:
#line 1506 "src/generated_src/php_parser.ypp"
    { 
			(yyval.ast_variable_name) = NEW(AST_reflection, ((yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 143:
#line 1510 "src/generated_src/php_parser.ypp"
    { 
			(yyvsp[(3) - (4)].ast_expr)->attrs->set("phc.unparser.needs_curlies", new Boolean(true));
			(yyval.ast_variable_name) = NEW(AST_reflection, ((yyvsp[(3) - (4)].ast_expr)));
		;}
    break;

  case 144:
#line 1518 "src/generated_src/php_parser.ypp"
    {
			Token_variable_name* name = new Token_variable_name((yyvsp[(3) - (3)].string));
			
			AST_static_declaration* v = NEW(AST_static_declaration, (name, NULL));
			(yyvsp[(1) - (3)].list_ast_statement)->push_back(v);
			
			(yyval.list_ast_statement) = (yyvsp[(1) - (3)].list_ast_statement);
		;}
    break;

  case 145:
#line 1527 "src/generated_src/php_parser.ypp"
    {
			Token_variable_name* name = new Token_variable_name((yyvsp[(3) - (5)].string));

			AST_static_declaration* v = NEW(AST_static_declaration, (name, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].list_ast_statement)->push_back(v);
			
			(yyval.list_ast_statement) = (yyvsp[(1) - (5)].list_ast_statement);
		;}
    break;

  case 146:
#line 1536 "src/generated_src/php_parser.ypp"
    {
			Token_variable_name* name = new Token_variable_name((yyvsp[(1) - (1)].string));
			
			List<AST_statement*>* list = new List<AST_statement*>;
			AST_static_declaration* v = NEW(AST_static_declaration, (name, NULL));
			list->push_back(v);
			
			(yyval.list_ast_statement) = list;
		;}
    break;

  case 147:
#line 1546 "src/generated_src/php_parser.ypp"
    {
			Token_variable_name* name = new Token_variable_name((yyvsp[(1) - (3)].string));
			
			List<AST_statement*>* list = new List<AST_statement*>;
			AST_static_declaration* v = NEW(AST_static_declaration, (name, (yyvsp[(3) - (3)].ast_expr)));
			list->push_back(v);

			(yyval.list_ast_statement) = list;
		;}
    break;

  case 148:
#line 1559 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_member)->push_back_all((yyvsp[(2) - (2)].list_ast_member));
			
			(yyval.list_ast_member) = (yyvsp[(1) - (2)].list_ast_member);			
		;}
    break;

  case 149:
#line 1565 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_member) = new List<AST_member*>;
		;}
    break;

  case 150:
#line 1572 "src/generated_src/php_parser.ypp"
    {
			List<AST_member*>::iterator i;
			for(i = (yyvsp[(2) - (3)].list_ast_member)->begin(); i != (yyvsp[(2) - (3)].list_ast_member)->end(); i++)
			{
				AST_attribute* attribute = dynamic_cast<AST_attribute*>(*i);
				assert(attribute != NULL);
				attribute->attr_mod = (yyvsp[(1) - (3)].ast_attr_mod)->clone();
			}

			(yyval.list_ast_member) = (yyvsp[(2) - (3)].list_ast_member);
		;}
    break;

  case 151:
#line 1584 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_member) = (yyvsp[(1) - (2)].list_ast_member);
		;}
    break;

  case 152:
#line 1587 "src/generated_src/php_parser.ypp"
    {context->current_method = dynamic_cast<String*>((yyvsp[(4) - (4)].string));;}
    break;

  case 153:
#line 1588 "src/generated_src/php_parser.ypp"
    {
			Token_method_name* name = new Token_method_name((yyvsp[(4) - (9)].string));
		
			AST_signature* signature = NEW(AST_signature, ((yyvsp[(1) - (9)].ast_method_mod), (yyvsp[(3) - (9)].integer)->value(), name, (yyvsp[(7) - (9)].list_ast_formal_parameter)));
			
			List<AST_member*>* members = new List<AST_member*>;
			(yyvsp[(2) - (9)].ast_method)->signature = signature;
			(yyvsp[(2) - (9)].ast_method)->statements = (yyvsp[(9) - (9)].list_ast_statement);
			members->push_back((yyvsp[(2) - (9)].ast_method));
			
			(yyval.list_ast_member) = members;
		;}
    break;

  case 154:
#line 1604 "src/generated_src/php_parser.ypp"
    {
			// Abstract method
			(yyval.list_ast_statement) = NULL; 
		;}
    break;

  case 155:
#line 1609 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 156:
#line 1616 "src/generated_src/php_parser.ypp"
    {
			if((yyvsp[(1) - (1)].ast_method_mod)->is_abstract)
			{
				phc_error(ERR_ABSTRACT_VARS, (yyvsp[(1) - (1)].ast_method_mod)->get_filename(), (yyvsp[(1) - (1)].ast_method_mod)->get_line_number());
			}

			(yyval.ast_attr_mod) = NEW(AST_attr_mod, ((yyvsp[(1) - (1)].ast_method_mod))); 
		;}
    break;

  case 157:
#line 1625 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_attr_mod) = NEW(AST_attr_mod, (false, false, false, false, false));
		;}
    break;

  case 158:
#line 1632 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = new AST_method_mod();
		;}
    break;

  case 159:
#line 1636 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = (yyvsp[(1) - (1)].ast_method_mod);
		;}
    break;

  case 160:
#line 1643 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = (yyvsp[(1) - (1)].ast_method_mod);
		;}
    break;

  case 161:
#line 1647 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = NEW(AST_method_mod, ((yyvsp[(1) - (2)].ast_method_mod), (yyvsp[(2) - (2)].ast_method_mod))); 
		;}
    break;

  case 162:
#line 1654 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = AST_method_mod::new_PUBLIC();
		;}
    break;

  case 163:
#line 1658 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = AST_method_mod::new_PROTECTED();
		;}
    break;

  case 164:
#line 1662 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = AST_method_mod::new_PRIVATE();
		;}
    break;

  case 165:
#line 1666 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = AST_method_mod::new_STATIC();
		;}
    break;

  case 166:
#line 1670 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = AST_method_mod::new_ABSTRACT();
		;}
    break;

  case 167:
#line 1674 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = AST_method_mod::new_FINAL();
		;}
    break;

  case 168:
#line 1681 "src/generated_src/php_parser.ypp"
    {
			Token_variable_name* name = new Token_variable_name((yyvsp[(3) - (3)].string));
			
			AST_attribute* attr = NEW(AST_attribute, (new AST_attr_mod(), name, NULL));
			(yyvsp[(1) - (3)].list_ast_member)->push_back(attr);
			
			(yyval.list_ast_member) = (yyvsp[(1) - (3)].list_ast_member);
		;}
    break;

  case 169:
#line 1690 "src/generated_src/php_parser.ypp"
    {
			Token_variable_name* name = new Token_variable_name((yyvsp[(3) - (5)].string));
			
			AST_attribute* attr = NEW(AST_attribute, (new AST_attr_mod(), name, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].list_ast_member)->push_back(attr);

			(yyval.list_ast_member) = (yyvsp[(1) - (5)].list_ast_member);			
		;}
    break;

  case 170:
#line 1699 "src/generated_src/php_parser.ypp"
    {
			Token_variable_name* name = new Token_variable_name((yyvsp[(1) - (1)].string));
			List<AST_member*>* members = new List<AST_member*>;

			AST_attribute* attr = NEW(AST_attribute, (new AST_attr_mod(), name, NULL));	
			members->push_back(attr);

			(yyval.list_ast_member) = members;
		;}
    break;

  case 171:
#line 1709 "src/generated_src/php_parser.ypp"
    { 
			Token_variable_name* name = new Token_variable_name((yyvsp[(1) - (3)].string));
			List<AST_member*>* members = new List<AST_member*>;

			AST_attribute* attr = NEW(AST_attribute, (new AST_attr_mod(), name, (yyvsp[(3) - (3)].ast_expr)));
			members->push_back(attr);

			(yyval.list_ast_member) = members;
		;}
    break;

  case 172:
#line 1722 "src/generated_src/php_parser.ypp"
    {
			Token_variable_name* name = new Token_variable_name((yyvsp[(3) - (5)].string));

			AST_attribute* attr = NEW(AST_attribute, (AST_attr_mod::new_CONST(), name, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].list_ast_member)->push_back(attr);
			
			(yyval.list_ast_member) = (yyvsp[(1) - (5)].list_ast_member);
		;}
    break;

  case 173:
#line 1731 "src/generated_src/php_parser.ypp"
    {
			Token_variable_name* name = new Token_variable_name((yyvsp[(2) - (4)].string));
			List<AST_member*>* members = new List<AST_member*>;

			AST_attribute* attr = NEW(AST_attribute, (AST_attr_mod::new_CONST(), name, (yyvsp[(4) - (4)].ast_expr)));
			members->push_back(attr);

			(yyval.list_ast_member) = members;
		;}
    break;

  case 174:
#line 1747 "src/generated_src/php_parser.ypp"
    {
			AST_method_invocation* fn = NEW(AST_method_invocation, ("echo", (yyvsp[(3) - (3)].ast_expr)));
			(yyvsp[(1) - (3)].list_ast_statement)->push_back(NEW(AST_eval_expr, (fn)));
			
			(yyval.list_ast_statement) = (yyvsp[(1) - (3)].list_ast_statement);
		;}
    break;

  case 175:
#line 1754 "src/generated_src/php_parser.ypp"
    {
			List<AST_statement*>* echo_list = new List<AST_statement*>;
			
			AST_method_invocation* fn = NEW(AST_method_invocation, ("echo", (yyvsp[(1) - (1)].ast_expr)));
			echo_list->push_back(NEW(AST_eval_expr, (fn)));
			
			(yyval.list_ast_statement) = echo_list;
		;}
    break;

  case 176:
#line 1766 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NULL;
		;}
    break;

  case 177:
#line 1770 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr)
		;}
    break;

  case 178:
#line 1780 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = new AST_bin_op((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ",");
		;}
    break;

  case 179:
#line 1784 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 180:
#line 1791 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_list_assignment, ((yyvsp[(3) - (6)].ast_list_elements), (yyvsp[(6) - (6)].ast_expr)));
		;}
    break;

  case 181:
#line 1795 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_assignment, (expect_variable((yyvsp[(1) - (3)].ast_expr)), false, (yyvsp[(3) - (3)].ast_expr)));
		;}
    break;

  case 182:
#line 1799 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_assignment, (expect_variable((yyvsp[(1) - (4)].ast_expr)), true, (yyvsp[(4) - (4)].ast_expr)));
		;}
    break;

  case 183:
#line 1803 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_assignment, (expect_variable((yyvsp[(1) - (6)].ast_expr)), true, NEW(AST_new, ((yyvsp[(5) - (6)].ast_class_name), (yyvsp[(6) - (6)].list_ast_actual_parameter)))));
		;}
    break;

  case 184:
#line 1807 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_new, ((yyvsp[(2) - (3)].ast_class_name), (yyvsp[(3) - (3)].list_ast_actual_parameter)));
		;}
    break;

  case 185:
#line 1811 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_clone, ((yyvsp[(2) - (2)].ast_expr))); 
		;}
    break;

  case 186:
#line 1815 "src/generated_src/php_parser.ypp"
    {
			AST_variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));

			AST_expr* var_c;
			var_c = var->clone();
			
			AST_assignment* agn = NEW(AST_assignment, (var, false, NEW(AST_bin_op, (var_c, (yyvsp[(3) - (3)].ast_expr), "+"))));
			agn->attrs->set("phc.unparser.is_opeq", new Boolean(true));
			(yyval.ast_expr) = agn;
		;}
    break;

  case 187:
#line 1826 "src/generated_src/php_parser.ypp"
    {
			AST_variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));

			AST_expr* var_c;
			var_c = var->clone();
			
			AST_assignment* agn = NEW(AST_assignment, (var, false, NEW(AST_bin_op, (var_c, (yyvsp[(3) - (3)].ast_expr), "-"))));
			agn->attrs->set("phc.unparser.is_opeq", new Boolean(true));
			(yyval.ast_expr) = agn;
		;}
    break;

  case 188:
#line 1837 "src/generated_src/php_parser.ypp"
    {
			AST_variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));

			AST_expr* var_c;
			var_c = var->clone();
			
			AST_assignment* agn = NEW(AST_assignment, (var, false, NEW(AST_bin_op, (var_c, (yyvsp[(3) - (3)].ast_expr), "*"))));
			agn->attrs->set("phc.unparser.is_opeq", new Boolean(true));
			(yyval.ast_expr) = agn;
		;}
    break;

  case 189:
#line 1848 "src/generated_src/php_parser.ypp"
    {
			AST_variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			
			AST_expr* var_c;
			var_c = var->clone();
			
			AST_assignment* agn = NEW(AST_assignment, (var, false, NEW(AST_bin_op, (var_c, (yyvsp[(3) - (3)].ast_expr), "/"))));
			agn->attrs->set("phc.unparser.is_opeq", new Boolean(true));
			(yyval.ast_expr) = agn;
		;}
    break;

  case 190:
#line 1859 "src/generated_src/php_parser.ypp"
    {
			AST_variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			
			AST_expr* var_c;
			var_c = var->clone();
			
			AST_assignment* agn = NEW(AST_assignment, (var, false, NEW(AST_bin_op, (var_c, (yyvsp[(3) - (3)].ast_expr), "."))));
			agn->attrs->set("phc.unparser.is_opeq", new Boolean(true));
			(yyval.ast_expr) = agn;
		;}
    break;

  case 191:
#line 1870 "src/generated_src/php_parser.ypp"
    {
			AST_variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			
			AST_expr* var_c;
			var_c = var->clone();
			
			AST_assignment* agn = NEW(AST_assignment, (var, false, NEW(AST_bin_op, (var_c, (yyvsp[(3) - (3)].ast_expr), "%"))));
			agn->attrs->set("phc.unparser.is_opeq", new Boolean(true));
			(yyval.ast_expr) = agn;
		;}
    break;

  case 192:
#line 1881 "src/generated_src/php_parser.ypp"
    {
			AST_variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			
			AST_expr* var_c;
			var_c = var->clone();
			
			AST_assignment* agn = NEW(AST_assignment, (var, false, NEW(AST_bin_op, (var_c, (yyvsp[(3) - (3)].ast_expr), "&"))));
			agn->attrs->set("phc.unparser.is_opeq", new Boolean(true));
			(yyval.ast_expr) = agn;
		;}
    break;

  case 193:
#line 1892 "src/generated_src/php_parser.ypp"
    {
			AST_variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			
			AST_expr* var_c;
			var_c = var->clone();
			
			AST_assignment* agn = NEW(AST_assignment, (var, false, NEW(AST_bin_op, (var_c, (yyvsp[(3) - (3)].ast_expr), "|"))));
			agn->attrs->set("phc.unparser.is_opeq", new Boolean(true));
			(yyval.ast_expr) = agn;
		;}
    break;

  case 194:
#line 1903 "src/generated_src/php_parser.ypp"
    {
			AST_variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			
			AST_expr* var_c;
			var_c = var->clone();
			
			AST_assignment* agn = NEW(AST_assignment, (var, false, NEW(AST_bin_op, (var_c, (yyvsp[(3) - (3)].ast_expr), "^"))));
			agn->attrs->set("phc.unparser.is_opeq", new Boolean(true));
			(yyval.ast_expr) = agn;
		;}
    break;

  case 195:
#line 1914 "src/generated_src/php_parser.ypp"
    {
			AST_variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			
			AST_expr* var_c;
			var_c = var->clone();
			
			AST_assignment* agn = NEW(AST_assignment, (var, false, NEW(AST_bin_op, (var_c, (yyvsp[(3) - (3)].ast_expr), "<<"))));
			agn->attrs->set("phc.unparser.is_opeq", new Boolean(true));
			(yyval.ast_expr) = agn;
		;}
    break;

  case 196:
#line 1925 "src/generated_src/php_parser.ypp"
    {
			AST_variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			
			AST_expr* var_c;
			var_c = var->clone();
			
			AST_assignment* agn = NEW(AST_assignment, (var, false, NEW(AST_bin_op, (var_c, (yyvsp[(3) - (3)].ast_expr), ">>"))));
			agn->attrs->set("phc.unparser.is_opeq", new Boolean(true));
			(yyval.ast_expr) = agn;
		;}
    break;

  case 197:
#line 1936 "src/generated_src/php_parser.ypp"
    { 
			(yyval.ast_expr) = NEW(AST_post_op, (expect_variable((yyvsp[(1) - (2)].ast_expr)), "++"));
		;}
    break;

  case 198:
#line 1940 "src/generated_src/php_parser.ypp"
    { 
			(yyval.ast_expr) = NEW(AST_pre_op, (expect_variable((yyvsp[(2) - (2)].ast_expr)), "++"));
		;}
    break;

  case 199:
#line 1944 "src/generated_src/php_parser.ypp"
    { 
			(yyval.ast_expr) = NEW(AST_post_op, (expect_variable((yyvsp[(1) - (2)].ast_expr)), "--"));
		;}
    break;

  case 200:
#line 1948 "src/generated_src/php_parser.ypp"
    { 
			(yyval.ast_expr) = NEW(AST_pre_op, (expect_variable((yyvsp[(2) - (2)].ast_expr)), "--"));
		;}
    break;

  case 201:
#line 1952 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "||"));
		;}
    break;

  case 202:
#line 1956 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "&&"));
		;}
    break;

  case 203:
#line 1960 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "or"));
		;}
    break;

  case 204:
#line 1964 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "and"));
		;}
    break;

  case 205:
#line 1968 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "xor"));
		;}
    break;

  case 206:
#line 1972 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "|"));
		;}
    break;

  case 207:
#line 1976 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "&"));
		;}
    break;

  case 208:
#line 1980 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "^"));
		;}
    break;

  case 209:
#line 1984 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
		;}
    break;

  case 210:
#line 1988 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (4)].ast_expr), (yyvsp[(3) - (4)].ast_expr), "."));

			/*
			 * Interface with the lexer: return to in-string state 
			 */
			 
			context->return_to_complex_syntax();
		;}
    break;

  case 211:
#line 1998 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "+"));
		;}
    break;

  case 212:
#line 2002 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "-"));
		;}
    break;

  case 213:
#line 2006 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "*"));
		;}
    break;

  case 214:
#line 2010 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "/"));
		;}
    break;

  case 215:
#line 2014 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "%"));
		;}
    break;

  case 216:
#line 2018 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "<<"));
		;}
    break;

  case 217:
#line 2022 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ">>"));
		;}
    break;

  case 218:
#line 2026 "src/generated_src/php_parser.ypp"
    {
			// We ignore unary plus
			(yyval.ast_expr) = (yyvsp[(2) - (2)].ast_expr); 
		;}
    break;

  case 219:
#line 2031 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_unary_op, ((yyvsp[(2) - (2)].ast_expr), "-")); 
		;}
    break;

  case 220:
#line 2035 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_unary_op, ((yyvsp[(2) - (2)].ast_expr), "!")); 
		;}
    break;

  case 221:
#line 2039 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_unary_op, ((yyvsp[(2) - (2)].ast_expr), "~")); 
		;}
    break;

  case 222:
#line 2043 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "==="));
		;}
    break;

  case 223:
#line 2047 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "!=="));
		;}
    break;

  case 224:
#line 2051 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "=="));
		;}
    break;

  case 225:
#line 2055 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "!="));
		;}
    break;

  case 226:
#line 2059 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "<"));
		;}
    break;

  case 227:
#line 2063 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), "<="));
		;}
    break;

  case 228:
#line 2067 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ">"));
		;}
    break;

  case 229:
#line 2071 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_expr), ">="));
		;}
    break;

  case 230:
#line 2075 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_instanceof, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_class_name)));
		;}
    break;

  case 231:
#line 2079 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (3)].ast_expr)->attrs->set("phc.unparser.needs_brackets", new Boolean(true));
			
			(yyval.ast_expr) = (yyvsp[(2) - (3)].ast_expr);
		;}
    break;

  case 232:
#line 2085 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_conditional_expr, ((yyvsp[(1) - (5)].ast_expr), (yyvsp[(3) - (5)].ast_expr), (yyvsp[(5) - (5)].ast_expr))); 
		;}
    break;

  case 233:
#line 2089 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_method_invocation);
		;}
    break;

  case 234:
#line 2093 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_cast, ("int", (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 235:
#line 2097 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_cast, ("real", (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 236:
#line 2101 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_cast, ("string", (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 237:
#line 2105 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_cast, ("array", (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 238:
#line 2109 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_cast, ("object", (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 239:
#line 2113 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_cast, ("bool", (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 240:
#line 2117 "src/generated_src/php_parser.ypp"
    { 
			(yyval.ast_expr) = NEW(AST_cast, ("unset", (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 241:
#line 2121 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_method_invocation, ("exit", (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 242:
#line 2125 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_ignore_errors, ((yyvsp[(2) - (2)].ast_expr))); 
		;}
    break;

  case 243:
#line 2129 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 244:
#line 2133 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_array, ((yyvsp[(3) - (4)].list_ast_array_elem))); 
		;}
    break;

  case 245:
#line 2137 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_method_invocation, ("print", (yyvsp[(2) - (2)].ast_expr)));	
		;}
    break;

  case 246:
#line 2144 "src/generated_src/php_parser.ypp"
    {
			Token_method_name* fn = new Token_method_name((yyvsp[(1) - (4)].string));
		
			(yyval.ast_method_invocation) = NEW(AST_method_invocation, (NULL, fn, (yyvsp[(3) - (4)].list_ast_actual_parameter)));
		;}
    break;

  case 247:
#line 2150 "src/generated_src/php_parser.ypp"
    {
			Token_method_name* fn = new Token_method_name((yyvsp[(3) - (6)].string));

			(yyval.ast_method_invocation) = NEW(AST_method_invocation, ((yyvsp[(1) - (6)].token_class_name), fn, (yyvsp[(5) - (6)].list_ast_actual_parameter)));
		;}
    break;

  case 248:
#line 2156 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(AST_method_invocation, ((yyvsp[(1) - (6)].token_class_name), NEW(AST_reflection, ((yyvsp[(3) - (6)].ast_variable))), (yyvsp[(5) - (6)].list_ast_actual_parameter)));
		;}
    break;

  case 249:
#line 2160 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(AST_method_invocation, (NULL, NEW(AST_reflection, ((yyvsp[(1) - (4)].ast_variable))), (yyvsp[(3) - (4)].list_ast_actual_parameter)));
		;}
    break;

  case 250:
#line 2167 "src/generated_src/php_parser.ypp"
    {
			Token_class_name* name = new Token_class_name((yyvsp[(1) - (1)].string));
			(yyval.token_class_name) = name; 
		;}
    break;

  case 251:
#line 2175 "src/generated_src/php_parser.ypp"
    {
			Token_class_name* name = new Token_class_name((yyvsp[(1) - (1)].string));

			(yyval.ast_class_name) = name; 
		;}
    break;

  case 252:
#line 2181 "src/generated_src/php_parser.ypp"
    { 
			(yyval.ast_class_name) = NEW(AST_reflection, ((yyvsp[(1) - (1)].ast_variable))); 
		;}
    break;

  case 253:
#line 2192 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(3) - (4)].ast_variable)->target = (yyvsp[(1) - (4)].ast_variable);

			List<AST_variable*>::const_iterator i;
			for(i = (yyvsp[(4) - (4)].list_ast_variable)->begin(); i != (yyvsp[(4) - (4)].list_ast_variable)->end(); i++)
			{
				(*i)->target = (yyvsp[(3) - (4)].ast_variable);
				(yyvsp[(3) - (4)].ast_variable) = *i;
			}
			
			(yyval.ast_variable) = (yyvsp[(3) - (4)].ast_variable); 
		;}
    break;

  case 254:
#line 2205 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 255:
#line 2212 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_variable)->push_back((yyvsp[(2) - (2)].ast_variable));
			(yyval.list_ast_variable) = (yyvsp[(1) - (2)].list_ast_variable);
		;}
    break;

  case 256:
#line 2217 "src/generated_src/php_parser.ypp"
    { 
			List<AST_variable*>* vars = new List<AST_variable*>;
			(yyval.list_ast_variable) = vars;
		;}
    break;

  case 257:
#line 2225 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(2) - (2)].ast_variable);
		;}
    break;

  case 258:
#line 2235 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Token_int, (0L, new String("0")));
		;}
    break;

  case 259:
#line 2239 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Token_int, (0L, new String("0")));
		;}
    break;

  case 260:
#line 2243 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(2) - (3)].ast_expr);
		;}
    break;

  case 261:
#line 2250 "src/generated_src/php_parser.ypp"
    { 
			List<AST_actual_parameter*>* args = new List<AST_actual_parameter*>;
			
			(yyval.list_ast_actual_parameter) = args; 
		;}
    break;

  case 262:
#line 2256 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = (yyvsp[(2) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 263:
#line 2263 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_int); 
		;}
    break;

  case 264:
#line 2267 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Token_real, (atof((yyvsp[(1) - (1)].string)->c_str()), (yyvsp[(1) - (1)].string)));
		;}
    break;

  case 265:
#line 2271 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_string);	
		;}
    break;

  case 266:
#line 2275 "src/generated_src/php_parser.ypp"
    { 
			(yyval.ast_expr) = NEW(Token_bool, (false, (yyvsp[(1) - (1)].string)));
		;}
    break;

  case 267:
#line 2279 "src/generated_src/php_parser.ypp"
    { 
			(yyval.ast_expr) = NEW(Token_bool, (true, (yyvsp[(1) - (1)].string)));
		;}
    break;

  case 268:
#line 2283 "src/generated_src/php_parser.ypp"
    { 
			(yyval.ast_expr) = NEW(Token_null, ((yyvsp[(1) - (1)].string)));
		;}
    break;

  case 269:
#line 2287 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Token_int, (context->source_line, new String("__LINE__")));
		;}
    break;

  case 270:
#line 2291 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Token_string, (context->filename, new String("__FILE__")));
		;}
    break;

  case 271:
#line 2295 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Token_string, (context->current_class, new String("__CLASS__")));
		;}
    break;

  case 272:
#line 2299 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Token_string, (context->current_method, new String("__METHOD__")));
		;}
    break;

  case 273:
#line 2303 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Token_string, (context->current_method, new String("__FUNCTION__")));
		;}
    break;

  case 274:
#line 2310 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 275:
#line 2314 "src/generated_src/php_parser.ypp"
    {
			Token_constant_name* name = new Token_constant_name((yyvsp[(1) - (1)].string));
			(yyval.ast_expr) = NEW(AST_constant, ("%MAIN%", name)); 
		;}
    break;

  case 276:
#line 2319 "src/generated_src/php_parser.ypp"
    {
			// We simply ignore the +
			(yyval.ast_expr) = (yyvsp[(2) - (2)].ast_expr);
		;}
    break;

  case 277:
#line 2324 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_unary_op, ((yyvsp[(2) - (2)].ast_expr), "-"));
		;}
    break;

  case 278:
#line 2328 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(AST_array, ((yyvsp[(3) - (4)].list_ast_array_elem)));
		;}
    break;

  case 279:
#line 2332 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_constant);
		;}
    break;

  case 280:
#line 2339 "src/generated_src/php_parser.ypp"
    {
			Token_class_name* class_name = new Token_class_name((yyvsp[(1) - (3)].string));
			Token_constant_name* constant = new Token_constant_name((yyvsp[(3) - (3)].string));
			
			(yyval.ast_constant) = NEW(AST_constant, (class_name, constant));
		;}
    break;

  case 281:
#line 2349 "src/generated_src/php_parser.ypp"
    {
			Token_constant_name* name = new Token_constant_name((yyvsp[(1) - (1)].string));

			(yyval.ast_expr) = NEW(AST_constant, ("%MAIN%", name));
		;}
    break;

  case 282:
#line 2355 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_constant);
		;}
    break;

  case 283:
#line 2359 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 284:
#line 2366 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_array_elem) = new List<AST_array_elem*>;
		;}
    break;

  case 285:
#line 2370 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (2)].list_ast_array_elem);
		;}
    break;

  case 288:
#line 2385 "src/generated_src/php_parser.ypp"
    {
			AST_array_elem* elem = NEW(AST_array_elem, ((yyvsp[(3) - (5)].ast_expr), false, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].list_ast_array_elem)->push_back(elem);

			(yyval.list_ast_array_elem) = (yyvsp[(1) - (5)].list_ast_array_elem);
		;}
    break;

  case 289:
#line 2392 "src/generated_src/php_parser.ypp"
    {
			AST_array_elem* elem = NEW(AST_array_elem, (NULL, false, (yyvsp[(3) - (3)].ast_expr)));
			(yyvsp[(1) - (3)].list_ast_array_elem)->push_back(elem);
			
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (3)].list_ast_array_elem);
		;}
    break;

  case 290:
#line 2399 "src/generated_src/php_parser.ypp"
    {
			List<AST_array_elem*>* list = new List<AST_array_elem*>;
			AST_array_elem* elem = NEW(AST_array_elem, ((yyvsp[(1) - (3)].ast_expr), false, (yyvsp[(3) - (3)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 291:
#line 2407 "src/generated_src/php_parser.ypp"
    {
			List<AST_array_elem*>* list = new List<AST_array_elem*>;
			AST_array_elem* elem = NEW(AST_array_elem, (NULL, false, (yyvsp[(1) - (1)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 292:
#line 2418 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 293:
#line 2422 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 294:
#line 2429 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 295:
#line 2436 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 296:
#line 2443 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 297:
#line 2467 "src/generated_src/php_parser.ypp"
    {
			List<AST_expr*>::iterator i;
			for(i = (yyvsp[(2) - (2)].list_ast_expr)->begin(); i != (yyvsp[(2) - (2)].list_ast_expr)->end(); i++)
			{
				AST_variable* var = dynamic_cast<AST_variable*>(*i);
				AST_method_invocation* fn = dynamic_cast<AST_method_invocation*>(*i);

				if(var)
				{
					var->target = (yyvsp[(1) - (2)].ast_expr);
					
					List<AST_actual_parameter*>* function_params = dynamic_cast<List<AST_actual_parameter*>*>(var->attrs->get("phc.parser.function_params"));
	
					if(function_params)
					{
						(yyvsp[(1) - (2)].ast_expr) = NEW(AST_method_invocation, (NULL, NEW(AST_reflection,(var)), function_params));
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

  case 298:
#line 2499 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 299:
#line 2510 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_expr)->push_back((yyvsp[(2) - (2)].ast_expr));
			
			(yyval.list_ast_expr) = (yyvsp[(1) - (2)].list_ast_expr);
		;}
    break;

  case 300:
#line 2516 "src/generated_src/php_parser.ypp"
    {
			List<AST_expr*>* props = new List<AST_expr*>;
			props->push_back((yyvsp[(1) - (1)].ast_expr));
			
			(yyval.list_ast_expr) = props;
		;}
    break;

  case 301:
#line 2545 "src/generated_src/php_parser.ypp"
    {
			if((yyvsp[(3) - (3)].list_ast_actual_parameter))
			{
				if((yyvsp[(2) - (3)].ast_variable)->array_indices->empty())
				{
					Token_variable_name* vn = dynamic_cast<Token_variable_name*>((yyvsp[(2) - (3)].ast_variable)->variable_name);
				
					if(vn)
					{
						Token_method_name* fn;
						
						fn = NEW(Token_method_name, (vn->value));
						(yyval.ast_expr) = NEW(AST_method_invocation, (NULL, fn, (yyvsp[(3) - (3)].list_ast_actual_parameter)));
					}
					else
					{
						AST_reflection* fn;

						fn = dynamic_cast<AST_reflection*>((yyvsp[(2) - (3)].ast_variable)->variable_name);
						assert(fn);
						(yyval.ast_expr) = NEW(AST_method_invocation, (NULL, fn, (yyvsp[(3) - (3)].list_ast_actual_parameter)));
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

  case 302:
#line 2583 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = (yyvsp[(2) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 303:
#line 2587 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = NULL;
		;}
    break;

  case 304:
#line 2594 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 305:
#line 2598 "src/generated_src/php_parser.ypp"
    {
			for(long i = 0; i < (yyvsp[(1) - (2)].integer)->value(); i++)
			{
				(yyvsp[(2) - (2)].ast_variable) = NEW(AST_variable, (NEW(AST_reflection, ((yyvsp[(2) - (2)].ast_variable)))));
			}
			
			(yyval.ast_variable) = (yyvsp[(2) - (2)].ast_variable);
		;}
    break;

  case 306:
#line 2610 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(3) - (3)].ast_variable)->target = (yyvsp[(1) - (3)].token_class_name);
			(yyval.ast_variable) = (yyvsp[(3) - (3)].ast_variable); 
		;}
    break;

  case 307:
#line 2618 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 308:
#line 2622 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_method_invocation);
		;}
    break;

  case 309:
#line 2629 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 310:
#line 2633 "src/generated_src/php_parser.ypp"
    {
			for(long i = 0; i < (yyvsp[(1) - (2)].integer)->value(); i++)
			{
				(yyvsp[(2) - (2)].ast_variable) = NEW(AST_variable, (NEW(AST_reflection, ((yyvsp[(2) - (2)].ast_variable)))));
			}

			(yyval.ast_variable) = (yyvsp[(2) - (2)].ast_variable);
		;}
    break;

  case 311:
#line 2642 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 312:
#line 2649 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (4)].ast_variable)->array_indices->push_back((yyvsp[(3) - (4)].ast_expr));
			(yyval.ast_variable) = (yyvsp[(1) - (4)].ast_variable);
		;}
    break;

  case 313:
#line 2654 "src/generated_src/php_parser.ypp"
    {
			if((yyvsp[(3) - (4)].ast_expr) != NULL)
				(yyvsp[(3) - (4)].ast_expr)->attrs->set("phc.unparser.index_curlies", new Boolean(true));

			(yyvsp[(1) - (4)].ast_variable)->array_indices->push_back((yyvsp[(3) - (4)].ast_expr));
			(yyval.ast_variable) = (yyvsp[(1) - (4)].ast_variable);
		;}
    break;

  case 314:
#line 2662 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = NEW(AST_variable, ((yyvsp[(1) - (1)].ast_variable_name)));
		;}
    break;

  case 315:
#line 2669 "src/generated_src/php_parser.ypp"
    { 
			Token_variable_name* var = new Token_variable_name((yyvsp[(1) - (1)].string));
			(yyval.ast_variable_name) = var; 
		;}
    break;

  case 316:
#line 2674 "src/generated_src/php_parser.ypp"
    { 
			(yyvsp[(3) - (4)].ast_expr)->attrs->set("phc.unparser.needs_curlies", new Boolean(true));
			(yyval.ast_variable_name) = NEW(AST_reflection, ((yyvsp[(3) - (4)].ast_expr))); 
		;}
    break;

  case 317:
#line 2682 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NULL;
		;}
    break;

  case 318:
#line 2686 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 319:
#line 2693 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 320:
#line 2697 "src/generated_src/php_parser.ypp"
    {
			// This is a "normal" variable (which includes a $), i.e. $x->$y
			// So, we need to add a level of indirection
			(yyval.ast_variable) = NEW(AST_variable, (NEW(AST_reflection, ((yyvsp[(1) - (1)].ast_variable))))); 
		;}
    break;

  case 321:
#line 2709 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (4)].ast_variable)->array_indices->push_back((yyvsp[(3) - (4)].ast_expr));
			(yyval.ast_variable) = (yyvsp[(1) - (4)].ast_variable);
		;}
    break;

  case 322:
#line 2714 "src/generated_src/php_parser.ypp"
    {
			if((yyvsp[(3) - (4)].ast_expr) != NULL)
				(yyvsp[(3) - (4)].ast_expr)->attrs->set("phc.unparser.index_curlies", new Boolean(true));

			(yyvsp[(1) - (4)].ast_variable)->array_indices->push_back((yyvsp[(3) - (4)].ast_expr));
			(yyval.ast_variable) = (yyvsp[(1) - (4)].ast_variable);
		;}
    break;

  case 323:
#line 2722 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = NEW(AST_variable, ((yyvsp[(1) - (1)].ast_variable_name))); 
		;}
    break;

  case 324:
#line 2732 "src/generated_src/php_parser.ypp"
    { 
			Token_variable_name* var = new Token_variable_name((yyvsp[(1) - (1)].string));
			(yyval.ast_variable_name) = var; 
		;}
    break;

  case 325:
#line 2737 "src/generated_src/php_parser.ypp"
    { 
			(yyvsp[(2) - (3)].ast_expr)->attrs->set("phc.unparser.needs_curlies", new Boolean(true));
			(yyval.ast_variable_name) = NEW(AST_reflection, ((yyvsp[(2) - (3)].ast_expr))); 
		;}
    break;

  case 326:
#line 2748 "src/generated_src/php_parser.ypp"
    {
			(yyval.integer) = new Integer(1);
		;}
    break;

  case 327:
#line 2752 "src/generated_src/php_parser.ypp"
    {
			(*(yyvsp[(1) - (2)].integer))++;
			(yyval.integer) = (yyvsp[(1) - (2)].integer); 
		;}
    break;

  case 328:
#line 2760 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].ast_list_elements)->list_elements->push_back((yyvsp[(3) - (3)].ast_list_element));
			
			(yyval.ast_list_elements) = (yyvsp[(1) - (3)].ast_list_elements); 
		;}
    break;

  case 329:
#line 2766 "src/generated_src/php_parser.ypp"
    {
			List<AST_list_element*>* elements = new List<AST_list_element*>;
			elements->push_back((yyvsp[(1) - (1)].ast_list_element));
			
			(yyval.ast_list_elements) = NEW(AST_list_elements, (elements)); 
		;}
    break;

  case 330:
#line 2779 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_list_element) = expect_variable((yyvsp[(1) - (1)].ast_expr)); 
		;}
    break;

  case 331:
#line 2783 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_list_element) = (yyvsp[(3) - (4)].ast_list_elements);
		;}
    break;

  case 332:
#line 2787 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_list_element) = NULL;
		;}
    break;

  case 333:
#line 2794 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_array_elem) = new List<AST_array_elem*>;
		;}
    break;

  case 334:
#line 2798 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (2)].list_ast_array_elem);
		;}
    break;

  case 335:
#line 2808 "src/generated_src/php_parser.ypp"
    {
			AST_array_elem* elem = NEW(AST_array_elem, ((yyvsp[(3) - (5)].ast_expr), false, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].list_ast_array_elem)->push_back(elem);

			(yyval.list_ast_array_elem) = (yyvsp[(1) - (5)].list_ast_array_elem);
		;}
    break;

  case 336:
#line 2815 "src/generated_src/php_parser.ypp"
    {
			AST_array_elem* elem = NEW(AST_array_elem, (NULL, false, (yyvsp[(3) - (3)].ast_expr)));
			(yyvsp[(1) - (3)].list_ast_array_elem)->push_back(elem);
			
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (3)].list_ast_array_elem);
		;}
    break;

  case 337:
#line 2822 "src/generated_src/php_parser.ypp"
    {
			List<AST_array_elem*>* list = new List<AST_array_elem*>;
			AST_array_elem* elem = NEW(AST_array_elem, ((yyvsp[(1) - (3)].ast_expr), false, (yyvsp[(3) - (3)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 338:
#line 2830 "src/generated_src/php_parser.ypp"
    {
			List<AST_array_elem*>* list = new List<AST_array_elem*>;
			AST_array_elem* elem = NEW(AST_array_elem, (NULL, false, (yyvsp[(1) - (1)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 339:
#line 2838 "src/generated_src/php_parser.ypp"
    {
			AST_array_elem* elem = 
				NEW(AST_array_elem, ((yyvsp[(3) - (6)].ast_expr), true, (yyvsp[(6) - (6)].ast_expr)));
			(yyvsp[(1) - (6)].list_ast_array_elem)->push_back(elem);

			(yyval.list_ast_array_elem) = (yyvsp[(1) - (6)].list_ast_array_elem);
		;}
    break;

  case 340:
#line 2846 "src/generated_src/php_parser.ypp"
    {
			AST_array_elem* elem = 
				NEW(AST_array_elem, (NULL, true, (yyvsp[(4) - (4)].ast_expr)));
			(yyvsp[(1) - (4)].list_ast_array_elem)->push_back(elem);
			
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (4)].list_ast_array_elem);
		;}
    break;

  case 341:
#line 2854 "src/generated_src/php_parser.ypp"
    {
			List<AST_array_elem*>* list = new List<AST_array_elem*>;
			AST_array_elem* elem = 
				NEW(AST_array_elem, ((yyvsp[(1) - (4)].ast_expr), true, (yyvsp[(4) - (4)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 342:
#line 2863 "src/generated_src/php_parser.ypp"
    {
			List<AST_array_elem*>* list = new List<AST_array_elem*>;
			AST_array_elem* elem = 
				NEW(AST_array_elem, (NULL, true, (yyvsp[(2) - (2)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 343:
#line 2875 "src/generated_src/php_parser.ypp"
    {
			Token_method_name* fn = NEW(Token_method_name, (new String("isset")));
			(yyval.ast_method_invocation) = NEW(AST_method_invocation, (NULL, fn, (yyvsp[(3) - (4)].list_ast_actual_parameter)));
		;}
    break;

  case 344:
#line 2880 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(AST_method_invocation, ("empty", (yyvsp[(3) - (4)].ast_expr)));
		;}
    break;

  case 345:
#line 2884 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(AST_method_invocation, ("include", (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 346:
#line 2888 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(AST_method_invocation, ("include_once", (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 347:
#line 2892 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(AST_method_invocation, ("eval", (yyvsp[(3) - (4)].ast_expr)));
		;}
    break;

  case 348:
#line 2896 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(AST_method_invocation, ("require", (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 349:
#line 2900 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(AST_method_invocation, ("require_once", (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 350:
#line 2907 "src/generated_src/php_parser.ypp"
    {
			List<AST_actual_parameter*>* params = new List<AST_actual_parameter*>;
			
			params->push_back(NEW(AST_actual_parameter, (false, (yyvsp[(1) - (1)].ast_expr))));
			(yyval.list_ast_actual_parameter) = params;
		;}
    break;

  case 351:
#line 2914 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back(NEW(AST_actual_parameter, (false, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 352:
#line 2922 "src/generated_src/php_parser.ypp"
    {
			Token_constant_name* constant = new Token_constant_name((yyvsp[(3) - (3)].string));

			(yyval.ast_constant) = NEW(AST_constant, ((yyvsp[(1) - (3)].token_class_name), constant));
		;}
    break;

  case 353:
#line 2935 "src/generated_src/php_parser.ypp"
    {
			// If there are any remaining comments, add them as a NOP
			if(!context->last_comments.empty())
				(yyvsp[(2) - (3)].list_ast_statement)->push_back(NEW(AST_nop, ()));

			(yyval.list_ast_statement) = (yyvsp[(2) - (3)].list_ast_statement);
		;}
    break;


/* Line 1267 of yacc.c.  */
#line 6520 "src/generated/php_parser.tab.cpp"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (context, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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



