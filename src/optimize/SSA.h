#ifndef PHC_SSA
#define PHC_SSA

#include <boost/graph/properties.hpp>
#include <stack>

using namespace boost;

#include "CFG.h"

class Phi : virtual public Object
{
public:
	MIR::VARIABLE_NAME* lhs;
	// TODO make private
	list<pair<MIR::VARIABLE_NAME*, Edge*> >* args;

public:
	Phi (MIR::VARIABLE_NAME* lhs);

	void add_arg (int version, Edge* source);
	MIR::VARIABLE_NAME_list* get_args ();
	list<pair<MIR::VARIABLE_NAME*, Edge*> >* get_arg_edges ();

	Phi* clone () { assert (0); } // TODO

	void dump ();
};

typedef List<Phi*> Phi_list;

class Dominance
{
	CFG* cfg;
	Map <Basic_block*, BB_list*> df;
	Map <Basic_block*, BB_list*> forward_idoms;
	Map <Basic_block*, Basic_block*> idoms;

public:
	Dominance (CFG* cfg);


	// Terms are defined in a comment in SSA.cpp.
	void calculate_immediate_dominators ();
	void calculate_local_dominance_frontier ();
	void propagate_dominance_frontier_upwards ();

private:
	friend class Basic_block;
	BB_list* get_bb_dominance_frontier (Basic_block*);
	void add_to_bb_dominance_frontier (Basic_block* bb, Basic_block* frontier);
	Basic_block* get_bb_immediate_dominator (Basic_block*);
	BB_list* get_blocks_dominated_by_bb (Basic_block* bb);
};

// Renaming (Cooper/Torczon, setion 9.3.4).

/* Given a BB, this will perform recursively perform SSA renaming, descending
 * the dominator tree. COUNTER is the version of the next SSA_NAME. VAR_STACKS
 * is the stack of versions used by a named variable. When returning from
 * recursing, the stack is popped to reveal the version used on the previous
 * level. */
class SSA_renaming
{
	CFG* cfg;

	/* Following the example of GCC, we give each SSA_NAME a distinct number.
	 * So instead of x_0, y_0, x_1, y_1, as in textbooks, we use x_0, y_1,
	 * x_2, y_2. This allows us use the version as an index into a bitvector
	 * (which we may or may not do in the future).
	 */
	int counter;
	map<string, stack<int> > var_stacks;

public:
	SSA_renaming (CFG* cfg);

	/*
	 * Public interface
	 */
	void initialize_var_stack (MIR::VARIABLE_NAME* var_name);
	void rename_vars (Basic_block* bb);

private:
	/*
	 * Helper functions
	 */
	void push_to_var_stack (MIR::VARIABLE_NAME* var_name, int version);
	int read_var_stack (MIR::VARIABLE_NAME* var_name);
	void pop_var_stack (MIR::VARIABLE_NAME* var_name);

	// Rename the variable into SSA, giving it a version.
	void create_new_ssa_name (MIR::VARIABLE_NAME* var_name);
	void debug_var_stacks ();
};

#endif // PHC_SSA