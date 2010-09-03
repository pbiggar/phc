#ifndef PHC_SSI
#define PHC_SSI

class CFG;
class Whole_program;

#include "optimize/ssa/HSSA.h"

class SSI : public HSSA {
public:
  SSI(Whole_program *wp, CFG *cfg);
  void insert_nodes();

private:
  bool insert_sigma_nodes();
};

#endif // PHC_SSI
