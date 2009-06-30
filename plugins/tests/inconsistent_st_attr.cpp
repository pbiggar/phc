/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that each variable is consistenly either in the symbol table, or not.
 */

#include "process_ir/General.h"
#include "pass_manager/Plugin_pass.h"
#include "MIR_visitor.h"

using namespace MIR;
using namespace std;

bool success = true;

class Inconstent_st_attr : public Visitor
{
private:
	Map<string, bool> var_map;
	bool check; // only check with methods


public:
	Inconstent_st_attr () : check(false) {}

	// Only check within methods
	void children_method (Method* in)
	{
		var_map.clear (); // This is per-method only
		check = true;
		visit_statement_list (in->statements);
		check = false;
	}

	void pre_variable_name (VARIABLE_NAME* in)
	{
		if (!check)
			return;

		if (var_map.find(*in->value) != var_map.end()) // already exists
		{
			if (var_map[*in->value] != in->attrs->is_true ("phc.codegen.st_entry_not_required"))
			{
				success = false;
				cout << "Failure" << endl;

				cdebug << "Variable: ";
				debug (in);
				cdebug << " expected " << var_map[*in->value] << " st entry, but got " << in->attrs->is_true ("phc.codegen.st_entry_not_required") << endl;
				xadebug (in);
			}
		}
		else
			var_map [*in->value] = in->attrs->is_true ("phc.codegen.st_entry_not_required");
	}
};

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager*, String* option)
{
	in->visit (new Inconstent_st_attr);
}

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_mir_pass (pass);
}

extern "C" void unload ()
{
	if (success)
		cout << "Success" << endl;
}
