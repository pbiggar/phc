/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * This unparses the MIR in a C-style, intending to make references and
 * dereferences and pointers explicit within the code.
 */

#include <iostream>
#include <iomanip> 

#include "process_ir/General.h"
#include "pass_manager/Plugin_pass.h"

using namespace std;
using namespace MIR;

class C_unparser 
: public PHP_unparser, public Visitor
{
public:
	C_unparser (ostream& os, bool in_php)
	: PHP_unparser (os, in_php)
	{
	}

	void unparse (IR::Node* in)
	{
		(dyc <MIR::PHP_script> (in))->visit (this);
	}

	/* Variables in their various contexts. */
	void read_rvalue (Rvalue* in)
	{
		if (isa<Literal> (in))
			visit_rvalue (in);
		else
		{
			echo ("(*");
			visit_rvalue (in);
			echo (")");
		}
	}
	void reference_rvalue (Rvalue* in)
	{
		visit_rvalue (in);
	}

	void reference_expr (Expr* in)
	{
		visit_expr (in);
	}

	void read_expr_value (Expr* in)
	{
		// Not sure how best to handle this. Just add a * where necessary for now
		switch (in->classid ())
		{
			case INT::ID:
			case STRING::ID:
			case NIL::ID:
			case REAL::ID:
			case BOOL::ID:
			case Bin_op::ID:
			case Unary_op::ID:
				visit_expr (in);
				break;
			default:
				echo ("(*");
				visit_expr (in);
				echo (")");
		}
	}

	void write_var_ref (VARIABLE_NAME* in)
	{
		visit_variable_name (in);
	}

	void write_var_value (VARIABLE_NAME* in)
	{
		echo ("(*");
		visit_variable_name (in);
		echo (")");
	}

	void reference_var (VARIABLE_NAME* in)
	{
		visit_variable_name (in);
	}

	void read_var_value (VARIABLE_NAME* in)
	{
		echo ("(*");
		visit_variable_name (in);
		echo (")");
	}

	/* statements */
	void children_assign_var(Assign_var* in)
	{
		if(in->is_ref)
		{
			write_var_ref (in->lhs);
			echo(" = ");
			reference_expr (in->rhs);
		}
		else
		{
			write_var_value (in->lhs);
			echo(" = ");
			read_expr_value (in->rhs);
		}
	}

	void children_eval_expr (Eval_expr* in)
	{
		read_expr_value (in->expr);
	}

	void children_branch (Branch* in)
	{
		echo ("if (");
		read_var_value (in->variable_name);
		echo (") goto ");
		visit_label_name (in->iftrue);
		echo ("; else goto ");
		visit_label_name (in->iffalse);
	}

	void children_label (Label* in)
	{
		visit_label_name (in->label_name);
		echo(":");
	}

	void post_statement (Statement* in)
	{
		echo_nl(";");
	}

	/* exprs */

	void children_variable_name(VARIABLE_NAME* in)
	{
		echo(in->value);
	}

	void children_method_invocation (Method_invocation* in)
	{
		visit_method_name (in->method_name);
		echo ("(");
		foreach (Actual_parameter* param, *in->actual_parameters)
		{
			visit_actual_parameter (param);
			if (param != in->actual_parameters->back ())
				echo (", ");
		}
		echo (")");
	}

	void children_bin_op (Bin_op* in)
	{
		read_rvalue (in->left);
		echo (" ");
		echo (in->op->value);
		echo (" ");
		read_rvalue (in->right);
	}

	void children_int (INT* in)
	{
		echo(in->get_value_as_string());
	}
	void children_string (STRING* in)
	{
		echo ("\"");
		echo(in->get_value_as_string());
		echo ("\"");
	}
	void children_nil (NIL* in)
	{
		echo("NULL");
	}
	void children_real (REAL* in)
	{
		echo(in->get_value_as_string());
	}
	void children_bool (BOOL* in)
	{
		echo(in->get_value_as_string());
	}








	/* non-exprs */

	void children_method_name (METHOD_NAME* in)
	{
		echo (in->value);
	}

	void children_label_name (LABEL_NAME* in)
	{
		echo (in->value);
	}

	void children_actual_parameter (Actual_parameter* in)
	{
		// TODO: we need the method signature to simplify this
		// If we dont know how the variable is being passed, conservatively
		// assume its by reference.
//		if (!isa<Literal> (in->rvalue))
//			echo ("*");

		reference_rvalue (in->rvalue);
	}

	void children_method (Method* in)
	{
		echo ("void ");
		visit_method_name (in->signature->method_name);
		echo_nl ("()");
		echo_nl ("{");
		visit_statement_list (in->statements);
		echo_nl ("}");
	}

};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("lfc"));
}

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager* pm, String* option)
{
	C_unparser* cup = new C_unparser (cout, true);
	cup->unparse (in);
}

