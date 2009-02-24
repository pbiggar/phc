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
class Abstract_value;
class Value_node;
class Index_node;
class Storage_node;

/*
 * Must- or may- information.
 */
enum _certainty { POSSIBLE = 1, DEFINITE = 2, PTG_ALL = 3 };
typedef enum _certainty certainty;

certainty combine_certs (certainty c1, certainty c2);

#define UNKNOWN "*"

#define CFG_ST(CFG) (*(CFG)->method->signature->method_name->value)
#define ST(BB) (CFG_ST ((BB)->cfg))

// Storage node prefix
#define SNP "ST"

// Abstract_value suffix
#define ABV "ABV"

// Return value's name
#define RETNAME "__RETNAME__"

// Main storage node
#define MSN "__MAIN__"


typedef Set<string> Types;

/* Although we dont need to implement all functions from WPA in every analysis,
 * it is useful to check which conform, especially when the interfaces are
 * changing. By setting FIND_*_NON_CONFORMING, each interface function will
 * cause breakage at compile-time/run-time if it is not implemented.
 *
 * We don't want to make all classes conform though - say for Callgraph. So
 * these should be turned off after use
 */
//#define FIND_COMPILE_TIME_NON_CONFORMING

#ifdef FIND_COMPILE_TIME_NON_CONFORMING
#define CT_IMPL =0
#else
#define CT_IMPL {}
#endif


class WPA : virtual public GC_obj
{
public:
	Whole_program* wp;
	string name;
	Map<long, bool> changed_flags;

	WPA (Whole_program* wp)
	: wp (wp)
	{
	}

	/*
	 * Interprocural handling
	 */
	// Propagate caller results to the callee.
	virtual void forward_bind (Basic_block* caller, Entry_block* entry) CT_IMPL;

	// Propagate callee results back to the caller.
	virtual void backward_bind (Basic_block* caller, Exit_block* exit) CT_IMPL;


	/*
	 * Assigning values
	 */

	// This creates a reference between lhs and rhs. Values are propagated
	// separately.
	virtual void create_reference (Basic_block* bb, Index_node* lhs,
											 Index_node* rhs, certainty cert) CT_IMPL;

	// It might seem that copying should naturally be included here, but
	// actually copying is has context-dependant semantics, and instead calls
	// the lower-level functions here.

	// LHS has a value taken from STORAGE. STORAGE must already exist.
	virtual void assign_value (Basic_block* bb, Index_node* lhs,
										Storage_node* storage, certainty cert) CT_IMPL;

	// Create STORAGE, with the gives TYPES.
	virtual void set_storage (Basic_block* bb, Storage_node* storage,
									  Types types) CT_IMPL;

	// Create STORAGE, an abstract value with the given types.
	virtual void set_scalar (Basic_block* bb, Value_node* storage,
									 Abstract_value* val) CT_IMPL;

	/*
	 * Killing values
	 */

	virtual void kill_value (Basic_block* bb, Index_node* lhs) CT_IMPL;

	// Kill name's reference set. Kill_value will be called separately.
	virtual void kill_reference (Basic_block* bb, Index_node* lhs) CT_IMPL;


	/*
	 * Special case for use-def
	 */

	// There has been a use of USE, with the certainty CERT.
	virtual void record_use (Basic_block* bb, Index_node* use,
									 certainty cert) CT_IMPL;


	/*
	 * Propagating results
	 */

	// Pull the results from BB's predecessor. Whole_program abstracts the
	// checking of the is_executable bit, to make things a bit simpler for the
	// analysis. pull_first_pred() is a little bit special, as analyses will
	// probably just copy results, whereas they would merge them for other
	// edges.
	virtual void pull_init (Basic_block* bb) CT_IMPL;
	virtual void pull_first_pred (Basic_block* bb, Basic_block* pred) CT_IMPL;
	virtual void pull_pred (Basic_block* bb, Basic_block* pred) CT_IMPL;
	virtual void pull_finish (Basic_block* bb) CT_IMPL;

	// Combine local results to an OUT solution. This should set
	// CHANGED_FLAGS [bb->ID] if neccessary.
	virtual void aggregate_results (Basic_block* bb) CT_IMPL;

	// Do we need to iterate again?
	virtual bool solution_changed (Basic_block* bb)
	{
		return changed_flags[bb->ID];
	}

	// Return whether the solutions are equal (ie, whether we have reached a
	// fixed-point in our Whole-program iteration).
	virtual bool equals (WPA* other) = 0;


	/*
	 * Debugging information
	 */
	virtual void dump (Basic_block* bb, string comment) = 0;
};




#endif // PHC_WPA
