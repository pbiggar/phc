/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Assign temporaries 
 */

#ifndef PHC_ASSIGN_TEMPS_H
#define PHC_ASSIGN_TEMPS_H

#include "AST_visitor.h"

enum scope { GLOBAL_SCOPE, LOCAL_SCOPE };

class Assign_temps : public AST_visitor
{
public:
	void pre_php_script(AST_php_script* in);
	void post_php_script(AST_php_script* in);
	void pre_method(AST_method* in);
	void post_method(AST_method* in);
	void pre_expr(AST_expr* in);

protected:
	int next_global_fresh;
	int next_local_fresh;
	scope current_scope;
	Integer* fresh();
};

#endif // PHC_ASSIGN_TEMPS_H
