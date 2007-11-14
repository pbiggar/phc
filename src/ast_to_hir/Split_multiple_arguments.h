/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Split statements that accept multiple arguments in the AST but only a
 * single argument in the HIR (such as global, const, static and var) into
 * multiple statements, one for each argument in the source
 */

#ifndef PHC_SPLIT_MULTIPLE_ARGUMENTS_H
#define PHC_SPLIT_MULTIPLE_ARGUMENTS_H

#include "AST_transform.h"

class Split_multiple_arguments : public AST::AST_transform
{
public:
	void pre_global(AST::AST_global* in, List<AST::AST_statement*>* out);
	void pre_static_declaration(AST::AST_static_declaration* in, List<AST::AST_statement*>* out);
	void pre_attribute(AST::AST_attribute* in, List<AST::AST_member*>* out);
};

#endif // PHC_SPLIT_MULTIPLE_ARGUMENTS_H