/*
 * The unparser proper
 */
#if 0
void C_unparser::children_php_script(PHP_script* in)
{
	// We don't call output_start_tag here, because the first statement
	// of the script maybe INLINE_HTML. We rely on the infrastructure in
	// PHP_unparser to output the tags when we need them

	// We don't want to output the { and }, so we manually traverse the list
	foreach (Statement* s, *in->statements)
		visit_statement(s);
	
	// However, to avoid not outputting a closing tag, we do call 
	// output_end_tag. If one was output already, nothing will happen
	output_end_tag();
}

void C_unparser::children_interface_def(Interface_def* in)
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

void C_unparser::children_class_def(Class_def* in)
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

void C_unparser::children_class_mod(Class_mod* in)
{
	if(in->is_abstract) echo("abstract ");
	if(in->is_final) echo("final ");
}

void C_unparser::children_method(Method* in)
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

void C_unparser::children_signature(Signature* in)
{
	visit_method_mod(in->method_mod);
	echo("function ");
	if(in->return_by_ref) echo("&");
	visit_method_name(in->method_name);
	visit_formal_parameter_list(in->formal_parameters);
}

void C_unparser::children_method_mod(Method_mod* in)
{
	if(in->is_public)		echo("public ");
	if(in->is_protected)	echo("protected ");
	if(in->is_private)	echo("private ");
	if(in->is_static)		echo("static ");
	if(in->is_abstract)	echo("abstract ");
	if(in->is_final)		echo("final ");
}

void C_unparser::children_formal_parameter(Formal_parameter* in)
{
	visit_type(in->type);
	if(in->is_ref) echo("&");
	visit_name_with_default(in->var);
}

void C_unparser::children_type(Type* in)
{
	if(in->class_name != NULL)
	{
		visit_class_name(in->class_name);
		echo(" ");
	}
}

void C_unparser::children_attribute(Attribute* in)
{
	visit_attr_mod(in->attr_mod);
	// Class attributes get a dollar sign, with the exception of const attributes
	if(!in->attr_mod->is_const) echo("$"); 
	visit_variable_name(in->var->variable_name);
	if(in->var->default_value != NULL)
	{
		echo(" = ");
		visit_static_value(in->var->default_value);
	}
	echo(";");
	// newline is output by post_commented_node
}

void C_unparser::children_attr_mod(Attr_mod* in)
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

void C_unparser::children_return(Return* in)
{
	echo("return");
	if(in->variable_name != NULL)
	{
		echo(" ");
		visit_variable_name(in->variable_name);
	}
	echo(";");
	// newline output by post_commented_node
}

void C_unparser::children_static_declaration(Static_declaration* in)
{
	echo("static ");
	visit_name_with_default (in->var);
	echo(";");
	// newline output by post_commented_node
}

void C_unparser::children_global(Global* in)
{
	echo("global ");
	
	echo("$");
	visit_variable_name(in->variable_name);
	echo(";");
	// newline output by post_commented_node
}

void C_unparser::children_try(Try* in)
{
	echo("try");
	space_or_newline();

	visit_statement_list(in->statements);
	space_or_newline();

	visit_catch_list(in->catches);
}

void C_unparser::children_catch(Catch* in)
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
void C_unparser::post_catch_chain(Catch* in)
{
}

void C_unparser::children_throw(Throw* in)
{
	echo("throw ");
	visit_variable_name(in->variable_name);
	echo(";");
}

void C_unparser::children_eval_expr(Eval_expr* in)
{
	visit_expr(in->expr);
	echo(";");
}

void C_unparser::children_assign_var(Assign_var* in)
{
	visit_variable_name (in->lhs);

	if(in->is_ref)
		echo(" =& ");
	else
		echo(" = ");

	visit_expr(in->rhs);
}

void C_unparser::children_cast(Cast* in)
{
	echo("(");
	visit_cast(in->cast);
	echo(") ");
	visit_variable_name(in->variable_name);
}

void C_unparser::children_unary_op(Unary_op* in)
{
	visit_op(in->op);

	// Special case for '-': avoid --1 (-+ or +- is OK)
	Literal* lit;
	Wildcard<Expr> outer, inner;

	if (in->match (new Unary_op (&outer, "-")))
	{
		if (outer.value->match (new Unary_op (&inner, "-"))
				|| ((lit = dynamic_cast<Literal*> (outer.value))
					&& (*lit->get_value_as_string ())[0] == '-'))
			echo (" ");
	}


	visit_expr(in->expr);
}

