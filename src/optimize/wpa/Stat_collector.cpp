/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * 
 * */
 
#include "Whole_program.h"
#include "../CFG.h"
#include "../Def_use_web.h"
#include "Def_use.h"
#include "../ssa/HSSA.h"
#include "Callgraph.h"
#include "Aliasing.h"
#include "lib/demangle.h"
#include "lib/Set.h"

#include "Stat_collector.h"

#include <iostream>


using namespace MIR;
using namespace boost;
using namespace std;

Stat_collector::Stat_collector()
{}

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
	inc_stat("total_num_bbs");

}

void
Stat_collector::visit_statement_block (Statement_block* bb)
{
	Context* cx = Context::non_contextual (bb);
	CTS ("num_statement_blocks");
	Get_var_name* gvn = new Get_var_name ();

	bb->statement->visit (gvn);

	foreach (MIR::VARIABLE_NAME* varname, gvn->var_names)
	{
		if (!get_stringset_stat ("total_num_unique_vars")->has (*varname->value))
		{
			add_to_stringset_stat ("total_num_unique_vars", *varname->value);
		}
		
		const Types * types = wp->get_abstract_value (cx, R_OUT, varname)->types;
		
		foreach (string t, *types)
			types_per_var[*varname->value].insert (t);


		CTS ("total_num_vars");

		int m = wp->aliasing->get_references (cx, R_IN, new Index_node (cx->symtable_name (), *varname->value), PTG_ALL)->size ();

		if (m > peak_aliases[*varname->value])
			peak_aliases[*varname->value] = m;
	}
}

void
Stat_collector::visit_entry_block (Entry_block* bb)
{
}


void
Stat_collector::visit_assign_array (Statement_block* bb, MIR::Assign_array* in)
{
		
	visit_expr(bb,in->rhs);
	
	if (wp->get_abstract_value (Context::non_contextual (bb), R_IN, in->lhs)->types->has ("unset"))
	{
		CTS ("num_implicit_array_defs");		
		CTS ("num_array_def_sites");	
	}

	CTS ("num_assign_array");
	collect_type_stats(bb, in->rhs,"types_assign_array");
	collect_type_stats(bb, in->index,"types_array_index");

	collect_deref_stats (bb, in->lhs, "writes", "Assign_array");
}

void
Stat_collector::visit_assign_field (Statement_block* bb, MIR::Assign_field * in)
{
	visit_expr(bb,in->rhs);
	VARIABLE_NAME* varname = dynamic_cast<VARIABLE_NAME*> (in->target);
	if (varname!=NULL)
	{
		if (wp->get_abstract_value (Context::non_contextual (bb), R_IN, varname)->types->has ("unset"))
			CTS ("num_implicit_object_defs");
		
		collect_deref_stats (bb, varname, "writes", "Assign_field");
	}
}

void
Stat_collector::visit_assign_next (Statement_block* bb, MIR::Assign_next* in)
{
	CTS ("num_assign_next");
	collect_type_stats (bb, in->lhs, "types_assign_next");
}

void
Stat_collector::visit_assign_var (Statement_block* bb, MIR::Assign_var* in)
{
	last_assignment_lhs = in->lhs;
	visit_expr(bb,in->rhs);
	last_assignment_lhs = NULL;	
	
	if (in->is_ref && isa<MIR::Array_access> (in->rhs))
	{
		if (wp->get_abstract_value (Context::non_contextual (bb), R_IN, in->lhs)->types->has ("unset"))
		{	
			CTS ("num_implicit_array_defs");
			CTS ("num_array_def_sites");
		}
	}	
	else
	{
		if (wp->get_abstract_value (Context::non_contextual (bb), R_OUT, in->lhs)->types->has ("array"))
			CTS ("num_array_def_sites");
	}

	MIR::Field_access* fa;
	MIR::VARIABLE_NAME* vn;
	if (in->is_ref && (fa = dynamic_cast<MIR::Field_access*> (in->rhs)))
	{
		if (vn = dynamic_cast<MIR::VARIABLE_NAME*> (fa->target))
		{
			if (wp->get_abstract_value (Context::non_contextual (bb), R_IN, vn)->types->has ("unset"))
				CTS ("num_implicit_object_defs");
		}
	}

	collect_type_stats(bb,in->lhs,"types_assign_var");
	CTS ("num_assign_var");
}

