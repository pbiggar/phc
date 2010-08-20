/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A lattice representing values we wish to represent. Currently models types
 * and literals.
 *
 */

#ifndef PHC_VALUE_ANALYSIS
#define PHC_VALUE_ANALYSIS

#include "optimize/Abstract_value.h"

#include "WPA_lattice.h"

class Absval_cell;

class Value_analysis : public WPA_lattice <const Alias_name*, const Absval_cell>
{
public:
	Value_analysis (Whole_program* wp);

	/*
	 * WPA lattice interface
	 */
	const Alias_name* context_merge_key (const Alias_name*) const;

	/*
	 * WPA interface
	 */

	void set_storage (Context* cx, const Storage_node* storage, const Types* types);
	void set_scalar (Context* cx, const Value_node* storage, const Abstract_value* val);
	void pull_possible_null (Context* cx, const Index_node* node);


	void kill_value (Context* cx, const Index_node*, bool);
	void assign_value (Context* cx, const Index_node*, const Storage_node*);

	void remove_fake_node (Context* cx, const Index_node* fake);

	const Absval_cell* get_value (Context* cx, Result_state state, const Alias_name* name) const;




	/*
	 * Literals
	 */

	const MIR::Literal* get_lit (Context* cx, Result_state state, const Alias_name* name) const;
	

	/*
	 * Types
	 */

	void remove_non_objects (Context* cx, Result_state state, const Index_node*);

	const Types* get_types (Context* cx, Result_state state, const Alias_name* name) const;


	static Types* get_bin_op_types (	Context* cx,
												const Abstract_value* left,
												const Abstract_value* right,
												string op);

	static Types* get_bin_op_type (string left, string right, string op);

	static Types* get_unary_op_types (Context* cx, const Abstract_value* operand, string op);
};


class Absval_cell : virtual public GC_obj
{
public:
	const Abstract_value* const value;
	bool case_insensitive;

	Absval_cell (const Abstract_value*, bool case_insensitive = false);
public:
	void dump (std::ostream& os = cdebug) const;
	bool equals (const Absval_cell* other) const;
	const Absval_cell* meet (const Absval_cell* other) const;

	static const Absval_cell* get_default ();
	static const Absval_cell* TOP;
};

SET_COMPARABLE (Absval_cell);
typedef Lattice_map<string, const Absval_cell> __str_lattice_type;
typedef CX_lattices<string, const Absval_cell> __str_cx_lattice_type;
typedef Lattice_map<const Alias_name*, const Absval_cell> __alias_lattice_type;
typedef CX_lattices<const Alias_name*, const Absval_cell> __alias_cx_lattice_type;


SET_COMPARABLE (__str_cx_lattice_type);
SET_COMPARABLE (__str_lattice_type);
SET_COMPARABLE (__alias_cx_lattice_type);
SET_COMPARABLE (__alias_lattice_type);




#endif // PHC_VALUE_ANALYSIS
