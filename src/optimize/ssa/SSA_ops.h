#ifndef PHC_SSA_OPS
#define PHC_SSA_OPS

#include <boost/functional/hash.hpp>

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


DECL (SSA_op);
DECL (SSA_def);
DECL (SSA_use);

class SSA_op : virtual public GC_obj
{
public:
	Basic_block* bb;
	SSA_name* name;
	int type_flag;

	SSA_op (Basic_block* bb, SSA_name* name, int type_flag);
	void dump();

public:
	// For defs, these are uses. For uses, these are defs.
	// For SSA_PHI, this is the LHS, or all the RHSs.
	// For SSA_CHI, this is the LHS, or the RHS
	// For SSA_BB, this is the must-defs, or all the uses.
	SSA_op_list aux_ops;
};

class SSA_def : public SSA_op
{
public:
	SSA_def (Basic_block* bb, SSA_name* name, int type_flag);

	SSA_use_list* get_uses ();
};

class SSA_use : public SSA_op
{
public:
	SSA_use (Basic_block* bb, SSA_name* name, int type_flag);

	SSA_def_list* get_defs ();
};


class SSA_op_map_equals : virtual public GC_obj
{
public:
	bool operator() (SSA_op* op1, SSA_op* op2) const
	{
		// Vertex pointers wont change, even when the graph is updated.
	
		return ((typeid (*op1) == typeid (*op2))
			&& (op1->bb->vertex == op2->bb->vertex)
			&& (op1->type_flag == op2->type_flag)
			&& (*op1->name == *op2->name));
	}
};

class SSA_op_map_hash : virtual public GC_obj
{
public:
	size_t operator() (SSA_op* op) const
	{
		size_t seed = 0;

		boost::hash_combine(seed, op->name->hash ());
		boost::hash_combine(seed, op->type_flag);
		boost::hash_combine(seed, op->bb->vertex);

		return seed;
	}
};



template <class _Tp>
class SSA_op_map : public Map<SSA_op*, _Tp, SSA_op_map_hash, SSA_op_map_equals>
{
};


#endif // PHC_SSA_OPS
