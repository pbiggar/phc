/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert MIR to prepare for conversion to SSA form. Currently, just convert
 * Pre_op to SSA_pre_op.
 * */

#ifndef PHC_INTO_SSA
#define PHC_INTO_SSA

#include "MIR_transform.h"

class Into_SSA : public MIR::Transform, virtual public GC_obj
{
public:
};

#endif // PHC_INTO_SSA
