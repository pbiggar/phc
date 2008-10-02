#ifndef PHC_SSA
#define PHC_SSA

#include <stack>
#include "CFG.h"
#include "Basic_block.h"

using namespace boost;

class Dominance
{
	// TODO: friend the calculate_dominace class
public:
	// Use vertexes so that the Blocks they refer to can be updated without
	// invalidating the dominance information.

	// Forward dominance frontier
	map <vertex_t, list<vertex_t> > df;

	// BB -> blocks dominated by BB
	map <vertex_t, list<vertex_t> > idominated;

	// BB -> BB's dominator
	map <vertex_t, vertex_t> idominator;

	CFG* cfg;


public:
	Dominance (CFG* cfg);

	void dump ();

	// Terms are defined in a comment in SSA.cpp.
	void calculate_forward_dominance ();
	void calculate_reverse_dominance ();

	// Dominance on the reverse CFG
	Dominance* reverse_dominance;

private:
	friend class Basic_block;
	BB_list* get_bb_dominance_frontier (Basic_block*);
	void add_to_bb_dominance_frontier (Basic_block* bb, Basic_block* frontier);
	bool is_bb_in_dominance_frontier (Basic_block* bb, Basic_block* frontier);

	Basic_block* get_bb_immediate_dominator (Basic_block*);
	BB_list* get_blocks_dominated_by_bb (Basic_block* bb);
	bool is_bb_dominated_by (Basic_block* bb, Basic_block* potential_dom);

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

/*
 * Regardless of the type of assignment or use, it can be represented in an
 * SSA_op of some kind.
 */
class SSA_op : public Object
{
public:
	SSA_op* clone () { assert (0); }
	virtual Basic_block* get_bb () = 0;
	virtual void dump() = 0;

	// Return the list of variables used by this operation
	virtual MIR::VARIABLE_NAME_list* get_uses () = 0;

	// Factory method depending on the type of the BB
	static SSA_op* for_bb (Basic_block* bb);
};

class SSA_phi : public SSA_op
{
public:
	Basic_block* bb;
	MIR::VARIABLE_NAME* phi_lhs;

	SSA_phi (Basic_block* bb, MIR::VARIABLE_NAME* phi_lhs);
	Basic_block* get_bb ();
	void dump ();

	// The args which are not Literals.
	MIR::VARIABLE_NAME_list* get_uses ();
};

class SSA_stmt : public SSA_op
{
public:
	Statement_block* bb;

	SSA_stmt (Statement_block* bb);
	MIR::Statement* get_statement ();
	Basic_block* get_bb ();
	void dump ();

	// Any uses in the statement (ignoring the phis in the block, obviously)
	MIR::VARIABLE_NAME_list* get_uses ();
};

class SSA_branch : public SSA_op
{
public:
	Branch_block* bb;

	SSA_branch (Branch_block* bb);
	Basic_block* get_bb ();
	void dump ();

	// Just the branch variable
	MIR::VARIABLE_NAME_list* get_uses ();
};

class SSA_formal : public SSA_op
{
public:
	Entry_block* bb;

	SSA_formal (Entry_block*);
	Basic_block* get_bb ();
	void dump ();

	// No uses here
	MIR::VARIABLE_NAME_list* get_uses ();
};



typedef List<SSA_op*> SSA_op_list;

// Perform an arbitrary comparison, in order to allow the ops to index a map.
bool ssa_op_ptr_comparison (SSA_op* op1, SSA_op* op2);

#endif // PHC_SSA
