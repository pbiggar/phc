#include "process_ir/General.h"
#include "Var_set.h"
#include "Var_map.h"

using namespace MIR;

bool
variable_name_ptr_comparison (VARIABLE_NAME* p1, VARIABLE_NAME* p2)
{
	assert (p1);
	assert (p2);

	// This needs to model '<', which must be transitive.
	return (*p1) < (*p2);
}

Var_set::Var_set()
: parent(&variable_name_ptr_comparison)
{
}

Var_set::Var_set(VARIABLE_NAME* var_name)
: parent(&variable_name_ptr_comparison)
{
	insert (var_name);
}

void
Var_set::dump()
{
	CHECK_DEBUG ();
	foreach (VARIABLE_NAME* var_name, *this)
	{
		cdebug << *var_name->value << ", ";
	}
	cdebug << "\n";
}


