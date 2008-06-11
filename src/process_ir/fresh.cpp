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
	static map<int, bool> randoms;
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


String* fresh (string prefix, int suffix)
{
	stringstream ss;
	ss << "__phc__" << prefix << suffix;

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
		int suffix = fresh_suffix ();
		VARIABLE_NAME* result = new VARIABLE_NAME (fresh (prefix, suffix));
		result->attrs->set ("phc.fresh.suffix", new Integer (suffix));
		result->attrs->set_true ("phc.codegen.st_entry_not_required");
		result->attrs->set_true ("phc.codegen.compiler_generated");
		return result;
	}
}


namespace HIR
{
	Variable* fresh_var(string prefix)
	{
		return new Variable (fresh_var_name (prefix));
	}

	VARIABLE_NAME* fresh_var_name (string prefix)
	{
		int suffix = fresh_suffix ();
		VARIABLE_NAME* result = new VARIABLE_NAME (fresh (prefix, suffix));
		result->attrs->set ("phc.fresh.suffix", new Integer (suffix));
		result->attrs->set_true ("phc.codegen.st_entry_not_required");
		result->attrs->set_true ("phc.codegen.compiler_generated");
		return result;
	}
}

namespace MIR
{
	Variable* fresh_var(string prefix)
	{
		return new Variable (fresh_var_name (prefix));
	}

	VARIABLE_NAME* fresh_var_name (string prefix)
	{
		int suffix = fresh_suffix ();
		VARIABLE_NAME* result = new VARIABLE_NAME (fresh (prefix, suffix));
		result->attrs->set ("phc.fresh.suffix", new Integer (suffix));
		result->attrs->set_true ("phc.codegen.st_entry_not_required");
		result->attrs->set_true ("phc.codegen.compiler_generated");
		return result;
	}

	HT_ITERATOR* fresh_iter ()
	{
		int suffix = fresh_suffix ();
		HT_ITERATOR* result = new HT_ITERATOR (suffix);
		result->attrs->set ("phc.fresh.suffix", new Integer (suffix));
		return result;
	}

	Label* fresh_label ()
	{
		int suffix = fresh_suffix ();
		LABEL_NAME* result = new LABEL_NAME (fresh ("L", suffix));
		result->attrs->set ("phc.fresh.suffix", new Integer (suffix));
		return new Label (result);
	}
}
