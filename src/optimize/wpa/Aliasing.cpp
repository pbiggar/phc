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
#include "Whole_program.h"
#include "optimize/Edge.h"
#include "optimize/Abstract_value.h"

using namespace MIR;
using namespace boost;
using namespace std;

Aliasing::Aliasing (Whole_program* wp)
: WPA(wp)
, outs (ptgs[R_OUT])
, ins (ptgs[R_IN])
, working (ptgs[R_WORKING])
, post_bind (ptgs[R_POST_BIND])
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
Aliasing::dump (Context* cx, Result_state state, string comment) const
{
	CHECK_DEBUG();

	if (has_analysis_result (cx, state))
	{
		stringstream ss;
		ss << cx << "(" << result_state_string (state) << "): " << comment;
		ptgs[state][cx]->dump_graphviz (s(ss.str()), cx, state, wp);
	}
}

void
Aliasing::dump_everything (string comment) const
{
	foreach (Context* cx, *outs.keys ())
		dump (cx, R_OUT, comment);
}

void
Aliasing::init (Context* outer)
{
	ins[outer] = new Points_to;
	init_block_results (outer);
}

void
Aliasing::register_class (Context* cx, string class_name)
{
	working[cx]->open_scope (SN (class_name));
}


void
Aliasing::init_block_results (Context* cx)
{
	working[cx] = ins[cx]->clone ();

	post_bind[cx] = NULL;
}

void
Aliasing::forward_bind (Context* caller, Context* entry)
{
	Points_to* ptg = working[caller]->clone ();
	ptg->consistency_check (caller, R_WORKING, wp);
	ptg->open_scope (entry->symtable_node ());

	// We need INS to read the current situation, but it shouldnt get modified.
	// We merge to keep monotonicity in the face of recursion.
	ins[entry] = merge (ins[entry], ptg);
	init_block_results (entry);
}

void
Aliasing::backward_bind (Context* caller, Context* exit)
{
	// TODO: this might segfault, if the exit node is not reachable.
	Points_to* ptg = outs[exit]->clone ();
	ptg->consistency_check (exit, R_OUT, wp);

	// No point clearing if there isn't an infinite call-string.
	if (wp->pm->args_info->call_string_length_arg == 0)
		ptg->close_scope (exit->symtable_node ());

	// See comment in WPA_lattice.
	// This needs to merge because the might be different receivers.
	post_bind [caller] = merge (post_bind [caller], ptg);
}

void
Aliasing::post_invoke_method (Context* caller)
{
	working[caller] = post_bind[caller];
	working[caller]->consistency_check (caller, R_WORKING, wp);

	post_bind[caller] = NULL;
}

void
Aliasing::pull_init (Context* cx)
{
	// Clear the INs, since we can completely recalculate it from the predecessors.
	ins[cx] = NULL;
}

void
Aliasing::pull_first_pred (Context* cx, Context* pred)
{
	ins[cx] = merge (ins[cx], outs[pred]);
}

void
Aliasing::pull_pred (Context* cx, Context* pred)
{
	ins[cx] = merge (ins[cx], outs[pred]);
}

void
Aliasing::pull_possible_null (Context* cx, const Index_node* index)
{
	ins[cx]->add_points_to (index, SCLVAL (index));
}

void
Aliasing::pull_finish (Context* cx)
{
	// You cant have no predecessors (and at least 1 must be executable)
	assert (ins[cx]);

	ins[cx]->consistency_check (cx, R_IN, wp);

	init_block_results (cx);
}

bool
Aliasing::has_analysis_result (Context* cx, Result_state state) const
{
	return ptgs[state].has (cx);
}


void
Aliasing::finish_block (Context* cx)
{
	Points_to* ptg = working[cx]->clone ();
	ptg->consistency_check (cx, R_WORKING, wp);
	ptg->remove_unreachable_nodes ();

	if (outs[cx] == NULL)
		changed_flags[cx] = true;
	else
		changed_flags[cx] = !ptg->equals (outs[cx]);

	// In a few cases, its really difficult to avoid calling finish block twice,
	// so don't clear WORKING.

	outs[cx] = ptg;
}

void
Aliasing::kill_value (Context* cx, const Index_node* lhs, bool also_kill_refs)
{
	Points_to* ptg = working[cx];

	// This removes LHS from the Points-to graph.
	foreach (const Storage_node* st, *ptg->get_points_to (lhs))
	{
		ptg->remove_points_to (lhs, st);
	}

	// Remove all references edges into or out of LHS
	if (also_kill_refs)
	{
		// If there are references, it would be wrong to remove the field.
		// This removes references and points-to as well.
		ptg->remove_field (lhs);
	}
}


void
Aliasing::kill_specific_value (Context* cx, Result_state state, const Index_node* lhs, const Storage_node* rhs)
{
	Points_to* ptg = ptgs[state][cx];

	// Just kill the edge.
	ptg->remove_points_to (lhs, rhs);
}

