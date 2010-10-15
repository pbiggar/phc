/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Worklist for Whole_program.
 */


#include "process_ir/General.h"

// TODO: put into lib
#include <queue>

class Edge;
class Basic_block;

#ifndef PHC_WORKLIST
#define PHC_WORKLIST

class Less_post_dominator : virtual public GC_obj
{
public:
	bool operator() (Edge* p1, Edge* p2);
};

class Worklist : virtual public GC_obj
{
public:
	// A Priority_queue which selects nodes which post-dominate other members,
	// after those members.
	std::priority_queue<Edge*, std::deque<Edge*>, Less_post_dominator> queue;

	// Don't add edges to existing BBs, so keep track.
	Set<Basic_block*> bbs;
	Map<Edge*, bool> executable_flags;

public:
	Worklist ();

	Edge* next ();

	void add (Edge* edge);

	bool is_executable (Edge* edge);

	size_t size ();

	bool empty ();

	void clear ();
};

#endif // PHC_WORKLIST
