/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate a fresh temporary
 */

#include "fresh.h"

AST_variable* fresh(string prefix)
{
	static map<string, int> temps;
	int t = temps[prefix]++;
	stringstream ss;
	ss << prefix << t;

	String* name = new String(ss.str());
	List<AST_expr*>* ind = new List<AST_expr*>;
	return new AST_variable(NULL, new Token_variable_name(name), ind);
}
