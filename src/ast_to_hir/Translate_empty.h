/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower calls to empty().
 */

#ifndef PHC_TRANSLATE_EMPTY_H
#define PHC_TRANSLATE_EMPTY_H

#include "AST_transform.h"

class Translate_empty : public AST_transform
{
	AST_expr* pre_method_invocation(AST_method_invocation* in); 
};

#endif // PHC_TRANSLATE_EMPTY_H
