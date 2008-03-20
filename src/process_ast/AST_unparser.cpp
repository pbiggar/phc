/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the AST back to PHP syntax. Makes an effort to adhere to the Zend
 * coding style guidelines at
 *
 *   http://framework.zend.com/manual/en/coding-standard.coding-style.html
 */

#include <iostream>
#include <iomanip> 
#include <vector>
#include "AST_unparser.h" 
#include "cmdline.h"
#include "process_ir/General.h"

extern struct gengetopt_args_info args_info;

using namespace std;
using namespace AST;

/*
 * Linearization
 *
 * This is used when unparsing concat operators to deal correctly with 
 * in-string syntax. The lexical analyser marks concat operators inserted by
 * phc as "phc.unparser.in_string_syntax.simple". The difficulty in using
 * this information in the unparser stems from the fact that the associativity
 * of the concat operators is effectively arbitrary. To solve this problem,
 * linearization does an in-order traversal of the tree, collecting "all"
 * operands of the concatenation, and then partitioning them into groups
 * that are part of the same string. For example,
 * 
 *   "1 $a 2" . $b . $c . "3 $c 4\n"
 *
 * in (linear) partitioned form is
 *
 *   {"1 ", $a, " 2"}, {$b}, {$c}, {"3 ", $c, " 04\n"}
 *
 * In children_bin_op this partitioning is then used to insert quotes at the
 * right places.
 */

class Linearize : public Visitor 
{
public:
	std::vector<Expr*> exprs;
	std::vector<OP*> ops;
	std::vector<int> partitions;
	bool start_new_partition;
	OP* last_op;

public:
	Linearize()
	{
		start_new_partition = true;
		last_op = NULL;
	}

public:
	void append(Expr* in)
	{
		exprs.push_back(in);
		ops.push_back(last_op);
		
		if(start_new_partition)
		{
			partitions.push_back(1);
		}
		else
		{
			partitions.back() += 1;
		}
	}
	
	void process_bin_op(Bin_op* in)
	{
		visit_expr(in->left);
		last_op = in->op;
		start_new_partition = !
			(    in->op->attrs->is_true("phc.unparser.in_string_syntax.simple")
			  || in->op->attrs->is_true("phc.unparser.in_string_syntax.delimited")
				|| in->op->attrs->is_true("phc.unparser.in_string_syntax.complex")
		 	);
		visit_expr(in->right);
	}

	// Overriding children_expr because we don't want to traverse into the 
	// subexpressions of non-bin-ops
	void children_expr(Expr* in)
	{
		Bin_op* bin_op = dynamic_cast<Bin_op*>(in);

		if(bin_op != NULL && *bin_op->op->value == ".")
			process_bin_op(bin_op);
		else
			append(in);
	}
};

/*
 * The unparser proper
 */

AST_unparser::AST_unparser (ostream& os) : PHP_unparser (os)
{
	in_string.push(false); 
}

void AST_unparser::children_php_script(PHP_script* in)
{
  if(in->attrs->has("phc.unparser.hash_bang") && !args_info.no_hash_bang_flag)
    echo_html(in->attrs->get_string("phc.unparser.hash_bang"));

	// We don't call output_start_tag here, because the first statement
	// of the script maybe INLINE_HTML. We rely on the infrastructure in
	// PHP_unparser to output the tags when we need them

	if(!args_info.no_leading_tab_flag) inc_indent();

	// We don't want to output the { and }, so we manually traverse the list
	List<Statement*>::const_iterator i;
	for(i = in->statements->begin(); i != in->statements->end(); i++)
		visit_statement(*i);
	
	if(!args_info.no_leading_tab_flag) dec_indent();

	// However, to avoid not outputting a closing tag, we do call 
	// output_end_tag. If one was output already, nothing will happen
	output_end_tag();
}

void AST_unparser::children_interface_def(Interface_def* in)
{
	echo("interface ");
	visit_interface_name(in->interface_name);

	if(!in->extends->empty())
	{
		echo(" extends ");
		visit_interface_name_list(in->extends);
	}
	
	visit_member_list(in->members);
}

