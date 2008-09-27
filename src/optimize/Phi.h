#ifndef PHI_MAP
#define PHI_MAP

#include <map>

#include "MIR.h"
#include "Set.h"

class Phi_map : public map
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
