#ifndef PHC_SSA_OPS
#define PHC_SSA_OPS

#include <stack>
#include "CFG.h"
#include "Basic_block.h"

using namespace boost;

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


#endif // PHC_SSA_OPS
