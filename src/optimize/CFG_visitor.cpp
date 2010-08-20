#include <boost/tuple/tuple.hpp>

#include "CFG_visitor.h"

using namespace MIR;
using namespace boost;

/*
 * Visitors
 */

void
CFG_visitor::visit_block (Basic_block* bb)
{
	foreach (SSA_name phi_lhs, *bb->get_phi_lhss ())
		visit_phi_node (bb, phi_lhs);

	// TODO: visit_ssa_op?

	// Sometimes you dont care what block is used.
	visit_basic_block (bb);

	if (Entry_block* eb = dynamic_cast<Entry_block*> (bb))
		visit_entry_block (eb);

	else if (Empty_block* eb = dynamic_cast<Empty_block*> (bb))
		visit_empty_block (eb);

	else if (Exit_block* eb = dynamic_cast<Exit_block*> (bb))
		visit_exit_block (eb);

	else if (Branch_block* brb = dynamic_cast<Branch_block*> (bb)) {
		visit_branch_block (brb);

		foreach (SSA_name sigma_rhs, *bb->get_sigma_rhss())
			visit_sigma_node(brb, sigma_rhs);
	}

	else if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
	{
		visit_statement_block (sb);

		switch (sb->statement->classid ())
		{
			case Assign_array::ID:
				visit_assign_array(sb, dyc<Assign_array>(sb->statement));
				break;
			case Assign_field::ID:
				visit_assign_field(sb, dyc<Assign_field>(sb->statement));
				break;
			case Assign_next::ID:
				visit_assign_next(sb, dyc<Assign_next>(sb->statement));
				break;
			case Assign_var::ID:
				visit_assign_var(sb, dyc<Assign_var>(sb->statement));
				break;
			case Assign_var_var::ID:
				visit_assign_var_var(sb, dyc<Assign_var_var>(sb->statement));
				break;
			case Catch::ID:
				visit_catch (sb, dyc<Catch>(sb->statement));
				break;
			case Class_alias::ID:
				visit_class_alias (sb, dyc<Class_alias>(sb->statement));
				break;
			case Eval_expr::ID:
				visit_eval_expr(sb, dyc<Eval_expr>(sb->statement));
				break;
			case Foreach_end::ID:
				visit_foreach_end(sb, dyc<Foreach_end>(sb->statement));
				break;
			case Foreach_next::ID:
				visit_foreach_next(sb, dyc<Foreach_next>(sb->statement));
				break;
			case Foreach_reset::ID:
				visit_foreach_reset(sb, dyc<Foreach_reset>(sb->statement));
				break;
			case Global::ID:
				visit_global(sb, dyc<Global>(sb->statement));
				break;
			case Interface_alias::ID:
				visit_interface_alias (sb, dyc<Interface_alias>(sb->statement));
				break;
			case Method_alias::ID:
				visit_method_alias (sb, dyc<Method_alias>(sb->statement));
				break;
			case Pre_op::ID:
				visit_pre_op(sb, dyc<Pre_op>(sb->statement));
				break;
			case Return::ID:
				visit_return(sb, dyc<Return>(sb->statement));
				break;
			case Static_declaration::ID:
				visit_static_declaration(sb, dyc<Static_declaration>(sb->statement));
				break;
			case Throw::ID:
				visit_throw(sb, dyc<Throw>(sb->statement));
				break;
			case Try::ID:
				visit_try(sb, dyc<Try>(sb->statement));
				break;
			case Unset::ID:
				visit_unset (sb, dyc<Unset>(sb->statement));
				break;
			default:
				xdebug (sb->statement);
				phc_unreachable ();
		}
	}

	else
		phc_unreachable ();
}

void
CFG_visitor::visit_basic_block (Basic_block*)
{
}

void
CFG_visitor::visit_entry_block (Entry_block*)
{
}

void
CFG_visitor::visit_empty_block (Empty_block*)
{
}

void
CFG_visitor::visit_exit_block (Exit_block*)
{
}

void
CFG_visitor::visit_branch_block (Branch_block*)
{
}


void
CFG_visitor::visit_statement_block (Statement_block*)
{
}


