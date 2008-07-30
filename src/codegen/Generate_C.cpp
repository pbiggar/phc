/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate C code
 *
 * Currently, the C code is generated from MIR; once we have an LIR,
 * the C code will be generated from the LIR instead.
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

#include "process_mir/MIR_unparser.h"
#include "process_ir/General.h"
#include "process_ir/XML_unparser.h"
#include <fstream>
#include "Generate_C.h"
#include "embed/embed.h"
#include "lib/List.h"
#include "lib/demangle.h"
#include <set>

using namespace MIR;

// Label supported features
void phc_unsupported (Node* node)
{
	cerr << "This context does not yet support this feature:" << endl;
	node->visit (new MIR_unparser (cerr, true));
	node->visit (new MIR_XML_unparser (cerr));
	abort ();
}

// A single pass isnt really sufficient, but we can hack around it
// with a prologue and an epilogue.
static ostringstream prologue;
static ostringstream code;
static ostringstream epilogue;

// TODO this is here for constant pooling. This should not be global.
static gengetopt_args_info* args_info;

bool Generate_C::pass_is_enabled (Pass_manager* pm)
{
	return pm->args_info->generate_c_flag or pm->args_info->compile_flag;
}

void Generate_C::run (IR::PHP_script* in, Pass_manager* pm)
{
	args_info = pm->args_info;
	if (not PHP::is_available ())
	{
		// TODO would be better if we checked for these at run-time if they
		// werent available at compile time.
		phc_error (	"phc requires PHP to be avaiable for compilation. " 
						"Please install the PHP embed SAPI, "
						"and run 'configure' on phc again");

		// TODO more information perhaps? Or integrate with configure warning?
	}

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

	in->visit(this);

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
 * variable; that is, a variable with a VARIABLE_NAME as name, no target,
 * and no array indices. Wherever we assume this, we use this function
 * "operand" to extract the variable name. That factors out a bit of recurring
 * code, and also flags where we make this assumption.
 */


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

string get_hash (VARIABLE_NAME* name)
{
	return get_hash (name->value);
}

void declare (string var)
{
	code 
		<< "zval** " << var << ";\n"
		<< "int is_" << var << "_new = 0;\n";
}

void cleanup (string target)
{
	code
		<< "if (is_" << target << "_new)\n"
		<< "  zval_ptr_dtor (" << target << ");\n";
}

String* get_non_st_name (VARIABLE_NAME* var_name)
{
	assert (var_name->attrs->is_true ("phc.codegen.st_entry_not_required"));

	stringstream ss;
	ss << "local_" << *var_name->value;
	return new String (ss.str ());
}



// Generate calls to read_var, for array and array index lookups, and the like.
void read_rvalue (Scope scope, string zvp, Rvalue* rvalue)
{
	VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (rvalue);
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

void read_st (Scope scope, string zvp, VARIABLE_NAME* var_name)
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

void index_assign_array (Scope scope, string zvp, VARIABLE_NAME* lhs, VARIABLE_NAME* index)
{
	code
		<< "zval** " << zvp << ";\n";

	// lhs_var can exist more than once; rename
	stringstream ss1;
	ss1 << zvp << "_lhs";
	string zvp_name = ss1.str ();

	read_st (scope, zvp_name, lhs);

	stringstream ss2;
	ss2 << zvp << "_index";
	string zvp_index = ss2.str ();

	code
		<< "// Array assignment\n";
	read_rvalue (scope, zvp_index, index);

	code
		<<	zvp << " = get_ht_entry ("
		<<		zvp_name << ", "
		<<		zvp_index
		<<		" TSRMLS_CC);\n"
		;
}

void index_array_index (Scope scope, string zvp, Index_array* ia)
{
	VARIABLE_NAME* var_name = ia->variable_name;

	code
		<< "zval** " << zvp << ";\n";

	// lhs_var can exist more than once; rename
	stringstream ss_var;
	ss_var << zvp << "_var";
	string zvp_name = ss_var.str ();

	read_st (scope, zvp_name, var_name);
	stringstream ss_index;
	ss_index << zvp << "_index";
	string zvp_index = ss_index.str ();

	code
		<< "// Array assignment\n";
	read_rvalue (scope, zvp_index, ia->index);

	code
		<<	zvp << " = get_ht_entry ("
		<<		zvp_name << ", "
		<<		zvp_index
		<<		" TSRMLS_CC);\n"
		;
}

void index_lhs (Scope scope, string zvp, Expr* expr)
{
	if (isa<Index_array> (expr))
	{
		index_array_index (LOCAL, "p_rhs", dyc<Index_array> (expr));
		return;
	}

	VARIABLE_NAME* var_name = dynamic_cast<VARIABLE_NAME*> (expr);

	code
		<< "zval** " << zvp << ";\n";

	if (var_name != NULL)
	{
		// lhs_var can exist more than once; rename
		stringstream ss;
		ss << zvp << "_var";
		string zvp_name = ss.str ();

		read_st (scope, zvp_name, var_name);
		code 
			<< "// Normal Assignment\n"
			<< zvp << " = " << zvp_name << ";\n";
	}
	else
	{
		// Variable variable.
		// After shredder, a variable variable cannot have array indices
		phc_unsupported (expr);

//		reference_var_var ();
	}
}


/* Generate code to read the variable named in VAR to the zval* ZVP */
void read (Scope scope, string zvp, Variable_name* var_name)
{
	if(isa<VARIABLE_NAME> (var_name))
	{
		stringstream ss;
		ss << zvp << "var";
		string name = ss.str ();
		read_rvalue (scope, name, dyc<VARIABLE_NAME> (var_name));
		// the same as read_rvalue, but doesnt declare
		code 
			<< "// Read normal variable\n"
			<< zvp << " = &" << name << ";\n"; 
	}
	else
	{
		// Variable variable.
		Variable_variable* var_var = dyc<Variable_variable>(var_name);

		code << "// Read variable variable\n";

		read_rvalue (scope, "var_var", var_var->variable_name);

		code
			<< zvp << " = read_var_var (" 
			<<		get_scope (scope) << ", "
			<<		"var_var "
			<<		" TSRMLS_CC);\n"
			;
	}
}

void read_array_index (Scope scope, string zvp, Index_array* ia)
{
	VARIABLE_NAME* var_name  = ia->variable_name;
	// access var as an array
	code << "// Read array variable\n";

	read_rvalue (scope, "r_array", var_name);
	read_rvalue (scope, "ra_index", ia->index);

	code
		<< "read_array ("
		<<		zvp << ", "
		<<		"r_array, "
		<<		"ra_index, "
		<<		"&is_" << zvp << "_new "
		<<		" TSRMLS_CC);\n"
		;
}

// Implementation of "global" (used in various places)
void global (Variable_name* var_name)
{
	code << "{\n";
	index_lhs (LOCAL, "p_local_global_var", var_name); // lhs
	index_lhs (GLOBAL, "p_global_var", var_name); // rhs

	// Note that p_global_var can be in the copy-on-write set.
	code 
		<< "sep_copy_on_write_ex (p_global_var);\n"
		<< "(*p_global_var)->is_ref = 1;\n"
		<< "(*p_global_var)->refcount++;\n"
		<< "zval_ptr_dtor (p_local_global_var);\n"
		<< "*p_local_global_var = *p_global_var;\n";
	

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
		// Post- functions
		(*this)["++"] = "increment_function";
		(*this)["--"] = "decrement_function";
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
	virtual bool match(Statement* that) = 0;
	virtual void generate_code(Generate_C* gen) = 0;
	virtual ~Pattern() {}
};


class Pattern_method_definition : public Pattern
{
public:
	bool match(Statement* that)
	{
		pattern = new Wildcard<Method>;
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
	Wildcard<Method>* pattern;
	Signature* signature;
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

	class Find_temps : public Visitor
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

			void pre_variable_name (VARIABLE_NAME* var_name)
			{
				if (!in_function && !in_class 
					&& var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
				{
					String* name = get_non_st_name (var_name);
					var_names.insert (*name);
				}
			}

			// TODO nesting doesnt work anyway
//			void pre_class_def (Class_def*) { in_class = true; }
//			void post_class_def (Class_def*) { in_class = false;}
//			void pre_method (Method*) { in_function = true; }
//			void post_method (Method*) { in_function = false; }
	};

	void generate_non_st_declarations (Method* method, Signature* sig)
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

		List<Formal_parameter*>* parameters = signature->formal_parameters;
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

			List<Formal_parameter*>::const_iterator i;
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
				if ((*i)->var->default_value)
				{
					code 
						<< "if (num_args <= " << index << ")\n"
						<< "{\n";

					// An assignment to default values doesnt fit in the IR. They
					// would need to be lowered first. The simplest option is to
					// convert them to AST, run them through the passes, and
					// generate code for that */
					phc_unsupported ((*i)->var->default_value);

/*					Statement* assign_default_values = 
						new Assign_var(
							(*i)->var->variable_name->clone (),
							false, 
							(*i)->var->default_value->clone ());

					gen->children_statement (assign_default_values);
*/					code << "} else {\n";
				}

				code
					<< "params[" << index << "]->refcount++;\n";

				// TODO this should be abstactable, but it work now, so
				// leave it.
				if ((*i)->var->variable_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
				{
					string name = *get_non_st_name ((*i)->var->variable_name);
					code 
						<< name << " = params[" << index << "];\n";
				}
				else
				{
					// TODO i dont believe theres a test for this
					code 
						<< "zend_hash_quick_add(EG(active_symbol_table), "
						<<		"\"" << *(*i)->var->variable_name->value << "\", " 
						<<		(*i)->var->variable_name->value->length() + 1 << ", "
						<<		get_hash ((*i)->var->variable_name) << ", "
						<<		"&params[" << index << "], "
						<<		"sizeof(zval*), NULL);\n"
					  ;
				  }

				if ((*i)->var->default_value)
					code << "}\n";
			}
				
			code << "}\n";

		}
		
		code << "// Function body\n";
	}

	void generate_non_st_cleanup (Method* method, Signature* sig)
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

class Pattern_label : public Pattern
{
public:
	bool match(Statement* that)
	{
		label = new Wildcard<LABEL_NAME>;
		return that->match(new Label(label));
	}

	void generate_code(Generate_C* gen)
	{
		code << *label->value->value << ":;\n";
	}

protected:
	Wildcard<LABEL_NAME>* label;
};

class Pattern_branch : public Pattern
{
public:
	bool match(Statement* that)
	{
		cond = new Wildcard<VARIABLE_NAME>;
		iftrue = new Wildcard<LABEL_NAME>;
		iffalse = new Wildcard<LABEL_NAME>;
		return that->match(new Branch(
			cond,
			iftrue, 
			iffalse
			));
	}

	void generate_code(Generate_C* gen)
	{
		code
			<< "{\n";
		read_rvalue (LOCAL, "p_cond", cond->value);
		code 
			<< "zend_bool bcond = zend_is_true (p_cond);\n";
		code 
			<< "if (bcond)\n"
			<< "	goto " << *iftrue->value->value << ";\n"
			<< "else\n"
			<< "	goto " << *iffalse->value->value << ";\n"
			<< "}\n"
			;
	}

protected:
	Wildcard<VARIABLE_NAME>* cond;
	Wildcard<LABEL_NAME>* iftrue;
	Wildcard<LABEL_NAME>* iffalse;
};

class Pattern_goto : public Pattern
{
public:
	bool match(Statement* that)
	{
		label = new Wildcard<LABEL_NAME>;
		return that->match(new Goto(label));
	}

	void generate_code(Generate_C* gen)
	{
		code << "goto " << *label->value->value << ";\n";
	}

protected:
	Wildcard<LABEL_NAME>* label;
};

/*
 * Assignment is a "virtual" pattern. It deals with the LHS of the assignment,
 * but not with the RHS. Various other classes inherit from Assignment, and
 * deal with the different forms the RHS can take.
 */

void index_assign_var (Scope scope, string zvp, VARIABLE_NAME* var_name)
{
	code
		<< "zval** " << zvp << ";\n";

	// lhs_var can exist more than once; rename
	stringstream ss;
	ss << zvp << "_var";
	string zvp_name = ss.str ();

	read_st (scope, zvp_name, var_name);
	code 
		<< "// Normal Assignment\n"
		<< zvp << " = " << zvp_name << ";\n";
}

class Pattern_assign_var : public Pattern
{
public:
	virtual Expr* rhs_pattern() = 0;
	virtual void generate_rhs () = 0;
	virtual ~Pattern_assign_var() {}

public:
	bool match(Statement* that)
	{
		lhs = new Wildcard<VARIABLE_NAME>;
		agn = new Assign_var (lhs, /* ignored */ false, rhs_pattern());
		return (that->match(agn));
	}

	void generate_code(Generate_C* gen)
	{
		code 
			<< "{\n";

		index_assign_var (LOCAL, "p_lhs", lhs->value);

		code 
			<<		"if (p_lhs != NULL)\n"
			<<		"{\n";

		// Generate code for the RHS
		generate_rhs ();

		code 
			<<		"}\n";
		
		code 
			<< "}\n";
		code << "phc_check_invariants (TSRMLS_C);\n";
	}

protected:
	Assign_var* agn;
	Wildcard<Target>* target;
	Wildcard<VARIABLE_NAME>* lhs;
};

void assign_rhs (bool is_ref, VARIABLE_NAME* rhs)
{
	if (not is_ref)
	{
		declare ("p_rhs");
		code 
			<< "zval* temp = NULL;\n"
			<< "p_rhs = &temp;\n";

		// copied from read ()
		read_rvalue (LOCAL, "p_rhs_var", rhs);

		code 
			<< "// Read normal variable\n"
			<< "p_rhs = &p_rhs_var;\n"
			<< "\n"
			<< "if (*p_lhs != *p_rhs)\n"
			<<		"write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);\n";
		cleanup ("p_rhs");
	}
	else
	{
		index_lhs (LOCAL, "p_rhs", rhs);
		code 
			<< "sep_copy_on_write_ex (p_rhs);\n"
			<< "(*p_rhs)->is_ref = 1;\n"
			<< "(*p_rhs)->refcount++;\n"
			<< "zval_ptr_dtor (p_lhs);\n"
			<< "*p_lhs = *p_rhs;\n";
	}
}

class Pattern_assign_array : public Pattern
{
public:
	bool match(Statement* that)
	{
		lhs = new Wildcard<VARIABLE_NAME>;
		index = new Wildcard<VARIABLE_NAME>;
		rhs = new Wildcard<VARIABLE_NAME>;
		agn = new Assign_array (lhs, index, false, rhs);
		return (that->match(agn));
	}

	void generate_code(Generate_C* gen)
	{
		assert (lhs->value);
		assert (index->value);
		assert (rhs->value);

		code 
			<< "{\n";

		index_assign_array (LOCAL, "p_lhs", lhs->value, index->value);

		code 
			<<		"if (p_lhs != NULL)\n"
			<<		"{\n";

		assign_rhs (agn->is_ref, rhs->value);

		code 
			<<		"}\n";
		
		code 
			<< "}\n";
		code << "phc_check_invariants (TSRMLS_C);\n";
	}

protected:
	Assign_array* agn;
	Wildcard<VARIABLE_NAME>* lhs;
	Wildcard<VARIABLE_NAME>* index;
	Wildcard<VARIABLE_NAME>* rhs;
};

void push_rhs (bool is_ref, VARIABLE_NAME* rhs)
{
	if (!is_ref)
	{
		declare ("p_rhs");
		code 
			<< "zval* temp = NULL;\n"
			<< "p_rhs = &temp;\n";
		read (LOCAL, "p_rhs", rhs);
		code 
			<< "if (*p_lhs != *p_rhs)\n"
			<<		"write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);\n";
		cleanup ("p_rhs");
	}
	else
	{
		index_lhs (LOCAL, "p_rhs", rhs);
		code 
			<< "sep_copy_on_write_ex (p_rhs);\n"
			<< "(*p_rhs)->is_ref = 1;\n"
			<< "(*p_rhs)->refcount++;\n"
			<< "zval_ptr_dtor (p_lhs);\n"
			<< "*p_lhs = *p_rhs;\n";
	}
}

class Pattern_push_array : public Pattern
{
public:
	bool match(Statement* that)
	{
		lhs = new Wildcard<VARIABLE_NAME>;
		rhs = new Wildcard<VARIABLE_NAME>;
		agn = new Push_array (lhs, false, rhs);
		return (that->match(agn));
	}

	void generate_code(Generate_C* gen)
	{
		assert (lhs->value);
		assert (rhs->value);

		code 
			<< "{\n"
			<<		"zval** p_lhs;\n";

		read_st (LOCAL, "p_lhs_var", lhs->value);
		code 
			<<	"	// Array push \n"
			<<	"	p_lhs = push_and_index_ht (p_lhs_var TSRMLS_CC);\n"
			<<	""
			<<	"	if (p_lhs != NULL)\n"
			<<	"	{\n";

		push_rhs (agn->is_ref, rhs->value);

		code 
			<<		"}\n"
			<< "}\n"
			<< "phc_check_invariants (TSRMLS_C);\n";
	}

protected:
	Push_array* agn;
	Wildcard<VARIABLE_NAME>* lhs;
	Wildcard<VARIABLE_NAME>* rhs;
};

/*
 * Assign_zval is a specialization of Assignment for assignments to a simple
 * zval which takes care of creating a new zval for the LHS if necessary.
 *
 * Assign_literal is a further specialization for those literal assignment
 * where the value of the literal is known at compile time (assigning a token
 * int, for example). The main difference between Assign_literal and 
 * Assign_zval is that Assign_literal can do constant pooling.
 */

class Pattern_assign_zval : public Pattern_assign_var
{
public:
	void generate_rhs ()
	{
		code
			<< "if ((*p_lhs)->is_ref)\n"
			<< "{\n"
			<< "  zval* paz_lhs = *p_lhs;\n"
			<< "  zval_dtor (paz_lhs);\n";
		initialize (code, "paz_lhs");
		code
			<< "}\n"
			<< "else\n"
			<< "{\n"
			<<	"	zval* literal;\n"
			<<	"	ALLOC_INIT_ZVAL (literal);\n";
		initialize (code, "literal");
		code
			<<	"	zval_ptr_dtor (p_lhs);\n"
			<<	"	*p_lhs = literal;\n"
			<< "}\n";
	}

	virtual void initialize (ostream& os, string var) = 0;
};

stringstream initializations;
stringstream finalizations;

template<class T, class K>
class Pattern_assign_literal : public Pattern_assign_zval 
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<T>;
		return rhs;
	}

	// record if we've seen this variable before
	void generate_rhs ()
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
				initializations << "ALLOC_INIT_ZVAL (" << var << ")\n";
				initialize (initializations, var);
			}
			code
				<< "if (" << var << " != *p_lhs)\n"
				<< "{\n"
				<<		"assert (!" << var << "->is_ref);\n"
				<<		"if ((*p_lhs)->is_ref)\n"
				<<			"overwrite_lhs (*p_lhs, " << var << ");\n"
				<<		"else\n"
				<<		"{\n"
				<<			var << "->refcount++;\n"
				<<			"zval_ptr_dtor (p_lhs);\n"
				<<			"*p_lhs = " << var << ";\n"
				<<		"}\n"
				<<	"}\n";
		}
		else
		{
			Pattern_assign_zval::generate_rhs();
		}
	}

	virtual string prefix () = 0;
	virtual K key () = 0;