void AST_unparser::children_class_def(Class_def* in)
{
	visit_class_mod(in->class_mod);
	echo("class ");
	visit_class_name(in->class_name);

	if(in->extends != NULL)
	{
		echo(" extends ");
		visit_class_name(in->extends);
	}
	
	if(!in->implements->empty())
	{
		echo(" implements ");
		visit_interface_name_list(in->implements);
	}
	
	visit_member_list(in->members);
}

void AST_unparser::children_class_mod(Class_mod* in)
{
	if(in->is_abstract) echo("abstract ");
	if(in->is_final) echo("final ");
}

void AST_unparser::children_method(Method* in)
{
	visit_signature(in->signature);
	if(in->statements != NULL)
	{
		newline();
		visit_statement_list(in->statements);
		newline();
	}
	else
		// Abstract method
		echo_nl(";");
}

void AST_unparser::children_signature(Signature* in)
{
	visit_method_mod(in->method_mod);
	echo("function ");
	if(in->is_ref) echo("&");
	visit_method_name(in->method_name);
	visit_formal_parameter_list(in->formal_parameters);
}

void AST_unparser::children_method_mod(Method_mod* in)
{
	if(in->is_public)		echo("public ");
	if(in->is_protected)	echo("protected ");
	if(in->is_private)	echo("private ");
	if(in->is_static)		echo("static ");
	if(in->is_abstract)	echo("abstract ");
	if(in->is_final)		echo("final ");
}

void AST_unparser::children_formal_parameter(Formal_parameter* in)
{
	visit_type(in->type);
	if(in->is_ref) echo("&");
	visit_name_with_default(in->var);
}

void AST_unparser::children_type(Type* in)
{
	if(in->class_name != NULL)
	{
		visit_class_name(in->class_name);
		echo(" ");
	}
}

void AST_unparser::children_attribute(Attribute* in)
{
	visit_attr_mod(in->attr_mod);
	// Class attributes get a dollar sign, with the exception of const attributes
	List<Name_with_default*>::const_iterator i;
	for(i = in->vars->begin(); i != in->vars->end(); i++)
	{
		if(i != in->vars->begin())
			echo(", ");

		if(!in->attr_mod->is_const) echo("$"); 
		visit_variable_name((*i)->variable_name);
		if((*i)->expr != NULL)
		{
			echo(" = ");
			visit_expr((*i)->expr);
		}
	}
	echo(";");
	// newline is output by post_commented_node
}

void AST_unparser::children_attr_mod(Attr_mod* in)
{
	if(in->is_public)		echo("public ");
	if(in->is_protected)	echo("protected ");
	if(in->is_private)	echo("private ");
	if(in->is_static)		echo("static ");
	if(in->is_const)		echo("const ");

	if(!in->is_public && 
		!in->is_protected && 
		!in->is_private && 
		!in->is_static && 
		!in->is_const)
			echo("var ");
}

void AST_unparser::children_if(If* in)
{
	if(in->attrs->is_true("phc.unparser.is_elseif")) echo("else");
	echo("if (");
	visit_expr(in->expr);
	echo(")");
	space_or_newline();

	visit_statement_list(in->iftrue);

	if(!in->iffalse->empty())
	{
		If* elseif = dynamic_cast<If*>(in->iffalse->front());

		space_or_newline();

		if(elseif && elseif->attrs->is_true("phc.unparser.is_elseif"))
		{
			visit_statement(elseif);
		}
		else
		{
			echo("else");
			space_or_newline();

			visit_statement_list(in->iffalse);
		}
	}

	newline();
}

/* This is simpler than the other if, since there's no user-written code to
 * maintain, and the statements can only be gotos */
void AST_unparser::children_branch(Branch* in)
{
	echo("if (");
	bool in_if_expression = true;
	visit_expr(in->expr);
	in_if_expression = false;
	echo(") goto ");
	visit_label_name (in->iftrue);
	echo (" else goto ");
	visit_label_name (in->iffalse);
	echo (";");

	newline();
}

void AST_unparser::children_while(While* in)
{
	echo("while (");
	visit_expr(in->expr);
	echo(")");
	space_or_newline();

	visit_statement_list(in->statements);
	newline();
}

void AST_unparser::children_do(Do* in)
{
	echo("do");
	space_or_newline();
	visit_statement_list(in->statements);
	space_or_newline();
	echo("while (");
	visit_expr(in->expr);
	echo_nl(");");
}

