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
#include "optimize/Abstract_value.h"

using namespace MIR;
using namespace boost;
using namespace std;

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
Aliasing::dump (Context cx, string comment)
{
	CHECK_DEBUG();
	stringstream ss;
	ss << cx << ": " << comment;
	outs[cx]->dump_graphviz (s(ss.str()), cx, wp);
}

void
Aliasing::init (Context outer)
{
	ins[outer] = new Points_to;
	outs[outer] = new Points_to;
}

void
Aliasing::forward_bind (Context caller, Context entry)
{
	Points_to* ptg = ins[caller]->clone ();

	ptg->consistency_check (caller, wp);

	ptg->open_scope (SYM (entry));

	// We need INS to read the current situation, but it shouldnt get modified.
	ins[entry] = ptg;
	outs[entry] = ptg;
}

void
Aliasing::backward_bind (Context caller, Context exit)
{
	Points_to* ptg = outs[exit]->clone ();

	outs[caller] = ptg;

	ptg->close_scope (SYM (exit));

	if (debugging_enabled)
		dump (exit, "After whole program");
}

void
Aliasing::pull_init (Context cx)
{
	ins[cx] = NULL;
}

void
Aliasing::pull_first_pred (Context cx, Context pred)
{
	ins[cx] = outs[pred]->clone ();
}

void
Aliasing::pull_pred (Context cx, Context pred)
{
	ins[cx] = ins[cx]->merge (outs[pred]);
}

void
Aliasing::pull_possible_null (Context cx, Index_node* node)
{
	Points_to* pt = ins[cx];

	// Copied from assign_value
	pt->add_edge (node, ABSVAL (node), POSSIBLE);

	// HACK: there must be existing values for node. They might just be
	// ABSVAL, in which case we're fine, or they might be another value, in
	// which case we need to set the edge to POSSIBLE.
	Storage_node_list* values = pt->get_values (node);
	if (values->size () > 1)
	{
		foreach (Storage_node* st, *values)
		{
			Alias_pair* pair = pt->get_edge (node, st);
			pt->set_pair_cert (pair, POSSIBLE);
		}
	}
}

void
Aliasing::pull_finish (Context cx)
{
	// You cant have no predecessors (and at least 1 must be executable)
	assert (ins[cx]);

	ins[cx]->consistency_check (cx, wp);
	outs[cx] = ins[cx]->clone ();
}


void
Aliasing::aggregate_results (Context cx)
{
	// TODO: pull_results creates the OUT entry, and it is updated through the
	// function. Here, we just want to set CHANGED_FLAG
	outs[cx]->consistency_check (cx, wp);
}

void
Aliasing::kill_value (Context cx, Index_node* lhs)
{
	Points_to* ptg = outs[cx];

	foreach (Storage_node* value, *ptg->get_values (lhs))
	{
		ptg->remove_pair (lhs, value);
		ptg->maybe_remove_node (lhs);
	}
}

// Remove all references edges into or out of INDEX. Also call kill_value.
void
Aliasing::kill_reference (Context cx, Index_node* lhs)
{
	Points_to* ptg = outs[cx];

	foreach (Index_node* other, *ptg->get_references (lhs, PTG_ALL))
	{
		ptg->remove_pair (lhs, other);
		ptg->remove_pair (other, lhs);
	}
}


void
Aliasing::set_storage (Context cx, Storage_node* storage, Types types)
{
	// While it seems like we should be adding a node here, the graph doesnt
	// actually have nodes, only edges, so we cant add anything.
}


void
Aliasing::set_scalar (Context cx, Value_node* storage, Abstract_value* val)
{
	// See set storage
}

void
Aliasing::create_reference (Context cx, Index_node* lhs, Index_node* rhs, certainty cert)
{
	Points_to* ptg = outs[cx];

	ptg->add_index (lhs, DEFINITE);
	ptg->add_index (rhs, DEFINITE);

	// Whole program handles value edges.

	// Transitive closure for reference edges
	certainty certainties[] = {POSSIBLE, DEFINITE};
	foreach (certainty edge_cert, certainties)
	{
		Index_node_list* pts = ptg->get_references (rhs, edge_cert);
		foreach (Index_node* in, *pts)
			ptg->add_bidir_edge (lhs, in,
				combine_certs (cert, edge_cert));
	}

	// Add reference edges
	ptg->add_bidir_edge (lhs, rhs, cert);
}

void
Aliasing::assign_value (Context cx, Index_node* lhs, Storage_node* storage, certainty cert)
{
	outs[cx]->add_index (lhs, DEFINITE);
	outs[cx]->add_edge (lhs, storage, cert);
}

