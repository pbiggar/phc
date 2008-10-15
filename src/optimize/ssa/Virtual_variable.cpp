#include "Virtual_variable.h"
#include "process_mir/MIR_unparser.h"
#include "process_ir/General.h"

// Virtual variables for expressions and statements

// Some nodes get virtual, some dont. This fails for nodes which dont, and
// returns a copy of the appropriate virtual variable otherwise.

using namespace MIR;

VARIABLE_NAME*
get_virtual (Node* in)
{
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
		case BOOL::ID:
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
		case Foreach_end::ID:
		case Foreach_get_key::ID:
		case Foreach_get_val::ID:
		case Foreach_has_key::ID:
		case Foreach_next::ID:
		case Foreach_reset::ID:
		case FOREIGN::ID:
		case Formal_parameter::ID:
		case Global::ID:
		case Goto::ID:
		case HT_ITERATOR::ID:
		case Instanceof::ID:
		case Interface_alias::ID:
		case Interface_def::ID:
		case INTERFACE_NAME::ID:
		case INT::ID:
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
		case NIL::ID:
		case OP::ID:
		case PARAM_INDEX::ID:
		case Param_is_ref::ID:
		case PHP_script::ID:
		case Pre_op::ID:
		case Assign_next::ID:
		case REAL::ID:
		case Return::ID:
		case Signature::ID:
		case SSA_pre_op::ID:
		case Static_array_elem::ID:
		case Static_array::ID:
		case Static_declaration::ID:
		case STRING::ID:
		case Throw::ID:
		case Try::ID:
		case Type::ID:
		case Unary_op::ID:
		case Unset::ID:
		case Variable_class::ID:
		case Variable_field::ID:
		case Variable_method::ID:
		case VARIABLE_NAME::ID:
		case Variable_variable::ID:
			phc_unreachable ();

		case Array_access::ID:
			in = new Array_access (dyc<Array_access> (in)->variable_name, NULL);
			break;

		case Assign_array::ID:
		{
			Assign_array *aa = dyc<Assign_array> (in);
			in = new Array_access (aa->lhs, NULL);
			break;
		}
	}

	stringstream ss;
	ss << "virt_" << unparse (in);
	VARIABLE_NAME* result = new VARIABLE_NAME (s (ss.str ()));
	result->is_virtual = true;
	return result;
}
