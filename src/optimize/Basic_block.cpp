#include "Basic_block.h"
#include "Backwards_flow_visitor.h"
#include "process_ir/General.h"

using namespace std;

/* Constructors */

Basic_block::Basic_block()
{
	defs = new Set();
	uses = new Set();
	live_in = new Set();
	live_out = new Set();
}

Branch_block::Branch_block (MIR::Branch* b) 
: branch (b) 
{

}

Statement_block::Statement_block (MIR::Statement* s) 
: statement(s)
{
}

list<pair<String*,String*> >*
Basic_block::get_graphviz_properties ()
{
	list<pair<String*,String*> >* result = new list<pair<String*,String*> >;
	assert (0);
	return result;
}

/* Labels for graphviz */
String*
Entry_block::get_graphviz_label ()
{
	return s("ENTRY");
}

String* Exit_block::get_graphviz_label ()
{
	return s("EXIT");
}

String* Empty_block::get_graphviz_label ()
{
	return s("");
}

String* Branch_block::get_graphviz_label ()
{
	return branch->variable_name->value;
}

String*
Statement_block::get_graphviz_label ()
{
	stringstream ss;
	MIR_unparser mup(ss, true);
	mup.unparse(statement);
	return s(ss.str());
}

list<pair<String*,String*> >*
Branch_block::get_graphviz_properties ()
{
	list<pair<String*,String*> >* result =
		Basic_block::get_graphviz_properties ();

	result->push_back (pair<String*,String*> (s("shape"), s("rectangle")));

	return result;
}


/* Dataflow */
bool
Basic_block::should_reiterate ()
{
	return solution_changed;
}

void
Basic_block::init_df ()
{
	// TODO make sure iteration count is taken into account
	iteration_count = 0;
	solution_changed = true;
	defs = new Set;
	uses = new Set;
	live_in = new Set;
	live_out = new Set;
}


list<std::pair<String*,Set*> >*
Basic_block::get_graphviz_bb_properties ()
{
	list<pair<String*,Set*> >* result = new list<std::pair<String*,Set*> >;
	if (defs)
		result->push_back (pair<String*, Set*> (s("defs"), defs));
	if (uses)
		result->push_back (pair<String*, Set*> (s("uses"), uses));
	return result;
}

list<std::pair<String*,Set*> >*
Basic_block::get_graphviz_head_properties ()
{
	list<std::pair<String*,Set*> >* result = new list<std::pair<String*,Set*> >;
	if (live_out)
		result->push_back (pair<String*, Set*> (s("OUT"), live_out));
	return result;
}

list<std::pair<String*,Set*> >*
Basic_block::get_graphviz_tail_properties ()
{
	list<std::pair<String*,Set*> >* result = new list<std::pair<String*,Set*> >;
	if (live_in)
		result->push_back (pair<String*, Set*> (s("IN"), live_in));
	return result;
}