void
CFG_visitor::visit_phi_node (Basic_block* bb, SSA_name phi_lhs)
{
}

void
CFG_visitor::visit_sigma_node (Branch_block* brb, SSA_name sigma_rhs)
{
}



void
CFG_visitor::visit_assign_array (Statement_block*, Assign_array*)
{
}

void
CFG_visitor::visit_assign_field (Statement_block*, Assign_field *)
{
}

void
CFG_visitor::visit_assign_next (Statement_block*, Assign_next*)
{
}

void
CFG_visitor::visit_assign_var (Statement_block*, Assign_var*)
{
}

void
CFG_visitor::visit_assign_var_var (Statement_block*, Assign_var_var*)
{
}

void
CFG_visitor::visit_catch (Statement_block*, Catch*)
{
}

void
CFG_visitor::visit_class_alias (Statement_block*, Class_alias*)
{
}

void
CFG_visitor::visit_eval_expr (Statement_block*, Eval_expr*)
{
}

void
CFG_visitor::visit_foreach_end (Statement_block*, Foreach_end*)
{
}

void
CFG_visitor::visit_foreach_next (Statement_block*, Foreach_next*)
{
}

void
CFG_visitor::visit_foreach_reset (Statement_block*, Foreach_reset*)
{
}

void
CFG_visitor::visit_global (Statement_block*, Global*)
{
}

void
CFG_visitor::visit_interface_alias (Statement_block*, Interface_alias*)
{
}

void
CFG_visitor::visit_method_alias (Statement_block*, Method_alias*)
{
}

void
CFG_visitor::visit_pre_op (Statement_block*, Pre_op*)
{
}

void
CFG_visitor::visit_return (Statement_block*, Return*)
{
}

void
CFG_visitor::visit_static_declaration (Statement_block*, Static_declaration*)
{
}

void
CFG_visitor::visit_throw (Statement_block*, Throw*)
{
}

void
CFG_visitor::visit_try (Statement_block*, Try*)
{
}

void
CFG_visitor::visit_unset (Statement_block*, Unset*)
{
}

/*
 * Exprs
 */

void
CFG_visitor::visit_expr (Statement_block* sb, Expr* in)
{
	switch(in->classid())
	{
		case Array_access::ID:
			visit_array_access (sb, dyc<Array_access> (in));
			break;
		case Array_next::ID:
			visit_array_next (sb, dyc<Array_next> (in));
			break;
		case Bin_op::ID:
			visit_bin_op (sb, dyc<Bin_op> (in));
			break;
		case BOOL::ID:
			visit_bool (sb, dyc<BOOL> (in));
			break;
		case Cast::ID:
			visit_cast (sb, dyc<Cast> (in));
			break;
		case Constant::ID:
			visit_constant (sb, dyc<Constant> (in));
			break;
		case Field_access::ID:
			visit_field_access (sb, dyc<Field_access> (in));
			break;
		case Foreach_get_key::ID:
			visit_foreach_get_key (sb, dyc<Foreach_get_key> (in));
			break;
		case Foreach_get_val::ID:
			visit_foreach_get_val (sb, dyc<Foreach_get_val> (in));
			break;
		case Foreach_has_key::ID:
			visit_foreach_has_key (sb, dyc<Foreach_has_key> (in));
			break;
		case Instanceof::ID:
			visit_instanceof (sb, dyc<Instanceof> (in));
			break;
		case INT::ID:
			visit_int (sb, dyc<INT> (in));
			break;
		case Isset::ID:
			visit_isset (sb, dyc<Isset> (in));
			break;
		case Method_invocation::ID:
			visit_method_invocation (sb, dyc<Method_invocation> (in));
			break;
		case New::ID:
			visit_new (sb, dyc<New> (in));
			break;
		case NIL::ID:
			visit_nil (sb, dyc<NIL> (in));
			break;
		case Param_is_ref::ID:
			visit_param_is_ref (sb, dyc<Param_is_ref> (in));
			break;
		case REAL::ID:
			visit_real (sb, dyc<REAL> (in));
			break;
		case STRING::ID:
			visit_string (sb, dyc<STRING> (in));
			break;
		case Unary_op::ID:
			visit_unary_op (sb, dyc<Unary_op> (in));
			break;
		case VARIABLE_NAME::ID:
			visit_variable_name (sb, dyc<VARIABLE_NAME> (in));
			break;
		case Variable_variable::ID:
			visit_variable_variable (sb, dyc<Variable_variable> (in));
			break;
		default:
			phc_unreachable ();
	}
}


