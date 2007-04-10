/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate a fresh temporary
 */

#include "fresh.h"

AST_variable* fresh()
{
	static int next_fresh = 0;

	stringstream ss;
	ss << "T" << next_fresh++;

	String* name = new String(ss.str());
	List<AST_expr*>* ind = new List<AST_expr*>;
	return new AST_variable(NULL, new Token_variable_name(name), ind);
}
