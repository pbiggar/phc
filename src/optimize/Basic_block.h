#ifndef PHC_BASIC_BLOCK
#define PHC_BASIC_BLOCK

#include <boost/graph/properties.hpp>

#include "MIR.h"
#include "CFG.h"
#include "Set.h"


/* Basic blocks */
class Basic_block
{
public:
	Basic_block();

	// Indicate to BGL that this represents a vertex internal property.
	typedef boost::vertex_property_tag kind;
	vertex_t vertex;

	// Labels for graphviz
	virtual String* get_graphviz_label () = 0;

	// Override if there are extra properties for this block.
	// Returns a list of (name,value) pairs
	virtual list<std::pair<String*,String*> >* get_graphviz_properties ();

	// Returns a list of (name, list[values]) pairs
	virtual list<std::pair<String*,Set*> >* get_graphviz_bb_properties ();
	virtual list<std::pair<String*,Set*> >* get_graphviz_head_properties ();
	virtual list<std::pair<String*,Set*> >* get_graphviz_tail_properties ();

public:
	// TODO: these should be moved into a solution class, so that we can have 1 per analysis.
	// Dataflow solution
	Set* defs;
	Set* uses;
	Set* live_in;
	Set* live_out;
	int iteration_count;
	bool changed;

	// this is a global solution, so each BB should have the same solution.
	Set* aliases; 
};

class Entry_block : public Basic_block
{
	virtual String* get_graphviz_label ();
};

class Exit_block : public Basic_block
{
	virtual String* get_graphviz_label ();
};

class Empty_block : public Basic_block
{
	virtual String* get_graphviz_label ();
};

class Branch_block : public Basic_block
{
public:
	MIR::Branch* branch;
	Branch_block (MIR::Branch* b);
	String* get_graphviz_label ();
	list<std::pair<String*,String*> >* get_graphviz_properties ();
};


class Statement_block : public Basic_block 
{
public:
	MIR::Statement* statement;
	Statement_block (MIR::Statement* s);
	virtual String* get_graphviz_label ();
};


#endif // PHC_BASIC_BLOCK
