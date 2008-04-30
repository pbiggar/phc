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
	// $iter = new ArrayObject ($array);
	// $iter = $iter->getIterator ();
	stringstream ss;
	String* iter = in->iter->get_value_as_string (); 
	String* arr = in->array->get_value_as_string (); 
	ss << "<?php $" << *iter
		<< " = new ArrayObject($" << *arr << ");\n"
		<< "$" << *iter << " = $" << *iter << "->getIterator();?>";

	out->push_back_all (parse_to_ast (new String (ss.str ()), in));
}

void Foreach_uppering::pre_foreach_next (AST::Foreach_next* in, List<Statement*>* out)
{
	stringstream ss;
	String* iter = in->iter->get_value_as_string (); 
	ss << "<?php $" << *iter
		<< "->next(); ?>";

	out->push_back_all (parse_to_ast (new String (ss.str ()), in));
}

void Foreach_uppering::pre_foreach_end (AST::Foreach_end* in, List<Statement*>* out)
{
	// Do nothing (the garbage collector will clean this up)
}

Expr* Foreach_uppering::pre_foreach_has_key (AST::Foreach_has_key* in)
{
	stringstream ss;
	String* iter = in->iter->get_value_as_string (); 
	ss << "<?php $" << *iter
		<< "->valid(); ?>";

	Wildcard<AST::Expr>* result = new Wildcard<AST::Expr>;
	List<AST::Statement*>* stmts = parse_to_ast (new String (ss.str ()), in);
	stmts->front()->match (new Eval_expr (result));
	return result->value;
}

Expr* Foreach_uppering::pre_foreach_get_key (AST::Foreach_get_key* in)
{
	if (in->attrs->is_true ("phc.unparser.use_get_key"))
		return new NIL ();

	stringstream ss;
	String* iter = in->iter->get_value_as_string (); 
	ss << "<?php $" << *iter
		<< "->key(); ?>";

	Wildcard<AST::Expr>* result = new Wildcard<AST::Expr>;
	List<AST::Statement*>* stmts = parse_to_ast (new String (ss.str ()), in);
	stmts->front()->match (new Eval_expr (result));
	return result->value;
}

Expr* Foreach_uppering::pre_foreach_get_val (AST::Foreach_get_val* in)
{
	stringstream ss;
	String* arr = in->array->get_value_as_string (); 
	String* key = in->key->get_value_as_string (); 
	ss << "<?php $" << *arr
		<< "[$" << *key << "]; ?>";

	Wildcard<AST::Expr>* result = new Wildcard<AST::Expr>;
	List<AST::Statement*>* stmts = parse_to_ast (new String (ss.str ()), in);
	stmts->front()->match (new Eval_expr (result));
	return result->value;
}
