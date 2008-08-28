#ifndef PHC_DEF_USE
#define PHC_DEF_USE

#include "MIR.h"
#include "Set.h"

// We dont want to put this into mir.tea. Its a long way from where its used.
class Def_use
{
public:
	static Set* get_defs (MIR::Statement* statement);
	static Set* get_uses (MIR::Statement* statement);
};

#endif // PHC_DEF_USE