void C_unparser::children_bin_op(Bin_op* in)
{
	if(*in->op->value == ".")
	{
		Linearize l;
		l.visit_expr(in);

		Vector<int>::const_iterator ps;
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

void C_unparser::children_conditional_expr(Conditional_expr* in)
{
	visit_expr(in->cond);
	echo(" ? ");
	visit_expr(in->iftrue);
	echo(" : ");
	visit_expr(in->iffalse);
}

void C_unparser::children_ignore_errors(Ignore_errors* in)
{
	echo("@");
	visit_expr(in->expr);
}

void C_unparser::children_constant(Constant* in)
{
	if(in->class_name != NULL)
	{
		visit_class_name(in->class_name);
		echo("::");
	}

	visit_constant_name(in->constant_name);
}

void C_unparser::children_instanceof(Instanceof* in)
{
	visit_expr(in->expr);
	echo(" instanceof ");
	visit_class_name(in->class_name);
}

void C_unparser::children_variable(Variable* in)
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

	foreach (Expr* expr, *in->array_indices)
	{
		if(expr && expr->attrs->is_true("phc.unparser.index_curlies"))
		{
			echo("{");
			if(expr) visit_expr(expr);
			echo("}");
		}
		else
		{
			echo("[");
			if(expr) visit_expr(expr);
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

void C_unparser::children_reflection(Reflection* in)
{
	visit_expr(in->expr);
}

void C_unparser::children_pre_op(Pre_op* in)
{
	visit_op(in->op);
	visit_variable(in->variable);
}

void C_unparser::children_post_op(Post_op* in)
{
	visit_variable(in->variable);
	visit_op(in->op);
}

void C_unparser::children_array(Array* in)
{
	echo("array");
	visit_array_elem_list(in->array_elems);
}

void C_unparser::children_array_elem(Array_elem* in)
{
	if(in->key != NULL)
	{
		visit_expr(in->key);
		echo(" => ");
	}
	if(in->is_ref) echo("&");
	visit_expr(in->val);
}

void C_unparser::children_method_invocation(Method_invocation* in)
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

void C_unparser::children_actual_parameter(Actual_parameter* in)
{
	if(in->is_ref) echo("&");
	visit_expr(in->expr);
}

void C_unparser::children_new(New* in)
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

void C_unparser::visit_interface_name_list(INTERFACE_NAME_list* in)
{
	INTERFACE_NAME_list::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_interface_name(*i);
	}
}

void C_unparser::visit_member_list(Member_list* in)
{
	newline();
	echo_nl("{");
	inc_indent();

	Visitor::visit_member_list(in);	

	dec_indent();
	echo_nl("}");
}

void C_unparser::visit_statement_list(Statement_list* in)
{
	bool no_curlies = in->size() == 1 && in->front()->attrs->is_true("phc.unparser.is_wrapped");

	if(!no_curlies) echo("{");
	inc_indent();

	Visitor::visit_statement_list(in);

	dec_indent();
	if(!no_curlies) echo("}");
}

void C_unparser::visit_formal_parameter_list(Formal_parameter_list* in)
{
	echo("(");
	Formal_parameter_list::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_formal_parameter(*i);
	}
	echo(")");
}

void C_unparser::visit_switch_case_list(Switch_case_list* in)
{
	echo_nl("{");
	inc_indent();

	Switch_case_list::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
		visit_switch_case(*i);

	dec_indent();
	echo_nl("}");
}

void C_unparser::visit_directive_list(Directive_list* in)
{
	echo("(");

	Directive_list::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_directive(*i);
	}
	
	echo(")");
}

void C_unparser::visit_catch_list(Catch_list* in)
{
	Catch_list::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) space_or_newline();
		visit_catch(*i);
	}
}

void C_unparser::visit_list_element_list(List_element_list* in)
{
	echo("list(");

	List_element_list::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		if(*i) visit_list_element(*i);
	}

	echo(")");
}

void C_unparser::visit_expr_list(Expr_list* in)
{
	foreach (Expr* expr, *in)
		if(expr) visit_expr(expr);
}

void C_unparser::visit_array_elem_list(Array_elem_list* in)
{
	echo("(");

	Array_elem_list::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_array_elem(*i);
	}

	echo(")");
}

void C_unparser::visit_actual_parameter_list(Actual_parameter_list* in)
{
	Actual_parameter_list::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_actual_parameter(*i);
	}
}

void C_unparser::visit_name_with_default_list(Name_with_default_list* in)
{
	Name_with_default_list::const_iterator i;
	for(i = in->begin(); i != in->end(); i++)
	{
		if(i != in->begin()) echo(", ");
		visit_name_with_default(*i);
	}
}

