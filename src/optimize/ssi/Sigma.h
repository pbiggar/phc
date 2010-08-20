#ifndef SIGMA_MAP
#define SIGMA_MAP

#include "lib/Map.h"
#include "optimize/ssa/SSA_name.h"

class Sigma_map : public Map<SSA_name, SSA_name>
{
public:
  Sigma_map ();
};

#endif // SIGMA_MAP
