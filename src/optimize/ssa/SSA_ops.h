#ifndef PHC_SSA_OPS
#define PHC_SSA_OPS

#include "MIR.h"
#include "optimize/Basic_block.h"

/*
 * Regardless of the type of assignment or use, it can be represented in an
 * SSA_op of some kind.
 *
 * The idea is to be able to differentiate between the different types of
 * assignment. This means that if a def belongs to a phi node, we dont think
 * it belongs to the basic block.
 */
class SSA_op : virtual public GC_obj
{
public:
	int type_flag;
	SSA_op (int type_flag);
	virtual Basic_block* get_bb () = 0;
	virtual void dump() = 0;

	// Return the list of variables used by this operation
	virtual old_Alias_name_list* get_uses () = 0;
};

class SSA_phi : public SSA_op
{
public:
	Basic_block* bb;
	Alias_name phi_lhs;

	SSA_phi (Basic_block* bb, Alias_name phi_lhs);
	Basic_block* get_bb ();
	void dump ();

	// The args which are not Literals.
	old_Alias_name_list* get_uses ();
};

class SSA_bb : public SSA_op
{
public:
	Basic_block* bb;

	MIR::Statement* get_statement ();

	SSA_bb (Basic_block* bb);
	Basic_block* get_bb ();
	void dump ();

	// Any uses in the statement (ignoring the phis in the block, obviously)
	old_Alias_name_list* get_uses ();
};

class SSA_chi : public SSA_op
{
public:
	Basic_block* bb;

	Alias_name lhs;
	Alias_name rhs;

	SSA_chi (Basic_block* bb, Alias_name lhs, Alias_name rhs);

	Basic_block* get_bb ();
	void dump ();
	old_Alias_name_list* get_uses ();
};

class SSA_mu : public SSA_op
{
public:
	Basic_block* bb;

	Alias_name rhs;

	SSA_mu (Basic_block* bb, Alias_name rhs);

	Basic_block* get_bb ();
	void dump ();
	old_Alias_name_list* get_uses ();
};



typedef List<SSA_op*> SSA_op_list;

// Perform an arbitrary comparison, in order to allow the ops to index a map.
bool ssa_op_ptr_comparison (SSA_op* op1, SSA_op* op2);


#endif // PHC_SSA_OPS
