/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A whole-program analysis. This has access to other analysis results as its
 * run, and must keep its state for the whole program. This simply provides the interface.
 */

#ifndef PHC_WPA
#define PHC_WPA

#include <ostream>

#include "optimize/Oracle.h"
#include "optimize/CFG_visitor.h"
#include "optimize/Lattice.h"

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

#define SYM(CX) ((CX).caller().name())

// Storage node prefix
#define SNP "ST"

// Abstract_value suffix
#define ABV "ABV"

// Return value's name
#define RETNAME "__RETNAME__"

// Basic_block ID. Takes into account the calling context, and the BB's ID number.
class Context : virtual public GC_obj
{
public:
	friend std::ostream &operator<<(std::ostream&, const Context&);

	List<Basic_block*> BBs;

	bool use_caller;

	static Context non_contextual (Basic_block* bb)
	{
		Context result;
		result.BBs.push_back (bb);
		result.use_caller = false;
		return result;
	}

	static Context contextual (Context caller, Basic_block* bb)
	{
		Context result;
		result.BBs = caller.BBs;
		result.use_caller = true;
		result.BBs.push_back (bb);
		return result;
	}

	// Use PEER's caller
	static Context as_peer (Context peer, Basic_block* bb)
	{
		Context result;
		result.BBs = peer.caller ().BBs;
		result.BBs.push_back (bb);
		result.use_caller = true;
		return result;
	}

	// Represents the first caller
	static Context outer_scope ()
	{
		Context result;
		result.BBs.push_back (NULL);
		result.use_caller = true;
		return result;
	}

	Context caller ()
	{
		assert (this->use_caller);

		Context result = *this;
		result.BBs.pop_back ();
		return result;
	}

	Basic_block* get_bb ()
	{
		return BBs.back();
	}

	bool operator< (const Context &other) const
	{
		// Not using context means any BB with the same ID matches.
		if (!this->use_caller)
			return this->BBs.back()->ID < other.BBs.back()->ID;

		// TODO: what about other.use_caller

		return this->name() < other.name();
	}

	bool operator== (const Context &other) const
	{
		return !(*this < other) && !(other < *this);
	}

	string name () const
	{
		stringstream ss;
		foreach (Basic_block* bb, BBs)
		{
			ss << "/" << bb->ID;
		}
		return ss.str ();
	}
};

std::ostream &operator<< (std::ostream &out, const Context &num);



string BB_array_name (Context cx);
string BB_object_name (Context cx);

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
	Map<Context, bool> changed_flags;

	WPA (Whole_program* wp)
	: wp (wp)
	{
	}

	/*
	 * Interprocural handling
	 */
	// Propagate caller results to the callee.
	virtual void forward_bind (Context caller, Context entry) CT_IMPL;

	// Propagate callee results back to the caller.
	virtual void backward_bind (Context caller, Context exit) CT_IMPL;


	/*
	 * Assigning values
	 */

	// This creates a reference between lhs and rhs. Values are propagated
	// separately.
	virtual void create_reference (Context cx, Index_node* lhs,
											 Index_node* rhs, certainty cert) CT_IMPL;

	// It might seem that copying should naturally be included here, but
	// actually copying is has context-dependant semantics, and instead calls
	// the lower-level functions here.

	// LHS has a value taken from STORAGE. STORAGE must already exist.
	virtual void assign_value (Context cx, Index_node* lhs,
										Storage_node* storage, certainty cert) CT_IMPL;

	// Create STORAGE, with the gives TYPES.
	virtual void set_storage (Context cx, Storage_node* storage,
									  Types types) CT_IMPL;

	// Create STORAGE, an abstract value with the given types.
	virtual void set_scalar (Context cx, Value_node* storage,
									 Abstract_value* val) CT_IMPL;

	/*
	 * Killing values
	 */

	virtual void kill_value (Context cx, Index_node* lhs) CT_IMPL;

	// Kill name's reference set. Kill_value will be called separately.
	virtual void kill_reference (Context cx, Index_node* lhs) CT_IMPL;


	/*
	 * Special case for use-def
	 */

	// There has been a use of USE, with the certainty CERT.
	virtual void record_use (Context cx, Index_node* use,
									 certainty cert) CT_IMPL;


	/*
	 * Propagating results
	 */

	// Pull the results from BB's predecessor. Whole_program abstracts the
	// checking of the is_executable bit, to make things a bit simpler for the
	// analysis. pull_first_pred() is a little bit special, as analyses will
	// probably just copy results, whereas they would merge them for other
	// edges.
	virtual void pull_init (Context cx) CT_IMPL;
	virtual void pull_first_pred (Context cx, Context pred) CT_IMPL;
	virtual void pull_pred (Context cx, Context pred) CT_IMPL;

	// Index_nodes may be NULL on some paths. This is hard to do at a
	// fine-grained level, but much easier at a higher level. pulls typically
	// work on INs, so this needs to be done now, rather than trying to do it
	// with an out.
	virtual void pull_possible_null (Context cx, Index_node* node) CT_IMPL;

	virtual void pull_finish (Context cx) CT_IMPL;

	// Combine local results to an OUT solution. This should set
	// CHANGED_FLAGS [bb->ID] if neccessary.
	virtual void aggregate_results (Context cx) CT_IMPL;

	// Do we need to iterate again?
	virtual bool solution_changed (Context cx)
	{
		return changed_flags[cx];
	}

	// Return whether the solutions are equal (ie, whether we have reached a
	// fixed-point in our Whole-program iteration).
	virtual bool equals (WPA* other) = 0;


	/*
	 * Debugging information
	 */
	virtual void dump (Context cx, string comment) = 0;
};


class CX_lattices : public Map<Context, Lattice_map>
{
public:
	void dump (Context cx, string name);
};


#endif // PHC_WPA
