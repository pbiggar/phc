/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Live variable analysis
 */

#include "Address_taken.h"
#include "process_ir/General.h"

using namespace MIR;

Address_taken::Address_taken ()
{
	aliases = new Set ();
}

// Transfer functions not required
void Address_taken::transfer_in (Basic_block* bb, list<Basic_block*>*) {}
void Address_taken::transfer_out (Basic_block*, list<Basic_block*>*) {}

void Address_taken::visit_branch_block (Branch_block* bb) {}
void Address_taken::visit_entry_block (Entry_block* bb)
{
	// All variables in the global scope are aliased.
	if (*bb->method->signature->method_name->value == "__MAIN__")
		alias_bottom (bb);

	foreach (Formal_parameter* fp, *bb->method->signature->formal_parameters)
		aliased (bb, fp->var->variable_name);
}

void
Address_taken::alias_bottom (Basic_block* bb)
{
	bb->aliases->insert_all ();
}

void
Address_taken::aliased (Basic_block* bb, Variable_name* in)
{
	if (isa<VARIABLE_NAME> (in))
		aliased (bb, dyc<VARIABLE_NAME> (in));
	else
		alias_bottom (bb);
}

void
Address_taken::aliased (Basic_block* bb, Rvalue* in)
{
	if (isa<VARIABLE_NAME> (in))
		aliased (bb, dyc<VARIABLE_NAME> (in));

	// nothing happens for literals
}

void
Address_taken::aliased (Basic_block* bb, VARIABLE_NAME* in)
{
	bb->aliases->insert (in->value);
}

// Aliased:
// all formal parameters (we cant tell if call-time-pass-by-reference is used)
// LHS of assign_var with is_ref
// RHS of assign_array with is_ref
// RHS of push_array with is_ref
// GLOBALs


// Exprs to be considered:
// RHS of assign_var
// EXPR of eval_expr
// EXPR of return (we dont know call-time-return-by-reference)


/* Expressions */
void 
Address_taken::alias_expr (Basic_block* bb, Expr* in)
{
	switch(in->classid())
	{
		case BOOL::ID:
		case Constant::ID:
		case INT::ID:
		case NIL::ID:
		case REAL::ID:
		case STRING::ID:
		case Bin_op::ID:
		case Cast::ID:
		case Foreach_get_key::ID:
		case Foreach_get_val::ID:
		case Foreach_has_key::ID:
		case Index_array::ID:
		case Isset::ID:
			// Nothing is aliased on the RHS of $x =& $y[$z]
		case Instanceof::ID:
		case Param_is_ref::ID:
		case Unary_op::ID:
		case Target_expr::ID:
			// do nothing
			break;

			// Given
			// $t->$x[$i]
			// $t->$$r[$i]
			// $x is aliased unless $t or $i exists
			// $r means everything is aliased unless $t or $i
		case Method_invocation::ID:
		{
			Method_invocation* mi = dyc<Method_invocation> (in);

			foreach (Actual_parameter* ap, *mi->actual_parameters)
				aliased (bb, ap->rvalue);

			break;
		}

		case New::ID:
		{
			New* n = dyc<New> (in);

			foreach (Actual_parameter* ap, *n->actual_parameters)
				aliased (bb, ap->rvalue);

			break;
		}

		case VARIABLE_NAME::ID:
			aliased (bb, dyc<VARIABLE_NAME> (in));
			break;

		case Variable_variable::ID:
			alias_bottom (bb);
			break;

		default:
			assert (0);
			break;
	}
}

void
Address_taken::visit_assign_array (Statement_block* bb, MIR::Assign_array* in)
{
	if (in->is_ref)
		aliased (bb, in->rhs);
}

void
Address_taken::visit_assign_target (Statement_block* bb, MIR::Assign_target* in)
{
	if (in->is_ref)
		aliased (bb, in->rhs);
}

void
Address_taken::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	if (in->is_ref)
	{
		alias_expr (bb, in->rhs);
		aliased (bb, in->lhs);
	}
}

void
Address_taken::visit_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in)
{
	if (in->is_ref)
	{
		aliased (bb, in->lhs);
		aliased (bb, in->rhs);
	}
}

void
Address_taken::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	alias_expr (bb, in->expr);
}

void
Address_taken::visit_foreach_end (Statement_block* bb, MIR::Foreach_end* in)
{
}

void
Address_taken::visit_foreach_next (Statement_block* bb, MIR::Foreach_next* in)
{
}

void
Address_taken::visit_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in)
{
}

void
Address_taken::visit_global (Statement_block* bb, MIR::Global* in)
{
	aliased (bb, in->variable_name);
}

void
Address_taken::visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in)
{
	// Nothing
}

void
Address_taken::visit_pre_op (Statement_block* bb, MIR::Pre_op* in)
{
	// Nothing
}

void
Address_taken::visit_push_array (Statement_block* bb, MIR::Push_array* in)
{
	if (in->is_ref)
		aliased (bb, in->rhs);
}

void
Address_taken::visit_return (Statement_block* bb, MIR::Return* in)
{
	alias_expr (bb, in->expr);
}
void
Address_taken::visit_static_declaration (Statement_block* bb, MIR::Static_declaration* in)
{
	// This could be set to anything in a different incovation of the
	// function.
	aliased (bb, in->var->variable_name);
}

void
Address_taken::visit_try (Statement_block* bb, MIR::Try*)
{
	alias_bottom (bb);
}

void
Address_taken::visit_throw (Statement_block* bb, MIR::Throw*)
{
	alias_bottom (bb);
}

void
Address_taken::visit_unset (Statement_block* sb, MIR::Unset*)
{
	// Nothing
}

void
Address_taken::init_block (Basic_block* bb)
{
	// We use a global set for this, since there is only one solution.
	bb->aliases = aliases;
}

bool
Address_taken::solution_has_changed (Basic_block* bb)
{
	// The solution never changes
	return false;
}
