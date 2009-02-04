/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Flow-, field-, and context-sensitive alias analysis, in a similar fashion to
 *
 * Michael Hind and Michael Burke and Paul Carini and Jong-Deok Choi,
 * Interprocedural pointer alias analysis
 * ACM Trans. Program. Lang. Syst., 1999
 *
 * We use an infinite call-string approach, and assume that other peoples
 * research can be used to constrain the memory usage at a later date. There is
 * one points-to graph per program point (which corresponds to a basic block
 * for us).
 */

#include "Points_to.h"
#include "Aliasing.h"

using namespace MIR;
using namespace boost;
using namespace std;

Aliasing::Aliasing (Whole_program* wp)
: WPA(wp)
{
}


void
Aliasing::dump (Basic_block* bb)
{
	CHECK_DEBUG();
	outs[bb->ID]->dump_graphviz (s(lexical_cast<string> (bb->ID)));
}


/*
 * Update the Points-to solution, and interface with other analyses.
 *
 *	We have information which we wish to pass to other analyses:
 *		- names whose value must be killed.
 *		- names whose value may be killed.
 *		- names whose value they may take their value from.
 *		- names which are used in the statement.
 */
void
Aliasing::forward_bind (Basic_block* context, CFG* callee_cfg,
										MIR::Actual_parameter_list* actuals,
										MIR::VARIABLE_NAME* retval)
{
	Points_to* ptg;

	if (context == NULL)
		ptg = new Points_to;
	else
		ptg = ins[context->ID]->clone ();

//	ptg->open_scope (CFG_ST(callee_cfg));

	// we dont save INS. Do we need it?
	outs[callee_cfg->get_entry_bb ()->ID] = ptg;
}

void
Aliasing::backward_bind (Basic_block* context, CFG* callee_cfg)
{
	if (context == NULL)
		return;

	Points_to* ptg = outs[callee_cfg->get_exit_bb ()->ID]->clone ();

	ptg->close_scope (CFG_ST(callee_cfg));
	outs[context->ID] = ptg;
}

void
Aliasing::pull_results (Basic_block* bb)
{
	if (bb->get_predecessors ()->size () > 1)
		phc_TODO ();

	ins[bb->ID] = outs[bb->get_predecessors ()->front ()->ID]->clone ();
	outs[bb->ID] = ins[bb->ID]->clone ();
}


void
Aliasing::aggregate_results (Basic_block* bb)
{
	// TODO: pull_results creates the OUT entry, and it is updated through the
	// function. Here, we just want to set CHANGED_FLAG
}

void
Aliasing::kill_value (Basic_block* bb, Alias_name lhs)
{
	outs[bb->ID]->kill_value (lhs.ind());
}

void
Aliasing::kill_reference (Basic_block* bb, Alias_name lhs)
{
	outs[bb->ID]->kill_reference (lhs.ind());
}


void
Aliasing::assign_scalar (Basic_block* bb, Alias_name lhs, MIR::Literal* lit, certainty cert)
{
	if (cert != DEFINITE)
		phc_TODO ();
	
	outs[bb->ID]->assign_scalar (lhs.ind ());
}

void
Aliasing::assign_array (Basic_block* bb, Alias_name lhs, string unique_name, certainty cert)
{
	if (cert != DEFINITE)
		phc_TODO ();

	outs[bb->ID]->add_node (lhs.ind ());
	outs[bb->ID]->add_edge (lhs.ind (), SN (unique_name));
}

void
Aliasing::assign_by_ref (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert)
{
	if (cert != DEFINITE)
		phc_TODO ();

	outs[bb->ID]->assign_by_ref (lhs.ind (), rhs.ind());
}

void
Aliasing::assign_by_copy (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert)
{
	if (cert != DEFINITE)
		phc_TODO ();

	outs[bb->ID]->assign_by_copy (lhs.ind(), rhs.ind());
}


Index_node_list*
Aliasing::get_references (Basic_block* bb, Index_node* index,
												certainty cert)
{
	return ins[bb->ID]->get_references (index, cert);
}

Storage_node_list*
Aliasing::get_points_to (Basic_block* bb, Index_node* index,
												certainty cert)
{
	return ins[bb->ID]->get_points_to (index, cert);
}


/*
 * Path is used to represent the MIR constructs in an abstract way that
 * models all the MIR constructs. A name is a limited combination of Index_
 * and Storage_nodes which represents a path in the Points_to graph, and as
 * such can represent more than 1 Index_node.
 *
 *
 * For "->" read 'indexed_by"
 *		$a[$i]		(ST -> "a") -> (ST -> "i")
 *		$a				ST -> "a"
 *		$$a			ST -> (ST -> "a")
 *		$a["str"]	(ST -> "a") -> "str"
 *		$a->f			(ST -> "a") -> "f"
 *		$a->$f		(ST -> "a") -> (ST -> "f")
 */

Indexing::Indexing (Path* lhs, Path *rhs)
: lhs (lhs)
, rhs (rhs)
{
}

ST_path::ST_path (string name)
: name (name)
{
}

Index_path::Index_path (string name)
: name (name)
{
}


// In the context of the symtable st, create a Path for NODE
Path*
P (string symtable, Node* in)
{
	ST_path* st = new ST_path (symtable);

	switch (in->classid ())
	{
		case VARIABLE_NAME::ID:
			return new Indexing (st,
					new Index_path (*dyc<VARIABLE_NAME> (in)->value));

		case Array_access::ID:
		{
			Array_access* aa = dyc<Array_access> (in);

			return new Indexing (
				new Indexing (st, new Index_path (*aa->variable_name->value)),
				P (symtable, aa->index));
		}

		default:
			DEBUG (demangle (in));
			phc_TODO ();
	}
}



