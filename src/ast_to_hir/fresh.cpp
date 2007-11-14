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


String* fresh(string prefix)
{
	int t;
	static map<string, int> temps;
	if (args_info.obfuscate_flag)
		t = unique_random ();
	else
		t = temps[prefix]++;

	stringstream ss;
	ss << prefix << t;

	return new String(ss.str());
}

AST_variable* fresh_var(string prefix)
{
	AST_variable* var = new AST_variable (
		NULL, 
		new Token_variable_name (fresh (prefix)), 
		new List<AST_expr*>
		);

	var->variable_name->attrs->set_true ("phc.codegen.st_entry_not_required");
	return var;
}

AST_label* fresh_label ()
{
	return new AST_label (
		new Token_label_name (fresh("L")));
}