void
Stat_collector::visit_assign_var_var (Statement_block* bb, MIR::Assign_var_var* in)
{
	visit_expr(bb,in->rhs);

	collect_type_stats(bb,in->lhs,"types_assign_var_var");
	CTS ("num_assign_var_var");
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
	CTS ("num_pre_op_var");
}

void
Stat_collector::visit_return (Statement_block* bb, MIR::Return* in)
{
	collect_type_stats (bb, in->rvalue, "types_return");
	CTS ("num_return");
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
}

void
Stat_collector::visit_array_access (Statement_block* bb, MIR::Array_access* in)
{
	collect_type_stats (bb, in->variable_name, "types_array_access");
	collect_type_stats (bb, in->index, "types_array_index");
	CTS ("num_array_access");
	collect_deref_stats (bb, in->variable_name, "reads", "Array_access");
}

void
Stat_collector::visit_array_next (Statement_block* bb, MIR::Array_next* in)
{

}

void
Stat_collector::visit_bin_op (Statement_block* bb, MIR::Bin_op* in)
{

	collect_type_stats (bb, in->left, "types_bin_op_lhs");
	collect_type_stats (bb, in->right, "types_bin_op_rhs");
	CTS ("num_bin_op_lhs");
}

void
Stat_collector::visit_bool (Statement_block* bb, MIR::BOOL* in)
{
}

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
	MIR::VARIABLE_NAME* varname = dynamic_cast<VARIABLE_NAME*> (in->target);
	if (varname)
		collect_deref_stats (bb, varname, "reads", "Field_access");	
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
}

void
Stat_collector::visit_isset (Statement_block* bb, MIR::Isset* in)
{
}

