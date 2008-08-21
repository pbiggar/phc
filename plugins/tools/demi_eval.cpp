/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Replace every second statement with an eval () of the string with the string representation of the statement.
 */

#include "MIR_transform.h"
#include "pass_manager/Plugin_pass.h"
#include "process_ir/General.h"
#include "parsing/Parse_buffer.h"

using namespace MIR;

class Demi_eval : public Transform
{

	private:
		Demi_eval () {} // dont allow this constructor

	protected:

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
				// We can't simplify this because we need to properly quote the
				// string. The easiest way is to unparse it, and put it into a
				// STRING, so it will be properly unparsed.
				stringstream ss;
				MIR_unparser* pup = new MIR_unparser (ss, true);
				pup->unparse (in);
				STRING* eval_str = new STRING (s (ss.str ()));
				

				// eval ("$x = 5");
				(*out << "eval (" << eval_str << ");").finish (in);
			}
			convert = !convert;
		}

		// We will now need a symbol table entry for all the variables in this program. */
		VARIABLE_NAME* post_variable_name (VARIABLE_NAME* in)
		{
			in->attrs->erase ("phc.codegen.st_entry_not_required");
			return in;
		}
};

// Fresh variables are marked as not needing a symbol table entry automatically. We cant get one in an eval (for now).
extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("mir"));
}

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager* pm, String* option)
{
	bool bool_option = false;
	if (*(option) == "true")
		bool_option = true;

	in->transform_children (new Demi_eval (pm, bool_option));
}
