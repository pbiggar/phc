/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Worklist for Whole_program.
 */


#include "lib/Set.h"

#include "Worklist.h"

#include "optimize/Edge.h"
#include "optimize/Basic_block.h"

bool
Less_post_dominator::operator() (Edge* p1, Edge* p2)
{
	Basic_block* t1 = p1->get_target ();
	Basic_block* t2 = p2->get_target ();

	// The queue prioritizes maximal elements, so return true for post-domination.
	return !t1->is_reverse_dominated_by (t2);
}


Worklist::Worklist ()
: queue (Less_post_dominator (), std::deque<Edge*> ())
{
}

Edge*
Worklist::next ()
{
	Edge* result = queue.top ();
	queue.pop ();
	bbs.erase (result->get_target ());
	return result;
}

void
Worklist::add (Edge* edge)
{
	executable_flags[edge] = true;

	// Dont add edges whose targets are already present
	if (bbs.has (edge->get_target ()))
		return;

	bbs.insert (edge->get_target ());
	queue.push (edge);
}

bool
Worklist::is_executable (Edge* edge)
{
	return executable_flags[edge];
}

size_t
Worklist::size ()
{
	return queue.size ();
}

bool
Worklist::empty ()
{
	return queue.empty ();
}

void
Worklist::clear ()
{
	while (size ())
		next (); // throw it away


	executable_flags.clear ();
}


