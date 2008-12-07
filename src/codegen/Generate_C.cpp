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
 */

// TODO Variable_variables cannot be used to access superglobals. See warning
// in http://php.net/manual/en/language.variables.superglobals.php
// TODO: that is not true - add a test case.

// TODO:
//		magic methods are:
//			__construct
//			__destruct
//			__get
//			__set
//			__unset
//			__isset
//			__call
//			__toString
//			__serialize
//			__unserialize
//
//	So that means casts are pure.

#include <fstream>

#include "lib/List.h"
#include "lib/Set.h"
#include "lib/escape.h"
#include "lib/demangle.h"
#include "process_ir/General.h"
#include "process_ir/XML_unparser.h"

#include "Generate_C.h"
#include "embed/embed.h"

using namespace MIR;
using namespace std;

// Label supported features
void phc_unsupported (Node* node, const char* feature)
{
	cerr << "Could not generate code for " << feature << endl;
	(new MIR_unparser (cerr, true))->unparse (node);
	cerr << endl;
	xml_unparse (node, cerr);
	exit (-1);
}

// A single pass isnt really sufficient, but we can hack around it
// with a prologue and an epilogue.
static stringstream prologue;
static stringstream code;
static stringstream epilogue;
static stringstream initializations;
static stringstream finalizations;

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

// TODO: split functionality into 3 separate portions. Split the visitor and Pass functionality.
//	Generate_C_prologue gen_prologue;
//	Generate_C_body gen_body;
//	Generate_C_epilogue gen_epilogue;
//	Generate_C_initializations gen_initialize;
//	Generate_C_finalizations gen_finalize;

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


/*
 * Helper functions
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

string suffix (string str, string suffix)
{
	stringstream ss;
	ss << str << "_" << suffix;
	return ss.str ();
}

string prefix (string str, string prefix)
{
	stringstream ss;
	ss << prefix << "_" << str;
	return ss.str ();
}

string get_non_st_name (String* var_name)
{
	return prefix (*var_name, "local");
}

string get_non_st_name (VARIABLE_NAME* var_name)
{
	assert (var_name->attrs->is_true ("phc.codegen.st_entry_not_required"));
	return get_non_st_name (var_name->value);
}

string read_literal (Scope, string, Literal*);

// Declare and fetch a zval* containing the value for RVALUE. The value can be
// changed, but the symbol-table entry cannot be affected through this.
string read_rvalue (Scope scope, string zvp, Rvalue* rvalue)
{
	stringstream ss;
	if (isa<Literal> (rvalue))
	{
		return read_literal (scope, zvp, dyc<Literal> (rvalue));
	}

	VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (rvalue);
	if (scope == LOCAL && var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
	{
		string name = get_non_st_name (var_name);
		ss
		<< "zval* " << zvp << ";\n"
		<< "if (" << name << " == NULL)\n"
		<< "{\n"
		<<		zvp << " = EG (uninitialized_zval_ptr);\n"
		<< "}\n"
		<< "else\n"
		<< "{\n"
		<<		zvp << " = " << name << ";\n"
		<< "}\n"
		;
	}
	else
	{
		String* name = var_name->value;
		ss	
		<< "zval* " << zvp << " = read_var (" 
		<<								get_scope (scope) << ", "
		<<								"\"" << *name << "\", "
		<<								name->size () + 1  << ", "
		<<								get_hash (name) << " TSRMLS_CC);\n"
		;
	}
	return ss.str ();
}

// TODO: This should be integrated into each function. In particular, we want
// to remove the slowness of adding the uninitialized_zval_ptr, only to remove
// it a second later.

// Declare and fetch a zval** into ZVP, which is the symbol-table entry for
// VAR_NAME. This zval** can be over-written, which will change the
// symbol-table entry.
string get_st_entry (Scope scope, string zvp, VARIABLE_NAME* var_name)
{
	stringstream ss;
	if (scope == LOCAL && var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
	{
		string name = get_non_st_name (var_name);
		ss
		<< "if (" << name << " == NULL)\n"
		<< "{\n"
		<<		name << " = EG (uninitialized_zval_ptr);\n"
		<<		name << "->refcount++;\n"
		<< "}\n"
		<<	"zval** " << zvp << " = &" << name << ";\n";
	}
	else
	{
		String* name = var_name->value;
		ss
		<< "zval** " << zvp << "= get_st_entry (" 
		<<									get_scope (scope) << ", "
		<<									"\"" << *name << "\", "
		<<									name->size () + 1  << ", "
		<<									get_hash (name) << " TSRMLS_CC);\n";
	}
	return ss.str();
}

// Declare and fetch a zval** into ZVP, which is the hash-table entry for
// VAR_NAME[INDEX]. This zval** can be over-written, which will change the
// hash-table entry.
string get_array_entry (Scope scope, string zvp, VARIABLE_NAME* var_name, Rvalue* index)
{
	stringstream ss;
	string zvp_name = suffix (zvp, "var");
	string zvp_index = suffix (zvp, "index");

	ss	
	// TODO dont need get_st_entry here
	<< get_st_entry (scope, zvp_name, var_name)
	<< read_rvalue (scope, zvp_index, index)
	<<	"zval**" << zvp << " = get_ht_entry ("
	<<						zvp_name << ", "
	<<						zvp_index
	<<						" TSRMLS_CC);\n"
	;

	return ss.str();
}

/* Generate code to read the variable named in VAR to the zval* ZVP */
string read_var (Scope scope, string zvp, VARIABLE_NAME* var_name)
{
	// the same as read_rvalue, but doesnt declare
	stringstream ss;
	string name = suffix (zvp, "var");

	ss
	<< "// Read normal variable\n"
	<< read_rvalue (scope, name, var_name)
	<< zvp << " = &" << name << ";\n"; 

	return ss.str();
}

/*
 * Find the variable in target_scope whose name is given by var_var in var_scope
 * and store the result in zvp
 */
string get_var_var (Scope target_scope, string zvp, Scope var_scope, VARIABLE_NAME* var_var)
{
	stringstream ss;
	ss
	<< "// Read variable variable\n"
	<< "{\n"
	<< read_rvalue (var_scope, "var_var", var_var)
	<< zvp << " = get_var_var (" 
	<<					get_scope (target_scope) << ", "
	<<					"var_var, "
	<<					"1 "
	<<					"TSRMLS_CC);\n"
	<< "}\n"
	;
	return ss.str();
}

/*
 * Like get_var_var, but do not add the variable to the scope
 * if not already there
 */
string read_var_var (Scope scope, string zvp, VARIABLE_NAME* var_var)
{
	stringstream ss;
	ss
	<< "// Read variable variable\n"
	<< read_rvalue (scope, "var_var", var_var)
	<< zvp << " = read_var_var (" 
	<<					get_scope (scope) << ", "
	<<					"var_var "
	<<					" TSRMLS_CC);\n"
	;
	return ss.str();
}


/*
 * Map of the Zend functions that implement the operators
 *
 * The map also contains entries for ++ and --, which are identical to the
 * entries for + and -, but obviously need to be invoked slightly differently.
 */