void
CFG_visitor::visit_array_access (Statement_block*, Array_access* in)
{
}

void
CFG_visitor::visit_array_next (Statement_block*, Array_next* in)
{
}

void
CFG_visitor::visit_bin_op (Statement_block*, Bin_op* in)
{
}

void
CFG_visitor::visit_bool (Statement_block*, BOOL* in)
{
}

void
CFG_visitor::visit_cast (Statement_block*, Cast* in)
{
}

void
CFG_visitor::visit_constant (Statement_block*, Constant* in)
{
}

void
CFG_visitor::visit_field_access (Statement_block*, Field_access* in)
{
}

void
CFG_visitor::visit_foreach_get_key (Statement_block*, Foreach_get_key* in)
{
}

void
CFG_visitor::visit_foreach_get_val (Statement_block*, Foreach_get_val* in)
{
}

void
CFG_visitor::visit_foreach_has_key (Statement_block*, Foreach_has_key* in)
{
}

void
CFG_visitor::visit_instanceof (Statement_block*, Instanceof* in)
{
}

void
CFG_visitor::visit_int (Statement_block*, INT* in)
{
}

void
CFG_visitor::visit_isset (Statement_block*, Isset* in)
{
}

void
CFG_visitor::visit_method_invocation (Statement_block*, Method_invocation* in)
{
}

void
CFG_visitor::visit_new (Statement_block*, New* in)
{
}

void
CFG_visitor::visit_nil (Statement_block*, NIL* in)
{
}

void
CFG_visitor::visit_param_is_ref (Statement_block*, Param_is_ref* in)
{
}

void
CFG_visitor::visit_real (Statement_block*, REAL* in)
{
}

void
CFG_visitor::visit_string (Statement_block*, STRING* in)
{
}

void
CFG_visitor::visit_unary_op (Statement_block*, Unary_op* in)
{
}

void
CFG_visitor::visit_variable_name (Statement_block*, VARIABLE_NAME* in)
{
}

void
CFG_visitor::visit_variable_variable (Statement_block*, Variable_variable* in)
{
}




/*
 * Transforms
 */
