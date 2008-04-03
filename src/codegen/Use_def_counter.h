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

#include "process_ir/General.h"
#include "HIR_visitor.h"

using namespace HIR;
VARIABLE_NAME* simple_var (Expr* in);
void print_map (map<string, int>& in);
bool extract_simple_assignment (Eval_expr* in, VARIABLE_NAME*& lhs, VARIABLE_NAME*& rhs, Assignment*& assignment);

/* Entering at the method level, count the total occurences of a
 * variable, and the number of defintions, and the uses is the
 * difference of the two. */
class Use_def_counter : public HIR::Visitor
{
	map<string, int>& uses;
	map<string, int>& defs;
	map<string, int> occurences;
	bool ignore_methods; // for global

public:
	Use_def_counter (map<string, int>& uses, map<string, int>& defs);

	void pre_method (Method* in);
	void pre_assignment (Assignment* in);
	void pre_variable_name (VARIABLE_NAME* in);
	void post_method (Method* in);
};
