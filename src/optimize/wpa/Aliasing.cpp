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
Aliasing::dump (Basic_block* bb, string comment)
{
	CHECK_DEBUG();
	stringstream ss;
	ss << bb->ID << ":" << comment;
	outs[bb->ID]->dump_graphviz (s(ss.str()), bb, wp);
}


void
Aliasing::forward_bind (Basic_block* caller, Entry_block* entry)
{
	Points_to* ptg;

	if (caller == NULL)
		ptg = new Points_to;
	else
		ptg = ins[caller->ID]->clone ();

	ptg->consistency_check ();
	// We need INS to read the current situation, but it shouldnt get modified.
	ins[entry->ID] = ptg;
	outs[entry->ID] = ptg;
}

void
Aliasing::backward_bind (Basic_block* caller, Exit_block* exit)
{
	Points_to* ptg = outs[exit->ID]->clone ();

	ptg->close_scope (ST(exit));


	if (caller != NULL)
		outs[caller->ID] = ptg;
	else
	{
		if (debugging_enabled)
			ptg->dump_graphviz (s("After whole program"), exit, wp);
	}
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
Aliasing::pull_possible_null (Basic_block* bb, Index_node* node)
{
	// Copied from assign_value
	ins[bb->ID]->add_edge (node, ABSVAL (node), POSSIBLE);
}

void
Aliasing::pull_finish (Basic_block* bb)
{
	// You cant have no predecessors (and at least 1 must be executable)
	assert (ins[bb->ID]);

	ins[bb->ID]->consistency_check ();
	outs[bb->ID] = ins[bb->ID]->clone ();
}


void
Aliasing::aggregate_results (Basic_block* bb)
{
	// TODO: pull_results creates the OUT entry, and it is updated through the
	// function. Here, we just want to set CHANGED_FLAG
	outs[bb->ID]->consistency_check ();
}

void
Aliasing::kill_value (Basic_block* bb, Index_node* lhs)
{
	Points_to* ptg = outs[bb->ID];

	foreach (Storage_node* value, *ptg->get_values (lhs))
	{
		ptg->remove_pair (lhs, value);
	}
}

// Remove all references edges into or out of INDEX. Also call kill_value.
void
Aliasing::kill_reference (Basic_block* bb, Index_node* lhs)
{
	Points_to* ptg = outs[bb->ID];

	foreach (Index_node* other, *ptg->get_references (lhs, PTG_ALL))
	{
		ptg->remove_pair (lhs, other);
		ptg->remove_pair (other, lhs);
	}
}


void
Aliasing::set_storage (Basic_block* bb, Storage_node* storage, Types types)
{
	// While it seems like we should be adding a node here, the graph doesnt
	// actually have nodes, only edges, so we cant add anything.
}


void
Aliasing::set_scalar (Basic_block* bb, Value_node* storage, Abstract_value* val)
{
	// See set storage
}

void
Aliasing::create_reference (Basic_block* bb, Index_node* lhs, Index_node* rhs, certainty cert)
{
	phc_TODO ();
	Points_to* ptg = outs[bb->ID];

	ptg->add_index (lhs, DEFINITE);
	ptg->add_index (rhs, DEFINITE);

	// Transitive closure for points-to edges
	add_all_points_to_edges (bb, lhs, rhs, cert);

	// Transitive closure for reference edges
	certainty certainties[] = {POSSIBLE, DEFINITE};
	foreach (certainty edge_cert, certainties)
	{
		Index_node_list* pts = ptg->get_references (rhs, edge_cert);
		foreach (Index_node* in, *pts)
			ptg->add_bidir_edge (lhs, in,
				combine_certs (cert, edge_cert));
	}


	ptg->add_bidir_edge (lhs, rhs, cert);
}

void
Aliasing::assign_value (Basic_block* bb, Index_node* lhs, Storage_node* storage, certainty cert)
{
	outs[bb->ID]->add_index (lhs, DEFINITE);
	outs[bb->ID]->add_edge (lhs, storage, cert);
}

void
Aliasing::add_all_points_to_edges (Basic_block* bb, Index_node* lhs, Index_node* rhs, certainty cert)
{
	// Do not copy the abstract value!!!
	phc_TODO ();

	certainty certainties[] = {POSSIBLE, DEFINITE};
	foreach (certainty edge_cert, certainties)
	{
		Storage_node_list* pts = ins[bb->ID]->get_values (rhs);
		foreach (Storage_node* st, *pts)
			outs[bb->ID]->add_edge (lhs, st, combine_certs (edge_cert, cert));
	}
}



Index_node_list*
Aliasing::get_references (Basic_block* bb, Index_node* index,
												certainty cert)
{
	return ins[bb->ID]->get_references (index, cert);
}

Storage_node_list*
Aliasing::get_values (Basic_block* bb, Index_node* index)
{
	Points_to* ptg = ins[bb->ID];
	Storage_node_list* result = ptg->get_values (index);

	// For undefined nodes, we look to the UNKNOWN node. 
	Alias_pair* edge = ptg->get_edge (index->get_storage(), index);
	assert ((edge == NULL) xor !result->empty ());
	if (edge == NULL)
	{
		return get_values (bb, IN (index->storage, UNKNOWN));
	}

	return result;
}


Index_node_list*
Aliasing::get_indices (Basic_block* bb, Storage_node* storage)
{
	return ins[bb->ID]->get_indices (storage);
}

Index_node_list*
Aliasing::get_possible_nulls (BB_list* bbs)
{
	List<Points_to*>* graphs = new List<Points_to*>;

	foreach (Basic_block* bb, *bbs)
		graphs->push_back (outs[bb->ID]);

	return Points_to::get_possible_nulls (graphs);
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