static class Op_functions : public Map<string,string>
{
public:
	Op_functions() : Map<string,string>()
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

class Pattern : virtual public GC_obj
{
public:
	Pattern () : use_scope (true) {}
	virtual bool match(Statement* that) = 0;
	virtual void generate_code(Generate_C* gen) = 0;
	virtual ~Pattern() {}
	bool use_scope;
};


class Pattern_method_definition : public Pattern
{
public:
	bool match(Statement* that)
	{
		use_scope = false;
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
		code
		<< "{\n"
		<<		"void **p;\n"
		<<		"int arg_count;\n"
		<<		"zval *param_ptr;\n"
		<<	"\n"
		<<		"p = EG(argument_stack).top_element-2;\n"
		<<		"arg_count = (ulong) *p;\n"
		<<	"\n"
		<<		"printf(\"\\nARGUMENT STACK\\n\");\n"
		<<		"while (arg_count > 0)\n"
		<<		"{\n"
		<<		"	param_ptr = *(p-arg_count);\n"
		<<		"	printf(\"addr = %08X, refcount = %d, is_ref = %d\\n\", (long)param_ptr, param_ptr->refcount, param_ptr->is_ref);\n"
		<<		"	arg_count--;\n"
		<<		"}\n"
		<<		"printf(\"END ARGUMENT STACK\\n\");\n"
		<< "}\n"
		;
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


		// Declare variables which can go outside the symbol table
		String_list* var_names = dyc<String_list> (pattern->value->attrs->get ("phc.codegen.non_st_vars"));
		foreach (String* var, *var_names)
			code << "zval* " << get_non_st_name (var) << " = NULL;\n";


		// Declare hashtable iterators for the function
		String_list* iterators = dyc<String_list> (pattern->value->attrs->get ("phc.codegen.ht_iterators"));
		foreach (String* iter, *iterators)
			code << "HashPosition " << *iter << ";\n";


		// debug_argument_stack();

		// TODO: the same variable may be used twice in the signature. This leads to a memory leak.
		Formal_parameter_list* parameters = signature->formal_parameters;
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

			int index = 0;
			foreach (Formal_parameter* param, *parameters)
			{
//				code << "printf(\"refcount = %d, is_ref = %d\\n\", params[" << index << "]->refcount, params[" << index << "]->is_ref);\n";
				code << "// param " << index << "\n";

				// if a default value is available, then create code to
				// assign it if an argument is not provided at run time.
				// We model it as an assignment to the named variable,
				// and call on the code generator to generate the
				// default assignment for us.
				if (param->var->default_value)
				{
					code 
					<< "if (num_args <= " << index << ")\n"
					<< "{\n";

					// An assignment to default values doesnt fit in the IR. They
					// would need to be lowered first. The simplest option is to
					// convert them to AST, run them through the passes, and
					// generate code for that */
					phc_unsupported (param->var->default_value, "default values");

/*					Statement* assign_default_values = 
						new Assign_var(
							param->var->variable_name->clone (),
							false, 
							param->var->default_value->clone ());

					gen->children_statement (assign_default_values);
*/					code << "} else {\n";
				}

				code
				<< "params[" << index << "]->refcount++;\n";

				// TODO this should be abstactable, but it work now, so
				// leave it.
				if (param->var->variable_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
				{
					string name = get_non_st_name (param->var->variable_name);
					code 
					<< name << " = params[" << index << "];\n";
				}
				else
				{
					// TODO i dont believe theres a test for this
					code 
					<< "zend_hash_quick_add(EG(active_symbol_table), "
					<<		"\"" << *param->var->variable_name->value << "\", " 
					<<		param->var->variable_name->value->length() + 1 << ", "
					<<		get_hash (param->var->variable_name) << ", "
					<<		"&params[" << index << "], "
					<<		"sizeof(zval*), NULL);\n"
					;
				}

				if (param->var->default_value)
					code << "}\n";

				index++;
			}
				
			code << "}\n";

		}
		
		code << "// Function body\n";
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

		// Cleanup local variables
		String_list* var_names = dyc<String_list> (pattern->value->attrs->get ("phc.codegen.non_st_vars"));
		assert (var_names);
		foreach (String* var_name, *var_names)
		{
			string name = get_non_st_name (var_name);
			code
			<< "if (" << name << " != NULL)\n"
			<< "{\n"
			<<		"zval_ptr_dtor (&" << name << ");\n"
			<< "}\n"
			;
		}

		code << "}\n";
	}
};

/*
 * Expressions
 */

/*
 * Assignment is a "virtual" pattern. It deals with the LHS of the assignment,
 * but not with the RHS. Various other classes inherit from Assignment, and
 * deal with the different forms the RHS can take.
 */
class Pattern_assign_var : public Pattern
{
public:
	virtual Expr* rhs_pattern() = 0;
	virtual ~Pattern_assign_var() {}

public:
	bool match(Statement* that)
	{
		lhs = new Wildcard<VARIABLE_NAME>;
		agn = new Assign_var (lhs, /* ignored */ false, rhs_pattern ());
		return (that->match (agn));
	}

protected:
	Assign_var* agn;
	Wildcard<VARIABLE_NAME>* lhs;
};

/*
 * $x = $y; (1)
 *		or
 *	$x =& $y; (2)
 *
 *	Semantics (same as $x[$i] = $y, except with sym-table insted of hash-table):
 *	(1) If $x is a reference, copy the value of $y into the zval at $x.
 *	       If $y doesn't exist, copy from uninitialized_zval.
 *	    If $x is not a reference, overwrite the ST entry with $y, removing the old entry.
 *	       If $y doesn't exist, put in uninitialized_zval.
 *			 If $x doesnt exist, put uninitiliazed_val in, then replace it
 *			 with $y (saved a second hashing operation).
 *	(2) Remove the current ST entry, replacing it with a reference to $y.
 *	    If $y doesnt exist, initialize it. If $x doesn't exist, it doesnt matter.
 */
class Pattern_assign_expr_var : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<VARIABLE_NAME>;
		return rhs;
	}

	void generate_code (Generate_C* gen)
	{
		// TODO combine with assign_expr_var_var
		// and assign_expr_array_access
		if (!agn->is_ref)
		{
			code
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< read_rvalue (LOCAL, "rhs", rhs->value)
			<< "if (*p_lhs != rhs)\n"
			<<		"write_var (p_lhs, rhs);\n"
			;
		}
		else
		{
			code
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< get_st_entry (LOCAL, "p_rhs", rhs->value)
			<< "copy_into_ref (p_lhs, p_rhs);\n"
			;
		}
	}

protected:
	Wildcard<VARIABLE_NAME>* rhs;
};

/* $x = $$y;
 *		or
 *	$x =& $$y;
 *
 * Semantics:
 *		The same as $x = $z; except $z is named at run-time by $y.
 *		Additionally, there is a conversion to strings needed:
 *			TODO
 */
class Pattern_assign_expr_var_var : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<Variable_variable>;
		return rhs;
	}

	void generate_code (Generate_C* gen)
	{
		if (!agn->is_ref)
		{
			code
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< "zval** p_rhs;\n"
			<< read_var_var (LOCAL, "p_rhs", rhs->value->variable_name)
			<< "if (*p_lhs != *p_rhs)\n"
			<<		"write_var (p_lhs, *p_rhs);\n"
			;
		}
		else
		{
			code
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< "zval** p_rhs;\n"
			<< get_var_var (LOCAL, "p_rhs", LOCAL, rhs->value->variable_name)
			<< "copy_into_ref (p_lhs, p_rhs);\n"
			;
		}
	}

protected:
	Wildcard<Variable_variable>* rhs;
};


