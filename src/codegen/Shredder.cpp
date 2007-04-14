/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Transform the AST into 3AC-like code.
 */

#include "Shredder.h"
#include "fresh.h"

// For development only
#include "process_ast/XML_unparser.h"
#include "process_ast/PHP_unparser.h"

class Prep : public AST_visitor
{
	void pre_node(AST_node* in)
	{
		in->attrs->erase("phc.unparser.is_opeq");
		in->attrs->erase("phc.unparser.is_global_stmt");
		in->attrs->erase("phc.unparser.starts_line");
	}

	void pre_assignment(AST_assignment* in)
	{
		in->variable->attrs->set_true("phc.shredder.need_addr");
	}

	void pre_unset(AST_unset* in)
	{
		in->variable->attrs->set_true("phc.shredder.need_addr");
	}

	void pre_attribute(AST_attribute* in)
	{
		// Do not generate a temp to hold the default value of an attribute
		if(in->expr != NULL)
			in->expr->attrs->set_true("phc.shredder.no_temp");
	}

	void pre_static_declaration(AST_static_declaration* in)
	{
		// Do not generate a temp to hold the default value of a static var
		if(in->expr != NULL)
			in->expr->attrs->set_true("phc.shredder.no_temp");
	}
};

Shredder::Shredder()
{
	pieces = new List<AST_statement*>;
}

void Shredder::post_eval_expr(AST_eval_expr* in, List<AST_statement*>* out)
{
	if(in->expr->classid() != AST_assignment::ID)
	{
		// All eval_expr must be assignments; if they are not, we generate
		// a dummy assignment on the LHS
		in->expr = new AST_assignment(fresh("TS"), false, in->expr);
	}
	
	push_back_pieces(in, out);
}

void Shredder::post_return(AST_return* in, List<AST_statement*>* out)
{
	push_back_pieces(in, out);
}

void Shredder::post_unset(AST_unset* in, List<AST_statement*>* out)
{
	push_back_pieces(in, out);
}

void Shredder::post_branch(AST_branch* in, List<AST_statement*>* out)
{
	push_back_pieces(in, out);
}

/*
 * Global is translated into a reference to the GLOBALS array
 */

void Shredder::pre_global(AST_global* in, List<AST_statement*>* out)
{
	Token_variable_name* name;
	name = dynamic_cast<Token_variable_name*>(in->variable_name);

	if(name != NULL)
	{
		out->push_back(new AST_eval_expr(new AST_assignment(
			new AST_variable(NULL, name, new List<AST_expr*>),
			true,
			new AST_variable(
				NULL, 
				new Token_variable_name(new String("GLOBALS")),
				new List<AST_expr*>(new Token_string(
					name->value->clone(),
					name->value->clone()
			))))));
	}
	else
	{
		AST_reflection* reflection;
		reflection = dynamic_cast<AST_reflection*>(in->variable_name);
		assert(reflection != NULL);

		out->push_back(new AST_eval_expr(new AST_assignment(
			new AST_variable(NULL, reflection, new List<AST_expr*>),
			true,
			new AST_variable(
				NULL, 
				new Token_variable_name(new String("GLOBALS")),
				new List<AST_expr*>(reflection->expr)
			))));
	}
}

/*
 * Variables (array indexing, object indexing)
 *
 * We do the indexing bit-by-bit. For example, for $c->a[1][2][3], we get
 *
 *	$T0 =& $c->arr;
 *	$T1 =& $T0[1];
 *	$T2 =& $T1[2];
 *	$T3 =& $T2[3];
 *
 * If the variable occurs on the LHS of an assignment (if the attribute
 * "phc.shredder.need_addr" is set), we stop one short, and use that as the
 * LHS. In the example above, we'd stop at the assignment to $T2, and then
 * use 
 *
 *   $T2[3] = ...
 *
 * as the LHS of the assignment. This isn't strictly necessary for array
 * assignment (since we are using reference assignment), but it is strictly
 * necessary if the variable is the argument to a call to "unset", for example.
 *
 * Note that it is important to use reference assignment, because when we
 * assign to $T2[2] above, we want the original object $c to be modified.
 */

AST_variable* Shredder::post_variable(AST_variable* in)
{
	AST_variable* prev = in;
	
	int num_pieces = 
		  (in->target != NULL ? 1 : 0) 
		+ in->array_indices->size()
		- (in->attrs->is_true("phc.shredder.need_addr") ? 1 : 0);

	if(in->target != NULL && num_pieces > 0)
	{
		AST_variable* temp = fresh("TS");
		pieces->push_back(new AST_eval_expr(new AST_assignment(
			temp, true,
			new AST_variable(
				in->target,
				in->variable_name->clone(),
				new List<AST_expr*>()))));
		prev = temp;
		num_pieces--;

		in->target = NULL;
	}
	
	while(num_pieces > 0)
	{
		AST_variable* temp = fresh("TS");
		pieces->push_back(new AST_eval_expr(new AST_assignment(
			temp, true, 
			new AST_variable(
				NULL, 
				prev->variable_name->clone(), 
				new List<AST_expr*>(in->array_indices->front())))));
		prev = temp;
		num_pieces--;

		in->array_indices->pop_front();
	}

	if(prev != in && !in->array_indices->empty())
	{
		prev = prev->clone();
		prev->array_indices->push_back(in->array_indices->front());
		in->array_indices->pop_front();
	}

	return prev;
}

