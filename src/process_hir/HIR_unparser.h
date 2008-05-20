/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the HIR back to PHP syntax
 */

#ifndef PHC_HIR_UNPARSER
#define PHC_HIR_UNPARSER

#include "HIR_visitor.h"
#include "process_ast/AST_unparser.h"

class HIR_unparser : public virtual PHP_unparser, public virtual HIR::Visitor
{
public:
	HIR_unparser(ostream& os = cout, bool in_php = false);
	void unparse (IR::Node* in);
	void unparse_foreign (IR::Node* in);

protected:
	AST_unparser ast_unparser;

public:
	// TODO: These rightly belong in the HIR, but leave them here so that the steps are small.
	void children_foreach_reset(HIR::Foreach_reset* in);
	void children_foreach_next(HIR::Foreach_next* in);
	void children_foreach_end(HIR::Foreach_end* in);
	void children_foreach_has_key(HIR::Foreach_has_key* in);
	void children_foreach_get_key(HIR::Foreach_get_key* in);
	void children_foreach_get_val(HIR::Foreach_get_val* in);
	void children_ht_iterator(HIR::HT_ITERATOR* in);


};

#endif // PHC_HIR_UNPARSER 
