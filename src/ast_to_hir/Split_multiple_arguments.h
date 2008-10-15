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

class Split_multiple_arguments : public AST::Transform, virtual public GC_obj
{
public:
	void pre_global(AST::Global* in, AST::Statement_list* out);
	void pre_static_declaration(AST::Static_declaration* in, AST::Statement_list* out);
	void pre_attribute(AST::Attribute* in, AST::Member_list* out);
};

#endif // PHC_SPLIT_MULTIPLE_ARGUMENTS_H
