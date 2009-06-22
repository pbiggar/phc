/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * 
 * */

#include "Aliasing.h"
#include "Points_to.h"
#include "Whole_program.h"

#include "Stat_collector.h"

#include <iostream>


using namespace MIR;
using namespace boost;
using namespace std;


Stat_collector::Stat_collector (Whole_program* wp)
: wp (wp)
{		
}

void
Stat_collector::run (CFG* cfg)
{
}

void
Stat_collector::visit_basic_block (Basic_block* bb)
{
}

void
Stat_collector::visit_statement_block (Statement_block* bb)
{

}

void
Stat_collector::visit_entry_block (Entry_block* bb)
{
}


void
Stat_collector::visit_assign_array (Statement_block* bb, MIR::Assign_array* in)
{
	visit_expr(bb,in->rhs);

	collect_type_stats(bb,in->lhs,"types_assign_array");
	collect_type_stats(bb,in->index,"types_array_index");

}

void
Stat_collector::visit_assign_field (Statement_block* bb, MIR::Assign_field * in)
{
}

void
Stat_collector::visit_assign_next (Statement_block* bb, MIR::Assign_next* in)
{
	collect_type_stats (bb, in->lhs, "types_assign_next");
}

void
Stat_collector::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	last_assignment_lhs = *in->lhs->value;
	visit_expr(bb,in->rhs);

	collect_type_stats(bb,in->lhs,"types_assign_var");

	string s = "Assignments to "+last_assignment_lhs;
	CTS(s);
}

void
Stat_collector::visit_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in)
{
	visit_expr(bb,in->rhs);

	collect_type_stats(bb,in->lhs,"types_assign_var_var");
}

void
Stat_collector::visit_catch (Statement_block* bb, MIR::Catch* in)
{
}

void
Stat_collector::visit_class_alias (Statement_block* bb, MIR::Class_alias* in)
{
}

void
Stat_collector::visit_eval_expr (Statement_block* bb, MIR::Eval_expr* in)
{
	visit_expr (bb,in->expr);
}

void
Stat_collector::visit_foreach_end (Statement_block* bb, MIR::Foreach_end* in)
{
	collect_type_stats (bb,in->array,"types_foreach_array");
}

void
Stat_collector::visit_foreach_next (Statement_block* bb, MIR::Foreach_next* in)
{
	collect_type_stats (bb,in->array,"types_foreach_array");
}

void
Stat_collector::visit_foreach_reset (Statement_block* bb, MIR::Foreach_reset* in)
{
	collect_type_stats (bb,in->array,"types_foreach_array");
}

void
Stat_collector::visit_global (Statement_block* bb, MIR::Global* in)
{
}

void
Stat_collector::visit_interface_alias (Statement_block* bb, MIR::Interface_alias* in)
{
}

void
Stat_collector::visit_method_alias (Statement_block* bb, MIR::Method_alias* in)
{
}

void
Stat_collector::visit_pre_op (Statement_block* bb, MIR::Pre_op* in)
{
		collect_type_stats (bb, in->variable_name, "types_pre_op_var");
}

void
Stat_collector::visit_return (Statement_block* bb, MIR::Return* in)
{
	collect_type_stats (bb, in->rvalue, "types_return");
}

void
Stat_collector::visit_static_declaration (Statement_block* bb, MIR::Static_declaration* in)
{
}

void
Stat_collector::visit_throw (Statement_block* bb, MIR::Throw* in)
{
}

void
Stat_collector::visit_try (Statement_block* bb, MIR::Try* in)
{
}

void
Stat_collector::visit_unset (Statement_block* bb, MIR::Unset* in)
{
//	collect_type_stats (bb, in->variable_name, "types_unset_var");
}

void
Stat_collector::visit_array_access (Statement_block* bb, MIR::Array_access* in)
{
		collect_type_stats (bb, in->variable_name, "types_array_access");
		collect_type_stats (bb, in->index, "types_array_index");

}

void
Stat_collector::visit_array_next (Statement_block* bb, MIR::Array_next* in)
{
	phc_TODO ();
}

void
Stat_collector::visit_bin_op (Statement_block* bb, MIR::Bin_op* in)
{

	collect_type_stats (bb, in->left, "types_bin_op_lhs");
	collect_type_stats (bb, in->right, "types_bin_op_rhs");

}

void
Stat_collector::visit_bool (Statement_block* bb, MIR::BOOL* in)
{
/*	if (!CTS(last_assignment_lhs+" assigned to BOOL"))
	{
		CTS ("Number of types assigned to "+last_assignment_lhs);
	}
*/}

void
Stat_collector::visit_cast (Statement_block* bb, MIR::Cast* in)
{
}

void
Stat_collector::visit_constant (Statement_block* bb, MIR::Constant* in)
{
}

void
Stat_collector::visit_field_access (Statement_block* bb, MIR::Field_access* in)
{
}

void
Stat_collector::visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in)
{
}

void
Stat_collector::visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in)
{
}

void
Stat_collector::visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in)
{
}

void
Stat_collector::visit_instanceof (Statement_block* bb, MIR::Instanceof* in)
{
}

void
Stat_collector::visit_int (Statement_block* bb, MIR::INT* in)
{
/*	if(! CTS (last_assignment_lhs+" assigned to INT"))
	{
		CTS ("Number of types assigned to "+last_assignment_lhs);
	}
*/}

void
Stat_collector::visit_isset (Statement_block* bb, MIR::Isset* in)
{
}


void
Stat_collector::visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in)
{

	foreach (Actual_parameter* param, *in->actual_parameters)
	{
		collect_type_stats (bb,param->rvalue,"types_method_parameter");
	}
}

void
Stat_collector::visit_new (Statement_block* bb, MIR::New* in)
{
}

void
Stat_collector::visit_nil (Statement_block* bb, MIR::NIL* in)
{
}

void
Stat_collector::visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in)
{
}

void
Stat_collector::visit_real (Statement_block* bb, MIR::REAL* in)
{
/*	if (!CTS (last_assignment_lhs+" assigned to REAL"))
	{
		CTS ("Number of types assigned to "+last_assignment_lhs);
	}
*/}

void
Stat_collector::visit_string (Statement_block* bb, MIR::STRING* in)
{
/*	if (!CTS (last_assignment_lhs+" assigned to STRING"))
	{
		CTS ("Number of types assigned to "+last_assignment_lhs);
	}
*/}

void
Stat_collector::visit_unary_op (Statement_block* bb, MIR::Unary_op* in)
{
	collect_type_stats (bb, in->variable_name, "types_unary_op_var");
}

void
Stat_collector::visit_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in)
{

}

void
Stat_collector::visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in)
{

}

void
Stat_collector::collect_type_stats (Basic_block* bb, MIR::Rvalue* rval,string statname )
{
	Abstract_value* absval = wp->get_abstract_value (Context::non_contextual (bb), R_OUT, rval);
	if (absval->types)
	{
		foreach (string type, *absval->types)
		{
			add_to_stringset_stat (statname,type);	
		}
	}
}