protected:
	Wildcard<T>* rhs;
};

class Pattern_assign_bool : public Pattern_assign_literal<BOOL, bool>
{
	string prefix () { return "phc_const_pool_bool_"; }
	bool key () { return rhs->value->value; }

	void initialize (ostream& os, string var)
	{
		os	<< "ZVAL_BOOL (" << var << ", " 
			<<		(rhs->value->value ? 1 : 0) << ");\n";
	}

};

class Pattern_assign_int : public Pattern_assign_literal<INT, long>
{
	string prefix () { return "phc_const_pool_int_"; }
	long key () { return rhs->value->value; }

	void initialize (ostream& os, string var)
	{
		os << "ZVAL_LONG (" << var << ", " << rhs->value->value << ");\n";
	}
};

class Pattern_assign_real : public Pattern_assign_literal<REAL, string>
{
	string prefix () { return "phc_const_pool_real_"; }
	string key () { return *(dynamic_cast<String*>(rhs->value->attrs->get("phc.codegen.source_rep"))); }

	void initialize (ostream& os, string var)
	{
		os	<< "zend_eval_string(\"" << key() << ";\","
			<<		var << ", "
			<<		"\"literal\" TSRMLS_CC);\n";
	}
};

class Pattern_assign_nil : public Pattern_assign_literal<NIL, string>
{
	string prefix () { return "phc_const_pool_null_"; }
	string key () { return ""; }

