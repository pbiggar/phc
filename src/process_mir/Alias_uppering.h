/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Upper method, class and function aliases.
 */

#ifndef PHC_ALIAS_UPPERING
#define PHC_ALIAS_UPPERING

#include "MIR_transform.h"

class Alias_uppering : public MIR::Transform, virtual public GC_obj
{
public:
	void pre_class_alias (MIR::Class_alias* in, MIR::Statement_list* out);
	void pre_method_alias (MIR::Method_alias* in, MIR::Statement_list* out);
	void pre_interface_alias (MIR::Interface_alias* in, MIR::Statement_list* out);
};

#endif // PHC_ALIAS_UPPERING
