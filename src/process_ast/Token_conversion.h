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

class Token_conversion : public AST::AST_transform
{
public:
	AST::AST_expr* pre_int (AST::Token_int* in);
	AST::AST_expr* pre_real (AST::Token_real* in);
	AST::AST_expr* pre_unary_op (AST::AST_unary_op* in);
};

#endif // PHC_TOKEN_CONVERSION