	void initialize (ostream& os, string var)
	{
		os << "ZVAL_NULL (" << var << ");\n";
	}
};

class Pattern_assign_string : public Pattern_assign_literal<STRING, string>
{
	string prefix () { return "phc_const_pool_string_"; }
	string key () { return *rhs->value->value; }

	void initialize (ostream& os, string var)
	{
		os << "ZVAL_STRINGL(" << var << ", " 
			<<		"\"" << escape(rhs->value->value) << "\", "
			<<		rhs->value->value->length() << ", 1);\n";
	}

	// Escape according to C rules (this varies slightly from unparsing for PHP
	// and dot).
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


class Pattern_assign_var_to_var : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<VARIABLE_NAME>;
		return rhs;
	}

	void generate_rhs ()
	{
		if (!agn->is_ref)
		{
			declare ("p_rhs");
			code 
				<< "zval* temp = NULL;\n"
				<< "p_rhs = &temp;\n";
			read (LOCAL, "p_rhs", rhs->value);
			code 
				<< "if (*p_lhs != *p_rhs)\n"
				<<		"write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);\n";
			cleanup ("p_rhs");
		}
		else
		{
			index_lhs (LOCAL, "p_rhs", rhs->value);
			code 
				<< "sep_copy_on_write_ex (p_rhs);\n"
				<< "(*p_rhs)->is_ref = 1;\n"
				<< "(*p_rhs)->refcount++;\n"
				<< "zval_ptr_dtor (p_lhs);\n"
				<< "*p_lhs = *p_rhs;\n";
		}
	}

