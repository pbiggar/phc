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

class Lower_control_flow : public AST::AST_transform
{
	private:
		List<AST::AST_node*> break_levels;
		List<AST::AST_node*> continue_levels;

	public:
		AST::AST_php_script* post_php_script (AST::AST_php_script* in);

	public:
		template<class T> void add_label (AST::AST_node*, List<AST::AST_statement*>*);
		template<class T> AST::AST_label* exit_label (AST::AST_node*);
		template<class T> void lower_exit (T*, List<AST::AST_statement*>*);
		void lower_for (AST::AST_for*, List<AST::AST_statement*>*);
		void lower_foreach (AST::AST_foreach*, List<AST::AST_statement*>*);
		void lower_do (AST::AST_do*, List<AST::AST_statement*>*);
		void lower_if (AST::AST_if*, List<AST::AST_statement*>*);
		void lower_while (AST::AST_while* in, List<AST::AST_statement*>* out);
		void lower_switch (AST::AST_switch* in, List<AST::AST_statement*>* out);

	public:
		void pre_control_flow (AST::AST_statement* in, List<AST::AST_statement*>* out);
		void pre_while(AST::AST_while* in, List<AST::AST_statement*>* out);
		void pre_do(AST::AST_do* in, List<AST::AST_statement*>* out);
		void pre_for(AST::AST_for* in, List<AST::AST_statement*>* out);
		void pre_foreach(AST::AST_foreach* in, List<AST::AST_statement*>* out);
		void pre_switch(AST::AST_switch* in, List<AST::AST_statement*>* out);

		void post_while(AST::AST_while* in, List<AST::AST_statement*>* out);
		void post_do(AST::AST_do* in, List<AST::AST_statement*>* out);
		void post_for(AST::AST_for* in, List<AST::AST_statement*>* out);
		void post_foreach(AST::AST_foreach* in, List<AST::AST_statement*>* out);
		void post_switch(AST::AST_switch* in, List<AST::AST_statement*>* out);
		void post_if(AST::AST_if* in, List<AST::AST_statement*>* out);
		void post_break(AST::AST_break* in, List<AST::AST_statement*>* out);
		void post_continue(AST::AST_continue* in, List<AST::AST_statement*>* out);
};

#endif // PHC_LOWER_CONTROL_FLOW_H
