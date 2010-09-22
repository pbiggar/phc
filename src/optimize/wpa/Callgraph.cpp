/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Callgraph construction.
 */

#include "Callgraph.h"

using namespace MIR;
using namespace boost;
using namespace std;

Callgraph::Callgraph (Whole_program* wp)
: WPA(wp)
{
}

void
Callgraph::init (Context* outer)
{
}

void
Callgraph::forward_bind (Context* caller_cx, Context* entry_cx)
{
	Method_info* callee = entry_cx->get_bb ()->cfg->method_info;
	Method_info* caller = NULL; // for outer scope
	if (caller_cx->get_bb ()->cfg)
		caller = caller_cx->get_bb ()->cfg->method_info;

	methods.insert (callee);
	call_edges[caller].insert (callee);
}

Method_info_list*
Callgraph::get_called_methods ()
{
	return methods.to_list ();
}

Method_info_list*
Callgraph::bottom_up ()
{
	Method_info_list* result = new Method_info_list;

	Method_info_list* worklist = new Method_info_list;
	
	foreach (Method_info* mi, methods)
	{
		if (*mi->name == "__MAIN__")
			worklist->push_back (mi);
	}

	Set<Method_info*> seen;

	while (worklist->size ())
	{
		Method_info* info = worklist->front ();
		worklist->pop_front ();

		if (seen.has (info))
			continue;

		seen.insert (info);

		// Note _front_ for bottom-up
		result->push_front (info);

		// Successors
		foreach (Method_info* mi, call_edges[info])
			worklist->push_back (mi);

	}

	return result;
}

bool
Callgraph::equals (WPA* wpa)
{
	Callgraph* other = dyc<Callgraph> (wpa);
	return methods.equals (&other->methods)
		 && call_edges.equals (&other->call_edges);
}



void
Callgraph::dump (Context* cx, Result_state, string comment) const
{
	// Only dump on entry and exit
	if (!isa<Entry_block> (cx->get_bb()) && !isa<Exit_block> (cx->get_bb()))
		return;

	dump_graphviz (s(cx->name () + ": " + comment));
}

void
Callgraph::dump_everything (string comment) const
{
	dump_graphviz (s(comment));
}

void
Callgraph::merge_contexts ()
{
}

void
Callgraph::dump_graphviz (String* label) const
{
	if (label == NULL)
	{
		CHECK_DEBUG ();
		label = s("TEST");
	}

	cout
	<< "digraph G {\n"
	<< "graph [labelloc=t];\n"
	<< "graph [label=\"Callgraph: " << *label << "\"];\n"
	;

	foreach (Method_info* caller, methods)
	{
		// Target
		cout
		<< "\""
		<< *caller->name 
		<< "\""
		<< ";\n"
		;

		foreach (Method_info* callee, call_edges[caller])
		{
			// Edge
			cout 
			<< "\""
			<< *caller->name
			<< "\" -> \"" 
			<< *callee->name
			<< "\";\n"
			;
		}
	}

	cout
	<< "}\n"
	;
}

bool
Callgraph::has_analysis_result (Context* cx, Result_state) const
{
  return false;
}

void
Callgraph::register_class_use (Class_info* cinfo)
{
	do
	{
		used_classes.insert (cinfo);
		cinfo = cinfo->get_parent ();
	}
	while(cinfo!=NULL);
}

Class_info_list*
Callgraph::get_used_classes ()
{
	return used_classes.to_list ();
}
