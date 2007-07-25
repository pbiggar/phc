/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 *
 * Replaces an include statement with the parsed contents of the included file.
 */

#ifndef PHC_PROCESS_INCLUDES
#define PHC_PROCESS_INCLUDES

#include "AST_transform.h"

class Process_includes : public AST_transform
{
public:
	bool gotos_allowed;
	Process_includes (bool gotos_allowed);

public:
	void pre_method(AST_method* in, List<AST_member*>* out);
	void pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out);

};

#endif // PHC_PROCESS_INCLUDES
