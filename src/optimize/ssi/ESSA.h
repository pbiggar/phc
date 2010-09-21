#ifndef PHC_ESSA
#define PHC_ESSA

class CFG;
class SSA_def;
class Aliasing;
class Basic_block;
class Whole_program;

#include "optimize/ssa/HSSA.h"
#include "process_ir/General.h"

class ESSA : public HSSA {
public:
  ESSA(Whole_program *wp, CFG *cfg);
  void insert_nodes();

private:
  bool insert_sigma_nodes();
  SSA_def *find_variable(Basic_block *bb, MIR::VARIABLE_NAME *var_name);
  SSA_name_list *collect_vars(Basic_block *bb);
};

#endif // PHC_ESSA
