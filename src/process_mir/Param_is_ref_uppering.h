/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 *  Replace param_is_ref with calls to ReflectionFunction.
 */

#ifndef PHC_PARAM_IS_REF_UPPERING
#define PHC_PARAM_IS_REF_UPPERING

#include "MIR_transform.h"
#include "AST.h"


class Param_is_ref_uppering : public MIR::Transform
{
public:
	void pre_assign_var (MIR::Assign_var* in, List<MIR::Statement*>* out);
};

#endif // PHC_PARAM_IS_REF_UPPERING
