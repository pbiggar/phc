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
	void forward_bind (Basic_block* caller, Entry_block* entry);
	void backward_bind (Basic_block* context, Exit_block* exit);

	void kill_value (Basic_block* bb, Index_node* lhs);

	void assign_value (Basic_block* bb, Index_node* lhs,
							 Storage_node* storage, certainty cert);


	void pull_init (Basic_block* bb);
	void pull_first_pred (Basic_block* bb, Basic_block* pred);
	void pull_pred (Basic_block* bb, Basic_block* pred);
	void pull_finish (Basic_block* bb);

	void aggregate_results (Basic_block* bb);

	bool equals (WPA* other);
	void dump (Basic_block* bb, string comment);

	// Get results
	Lattice_cell* get_value (Basic_block* bb, Alias_name name);

private:
	void init_outs (Basic_block* bb);

protected:
	BB_lattices ins;
	BB_lattices clones;
	BB_lattices outs;

	friend class Whole_program;
};

#endif // PHC_WPA_LATTICE
