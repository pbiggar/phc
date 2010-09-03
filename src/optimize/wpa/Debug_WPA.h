/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A simple pass printing debugging information. The idea is that you can use
 * --debug=debug-wpa to see what Whole_program is calling.
 */

#ifndef PHC_DEBUG_WPA
#define PHC_DEBUG_WPA

#include "WPA.h"

class Debug_WPA : public WPA
{
public:

	Debug_WPA (Whole_program* wp);

	void init (Context* outer);
	void forward_bind (Context* caller, Context* entry);
	void backward_bind (Context* caller, Context* exit);

	void pre_invoke_method (Context* caller);
	void post_invoke_method (Context* caller);

	void create_reference (Context* cx, const Index_node* lhs,
								 const Index_node* rhs, Certainty cert);

	void assign_value (Context* cx, const Index_node* lhs, const Storage_node* storage);

	void set_storage (Context* cx, const Storage_node* storage, const Types* types);
	void set_scalar (Context* cx, const Value_node* storage, const Abstract_value* val);

	void kill_value (Context* cx, const Index_node* lhs, bool also_kill_refs = false);

	void record_use (Context* cx, const Index_node* use, Certainty cert);
	

	void pull_init (Context* cx);
	void pull_first_pred (Context* cx, Context* pred);
	void pull_pred (Context* cx, Context* pred);
	void pull_possible_null (Context* cx, const Index_node* node);
	void pull_finish (Context* cx);

	void finish_block (Context* cx);

	bool solution_changed (Context* cx) const;
	bool has_analysis_result (Context* cx, Result_state) const;

	bool equals (WPA* other);
	void dump (Context* cx, Result_state state, string comment) const;
	void dump_everything (string comment) const;
	void merge_contexts ();
};


#endif // DEBUG_WPA
