/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A whole-program analysis. This has access to other analysis results as its
 * run, and must keep its state for the whole program. This simply provides the interface.
 */

#ifndef PHC_WPA
#define PHC_WPA

#include "optimize/Oracle.h"
#include "optimize/CFG_visitor.h"
#include "Whole_program.h"

class Whole_program;
class Points_to;

/*
 * Must- or may- information.
 */
enum _certainty { POSSIBLE = 1, DEFINITE = 2, PTG_ALL = 3 };
typedef enum _certainty certainty;


class WPA : virtual public GC_obj
{
public:
	Whole_program* wp;
	Map<long, bool> changed_flags;

	WPA (Whole_program* wp)
	: wp (wp)
	{
	}


	// TODO
	// - Add forward/backward bind.
	// - Have assign_by_ref/copy call assign_by_value by default.
	// - Move most of aliasing into Whole_progrma.
	// - Move most of Points_to into Aliasing, and make it a WPA.
	virtual void kill_value (Basic_block* bb, Alias_name name){};
	virtual void kill_reference (Basic_block* bb, Alias_name name){};
	virtual void assign_scalar (Basic_block* bb, Alias_name lhs, MIR::Literal* rhs, certainty cert){};
	virtual void assign_by_ref (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert){};
	virtual void assign_by_copy (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert){};
	virtual void record_use (Basic_block* bb, Alias_name use, certainty cert){};



	bool solution_changed (Basic_block* bb)
	{
		return changed_flags[bb->ID];
	}

	// Pull the results from the predecessor.
	virtual void pull_results (Basic_block* bb){};

	// This should set SOLUTION_CHANGED
	virtual void aggregate_results (Basic_block* bb){};

	// Print debugging information
	virtual void dump (Basic_block* bb) = 0;
};




#endif // PHC_WPA
