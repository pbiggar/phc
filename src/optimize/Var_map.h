#ifndef PHC_VAR_MAP
#define PHC_VAR_MAP

#include "lib/Map.h"
#include "lib/String.h"
#include "Alias_name.h"

template <typename _Tp>
class Var_map
: public Map<Alias_name, _Tp>
{
};


#endif // PHC_VAR_MAP