void
Aliasing::merge_contexts ()
{
	Context cx;
	Points_to* ptg;

	// TODO: merge symbol tables - ASAP


	// First create a noncontextual context for each BB
	// (Careful not to overwrite outer_scope)
	Map<Context, Points_to*> new_ins;
	foreach (tie (cx, ptg), ins)
	{
		Context new_cx = cx.get_non_contextual ();

		if (!new_ins.has (new_cx))
			new_ins[new_cx] = ptg->clone ();
		else
			new_ins[new_cx]->merge (ptg);
	}

	ins.clear();
	ins = new_ins;

	Map<Context, Points_to*> new_outs;
	foreach (tie (cx, ptg), outs)
	{
		Context new_cx = cx.get_non_contextual ();

		if (!new_outs.has (new_cx))
			new_outs[new_cx] = ptg->clone ();
		else
			new_outs[new_cx]->merge (ptg);
	}

	outs.clear();
	outs = new_outs;
}

Index_node_list*
Aliasing::get_references (Context cx, Index_node* index,
												certainty cert)
{
	return ins[cx]->get_references (index, cert);
}

Storage_node_list*
Aliasing::get_values (Context cx, Index_node* index)
{
	Points_to* ptg = ins[cx];

	// Check the node exists.	
	if (ptg->get_edge (index->get_storage(), index))
		return ptg->get_values (index);


	// For undefined nodes, we look to the UNKNOWN node. 
	Index_node* unknown = IN (index->storage, UNKNOWN);
	Alias_pair* unknown_edge = ptg->get_edge (unknown->get_storage(), unknown);
	assert (unknown_edge);

	return ptg->get_values (unknown);
}


Index_node_list*
Aliasing::get_indices (Context cx, Storage_node* storage)
{
	return ins[cx]->get_indices (storage);
}

Index_node_list*
Aliasing::get_possible_nulls (List<Context>* cxs)
{
	List<Points_to*>* graphs = new List<Points_to*>;

	foreach (Context cx, *cxs)
		graphs->push_back (outs[cx]);

	return Points_to::get_possible_nulls (graphs);
}


certainty
Aliasing::get_cert (Context cx, Storage_node* st, Index_node* in)
{
	return ins[cx]->get_edge (st, in)->cert;
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
	assert (name != "");
}

Index_path::Index_path (string name)
: name (name)
{
	assert (name != "");
}

Path*
P (string st, string ind)
{
	return new Indexing (new ST_path (st), new Index_path (ind));
}

// In the context of the symtable st, create a Path for NODE
Path*
P (string symtable, Node* in)
{
	ST_path* st = new ST_path (symtable);

	switch (in->classid ())
	{
		case VARIABLE_NAME::ID:
			return P (symtable, *dyc<VARIABLE_NAME> (in)->value);

		case Array_access::ID:
		{
			// (ST -> var) -> index
			Array_access* aa = dyc<Array_access> (in);

			if (isa<VARIABLE_NAME> (aa->index))
			{
				return new Indexing (
						P (symtable, aa->variable_name),
						P (symtable, aa->index));
			}
			else
			{
				return new Indexing (
						P (symtable, aa->variable_name),
						// TODO: not get_value_as_string
						new Index_path (*dyc<Literal> (aa->index)->get_value_as_string ()));
			}
		}

		case Assign_next::ID:
		{
			// (ST -> var) -> *
			Assign_next* an = dyc<Assign_next> (in);

			return new Indexing (
					P (symtable, an->lhs),
					new Index_path ("*"));
		}

		case Assign_array::ID:
		{
			Assign_array* aa = dyc<Assign_array> (in);
			return P (symtable, new Array_access (aa->lhs, aa->index));
		}

		case Unset::ID:
		{
			Unset* unset = dyc<Unset> (in);

			if (unset->target)
				phc_TODO ();

			if (unset->array_indices->size ())
				phc_TODO ();

			// VARIABLE_NAME: st -> var
			// or
			// Variable_variable: st -> (st -> var_name)
			Path* var_indexing = P (symtable, unset->variable_name);

			return var_indexing;
		}

		case INT::ID:
		case STRING::ID:
			return new Index_path (*dyc<Literal> (in)->get_value_as_string ());

		default:
			DEBUG (demangle (in));
			phc_TODO ();
	}
}

void
Indexing::dump (ostream& os)
{
	os << "(";
	lhs->dump(os);
	os << " -> ";
	rhs->dump(os);
	os << ")";
}

void
ST_path::dump (ostream& os)
{
	os << name;
}

void
Index_path::dump (ostream& os)
{
	os << name;
}