protected:
	Wildcard<VARIABLE_NAME>* rhs;
};

class Pattern_assign_array_index_to_var : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<Index_array>;
		return rhs;
	}

	void generate_rhs ()
	{
		if (!agn->is_ref)
		{
			declare ("p_rhs");
			code 
				<< "zval* temp = NULL;\n"
				<< "p_rhs = &temp;\n";
			read_array_index (LOCAL, "p_rhs", rhs->value);
			code 
				<< "if (*p_lhs != *p_rhs)\n"
				<<		"write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);\n";
			cleanup ("p_rhs");
		}
		else
		{
			index_array_index (LOCAL, "p_rhs", rhs->value);
			code 
				<< "sep_copy_on_write_ex (p_rhs);\n"
				<< "(*p_rhs)->is_ref = 1;\n"
				<< "(*p_rhs)->refcount++;\n"
				<< "zval_ptr_dtor (p_lhs);\n"
				<< "*p_lhs = *p_rhs;\n";
		}
	}

protected:
	Wildcard<Index_array>* rhs;
};

class Pattern_cast : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<VARIABLE_NAME>;
		cast = new Wildcard<CAST>;
		return new Cast (cast, rhs);
	}

	void generate_rhs ()
	{
		assert (agn->is_ref == false);
		assert (lhs);

		// this much copied from Assign_var
		if (!agn->is_ref)
		{
			declare ("p_rhs");
			code 
				<< "zval* temp = NULL;\n"
				<< "p_rhs = &temp;\n";
			read (LOCAL, "p_rhs", rhs->value);
			code 
				<< "if (*p_lhs != *p_rhs)\n"
				<<		"write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);\n";
			cleanup ("p_rhs");
		}
		else
		{
			index_lhs (LOCAL, "p_rhs", rhs->value);
			code 
				<< "sep_copy_on_write_ex (p_rhs);\n"
				<< "(*p_rhs)->is_ref = 1;\n"
				<< "(*p_rhs)->refcount++;\n"
				<< "zval_ptr_dtor (p_lhs);\n"
				<< "*p_lhs = *p_rhs;\n";
		}
		// as far as here

		if (*cast->value->value == "string")
			code << "cast_var (p_lhs, IS_STRING);\n";
		else if (*cast->value->value == "int")
			code << "cast_var (p_lhs, IS_LONG);\n";
		else if (*cast->value->value == "array")
			code << "cast_var (p_lhs, IS_ARRAY);\n";
		else if (*cast->value->value == "null")
			code << "cast_var (p_lhs, IS_NULL);\n";
		else if (*cast->value->value == "bool" || *cast->value->value == "boolean")
			code << "cast_var (p_lhs, IS_BOOL);\n";
		else if (*cast->value->value == "real")
			code << "cast_var (p_lhs, IS_DOUBLE);\n";
		else
			assert (0 && "unimplemented"); // TODO: unimplemented
	}

public:
	Wildcard<CAST>* cast;
	Wildcard<VARIABLE_NAME>* rhs;
};

class Pattern_global : public Pattern 
{
public:
	bool match(Statement* that)
	{
		rhs = new Wildcard<Variable_name>;
		return(that->match(new Global(rhs)));
	}

	void generate_code(Generate_C* gen)
	{
		global (rhs->value);
	}

protected:
	Wildcard<Variable_name>* rhs;
};

class Pattern_assign_constant : public Pattern_assign_var
{
public:

	Expr* rhs_pattern()
	{
		rhs = new Wildcard<Constant> ();
		return rhs;
	}

	void generate_rhs ()
	{
		assert (lhs);
		// Check whether its in the form CONST or CLASS::CONST
		String* name = new String ("");
		if (rhs->value->class_name)
		{
			name->append (*rhs->value->class_name->value);
			name->append ("::");
		}

		name->append (*rhs->value->constant_name->value);

		// zend_get_constant returns a copy of the constant, so we can
		// put it in directly for non-reference lhss, and use the
		// data directly without copying for reference lhss.
		code
			<< "if (!(*p_lhs)->is_ref)\n"
			<< "{\n"
			<<		"zval_ptr_dtor (p_lhs);\n"
			<<		"get_constant ( "
			<<			"\"" << *name << "\", "
			<<			name->length() << ", " // exclude NULL-terminator
			<<			"p_lhs "
			<<			" TSRMLS_CC);\n"
			<< "}\n"
			<< "else\n"
			<< "{\n"
			<<		"zval* constant;\n"
			<<		"get_constant ( "
			<<			"\"" << *name << "\", "
			<<			name->length() << ", " // exclude NULL-terminator
			<<			"&constant "
			<<			" TSRMLS_CC);\n"
			// get_constant guarantees new memory, so we can reuse the data, rather than copy and delete it
			<<		"overwrite_lhs_no_copy (*p_lhs, constant);\n"
			<<		"safe_free_zval_ptr (constant);\n"
			<< "}\n";
	}

protected:
	Wildcard<Constant>* rhs;
};

