/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lower calls to empty().
 */

#ifndef PHC_TRANSLATE_EMPTY_H
#define PHC_TRANSLATE_EMPTY_H

#include "HIR_transform.h"

class Translate_empty : public HIR::Transform
{
	HIR::Expr* pre_method_invocation(HIR::Method_invocation* in); 
};

#endif // PHC_TRANSLATE_EMPTY_H