void AST_unparser::children_for(For* in)
{
	echo("for(");
	if(in->init != NULL) visit_expr(in->init);
	echo("; ");
	if(in->cond != NULL) visit_expr(in->cond);
	echo("; ");
	if(in->incr != NULL) visit_expr(in->incr);
	echo(")");
	space_or_newline();

	visit_statement_list(in->statements);
	newline();
}

void AST_unparser::children_foreach(Foreach* in)
{
	echo("foreach (");
	visit_expr(in->expr);
	echo(" as ");
	if(in->key != NULL) 
	{
		visit_variable(in->key);
		echo(" => ");
	}
	if(in->is_ref) echo("&");
	visit_variable(in->val);
	echo(")");
	space_or_newline();

	visit_statement_list(in->statements);
	newline();
}

void AST_unparser::children_foreach_reset (Foreach_reset* in)
{
	visit_ht_iterator (in->ht_iterator);
	echo (" = new ArrayObject (");
	visit_variable (in->variable);
	echo (");");
	newline ();
	visit_ht_iterator (in->ht_iterator);
	echo (" = ");
	visit_ht_iterator (in->ht_iterator);
	echo ("->getIterator ();");
}

void AST_unparser::children_foreach_next (Foreach_next* in)
{
	visit_ht_iterator (in->ht_iterator);
	echo ("->next ();");
}

void AST_unparser::children_foreach_end (Foreach_end* in)
{
}

void AST_unparser::children_foreach_has_key (Foreach_has_key* in)
{
	visit_ht_iterator (in->ht_iterator);
	echo ("->valid ()");
}

void AST_unparser::children_foreach_get_key (Foreach_get_key* in)
{
	visit_ht_iterator (in->ht_iterator);
	echo ("->key ()");
}

void AST_unparser::children_foreach_get_val (Foreach_get_val* in)
{
	// If there is no key in the AST, we need to unparse one anyway, so we can
	// access it.
	Expr* expr;
	if (in->attrs->has ("phc.unparser.foreach_get_key"))
	{
		Object* obj = in->attrs->get ("phc.unparser.foreach_get_key");
		Eval_expr* get_key = dynamic_cast<Eval_expr*> (obj);
		assert (get_key);
		expr = get_key->expr;
	}
	else
	{
		// The key isnt in the AST, so it was added as an attribute instead.
		Object* obj = in->attrs->get ("phc.unparser.foreach_key");
		Variable* key = dynamic_cast<Variable*> (obj);
		assert (key);
		expr = key;
	}
	visit_variable (in->variable);
}


void AST_unparser::children_ht_iterator(HT_ITERATOR* in)
{
	echo ("$");
	echo (in->get_value_as_string ());
}

void AST_unparser::children_switch(Switch* in)
{
	echo("switch (");
	visit_expr(in->expr);
	echo(")");
	space_or_newline();

	visit_switch_case_list(in->switch_cases);
}

void AST_unparser::children_switch_case(Switch_case* in)
{
	if(in->expr != NULL)
	{
		echo("case ");
		visit_expr(in->expr);
		echo_nl(":");
	}
	else
	{
		echo_nl("default:");
	}

	// We don't want curlies here
	inc_indent();

	List<Statement*>::const_iterator i;
	for(i = in->statements->begin(); i != in->statements->end(); i++)
		visit_statement(*i);

	dec_indent();
}

void AST_unparser::children_break(Break* in)
{
	echo("break");
	if(in->expr != NULL)
	{
		echo(" ");
		visit_expr(in->expr);
	}
	echo(";");
	// newline output by post_commented_node
}

void AST_unparser::children_continue(Continue* in)
{
	echo("continue");
	if(in->expr != NULL)
	{
		echo(" ");
		visit_expr(in->expr);
	}
	echo(";");
	// newline output by post_commented_node
}

void AST_unparser::children_return(Return* in)
{
	echo("return");
	if(in->expr != NULL)
	{
		echo(" ");
		visit_expr(in->expr);
	}
	echo(";");
	// newline output by post_commented_node
}

void AST_unparser::children_static_declaration(Static_declaration* in)
{
	echo("static ");
	visit_name_with_default_list(in->vars);
	echo(";");
	// newline output by post_commented_node
}

