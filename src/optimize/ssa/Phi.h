#ifndef PHI_MAP
#define PHI_MAP

#include "lib/Map.h"

#include "MIR.h"

class Phi_map : public Map
<
	MIR::VARIABLE_NAME*,
	MIR::Rvalue*,
	bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*)
>
{
public:
	Phi_map ();
};

#endif // PHI_MAP