void
CFG_visitor::transform_block (Basic_block* bb)
{
	// bb->replace will move the phi nodes from BB to the new BBs. So here we
	// just update BB.
	
	// Allow it to update the CFG directly, its much easier.
	foreach (SSA_name phi_lhs, *bb->get_phi_lhss ())
		transform_phi_node (bb, phi_lhs);

	// TODO transform ssa_op?

	BB_list* out = new BB_list;

	if (Entry_block* eb = dynamic_cast<Entry_block*> (bb))
		transform_entry_block (eb, out);

	else if (Empty_block* eb = dynamic_cast<Empty_block*> (bb))
		transform_empty_block (eb, out);

	else if (Exit_block* eb = dynamic_cast<Exit_block*> (bb))
		transform_exit_block (eb, out);

	else if (Branch_block* brb = dynamic_cast<Branch_block*> (bb))
		transform_branch_block (brb, out);

	else if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
	{
		switch (sb->statement->classid ())
		{
			case Assign_array::ID:
				transform_assign_array(sb, dyc<Assign_array>(sb->statement), out);
				break;
			case Assign_field::ID:
				transform_assign_field(sb, dyc<Assign_field>(sb->statement), out);
				break;
			case Assign_next::ID:
				transform_assign_next(sb, dyc<Assign_next>(sb->statement), out);
				break;
			case Assign_var::ID:
				transform_assign_var(sb, dyc<Assign_var>(sb->statement), out);
				break;
			case Assign_var_var::ID:
				transform_assign_var_var(sb, dyc<Assign_var_var>(sb->statement), out);
				break;
			case Catch::ID:
				transform_catch (sb, dyc<Catch>(sb->statement), out);
				break;
			case Class_alias::ID:
				transform_class_alias (sb, dyc<Class_alias>(sb->statement), out);
				break;
			case Eval_expr::ID:
				transform_eval_expr(sb, dyc<Eval_expr>(sb->statement), out);
				break;
			case Foreach_end::ID:
				transform_foreach_end(sb, dyc<Foreach_end>(sb->statement), out);
				break;
			case Foreach_next::ID:
				transform_foreach_next(sb, dyc<Foreach_next>(sb->statement), out);
				break;
			case Foreach_reset::ID:
				transform_foreach_reset(sb, dyc<Foreach_reset>(sb->statement), out);
				break;
			case Global::ID:
				transform_global(sb, dyc<Global>(sb->statement), out);
				break;
			case Interface_alias::ID:
				transform_interface_alias (sb, dyc<Interface_alias>(sb->statement), out);
				break;
			case Method_alias::ID:
				transform_method_alias (sb, dyc<Method_alias>(sb->statement), out);
				break;
			case Pre_op::ID:
				transform_pre_op(sb, dyc<Pre_op>(sb->statement), out);
				break;
			case Return::ID:
				transform_return(sb, dyc<Return>(sb->statement), out);
				break;
			case Static_declaration::ID:
				transform_static_declaration(sb, dyc<Static_declaration>(sb->statement), out);
				break;
			case Throw::ID:
				transform_throw(sb, dyc<Throw>(sb->statement), out);
				break;
			case Try::ID:
				transform_try(sb, dyc<Try>(sb->statement), out);
				break;
			case Unset::ID:
				transform_unset(sb, dyc<Unset>(sb->statement), out);
				break;
			default:
				phc_unreachable ();
		}
	}
	else
		phc_unreachable ();

	bb->cfg->replace_bb (bb, out);
}


/*
 * Blocks
 */

