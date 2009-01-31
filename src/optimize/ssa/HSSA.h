#ifndef PHC_HSSA
#define PHC_HSSA


class CFG;
class Whole_program;

class HSSA : virtual public GC_obj
{
	Whole_program* wp;
	CFG* cfg;

public:
	// Hashed SSA
	HSSA (Whole_program* wp, CFG* cfg);

	void convert_to_hssa_form ();
	void convert_out_of_ssa_form ();
};


#endif // PHC_HSSA
