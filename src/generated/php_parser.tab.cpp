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
     T_STRING = 364,
     IDENT = 365,
     VARIABLE = 366,
     T_INT = 367,
     T_REAL = 368,
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
#define T_STRING 364
#define IDENT 365
#define VARIABLE 366
#define T_INT 367
#define T_REAL 368
#define INLINE_HTML 369
#define INVALID_TOKEN 370




/* Copy the first part of user declarations.  */
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
#line 95 "src/generated_src/php_parser.ypp"
{
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
}
/* Line 187 of yacc.c.  */
#line 476 "src/generated/php_parser.tab.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 151 "src/generated_src/php_parser.ypp"

	int PHP_lex(YYSTYPE* yylval, void* scanner);
	#define scanner context->scanner


/* Line 216 of yacc.c.  */
#line 493 "src/generated/php_parser.tab.cpp"

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
#define YYLAST   5693

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  142
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  120
/* YYNRULES -- Number of rules.  */
#define YYNRULES  355
/* YYNRULES -- Number of states.  */
#define YYNSTATES  690

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
     836,   839,   842,   845,   848,   851,   853,   858,   861,   866,
     873,   880,   885,   887,   889,   891,   896,   898,   901,   902,
     905,   906,   909,   913,   914,   918,   920,   922,   924,   926,
     928,   930,   932,   934,   936,   938,   940,   942,   944,   947,
     950,   955,   957,   961,   963,   965,   967,   968,   971,   972,
     974,   980,   984,   988,   990,   992,   994,   996,   998,  1000,
    1003,  1005,  1008,  1010,  1014,  1018,  1019,  1021,  1024,  1028,
    1030,  1032,  1034,  1037,  1039,  1044,  1049,  1051,  1053,  1058,
    1059,  1061,  1063,  1065,  1070,  1075,  1077,  1079,  1083,  1085,
    1088,  1092,  1094,  1096,  1101,  1102,  1103,  1106,  1112,  1116,
    1120,  1122,  1129,  1134,  1139,  1142,  1147,  1152,  1155,  1158,
    1163,  1166,  1169,  1171,  1175,  1179
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
     235,    -1,   108,   235,    -1,    31,   226,    -1,   133,   235,
      -1,   231,    -1,     9,   135,   256,   136,    -1,    44,   235,
      -1,   110,   135,   200,   136,    -1,   221,    87,   110,   135,
     200,   136,    -1,   221,    87,   243,   135,   200,   136,    -1,
     243,   135,   200,   136,    -1,   110,    -1,   110,    -1,   223,
      -1,   246,    84,   250,   224,    -1,   246,    -1,   224,   225,
      -1,    -1,    84,   250,    -1,    -1,   135,   136,    -1,   135,
     235,   136,    -1,    -1,   135,   200,   136,    -1,   112,    -1,
     113,    -1,   109,    -1,    73,    -1,    72,    -1,    74,    -1,
       8,    -1,     6,    -1,    55,    -1,    56,    -1,    54,    -1,
     228,    -1,   110,    -1,   121,   229,    -1,   122,   229,    -1,
       9,   135,   232,   136,    -1,   230,    -1,   110,    87,   110,
      -1,   110,    -1,   260,    -1,   228,    -1,    -1,   234,   233,
      -1,    -1,   116,    -1,   234,   116,   229,    83,   229,    -1,
     234,   116,   229,    -1,   229,    83,   229,    -1,   229,    -1,
     236,    -1,   219,    -1,   239,    -1,   239,    -1,   239,    -1,
     245,   240,    -1,   245,    -1,   240,   241,    -1,   241,    -1,
      84,   250,   242,    -1,   135,   200,   136,    -1,    -1,   247,
      -1,   253,   247,    -1,   221,    87,   243,    -1,   246,    -1,
     220,    -1,   247,    -1,   253,   247,    -1,   244,    -1,   247,
     134,   249,   141,    -1,   247,   138,   235,   139,    -1,   248,
      -1,   111,    -1,   140,   138,   235,   139,    -1,    -1,   235,
      -1,   251,    -1,   243,    -1,   251,   134,   249,   141,    -1,
     251,   138,   235,   139,    -1,   252,    -1,   110,    -1,   138,
     235,   139,    -1,   140,    -1,   253,   140,    -1,   254,   116,
     255,    -1,   255,    -1,   239,    -1,    42,   135,   254,   136,
      -1,    -1,    -1,   257,   233,    -1,   257,   116,   235,    83,
     235,    -1,   257,   116,   235,    -1,   235,    83,   235,    -1,
     235,    -1,   257,   116,   235,    83,   118,   237,    -1,   257,
     116,   118,   237,    -1,   235,    83,   118,   237,    -1,   118,
     237,    -1,    41,   135,   259,   136,    -1,    23,   135,   239,
     136,    -1,    38,   235,    -1,    39,   235,    -1,    30,   135,
     235,   136,    -1,    45,   235,    -1,    46,   235,    -1,   239,
      -1,   259,   116,   239,    -1,   221,    87,   110,    -1,   138,
     146,   139,    -1
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
    2062,  2066,  2070,  2074,  2078,  2082,  2086,  2090,  2098,  2112,
    2118,  2122,  2129,  2137,  2143,  2154,  2167,  2174,  2180,  2187,
    2198,  2209,  2220,  2237,  2243,  2250,  2254,  2258,  2262,  2266,
    2270,  2274,  2278,  2282,  2286,  2290,  2297,  2301,  2306,  2311,
    2315,  2319,  2326,  2336,  2342,  2346,  2354,  2357,  2366,  2368,
    2372,  2379,  2386,  2394,  2405,  2409,  2416,  2423,  2430,  2454,
    2486,  2497,  2503,  2532,  2570,  2575,  2581,  2585,  2597,  2605,
    2609,  2616,  2620,  2629,  2636,  2641,  2649,  2656,  2661,  2670,
    2673,  2680,  2684,  2696,  2701,  2709,  2719,  2724,  2735,  2739,
    2747,  2753,  2766,  2770,  2775,  2782,  2785,  2795,  2802,  2809,
    2817,  2825,  2833,  2841,  2850,  2862,  2867,  2871,  2876,  2881,
    2885,  2890,  2898,  2905,  2913,  2926
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
  "unticked_function_declaration_statement", "@1",
  "unticked_class_declaration_statement", "@2", "@3", "class_entry_type",
  "extends_from", "interface_entry", "interface_extends_list",
  "implements_list", "interface_list", "foreach_optional_arg",
  "foreach_variable", "for_statement", "foreach_statement",
  "declare_statement", "declare_list", "switch_case_list", "case_list",
  "case_separator", "while_statement", "elseif_list", "new_elseif_list",
  "else_single", "new_else_single", "parameter_list",
  "non_empty_parameter_list", "optional_class_type",
  "function_call_parameter_list", "non_empty_function_call_parameter_list",
  "global_var_list", "global_var", "static_var_list",
  "class_statement_list", "class_statement", "@4", "@5", "method_body",
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
     219,   219,   219,   219,   219,   219,   219,   219,   220,   220,
     220,   220,   221,   222,   222,   223,   223,   224,   224,   225,
     226,   226,   226,   227,   227,   228,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   229,   229,   229,   229,
     229,   229,   230,   231,   231,   231,   232,   232,   233,   233,
     234,   234,   234,   234,   235,   235,   236,   237,   238,   239,
     239,   240,   240,   241,   242,   242,   243,   243,   244,   245,
     245,   246,   246,   246,   247,   247,   247,   248,   248,   249,
     249,   250,   250,   251,   251,   251,   252,   252,   253,   253,
     254,   254,   255,   255,   255,   256,   256,   257,   257,   257,
     257,   257,   257,   257,   257,   258,   258,   258,   258,   258,
     258,   258,   259,   259,   260,   261
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
       2,     2,     2,     2,     2,     1,     4,     2,     4,     6,
       6,     4,     1,     1,     1,     4,     1,     2,     0,     2,
       0,     2,     3,     0,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       4,     1,     3,     1,     1,     1,     0,     2,     0,     1,
       5,     3,     3,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     1,     3,     3,     0,     1,     2,     3,     1,
       1,     1,     2,     1,     4,     4,     1,     1,     4,     0,
       1,     1,     1,     4,     4,     1,     1,     3,     1,     2,
       3,     1,     1,     4,     0,     0,     2,     5,     3,     3,
       1,     6,     4,     4,     2,     4,     4,     2,     2,     4,
       2,     2,     1,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     2,     1,   272,   271,     0,     0,    76,     0,
      23,    20,     0,     0,     0,   260,    21,    18,    26,     0,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,     0,     0,    19,   275,   273,   274,     0,    81,
       0,     0,    24,     0,     0,   269,   268,   270,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   267,   283,   317,
     265,   266,    46,     0,     0,     0,     0,     0,     0,    53,
      10,   328,     3,     5,     0,     0,     0,     0,     0,     0,
       0,     0,    68,    15,     6,     7,    66,    67,     0,     0,
     295,   310,     0,   285,   245,     0,   294,     0,   296,     0,
     313,   300,   309,   311,   316,     0,   235,   284,    29,   335,
      36,     0,    38,     0,     0,   177,     0,     0,     0,   243,
     142,     0,     0,   141,   347,   348,     0,   334,   253,     0,
     263,   254,   256,   311,     0,   247,   350,   351,    40,   295,
       0,   296,   147,     0,     0,    64,     0,     0,    78,    77,
     187,     0,     0,   252,     0,   200,   298,   202,   236,   237,
     238,   239,   240,   241,   242,   133,   220,   221,   222,   223,
     244,     0,     0,     0,     0,     0,     0,     0,   178,     0,
       0,     0,    69,     0,    72,    82,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    47,   199,   201,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   133,
       0,   299,   302,   319,     0,   329,   312,     0,   340,     0,
     288,    37,    39,     0,    45,     0,     0,   261,     0,     0,
     143,   296,     0,    43,   352,     0,     0,   332,     0,   331,
       0,   133,   186,     0,   312,    41,    42,     0,     0,    44,
       0,    61,    63,     0,    48,    55,     0,     0,     0,     0,
     132,   295,   296,   233,     0,   355,     9,    11,    12,    13,
       0,     0,   295,   296,     0,     0,     0,   179,   181,     0,
       0,     0,    25,     0,    70,    79,     0,     0,   354,   308,
     306,     0,   206,   205,   207,   232,   226,   224,   227,   225,
     229,   231,   218,   219,   203,   204,     0,   208,   209,   210,
     211,   213,   214,   215,   216,   217,   228,   230,     0,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
       0,   183,     0,   326,     0,   322,   305,   321,   325,   301,
     320,     0,     0,   344,   297,     0,   246,   289,   336,   176,
     346,   349,   262,     0,   140,     0,   345,   334,   334,     0,
     308,     0,   258,     0,   277,     0,     0,   276,   148,   281,
     145,     0,     0,    65,     8,     0,   136,   248,     0,     0,
     318,     0,     0,     0,     0,     0,   178,     0,     0,     0,
       0,     0,     0,     0,     0,    84,   252,    83,    86,   150,
     133,   133,   307,   212,     0,     0,   184,   251,     0,   133,
     303,   319,     0,   314,   315,     0,   339,     0,   338,   144,
     353,     0,   330,     0,   264,   255,   286,     0,   278,   279,
       0,    62,    49,     0,   295,   296,     0,    10,   111,    88,
       0,    88,    90,    10,   109,    32,     0,     0,   180,   104,
     104,    35,    98,     0,    10,    96,    52,     0,   129,    80,
       0,     0,     0,   160,     0,     0,   234,   263,   327,     0,
       0,     0,   343,   342,     0,   333,   182,     0,   257,   293,
       0,   288,   282,   146,   139,    14,   113,   115,     0,     0,
      91,     0,     0,     0,   178,   104,     0,   104,     0,     0,
       0,     0,   131,   130,     0,   119,     0,    85,   150,    87,
       0,   167,   159,   169,   164,   166,   165,   168,    75,   149,
       0,     0,   158,   162,     0,   249,   250,   185,   304,   323,
     324,     0,   337,   259,     0,   280,   289,   287,   117,     0,
      17,     0,    30,    89,     0,     0,     0,    33,     0,     0,
      27,    28,     0,     0,     0,     0,   100,    99,     0,     0,
       0,   129,   121,     0,   160,     0,   172,     0,    68,   163,
       0,   152,   341,   292,   291,     0,     0,     0,   116,     0,
      10,    94,    51,    50,   110,     0,     0,   102,     0,   107,
     108,    10,   101,    97,    57,    71,     0,     0,   122,    73,
       0,     0,     0,   151,     0,     0,     0,    10,     0,     0,
       0,     0,    10,    92,    34,   103,    10,   106,     0,    54,
      56,    58,   125,     0,   124,     0,    74,   175,   173,   170,
     153,     0,   290,   118,     0,    31,     0,     0,     0,   105,
       0,    59,     0,   126,   123,     0,     0,   174,     0,   112,
      95,     0,     0,   128,     0,   171,   129,    10,    93,     0,
     127,     0,   114,     0,     0,    60,   156,   154,   157,   155
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    72,   172,   286,   287,    74,   561,    75,
      76,    77,    78,    79,    80,    81,   638,    82,   573,   574,
      83,   639,   640,   641,   270,   271,   147,   288,   289,   183,
      86,   413,    87,   305,   646,    88,   415,    89,   307,   481,
     417,   509,   461,   634,   602,   476,   301,   471,   516,   611,
     465,   507,   558,   562,   597,   524,   525,   526,   279,   280,
     122,   123,   143,   483,   539,   666,   689,   687,   540,   541,
     542,   543,   587,   544,   114,   296,   297,    90,    91,    92,
     130,   131,   445,   498,   119,   262,    93,   388,   389,    94,
     500,   368,   501,    95,    96,   462,    97,    98,   231,   232,
     430,    99,   100,   101,   102,   103,   104,   361,   356,   357,
     358,   105,   258,   259,   239,   240,   106,   255,   107,   108
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -438
static const yytype_int16 yypact[] =
{
    -438,    29,  1978,  -438,  -438,  -438,   -92,  3020,  -438,  3128,
    -438,  -438,  4208,   -65,   -39,   -37,  -438,  -438,  -438,   -46,
    -438,  4208,  4208,   -23,   -14,   -49,  4208,  4208,  4208,  3236,
      74,  -438,    56,   -61,  -438,  -438,  -438,  -438,   116,  -438,
     183,  4208,  -438,  4208,    63,  -438,  -438,  -438,    -3,    -3,
    4208,  4208,  4208,  4208,  4208,  4208,  4208,  -438,   -64,  -438,
    -438,  -438,  -438,  4208,  4208,  4208,  4208,  4208,  4208,  -438,
    -438,    70,  -438,  -438,    85,    88,   110,  2909,   118,   120,
     132,   130,   156,  -438,  -438,  -438,  -438,  -438,   165,   166,
    -438,  -438,   191,  -438,  -438,  4346,  -438,    97,   528,   144,
    -438,   196,  -438,    59,  -438,    20,  -438,  -438,  -438,  3344,
    -438,  4412,  -438,  4475,   -88,  5378,    -3,  4208,  3452,  -438,
    -438,   -71,   -74,  -438,  5378,  5378,    -3,   -10,   194,   197,
     148,  -438,   202,    66,    20,   470,  5378,  5378,  -438,   150,
    5378,   956,   159,   -28,    -3,  -438,   186,   160,  -438,  -438,
    -438,  4541,   157,   161,   211,  -438,  -438,  -438,  -438,  -438,
    -438,  -438,  -438,  -438,  -438,  3560,    18,    18,   259,  -438,
    -438,  4604,  1311,  4208,  4208,  4208,  4208,   257,  4208,  4208,
     201,   247,  -438,   206,  -438,   286,    46,  4208,  4208,  4208,
     -49,  4208,  4208,  4208,  4208,  4208,  4208,  4208,  4208,  4208,
    4208,  4208,  4208,  4208,  4208,  4208,  4208,  4208,  4208,  4208,
    4208,  4208,  4208,  4208,  -438,  -438,  -438,  4208,  4208,  4208,
    4208,  4208,  4208,  4208,  4208,  4208,  4208,  4208,  3668,  3560,
     -51,   196,  -438,  4208,  4208,    70,    87,    -3,  5249,   187,
     204,  -438,  -438,  4208,  -438,   188,  4670,  -438,  4733,  4208,
    -438,  -438,   -46,  -438,  -438,   -85,   190,  -438,   -83,  -438,
      37,  3560,  -438,   -51,    66,  -438,  -438,   431,   216,  -438,
     -70,  -438,  -438,   192,  -438,  -438,   205,    62,    -3,   193,
     225,    22,  1054,  -438,   209,  -438,  -438,  -438,  -438,  -438,
     342,  4799,   333,   240,  4862,   213,   212,   234,  5378,  4928,
     222,    23,  -438,   221,  -438,   325,   250,   223,   227,   228,
      66,    20,   470,   184,  5440,  -438,   869,   869,   869,   869,
     642,   642,    -6,    -6,   801,  5497,   728,  5509,  1097,  5564,
      18,    18,    18,   259,   259,   259,   642,   642,  5186,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
      -5,   470,   229,  -438,  4208,  -438,   231,    76,  -438,  -438,
    5378,   230,   983,  -438,  -438,  3776,  -438,  3884,  -438,  5378,
    -438,  -438,  -438,  1040,  -438,    -3,  -438,   -10,   -10,   238,
    -438,   233,  -438,   237,   287,   431,   431,  -438,  -438,  -438,
     243,    -3,   239,  -438,  -438,   227,  -438,  -438,  3992,   241,
    -438,  2244,    -3,    43,  2377,  4208,  4208,  4208,    -4,   431,
     265,  2510,   250,   245,   250,   321,  -438,   268,  -438,  -438,
    3560,  3560,    66,  -438,  4208,   -49,  -438,  -438,  1127,  3560,
    -438,  4208,  4208,  -438,  -438,    -3,  5378,    -3,  5316,  -438,
    -438,    28,  -438,  4208,  -438,   302,   431,   277,  -438,  -438,
     431,  -438,  -438,    -3,    34,  4426,   254,  -438,  -438,   309,
      -3,   309,  -438,  -438,  -438,  -438,  4991,   256,  5378,   258,
     260,  -438,  -438,   264,  -438,  -438,  -438,   285,     0,  -438,
     250,   267,   250,    -7,   262,   278,   660,   148,  -438,   279,
     282,  1184,  -438,  -438,  4100,  -438,   470,   -51,  -438,   341,
     289,   310,  -438,  -438,  -438,  -438,  2111,   208,    43,   296,
    -438,   297,  1446,   298,  4208,  -438,   164,  -438,     1,   431,
    1579,   305,  -438,  -438,   306,   318,   -25,   268,  -438,  -438,
     328,  -438,  -438,  -438,  -438,  -438,  -438,  -438,  -438,  -438,
     334,   409,   170,  -438,   -26,  -438,  -438,  -438,  -438,  -438,
    -438,    -3,  5378,  -438,   431,  -438,   431,  -438,   214,  2909,
    -438,   311,  -438,  -438,  2643,  2643,   312,  -438,   314,   200,
    -438,  -438,   315,  4208,    14,    10,  -438,  -438,   316,   130,
     130,    12,   317,   337,    16,   324,   327,   -12,   156,  -438,
     345,  -438,  -438,  -438,   368,   336,   339,   442,  -438,  4208,
    -438,  -438,  -438,  -438,  -438,  2776,   335,  -438,  4282,  -438,
    -438,  -438,  -438,  -438,   247,  -438,    15,   431,   349,  -438,
     431,   431,   371,  -438,   373,   358,   431,  -438,  4208,   354,
    5057,  1712,  -438,  -438,  -438,  -438,  -438,  2111,   357,  -438,
     247,  -438,   363,   387,  -438,   431,  -438,  -438,  -438,   369,
    -438,   431,  -438,  2111,  5120,  -438,  2909,   365,  1845,  2111,
     250,  -438,   431,   376,  -438,   431,   372,  -438,   380,  -438,
    -438,   377,   397,  -438,   431,  -438,     0,  -438,  -438,   379,
    -438,   381,  2111,   130,   100,  -438,  -438,  -438,  -438,  -438
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -438,  -438,  -438,  -438,  -437,  -438,    -2,  -438,   -45,  -438,
    -438,  -438,  -438,  -438,  -438,  -438,   344,   -11,  -438,  -438,
    -438,  -438,  -438,  -124,  -438,   135,  -438,   526,   527,   -50,
    -438,  -438,  -438,  -438,  -438,  -438,  -438,  -438,  -438,  -438,
      57,    78,    52,  -438,    -1,  -438,  -438,  -438,  -434,   -66,
    -438,  -438,  -438,  -438,  -438,  -125,  -438,   -27,  -214,  -438,
    -438,   313,  -438,    33,  -438,  -438,  -438,  -438,  -438,  -438,
    -438,    24,  -438,  -438,  -438,  -387,  -438,   -13,  -438,   -24,
    -176,  -438,  -438,  -438,  -438,    80,  -262,  -374,  -438,  -438,
    -438,    67,  -438,   468,   448,  -234,   217,   582,  -438,   343,
    -438,  -178,  -438,  -438,   -15,   -21,  -438,   139,  -246,  -438,
    -438,   -19,   195,   198,  -438,  -438,  -438,  -438,  -438,   -79
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -308
static const yytype_int16 yytable[] =
{
      73,   129,   181,   363,   133,   387,   134,   530,   309,   522,
     132,   448,   449,   570,   315,   352,   139,   382,   571,   467,
     506,   522,   570,  -252,   154,   154,   512,   571,   243,     3,
     530,   375,   256,   378,   190,   472,   518,   520,   425,   153,
      59,   531,   252,   109,   396,   532,   391,   381,   145,   244,
     533,   376,   355,   379,   534,   535,   536,   537,   190,   353,
      59,   128,    59,   253,   531,   120,   392,   249,   532,    71,
     116,   165,   499,   533,   146,   177,   503,   534,   535,   536,
     537,   569,   380,   575,   236,   355,   582,   354,   268,    71,
     590,    71,   154,   583,   121,   201,   117,   154,   118,   309,
     153,    59,   154,   154,   622,   153,    59,   153,    59,   269,
     523,   591,   126,   264,   205,   206,   207,   208,   209,   210,
     154,   127,   523,   387,   387,   623,   642,   568,   469,   148,
      71,    59,   538,   643,   470,    71,  -120,    71,  -134,   410,
     576,   208,   209,   210,   378,   577,   609,   387,    59,   612,
    -137,   610,   281,   153,    59,   619,   308,    59,  -134,   411,
     235,   460,   292,   631,   495,   310,   129,   311,   459,   133,
    -137,   134,   395,    59,   637,   132,   570,    71,   215,   216,
     593,   571,   594,    71,   387,   142,    71,   187,   387,   189,
     653,   144,   572,   233,  -306,   658,   149,   234,   152,   659,
     233,   492,    71,   493,   234,  -161,   484,   485,   173,   310,
     431,   311,   570,   154,   432,   489,   281,   571,   531,   504,
     174,   233,  -307,   175,   190,   234,   510,   533,   606,   559,
     560,   534,   535,   536,   537,   595,   560,   686,    70,   310,
     682,   311,   310,   644,   311,   176,   647,   648,   281,   487,
     403,   553,   652,   178,   154,   179,   310,   387,   311,   191,
     192,   193,   194,   195,   196,   155,   157,   180,    70,   197,
     198,   664,   199,   200,   182,   184,   185,   667,   186,   229,
     230,  -252,   418,   261,   260,   201,   263,   265,   673,   267,
     422,   675,   387,   276,   387,   273,   165,   274,   277,   190,
     680,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     295,   300,   211,   212,   302,   213,   304,   592,   306,   355,
     367,  -298,  -298,   366,   370,   377,   154,   390,   393,   397,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   398,   394,   402,   399,   187,   188,   189,   405,   406,
     407,   154,   409,   154,   154,   387,   412,   414,   387,   387,
     416,   419,   420,   421,   387,   427,   429,   154,   443,   444,
     228,   433,   446,   450,   447,   473,   452,   456,   154,   154,
     478,   480,   190,   387,   482,   454,   497,   502,   477,   387,
     479,   505,   508,   514,   519,   515,   521,   517,   545,   458,
     387,   129,   464,   387,   133,   528,   134,   281,   281,   475,
     132,   154,   387,   154,   546,   548,   281,   191,   192,   193,
     194,   195,   196,   549,   554,   555,   556,   197,   198,   154,
     199,   200,   564,   565,   581,   567,   154,     4,   585,     5,
     383,   579,   580,   201,    18,   586,   599,   617,   618,   604,
     605,   626,   607,   613,   620,   625,   418,   621,   529,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   627,   629,
     211,   212,   635,   213,   628,   111,   310,   113,   311,   645,
     115,   400,   649,   650,   154,    35,    36,    37,   651,   124,
     125,   655,   660,   662,   135,   136,   137,   140,   663,   665,
     614,   615,   670,    45,    46,    47,   674,   676,   679,   150,
     190,   151,   677,   596,   678,   683,   661,   684,   158,   159,
     160,   161,   162,   163,   164,   303,   451,   154,    84,    85,
     588,   166,   167,   168,   169,   170,   171,   527,   624,   511,
      57,   384,   636,    60,    61,   191,   192,   193,   194,   195,
     196,   681,   385,   386,   616,   197,   198,   598,   199,   200,
     563,   584,   601,   601,   603,   374,   589,   547,   557,   250,
     490,   201,   441,     0,   359,     0,   442,   238,     0,     0,
       0,     0,     0,     0,     0,   246,   248,   202,   203,   204,
     205,   206,   207,   208,   209,   210,     0,     0,   211,   212,
       0,   213,     0,   633,   685,   688,     0,     0,     0,  -298,
    -298,   141,     0,     0,     0,     0,     0,     0,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,     0,
     156,   156,     0,   140,     0,     0,   672,     0,     0,     0,
       0,   290,   291,   140,   294,     0,   298,   299,     0,     0,
       0,     0,     0,     0,   669,   312,   313,   314,   228,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   190,     0,     0,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   351,   140,   245,     0,
     190,   360,   362,   251,     0,     0,     0,     0,   254,   257,
       0,   369,     0,     0,     0,     0,     0,   373,     0,     0,
       0,  -308,  -308,     0,     0,     0,   272,   197,   198,   140,
       0,   187,   188,   189,     0,   191,   192,   193,   194,   195,
     196,     0,     0,   201,     0,   197,   198,   282,   199,   200,
       0,     0,     0,     0,     0,     0,     0,   293,     0,     0,
       0,   201,   205,   206,   207,   208,   209,   210,   190,     0,
    -308,  -308,     0,     0,     0,     0,     0,   202,   203,   204,
     205,   206,   207,   208,   209,   210,     0,     0,   211,   212,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   191,   192,   193,   194,   195,   196,     0,
       0,   282,     0,   197,   198,     0,   199,   200,     0,   364,
       0,     0,   428,     0,     0,     0,     0,     0,     0,   201,
       0,     0,     0,   436,     0,   438,     0,     0,     0,     0,
       0,   190,     0,   282,     0,   202,   203,   204,   205,   206,
     207,   208,   209,   210,     0,     0,   211,   212,     0,   213,
     364,     0,     0,     0,     0,     0,   140,   423,     0,     0,
       0,     0,     0,   466,   298,   468,   191,   192,   193,   194,
     195,   196,     0,     0,     0,     0,   197,   198,   140,   140,
     200,     0,   486,     0,     0,     0,     0,   140,     0,   360,
     491,     0,   201,     0,     0,     0,     0,     0,     0,   190,
       0,   496,     0,     0,     0,     0,     0,     0,   202,   203,
     204,   205,   206,   207,   208,   209,   210,     0,     0,   211,
     212,     0,   426,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -308,  -308,  -308,  -308,   195,   196,
       0,     0,     0,     0,   197,   198,     0,   440,     0,   257,
     257,     0,   552,     0,     0,     0,     0,     0,     0,     0,
     201,     0,     0,   272,     0,     0,     0,     0,     0,     0,
     455,     0,   298,     0,   364,   364,   187,   188,   189,   205,
     206,   207,   208,   209,   210,     0,     0,   211,   212,     0,
       0,     0,   282,   282,     0,     0,     0,     0,     0,     0,
       0,   282,     0,     0,     0,     0,     0,   364,     0,   364,
       0,     0,     0,   190,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   364,     0,  -298,  -298,     0,
       0,   608,   364,   187,   188,   189,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,     0,   191,   192,
     193,   194,   195,   196,     0,     0,     0,   630,   197,   198,
       0,   199,   200,     0,     0,     0,     0,     0,     0,     0,
     190,     0,     0,     0,   201,     0,   228,     0,     0,     0,
     364,     0,     0,   266,     0,     0,   654,     0,     0,     0,
     202,   203,   204,   205,   206,   207,   208,   209,   210,     0,
       0,   211,   212,     0,   213,   191,   192,   193,   194,   195,
     196,     0,   434,     0,     0,   197,   198,     0,   199,   200,
     187,   188,   189,   364,     0,  -298,  -298,   190,     0,     0,
       0,   201,     0,     0,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,     0,     0,   202,   203,   204,
     205,   206,   207,   208,   209,   210,     0,   190,   211,   212,
    -135,   213,   191,   192,   193,   194,   195,   196,     0,   439,
       0,     0,   197,   198,   228,     0,     0,   187,   188,   189,
    -135,     0,     0,     0,     0,     0,     0,     0,   201,     0,
       0,     0,   191,   192,   193,   194,   195,   196,     0,     0,
       0,     0,   197,   198,     0,   199,   200,   205,   206,   207,
     208,   209,   210,     0,   190,   211,   212,     0,   201,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   202,   203,   204,   205,   206,   207,
     208,   209,   210,     0,     0,   211,   212,     0,   213,   191,
     192,   193,   194,   195,   196,     0,   488,     0,     0,   197,
     198,     0,   199,   200,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   201,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   202,   203,   204,   205,   206,   207,   208,   209,   210,
       0,     0,   211,   212,     0,   213,     0,     4,     0,     5,
       6,     0,     7,   550,     8,     0,     9,    10,     0,     0,
      11,    12,     0,     0,    13,     0,     0,     0,     0,     0,
       0,    14,    15,     0,    16,    17,    18,    19,    20,    21,
      22,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,    34,    35,    36,    37,    38,     0,
      39,     0,     0,     0,     0,    40,    41,    42,     0,    43,
       0,     0,   284,    45,    46,    47,     0,     0,     0,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,     0,     0,     0,     0,
       0,     0,    63,    64,     0,     0,     0,    65,    66,     0,
       0,     0,     0,     0,    67,     0,    68,     0,    69,    70,
     285,    71,     4,     0,     5,     6,     0,     7,     0,     8,
       0,     9,    10,     0,     0,    11,    12,     0,     0,    13,
       0,     0,     0,     0,     0,   566,    14,    15,     0,    16,
      17,    18,    19,    20,    21,    22,     0,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     0,    34,
      35,    36,    37,    38,     0,    39,     0,     0,     0,     0,
      40,    41,    42,     0,    43,     0,     0,   284,    45,    46,
      47,     0,     0,     0,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,     0,     0,     0,     0,     0,     0,    63,    64,     0,
       0,     0,    65,    66,     0,     0,     0,     0,     0,    67,
       0,    68,     0,    69,    70,     4,    71,     5,     6,     0,
       7,     0,     8,     0,     9,    10,     0,     0,    11,    12,
       0,     0,    13,   578,     0,     0,     0,     0,     0,    14,
      15,     0,    16,    17,    18,    19,    20,    21,    22,     0,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     0,    34,    35,    36,    37,    38,     0,    39,     0,
       0,     0,     0,    40,    41,    42,     0,    43,     0,     0,
     284,    45,    46,    47,     0,     0,     0,     0,     0,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,     0,     0,     0,     0,     0,     0,
      63,    64,     0,     0,     0,    65,    66,     0,     0,     0,
       0,     0,    67,     0,    68,     0,    69,    70,     4,    71,
       5,     6,     0,     7,     0,     8,     0,     9,    10,     0,
       0,    11,    12,     0,     0,    13,     0,     0,   657,     0,
       0,     0,    14,    15,     0,    16,    17,    18,    19,    20,
      21,    22,     0,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,     0,    34,    35,    36,    37,    38,
       0,    39,     0,     0,     0,     0,    40,    41,    42,     0,
      43,     0,     0,   284,    45,    46,    47,     0,     0,     0,
       0,     0,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,     0,     0,     0,
       0,     0,     0,    63,    64,     0,     0,     0,    65,    66,
       0,     0,     0,     0,     0,    67,     0,    68,     0,    69,
      70,     4,    71,     5,     6,     0,     7,     0,     8,     0,
       9,    10,     0,     0,    11,    12,     0,     0,    13,     0,
     671,     0,     0,     0,     0,    14,    15,     0,    16,    17,
      18,    19,    20,    21,    22,     0,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     0,    34,    35,
      36,    37,    38,     0,    39,     0,     0,     0,     0,    40,
      41,    42,     0,    43,     0,     0,   284,    45,    46,    47,
       0,     0,     0,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
       0,     0,     0,     0,     0,     0,    63,    64,     0,     0,
       0,    65,    66,     0,     0,     0,     0,     0,    67,     0,
      68,     0,    69,    70,     4,    71,     5,     6,     0,     7,
       0,     8,     0,     9,    10,     0,     0,    11,    12,     0,
       0,    13,     0,     0,     0,     0,     0,     0,    14,    15,
       0,    16,    17,    18,    19,    20,    21,    22,     0,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       0,    34,    35,    36,    37,    38,     0,    39,     0,     0,
       0,     0,    40,    41,    42,     0,    43,     0,     0,    44,
      45,    46,    47,     0,     0,     0,     0,     0,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,     0,     0,     0,     0,     0,     0,    63,
      64,     0,     0,     0,    65,    66,     0,     0,     0,     0,
       0,    67,     0,    68,     0,    69,    70,     4,    71,     5,
       6,     0,     7,     0,     8,     0,     9,    10,     0,     0,
      11,    12,     0,     0,    13,     0,     0,     0,     0,     0,
       0,    14,    15,     0,    16,    17,    18,    19,    20,    21,
      22,     0,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     0,    34,    35,    36,    37,    38,     0,
      39,     0,     0,     0,     0,    40,    41,    42,     0,    43,
       0,     0,   284,    45,    46,    47,     0,     0,     0,     0,
       0,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,     0,     0,     0,     0,
       0,     0,    63,    64,     0,     0,     0,    65,    66,     0,
       0,     0,     0,     0,    67,     0,    68,     0,    69,    70,
       4,    71,     5,     6,     0,     7,     0,     0,     0,     9,
      10,     0,     0,    11,    12,     0,     0,    13,     0,     0,
       0,     0,     0,     0,    14,    15,     0,    16,    17,     0,
      19,    20,    21,    22,     0,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     0,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,    41,
      42,     0,    43,     0,     0,     0,    45,    46,    47,     0,
       0,     0,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,     0,
       0,     0,     0,     0,     0,    63,    64,     0,     0,     0,
      65,    66,     0,     0,     0,     0,   457,    67,     0,    68,
       0,    69,    70,     4,    71,     5,     6,     0,     7,     0,
       0,     0,     9,    10,     0,     0,    11,    12,     0,     0,
      13,     0,     0,     0,     0,     0,     0,    14,    15,     0,
      16,    17,     0,    19,    20,    21,    22,     0,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     0,
      34,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,     0,    41,    42,     0,    43,     0,     0,     0,    45,
      46,    47,     0,     0,     0,     0,     0,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,     0,     0,     0,     0,     0,     0,    63,    64,
       0,     0,     0,    65,    66,     0,     0,     0,     0,   463,
      67,     0,    68,     0,    69,    70,     4,    71,     5,     6,
       0,     7,     0,     0,     0,     9,    10,     0,     0,    11,
      12,     0,     0,    13,     0,     0,     0,     0,     0,     0,
      14,    15,     0,    16,    17,     0,    19,    20,    21,    22,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     0,    34,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,    41,    42,     0,    43,     0,
       0,     0,    45,    46,    47,     0,     0,     0,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,     0,     0,     0,     0,     0,
       0,    63,    64,     0,     0,     0,    65,    66,     0,     0,
       0,     0,   474,    67,     0,    68,     0,    69,    70,     4,
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
       0,     0,     0,     0,    63,    64,     0,     0,     0,    65,
      66,     0,     0,     0,     0,   600,    67,     0,    68,     0,
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
      62,     0,     0,     0,     0,     0,     0,    63,    64,     0,
       0,     0,    65,    66,     0,     0,     0,     0,   632,    67,
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
      59,    60,    61,    62,     0,     0,     4,     0,     5,     6,
      63,    64,     0,     0,     0,    65,    66,     0,     0,     0,
       0,     0,    67,    13,    68,     0,    69,    70,     0,    71,
      14,    15,     0,     0,     0,     0,     0,     0,    21,    22,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,    41,     0,     0,     0,     0,
       0,     0,    45,    46,    47,     0,     0,     0,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,     4,     0,     5,     6,     0,     0,
       0,    63,    64,     0,     0,     0,    65,    66,     0,     0,
       0,    13,     0,    67,     0,    68,     0,   110,    14,    15,
      71,     0,     0,     0,     0,     0,    21,    22,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,     0,    41,     0,     0,     0,     0,     0,     0,
      45,    46,    47,     0,     0,     0,     0,     0,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,     4,     0,     5,     6,     0,     0,     0,    63,
      64,     0,     0,     0,    65,    66,     0,     0,     0,    13,
       0,    67,     0,    68,     0,   112,    14,    15,    71,     0,
       0,     0,     0,     0,    21,    22,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,     0,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
       0,    41,     0,     0,     0,     0,     0,     0,    45,    46,
      47,     0,     0,     0,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
       4,     0,     5,     6,     0,     0,     0,    63,    64,     0,
       0,     0,    65,    66,     0,     0,     0,    13,     0,    67,
       0,    68,     0,   138,    14,    15,    71,     0,     0,     0,
       0,     0,    21,    22,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,     0,     0,     0,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,    41,
       0,     0,     0,     0,     0,     0,    45,    46,    47,     0,
       0,     0,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,     4,     0,
       5,     6,   237,     0,     0,    63,    64,     0,     0,     0,
      65,    66,     0,     0,     0,    13,     0,    67,     0,    68,
       0,     0,    14,    15,    71,     0,     0,     0,     0,     0,
      21,    22,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,    41,     0,     0,
       0,     0,     0,     0,    45,    46,    47,     0,     0,     0,
       0,     0,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,     4,     0,     5,     6,
       0,     0,     0,    63,    64,     0,     0,     0,    65,    66,
       0,     0,     0,    13,     0,    67,     0,    68,   247,     0,
      14,    15,    71,     0,     0,     0,     0,     0,    21,    22,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,    41,     0,     0,     0,     0,
       0,     0,    45,    46,    47,     0,     0,     0,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,     4,     0,     5,     6,   278,     0,
       0,    63,    64,     0,     0,     0,    65,    66,     0,     0,
       0,    13,     0,    67,     0,    68,     0,     0,    14,    15,
      71,     0,     0,     0,     0,     0,    21,    22,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,     0,    41,     0,     0,     0,     0,     0,     0,
      45,    46,    47,     0,     0,     0,     0,     0,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,     4,     0,     5,     6,   350,     0,     0,    63,
      64,     0,     0,     0,    65,    66,     0,     0,     0,    13,
       0,    67,     0,    68,     0,     0,    14,    15,    71,     0,
       0,     0,     0,     0,    21,    22,     0,    23,    24,    25,
      26,    27,    28,     0,     0,     0,     0,     0,     0,     0,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
       0,    41,     0,     0,     0,     0,     0,     0,    45,    46,
      47,     0,     0,     0,     0,     0,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
       4,     0,     5,     6,   435,     0,     0,    63,    64,     0,
       0,     0,    65,    66,     0,     0,     0,    13,     0,    67,
       0,    68,     0,     0,    14,    15,    71,     0,     0,     0,
       0,     0,    21,    22,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,     0,     0,     0,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,    41,
       0,     0,     0,     0,     0,     0,    45,    46,    47,     0,
       0,     0,     0,     0,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,     4,     0,
       5,     6,   437,     0,     0,    63,    64,     0,     0,     0,
      65,    66,     0,     0,     0,    13,     0,    67,     0,    68,
       0,     0,    14,    15,    71,     0,     0,     0,     0,     0,
      21,    22,     0,    23,    24,    25,    26,    27,    28,     0,
       0,     0,     0,     0,     0,     0,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,    41,     0,     0,
       0,     0,     0,     0,    45,    46,    47,     0,     0,     0,
       0,     0,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,     4,     0,     5,     6,
     453,     0,     0,    63,    64,     0,     0,     0,    65,    66,
       0,     0,     0,    13,     0,    67,     0,    68,     0,     0,
      14,    15,    71,     0,     0,     0,     0,     0,    21,    22,
       0,    23,    24,    25,    26,    27,    28,     0,     0,     0,
       0,     0,     0,     0,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,    41,     0,     0,     0,     0,
       0,     0,    45,    46,    47,     0,     0,     0,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,     4,     0,     5,     6,   551,     0,
       0,    63,    64,     0,     0,     0,    65,    66,     0,     0,
       0,    13,     0,    67,     0,    68,     0,     0,    14,    15,
      71,     0,     0,     0,     0,     0,    21,    22,     0,    23,
      24,    25,    26,    27,    28,     0,     0,     0,     0,     0,
       0,     0,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,     0,    41,     0,     0,     0,     0,     0,     0,
      45,    46,    47,     0,     0,   187,   188,   189,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,   190,     0,     0,     0,     0,     0,     0,    63,
      64,     0,     0,     0,    65,    66,     0,     0,     0,     0,
       0,    67,     0,    68,     0,     0,     0,     0,    71,   187,
     188,   189,     0,     0,     0,     0,     0,   191,   192,   193,
     194,   195,   196,     0,     0,     0,     0,   197,   198,     0,
     199,   200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,     0,     0,   190,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   202,
     203,   204,   205,   206,   207,   208,   209,   210,     0,     0,
     211,   212,     0,   213,   609,   187,   188,   189,     0,   610,
       0,   191,   192,   193,   194,   195,   196,     0,     0,     0,
       0,   197,   198,     0,   199,   200,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   201,     0,     0,
       0,     0,   190,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   202,   203,   204,   205,   206,   207,   208,
     209,   210,     0,     0,   211,   212,     0,   213,   187,   188,
     189,     0,     0,   214,     0,     0,     0,   191,   192,   193,
     194,   195,   196,     0,     0,     0,     0,   197,   198,     0,
     199,   200,     0,     0,     0,     0,     0,  -298,  -298,     0,
       0,     0,     0,   201,     0,   190,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,     0,     0,   202,
     203,   204,   205,   206,   207,   208,   209,   210,     0,     0,
     211,   212,  -138,   213,   187,   188,   189,     0,     0,   241,
     191,   192,   193,   194,   195,   196,   228,     0,     0,     0,
     197,   198,  -138,   199,   200,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   201,     0,     0,     0,
       0,   190,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   202,   203,   204,   205,   206,   207,   208,   209,
     210,     0,     0,   211,   212,     0,   213,   187,   188,   189,
       0,     0,   242,     0,     0,     0,   191,   192,   193,   194,
     195,   196,     0,     0,     0,     0,   197,   198,     0,   199,
     200,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   201,     0,   190,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   202,   203,
     204,   205,   206,   207,   208,   209,   210,     0,     0,   211,
     212,     0,   213,   187,   188,   189,     0,     0,   275,   191,
     192,   193,   194,   195,   196,     0,     0,     0,     0,   197,
     198,     0,   199,   200,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   201,     0,     0,     0,     0,
     190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   202,   203,   204,   205,   206,   207,   208,   209,   210,
       0,     0,   211,   212,     0,   213,   187,   188,   189,     0,
     283,     0,     0,     0,     0,   191,   192,   193,   194,   195,
     196,     0,     0,     0,     0,   197,   198,     0,   199,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,     0,   190,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   202,   203,   204,
     205,   206,   207,   208,   209,   210,     0,     0,   211,   212,
       0,   213,   187,   188,   189,     0,   371,     0,   191,   192,
     193,   194,   195,   196,     0,     0,     0,     0,   197,   198,
       0,   199,   200,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   201,     0,     0,     0,     0,   190,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     202,   203,   204,   205,   206,   207,   208,   209,   210,     0,
       0,   211,   212,     0,   213,   187,   188,   189,     0,   372,
       0,     0,     0,     0,   191,   192,   193,   194,   195,   196,
       0,     0,     0,     0,   197,   198,     0,   199,   200,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     201,     0,   190,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   202,   203,   204,   205,
     206,   207,   208,   209,   210,     0,     0,   211,   212,     0,
     213,   187,   188,   189,     0,   401,     0,   191,   192,   193,
     194,   195,   196,     0,     0,     0,     0,   197,   198,     0,
     199,   200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,     0,     0,     0,     0,   190,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   202,
     203,   204,   205,   206,   207,   208,   209,   210,     0,     0,
     211,   212,     0,   213,   187,   188,   189,     0,   404,     0,
       0,     0,     0,   191,   192,   193,   194,   195,   196,     0,
       0,     0,     0,   197,   198,     0,   199,   200,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
       0,   190,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   202,   203,   204,   205,   206,
     207,   208,   209,   210,     0,     0,   211,   212,     0,   213,
     187,   188,   189,     0,   408,     0,   191,   192,   193,   194,
     195,   196,     0,     0,     0,     0,   197,   198,     0,   199,
     200,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   201,     0,     0,     0,     0,   190,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   202,   203,
     204,   205,   206,   207,   208,   209,   210,     0,     0,   211,
     212,     0,   213,   187,   188,   189,     0,   513,     0,     0,
       0,     0,   191,   192,   193,   194,   195,   196,     0,     0,
       0,     0,   197,   198,     0,   199,   200,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   201,     0,
     190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   202,   203,   204,   205,   206,   207,
     208,   209,   210,     0,     0,   211,   212,     0,   213,   187,
     188,   189,     0,   656,     0,   191,   192,   193,   194,   195,
     196,     0,     0,     0,     0,   197,   198,     0,   199,   200,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   201,     0,     0,     0,     0,   190,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   202,   203,   204,
     205,   206,   207,   208,   209,   210,     0,     0,   211,   212,
       0,   213,   187,   188,   189,     0,   668,     0,     0,     0,
       0,   191,   192,   193,   194,   195,   196,     0,     0,     0,
       0,   197,   198,     0,   199,   200,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   201,     0,   190,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   202,   203,   204,   205,   206,   207,   208,
     209,   210,     0,     0,   211,   212,     0,   213,   424,   187,
     188,   189,     0,     0,   191,   192,   193,   194,   195,   196,
       0,     0,   365,     0,   197,   198,     0,   199,   200,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     201,     0,     0,     0,     0,     0,   190,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   202,   203,   204,   205,
     206,   207,   208,   209,   210,     0,     0,   211,   212,     0,
     213,   187,   188,   189,     0,     0,     0,     0,     0,     0,
       0,   191,   192,   193,   194,   195,   196,     0,     0,   494,
       0,   197,   198,     0,   199,   200,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   201,   190,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   202,   203,   204,   205,   206,   207,   208,
     209,   210,     0,   187,   211,   212,     0,   213,     0,     0,
       0,     0,     0,   191,   192,   193,   194,   195,   196,     0,
       0,     0,     0,   197,   198,     0,   199,   200,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   201,
     190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   202,   203,   204,   205,   206,
     207,   208,   209,   210,     0,     0,   211,   212,     0,   213,
       0,     0,     0,     0,     0,   191,   192,   193,   194,   195,
     196,     0,     0,     0,     0,   197,   198,     0,   199,   200,
       0,     0,     0,     0,     0,     0,     0,   190,     0,     0,
       0,   201,     0,     0,     0,     0,     0,     0,     0,   190,
       0,     0,     0,     0,     0,     0,     0,   202,   203,   204,
     205,   206,   207,   208,   209,   210,     0,     0,   211,   212,
       0,   213,   191,   192,   193,   194,   195,   196,     0,     0,
       0,     0,   197,   198,   191,   192,   193,   194,   195,   196,
       0,     0,     0,     0,   197,   198,     0,     0,   201,     0,
       0,     0,     0,     0,   190,     0,     0,     0,     0,     0,
     201,     0,     0,     0,   202,   203,   204,   205,   206,   207,
     208,   209,   210,     0,     0,   211,   212,   203,   204,   205,
     206,   207,   208,   209,   210,     0,     0,   211,   212,   191,
     192,   193,   194,   195,   196,     0,     0,     0,     0,   197,
     198,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   201,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   203,     0,   205,   206,   207,   208,   209,   210,
       0,     0,   211,   212
};

static const yytype_int16 yycheck[] =
{
       2,    25,    81,   237,    25,   267,    25,    14,   186,     9,
      25,   385,   386,    12,   190,   229,    29,   263,    17,   406,
     457,     9,    12,    87,    48,    49,   463,    17,   116,     0,
      14,   116,    42,   116,    40,   409,   470,   474,    43,   110,
     111,    48,   116,   135,   278,    52,   116,   261,   109,   137,
      57,   136,   230,   136,    61,    62,    63,    64,    40,   110,
     111,   110,   111,   137,    48,   111,   136,   138,    52,   140,
     135,   135,   446,    57,   135,    77,   450,    61,    62,    63,
      64,   515,   260,   517,   105,   263,   111,   138,   116,   140,
     116,   140,   116,   118,   140,   101,   135,   121,   135,   277,
     110,   111,   126,   127,   116,   110,   111,   110,   111,   137,
     110,   137,   135,   134,   120,   121,   122,   123,   124,   125,
     144,   135,   110,   385,   386,   137,   111,   514,   132,    13,
     140,   111,   139,   118,   138,   140,   136,   140,   116,   116,
     139,   123,   124,   125,   116,   519,   132,   409,   111,   139,
     116,   137,   165,   110,   111,   139,   110,   111,   136,   136,
     140,   118,   175,   600,   136,   186,   190,   186,   402,   190,
     136,   190,   110,   111,   611,   190,    12,   140,    81,    82,
     554,    17,   556,   140,   446,   111,   140,     3,   450,     5,
     627,   135,    28,   134,   135,   632,    13,   138,   135,   636,
     134,   435,   140,   437,   138,    35,   420,   421,   138,   230,
     134,   230,    12,   237,   138,   429,   229,    17,    48,   453,
     135,   134,   135,   135,    40,   138,   460,    57,    28,    21,
      22,    61,    62,    63,    64,    21,    22,   137,   138,   260,
     677,   260,   263,   617,   263,   135,   620,   621,   261,   425,
      10,   497,   626,   135,   278,   135,   277,   519,   277,    75,
      76,    77,    78,    79,    80,    48,    49,   135,   138,    85,
      86,   645,    88,    89,   118,   110,   110,   651,    87,   135,
      84,    87,   306,   135,    87,   101,    84,   137,   662,   130,
     311,   665,   554,   136,   556,   109,   135,   137,    87,    40,
     674,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      53,   110,   128,   129,    67,   131,   110,   551,    32,   497,
     116,    81,    82,   136,   136,   135,   350,   111,   136,   136,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   116,   137,    10,   135,     3,     4,     5,   135,   137,
     116,   375,   130,   377,   378,   617,   135,    32,   620,   621,
     110,   138,   135,   135,   626,   136,   135,   391,   130,   136,
     130,   141,   135,   130,    87,   110,   137,   136,   402,   403,
     135,    60,    40,   645,   116,   398,    84,   110,   412,   651,
     414,   137,    83,   137,   130,   137,   111,   137,   136,   401,
     662,   425,   404,   665,   425,   138,   425,   420,   421,   411,
     425,   435,   674,   437,   136,   136,   429,    75,    76,    77,
      78,    79,    80,   141,    83,   136,   116,    85,    86,   453,
      88,    89,   136,   136,   116,   137,   460,     6,   110,     8,
       9,   136,   136,   101,    35,   111,   135,   130,   111,   137,
     136,    83,   137,   137,   130,   110,   480,   130,   482,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   132,    27,
     128,   129,   137,   131,   135,     7,   497,     9,   497,   130,
      12,   139,   111,   110,   508,    54,    55,    56,   130,    21,
      22,   137,   135,   130,    26,    27,    28,    29,   111,   130,
     579,   580,   137,    72,    73,    74,   130,   135,   111,    41,
      40,    43,   132,   558,   137,   136,   640,   136,    50,    51,
      52,    53,    54,    55,    56,   181,   391,   551,     2,     2,
     541,    63,    64,    65,    66,    67,    68,   480,   588,   461,
     109,   110,   608,   112,   113,    75,    76,    77,    78,    79,
      80,   676,   121,   122,   581,    85,    86,   559,    88,    89,
     508,   528,   564,   565,   565,   252,   542,   487,   501,   121,
     431,   101,   377,    -1,   231,    -1,   378,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,   118,   117,   118,   119,
     120,   121,   122,   123,   124,   125,    -1,    -1,   128,   129,
      -1,   131,    -1,   605,   683,   684,    -1,    -1,    -1,    81,
      82,    29,    -1,    -1,    -1,    -1,    -1,    -1,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    -1,
      48,    49,    -1,   165,    -1,    -1,   660,    -1,    -1,    -1,
      -1,   173,   174,   175,   176,    -1,   178,   179,    -1,    -1,
      -1,    -1,    -1,    -1,   656,   187,   188,   189,   130,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,    40,    -1,    -1,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   116,    -1,
      40,   233,   234,   121,    -1,    -1,    -1,    -1,   126,   127,
      -1,   243,    -1,    -1,    -1,    -1,    -1,   249,    -1,    -1,
      -1,    79,    80,    -1,    -1,    -1,   144,    85,    86,   261,
      -1,     3,     4,     5,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,   101,    -1,    85,    86,   165,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   175,    -1,    -1,
      -1,   101,   120,   121,   122,   123,   124,   125,    40,    -1,
     128,   129,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,   125,    -1,    -1,   128,   129,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    -1,
      -1,   229,    -1,    85,    86,    -1,    88,    89,    -1,   237,
      -1,    -1,   354,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    -1,   365,    -1,   367,    -1,    -1,    -1,    -1,
      -1,    40,    -1,   261,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,   125,    -1,    -1,   128,   129,    -1,   131,
     278,    -1,    -1,    -1,    -1,    -1,   398,   139,    -1,    -1,
      -1,    -1,    -1,   405,   406,   407,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,   420,   421,
      89,    -1,   424,    -1,    -1,    -1,    -1,   429,    -1,   431,
     432,    -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,   443,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    -1,    -1,   128,
     129,    -1,   350,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    -1,   375,    -1,   377,
     378,    -1,   494,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    -1,   391,    -1,    -1,    -1,    -1,    -1,    -1,
     398,    -1,   514,    -1,   402,   403,     3,     4,     5,   120,
     121,   122,   123,   124,   125,    -1,    -1,   128,   129,    -1,
      -1,    -1,   420,   421,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   429,    -1,    -1,    -1,    -1,    -1,   435,    -1,   437,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   453,    -1,    81,    82,    -1,
      -1,   573,   460,     3,     4,     5,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    -1,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,   599,    85,    86,
      -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,   101,    -1,   130,    -1,    -1,    -1,
     508,    -1,    -1,   137,    -1,    -1,   628,    -1,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,   125,    -1,
      -1,   128,   129,    -1,   131,    75,    76,    77,    78,    79,
      80,    -1,   139,    -1,    -1,    85,    86,    -1,    88,    89,
       3,     4,     5,   551,    -1,    81,    82,    40,    -1,    -1,
      -1,   101,    -1,    -1,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,   125,    -1,    40,   128,   129,
     116,   131,    75,    76,    77,    78,    79,    80,    -1,   139,
      -1,    -1,    85,    86,   130,    -1,    -1,     3,     4,     5,
     136,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    85,    86,    -1,    88,    89,   120,   121,   122,
     123,   124,   125,    -1,    40,   128,   129,    -1,   101,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,   125,    -1,    -1,   128,   129,    -1,   131,    75,
      76,    77,    78,    79,    80,    -1,   139,    -1,    -1,    85,
      86,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      -1,    -1,   128,   129,    -1,   131,    -1,     6,    -1,     8,
       9,    -1,    11,   139,    13,    -1,    15,    16,    -1,    -1,
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
     139,   140,     6,    -1,     8,     9,    -1,    11,    -1,    13,
      -1,    15,    16,    -1,    -1,    19,    20,    -1,    -1,    23,
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
      11,    -1,    13,    -1,    15,    16,    -1,    -1,    19,    20,
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
      -1,    19,    20,    -1,    -1,    23,    -1,    -1,    26,    -1,
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
      15,    16,    -1,    -1,    19,    20,    -1,    -1,    23,    -1,
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
      -1,    13,    -1,    15,    16,    -1,    -1,    19,    20,    -1,
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
       9,    -1,    11,    -1,    13,    -1,    15,    16,    -1,    -1,
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
      16,    -1,    -1,    19,    20,    -1,    -1,    23,    -1,    -1,
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
      -1,    -1,    15,    16,    -1,    -1,    19,    20,    -1,    -1,
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
      -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,    19,
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
      -1,    -1,    -1,    -1,   121,   122,    -1,    -1,    -1,   126,
     127,    -1,    -1,    -1,    -1,   132,   133,    -1,   135,    -1,
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
     114,    -1,    -1,    -1,    -1,    -1,    -1,   121,   122,    -1,
      -1,    -1,   126,   127,    -1,    -1,    -1,    -1,   132,   133,
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
     111,   112,   113,   114,    -1,    -1,     6,    -1,     8,     9,
     121,   122,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,
      -1,    -1,   133,    23,   135,    -1,   137,   138,    -1,   140,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     6,    -1,     8,     9,    -1,    -1,
      -1,   121,   122,    -1,    -1,    -1,   126,   127,    -1,    -1,
      -1,    23,    -1,   133,    -1,   135,    -1,   137,    30,    31,
     140,    -1,    -1,    -1,    -1,    -1,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     6,    -1,     8,     9,    -1,    -1,    -1,   121,
     122,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,    23,
      -1,   133,    -1,   135,    -1,   137,    30,    31,   140,    -1,
      -1,    -1,    -1,    -1,    38,    39,    -1,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
       6,    -1,     8,     9,    -1,    -1,    -1,   121,   122,    -1,
      -1,    -1,   126,   127,    -1,    -1,    -1,    23,    -1,   133,
      -1,   135,    -1,   137,    30,    31,   140,    -1,    -1,    -1,
      -1,    -1,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,     6,    -1,
       8,     9,   118,    -1,    -1,   121,   122,    -1,    -1,    -1,
     126,   127,    -1,    -1,    -1,    23,    -1,   133,    -1,   135,
      -1,    -1,    30,    31,   140,    -1,    -1,    -1,    -1,    -1,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     6,    -1,     8,     9,
      -1,    -1,    -1,   121,   122,    -1,    -1,    -1,   126,   127,
      -1,    -1,    -1,    23,    -1,   133,    -1,   135,   136,    -1,
      30,    31,   140,    -1,    -1,    -1,    -1,    -1,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     6,    -1,     8,     9,   118,    -1,
      -1,   121,   122,    -1,    -1,    -1,   126,   127,    -1,    -1,
      -1,    23,    -1,   133,    -1,   135,    -1,    -1,    30,    31,
     140,    -1,    -1,    -1,    -1,    -1,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     6,    -1,     8,     9,   118,    -1,    -1,   121,
     122,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,    23,
      -1,   133,    -1,   135,    -1,    -1,    30,    31,   140,    -1,
      -1,    -1,    -1,    -1,    38,    39,    -1,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
       6,    -1,     8,     9,   118,    -1,    -1,   121,   122,    -1,
      -1,    -1,   126,   127,    -1,    -1,    -1,    23,    -1,   133,
      -1,   135,    -1,    -1,    30,    31,   140,    -1,    -1,    -1,
      -1,    -1,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,     6,    -1,
       8,     9,   118,    -1,    -1,   121,   122,    -1,    -1,    -1,
     126,   127,    -1,    -1,    -1,    23,    -1,   133,    -1,   135,
      -1,    -1,    30,    31,   140,    -1,    -1,    -1,    -1,    -1,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     6,    -1,     8,     9,
     118,    -1,    -1,   121,   122,    -1,    -1,    -1,   126,   127,
      -1,    -1,    -1,    23,    -1,   133,    -1,   135,    -1,    -1,
      30,    31,   140,    -1,    -1,    -1,    -1,    -1,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     6,    -1,     8,     9,   118,    -1,
      -1,   121,   122,    -1,    -1,    -1,   126,   127,    -1,    -1,
      -1,    23,    -1,   133,    -1,   135,    -1,    -1,    30,    31,
     140,    -1,    -1,    -1,    -1,    -1,    38,    39,    -1,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    -1,    -1,     3,     4,     5,    -1,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,    40,    -1,    -1,    -1,    -1,    -1,    -1,   121,
     122,    -1,    -1,    -1,   126,   127,    -1,    -1,    -1,    -1,
      -1,   133,    -1,   135,    -1,    -1,    -1,    -1,   140,     3,
       4,     5,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,   125,    -1,    -1,
     128,   129,    -1,   131,   132,     3,     4,     5,    -1,   137,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,   119,   120,   121,   122,   123,
     124,   125,    -1,    -1,   128,   129,    -1,   131,     3,     4,
       5,    -1,    -1,   137,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,   101,    -1,    40,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    -1,    -1,   117,
     118,   119,   120,   121,   122,   123,   124,   125,    -1,    -1,
     128,   129,   116,   131,     3,     4,     5,    -1,    -1,   137,
      75,    76,    77,    78,    79,    80,   130,    -1,    -1,    -1,
      85,    86,   136,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
     125,    -1,    -1,   128,   129,    -1,   131,     3,     4,     5,
      -1,    -1,   137,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   101,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    -1,    -1,   128,
     129,    -1,   131,     3,     4,     5,    -1,    -1,   137,    75,
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
     123,   124,   125,    -1,    -1,   128,   129,    -1,   131,     3,
       4,     5,    -1,   136,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,   125,    -1,    -1,   128,   129,
      -1,   131,     3,     4,     5,    -1,   136,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,   119,   120,   121,   122,   123,
     124,   125,    -1,    -1,   128,   129,    -1,   131,   132,     3,
       4,     5,    -1,    -1,    75,    76,    77,    78,    79,    80,
      -1,    -1,    83,    -1,    85,    86,    -1,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   122,   123,   124,   125,    -1,    -1,   128,   129,    -1,
     131,     3,     4,     5,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    83,
      -1,    85,    86,    -1,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,   118,   119,   120,   121,   122,   123,
     124,   125,    -1,     3,   128,   129,    -1,   131,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    85,    86,    -1,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   117,   118,   119,   120,   121,
     122,   123,   124,   125,    -1,    -1,   128,   129,    -1,   131,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    85,    86,    -1,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,   122,   123,   124,   125,    -1,    -1,   128,   129,
      -1,   131,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    85,    86,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    85,    86,    -1,    -1,   101,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,   125,    -1,    -1,   128,   129,   118,   119,   120,
     121,   122,   123,   124,   125,    -1,    -1,   128,   129,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   118,    -1,   120,   121,   122,   123,   124,   125,
      -1,    -1,   128,   129
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
     112,   113,   114,   121,   122,   126,   127,   133,   135,   137,
     138,   140,   145,   148,   149,   151,   152,   153,   154,   155,
     156,   157,   159,   162,   169,   170,   172,   174,   177,   179,
     219,   220,   221,   228,   231,   235,   236,   238,   239,   243,
     244,   245,   246,   247,   248,   253,   258,   260,   261,   135,
     137,   235,   137,   235,   216,   235,   135,   135,   135,   226,
     111,   140,   202,   203,   235,   235,   135,   135,   110,   221,
     222,   223,   246,   247,   253,   235,   235,   235,   137,   219,
     235,   239,   111,   204,   135,   109,   135,   168,    13,    13,
     235,   235,   135,   110,   221,   238,   239,   238,   235,   235,
     235,   235,   235,   235,   235,   135,   235,   235,   235,   235,
     235,   235,   146,   138,   135,   135,   135,   148,   135,   135,
     135,   261,   118,   171,   110,   110,    87,     3,     4,     5,
      40,    75,    76,    77,    78,    79,    80,    85,    86,    88,
      89,   101,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   128,   129,   131,   137,    81,    82,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   130,   135,
      84,   240,   241,   134,   138,   140,   247,   118,   235,   256,
     257,   137,   137,   116,   137,   239,   235,   136,   235,   138,
     236,   239,   116,   137,   239,   259,    42,   239,   254,   255,
      87,   135,   227,    84,   247,   137,   137,   130,   116,   137,
     166,   167,   239,   109,   137,   137,   136,    87,   118,   200,
     201,   219,   239,   136,    71,   139,   147,   148,   169,   170,
     235,   235,   219,   239,   235,    53,   217,   218,   235,   235,
     110,   188,    67,   158,   110,   175,    32,   180,   110,   243,
     247,   253,   235,   235,   235,   222,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     118,   235,   200,   110,   138,   243,   250,   251,   252,   241,
     235,   249,   235,   237,   239,    83,   136,   116,   233,   235,
     136,   136,   136,   235,   203,   116,   136,   135,   116,   136,
     243,   200,   250,     9,   110,   121,   122,   228,   229,   230,
     111,   116,   136,   136,   137,   110,   237,   136,   116,   135,
     139,   136,    10,    10,   136,   135,   137,   116,   136,   130,
     116,   136,   135,   173,    32,   178,   110,   182,   221,   138,
     135,   135,   247,   139,   132,    43,   239,   136,   235,   135,
     242,   134,   138,   141,   139,   118,   235,   118,   235,   139,
     239,   254,   255,   130,   136,   224,   135,    87,   229,   229,
     130,   167,   137,   118,   219,   239,   136,   132,   148,   237,
     118,   184,   237,   132,   148,   192,   235,   217,   235,   132,
     138,   189,   229,   110,   132,   148,   187,   221,   135,   221,
      60,   181,   116,   205,   200,   200,   235,   222,   139,   200,
     249,   235,   237,   237,    83,   136,   235,    84,   225,   229,
     232,   234,   110,   229,   237,   137,   146,   193,    83,   183,
     237,   183,   146,   136,   137,   137,   190,   137,   190,   130,
     146,   111,     9,   110,   197,   198,   199,   182,   138,   221,
      14,    48,    52,    57,    61,    62,    63,    64,   139,   206,
     210,   211,   212,   213,   215,   136,   136,   227,   136,   141,
     139,   118,   235,   250,    83,   136,   116,   233,   194,    21,
      22,   150,   195,   184,   136,   136,    29,   137,   217,   190,
      12,    17,    28,   160,   161,   190,   139,   229,    24,   136,
     136,   116,   111,   118,   205,   110,   111,   214,   159,   213,
     116,   137,   237,   229,   229,    21,   150,   196,   148,   135,
     132,   148,   186,   186,   137,   136,    28,   137,   235,   132,
     137,   191,   139,   137,   261,   261,   199,   130,   111,   139,
     130,   130,   116,   137,   171,   110,    83,   132,   135,    27,
     235,   146,   132,   148,   185,   137,   191,   146,   158,   163,
     164,   165,   111,   118,   229,   130,   176,   229,   229,   111,
     110,   130,   229,   146,   235,   137,   136,    26,   146,   146,
     135,   165,   130,   111,   229,   130,   207,   229,   136,   148,
     137,    25,   221,   229,   130,   229,   135,   132,   137,   111,
     229,   197,   146,   136,   136,   261,   137,   209,   261,   208
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
#line 477 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<Statement*>;
		;}
    break;

  case 5:
#line 484 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 6:
#line 488 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (1)].ast_method));
		;}
    break;

  case 7:
#line 492 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (1)].ast_statement));
		;}
    break;

  case 8:
#line 496 "src/generated_src/php_parser.ypp"
    {
			assert(0);
		;}
    break;

  case 9:
#line 506 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_statement)->push_back_all((yyvsp[(2) - (2)].list_ast_statement));
			(yyval.list_ast_statement) = (yyvsp[(1) - (2)].list_ast_statement);
		;}
    break;

  case 10:
#line 511 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<Statement*>;
		;}
    break;

  case 11:
#line 518 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 12:
#line 522 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (1)].ast_method));
		;}
    break;

  case 13:
#line 526 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (1)].ast_statement));
		;}
    break;

  case 14:
#line 530 "src/generated_src/php_parser.ypp"
    {
			assert(0);
		;}
    break;

  case 15:
#line 537 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 16:
#line 548 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_if) = NEW(If, (NULL, NULL, NULL));
		;}
    break;

  case 17:
#line 555 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_if) = NEW(If, (NULL, NULL, NULL));
		;}
    break;

  case 18:
#line 562 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_foreach) = NEW(Foreach, (NULL, NULL, false, NULL, NULL));
		;}
    break;

  case 19:
#line 569 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_while) = NEW(While, (NULL, NULL));
		;}
    break;

  case 20:
#line 576 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_do) = NEW(Do, (NULL, NULL));
		;}
    break;

  case 21:
