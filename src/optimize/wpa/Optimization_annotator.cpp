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

#include "Optimization_annotator.h"


using namespace MIR;
using namespace boost;
using namespace std;

/*
 * Apply the optimization results.
 */
Optimization_annotator::Optimization_annotator (Whole_program* wp)
: wp (wp)
{
}

void
Optimization_annotator::run (CFG* cfg)
{
}

void
Optimization_annotator::visit_entry_block (Entry_block* bb)
{
	// We'd like to mark unused functions instead, to be on the safe side.
	// However, we don't analyse unused functions.

	// Some functions may be analysed, which are later marked as unused due to
	// inlining. In this case, we rely on Whole_program iterating to find that
	// out.
	bb->cfg->method->attrs->set_true ("phc.optimize.used");
}


void
Optimization_annotator::visit_assign_array (Statement_block* bb, MIR::Assign_array* in)
{
}

void
Optimization_annotator::visit_assign_field (Statement_block* bb, MIR::Assign_field * in)
{
}

void
Optimization_annotator::visit_assign_next (Statement_block* bb, MIR::Assign_next* in)
{
}

void
Optimization_annotator::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
}

void
Optimization_annotator::visit_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in)
{
}

void
Optimization_annotator::visit_catch (Statement_block* bb, MIR::Catch* in)
{
}

void
Optimization_annotator::visit_class_alias (Statement_block* bb, MIR::Class_alias* in)
{
}

void
Optimization_annotator::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
}

void
Optimization_annotator::visit_foreach_end (Statement_block* bb, MIR::Foreach_end* in)
{
}

void
Optimization_annotator::visit_foreach_next (Statement_block* bb, MIR::Foreach_next* in)
{
}

void
Optimization_annotator::visit_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in)
{
}

void
Optimization_annotator::visit_global (Statement_block* bb, MIR::Global* in)
{
}

void
Optimization_annotator::visit_interface_alias (Statement_block* bb, MIR::Interface_alias* in)
{
}

void
Optimization_annotator::visit_method_alias (Statement_block* bb, MIR::Method_alias* in)
{
}

void
Optimization_annotator::visit_pre_op (Statement_block* bb, MIR::Pre_op* in)
{
}

void
Optimization_annotator::visit_return (Statement_block* bb, MIR::Return* in)
{
}

void
Optimization_annotator::visit_static_declaration (Statement_block* bb, MIR::Static_declaration* in)
{
}

void
Optimization_annotator::visit_throw (Statement_block* bb, MIR::Throw* in)
{
}

void
Optimization_annotator::visit_try (Statement_block* bb, MIR::Try* in)
{
}

void
Optimization_annotator::visit_unset (Statement_block* bb, MIR::Unset* in)
{
}


void
Optimization_annotator::visit_array_access (Statement_block* bb, MIR::Array_access* in)
{
}

void
Optimization_annotator::visit_array_next (Statement_block* bb, MIR::Array_next* in)
{
}

void
Optimization_annotator::visit_bin_op (Statement_block* bb, MIR::Bin_op* in)
{
}

void
Optimization_annotator::visit_bool (Statement_block* bb, MIR::BOOL* in)
{
}

void
Optimization_annotator::visit_cast (Statement_block* bb, MIR::Cast* in)
{
}

void
Optimization_annotator::visit_constant (Statement_block* bb, MIR::Constant* in)
{
}

void
Optimization_annotator::visit_field_access (Statement_block* bb, MIR::Field_access* in)
{
}

void
Optimization_annotator::visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in)
{
}

void
Optimization_annotator::visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in)
{
}

void
Optimization_annotator::visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in)
{
}

void
Optimization_annotator::visit_instanceof (Statement_block* bb, MIR::Instanceof* in)
{
}

void
Optimization_annotator::visit_int (Statement_block* bb, MIR::INT* in)
{
}

void
Optimization_annotator::visit_isset (Statement_block* bb, MIR::Isset* in)
{
}


void
Optimization_annotator::visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in)
{
}

void
Optimization_annotator::visit_new (Statement_block* bb, MIR::New* in)
{
}

void
Optimization_annotator::visit_nil (Statement_block* bb, MIR::NIL* in)
{
}

void
Optimization_annotator::visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in)
{
}

void
Optimization_annotator::visit_real (Statement_block* bb, MIR::REAL* in)
{
}

void
Optimization_annotator::visit_string (Statement_block* bb, MIR::STRING* in)
{
}

void
Optimization_annotator::visit_unary_op (Statement_block* bb, MIR::Unary_op* in)
{
}

void
Optimization_annotator::visit_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in)
{
}

void
Optimization_annotator::visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in)
{
}
