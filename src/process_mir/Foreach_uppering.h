/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert Foreach statements to use ArrayIterators.
 */

#ifndef PHC_FOREACH_UPPERING_H
#define PHC_FOREACH_UPPERING_H

#include "MIR_transform.h"


class Foreach_uppering : public MIR::Transform
{
public:
	void pre_foreach_reset (MIR::Foreach_reset* in, List<MIR::Statement*>* out);
	void pre_foreach_next (MIR::Foreach_next* in, List<MIR::Statement*>* out);
	void pre_foreach_end (MIR::Foreach_end* in, List<MIR::Statement*>* out);
	MIR::Expr* pre_foreach_has_key (MIR::Foreach_has_key* in);
	MIR::Expr* pre_foreach_get_key (MIR::Foreach_get_key* in);
	MIR::Expr* pre_foreach_get_val (MIR::Foreach_get_val* in);
};

#endif // PHC_FOREACH_UPPERING_H
