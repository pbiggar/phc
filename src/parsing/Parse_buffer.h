/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Provide convenience operators for parsing code
 */

#include "process_ir/General.h"

#ifndef PHC_PARSE_BUFFER
#define PHC_PARSE_BUFFER

class Parse_buffer
{

// TODO protected via friend <<
public:
	// provides line numbers
	List<AST::Statement*>* out;
	stringstream ss;

public:

	Parse_buffer ();
	Parse_buffer (List<AST::Statement*>* out);

	void finish (AST::Node* anchor);
	void to_pass (String* pass, AST::Node* anchor);
};

/* When given a list of IR statements, use the << operator to parse the given
 * string into it. When a IR::Node is passed, use the appropriate unparser to
 * generate ssource from it. */

// Left-most
Parse_buffer& operator<<(List<AST::Statement*>& stmts, const char* in);
Parse_buffer& operator<<(Parse_buffer& out, AST::Node* in);
Parse_buffer& operator<<(Parse_buffer& out, const char* in);

#endif // PHC_PARSE_BUFFER
