/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Use the results of the analyses to transform the MIR. Do not handle dead
 * code.
 * */

#include "Aliasing.h"
#include "Points_to.h"
#include "Whole_program.h"
#include "optimize/Abstract_value.h"

#include "Optimization_transformer.h"


using namespace MIR;
using namespace boost;
using namespace std;

/*
 * Apply the optimization results.
 */
Optimization_transformer::Optimization_transformer (Whole_program* wp)
: wp (wp)
{
}

void
Optimization_transformer::run (CFG* cfg)
{
}

Abstract_value*
Optimization_transformer::get_in_abstract_value (Basic_block* bb, Rvalue* in)
{
	if (isa<Literal> (in))
		return new Abstract_value (dyc<Literal> (in));

	Context* cx = Context::non_contextual (bb);
	return wp->get_bb_in_abstract_value (
			cx,
			VN (cx->symtable_name (), dyc<VARIABLE_NAME> (in))->name ());
}

Abstract_value*
Optimization_transformer::get_out_abstract_value (Basic_block* bb, Rvalue* in)
{
	if (isa<Literal> (in))
		return new Abstract_value (dyc<Literal> (in));

	Context* cx = Context::non_contextual (bb);
	return wp->get_abstract_value (
			cx,
			VN (cx->symtable_name (), dyc<VARIABLE_NAME> (in))->name ());
}


Rvalue*
Optimization_transformer::get_literal (Basic_block* bb, Rvalue* in)
{
	Abstract_value* absval = get_in_abstract_value (bb, in);

	if (absval->lit == NULL)
		return in;

	return absval->lit;
}

void
Optimization_transformer::visit_branch_block (Branch_block* bb)
{
	Literal* lit = dynamic_cast <Literal*> (get_literal (bb, bb->branch->variable_name));
	if (lit)
		bb->cfg->set_branch_direction (bb, PHP::is_true (lit));
}


void
Optimization_transformer::visit_assign_array (Statement_block* bb, MIR::Assign_array* in)
{
	in->index = get_literal (bb, in->index);

	if (!in->is_ref)
		in->rhs = get_literal (bb, in->rhs);
}

void
Optimization_transformer::visit_assign_field (Statement_block* bb, MIR::Assign_field * in)
{
	phc_TODO ();
}


void
Optimization_transformer::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	// TODO: check that there are no implicit operations on the rhs. This could
	// be done by checking that there is not a def to the RHS.

	// The assignment is by reference. We may be able to remove this later,
	// via DCE.
	if (not in->is_ref && not isa<Method_invocation> (in->rhs) && not isa<New> (in->rhs))
	{
		// If the RHS value is known, replace it outright.
		Literal* lit = get_out_abstract_value (bb, in->lhs)->lit;

		if (lit)
			in->rhs = lit;
	}

	// visit_expr for whatever is left
	visit_expr (bb, in->rhs);

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
	if (isa<Variable_variable> (in->variable_name))
		phc_TODO ();
}

void
Optimization_transformer::visit_pre_op (Statement_block* bb, MIR::Pre_op* in)
{
	Literal* lit = get_out_abstract_value (bb, in->variable_name)->lit;

	if (lit)
		bb->statement = new Assign_var (in->variable_name, lit);
}

void
Optimization_transformer::visit_assign_next (Statement_block* bb, MIR::Assign_next* in)
{
	if (!in->is_ref)
		in->rhs = get_literal (bb, in->rhs);
}

void
Optimization_transformer::visit_return (Statement_block* bb, MIR::Return* in)
{
	if (bb->cfg->method->signature->return_by_ref)
		return;

	in->rvalue = get_literal (bb, in->rvalue);
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
	// We can remove unsets from uninits later.
	// TODO: We should replace array indices
}


void
Optimization_transformer::visit_array_access (Statement_block* bb, MIR::Array_access* in)
{
	in->index = get_literal (bb, in->index);

	// If the RHS is completely known, the analysis will pick it up.
}

void
Optimization_transformer::visit_bin_op (Statement_block* bb, MIR::Bin_op* in)
{
	in->left = get_literal (bb, in->left);
	in->right = get_literal (bb, in->right);
}

void
Optimization_transformer::visit_bool (Statement_block* bb, MIR::BOOL* in)
{
}

void
Optimization_transformer::visit_cast (Statement_block* bb, MIR::Cast* in)
{
	// TODO: if we know the type, we might be able to remove the cast.
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
}

void
Optimization_transformer::visit_isset (Statement_block* bb, MIR::Isset* in)
{
	phc_TODO ();
}


void
Optimization_transformer::visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in)
{
	Method_info_list* receivers = wp->get_possible_receivers (in);

	// Update the parameters with constants
	int i = -1;
	foreach (Actual_parameter* param, *in->actual_parameters)
	{
		i++;

		if (isa<Literal> (param->rvalue))
			continue;

		bool may_ref = param->is_ref;
		foreach (Method_info* info, *receivers)
		{
			may_ref |= info->param_by_ref (i);
		}

		if (not may_ref)
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
}

void
Optimization_transformer::visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in)
{
	phc_TODO ();
}

void
Optimization_transformer::visit_real (Statement_block* bb, MIR::REAL* in)
{
}

void
Optimization_transformer::visit_string (Statement_block* bb, MIR::STRING* in)
{
}

void
Optimization_transformer::visit_unary_op (Statement_block* bb, MIR::Unary_op* in)
{
}

void
Optimization_transformer::visit_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in)
{
}

void
Optimization_transformer::visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in)
{
	phc_TODO ();
}
