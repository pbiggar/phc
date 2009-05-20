/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Conditional constant propagation.
 *
 * In theory this is Wegbreits conditional constant propagation, but I'm just
 * going to steal the implementation from SWPA_lattice, so its a step forward, and then
 * one back, which will probably land in about the same place.
 *
 */

#include "WPA_lattice.h"
#include "Points_to.h"

using namespace std;
using namespace boost;
using namespace MIR;

WPA_lattice::WPA_lattice (Whole_program* wp)
: WPA (wp)
{
}

bool
WPA_lattice::equals (WPA* wpa)
{
	WPA_lattice* other = dyc<WPA_lattice> (wpa);
	return this->ins.equals (&other->ins)
		&& this->outs.equals (&other->outs);
}

void
WPA_lattice::dump(Context cx, string comment)
{
	ins.dump (cx, "IN");
	outs.dump (cx, "OUT");
}

void
WPA_lattice::dump_everything (string comment)
{
	ins.dump_everything ("IN");
	outs.dump_everything ("OUT");
}


void
WPA_lattice::init (Context outer)
{
}

/*
 * Traditionally, we would use 4 sets:
 *
 *		IN, OUT, GEN, KILL
 *	where
 *		OUT = (IN / KILL) U GEN
 *
 *	But its easier to just have IN and OUT. On BB entry, IN is created from the
 *	previous blocks, and copied to OUT. Then OUT is operated on directly.
 *
 *	To make this monotonic, we need to record the old OUT, and compare it
 *	during aggregate_results (where we would traditionally perform the
 *	equation).
 *
 *
 * Pioli's implementation differs slightly:
 *
 *	So, we need to mark when a solution changes. Pioli's solution was to push
 *	results into the next section, instead of pulling. This meant saving half
 *	the result sets, and setting a block to be executed when a merge changed
 *	the solution. But this might break with branches:
 *
 *			if (...)
 *		1:		$x = 5;
 *			else
 *		2:		;
 *		3:
 *
 *	At 3: we expect $x to have the value BOTTOM, not 5, as it is uninit (and
 *	therefore NULL) at 2:.
 *
 *	This is possible using pull. To make it possible using a push model, we
 *	would need to count the number of times a value is pushed. If it is pushed
 *	less than the number of predecessor edges, it should be merged with NULL.
 *	But would this work for aliasing?
 *
 *	And if we're doing a monotonic analysis, wont running it when NULL has not
 *	yet been pushed ruin the results?  I guess when pushing the results, we
 *	must also push for missing variables.
 *
 *	Pioli avoided all this by doing flow-insensitive analysis. I'm sure its
 *	doable, but not a priority.
 */

void
WPA_lattice::kill_value (Context cx, Index_node* lhs)
{
	outs[cx][lhs->name().str()] = TOP;
	outs[cx][ABSVAL (lhs)->name().str()] = TOP;
}

void
WPA_lattice::assign_value (Context cx, Index_node* lhs, Storage_node* storage, Certainty cert)
{
	Lattice_map& lat = outs[cx];
	string name = lhs->name().str();
	lat[name] = meet (lat[name], lat[storage->name().str()]);
}

void
WPA_lattice::pull_init (Context cx)
{
	// TODO: This will fail if our context does not handle recursion well
	changed_flags[cx] = false;
	ins[cx].clear ();
}

void
WPA_lattice::pull_first_pred (Context cx, Context pred)
{
	ins[cx].merge (&outs[pred]);
}

void
WPA_lattice::pull_pred (Context cx, Context pred)
{
	ins[cx].merge (&outs[pred]);
}


void
WPA_lattice::pull_finish (Context cx)
{
	init_outs (cx);
}

void
WPA_lattice::aggregate_results (Context cx)
{
	// Set solution_changed
	changed_flags[cx] = !outs[cx].equals (&clones[cx]);

	// We probably dont need a full set of clones.
	clones[cx].clear();
	clones[cx].merge (&outs[cx]);
}


void
WPA_lattice::forward_bind (Context caller, Context entry)
{
	// TODO: do we really want to clear? does that make it non-monotonic?

	ins[entry].merge(&ins[caller]);

	init_outs (entry);
}

void
WPA_lattice::backward_bind (Context caller, Context exit)
{
	// pull_results inits outs, so we need to clear it, or we'll be merging
	// with old results.
	outs[caller].clear ();
	outs[caller].merge(&outs[exit]);
}

void
WPA_lattice::merge_contexts ()
{
	Context cx;
	Lattice_map m;
	Lattice_map& map = m; // grrrr

	// Non-overwriting inserts do not invalidate iterators, which
	// makes this OK.

	CX_lattices new_ins;
	foreach (tie (cx, map), ins)
	{
		// Each map needs its key's names changed.
		Lattice_map newmap;

		string str;
		Lattice_cell* cell;
		foreach (tie (str, cell), map)
		{
			str = Context::convert_context_name (str);

			// There may be multiple cells for the same name.
			newmap[str] = meet (newmap[str], cell);
		}

		// The context needs to change names too.
		new_ins[cx.get_non_contextual ()].merge (&newmap);
	}
	ins = new_ins;

	// TODO: remove code duplication
	CX_lattices new_outs;
	foreach (tie (cx, map), outs)
	{
		// Each map needs its key's names changed.
		Lattice_map newmap;

		string str;
		Lattice_cell* cell;
		foreach (tie (str, cell), map)
		{
			str = Context::convert_context_name (str);

			// There may be multiple cells for the same name.
			newmap[str] = meet (newmap[str], cell);
		}

		// The context needs to change names too.
		new_outs[cx.get_non_contextual ()].merge (&newmap);
	}
	outs = new_outs;
}


void
WPA_lattice::init_outs (Context cx)
{
	outs[cx].merge (&ins[cx]);
}

Lattice_cell*
WPA_lattice::get_value (Context cx, Alias_name name)
{
	return ins[cx][name.str()];
}