void AST_unparser::children_global(Global* in)
{
	echo("global ");
	List<Variable_name*>::const_iterator i;
	for(i = in->variable_names->begin(); i != in->variable_names->end(); i++)
	{
		if(i != in->variable_names->begin())
			echo(", ");

		echo("$");
		visit_variable_name(*i);
	}
	echo(";");
	// newline output by post_commented_node
}

void AST_unparser::children_declare(Declare* in)
{
	echo("declare");
	visit_directive_list(in->directives);
	space_or_newline();

	if(!in->statements->empty())
	{
		visit_statement_list(in->statements);
		newline();
	}
	else
	{
		echo(";");
		// newline output by post_commented_node
	}
}

void AST_unparser::children_directive(Directive* in)
{
	visit_directive_name(in->directive_name);
	echo(" = ");
	visit_expr(in->expr);
}

void AST_unparser::children_try(Try* in)
{
	echo("try");
	space_or_newline();

	visit_statement_list(in->statements);
	space_or_newline();

	visit_catch_list(in->catches);
}

void AST_unparser::children_catch(Catch* in)
{
	echo("catch (");
	visit_class_name(in->class_name);
	echo(" $");
	visit_variable_name(in->variable_name);
	echo(")");
	space_or_newline();

	visit_statement_list(in->statements);
}

// We override post_catch_chain to avoid post_commented_node adding a newline
// after every catch (which messes up the layout when using same line curlies)
// We cannot deal with after-comments here, so we just assert that they don't
// exist and wait until somebody complains :)
void AST_unparser::post_catch_chain(Catch* in)
{
	List<String*>::const_iterator i;
	List<String*>* comments = in->get_comments();
	
	for(i = comments->begin(); i != comments->end(); i++)
	{
		assert(!((*i)->attrs->is_true("phc.unparser.comment.after")));
	}
}

void AST_unparser::children_throw(Throw* in)
{
	echo("throw ");
	visit_expr(in->expr);
	echo(";");
	// newline output by post_commented_node
}

void AST_unparser::children_eval_expr(Eval_expr* in)
{
	if(in->attrs->is_true("phc.unparser.is_inline_html"))
	{
		Method_invocation* inv;
		STRING* str;

		inv = dynamic_cast<Method_invocation*>(in->expr);
		assert(inv);
		str = dynamic_cast<STRING*>(inv->actual_parameters->front()->expr);
		assert(str);

		echo_html(str->get_source_rep ());
	}
	else
	{
		visit_expr(in->expr);
		clear_delayed_newline();
		echo(";");
		// The newline gets added by post_commented_node
	}
}

void AST_unparser::children_assignment(Assignment* in)
{
	visit_variable(in->variable);

	if(in->is_ref)
		echo(" =& ");
	else
		echo(" = ");

	visit_expr(in->expr);
}

// $a += $b;
void AST_unparser::children_op_assignment(Op_assignment* in)
{
		visit_variable(in->variable);

		echo(" ");
		visit_op(in->op);
		echo("= ");

		visit_expr(in->expr);
}

void AST_unparser::children_list_assignment(List_assignment* in)
{
	visit_list_element_list(in->list_elements);
	echo(" = ");
	visit_expr(in->expr);
}

void AST_unparser::children_cast(Cast* in)
{
	echo("(");
	visit_cast(in->cast);
	echo(") ");
	visit_expr(in->expr);
}

void AST_unparser::children_unary_op(Unary_op* in)
{
	visit_op(in->op);
	visit_expr(in->expr);
}

