#ifndef PHC_SSI_OPS
#define PHC_SSI_OPS

#include <boost/functional/hash.hpp>

#include "MIR.h"
#include "optimize/ssa/SSA_ops.h"
#include "optimize/Basic_block.h"

DECL (SSI_op);

class SSI_op : public SSA_op {
  SSI_op (Basic_block* bb, SSA_name* name, int type_flag);
};

#endif // PHC_SSI_OPS
