/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convert Foreach statements to use ArrayIterators.
 */

#include "Foreach_uppering.h"
#include "process_ir/General.h"

using namespace AST;

void Foreach_uppering::pre_foreach_reset (AST::Foreach_reset* in, List<Statement*>* out)
{
	(*out
		<< "$" << in->iter << " = new ArrayObject ($" << in->array << ");\n"
		<< "$" << in->iter << " = $" << in->iter << "->getIterator();"
	).finish (in);
}

void Foreach_uppering::pre_foreach_next (AST::Foreach_next* in, List<Statement*>* out)
{
	(*out
		<< "$" << in->iter << "->next ();\n"
	).finish (in);
}

void Foreach_uppering::pre_foreach_end (AST::Foreach_end* in, List<Statement*>* out)
{
	// Do nothing (the garbage collector will clean this up)
}

Expr* Foreach_uppering::pre_foreach_has_key (AST::Foreach_has_key* in)
{
	List<AST::Statement*> out;
	(out
		<< "$" << in->iter << "->valid ();\n"
	).finish (in);

	return dynamic_cast<Expr*> (out.front()->find (new Wildcard<Expr>));
}

Expr* Foreach_uppering::pre_foreach_get_key (AST::Foreach_get_key* in)
{
	if (in->attrs->is_true ("phc.unparser.use_get_key"))
	{
		NIL* nil = new NIL;
		nil->clone_mixin_from (in);
		return nil;
	}

	List<AST::Statement*> out;
	(out
		<< "$" << in->iter << "->key ();\n"
	).finish (in);

	return dynamic_cast<Expr*> (out.front()->find (new Wildcard<Expr>));
}

Expr* Foreach_uppering::pre_foreach_get_val (AST::Foreach_get_val* in)
{
	List<AST::Statement*> out;
	(out
		<< "$" << in->array << "[$" << in->key << "];"
	).finish (in);

	return dynamic_cast<Expr*> (out.front()->find (new Wildcard<Expr>));
}
