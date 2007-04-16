/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate a fresh temporary
 */

#include "fresh.h"

String* fresh(string prefix)
{
	static map<string, int> temps;
	int t = temps[prefix]++;
	stringstream ss;
	ss << prefix << t;

	return new String(ss.str());
}

AST_variable* fresh_var(string prefix)
{
	return new AST_variable(
		NULL, 
		new Token_variable_name(fresh(prefix)), 
		new List<AST_expr*>
		);
}

AST_label* fresh_label ()
{
	return new AST_label (
		new Token_label_name (fresh("L")));
}



