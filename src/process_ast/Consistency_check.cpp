/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that the tree is valid. This differs from Invalid_check, in
 * that Invalid_check only checks for incorrect PHP. These checks
 * are a superset of those, and should incorporate any assumptions
 * we make about the AST/HIR, so long as they arent specified in the
 * grammar, in which case the grammar check will pick them up.
 */

#include "Consistency_check.h"


void check (AST_node* in)
{
	// check validity
	if (not in->is_valid ())
		phc_internal_error ("Node is not valid", in);

	in->visit (new Consistency_check ());
}

/* There were other checks, but these have been moved into mixin code, so they
 * can be called earlier, or into check (), since theres no point calling them
 * repeatedly */
Consistency_check::Consistency_check () 
{
	this->use_ice = true;
}
