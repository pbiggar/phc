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

class Whole_program;
class Points_to;

/*
 * Must- or may- information.
 */
#define DECL(T) class T; typedef List<T*> T##_list;

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

	// TODO: Have assign_by_ref/copy call assign_by_value by default.

	// Propagate caller results to the callee.
	virtual void forward_bind (Basic_block* bb, CFG* callee_cfg,
										MIR::Actual_parameter_list* actuals,
										MIR::VARIABLE_NAME* retval){};

	// Propagate callee results back to the caller.
	virtual void backward_bind (Basic_block* bb, CFG* callee_cfg){};

	// NAME's value is killed.
	virtual void kill_value (Basic_block* bb, Alias_name name){};

	// NAME's reference set and value is killed.
	virtual void kill_reference (Basic_block* bb, Alias_name name){};

	// LHS is assigned a literal value from RHS, with the certainty CERT.
	virtual void assign_scalar (Basic_block* bb, Alias_name lhs,
										 MIR::Literal* rhs, certainty cert){};

	// LHS is made to reference RHS, with the certainty CERT. Note this copies
	// the value.
	virtual void assign_by_ref (Basic_block* bb, Alias_name lhs,
										 Alias_name rhs, certainty cert){};

	
	// RHS is copied into LHS, with the certainty CERT.
	virtual void assign_by_copy (Basic_block* bb, Alias_name lhs,
										  Alias_name rhs, certainty cert){};
	
	// There has been a use of USE, with the certainty CERT.
	virtual void record_use (Basic_block* bb, Alias_name use,
									 certainty cert){};

	// Pull the results from BB's predecessor.
	virtual void pull_results (Basic_block* bb){};

	// Combine local results to an OUT solution. This should set
	// CHANGED_FLAGS[bb->ID] if neccessary.
	virtual void aggregate_results (Basic_block* bb){};

	// Print debugging information
	virtual void dump (Basic_block* bb) = 0;

	virtual bool solution_changed (Basic_block* bb)
	{
		return changed_flags[bb->ID];
	}


};




#endif // PHC_WPA
