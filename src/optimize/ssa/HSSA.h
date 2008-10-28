#ifndef PHC_HSSA
#define PHC_HSSA

#include "../CFG.h"
#include "../Basic_block.h"


class HSSA : virtual public GC_obj
{
	CFG* cfg;

public:

	// Hashed SSA
	HSSA(CFG* cfg);

	void convert_to_hssa_form ();

	// Add mu and chi functions
	void add_mu_and_chi_nodes (Set* aliases);

	// Normal SSA
	void convert_to_ssa_form ();
	void convert_out_of_ssa_form ();
	void rebuild_ssa_form ();
};


#endif // PHC_HSSA
