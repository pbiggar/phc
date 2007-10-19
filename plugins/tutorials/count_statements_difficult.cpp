#include "pass_manager/Pass_manager.h"

using namespace AST;

int count(List<AST_statement*>* in)
{
	// Every item in "in" is a statement
	int num_statements = in->size();

	// But there can also be statements nested inside any 
	// of the statements in "in". We consider each one in turn.
	List<AST_statement*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		// Check if the statement is an if-statement
		if(AST_if* if_stmt = dynamic_cast<AST_if*>(*i))
		{
			num_statements += count(if_stmt->iftrue);
			num_statements += count(if_stmt->iffalse);
		}
	}

	return num_statements;
}

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, "ast");
}

extern "C" void run (AST_php_script* in, Pass_manager* pm)
{
	int num_statements = count(in->statements);
	cout << num_statements << " statements found" << endl;
}
