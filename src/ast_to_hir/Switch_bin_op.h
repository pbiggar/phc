/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Replace '>=' and '>' with '<=' and '<', after switching the operands.
 */

#ifndef PHC_SWITCH_BIN_OP_H
#define PHC_SWITCH_BIN_OP_H

#include "AST_transform.h"

/*
 * This needs to run after shredding, because the operands might be side-effecting.
 */

class Switch_bin_op : public AST::Transform, virtual public GC_obj
{
	AST::Expr* pre_bin_op (AST::Bin_op* in);
};

#endif // PHC_SWITCH_BIN_OP_H
