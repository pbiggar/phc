/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lift functions and classes to the global scope, and introduce "__MAIN__"
 */

#ifndef PHC_LIFT_FUNCTIONS_AND_CLASSES_H
#define PHC_LIFT_FUNCTIONS_AND_CLASSES_H

#include "AST_transform.h"

enum scope { GLOBAL_SCOPE, LOCAL_SCOPE };

class Lift_functions_and_classes : public AST_transform
{
public:
	void children_php_script(AST_php_script* in);
	void pre_class_def(AST_class_def* in, List<AST_statement*>* out);
	void pre_interface_def(AST_interface_def* in, List<AST_statement*>* out);
	void pre_method(AST_method* in, List<AST_method*>* out);
	void post_method(AST_method* in, List<AST_method*>* out);
	void pre_if(AST_if* in, List<AST_statement*>* out);
	void pre_while(AST_while* in, List<AST_statement*>* out);
	void pre_do(AST_do* in, List<AST_statement*>* out);
	void pre_for(AST_for* in, List<AST_statement*>* out);
	void pre_foreach(AST_foreach* in, List<AST_statement*>* out);
	void pre_switch(AST_switch* in, List<AST_statement*>* out);
	void pre_break(AST_break* in, List<AST_statement*>* out);
	void pre_continue(AST_continue* in, List<AST_statement*>* out);
	void pre_return(AST_return* in, List<AST_statement*>* out);
	void pre_static_declaration(AST_static_declaration* in, List<AST_statement*>* out);
	void pre_unset(AST_unset* in, List<AST_statement*>* out);
	void pre_declare(AST_declare* in, List<AST_statement*>* out);
	void pre_try(AST_try* in, List<AST_statement*>* out);
	void pre_throw(AST_throw* in, List<AST_statement*>* out);
	void pre_eval_expr(AST_eval_expr* in, List<AST_statement*>* out);
	void pre_nop(AST_nop* in, List<AST_statement*>* out);

protected:
	scope current_scope;
	List<AST_statement*>* main;
};

#endif // PHC_LIFT_FUNCTIONS_AND_CLASSES
