/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Abstraction for passes that simply propagate a lattice. This avoids a great
 * deal of code duplication.
 *
 */

#ifndef PHC_WPA_LATTICE
#define PHC_WPA_LATTICE

#include "WPA.h"
#include "optimize/Lattice.h"

class WPA_lattice : public WPA
{
public:
	WPA_lattice (Whole_program* wp);


	// WPA
	void init (Context outer);
	void forward_bind (Context caller, Context entry);
	void backward_bind (Context caller, Context exit);

	void kill_value (Context cx, Index_node* lhs);

	void assign_value (Context cx, Index_node* lhs, Storage_node* storage);


	void pull_init (Context cx);
	void pull_first_pred (Context cx, Context pred);
	void pull_pred (Context cx, Context pred);
	void pull_possible_null (Context cx, Index_node* node) = 0;
	void pull_finish (Context cx);

	void aggregate_results (Context cx);

	bool equals (WPA* other);
	void dump (Context cx, string comment);
	void dump_everything (string comment);

	void merge_contexts ();

	// Get results
	Lattice_cell* get_value (Context cx, Alias_name name);

private:
	void init_outs (Context cx);

protected:
	CX_lattices ins;
	CX_lattices clones;
	CX_lattices outs;

	friend class Whole_program;
};

#endif // PHC_WPA_LATTICE
