#include "Phi.h"
#include "optimize/Set.h"

using namespace MIR;

Phi_map::Phi_map()
: Map<
	MIR::VARIABLE_NAME*,
	MIR::Rvalue*,
	bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*)> (&variable_name_ptr_comparison)
{

}
