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
	if (*in->get_source_rep () == "__LINE__" or *in->get_source_rep () == "__FILE__")
		return in;

	assert (in->value == 0);
	return PHP::convert_token (in);
}

Expr* Token_conversion::pre_real (REAL* in)
{
	assert (in->value == 0.0);
	return PHP::convert_token (in);
}

// Convert unary_op(-,int(5)) to int(-5), and similarly for reals. Note that
// multiple '-' unary ops are allowed.
Expr* Token_conversion::pre_unary_op(Unary_op* in)
{
	Wildcard<INT>* i = new Wildcard<INT>;
	Wildcard<REAL>* r = new Wildcard<REAL>;

	// In all cases, we assign to result, and at the end copy all
	// attributes from *in to *result
	Expr* result;

	if(in->match(new Unary_op(i, "-")))
	{
		String* source_rep = new String("-");
		*source_rep += *i->value->get_source_rep ();
		i->value->set_source_rep (source_rep);
		result = PHP::convert_token (i->value);
	}
	else if(in->match(new Unary_op(r, "-")))
	{
		String* source_rep = new String("-");
		*source_rep += *r->value->get_source_rep ();
		r->value->set_source_rep (source_rep);
		result = PHP::convert_token (r->value);
	}
	else
	{
		// No changes
		return in;
	}

	// TODO Does this overwrite the source_rep from above?
	result->attrs->clone_all_from(in->attrs);

	return result;
}
