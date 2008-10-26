/* 
 * phc -- the open source PHP compiler 
 * See doc/license/README.license for licensing information
 *
 * Replace a token containing just a string representation, with one containing
 * its value aswell
 */

#ifndef PHC_TOKEN_CONVERSION
#define PHC_TOKEN_CONVERSION

#include "AST_transform.h"

class Token_conversion : public AST::Transform, virtual public GC_obj
{
public:
	AST::Expr* pre_int (AST::INT* in);
	AST::Expr* pre_real (AST::REAL* in);
	AST::Expr* pre_unary_op (AST::Unary_op* in);
};

#endif // PHC_TOKEN_CONVERSION
