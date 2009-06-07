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

class Value_analysis : public WPA_lattice <Absval_cell>
{
public:
	Value_analysis (Whole_program* wp);

	/*
	 * WPA interface
	 */

	void set_storage (Context cx, Storage_node* storage, Types* types);
	void set_scalar (Context cx, Value_node* storage, Abstract_value* val);
	void pull_possible_null (Context cx, Index_node* node);


	/*
	 * Literals
	 */

	MIR::Literal* get_lit (Context cx, Alias_name name);

	/*
	 * Types
	 */

	Types* get_types (Context cx, Alias_name name);


	static Types* get_bin_op_types (	Context cx,
												Abstract_value* left,
												Abstract_value* right,
												string op);

	static Types* get_bin_op_type (string left, string right, string op);

	static Types* get_unary_op_types (Context cx, Abstract_value* operand, string op);
};


class Absval_cell : virtual public GC_obj
{
public:
	Absval_cell (Abstract_value*);
	Abstract_value* const value;

public:
	void dump (std::ostream& os = cdebug);
	bool equals (Absval_cell* other);
	Absval_cell* meet (Absval_cell* other);

	static Absval_cell* get_default ();
	static Absval_cell* TOP;
};

SET_COMPARABLE (Absval_cell);
SET_COMPARABLE (CX_lattices<Absval_cell>);
SET_COMPARABLE (Lattice_map<Absval_cell>);




#endif // PHC_VALUE_ANALYSIS