#line 583 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_for) = NEW(For, (NULL, NULL, NULL, NULL));
		;}
    break;

  case 22:
#line 590 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_switch) = NEW(Switch, (NULL, NULL));
		;}
    break;

  case 23:
#line 597 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_declare) = NEW(Declare, (NULL, NULL));
		;}
    break;

  case 24:
#line 604 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_try) = NEW(Try, (NULL, NULL));
		;}
    break;

  case 25:
#line 611 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_catch) = NEW(Catch, (NULL, NULL, NULL));
		;}
    break;

  case 26:
#line 618 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method) = NEW(Method, (NULL, NULL));
		;}
    break;

  case 27:
#line 625 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_switch_case) = NEW(Switch_case, (NULL, NULL));
		;}
    break;

  case 28:
#line 632 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_switch_case) = NEW(Switch_case, (NULL, NULL));
		;}
    break;

  case 29:
#line 640 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 30:
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
#line 702 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (5)].ast_while)->expr = (yyvsp[(3) - (5)].ast_expr);
			(yyvsp[(1) - (5)].ast_while)->statements = (yyvsp[(5) - (5)].list_ast_statement);

			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (5)].ast_while));
		;}
    break;

  case 33:
#line 709 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (7)].ast_do)->statements = (yyvsp[(2) - (7)].list_ast_statement);
			(yyvsp[(1) - (7)].ast_do)->expr = (yyvsp[(5) - (7)].ast_expr);
			
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (7)].ast_do));
		;}
    break;

  case 34:
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
#line 725 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (5)].ast_switch)->expr = (yyvsp[(3) - (5)].ast_expr);
			(yyvsp[(1) - (5)].ast_switch)->switch_cases = (yyvsp[(5) - (5)].list_ast_switch_case);
			
			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (5)].ast_switch));
		;}
    break;

  case 36:
