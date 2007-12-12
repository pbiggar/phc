/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * After each statement, add a debug_zval_dump call to each variable in the statement.
 */

#include "HIR_transform.h"
#include "process_hir/HIR_unparser.h"
#include "pass_manager/Plugin_pass.h"
#include "hir_to_mir/Shredder.h"
#include "process_ir/fresh.h"
#include "lib/List.h"

using namespace HIR;

class Demi_eval : public Transform
{

	private:
		Demi_eval () {} // dont allow this constructor

	protected:
		// we use the pass manager to lower some constructs we create, so that we
		// can run after the HIR.
		Pass_manager* pm;

		// We convert every second statement to an eval, so this keeps track. It
		// gets initialized by INIT in the constructor.
		bool convert;

	public:

		Demi_eval (Pass_manager* pm, bool init)
		{
			convert = init;
		}

		void post_statement (Statement *in, List<Statement*>* out)
		{
			if (in->classid() == Method::ID
					or in->classid() == Class_def::ID
					or in->classid() == Goto::ID
					or in->classid() == Label::ID
					or in->classid() == Branch::ID)
			{
				out->push_back (in);
				return;
			}

			if (!convert)
			{
				out->push_back (in);
			}
			else
			{
				// unparse the statement into a string
				stringstream ss;
				HIR_unparser* pup = new HIR_unparser (ss);
				in->visit (pup);
				String* eval_string = new String (ss.str ());


				/* $TDEs0 = "$x = 5;";
				 * $TDEr0 = eval ($TDEs0);
				 */
				Variable* string_var = fresh_var ("TDEs");
				out->push_back (new Eval_expr (
							new Assignment (
								string_var,
								false, 
								new STRING (eval_string))));

				out->push_back (new Eval_expr (
							new Assignment (
								fresh_var ("TDEr"),
								false,
								new Method_invocation (
									NULL, 
									new METHOD_NAME (new String ("eval")), 
									new List <Actual_parameter*> (
										new Actual_parameter (
											false, 
											string_var->clone ()))))));
			}
			convert = !convert;
		}
};

// Fresh variables are marked as not needing a symbol table entry automatically. We cant get one in an eval (for now).
extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_before_named_pass (pass, "ast");
}

extern "C" void run_ast (Node* in, Pass_manager* pm, String* option)
{
	bool bool_option = false;
	if (*(option) == "true")
		bool_option = true;

	in->transform_children (new Demi_eval (pm, bool_option));
}
