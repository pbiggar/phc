#include "Basic_block.h"

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