class Pattern_assign_expr_array_access : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<Array_access>;
		return rhs;
	}

	void generate_code (Generate_C* gen)
	{
		VARIABLE_NAME* var_name  = rhs->value->variable_name;

		if (!agn->is_ref)
		{
			code
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< "zval* rhs;\n"
			<< "int is_p_rhs_new = 0;\n"

			<<	read_rvalue (LOCAL, "r_array", var_name)
			<<	read_rvalue (LOCAL, "ra_index", rhs->value->index)

			<< "if (Z_TYPE_P (r_array) != IS_ARRAY)\n"
			<< "{\n"
			<< "	if (Z_TYPE_P (r_array) == IS_STRING)\n"
			<< "	{\n"
			<< "		is_p_rhs_new = 1;\n"
			<< "		rhs = read_string_index (r_array, ra_index TSRMLS_CC);\n"
			<< "	}\n"
			<< "  else\n"
			// TODO: warning here?
			<< "		rhs = EG (uninitialized_zval_ptr);\n"
			<< "}\n"
			<< "else\n"
			<< "{\n"

			<<		"// Read array variable\n"
			<<		"read_array ("
			<<			"&rhs" << ", "
			<<			"r_array, "
			<<			"ra_index "
			<<			" TSRMLS_CC);\n"
			<< "}\n"

			<< "if (*p_lhs != rhs)\n"
			<<		"write_var (p_lhs, rhs);\n"

			<< "if (is_p_rhs_new) zval_ptr_dtor (&rhs);\n";
		}
		else
		{
			code 
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< get_array_entry (LOCAL, "p_rhs", rhs->value->variable_name, rhs->value->index)
			<< "copy_into_ref (p_lhs, p_rhs);\n"
			;
		}
	}

protected:
	Wildcard<Array_access>* rhs;
};

// A small tweak on $T = $x;
class Pattern_assign_expr_cast : public Pattern_assign_expr_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<VARIABLE_NAME>;
		cast = new Wildcard<CAST>;
		return new Cast (cast, rhs);
	}

	void generate_code (Generate_C* gen)
	{
		assert (!agn->is_ref);
		Pattern_assign_expr_var::generate_code (gen);

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
};

class Pattern_assign_expr_constant : public Pattern_assign_var
{
public:

	Expr* rhs_pattern()
	{
		rhs = new Wildcard<Constant> ();
		return rhs;
	}

	void generate_code (Generate_C* gen)
	{
		assert (!agn->is_ref);

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
		<< get_st_entry (LOCAL, "p_lhs", lhs->value)
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
		<< "}\n"
		;
	}

protected:
	Wildcard<Constant>* rhs;
};

class Pattern_assign_expr_bin_op : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		left = new Wildcard<Rvalue>;
		op = new Wildcard<OP>;
		right = new Wildcard<Rvalue>;

		return new Bin_op (left, op, right); 
	}

	void generate_code (Generate_C* gen)
	{
		assert (lhs);
		assert (op_functions.has (*op->value->value));

		string op_fn = op_functions[*op->value->value]; 

		code
		<< get_st_entry (LOCAL, "p_lhs", lhs->value)
		<< read_rvalue (LOCAL, "left", left->value)
		<< read_rvalue (LOCAL, "right", right->value)

		<< "if (in_copy_on_write (*p_lhs))\n"
		<< "{\n"
		<< "	zval_ptr_dtor (p_lhs);\n"
		<< "	ALLOC_INIT_ZVAL (*p_lhs);\n"
		<< "}\n"
		<< "zval old = **p_lhs;\n"
		<< "int result_is_operand = (*p_lhs == left || *p_lhs == right);\n"
		;

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
	Wildcard<Rvalue>* left;
	Wildcard<OP>* op;
	Wildcard<Rvalue>* right;
};

class Pattern_assign_expr_unary_op : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		op = new Wildcard<OP>;
		var_name = new Wildcard<VARIABLE_NAME>;

		return new Unary_op(op, var_name);
	}

	void generate_code (Generate_C* gen)
	{
		assert (op_functions.has (*op->value->value));

		string op_fn = op_functions[*op->value->value]; 

		code
		<< get_st_entry (LOCAL, "p_lhs", lhs->value)
		<< read_rvalue (LOCAL, "expr", var_name->value)

		<< "if (in_copy_on_write (*p_lhs))\n"
		<< "{\n"
		<< "	zval_ptr_dtor (p_lhs);\n"
		<< "	ALLOC_INIT_ZVAL (*p_lhs);\n"
		<< "}\n"
		<< "zval old = **p_lhs;\n"
		<< "int result_is_operand = (*p_lhs == expr)\n;"

		<< op_fn << "(*p_lhs, expr TSRMLS_CC);\n"

		<< "if (!result_is_operand)\n"
		<<		"zval_dtor (&old);\n"
		;

	}

protected:
	Wildcard<OP>* op;
	Wildcard<VARIABLE_NAME>* var_name;
};



/*
 * Assign_value is a specialization of Assign_var for assignments to a simple
 * zval which takes care of creating a new zval for the LHS.
 *
 * Assign_literal is a further specialization for those literal assignment
 * where the value of the literal is known at compile time (assigning a token
 * int, for example). The main difference between Assign_literal and 
 * Assign_zval is that Assign_literal can do constant pooling.
 */

class Pattern_assign_value : public Pattern_assign_var
{
public:
	void generate_code (Generate_C* gen)
	{
		code
		<< get_st_entry (LOCAL, "p_lhs", lhs->value)
		<< "if ((*p_lhs)->is_ref)\n"
		<< "{\n"
		<< "  // Always overwrite the current value\n"
		<< "  zval* value = *p_lhs;\n"
		<< "  zval_dtor (value);\n";

		initialize (code, "value");

		code
		<< "}\n"
		<< "else\n"
		<< "{\n"
		<<	"	zval* value;\n"
		<<	"	ALLOC_INIT_ZVAL (value);\n";

		initialize (code, "value");

		code
		<<	"	zval_ptr_dtor (p_lhs);\n"
		<<	"	*p_lhs = value;\n"
		<< "}\n";
	}

	virtual void initialize (ostream& os, string var) = 0;
};

string
write_literal_value_directly_into_zval (string var, Literal* lit)
{
	stringstream ss;
	if (INT* value = dynamic_cast<INT*> (lit))
	{
		ss << "ZVAL_LONG (" << var << ", " << value->value << ");\n";
	}
	else if (REAL* value = dynamic_cast<REAL*> (lit))
	{
		ss
		<< "{\n"
		<< "	unsigned char val[] = {\n"
		;

		// Construct the value a byte at a time from our representation in memory.
		unsigned char* values_bytes = (unsigned char*)(&value->value);
		for (unsigned int i = 0; i < sizeof (double); i++)
		{
			ss << (unsigned int)(values_bytes[i]) << ", ";
		}
		ss
		<< "};\n"
		<< "ZVAL_DOUBLE (" << var << ", *(double*)(val));\n"
		<< "}\n"
		;
	}
	else if (STRING* value = dynamic_cast<STRING*> (lit))
	{
		ss
		<< "ZVAL_STRINGL(" << var << ", " 
		<<		"\"" << *escape_C_dq (value->value) << "\", "
		<<		value->value->length() << ", 1);\n";
	}
	else if (NIL* value = dynamic_cast<NIL*> (lit))
	{
		ss << "ZVAL_NULL (" << var << ");\n";
	}
	else if (BOOL* value = dynamic_cast<BOOL*> (lit))
	{
		ss
		<< "ZVAL_BOOL (" << var << ", " 
		<<		(value->value ? 1 : 0) << ");\n"
		;
	}

	return ss.str();
}

