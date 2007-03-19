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

AST_expr* Token_conversion::pre_int(Token_int* in)
{
	errno = 0; // clear this since we need to know if strtol sets it

	// we need to know about overflow, so we use strtol here, and strtoll later
	strtol(in->source_rep->c_str(), NULL, 0);

	// if theres overflow, it gets converted to a real, except if its
	// specfied in hex, and its greater than 0x100000000, in which case it
	// becomes int(MAX_INT)
	if(errno == ERANGE)
	{
		errno = 0;
		// check for a hexadecimal integer in the right range
		if (		in->source_rep->compare(0, 2, "0x", 2) == 0
				or in->source_rep->compare(0, 2, "0X", 2) == 0
				or in->source_rep->compare(0, 3, "-0x", 3) == 0
				or in->source_rep->compare(0, 3, "-0X", 3) == 0
			)
		{
			if(strtoll(in->source_rep->c_str(), NULL, 16) > (long long)(ULONG_MAX))
			{
				assert(errno == 0);
				Token_int* i = new Token_int(LONG_MAX, in->source_rep);
				i->attrs->set("phc.line_number", in->attrs->get("phc.line_number"));
				return i;
			}
			else 
			{
				assert(errno == 0);
				if(strtoll(in->source_rep->c_str(), NULL, 16) < -(long long)(ULONG_MAX))
				{
					assert(errno == 0);
					// Why LONG_MIN + 1? Well. Ask the PHP folks :)
					Token_int* i = new Token_int(LONG_MIN + 1, in->source_rep);
					i->attrs->set("phc.line_number", in->attrs->get("phc.line_number"));
					return i;
				}
				else
				{
					assert(errno == 0);
					// some platforms (cygwin and solaris at least) dont like atof (or strtod) on
					// hex numbers, despite it being part of the C standard for a very
					// long time. Since we're processing digits, we can safely go the long way.
					double value = static_cast<double>(strtoll(in->source_rep->c_str(), NULL, 16));
					assert(errno == 0);
					Token_real* r = new Token_real(value, in->source_rep);
					r->attrs->set("phc.line_number", in->attrs->get("phc.line_number"));
					return r;
				}
			}
		}

		// get a real in the case of overflow
		double value = strtod(in->source_rep->c_str(), (char **)NULL);
		assert(errno == 0);
		Token_real* r = new Token_real(value, in->source_rep);
		r->attrs->set("phc.line_number", in->attrs->get("phc.line_number"));
		return r;
	}
	else
	{
		return in;
	}
}

// Convert unary_op(-,int(5)) to int(-5), and similarly for reals
AST_expr* Token_conversion::pre_unary_op(AST_unary_op* in)
{
	Wildcard<AST_expr>* expr = new Wildcard<AST_expr>;
	Wildcard<Token_int>* i = new Wildcard<Token_int>;
	Wildcard<Token_real>* f = new Wildcard<Token_real>;

	if(in->match(new AST_unary_op(new AST_unary_op(expr, "-"), "-")))
	{
		// Double negation; remove both
		return pre_expr(expr->value);
	}

	if(in->match(new AST_unary_op(i, "-")))
	{
		String* source_rep = new String("-");
		*source_rep += *i->value->source_rep;
		i->value->source_rep = source_rep;
		i->value->value = -(i->value->value);
		return pre_expr(i->value);
	}

	if(in->match(new AST_unary_op(f, "-")))
	{
		String* source_rep = new String("-");
		*source_rep += *f->value->source_rep;
		f->value->source_rep = source_rep;
		f->value->value = -(f->value->value);
		return pre_expr(f->value);
	}
	
	return in;
}
