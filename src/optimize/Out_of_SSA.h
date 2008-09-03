/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert MIR to prepare for conversion to SSA form. Currently, just convert
 * Pre_op to SSA_pre_op.
 * */

#ifndef PHC_OUT_OF_SSA
#define PHC_OUT_OF_SSA

#include "MIR_visitor.h"

class Out_of_SSA : public MIR::Transform
{
public:
	// Convert
	//		$def = $use ++ 1; // not real PHP
	//	into
	//		$def = $use;
	//		++$def;
	void pre_ssa_pre_op (MIR::SSA_pre_op* in, MIR::Statement_list* out)
	{
		out->push_back (new MIR::Assign_var (in->def, false, in->use));
		out->push_back (new MIR::Pre_op (in->op, in->def));
	}
};

#endif // PHC_OUT_OF_SSA
