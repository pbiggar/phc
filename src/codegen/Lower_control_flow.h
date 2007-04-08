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
		void pre_while(AST_while* in, List<AST_statement*>* out);
		void pre_do(AST_do* in, List<AST_statement*>* out);
		void pre_for(AST_for* in, List<AST_statement*>* out);
		void pre_foreach(AST_foreach* in, List<AST_statement*>* out);
		void pre_if(AST_if* in, List<AST_statement*>* out);
		void pre_switch(AST_switch* in, List<AST_statement*>* out);
		void pre_switch_case(AST_switch_case* in, List<AST_switch_case*>* out);
		void pre_break(AST_break* in, List<AST_statement*>* out);
		void pre_continue(AST_continue* in, List<AST_statement*>* out);
		void pre_try(AST_try* in, List<AST_statement*>* out);
		void pre_catch(AST_catch* in, List<AST_catch*>* out);
		void pre_throw(AST_throw* in, List<AST_statement*>* out);
		AST_expr* pre_conditional_expr(AST_conditional_expr* in);
};

#endif // PHC_LOWER_CONTROL_FLOW_H