/*
 * Binary and unary operators
 *
 * The "lazy" binary operators (&&, ||, and friends) are not dealt with here, 
 * but in the lowering pass. Pre and post operators are translated to binary
 * operators.
 */

AST_expr* Shredder::post_bin_op(AST_bin_op* in)
{
	return create_piece(in);
}

AST_expr* Shredder::post_unary_op(AST_unary_op* in)
{
	return create_piece(in);
}
	
AST_expr* Shredder::post_conditional_expr(AST_conditional_expr* in)
{
	return create_piece(in);
}

AST_expr* Shredder::post_pre_op(AST_pre_op* in)
{
	Token_op* op;
	
	if(*in->op->value == "--")
		op = new Token_op(new String("-"));
	else if(*in->op->value == "++")
		op = new Token_op(new String("+"));
	else
		assert(0);

	AST_variable* one = fresh("TS");

	pieces->push_back(new AST_eval_expr(new AST_assignment(
		one,
		false,
		new Token_int(1, new String("1")))));
	pieces->push_back(new AST_eval_expr(new AST_assignment(
		in->variable->clone(),
		false,
		new AST_bin_op(
			in->variable->clone(),
			op,
			one))));
	
	return in->variable->clone();
}

AST_expr* Shredder::post_post_op(AST_post_op* in)
{
	Token_op* op;
	
	if(*in->op->value == "--")
		op = new Token_op(new String("-"));
	else if(*in->op->value == "++")
		op = new Token_op(new String("+"));
	else
		assert(0);

	AST_variable* old_value = fresh("TS");
	AST_variable* one = fresh("TS");

	pieces->push_back(new AST_eval_expr(new AST_assignment(
		old_value,
		false,
		in->variable->clone())));
	pieces->push_back(new AST_eval_expr(new AST_assignment(
		one,
		false,
		new Token_int(1, new String("1")))));
	pieces->push_back(new AST_eval_expr(new AST_assignment(
		in->variable->clone(),
		false,
		new AST_bin_op(
			in->variable->clone(),
			op,
			one))));
	
	return old_value;
}

/*
 * Literals
 */

AST_expr* Shredder::post_int(Token_int* in)
{
	if(in->attrs->is_true("phc.shredder.no_temp"))
		return in;
	else
		return create_piece(in);
}

AST_expr* Shredder::post_real(Token_real* in)
{
	if(in->attrs->is_true("phc.shredder.no_temp"))
		return in;
	else
		return create_piece(in);
}

AST_expr* Shredder::post_string(Token_string* in)
{
	if(in->attrs->is_true("phc.shredder.no_temp"))
		return in;
	else
		return create_piece(in);
}

AST_expr* Shredder::post_bool(Token_bool* in)
{
	if(in->attrs->is_true("phc.shredder.no_temp"))
		return in;
	else
		return create_piece(in);
}

AST_expr* Shredder::post_null(Token_null* in)
{
	if(in->attrs->is_true("phc.shredder.no_temp"))
		return in;
	else
		return create_piece(in);
}

/*
 * Since the shredder changes all eval_expr into assignments, it will change
 * echo("hi") to $Tx = echo("hi"); but since "echo" isn't a true function
 * call in PHP, this will generate incorrect PHP code. For that reason, we
 * translate "echo" to "print" here.
 */

Token_method_name* Shredder::post_method_name(Token_method_name* in)
{
	if(*in->value == "echo")
		return new Token_method_name(new String("print"));
	else
		return in;

}

/*
 * Remove unparser attributes
 */

void Shredder::children_php_script(AST_php_script* in)
{
	Prep prep;
	in->visit(&prep);

	AST_transform::children_php_script(in);
}

/*
 * Most methods in the shredder to the same: an expression is split into
 * lots of assignments, one corresponding to each individual operator in
 * the expression. This is implemented by "create_piece".
 */

AST_variable* Shredder::create_piece(AST_expr* in)
{
	AST_variable* temp = fresh("TS");
	pieces->push_back(new AST_eval_expr(new AST_assignment(temp, false, in)));
	return temp;
}

/*
 * Once an expression has been split into multiple statements, we want
 * to assemble the pieces, and then execute the original statements.
 */

void Shredder::push_back_pieces(AST_statement* in, List<AST_statement*>* out)
{
	out->push_back_all(pieces);
	out->push_back(in);

	// Move comment to the first piece (if any)
	if(!pieces->empty())
	{
		pieces->front()->attrs->set("phc.comments", in->get_comments());
		in->attrs->set("phc.comments", new List<String*>);
	}

	pieces->clear();
}

