#include "Virtual_variable.h"
#include "process_mir/MIR_unparser.h"
#include "process_ir/General.h"
#include "optimize/Basic_block.h"

// Virtual variables for expressions and statements

// Some nodes get virtual, some dont. This fails for nodes which dont, and
// returns a copy of the appropriate virtual variable otherwise.

using namespace MIR;

VARIABLE_NAME*
get_virtual (Basic_block* bb, Node* in)
{
	if (bb->virtuals->has (in))
		return bb->virtuals->get (in);

	// For Expr
	switch (in->classid ())
	{
		case Actual_parameter::ID:
		case Assign_field::ID:
		case Assign_var::ID:
		case Assign_var_var::ID:
		case Attribute::ID:
		case Attr_mod::ID:
		case Bin_op::ID:
		case Branch::ID:
		case Cast::ID:
		case CAST::ID:
		case Catch::ID:
		case Class_alias::ID:
		case Class_def::ID:
		case Class_mod::ID:
		case CLASS_NAME::ID:
		case Constant::ID:
		case CONSTANT_NAME::ID:
		case Eval_expr::ID:
		case Field_access::ID:
		case FIELD_NAME::ID:
		case FOREIGN::ID:
		case Formal_parameter::ID:
		case Global::ID:
		case Goto::ID:
		case Instanceof::ID:
		case Interface_alias::ID:
		case Interface_def::ID:
		case INTERFACE_NAME::ID:
		case Isset::ID:
		case Label::ID:
		case LABEL_NAME::ID:
		case Method_alias::ID:
		case Method::ID:
		case Method_invocation::ID:
		case Method_mod::ID:
		case METHOD_NAME::ID:
		case Name_with_default::ID:
		case New::ID:
		case OP::ID:
		case PARAM_INDEX::ID:
		case Param_is_ref::ID:
		case PHP_script::ID:
		case Pre_op::ID:
		case Return::ID:
		case Signature::ID:
		case SSA_pre_op::ID:
		case Static_array_elem::ID:
		case Static_array::ID:
		case Static_declaration::ID:
		case Throw::ID:
		case Try::ID:
		case Type::ID:
		case Unary_op::ID:
		case Unset::ID:
		case Variable_class::ID:
		case Variable_field::ID:
		case Variable_method::ID:
		case Variable_variable::ID:
			phc_TODO ();

		/*
		 * These dont need virtuals
		 */
		case BOOL::ID:
		case INT::ID:
		case NIL::ID:
		case REAL::ID:
		case STRING::ID:
		case VARIABLE_NAME::ID:
			return NULL;

		/*
		 * Model arrays:
		 *		The aim is to make sure they all result in the same name when
		 *		unparsed.
		 */
		case Array_access::ID:
			in = new Array_access (dyc<Array_access> (in)->variable_name, NULL);
			break;

		case Assign_array::ID:
			in = new Array_access (dyc<Assign_array> (in)->lhs, NULL);
			break;

		case Assign_next::ID:
			in = new Array_access (dyc<Assign_next> (in)->lhs, NULL);
			break;

		case Foreach_end::ID:
			in = new Array_access (dyc<Foreach_end> (in)->array, NULL);
			break;

		case Foreach_get_key::ID:
			in = new Array_access (dyc<Foreach_get_key> (in)->array, NULL);
			break;

		case Foreach_get_val::ID:
			in = new Array_access (dyc<Foreach_get_val> (in)->array, NULL);
			break;

		case Foreach_has_key::ID:
			in = new Array_access (dyc<Foreach_has_key> (in)->array, NULL);
			break;

		case Foreach_next::ID:
			in = new Array_access (dyc<Foreach_next> (in)->array, NULL);
			break;

		case Foreach_reset::ID:
			in = new Array_access (dyc<Foreach_reset> (in)->array, NULL);
			break;


		
		// Just leave them. They'll always unparse the same way, and
		// shouldnt interact with other names.
		case HT_ITERATOR::ID:
			break;

			
	}

	stringstream ss;
	ss << "virt_" << unparse (in);
	VARIABLE_NAME* result = new VARIABLE_NAME (s (ss.str ()));
	result->is_virtual = true;

	(*bb->virtuals)[in] = result;

	return result;
}
