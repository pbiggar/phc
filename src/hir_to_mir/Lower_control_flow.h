/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower any control flow statements into conditional
 * gotos, and add necessary labels.
 */

#ifndef PHC_LOWER_CONTROL_FLOW_H
#define PHC_LOWER_CONTROL_FLOW_H

#include "HIR_lower_expr.h"

class Lower_control_flow : public Lower_expr
{
	private:
		List<HIR::Node*> break_levels;
		List<HIR::Node*> continue_levels;

	public:
		template<class T> void add_label (HIR::Node*, List<HIR::Statement*>*);
		template<class T> HIR::Label* exit_label (HIR::Node*);
		template<class T> void lower_exit (T*, List<HIR::Statement*>*);
		void lower_for (HIR::For*, List<HIR::Statement*>*);
		void lower_foreach (HIR::Foreach*, List<HIR::Statement*>*);
		void lower_do (HIR::Do*, List<HIR::Statement*>*);
		void lower_if (HIR::If*, List<HIR::Statement*>*);
		void lower_while (HIR::While* in, List<HIR::Statement*>* out);
		void lower_switch (HIR::Switch* in, List<HIR::Statement*>* out);

	public:
		void pre_control_flow (HIR::Statement* in, List<HIR::Statement*>* out);
		void pre_while(HIR::While* in, List<HIR::Statement*>* out);
		void pre_do(HIR::Do* in, List<HIR::Statement*>* out);
		void pre_for(HIR::For* in, List<HIR::Statement*>* out);
		void pre_foreach(HIR::Foreach* in, List<HIR::Statement*>* out);
		void pre_switch(HIR::Switch* in, List<HIR::Statement*>* out);

		void post_while(HIR::While* in, List<HIR::Statement*>* out);
		void post_do(HIR::Do* in, List<HIR::Statement*>* out);
		void post_for(HIR::For* in, List<HIR::Statement*>* out);
		void post_foreach(HIR::Foreach* in, List<HIR::Statement*>* out);
		void post_switch(HIR::Switch* in, List<HIR::Statement*>* out);
		void post_if(HIR::If* in, List<HIR::Statement*>* out);
		void post_break(HIR::Break* in, List<HIR::Statement*>* out);
		void post_continue(HIR::Continue* in, List<HIR::Statement*>* out);
};

#endif // PHC_LOWER_CONTROL_FLOW_H
