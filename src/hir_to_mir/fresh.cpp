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

using namespace AST;

// TODO Globals. Bad. Do this another way.
extern struct gengetopt_args_info args_info;

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

int fresh_suffix (string prefix)
{
	static map<string, int> temps;
	if (args_info.obfuscate_flag)
		return unique_random ();
	else
		return temps[prefix]++;
}


String* fresh(string prefix)
{
	int t = fresh_suffix (prefix);
	stringstream ss;
	ss << prefix << t;

	return new String(ss.str());
}

Variable* fresh_var(string prefix)
{
	Variable* var = new Variable (
		NULL, 
		new VARIABLE_NAME (fresh (prefix)), 
		new List<Expr*>
		);

	var->variable_name->attrs->set_true ("phc.codegen.st_entry_not_required");
	return var;
}

HT_ITERATOR* fresh_iter ()
{
	return new HT_ITERATOR (fresh_suffix ("I"));
}

Label* fresh_label ()
{
	return new Label (
		new LABEL_NAME (fresh("L")));
}

