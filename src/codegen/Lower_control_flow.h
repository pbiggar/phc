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
	private:
		List<AST_node*> break_levels;
		List<AST_node*> continue_levels;

	public:
		AST_php_script* post_php_script (AST_php_script* in);

	public:
		template<class T> void potentially_add_label (AST_node*, List<AST_statement*>*);
		template<class T> AST_label* exit_label (AST_node*);
		template<class T> void lower_exit (T*, List<AST_statement*>*);
		void lower_for (AST_for*, List<AST_statement*>*);
		void lower_foreach (AST_foreach*, List<AST_statement*>*);
		void lower_do (AST_do*, List<AST_statement*>*);
		void lower_if (AST_if*, List<AST_statement*>*);
		void lower_while (AST_while* in, List<AST_statement*>* out);
		void lower_switch(AST_switch* in, List<AST_statement*>* out);

	public:
		void pre_while(AST_while* in, List<AST_statement*>* out);
		void pre_do(AST_do* in, List<AST_statement*>* out);
		void pre_for(AST_for* in, List<AST_statement*>* out);
		void pre_foreach(AST_foreach* in, List<AST_statement*>* out);
		void pre_switch(AST_switch* in, List<AST_statement*>* out);

		void post_while(AST_while* in, List<AST_statement*>* out);
		void post_do(AST_do* in, List<AST_statement*>* out);
		void post_for(AST_for* in, List<AST_statement*>* out);
		void post_foreach(AST_foreach* in, List<AST_statement*>* out);
		void post_switch(AST_switch* in, List<AST_statement*>* out);
		void post_if(AST_if* in, List<AST_statement*>* out);
		void post_break(AST_break* in, List<AST_statement*>* out);
		void post_continue(AST_continue* in, List<AST_statement*>* out);
};

#endif // PHC_LOWER_CONTROL_FLOW_H
