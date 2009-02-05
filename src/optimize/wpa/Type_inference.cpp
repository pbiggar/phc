/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Type-inference.
 *
 */

#include "Aliasing.h"
#include "Type_inference.h"
#include "Whole_program.h"
#include "Points_to.h"

using namespace MIR;
using namespace std;
using namespace boost;

Type_inference::Type_inference (Whole_program* wp)
: WPA (wp)
{
}

void
Type_inference::dump (Basic_block* bb)
{
	ins.dump (bb, "IN");
	locals.dump (bb, "LOCAL");
	outs.dump (bb, "OUT");
}

void
Type_inference::forward_bind (CFG* caller_cfg, CFG* callee_cfg, MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs)
{
}

void
Type_inference::backward_bind (CFG* caller_cfg, CFG* callee_cfg)
{
}



