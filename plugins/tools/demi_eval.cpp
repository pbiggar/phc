/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * After each statement, add a debug_zval_dump call to each variable in the statement.
 */

#include "AST_transform.h"
#include "process_ast/XML_unparser.h"
#include "process_ast/PHP_unparser.h"
#include "process_ast/Pass_manager.h"
#include "codegen/Shredder.h"
#include "codegen/fresh.h"
#include "lib/List.h"

class Demi_eval : public AST_transform
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

		void post_statement (AST_statement *in, List<AST_statement*>* out)
		{
			if (in->classid() == AST_method::ID
					or in->classid() == AST_class_def::ID
					or in->classid() == AST_goto::ID
					or in->classid() == AST_label::ID
					or in->classid() == AST_branch::ID)
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
				PHP_unparser* pup = new PHP_unparser (ss);
				in->visit (pup);
				String* eval_string = new String (ss.str ());


				/* $TDEs0 = "$x = 5;";
				 * $TDEr0 = eval ($TDEs0);
				 */
				AST_variable* string_var = fresh_var ("TDEs");
				out->push_back (new AST_eval_expr (
							new AST_assignment (
								string_var,
								false, 
								new Token_string (eval_string))));

				out->push_back (new AST_eval_expr (
							new AST_assignment (
								fresh_var ("TDEr"),
								false,
								new AST_method_invocation (
									NULL, 
									new Token_method_name (new String ("eval")), 
									new List <AST_actual_parameter*> (
										new AST_actual_parameter (
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

extern "C" void run (AST_node* in, Pass_manager* pm, String* option)
{
	bool bool_option = false;
	if (*(option) == "true")
		bool_option = true;

	in->transform_children (new Demi_eval (pm, bool_option));
}
