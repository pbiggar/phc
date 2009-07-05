/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Callgraph construction.
 */

#ifndef PHC_CALLGRAPH
#define PHC_CALLGRAPH

#include "WPA.h"
#include "optimize/Method_info.h"

class Callgraph : public WPA
{
	Set<Method_info*> methods;
	Map<Method_info*, Set<Method_info*> > call_edges;

public:
	Callgraph (Whole_program* wp);

	// WPA
	void init (Context* outer);
	void forward_bind (Context* caller, Context* entry);

	Method_info_list* get_called_methods ();
	Method_info_list* bottom_up ();

	bool equals (WPA* other);
	void dump (Context* cx, Result_state state, string comment) const;
	void dump_everything (string comment) const;
	void merge_contexts ();


	bool has_analysis_result (Context* cx, Result_state state) const;


private:

	void dump_graphviz (String* label) const;
};

#endif // PHC_CALLGRAPH
