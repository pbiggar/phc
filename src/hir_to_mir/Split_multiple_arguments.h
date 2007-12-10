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

class Split_multiple_arguments : public AST::Transform
{
public:
	void pre_global(AST::Global* in, List<AST::Statement*>* out);
	void pre_static_declaration(AST::Static_declaration* in, List<AST::Statement*>* out);
	void pre_attribute(AST::Attribute* in, List<AST::Member*>* out);
};

#endif // PHC_SPLIT_MULTIPLE_ARGUMENTS_H
