/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lexical analyser
 *
 * NOTE: 
 * In PHP, the constant "01090" is taken to be an octal number; everything
 * from the 9 onwards is silently ignored (so, the number evaluates to 8
 * decimal). phc will give an error message instead.
*/

%{
	#include <assert.h>
	#include <string.h>
	#include "lib/Integer.h"
	#include "php_parser.tab.hpp"
	#include "cmdline.h"
	#include "parsing/PHP_context.h"

	extern struct gengetopt_args_info args_info;
	extern "C" const struct keyword* in_word_set(const char*, unsigned int);

	#define YY_SKIP_YYWRAP

	/*
	 * Macros to return a token
	 * If dump_tokens_flag is set, also print the token to stdout
	 */

	#define RETURN(x) {															\
		if(args_info.dump_tokens_flag)										\
			printf("%ld: " #x "\n", yyextra->source_line);				\
		yyextra->after_arrow = (x) == O_SINGLEARROW;						\
		return x; }
	#define RETURN_OP(x) { 														\
		if(args_info.dump_tokens_flag) 										\
			printf("%ld: SIMPLE_OP %c\n", yyextra->source_line, x); 	\
		yyextra->after_arrow = false;											\
		return x; } 

	#define RETURN_ALL(state)					\
		yyextra->mt_final_state = state;		\
		yyextra->mt_index = 1;					\
		BEGIN(RET_MULTI);							\
		*yylval = yyextra->mt_lval[0];			\
		RETURN(yyextra->mt_type[0]);

	struct keyword { char* name; int token; };

	#define YY_EXTRA_TYPE PHP_context*

	// TODO: remove
	#define YYSTYPE Object*
%}

%option reentrant
%option bison-bridge
%option prefix="PHP_"
%option noyywrap
%option stack
%option nounput
%option noyy_top_state

	/* Define lexical states */

%x PHP
%x SQ_STR		
%x SQ_ESC
%x BT_STR
%x DQ_STR		
%x HD_STR
%x HD_NL
%x HD_MAIN
%x HD_END
%x ESCAPE
%x ML_COMM
%x SL_COMM

%x COMPLEX1
%x COMPLEX2

%x RET_MULTI

	/* Define a few tokens referenced in the grammar, below */

NL					\r?\n?
WS					[ \t\n\r]
ANY				[\x00-\xff]	

