/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert Foreach statements to use ArrayIterators.
 */

#ifndef PHC_FOREACH_UPPERING_H
#define PHC_FOREACH_UPPERING_H

#include "MIR_transform.h"


class Foreach_uppering : public MIR::Transform, virtual public GC_obj
{
public:
	void pre_foreach_reset (MIR::Foreach_reset* in, MIR::Statement_list* out);
	void pre_foreach_next (MIR::Foreach_next* in, MIR::Statement_list* out);
	void pre_foreach_end (MIR::Foreach_end* in, MIR::Statement_list* out);
	MIR::Expr* pre_foreach_has_key (MIR::Foreach_has_key* in);
	MIR::Expr* pre_foreach_get_key (MIR::Foreach_get_key* in);
	void pre_assign_var  (MIR::Assign_var* in, MIR::Statement_list* out);
};

#endif // PHC_FOREACH_UPPERING_H
