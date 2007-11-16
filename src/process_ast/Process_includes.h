/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 *
 * Replaces an include statement with the parsed contents of the included file.
 */

#ifndef PHC_PROCESS_INCLUDES
#define PHC_PROCESS_INCLUDES

#include "ast_to_hir/Lower_expr.h"
#include "pass_manager/Pass_manager.h"

class Process_includes : public Lower_expr, public Pass
{
public:
	// This means that the pass should try its hardest to include
	// things, and issue warnings on anything that remains.
	bool hir;

	Process_includes (bool hir, String* pass_name, Pass_manager* pm, const char* name);
	void do_not_include (const char*, AST::AST_eval_expr*, List<AST::AST_statement*>*, AST::AST_actual_parameter*);

	// Pass information
public:

	String* pass_name;
	Pass_manager* pm;
	void run (IR* in, Pass_manager* pm)
	{
		assert (in->hir == NULL);
		in->ast->transform_children (this);
	}

	bool pass_is_enabled (Pass_manager* pm);

public:
	void pre_method(AST::AST_method* in, List<AST::AST_member*>* out);
	void pre_eval_expr(AST::AST_eval_expr* in, List<AST::AST_statement*>* out);

};

#endif // PHC_PROCESS_INCLUDES