class Pattern_assign_literal : public Pattern_assign_value
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<Literal>;
		return rhs;
	}

	// record if we've seen this variable before
	void generate_code (Generate_C* gen)
	{
		assert (!agn->is_ref);
		if (args_info->optimize_given)
		{
			code
			<< read_literal (LOCAL, "rhs", rhs->value)
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< "if (*p_lhs != rhs)\n"
			<<		"write_var (p_lhs, rhs);\n"
			;
		}
		else
		{
			Pattern_assign_value::generate_code (gen);
		}
	}

	void initialize (ostream& os, string var)
	{
		os << write_literal_value_directly_into_zval (var, rhs->value);
	}

public:
	Wildcard<Literal>* rhs;
};



string
read_literal (Scope scope, string zvp, Literal* lit)
{
	stringstream ss;
	if (args_info->optimize_given)
	{
		ss 
		<< "zval* " << zvp << " = "
		<<	*lit->attrs->get_string ("phc.codegen.pool_name")
		<< ";\n";
	}
	else
	{
		ss
		<< "zval " << zvp << "_lit_tmp;\n"
		<< "INIT_ZVAL (" << zvp << "_lit_tmp);\n"
		<< "zval* " << zvp << " = &" << zvp << "_lit_tmp;\n"
		<< write_literal_value_directly_into_zval (zvp, lit)
		;
	}
	return ss.str();
}

// Isset uses Pattern_assign_value, as it only has a boolean value. It puts the
// BOOL into the ready made zval.
class Pattern_assign_expr_isset : public Pattern_assign_value
{
	Expr* rhs_pattern()
	{
		isset = new Wildcard<Isset>;
		return isset;
	}

	void initialize(ostream& code, string lhs)
	{
		VARIABLE_NAME* var_name = dynamic_cast<VARIABLE_NAME*> (isset->value->variable_name);

		if (var_name)
		{
			if (isset->value->array_indices->size() == 0)
			{
				if (var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
				{
					string name = get_non_st_name (var_name);
					code 
					<< "ZVAL_BOOL(" << lhs << ", " 
					<< name << " != NULL && !ZVAL_IS_NULL(" << name << "));\n"; 
				}
				else
				{
					code
					<< read_rvalue (LOCAL, "rhs", var_name)
					<< "ZVAL_BOOL(" << lhs << ", !ZVAL_IS_NULL (rhs));\n" 
					;
				}
			}
			else 
			{
				// TODO this can have > 1 array_index
				assert(isset->value->array_indices->size() == 1);
				Rvalue* index = isset->value->array_indices->front();

	        code
				<< get_st_entry (LOCAL, "u_array", var_name)
				<< read_rvalue (LOCAL, "u_index", index)
				<< "ZVAL_BOOL(" << lhs << ", "
				<< "isset_array ("
				<<    "u_array, "
				<<    "u_index));\n"
				;
			}
		}
		else
		{
			// Variable variable
			// TODO
			Variable_variable* var_var;
			var_var = dynamic_cast<Variable_variable*>(isset->value->variable_name);
			assert(var_var);

			code
			<< "zval** p_rhs;\n"
			<< read_var_var (LOCAL, "p_rhs", var_var->variable_name)
			<< "ZVAL_BOOL(" << lhs << ", !ZVAL_IS_NULL(*p_rhs));\n" 
			;
		}
	}

protected:
	Wildcard<Isset>* isset;
};

// Like ISSET, this just returns a BOOL into a waiting zval.
class Pattern_assign_expr_foreach_has_key : public Pattern_assign_value
{

	Expr* rhs_pattern()
	{
		has_key = new Wildcard<Foreach_has_key>;
		return has_key;
	}

	void initialize (ostream& os, string var)
	{
		os
		<< read_rvalue (LOCAL, "fe_array", has_key->value->array)
		
		<< "int type = zend_hash_get_current_key_type_ex ("
		<<							"fe_array->value.ht, "
		<<							"&" << *has_key->value->iter->value << ");\n"
		<< "ZVAL_BOOL(" << var << ", type != HASH_KEY_NON_EXISTANT);\n";
	}

protected:
	Wildcard<Foreach_has_key>* has_key;
};

// Like ISSET, this just returns an INT or STRING into a waiting zval.
class Pattern_assign_expr_foreach_get_key : public Pattern_assign_value
{
	Expr* rhs_pattern()
	{
		get_key = new Wildcard<Foreach_get_key>;
		return get_key;
	}

	void initialize (ostream& os, string var)
	{
		os
		<< read_rvalue (LOCAL, "fe_array", get_key->value->array)
		<< "char* str_index = NULL;\n"
		<< "uint str_length;\n"
		<< "ulong num_index;\n"
		<< "int result = zend_hash_get_current_key_ex (\n"
		<<						"fe_array->value.ht,"
		<<						"&str_index, &str_length, &num_index, "
		<<						"0, "
		<<						"&" << *get_key->value->iter->value << ");\n"
		<< "if (result == HASH_KEY_IS_LONG)\n"
		<< "{\n"
		<<		"ZVAL_LONG (" << var << ", num_index);\n"
		<< "}\n"
		<< "else\n"
		<< "{\n"
		<<		"ZVAL_STRINGL (" << var << ", str_index, str_length - 1, 1);\n"
		<< "}\n";
	}

protected:
	Wildcard<Foreach_get_key>* get_key;
};

class Pattern_assign_expr_foreach_get_val : public Pattern_assign_var
{
	Expr* rhs_pattern()
	{
		get_val = new Wildcard<Foreach_get_val>;
		return get_val;
	}

	void generate_code (Generate_C* gen)
	{
		code
		<< get_st_entry (LOCAL, "p_lhs", lhs->value)
		<< read_rvalue (LOCAL, "fe_array", get_val->value->array)

		<< "zval** p_rhs = NULL;\n"
		<< "int result = zend_hash_get_current_data_ex (\n"
		<<							"fe_array->value.ht, "
		<<							"(void**)(&p_rhs), "
		<<							"&" << *get_val->value->iter->value << ");\n"
		<< "assert (result == SUCCESS);\n"
		;

		if (!agn->is_ref)
			code << "write_var (p_lhs, *p_rhs);\n";
		else
			code << "copy_into_ref (p_lhs, p_rhs);\n";
	}

protected:
	Wildcard<Foreach_get_val>* get_val;
};




/* A number of patterns can be n the form of either Eval_expr
 * (Method_invocation) or Assign_var (_, _, Method_invocation). Abstract this
 * to avoid duplication. */
class Pattern_eval_expr_or_assign_var : public Pattern_assign_var
{
public:
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
};

class Pattern_expr_builtin : public Pattern_eval_expr_or_assign_var
{
public:
	bool match(Statement* that)
	{
		bool result = Pattern_eval_expr_or_assign_var::match (that);
		if (not result)
			return false;

		string& name = *method_name->value->value;
		return
			// TODO are there more?
				name == "eval"
			|| name == "exit"
			|| name == "die"
			|| name == "print"
			|| name == "echo"
			|| name == "include"
			|| name == "include_once"
			|| name == "require"
			|| name == "require_once"
			|| name == "empty";
	}

	Expr* rhs_pattern()
	{
		method_name = new Wildcard<METHOD_NAME>;
		arg = new Wildcard<Actual_parameter>;
		return new Method_invocation(
			NULL,
			method_name,
			new List<Actual_parameter*>(arg));
	}

