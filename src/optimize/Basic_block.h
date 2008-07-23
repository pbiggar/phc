#ifndef PHC_BASIC_BLOCK
#define PHC_BASIC_BLOCK

#include <boost/graph/properties.hpp>
#include "MIR.h"
#include "CFG.h"


class Backwards_flow_visitor;

/* Basic blocks */
class Basic_block
{
public:
	// Indicate to BGL that this represents a vertex internal property.
	typedef boost::vertex_property_tag kind;
	vertex_t vertex;

	// Labels for graphviz
	virtual String* get_graphviz_label () = 0;

	// Override if there are extra properties for this block.
	virtual String* get_graphviz_properties ();

	// Process this block using the passed analysis
	bool process (Backwards_flow_visitor*);

	// Dataflow solution
public:
	int iteration_count;
	

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
	virtual String* get_graphviz_label ();
	virtual String* get_graphviz_properties ();
};


class Statement_block : public Basic_block 
{
public:
	MIR::Statement* statement;
	Statement_block (MIR::Statement* s);
	virtual String* get_graphviz_label ();
};


#endif // PHC_BASIC_BLOCK
