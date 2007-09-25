/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate C code
 *
 * Currently, the C code is generated directly from the AST; once we have an
 * IR, the C code will be generated from the IR instead.
 *
 * We define a virtual class "Pattern" which corresponds to a particular kind
 * of statement that we can generate code for. We inherit from Pattern to 
 * define the various statements we can translate, create instances of each
 * of these classes, and then for every statement in the input, cycle through
 * all the patterns to find one that matches, and then call "generate_code"
 * on that pattern.
 *
 * We rely on the Shredder, Lower_control_flow and Lower_expr_flow. In a few
 * places, however, we still need a "new" temporary, but these temporaries all
 * have in common that they are short-lived (we never need to call "fresh",
 * for instance). Where we need these, we open a local C scope, and then just
 * use a descriptive name; the life-span of the temporary then is limited to
 * this scope. The equivalent of opening a local C scope when generating 
 * assembly code instead would simply be a temporary value on the stack.
 */

#include <fstream>
#include "Generate_C.h"
#include "embed/embed.h"
#include "process_ast/XML_unparser.h"
#include "lib/List.h"
#include "process_ast/PHP_unparser.h"
#include <set>

// A single pass isnt really sufficient, but we can hack around it
// with a prologue and an epilogue.
static ostringstream prologue;
static ostringstream code;
static ostringstream epilogue;

// TODO this is here for constant pooling. This should not be global.
static gengetopt_args_info* args_info;

void Generate_C::run (AST_php_script* in, Pass_manager* pm)
{
	args_info = pm->args_info;
	if (!pm->args_info->generate_c_flag 
		&& !pm->args_info->compile_flag)
		return;

	if (pm->args_info->extension_given)
	{
		extension_name = new String (pm->args_info->extension_arg);
		is_extension = true;
	}
	else
	{
		extension_name = new String("app");
		is_extension = false;
	}

	in->visit (this);

	os << prologue.str ();
	os << code.str ();
	os << epilogue.str ();

	if (pm->args_info->generate_c_flag)
	{
		cout << prologue.str ();
		cout << code.str ();
		cout << epilogue.str ();
	}
}

/* TODO any non-top-level class or function should be promoted to a top-level
 * class/function with a different name, and it its place to be a call to
 * "register_dynamic_class(C, __phc__C1__)". Top-level classes and functions
 * are marked with the "phc.lower_control_flow.top_level_declaration"
 * attribute. */

/*
 * After the shredder, many expressions can only contain "simple" variables.
 * For example, where a bin-op could contain arbitrary expressions on the left
 * and right, after the shredder, both of those expressions must be a simple
 * variable; that is, a variable with a Token_variable_name as name, no target,
 * and no array indices. Wherever we assume this, we use this function
 * "operand" to extract the variable name. That factors out a bit of recurring
 * code, and also flags where we make this assumption.
 */

String* operand(AST_expr* in)
{
	AST_variable* var;
	Token_variable_name* var_name;
	static PHP_unparser pup(cerr);

	assert(in);
	
	var = dynamic_cast<AST_variable*>(in);
	if(var == NULL)
	{
		cerr << "Expected simple variable but got expression ";
		in->visit(&pup);
		if(in->get_line_number() != 0)
			cerr << " on line " << in->get_line_number();
		cerr << endl;
		assert(0);
	}
	if(var->target != NULL)
	{
		cerr << "Expected simple variable but got field access ";
		in->visit(&pup);
		if(in->get_line_number() != 0)
			cerr << " on line " << in->get_line_number();
		cerr << endl;
		assert(0);
	}
	if(var->array_indices->size() != 0)
	{
		cerr << "Expected simple variable but got array index ";
		in->visit(&pup);
		if(in->get_line_number() != 0)
			cerr << " on line " << in->get_line_number();
		cerr << endl;
		assert(0);
	}

	var_name = dynamic_cast<Token_variable_name*>(var->variable_name);
	if(var_name == NULL)
	{
		cerr << "Expected simple variable but got variable variable ";
		in->visit(&pup);
		if(in->get_line_number() != 0)
			cerr << " on line " << in->get_line_number();
		cerr << endl;
		assert(0);
	}

	return var_name->value;
}

enum Scope { LOCAL, GLOBAL };
string get_scope (Scope scope)
{
	if(scope == LOCAL)
		return "EG(active_symbol_table)";
	else
		return "&EG(symbol_table)";
}

string get_hash (String* name)
{
	// the "u" at the end of the constant makes it unsigned, which
	// stops gcc warning us about it.
	stringstream ss;
	ss << PHP::get_hash (name) << "u";
	return ss.str ();
}

string get_hash (Token_variable_name* name)
{
	return get_hash (name->value);
}

void declare (string var)
{
	code 
		<< "zval* " << var << ";\n"
		<< "int is_" << var << "_new = 0;\n";
}

void cleanup (string target)
{
	code
		<< "if (is_" << target << "_new)\n"
		<< "  zval_ptr_dtor (&" << target << ");\n";
}

String* get_non_st_name (Token_variable_name* var_name)
{
	assert (var_name->attrs->is_true ("phc.codegen.st_entry_not_required"));

	stringstream ss;
	ss << "local_" << *var_name->value;
	return new String (ss.str ());
}