	void generate_code (Generate_C* gen)
	{
		code
		<< read_rvalue (LOCAL, "p_arg", arg->value->rvalue);

		// TODO add extra param for include.

		if (lhs)
		{
			assert (!agn->is_ref);

			// create a result
			code
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< "zval* rhs;\n"
			<< "ALLOC_INIT_ZVAL (rhs);\n"
			<< "phc_builtin_" << *method_name->value->value << " (p_arg, rhs, \"" 
				<< *arg->value->get_filename() << "\" TSRMLS_CC);\n"

			<< "write_var (p_lhs, rhs);\n"
			<< "zval_ptr_dtor (&rhs);\n";
		}
		else
			code
			<< "phc_builtin_" << *method_name->value->value << " (p_arg, NULL, \""
				<< *arg->value->get_filename() << "\" TSRMLS_CC);\n";
	}

protected:
	Wildcard<METHOD_NAME>* method_name;
	Wildcard<Actual_parameter>* arg;
};

void
init_function_record (string name, Node* node)
{
	static Set<string> record;

	string fci_name = suffix (name, "fci");
	string fcic_name = suffix (name, "fcic");

	// initialize and declare the first time only
	if (!record.has (name))
	{
		record.insert (name);

		prologue
		<< "static zend_fcall_info " << fci_name << ";\n"
		<< "static zend_fcall_info_cache " << fcic_name << " = {0,NULL,NULL,NULL};\n"
		;
	}

	// Its not necessarily a good idea to initialize at the start, since we
	// still have to check if its initialized at call-time (it may have been
	// created in the meantime.
	code
	<< "initialize_function_call (" 
	<<			"&" << fci_name << ", "
	<<			"&" << fcic_name << ", "
	<<			"\"" << name << "\", "
	<<			"\"" << *node->get_filename () << "\", " 
	<<			node->get_line_number ()
	<<			" TSRMLS_CC);\n"
	;
}

class Pattern_assign_expr_param_is_ref : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<Param_is_ref>;
		return rhs;
	}

	void generate_code (Generate_C* gen)
	{
		assert (!agn->is_ref);

		string name = *dyc<METHOD_NAME> (rhs->value->method_name)->value;
		int index = rhs->value->param_index->value;

		init_function_record (name, rhs->value);

		string fci_name = suffix (name, "fci");
		string fcic_name = suffix (name, "fcic");

		code
		<< "zend_function* signature = " << fcic_name << ".function_handler;\n"
		<< "zend_arg_info* arg_info = signature->common.arg_info;\n"
		<< "int count = 0;\n"
		<< "while (arg_info && count < " << index << ")\n"
		<< "{\n"
		<<		"count++;\n"
		<<		"arg_info++;\n"
		<< "}\n"

		// TODO this could be locally allocated
		<< get_st_entry (LOCAL, "p_lhs", lhs->value)
		<< "zval* rhs;\n"
		<< "ALLOC_INIT_ZVAL (rhs);\n"
		<< "if (count == " << index << ")\n"
		<< "{\n"
		<<		"ZVAL_BOOL (rhs, arg_info->pass_by_reference);\n"
		<< "}\n"
		<< "else\n"
		<< "{\n"
		<<		"ZVAL_BOOL (rhs, signature->common.pass_rest_by_reference);\n"
		<< "}\n"
		<<	"write_var (p_lhs, rhs);\n"
		<< "zval_ptr_dtor (&rhs);\n"
		;

	}

protected:
	Wildcard<Param_is_ref>* rhs;
};



class Pattern_expr_method_invocation : public Pattern_eval_expr_or_assign_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<Method_invocation>;
		return rhs;
	}

	void generate_code (Generate_C* gen)
	{
		Actual_parameter_list::const_iterator i;
		unsigned index;
		
		// code << "debug_hash(EG(active_symbol_table));\n";

		// Variable function or ordinary function?
		METHOD_NAME* name = dynamic_cast<METHOD_NAME*>(rhs->value->method_name);
		if (name == NULL) phc_unsupported (rhs->value, "variable function");

		string fci_name = suffix (*name->value, "fci");
		string fcic_name = suffix (*name->value, "fcic");
		init_function_record (*name->value, rhs->value);

		code
		<< "zend_function* signature = " << fcic_name << ".function_handler;\n"
		;

		// Figure out which parameters need to be passed by reference
		int num_args = rhs->value->actual_parameters->size();
		if (num_args)
		{
			code
			<< "zend_arg_info* arg_info = signature->common.arg_info;\n"
			<< "int by_ref[" << num_args << "];\n"
			;
		}

		// TODO: Not 100% this is fully correct; in particular, 
		// pass_rest_by_reference does not seem to work.
		index = 0;
		foreach (Actual_parameter* param, *rhs->value->actual_parameters)
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
			
			if(param->is_ref) code << "by_ref[" << index << "] = 1;\n";
			
			// code << "printf(\"by reference: %d\\n\", by_ref[" << index << "]);\n";
			index++;
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

		index = 0;
		foreach (Actual_parameter* param, *rhs->value->actual_parameters)
		{
			VARIABLE_NAME* var_name = dyc<VARIABLE_NAME>(param->rvalue);

			code
			<< "destruct[" << index << "] = 0;\n"
			<< "if (by_ref [" << index << "])\n"
			<< "{\n"

			<< get_st_entry (LOCAL, "p_arg", var_name)

			<< "	args_ind[" << index << "] = fetch_var_arg_by_ref ("
			<<				"p_arg);\n"
			<< "	assert (!in_copy_on_write (*args_ind[" << index << "]));\n"
			<<	"  args[" << index << "] = *args_ind[" << index << "];\n"
			<< "}\n"
			<< "else\n"
			<< "{\n"

			<< read_rvalue (LOCAL, "arg", var_name)

			<< "  args[" << index << "] = fetch_var_arg ("
			<<				"arg, "
			<<				"&destruct[" << index << "]);\n"
			<< " args_ind[" << index << "] = &args[" << index << "];\n"
			<< "}\n"
			;

			index++;
		}

		code
		<< "phc_setup_error (1, \""
		<<				*rhs->get_filename () << "\", " 
		<<				rhs->get_line_number () << ", "
		<< "			NULL TSRMLS_CC);\n"

		// save existing paramters, in case of recursion
		<< "int param_count_save = " << fci_name << ".param_count;\n"
		<< "zval*** params_save = " << fci_name << ".params;\n"
		<< "zval** retval_save = " << fci_name << ".retval_ptr_ptr;\n"

		<< "zval* rhs = NULL;\n"

		// set up params
		<< fci_name << ".params = args_ind;\n"
		<< fci_name << ".param_count = " << num_args << ";\n"
		<< fci_name << ".retval_ptr_ptr = &rhs;\n"

		// call the function
		<< "int success = zend_call_function (&" << fci_name << ", &" << fcic_name << " TSRMLS_CC);\n"
		<< "assert(success == SUCCESS);\n"

		// restore params
		<< fci_name << ".params = params_save;\n"
		<< fci_name << ".param_count = param_count_save;\n"
		<< fci_name << ".retval_ptr_ptr = retval_save;\n"

		// unset the errors
		<< "phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);\n"
		;

		for (index = 0; index < rhs->value->actual_parameters->size (); index++)
		{
			// TODO put the for loop into generated code
			code 
			<< "if (destruct[" << index << "])\n"
			<< "{\n"
			<< "	assert (destruct[" << index << "] == 1);\n"
			<< "	zval_ptr_dtor (args_ind[" << index << "]);\n"
			<< "}\n"
			;
		}

		// When the Zend engine returns by reference, it allocates a zval into
		// retval_ptr_ptr. To return by reference, the callee writes
		// into the retval_ptr_ptr, freeing the allocated value as it does.
		// (Note, it may not actually return anything). So the zval returned -
		// whether we return it, or it is the allocated zval - has a refcount
		// of 1.
		// The caller is responsible for cleaning that up (note, this is
		// unaffected by whether it is added to some COW set).

		// For reasons unknown, the Zend API resets the
		// refcount and is_ref fields of the return value after the
		// function returns (unless the callee is interpreted). If the function
		// is supposed to return by reference, this loses the refcount. There
		// is nothing we can do in this situation (apart from rewriting the
		// calling convention, but even that will only work for code we call
		// ourselves).

		// Increment the refcount and set is_ref, to make it clear it cannot go
		// in a copy-on-write set.
		code
		<< "if(signature->common.return_reference && signature->type != ZEND_USER_FUNCTION)\n"
		<< "{\n"
		<< "	assert (rhs != EG(uninitialized_zval_ptr));\n"
		<< "	rhs->is_ref = 1;\n"
		<< "	rhs->refcount++;\n"
		<< "}\n"
		;

		if (lhs)
		{
			code << get_st_entry (LOCAL, "p_lhs", lhs->value);

			if (!agn->is_ref)
				code << "write_var (p_lhs, rhs);\n";
			else
				code << "copy_into_ref (p_lhs, &rhs);\n";
		}

		// p_rhs should be completely destroyed: both the reference we add for
		// references, and the reference from the callee.
		code 
		<< "zval_ptr_dtor (&rhs);\n"
		<< "if(signature->common.return_reference && signature->type != ZEND_USER_FUNCTION)\n"
		<< "	zval_ptr_dtor (&rhs);\n"
		;
	}