#line 732 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Break, (NULL)));
		;}
    break;

  case 37:
#line 736 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Break, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 38:
#line 740 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Continue, (NULL)));
		;}
    break;

  case 39:
#line 744 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Continue, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 40:
#line 748 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Return, (NULL)));
		;}
    break;

  case 41:
#line 752 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Return, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 42:
#line 756 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Return, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 43:
#line 760 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Global, ((yyvsp[(2) - (3)].list_ast_variable_name))));
		;}
    break;

  case 44:
#line 764 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Static_declaration, ((yyvsp[(2) - (3)].list_ast_name_with_default))));
		;}
    break;

  case 45:
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
#line 789 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Eval_expr, ((yyvsp[(1) - (2)].ast_expr))));
		;}
    break;

  case 48:
#line 793 "src/generated_src/php_parser.ypp"
    {
			Method_invocation* fn;
			fn = NEW(Method_invocation, ("use", (yyvsp[(2) - (3)].token_string)));
			fn->attrs->set_true("phc.unparser.no_brackets");
			(yyval.list_ast_statement) = wrap(NEW(Eval_expr, (fn)));
		;}
    break;

  case 49:
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
#line 859 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (5)].ast_declare)->directives = (yyvsp[(3) - (5)].list_ast_directive);
			(yyvsp[(1) - (5)].ast_declare)->statements = (yyvsp[(5) - (5)].list_ast_statement);

			(yyval.list_ast_statement) = wrap((yyvsp[(1) - (5)].ast_declare));
		;}
    break;

  case 53:
#line 866 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Nop, ()));
		;}
    break;

  case 54:
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
#line 887 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = wrap(NEW(Throw, ((yyvsp[(2) - (3)].ast_expr))));
		;}
    break;

  case 56:
#line 894 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_catch) = (yyvsp[(1) - (1)].list_ast_catch);
		;}
    break;

  case 57:
#line 898 "src/generated_src/php_parser.ypp"
    {
			List<Catch*>* catches = new List<Catch*>;
			(yyval.list_ast_catch) = catches;
		;}
    break;

  case 58:
#line 906 "src/generated_src/php_parser.ypp"
    {
			List<Catch*>* catches = new List<Catch*>;
			catches->push_back((yyvsp[(1) - (1)].ast_catch));
			
			(yyval.list_ast_catch) = catches;
		;}
    break;

  case 59:
#line 913 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_catch)->push_back((yyvsp[(2) - (2)].ast_catch));
			
			(yyval.list_ast_catch) = (yyvsp[(1) - (2)].list_ast_catch);
		;}
    break;

  case 60:
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
#line 935 "src/generated_src/php_parser.ypp"
    {
			List<Actual_parameter*>* vars = new List<Actual_parameter*>;
			vars->push_back(new Actual_parameter(false, (yyvsp[(1) - (1)].ast_variable)));
			(yyval.list_ast_actual_parameter) = vars;
		;}
    break;

  case 62:
#line 941 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back(new Actual_parameter(false, (yyvsp[(3) - (3)].ast_variable)));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 63:
#line 949 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = expect_variable((yyvsp[(1) - (1)].ast_expr));
		;}
    break;

  case 64:
#line 956 "src/generated_src/php_parser.ypp"
    {
			(yyval.token_string) = (yyvsp[(1) - (1)].token_string);
		;}
    break;

  case 65:
#line 960 "src/generated_src/php_parser.ypp"
    {
			(yyval.token_string) = (yyvsp[(2) - (3)].token_string);
		;}
    break;

  case 66:
#line 967 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method) = (yyvsp[(1) - (1)].ast_method);
		;}
    break;

  case 67:
#line 974 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_statement) = (yyvsp[(1) - (1)].ast_statement);
		;}
    break;

  case 68:
#line 981 "src/generated_src/php_parser.ypp"
    {
			(yyval.integer) = new Integer(0);
		;}
    break;

  case 69:
#line 985 "src/generated_src/php_parser.ypp"
    {
			(yyval.integer) = new Integer(1);
		;}
    break;

  case 70:
#line 991 "src/generated_src/php_parser.ypp"
    {context->current_method = dynamic_cast<String*>((yyvsp[(3) - (3)].string));;}
    break;

  case 71:
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
#line 1004 "src/generated_src/php_parser.ypp"
    {context->current_class = dynamic_cast<String*>((yyvsp[(2) - (2)].string));;}
    break;

  case 73:
#line 1004 "src/generated_src/php_parser.ypp"
    {context->current_class = new String ();;}
    break;

  case 74:
#line 1005 "src/generated_src/php_parser.ypp"
    {
			CLASS_NAME* name = new CLASS_NAME((yyvsp[(2) - (9)].string));

			(yyvsp[(1) - (9)].ast_class_def)->class_name = name;
			(yyvsp[(1) - (9)].ast_class_def)->extends = (yyvsp[(4) - (9)].token_class_name);
			(yyvsp[(1) - (9)].ast_class_def)->implements = (yyvsp[(5) - (9)].list_token_interface_name);
			(yyvsp[(1) - (9)].ast_class_def)->members = (yyvsp[(7) - (9)].list_ast_member);

			(yyval.ast_statement) = (yyvsp[(1) - (9)].ast_class_def);
		;}
    break;

  case 75:
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
#line 1039 "src/generated_src/php_parser.ypp"
    {
			Class_mod* mod = NEW(Class_mod, (false, false));
			(yyval.ast_class_def) = NEW(Class_def, (mod));
		;}
    break;

  case 77:
#line 1044 "src/generated_src/php_parser.ypp"
    {
			Class_mod* mod = NEW(Class_mod, (true, false));
			(yyval.ast_class_def) = NEW(Class_def, (mod));
		;}
    break;

  case 78:
#line 1049 "src/generated_src/php_parser.ypp"
    {
			Class_mod* mod = NEW(Class_mod, (false, true));
			(yyval.ast_class_def) = NEW(Class_def, (mod));
		;}
    break;

  case 79:
#line 1057 "src/generated_src/php_parser.ypp"
    {
			(yyval.token_class_name) = NULL;
		;}
    break;

  case 80:
#line 1061 "src/generated_src/php_parser.ypp"
    {
			(yyval.token_class_name) = (yyvsp[(2) - (2)].token_class_name);
		;}
    break;

  case 81:
#line 1068 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_interface_def) = NEW(Interface_def, (NULL, NULL, NULL));
		;}
    break;

  case 82:
#line 1075 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_token_interface_name) = new List<INTERFACE_NAME*>;
		;}
    break;

  case 83:
#line 1079 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_token_interface_name) = (yyvsp[(2) - (2)].list_token_interface_name);
		;}
    break;

  case 84:
#line 1089 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_token_interface_name) = new List<INTERFACE_NAME*>;
		;}
    break;

  case 85:
#line 1093 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_token_interface_name) = (yyvsp[(2) - (2)].list_token_interface_name);
		;}
    break;

  case 86:
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
#line 1110 "src/generated_src/php_parser.ypp"
    {
			INTERFACE_NAME* ifn = NEW(INTERFACE_NAME, ((yyvsp[(3) - (3)].token_class_name)->value));
			(yyvsp[(1) - (3)].list_token_interface_name)->push_back(ifn);
			
			(yyval.list_token_interface_name) = (yyvsp[(1) - (3)].list_token_interface_name);
		;}
    break;

  case 88:
#line 1120 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = NULL;
		;}
    break;

  case 89:
#line 1124 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(2) - (2)].ast_variable);
		;}
    break;

  case 90:
#line 1131 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = expect_variable((yyvsp[(1) - (1)].ast_expr));
		;}
    break;

  case 91:
#line 1135 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (2)].ast_expr)->attrs->set_true("phc.parser.is_ref");
			(yyval.ast_variable) = expect_variable((yyvsp[(2) - (2)].ast_expr));
		;}
    break;

  case 92:
#line 1143 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 93:
#line 1147 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (4)].list_ast_statement);
		;}
    break;

  case 94:
#line 1154 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 95:
#line 1158 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (4)].list_ast_statement);
		;}
    break;

  case 96:
#line 1165 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 97:
#line 1169 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (4)].list_ast_statement);
		;}
    break;

  case 98:
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
#line 1186 "src/generated_src/php_parser.ypp"
    {
			DIRECTIVE_NAME* name = NEW (DIRECTIVE_NAME, ((yyvsp[(3) - (5)].string)));
			
			Directive* dir = NEW(Directive, (name, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].list_ast_directive)->push_back(dir);
			(yyval.list_ast_directive) = (yyvsp[(1) - (5)].list_ast_directive);
		;}
    break;

  case 100:
#line 1197 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = (yyvsp[(2) - (3)].list_ast_switch_case);
		;}
    break;

  case 101:
#line 1201 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = (yyvsp[(3) - (4)].list_ast_switch_case);
		;}
    break;

  case 102:
#line 1205 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = (yyvsp[(2) - (4)].list_ast_switch_case);
		;}
    break;

  case 103:
#line 1209 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = (yyvsp[(3) - (5)].list_ast_switch_case);
		;}
    break;

  case 104:
#line 1216 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_switch_case) = new List<Switch_case*>;
		;}
    break;

  case 105:
#line 1220 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (5)].ast_switch_case)->statements = (yyvsp[(5) - (5)].list_ast_statement);
			(yyvsp[(2) - (5)].ast_switch_case)->expr = (yyvsp[(3) - (5)].ast_expr);
			
			(yyvsp[(1) - (5)].list_ast_switch_case)->push_back((yyvsp[(2) - (5)].ast_switch_case));
			
			(yyval.list_ast_switch_case) = (yyvsp[(1) - (5)].list_ast_switch_case);
		;}
    break;

  case 106:
#line 1229 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (4)].ast_switch_case)->statements = (yyvsp[(4) - (4)].list_ast_statement);
			(yyvsp[(2) - (4)].ast_switch_case)->expr = NULL;
			
			(yyvsp[(1) - (4)].list_ast_switch_case)->push_back((yyvsp[(2) - (4)].ast_switch_case));
			
			(yyval.list_ast_switch_case) = (yyvsp[(1) - (4)].list_ast_switch_case);
		;}
    break;

  case 109:
#line 1249 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 110:
#line 1253 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (4)].list_ast_statement);
		;}
    break;

  case 111:
#line 1260 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_if) = NULL;
		;}
    break;

  case 112:
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
#line 1300 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_if) = NULL;
		;}
    break;

  case 114:
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
#line 1333 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<Statement*>;
		;}
    break;

  case 116:
#line 1337 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(2) - (2)].list_ast_statement);
		;}
    break;

  case 117:
#line 1347 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = new List<Statement*>;
		;}
    break;

  case 118:
#line 1351 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(3) - (3)].list_ast_statement);
		;}
    break;

  case 119:
#line 1358 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (1)].list_ast_formal_parameter);
		;}
    break;

  case 120:
#line 1362 "src/generated_src/php_parser.ypp"
    {
			List<Formal_parameter*>* params = new List<Formal_parameter*>;
			(yyval.list_ast_formal_parameter) = params;
		;}
    break;

  case 121:
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
#line 1417 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(4) - (4)].string));
			
			(yyvsp[(1) - (4)].list_ast_formal_parameter)->push_back(NEW(Formal_parameter, ((yyvsp[(3) - (4)].ast_type), name)));
			
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (4)].list_ast_formal_parameter);
		;}
    break;

  case 126:
#line 1425 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(5) - (5)].string));
			
			(yyvsp[(1) - (5)].list_ast_formal_parameter)->push_back(NEW(Formal_parameter, ((yyvsp[(3) - (5)].ast_type), true, name)));
			
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (5)].list_ast_formal_parameter);
		;}
    break;

  case 127:
#line 1433 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(5) - (7)].string));
			
			(yyvsp[(1) - (7)].list_ast_formal_parameter)->push_back(NEW(Formal_parameter, ((yyvsp[(3) - (7)].ast_type), true, NEW(Name_with_default, (name, (yyvsp[(7) - (7)].ast_expr))))));
			
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (7)].list_ast_formal_parameter);
		;}
    break;

  case 128:
#line 1441 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(4) - (6)].string));
			
			(yyvsp[(1) - (6)].list_ast_formal_parameter)->push_back(NEW(Formal_parameter, ((yyvsp[(3) - (6)].ast_type), false, NEW(Name_with_default, (name, (yyvsp[(6) - (6)].ast_expr))))));
			
			(yyval.list_ast_formal_parameter) = (yyvsp[(1) - (6)].list_ast_formal_parameter);
		;}
    break;

  case 129:
#line 1452 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_type) = NEW(Type, (NULL));
		;}
    break;

  case 130:
#line 1456 "src/generated_src/php_parser.ypp"
    {
			CLASS_NAME* class_name = new CLASS_NAME((yyvsp[(1) - (1)].string));
			(yyval.ast_type) = NEW(Type, (class_name));
		;}
    break;

  case 131:
#line 1461 "src/generated_src/php_parser.ypp"
    {
			CLASS_NAME* class_name = new CLASS_NAME(new String ("array"));
			(yyval.ast_type) = NEW(Type, (class_name));
		;}
    break;

  case 132:
#line 1469 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (1)].list_ast_actual_parameter);
		;}
    break;

  case 133:
#line 1473 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = new List<Actual_parameter*>;
		;}
    break;

  case 134:
#line 1480 "src/generated_src/php_parser.ypp"
    {
			List<Actual_parameter*>* list = new List<Actual_parameter*>;
			list->push_back(NEW(Actual_parameter, (false, (yyvsp[(1) - (1)].ast_expr))));
			(yyval.list_ast_actual_parameter) = list;
		;}
    break;

  case 135:
#line 1486 "src/generated_src/php_parser.ypp"
    {
			List<Actual_parameter*>* list = new List<Actual_parameter*>;
			list->push_back(NEW(Actual_parameter, (false, (yyvsp[(1) - (1)].ast_expr))));
			(yyval.list_ast_actual_parameter) = list;
		;}
    break;

  case 136:
#line 1492 "src/generated_src/php_parser.ypp"
    {
			List<Actual_parameter*>* list = new List<Actual_parameter*>;
			list->push_back(NEW(Actual_parameter, (true, (yyvsp[(2) - (2)].ast_expr))));
			(yyval.list_ast_actual_parameter) = list;
		;}
    break;

  case 137:
#line 1498 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back(NEW(Actual_parameter, (false, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 138:
#line 1503 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back(NEW(Actual_parameter, (false, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 139:
#line 1508 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (4)].list_ast_actual_parameter)->push_back(NEW(Actual_parameter, (true, (yyvsp[(4) - (4)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (4)].list_ast_actual_parameter);
		;}
    break;

  case 140:
#line 1516 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_variable_name)->push_back((yyvsp[(3) - (3)].ast_variable_name));
			(yyval.list_ast_variable_name) = (yyvsp[(1) - (3)].list_ast_variable_name);
		;}
    break;

  case 141:
#line 1521 "src/generated_src/php_parser.ypp"
    {
			List<Variable_name*>* list = new List<Variable_name*>;
			list->push_back((yyvsp[(1) - (1)].ast_variable_name));
			
			(yyval.list_ast_variable_name) = list;
		;}
    break;

  case 142:
#line 1531 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable_name) = NEW(VARIABLE_NAME, ((yyvsp[(1) - (1)].string)));
		;}
    break;

  case 143:
#line 1535 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable_name) = NEW(Reflection, ((yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 144:
#line 1539 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(3) - (4)].ast_expr)->attrs->set_true("phc.unparser.needs_user_curlies");
			(yyval.ast_variable_name) = NEW(Reflection, ((yyvsp[(3) - (4)].ast_expr)));
		;}
    break;

  case 145:
#line 1547 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(3) - (3)].string));
			(yyvsp[(1) - (3)].list_ast_name_with_default)->push_back(NEW(Name_with_default, (name, NULL)));
			(yyval.list_ast_name_with_default) = (yyvsp[(1) - (3)].list_ast_name_with_default);
		;}
    break;

  case 146:
#line 1553 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(3) - (5)].string));
			(yyvsp[(1) - (5)].list_ast_name_with_default)->push_back(NEW(Name_with_default, (name, (yyvsp[(5) - (5)].ast_expr))));
			(yyval.list_ast_name_with_default) = (yyvsp[(1) - (5)].list_ast_name_with_default);
		;}
    break;

  case 147:
#line 1559 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(1) - (1)].string));
			List<Name_with_default*>* list = new List<Name_with_default*>;
			list->push_back(NEW(Name_with_default, (name, NULL)));
			(yyval.list_ast_name_with_default) = list;
		;}
    break;

  case 148:
#line 1566 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(1) - (3)].string));
			List<Name_with_default*>* list = new List<Name_with_default*>;
			list->push_back(NEW(Name_with_default, (name, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_name_with_default) = list;
		;}
    break;

  case 149:
#line 1576 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_member)->push_back((yyvsp[(2) - (2)].ast_member));
			(yyval.list_ast_member) = (yyvsp[(1) - (2)].list_ast_member);
		;}
    break;

  case 150:
#line 1581 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_member) = new List<Member*>;
		;}
    break;

  case 151:
#line 1588 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_member) = NEW(Attribute, ((yyvsp[(1) - (3)].ast_attr_mod), (yyvsp[(2) - (3)].list_ast_name_with_default)));
		;}
    break;

  case 152:
#line 1592 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_member) = (yyvsp[(1) - (2)].ast_attribute);
		;}
    break;

  case 153:
#line 1595 "src/generated_src/php_parser.ypp"
    {context->current_method = dynamic_cast<String*>((yyvsp[(4) - (4)].string));;}
    break;

  case 154:
#line 1595 "src/generated_src/php_parser.ypp"
    {context->current_method = new String;;}
    break;

  case 155:
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
#line 1609 "src/generated_src/php_parser.ypp"
    {
			// Abstract method
			(yyval.list_ast_statement) = NULL;
		;}
    break;

  case 157:
#line 1614 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_statement) = (yyvsp[(1) - (1)].list_ast_statement);
		;}
    break;

  case 158:
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
#line 1630 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_attr_mod) = NEW(Attr_mod, (false, false, false, false, false));
		;}
    break;

  case 160:
#line 1637 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = new Method_mod();
		;}
    break;

  case 161:
#line 1641 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = (yyvsp[(1) - (1)].ast_method_mod);
		;}
    break;

  case 162:
#line 1648 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = (yyvsp[(1) - (1)].ast_method_mod);
		;}
    break;

  case 163:
#line 1652 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = NEW(Method_mod, ((yyvsp[(1) - (2)].ast_method_mod), (yyvsp[(2) - (2)].ast_method_mod)));
		;}
    break;

  case 164:
#line 1659 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = Method_mod::new_PUBLIC();
		;}
    break;

  case 165:
#line 1663 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = Method_mod::new_PROTECTED();
		;}
    break;

  case 166:
#line 1667 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = Method_mod::new_PRIVATE();
		;}
    break;

  case 167:
#line 1671 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = Method_mod::new_STATIC();
		;}
    break;

  case 168:
#line 1675 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = Method_mod::new_ABSTRACT();
		;}
    break;

  case 169:
#line 1679 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_mod) = Method_mod::new_FINAL();
		;}
    break;

  case 170:
#line 1686 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(3) - (3)].string));
			(yyvsp[(1) - (3)].list_ast_name_with_default)->push_back(NEW(Name_with_default, (name, NULL)));
			(yyval.list_ast_name_with_default) = (yyvsp[(1) - (3)].list_ast_name_with_default);
		;}
    break;

  case 171:
#line 1692 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(3) - (5)].string));
			(yyvsp[(1) - (5)].list_ast_name_with_default)->push_back(NEW(Name_with_default, (name, (yyvsp[(5) - (5)].ast_expr))));
			(yyval.list_ast_name_with_default) = (yyvsp[(1) - (5)].list_ast_name_with_default);
		;}
    break;

  case 172:
#line 1698 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(1) - (1)].string));
			List<Name_with_default*>* vars = new List<Name_with_default*>;
			vars->push_back(NEW(Name_with_default, (name, NULL)));
			(yyval.list_ast_name_with_default) = vars;
		;}
    break;

  case 173:
#line 1705 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(1) - (3)].string));
			List<Name_with_default*>* vars = new List<Name_with_default*>;
			vars->push_back(NEW(Name_with_default, (name, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_name_with_default) = vars;
		;}
    break;

  case 174:
#line 1715 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* name = new VARIABLE_NAME((yyvsp[(3) - (5)].string));
			Name_with_default* var = NEW(Name_with_default, (name, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].ast_attribute)->vars->push_back(var);
			(yyval.ast_attribute) = (yyvsp[(1) - (5)].ast_attribute);
		;}
    break;

  case 175:
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
#line 1744 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back (NEW (Actual_parameter, (false, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 177:
#line 1749 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = new List<Actual_parameter*>;
			(yyval.list_ast_actual_parameter)->push_back(NEW(Actual_parameter, (false, (yyvsp[(1) - (1)].ast_expr))));
		;}
    break;

  case 178:
#line 1757 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NULL;
		;}
    break;

  case 179:
#line 1761 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr)
		;}
    break;

  case 180:
#line 1771 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 181:
#line 1776 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 182:
#line 1783 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(List_assignment, ((yyvsp[(3) - (6)].ast_nested_list_elements)->list_elements, (yyvsp[(6) - (6)].ast_expr)));
		;}
    break;

  case 183:
#line 1787 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Assignment, (expect_variable((yyvsp[(1) - (3)].ast_expr)), false, (yyvsp[(3) - (3)].ast_expr)));
		;}
    break;

  case 184:
#line 1791 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Assignment, (expect_variable((yyvsp[(1) - (4)].ast_expr)), true, (yyvsp[(4) - (4)].ast_expr)));
		;}
    break;

  case 185:
#line 1795 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(6) - (6)].ast_new)->class_name = (yyvsp[(5) - (6)].ast_class_name);
			(yyval.ast_expr) = NEW(Assignment, (expect_variable((yyvsp[(1) - (6)].ast_expr)), true, (yyvsp[(6) - (6)].ast_new)));
		;}
    break;

  case 186:
#line 1800 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(3) - (3)].ast_new)->class_name = (yyvsp[(2) - (3)].ast_class_name);
			(yyval.ast_expr) = (yyvsp[(3) - (3)].ast_new);
		;}
    break;

  case 187:
#line 1805 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Method_invocation, ("clone", (yyvsp[(2) - (2)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 188:
#line 1810 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "+", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 189:
#line 1815 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "-", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 190:
#line 1820 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "*", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 191:
#line 1825 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "/", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 192:
#line 1830 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, ".", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 193:
#line 1835 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "%", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 194:
#line 1840 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "&", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 195:
#line 1845 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "|", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 196:
#line 1850 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "^", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 197:
#line 1855 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, "<<", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 198:
#line 1860 "src/generated_src/php_parser.ypp"
    {
			Variable* var = expect_variable((yyvsp[(1) - (3)].ast_expr));
			(yyval.ast_expr) = new Op_assignment(var, ">>", (yyvsp[(3) - (3)].ast_expr));
		;}
    break;

  case 199:
#line 1865 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Post_op, (expect_variable((yyvsp[(1) - (2)].ast_expr)), "++"));
		;}
    break;

  case 200:
#line 1869 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Pre_op, (expect_variable((yyvsp[(2) - (2)].ast_expr)), "++"));
		;}
    break;

  case 201:
#line 1873 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Post_op, (expect_variable((yyvsp[(1) - (2)].ast_expr)), "--"));
		;}
    break;

  case 202:
#line 1877 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Pre_op, (expect_variable((yyvsp[(2) - (2)].ast_expr)), "--"));
		;}
    break;

  case 203:
#line 1881 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 204:
#line 1886 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 205:
#line 1891 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 206:
#line 1896 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 207:
#line 1901 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 208:
#line 1906 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 209:
#line 1911 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 210:
#line 1916 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 211:
#line 1921 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 212:
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
#line 1937 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 214:
#line 1942 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 215:
#line 1947 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 216:
#line 1952 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 217:
#line 1957 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 218:
#line 1962 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 219:
#line 1967 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 220:
#line 1972 "src/generated_src/php_parser.ypp"
    {
			// We ignore unary plus
			(yyval.ast_expr) = (yyvsp[(2) - (2)].ast_expr);
		;}
    break;

  case 221:
#line 1977 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Unary_op, ((yyvsp[(1) - (2)].token_op), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 222:
#line 1981 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Unary_op, ((yyvsp[(1) - (2)].token_op), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 223:
#line 1985 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Unary_op, ((yyvsp[(1) - (2)].token_op), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 224:
#line 1989 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 225:
#line 1994 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 226:
#line 1999 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 227:
#line 2004 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 228:
#line 2009 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 229:
#line 2014 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 230:
#line 2019 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 231:
#line 2024 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Bin_op, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(2) - (3)].token_op), (yyvsp[(3) - (3)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_binop_brackets");
		;}
    break;

  case 232:
#line 2029 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Instanceof, ((yyvsp[(1) - (3)].ast_expr), (yyvsp[(3) - (3)].ast_class_name)));
		;}
    break;

  case 233:
#line 2033 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (3)].ast_expr)->attrs->set_true("phc.unparser.needs_user_brackets");
			
			(yyval.ast_expr) = (yyvsp[(2) - (3)].ast_expr);
		;}
    break;

  case 234:
#line 2039 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Conditional_expr, ((yyvsp[(1) - (5)].ast_expr), (yyvsp[(3) - (5)].ast_expr), (yyvsp[(5) - (5)].ast_expr)));
		;}
    break;

  case 235:
#line 2043 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_method_invocation);
		;}
    break;

  case 236:
#line 2047 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("int", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 237:
#line 2051 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("real", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 238:
#line 2055 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("string", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 239:
#line 2059 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("array", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 240:
#line 2063 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("object", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 241:
#line 2067 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("bool", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 242:
#line 2071 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Cast, ("unset", (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 243:
#line 2075 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(2) - (2)].ast_method_invocation);
		;}
    break;

  case 244:
#line 2079 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Ignore_errors, ((yyvsp[(2) - (2)].ast_expr)));
		;}
    break;

  case 245:
#line 2083 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 246:
#line 2087 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Array, ((yyvsp[(3) - (4)].list_ast_array_elem)));
		;}
    break;

  case 247:
#line 2091 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Method_invocation, ("print", (yyvsp[(2) - (2)].ast_expr)));
			(yyval.ast_expr)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 248:
#line 2099 "src/generated_src/php_parser.ypp"
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

  case 249:
#line 2113 "src/generated_src/php_parser.ypp"
    {
			METHOD_NAME* fn = new METHOD_NAME((yyvsp[(3) - (6)].string));

			(yyval.ast_method_invocation) = NEW(Method_invocation, ((yyvsp[(1) - (6)].token_class_name), fn, (yyvsp[(5) - (6)].list_ast_actual_parameter)));
		;}
    break;

  case 250:
#line 2119 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ((yyvsp[(1) - (6)].token_class_name), NEW(Reflection, ((yyvsp[(3) - (6)].ast_variable))), (yyvsp[(5) - (6)].list_ast_actual_parameter)));
		;}
    break;

  case 251:
#line 2123 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, (NULL, NEW(Reflection, ((yyvsp[(1) - (4)].ast_variable))), (yyvsp[(3) - (4)].list_ast_actual_parameter)));
		;}
    break;

  case 252:
#line 2130 "src/generated_src/php_parser.ypp"
    {
			CLASS_NAME* name = new CLASS_NAME((yyvsp[(1) - (1)].string));
			(yyval.token_class_name) = name;
		;}
    break;

  case 253:
#line 2138 "src/generated_src/php_parser.ypp"
    {
			CLASS_NAME* name = new CLASS_NAME((yyvsp[(1) - (1)].string));

			(yyval.ast_class_name) = name;
		;}
    break;

  case 254:
#line 2144 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_class_name) = NEW(Reflection, ((yyvsp[(1) - (1)].ast_variable)));
		;}
    break;

  case 255:
#line 2155 "src/generated_src/php_parser.ypp"
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

  case 256:
#line 2168 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 257:
#line 2175 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_variable)->push_back((yyvsp[(2) - (2)].ast_variable));
			(yyval.list_ast_variable) = (yyvsp[(1) - (2)].list_ast_variable);
		;}
    break;

  case 258:
#line 2180 "src/generated_src/php_parser.ypp"
    {
			List<Variable*>* vars = new List<Variable*>;
			(yyval.list_ast_variable) = vars;
		;}
    break;

  case 259:
#line 2188 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(2) - (2)].ast_variable);
		;}
    break;

  case 260:
#line 2198 "src/generated_src/php_parser.ypp"
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

  case 261:
#line 2210 "src/generated_src/php_parser.ypp"
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

  case 262:
#line 2221 "src/generated_src/php_parser.ypp"
    {
			Actual_parameter* arg = NEW(Actual_parameter, (false, (yyvsp[(2) - (3)].ast_expr)));
			(yyval.ast_method_invocation) = NEW(Method_invocation,
				( NULL
				, new METHOD_NAME(new String("exit"))
				, new List<Actual_parameter*>(arg)
				));
		;}
    break;

  case 263:
#line 2237 "src/generated_src/php_parser.ypp"
    {
			List<Actual_parameter*>* args = new List<Actual_parameter*>;
			
			(yyval.ast_new) = NEW(New, (NULL, args));
			(yyval.ast_new)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 264:
#line 2244 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_new) = NEW(New, (NULL, (yyvsp[(2) - (3)].list_ast_actual_parameter)));
		;}
    break;

  case 265:
#line 2251 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_int);
		;}
    break;

  case 266:
#line 2255 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_real);
		;}
    break;

  case 267:
#line 2259 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_string);
		;}
    break;

  case 268:
#line 2263 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_bool);
		;}
    break;

  case 269:
#line 2267 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_bool);
		;}
    break;

  case 270:
#line 2271 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_null);
		;}
    break;

  case 271:
#line 2275 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_int);
		;}
    break;

  case 272:
#line 2279 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_string);
		;}
    break;

  case 273:
#line 2283 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_string);
		;}
    break;

  case 274:
#line 2287 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_string);
		;}
    break;

  case 275:
#line 2291 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].token_string);
		;}
    break;

  case 276:
#line 2298 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 277:
#line 2302 "src/generated_src/php_parser.ypp"
    {
			CONSTANT_NAME* name = new CONSTANT_NAME((yyvsp[(1) - (1)].string));
			(yyval.ast_expr) = NEW(Constant, (NULL, name));
		;}
    break;

  case 278:
#line 2307 "src/generated_src/php_parser.ypp"
    {
			// We simply ignore the +
			(yyval.ast_expr) = (yyvsp[(2) - (2)].ast_expr);
		;}
    break;

  case 279:
#line 2312 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Unary_op, ((yyvsp[(2) - (2)].ast_expr), "-"));
		;}
    break;

  case 280:
#line 2316 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NEW(Array, ((yyvsp[(3) - (4)].list_ast_array_elem)));
		;}
    break;

  case 281:
#line 2320 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_constant);
		;}
    break;

  case 282:
#line 2327 "src/generated_src/php_parser.ypp"
    {
			CLASS_NAME* class_name = new CLASS_NAME((yyvsp[(1) - (3)].string));
			CONSTANT_NAME* constant = new CONSTANT_NAME((yyvsp[(3) - (3)].string));
			
			(yyval.ast_constant) = NEW(Constant, (class_name, constant));
		;}
    break;

  case 283:
#line 2337 "src/generated_src/php_parser.ypp"
    {
			CONSTANT_NAME* name = new CONSTANT_NAME((yyvsp[(1) - (1)].string));

			(yyval.ast_expr) = NEW(Constant, (NULL, name));
		;}
    break;

  case 284:
#line 2343 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_constant);
		;}
    break;

  case 285:
#line 2347 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 286:
#line 2354 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_array_elem) = new List<Array_elem*>;
		;}
    break;

  case 287:
#line 2358 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (2)].list_ast_array_elem);
		;}
    break;

  case 290:
#line 2373 "src/generated_src/php_parser.ypp"
    {
			Array_elem* elem = NEW(Array_elem, ((yyvsp[(3) - (5)].ast_expr), false, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].list_ast_array_elem)->push_back(elem);

			(yyval.list_ast_array_elem) = (yyvsp[(1) - (5)].list_ast_array_elem);
		;}
    break;

  case 291:
#line 2380 "src/generated_src/php_parser.ypp"
    {
			Array_elem* elem = NEW(Array_elem, (NULL, false, (yyvsp[(3) - (3)].ast_expr)));
			(yyvsp[(1) - (3)].list_ast_array_elem)->push_back(elem);
			
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (3)].list_ast_array_elem);
		;}
    break;

  case 292:
#line 2387 "src/generated_src/php_parser.ypp"
    {
			List<Array_elem*>* list = new List<Array_elem*>;
			Array_elem* elem = NEW(Array_elem, ((yyvsp[(1) - (3)].ast_expr), false, (yyvsp[(3) - (3)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 293:
#line 2395 "src/generated_src/php_parser.ypp"
    {
			List<Array_elem*>* list = new List<Array_elem*>;
			Array_elem* elem = NEW(Array_elem, (NULL, false, (yyvsp[(1) - (1)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 294:
#line 2406 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 295:
#line 2410 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 296:
#line 2417 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 297:
#line 2424 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 298:
#line 2431 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 299:
#line 2455 "src/generated_src/php_parser.ypp"
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

  case 300:
#line 2487 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 301:
#line 2498 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (2)].list_ast_expr)->push_back((yyvsp[(2) - (2)].ast_expr));
			
			(yyval.list_ast_expr) = (yyvsp[(1) - (2)].list_ast_expr);
		;}
    break;

  case 302:
#line 2504 "src/generated_src/php_parser.ypp"
    {
			List<Expr*>* props = new List<Expr*>;
			props->push_back((yyvsp[(1) - (1)].ast_expr));
			
			(yyval.list_ast_expr) = props;
		;}
    break;

  case 303:
#line 2533 "src/generated_src/php_parser.ypp"
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

  case 304:
#line 2571 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = (yyvsp[(2) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 305:
#line 2575 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_actual_parameter) = NULL;
		;}
    break;

  case 306:
#line 2582 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 307:
#line 2586 "src/generated_src/php_parser.ypp"
    {
			for(long i = 0; i < (yyvsp[(1) - (2)].integer)->value(); i++)
			{
				(yyvsp[(2) - (2)].ast_variable) = NEW(Variable, (NEW(Reflection, ((yyvsp[(2) - (2)].ast_variable)))));
			}
			
			(yyval.ast_variable) = (yyvsp[(2) - (2)].ast_variable);
		;}
    break;

  case 308:
#line 2598 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(3) - (3)].ast_variable)->target = (yyvsp[(1) - (3)].token_class_name);
			(yyval.ast_variable) = (yyvsp[(3) - (3)].ast_variable);
		;}
    break;

  case 309:
#line 2606 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 310:
#line 2610 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_method_invocation);
		;}
    break;

  case 311:
#line 2617 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 312:
#line 2621 "src/generated_src/php_parser.ypp"
    {
			for(long i = 0; i < (yyvsp[(1) - (2)].integer)->value(); i++)
			{
				(yyvsp[(2) - (2)].ast_variable) = NEW(Variable, (NEW(Reflection, ((yyvsp[(2) - (2)].ast_variable)))));
			}

			(yyval.ast_variable) = (yyvsp[(2) - (2)].ast_variable);
		;}
    break;

  case 313:
#line 2630 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 314:
#line 2637 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (4)].ast_variable)->array_indices->push_back((yyvsp[(3) - (4)].ast_expr));
			(yyval.ast_variable) = (yyvsp[(1) - (4)].ast_variable);
		;}
    break;

  case 315:
#line 2642 "src/generated_src/php_parser.ypp"
    {
			if((yyvsp[(3) - (4)].ast_expr) != NULL)
				(yyvsp[(3) - (4)].ast_expr)->attrs->set_true("phc.unparser.index_curlies");

			(yyvsp[(1) - (4)].ast_variable)->array_indices->push_back((yyvsp[(3) - (4)].ast_expr));
			(yyval.ast_variable) = (yyvsp[(1) - (4)].ast_variable);
		;}
    break;

  case 316:
#line 2650 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = NEW(Variable, ((yyvsp[(1) - (1)].ast_variable_name)));
		;}
    break;

  case 317:
#line 2657 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* var = new VARIABLE_NAME((yyvsp[(1) - (1)].string));
			(yyval.ast_variable_name) = var;
		;}
    break;

  case 318:
#line 2662 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(3) - (4)].ast_expr)->attrs->set_true("phc.unparser.needs_user_curlies");
			(yyval.ast_variable_name) = NEW(Reflection, ((yyvsp[(3) - (4)].ast_expr)));
		;}
    break;

  case 319:
#line 2670 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = NULL;
		;}
    break;

  case 320:
#line 2674 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_expr) = (yyvsp[(1) - (1)].ast_expr);
		;}
    break;

  case 321:
#line 2681 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = (yyvsp[(1) - (1)].ast_variable);
		;}
    break;

  case 322:
#line 2685 "src/generated_src/php_parser.ypp"
    {
			// This is a "normal" variable (which includes a $), i.e. $x->$y
			// So, we need to add a level of indirection
			(yyval.ast_variable) = NEW(Variable, (NEW(Reflection, ((yyvsp[(1) - (1)].ast_variable)))));
		;}
    break;

  case 323:
#line 2697 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (4)].ast_variable)->array_indices->push_back((yyvsp[(3) - (4)].ast_expr));
			(yyval.ast_variable) = (yyvsp[(1) - (4)].ast_variable);
		;}
    break;

  case 324:
#line 2702 "src/generated_src/php_parser.ypp"
    {
			if((yyvsp[(3) - (4)].ast_expr) != NULL)
				(yyvsp[(3) - (4)].ast_expr)->attrs->set_true("phc.unparser.index_curlies");

			(yyvsp[(1) - (4)].ast_variable)->array_indices->push_back((yyvsp[(3) - (4)].ast_expr));
			(yyval.ast_variable) = (yyvsp[(1) - (4)].ast_variable);
		;}
    break;

  case 325:
#line 2710 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_variable) = NEW(Variable, ((yyvsp[(1) - (1)].ast_variable_name)));
		;}
    break;

  case 326:
#line 2720 "src/generated_src/php_parser.ypp"
    {
			VARIABLE_NAME* var = new VARIABLE_NAME((yyvsp[(1) - (1)].string));
			(yyval.ast_variable_name) = var;
		;}
    break;

  case 327:
#line 2725 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(2) - (3)].ast_expr)->attrs->set_true("phc.unparser.needs_user_curlies");
			(yyval.ast_variable_name) = NEW(Reflection, ((yyvsp[(2) - (3)].ast_expr)));
		;}
    break;

  case 328:
#line 2736 "src/generated_src/php_parser.ypp"
    {
			(yyval.integer) = new Integer(1);
		;}
    break;

  case 329:
#line 2740 "src/generated_src/php_parser.ypp"
    {
			(*(yyvsp[(1) - (2)].integer))++;
			(yyval.integer) = (yyvsp[(1) - (2)].integer);
		;}
    break;

  case 330:
#line 2748 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].ast_nested_list_elements)->list_elements->push_back((yyvsp[(3) - (3)].ast_list_element));
			
			(yyval.ast_nested_list_elements) = (yyvsp[(1) - (3)].ast_nested_list_elements);
		;}
    break;

  case 331:
#line 2754 "src/generated_src/php_parser.ypp"
    {
			List<List_element*>* elements = new List<List_element*>;
			elements->push_back((yyvsp[(1) - (1)].ast_list_element));
			
			(yyval.ast_nested_list_elements) = NEW(Nested_list_elements, (elements));
		;}
    break;

  case 332:
#line 2767 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_list_element) = expect_variable((yyvsp[(1) - (1)].ast_expr));
		;}
    break;

  case 333:
#line 2771 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_list_element) = (yyvsp[(3) - (4)].ast_nested_list_elements);
		;}
    break;

  case 334:
#line 2775 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_list_element) = NULL;
		;}
    break;

  case 335:
#line 2782 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_array_elem) = new List<Array_elem*>;
		;}
    break;

  case 336:
#line 2786 "src/generated_src/php_parser.ypp"
    {
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (2)].list_ast_array_elem);
		;}
    break;

  case 337:
#line 2796 "src/generated_src/php_parser.ypp"
    {
			Array_elem* elem = NEW(Array_elem, ((yyvsp[(3) - (5)].ast_expr), false, (yyvsp[(5) - (5)].ast_expr)));
			(yyvsp[(1) - (5)].list_ast_array_elem)->push_back(elem);

			(yyval.list_ast_array_elem) = (yyvsp[(1) - (5)].list_ast_array_elem);
		;}
    break;

  case 338:
#line 2803 "src/generated_src/php_parser.ypp"
    {
			Array_elem* elem = NEW(Array_elem, (NULL, false, (yyvsp[(3) - (3)].ast_expr)));
			(yyvsp[(1) - (3)].list_ast_array_elem)->push_back(elem);
			
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (3)].list_ast_array_elem);
		;}
    break;

  case 339:
#line 2810 "src/generated_src/php_parser.ypp"
    {
			List<Array_elem*>* list = new List<Array_elem*>;
			Array_elem* elem = NEW(Array_elem, ((yyvsp[(1) - (3)].ast_expr), false, (yyvsp[(3) - (3)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 340:
#line 2818 "src/generated_src/php_parser.ypp"
    {
			List<Array_elem*>* list = new List<Array_elem*>;
			Array_elem* elem = NEW(Array_elem, (NULL, false, (yyvsp[(1) - (1)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 341:
#line 2826 "src/generated_src/php_parser.ypp"
    {
			Array_elem* elem = 
				NEW(Array_elem, ((yyvsp[(3) - (6)].ast_expr), true, (yyvsp[(6) - (6)].ast_expr)));
			(yyvsp[(1) - (6)].list_ast_array_elem)->push_back(elem);

			(yyval.list_ast_array_elem) = (yyvsp[(1) - (6)].list_ast_array_elem);
		;}
    break;

  case 342:
#line 2834 "src/generated_src/php_parser.ypp"
    {
			Array_elem* elem = 
				NEW(Array_elem, (NULL, true, (yyvsp[(4) - (4)].ast_expr)));
			(yyvsp[(1) - (4)].list_ast_array_elem)->push_back(elem);
			
			(yyval.list_ast_array_elem) = (yyvsp[(1) - (4)].list_ast_array_elem);
		;}
    break;

  case 343:
#line 2842 "src/generated_src/php_parser.ypp"
    {
			List<Array_elem*>* list = new List<Array_elem*>;
			Array_elem* elem = 
				NEW(Array_elem, ((yyvsp[(1) - (4)].ast_expr), true, (yyvsp[(4) - (4)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 344:
#line 2851 "src/generated_src/php_parser.ypp"
    {
			List<Array_elem*>* list = new List<Array_elem*>;
			Array_elem* elem = 
				NEW(Array_elem, (NULL, true, (yyvsp[(2) - (2)].ast_expr)));
			list->push_back(elem);

			(yyval.list_ast_array_elem) = list;
		;}
    break;

  case 345:
#line 2863 "src/generated_src/php_parser.ypp"
    {
			METHOD_NAME* fn = NEW(METHOD_NAME, (new String("isset")));
			(yyval.ast_method_invocation) = NEW(Method_invocation, (NULL, fn, (yyvsp[(3) - (4)].list_ast_actual_parameter)));
		;}
    break;

  case 346:
#line 2868 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ("empty", (yyvsp[(3) - (4)].ast_expr)));
		;}
    break;

  case 347:
#line 2872 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ("include", (yyvsp[(2) - (2)].ast_expr)));
			(yyval.ast_method_invocation)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 348:
#line 2877 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ("include_once", (yyvsp[(2) - (2)].ast_expr)));
			(yyval.ast_method_invocation)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 349:
#line 2882 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ("eval", (yyvsp[(3) - (4)].ast_expr)));
		;}
    break;

  case 350:
#line 2886 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ("require", (yyvsp[(2) - (2)].ast_expr)));
			(yyval.ast_method_invocation)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 351:
#line 2891 "src/generated_src/php_parser.ypp"
    {
			(yyval.ast_method_invocation) = NEW(Method_invocation, ("require_once", (yyvsp[(2) - (2)].ast_expr)));
			(yyval.ast_method_invocation)->attrs->set_true("phc.unparser.no_brackets");
		;}
    break;

  case 352:
#line 2899 "src/generated_src/php_parser.ypp"
    {
			List<Actual_parameter*>* params = new List<Actual_parameter*>;
			
			params->push_back(NEW(Actual_parameter, (false, (yyvsp[(1) - (1)].ast_expr))));
			(yyval.list_ast_actual_parameter) = params;
		;}
    break;

  case 353:
#line 2906 "src/generated_src/php_parser.ypp"
    {
			(yyvsp[(1) - (3)].list_ast_actual_parameter)->push_back(NEW(Actual_parameter, (false, (yyvsp[(3) - (3)].ast_expr))));
			(yyval.list_ast_actual_parameter) = (yyvsp[(1) - (3)].list_ast_actual_parameter);
		;}
    break;

  case 354:
#line 2914 "src/generated_src/php_parser.ypp"
    {
			CONSTANT_NAME* constant = new CONSTANT_NAME((yyvsp[(3) - (3)].string));

			(yyval.ast_constant) = NEW(Constant, ((yyvsp[(1) - (3)].token_class_name), constant));
		;}
    break;

  case 355:
#line 2927 "src/generated_src/php_parser.ypp"
    {
			// If there are any remaining comments, add them as a NOP
			if(!context->last_comments.empty())
				(yyvsp[(2) - (3)].list_ast_statement)->push_back(NEW(Nop, ()));

			if(!(yyvsp[(2) - (3)].list_ast_statement)->empty())
				(yyvsp[(2) - (3)].list_ast_statement)->front()->attrs->erase("phc.unparser.is_wrapped");

			(yyval.list_ast_statement) = (yyvsp[(2) - (3)].list_ast_statement);
		;}
    break;


/* Line 1267 of yacc.c.  */
#line 6492 "src/generated/php_parser.tab.cpp"
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



