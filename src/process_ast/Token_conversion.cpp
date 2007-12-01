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

using namespace AST;

Expr* Token_conversion::pre_int (INT* in)
{
	if (*in->source_rep == "__LINE__" or *in->source_rep == "__FILE__")
		return in;

	assert (in->value == 0);
	return PHP::convert_token (in);
}

Expr* Token_conversion::pre_real (REAL* in)
{
	assert (in->value == 0.0);
	return PHP::convert_token (in);
}

// Convert unary_op(-,int(5)) to int(-5), and similarly for reals
Expr* Token_conversion::pre_unary_op(Unary_op* in)
{
	Wildcard<Expr>* expr = new Wildcard<Expr>;
	Wildcard<INT>* i = new Wildcard<INT>;
	Wildcard<REAL>* r = new Wildcard<REAL>;

	// In all cases, we assign to result, and at the end copy all
	// attributes from *in to *result
	Expr* result;

	if(in->match(new Unary_op(new Unary_op(expr, "-"), "-")))
	{
		// Double negation; remove both
		result = pre_expr(expr->value);
	}

	// TODO add a pass to check for the lack of unary -s

	else if(in->match(new Unary_op(i, "-")))
	{
		String* source_rep = new String("-");
		*source_rep += *i->value->source_rep;
		i->value->source_rep = source_rep;
		result = PHP::convert_token (i->value);
	}

	else if(in->match(new Unary_op(r, "-")))
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
