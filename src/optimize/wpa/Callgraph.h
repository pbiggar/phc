/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Callgraph construction.
 */

#ifndef PHC_CALLGRAPH
#define PHC_CALLGRAPH

#include "WPA.h"

class Callgraph : public WPA
{
	Set<string> methods ;
	Map<string, Set<string> > call_edges;

public:
	Callgraph (Whole_program* wp);

	void add_user_call (Basic_block* context, CFG* callee);
	void add_summary_call (Basic_block* context, Method_info* callee);
	void add_call_edge (string caller, string callee);

	String_list* get_called_methods ();
	String_list* bottom_up ();

	void dump (Basic_block* bb);
	void dump_graphviz (String* label);

	// We don't need most of the standard interface.
	void pull_results (Basic_block* bb) {}
	void aggregate_results (Basic_block* bb) {}

	void kill_value (Basic_block* bb, Alias_name name){}
	void kill_reference (Basic_block* bb, Alias_name name){}
	void assign_scalar (Basic_block* bb, Alias_name lhs, MIR::Literal* rhs, certainty cert){}
	void assign_by_ref (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert){}
	void assign_by_copy (Basic_block* bb, Alias_name lhs, Alias_name rhs, certainty cert){}
	void record_use (Basic_block* bb, Alias_name lhs, certainty cert){}


};

#endif // PHC_CALLGRAPH
