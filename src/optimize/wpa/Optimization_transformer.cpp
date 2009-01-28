/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Use the results of the analyses to transform the MIR. Do not handle dead
 * code.
 * */


#include "Optimization_transformer.h"
#include "optimize/SCCP.h"
#include "Whole_program.h"
#include "CCP.h"


using namespace MIR;
using namespace boost;
using namespace std;

/*
 * Apply the optimization results.
 */
Optimization_transformer::Optimization_transformer (Aliasing* aliasing)
: aliasing (aliasing)
{
}

void
Optimization_transformer::run (CFG* cfg)
{
}


void
Optimization_transformer::visit_assign_array (Statement_block* bb, MIR::Assign_array* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_assign_field (Statement_block* bb, MIR::Assign_field * in)
{
	phc_TODO ();
}


Rvalue*
Optimization_transformer::get_literal (Basic_block* bb, Rvalue* in)
{
	if (isa<Literal> (in))
		return in;


	string ns = NAME (bb);
	VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (in);

	Index_node* rhs = VN (ns, var_name);
	CCP* ccp = aliasing->wp->ccp;
	Lattice_cell* result = ccp->ins[bb->ID][rhs->get_unique_name ()];

	if (result == BOTTOM)
		return in;

	if (result == TOP)
		return new NIL;

	return dyc<Literal_cell> (result)->value;
}

void
Optimization_transformer::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	string ns = NAME (bb);
	Index_node* lhs = IN (ns, *in->lhs->value);

	// The assignment is by reference. We will be able to remove this later, via DCE.
	if (in->is_ref)
		return;

	// Ignore
	if (isa<Literal> (in->rhs))
		return;

	// TODO: check that there are no implicit operations on the rhs

	if (isa<VARIABLE_NAME> (in->rhs))
		in->rhs = get_literal (bb, dyc<VARIABLE_NAME> (in->rhs));
}

void
Optimization_transformer::visit_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	visit_expr (bb, in->expr);
}

void
Optimization_transformer::visit_foreach_end (Statement_block* bb, MIR::Foreach_end* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_foreach_next (Statement_block* bb, MIR::Foreach_next* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_global (Statement_block* bb, MIR::Global* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_pre_op (Statement_block* bb, MIR::Pre_op* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_assign_next (Statement_block* bb, MIR::Assign_next* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_return (Statement_block* bb, MIR::Return* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_ssa_pre_op (Statement_block* bb, MIR::SSA_pre_op* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_static_declaration (Statement_block* bb, MIR::Static_declaration* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_throw (Statement_block* bb, MIR::Throw* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_try (Statement_block* bb, MIR::Try* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_unset (Statement_block* bb, MIR::Unset* in)
{
	phc_TODO ();
}


void
Optimization_transformer::visit_array_access (Statement_block* bb, MIR::Array_access* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_bin_op (Statement_block* bb, MIR::Bin_op* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_bool (Statement_block* bb, MIR::BOOL* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_cast (Statement_block* bb, MIR::Cast* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_constant (Statement_block* bb, MIR::Constant* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_field_access (Statement_block* bb, MIR::Field_access* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_instanceof (Statement_block* bb, MIR::Instanceof* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_int (Statement_block* bb, MIR::INT* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_isset (Statement_block* bb, MIR::Isset* in)
{
	phc_TODO ();
}


void
Optimization_transformer::visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in)
{
	if (!isa<METHOD_NAME> (in->method_name))
		phc_TODO ();

	METHOD_NAME* name = dyc<METHOD_NAME> (in->method_name);

	// TODO: this should get all possible receivers
	
	Method_info* info = Oracle::get_method_info (name->value);

	if (info->has_implementation ())
		phc_TODO ();


	// Update the parameters with constants
	int i = -1;
	foreach (Actual_parameter* param, *in->actual_parameters)
	{
		i++;

		if (isa<Literal> (param->rvalue))
			continue;

		if (!param->is_ref
				&& !info->params->at (i)->pass_by_reference)
		{
			param->rvalue = get_literal (bb, param->rvalue);
		}
	}
}

void
Optimization_transformer::visit_new (Statement_block* bb, MIR::New* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_nil (Statement_block* bb, MIR::NIL* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_real (Statement_block* bb, MIR::REAL* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_string (Statement_block* bb, MIR::STRING* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_unary_op (Statement_block* bb, MIR::Unary_op* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in)
{
	phc_TODO ();
}