void
CFG_visitor::transform_entry_block (Entry_block* in, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_empty_block (Empty_block* in, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_exit_block (Exit_block* in, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_branch_block (Branch_block* in, BB_list* out)
{
	out->push_back (in);
}


void
CFG_visitor::transform_phi_node (Basic_block* bb, SSA_name lhs)
{
}


/*
 * Statements
 */

void
CFG_visitor::transform_assign_array (Statement_block* in, Assign_array*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_assign_field (Statement_block* in, Assign_field*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_assign_next (Statement_block* in, Assign_next*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_assign_var (Statement_block* in, Assign_var*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_assign_var_var (Statement_block* in, Assign_var_var*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_catch (Statement_block* in, MIR::Catch*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_class_alias (Statement_block* in, MIR::Class_alias*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_eval_expr (Statement_block* in, Eval_expr*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_foreach_end (Statement_block* in, Foreach_end*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_foreach_next (Statement_block* in, Foreach_next*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_foreach_reset (Statement_block* in, Foreach_reset*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_global (Statement_block* in, Global*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_interface_alias (Statement_block* in, MIR::Interface_alias*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_method_alias (Statement_block* in, MIR::Method_alias*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_pre_op (Statement_block* in, Pre_op*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_return (Statement_block* in, Return*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_static_declaration (Statement_block* in, Static_declaration*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_throw (Statement_block* in, Throw*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_try (Statement_block* in, Try*, BB_list* out)
{
	out->push_back (in);
}

void
CFG_visitor::transform_unset (Statement_block* in, Unset*, BB_list* out)
{
	out->push_back (in);
}

/*
 * Exprs
 */

Expr*
CFG_visitor::transform_expr (Statement_block* sb, Expr* in)
{
	switch(in->classid())
	{
		case Array_access::ID:
			return transform_array_access (sb, dyc<Array_access> (in));
		case Array_next::ID:
			return transform_array_next (sb, dyc<Array_next> (in));
		case Bin_op::ID:
			return transform_bin_op (sb, dyc<Bin_op> (in));
		case BOOL::ID:
			return transform_bool (sb, dyc<BOOL> (in));
		case Cast::ID:
			return transform_cast (sb, dyc<Cast> (in));
		case Constant::ID:
			return transform_constant (sb, dyc<Constant> (in));
		case Field_access::ID:
			return transform_field_access (sb, dyc<Field_access> (in));
		case Foreach_get_key::ID:
			return transform_foreach_get_key (sb, dyc<Foreach_get_key> (in));
		case Foreach_get_val::ID:
			return transform_foreach_get_val (sb, dyc<Foreach_get_val> (in));
		case Foreach_has_key::ID:
			return transform_foreach_has_key (sb, dyc<Foreach_has_key> (in));
		case Instanceof::ID:
			return transform_instanceof (sb, dyc<Instanceof> (in));
		case INT::ID:
			return transform_int (sb, dyc<INT> (in));
		case Isset::ID:
			return transform_isset (sb, dyc<Isset> (in));
		case Method_invocation::ID:
			return transform_method_invocation (sb, dyc<Method_invocation> (in));
		case New::ID:
			return transform_new (sb, dyc<New> (in));
		case NIL::ID:
			return transform_nil (sb, dyc<NIL> (in));
		case Param_is_ref::ID:
			return transform_param_is_ref (sb, dyc<Param_is_ref> (in));
		case REAL::ID:
			return transform_real (sb, dyc<REAL> (in));
		case STRING::ID:
			return transform_string (sb, dyc<STRING> (in));
		case Unary_op::ID:
			return transform_unary_op (sb, dyc<Unary_op> (in));
		case VARIABLE_NAME::ID:
			return transform_variable_name (sb, dyc<VARIABLE_NAME> (in));
		case Variable_variable::ID:
			return transform_variable_variable (sb, dyc<Variable_variable> (in));
		default:
			phc_unreachable ();
	}
}

Expr*
CFG_visitor::transform_array_access (Statement_block*, Array_access* in)
{
	return in;
}

Expr*
CFG_visitor::transform_array_next (Statement_block*, Array_next* in)
{
	return in;
}

Expr*
CFG_visitor::transform_bin_op (Statement_block*, Bin_op* in)
{
	return in;
}

Expr*
CFG_visitor::transform_bool (Statement_block*, BOOL* in)
{
	return in;
}

Expr*
CFG_visitor::transform_cast (Statement_block*, Cast* in)
{
	return in;
}

Expr*
CFG_visitor::transform_constant (Statement_block*, Constant* in)
{
	return in;
}

Expr*
CFG_visitor::transform_field_access (Statement_block*, Field_access* in)
{
	return in;
}

Expr*
CFG_visitor::transform_foreach_get_key (Statement_block*, Foreach_get_key* in)
{
	return in;
}

Expr*
CFG_visitor::transform_foreach_get_val (Statement_block*, Foreach_get_val* in)
{
	return in;
}

Expr*
CFG_visitor::transform_foreach_has_key (Statement_block*, Foreach_has_key* in)
{
	return in;
}

Expr*
CFG_visitor::transform_instanceof (Statement_block*, Instanceof* in)
{
	return in;
}

Expr*
CFG_visitor::transform_int (Statement_block*, INT* in)
{
	return in;
}

Expr*
CFG_visitor::transform_isset (Statement_block*, Isset* in)
{
	return in;
}

Expr*
CFG_visitor::transform_method_invocation (Statement_block*, Method_invocation* in)
{
	return in;
}

Expr*
CFG_visitor::transform_new (Statement_block*, New* in)
{
	return in;
}

Expr*
CFG_visitor::transform_nil (Statement_block*, NIL* in)
{
	return in;
}

Expr*
CFG_visitor::transform_param_is_ref (Statement_block*, Param_is_ref* in)
{
	return in;
}

Expr*
CFG_visitor::transform_real (Statement_block*, REAL* in)
{
	return in;
}

Expr*
CFG_visitor::transform_string (Statement_block*, STRING* in)
{
	return in;
}

Expr*
CFG_visitor::transform_unary_op (Statement_block*, Unary_op* in)
{
	return in;
}

Expr*
CFG_visitor::transform_variable_name (Statement_block*, VARIABLE_NAME* in)
{
	return in;
}

Expr*
CFG_visitor::transform_variable_variable (Statement_block*, Variable_variable* in)
{
	return in;
}
