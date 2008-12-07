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

#include "lib/Vector.h"

class Lower_control_flow : public HIR::Lower_expr
{
private:
	Vector<HIR::Node*> break_levels;
	Vector<HIR::Node*> continue_levels;
	HIR_to_MIR folder;

public:
	MIR::VARIABLE_NAME* fold_var (HIR::VARIABLE_NAME* in);
	template<class T> MIR::Label* get_label (HIR::Node* in);
	template<class T> void add_label (HIR::Node*, HIR::Statement_list*);
	template<class T> MIR::Label* exit_label (HIR::Node*);
	template<class T> void lower_exit (T*, HIR::Statement_list*);
	void lower_foreach (HIR::Foreach*, HIR::Statement_list*);
	void lower_if (HIR::If*, HIR::Statement_list*);
	void lower_loop (HIR::Loop* in, HIR::Statement_list* out);

public:
	void pre_control_flow (HIR::Statement* in, HIR::Statement_list* out);
	void pre_loop(HIR::Loop* in, HIR::Statement_list* out);
	void pre_foreach(HIR::Foreach* in, HIR::Statement_list* out);

	void post_loop(HIR::Loop* in, HIR::Statement_list* out);
	void post_foreach(HIR::Foreach* in, HIR::Statement_list* out);
	void post_if(HIR::If* in, HIR::Statement_list* out);
	void post_break(HIR::Break* in, HIR::Statement_list* out);
	void post_continue(HIR::Continue* in, HIR::Statement_list* out);
};

#endif // PHC_LOWER_CONTROL_FLOW_H