void AST_unparser::children_bin_op(Bin_op* in)
{
	if(*in->op->value == ".")
	{
		Linearize l;
		l.visit_expr(in);

		vector<int>::const_iterator ps;
		int i = 0;
		for(ps = l.partitions.begin(); ps != l.partitions.end(); ps++)
		{
			if(i != 0) echo(" . ");

			if(*ps == 1)
			{
				visit_expr(l.exprs[i]);
			}
			else
			{
				in_string.push(true);
			
				if(l.exprs[i]->attrs->has("phc.unparser.heredoc_id"))
				{
					echo("<<<");
					echo(l.exprs[i]->attrs->get_string("phc.unparser.heredoc_id"));
					echo("\n"); // avoid leading tabs
				}
				else
				{
					// If the first element in the partition starts_line set, 
					// we make the partition start on a new line. We have to do this here
					// rather than relying on the default action in pre_node to avoid 
					// the partition being unparsed as
					//
					// echo "
					//       foo $ bar"
					//
					// which would normally happen when 'foo' has starts_line set.
					if(l.exprs[i]->attrs->is_true("phc.unparser.starts_line"))
					{
						newline();
						echo(args_info.tab_arg);
					}

					echo("\"");
				}

				for(int j = i; j < i + *ps; j++) 
				{
					last_op.push(l.ops[j]);
					visit_expr(l.exprs[j]);
					last_op.pop();
				}

				if(l.exprs[i]->attrs->has("phc.unparser.heredoc_id"))
				{
					echo("\n");	// avoid leading tabs
					echo(l.exprs[i]->attrs->get_string("phc.unparser.heredoc_id"));
					echo_delayed_newline();
				}
				else
				{
					echo("\"");
				}

				in_string.pop();
			}

			i += *ps;
		}
	}
	else
	{
		visit_expr(in->left);
		if(*in->op->value != ",") echo(" "); // We output "3 + 5", but "3, 5"
		visit_op(in->op);
		echo(" ");
		visit_expr(in->right);
	}
}

void AST_unparser::children_conditional_expr(Conditional_expr* in)
{
	visit_expr(in->cond);
	echo(" ? ");
	visit_expr(in->iftrue);
	echo(" : ");
	visit_expr(in->iffalse);
}

void AST_unparser::children_ignore_errors(Ignore_errors* in)
{
	echo("@");
	visit_expr(in->expr);
}

void AST_unparser::children_constant(Constant* in)
{
	if(in->class_name != NULL)
	{
		visit_class_name(in->class_name);
		echo("::");
	}

	visit_constant_name(in->constant_name);
}

void AST_unparser::children_instanceof(Instanceof* in)
{
	visit_expr(in->expr);
	echo(" instanceof ");
	visit_class_name(in->class_name);
}

void AST_unparser::children_variable(Variable* in)
{
	Reflection* reflection;
	Variable* name = NULL;

	// last_op.top() applies only to the top-level variable (in), not to 
	// any variables that may be used inside in. Therefore, we copy 
	// last_op.top() to a local variable, and then push NULL to last_op
	OP* in_last_op = last_op.empty() ? NULL : last_op.top();
	last_op.push(NULL);

	if(    in_last_op != NULL   
			&& in_last_op->attrs->is_true("phc.unparser.in_string_syntax.complex"))
	{
		echo("{");
		in_string.push(false);
	}

	if(in->target != NULL)
	{
		CLASS_NAME* class_name = dynamic_cast<CLASS_NAME*>(in->target);

		if(class_name)
		{
			visit_class_name(class_name);
			echo("::$");
		}
		else
		{
			visit_target(in->target);
			echo("->");
		}
	}
	else
	{
		echo("$");
	}

	reflection = dynamic_cast<Reflection*>(in->variable_name);
	
	if(reflection)
	{
		name = dynamic_cast<Variable*>(reflection->expr);
		visit_variable_name(in->variable_name);
	}
	else
	{
		if(    in_last_op != NULL   
				&& in_last_op->attrs->is_true("phc.unparser.in_string_syntax.delimited")
			)
		{
			echo("{");
			visit_variable_name(in->variable_name);
			echo("}");
		}
		else
		{
			visit_variable_name(in->variable_name);
		}
	}

	List<Expr*>::const_iterator i;
	for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
	{
		if(*i && (*i)->attrs->is_true("phc.unparser.index_curlies"))
		{
			echo("{");
			if(*i) visit_expr(*i);
			echo("}");
		}
		else
		{
			echo("[");
			if(*i) visit_expr(*i);
			echo("]");
		}
	}

	if(    in_last_op != NULL  
			&& in_last_op->attrs->is_true("phc.unparser.in_string_syntax.complex")
		)
	{
		in_string.pop();
		echo("}");
	}
	
	last_op.pop();
}

void AST_unparser::children_reflection(Reflection* in)
{
	visit_expr(in->expr);
}

