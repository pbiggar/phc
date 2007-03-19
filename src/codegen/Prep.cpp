/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Prepare the AST for code generation (desugaring) 
 */

#include "Prep.h"

Token_method_name* Prep::post_method_name(Token_method_name* in)
{
	if(*in->value == "echo")
		in->value = new String("printf");
	
	return in;
}

AST_expr* Prep::post_assignment(AST_assignment* in)
{
	// We need an address on the LHS for both reference assignments 
	// (in which case the hashtable must be updated to point to a new zval),
	// and for non-reference assignments (in which case the hashtable must
	// be updated to point to a new zval *if* copy-on-write is possible).
	in->variable->attrs->set("phc.generate_c.is_addr", new Boolean(1));

	return in;
}

void Prep::post_unset(AST_unset* in, List<AST_statement*>* out)
{
	out->push_back(in);
	in->variable->attrs->set("phc.generate_c.is_addr", new Boolean(1));
}
