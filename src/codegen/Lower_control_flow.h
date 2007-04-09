/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower any control flow statements into conditional
 * gotos, and add necessary labels.
 */

#ifndef PHC_LOWER_CONTROL_FLOW_H
#define PHC_LOWER_CONTROL_FLOW_H

#include "AST_transform.h"

class Lower_control_flow : public AST_transform
{
	public:
		void post_while(AST_while* in, List<AST_statement*>* out);
		void post_do(AST_do* in, List<AST_statement*>* out);
		void post_for(AST_for* in, List<AST_statement*>* out);
		void post_foreach(AST_foreach* in, List<AST_statement*>* out);
		void post_if(AST_if* in, List<AST_statement*>* out);
		void post_switch(AST_switch* in, List<AST_statement*>* out);
		void post_switch_case(AST_switch_case* in, List<AST_switch_case*>* out);
		void post_break(AST_break* in, List<AST_statement*>* out);
		void post_continue(AST_continue* in, List<AST_statement*>* out);
		void post_try(AST_try* in, List<AST_statement*>* out);
		void post_catch(AST_catch* in, List<AST_catch*>* out);
		void post_throw(AST_throw* in, List<AST_statement*>* out);
		AST_expr* post_conditional_expr(AST_conditional_expr* in);
};

#endif // PHC_LOWER_CONTROL_FLOW_H