/* A number of patterns can be n the form of either Eval_expr
 * (Method_invocation) or Assign_var (_, _, Method_invocation). Abstract this
 * to avoid duplication. */
class Pattern_eval_expr_or_assign_var : public Pattern_assign_var
{
	bool match(Statement* that)
	{
		bool result = that->match (new Eval_expr (rhs_pattern()));
		if (result)
		{
			lhs = NULL;
			return true;
		}
		else
			return Pattern_assign_var::match(that);
	}

	void generate_code(Generate_C* gen)
	{
		if (lhs == NULL)
		{
			code << "{\n";
			generate_rhs ();
			code << "}\n";
		}
		else
			Pattern_assign_var::generate_code (gen);
	}
};

class Pattern_eval : public Pattern_eval_expr_or_assign_var
{
	Expr* rhs_pattern()
	{
		eval_arg = new Wildcard<Actual_parameter>;
		return new Method_invocation(
			NULL,	
			new METHOD_NAME( new String("eval")),
			new List<Actual_parameter*>(eval_arg
				)
			);
	}

	// TODO this is untidy, and slower than it should be. Not a
	// priority.
	void generate_rhs ()
	{
		if (eval_arg->value->target) phc_unsupported (eval_arg->value);
		if (eval_arg->value->array_indices->size ()) phc_unsupported (eval_arg->value);

		code << "{\n";
		read_rvalue (LOCAL, "eval_arg", dyc<VARIABLE_NAME> (eval_arg->value->variable_name));

		if (lhs)
		{
			declare ("p_rhs");
			code 
				<< "zval* temp = NULL;\n"
				<< "p_rhs = &temp;\n"
				<< "eval (eval_arg, p_rhs, &is_p_rhs_new TSRMLS_CC);\n";

			if (!agn->is_ref)
			{
				code 
					<< "write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);\n";
			}
			else
			{
				code 
					<< "sep_copy_on_write_ex (p_rhs);\n"
					<< "(*p_rhs)->is_ref = 1;\n"
					<< "(*p_rhs)->refcount++;\n"
					<< "zval_ptr_dtor (p_lhs);\n"
					<< "*p_lhs = *p_rhs;\n";
			}
			cleanup ("p_rhs");
		}
		else
		{
			code << "eval (eval_arg, NULL, NULL TSRMLS_CC);\n";
		}

		code << "}\n" ;
	}

protected:
	Wildcard<Actual_parameter>* eval_arg;
};

// TODO exit/die/unset etc are probably not by reference. I can probably shred
// them as a result. Also, they probably can't be called with variable
// variables.
class Pattern_exit : public Pattern_eval_expr_or_assign_var
{
public:
	Pattern_exit () { name = new METHOD_NAME (s("exit")); }

public:
	Expr* rhs_pattern ()
	{
		exit_arg = new Wildcard<Actual_parameter> ();
		return new Method_invocation(
						NULL,	
						name,
						new List<Actual_parameter*>(exit_arg)
						);
	}

	void generate_rhs ()
	{
		code << "{\n";
		if (exit_arg->value->target) phc_unsupported (exit_arg->value);
		if (exit_arg->value->array_indices->size ()) phc_unsupported (exit_arg->value);

		read_rvalue (LOCAL, "arg", dyc<VARIABLE_NAME> (exit_arg->value->variable_name));

		// Fetch the parameter
		code
			<<	"// Exit ()\n"
			<<	"phc_exit (arg TSRMLS_CC);\n";

		code << "}\n";
	}

protected:
	Wildcard<Actual_parameter>* exit_arg;
	METHOD_NAME* name;
};

// die() and exit() are synonyms
class Pattern_die : public Pattern_exit
{
public:
	Pattern_die() { name = new METHOD_NAME (s("die")); }
};

