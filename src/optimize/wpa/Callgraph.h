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

	void add_summary_call (Basic_block* context, Method_info* callee);

	// WPA
	void forward_bind (Basic_block* bb, CFG* callee_cfg,
							 MIR::Actual_parameter_list* actuals,
							 MIR::VARIABLE_NAME* retval);

	String_list* get_called_methods ();
	String_list* bottom_up ();

	bool equals (WPA* other);
	void dump (Basic_block* bb);


private:

	void add_call_edge (string caller, string callee);
	void dump_graphviz (String* label);
};

#endif // PHC_CALLGRAPH
