/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Live variable analysis
 */

#include "Live_variable_analysis.h"
#include "Dead_code_elimination.h"
#include "Address_taken.h"
#include "process_ir/General.h"
#include "cmdline.h"

using namespace MIR;

void
Live_variable_analysis::init_block (Basic_block* bb)
{
	bb->defs = new Set();
	bb->uses = new Set();
	bb->live_in = new Set();
	bb->live_out = new Set();
	bb->changed = false;
}

bool
Live_variable_analysis::solution_has_changed (Basic_block* bb)
{
	bool result = bb->changed;
	bb->changed = false;
	return result;
}

void
Live_variable_analysis::transfer_in (Basic_block* bb, list<Basic_block*>*)
{
	Set* old = bb->live_in;

	// IN = (OUT / DEFS) U USES
	bb->live_in = bb->live_out->set_difference (bb->defs)->set_union (bb->uses);

	if (*bb->live_in != *old)
		bb->changed = true;
}

void
Live_variable_analysis::transfer_out (Basic_block* bb, list<Basic_block*>* succs)
{
	// OUT = \/ IN (s), where s in Succs (BB).
	bb->live_out = new Set;
	foreach (Basic_block* succ, *succs)
	{
		bb->live_out = bb->live_out->set_union (succ->live_in);
	}

	// We don't care if the OUT solution changes, unless the IN solution does,
	// as the OUT solution wouldn't propagate.
}

void
use_bottom (Basic_block* bb)
{
	bb->uses->insert_all ();
}

void
use (Basic_block* bb, VARIABLE_NAME* var_name)
{
	bb->uses->insert (var_name);
}

void
use (Basic_block* bb, Rvalue* rval)
{
	if (isa<VARIABLE_NAME> (rval))
		use (bb, dyc<VARIABLE_NAME> (rval));
}

void
use (Basic_block* bb, Variable_name* var_name)
{
	if (isa<VARIABLE_NAME> (var_name))
		use (bb, dyc<VARIABLE_NAME> (var_name));
	else
		use_bottom (bb);
}

void
def (Basic_block* bb, VARIABLE_NAME* var_name)
{
	cdebug << "def: " << *var_name->value;
	if (Statement_block* sb = dynamic_cast<Statement_block*> (bb))
	{
		cdebug << " in ";
		debug (sb->statement);
		xdebug (sb->statement);
	}

	bb->defs->insert (var_name);
}

void
Live_variable_analysis::visit_branch_block (Branch_block* bb)
{
	use (bb, bb->branch->variable_name);
}

/* Expressions */
void use_expr (Basic_block* bb, Expr* in)
{
	switch(in->classid())
	{
		case BOOL::ID:
		case Constant::ID:
		case INT::ID:
		case NIL::ID:
		case REAL::ID:
		case STRING::ID:
		case Param_is_ref::ID:
			// do nothing
			break;

		case Bin_op::ID:
		{
			Bin_op* bin_op = dyc<Bin_op> (in);
			use (bb, bin_op->left);
			use (bb, bin_op->right);
			break;
		}

		case Cast::ID:
			use (bb, dyc<Cast> (in)->variable_name);
			break;

		case Foreach_get_key::ID:
			use (bb, dyc<Foreach_get_key> (in)->array);
			break;

		case Foreach_get_val::ID:
			use (bb, dyc<Foreach_get_val> (in)->array);
			break;

		case Foreach_has_key::ID:
			use (bb, dyc<Foreach_has_key> (in)->array);
			break;

		case Array_access::ID:
		{
			Array_access* ia = dyc<Array_access> (in);
			use (bb, ia->variable_name);
			use (bb, ia->index);
			break;
		}

		case Isset::ID:
		{
			Isset* i = dyc<Isset> (in);
			if (i->target && isa<VARIABLE_NAME> (i->target))
				use (bb, dyc<VARIABLE_NAME> (i->target));

			// If there is a target, then a var-var means a field access, not
			// accessing any variable.
			if (isa<Variable_variable> (i->variable_name))
			{
				if (i->target)
					use (bb, dyc<Variable_variable> (i->variable_name)->variable_name);
				else
					use_bottom (bb);
			}
			else
				use (bb, dyc<VARIABLE_NAME> (i->variable_name));

			foreach (Rvalue* rv, *i->array_indices)
				use (bb, rv);

			break;
		}

		case Instanceof::ID:
			use (bb, dyc<Instanceof> (in)->variable_name);
			break;

		case Method_invocation::ID:
		{
			Method_invocation* mi = dyc<Method_invocation> (in);

			if (isa<VARIABLE_NAME> (mi->method_name))
				assert (0); // TODO

			foreach (Actual_parameter* ap, *mi->actual_parameters)
			{
				VARIABLE_NAME* var_name = dynamic_cast<VARIABLE_NAME*> (ap->rvalue);
				if (var_name)
					use (bb, var_name);
			}
			break;
		}

		case New::ID:
		{
			New* n = dyc<New> (in);

			if (isa<VARIABLE_NAME> (n->class_name))
				assert (0); // TODO

			foreach (Actual_parameter* ap, *n->actual_parameters)
			{
				VARIABLE_NAME* var_name = dynamic_cast<VARIABLE_NAME*> (ap->rvalue);
				if (var_name)
					use (bb, var_name);
			}
			break;
		}

		case Field_access::ID:
		{
			Field_access* fa = dyc<Field_access> (in);

			// This uses a variable field, not a variable expr.
			if (isa<Variable_field> (fa->field_name))
				use (bb, dyc<Variable_field> (fa->field_name)->variable_name);

			if (isa<VARIABLE_NAME> (fa->target))
				use (bb, dyc<VARIABLE_NAME> (fa->target));

			break;
		}

		case Unary_op::ID:
			use (bb, dyc<Unary_op> (in)->variable_name);
			break;

		case VARIABLE_NAME::ID:
			use (bb, dyc<VARIABLE_NAME> (in));
			break;

		case Variable_variable::ID:
			use_bottom (bb);
			break;

		default:
			assert (0);
			break;
	}
}

