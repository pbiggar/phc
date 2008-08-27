/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Shred lists.
 */

#ifndef PHC_EARLY_SHREDDER_H
#define PHC_EARLY_SHREDDER_H

#include "ast_to_hir/AST_lower_expr.h"

// Some shredding will create variables which may be missed if done
// at the same time as the variable shredding.
class List_shredder : public AST::Lower_expr
{
public:

	/* Shred
	 *  $x = (list ($a, $b, $c) = array ($c, $b, a));
	 * into
	 *	  $PLA = array ($c, $b, $a);
	 *	  $c = $PLA[2];
	 *	  $b = $PLA[1];
	 *	  $a = $PLA[0];
	 *	  $x = $PLA; // note that left evaluates to the RHS of the assignment
	 *
	 *	Note the reverse order. This matters if you've arrays on the lhs.
	 *	Note that references arent allowed here.
	 */

	AST::Expr* post_list_assignment(AST::List_assignment* in);
};


#endif // PHC_EARLY_SHREDDER_H
