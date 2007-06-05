/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that the tree is valid. This differs from Invalid_check, in that
 * Invalid_check only checks for incorrect PHP. These checks are a superset of
 * those, and should incorporate any assumptions we make about the AST/HIR. 
 */

#include "Consistency_check.h"


void check (AST_node* in)
{
	in->visit (new Consistency_check ());
}


Consistency_check::Consistency_check () 
{
	this->use_ice = true;
}

void Consistency_check::pre_node (AST_node* in)
{
	// check we dont create any bad constructs
	Invalid_check::pre_node (in);

	// check validity
	if (not in->is_valid ())
		phc_internal_error ("Node is not valid", in);

	// check we have no null attributes
	AttrMap::const_iterator i;
	for(i = in->attrs->begin(); i != in->attrs->end(); i++)
	{
		if ((*i).second == NULL)
			phc_internal_error ("Cant have null attributes", in);
	}
}


void Consistency_check::visit_expr_list (List<AST_expr*>* in)
{
	List<AST_expr*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if ((*i) == NULL)
		{
			phc_internal_error ("Cant have null list elements", in);
		}
	}

}
