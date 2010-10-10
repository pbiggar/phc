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
class Constant_state;
class Def_use;
class Include_analysis;
class Value_analysis;
class VRP;

class Optimization_transformer;
class Optimization_annotator;
class Stat_collector;
class Pass_manager;
class Path;
class WPA;
class Absval_cell;

/*
 * Intended to be used as FWPA->whatever ();
 */

// This gets used everywhere.
#define foreach_wpa(WP)		foreach (WPA* wpa, WP->analyses)

#define FWPA	 foreach (WPA* wpa, this->analyses) wpa

class Whole_program : public CFG_visitor
{
	// Previous iteration - stored for analyses_have_reached_fix_point
	List<WPA*> old_analyses;

public:

	List<WPA*> analyses;

	Pass_manager* pm;

	Optimization_transformer* transformer;
	Optimization_annotator* annotator;
	Stat_collector* stat_coll;

	// Analyses should be able to reach in here to get other analyses'
	// results.
	Aliasing* aliasing;
	Callgraph* callgraph;
	Constant_state* constants;
	Def_use* def_use;
	Value_analysis* values;

	// name of __MAIN__ scope
	string main_scope;

	/*
	 * Special shortcut to mark the successor of die() and exit() as non-executable
	 */
	bool skip_after_die;

	/*
	 * When copying data, we dont want to collapse stuff into a single
	 * array/object. This is used for new objects and arrays, but also for fake
	 * nodes used for copying.
	 *
	 * If we handle these numbers incorrectly, the analysis will never converge.
	 * If we keep counting forever, the arrays will have different names
	 * everytime. We must instead start from zero in each basic block being
	 * analysed.
	 */
	int unique_count ();

	/*
	 * Stacks for every block
	 */
	Stack<int> unique_counts;

	/*
	 * Empty storage counts.
	 */
	CX_map<int> storage_counts;

	// Keep track of newly created empty storage nodes
	// for the whole system and for each basic block.
	int next_storage_count, block_storage_count;
	int get_storage_count(Context *ctx);

	/*
	 * Block contexts.
	 */
	Stack<Context*> block_cxs;
	Context* block_cx ();

	/*
	 * Stacks for assignments
	 */
	Stack<Path*> saved_plhss;
	Stack<MIR::VARIABLE_NAME*> saved_lhss;
	Stack<bool> saved_is_refs;

	Path* saved_plhs ();
	MIR::VARIABLE_NAME* saved_lhs ();
	bool saved_is_ref ();

	void init_stacks ();
	void finish_stacks ();


public:
	Whole_program(Pass_manager* pm);

	void run (MIR::PHP_script* in);
	void run (CFG* cfg){phc_unreachable ();}

	void initialize (Context* cx);
	bool analyses_have_converged ();

	/* 
	 * Creating and using analyses.
	 */
	void register_analysis (string name, WPA* analysis);

	void invoke_method (Context* caller_cx,
							  MIR::VARIABLE_NAME* lhs,
							  MIR::Method_invocation* in);

	void invoke_method (Context* caller_cx,
							  MIR::VARIABLE_NAME* lhs,
							  MIR::VARIABLE_NAME* target,
							  Method_info_list* receivers,
							  MIR::Actual_parameter_list* params);

	void instantiate_object (	Context* caller_cx,
										MIR::VARIABLE_NAME* self,
										MIR::New* in);

	void generate_summary (User_method_info* info);

	void merge_contexts ();

	// Optimizations on user-code
	void apply_results (User_method_info* info);
	void annotate_results (User_method_info* info);
	void perform_local_optimizations (User_method_info* info);
	void perform_interprocedural_optimizations (User_method_info* info);
	void collect_stats (User_method_info* info);
	void collect_preliminary_stats (User_method_info* info);
	void strip (MIR::PHP_script* in);


	// Apply the interprocedural optimization results to this BB.
	void analyse_method_info (Method_info* info,
									  Context* caller_cx,
									  MIR::Actual_parameter_list* actuals,
									  MIR::VARIABLE_NAME* lhs);

	void analyse_function (User_method_info* info,
								  Context* caller_cx,
								  MIR::Actual_parameter_list*,
								  MIR::VARIABLE_NAME* lhs);

	void analyse_summary (Summary_method_info* info,
								 Context* caller_cx,
							    MIR::Actual_parameter_list*,
								 MIR::VARIABLE_NAME* lhs);

	void apply_modelled_function (Summary_method_info* info, Context* cx, Context* caller_cx);

	void init_superglobals (Context* cx);
	void init_classes (Context* cx);


	/*
	 * Calls to the WPA modules.
	 */
	void forward_bind (Method_info* info,
							 Context* entry_cx,
							 MIR::Actual_parameter_list* actuals);

	void backward_bind (Method_info* info,
							  Context* entry_cx,
							  MIR::VARIABLE_NAME* lhs);

	// Performs points-to analysis, and call the other analyses with the
	// results. Returns true if a solution has changed, requiring this block
	// to be reanalysed.
	void init_block (Context* cx);
	bool analyse_block (Context* cx);
	void finish_block (Context* cx, bool pop = true);

