/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Perform a number of whole-program analyses simulteneously.
 */

/*
 * This is the basis for simulatenous optimizations. It seems that we need
 * alias analysis to do type-inference, and type-inference for alias
 * analysis.  On top of this, we would get more precise results if we did the
 * analysis conditionally (or symbolically - aka evaluating constants and
 * branches).  Additionally, we can use this to model global state, including
 * include_path, the error_reporting level, defined functions, classes and
 * constants, etc.
 *
 * The analysis starts in main, and each statement is symbolically executed
 * (referred heretofore as evaluated) by each analyser before the next
 * statement is evaluated. When another function is called, it propagates the
 * current results (or global results for global state) into the callee, and
 * the callee is the evaluated, before returning to the caller. Once the
 * entire program is evaluated in this manner, we will have complete results,
 * including a callgraph and types. Then other analyses who merely consume
 * this information can run, and annotated things for the code generator.
 *
 * The analysis will proceed conditionally, in the sense of CCP, which means
 * that it will evaluate a conditional, and only proceed down 1 path if we
 * are able to evaluate it. Passes will be passed a clone of the statement,
 * and so can update it if they wish. The statement will be passed to each
 * analysis until it fix-points.
 *
 * The analyses will have to each other, so that we can get a type if
 * required for callgraph resolution, etc.
 *
 */

#ifndef PHC_WHOLE_PROGRAM
#define PHC_WHOLE_PROGRAM

#include "lib/Map.h"
#include "WPA.h"

DECL(Method_info);
DECL(Index_node);
DECL(Reference);

class CFG;
class Basic_block;

class Aliasing;
class Callgraph;
class CCP;
class Constant_state;
class Def_use;
class Include_analysis;
class Optimization_transformer;
class Optimization_annotator;
class Pass_manager;
class Path;
class Type_inference;
class VRP;
class WPA;


// This gets used everywhere.
#define foreach_wpa(WP)					\
	foreach (WPA* wpa, WP->analyses)

typedef enum _Indexing_flags
{
	NO_FLAGS = 0x0,
	RECORD_USES = 0x1,
	IMPLICIT_CONVERSION = 0x2,
} Indexing_flags;


class Whole_program : public CFG_visitor
{
	// Previous iteration - stored for analyses_have_reached_fix_point
	List<WPA*> old_analyses;

public:

	List<WPA*> analyses;

	Pass_manager* pm;

	Optimization_transformer* transformer;
	Optimization_annotator* annotator;

	// Analyses should be able to reach in here to get other analyses'
	// results.
	Aliasing* aliasing;
	CCP* ccp;
	Def_use* def_use;
	Callgraph* callgraph;
	Type_inference* type_inf;

	// For assignments
	Path* saved_plhs;
	MIR::VARIABLE_NAME* saved_lhs;
	bool saved_is_ref;

	// name of __MAIN__ scope
	string main_scope;


public:
	Whole_program(Pass_manager* pm);

	void run (MIR::PHP_script* in);
	void run (CFG* cfg){phc_unreachable ();}

	void initialize ();
	bool analyses_have_converged ();

	/* 
	 * Creating and using analyses.
	 */
	void register_analysis (string name, WPA* analysis);

	void invoke_method (MIR::Method_invocation* in,
							  Context caller_cx,
							  MIR::VARIABLE_NAME* lhs);

	Method_info_list* get_possible_receivers (MIR::Target*, MIR::Method_name*);
	Method_info_list* get_possible_receivers (MIR::Param_is_ref*);
	Method_info_list* get_possible_receivers (MIR::Method_invocation*);

	void generate_summary (User_method_info* info);

	void merge_contexts ();

	/* Optimizations on user-code */
	void apply_results (User_method_info* info);
	void annotate_results (User_method_info* info);
	void perform_local_optimizations (User_method_info* info);
	void perform_interprocedural_optimizations (User_method_info* info);

	void strip (MIR::PHP_script* in);

	// Apply the interprocedural optimization results to this BB.

	void analyse_method_info (Method_info* info,
									  Context caller_cx,
									  MIR::Actual_parameter_list* actuals,
									  MIR::VARIABLE_NAME* lhs);

	void analyse_function (User_method_info* info,
								  Context caller_cx,
								  MIR::Actual_parameter_list*,
								  MIR::VARIABLE_NAME* lhs);

	void analyse_summary (Summary_method_info* info,
								 Context caller_cx,
							    MIR::Actual_parameter_list*,
								 MIR::VARIABLE_NAME* lhs);

	void apply_modelled_function (Summary_method_info* info, Context cx);

	void init_superglobals (Context cx);

