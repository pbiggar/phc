/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Live variable analysis
 */

#include "process_ir/General.h"
#include "Address_taken.h"
#include "ssa/Virtual_variable.h"

using namespace MIR;

Address_taken::Address_taken ()
{
	aliases = new Set ();
}

void
Address_taken::visit_entry_block (Entry_block* bb)
{
	foreach (Formal_parameter* fp, *bb->method->signature->formal_parameters)
		aliased (bb, fp->var->variable_name);
}

void
Address_taken::alias_bottom (Basic_block* bb)
{
	// Havent thought this one through yet
	assert (0);
	aliases->insert_all ();
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
	aliases->insert (in);
}

// Aliased:
// all formal parameters (we cant tell if call-time-pass-by-reference is used)
// LHS of assign_var with is_ref
// RHS of assign_array with is_ref
// RHS of assign_next with is_ref
// GLOBALs


// Exprs to be considered:
// RHS of assign_var
// EXPR of eval_expr
// EXPR of return (we dont know call-time-return-by-reference)


/* This is the rhs of an $x =& ... assignment. So ignore things like parameters, which will be handled by visit_expr. This just handles RHSs. */
void
Address_taken::alias_expr (Basic_block* bb, Expr* in)
{
	phc_TODO ();
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
		case Array_access::ID:
			// Nothing is aliased on the RHS of $x =& $y[$z]
		case Isset::ID:
		case Instanceof::ID:
		case Param_is_ref::ID:
		case Unary_op::ID:
		case Field_access::ID:
			phc_TODO ();
			assert (0);
			// do nothing
			break;

			// Given
			// $t->$x[$i]
			// $t->$$r[$i]
			// $x is aliased unless $t or $i exists
			// $r means everything is aliased unless $t or $i
		case Method_invocation::ID:
		{
			phc_TODO ();
			Method_invocation* mi = dyc<Method_invocation> (in);
			break;
		}

		case New::ID:
		{
			phc_TODO ();
			New* n = dyc<New> (in);

			foreach (Actual_parameter* ap, *n->actual_parameters)
				aliased (bb, ap->rvalue);

			break;
		}

		case VARIABLE_NAME::ID:
			phc_TODO ();
			aliased (bb, dyc<VARIABLE_NAME> (in));
			break;

		case Variable_variable::ID:
			phc_TODO ();
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
	// Indirect assignments have their virtual variables aliased
	aliased (bb, get_virtual (bb, in));

	if (in->is_ref)
		aliased (bb, in->rhs);
}

void
Address_taken::visit_assign_field (Statement_block* bb, MIR::Assign_field* in)
{
	aliased (bb, get_virtual (bb, in));

	if (in->is_ref)
		aliased (bb, in->rhs);
}

void
Address_taken::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	visit_expr (bb, in->rhs);

	if (in->is_ref)
	{
		aliased (bb, in->lhs);

		VARIABLE_NAME* virt = get_virtual (bb, in->rhs);
		if (virt)
			aliased (bb, virt);
	}
}

void
Address_taken::visit_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in)
{
	phc_TODO ();
	if (in->is_ref)
	{
		aliased (bb, in->lhs);
		aliased (bb, in->rhs);
	}
}

void
Address_taken::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	visit_expr (bb, in->expr);
}

void
Address_taken::visit_global (Statement_block* bb, MIR::Global* in)
{
	aliased (bb, in->variable_name);
}

void
Address_taken::visit_assign_next (Statement_block* bb, MIR::Assign_next* in)
{
	if (in->is_ref)
		aliased (bb, in->rhs);
}

void
Address_taken::visit_return (Statement_block* bb, MIR::Return* in)
{
	aliased (bb, in->variable_name);
}
void
Address_taken::visit_static_declaration (Statement_block* bb, MIR::Static_declaration* in)
{
	// This could be set to anything in a different invocation of the
	// function (TODO: unsure about this)
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

/*
 * Exprs - get the aliases in the expression, assuming it is not in the form:
 *		$x =& ...
 *	but instead:
 *		$x = ...
 *	or just
 *		...
 */

/*
 * Do nothings:
 *		Literals and constants
 *		unary_ops and bin_ops
 *
 *	Virtual vars
 *		array_access
 *		field_access
 *
 *		
 */
void
Address_taken::visit_array_access (Statement_block* bb, MIR::Array_access* in)
{
	aliased (bb, get_virtual (bb, in));
}

void
Address_taken::visit_field_access (Statement_block* bb, MIR::Field_access* in)
{
	phc_TODO ();
}

void
Address_taken::visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in)
{
	aliased (bb, get_virtual (bb, in));
}

void
Address_taken::visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in)
{
	aliased (bb, get_virtual (bb, in));
}

void
Address_taken::visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in)
{
	aliased (bb, get_virtual (bb, in));
}

void
Address_taken::visit_instanceof (Statement_block* bb, MIR::Instanceof* in)
{
	phc_TODO ();
}
void
Address_taken::visit_isset (Statement_block* bb, MIR::Isset* in)
{
	phc_TODO ();
}
void
Address_taken::visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in)
{
	foreach (Actual_parameter* ap, *in->actual_parameters)
		aliased (bb,ap->rvalue);
}
void
Address_taken::visit_new (Statement_block* bb, MIR::New* in)
{
	phc_TODO ();
}

void
Address_taken::visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in)
{
	// TODO:
	// Is this a may-use of possibly every variable in the function?
	phc_TODO ();
}


