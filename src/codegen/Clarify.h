/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Make implicit parts of a script explicit for the Code Generator.
 */

#ifndef PHC_CLARIFY_H
#define PHC_CLARIFY_H

#include "MIR_visitor.h"

class Clarify : public MIR::Visitor, virtual public GC_obj
{
	void post_method (MIR::Method* in);
};


#endif // PHC_CLARIFY_H
