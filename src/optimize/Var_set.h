#ifndef PHC_VAR_SET
#define PHC_VAR_SET

#include "lib/Set.h"
#include "lib/String.h"
#include "Alias_name.h"

class Var_set 
: public Set<Alias_name>
{
public:
	typedef Set<Alias_name> parent;

public:

	Var_set();

	Var_set* set_union (Var_set* other);
	Var_set* set_intersection (Var_set* other);
	Var_set* set_difference (Var_set* other);

	void dump();
};


#endif // PHC_VAR_SET
