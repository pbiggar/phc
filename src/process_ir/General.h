#include "debug.h"
#include "Foreach.h"

#include "HIR.h"

/* Lower IN by running all the passes between "hir" and NAME on it. */
List<HIR::Statement*>* lower_to_hir (const char* name, HIR::Statement* in);
