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

class Lower_control_flow : public AST::Transform
{
	private:
		List<AST::Node*> break_levels;
		List<AST::Node*> continue_levels;

	public:
		AST::PHP_script* post_php_script (AST::PHP_script* in);

	public:
		template<class T> void add_label (AST::Node*, List<AST::Statement*>*);
		template<class T> AST::Label* exit_label (AST::Node*);
		template<class T> void lower_exit (T*, List<AST::Statement*>*);
		void lower_for (AST::For*, List<AST::Statement*>*);
		void lower_foreach (AST::Foreach*, List<AST::Statement*>*);
		void lower_do (AST::Do*, List<AST::Statement*>*);
		void lower_if (AST::If*, List<AST::Statement*>*);
		void lower_while (AST::While* in, List<AST::Statement*>* out);
		void lower_switch (AST::Switch* in, List<AST::Statement*>* out);

	public:
		void pre_control_flow (AST::Statement* in, List<AST::Statement*>* out);
		void pre_while(AST::While* in, List<AST::Statement*>* out);
		void pre_do(AST::Do* in, List<AST::Statement*>* out);
		void pre_for(AST::For* in, List<AST::Statement*>* out);
		void pre_foreach(AST::Foreach* in, List<AST::Statement*>* out);
		void pre_switch(AST::Switch* in, List<AST::Statement*>* out);

		void post_while(AST::While* in, List<AST::Statement*>* out);
		void post_do(AST::Do* in, List<AST::Statement*>* out);
		void post_for(AST::For* in, List<AST::Statement*>* out);
		void post_foreach(AST::Foreach* in, List<AST::Statement*>* out);
		void post_switch(AST::Switch* in, List<AST::Statement*>* out);
		void post_if(AST::If* in, List<AST::Statement*>* out);
		void post_break(AST::Break* in, List<AST::Statement*>* out);
		void post_continue(AST::Continue* in, List<AST::Statement*>* out);
};

#endif // PHC_LOWER_CONTROL_FLOW_H