PHP				[pP][hH][pP]
PHP_START		"<?"{PHP}?
SCRIPT_START	"<script"{WS}+"language"{WS}*"="{WS}*['"]{WS}*{PHP}{WS}*['"]{WS}*">"
START				{PHP_START}|{SCRIPT_START}
START_ECHO		"<?="
PHP_STOP			"?>"
SCRIPT_STOP		"</script"{WS}*">"
STOP				({PHP_STOP}|{SCRIPT_STOP}){NL}?

IDENT				[a-zA-Z_\x7F-\xFF][a-zA-Z0-9_\x7F-\xFF]*

DEC				([1-9][0-9]*)|0
HEX				0[xX][0-9a-fA-F]+
OCT				0[0-7]+
INT				({DEC}|{HEX}|{OCT})

LNUM				[0-9]+
DNUM				([0-9]*[\.]{LNUM})|({LNUM}[\.][0-9]*)
EXPONENT_DNUM	(({LNUM}|{DNUM})[eE][+-]?{LNUM})
REAL				{DNUM}|{EXPONENT_DNUM}

BRACKET			[(){}[\]]
ARITHMETIC		[+\-/*%^]
BITWISE			[&|~]
RELATIONAL		[=><]
OTHER_OP			[.!,?:$@]
SIMPLE_OP		{BRACKET}|{ARITHMETIC}|{BITWISE}|{RELATIONAL}|{OTHER_OP}

CS					"("{WS}*
CE					{WS}*")"
INT_CAST			{CS}("integer"|"int"){CE}
REAL_CAST		{CS}("float"|"real"|"double"){CE}
STRING_CAST		{CS}"string"{CE} 
ARRAY_CAST		{CS}"array"{CE}
OBJECT_CAST		{CS}"object"{CE} 
BOOL_CAST		{CS}("bool"|"boolean"){CE}
UNSET_CAST		{CS}"unset"{CE}

%%

	/* Update source_line */

<*>{NL}					{
								if(YY_START != SL_COMM && YY_START != ML_COMM)
									yyextra->attach_to_previous = 0;

								yyextra->source_line++; 
								REJECT;
							}

	/* Casts */

<PHP>{INT_CAST}		{ RETURN(CAST_INT);  }
<PHP>{REAL_CAST}		{ RETURN(CAST_REAL);  }
<PHP>{STRING_CAST}	{ RETURN(CAST_STRING);  }
<PHP>{ARRAY_CAST}		{ RETURN(CAST_ARRAY);  }
<PHP>{OBJECT_CAST}	{ RETURN(CAST_OBJECT);  }
<PHP>{BOOL_CAST}		{ RETURN(CAST_BOOL);  }
<PHP>{UNSET_CAST}		{ RETURN(CAST_UNSET);  }

	/* Operators */

<PHP>"=="				{ RETURN(O_EQEQ); }
<PHP>"==="				{ RETURN(O_EQEQEQ); }
<PHP>"!="				{ RETURN(O_NOTEQ); }
<PHP>"<>"				{ RETURN(O_NOTEQ); }
<PHP>"!=="				{ RETURN(O_NOTEQEQ); }
<PHP>"<="				{ RETURN(O_LE); }
<PHP>">="				{ RETURN(O_GE); }
<PHP>"++"				{ RETURN(O_INC); }
<PHP>"--"				{ RETURN(O_DEC); }
<PHP>"=>"				{ RETURN(O_DOUBLEARROW); }
<PHP>"->"				{ RETURN(O_SINGLEARROW); }

<PHP>"<<"				{ RETURN(O_SL); }
<PHP>">>"				{ RETURN(O_SR); }

<PHP>"+="				{ RETURN(O_PLUSEQ); }
<PHP>"-="				{ RETURN(O_MINUSEQ); }
<PHP>"*="				{ RETURN(O_MULEQ); }
<PHP>"/="				{ RETURN(O_DIVEQ); }
<PHP>".="				{ RETURN(O_CONCATEQ); }
<PHP>"%="				{ RETURN(O_MODEQ); }
<PHP>"&="				{ RETURN(O_ANDEQ); }
<PHP>"|="				{ RETURN(O_OREQ); }
<PHP>"^="				{ RETURN(O_XOREQ); }
<PHP>"<<="				{ RETURN(O_SLEQ); }
<PHP>">>="				{ RETURN(O_SREQ); }
<PHP>"::"				{ RETURN(O_COLONCOLON); }

<PHP>"&&"				{ RETURN(O_LOGICAND); }
<PHP>"||"				{ RETURN(O_LOGICOR); }

<PHP>{SIMPLE_OP}		{ RETURN_OP(*yytext); }
<PHP>";"					{ yyextra->attach_to_previous = true; RETURN_OP(';'); } 

	/* Tokens */

<PHP>${IDENT}			{
								// variable names do not contain $
								*yylval = new String(yytext+1); 
								RETURN(VARIABLE);
							}
<PHP>{IDENT}			%{
							{	// Can't declare local variables without scoping them
								
								// We generate a semantic value which equals the 
								// keyword so that we can reproduce it exactly the
								// same way in the unparsers, if we so desire 
								// (keywords are case insensitive)
								*yylval = new String(yytext);
							
								// Check if the ident is in fact a keyword
								const struct keyword* keyword;
								keyword = in_word_set(yytext, yyleng);
								if(keyword != 0 && !yyextra->after_arrow)
								{
									switch(keyword->token)
									{
										case K_CLASS:
										case K_FUNCTION:
											yyextra->attach_to_previous = 1;
											break;
									}
									
									RETURN(keyword->token);
								}
								else
								{
									RETURN(IDENT);
								}
							}
							%}
<PHP>{INT}				{ *yylval = new String(yytext); RETURN(INT); }
<PHP>{REAL}				{ *yylval = new String(yytext); RETURN(REAL); }
<PHP>{STOP}				{ yyextra->buffer = ""; BEGIN(INITIAL); RETURN(';'); }

	/* Strings */

<PHP>"'"					{ yyextra->buffer = ""; BEGIN(SQ_STR); }
<PHP>"`"					{ yyextra->buffer = ""; BEGIN(BT_STR); }
<PHP>"\""				{ yyextra->buffer = ""; BEGIN(DQ_STR); }
<PHP>"<<<"" "?			{ yyextra->buffer = ""; BEGIN(HD_STR); }

	/* Comments */

<PHP>^[ \t]*\n			{
								// Following a suggestion by Tim Van Holder on bison-help,
								// we treat blank lines as comments
								yyextra->last_comments.push_back(new String(""));
							}
<PHP>"/*"				{
								yyextra->buffer = yytext;	
								BEGIN(ML_COMM); 
							}
<PHP>#|"//"				{ 
								yyextra->buffer = yytext;	
								BEGIN(SL_COMM); 
							}

<ML_COMM>"*/"			{ 
								yyextra->buffer.append(yytext);
								
								if(yyextra->attach_to_previous)
									yyextra->attach_comment(new String(yyextra->buffer));
								else
									yyextra->last_comments.push_back(new String(yyextra->buffer));
								BEGIN(PHP); 
							
								yyextra->buffer = "";
							}
<ML_COMM>{ANY}			{ yyextra->buffer.push_back(*yytext); }

<SL_COMM>{NL}			{ 
								if(yyextra->attach_to_previous)
									yyextra->attach_comment(new String(yyextra->buffer));
								else
									yyextra->last_comments.push_back(new String(yyextra->buffer));
								yyextra->attach_to_previous = 0;
								BEGIN(PHP);

								yyextra->buffer = "";
							}
<SL_COMM>{STOP}		{ yyextra->buffer = ""; BEGIN(INITIAL); }
<SL_COMM>.				{ yyextra->buffer.push_back(*yytext); }	

	/* Any other character */

<PHP>{WS}				/* Ignore */
<PHP>{ANY}				{ RETURN(INVALID_TOKEN); }

	/* Deal with singly quoted strings */

<SQ_STR>\'			{
							String* str = new String(yyextra->buffer);
							str->attrs->set("phc.unparser.is_singly_quoted", new Boolean(true)); 
							*yylval = str;
							BEGIN(PHP);
							yyextra->buffer = "";
							RETURN(STRING);
						}