// Generate calls to read_var, for array and array index lookups, and the like.
void read_simple (Scope scope, string zvp, Token_variable_name* var_name)
{
	if (scope == LOCAL && var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
	{
		String* name = get_non_st_name (var_name);
		code 
			<< "zval* " << zvp << ";\n"
			<< "if (" << *name << " == NULL)\n"
			<< "{\n"
			<<		zvp << " = EG (uninitialized_zval_ptr);\n"
			<< "}\n"
			<< "else\n"
			<< "{\n"
			<<		zvp << " = " << *name << ";\n"
			<< "}\n";
	}
	else
	{
		String* name = var_name->value;
		code
			<< "zval* " << zvp << "= read_var (" 
			<<								get_scope (scope) << ", "
			<<								"\"" << *name << "\", "
			<<								name->size () + 1  << ", "
			<<									get_hash (name) << " TSRMLS_CC);\n";
	}
}

void read_st (Scope scope, string zvp, Token_variable_name* var_name)
{
	if (scope == LOCAL && var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
	{
		String* name = get_non_st_name (var_name);
		code 
			<< "if (" << *name << " == NULL)\n"
			<< "{\n"
			<<		*name << " = EG (uninitialized_zval_ptr);\n"
			<<		*name << "->refcount++;\n"
			<< "}\n"
			<<	"zval** " << zvp << " = &" << *name << ";\n";
	}
	else
	{
		// Segfaults will serve as assertions
		String* name = var_name->value;
		code
			<< "zval** " << zvp << "= get_st_entry (" 
			<<									get_scope (scope) << ", "
			<<									"\"" << *name << "\", "
			<<									name->size () + 1  << ", "
			<<									get_hash (name) << " TSRMLS_CC);\n";
	}
}

// Note this can return NULL if its not a variable name
Token_variable_name* get_var_name (AST_expr* var_expr)
{
	AST_variable* var = dynamic_cast<AST_variable*> (var_expr);
	assert (var);
	Token_variable_name* name = dynamic_cast<Token_variable_name*> (var->variable_name);
	return name;
}

Token_variable_name* get_var_name (AST_reflection* var_refl)
{
	AST_variable* var = dynamic_cast<AST_variable*> (var_refl->expr);
	assert (var);
	Token_variable_name* name = dynamic_cast<Token_variable_name*> (var->variable_name);
	return name;
}



/* Generate code to write ZVP, a variable in the generated code,
 * to VAR, a named variable. */
void write (Scope scope, string zvp, AST_variable* var)
{
	// Variable variable or ordinary variable?
	Token_variable_name* token_name
		= dynamic_cast<Token_variable_name*>(var->variable_name);

	// TODO: deal with object indexing
	assert(var->target == NULL);

	if (token_name != NULL)
	{
		if (var->array_indices->size() == 1)
		{
			// access var as an array
			if (var->array_indices->front () != NULL)
			{
				code
					<< "// Array assignment\n";

				read_simple (scope, "wa_index", get_var_name (var->array_indices->front ()));
				read_st (scope, "w_array", get_var_name (var));

				code
					<< "write_array ("
					<<		get_scope (scope) << ", "
					<<		"w_array, "
					<<		"wa_index, "
					<<		"&" << zvp << ", "
					<<		"&is_" << zvp << "_new TSRMLS_CC);\n";
			}
			else
			{
				read_st (scope, "w_array", get_var_name (var));

				code
					<< "// Array pushing\n"
					<< "push_var ("
					<<		get_scope (scope) << ", "
					<<		"w_array, "
					<<		"&" << zvp << ", "
					<<		"&is_" << zvp << "_new TSRMLS_CC);\n";
			}
		}
		else
		{
			read_st (scope, "w_var", get_var_name (var));
			code 
				<< "// Normal assignment\n"
				<< "write_var (" 
				<<		get_scope (scope) << ", "
				<<		"w_var, "
				<<		"&" << zvp << ", "
				<<		"&is_" << zvp << "_new TSRMLS_CC);\n";
		}
	}
	else
	{
		// Variable variable.
		// After shredder, a variable variable cannot have array indices
		assert(var->array_indices->size() == 0);
		assert (0);

		code << "assert (0); // write_var_var \n";
//		write_var_var ();
	}
}

/* Separate the rhs, and write it back to the symbol table if necessary */
void separate (Scope scope, string zvp, AST_expr* expr)
{
	AST_variable* var = dynamic_cast<AST_variable*> (expr);
	Token_variable_name* var_name = get_var_name (expr);

	// if its new, check it wont separate
	code 
		<< "if (is_" << zvp << "_new)\n"
		<<	"	assert (!(" << zvp << "->refcount > 1 "
		<<	"		&& !" << zvp << "->is_ref));\n";

	assert(var->target == NULL);

	if (var_name != NULL)
	{
		read_st (scope, "sep_var", var_name);
		if (var->array_indices->size() == 1)
		{
			// access var as an array
			if (var->array_indices->front () != NULL)
			{
				read_simple (scope, "sa_index", get_var_name (var->array_indices->front ()));
				code
					<< "separate_array_entry ("
					<<		get_scope (scope) << ", "
					<<		"sep_var, "
					<<		"sa_index, "
					<<		"&" << zvp << ", "
					<<		"&is_" << zvp << "_new "
					<<		" TSRMLS_CC);\n";
			}
			else
			{
				assert (0); // no push version
			}
		}
		else
		{
			assert (var->array_indices->size() == 0);
			code 
				<< "separate_var (" 
				<<		get_scope (scope) << ", "
				<<		"sep_var, "
				<<		"&is_" << zvp << "_new "
				<< " TSRMLS_CC);\n";

			// TODO this can be removed when we move to zval**s instead
			// of zval*s for rhss
			code 
				<< zvp << " = *sep_var;\n";
		}
	}
	else
	{
		// Variable variable.
		// After shredder, a variable variable cannot have array indices
		assert (0); // TODO
		assert (var->array_indices->size() == 0);

		code << "assert (0); // separate_var_var\n";
//		separate_var_var ();
	}
}

/* Generate code to write ZVP, a variable in the generated code,
 * to LHS, a named variable. RHS is needed for the reference. */
void write_reference (Scope scope, string zvp, AST_variable* var)
{
  Token_variable_name* var_name = get_var_name (var);

	// TODO: deal with object indexing
	assert (var->target == NULL);

	if (var_name != NULL)
	{
		read_st (scope, "ref_var", get_var_name (var));
		if (var->array_indices->size() == 1)
		{
			// access var as an array
			if (var->array_indices->front () != NULL)
			{
				code
					<< "// Reference array assignment\n";
				read_simple (scope, "war_index", get_var_name (var->array_indices->front()));

				code
					<< "write_array_reference ("
					<<		get_scope (scope) << ", "
					<<		"ref_var, "
					<<		"war_index, "
					<<		"&" << zvp << ", "
					<<		"&is_" << zvp << "_new TSRMLS_CC);\n"
				;
			}
			else
			{
				code 
					<< "push_var_reference (" 
					<<		get_scope (scope) << ", "
					<<		"ref_var, "
					<<		"&" << zvp << ", &is_" << zvp << "_new TSRMLS_CC);\n";
			}
		}
		else
		{
			assert (var->array_indices->size() == 0);
			code 
				<< "// Normal Reference Assignment\n"
				<< "write_var_reference (" 
				<<		get_scope (scope) << ", "
				<<		"ref_var, "
				<<		"&" << zvp << ", "
				<<		"&is_" << zvp << "_new TSRMLS_CC);\n";
		}
	}
	else
	{
		// Variable variable.
		// After shredder, a variable variable cannot have array indices
		assert (0); // TODO
		assert(var->array_indices->size() == 0);

		code << "assert (0); // write_var_var_reference\n";
//		reference_var_var ();
	}
}

void index_lhs (Scope scope, string zvp, AST_variable* var)
{
  Token_variable_name* var_name = get_var_name (var);

	// TODO: deal with object indexing
	assert (var->target == NULL);
	code
		<< "zval** " << zvp << ";\n";

	if (var_name != NULL)
	{
		read_st (scope, "lhs_var", get_var_name (var));
		if (var->array_indices->size() == 1)
		{
			// access var as an array
			if (var->array_indices->front () != NULL)
			{
				code
					<< "// Array assignment\n";
				read_simple (scope, "lhs_index", get_var_name (var->array_indices->front()));

				code
					<<	zvp << " = get_ht_entry ("
					<<		"lhs_var, "
					<<		"lhs_index "
					<<		" TSRMLS_CC);\n"
				;
			}
			else
			{
				code
					<< "// Array push \n";
				code 
					<< zvp << " = push_and_index_ht (" 
					<<		"lhs_var, "
					<<		" TSRMLS_CC);\n";
			}
		}
		else
		{
			assert (var->array_indices->size() == 0);
			code 
				<< "// Normal Assignment\n"
				<< zvp << " = lhs_var;\n";
		}
	}
	else
	{
		// Variable variable.
		// After shredder, a variable variable cannot have array indices
		assert (0); // TODO
		assert(var->array_indices->size() == 0);

		code << "assert (0); // write_var_var_reference\n";
//		reference_var_var ();
	}
}

/* Generate code to read the variable named in VAR to the zval* ZVP */
void read (Scope scope, string zvp, AST_expr* expr)
{
	AST_variable* var = dynamic_cast<AST_variable*> (expr);
	assert (var);
	assert(var->target == NULL);

	// Variable variable or ordinary variable?
	Token_variable_name* var_name = get_var_name (expr);

	// TODO: deal with object indexing

	if(var_name != NULL)
	{
		if (var->array_indices->size() == 1)
		{
			// access var as an array
			if (var->array_indices->front () != NULL)
			{
				code << "// Read array variable\n";

				read_simple (scope, "r_array", get_var_name (var));
				read_simple (scope, "ra_index", get_var_name (var->array_indices->front ()));

				code
					<< zvp << " = read_array (" 
					<<		get_scope (scope) << ", "
					<<		"r_array, "
					<<		"ra_index, "
					<<		"&is_" << zvp << "_new "
					<<		" TSRMLS_CC);\n"
					;
			}
			else
				assert (0);
		}
		else
		{
			stringstream ss;
			ss << zvp << "var";
			String* name = new String (ss.str ());
			read_simple (scope, *name, get_var_name (var));
			assert (var->array_indices->size() == 0);
			// the same as read_simple, but doesnt declare
			code 
				<< "// Read normal variable\n"
				<< zvp << " = " << *name << ";\n"; 
		}
	}
	else
	{
		// Variable variable.
		// After shredder, a variable variable cannot have array indices
		AST_reflection* refl;
		refl = dynamic_cast<AST_reflection*>(var->variable_name);

		if (var->array_indices->size() == 1)
		{
			// access var as an array
			if (var->array_indices->front () != NULL)
			{
				code << "// Read array variable-variable\n";

				read_simple (scope, "refl", get_var_name (refl));
				read_simple (scope, "refl_index", get_var_name (var->array_indices->front ()));

				code
					<< zvp << " = read_var_array (" 
					<<		get_scope (scope) << ", "
					<<		"refl, "
					<<		"refl_index "
					<<		" TSRMLS_CC);\n";
			}
			else
				assert (0);
		}
		else
		{
			assert (var->array_indices->size() == 0);
			code << "// Read variable variable\n";

			read_simple (scope, "refl", get_var_name (refl));

			code
				<< zvp << " = read_var_var (" 
				<<		get_scope (scope) << ", "
				<<		"refl "
				<<		" TSRMLS_CC);\n"
				;
		}
	}
}

// Implementation of "global" (used in various places)
void global (AST_variable_name* var_name)
{
	AST_variable *var = new AST_variable (NULL,
					var_name,
					new List < AST_expr * >());

	code << "{\n";
	declare ("global_var");
	// TODO this isnt necessary
	read (GLOBAL, "global_var", var);

	// TODO should separate be done lazily? Is this even correct?
	separate (GLOBAL, "global_var", var);
	write_reference (LOCAL, "global_var", var);
	cleanup ("global_var");
	code << "}\n";
}

/*
 * Map of the Zend functions that implement the operators
 *
 * The map also contains entries for ++ and --, which are identical to the
 * entries for + and -, but obviously need to be invoked slightly differently.
 */

static class Op_functions : public map<string,string>
{
public:
	Op_functions() : map<string,string>()
	{
		// Binary functions
		(*this)["+"] = "add_function";	
		(*this)["-"] = "sub_function";	
		(*this)["*"] = "mul_function";	
		(*this)["/"] = "div_function";	
		(*this)["%"] = "mod_function";	
		(*this)["xor"] = "boolean_xor_function";
		(*this)["|"] = "bitwise_or_function";
		(*this)["&"] = "bitwise_and_function";
		(*this)["^"] = "bitwise_xor_function";
		(*this)["<<"] = "shift_left_function";
		(*this)[">>"] = "shift_right_function";
		(*this)["."] = "concat_function";
		(*this)["=="] = "is_equal_function";
		(*this)["==="] = "is_identical_function";
		(*this)["!=="] = "is_not_identical_function";
		(*this)["!="] = "is_not_equal_function";
		(*this)["<>"] = "is_not_equal_function";
		(*this)["<"] = "is_smaller_function";
		(*this)["<="] = "is_smaller_or_equal_function";
		// Unary functions
		(*this)["!"] = "boolean_not_function";
		(*this)["not"] = "boolean_not_function";
		(*this)["~"] = "bitwise_not_function";
		// The operands to the next two functions must be swapped
		(*this)[">="] = "is_smaller_or_equal_function"; 
		(*this)[">"] = "is_smaller_function";
	}
} op_functions;

/*
 * Pattern definitions for statements
 */

class Pattern 
{
public:
	virtual bool match(AST_statement* that) = 0;
	virtual void generate_code(Generate_C* gen) = 0;
	virtual ~Pattern() {}
};


class Method_definition : public Pattern
{
public:
	bool match(AST_statement* that)
	{
		pattern = new Wildcard<AST_method>;
		return that->match(pattern);
	}

	void generate_code(Generate_C* gen)
	{
		this->gen = gen;
		signature = pattern->value->signature;
		gen->methods->push_back(signature);

		method_entry();
		gen->return_by_reference = signature->is_ref;
		gen->visit_statement_list(pattern->value->statements);
		method_exit();
	}

protected:
	Wildcard<AST_method>* pattern;
	AST_signature* signature;
	Generate_C* gen;

protected:
	void debug_argument_stack()
	{
		code <<
		"{\n"
		"void **p;\n"
		"int arg_count;\n"
		"zval *param_ptr;\n"
		"\n"
		"p = EG(argument_stack).top_element-2;\n"
		"arg_count = (ulong) *p;\n"
		"\n"
		"printf(\"\\nARGUMENT STACK\\n\");\n"
		"while (arg_count > 0) {\n"
		"	param_ptr = *(p-arg_count);\n"
		"	printf(\"addr = %08X, refcount = %d, is_ref = %d\\n\", (long)param_ptr, param_ptr->refcount, param_ptr->is_ref);\n"
		"	arg_count--;\n"
		"}\n"
		"printf(\"END ARGUMENT STACK\\n\");\n"
		"}\n"
		;
	}

	class Find_temps : public AST_visitor
	{
		public:

			// Dont find variables within other functions, if those
			// functions/classes are in.
			bool in_class;
			bool in_function;
			set<string> var_names;

			Find_temps () :
				in_class (false),
				in_function (false) 
			{
			}

			void pre_variable_name (Token_variable_name* var_name)
			{
				if (!in_function && !in_class 
					&& var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
				{
					String* name = get_non_st_name (var_name);
					var_names.insert (*name);
				}
			}

			// TODO nesting doesnt work anyway
//			void pre_class_def (AST_class_def*) { in_class = true; }
//			void post_class_def (AST_class_def*) { in_class = false;}
//			void pre_method (AST_method*) { in_function = true; }
//			void post_method (AST_method*) { in_function = false; }
	};

	void generate_non_st_declarations (AST_method* method, AST_signature* sig)
	{
		Find_temps ft;
		// collect all the variables
		method->visit (&ft);
		sig->visit (&ft);
		set<string>::const_iterator i;
		for (i = ft.var_names.begin (); i != ft.var_names.end (); i++)
		{
			code
				<< "zval* " << *i << " = NULL;\n";
		}
	}

	void method_entry()
	{
		code
		// Function header
		<< "PHP_FUNCTION(" << *signature->method_name->value << ")\n"
		<< "{\n"
		;

		// __MAIN__ uses the global symbol table. Dont allocate for
		// functions which dont need a symbol table.
		if (*signature->method_name->value != "__MAIN__" 
			&& not signature->method_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
		{
			code
			<< "// Setup locals array\n"
			<< "HashTable* locals;\n"
			<< "ALLOC_HASHTABLE(locals);\n"
			<< "zend_hash_init(locals, 64, NULL, ZVAL_PTR_DTOR, 0);\n"
			<< "HashTable* old_active_symbol_table = EG(active_symbol_table);\n"
			<< "EG(active_symbol_table) = locals;\n"
			;
		}

		generate_non_st_declarations (pattern->value, signature);


		// debug_argument_stack();

		List<AST_formal_parameter*>* parameters = signature->formal_parameters;
		if(parameters && parameters->size() > 0)
		{
			code 
			<< "// Add all parameters as local variables\n"
			<< "{\n"
			<< "int num_args = ZEND_NUM_ARGS ();\n"
			<< "zval* params[" << parameters->size() << "];\n"
			// First parameter to zend_get_parameters_array does not appear
			// to be used (by looking at the source)
			<< "zend_get_parameters_array(0, num_args, params);\n"
			;

			List<AST_formal_parameter*>::const_iterator i;
			int index;	
			for(i = parameters->begin(), index = 0;
				i != parameters->end();
				i++, index++)
			{
//				code << "printf(\"refcount = %d, is_ref = %d\\n\", params[" << index << "]->refcount, params[" << index << "]->is_ref);\n";
				code << "// param " << index << "\n";

				// if a default value is available, then create code to
				// assign it if an argument is not provided at run time.
				// We model it as an assignment to the named variable,
				// and call on the code generator to generate the
				// default assignment for us.
				if ((*i)->expr)
				{
					code 
						<< "if (num_args <= " << index << ")\n"
						<< "{\n";

					AST_statement* assign_default_values = 
						new AST_eval_expr (
								new AST_assignment (
									new AST_variable (
										NULL,
										(*i)->variable_name->clone (),
										new List<AST_expr*> ()),
									false, (*i)->expr->clone ()));

					gen->children_statement (assign_default_values);
					code << "} else {\n";
				}

				code
					<< "params[" << index << "]->refcount++;\n";

				// TODO this should be abstactable, but it work now, so
				// leave it.
				if ((*i)->variable_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
				{
					string name = *get_non_st_name ((*i)->variable_name);
					code 
						<< name << " = params[" << index << "];\n";
				}
				else
				{
					// TODO i dont believe theres a test for this
					code 
						<< "zend_hash_quick_add(EG(active_symbol_table), "
						<<		"\"" << *(*i)->variable_name->value << "\", " 
						<<		(*i)->variable_name->value->length() + 1 << ", "
						<<		get_hash ((*i)->variable_name) << ", "
						<<		"&params[" << index << "], "
						<<		"sizeof(zval*), NULL);\n"
					  ;
				  }

				if ((*i)->expr)
					code << "}\n";
			}
				
			code << "}\n";

		}
		
		code << "// Function body\n";
	}

	void generate_non_st_cleanup (AST_method* method, AST_signature* sig)
	{
		Find_temps ft;
		// collect all the variables
		method->visit (&ft);
		sig->visit (&ft);
		set<string>::const_iterator i;
		for (i = ft.var_names.begin (); i != ft.var_names.end (); i++)
		{
			code
				<< "if (" << *i << " != NULL)\n"
				<< "{\n"
				<<		"zval_ptr_dtor (&" << *i << ");\n"
				<< "}\n";
	
		}
	}


	void method_exit()
	{
		code
		// Labels are local to a function
		<< "// Method exit\n"
		<< "end_of_function:__attribute__((unused));\n"
		;


		if (*signature->method_name->value != "__MAIN__"
			&& not signature->method_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
		{
			code
			<< "// Destroy locals array\n"
			<< "zend_hash_destroy(locals);\n"
			<< "FREE_HASHTABLE(locals);\n"
			<< "EG(active_symbol_table) = old_active_symbol_table;\n"
			;
		}

		generate_non_st_cleanup (pattern->value, signature);

		code << "}\n";
	}
};

class Label : public Pattern
{
public:
	bool match(AST_statement* that)
	{
		label = new Wildcard<Token_label_name>;
		return that->match(new AST_label(label));
	}

	void generate_code(Generate_C* gen)
	{
		code << *label->value->value << ":;\n";
	}

protected:
	Wildcard<Token_label_name>* label;
};

class Branch : public Pattern
{
public:
	bool match(AST_statement* that)
	{
		cond = new Wildcard<AST_variable>;
		iftrue = new Wildcard<Token_label_name>;
		iffalse = new Wildcard<Token_label_name>;
		return that->match(new AST_branch(
			cond,
			iftrue, 
			iffalse
			));
	}

	void generate_code(Generate_C* gen)
	{
		code
			<< "{\n";
		declare ("cond");
		read (LOCAL, "cond", cond->value);
		code 
			<< "zend_bool bcond = zend_is_true(cond);\n";
		cleanup ("cond");
		code 
			<< "if (bcond)\n"
			<< "	goto " << *iftrue->value->value << ";\n"
			<< "else\n"
			<< "	goto " << *iffalse->value->value << ";\n"
			<< "}\n"
			;
	}

protected:
	Wildcard<AST_variable>* cond;
	Wildcard<Token_label_name>* iftrue;
	Wildcard<Token_label_name>* iffalse;
};

class Goto : public Pattern
{
public:
	bool match(AST_statement* that)
	{
		label = new Wildcard<Token_label_name>;
		return that->match(new AST_goto(label));
	}

	void generate_code(Generate_C* gen)
	{
		code << "goto " << *label->value->value << ";\n";
	}

protected:
	Wildcard<Token_label_name>* label;
};

/*
 * Assignment is a "virtual" pattern. It deals with the LHS of the assignment,
 * but not with the RHS. Various other classes inherit from Assignment, and
 * deal with the different forms the RHS can take.
 */

class Assignment : public Pattern
{
public:
	virtual AST_expr* rhs_pattern() = 0;
	virtual void generate_rhs() = 0;
	virtual ~Assignment() {}

	/* Have we converted to the new way yet? */
	virtual bool fixed ()
	{
		return false;
	}

public:
	bool match(AST_statement* that)
	{
		lhs = new Wildcard<AST_variable>;
		agn = new AST_assignment(lhs, /* ignored */ false, rhs_pattern());
		return that->match(new AST_eval_expr(agn));
	}

	/* MEMORY DISCUSSION
	 *
	 * Variables are created on both sides, many of which have to be cleaned up:
	 *
	 * For lhs variables:
	 *		Indexing the lhs returns a new var or refcount 1, or old var, with an
	 *		incremented refcount. If we update the hash table, the old var gets
	 *		its refcount decremented to account for its removal from the
	 *		hashtable, so we decrement its value to account for our increment. If
	 *		its new, the decrement is also necessary. If we have the same variable
	 *		on both sides, the hash table doesnt touch it, so we remove the extra
	 *		lhs increment and the rhs increment. TODO what about references?
	 *
	 *  - if st is updated, the old contents are auto decremented by the zend_hash_update
	 *  - index_ht increments the refcount of the fetched var.
	 *  - 
	 *  - 
	 */

	void generate_code(Generate_C* gen)
	{
		code << "{\n";

		if (fixed ())
		{
			index_lhs (LOCAL, "p_lhs", lhs->value);

			// Generate code for the RHS
			generate_rhs();
		}
		else
		{
			declare ("rhs");

			// Generate code for the RHS
			generate_rhs();

			// write it back to the lhs
			if(!agn->is_ref)
				write (LOCAL, "rhs", lhs->value);
			else
			{
				// this must be a copy
				Wildcard<AST_variable>* rhs = dynamic_cast<Wildcard<AST_variable>*> (agn->expr);
				if (rhs)
				{
					separate (LOCAL, "rhs", rhs->value);
				}
				else
				{
					// method_invocations separate before they return, so no need.
					assert (dynamic_cast<Wildcard<AST_method_invocation>*> (agn->expr));
				}
				write_reference (LOCAL, "rhs", lhs->value);
			}
			cleanup ("rhs");
		}


		code << "}\n";

		code << "phc_check_invariants (TSRMLS_C);\n";
	}

protected:
	AST_assignment* agn;
	Wildcard<AST_variable>* lhs;
};

/* An optimization for
 *		$str = $str . "string";
 *
 *	We pass the rhs as both arguments, and concat_function calls a
 *	realloc. The old way is to give it new memory, and have it copy
 *	both strings in, then clean up the old one.
 */
class Str_cat : public Pattern
{
	bool match(AST_statement* that)
	{
		left = new Wildcard<AST_variable>;
		Token_op* op = new Token_op (new String ("."));
		right = new Wildcard<AST_variable>;
		lhs = new Wildcard<AST_variable>;
		AST_expr* rhs = new AST_bin_op (left, op, right); 

		agn = new AST_assignment(lhs, /* ignored */ false, rhs);
		bool match = that->match(new AST_eval_expr(agn));
		if (!match)
			return false;

		Token_variable_name* left_var_name = dynamic_cast <Token_variable_name*> (left->value->variable_name);
		Token_variable_name* lhs_var_name = dynamic_cast <Token_variable_name*> (lhs->value->variable_name);
		if (left_var_name == NULL or lhs_var_name == NULL)
			return false;

		return (*left_var_name->value == *lhs_var_name->value);
	}

	void generate_code(Generate_C* gen)
	{
		// Open local scope and create a zval* to hold the RHS result
		code << "{\n";

		string op_fn = op_functions["."]; 

		declare ("left");
		declare ("right");
		read (LOCAL, "left", left->value);
		read (LOCAL, "right", right->value);

		code 
			<< "if (left == EG (uninitialized_zval_ptr))\n"
			<< "{\n";
		separate (LOCAL, "left", left->value);
		code
			<< "}\n";

		code << op_fn << "(left, left, right TSRMLS_CC);\n";

		cleanup ("left");
		cleanup ("right");

		// close local scope
		code << "}\n";

		code << "phc_check_invariants (TSRMLS_C);\n";
	}

protected:
	AST_assignment* agn;
	Wildcard<AST_variable>* lhs;
	Wildcard<AST_variable>* left;
	Wildcard<AST_variable>* right;
};

/*
 * Assign_literal is another virtual class, and corresponds to
 * assigning an int, bool, etc. all of which inherit from
 * Assign_literal.
 */


stringstream initializations;
stringstream finalizations;

template<class T, class K>
class Assign_literal : public Assignment
{
public:
	AST_expr* rhs_pattern()
	{
		rhs = new Wildcard<T>;
		return rhs;
	}

	// record if we've seen this variable before
	void generate_rhs()
	{
		// TODO If this isnt static, there is a new hash each time,
		// because there is a new object each time it is called. Why is
		// there a new object each time?
		static map<K, string> vars;
		if (args_info->optimize_given)
		{
			// The first time we see a constant, we add a declaration,
			// initialization and finalization. After that, we find the
			// first one and refer to it.


			string var;
			if (vars.find (key ()) != vars.end ())
				var = vars [key ()];
			else
			{
				// This is the first time we see the variable. Create the
				// variables and add declarations. 
				stringstream name;
				name << prefix() << vars.size ();
				var = name.str ();
				vars [key ()] = var;

				prologue << "zval* " << var << ";\n";
				finalizations << "zval_ptr_dtor (&" << var << ");\n";
				initialize (initializations, var);
			}

			code << "rhs = " << var << ";\n";
		}
		else
		{
			// initialize at this point in the code
			code << "is_rhs_new = 1;\n";
			initialize (code, "rhs");
		}
	}

	virtual string prefix () = 0;
	virtual K key () = 0;
	virtual void initialize (ostream& os, string var) = 0;

protected:
	Wildcard<T>* rhs;
};


class Assign_bool : public Assign_literal<Token_bool, bool>
{
	string prefix () { return "phc_const_pool_bool_"; }
	bool key () { return rhs->value->value; }

	void initialize (ostream& os, string var)
	{
		os << "MAKE_STD_ZVAL (" << var << ");\n" 
			<< "ZVAL_BOOL (" << var << ", " 
			<<		(rhs->value->value ? 1 : 0) << ");\n";
	}

};

class Assign_int : public Assign_literal<Token_int, long>
{
	string prefix () { return "phc_const_pool_int_"; }
	long key () { return rhs->value->value; }

	void initialize (ostream& os, string var)
	{
		os << "MAKE_STD_ZVAL (" << var << ");\n"
			<< "ZVAL_LONG (" << var << ", " << rhs->value->value << ");\n";
	}
};

class Assign_real : public Assign_literal<Token_real, string>
{
	string prefix () { return "phc_const_pool_real_"; }
	string key () { return *rhs->value->get_source_rep (); }

	void initialize (ostream& os, string var)
	{
		os << "MAKE_STD_ZVAL (" << var << ");\n"
			<< "zend_eval_string(\"" << *rhs->value->get_source_rep () << ";\","
			<<		var << ", "
			<<		"\"literal\" TSRMLS_CC);\n";
	}
};

class Assign_null : public Assign_literal<Token_null, string>
{
	string prefix () { return "phc_const_pool_null_"; }
	string key () { return ""; }

	void initialize (ostream& os, string var)
	{
		os << "MAKE_STD_ZVAL (" << var << ");\n"
			<< "ZVAL_NULL (" << var << ");\n";
	}
};

class Assign_string : public Assign_literal<Token_string, string>
{
	string prefix () { return "phc_const_pool_string_"; }
	string key () { return *rhs->value->get_source_rep (); }

	void initialize (ostream& os, string var)
	{
		os << "MAKE_STD_ZVAL (" << var << ");\n"
			<< "ZVAL_STRINGL(" << var << ", " 
			<<		"\"" << escape(rhs->value->value) << "\", "
			<<		rhs->value->value->length() << ", 1);\n";
	}

	string escape(String* s)
	{
		stringstream ss;

		String::const_iterator i;
		for(i = s->begin(); i != s->end(); i++)
		{
			if(*i == '"' || *i == '\\')
			{
				ss << "\\" << *i;
			}
			else if(*i >= 32 && *i < 127)
			{
				ss << *i;
			}
			else
			{
				ss << "\\" << setw(3) << setfill('0') << oct << uppercase << (unsigned long int)(unsigned char) *i;
				ss << resetiosflags(code.flags());
			}
		}

		return ss.str();
	}
};


class Copy : public Assignment
{
public:
	AST_expr* rhs_pattern()
	{
		rhs = new Wildcard<AST_variable>;
		return rhs;
	}

	void generate_rhs()
	{
		read (LOCAL, "rhs", rhs->value);
	}

protected:
	Wildcard<AST_variable>* rhs;
};

class Cast_array : public Copy
{
public:
	AST_expr* rhs_pattern()
	{
		rhs = new Wildcard<AST_variable>;
		return new AST_cast (new Token_cast (
			new String ("array")),
			rhs);
	}

	virtual void generate_rhs ()
	{
		Copy::generate_rhs ();
		code << "cast_var (&rhs, &is_rhs_new, IS_ARRAY TSRMLS_CC);\n";
	}
};

class Global : public Pattern 
{
public:
	bool match(AST_statement* that)
	{
		rhs = new Wildcard<AST_variable_name>;
		return(that->match(new AST_global(rhs)));
	}

	void generate_code(Generate_C* gen)
	{
		global (rhs->value);
	}

protected:
	Wildcard<AST_variable_name>* rhs;
};

class Assign_constant : public Assignment
{
public:

	AST_expr* rhs_pattern()
	{
		rhs = new Wildcard<AST_constant> ();
		return rhs;
	}

	void generate_rhs ()
	{
		// Check whether its in the form CONST or CLASS::CONST
		String* name = new String ("");
		if (rhs->value->class_name)
		{
			name->append (*rhs->value->class_name->value);
			name->append ("::");
		}

		name->append (*rhs->value->constant_name->value);

		code
			<< "get_constant ( "
			<<			"\"" << *name << "\", "
			<<			name->length() << ", " // exclude NULL-terminator
			<<			"&rhs, "
			<<			"&is_rhs_new TSRMLS_CC);\n"
			;
	}

protected:
	Wildcard<AST_constant>* rhs;
};

class Eval : public Assignment
{
	AST_expr* rhs_pattern()
	{
		eval_arg = new Wildcard<AST_variable>;
		return new AST_method_invocation(
			NULL,	
			new Token_method_name( new String("eval")),
			new List<AST_actual_parameter*>(
				new AST_actual_parameter (false, eval_arg)
				)
			);
	}

	void generate_rhs()	
	{
		code << "{\n";

		read_simple (LOCAL, "eval_arg", get_var_name (eval_arg->value));
		code << "eval (eval_arg, &rhs, &is_rhs_new TSRMLS_CC);\n";

		code << "}\n" ;
	}

protected:
	Wildcard<AST_variable>* eval_arg;
};

class Exit : public Pattern
{
public:
	bool match (AST_statement* that)
	{
		exit_arg = new Wildcard<AST_variable> ();
		Wildcard<Token_method_name>* name = new Wildcard <Token_method_name> ();
		return that->match (
				new AST_eval_expr (
					new AST_assignment (new Wildcard<AST_variable>, false, // ignored
						new AST_method_invocation(
							NULL,	
							name,
							new List<AST_actual_parameter*>(
								new AST_actual_parameter(false, exit_arg)
								)
							))))
			&& (*name->value->value == "exit" || *name->value->value == "die");
	}

	void generate_code (Generate_C* gen)
	{
		code << "{\n";
		declare ("arg");
		read (LOCAL, "arg", exit_arg->value);

		// Fetch the parameter
		code
			<<		"// Exit ()\n"
			<<		"phc_exit (arg TSRMLS_CC);\n";

		code << "}\n";
	}

protected:
	Wildcard<AST_variable>* exit_arg;
};

class Method_invocation : public Assignment
{
public:
	AST_expr* rhs_pattern()
	{
		rhs = new Wildcard<AST_method_invocation>;
		return rhs;
	}

	void generate_rhs()
	{
		List<AST_actual_parameter*>::const_iterator i;
		unsigned index;
		
		// code << "debug_hash(EG(active_symbol_table));\n";

		// Variable function or ordinary function?
		Token_method_name* name;
		name = dynamic_cast<Token_method_name*>(rhs->value->method_name);

		if(name != NULL)
		{
			code
			<< "// Create zval to hold function name\n"
			<< "zval function_name;\n"
			<< "INIT_PZVAL(&function_name);\n"
			<< "ZVAL_STRING(&function_name, "
			<<		"\"" << *name->value << "\", "
			<<		"0);\n"
			<< "zval* function_name_ptr;\n"
			<< "function_name_ptr = &function_name;\n"
			;
		}
		else
		{
			assert(0);
		}
	
		int num_args = rhs->value->actual_parameters->size();

		// Figure out which parameters need to be passed by reference
		code
		<< "zend_function* signature;\n"
		<< "zend_is_callable_ex(function_name_ptr, 0, NULL, NULL, NULL, &signature, NULL TSRMLS_CC);\n"

		// check for non-existant functions
		<< "if (signature == NULL) {\n"
		<< "	phc_setup_error (1, " << rhs->get_filename () << ", " << rhs->get_line_number () << ", NULL TSRMLS_CC);\n"
		<< "	php_error_docref (NULL TSRMLS_CC, E_ERROR, \"Call to undefined function %s()\", \"" << *name->value << "\");\n"
		<< "	phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);\n"
		<<	"}\n";


		if (num_args)
		{
			code
				<< "zend_arg_info* arg_info = signature->common.arg_info;\n"
				<< "int by_ref[" << num_args << "];\n"
				;
		}

		// TODO: Not 100% this is fully correct; in particular, 
		// pass_rest_by_reference does not seem to work.
		// code << "printf(\"\\ncalling %s\\n\", signature->common.function_name);\n";
		for(
			i = rhs->value->actual_parameters->begin(), index = 0; 
			i != rhs->value->actual_parameters->end(); 
			i++, index++)
		{
			// code << "printf(\"argument '%s' \", arg_info ? arg_info->name : \"(unknown)\");\n";
			
			code
			<< "if(arg_info)\n"
			<< "{\n"
			<< "	by_ref[" << index << "] = arg_info->pass_by_reference;\n"
			<< "	arg_info++;\n"
			<< "}\n"
			<< "else\n"
			<< "{\n"
			<< "	by_ref[" << index << "] = signature->common.pass_rest_by_reference;\n"
			<< "}\n"
			;
			
			if((*i)->is_ref) code << "by_ref[" << index << "] = 1;\n";
			
			// code << "printf(\"by reference: %d\\n\", by_ref[" << index << "]);\n";
		}

		if (num_args)
		{
			code 
				<< "// Setup array of arguments\n"
				<< "int destruct[" << num_args << "]; // set to 1 if the arg is new\n"
				<< "zval* args[" << num_args  << "];\n"
				;
		}
		code 
			<< "zval** args_ind[" << num_args  << "];\n";

		for(
			i = rhs->value->actual_parameters->begin(), index = 0; 
			i != rhs->value->actual_parameters->end(); 
			i++, index++)
		{
			// use this is a check, but actually use the index_st_rhs to generate this
			AST_variable* var = dynamic_cast<AST_variable*> ((*i)->expr);
			Token_variable_name* var_name = get_var_name ((*i)->expr);

			code << "destruct[" << index << "] = 0;\n";
			/* If we need a point that goes straight into the
			 * hashtable, which we do for pass-by-ref, then we return a
			 * zval**, straight into args_ind. Otherwise we return a
			 * zval*, put it in args, and fetch it into args_ind after.
			 * (It is difficult to return a zval** which doesnt point
			 * into its containing hashtable, otherwise. */
			if (var->array_indices->size ())
			{
				// TODO: variables are allowed have more than 1 index (so long as
				// the indexes are all temporaries). We do not know whether to
				// shred the variables using references or not, since we do not
				// know until run-time whether the function is call-by-reference or
				// not.
				assert (var->array_indices->size () == 1);
				Token_variable_name* ind = 
					get_var_name (var->array_indices->front ());

				code
					<< "if (by_ref [" << index << "])\n"
					<< "{\n";

				read_st (LOCAL, "arg", var_name);
				read_simple (LOCAL, "ind", ind);

				code
					<< "	args_ind[" << index << "] = fetch_array_arg_by_ref ("
					<<				get_scope (LOCAL) << ", "
					<<				"arg, "
					<<				"ind, "
					<<				"&destruct[" << index << "] TSRMLS_CC);\n"
					<<	"  args[" << index << "] = *args_ind[" << index << "];\n"
					<< "}\n"
					<< "else\n"
					<< "{\n";

				read_simple (LOCAL, "arg", var_name);
				read_simple (LOCAL, "ind", ind);

				code
					<< "  args[" << index << "] = fetch_array_arg ("
					<<				get_scope (LOCAL) << ", "
					<<				"arg, "
					<<				"ind, "
					<<				"&destruct[" << index << "] TSRMLS_CC);\n"
					<< " args_ind[" << index << "] = &args[" << index << "];\n"
					<< "}\n"
					;
			}
			else
			{
				// TODO: Its correct to handle variable variables here, since we
				// dont know if they are to be passed by reference or not, so they
				// cannot be shredder earlier.
				assert (var_name);
				code 
					<< "if (by_ref [" << index << "])\n"
					<< "{\n";

				read_st (LOCAL, "p_arg", var_name);
				code
					<< "	args_ind[" << index << "] = fetch_var_arg_by_ref ("
					<<				get_scope (LOCAL) << ", "
					<<				"p_arg TSRMLS_CC);\n"
					<<	"  args[" << index << "] = *args_ind[" << index << "];\n"
					<< "}\n"
					<< "else\n"
					<< "{\n";

				read_simple (LOCAL, "arg", var_name);

				code
					<< "  args[" << index << "] = fetch_var_arg ("
					<<				get_scope (LOCAL) << ", "
					<<				"arg, "
					<<				"&destruct[" << index << "] TSRMLS_CC);\n"
					<< " args_ind[" << index << "] = &args[" << index << "];\n"
					<< "}\n"
					;

			}
		}

		code
			<< "phc_setup_error (1, " 
			<<				rhs->get_filename () << ", " 
			<<				rhs->get_line_number () << ", "
			<< "			NULL TSRMLS_CC);\n"
			<< "// Call the function\n"
			<< "int success;\n"	
			<< "success = call_user_function_ex(EG(function_table), " 
			<< "					NULL, function_name_ptr, &rhs, " 
			<<						num_args << ", args_ind, "
			<<						"0, NULL TSRMLS_CC);\n"
			<< "assert(success == SUCCESS);\n"
			<< "phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);\n"
			;

		// Workaround a bug (feature?) of the Zend API that I don't know how to
		// solve otherwise. It seems that Zend resets the refcount and is_ref
		// fields of the return value after the function returns. That is okay
		// if the function does not return a reference (because it will have
		// created a fresh zval to hold the result), but obviously garbage
		// collector problems when the function returned a reference to an
		// existing zval. Hence, we increment the refcount here, and set is_ref
		// to true if the function signature declares the function to return a
		// reference. This causes memory leaks, so we make a note to clean up the
		// memory. It only occurs when calling eval'd functions, because they do
		// in fact return the correct refcount.
		code 
		<< "if(signature->common.return_reference)\n"
		<< "{\n"
		<< "	assert (rhs != EG(uninitialized_zval_ptr));\n"
		<< "	rhs->is_ref = 1;\n"
		// TODO what happens if there's supposed to be 8 or 10
		// references to it.
		<< "  if (signature->type == ZEND_USER_FUNCTION)\n"
		<< "		is_rhs_new = 1;\n"
		<< "}\n"
		<< "else\n"
		<< "{\n"
		<< "	is_rhs_new = 1;\n"
		<< "}\n"
		;

		if (agn->is_ref)
		{
			// TODO separate here?
			code 
				<< "if (rhs->refcount > 1 && !rhs->is_ref)\n"
				<< "  zvp_clone (&rhs, &is_rhs_new);\n";
		}

		for(
			i = rhs->value->actual_parameters->begin(), index = 0; 
			i != rhs->value->actual_parameters->end(); 
			i++, index++)
		{
			// TODO put the for loop into generated code
			code 
				<< "if (destruct[" << index << "])\n"
				<< "{\n"
				<< "	assert (destruct[" << index << "] == 1);\n"
				<< "	zval_ptr_dtor (args_ind[" << index << "]);\n"
				<< "}\n";
		}
		
		// code << "debug_hash(EG(active_symbol_table));\n";
	}

protected:
	Wildcard<AST_method_invocation>* rhs;
};

class Bin_op : public Assignment
{
public:
	AST_expr* rhs_pattern()
	{
		left = new Wildcard<AST_variable>;
		op = new Wildcard<Token_op>;
		right = new Wildcard<AST_variable>;

		return new AST_bin_op (left, op, right); 
	}
	bool fixed ()
	{
		return true;
	}

	void generate_rhs()
	{
		assert(
			op_functions.find(*op->value->value) != 
			op_functions.end());
		string op_fn = op_functions[*op->value->value]; 

		read_simple (LOCAL, "left", get_var_name (left->value));
		read_simple (LOCAL, "right", get_var_name (right->value));

		code
			<< "if (in_copy_on_write (*p_lhs))\n"
			<< "{\n"
			<< "	zval_ptr_dtor (p_lhs);\n"
			<< "	ALLOC_INIT_ZVAL (*p_lhs);\n"
			<< "}\n"
			<< "zval old = **p_lhs;\n"
			<< "int result_is_operand = (*p_lhs == left || *p_lhs == right)\n;";

		// some operators need the operands to be reversed (since we
		// call the opposite function). This is accounted for in the
		// binops table.
		if(*op->value->value == ">" || *op->value->value == ">=")
			code << op_fn << "(*p_lhs, right, left TSRMLS_CC);\n";
		else
			code << op_fn << "(*p_lhs, left, right TSRMLS_CC);\n";

		// If the result is one of the operand, the operator function
		// will already have cleaned up the result
		code
			<< "if (!result_is_operand)\n"
			<<		"zval_dtor (&old);\n";

	}

protected:
	Wildcard<AST_variable>* left;
	Wildcard<Token_op>* op;
	Wildcard<AST_variable>* right;
};

class Unary_op : public Assignment
{
public:
	AST_expr* rhs_pattern()
	{
		op = new Wildcard<Token_op>;
		expr = new Wildcard<AST_variable>;

		return new AST_unary_op(op, expr);
	}

	virtual bool fixed ()
	{
		return true;
	}

	void generate_rhs()
	{
		assert(
			op_functions.find(*op->value->value) != 
			op_functions.end());
		string op_fn = op_functions[*op->value->value]; 

		read_simple (LOCAL, "expr", get_var_name (expr->value));

		code
			<< "if (in_copy_on_write (*p_lhs))\n"
			<< "{\n"
			<< "	zval_ptr_dtor (p_lhs);\n"
			<< "	ALLOC_INIT_ZVAL (*p_lhs);\n"
			<< "}\n"
			<< "zval old = **p_lhs;\n"
			<< "int result_is_operand = (*p_lhs == expr)\n;";

		code 
			<< op_fn << "(*p_lhs, expr TSRMLS_CC);\n" ;

		code
			<< "if (!result_is_operand)\n"
			<<		"zval_dtor (&old);\n";

	}

protected:
	Wildcard<Token_op>* op;
	Wildcard<AST_variable>* expr;
};

class Return : public Pattern
{
	bool match(AST_statement* that)
	{
		expr = new Wildcard<AST_expr>;
		return(that->match(new AST_return(expr)));
	}

	void generate_code(Generate_C* gen)
	{
		code << "{\n";
		declare ("rhs");
		read (LOCAL, "rhs", expr->value);

		if(!gen->return_by_reference)
		{
			// Run-time return by reference had slightly different
			// semantics to compile-time. There is no way within a
			// function to tell if the run-time return by reference is
			// set, but its unnecessary anyway.
			code 
				<< "return_value->value = rhs->value;\n"
				<< "return_value->type = rhs->type;\n"
				<< "zval_copy_ctor(return_value);\n"
				;
		}
		else
		{
			separate (LOCAL, "rhs", expr->value);

			code
				<< "zval_ptr_dtor(return_value_ptr);\n"
				<< "rhs->is_ref = 1;\n"
				<< "rhs->refcount++;\n"
				<< "*return_value_ptr = rhs;\n";
			;
//		code << "printf(\"<<< rhs (%08X) %08X %d %d >>>\\n\", return_value_ptr, rhs, rhs->refcount, rhs->is_ref);\n";

		}
		cleanup ("rhs");

		code 
		<< "goto end_of_function;\n"
		<< "}\n"
		;
	}

protected:
	Wildcard<AST_expr>* expr;
};

class Unset : public Pattern
{
	bool match(AST_statement* that)
	{
		var = new Wildcard<AST_variable>;
		return(that->match(new AST_unset(var)));
	}

	void generate_code(Generate_C* gen)
	{
		code << "{\n";

		// TODO: deal with object indexing
		assert(var->value->target == NULL);

		Token_variable_name* var_name = get_var_name (var->value);

		if (var_name != NULL)
		{
			if (var->value->array_indices->size() == 0)
			{
				if (var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
				{
					String* name = get_non_st_name (var_name);
					code
						<< "if (" << *name << " != NULL)\n"
						<< "{\n"
						<<		"zval_ptr_dtor (&" << *name << ");\n"
						<<		*name << " = NULL;\n"
						<< "}\n";
				}
				else
				{
					String* name = var_name->value;
					code
						<< "unset_var ("
						<<		get_scope (LOCAL) << ", "
						<<		"\"" << *name << "\", "
						<<		name->length() + 1
						// no get_hash version
						<<		" TSRMLS_CC);\n";
				}
			}
			else 
			{
				assert(var->value->array_indices->size() == 1);
				Token_variable_name* index = get_var_name (var->value->array_indices->front());
				read_st (LOCAL, "u_array", var_name);
				read_simple (LOCAL, "u_index", index);

				code
					<< "unset_array ("
					<<		get_scope (LOCAL) << ", "
					<<    "u_array, "
					<<    "u_index "
					<<		" TSRMLS_CC);\n";
			}
		}
		else
		{
			// Variable variable
			// TODO
			assert(0);
		}
		code << "}\n";
	}

protected:
	Wildcard<AST_variable>* var;
};

/*
 * Visitor methods to generate C code
 * Visitor for statements uses the patterns defined above.
 */

void Generate_C::children_statement(AST_statement* in)
{
	// Make reading the generated code easier. If we use a /* comment,
	// then we may get nested /* */ comments, which arent allowed and
	// result in syntax errors in C. Use // instead.
	stringstream ss;
	in->visit (new PHP_unparser (ss));

	while (not ss.eof ())
	{
		string str;
		getline (ss, str);
		code << "// " << str << endl;
	}

	Pattern* patterns[] = 
	{
		new Method_definition()
	,	new Assign_string ()
	,	new Assign_int ()
	,	new Assign_bool ()
	,	new Assign_real ()
	,	new Assign_null ()
	,	new Assign_constant ()
	,	new Copy()
	,	new Global()
	,	new Eval()
	,	new Exit()
	,	new Method_invocation()
//	,	new Str_cat()
	,	new Bin_op()
	,	new Unary_op()
	,	new Label()
	,	new Branch()
	,	new Goto()
	,	new Return()
	,	new Unset()
	,	new Cast_array ()
	};

	bool matched = false;
	for(unsigned i = 0; i < sizeof(patterns) / sizeof(Pattern*); i++)
	{
		if(patterns[i]->match(in))
		{
			patterns[i]->generate_code(this);
			matched = true;
			break;
		}
	}

	if(not matched)
	{
		PHP_unparser pup(cerr);
		cerr << "could not generate code for ";
		in->visit(&pup);
		abort();
	}
}

void Generate_C::pre_php_script(AST_php_script* in)
{
	// For now, we simply include this.
	ifstream file ("libphc.cpp");
	assert (file.is_open ());

	while (not file.eof ())
	{
		string str;
		getline (file, str);
		prologue << str << endl;
	}

	file.close ();
	assert (file.is_open () == false);
}

void Generate_C::post_php_script(AST_php_script* in)
{
	List<AST_signature*>::const_iterator i;

	code << "// ArgInfo structures (necessary to support compile time pass-by-reference)\n";
	for(i = methods->begin(); i != methods->end(); i++)
	{
		String* name = (*i)->method_name->value;

		// TODO: pass by reference only works for PHP>5.1.0. Do we care?
		code 
		<< "ZEND_BEGIN_ARG_INFO_EX(" << *name << "_arg_info, 0, "
		<< ((*i)->is_ref ? "1" : "0")
		<< ", 0)\n"
		;

		// TODO: deal with type hinting

		List<AST_formal_parameter*>::const_iterator j;
		for(
			j = (*i)->formal_parameters->begin();
			j != (*i)->formal_parameters->end();
			j++)
		{
			code 
			<< "ZEND_ARG_INFO("
			<< ((*j)->is_ref ? "1" : "0")
			<< ", \"" << *(*j)->variable_name->value << "\")\n"; 
		}

		code << "ZEND_END_ARG_INFO()\n";
	}

	code 
		<< "// Register all functions with PHP\n"
		<< "static function_entry " << *extension_name << "_functions[] = {\n"
		;
	for(i = methods->begin(); i != methods->end(); i++)
	{
		String* name = (*i)->method_name->value;
		code << "PHP_FE(" << *name << ", " << *name << "_arg_info)\n";
	}

	code << "{ NULL, NULL, NULL }\n";
	code << "};\n";

	code
		<< "// Register the module itself with PHP\n"
		<< "zend_module_entry " << *extension_name << "_module_entry = {\n"
		<< "STANDARD_MODULE_HEADER, \n"
		<< "\"" << *extension_name << "\",\n"
		<< *extension_name << "_functions,\n"
		<< "NULL, /* MINIT */\n"
		<< "NULL, /* MSHUTDOWN */\n"
		<< "NULL, /* RINIT */\n"
		<< "NULL, /* RSHUTDOWN */\n"
		<< "NULL, /* MINFO */\n"
		<< "\"1.0\",\n"
		<< "STANDARD_MODULE_PROPERTIES\n"
		<< "};\n"
		;

	if(is_extension)
	{
		code << "ZEND_GET_MODULE(" << *extension_name << ")\n";
	}
	else
	{
		code << "#include <sapi/embed/php_embed.h>\n";
		code << "#include <signal.h>\n\n";
	
		code <<
		"void sighandler(int signum)\n"
		"{\n"
		"	switch(signum)\n"
		"	{\n"
		"		case SIGABRT:\n"
		"			printf(\"SIGABRT received!\\n\");\n"
		"			break;\n"
		"		case SIGSEGV:\n"
		"			printf(\"SIGSEGV received!\\n\");\n"
		"			break;\n"
		"		default:\n"
		"			printf(\"Unknown signal received!\\n\");\n"
		"			break;\n"
		"	}\n"
		"\n"
		"	printf(\"This could be a bug in phc. If you suspect it is, please email\\n\");\n"
		"	printf(\"a bug report to phc-general@phpcompiler.org.\\n\");\n"
		"	exit(-1);\n"
		"}\n";
	
		code << 
		"\n"
		"int\n"
		"main (int argc, char* argv[])\n"
		"{\n"
		"   int phc_exit_status;\n"
		"   signal(SIGABRT, sighandler);\n"
		"   signal(SIGSEGV, sighandler);\n"
		"\n"
		"   TSRMLS_D;\n"
		"   php_embed_init (argc, argv PTSRMLS_CC);\n"
		"   zend_first_try\n"
		"   {\n"
		"      // initialize all the constants\n"
		<< initializations.str () << 
		"\n"
		"      // load the compiled extension\n"
		"      zend_startup_module (&" << *extension_name << "_module_entry);\n"
		"\n"
		"      zval main_name;\n"
		"      ZVAL_STRING (&main_name, \"__MAIN__\", NULL);\n"
		"\n"
		"      zval retval;\n"
		"\n"
		"      // Use standard errors, on stdout\n"
		"      zend_alter_ini_entry (\"report_zend_debug\", sizeof(\"report_zend_debug\"), \"0\", sizeof(\"0\") - 1, PHP_INI_ALL, PHP_INI_STAGE_RUNTIME);\n"
		"      zend_alter_ini_entry (\"display_startup_errors\", sizeof(\"display_startup_errors\"), \"1\", sizeof(\"1\") - 1, PHP_INI_ALL, PHP_INI_STAGE_RUNTIME);\n"
		"\n"
		"      // call __MAIN__\n"
		"      int success = call_user_function( \n"
		"                   EG (function_table),\n"
		"                   NULL,\n"
		"                   &main_name,\n"
		"                   &retval,\n"
		"                   0,\n"
		"                   NULL\n"
		"                   TSRMLS_CC);\n"
		"\n"
		"      assert (success == SUCCESS);\n"
		"\n"
		"\n"
		"   }\n"
		"   zend_catch\n"
		"   {\n"
		"   }\n"
		"   zend_end_try ();\n"
		<< finalizations.str () << 
		"   phc_exit_status = EG(exit_status);\n"
		"   php_embed_shutdown (TSRMLS_C);\n"
		"\n"
		"  return phc_exit_status;\n"
		"}\n" ;
	}
}

/*
 * Bookkeeping 
 */

Generate_C::Generate_C(ostream& os) : os (os)
{
	methods = new List<AST_signature*>;
	name = new String ("generate-c");
}
