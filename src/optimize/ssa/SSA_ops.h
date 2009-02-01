#ifndef PHC_SSA_OPS
#define PHC_SSA_OPS

#include "MIR.h"
#include "optimize/Basic_block.h"

/*
 * Regardless of the type of assignment or use, it can be represented in an
 * SSA_op of some kind.
 */
class SSA_op : virtual public GC_obj
{
public:
	int type_flag;
	SSA_op (int type_flag);
	virtual Basic_block* get_bb () = 0;
	virtual void dump() = 0;

	// Return the list of variables used by this operation
	virtual Alias_name_list* get_uses () = 0;

	// Factory method depending on the type of the BB
	// TODO: I expect this is no longer a good idea.
	static SSA_op* for_bb (Basic_block* bb);
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
	Alias_name_list* get_uses ();
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
	Alias_name_list* get_uses ();
};

class SSA_branch : public SSA_op
{
public:
	Branch_block* bb;

	SSA_branch (Branch_block* bb);
	Basic_block* get_bb ();
	void dump ();

	// Just the branch variable
	Alias_name_list* get_uses ();
};

class SSA_formal : public SSA_op
{
public:
	// Can take an entry or exit block.
	// TODO: should exits be separated? (this essentially lists escaping variables).
	Basic_block* bb;

	SSA_formal (Basic_block*);
	Basic_block* get_bb ();
	void dump ();

	// No uses here
	Alias_name_list* get_uses ();
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
	Alias_name_list* get_uses ();
};

class SSA_mu : public SSA_op
{
public:
	Basic_block* bb;

	Alias_name rhs;

	SSA_mu (Basic_block* bb, Alias_name rhs);

	Basic_block* get_bb ();
	void dump ();
	Alias_name_list* get_uses ();
};



typedef List<SSA_op*> SSA_op_list;

// Perform an arbitrary comparison, in order to allow the ops to index a map.
bool ssa_op_ptr_comparison (SSA_op* op1, SSA_op* op2);


#endif // PHC_SSA_OPS
