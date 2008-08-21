#include "Basic_block.h"
#include "process_ir/General.h"
#include "process_mir/MIR_unparser.h"

using namespace std;

/* Constructors */

Basic_block::Basic_block()
: vertex (NULL)
, defs (NULL)
, uses (NULL)
, live_in (NULL)
, live_out (NULL)
, changed (false)
, aliases (NULL)
{
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


list<std::pair<String*,Set*> >*
Basic_block::get_graphviz_bb_properties ()
{
	list<pair<String*,Set*> >* result = new list<std::pair<String*,Set*> >;
	if (defs)
		result->push_back (pair<String*, Set*> (s("defs"), defs));
	if (uses)
		result->push_back (pair<String*, Set*> (s("uses"), uses));
	if (aliases && dynamic_cast<Entry_block*> (this))
		result->push_back (pair<String*, Set*> (s("aliases"), aliases));
	return result;
}

list<std::pair<String*,Set*> >*
Basic_block::get_graphviz_head_properties ()
{
	list<std::pair<String*,Set*> >* result = new list<std::pair<String*,Set*> >;
	if (live_in)
		result->push_back (pair<String*, Set*> (s("IN"), live_in));
	return result;
}

list<std::pair<String*,Set*> >*
Basic_block::get_graphviz_tail_properties ()
{
	list<std::pair<String*,Set*> >* result = new list<std::pair<String*,Set*> >;
	if (live_out)
		result->push_back (pair<String*, Set*> (s("OUT"), live_out));
	return result;
}
