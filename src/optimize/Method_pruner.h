/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Remove methods with the phc.optimize.unused_method annotation.
 */

#ifndef PHC_METHOD_PRUNER
#define PHC_METHOD_PRUNER

#include "MIR_transform.h"

class Method_pruner : public MIR::Transform, virtual public GC_obj
{
public:
    void pre_method (MIR::Method* in, MIR::Method_list* out)
	 {
		 if (in->attrs->is_true ("phc.optimize.used"))
			 out->push_back (in);
	 }
};

#endif // PHC_METHOD_PRUNER
