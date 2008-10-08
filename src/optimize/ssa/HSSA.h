#ifndef PHC_HSSA
#define PHC_HSSA

#include "../CFG.h"
#include "../Basic_block.h"


class HSSA
{
	CFG* cfg;

public:

	// Hashed SSA
	HSSA(CFG* cfg);

	void convert_to_hssa_form ();

	// Analyse the CFG, and fill the virtual-variables map
	void create_virtuals ();

	// Normal SSA
	void convert_to_ssa_form ();
	void convert_out_of_ssa_form ();
	void rebuild_ssa_form ();
};


#endif // PHC_HSSA