void
Live_variable_analysis::visit_assign_array (Statement_block* bb, MIR::Assign_array* in)
{
	use (bb, in->lhs); // may be defined, but we conservativly say it won't.
	use (bb, in->index);
	use (bb, in->rhs); // cant be defined
}

void
Live_variable_analysis::visit_assign_field (Statement_block* bb, MIR::Assign_field* in)
{
	if (isa<VARIABLE_NAME> (in->target))
		use (bb, dyc<VARIABLE_NAME> (in->target));

	// field_name should be ignored, but variable_field uses a var_name
	if (isa<Variable_field> (in->field_name))
		use (bb, dyc<Variable_field> (in->field_name)->variable_name);
}

void
Live_variable_analysis::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	def (bb, in->lhs);
	use_expr (bb, in->rhs);
}

void
Live_variable_analysis::visit_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in)
{
	// We don't know what variable is assigned, so we conservatively say none.
	use (bb, in->rhs);
}

void
Live_variable_analysis::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	use_expr (bb, in->expr);
}

void
Live_variable_analysis::visit_foreach_end (Statement_block* bb, MIR::Foreach_end* in)
{
	use (bb, in->array);
}

void
Live_variable_analysis::visit_foreach_next (Statement_block* bb, MIR::Foreach_next* in)
{
	use (bb, in->array);
}

void
Live_variable_analysis::visit_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in)
{
	use (bb, in->array);
}

void
Live_variable_analysis::visit_global (Statement_block* bb, MIR::Global* in)
{
	if (isa<VARIABLE_NAME> (in->variable_name))
		def (bb, dyc<VARIABLE_NAME> (in->variable_name));
	else
		use (bb, dyc<Variable_variable> (in->variable_name));
}

void
Live_variable_analysis::visit_pre_op (Statement_block* bb, MIR::Pre_op* in)
{
	use (bb, in->variable_name);
	// Technically, it is also DEF, but it makes no difference.
}

void
Live_variable_analysis::visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in)
{
	// Nothing used
}

void
Live_variable_analysis::visit_push_array (Statement_block* bb, MIR::Push_array* in)
{
	use (bb, in->lhs);
	use (bb, in->rhs);
}

void
Live_variable_analysis::visit_return (Statement_block* bb, MIR::Return* in)
{
	use (bb, in->variable_name);
}

void
Live_variable_analysis::visit_static_declaration (Statement_block* sb, MIR::Static_declaration*)
{
	// A defintion the first time the function is called: after that it isnt a use or a def. Do nothing.
}

void
Live_variable_analysis::visit_try (Statement_block* bb, MIR::Try*)
{
	use_bottom (bb);
}

void Live_variable_analysis::visit_throw (Statement_block* bb, MIR::Throw*)
{
	use_bottom (bb);
}

void
Live_variable_analysis::visit_unset (Statement_block* bb, MIR::Unset* in)
{
	foreach (Rvalue* index, *in->array_indices)
	{
		use (bb, index);
	}

	VARIABLE_NAME* var_name = dynamic_cast<VARIABLE_NAME*> (in->variable_name);

	// only unset ($x); defines $x
	if (in->target == NULL
		&& var_name
		&& in->array_indices->size () == 0)
	{
		def (bb, var_name); 
	}

	// unset ($x[0]); uses $x
	if (in->target == NULL
		&& var_name
		&& in->array_indices->size ())
	{
		use(bb, var_name);
	}

	// unset ($t->$x) uses $x
	if (in->target
		&& var_name == NULL)
	{
		use (bb, dyc<Variable_variable> (in->variable_name)->variable_name);
	}

	// unset	($t->x) uses $t
	if (in->target && isa<VARIABLE_NAME> (in->target))
	{
		use (bb, dyc<VARIABLE_NAME> (in->target));
	}

	// unset ($$x) can use anything, but doesn't define a particular variable.
	if (in->target == NULL
		&& var_name == NULL)
	{
		use_bottom (bb);
	}
}