class Pattern_method_invocation : public Pattern_eval_expr_or_assign_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<Method_invocation>;
		return rhs;
	}

	void generate_rhs ()
	{
		List<Actual_parameter*>::const_iterator i;
		unsigned index;
		
		// code << "debug_hash(EG(active_symbol_table));\n";

		// Variable function or ordinary function?
		METHOD_NAME* name;
		name = dynamic_cast<METHOD_NAME*>(rhs->value->method_name);

		if (name == NULL) phc_unsupported (rhs->value);

		declare ("p_rhs");
		code 
			<< "zval* temp;\n"
			<< "p_rhs = &temp;\n";

		int num_args = rhs->value->actual_parameters->size();
		code
			// lookup the function and cache it for next time
			<< "// Call the function\n"
			<< "static zend_fcall_info fci;\n"
			<< "static zend_fcall_info_cache fcic = {0,NULL,NULL,NULL};\n"
			<< "if (!fcic.initialized)\n"
			<< "{\n"
			<<		"zval function_name;\n"
			<<		"INIT_PZVAL(&function_name);\n"
			<<		"ZVAL_STRING(&function_name, "
			<<			"\"" << *name->value << "\", "
			<<			"0);\n"

			<<		"int result = zend_fcall_info_init (&function_name, &fci, &fcic TSRMLS_CC);\n"
			<< 	"if (result == FAILURE) // check for missing function\n"
			<< 	"{\n"
			<<			"phc_setup_error (1, \"" 
			<< 			*rhs->get_filename () << "\", " 
			<< 			rhs->get_line_number () << ", "
			<<				"NULL TSRMLS_CC);\n"
						// die
			<<			"php_error_docref (NULL TSRMLS_CC, E_ERROR, "
			<<				"\"Call to undefined function %s()\", \"" 
			<< 			*name->value << "\");\n"
			<< 	"}\n"
			<< "}\n"
			<< "zend_function* signature = fcic.function_handler;\n";


		// Figure out which parameters need to be passed by reference
		if (num_args)
		{
			code
				<< "zend_arg_info* arg_info = signature->common.arg_info;\n"
				<< "int by_ref[" << num_args << "];\n"
				;
		}

		// TODO: Not 100% this is fully correct; in particular, 
		// pass_rest_by_reference does not seem to work.
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
			if ((*i)->target) phc_unsupported (*i);

			VARIABLE_NAME* var_name = dyc<VARIABLE_NAME>((*i)->variable_name);

			code << "destruct[" << index << "] = 0;\n";
			/* If we need a point that goes straight into the
			 * hashtable, which we do for pass-by-ref, then we return a
			 * zval**, straight into args_ind. Otherwise we return a
			 * zval*, put it in args, and fetch it into args_ind after.
			 * (It is difficult to return a zval** which doesnt point
			 * into its containing hashtable, otherwise. */
			if ((*i)->array_indices->size ())
			{
				// TODO: variables are allowed have more than 1 index
				// (so long as the indexes are all temporaries). We do
				// not know whether to shred the variables using
				// references or not, since we do not know until
				// run-time whether the function is call-by-reference or
				// not.
				if ((*i)->array_indices->size () > 1) phc_unsupported (*i);
				Rvalue* ind = (*i)->array_indices->front ();

				code
					<< "if (by_ref [" << index << "])\n"
					<< "{\n";

				read_st (LOCAL, "arg", var_name);
				read_rvalue (LOCAL, "ind", ind);

				code
					<< "	args_ind[" << index << "] = fetch_array_arg_by_ref ("
					<<				"arg, "
					<<				"ind, "
					<<				"&destruct[" << index << "] TSRMLS_CC);\n"
					<<	"  args[" << index << "] = *args_ind[" << index << "];\n"
					<< "	assert (!in_copy_on_write (*args_ind[" << index << "]));\n"
					<< "}\n"
					<< "else\n"
					<< "{\n";

				read_rvalue (LOCAL, "arg", var_name);
				read_rvalue (LOCAL, "ind", ind);

				code
					<< "  args[" << index << "] = fetch_array_arg ("
					<<				"arg, "
					<<				"ind, "
					<<				"&destruct[" << index << "] TSRMLS_CC);\n"
					<< " args_ind[" << index << "] = &args[" << index << "];\n"
					<< "}\n"
					;
			}
			else
			{

				code 
					<< "if (by_ref [" << index << "])\n"
					<< "{\n";
;
				read_st (LOCAL, "p_arg", var_name);
				code
					<< "	args_ind[" << index << "] = fetch_var_arg_by_ref ("
					<<				"p_arg);\n"
					<< "	assert (!in_copy_on_write (*args_ind[" << index << "]));\n"
					<<	"  args[" << index << "] = *args_ind[" << index << "];\n"
					<< "}\n"
					<< "else\n"
					<< "{\n";

				read_rvalue (LOCAL, "arg", var_name);

				code
					<< "  args[" << index << "] = fetch_var_arg ("
					<<				"arg, "
					<<				"&destruct[" << index << "]);\n"
					<< " args_ind[" << index << "] = &args[" << index << "];\n"
					<< "}\n"
					;

			}
		}

		code
			<< "phc_setup_error (1, \""
			<<				*rhs->get_filename () << "\", " 
			<<				rhs->get_line_number () << ", "
			<< "			NULL TSRMLS_CC);\n"

			// save existing paramters, in case of recursion
			<< "int param_count_save = fci.param_count;\n"
			<< "zval*** params_save = fci.params;\n"
			<< "zval** retval_save = fci.retval_ptr_ptr;\n"

			// set up params
			<< "fci.params = args_ind;\n"
			<< "fci.param_count = " << num_args << ";\n"
			<< "fci.retval_ptr_ptr = p_rhs;\n"

			// call the function
			<< "int success = zend_call_function (&fci, &fcic TSRMLS_CC);\n"
			<< "assert(success == SUCCESS);\n"

			// restore params
			<< "fci.params = params_save;\n"
			<< "fci.param_count = param_count_save;\n"
			<< "fci.retval_ptr_ptr = retval_save;\n"

			// unset the errors
			<< "phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);\n"
			;

		// Workaround a bug (feature?) of the Zend API that I don't
		// know how to solve otherwise. It seems that Zend resets the
		// refcount and is_ref fields of the return value after the
		// function returns. That is okay if the function does not
		// return a reference (because it will have created a fresh
		// zval to hold the result), but obviously garbage collector
		// problems when the function returned a reference to an
		// existing zval. Hence, we increment the refcount here, and
		// set is_ref to true if the function signature declares the
		// function to return a reference. This causes memory leaks,
		// so we make a note to clean up the memory. It only occurs
		// when calling eval'd functions, because they do in fact
		// return the correct refcount.
		code 
			<< "if(signature->common.return_reference)\n"
			<< "{\n"
			<< "	assert (*p_rhs != EG(uninitialized_zval_ptr));\n"
			<< "	(*p_rhs)->is_ref = 1;\n"
			// TODO what happens if there's supposed to be 8 or 10
			// references to it.
			<< "  if (signature->type == ZEND_USER_FUNCTION)\n"
			<< "		is_p_rhs_new = 1;\n"
			<< "}\n"
			<< "else\n"
			<< "{\n"
			<< "	is_p_rhs_new = 1;\n"
			<< "}\n" ;

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

		if (lhs)
		{
			if (!agn->is_ref)
			{
				code 
					<< "write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);\n";
			}
			else
			{
				code 
					<< "sep_copy_on_write_ex (p_rhs);\n"
					<< "(*p_rhs)->is_ref = 1;\n"
					<< "(*p_rhs)->refcount++;\n"
					<< "zval_ptr_dtor (p_lhs);\n"
					<< "*p_lhs = *p_rhs;\n";
			}
		}
		cleanup ("p_rhs");
		
		// code << "debug_hash(EG(active_symbol_table));\n";
	}

protected:
	Wildcard<Method_invocation>* rhs;
};

class Pattern_bin_op : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		left = new Wildcard<VARIABLE_NAME>;
		op = new Wildcard<OP>;
		right = new Wildcard<VARIABLE_NAME>;

		return new Bin_op (left, op, right); 
	}

	void generate_rhs ()
	{
		assert (lhs);
		assert(
			op_functions.find(*op->value->value) != 
			op_functions.end());
		string op_fn = op_functions[*op->value->value]; 

		read_rvalue (LOCAL, "left", left->value);
		read_rvalue (LOCAL, "right", right->value);

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
	Wildcard<VARIABLE_NAME>* left;
	Wildcard<OP>* op;
	Wildcard<VARIABLE_NAME>* right;
};

class Pattern_unary_op : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		op = new Wildcard<OP>;
		var_name = new Wildcard<VARIABLE_NAME>;

		return new Unary_op(op, var_name);
	}

	void generate_rhs ()
	{
		assert (lhs);
		assert(
			op_functions.find(*op->value->value) != 
			op_functions.end());
		string op_fn = op_functions[*op->value->value]; 

		read_rvalue (LOCAL, "expr", var_name->value);

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
	Wildcard<OP>* op;
	Wildcard<VARIABLE_NAME>* var_name;
};

