/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Transform the AST into 3AC-like code.
 */

#include "Shredder.h"
#include "fresh.h"

Shredder::Shredder()
{
	pieces = new List<AST_statement*>;
}

void Shredder::post_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
{
	out->push_back_all(pieces);
	out->push_back(in);
	pieces->clear();
}

/*
 * Variables (array indexing, object indexing)
 * TODO: variables on the LHS need to be treated differently from variables
 * on the RHS
 */

AST_variable* Shredder::post_variable(AST_variable* in)
{
	AST_variable* prev = in;

	if(in->target != NULL)
	{
		AST_variable* temp = fresh();
		pieces->push_back(new AST_eval_expr(new AST_assignment(
			temp, false,
			new AST_variable(
				in->target,
				in->variable_name->clone(),
				new List<AST_expr*>()))));
		prev = temp;

		in->target = NULL;
	}
	
	while(not in->array_indices->empty())
	{
		AST_variable* temp = fresh();
		pieces->push_back(new AST_eval_expr(new AST_assignment(
			temp, false, 
			new AST_variable(
				NULL, 
				prev->variable_name->clone(), 
				new List<AST_expr*>(in->array_indices->front())))));
		prev = temp;

		in->array_indices->pop_front();
	}

	return prev;
}

/*
 * Binary and unary operators
 *
 * The "lazy" binary operators (&&, ||, and friends) are not dealt with here, 
 * but in the lowering pass.
 */

AST_expr* Shredder::post_bin_op(AST_bin_op* in)
{
	return create_piece(in);
}

AST_expr* Shredder::post_unary_op(AST_unary_op* in)
{
	return create_piece(in);
}

/*
 * Literals
 */

AST_expr* Shredder::post_int(Token_int* in)
{
	return create_piece(in);
}

AST_expr* Shredder::post_real(Token_real* in)
{
	return create_piece(in);
}

AST_expr* Shredder::post_string(Token_string* in)
{
	return create_piece(in);
}

AST_expr* Shredder::post_bool(Token_bool* in)
{
	return create_piece(in);
}

AST_expr* Shredder::post_null(Token_null* in)
{
	return create_piece(in);
}

/*
 * Most methods in the shredder to the same: an expression is split into
 * lots of assignments, one corresponding to each individual operator in
 * the expression. This is implemented by "create_piece".
 */

AST_variable* Shredder::create_piece(AST_expr* in)
{
	AST_variable* temp = fresh();
	pieces->push_back(new AST_eval_expr(new AST_assignment(temp, false, in)));
	return temp;
}