<SQ_STR>\\			{ BEGIN(SQ_ESC); }
<SQ_STR>{ANY}		{ yyextra->buffer.push_back(*yytext); }

<SQ_ESC>\'			{ yyextra->buffer.push_back(*yytext); BEGIN(SQ_STR); }
<SQ_ESC>{ANY}		{
							yyextra->buffer.push_back('\\');
							yyextra->buffer.push_back(*yytext);
							BEGIN(SQ_STR); 
						}

	/* Deal with backticked strings. */

<BT_STR>\`			{
							yyextra->schedule_return(IDENT, "shell_exec");
							yyextra->schedule_return('(');
							yyextra->schedule_return(STRING, yyextra->buffer);
							yyextra->schedule_return(')');
							yyextra->buffer = "";
							RETURN_ALL(PHP);
						}
<BT_STR>{ANY}		{ yyextra->buffer.push_back(*yytext); }

	/* Deal with in-string syntax (in DQ_STR, and HD_STR) */

<DQ_STR,HD_MAIN>"$"{IDENT} {
							yyextra->schedule_return(STRING, yyextra->buffer);
							yyextra->schedule_return('.');
							yyextra->schedule_return(VARIABLE, &yytext[1]);
							yyextra->schedule_return('.');

							yyextra->buffer = "";
							RETURN_ALL(YY_START);
						}	
<DQ_STR,HD_MAIN>"${"{IDENT}"}" {
							yyextra->schedule_return(STRING, yyextra->buffer);
							yyextra->schedule_return('.');
							yyextra->schedule_return(VARIABLE, &yytext[2], yyleng - 3);
							yyextra->schedule_return('.');
							yyextra->buffer = "";
							RETURN_ALL(YY_START);
						}
<DQ_STR,HD_MAIN>"$"{IDENT}"["{INT}"]" %{
						{
							long left, right;
							left = strchr(yytext, '[') - yytext;
							right = strchr(yytext, ']') - yytext;

							yyextra->schedule_return(STRING, yyextra->buffer);
							yyextra->schedule_return('.');
							yyextra->schedule_return(VARIABLE, &yytext[1], left - 1);
							yyextra->schedule_return('[');
							yyextra->schedule_return(INT, &yytext[left+1], right - left - 1);
							yyextra->schedule_return(']');
							yyextra->schedule_return('.');
							
							yyextra->buffer = "";
							RETURN_ALL(YY_START);
						} 
						%}
<DQ_STR,HD_MAIN>"$"{IDENT}"["{IDENT}"]" %{
						{
							long left, right;
							left = strchr(yytext, '[') - yytext;
							right = strchr(yytext, ']') - yytext;
							
							yyextra->schedule_return(STRING, yyextra->buffer);
							yyextra->schedule_return('.');
							yyextra->schedule_return(VARIABLE, &yytext[1], left - 1);
							yyextra->schedule_return('[');
							yyextra->schedule_return(STRING, &yytext[left+1], right - left - 1);
							yyextra->schedule_return(']');
							yyextra->schedule_return('.');
							
							yyextra->buffer = "";
							RETURN_ALL(YY_START);
						} 
						%}
<DQ_STR,HD_MAIN>"$"{IDENT}"[$"{IDENT}"]" %{
						{
							long left, right;
							left = strchr(yytext, '[') - yytext;
							right = strchr(yytext, ']') - yytext;
							
							yyextra->schedule_return(STRING, yyextra->buffer);
							yyextra->schedule_return('.');
							yyextra->schedule_return(VARIABLE, &yytext[1], left - 1);
							yyextra->schedule_return('[');
							yyextra->schedule_return(VARIABLE, &yytext[left+2], right - left - 2);
							yyextra->schedule_return(']');
							yyextra->schedule_return('.');
							
							yyextra->buffer = "";
							RETURN_ALL(YY_START);
						} 
						%}
<DQ_STR,HD_MAIN>"$"{IDENT}"->"{IDENT} %{
						{
							long arrow;
							arrow = strchr(yytext, '-') - yytext;
							
							yyextra->schedule_return(STRING, yyextra->buffer);
							yyextra->schedule_return('.');
							yyextra->schedule_return(VARIABLE, &yytext[1], arrow - 1);
							yyextra->schedule_return(O_SINGLEARROW);
							yyextra->schedule_return(IDENT, &yytext[arrow+2]);
							yyextra->schedule_return('.');

							yyextra->buffer = "";
							RETURN_ALL(YY_START);
						} 
						%}

<DQ_STR,HD_MAIN>"{$"	{
							yy_push_state(COMPLEX2, yyscanner);
							yy_push_state(COMPLEX1, yyscanner);
							*yylval = new String(yyextra->buffer);
							yyless(1);
							yyextra->buffer = "";
							RETURN(STRING);
						}

<ESCAPE>n			{ yyextra->buffer.push_back('\n'); yy_pop_state(yyscanner); }
<ESCAPE>t			{ yyextra->buffer.push_back('\t'); yy_pop_state(yyscanner); }
<ESCAPE>r			{ yyextra->buffer.push_back('\r'); yy_pop_state(yyscanner); }
<ESCAPE>\\			{ yyextra->buffer.push_back('\\'); yy_pop_state(yyscanner); }
<ESCAPE>\$			{ yyextra->buffer.push_back('$');  yy_pop_state(yyscanner); }
<ESCAPE>x[0-9A-Fa-f]{1,2} %{
						{
							char c = (char) strtol(yytext + 1, 0, 16);
							yyextra->buffer.push_back(c);
							yy_pop_state(yyscanner);
						}
						%}
<ESCAPE>[0-7]{1,3} %{
						{
							char c = (char) strtol(yytext, 0, 8);
							yyextra->buffer.push_back(c);
							yy_pop_state(yyscanner);
						}
						%}
<ESCAPE>{ANY}		{ 
							yyextra->buffer.push_back('\\');
							yyextra->buffer.push_back(*yytext);
							yy_pop_state(yyscanner);
						}

	/* Complex syntax */

<COMPLEX1>{ANY}	{
							yyless(0);
							BEGIN(PHP);
							RETURN_OP(O_MAGIC_CONCAT);
						}
<COMPLEX2>{ANY}	{
							yyless(0);
							yy_pop_state(yyscanner);
							RETURN_OP('.');
						}

	/* Deal with (doubly quoted) strings. */

<DQ_STR>\"			{
							*yylval = new String(yyextra->buffer);
							BEGIN(PHP);
							yyextra->buffer = "";
							RETURN(STRING);
						}

<DQ_STR>\\\"		{ yyextra->buffer.push_back('"'); }
<DQ_STR>\\			{ yy_push_state(ESCAPE, yyscanner); }
<DQ_STR>{ANY}		{ yyextra->buffer.push_back(*yytext); }

	/* Heredoc syntax */

<HD_STR>{IDENT}	{
							yyextra->heredoc_id = strdup(yytext);
							yyextra->heredoc_id_len = yyleng;
							yyextra->heredoc_id_ptr = 0;
							
							if(!strcmp(yytext, "INLINE_C"))
								yyextra->last_comments.push_back(new String("// phc:inline-c"));

							BEGIN(HD_NL);
						}
<HD_STR>.			{ 
							yyless(0); 
							BEGIN(PHP); 
							RETURN(INVALID_TOKEN);
						}

<HD_NL>{NL}			{ BEGIN(HD_MAIN); }
<HD_NL>{ANY}		{ RETURN(INVALID_TOKEN);	}

<HD_MAIN>\\			{ yy_push_state(ESCAPE, yyscanner); }
<HD_MAIN>^{ANY}	{
							yyextra->buffer.push_back(*yytext);

							if(*yytext == yyextra->heredoc_id[0])
								yyextra->heredoc_id_ptr = &yyextra->heredoc_id[1];
						}
<HD_MAIN>{ANY}		%{
							yyextra->buffer.push_back(*yytext);

							if(yyextra->heredoc_id_ptr && (*yyextra->heredoc_id_ptr == *yytext))
								yyextra->heredoc_id_ptr++;
							else
								yyextra->heredoc_id_ptr = 0;

							if(yyextra->heredoc_id_ptr - yyextra->heredoc_id == yyextra->heredoc_id_len)
							{	
								BEGIN(HD_END);
							}
						%}
<HD_END>{NL}|;		%{ 
							{
								// Remove heredoc_id from the buffer 
								long string_len = yyextra->buffer.size() - yyextra->heredoc_id_len;

								// The linebreak of the last line of the HEREDOC
								// string should also be stripped
								if(string_len > 0 && yyextra->buffer[string_len - 1] == '\n')
									string_len--;
								if(string_len > 0 && yyextra->buffer[string_len - 1] == '\r')
									string_len--; // Windows file
							
								*yylval = new String(yyextra->buffer.substr(0, string_len));
								
								if(yytext[0] == ';')
									yyless(0);
								
								BEGIN(PHP);
								yyextra->buffer = "";
								RETURN(STRING);
							}
						%}
<HD_END>.			%{
							yyextra->buffer.push_back(*yytext);
							yyextra->heredoc_id_ptr = 0;
							BEGIN(HD_MAIN);
						%}

	/* Returning multiple tokens */

<RET_MULTI>{ANY}	{
							yyless(0);

							if(yyextra->mt_index == yyextra->mt_count - 1)
							{
								yyextra->mt_count = 0;
								BEGIN(yyextra->mt_final_state);
							}

							*yylval = yyextra->mt_lval[yyextra->mt_index];
							yyextra->mt_index++;
							RETURN(yyextra->mt_type[yyextra->mt_index - 1]);
						}

	/* Deal with HTML fragments */

{START_ECHO}		{
							// The logic that deals with returning multiple tokens
							// needs at least two tokens to work with.
							if(!yyextra->buffer.empty())
								yyextra->schedule_return(INLINE_HTML, yyextra->buffer);
							else
								yyextra->schedule_return(';');

							yyextra->schedule_return(K_ECHO);
							RETURN_ALL(PHP);
						}
{START}				%{
							BEGIN(PHP); 

							if(!yyextra->buffer.empty())
							{
								*yylval = new String(yyextra->buffer);
								RETURN(INLINE_HTML);
							}
						%}
<<EOF>>				%{
							if(yyextra->buffer.empty())
							{
								yyterminate();
							} 
							else 
							{
								*yylval = new String(yyextra->buffer);	
								yyextra->buffer = "";
								RETURN(INLINE_HTML);
							}
						%}
{ANY}					{ yyextra->buffer.push_back(*yytext); }

%%

/**
 * We need to define this here rather than in PHP_lexer.h because we
 * need access to the BEGIN and COMPLEX2 macros defined in lex.yy.cc
 */

void PHP_context::init_scanner(FILE* input)
{
	yylex_init(&scanner);
	yyset_extra(this, scanner);
	yyset_in(input, scanner);
}

void PHP_context::destroy_scanner()
{
	yylex_destroy(scanner);
}

void PHP_context::return_to_complex_syntax()
{
	yy_pop_state(scanner);
}

// Attach a comment to the last node generated
void PHP_context::attach_comment(String *s)
{
	s->attrs->set("phc.unparser.comment.after", new Boolean(true));
	assert(last_commented_node);
	last_commented_node->get_comments()->push_back(s);
}	
	
void PHP_context::schedule_return(long type, const char* lval, long length)
{
	mt_type[mt_count] = type;

	if(lval)
	{
		if(length == -1)
			mt_lval[mt_count] = new String(lval);
		else
			mt_lval[mt_count] = new String(lval, length);
	}
	else
	{
		mt_lval[mt_count] = NULL;
	}

	mt_count++;
}

void PHP_context::schedule_return(long type, string& s)
{
	schedule_return(type, s.c_str(), s.size());
}
