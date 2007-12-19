#include "debug.h"
#include "Foreach.h"

#include "HIR.h"

/* Lower IN by running all the passes between "hir" and NAME on it. */
List<HIR::Statement*>* lower_to_hir (const char* name, HIR::Statement* in);

/* Parse CODE into a list of HIR statements, using NODE as the source for
 * filenames and line numbers. */
List<HIR::Statement*>* parse_to_hir (String * code, HIR::Node* node);
