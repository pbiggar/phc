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
#include "Value_analysis.h"

class Constant_state : public WPA_lattice <string, const Absval_cell>
{
public:
	Constant_state (Whole_program* wp);

	/*
	 * WPA lattice interface
	 */

	string context_merge_key (string) const;

	/*
	 * Interface
	 */

	void set_constant (Context* cx, string name, const Abstract_value* value);

	// Sets a constant whose name we don't know
	void set_unknown_constant (Context* cx, const Abstract_value* value);

	bool is_constant_defined (Context* cx, Result_state state, string name) const;
	const Abstract_value* get_constant (Context* cx, Result_state state, string name) const;

	/*
	 * WPA interface
	 */

	// TODO: I think these aren't pure virtual, so they can be removed.
	void pull_possible_null (Context* cx, Index_node* node) {};
	void kill_value (Context* cx, Index_node*, bool) {};
	void assign_value (Context* cx, Index_node*, Storage_node*) {};

};


#endif // PHC_CONSTANT_STATE