void AST_unparser::children_pre_op(Pre_op* in)
{
	visit_op(in->op);
	visit_variable(in->variable);
}

void AST_unparser::children_post_op(Post_op* in)
{
	visit_variable(in->variable);
	visit_op(in->op);
}

void AST_unparser::children_array(Array* in)
{
	echo("array");
	visit_array_elem_list(in->array_elems);
}

void AST_unparser::children_array_elem(Array_elem* in)
{
	if(in->key != NULL)
	{
		visit_expr(in->key);
		echo(" => ");
	}
	if(in->is_ref) echo("&");
	visit_expr(in->val);
}

void AST_unparser::children_method_invocation(Method_invocation* in)
{
	bool after_arrow = false;
	CLASS_NAME* static_method;

	static_method = dynamic_cast<CLASS_NAME*>(in->target);
	if(static_method)
	{
		visit_class_name(static_method);
		echo("::");
	}
	else if(in->target != NULL)
	{
		visit_target(in->target);
		echo("->");
		after_arrow = true;
	}

	if(in->attrs->is_true("phc.unparser.is_backticked"))
	{
		assert(in->actual_parameters->size() == 1);

		Linearize l;
		l.visit_expr(in->actual_parameters->front()->expr);

		assert(l.partitions.size() == 1);

		echo("`");
		in_string.push(true);
		for(int i = 0; i < l.partitions[0]; i++)
		{
			visit_expr(l.exprs[i]);
		}
		in_string.pop();
		echo("`");
	}
	else if(in->attrs->is_true("phc.unparser.no_brackets"))
	{
		visit_method_name(in->method_name);

		if(    in->actual_parameters->size() == 1 
		    && in->actual_parameters->front()->attrs->is_true("phc.unparser.is_default")
			)
		{
			// output nothing; only argument is marked as 'default' (e.g., exit;)
		}
		else
		{
			echo(" ");	
			visit_actual_parameter_list(in->actual_parameters);
		}
	}
	else if (in->match (new Method_invocation (NULL, new METHOD_NAME (new String ("echo")), NULL)))
	{
		visit_method_name(in->method_name);

		// echo ($x, $y) can't be parsed properly.
		echo(" ");
		visit_actual_parameter_list(in->actual_parameters);
	}
	else
	{
		visit_method_name(in->method_name);

		if(    in->actual_parameters->size() == 1 
		    && in->actual_parameters->front()->attrs->is_true("phc.unparser.is_default")
			)
		{
			// output nothing; only argument is marked as 'default' (e.g., exit();)
			echo("()");
		}
		else
		{
			echo("(");
			visit_actual_parameter_list(in->actual_parameters);
			echo(")");
		}
	}
}

void AST_unparser::children_actual_parameter(Actual_parameter* in)
{
	if(in->is_ref) echo("&");
	visit_expr(in->expr);
}

void AST_unparser::children_new(New* in)
{
	echo("new ");
	visit_class_name(in->class_name);

	if(in->attrs->is_true("phc.unparser.no_brackets"))
	{
		// it is only allowed to omit brackets if there are no parameters
		assert(in->actual_parameters->size() == 0);
	}
	else
	{
		echo("(");
		visit_actual_parameter_list(in->actual_parameters);
		echo(")");
	}
}

void AST_unparser::visit_interface_name_list(List<INTERFACE_NAME*>* in)
{
	List<INTERFACE_NAME*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_interface_name(*i);
	}
}

void AST_unparser::visit_member_list(List<Member*>* in)
{
	newline();
	echo_nl("{");
	inc_indent();

	Visitor::visit_member_list(in);	

	dec_indent();
	echo_nl("}");
}

void AST_unparser::visit_statement_list(List<Statement*>* in)
{
	bool no_curlies = in->size() == 1 && in->front()->attrs->is_true("phc.unparser.is_wrapped");

	if(!no_curlies) echo("{");
	inc_indent();

	Visitor::visit_statement_list(in);

	dec_indent();
	if(!no_curlies) echo("}");
}

void AST_unparser::visit_formal_parameter_list(List<Formal_parameter*>* in)
{
	echo("(");
	List<Formal_parameter*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_formal_parameter(*i);
	}
	echo(")");
}

