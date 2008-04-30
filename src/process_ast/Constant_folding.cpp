/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 *
 * Fold constant binary and unary expressions.
 * Note lack of constant propagation.
 */

#include "Constant_folding.h" 
#include "embed/embed.h" 

using namespace AST;

Expr* Constant_folding::post_bin_op (Bin_op* in)
{
	Literal* left = dynamic_cast<Literal*> (in->left);
	Literal* right = dynamic_cast<Literal*> (in->right);

	if (left == NULL || right == NULL)
		return in;

	return PHP::fold_constant_expr (in);
}

Expr* Constant_folding::post_unary_op (Unary_op* in)
{
	// TODO I expect there is a constant, near LONG_MAX, for which the '-' sign
	// turns it into a float, and the second '-' turns it into a positive float,
	// yet if we remove both '-' signs, we get an int. I couldn't find it with
	// some quick tests.

	// Match (- - f())
	Wildcard<Expr>* expr = new Wildcard<Expr>;
	if (in->match (new Unary_op (new Unary_op (expr, "-"), "-")))
	{
		return expr;
	}

	// match constant	
	Literal* lit = dynamic_cast<Literal*> (in->expr);
	if (lit)
		return PHP::fold_constant_expr (in);


	return in;
}
