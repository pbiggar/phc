/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 *
 * Replaces an include statement with the parsed contents of the included file.
 */

#ifndef PHC_PROCESS_INCLUDES
#define PHC_PROCESS_INCLUDES

#include "AST_transform.h"
#include "Pass_manager.h"

using namespace AST;

class Process_includes : public AST_transform, public Pass
{
public:
	// This means that the pass should try its hardest to include
	// things, and issue warnings on anything that remains. Without
	// DEFINITIVE set, it wont insert gotos.
	bool definitive;
	String* pass_name;
	Pass_manager* pm;
	Process_includes (bool definitive, String* pass_name, Pass_manager* pm, const char* name);
	void run (AST_php_script* in, Pass_manager* pm)
	{
		in->transform_children (this);
	}
	bool pass_is_enabled (Pass_manager* pm);

public:
	void pre_method(AST_method* in, List<AST_member*>* out);
	void pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out);

};

#endif // PHC_PROCESS_INCLUDES
