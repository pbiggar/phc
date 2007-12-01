/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower calls to empty().
 */

#ifndef PHC_TRANSLATE_EMPTY_H
#define PHC_TRANSLATE_EMPTY_H

#include "AST_transform.h"

class Translate_empty : public AST::Transform
{
	AST::Expr* pre_method_invocation(AST::Method_invocation* in); 
};

#endif // PHC_TRANSLATE_EMPTY_H
