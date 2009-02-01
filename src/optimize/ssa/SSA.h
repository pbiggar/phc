#ifndef PHC_SSA
#define PHC_SSA

#include "lib/Stack.h"

#include "../CFG.h"
#include "../Basic_block.h"

// Renaming (Cooper/Torczon, section 9.3.4).

/* Given a BB, this will perform recursively perform SSA renaming, descending
 * the dominator tree. COUNTER is the version of the next SSA_NAME. VAR_STACKS
 * is the stack of versions used by a named variable. When returning from
 * recursing, the stack is popped to reveal the version used on the previous
 * level. */
class SSA_renaming : virtual public GC_obj
{
	CFG* cfg;

	/* Following the example of GCC, we give each SSA_NAME a distinct number.
	 * So instead of x_0, y_0, x_1, y_1, as in textbooks, we use x_0, y_1,
	 * x_2, y_2. This allows us use the version as an index into a bitvector
	 * (which we may or may not do in the future).
	 */
	int counter;
	Map<Alias_name, Stack<int> > var_stacks;

public:
	SSA_renaming (CFG* cfg);

	/*
	 * Public interface
	 */
	void rename_vars (Basic_block* bb);

private:
	/*
	 * Helper functions
	 */
	void push_to_var_stack (Alias_name name, int version);
	int read_var_stack (Alias_name name);
	void pop_var_stack (Alias_name name);

	// Rename the variable into SSA, giving it a version.
	void create_new_ssa_name (Alias_name name);
	void debug_var_stacks ();
};

#endif // PHC_SSA
