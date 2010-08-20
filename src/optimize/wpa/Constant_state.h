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

	bool can_constant_be_defined (Context* cx, Result_state state, string name, bool case_insensitive = false) const;
	void set_constant (Context* cx, string name, const Abstract_value* value, bool case_insensitive = false);

	// Sets a constant whose name we don't know
	void set_unknown_constant (Context* cx, const Abstract_value* value, bool case_insensitive = false);

	bool is_constant_defined (Context* cx, Result_state state, string name) const;
	const Abstract_value* get_constant (Context* cx, Result_state state, string name) const;

	/*
	 * WPA interface
	 */

	void pull_possible_null (Context* cx, const Index_node* node) {};
};


#endif // PHC_CONSTANT_STATE