class Pattern_pre_op : public Pattern
{
public:
	bool match(Statement* that)
	{
		op = new Wildcard<OP>;
		var = new Wildcard<VARIABLE_NAME>;
		return(that->match(new Pre_op(op, var)));
	}

	void generate_code(Generate_C* gen)
	{
		code << "{\n";

		assert(
			op_functions.find(*op->value->value) != 
			op_functions.end());
		string op_fn = op_functions[*op->value->value]; 

		read_st (LOCAL, "p_var", var->value);

		code
			<< "sep_copy_on_write_ex (p_var);\n"
			<< op_fn << "(*p_var);\n";

		code << "}\n";
	}

protected:
	Wildcard<VARIABLE_NAME>* var;
	Wildcard<OP>* op;
};


class Pattern_return : public Pattern
{
	bool match(Statement* that)
	{
		expr = new Wildcard<Expr>;
		return(that->match(new Return(expr)));
	}

	void generate_code(Generate_C* gen)
	{
		code << "{\n";
		if(!gen->return_by_reference)
		{
			read_rvalue (LOCAL, "rhs", dyc<VARIABLE_NAME> (expr->value));

			// Run-time return by reference had slightly different
			// semantics to compile-time. There is no way within a
			// function to tell if the run-time return by reference is
			// set, but its unnecessary anyway.
			code 
				<< "return_value->value = rhs->value;\n"
				<< "return_value->type = rhs->type;\n"
				<< "zval_copy_ctor (return_value);\n"
				;
		}
		else
		{
			// converted into an array
			// TODO: why?
			if (isa<Index_array> (expr->value))
				index_lhs (LOCAL, "p_rhs", dyc<Index_array> (expr->value));
			else
				index_lhs (LOCAL, "p_rhs", expr->value);

			code
				<< "sep_copy_on_write_ex (p_rhs);\n"
				<< "zval_ptr_dtor (return_value_ptr);\n"
				<< "(*p_rhs)->is_ref = 1;\n"
				<< "(*p_rhs)->refcount++;\n"
				<< "*return_value_ptr = *p_rhs;\n";

		}

		code 
		<< "goto end_of_function;\n"
		<< "}\n"
		;
	}

protected:
	Wildcard<Expr>* expr;
};

class Pattern_unset : public Pattern
{
	bool match(Statement* that)
	{
		param = new Wildcard<Actual_parameter>;
		return that->match(
			new Eval_expr (
				new Method_invocation(
					"unset",
					param)));
	}

	void generate_code(Generate_C* gen)
	{
		code << "{\n";

		VARIABLE_NAME* var_name = dynamic_cast <VARIABLE_NAME*> (param->value->variable_name);

		if (var_name != NULL)
		{
			if (param->value->array_indices->size() == 0)
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
						<<		");\n";
				}
			}
			else 
			{
				assert(param->value->array_indices->size() == 1);
				Rvalue* index = (param->value->array_indices->front());
				read_st (LOCAL, "u_array", var_name);
				read_rvalue (LOCAL, "u_index", index);

				code
					<< "unset_array ("
					<<    "u_array, "
					<<    "u_index "
					<<		" TSRMLS_CC);\n";
			}
		}
		else
		{
			// Variable variable
			// TODO
			phc_unsupported (param);
		}
		code << "}\n";
	}

protected:
	Wildcard<Actual_parameter>* param;
};

class Pattern_isset : public Pattern_assign_zval
{
	Expr* rhs_pattern()
	{
		param = new Wildcard<Actual_parameter>;
		return new Method_invocation("isset", param);
	}

	void initialize(ostream& code, string lhs)
	{
		code << "{\n";

		VARIABLE_NAME* var_name = dynamic_cast<VARIABLE_NAME*> (param->value->variable_name);

		if (var_name)
		{
			if (param->value->array_indices->size() == 0)
			{
				if (var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
				{
					String* name = get_non_st_name (var_name);
					code << "ZVAL_BOOL(" << lhs << ", " << *name << " != NULL);\n"; 
				}
				else
				{
					String* name = var_name->value;
					code
						<< "ZVAL_BOOL(" << lhs << ", "
						<< "isset_var ("
						<<		get_scope (LOCAL) << ", "
						<<		"\"" << *name << "\", "
						<<		name->length() + 1
						// no get_hash version
						<<		"));\n";
				}
			}
			else 
			{
				// TODO this can have > 1 array_index
				assert(param->value->array_indices->size() == 1);
				Rvalue* index = param->value->array_indices->front();
				read_st (LOCAL, "u_array", var_name);
				read_rvalue (LOCAL, "u_index", index);

				code
				  << "ZVAL_BOOL(" << lhs << ", "
					<< "isset_array ("
					<<    "u_array, "
					<<    "u_index "
					<<		" TSRMLS_CC));\n";
			}
		}
		else
		{
			// Variable variable
			// TODO
			phc_unsupported (param);
		}
		code << "}\n";
	}

protected:
	Wildcard<Actual_parameter>* param;
};

/*
 * Foreach patterns
 */

class Pattern_foreach_reset: public Pattern
{
	bool match (Statement* that)
	{
		reset = new Wildcard<Foreach_reset>;
		return that->match (reset);
	}

	void generate_code(Generate_C* gen)
	{
		// declare the external iterator so outside local scope blocks
		code
			<< "HashPosition " << *reset->value->iter->value << ";\n"
			<< "{\n";

		read_rvalue (LOCAL, "fe_array", reset->value->array);
		code 
			<< "zend_hash_internal_pointer_reset_ex ("
			<< "						fe_array->value.ht, "
			<< "						&" << *reset->value->iter->value << ");\n"
			<< "}\n";
	}

protected:
	Wildcard<Foreach_reset>* reset;
};

class Pattern_foreach_has_key : public Pattern_assign_zval
{

	Expr* rhs_pattern()
	{
		has_key = new Wildcard<Foreach_has_key>;
		return has_key;
	}

	void initialize (ostream& os, string var)
	{
		read_rvalue (LOCAL, "fe_array", has_key->value->array);
		os
			<< "int type = zend_hash_get_current_key_type_ex ("
			<< "						fe_array->value.ht, "
			<< "						&" << *has_key->value->iter->value << ");\n"
			<< "ZVAL_BOOL(" << var << ", type != HASH_KEY_NON_EXISTANT);\n";
	}

protected:
	Wildcard<Foreach_has_key>* has_key;
};

class Pattern_foreach_get_key : public Pattern_assign_zval
{
	Expr* rhs_pattern()
	{
		get_key = new Wildcard<Foreach_get_key>;
		return get_key;
	}

