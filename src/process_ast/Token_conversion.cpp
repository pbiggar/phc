/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 *
 * Replace a token containing just a string representation, with one containing
 * its value aswell
 */

#include <limits.h>
#include <errno.h>
#include "Token_conversion.h"
#include "lib/error.h"
#include "embed/embed.h"

/*
 * When we parse, values such as ints, strings, floats, bools etc, used to be
 * converted on the spot to their semantic values. However, this made it
 * difficult to accomplish several things, such as implicit conversion of large
 * ints to floats, dealing with int edge cases, and storing the source
 * reprentation of a value (TRUE vs true).
 *
 * Instead, we now leave all these values in their string reprentation while
 * parsing, and convert them to their semantic values using this transformation.
 */

AST_expr* Token_conversion::pre_int (Token_int* in)
{
	if (*in->source_rep == "__LINE__" or *in->source_rep == "__FILE__")
		return in;

	assert (in->value == 0);
	return PHP::convert_token (in);
}

AST_expr* Token_conversion::pre_real (Token_real* in)
{
	assert (in->value == 0.0);
	return PHP::convert_token (in);
}

// Convert unary_op(-,int(5)) to int(-5), and similarly for reals
AST_expr* Token_conversion::pre_unary_op(AST_unary_op* in)
{
	Wildcard<AST_expr>* expr = new Wildcard<AST_expr>;
	Wildcard<Token_int>* i = new Wildcard<Token_int>;
	Wildcard<Token_real>* r = new Wildcard<Token_real>;

	// In all cases, we assign to result, and at the end copy all
	// attributes from *in to *result
	AST_expr* result;

	if(in->match(new AST_unary_op(new AST_unary_op(expr, "-"), "-")))
	{
		// Double negation; remove both
		result = pre_expr(expr->value);
	}

	// TODO add a pass to check for the lack of unary -s

	else if(in->match(new AST_unary_op(i, "-")))
	{
		String* source_rep = new String("-");
		*source_rep += *i->value->source_rep;
		i->value->source_rep = source_rep;
		result = PHP::convert_token (i->value);
	}

	else if(in->match(new AST_unary_op(r, "-")))
	{
		String* source_rep = new String("-");
		*source_rep += *r->value->source_rep;
		r->value->source_rep = source_rep;
		result = PHP::convert_token (r->value);
	}
	
	else 
	{
		// No changes
		return in;
	}

	result->attrs->clone_all_from(in->attrs);
	return result;
}
