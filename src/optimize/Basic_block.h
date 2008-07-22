#include <boost/graph/properties.hpp>
#include "MIR.h"
#include "process_ir/General.h"


/* Basic blocks */
class Basic_block
{
public:
	// Indicate to BGL that this represents a vertex internal property.
	typedef boost::vertex_property_tag kind;

	// Labels for graphviz
	virtual String* get_graphviz_label () = 0;

	// Override if there are extra properties for this block.
	virtual String* get_graphviz_properties ();

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