	/*
	 * Assignments by paths (aka high-level)
	 */
	void assign_path_scalar (Context* cx, Path* lhs, const MIR::Literal* lit, bool allow_kill = true);
	void assign_path_scalar (Context* cx, Path* plhs, const Abstract_value* absval, bool allow_kill = true);
	void assign_path_static_array (Context* cx, Path* plhs, MIR::Static_array* array, bool allow_kill = true);
	void assign_path_unknown (Context* cx, Path* lhs, bool allow_kill = true);
	void assign_path_typed (Context* cx, Path* lhs, const Types* types, bool allow_kill = true);
	void assign_path_by_ref (Context* cx, Path* lhs, Path* rhs, bool allow_kill = true);
	void assign_path_by_copy (Context* cx, Path* lhs, Path* rhs, bool allow_kill = true);
	void assign_path_by_cast (Context* cx, Path* lhs, Path* rhs, string type, bool allow_kill = true);
	void assign_path_value (Context* cx, Path* lhs, const Storage_node* st, bool allow_kill = true);
	string assign_path_empty_array (Context* cx, Path* lhs, string name, bool allow_kill = true);
	string assign_path_typed_array (Context* cx, Path* lhs, const Types* types, string name, bool allow_kill = true);
	string assign_path_empty_object (Context* cx, Path* lhs, string type, string name, bool allow_kill = true);

	void assign_attribute (Context* cx, string obj, MIR::Attribute*);

	/*
	 * Assignments by node (aka lower-level)
	 */

	void assign_absval (Context* cx, const Index_node* lhs, const Abstract_value* absval);
	void assign_storage (Context* cx, const Index_node* lhs, const Storage_node* storage);
	Index_node* create_fake_index (Context* cx);
	void destroy_fake_indices (Context* cx);
	Storage_node* build_static_array (Context* cx, MIR::Static_array* array);

	// If no name is provided, an anonymous name is chosen.
	Storage_node* create_empty_storage (Context* cx, string type, string name = "");

	// Copy the value from RHS to LHS (since we're copying a cyclic graph, we
	// need to keep the track of already copied values, and copy them back, or
	// this will go into an infinite-loop).
	typedef Map<string, string> Name_map;

	void copy_value (Context* cx, const Index_node* lhs, const Index_node* rhs, Name_map map = Name_map());
	void copy_structure (Context* cx, const Index_node* lhs, const Storage_node* rhs, string type, Name_map map = Name_map());

	void refer_to_value (Context* cx, const Index_node* lhs, const Index_node* rhs, Certainty cert);

	// Cast the value from RHS to LHS
	void cast_value (Context* cx, const Index_node* lhs, const Index_node* rhs, string type);
	void cast_to_storage (Context* cx, const Index_node* lhs, const Index_node* rhs, string type);

	const Index_node* check_owner_type (Context* cx, const Index_node* index, bool ref_rhs);
	const Abstract_value* read_from_scalar_value (Context* cx, const Index_node* rhs);

	bool is_killable (Context* cx, cIndex_node_list* indices);

	/*
	 * Misc
	 */

	// PATH can refer to many nodes. Get the list of Index_nodes it points to.
	// Set the RHS_BY_REF flag if PATH represents the RHS of an
	// assignment-by-reference.
	cIndex_node_list* get_named_indices (Context* cx, Result_state state, Path* path, bool is_readonly = false);
	cIndex_node_list* get_array_named_indices (Context* cx, Result_state state, Path* lhs, String* index, bool is_readonly);

	// Get anything the path can point to, and all nodes that they may reference.
	cReference_list* get_lhs_references (Context* cx, Path* path);

	const Index_node* coerce_to_string (Context* cx, const Index_node* val);


	Edge_list* get_successors (Context* cx);
	void pull_results (Context* cx, BB_list* bbs);
	cIndex_node_list* get_possible_nulls (List<Context*>*);

	void record_use (Context* cx, const Index_node* node);




	/*
	 * Access to analysis results
	 */

	Method_info_list* get_possible_receivers (Context* cx, Result_state state, MIR::Target*, MIR::Method_name*);
	Method_info_list* get_possible_receivers (Context* cx, Result_state state, MIR::Param_is_ref*);
	Method_info_list* get_possible_receivers (Context* cx, Result_state state, MIR::Method_invocation*);
	Method_info_list* get_possible_receivers (Context* cx, Result_state state, MIR::New*);

	/* Local analysis - calling other analyses */
	void dump (Context* cx, Result_state state, string comment);


private:
	// Get the value of node (can be UNKNOWN).
	String* get_string_value (Context* cx, Result_state state, const Index_node* node);

	const Abstract_value* get_abstract_value (Context* cx, Result_state state, const Alias_name* name);
	friend class WPA;
	friend class Points_to;
	friend class Points_to_impl;

public:
	const Abstract_value* get_abstract_value (Context* cx, Result_state state, MIR::Rvalue* rval);
	const Abstract_value* get_abstract_value (Context* cx, Result_state state, MIR::VARIABLE_NAME*);



	/*
	 * Actually perform analysis
	 */

	void visit_branch_block (Branch_block*);

	void standard_lhs (Basic_block* bb, MIR::Node* lhs, bool is_ref, MIR::Rvalue* rhs);
	void standard_rhs (Basic_block* bb, MIR::Node* in);

	DECLARE_STATEMENT_CFG_VISITORS
	DECLARE_EXPR_CFG_VISITORS

private:
	int iteration_num;

private:
	/*
	 * Model straightforward functions
	 */
	Set<string> modelled_functions;
	Map<string, List<int> > coercion_model;
	Map<string, Types*> type_model;

	/*
	 * Initial population of modelled functions.
	 */
	void populate_modelled_functions();
};


#endif // PHC_WHOLE_PROGRAM
