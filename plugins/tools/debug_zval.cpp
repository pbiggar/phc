/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * After each statement, add a debug_zval_dump call to each variable in the statement.
 */

#include "AST_transform.h"
#include "process_ast/AST_unparser.h"
#include "pass_manager/Plugin_pass.h"
#include "parsing/Parse_buffer.h"
#include "process_ir/General.h"

using namespace AST;

class Debug_zval : public Transform
{

protected:
	// we use the pass manager to lower some constructs we create, so that we
	// can run after the HIR.
	Pass_manager* pm; 

	List<Statement*>* debugs;
public:

	Debug_zval (Pass_manager* pm) : pm(pm)
	{
		debugs = new List<Statement*> ();
	}

	void post_statement (Statement *in, List<Statement*>* out)
	{
		out->push_back (in);
		out->push_back_all (debugs);
		debugs->clear ();
	}

	Variable* post_variable (Variable* var)
	{
		// printf ("$var: ");
		(*debugs 
			<< "printf (\"\\" << var << ": \");"
		).to_pass (s("rse"), var); // TODO do relative to current pass

		// Replace $x[] with just $x
		Variable* dumped_var = var;
		if (var->array_indices->size () == 1 && var->array_indices->front() == NULL)
		{
			dumped_var = var->clone ();
			dumped_var->array_indices->pop_front ();
		}

		// debug_zval_dump ($var);
		(*debugs 
			<< "debug_zval_dump (" << dumped_var << ");"
		).to_pass (s("rse"), var); // TODO do relative to current pass

		return var;
	}
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_before_named_pass (pass, s("AST-to-HIR"));
}

extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
{
	// We run the pass manager again on the generated code. We need to make sure
	// we dont cause infinite recursion
	in->transform_children (new Debug_zval (pm));
}