void
Aliasing::remove_fake_node (Context* cx, const Index_node* fake)
{
	working[cx]->remove_field (fake);
}

void
Aliasing::set_storage (Context* cx, const Storage_node* storage, const Types* types)
{
	// Check if its gone abstract.
	working[cx]->inc_abstract (storage);
}


void
Aliasing::set_scalar (Context* cx, const Value_node* storage, const Abstract_value* val)
{
	// See set storage
}

void
Aliasing::create_reference (Context* cx, const Index_node* lhs, const Index_node* rhs, Certainty cert)
{
	Points_to* ptg = working[cx];

	// Whole program handles all edges, so this is very simple
	ptg->add_reference (lhs, rhs, cert);
}

void
Aliasing::assign_value (Context* cx, const Index_node* lhs, const Storage_node* storage)
{
	Points_to* ptg = working[cx];

	ptg->add_field (lhs);
	ptg->add_points_to (lhs, storage);
}

void
Aliasing::merge_contexts ()
{
	// Make sure innaccessible results aren't available
	working.clear ();
	post_bind.clear ();

	Context* cx;
	Points_to* ptg;

	// Don't like putting this here (would rather have something in Stat_collector),
	// but not sure if it can be avoided:
	set_stat ("num_contexts", ins.size ());

	// First create a noncontextual context for each BB
	// (Careful not to overwrite outer_scope)
	CX_map<Points_to*> new_ins;
	foreach (tie (cx, ptg), ins)
	{
		Context* new_cx = cx->get_non_contextual ();

		if (!new_ins.has (new_cx))
			new_ins[new_cx] = ptg->clone ();
		else
			new_ins[new_cx]->merge (ptg);

		new_ins[new_cx]->convert_context_names ();
	}

	ins.clear();
	ins = new_ins;

	CX_map<Points_to*> new_outs;
	foreach (tie (cx, ptg), outs)
	{
		Context* new_cx = cx->get_non_contextual ();

		if (!new_outs.has (new_cx))
			new_outs[new_cx] = ptg->clone ();
		else
			new_outs[new_cx]->merge (ptg);

		new_outs[new_cx]->convert_context_names ();
	}

	outs.clear();
	outs = new_outs;
}

cReference_list*
Aliasing::get_references (Context* cx, Result_state state, const Index_node* index, Certainty cert) const
{
	return ptgs[state][cx]->get_references (index, cert);
}

cStorage_node_list*
Aliasing::get_points_to (Context* cx, Result_state state, const Index_node* index) const
{
	return ptgs[state][cx]->get_points_to (index);
}


cIndex_node_list*
Aliasing::get_fields (Context* cx, Result_state state, const Storage_node* storage) const
{
	return ptgs[state][cx]->get_fields (storage);
}

bool
Aliasing::is_abstract (Context* cx, Result_state state, const Storage_node* st) const
{
	return ptgs[state][cx]->is_abstract (st);
}

bool
Aliasing::is_abstract_field (Context* cx, Result_state state, const Index_node* index) const
{
	return ptgs[state][cx]->is_abstract_field (index);
}

bool
Aliasing::has_storage_node (Context* cx, Result_state state, const Storage_node* st) const
{
	return ptgs[state][cx]->has_storage_node (st);
}

bool
Aliasing::has_field (Context* cx, Result_state state, const Index_node* index) const
{
	return ptgs[state][cx]->has_field (index);
}

cStorage_node_list*
Aliasing::get_storage_nodes (Context* cx, Result_state state) const
{
	return ptgs[state][cx]->get_storage_nodes ();
}


cIndex_node_list*
Aliasing::get_incoming (Context* cx, Result_state state, const Storage_node* st) const
{
	return ptgs[state][cx]->get_incoming (st);
}


const Storage_node*
Aliasing::get_owner (Context* cx, Result_state state, const Index_node* index) const
{
	return ptgs[state][cx]->get_owner (index);
}

cField_edge_list* 
Aliasing::get_field_edges (Context* cx, Result_state state) const
{
	return ptgs[state][cx]->get_field_edges ();
}

int
Aliasing::get_total_num_field_edges () const
{
	int res = 0;
	Context* cx;
	Points_to* ptg;
	foreach (tie (cx, ptg), ins)
		res += get_field_edges (cx, R_IN)->size ();

	return res;
}

cPoints_to_edge_list* 
Aliasing::get_points_to_edges (Context* cx, Result_state state) const
{
	return ptgs[state][cx]->get_points_to_edges ();
}

int
Aliasing::get_total_num_points_to_edges () const
{
	int res = 0;
	Context* cx;
	Points_to* ptg;
	foreach (tie (cx, ptg), ins)
		res += get_points_to_edges (cx, R_IN)->size ();

	return res;
}

cReference_edge_list*
Aliasing::get_possible_reference_edges (Context* cx, Result_state state) const
{
	return ptgs[state][cx]->get_possible_reference_edges ();
}

