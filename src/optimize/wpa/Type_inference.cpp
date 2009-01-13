/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Type-inference.
 *
 */

#include "Type_inference.h"
#include "BCCH_aliasing.h"
#include "Whole_program.h"

using namespace MIR;
using namespace std;
using namespace boost;

Type_inference::Type_inference (Whole_program* wp)
: WPA (wp)
{
}

void
Type_inference::use_summary_results (Method_info* info)
{
	// Handle magic methods. If any parameter can have a magic method, and is
	// an object, invoke the method from Whole_program. We do not need to get
	// the list of receivers here, as Whole_program will query us to find them
	// out separately. We only need to know whether or not there is an
	// invocation.
	
	foreach (Parameter_info* pinfo, *info->params)
	{
		// Get the types of each actual parameter
		phc_TODO ();
	}
}

String_list*
Type_inference::get_types (Var_node* node)
{
	String_list* result = new String_list;

	foreach (Atom_node* end, *node->get_pointees<Atom_node>())
	{
		// HACK
		result->push_back (s (demangle (end->atom, false)));
	}

	return result;
}

void
Type_inference::dump()
{
	// Traverse the points-to graph. For each variable in it, find the types
	// it may point to.
	foreach (Var_node* node, *wp->bcch_aliasing->ptg->get_nodes<Var_node> ())
	{
		cdebug << *node->var_name->value << ": [ ";

		foreach (String* type_name, *get_types (node))
		{
			cdebug << *type_name << ", ";
		}

		cdebug << "]" << endl;
	}
}
