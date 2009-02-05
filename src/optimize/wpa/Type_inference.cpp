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
#include "MIR.h"

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
	phc_TODO ();
}

void
Type_inference::backward_bind (CFG* caller_cfg, CFG* callee_cfg)
{
	phc_TODO ();
}

void
Type_inference::assign_unknown (Basic_block* bb, Alias_name lhs, certainty cert)
{
	locals[bb->ID][lhs.str()] = meet (locals[bb->ID][lhs.str()], BOTTOM);
}

void
Type_inference::assign_unknown_typed (Basic_block* bb, Alias_name lhs, string type, certainty cert)
{
	locals[bb->ID][lhs.str()] = meet (locals[bb->ID][lhs.str()], new Type_cell (type));
}
	
void
Type_inference::assign_empty_array (Basic_block* bb, Alias_name lhs, string unique_name, certainty cert)
{
	// Is this really a good way to do this?
	locals[bb->ID][lhs.str()] = meet (locals[bb->ID][lhs.str()], new Type_cell ("array"));
	locals[bb->ID][unique_name] = meet (locals[bb->ID][unique_name], new Type_cell ("array"));
}

void
Type_inference::assign_scalar (Basic_block* bb, Alias_name lhs, MIR::Literal* rhs, certainty cert)
{
	Map<int, string> type_names;
	type_names[MIR::BOOL::ID]		= "bool";
	type_names[MIR::INT::ID]		= "int";
	type_names[MIR::NIL::ID]		= "nil";
	type_names[MIR::REAL::ID]		= "real";
	type_names[MIR::STRING::ID]	= "string";

	locals[bb->ID][lhs.str()] = meet (locals[bb->ID][lhs.str()],
		new Type_cell (type_names[rhs->classid()]));
}

void
Type_inference::assign_value (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert)
{
	phc_TODO ();
}

void
Type_inference::kill_value (Basic_block* bb, Alias_name lhs)
{
	if (locals[bb->ID].has (lhs.str()))
		phc_TODO ();
}

void
Type_inference::pull_results (Basic_block* bb)
{
	// TODO:
	// again, copied from CCP. This should be abstracted.

	// TODO: only pull along executable edges
	// TODO: I could imagine this causing error in the presence of recursion.
	changed_flags[bb->ID] = false;

	// Throw away old values (change is detected in aggregation)
	ins[bb->ID].clear ();
	locals[bb->ID].clear ();

	foreach (Basic_block* pred, *bb->get_predecessors ())
	{
		ins[bb->ID].merge (&outs[pred->ID]);
	}

	if (bb->get_predecessors()->size() > 1)
		phc_TODO (); // check it
}

void
Type_inference::aggregate_results (Basic_block* bb)
{
	phc_TODO ();
}

/*
 * Lattice
 */

Type_cell::Type_cell (string type)
{
	types.insert (type);
}

void
Type_cell::dump ()
{
	foreach (string type, types)
	{
		cdebug << type << ", ";
	}
}

bool
Type_cell::equals (Lattice_cell* other)
{
	phc_TODO ();
}

Lattice_cell*
Type_cell::meet (Lattice_cell* other)
{
	phc_TODO ();
}
