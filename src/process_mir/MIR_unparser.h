/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the MIR back to PHP syntax
 */

#ifndef PHC_MIR_UNPARSER
#define PHC_MIR_UNPARSER

#include "MIR_visitor.h"


class MIR_unparser : public virtual MIR::Visitor
{
protected:
	ostream& os;
	MIR::Node* entry_node;

public:
	MIR_unparser(ostream& os = cout);
	void pre_node (MIR::Node* in);
	void post_node (MIR::Node* in);
};

#endif // PHC_MIR_UNPARSER 