void AST_unparser::visit_switch_case_list(List<Switch_case*>* in)
{
	echo_nl("{");
	inc_indent();

	List<Switch_case*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
		visit_switch_case(*i);

	dec_indent();
	echo_nl("}");
}

void AST_unparser::visit_directive_list(List<Directive*>* in)
{
	echo("(");

	List<Directive*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_directive(*i);
	}
	
	echo(")");
}

void AST_unparser::visit_catch_list(List<Catch*>* in)
{
	List<Catch*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) space_or_newline();
		visit_catch(*i);
	}
}

void AST_unparser::visit_list_element_list(List<List_element*>* in)
{
	echo("list(");

	List<List_element*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		if(*i) visit_list_element(*i);
	}

	echo(")");
}

void AST_unparser::visit_expr_list(List<Expr*>* in)
{
	List<Expr*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
		if(*i) visit_expr(*i);
}

void AST_unparser::visit_array_elem_list(List<Array_elem*>* in)
{
	echo("(");

	List<Array_elem*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_array_elem(*i);
	}

	echo(")");
}

void AST_unparser::visit_actual_parameter_list(List<Actual_parameter*>* in)
{
	List<Actual_parameter*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_actual_parameter(*i);
	}
}

void AST_unparser::visit_name_with_default_list(List<Name_with_default*>* in)
{
	List<Name_with_default*>::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_name_with_default(*i);
	}
}

// Token classes
void AST_unparser::children_interface_name(INTERFACE_NAME* in)
{
	echo(in->value);
}

void AST_unparser::children_class_name(CLASS_NAME* in)
{
	echo(in->value);
}

void AST_unparser::children_method_name(METHOD_NAME* in)
{
	echo(in->value);
}

void AST_unparser::children_variable_name(VARIABLE_NAME* in)
{
	echo(in->value);
}

void AST_unparser::children_directive_name(DIRECTIVE_NAME* in)
{
	echo(in->value);
}

void AST_unparser::children_cast(CAST* in)
{
	echo(in->get_source_rep ());
}

void AST_unparser::children_op(OP* in)
{
	echo(in->value);
}

void AST_unparser::children_constant_name(CONSTANT_NAME* in)
{
	echo(in->value);
}

void AST_unparser::children_int(INT* in)
{
	echo(in->get_source_rep ());
}

void AST_unparser::children_real(REAL* in)
{
	echo(in->get_source_rep ());
}

void AST_unparser::children_string(STRING* in)
{
	if(
			*in->get_source_rep () == "__FILE__" ||
			*in->get_source_rep () == "__CLASS__" ||
			*in->get_source_rep () == "__METHOD__" ||
			*in->get_source_rep () == "__FUNCTION__"
	  )
	{
		echo(in->get_source_rep ());
	}
	else
	{
    // any escaping must already be present in source_rep; any strings that
    // originate from the user will be escaped as the user escaped them,
    // and any strings that originate from passes within the compiler should
    // have been escaped by those passes
	
		if(in_string.top())
		{
			echo(in->get_source_rep ());
		}
		else
		{
	    if(in->attrs->is_true("phc.unparser.is_doubly_quoted"))
			{
				echo("\"");
				echo(in->get_source_rep ());
				echo("\"");
			}
			else if(in->attrs->has("phc.unparser.heredoc_id"))
			{
				echo("<<<");
				echo(in->attrs->get_string("phc.unparser.heredoc_id"));
				echo("\n"); // avoid leading tabs
				echo(in->get_source_rep ()); 
				echo("\n");
				echo(in->attrs->get_string("phc.unparser.heredoc_id"));
				echo_delayed_newline();
			}
			else 
			{
				echo("'");
				if (in->has_source_rep ())
					echo(in->get_source_rep ());
				else
					echo(escape_sq (in->get_source_rep ()));
				echo("'");
			}
		}
	}
}

void AST_unparser::children_bool(BOOL* in)
{
	echo(in->get_source_rep ());
}

void AST_unparser::children_nil(NIL* in)
{
	echo(in->get_source_rep ());
}

// Generic classes
void AST_unparser::pre_node(Node* in)
{
	if(    in->attrs->is_true("phc.unparser.starts_line")
			&& !in_string.top()
	  )
	{
		newline();
		echo(args_info.tab_arg);
	}
}

