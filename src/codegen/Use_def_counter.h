/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * HACK TODO: Remove.
 * This is exactly the sort of hacky thing we wanted
 * to remove. This would be much better done with a data-flow
 * framework, but is much easier than cleaning up the passes, which
 * would otherwise be necessary.
 *
 * Count the uses and defs of each variable. Of course, it is very
 * imprecise, only works for very certain cases, doesn't use any
 * sort of data-flow techniques, won't work in the general case in
 * the presence of any sort of features, doesn't take references
 * into account, etc. This is only barely usable for the hacky dead
 * code elimination and copy propagation I've hacked into place.
 *
 */

#ifndef PHC_USE_DEF_COUNTER
#define PHC_USE_DEF_COUNTER

#include "process_ir/General.h"
#include "HIR_visitor.h"
#include "stack"
#include "map"
#include "HIR.h"

HIR::VARIABLE_NAME* simple_var (HIR::Expr* in);
bool extract_simple_assignment (HIR::Eval_expr* in, HIR::VARIABLE_NAME*& lhs, HIR::VARIABLE_NAME*& rhs, HIR::Assignment*& assignment);

/* Entering at the method level, count the total occurences of a
 * variable, and the number of defintions, and the uses is the
 * difference of the two. */
class Use_def_counter : public HIR::Visitor
{
	// For analysis
private:
	stack< map<string, int>* > analysis_defs;
	stack< map<string, int>* > analysis_occurences;

	void pre_method (HIR::Method* in);
	void pre_assignment (HIR::Assignment* in);
	void pre_variable_name (HIR::VARIABLE_NAME* in);
	void post_method (HIR::Method* in);
	void children_php_script (HIR::PHP_script* in);

	// start analysing a new method
	void init_analysis ();
	void finish_analysis (List<HIR::Statement*>* in);

public:
	Use_def_counter ();
};


class Clear_use_defs : public HIR::Visitor
{
	void pre_node (HIR::Node* in)
	{
		in->attrs->erase_with_prefix ("phc.use_defs");
	}
};

#endif // PHC_USE_DEF_COUNTER

