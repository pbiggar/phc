/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Once a constant is defined, it cannot be redefined or undefined. Keep a list
 * of constants defined before this point.
 */

#ifndef PHC_CONSTANT_STATE
#define PHC_CONSTANT_STATE

#include "WPA_lattice.h"

class Constant_state : public WPA_lattice
{
public:
	Constant_state (Whole_program* wp);

	/*
	 * Interface
	 */

	void set_constant (Context cx, Abstract_value* name, Abstract_value* value);
	Abstract_value* get_constant (Context cx, MIR::Constant* constant);

	/*
	 * WPA interface
	 */

	void pull_possible_null (Context cx, Index_node* node);

};


#endif // PHC_CONSTANT_STATE
