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
#include "optimize/Edge.h"

using namespace MIR;
using namespace boost;
using namespace std;

Storage_node* SCALAR()
{
	return new Storage_node ("SCALAR");
}

Aliasing::Aliasing (Whole_program* wp)
: WPA(wp)
{
}


bool
Aliasing::equals (WPA* wpa)
{
	Aliasing* other = dyc<Aliasing> (wpa);
	return ins.equals (&other->ins)
		&& outs.equals (&other->outs);
}

void
Aliasing::dump (Basic_block* bb, string comment)
{
	CHECK_DEBUG();
	stringstream ss;
	ss << bb->ID << ":" << comment;
	outs[bb->ID]->dump_graphviz (s(ss.str()));
}


void
Aliasing::forward_bind (Basic_block* caller, Entry_block* entry)
{
	Points_to* ptg;

	if (caller == NULL)
		ptg = new Points_to;
	else
		ptg = ins[caller->ID]->clone ();

	// We need INS to read the current situation, but it shouldnt get modified.
	ins[entry->ID] = ptg;
	outs[entry->ID] = ptg;
}

void
Aliasing::backward_bind (Basic_block* caller, Basic_block* exit)
{
	if (caller == NULL)
		return;

	Points_to* ptg = outs[exit->ID]->clone ();

	ptg->close_scope (ST(exit));
	outs[caller->ID] = ptg;
}

void
Aliasing::pull_init (Basic_block* bb)
{
	ins[bb->ID] = NULL;
}

void
Aliasing::pull_first_pred (Basic_block* bb, Basic_block* pred)
{
	ins[bb->ID] = outs[pred->ID]->clone ();
}

void
Aliasing::pull_pred (Basic_block* bb, Basic_block* pred)
{
	ins[bb->ID] = ins[bb->ID]->merge (outs[pred->ID]);
}

void
Aliasing::pull_finish (Basic_block* bb)
{
	// You cant have no predecessors (and at least 1 must be executable)
	assert (ins[bb->ID]);

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
	Points_to* ptg = outs[bb->ID];
	ptg->add_node (lhs.ind(), DEFINITE);

	foreach (Storage_node* value, *ptg->get_values (lhs.ind(), PTG_ALL))
	{
		ptg->remove_pair (lhs.ind(), value);
	}
}

// Remove all references edges into or out of INDEX. Also call kill_value.
void
Aliasing::kill_by_ref (Basic_block* bb, Alias_name lhs)
{
	Points_to* ptg = outs[bb->ID];
	ptg->add_node (lhs.ind(), DEFINITE);

	foreach (Index_node* other, *ptg->get_references (lhs.ind(), PTG_ALL))
	{
		ptg->remove_pair (lhs.ind(), other);
		ptg->remove_pair (other, lhs.ind());
	}
}


void
Aliasing::assign_scalar (Basic_block* bb, Alias_name lhs, MIR::Literal* lit, certainty cert)
{
	// This kills any objects or arrays currently pointed-to. However, that's
	// done in kill_value.
	outs[bb->ID]->add_node (lhs.ind (), cert);
	outs[bb->ID]->add_edge (lhs.ind (), SCALAR(), cert);
}

void
Aliasing::assign_empty_array (Basic_block* bb, Alias_name lhs, string unique_name, certainty cert)
{
	outs[bb->ID]->add_node (lhs.ind (), cert);
	outs[bb->ID]->add_edge (lhs.ind (), SN (unique_name), cert);
}

void
Aliasing::assign_unknown (Basic_block* bb, Alias_name lhs, certainty cert)
{
	outs[bb->ID]->add_node (lhs.ind (), cert);
	outs[bb->ID]->add_edge (lhs.ind (), SCALAR(), cert);
}

void
Aliasing::assign_by_ref (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert)
{
	Points_to* ptg = outs[bb->ID];

	ptg->add_node (lhs.ind(), cert);
	ptg->add_node (rhs.ind(), cert);

	// Transitive closure for points-to edges
	add_all_points_to_edges (bb, lhs, rhs, cert);

	// Transitive closure for reference edges
	certainty certainties[] = {POSSIBLE, DEFINITE};
	foreach (certainty edge_cert, certainties)
	{
		Index_node_list* pts = ptg->get_references (rhs.ind (), edge_cert);
		foreach (Index_node* in, *pts)
			ptg->add_bidir_edge (lhs.ind(), in,
				combine_certs (cert, edge_cert));
	}


	ptg->add_bidir_edge (lhs.ind(), rhs.ind(), cert);
}

void
Aliasing::assign_by_copy (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert)
{
	outs[bb->ID]->add_node (lhs.ind(), cert);
	add_all_points_to_edges (bb, lhs, rhs, cert);
}

void
Aliasing::add_all_points_to_edges (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert)
{
	certainty certainties[] = {POSSIBLE, DEFINITE};
	foreach (certainty edge_cert, certainties)
	{
		Storage_node_list* pts = ins[bb->ID]->get_values (rhs.ind (), edge_cert);
		foreach (Storage_node* st, *pts)
			outs[bb->ID]->add_edge (lhs.ind (), st, combine_certs (edge_cert, cert));
	}
}



Index_node_list*
Aliasing::get_references (Basic_block* bb, Index_node* index,
												certainty cert)
{
	return ins[bb->ID]->get_references (index, cert);
}

Storage_node_list*
Aliasing::get_values (Basic_block* bb, Index_node* index,
												certainty cert)
{
	return ins[bb->ID]->get_values (index, cert);
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

		case Assign_array::ID:
		{
			Assign_array* aa = dyc<Assign_array> (in);

			return new Indexing (
				new Indexing (st, new Index_path (*aa->lhs->value)),
				P (symtable, aa->index));
		}

		default:
			DEBUG (demangle (in));
			phc_TODO ();
	}
}



