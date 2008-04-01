/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Provide convenience operators for parsing code
 */

#include "Parse_buffer.h"
#include "process_ast/AST_unparser.h"

Parse_buffer::Parse_buffer () {}

Parse_buffer::Parse_buffer (List<AST::Statement*>* out) 
: out (out)
{
}

void Parse_buffer::finish (AST::Node* anchor)
{
	out->push_back_all (parse_to_ast (new String (ss.str ()), anchor));
}

void Parse_buffer::to_pass (String* pass, AST::Node* anchor)
{
	out->push_back_all (lower_ast (pass, parse_to_ast (new String (ss.str ()), anchor)));
}

/* When given a list of IR statements, use the << operator to parse the given
 * string into it. When a IR::Node is passed, use the appropriate unparser to
 * generate ssource from it. */

// The left-most << in the chain needs to create the buffer
Parse_buffer::Parse_buffer& operator<<(List<AST::Statement*>& stmts, const char* in)
{
	Parse_buffer& out = *(new Parse_buffer (&stmts));
	out.ss << "<?php " << in;
	return out;
}

Parse_buffer::Parse_buffer& operator<<(Parse_buffer& out, AST::Node* in)
{
	// Use the unparser
	stringstream ss;
	in->visit (new AST_unparser (ss, true));
	out.ss << ss.str ();

	return out;
}

Parse_buffer::Parse_buffer& operator<<(Parse_buffer& out, const char* in)
{
	out.ss << in;
	return out;
}