	/* Local analysis - calling other analyses */
	void dump (Context cx, string comment);


	/*
	 * Calls to the WPA modules.
	 */
	void forward_bind (Method_info* info,
							 Context entry_cx,
							 MIR::Actual_parameter_list* actuals);

	void backward_bind (Method_info* info,
							  Context entry_cx,
							  MIR::VARIABLE_NAME* lhs);

	// Performs points-to analysis, and call the other analyses with the
	// results. Returns true if a solution has changed, requiring this block
	// to be reanalysed.
	bool analyse_block (Context cx);

	// These functions describe the operation being performed in each block.
	// They pass the information to the Points-to graph, and to the other
	// analyses. The BB is to give a unique index to the results.
	void assign_scalar (Context cx, Path* lhs, MIR::Literal* lit);
	void assign_unknown (Context cx, Path* lhs);
	void assign_typed (Context cx, Path* lhs, Types types);
	void assign_empty_array (Context cx, Path* lhs, string name);
	void assign_by_ref (Context cx, Path* lhs, Path* rhs);
	void assign_by_copy (Context cx, Path* lhs, Path* rhs);

	// Copy the value from RHS to LHS.
	void copy_value (Context cx, Index_node* lhs, Index_node* rhs);

	bool copy_from_abstract_value (Context cx, Index_node* lhs, Index_node* rhs);

	void record_use (Context cx, Index_node* node);

	void pull_results (Context cx);

	// Most pesimistic case
	void ruin_everything (Context cx, Path* path);


	/*
	 * These might be considered to belong elsewhere, but each of them is
	 * tricky for some reason.
	 */

	Edge_list* get_successors (Context cx);

	// Get the list of potential values of node (can include '*' when it is
	// unknown).
	String_list* get_string_values (Context cx, Index_node* node);

	Abstract_value* get_abstract_value (Context cx, Alias_name name);

	// Get all the possible names, and merge them.
	Abstract_value* get_abstract_value (Context cx, MIR::Rvalue* rval);

	// Special case, get the output value, not the input
	Abstract_value* get_bb_out_abstract_value (Context cx, Alias_name name);

	// PATH can refer to many nodes. Get the list of Index_nodes it points to.
	Index_node_list* get_named_indices (Context cx, Path* path, Indexing_flags flags = NO_FLAGS);

	// NULL if more than 1 exists
	Index_node* get_named_index (Context cx, Path* path, Indexing_flags flags = NO_FLAGS);


	// Get anything the path can point to, and all nodes that they may reference.
	Reference_list* get_all_referenced_names (Context cx, Path* path, Indexing_flags flags = NO_FLAGS);


	/*
	 * Actually perform analysis
	 */

	Context block_cx;

	void visit_branch_block (Branch_block*);

	void visit_assign_array (Statement_block*, MIR::Assign_array*);
	void visit_assign_field (Statement_block*, MIR::Assign_field *);
	void visit_assign_var (Statement_block*, MIR::Assign_var*);
	void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*);
	void visit_eval_expr (Statement_block*, MIR::Eval_expr*);
	void visit_foreach_end (Statement_block*, MIR::Foreach_end*);
	void visit_foreach_next (Statement_block*, MIR::Foreach_next*);
	void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*);
	void visit_global (Statement_block*, MIR::Global*);
	void visit_pre_op (Statement_block*, MIR::Pre_op*);
	void visit_assign_next (Statement_block*, MIR::Assign_next*);
	void visit_return (Statement_block*, MIR::Return*);
	void visit_static_declaration (Statement_block*, MIR::Static_declaration*);
	void visit_throw (Statement_block*, MIR::Throw*);
	void visit_try (Statement_block*, MIR::Try*);
	void visit_unset (Statement_block*, MIR::Unset*);

	void visit_array_access (Statement_block* bb, MIR::Array_access* in);
	void visit_bin_op (Statement_block* bb, MIR::Bin_op* in);
	void visit_cast (Statement_block* bb, MIR::Cast* in);
	void visit_constant (Statement_block* bb, MIR::Constant* in);
	void visit_field_access (Statement_block* bb, MIR::Field_access* in);
	void visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in);
	void visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in);
	void visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in);
	void visit_instanceof (Statement_block* bb, MIR::Instanceof* in);
	void visit_isset (Statement_block* bb, MIR::Isset* in);
	void visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in);
	void visit_new (Statement_block* bb, MIR::New* in);
	void visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in);
	void visit_unary_op (Statement_block* bb, MIR::Unary_op* in);
	void visit_variable_name (Statement_block* bb, MIR::VARIABLE_NAME* in);
	void visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in);
};


#endif // PHC_WHOLE_PROGRAM
