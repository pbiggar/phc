/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the HIR back to PHP syntax
 */

#ifndef PHC_HIR_UNPARSER
#define PHC_HIR_UNPARSER

#include "HIR_visitor.h"


class HIR_unparser : public virtual HIR::Visitor
{
protected:
	ostream& os;

public:
	HIR_unparser(ostream& os = cout);
	void pre_php_script (HIR::PHP_script* in);
};

#endif // PHC_HIR_UNPARSER 