protected:
	Wildcard<Method_invocation>* rhs;
};


/*
 * Statements
 */

/* $x[$i] = $y; (1)
 *		or
 * $x[$i] =& $y; (2)
 *
 * Semantics:
 *	(1) If $x[$i] is a reference, copy the value of $y into the zval at $x[$i].
 *	       If $y doesn't exist, we can copy from uninitialized_zval.
 *	    If $x[$i] is not a reference, overwrite the HT entry with $y, removing the old entry.
 *	       If $y doesn't exist, put in uninitialized_zval.
 *			 If $x[$i] doesnt exist, put uninitiliazed_val in, then replace it
 *			 with $y (saved a second hashing operation).
 *
 *	(2) Remove the current HT entry, replacing it with a reference to $y.
 *	    If $y doesnt exist, initialize it. If $x[$i] doesn't exist, it doesnt matter.
 */
class Pattern_assign_array : public Pattern
{
public:
	bool match(Statement* that)
	{
		lhs = new Wildcard<VARIABLE_NAME>;
		index = new Wildcard<Rvalue>;
		rhs = new Wildcard<Rvalue>;
		agn = new Assign_array (lhs, index, false, rhs);
		return (that->match(agn));
	}

	void generate_code(Generate_C* gen)
	{
		assert (lhs->value);
		assert (index->value);
		assert (rhs->value);

		code 
		<<	get_array_entry (LOCAL, "p_lhs", lhs->value, index->value)
		;
	
		if (not agn->is_ref)
		{
		  code	
		  << read_rvalue (LOCAL, "rhs", rhs->value)
		  << "\n"
		  << "if (*p_lhs != rhs)\n"
		  <<		"write_var (p_lhs, rhs);\n"
		  ;
		}
		else
		{
			code
			<< get_st_entry (LOCAL, "p_rhs", dyc<VARIABLE_NAME> (rhs->value))
			<< "copy_into_ref (p_lhs, p_rhs);\n"
			;
		}
	}

protected:
	Assign_array* agn;
	Wildcard<VARIABLE_NAME>* lhs;
	Wildcard<Rvalue>* index;
	Wildcard<Rvalue>* rhs;
};

/*
 * $x[] = $y; (1)
 *		or
 * $x[] =& $y; (2)
 *
 * Semantics:
 * (1) Copy $y in to $x (even if $y is a reference, we copy)
 * (2) Place a reference to $y into $x.
 * In both cases $x may not be initialized, or may not be an array.
 * If $x is uninitiliazed, it becomes an array, and the value is pushed.
 * If $x is false, or "" (but not 0), it is initialized (no warning).
 * If $x is a different scalar, a warning is printed, but that $x is not initialized (nothing pushed).
 * If $x is a string (but not ""), a fatal error is thrown.
 */
class Pattern_assign_next : public Pattern
{
public:
	bool match(Statement* that)
	{
		lhs = new Wildcard<VARIABLE_NAME>;
		rhs = new Wildcard<Rvalue>;
		agn = new Assign_next (lhs, false, rhs);
		return (that->match(agn));
	}

	void generate_code(Generate_C* gen)
	{
		assert (lhs->value);
		assert (rhs->value);

		code 
		<<	"zval** p_lhs;\n"

		<< get_st_entry (LOCAL, "p_lhs_var", lhs->value)

		<<	"// Array push \n"
		<<	"p_lhs = push_and_index_ht (p_lhs_var TSRMLS_CC);\n"
	
		// TODO this can return NULL if there is an error.
		<<	"if (p_lhs != NULL)\n"
		<<	"{\n";

		if (!agn->is_ref)
		{
			code
			<< read_rvalue (LOCAL, "rhs", rhs->value)
			
			<< "if (*p_lhs != rhs)\n"
			<<	"	write_var (p_lhs, rhs);\n"
			;
		}
		else
		{
			// TODO this is wrong
			code	
			<< get_st_entry (LOCAL, "p_rhs", dyc<VARIABLE_NAME> (rhs->value))
			<< "copy_into_ref (p_lhs, p_rhs);\n"
			;
		}

		code << "}\n"
		;
	}

protected:
	Assign_next* agn;
	Wildcard<VARIABLE_NAME>* lhs;
	Wildcard<Rvalue>* rhs;
};

/*
 * $$x = $y
 */

class Pattern_assign_var_var : public Pattern
{
	bool match(Statement* that)
	{
		lhs = new Wildcard<VARIABLE_NAME>;
		rhs = new Wildcard<Rvalue>;
		stmt = new Assign_var_var(lhs, false, rhs);
		return(that->match(stmt));	
	}

	void generate_code(Generate_C* gen)
	{
		if(!stmt->is_ref)
		{
			code
			<< "zval** p_lhs;\n"
			<< get_var_var (LOCAL, "p_lhs", LOCAL, lhs->value)
			<< read_rvalue (LOCAL, "rhs", rhs->value)
			<< "if (*p_lhs != rhs)\n"
			<<		"write_var (p_lhs, rhs);\n"
			;
		}
		else
		{
			code
			<< "zval** p_lhs;\n"
			<< get_var_var (LOCAL, "p_lhs", LOCAL, lhs->value)
			<< get_st_entry (LOCAL, "p_rhs", dyc<VARIABLE_NAME> (rhs->value))
			<< "copy_into_ref (p_lhs, p_rhs);\n"
			;
		}
	}

	Assign_var_var* stmt;
	Wildcard<VARIABLE_NAME>* lhs;
	Wildcard<Rvalue>* rhs;
};
	
/*
 * global $a or global $$a
 */
class Pattern_global : public Pattern 
{
public:
	bool match(Statement* that)
	{
		var_name = new Wildcard<Variable_name>;
		return(that->match(new Global(var_name)));
	}

	void generate_code(Generate_C* gen)
	{
		code
		<< index_lhs (LOCAL, "p_local_global_var", var_name->value) // lhs
		<< index_lhs (GLOBAL, "p_global_var", var_name->value) // rhs
		// Note that p_global_var can be in a copy-on-write set.
		<< "copy_into_ref (p_local_global_var, p_global_var);\n"
		;
	}

