/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Use the results of the analyses to transform the MIR. Do not handle dead
 * code.
 * */

#include "Aliasing.h"
#include "Points_to.h"
#include "Def_use.h"
#include "Whole_program.h"
#include "optimize/Abstract_value.h"

#include "Optimization_transformer.h"
#include "Value_analysis.h"


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

const Abstract_value*
Optimization_transformer::get_in_abstract_value (Basic_block* bb, Rvalue* in)
{
	if (isa<Literal> (in))
		return new Abstract_value (dyc<Literal> (in));

	Context* cx = Context::non_contextual (bb);
	return wp->get_abstract_value (cx, R_IN, dyc<VARIABLE_NAME> (in));
}

const Abstract_value*
Optimization_transformer::get_out_abstract_value (Basic_block* bb, Rvalue* in)
{
	if (isa<Literal> (in))
		return new Abstract_value (dyc<Literal> (in));

	Context* cx = Context::non_contextual (bb);
	return wp->get_abstract_value (cx, R_OUT, dyc<VARIABLE_NAME> (in));
}


Rvalue*
Optimization_transformer::get_literal (Basic_block* bb, Rvalue* in)
{
	const Abstract_value* absval = get_in_abstract_value (bb, in);

	if (absval->lit == NULL)
		return in;

	return clone (absval->lit);
}

void
Optimization_transformer::visit_block (Basic_block* bb)
{
	Context* cx = Context::non_contextual (bb);
	if (!wp->values->has_analysis_result (cx, R_IN))
		return;

	CFG_visitor::visit_block (bb);
	CFG_visitor::transform_block (bb);
}

void
Optimization_transformer::visit_branch_block (Branch_block* bb)
{
	Literal* lit = dynamic_cast <Literal*> (get_literal (bb, bb->branch->variable_name));
	if (lit)
	{
		CTS ("num_branches_replaced_with_direction");
		bb->cfg->set_branch_direction (bb, PHP::is_true (lit));
	}
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
	if (!in->is_ref)
		in->rhs = get_literal (bb, in->rhs);

	// TODO: change a variable field into a known field name
}

bool
Optimization_transformer::rhs_is_pure (Statement_block* bb, MIR::Expr* in)
{
	// We dont model enough here to be sure.
	if (isa<New> (in))
		return false;

	if (Method_invocation* mi = dynamic_cast<Method_invocation*> (in))
	{
		METHOD_NAME* name = dynamic_cast<METHOD_NAME*> (mi->method_name);
		if (name == NULL)
			return false;

		if (!Oracle::is_pure_function (name))
			return false;

		foreach (Actual_parameter* param, *mi->actual_parameters)
			if (get_literal (bb, param->rvalue) == NULL)
				return false;
	}

	// If the only definition is the LHS, nothing else has happened
	cIndex_node_list* defs = wp->def_use->get_defs (bb);
	cIndex_node_list* may_defs = wp->def_use->get_may_defs (bb);
	if (defs->size () + may_defs->size () != 1)
		return false;

	return true;
}


void
Optimization_transformer::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	// If the RHS value is known, replace it outright.
	const Literal* lit = get_out_abstract_value (bb, in->lhs)->lit;

	if (	lit
		&& in->is_ref == false 
		&& rhs_is_pure (bb, in->rhs))
	{
		in->rhs = clone (lit);
	}
	else
		visit_expr (bb, in->rhs);
}

void
Optimization_transformer::visit_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in)
{
	// TODO: optimize to assign_var if possible.
}

void
Optimization_transformer::visit_catch (Statement_block* bb, MIR::Catch* in)
{
}

void
Optimization_transformer::visit_class_alias (Statement_block* bb, MIR::Class_alias* in)
{
}

void
Optimization_transformer::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	visit_expr (bb, in->expr);
}

void
Optimization_transformer::visit_foreach_end (Statement_block* bb, MIR::Foreach_end* in)
{
}

void
Optimization_transformer::visit_foreach_next (Statement_block* bb, MIR::Foreach_next* in)
{
}

void
Optimization_transformer::visit_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in)
{
}

