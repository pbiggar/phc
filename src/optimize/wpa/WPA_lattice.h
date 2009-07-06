/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Abstraction for passes that simply propagate a lattice. This avoids a great
 * deal of code duplication.
 *
 */

#ifndef PHC_WPA_LATTICE
#define PHC_WPA_LATTICE

#include "WPA.h"
#include "Points_to.h"
#include "optimize/Lattice.h"

template <class Key_type, class Cell_type>
class WPA_lattice : public WPA
{
protected:
	typedef Lattice_map<Key_type, Cell_type> Lattice_type;
	typedef WPA_lattice<Key_type, Cell_type> this_type;

protected:
	Map<Result_state, CX_lattices<Key_type, Cell_type> > lattices;
	CX_lattices<Key_type, Cell_type>& outs;
	CX_lattices<Key_type, Cell_type>& ins;
	CX_lattices<Key_type, Cell_type>& working;
	CX_lattices<Key_type, Cell_type>& post_bind;


public:
	WPA_lattice (Whole_program* wp)
	: WPA (wp)
	, outs (lattices[R_OUT])
	, ins (lattices[R_IN])
	, working (lattices[R_WORKING])
	, post_bind (lattices[R_POST_BIND])
	{
	}

	virtual Key_type context_merge_key (Key_type) const = 0;


	/*
	 * WPA
	 */
	void init (Context* outer)
	{
		// The maps initialize themselves.
	}

	void forward_bind (Context* caller, Context* entry)
	{
		// We dont clear anything, since we want the results to be monotonic in the
		// presence of recursion.

		ins[entry].merge (&working[caller]);

		init_block_results (entry);
	}

	void backward_bind (Context* caller, Context* exit)
	{
		// Overwrite working - its not saved between goes.
		post_bind[caller].merge (&outs[exit]);
	}

	void post_invoke_method (Context* caller)
	{
		// Overwrite working - its not saved between goes.
		working[caller] = post_bind[caller];
		post_bind[caller].clear ();
	}


	/*
	 * Traditionally, we would use 4 sets:
	 *
	 *		IN, OUT, GEN, KILL
	 *	where
	 *		OUT = (IN / KILL) U GEN
	 *
	 *	But its easier to just have IN and OUT. On BB entry, IN is created from
	 *	the previous blocks, and copied to OUT. Then OUT is operated on directly.
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
	 *	would need to count the number of times a value is pushed. If it is
	 *	pushed less than the number of predecessor edges, it should be merged
	 *	with NULL.  But would this work for aliasing?
	 *
	 *	And if we're doing a monotonic analysis, wont running it when NULL has
	 *	not yet been pushed ruin the results?  I guess when pushing the results,
	 *	we must also push for missing variables.
	 *
	 *	Pioli avoided all this by doing flow-insensitive analysis. I'm sure its
	 *	doable, but not a priority.
	 */

	void pull_init (Context* cx)
	{
		ins[cx].clear ();
	}

	void pull_first_pred (Context* cx, Context* pred)
	{
		ins[cx].merge (&outs[pred]);
	}

	void pull_pred (Context* cx, Context* pred)
	{
		ins[cx].merge (&outs[pred]);
	}

	void pull_possible_null (Context* cx, const Index_node* node) = 0;

	void pull_finish (Context* cx)
	{
		init_block_results (cx);
	}

	void finish_block (Context* cx)
	{
		changed_flags[cx] = !working[cx].equals (&outs[cx]);
	
		outs[cx] = working[cx];

		// See comment in Aliasing::finish_block
	}

	bool equals (WPA* wpa)
	{
		this_type* other = dyc<this_type> (wpa);
		return this->ins.equals (&other->ins)
			&& this->outs.equals (&other->outs);
	}

	void dump (Context* cx, Result_state state, string comment) const
	{
		lattices[state].dump (cx, comment);
	}

	void dump_everything (string comment) const
	{
		ins.dump_everything ("IN");
		outs.dump_everything ("OUT");
	}

	void merge_contexts ()
	{
		working.clear ();
		post_bind.clear ();


		Context* cx;
		Lattice_type m;
		Lattice_type& map = m; // grrrr

		// Non-overwriting inserts do not invalidate iterators, which
		// makes this OK.

		CX_lattices<Key_type, Cell_type> new_ins;
		foreach (tie (cx, map), ins)
		{
			// Each map needs its key's names changed.
			Lattice_type newmap;

			Key_type key;
			Cell_type* cell;
			foreach (tie (key, cell), map)
			{
				Key_type new_key = context_merge_key (key);
				newmap[new_key] = newmap[new_key]->meet (cell);
			}

			// The context needs to change names too.
			new_ins[cx->get_non_contextual ()].merge (&newmap);
		}
		ins = new_ins;

		// TODO: remove code duplication
		CX_lattices<Key_type, Cell_type> new_outs;
		foreach (tie (cx, map), outs)
		{
			// Each map needs its key's names changed.
			Lattice_type newmap;

			Key_type key;
			Cell_type* cell;
			foreach (tie (key, cell), map)
			{
				Key_type new_key = context_merge_key (key);
				newmap[new_key] = newmap[new_key]->meet (cell);
			}

			// The context needs to change names too.
			new_outs[cx->get_non_contextual ()].merge (&newmap);
		}
		outs = new_outs;

	}


	bool has_analysis_result (Context* cx, Result_state state) const
	{
		return lattices[state].has (cx);
	}

private:

	void init_block_results (Context* cx)
	{
		working[cx] = ins[cx];

		post_bind[cx].clear ();
	}


};

#endif // PHC_WPA_LATTICE
