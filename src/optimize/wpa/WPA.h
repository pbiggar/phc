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



class Annotator : virtual public GC_obj, public MIR::Visitor
{
public:
	Points_to* ptg;
	Basic_block* bb;
	Annotator (){}
};

class WPA : virtual public GC_obj
{
public:
	Whole_program* wp;
	Annotator* pre_annotator;
	Annotator* post_annotator;
	Map<long, bool> changed_flags;

	WPA (Whole_program* wp)
	: wp (wp)
	, pre_annotator (NULL)
	, post_annotator (NULL)
	{
	}

	// Set the value of INDEX_NODE to LIT. CERT indicates whether the assignment
	// can be considered killing.
	virtual void set_value (Basic_block* bb, string lhs, MIR::Literal* rhs, certainty cert) = 0;
	virtual void set_value_from (Basic_block* bb, string lhs, string rhs, certainty cert) = 0;



	bool solution_changed (Basic_block* bb)
	{
		return changed_flags[bb->ID];
	}

	// Pull the results from the predecessor.
	virtual void pull_results (Basic_block* bb) = 0;

	// This sets SOLUTION_CHANGED
	virtual void aggregate_results (Basic_block* bb) = 0;

	// Print debugging information
	virtual void dump (Basic_block* bb) = 0;




	// Annotate BB using information from POINTS-TO
	void pre_annotate (Basic_block* bb, Points_to* ptg)
	{
		if (pre_annotator == NULL)
			return;

		pre_annotator->ptg = ptg;
		pre_annotator->bb = bb;


		if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
			sb->statement->visit (pre_annotator);
		else if (Branch_block* brb = dynamic_cast<Branch_block*> (bb))
			phc_TODO ();

		// TODO: we're gonna have to offer a way to annotate entry and exit blocks.
	}
	void post_annotate (Basic_block* bb, Points_to*)
	{
		if (post_annotator == NULL)
			return;

		phc_TODO ();
	}
};




#endif // PHC_WPA