	string index_lhs (Scope scope, string zvp, Expr* expr)
	{
		stringstream ss;
	
		VARIABLE_NAME* var_name = dynamic_cast<VARIABLE_NAME*> (expr);
		if (var_name)
		{
			ss
			<< "// Normal global\n"
			<< get_st_entry (scope, zvp, var_name)
			;
		}
		else
		{
			Variable_variable* var_var;
			var_var = dynamic_cast<Variable_variable*> (expr);
			assert(var_var != NULL);

		  ss
		  << "// Variable global\n"
		  << "zval** " << zvp << ";\n"
		  // The variable variable is always in the local scope
		  << get_var_var (scope, zvp, LOCAL, var_var->variable_name)
		  ;
    }

  	return ss.str();
  }

protected:
	Wildcard<Variable_name>* var_name;
};


class Pattern_label : public Pattern
{
public:
	bool match(Statement* that)
	{
		use_scope = false;
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
		<<	read_rvalue (LOCAL, "p_cond", cond->value)

		<<	"zend_bool bcond = zend_is_true (p_cond);\n"
		<<	"if (bcond)\n"
		<<	"	goto " << *iftrue->value->value << ";\n"
		<<	"else\n"
		<<	"	goto " << *iffalse->value->value << ";\n"
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

class Pattern_return : public Pattern
{
	bool match(Statement* that)
	{
		rvalue = new Wildcard<Rvalue>;
		return that->match (new Return (rvalue));
	}

	void generate_code(Generate_C* gen)
	{
		if(!gen->return_by_reference)
		{
			code 
			<< read_rvalue (LOCAL, "rhs", rvalue->value)

			// Run-time return by reference had slightly different
			// semantics to compile-time. There is no way within a
			// function to tell if the run-time return by reference is
			// set, but its unnecessary anyway.
			// TODO: I dont believe in run-time return by reference. It seems that
			// it only work in the presence of compile-time return by reference.
			<< "return_value->value = rhs->value;\n"
			<< "return_value->type = rhs->type;\n"
			<< "zval_copy_ctor (return_value);\n"
			;
		}
		else
		{
			code
			<< get_st_entry (LOCAL, "p_rhs", dyc<VARIABLE_NAME> (rvalue->value))
			<< "sep_copy_on_write_ex (p_rhs);\n"
			<< "zval_ptr_dtor (return_value_ptr);\n"
			<< "(*p_rhs)->is_ref = 1;\n"
			<< "(*p_rhs)->refcount++;\n"
			<< "*return_value_ptr = *p_rhs;\n"
			;
		}

		code 
		<< "goto end_of_function;\n"
		;
	}

protected:
	Wildcard<Rvalue>* rvalue;
};

class Pattern_unset : public Pattern
{
	bool match(Statement* that)
	{
		unset = new Wildcard<Unset>;
		return that->match(unset);
	}

	void generate_code(Generate_C* gen)
	{
		VARIABLE_NAME* var_name = dynamic_cast <VARIABLE_NAME*> (unset->value->variable_name);

		if (var_name != NULL)
		{
			if (unset->value->array_indices->size() == 0)
			{
				if (var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
				{
					string name = get_non_st_name (var_name);
					code
					<< "if (" << name << " != NULL)\n"
					<< "{\n"
					<<		"zval_ptr_dtor (&" << name << ");\n"
					<<		name << " = NULL;\n"
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
				assert(unset->value->array_indices->size() == 1);
				Rvalue* index = (unset->value->array_indices->front());
				code
				<< get_st_entry (LOCAL, "u_array", var_name)
				<< read_rvalue (LOCAL, "u_index", index)

				<< "unset_array ("
				<<    "u_array, "
				<<    "u_index "
				<<		" TSRMLS_CC);\n";
			}
		}
		else
		{
			// Variable variable
			phc_unsupported (unset, "unset variable variable");
		}
	}

protected:
	Wildcard<Unset>* unset;
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
		assert (op_functions.has (*op->value->value));

		string op_fn = op_functions[*op->value->value]; 

		code 
		<<	get_st_entry (LOCAL, "p_var", var->value)

		<<	"sep_copy_on_write_ex (p_var);\n"
		<<	op_fn << "(*p_var);\n"
		;
	}

protected:
	Wildcard<VARIABLE_NAME>* var;
	Wildcard<OP>* op;
};


/*
 * Aliases
 */

class Pattern_method_alias : public Pattern
{
	bool match (Statement* that)
	{
		alias = new Wildcard<Method_alias>;
		return that->match (alias);
	}

	void generate_code(Generate_C* gen)
	{
		String alias_name = *alias->value->alias->value->clone();
		alias_name.toLower();
		String method_name = *alias->value->method_name->value->clone();
		method_name.toLower();

		code
		<<	"zend_function* existing;\n"
		<<	"// find the existing function\n"
		<<	"int result = zend_hash_find ("
		<<		"EG (function_table),"
		<<		"\"" << method_name << "\", "
		<<		(method_name.size()+1) << ", "
		<<		"(void**) &existing);\n"
		<<	"assert (result == SUCCESS);\n"
		<<	"// rename it\n"
		<<	"existing->common.function_name = \"" << alias_name << "\";"
		<<	"// add it with the new name\n"
		<<	"result = zend_hash_add ("
		<<		"EG (function_table),"
		<<		"\"" << alias_name << "\", "
		<<		(alias_name.size()+1) << ", "
		<<		"(void**)existing,"
		<<		"sizeof(zend_function),"
		<<		"NULL);\n"
		<<	"assert (result == SUCCESS);\n"
		;
	}

protected:
	Wildcard<Method_alias>* alias;
};

class Pattern_class_or_interface_alias : public Pattern
{
	bool match (Statement* that)
	{
		class_alias = new Wildcard<Class_alias>;
		interface_alias = new Wildcard<Interface_alias>;
		return that->match (class_alias)
			|| that->match (interface_alias);
	}

	void generate_code(Generate_C* gen)
	{
		String* aliased_name;
		String* alias_name;

		if (interface_alias->value)
		{
			aliased_name = interface_alias->value->interface_name->value;
			alias_name = interface_alias->value->alias->value;
		}
		else if (class_alias->value)
		{
			aliased_name = class_alias->value->class_name->value;
			alias_name = class_alias->value->alias->value;
		}
		else
			assert (0);

		alias_name = alias_name->clone ();
		alias_name->toLower();

		aliased_name = aliased_name->clone ();
		aliased_name->toLower();

		code
		<<	"zend_class_entry* existing;\n"
		<<	"// find the existing class_entry\n"
		<<	"int result = zend_hash_find ("
		<<		"EG (class_table),"
		<<		"\"" << *aliased_name << "\", "
		<<		(aliased_name->size()+1) << ", "
		<<		"(void**) &existing);\n"
		<<	"assert (result == SUCCESS);\n"
		<<	"// rename it\n"
		<<	"existing->name = \"" << *alias_name << "\";"
		<<	"// add it with the new name\n"
		<<	"result = zend_hash_add ("
		<<		"EG (class_table),"
		<<		"\"" << *alias_name << "\", "
		<<		(alias_name->size()+1) << ", "
		<<		"(void**)existing,"
		<<		"sizeof(zend_entry),"
		<<		"NULL);\n"
		<<	"assert (result == SUCCESS);\n"
		;
	}

protected:
	Wildcard<Class_alias>* class_alias;
	Wildcard<Interface_alias>* interface_alias;
};




/*
 * Foreach patterns
 */

class Pattern_foreach_reset : public Pattern
{
	bool match (Statement* that)
	{
		use_scope = false;
		reset = new Wildcard<Foreach_reset>;
		return that->match (reset);
	}

	void generate_code(Generate_C* gen)
	{
		// declare the external iterator outside local scope blocks
		code
		<< "{\n"
		<<		read_rvalue (LOCAL, "fe_array", reset->value->array)
		<<		"zend_hash_internal_pointer_reset_ex ("
		<<		"						fe_array->value.ht, "
		<<		"						&" << *reset->value->iter->value << ");\n"
		<< "}\n";
	}

protected:
	Wildcard<Foreach_reset>* reset;
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
		code
		<<	read_rvalue (LOCAL, "fe_array", next->value->array)
		<<	"int result = zend_hash_move_forward_ex ("
		<<						"fe_array->value.ht, "
		<<						"&" << *next->value->iter->value << ");\n"
		<<	"assert (result == SUCCESS);\n"
		;
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
		code
		<<	read_rvalue (LOCAL, "fe_array", end->value->array)
		<<	"zend_hash_internal_pointer_end_ex ("
		<<						"fe_array->value.ht, "
		<<						"&" << *end->value->iter->value << ");\n"
		;
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
	MIR_unparser (ss, true).unparse (in);

	while (not ss.eof ())
	{
	  // Make reading the generated code easier. If we use a /*
	  // comment, then we may get nested /* */ comments, which arent
	  // allowed and result in syntax errors in C. Use // instead.
		string str;
		getline (ss, str);
		if (str == "")
			continue;

		code << "// " << *escape_C_comment (s(str)) << endl;
	}

	Pattern* patterns[] = 
	{
		new Pattern_method_definition()
	// Expressions, which can only be RHSs to Assign_vars
	,	new Pattern_assign_expr_constant ()
	,	new Pattern_assign_expr_var ()
	,	new Pattern_assign_expr_var_var ()
	,	new Pattern_assign_expr_array_access ()
	// TODO: array_next
	,	new Pattern_assign_expr_param_is_ref ()
	,	new Pattern_assign_expr_isset()
	,	new Pattern_assign_expr_bin_op()
	,	new Pattern_assign_expr_unary_op()
	,	new Pattern_assign_expr_cast ()
	,	new Pattern_assign_expr_foreach_has_key ()
	,	new Pattern_assign_expr_foreach_get_key ()
	,	new Pattern_assign_expr_foreach_get_val ()
	// Literals are special, as they constant pool, and can be used as Rvalues
	,	new Pattern_assign_literal ()
	// Method invocations and NEWs can be part of Eval_expr or just Assign_vars
	,	new Pattern_expr_builtin()
	,	new Pattern_expr_method_invocation()
	// All the rest are just statements
	,	new Pattern_assign_array ()
	,	new Pattern_assign_next ()
	,  new Pattern_assign_var_var ()
	,	new Pattern_class_or_interface_alias ()
	,	new Pattern_method_alias ()
	,	new Pattern_branch()
	,	new Pattern_goto()
	,	new Pattern_label()
	,	new Pattern_foreach_end ()
	,	new Pattern_foreach_next ()
	,	new Pattern_foreach_reset ()
	,	new Pattern_global()
	,	new Pattern_return()
	,	new Pattern_unset()
	,	new Pattern_pre_op()
	};

	bool matched = false;
	for(unsigned i = 0; i < sizeof(patterns) / sizeof(Pattern*); i++)
	{
		if(patterns[i]->match(in))
		{
			bool brackets = patterns[i]->use_scope;
			if (brackets)
				code << "{\n";

			patterns[i]->generate_code(this);

			if (brackets)
			{
				code
				<<		"phc_check_invariants (TSRMLS_C);\n"
				<< "}\n";
			}

			matched = true;
			break;
		}
	}

	if(not matched)
	{
		phc_unsupported (in, "unknown construct");
	}
}

void include_file (ostream& out, String* filename)
{
	// For now, we simply include this.
	ifstream file;

	stringstream ss1, ss2;
	ss1 << "runtime/" << *filename;
	ss2 << DATADIR << "/phc/" << *filename;

	// Check the current directory first. This means we can change the file without recompiling or installing.
	file.open (ss1.str ().c_str ());

	// Check the installed directory.
	if (!file.is_open())
		file.open (ss2.str ().c_str ());

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

void Generate_C::pre_php_script(PHP_script* in)
{
	include_file (prologue, s("support_routines.c"));
	include_file (prologue, s("builtin_functions.c"));


	// Add constant-pooling declarations
	if (args_info->optimize_given)
	{
		Literal_list* pooled_literals = rewrap_list <IR::Node, Literal> (dyc<IR::Node_list> (
			in->attrs->get ("phc.codegen.pooled_literals")));

		foreach (Literal* lit, *pooled_literals)
		{
			String* var = lit->attrs->get_string ("phc.codegen.pool_name");
			prologue << "zval* " << *var << ";\n";
			finalizations << "zval_ptr_dtor (&" << *var << ");\n";
			initializations
			<< "ALLOC_INIT_ZVAL (" << *var << ");\n"
			<< write_literal_value_directly_into_zval (*var, lit);
		}
	}

	
	// Add .ini settings
	// We only want to alter the ones given to us at the command-line
	foreach (String* key, *PHP::get_altered_ini_entries ())
	{
		String* value = PHP::get_ini_entry (key);
		initializations
		<< "zend_alter_ini_entry ("
		<< "\"" << *key << "\", "
		<< (key->size () + 1) << ", " // include NULL byte
		<< "\"" << *value << "\", "
		<< value->size () << ", " // don't include NULL byte
		<< "PHP_INI_ALL, PHP_INI_STAGE_RUNTIME);\n"
		;
	}
}

void Generate_C::post_php_script(PHP_script* in)
{
	code << "// ArgInfo structures (necessary to support compile time pass-by-reference)\n";
	foreach (Signature* s, *methods)
	{
		String* name = s->method_name->value;

		// TODO: pass by reference only works for PHP>5.1.0. Do we care?
		code 
		<< "ZEND_BEGIN_ARG_INFO_EX(" << *name << "_arg_info, 0, "
		<< (s->is_ref ? "1" : "0")
		<< ", 0)\n"
		;

		// TODO: deal with type hinting

		foreach (Formal_parameter* fp, *s->formal_parameters)
		{
			code 
			<< "ZEND_ARG_INFO("
			<< (fp->is_ref ? "1" : "0")
			<< ", \"" << *fp->var->variable_name->value << "\")\n"; 
		}

		code << "ZEND_END_ARG_INFO()\n";
	}

	code 
		<< "// Register all functions with PHP\n"
		<< "static function_entry " << *extension_name << "_functions[] = {\n"
		;

	foreach (Signature* s, *methods)
	{
		String* name = s->method_name->value;
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
		code << 
		"#include <sapi/embed/php_embed.h>\n"
		"#include <signal.h>\n"
		"\n"
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
		"}\n"
	
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
		"\n"
		"      // initialize the phc runtime\n"
		"      init_runtime();\n"
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
		"      // initialize all the constants\n"
		<< initializations.str () << // TODO put this in __MAIN__, or else extensions cant use it.
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
		"      // finalize the runtime\n"
		"      finalize_runtime();\n"
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
	methods = new Signature_list;
	name = new String ("generate-c");
	description = new String ("Generate C code from the MIR");
}