	void initialize (ostream& os, string var)
	{
		read_rvalue (LOCAL, "fe_array", get_key->value->array);
		os
			<< "char* str_index = NULL;\n"
			<< "uint str_length;\n"
			<< "ulong num_index;\n"
			<< "int result = zend_hash_get_current_key_ex (\n"
			<< "						fe_array->value.ht,"
			<< "						&str_index, &str_length, &num_index, "
			<< "						0, "
			<< "						&" << *get_key->value->iter->value << ");\n"
			<< "if (result == HASH_KEY_IS_LONG)\n"
			<< "{\n"
			<< "	ZVAL_LONG (" << var << ", num_index);\n"
			<< "}\n"
			<< "else\n"
			<< "{\n"
			<< "	ZVAL_STRINGL (" << var << ", str_index, str_length - 1, 1);\n"
			<< "}\n";
	}

protected:
	Wildcard<Foreach_get_key>* get_key;
};

class Pattern_foreach_get_val : public Pattern_assign_var
{
	Expr* rhs_pattern()
	{
		get_val = new Wildcard<Foreach_get_val>;
		return get_val;
	}

	void generate_rhs ()
	{
		// FIXME: this happens because of strange, multi-stage lowering
		if (lhs == NULL)
			return;

		read_rvalue (LOCAL, "fe_array", get_val->value->array);
		if (!agn->is_ref)
		{
			declare ("p_rhs");
			code 
				<< "zval* temp = NULL;\n"
				<< "p_rhs = &temp;\n"
				<< "int result = zend_hash_get_current_data_ex (\n"
				<< "						fe_array->value.ht, "
				<<							"(void**)(&p_rhs), "
				<< "						&" << *get_val->value->iter->value << ");\n"
				<< "assert (result == SUCCESS);\n"
				<< "write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);\n";
			cleanup ("p_rhs");
		}
		else
		{
			code 
				<< "zval** p_rhs = NULL;\n"
				<< "int result = zend_hash_get_current_data_ex (\n"
				<< "						fe_array->value.ht, "
				<<							"(void**)(&p_rhs), "
				<< "						&" << *get_val->value->iter->value << ");\n"
				<< "assert (result == SUCCESS);\n"
				<< "sep_copy_on_write_ex (p_rhs);\n"
				<< "(*p_rhs)->is_ref = 1;\n"
				<< "(*p_rhs)->refcount++;\n"
				<< "zval_ptr_dtor (p_lhs);\n"
				<< "*p_lhs = *p_rhs;\n";
		}
	}

protected:
	Wildcard<Foreach_get_val>* get_val;
};

class Pattern_foreach_next: public Pattern
{
	bool match (Statement* that)
	{
		next = new Wildcard<Foreach_next>;
		return that->match (next);
	}

	void generate_code (Generate_C* gen)
	{
		code << "{\n";
		read_rvalue (LOCAL, "fe_array", next->value->array);
		code 
			<< "int result = zend_hash_move_forward_ex ("
			<<							"fe_array->value.ht, "
			<<							"&" << *next->value->iter->value << ");\n"
			<< "assert (result == SUCCESS);\n";
		code << "}\n";
	}

protected:
	Wildcard<Foreach_next>* next;
};

class Pattern_foreach_end : public Pattern
{
	bool match (Statement* that)
	{
		end = new Wildcard<Foreach_end>;
		return that->match (end);
	}

	void generate_code(Generate_C* gen)
	{
		code << "{\n";
		read_rvalue (LOCAL, "fe_array", end->value->array);
		code 
			<< "zend_hash_internal_pointer_end_ex ("
			<<							"fe_array->value.ht, "
			<<							"&" << *end->value->iter->value << ");\n";
		code << "}\n";
	}

protected:
	Wildcard<Foreach_end>* end;
};



/*
 * Visitor methods to generate C code
 * Visitor for statements uses the patterns defined above.
 */

void Generate_C::children_statement(Statement* in)
{
	stringstream ss;
	MIR_unparser (ss).unparse (in);

	while (not ss.eof ())
	{
	  // Make reading the generated code easier. If we use a /*
	  // comment, then we may get nested /* */ comments, which arent
	  // allowed and result in syntax errors in C. Use // instead.
		string str;
		getline (ss, str);
		code << "// " << str << endl;
	}

	Pattern* patterns[] = 
	{
		new Pattern_method_definition()
	,	new Pattern_assign_string ()
	,	new Pattern_assign_int ()
	,	new Pattern_assign_bool ()
	,	new Pattern_assign_real ()
	,	new Pattern_assign_nil ()
	,	new Pattern_assign_constant ()
	,	new Pattern_assign_var_to_var ()
	,	new Pattern_assign_array_index_to_var ()
//	,	new Pattern_assign_var_var () TODO
	,	new Pattern_assign_array ()
	,	new Pattern_push_array ()
//	,	new Pattern_eval_expr () TODO
	,	new Pattern_global()
	,	new Pattern_eval()
	,	new Pattern_exit()
	,	new Pattern_die()
	,	new Pattern_unset()
	,	new Pattern_isset()
	,	new Pattern_method_invocation()
	,	new Pattern_pre_op()
	,	new Pattern_bin_op()
	,	new Pattern_unary_op()
	,	new Pattern_label()
	,	new Pattern_branch()
	,	new Pattern_goto()
	,	new Pattern_return()
	,	new Pattern_cast ()
	,	new Pattern_foreach_reset ()
	,	new Pattern_foreach_has_key ()
	,	new Pattern_foreach_get_key ()
	,	new Pattern_foreach_get_val ()
	,	new Pattern_foreach_next ()
	,	new Pattern_foreach_end ()
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
		cerr << "could not generate code for " << demangle(in, true) << endl;
		in->visit (new MIR_unparser (cout, true));
		in->visit (new MIR_XML_unparser (cout));
		abort();
	}
}

void Generate_C::pre_php_script(PHP_script* in)
{
	// For now, we simply include this.
	ifstream file;

	// Check the current directory first. This means we can change libphc.cpp without recompiling or installing.
	file.open ("libphc.cpp");

	// Check the installed directory.
	if (!file.is_open())
		file.open (DATADIR "/phc/libphc.cpp");

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

void Generate_C::post_php_script(PHP_script* in)
{
	List<Signature*>::const_iterator i;

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

		List<Formal_parameter*>::const_iterator j;
		for(
			j = (*i)->formal_parameters->begin();
			j != (*i)->formal_parameters->end();
			j++)
		{
			code 
			<< "ZEND_ARG_INFO("
			<< ((*j)->is_ref ? "1" : "0")
			<< ", \"" << *(*j)->var->variable_name->value << "\")\n"; 
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
		"   int dealloc_pools = 1;\n"
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
		"		dealloc_pools = 0;\n"
		"   }\n"
		"   zend_end_try ();\n"
		"   if (dealloc_pools)\n"
		"   {\n"
		<< finalizations.str () << 
		"   }\n"
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
	methods = new List<Signature*>;
	name = new String ("generate-c");
	description = new String ("Generate C code from the MIR");
}
