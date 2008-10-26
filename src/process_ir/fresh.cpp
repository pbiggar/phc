/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate a fresh temporary
 */

#include "fresh.h"
#include <cstdlib>
#include <ctime>
#include "cmdline.h"

using namespace std;

// TODO Globals. Bad. Do this another way.
extern struct gengetopt_args_info args_info;

// We need to set 
int fresh_suffix_counter = 0;

// We only want to call seed once, on first call of unique_random. We abuse the
// static initializer, but we need a non-void value for this.
int 
seed ()
{
	srand (time (0));
	return 0;
}

// Return a ranom int which hasnt been returned before
int
unique_random ()
{
	static Map<int, bool> randoms;
	static int x __attribute__((unused)) = seed (); // singleton-lite
	int num;

	// find a new number
	do
	{
		num = rand ();
	}
	while (randoms [num]);
	randoms [num] = true;
	return num;
}

int fresh_suffix ()
{
	if (args_info.obfuscate_flag)
		return unique_random ();
	else
		return fresh_suffix_counter++;
}

// Don't ever give a fresh variable, if it's already used in the program.
set<string> unfresh_vars;

String* fresh (string prefix)
{
	stringstream ss;
	do
	{
		ss.str(""); // erase
		//	ss << "__phc__" << prefix << suffix;
		ss << prefix << fresh_suffix();
	}
	while (unfresh_vars.find (ss.str()) != unfresh_vars.end());

	return new String(ss.str());
}

namespace AST
{
	Variable* fresh_var(string prefix)
	{
		return new Variable (fresh_var_name (prefix));
	}

	VARIABLE_NAME* fresh_var_name (string prefix)
	{
		VARIABLE_NAME* result = new VARIABLE_NAME (fresh (prefix));
		result->attrs->set_true ("phc.codegen.st_entry_not_required");
		result->attrs->set_true ("phc.codegen.compiler_generated");
		return result;
	}
}


namespace HIR
{
	VARIABLE_NAME* fresh_var_name (string prefix)
	{
		VARIABLE_NAME* result = new VARIABLE_NAME (fresh (prefix));
		result->attrs->set_true ("phc.codegen.st_entry_not_required");
		result->attrs->set_true ("phc.codegen.compiler_generated");
		return result;
	}

	CLASS_NAME* fresh_class_name (string prefix)
	{
		return new CLASS_NAME (fresh (prefix));
	}

	INTERFACE_NAME* fresh_interface_name (string prefix)
	{
		return new INTERFACE_NAME (fresh (prefix));
	}

	METHOD_NAME* fresh_method_name (string prefix)
	{
		return new METHOD_NAME (fresh (prefix));
	}
}

namespace MIR
{
	VARIABLE_NAME* fresh_var_name (string prefix)
	{
		VARIABLE_NAME* result = new VARIABLE_NAME (fresh (prefix));
		result->attrs->set_true ("phc.codegen.st_entry_not_required");
		result->attrs->set_true ("phc.codegen.compiler_generated");
		return result;
	}

	HT_ITERATOR* fresh_iter ()
	{
		return new HT_ITERATOR (fresh ("ht_iterator"));
	}

	Label* fresh_label ()
	{
		return new Label (fresh_label_name ());
	}

	LABEL_NAME* fresh_label_name ()
	{
		return new LABEL_NAME (fresh ("L"));
	}
}
