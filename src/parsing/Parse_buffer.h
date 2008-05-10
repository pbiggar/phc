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

#include "process_ir/General.h"
#include "process_ast/AST_unparser.h"
#include "process_hir/HIR_unparser.h"
#include "process_mir/MIR_unparser.h"

#ifndef PHC_PARSE_BUFFER
#define PHC_PARSE_BUFFER

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
		List<NS::Statement*>* stmts = parse_to_##LC (s(ss.str ()));				\
		(new Clone_blank_mixins<NS::Node, NS::Visitor> (anchor))->				\
			visit_statement_list (stmts);													\
		out->push_back_all (stmts);														\
	}																								\
	void to_pass (String* pass, NS::Node* anchor)									\
	{																								\
		List<NS::Statement*>* stmts = lower_##LC (									\
			pass, parse_to_##LC (s(ss.str ())));										\
		(new Clone_blank_mixins<NS::Node, NS::Visitor> (anchor))->				\
			visit_statement_list (stmts);													\
		out->push_back_all (stmts);														\
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