// Token classes
void C_unparser::children_interface_name(INTERFACE_NAME* in)
{
	echo(in->value);
}

void C_unparser::children_class_name(CLASS_NAME* in)
{
	echo(in->value);
}

void C_unparser::children_method_name(METHOD_NAME* in)
{
	echo(in->value);
}

void C_unparser::children_variable_name(VARIABLE_NAME* in)
{
	echo(in->value);
}

void C_unparser::children_directive_name(DIRECTIVE_NAME* in)
{
	echo(in->value);
}

void C_unparser::children_cast(CC* in)
{
	echo(in->get_source_rep ());
}

void C_unparser::children_op(OP* in)
{
	echo(in->value);
}

void C_unparser::children_constant_name(CONSTANT_NAME* in)
{
	echo(in->value);
}

void C_unparser::children_int(INT* in)
{
	echo(in->get_source_rep ());
}

void C_unparser::children_real(REAL* in)
{
	echo(in->get_source_rep ());
}

void C_unparser::children_string(STRING* in)
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

void C_unparser::children_bool(BOOL* in)
{
	echo(in->get_source_rep ());
}

void C_unparser::children_nil(NIL* in)
{
	echo(in->get_source_rep ());
}

// Generic classes
void C_unparser::pre_node(Node* in)
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

void C_unparser::pre_variable (Variable* in)
{
	Reflection* reflect = dynamic_cast<Reflection*>(in->variable_name);
	if (reflect && 
			(needs_curlies (reflect) || in->array_indices->size () > 0))
		reflect->expr->attrs->set_true ("phc.unparser.needs_curlies");
}

void C_unparser::pre_method_invocation (Method_invocation* in)
{
	Reflection* reflect = dynamic_cast<Reflection*>(in->method_name);
	if (in->target
			&& reflect && needs_curlies (reflect))
		reflect->expr->attrs->set_true ("phc.unparser.needs_curlies");
}

void C_unparser::pre_global (Global* in)
{
	foreach (Variable_name* vn, *in->variable_names)
	{
		Reflection* reflect = dynamic_cast<Reflection*>(vn);
		if (reflect && needs_curlies (reflect))
			reflect->expr->attrs->set_true ("phc.unparser.needs_curlies");
	}
}

void C_unparser::pre_expr(Expr* in)
{
	if(in->attrs->is_true("phc.unparser.needs_user_brackets"))
		echo("(");
	if(in->attrs->is_true("phc.unparser.needs_curlies") or in->attrs->is_true("phc.unparser.needs_user_curlies"))
		echo("{");
}

void C_unparser::post_expr(Expr* in)
{
	if(in->attrs->is_true("phc.unparser.needs_curlies") or in->attrs->is_true("phc.unparser.needs_user_curlies"))
		echo("}");
	if(in->attrs->is_true("phc.unparser.needs_user_brackets"))
		echo(")");
}

void C_unparser::pre_bin_op (Bin_op* in)
{
	if(!in->attrs->is_true("phc.unparser.no_binop_brackets")
		&& (*in->op->value != ","))
		echo("(");
}

void C_unparser::post_bin_op (Bin_op* in)
{
	if(!in->attrs->is_true("phc.unparser.no_binop_brackets")
		&& (*in->op->value != ","))
		echo(")");
}

void C_unparser::pre_commented_node(Commented_node* in)
{
	foreach (String* s, *in->get_comments ())
	{
		if(!s->attrs->is_true("phc.unparser.comment.after"))
		{
			echo(s);
			newline();
		}
	}
}

// Note: does not get executed for Catch (which overrides post_catch_chain)
void C_unparser::post_commented_node(Commented_node* in)
{
	foreach (String* s, *in->get_comments ())
	{
		if(s->attrs->is_true("phc.unparser.comment.after"))
		{
			if(!ups->at_start_of_line) echo(" ");
			echo(s);
			newline();
		}
	}

	if(!ups->at_start_of_line) newline();
}

void C_unparser::children_nop (Nop* in)
{
	// If the NOP is the only statement is a block, and there are no curlies
	// around it, we must output the semi-colon
	if(in->attrs->is_true("phc.unparser.is_wrapped"))
		echo(";");
}

void C_unparser::children_name_with_default (Name_with_default* in)
{
	echo("$");
	visit_variable_name(in->variable_name);
	if(in->expr != NULL)
	{
		echo(" = ");
		visit_expr(in->expr);
	}
}

void C_unparser::pre_foreign(FOREIGN* in)
{
	assert (0);
}
#endif
