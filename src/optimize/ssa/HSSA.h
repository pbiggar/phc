#ifndef PHC_HSSA
#define PHC_HSSA

class CFG;
class SSA_name;
class Basic_block;
class Whole_program;

#include "process_ir/General.h"

class HSSA : virtual public GC_obj
{
protected:
	Whole_program* wp;
	CFG* cfg;
	bool check_ssi;

	/*
	* Following the example of GCC, we give each SSA_NAME a distinct number.
	* So instead of x_0, y_0, x_1, y_1, as in textbooks, we use x_0, y_1, x_2,
	* y_3. This allows us to use the version as an index into a bitvector (which
	* we may or may not do in the future).
	*/
	int counter;
	Map<std::string, Stack<int> > var_stacks;

public:
	HSSA(Whole_program* wp, CFG* cfg);

	void convert_to_hssa_form ();
	void convert_out_of_hssa_form ();

protected:
	/*
	 * Generic interface to insert nodes. SSA will insert phi nodes, while SSI
	 * variants will insert both phi and sigma nodes.
	 */
	virtual void insert_nodes ();

	/*
	 * Insertion of phi nodes.
	 */
	bool insert_phi_nodes();

	/*
	 * Renaming (Cooper/Torczon, section 9.3.4).
	 * Given a BB, this will perform recursively perform SSA renaming,
	 * descending the dominator tree. COUNTER is the version of the next
	 * SSA_NAME. VAR_STACKS is the stack of versions used by a named variable.
	 * When returning from recursing, the stack is popped to reveal the version
	 * used on the previous level.
	 */
	void rename_vars (Basic_block* bb);
	void push_to_var_stack (SSA_name* name);
	int read_var_stack (SSA_name* name);
	void pop_var_stack (SSA_name* name);

	// Rename the variable into SSA, giving it a version.
	void create_new_ssa_name (SSA_name* name);
	void debug_top_var_stack (SSA_name* var, std::string type);
};


#endif // PHC_HSSA
