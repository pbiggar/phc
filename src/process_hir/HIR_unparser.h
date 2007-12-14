/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the HIR back to PHP syntax
 */

#ifndef PHC_HIR_UNPARSER
#define PHC_HIR_UNPARSER

#include "HIR_visitor.h"
#include "process_ir/PHP_unparser.h"
#include <stack>


class HIR_unparser : public virtual HIR::Visitor
{
protected:
	ostream& os;

public:
	HIR_unparser(ostream& os = cout);
	void pre_node(HIR::Node* in);
};

#endif // PHC_HIR_UNPARSER 