cReference_edge_list*
Aliasing::get_definite_reference_edges (Context* cx, Result_state state) const
{
	return ptgs[state][cx]->get_definite_reference_edges ();
}

int
Aliasing::get_num_possible_reference_edges () const
{
	int res = 0;
	Context* cx;
	Points_to* ptg;	
	foreach (tie (cx, ptg), ins)
		res += get_possible_reference_edges (cx, R_IN)->size ();

	return res;
}

int 
Aliasing::get_num_definite_reference_edges () const
{
	int res = 0;
	Context* cx;
	Points_to* ptg;
	foreach (tie (cx, ptg), ins)
		res += get_definite_reference_edges (cx, R_IN)->size ();	

	return res;
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
		/*
		 * Typical paths
		 */


		// Variable
		case VARIABLE_NAME::ID:
			// ST -> var
			return P (symtable, *dyc<VARIABLE_NAME> (in)->value);

		// Var-vars
		case Variable_variable::ID:
		{
			// ST -> (ST -> var)
			Variable_variable* varvar = dyc<Variable_variable> (in);
			return new Indexing (
				new ST_path (symtable),
				P (symtable, varvar->variable_name));
		}

		case Assign_var_var::ID:
		{
			Assign_var_var* avv = dyc<Assign_var_var> (in);
			return P (symtable, new Variable_variable (avv->lhs));
		}

		// Arrays
		case Array_access::ID:
		{
			Array_access* aa = dyc<Array_access> (in);

			if (isa<VARIABLE_NAME> (aa->index))
			{
				// (ST -> var) -> (ST -> index)
				return new Indexing (
						P (symtable, aa->variable_name),
						P (symtable, aa->index));
			}
			else
			{
				// (ST -> var) -> index
				return new Indexing (
						P (symtable, aa->variable_name),
						new Index_path (*PHP::get_string_value (dyc<Literal> (aa->index))));
			}
		}

		case Assign_array::ID:
		{
			Assign_array* aa = dyc<Assign_array> (in);
			return P (symtable, new Array_access (aa->lhs, aa->index));
		}

		// Fields
		case Field_access::ID:
		{
			// This is irritating: LHS can be Target or CLASS_NAME, RHS can be
			// Literal or VARIABLE_NAME.
			// ST-TARGET -> field_name
			// ST-TARGET -> (ST -> field_name)
			// (ST -> target) -> (ST -> field_name)
			// (ST -> target) -> field_name
			Field_access* fa = dyc<Field_access> (in);

			Path *lhs, *rhs;

			if (isa<VARIABLE_NAME> (fa->target))
			{
				// (ST -> target) -> ...
				lhs = P (symtable, dyc<VARIABLE_NAME> (fa->target));
			}
			else
			{
				// ST-TARGET -> ...
				lhs = new ST_path (*dyc<CLASS_NAME> (fa->target)->value->to_lower ());
			}


			if (isa<FIELD_NAME> (fa->field_name))
			{
				// ... -> field_name
				rhs = new Index_path (*dyc<FIELD_NAME> (fa->field_name)->value);
			}
			else
			{
				// ... -> (ST -> field_name)
				rhs = P (symtable, dyc<Variable_field> (fa->field_name)->variable_name);
			}

			return new Indexing (lhs, rhs);
		}

		case Assign_field::ID:
		{
			Assign_field* af = dyc<Assign_field> (in);
			return P (symtable, new Field_access (af->target, af->field_name));
		}



		case Assign_next::ID:
		{
			// (ST -> var) -> *
			Assign_next* an = dyc<Assign_next> (in);

			return new Indexing (
					P (symtable, an->lhs),
					new Index_path (UNKNOWN));
		}




		case Unset::ID:
		{
			Unset* unset = dyc<Unset> (in);

			Path* result = NULL;
			if (unset->target)
			{
				result = P (symtable, unset->target);
			}

			// VARIABLE_NAME: ST -> var
			// or
			// Variable_variable: ST -> (ST -> var_name)
			Path* var_path = P (symtable, unset->variable_name);
			if (result == NULL)
				result = var_path;
			else
				result = new Indexing (result, var_path);

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
			// TODO: does this ever come up?
			return new Index_path (*dyc<Literal> (in)->get_value_as_string ());

		// Pretend its just a variable.
		case Return::ID:
			return P (symtable, new VARIABLE_NAME (RETNAME));

		case HT_ITERATOR::ID:
			return P (symtable, new VARIABLE_NAME (dyc<HT_ITERATOR> (in)->value));	

		case Foreach_get_val::ID:
			return new Indexing (
				P (symtable, dyc<Foreach_get_val> (in)->array),
				new Index_path (UNKNOWN));


		default:
			stringstream ss;
			ss << "Unsupported MIR statement in path creation: " << demangle (in);
			phc_optimization_exception (ss.str());
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
