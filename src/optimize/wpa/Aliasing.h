/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Flow-, field-, and context-sensitive alias analysis, in a similar fashion to
 *
 * Michael Hind and Michael Burke and Paul Carini and Jong-Deok Choi,
 * Interprocedural pointer alias analysis
 * ACM Trans. Program. Lang. Syst., 1999
 *
 * We use an infinite call-string approach, and assume that other peoples
 * research can be used to constrain the memory usage at a later date. There
 * is one points-to graph per program point (which corresponds to a basic
 * block for us).
 */

#ifndef PHC_ALIASING
#define PHC_ALIASING

#include "WPA.h"
#include "Points_to.h"


class Optimization_transformer;
class Path;

class Aliasing : public CFG_visitor
{
public:
	Points_to* ptg;
	Whole_program* wp;
	Optimization_transformer* transformer;

	// Record 1 per program-point.
	Map<long, Points_to*> in_ptgs;
	Map<long, Points_to*> out_ptgs;

	Aliasing (Whole_program*);


	void use_summary_results (Basic_block* context, Method_info* info, MIR::Actual_parameter_list* in, MIR::VARIABLE_NAME* lhs);

	void forward_bind (Basic_block* bb, CFG* callee_cfg,
			MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* retval);

	void backward_bind (Basic_block* bb, CFG* callee_cfg);

	// Performs points-to analysis, and call the other analyses with the
	// results. Returns true if a solution has changed, requiring this block
	// to be reanalysed.
	bool analyse_block (Basic_block* bb);

	// Apply the interprocedural optimization results to this BB.
	void apply_results (Basic_block* bb);

	void dump (Basic_block* bb);

private:
	// These functions describe the operation being performed in each block.
	// They pass the information to the Points-to graph, and to the other
	// analyses. The BB is to give a unique index to the results.
	void assign_scalar (Basic_block* bb, Path* lhs, MIR::Literal* lit);
	void assign_by_ref (Basic_block* bb, Path* lhs, Path* rhs);
	void assign_by_copy (Basic_block* bb, Path* lhs, Path* rhs);

	void record_use (Basic_block* bb, Index_node* node);


	// Whole_program runs this, so we dont need it.
	void run (CFG* cfg){}

public:

	/* PATH can refer to many nodes. Get the list of Index_nodes it points to */
	Index_node_list* get_named_indices (Basic_block* bb, Path* path);

	// NULL if more than 1 exists
	Index_node* get_named_index (Basic_block* bb, Path* path);

	// Get the list of potential values of node (can include '*' when it is
	// unknown).
	String_list* get_string_values (Basic_block* bb, Index_node* node);

	/*
	 * For analysis
	 */
	void visit_branch_block (Branch_block*) { phc_TODO (); }

	void visit_assign_array (Statement_block*, MIR::Assign_array*) { phc_TODO (); }
	void visit_assign_field (Statement_block*, MIR::Assign_field *) { phc_TODO (); }
	void visit_assign_var (Statement_block*, MIR::Assign_var*);
	void visit_assign_var_var (Statement_block*, MIR::Assign_var_var*) { phc_TODO (); }
	void visit_eval_expr (Statement_block*, MIR::Eval_expr*);
	void visit_foreach_end (Statement_block*, MIR::Foreach_end*) { phc_TODO (); }
	void visit_foreach_next (Statement_block*, MIR::Foreach_next*) { phc_TODO (); }
	void visit_foreach_reset (Statement_block*, MIR::Foreach_reset*) { phc_TODO (); }
	void visit_global (Statement_block*, MIR::Global*);
	void visit_pre_op (Statement_block*, MIR::Pre_op*) { phc_TODO (); }
	void visit_assign_next (Statement_block*, MIR::Assign_next*) { phc_TODO (); }
	void visit_return (Statement_block*, MIR::Return*) { phc_TODO (); }
	void visit_static_declaration (Statement_block*, MIR::Static_declaration*) { phc_TODO (); }
	void visit_throw (Statement_block*, MIR::Throw*) { phc_TODO (); }
	void visit_try (Statement_block*, MIR::Try*) { phc_TODO (); }
	void visit_unset (Statement_block*, MIR::Unset*) { phc_TODO (); }

	void handle_method_invocation (Statement_block* bb, MIR::Method_invocation* in, MIR::VARIABLE_NAME* lhs);

	void handle_new (Statement_block* bb, MIR::New* in, MIR::VARIABLE_NAME* lhs);
};



/* A Path is a way of representing some dereferencing. See Aliasing.cpp. */
class Path : virtual public GC_obj
{
};

Path* P (string st, MIR::Node* node);

class Indexing : public Path 
{
public:
	Indexing (Path* lhs, Path* rhs);
	Path* lhs;
	Path* rhs;
};

class ST_path : public Path
{
public:
	string name;
	ST_path (string name);
};

class Index_path : public Path
{
public:
	Index_path (string name);
	string name;
};




#endif // PHC_ALIASING