void
Optimization_transformer::visit_global (Statement_block* bb, MIR::Global* in)
{
}

void
Optimization_transformer::visit_interface_alias (Statement_block* bb, MIR::Interface_alias* in)
{
}

void
Optimization_transformer::visit_method_alias (Statement_block* bb, MIR::Method_alias* in)
{
}

void
Optimization_transformer::visit_pre_op (Statement_block* bb, MIR::Pre_op* in)
{
	const Literal* lit = get_out_abstract_value (bb, in->variable_name)->lit;

	if (lit)
		bb->statement = new Assign_var (in->variable_name, clone (lit));
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
}

void
Optimization_transformer::visit_throw (Statement_block* bb, MIR::Throw* in)
{
}

void
Optimization_transformer::visit_try (Statement_block* bb, MIR::Try* in)
{
}

void
Optimization_transformer::visit_unset (Statement_block* bb, MIR::Unset* in)
{
	foreach (Rvalue*& rval, *in->array_indices)
	{
		rval = get_literal (bb, rval);
	}

	// TODO: We can remove unsets from uninits later.
}


void
Optimization_transformer::visit_array_access (Statement_block* bb, MIR::Array_access* in)
{
	in->index = get_literal (bb, in->index);

	// If the RHS is completely known, the analysis will pick it up.
}

void
Optimization_transformer::visit_array_next (Statement_block* bb, MIR::Array_next* in)
{
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
	// If known, visit_assign_var will handle it.
}

void
Optimization_transformer::visit_field_access (Statement_block* bb, MIR::Field_access* in)
{
	// TODO: can change a variable field to just a field.
	if (Variable_field* vf = dynamic_cast<Variable_field*> (in->field_name))
	{
		Rvalue* rval = get_literal (bb, vf->variable_name);
		if (Literal* lit = dynamic_cast<Literal*> (rval))
			in->field_name = new MIR::FIELD_NAME (PHP::get_string_value(lit));
	}
	
	// TODO: if this actually calls __get, we need to do some work here. That
	// cant happen yet, because we check for handlers early.
}

void
Optimization_transformer::visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in)
{
}

void
Optimization_transformer::visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in)
{
}

void
Optimization_transformer::visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in)
{
}

void
Optimization_transformer::visit_instanceof (Statement_block* bb, MIR::Instanceof* in)
{
}

void
Optimization_transformer::visit_int (Statement_block* bb, MIR::INT* in)
{
}

void
Optimization_transformer::visit_isset (Statement_block* bb, MIR::Isset* in)
{
	foreach (Rvalue*& rval, *in->array_indices)
	{
		rval = get_literal (bb, rval);
	}
}

void
Optimization_transformer::copy_in_literals (Basic_block* bb, Method_info_list* receivers, Actual_parameter_list* params)
{
	// Update the parameters with constants
	int i = -1;
	foreach (Actual_parameter* param, *params)
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
Optimization_transformer::visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in)
{
	Context* cx = Context::non_contextual (bb);
	copy_in_literals (bb, wp->get_possible_receivers (cx, R_IN, in), in->actual_parameters);
}

void
Optimization_transformer::visit_new (Statement_block* bb, MIR::New* in)
{
	Context* cx = Context::non_contextual (bb);
	copy_in_literals (bb, wp->get_possible_receivers (cx, R_IN, in), in->actual_parameters);
}

void
Optimization_transformer::visit_nil (Statement_block* bb, MIR::NIL* in)
{
}

void
Optimization_transformer::visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in)
{
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
	// TODO: optimize var-vars
}


void
Optimization_transformer::transform_eval_expr (Statement_block* in, Eval_expr* eval_expr, BB_list* out)
{
	if (!rhs_is_pure (in, eval_expr->expr))
		out->push_back (in);
}

/*
 * Exprs
 */

Expr*
Optimization_transformer::transform_cast (Statement_block* bb, Cast* in)
{
	// Remove the cast if we can.
	const Abstract_value* absval = get_in_abstract_value (bb, in->variable_name);
	if (*absval->types == Types (*in->cast->value))
		return in->variable_name;

	return in;
}
