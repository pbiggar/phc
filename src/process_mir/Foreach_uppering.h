/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert Foreach statements to use ArrayIterators.
 */

#ifndef PHC_FOREACH_UPPERING_H
#define PHC_FOREACH_UPPERING_H

#include "AST_transform.h"


class Foreach_uppering : public AST::Transform
{
public:
	void pre_foreach_reset (AST::Foreach_reset* in, List<AST::Statement*>* out);
	void pre_foreach_next (AST::Foreach_next* in, List<AST::Statement*>* out);
	void pre_foreach_end (AST::Foreach_end* in, List<AST::Statement*>* out);
	AST::Expr* pre_foreach_has_key (AST::Foreach_has_key* in);
	AST::Expr* pre_foreach_get_key (AST::Foreach_get_key* in);
	AST::Expr* pre_foreach_get_val (AST::Foreach_get_val* in);
};

#endif // PHC_FOREACH_UPPERING_H
