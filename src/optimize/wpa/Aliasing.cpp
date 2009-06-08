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

// TODO: Write an 'is-a-field-of' analysis.

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

Points_to*
merge (Points_to* ptg1, Points_to* ptg2)
{
	assert (ptg2 != NULL);
	if (ptg1 == NULL)
		return ptg2->clone ();
	else
		return ptg1->merge (ptg2);
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
Aliasing::dump_everything (string comment)
{
	foreach (Context cx, *outs.keys ())
		dump (cx, comment);
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

	ptg->open_scope (entry.symtable_node ());

	// We need INS to read the current situation, but it shouldnt get modified.
	// We merge to keep monotonicity in the face of recursion.
	ins[entry] = merge (ins[entry], ptg);
	outs[entry] = ins[entry]->clone ();
}

void
Aliasing::backward_bind (Context caller, Context exit)
{
	Points_to* ptg = outs[exit]->clone ();
	ptg->close_scope (exit.symtable_node ());
	ptg->consistency_check (exit, wp);

	// See comment in WPA_lattice.
	// This needs to merge because the might be different receivers.
	binder[caller] = merge (binder[caller], ptg);

	outs[caller] = binder[caller]->clone ();
	outs[caller]->consistency_check (exit, wp);
}

void
Aliasing::pull_init (Context cx)
{
	// Clear the INs, since we can completely recalculate it from the predecessors.
	ins[cx] = NULL;
}

void
Aliasing::pull_first_pred (Context cx, Context pred)
{
	ins[cx] = merge (ins[cx], outs[pred]);
}

void
Aliasing::pull_pred (Context cx, Context pred)
{
	ins[cx] = merge (ins[cx], outs[pred]);
}

void
Aliasing::pull_possible_null (Context cx, Index_node* index)
{
	ins[cx]->add_points_to (index, SCLVAL (index));
}

void
Aliasing::pull_finish (Context cx)
{
	// You cant have no predecessors (and at least 1 must be executable)
	assert (ins[cx]);

	ins[cx]->consistency_check (cx, wp);

	// No need to merge here, its handled in INS.
	outs[cx] = ins[cx]->clone ();
}


void
Aliasing::aggregate_results (Context cx)
{
	outs[cx]->consistency_check (cx, wp);
}

void
Aliasing::kill_value (Context cx, Index_node* lhs)
{
	Points_to* ptg = outs[cx];

	// This removes LHS from the Points-to graph. Since the value is no longer
	// valid, we need to remove its field edge too.
	foreach (Storage_node* st, *ptg->get_points_to (lhs))
	{
		ptg->remove_points_to (lhs, st);
	}
	ptg->remove_field (lhs);
}

// Remove all references edges into or out of LHS. KILL_VALUE is called separately.
void
Aliasing::kill_reference (Context cx, Index_node* lhs)
{
	Points_to* ptg = outs[cx];

	foreach (Reference* other, *ptg->get_references (lhs))
	{
		ptg->remove_reference (lhs, other->index);
	}
}


void
Aliasing::set_storage (Context cx, Storage_node* storage, Types* types)
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
Aliasing::create_reference (Context cx, Index_node* lhs, Index_node* rhs, Certainty cert)
{
	Points_to* ptg = outs[cx];

	// Whole program handles all edges, so this is very simple
	ptg->add_reference (lhs, rhs, cert);
}

void
Aliasing::assign_value (Context cx, Index_node* lhs, Storage_node* storage)
{
	Points_to* ptg = outs[cx];

	ptg->add_field (lhs);
	ptg->add_points_to (lhs, storage);
}

void
Aliasing::merge_contexts ()
{
	Context cx;
	Points_to* ptg;

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

		new_ins[new_cx]->convert_context_names ();
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

		new_outs[new_cx]->convert_context_names ();
	}

	outs.clear();
	outs = new_outs;
}

Reference_list*
Aliasing::get_references (Context cx, Index_node* index, Certainty cert)
{
	Points_to* ptg = outs[cx];
	return ptg->get_references (index, cert);
}

Storage_node_list*
Aliasing::get_points_to (Context cx, Index_node* index)
{
	Points_to* ptg = outs[cx];
	return ptg->get_points_to (index);
}


Index_node_list*
Aliasing::get_fields (Context cx, Storage_node* storage)
{
	Points_to* ptg = outs[cx];
	return ptg->get_fields (storage);
}

bool
Aliasing::is_abstract (Context cx, Storage_node* st)
{
	return outs[cx]->is_abstract (st);
}

bool
Aliasing::is_abstract_field (Context cx, Index_node* index)
{
	return outs[cx]->is_abstract_field (index);
}

bool
Aliasing::has_storage_node (Context cx, Storage_node* st)
{
	return outs[cx]->has_storage_node (st);
}

bool
Aliasing::has_field (Context cx, Index_node* ind)
{
	return outs[cx]->has_field (ind);
}

Storage_node_list*
Aliasing::get_storage_nodes (Context cx)
{
	return outs[cx]->get_storage_nodes ();
}


Storage_node*
Aliasing::get_owner (Context cx, Index_node* index)
{
	return outs[cx]->get_owner (index);
}


/*
 * Path is used to represent the MIR constructs in an abstract way that
 * models all the MIR constructs. A name is a limited combination of Index_
 * and Storage_nodes which represents a path in the Points_to graph, and as
 * such can represent more than 1 Index_node.
 *
 *
 * For "->" read 'indexed_by"
 *		$a				ST -> "a"
 *		$$a			ST -> (ST -> "a")
 *		$a["f"]		(ST -> "a") -> "f"
 *		$a->f			(ST -> "a") -> "f"
 *		$a->$f		(ST -> "a") -> (ST -> "f")
 *		$a[$f]		(ST -> "a") -> (ST -> "f")
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
						new Index_path (*PHP::get_string_value (dyc<Literal> (aa->index))));
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

			// VARIABLE_NAME: ST -> var
			// or
			// Variable_variable: ST -> (ST -> var_name)
			Path* result = P (symtable, unset->variable_name);

			// Given the current is X, this will be:
			//		(X) -> I0
			//		((X) -> I0) -> I1
			//	etc
			
			foreach (Rvalue* rval, *unset->array_indices)
			{
				Path* index;
				
				if (isa<VARIABLE_NAME> (rval))
					index = P (symtable, dyc<VARIABLE_NAME> (rval));
				else
					index = new Index_path (*PHP::get_string_value (dyc<Literal> (rval)));


				result = new Indexing (result, index);
			}


			return result;
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
