/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * After each statement, add a debug_zval_dump call to each variable in the statement.
 */

#include "AST_transform.h"
#include "process_ast/AST_unparser.h"
#include "pass_manager/Plugin_pass.h"
#include "ast_to_hir/Shredder.h"

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
		stringstream var_name;
		var->visit (new AST_unparser (var_name));
		var_name << ": ";

		// If we dont shred it, we cant generate code for it

		// printf ("\$var: ");
		Statement* print = new Eval_expr (
				new Method_invocation (
					NULL,
					new METHOD_NAME (new String ("printf")),
					new List<Actual_parameter*> (
						new Actual_parameter (false, 
							new STRING (new String (var_name.str ())))//,
//						new Actual_parameter (false, 
//							new STRING (new String (": ")))
							)));

		// Replace $x[] with just $x
		Variable* dumped_var = var;
		if (var->array_indices->size () == 1 && var->array_indices->front() == NULL)
		{
			dumped_var = var->clone ();
			dumped_var->array_indices->pop_front ();
		}

		// debug_zval_dump ($var);
		Statement* dump = new Eval_expr (
				new Method_invocation (
					NULL,
					new METHOD_NAME (new String ("debug_zval_dump")),
					new List<Actual_parameter*> (
						new Actual_parameter (false, dumped_var))));


		/* In order to shred these, they must be wrapped in a PHP_script
		 * first
		 * (Its hard to decide if this is a bug or not. Declaring it a bug would
		 * mean that we'd have to support passing any Node to any point in
		 * the pass queue. I dont think that's a good idea). */
		List<Statement*>* shredded = new List<Statement*> (print, dump);
		PHP_script* ir = new PHP_script (shredded);
		pm->run_from_until (new String ("lcf"), new String ("shred"), ir);
		debugs->push_back_all (shredded);

		return var;
	}
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_before_named_pass (pass, "hir");
}

extern "C" void run (Node* in, Pass_manager* pm)
{
	// We run the pass manager again on the generated code. We need to make sure
	// we dont cause infinite recursion
	in->transform_children (new Debug_zval (pm));
}
