/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Very simple inlining. Probably just removing calls to empty functions.
  */

#include "Inlining.h"
#include "Oracle.h"
#include "process_ir/General.h"

using namespace MIR;

void
Inlining::transform_eval_expr (Statement_block* bb, Eval_expr* in, BB_list* out)
{
	// remove it later
	out->push_back (bb);

	Method_invocation* mi = dynamic_cast<Method_invocation*> (in->expr);
	if (  mi == NULL
		|| mi->target
		|| isa<Variable_method> (mi->method_name))
		return;

	// Simplest thing possible: remove calls to empty functions
	User_method_info* info = Oracle::get_user_method_info (
		dyc<METHOD_NAME> (mi->method_name)->value);

	if (info == NULL)
		return;

	// TODO: technically, we have ignored the problem that a function call can
	// initialize a parameter which is called by ref. We've also ignored that
	// elsewhere, which really needs to be fixed.
	// TODO: shoudln't this be killed by DCE
	// TODO: use a User_method_info property

	// Empty CFGs have 2 statements only
	if (info->get_cfg ()->get_all_bbs()->size() != 2)
		return;

	DEBUG ("BB " << bb->ID << ": removing call to " << *info->name);

	// Remove it
	out->clear ();
}
