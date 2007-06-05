/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Check that the tree is valid. This differs from Invalid_check, in that
 * Invalid_check only checks for incorrect PHP. These checks are a superset of
 * those, and should incorporate any assumptions we make about the AST/HIR. 
 */

#include "Invalid_check.h"
void check (AST_node* in);

class Consistency_check : public Invalid_check
{
public:
	Consistency_check ();
	void pre_node (AST_node* in);
	void visit_expr_list (List<AST_expr*>* in);
};
