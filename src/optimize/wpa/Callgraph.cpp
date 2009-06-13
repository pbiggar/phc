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
	string caller;

	if (caller_cx->is_outer ())
		caller = "__OUTER__";
	else
		caller = *caller_cx->get_bb()->cfg->method->signature->method_name->value;

	string callee = *entry_cx->get_bb()->cfg->method->signature->method_name->value;

	methods.insert (callee);
	call_edges[caller].insert (callee);
}

String_list*
Callgraph::get_called_methods ()
{
	String_list* result = new String_list;

	foreach (string m, methods)
		result->push_back (s(m));

	return result;
}

String_list*
Callgraph::bottom_up ()
{
	String_list* result = new String_list;

	List<string> worklist ("__MAIN__");
	Set<string> seen;

	while (worklist.size ())
	{
		string method = worklist.front ();
		worklist.pop_front ();

		if (seen.has (method))
			continue;

		seen.insert (method);

		// Note _front_ for bottom-up
		result->push_front (s(method));

		// Successors
		foreach (string callee, call_edges[method])
			worklist.push_back (callee);

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
Callgraph::dump (Context* cx, string comment)
{
	// Only dump on entry and exit
	if (!isa<Entry_block> (cx->get_bb()) && !isa<Exit_block> (cx->get_bb()))
		return;

	dump_graphviz (s(cx->name () + ": " + comment));
}

void
Callgraph::dump_everything (string comment)
{
	dump_graphviz (s(comment));
}

void
Callgraph::merge_contexts ()
{
}

void
Callgraph::dump_graphviz (String* label)
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

	foreach (string method, methods)
	{
		// Target
		cout
		<< "\""
		<< method
		<< "\""
		<< ";\n"
		;

		foreach (string callee, call_edges[method])
		{
			// Edge
			cout 
			<< "\""
			<< method
			<< "\" -> \"" 
			<< callee 
			<< "\";\n"
			;
		}
	}

	cout
	<< "}\n"
	;
}
