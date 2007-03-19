/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Prepare the AST for code generation (desugaring) 
 */

#ifndef PHC_PREP_H
#define PHC_PREP_H

#include "AST_transform.h"

class Prep : public AST_transform
{
public:
	Token_method_name* post_method_name(Token_method_name* in);
	AST_expr* post_assignment(AST_assignment* in);
	void post_unset(AST_unset* in, List<AST_statement*>* out);
};

#endif // PHC_PREP_H
