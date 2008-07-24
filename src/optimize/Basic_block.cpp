#include "Basic_block.h"
#include "Backwards_flow_visitor.h"
#include "process_ir/General.h"

/* Constructors */
Branch_block::Branch_block (MIR::Branch* b) 
: branch (b) 
{
}

Statement_block::Statement_block (MIR::Statement* s) 
: statement(s)
{
}

String*
Basic_block::get_graphviz_properties ()
{
	return NULL;
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

String*
Branch_block::get_graphviz_properties ()
{
	return s("shape=\"rectangle\"");
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
