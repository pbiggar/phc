#ifndef PHC_VAR_SET
#define PHC_VAR_SET

#include "lib/Set.h"
#include "lib/String.h"

class Var_set 
: public Set<
	MIR::VARIABLE_NAME*, 
	bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*),
	phc_allocator<MIR::VARIABLE_NAME*>
>
{
public:
	typedef Set<
		MIR::VARIABLE_NAME*, 
		bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*),
		phc_allocator<MIR::VARIABLE_NAME*>
	> parent;

public:

	Var_set();
	Var_set (MIR::VARIABLE_NAME* elem1);

	Var_set* set_union (Var_set* other)
	{
		return static_cast <Var_set*> (parent::set_union (other));
	}

	Var_set* set_intersection (Var_set* other)
	{
		return static_cast <Var_set*> (parent::set_intersection (other));
	}

	Var_set* set_difference (Var_set* other)
	{
		return static_cast <Var_set*> (parent::set_difference (other));
	}

	void dump();
};


#endif // PHC_VAR_SET
