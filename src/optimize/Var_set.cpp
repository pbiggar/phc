#include "process_ir/General.h"
#include "Var_set.h"
#include "Var_map.h"

using namespace MIR;

Var_set::Var_set()
{
}

Var_set*
Var_set::set_union (Var_set* other)
{
	return static_cast <Var_set*> (parent::set_union (other));
}

Var_set*
Var_set:: set_intersection (Var_set* other)
{
	return static_cast <Var_set*> (parent::set_intersection (other));
}

Var_set*
Var_set:: set_difference (Var_set* other)
{
	return static_cast <Var_set*> (parent::set_difference (other));
}

void
Var_set::dump()
{
	CHECK_DEBUG ();
	foreach (Alias_name name, *this)
	{
		cdebug << name.str () << ", ";
	}
	cdebug << "\n";
}


