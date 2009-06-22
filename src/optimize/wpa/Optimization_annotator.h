/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Use the results of the analyses to transform the MIR. Do not handle dead
 * code.
 * */

#ifndef PHC_OPTIMIZATION_ANNOTATOR
#define PHC_OPTIMIZATION_ANNOTATOR

class Whole_program;
class Index_node;

class Optimization_annotator : public CFG_visitor
{
public:
	Whole_program* wp;
	Optimization_annotator (Whole_program*);

	void run (CFG* cfg);

	// for passing between visit_assign_var and visit_expr
	Index_node* lhs;
	bool assign_var_is_ref;

	void visit_entry_block (Entry_block* bb);

	DECLARE_STATEMENT_CFG_VISITORS
	DECLARE_EXPR_CFG_VISITORS
};

#endif // PHC_OPTIMIZATION_ANNOTATOR
