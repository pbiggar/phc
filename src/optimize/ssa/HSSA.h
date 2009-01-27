#ifndef PHC_HSSA
#define PHC_HSSA

#include "../CFG.h"
#include "../Basic_block.h"
#include "../wpa/BCCH_aliasing.h"


class HSSA : virtual public GC_obj
{
	CFG* cfg;

public:
	// Hashed SSA
	HSSA(CFG* cfg);

	void convert_to_hssa_form ();
	void convert_out_of_ssa_form ();
};


#endif // PHC_HSSA
