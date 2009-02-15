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


public:
	Whole_program(Pass_manager* pm);

	void run (MIR::PHP_script* in);
	void run (CFG* cfg){}

	void initialize ();
	bool analyses_have_converged ();

	/* 
	 * Creating and using analyses.
	 */
	void register_analysis (string name, WPA* analysis);

	void invoke_method (MIR::Method_invocation* in, Basic_block* context,
							  MIR::VARIABLE_NAME* lhs);

	Edge_list* get_branch_successors (Branch_block* bb);
	Method_info_list* get_possible_receivers (MIR::Method_invocation* in);



	void generate_summary (User_method_info* info);
	void merge_contexts (User_method_info* info);

	/* Optimizations on user-code */
	void apply_results (User_method_info* info);
	void annotate_results (User_method_info* info);
	void perform_local_optimizations (User_method_info* info);
	void perform_interprocedural_optimizations (User_method_info* info);

	void strip (MIR::PHP_script* in);

	// Apply the interprocedural optimization results to this BB.

	void analyse_method_info (Method_info* info,
									  Basic_block* caller,
									  MIR::Actual_parameter_list* actuals,
									  MIR::VARIABLE_NAME* lhs);

	void analyse_function (User_method_info* info,
								  Basic_block* caller,
								  MIR::Actual_parameter_list*,
								  MIR::VARIABLE_NAME* lhs);

	void analyse_summary (Summary_method_info* info,
								 Basic_block* caller,
							    MIR::Actual_parameter_list*,
								 MIR::VARIABLE_NAME* lhs);

	void apply_modelled_function (Method_info* info, Basic_block* caller);

	void init_superglobals (Entry_block* entry);

	/* Local analysis - calling other analyses */
	void dump (Basic_block* bb, string comment);


	/*
	 * Calls to the WPA modules.
	 */
	void forward_bind (Method_info* info,
							 Basic_block* caller,
							 Entry_block* entry,
							 MIR::Actual_parameter_list* actuals);

	void backward_bind (Method_info* info,
							  Basic_block* caller,
							  Exit_block* exit,
							  MIR::VARIABLE_NAME* lhs);

	// Performs points-to analysis, and call the other analyses with the
	// results. Returns true if a solution has changed, requiring this block
	// to be reanalysed.
	bool analyse_block (Basic_block* bb);

	// These functions describe the operation being performed in each block.
	// They pass the information to the Points-to graph, and to the other
	// analyses. The BB is to give a unique index to the results.
	void assign_scalar (Basic_block* bb, Path* lhs, MIR::Literal* lit);
	void assign_empty_array (Basic_block* bb, Path* lhs, string unique_name);
	void assign_by_ref (Basic_block* bb, Path* lhs, Path* rhs);
	void assign_by_copy (Basic_block* bb, Path* lhs, Path* rhs);
	void assign_unknown (Basic_block* bb, Path* lhs);
	void assign_unknown_typed (Basic_block* bb, Path* lhs, Types types);

	void record_use (Basic_block* bb, Index_node* node);

	void pull_results (Basic_block* bb);

	/*
	 * These might be considered to belong elsewhere, but each of them is
	 * tricky for some reason.
	 */

	// Get the list of potential values of node (can include '*' when it is
	// unknown).
	String_list* get_string_values (Basic_block* bb, Index_node* node);

	// PATH can refer to many nodes. Get the list of Index_nodes it points to.
	Index_node_list* get_named_indices (Basic_block* bb, Path* path, bool record_uses = false);

	// NULL if more than 1 exists
	Index_node* get_named_index (Basic_block* bb, Path* path, bool record_uses = false);



	/*
	 * Actually perform analysis
	 */
	void visit_branch_block (Branch_block*);

	void visit_assign_array (Statement_block*, MIR::Assign_array*);
	void visit_assign_field (Statement_block*, MIR::Assign_field *) { phc_TODO (); }
	void visit_assign_var (Statement_block*, MIR::Assign_var*);
	void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*) { phc_TODO (); }
	void visit_eval_expr (Statement_block*, MIR::Eval_expr*);
	void visit_foreach_end (Statement_block*, MIR::Foreach_end*) { phc_TODO (); }
	void visit_foreach_next (Statement_block*, MIR::Foreach_next*) { phc_TODO (); }
	void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*) { phc_TODO (); }
	void visit_global (Statement_block*, MIR::Global*);
	void visit_pre_op (Statement_block*, MIR::Pre_op*);
	void visit_assign_next (Statement_block*, MIR::Assign_next*) { phc_TODO (); }
	void visit_return (Statement_block*, MIR::Return*) { phc_TODO (); }
	void visit_static_declaration (Statement_block*, MIR::Static_declaration*) { phc_TODO (); }
	void visit_throw (Statement_block*, MIR::Throw*) { phc_TODO (); }
	void visit_try (Statement_block*, MIR::Try*) { phc_TODO (); }
	void visit_unset (Statement_block*, MIR::Unset*) { phc_TODO (); }

	// Interprocedural nodes
	void handle_method_invocation (Statement_block* bb, MIR::Method_invocation* in, MIR::VARIABLE_NAME* lhs);

	void handle_new (Statement_block* bb, MIR::New* in, MIR::VARIABLE_NAME* lhs);


	// Tricky bits
	void handle_bin_op (Statement_block* bb, Path* lhs, MIR::Bin_op* rhs);


};


#endif // PHC_WHOLE_PROGRAM
