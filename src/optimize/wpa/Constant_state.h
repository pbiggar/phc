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

	void set_constant (Context cx, string name, Abstract_value* value);

	// Sets a constant whose name we don't know
	void set_unknown_constant (Context cx, Abstract_value* value);

	bool is_constant_defined (Context cx, string name);
	Abstract_value* get_constant (Context cx, string name);

	/*
	 * WPA interface
	 */

	// These should maybe be moved out?
	void pull_possible_null (Context cx, Index_node* node) {};
	void kill_value (Context cx, Index_node*) {};
	void assign_value (Context cx, Index_node*, Storage_node*) {};

};


#endif // PHC_CONSTANT_STATE
