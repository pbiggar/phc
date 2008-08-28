/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 *
 * Replaces an include statement with the parsed contents of the included file.
 */

#ifndef PHC_PROCESS_INCLUDES
#define PHC_PROCESS_INCLUDES

#include "ast_to_hir/AST_lower_expr.h"
#include "pass_manager/Pass.h"

class Process_includes : public AST::Lower_expr, public Pass
{
public:
	// This means that the pass should try its hardest to include
	// things, and issue warnings on anything that remains.
	bool hir;

	Process_includes (bool hir, String* pass_name, Pass_manager* pm, String* name);
	void do_not_include (const char*, AST::Eval_expr*, AST::Statement_list*, AST::Actual_parameter*);

	// Pass information
public:

	String* pass_name;
	Pass_manager* pm;
	void run (IR::PHP_script* in, Pass_manager* pm)
	{
		in->transform_children(this);
	}

	bool pass_is_enabled (Pass_manager* pm);

public:
	void pre_method(AST::Method* in, AST::Member_list* out);
	void pre_eval_expr(AST::Eval_expr* in, AST::Statement_list* out);

};

#endif // PHC_PROCESS_INCLUDES
