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
	AST_php_script* current_script; // stores a record of the current script
	bool in_main_run; // indicates that the currently traversed method is %MAIN%::%RUN%

public:
	void children_php_script(AST_php_script* in);
	void pre_method(AST_method* in, List<AST_member*>* out);
	void pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out);

};

#endif // PHC_PROCESS_INCLUDES
