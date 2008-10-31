#ifndef PHC_VAR_MAP
#define PHC_VAR_MAP

#include "lib/Map.h"
#include "lib/String.h"

bool
variable_name_ptr_comparison (MIR::VARIABLE_NAME* p1, MIR::VARIABLE_NAME* p2);

template <typename _Tp>
class Var_map
: public Map<
	MIR::VARIABLE_NAME*, 
	_Tp,
	bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*),
	phc_allocator<std::pair<MIR::VARIABLE_NAME*, _Tp> >
>
, virtual public GC_obj
{
public:
	typedef Map<
		MIR::VARIABLE_NAME*,
		_Tp,
		bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*),
		phc_allocator<std::pair<MIR::VARIABLE_NAME*, _Tp> >
	> parent;

	Var_map() : parent(&variable_name_ptr_comparison) {}
};


#endif // PHC_VAR_MAP
