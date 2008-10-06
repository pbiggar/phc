#ifndef PHC_SSA
#define PHC_SSA

#include <stack>
#include "CFG.h"
#include "Basic_block.h"

using namespace boost;

/*
 * How to convert into HSSA form algorithm 2 from "Effective Representation of
 * Aliases and Indirect Memory Operations in SSA Form", by Chow et al.
 *
 * 1) Assign virtual variables to indirect variables in the program
 *
 * 2)	Perform alias analysis and insert MEW and CHI for all scalar and virtual variables
 *
 * 3) Insert PHIs using Cytron algorithm, including CHI as assignments
 *
 * 4) Rename all scalar and virtual variables using Cytron algorithm
 *
 * 5) Simultaneously:
 *		a)	Perform DCE, including on PHIs and CHIs, using Cytron algorithm
 *		b)	Perform steps 1 and 2 of algorithm 1 (Compute Zero Versions), to set
 *			the HasRealOcc flag for all variable versions. These steps are:
 *				czv1)	Initialize flag HasRealOcc for each variable version created
 *						by SSA renaming to false.
 *				czv2)	Pass over the program. On visiting a real occurrence, set the
 *						HasRealOcc flag for the variable version to true.
 *
 *	6)	Performs steps 3, 4 and 5 of CZV algorithm to set variable versions to 0. These steps are:
 *		czv3)	For each program varaible, create NonZeroPhiList and init to empty.
 *		czv4)	Iterate through all variable versions:
 *				a)	If HasRealOcc is false, and is defined by CHI, set version to 0
 *				b) If HasRealOcc is false, and is defined by PHI:
 *					-	If the version of one of the operands is 0, set version to 0
 *					-	Else if HasRealOcc flag of all operand is set to true, set
 *						HasRealOcc to true
 *					-	Else add version to NonZeroPhiList for the variable
 *		czv5)	For each program variable, iterate until its NonZeroPhiList no longer changes:
 *				a)	For each version in NonZeroPhiList
 *					-	If the version of one of the operands in 0, set version to 0
 *						and remove from NonZeroPhiList
 *					-	Else if the HasRealOcc flag of all operands is true, set
 *						HasRealOcc to true and remove from NonZeroPhiList
 *
 *	7)	Hash a unique value unmber and create the corresponding hash table VAR
 *		node for each scalar and virtual variable version that are determined to
 *		be live in Step 5a.
 *
 *	8) Conduct a pre-order traversal of the dominator tree of the control flow
 *		graph of the program and apply global value numbering to the code in each
 *		basic_block:
 *		a)	Hash expression trees bottom-up into the hash-table, searching for any
 *			existing matching entry before creating each new value number and
 *			entry.  At a VAR node, use the node created in step 7 for that
 *			variable version.
 *		b)	For two IVAR nodes to match, two conditions must be satisfied:
 *			1) Their address expressions have the same value number, and
 *			2) the versions of their virtual variables are either the same, or are
 *				separated by definitions that do not alias with the IVAR.
 *		c)	For each assignment statement, including PHI and CHI, represent its
 *			lhs by making the statement point to the VAR or IVAR for direct and
 *			indirect assignments respectively. Also make the VAR or IVAR node
 *			point back to its defining statement.
 *		d)	Update all PHI, MEW and CHI operands and results to make them refer to
 *			entries in the hash-table.
 *				
 */ 

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
