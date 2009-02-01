#ifndef PHI_MAP
#define PHI_MAP

#include "optimize/Var_map.h"

#include "MIR.h"

class Phi_map : public Var_map<Alias_name>
{
public:
	Phi_map ();
};

#endif // PHI_MAP