/* There are a number of places where curlies are required. All of these
 * involves reflection, and some special cases in the node containing the
 * reflected variable. In general $$$$x (ie any amunt of nested variabels) is
 * ok, and anything else requires curlies. */
bool needs_curlies (Reflection* in)
{
	Variable* var = dynamic_cast <Variable*> (in->expr);
	if (var 
		&& var->target == NULL
		&& var->array_indices->size() == 0)
		return false;

	return true;
}

void AST_unparser::pre_variable (Variable* in)
{
	Reflection* reflect = dynamic_cast<Reflection*>(in->variable_name);
	if (reflect && 
			(needs_curlies (reflect) || in->array_indices->size () > 0))
		reflect->expr->attrs->set_true ("phc.unparser.needs_curlies");
}

void AST_unparser::pre_method_invocation (Method_invocation* in)
{
	Reflection* reflect = dynamic_cast<Reflection*>(in->method_name);
	if (in->target
			&& reflect && needs_curlies (reflect))
		reflect->expr->attrs->set_true ("phc.unparser.needs_curlies");
}

void AST_unparser::pre_global (Global* in)
{
	List<Variable_name*>::const_iterator i;
	for(i = in->variable_names->begin(); i != in->variable_names->end(); i++)
	{
		Reflection* reflect = dynamic_cast<Reflection*>(*i);
		if (reflect && needs_curlies (reflect))
			reflect->expr->attrs->set_true ("phc.unparser.needs_curlies");
	}
}

void AST_unparser::pre_expr(Expr* in)
{
	if(in->attrs->is_true("phc.unparser.needs_user_brackets"))
		echo("(");
	if(in->attrs->is_true("phc.unparser.needs_curlies") or in->attrs->is_true("phc.unparser.needs_user_curlies"))
		echo("{");
}

void AST_unparser::post_expr(Expr* in)
{
	if(in->attrs->is_true("phc.unparser.needs_curlies") or in->attrs->is_true("phc.unparser.needs_user_curlies"))
		echo("}");
	if(in->attrs->is_true("phc.unparser.needs_user_brackets"))
		echo(")");
}

void AST_unparser::pre_bin_op (Bin_op* in)
{
	if(!in->attrs->is_true("phc.unparser.no_binop_brackets")
		&& (*in->op->value != ","))
		echo("(");
}

void AST_unparser::post_bin_op (Bin_op* in)
{
	if(!in->attrs->is_true("phc.unparser.no_binop_brackets")
		&& (*in->op->value != ","))
		echo(")");
}

void AST_unparser::pre_commented_node(Commented_node* in)
{
	List<String*>::const_iterator i;
	List<String*>* comments = in->get_comments();
	for(i = comments->begin(); i != comments->end(); i++)
	{
		if(!(*i)->attrs->is_true("phc.unparser.comment.after"))
		{
			echo(*i);
			newline();
		}
	}
}

// Note: does not get executed for Catch (which overrides post_catch_chain)
void AST_unparser::post_commented_node(Commented_node* in)
{
	List<String*>::const_iterator i;
	List<String*>* comments = in->get_comments();

	for(i = comments->begin(); i != comments->end(); i++)
	{
		if((*i)->attrs->is_true("phc.unparser.comment.after"))
		{
			if(!at_start_of_line) echo(" ");
			echo(*i);
			newline();
		}
	}

	if(!at_start_of_line) newline();
}

void AST_unparser::children_label_name (LABEL_NAME* in)
{
	echo(in->value);
}

void AST_unparser::children_goto (Goto* in)
{
	echo ("goto ");
	visit_label_name (in->label_name);
	echo_nl (";");
}

void AST_unparser::children_label (Label* in)
{
	visit_label_name (in->label_name);
	echo_nl(":");
}

void AST_unparser::children_nop (Nop* in)
{
	// If the NOP is the only statement is a block, and there are no curlies
	// around it, we must output the semi-colon
	if(in->attrs->is_true("phc.unparser.is_wrapped"))
		echo(";");
}

void AST_unparser::children_name_with_default (Name_with_default* in)
{
	echo("$");
	visit_variable_name(in->variable_name);
	if(in->expr != NULL)
	{
		echo(" = ");
		visit_expr(in->expr);
	}
}
