/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "pass_manager/Plugin_pass.h"
#include "AST.h"
#include "process_ir/General.h"

using namespace AST;
using namespace std;

int count(List<Statement*>* in)
{
	// Every item in "in" is a statement
	int num_statements = in->size();

	// But there can also be statements nested inside any 
	// of the statements in "in". We consider each one in turn.
	List<Statement*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		// Check if the statement is an if-statement
		if(If* if_stmt = dynamic_cast<If*>(*i))
		{
			num_statements += count(if_stmt->iftrue);
			num_statements += count(if_stmt->iffalse);
		}
	}

	return num_statements;
}

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("ast"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	int num_statements = count(in->statements);
	cout << num_statements << " statements found" << endl;
}
