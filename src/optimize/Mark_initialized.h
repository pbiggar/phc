/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Mark variables as definitely initialized, or definitely uninitialized, or
 * maybe initialized.
 *
 * When we generate code, we wish to know if the variable was are
 * using/defining is already initialized. This allows us avoid a number of
 * checks.
 *
 *	Though SSA form guarantees that a variable only has a single definition,
 *	we do not generate code in SSA form. Rather, we drop SSA indices and operate
 *	on the base names. So we need to propagate whether or not the _base_name_
 *	has been initialized, to each SSA name being defined.
 *
 *	If we were to use SSA form, we would have a problem with definitions of
 *	different versions of the same variable. We do not have a link between x_0
 *	and x_1, so if we store a result in x_0, we have no way to know at x_1 that
 *	it is the correct data to use (nor can we easily search for it).
 *
 *	We instead use a more traditional dataflow technique of simply propagating
 *	the list of initialized variables.
 *
 * Notes:
 *		- assignment to NULL and UNSET are different in this context - NULL
 *		leaves the variable initialized. unset makes the variable uninitialized
 *		(even for indirect assignments).
 *
 *		- aliasing doesnt affect things - indirect assignments can only occur for
 *		initialized variables, and do not affect the results.
 *	
*
 * TODO: this is another place that would benefit from splitting branches with
 * multiple predecessors (though it might be turned off in the case of space
 * constaints).
 *
 * TODO: it may be useful to initialize variables to ensure we know this in all
 * cases.
 */

#ifndef PHC_MARK_INITIALIZED
#define PHC_MARK_INITIALIZED


#include "Sparse_conditional_visitor.h"
#include "Lattice.h"
#include "Address_taken.h"

class Init_cell : public Lattice_cell
{
	void dump ();
	bool equals (Lattice_cell*);
};

// TOP -> INIT   -> BOTTOM
//        UNINIT
// We only need one instance of INIT and UNINIT, since they're all the same.
extern Init_cell* INIT;
extern Init_cell* UNINIT;

class Mark_initialized : public Flow_visitor
{
	Map<Basic_block*, Set> local_defs;
	Map<Basic_block*, Set> local_undefs;
	Map<Basic_block*, Lattice_map*> ins;
	Map<Basic_block*, Lattice_map*> outs;
	Map<Basic_block*, bool> repeat;
	Map<Basic_block*, bool> executed;

	Address_taken* aliasing;

public:
	Mark_initialized ();

	void run (CFG* cfg);
	void init_block (Basic_block*);

	// Local solution
	void visit_entry_block (Entry_block*);
	void visit_statement_block (Statement_block*);

	// Flow
	void transfer_in (Basic_block* bb, BB_list*);
	void transfer_out (Basic_block* bb, BB_list*);
	bool solution_has_changed (Basic_block*);
	
	// Use the analysis
	void post_pass (CFG* cfg);
};

#endif // PHC_MARK_INITIALIZED
