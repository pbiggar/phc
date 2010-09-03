#ifndef PHC_DOMINANCE
#define PHC_DOMINANCE

#include "lib/Map.h"

#include "optimize/CFG.h"

class Dominance : virtual public GC_obj
{
public:
	// Use vertexes so that the Blocks they refer to can be updated without
	// invalidating the dominance information.

	// Forward dominance frontier
	Map <vertex_t, List<vertex_t> > df;

	// BB -> blocks dominated by BB
	Map <vertex_t, List<vertex_t> > idominated;

	// BB -> BB's dominator
	Map <vertex_t, vertex_t> idominator;

	CFG* cfg;


public:
	Dominance (CFG* cfg);

	void dump ();

	// Terms are defined in Dominace.cpp.
	void calculate_forward_dominance ();
	void calculate_reverse_dominance ();

	// Dominance on the reverse CFG
	Dominance* reverse_dominance;

private:
	friend class Basic_block;
	BB_list* get_bb_dominance_frontier (Basic_block*);
	void add_to_bb_dominance_frontier (Basic_block* bb, Basic_block* frontier);
	bool is_bb_in_dominance_frontier (Basic_block* bb, Basic_block* frontier);

	Basic_block* get_bb_immediate_dominator (Basic_block*);
	BB_list* get_blocks_dominated_by_bb (Basic_block* bb);
	bool is_bb_dominated_by (Basic_block* bb, Basic_block* potential_dom);
	bool is_bb_strictly_dominated_by (Basic_block* bb, Basic_block* potential_dom);
};
#endif // PHC_DOMINANCE
