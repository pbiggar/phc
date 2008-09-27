#include "Phi.h"

using namespace MIR;

Phi_map::Phi_map()
: map<
	MIR::VARIABLE_NAME*,
	MIR::Rvalue*,
	bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*)> (&variable_name_ptr_comparison)
{

}
