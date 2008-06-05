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
#include "MIR.h"
#include "HIR_to_MIR.h"
#include "vector"

class Lower_control_flow : public HIR::Lower_expr
{
	private:
		vector<HIR::Node*> break_levels;
		vector<HIR::Node*> continue_levels;
		HIR_to_MIR folder;

	public:
		MIR::VARIABLE_NAME* fold_var (HIR::VARIABLE_NAME* in);
		template<class T> void add_label (HIR::Node*, List<HIR::Statement*>*);
		template<class T> MIR::Label* exit_label (HIR::Node*);
		template<class T> void lower_exit (T*, List<HIR::Statement*>*);
		void lower_foreach (HIR::Foreach*, List<HIR::Statement*>*);
		void lower_if (HIR::If*, List<HIR::Statement*>*);
		void lower_loop (HIR::Loop* in, List<HIR::Statement*>* out);

	public:
		void pre_control_flow (HIR::Statement* in, List<HIR::Statement*>* out);
		void pre_loop(HIR::Loop* in, List<HIR::Statement*>* out);
		void pre_foreach(HIR::Foreach* in, List<HIR::Statement*>* out);

		void post_loop(HIR::Loop* in, List<HIR::Statement*>* out);
		void post_foreach(HIR::Foreach* in, List<HIR::Statement*>* out);
		void post_if(HIR::If* in, List<HIR::Statement*>* out);
		void post_break(HIR::Break* in, List<HIR::Statement*>* out);
		void post_continue(HIR::Continue* in, List<HIR::Statement*>* out);
};

#endif // PHC_LOWER_CONTROL_FLOW_H
