/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Mark variables as definitely initialized, or definitely uninitialized, or maybe initialized.
 *
 *	The simplest thing to start with is, in SSA form, check if a use has a
 *	definition. However, we want to use these annotations for lvalues as well,
 *	which we obviously can't do in SSA form. Additionally, I'm not sure we can
 *	do it simply with the non-SSA def-use chains we have.
 *
 */

#include "MIR.h"

#include "Mark_initialized.h"

using namespace MIR;

void
Mark_initialized::visit_assign_var (Statement_block* sb, Assign_var* in)
{
//	foreach (VARIABLE_NAME* use, *sb->get_uses (SSA_STMT))
//	{
//		if (cfg->duw->get_defs (use, SSA_STMT | SSA_FORMAL)->size () > 0)
//			use->attrs->set_true ("phc.optimize.initialized")
//	}
}
