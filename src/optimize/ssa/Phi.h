#ifndef PHI_MAP
#define PHI_MAP

#include "lib/Map.h"
#include "SSA_name.h"

class Phi_map : public Map<SSA_name, SSA_name>
{
public:
	Phi_map ();
};

#endif // PHI_MAP
