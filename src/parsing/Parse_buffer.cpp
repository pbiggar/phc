/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Provide convenience operators for parsing code
 */

#include "Parse_buffer.h"
#include "process_ast/AST_unparser.h"

#include "process_ast/AST_unparser.h"
#include "process_hir/HIR_unparser.h"
#include "process_mir/MIR_unparser.h"


#define create_parse_buffer_definition(TYPE,LC)											\
/* When given a list of IR statements, use the << operator to parse the	*/		\
/* given	string into it. When a IR::Node is passed, use the appropriate */		\
/* unparser to	generate ssource from it. */												\
																										\
/* Left-most */																					\
TYPE##_Parse_buffer::TYPE##_Parse_buffer& operator<<(List<TYPE::Statement*>& stmts, string in)\
{																										\
	TYPE##_Parse_buffer& out = *(new TYPE##_Parse_buffer (&stmts));				\
	out.ss << "<?php " << in;																	\
	return out;																						\
}																										\
TYPE##_Parse_buffer::TYPE##_Parse_buffer& operator<<(List<TYPE::Statement*>& stmts, TYPE::Node* in)\
{																										\
	TYPE##_Parse_buffer& out = *(new TYPE##_Parse_buffer (&stmts));				\
	out.ss << "<?php ";																			\
																										\
	stringstream ss;																				\
	in->visit (new TYPE##_unparser (ss, true));											\
	out.ss << ss.str ();																			\
																										\
	return out;																						\
}																										\
																										\
																										\
TYPE##_Parse_buffer::TYPE##_Parse_buffer& operator<<(TYPE##_Parse_buffer& out, TYPE::Node* in)		\
{																										\
	stringstream ss;																				\
	in->visit (new TYPE##_unparser (ss, true));											\
	out.ss << ss.str ();																			\
																										\
	return out;																						\
}																										\
																										\
TYPE##_Parse_buffer::TYPE##_Parse_buffer& operator<<(TYPE##_Parse_buffer& out, string in)		\
{																										\
	out.ss << in;																					\
	return out;																						\
}																										\
TYPE##_Parse_buffer::TYPE##_Parse_buffer& operator<<(TYPE##_Parse_buffer& out, String* in)		\
{																										\
	out.ss << in;																					\
	return out;																						\
}																										\
TYPE##_Parse_buffer::TYPE##_Parse_buffer& operator<<(TYPE##_Parse_buffer& out, int in)		\
{																										\
	out.ss << in;																					\
	return out;																						\
}






create_parse_buffer_definition(AST,ast);
create_parse_buffer_definition(HIR,hir);
create_parse_buffer_definition(MIR,mir);

