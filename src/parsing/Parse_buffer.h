/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Provide convenience operators for parsing code.
 *
 * TODO:
 *		After parsing, there are a list of new nodes. Each one needs a line
 *		number and a filename. Each node that was passed to the parsing needs to
 *		be searched for, and needs attributes copied. It isnt sufficient by a
 *		long way to copy attributes from the top-level to nodes without attributes.
 */

#ifndef PHC_PARSE_BUFFER
#define PHC_PARSE_BUFFER

#include "process_ir/General.h"
#include "process_ast/AST_unparser.h"
#include "process_hir/HIR_unparser.h"
#include "process_mir/MIR_unparser.h"
#include "process_ir/Clone_blank_mixins.h"
#include "pass_manager/Pass_manager.h"


#include "parsing/parse.h"
extern Pass_manager* pm;

// TODO: figure out how to get rid of these nasty hacks
#define create_parse_buffer_declaration(NS,LC)										\
class NS##_Parse_buffer																		\
{																									\
	/* TODO: make these private and give protected access to << via */		\
	/* a friend declaration. */															\
public:																							\
	/* provides line numbers */															\
	List<NS::Statement*>* out;																\
	stringstream ss;																			\
																									\
public:																							\
																									\
	NS##_Parse_buffer (List<NS::Statement*>* out) : out (out) {}				\
																									\
	void finish (NS::Node* anchor)														\
	{																								\
		return to_pass (s(#LC), anchor);													\
	}																								\
	void to_pass (String* pass, NS::Node* anchor)									\
	{																								\
		AST::PHP_script* ast = parse_code (s(ss.str ()), NULL, 0);				\
		NS::PHP_script* script = pm->run_until (pass, ast)->as_##NS();			\
		script->visit (new Clone_blank_mixins<NS::Node, NS::Visitor> (anchor));\
		out->push_back_all (script->statements);										\
	};																								\
};																									\
																									\
/* These can start the buffer */															\
NS##_Parse_buffer& operator<<(List<NS::Statement*>& stmts, string in);		\
NS##_Parse_buffer& operator<<(List<NS::Statement*>& stmts, NS::Node* in);	\
																									\
/* These can continue the stream */														\
NS##_Parse_buffer& operator<<(NS##_Parse_buffer& out, NS::Node* in);			\
NS##_Parse_buffer& operator<<(NS##_Parse_buffer& out, string in);				\
NS##_Parse_buffer& operator<<(NS##_Parse_buffer& out, String* in);			\
NS##_Parse_buffer& operator<<(NS##_Parse_buffer& out, int in);


create_parse_buffer_declaration(AST,ast);
create_parse_buffer_declaration(HIR,hir);
create_parse_buffer_declaration(MIR,mir);

#endif // PHC_PARSE_BUFFER
