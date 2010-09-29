/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Provide convenience operators for parsing code
 */

#include "Parse_buffer.h"

#include "process_ast/AST_unparser.h"
#include "process_hir/HIR_unparser.h"
#include "process_mir/MIR_unparser.h"

/* When given a list of IR statements, use the << operator to parse the 
 * given string into it. When a IR::Node is passed, use the appropriate
 * unparser to	generate ssource from it. */
#define create_parse_buffer_definition(NS)											\
																									\
/* Left-most */																				\
NS##_parse_buffer&													\
operator<<(List<NS::Statement*>& stmts, string in)									\
{																									\
	NS##_parse_buffer& out = *(new NS##_parse_buffer ());							\
	out.stmts = &stmts;																		\
	out.ss << "<?php " << in;																\
	return out;																					\
}																									\
NS##_parse_buffer&													\
operator<<(List<NS::Statement*>& stmts, NS::Node* in)								\
{																									\
	NS##_parse_buffer& out = stmts << "";												\
	out << in;																					\
	return out;																					\
}																									\
																									\
																									\
NS##_parse_buffer&													\
operator<<(NS##_parse_buffer& out, NS::Node* in)									\
{																									\
	NS##_unparser (out.ss, true).unparse (in);										\
																									\
	out.used_nodes.push_back (in);														\
	return out;																					\
}																									\
																									\
NS##_parse_buffer&													\
operator<<(NS##_parse_buffer& out, string in)										\
{																									\
	out.ss << in;																				\
	return out;																					\
}																									\
NS##_parse_buffer&													\
operator<<(NS##_parse_buffer& out, String* in)										\
{																									\
	out.ss << *in;																				\
	return out;																					\
}																									\
NS##_parse_buffer&													\
operator<<(NS##_parse_buffer& out, int in)											\
{																									\
	out.ss << in;																				\
	return out;																					\
}

create_parse_buffer_definition(AST);
create_parse_buffer_definition(HIR);
create_parse_buffer_definition(MIR);