void
Stat_collector::visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in)
{
	string meth_func = "function";
	MIR::VARIABLE_NAME* varname;
	if (varname = dynamic_cast<VARIABLE_NAME*> (in->target))
		meth_func = "method";

	CTS (meth_func + "_call_sites");	
	
	Method_info_list* minfolist = wp->get_possible_receivers (Context::non_contextual(bb),R_OUT,in);
	int n = minfolist->size ();	
	
	CTS (meth_func + "s_with_" + lexical_cast<string> (n) + "_receivers");

	if (minfolist->size () == 1)
	{
		 User_method_info* info = dynamic_cast<User_method_info*> (minfolist->front ());
		 if (info != NULL)
		 {	
			 if (info->get_method ()->statements->size () == 0 || 
					 info->get_method ()->statements->size () == 1 
					 && info->get_method ()->statements->at (0)->classid () == Return::ID)			
			 {
				 CTS ("num_inlinable_" + meth_func + "s");
			 }
		 }	
	}
			
	foreach (Actual_parameter* param, *in->actual_parameters)
	{
		collect_type_stats (bb,param->rvalue,"types_" + meth_func + "_parameter");
		CTS ("num_" + meth_func + "_parameter");
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
}

void
Stat_collector::visit_string (Statement_block* bb, MIR::STRING* in)
{
}

void
Stat_collector::visit_unary_op (Statement_block* bb, MIR::Unary_op* in)
{
	collect_type_stats (bb, in->variable_name, "types_unary_op_var");
	CTS ("num_unary_op_var");
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
Stat_collector::collect_type_stats (Basic_block* bb, MIR::Rvalue* rval,string statname)
{
	const Abstract_value* absval = wp->get_abstract_value (Context::non_contextual (bb), R_OUT, rval);
	if (absval->types)
	{
		foreach (string type, *absval->types)
		{
			CTS (statname);
		}
	}
}

void 
Stat_collector::get_number_of_statements (CFG* cfg, string beforeafter)
{
	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
	
		if ((dynamic_cast<Statement_block*> (bb)))
		{
			CTS ("num_statements_" + beforeafter);
		}
		if (isa<Branch_block> (bb))
			CTS ("num_branches_"+beforeafter);
	}	
}

void 
Stat_collector::collect_def_use_stats (CFG* cfg)
{
	int starred, unstarred;

	Def_use* du = wp->def_use;
	if (cfg->duw)
		du = cfg->duw->get_def_use ();

	starred = du->get_num_vals (cfg, DEF, false);
	unstarred = du->get_num_refs (cfg, DEF, false);
	set_stat ("starred_defs", starred);
	set_stat ("unstarred_defs", unstarred);
	set_stat ("defs", starred + unstarred);

 	starred = du->get_num_vals (cfg, USE, false);
	unstarred = du->get_num_refs (cfg, USE, false);
	set_stat ("starred_uses", starred);
	set_stat ("unstarred_uses", unstarred);
	set_stat ("uses", starred + unstarred);

	starred = du->get_num_vals (cfg, MAYDEF, false);
	unstarred = du->get_num_refs (cfg, MAYDEF, false);
	set_stat ("starred_may_defs", starred);
	set_stat ("unstarred_may_defs", unstarred);
	set_stat ("may_defs", starred + unstarred);

	foreach (Basic_block* bb, *cfg->get_all_bbs ())
	{
		if (!((dynamic_cast<Entry_block*> (bb)) || (dynamic_cast<Exit_block*> (bb))))
		{
			foreach (const Alias_name* def, *du->get_defs (bb))
			{
				add_to_stringset_stat ("initialised_vars", def->str ());
				if (def->str ()[0] == '*')
					add_to_stringset_stat("starred_initialised_vars", def->str ());
			}
		}
	}
}

void
Stat_collector::collect_method_stats ()
{
	int num_functions = filter_types<User_method_info> (Oracle::get_all_methods())->size ();
	int num_classes = 0;
	foreach (User_class_info* cinf, *filter_types<User_class_info> (Oracle::get_all_classes ()))
	{
		num_functions += cinf->get_methods ()->size ();	
		num_classes++;
	}

	set_stat ("total_num_methods/functions", num_functions);
	set_stat ("num_unreachable_methods/functions", num_functions - filter_types<User_method_info> (wp->callgraph->get_called_methods ())->size ());

	set_stat ("total_classes_used", wp->callgraph->get_used_classes ()->size ());
	set_stat ("num_unreachable_classes", num_classes - wp->callgraph->get_used_classes ()->size ());
}

void
Stat_collector::collect_alias_analysis_stats ()
{
	set_stat ("num_field_edges", wp->aliasing->get_total_num_field_edges ());
	set_stat ("num_points_to_edges", wp->aliasing->get_total_num_points_to_edges ());
	int poss_ref_edges = wp->aliasing->get_num_possible_reference_edges ();
	int def_ref_edges = wp->aliasing->get_num_definite_reference_edges ();
	set_stat ("num_possible_reference_edges", poss_ref_edges);
	set_stat ("num_definite_reference_edges", def_ref_edges);
	set_stat ("num_reference_edges", poss_ref_edges + def_ref_edges);
}
 
void 
Stat_collector::collect_deref_stats (Basic_block* bb, MIR::VARIABLE_NAME* in, string read_write, string node_type)
{
	Context* cx = Context::non_contextual (bb);
	
	Set<string> temp;	

	Path* p = P (cx->symtable_name (), in);
	
	foreach (const Index_node* index, *wp->get_named_indices (cx, R_IN, p, true))
	{
		cStorage_node_list* snl = wp->aliasing->get_points_to (cx, R_IN, index);
		foreach (const Storage_node* sn, *snl)
			temp.insert (sn->str ());
	}
	CTS ("IR_Nodes_dereferenced_" + read_write + "_" +  node_type);
	if (temp.size () > 0)	
		CTS ("storage_nodes_deref_" + read_write + "_" + node_type);		
	foreach (string s, temp)
		CTS ("storage_nodes_deref_" + read_write + "_" + node_type);		
}

void 
Stat_collector::register_type_stats ()
{
	int n;
	string s;
	foreach (tie (s, n), peak_aliases)
	{
			CTS ("vars_with_" + lexical_cast<string> (n) + "_aliases");
	}

	peak_aliases.clear ();

	Set<string> ss;
	foreach (tie (s, ss), types_per_var)
	{
		CTS ("num_vars_" + lexical_cast<string> (ss.size ()) + "_types");
	}

	types_per_var.clear ();
} 
