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
#include <boost/format.hpp>

#include "lib/List.h"
#include "lib/Set.h"
#include "lib/Map.h"
#include "lib/escape.h"
#include "lib/demangle.h"
#include "process_ir/General.h"
#include "process_ir/XML_unparser.h"
#include "parsing/LIR_parser.h"

#include "Generate_LIR.h"
#include "process_lir/LIR_unparser.h"
#include "embed/embed.h"

using namespace std;
using namespace boost;

// These probably wont clash.
using namespace MIR;

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
static stringstream initializations;
static stringstream finalizations;

string templ (string);

// TODO this is here for constant pooling. This should not be global.
extern struct gengetopt_args_info args_info;

LIR::PHP_script*
Generate_LIR::fold_php_script (MIR::PHP_script* in)
{
	if (args_info.extension_given)
	{
		extension_name = new String (args_info.extension_arg);
		this->is_extension = true;
	}
	else
	{
		extension_name = new String("app");
		this->is_extension = false;
	}


	in->visit (this);
	return this->lir;
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

string get_scope_lir (Scope scope)
{
	if(scope == LOCAL)
		return "local";
	else
		return "global";
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

string read_literal (string, Literal*);
string read_literal_lir (string, Literal*);

// Declare and fetch a zval* containing the value for RVALUE. The value can be
// changed, but the symbol-table entry cannot be affected through this.
string read_rvalue (string zvp, Rvalue* rvalue)
{
	stringstream ss;
	if (isa<Literal> (rvalue))
	{
		return read_literal (zvp, dyc<Literal> (rvalue));
	}

	VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (rvalue);
	if (var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
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
		<<								get_scope (LOCAL) << ", "
		<<								"\"" << *name << "\", "
		<<								name->size () + 1  << ", "
		<<								get_hash (name) << " TSRMLS_CC);\n"
		;
	}
	return ss.str ();
}

string read_rvalue_lir (string zvp, Rvalue* rvalue)
{
	if (isa<Literal> (rvalue))
		return read_literal_lir (zvp, dyc<Literal> (rvalue));


	VARIABLE_NAME* var_name = dyc<VARIABLE_NAME> (rvalue);
	if (var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
	{
		return str(format (templ ("read_var_no_st"))
			% get_non_st_name (var_name)
			% zvp);
	}
	else
	{
		return str(format (templ ("read_var"))
			% get_scope_lir (LOCAL)
			% *var_name->value
			% zvp);
	}
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

string get_st_entry_lir (Scope scope, string zvp, VARIABLE_NAME* var_name)
{
	if (scope == LOCAL && var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
	{
		return str(format (templ ("get_st_entry_no_st"))
			% get_non_st_name (var_name) 
			% zvp);
	}
	else
	{
		return str(format (templ ("get_st_entry"))
			% get_scope_lir (LOCAL)
			% *var_name->value
			% zvp);
	}
}

// Declare and fetch a zval** into ZVP, which is the hash-table entry for
// VAR_NAME[INDEX]. This zval** can be over-written, which will change the
// hash-table entry.
string get_array_entry (string zvp, VARIABLE_NAME* var_name, Rvalue* index)
{
	stringstream ss;
	string zvp_name = suffix (zvp, "var");
	string zvp_index = suffix (zvp, "index");

	ss	
	// TODO dont need get_st_entry here
	<< get_st_entry (LOCAL, zvp_name, var_name)
	<< read_rvalue (zvp_index, index)
	<< "check_array_type (" << zvp_name << " TSRMLS_CC);\n"
	<<	"zval**" << zvp << " = get_ht_entry ("
	<<						zvp_name << ", "
	<<						zvp_index
	<<						" TSRMLS_CC);\n"
	;

	return ss.str();
}

/* Generate code to read the variable named in VAR to the zval* ZVP */
string read_var (string zvp, VARIABLE_NAME* var_name)
{
	// the same as read_rvalue, but doesnt declare
	stringstream ss;
	string name = suffix (zvp, "var");

	ss
	<< "// Read normal variable\n"
	<< read_rvalue (name, var_name)
	<< zvp << " = &" << name << ";\n"; 

	return ss.str();
}

/*
 * Find the variable in target_scope whose name is given by var_var in var_scope
 * and store the result in zvp
 */
string get_var_var (Scope scope, string zvp, string index)
{
	stringstream ss;
	ss
	<< "// Read variable variable\n"
	<< zvp << " = get_var_var (" 
	<<					get_scope (scope) << ", "
	<<					index << " "
	<<					"TSRMLS_CC);\n"
	;
	return ss.str();
}

/*
 * Like get_var_var, but do not add the variable to the scope
 * if not already there
 */
string read_var_var (string zvp, string index)
{
	stringstream ss;
	ss
	<< "// Read variable variable\n"
	<< zvp << " = read_var_var (" 
	<<					get_scope (LOCAL) << ", "
	<<					index << " "
	<<					" TSRMLS_CC);\n"
	;
	return ss.str();
}

string
write_var_lir (string lhs, string rhs)
{
	return str(format (templ ("write_var")) % lhs % rhs);
}

string
sep_copy_on_write_lir (string zvp)
{
	return str(format (templ ("sep_copy_on_write")) % zvp);
}


string
copy_into_ref_lir (string lhs, string rhs)
{
	return str(format (templ ("copy_into_ref")) % lhs % rhs);
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
	virtual void generate_code(Generate_LIR* gen) {assert (0); };
	virtual ~Pattern() {}
	bool use_scope;

	virtual LIR::Piece* generate_lir (String* comment, Generate_LIR* gen)
	{
		code << *comment;

		if (use_scope)
			code << "{\n";

		generate_code (gen);

		if (use_scope)
		{
			code
			<<		"phc_check_invariants (TSRMLS_C);\n"
			<< "}\n";
		}

		return gen->clear_code_buffer ();
	}
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

	LIR::Piece* generate_lir (String* comment, Generate_LIR* gen)
	{
		gen->lir->pieces->push_back (gen->clear_code_buffer ());
		signature = pattern->value->signature;

		method_entry();
		LIR::UNINTERPRETED* entry = gen->clear_code_buffer ();

		// Use a different gen for the nested function
		Generate_LIR* new_gen = new Generate_LIR ();
		new_gen->visit_statement_list (pattern->value->statements);

		method_exit();
		LIR::UNINTERPRETED* exit = gen->clear_code_buffer ();

		return new LIR::Method
			(new LIR::COMMENT (comment),
			entry,
			new_gen->lir->pieces,
			exit);
	}

protected:
	Wildcard<Method>* pattern;
	Signature* signature;

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
				
				// We can have multiple parameters with the same name. In that
				// case, destroy the predecessor (the second is not deemed to
				// assign to the first, so references etc are moot).
				if (param->var->variable_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
				{
					string name = get_non_st_name (param->var->variable_name);
					code 
					<< "if (" << name << " != NULL)\n"
					<< "{\n"
					<< "	zval_ptr_dtor (&" << name << ");\n"
					<< "}\n"
					<< name << " = params[" << index << "];\n";
				}
				else
				{
					code
					<< "zend_hash_del (EG(active_symbol_table), "
					<<		"\"" << *param->var->variable_name->value << "\", " 
					<<		param->var->variable_name->value->length() + 1 << ");\n"

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

		// See comment in Method_invocation. We save the refcount of
		// return_by_reference. Note that we get the wrong answer if we do this
		// before the destructors have run, since we can't tell how many
		// destructors will affect it.
		if (signature->is_ref)
		{
			code
			<< "if (*return_value_ptr)\n"
			<< "	saved_refcount = (*return_value_ptr)->refcount;\n"
			;
		}

		code << "}\n" ;
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
#define STRAIGHT(STR) stmts->push_back (new LIR::CODE (s (STR)))
#define DSL(STR) stmts->push_back (dyc<LIR::Statement> (parse_lir (s(#STR))))
#define LDSL(STR) do { stringstream ss; ss << STR; stmts->push_back_all (dyc<LIR::Statement_list> (parse_lir (s(ss.str())))); } while (0)
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<VARIABLE_NAME>;
		return rhs;
	}

	LIR::Piece* generate_lir (String* comment, Generate_LIR* gen)
	{
		LIR::Statement_list* stmts = new LIR::Statement_list;

		if (!agn->is_ref)
		{
			LDSL ("["
			<< get_st_entry_lir (LOCAL, "lhs", lhs->value)
			<< read_rvalue_lir ("rhs", rhs->value)
			<< "	(if "
			<<	"		(not (equals "
			<<	"			(deref (ZVPP lhs)) "
			<<	"			(ZVP rhs))) "
			<<	"		[ "
			<<				write_var_lir ("lhs", "rhs")
			<< "		] "
			<<	"		[])"
			<<	"]");
		}
		else
		{
			LDSL ("["
			<< get_st_entry_lir (LOCAL, "lhs", lhs->value)
			<< get_st_entry_lir (LOCAL, "rhs", rhs->value)
			<< sep_copy_on_write_lir ("rhs")
			<< copy_into_ref_lir ("lhs", "rhs")
			<<	"]");
		}

		return new LIR::Block (comment, stmts);
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

	void generate_code (Generate_LIR* gen)
	{
		if (!agn->is_ref)
		{
			code
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< "zval* rhs;\n"
			<< read_rvalue ("index", rhs->value->variable_name)
			<< read_var_var ("rhs", "index")
			<< "if (*p_lhs != rhs)\n"
			<<		"write_var (p_lhs, rhs);\n"
			;
		}
		else
		{
			code
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< "zval** p_rhs;\n"
			<< read_rvalue ("index", rhs->value->variable_name)
			<< get_var_var (LOCAL, "p_rhs", "index")
			<< "sep_copy_on_write (p_rhs);\n"
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

	void generate_code (Generate_LIR* gen)
	{
		VARIABLE_NAME* var_name  = rhs->value->variable_name;

		if (!agn->is_ref)
		{
			code
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< "zval* rhs;\n"
			<< "int is_p_rhs_new = 0;\n"

			<<	read_rvalue ("r_array", var_name)
			<<	read_rvalue ("ra_index", rhs->value->index)

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

			<<		"if (check_array_index_type (ra_index TSRMLS_CC))\n"
			<<		"{\n"

			<<		"// Read array variable\n"
			<<		"read_array ("
			<<			"&rhs" << ", "
			<<			"r_array, "
			<<			"ra_index "
			<<			" TSRMLS_CC);\n"
			<<		"}\n"
			<<		"else rhs = *p_lhs;\n" // HACK to fail  *p_lhs != rhs
			<< "}\n"

			<< "if (*p_lhs != rhs)\n"
			<<		"write_var (p_lhs, rhs);\n"

			<< "if (is_p_rhs_new) zval_ptr_dtor (&rhs);\n";
		}
		else
		{
			code 
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< get_array_entry ("p_rhs", rhs->value->variable_name, rhs->value->index)
			<< "sep_copy_on_write (p_rhs);\n"
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

	LIR::Piece* generate_lir (String* comment, Generate_LIR* gen)
	{
		assert (!agn->is_ref);
		LIR::Statement_list* stmts = new LIR::Statement_list;

		LIR::Block* assign_var = dyc<LIR::Block> (Pattern_assign_expr_var::generate_lir (comment, gen));
		stmts->push_back_all (assign_var->statements);


		if (*cast->value->value == "string")
			STRAIGHT ("cast_var (p_lhs, IS_STRING);\n");
		else if (*cast->value->value == "int")
			STRAIGHT ("cast_var (p_lhs, IS_LONG);\n");
		else if (*cast->value->value == "array")
			STRAIGHT ("cast_var (p_lhs, IS_ARRAY);\n");
		else if (*cast->value->value == "null")
			STRAIGHT ("cast_var (p_lhs, IS_NULL);\n");
		else if (*cast->value->value == "bool" || *cast->value->value == "boolean")
			STRAIGHT ("cast_var (p_lhs, IS_BOOL);\n");
		else if (*cast->value->value == "real")
			STRAIGHT ("cast_var (p_lhs, IS_DOUBLE);\n");
		else
			assert (0 && "unimplemented"); // TODO: unimplemented

		return new LIR::Block (comment, stmts);
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

	void generate_code (Generate_LIR* gen)
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

	void generate_code (Generate_LIR* gen)
	{
		assert (lhs);
		assert (op_functions.has (*op->value->value));

		string op_fn = op_functions[*op->value->value]; 

		code
		<< get_st_entry (LOCAL, "p_lhs", lhs->value)
		<< read_rvalue ("left", left->value)
		<< read_rvalue ("right", right->value)

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

	void generate_code (Generate_LIR* gen)
	{
		assert (op_functions.has (*op->value->value));

		string op_fn = op_functions[*op->value->value]; 

		code
		<< get_st_entry (LOCAL, "p_lhs", lhs->value)
		<< read_rvalue ("expr", var_name->value)

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
	void generate_code (Generate_LIR* gen)
	{
		code
		<< get_st_entry (LOCAL, "p_lhs", lhs->value)
		<< "zval* value;\n"
		<< "if ((*p_lhs)->is_ref)\n"
		<< "{\n"
		<< "  // Always overwrite the current value\n"
		<< "  value = *p_lhs;\n"
		<< "  zval_dtor (value);\n"
		<< "}\n"
		<< "else\n"
		<< "{\n"
		<<	"	ALLOC_INIT_ZVAL (value);\n"
		<<	"	zval_ptr_dtor (p_lhs);\n"
		<<	"	*p_lhs = value;\n"
		<< "}\n"
		;

		initialize (code, "value");
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
	void generate_code (Generate_LIR* gen)
	{
		assert (!agn->is_ref);
		if (args_info.optimize_given)
		{
			code
			<< read_literal ("rhs", rhs->value)
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
read_literal_lir (string zvp, Literal* lit)
{
	assert (0);
	stringstream ss;
	if (args_info.optimize_given)
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

string
read_literal (string zvp, Literal* lit)
{
	stringstream ss;
	if (args_info.optimize_given)
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
					<< read_rvalue ("rhs", var_name)
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
				<< read_rvalue ("u_index", index)
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
			assert(isset->value->array_indices->size() == 0);
			Variable_variable* var_var = dyc<Variable_variable> (isset->value->variable_name);

			code
			<< "zval* rhs;\n"
			<< read_rvalue ("index", var_var->variable_name)
			<< read_var_var ("rhs", "index")
			<< "ZVAL_BOOL(" << lhs << ", !ZVAL_IS_NULL(rhs));\n" 
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
		<< read_rvalue ("fe_array", has_key->value->array)
		
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
		<< read_rvalue ("fe_array", get_key->value->array)
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

	void generate_code (Generate_LIR* gen)
	{
		code
		<< get_st_entry (LOCAL, "p_lhs", lhs->value)
		<< read_rvalue ("fe_array", get_val->value->array)

		<< "zval** p_rhs = NULL;\n"
		<< "int result = zend_hash_get_current_data_ex (\n"
		<<							"fe_array->value.ht, "
		<<							"(void**)(&p_rhs), "
		<<							"&" << *get_val->value->iter->value << ");\n"
		<< "assert (result == SUCCESS);\n"
		;

		if (!agn->is_ref)

			code 
			<< "if (*p_lhs != *p_rhs)\n"
			<< "	write_var (p_lhs, *p_rhs);\n"
			;
		else
		{
			code 
			<< "sep_copy_on_write (p_rhs);\n"
			<< "copy_into_ref (p_lhs, p_rhs);\n";
		}
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

	void generate_code (Generate_LIR* gen)
	{
		code
		<< read_rvalue ("p_arg", arg->value->rvalue)
		<< "zval* rhs = NULL;\n"
		<< "zval** p_rhs = &rhs;\n"
		;

		if (lhs)
		{
			assert (!agn->is_ref);

			// create a result
			code
			<< get_st_entry (LOCAL, "p_lhs", lhs->value)
			<< "ALLOC_INIT_ZVAL (rhs);\n"
			<< "phc_builtin_" << *method_name->value->value << " (p_arg, p_rhs, \"" 
				<< *arg->value->get_filename() << "\" TSRMLS_CC);\n"

			<< "write_var (p_lhs, rhs);\n"
			<< "zval_ptr_dtor (p_rhs);\n";
		}
		else
			code
			<< "phc_builtin_" << *method_name->value->value << " (p_arg, p_rhs, \""
			<< *arg->value->get_filename() << "\" TSRMLS_CC);\n"
			<< "if (rhs != NULL) zval_ptr_dtor (p_rhs);\n"
			;
	}

protected:
	Wildcard<METHOD_NAME>* method_name;
	Wildcard<Actual_parameter>* arg;
};

void
init_function_record (string name, Node* node)
{
	string fci_name = suffix (name, "fci");
	string fcic_name = suffix (name, "fcic");

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

	void generate_code (Generate_LIR* gen)
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

	void generate_code (Generate_LIR* gen)
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

			<< read_rvalue ("arg", var_name)

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
		// is supposed to return by reference, this loses the refcount. This only
		// happens when non-interpreted code is called. We work around it, when
		// compiled code is called, by saving the refcount into SAVED_REFCOUNT,
		// in the return statement. The downside is that we may create an error
		// if our code is called by a callback, and returns by reference, and the
		// callback returns by reference. At least this is an obscure case.

		code
		<< "if(signature->common.return_reference && signature->type != ZEND_USER_FUNCTION)\n"
		<< "{\n"
		<< "	assert (rhs != EG(uninitialized_zval_ptr));\n"
		<< "	rhs->is_ref = 1;\n"
		<< "	if (saved_refcount != 0)\n"
		<< "	{\n"
		<< "		rhs->refcount = saved_refcount;\n"
		<< "	}\n"
		<< "	rhs->refcount++;\n"
		<< "}\n"
		<< "saved_refcount = 0;\n" // for 'obscure cases'
		;

		if (lhs)
		{
			code << get_st_entry (LOCAL, "p_lhs", lhs->value);

			if (!agn->is_ref)
			{
				code << "write_var (p_lhs, rhs);\n";
			}
			else
			{
				code
				<< "sep_copy_on_write (&rhs);\n"
				<< "copy_into_ref (p_lhs, &rhs);\n";
			}
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
 * // TODO objects
 * If $x is "", false or NULL, convert it to an array.
 * If $x is a string, assign into its $i_th position
 *		- convert $y to a string
 *	If $x is another scalar
 *		TODO error?
 *
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

	void generate_code(Generate_LIR* gen)
	{
		assert (lhs->value);
		assert (index->value);
		assert (rhs->value);

		code 
		// get the array
		<< get_st_entry (LOCAL, "p_lhs_array", lhs->value)
		<< "check_array_type (p_lhs_array TSRMLS_CC);\n"

		// get the index
		<< read_rvalue ("lhs_index", index->value)
	


		// Special case: string assignment
		<< "if (Z_TYPE_P (*p_lhs_array) == IS_STRING && Z_STRLEN_PP (p_lhs_array) > 0)\n"
		<< "{\n";
		if (agn->is_ref)
		{
			code
			<< "php_error_docref (NULL TSRMLS_CC, E_ERROR,"
			<<  "\"Cannot create references to/from string offsets nor overloaded objects\");\n"
			;
		}
		else
		{
			code
			<< read_rvalue ("rhs", rhs->value)
			<< "// TODO update the string\n"
			<< "write_string_index (p_lhs_array, lhs_index, rhs TSRMLS_CC);\n"
			;
		}
		code
		<< "}\n"


		// Array assignment
		<< "else if (Z_TYPE_PP (p_lhs_array) == IS_ARRAY)\n"
		<< "{\n"
		
		
		// get the HT entry
		<< "zval** p_lhs = get_ht_entry ("
		<<						"p_lhs_array, "
		<<						"lhs_index"	
		<<						" TSRMLS_CC);\n"
		;


		if (not agn->is_ref)
		{
		  code	
		  << read_rvalue ("rhs", rhs->value)
		  << "\n"
		  << "if (*p_lhs != rhs)\n"
		  <<		"write_var (p_lhs, rhs);\n"
		  ;
		}
		else
		{
			code
			<< get_st_entry (LOCAL, "p_rhs", dyc<VARIABLE_NAME> (rhs->value))
			<< "sep_copy_on_write (p_rhs);\n"
			<< "copy_into_ref (p_lhs, p_rhs);\n"
			;
		}
		code
		<< "}\n";
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

	void generate_code(Generate_LIR* gen)
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
			<< read_rvalue ("rhs", rhs->value)
			
			<< "if (*p_lhs != rhs)\n"
			<<	"	write_var (p_lhs, rhs);\n"
			;
		}
		else
		{
			// TODO this is wrong
			code	
			<< get_st_entry (LOCAL, "p_rhs", dyc<VARIABLE_NAME> (rhs->value))
			<< "sep_copy_on_write (p_rhs);\n"
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

	void generate_code(Generate_LIR* gen)
	{
		if(!stmt->is_ref)
		{
			code
			<< "zval** p_lhs;\n"
			<< read_rvalue ("index", lhs->value)
			<< get_var_var (LOCAL, "p_lhs", "index")
			<< read_rvalue ("rhs", rhs->value)
			<< "if (*p_lhs != rhs)\n"
			<<		"write_var (p_lhs, rhs);\n"
			;
		}
		else
		{
			code
			<< "zval** p_lhs;\n"
			<< read_rvalue ("index", lhs->value)
			<< get_var_var (LOCAL, "p_lhs", "index")
			<< get_st_entry (LOCAL, "p_rhs", dyc<VARIABLE_NAME> (rhs->value))
			<< "sep_copy_on_write (p_rhs);\n"
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

	void generate_code(Generate_LIR* gen)
	{
		code
		<< index_lhs (LOCAL, "p_local_global_var", var_name->value) // lhs
		<< index_lhs (GLOBAL, "p_global_var", var_name->value) // rhs
		// Note that p_global_var can be in a copy-on-write set.
		<< "sep_copy_on_write (p_global_var);\n"
		<< "copy_into_ref (p_local_global_var, p_global_var);\n"
		;
	}

	string index_lhs (Scope scope, string zvp, Expr* expr)
	{
		stringstream ss;
	
		if (VARIABLE_NAME* var_name = dynamic_cast<VARIABLE_NAME*> (expr))
		{
			ss
			<< "// Normal global\n"
			<< get_st_entry (scope, zvp, var_name)
			;
		}
		else
		{
			Variable_variable* var_var = dyc<Variable_variable> (expr);

			ss
			<< "// Variable global\n"
			<< "zval** " << zvp << ";\n"
			<< "{\n"
			<< read_rvalue ("index", var_var->variable_name)
			<< get_var_var (scope, zvp, "index")
			<< "}\n"
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

	void generate_code(Generate_LIR* gen)
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

	void generate_code(Generate_LIR* gen)
	{
		code 
		<<	read_rvalue ("p_cond", cond->value)

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

	void generate_code(Generate_LIR* gen)
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
		ret = new Wildcard<Return>;
		return that->match (ret);
	}

	void generate_code(Generate_LIR* gen)
	{
		if(!ret->value->attrs->is_true ("phc.codegen.return_by_ref"))
		{
			code 
			<< read_rvalue ("rhs", ret->value->rvalue)

			// Run-time return by reference has different
			// semantics to compile-time. If the function has CTRBR and RTRBR, the
			// the assignment will be reference. If one or the other is
			// return-by-copy, the result will be by copy. Its a question of
			// whether its separated at return-time (which we do here) or at the
			// call-site.
			<< "return_value->value = rhs->value;\n"
			<< "return_value->type = rhs->type;\n"
			<< "zval_copy_ctor (return_value);\n"
			;
		}
		else
		{
			code
			<< get_st_entry (LOCAL, "p_rhs", dyc<VARIABLE_NAME> (ret->value->rvalue))
			<< "sep_copy_on_write (p_rhs);\n"
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
	Wildcard<Return>* ret;
};

/*
 * unset ($x); (1)
 * or
 * unset ($x[$i]); (2) (corresponds to ZEND_UNSET_DIM)
 * or
 * unset ($x[$i][$j]); (3)
 *
 * Semantics:
 *
 *	(1) Remove $x from the symbol-table
 *	(2) If $x is a string, Error.
 *	    If $x is another scalar, do nothing
 *	    If $x is an array, remove entry $i
 *	(3) Different rules for > 1D indexing.
 *		 If the index is invalid, return NULL from that portion of indexing.
 *		 Then initialize it to an array. Then proceed.
 *
 * Allowed index types:
 *		double
 *		long
 *		bool
 *		resource (convert to long)
 *		string
 *		NULL (as "")
 *
 *	Anything else results in "Illegal offset type"
 *
 */
class Pattern_unset : public Pattern
{
	bool match(Statement* that)
	{
		unset = new Wildcard<Unset>;
		return that->match(unset);
	}

	void generate_code(Generate_LIR* gen)
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
				code
				<< "do\n"
				<< "{\n"
				;

				code
				<< get_st_entry (LOCAL, "u_array", var_name)
				<< "sep_copy_on_write (u_array);\n"
				<< "zval* array = *u_array;\n"
				;

				Rvalue_list* indices = unset->value->array_indices->clone ();
				Rvalue* back_index = indices->back ();
				indices->pop_back ();

				// Foreach index, read the array, but do not update it in place.
				foreach (Rvalue* index, *indices)
				{
					code
					<< "if (Z_TYPE_P (array) == IS_ARRAY)\n"
					<< "{\n"
					<<		read_rvalue ("index", index)
					// This uses check_array_index type because PHP behaves
					// differently for the inner index check than the outer one.
					<<	"	if (!check_array_index_type (index TSRMLS_CC))\n"
					<<	"	{\n"
					<<	"		array = EG(uninitialized_zval_ptr);\n"
					<<	"	}\n"
					<<	"	else\n"
					<< "		read_array (&array, array, index TSRMLS_CC);\n"
					<< "}\n"
					;
				}
				code
				<< read_rvalue ("index", back_index)
				<< "if (Z_TYPE_P (array) == IS_ARRAY)\n"
				<<	"	if (!check_unset_index_type (index TSRMLS_CC)) break;\n"

				<< "unset_array ("
				<<    "&array, "
				<<    "index "
				<<		" TSRMLS_CC);\n"
				;

				code
				<< "}\n"
				<< "while (0);\n"
				;
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

	void generate_code(Generate_LIR* gen)
	{
		assert (op_functions.has (*op->value->value));

		string op_fn = op_functions[*op->value->value]; 

		code 
		<<	get_st_entry (LOCAL, "p_var", var->value)

		<<	"sep_copy_on_write (p_var);\n"
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

	void generate_code(Generate_LIR* gen)
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

	void generate_code(Generate_LIR* gen)
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

	void generate_code(Generate_LIR* gen)
	{
		// declare the external iterator outside local scope blocks
		code
		<< "{\n"
		<<		read_rvalue ("fe_array", reset->value->array)
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

	void generate_code (Generate_LIR* gen)
	{
		code
		<<	read_rvalue ("fe_array", next->value->array)
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

	void generate_code(Generate_LIR* gen)
	{
		code
		<<	read_rvalue ("fe_array", end->value->array)
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

void Generate_LIR::children_statement(Statement* in)
{
	stringstream ss;
	stringstream comment;
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

		comment << "// " << *escape_C_comment (s(str)) << endl;
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
			lir->pieces->push_back (patterns[i]->generate_lir (
					s (comment.str ()),
					this));
			matched = true;
			break;
		}
	}

	if(not matched)
	{
		phc_unsupported (in, "unknown construct");
	}
}

string read_file (String* filename)
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
	stringstream ss;
	while (not file.eof ())
	{
		string str;
		getline (file, str);
		ss << str << endl;
	}

	file.close ();
	assert (file.is_open () == false);
	return ss.str ();
}

void include_file (ostream& out, String* filename)
{
	out << read_file (filename);
}

Map<string, string> templates;
void include_templates (String* filename)
{
	string templ_string = read_file (filename);
	string name, value;
	foreach (tie (name, value), *parse_templates (s(templ_string)))
		templates[name] = value;
}


string
templ (string name)
{
   if (!templates.has (name))
      phc_internal_error ("Missing template: %s", name.c_str ());

	return templates[name];
}


void Generate_LIR::pre_php_script(PHP_script* in)
{
	include_file (prologue, s("support.c"));
	include_file (prologue, s("debug.c"));
	include_file (prologue, s("zval.c"));
	include_file (prologue, s("string.c"));
	include_file (prologue, s("arrays.c"));
	include_file (prologue, s("isset.c"));
	include_file (prologue, s("methods.c"));
	include_file (prologue, s("misc.c"));
	include_file (prologue, s("unset.c"));
	include_file (prologue, s("var_vars.c"));

	include_file (prologue, s("builtin_functions.c"));

	include_templates (s("templates.lir"));


	// We need to save refcounts for functions returned by reference, where the
	// PHP engine destroys the refcount for no good reason.
	prologue << "int saved_refcount;\n";
	initializations << "saved_refcount = 0;\n";


	// Add constant-pooling declarations
	if (args_info.optimize_given)
	{
		Literal_list* pooled_literals = 
			in->attrs->get_list<Literal> ("phc.codegen.pooled_literals");

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

	// Add function cache declarations
	String_list* called_functions = dyc<String_list> (in->attrs->get ("phc.codegen.called_functions"));
	foreach (String* name, *called_functions)
	{
		string fci_name = suffix (*name, "fci");
		string fcic_name = suffix (*name, "fcic");

		prologue
		<< "static zend_fcall_info " << fci_name << ";\n"
		<< "static zend_fcall_info_cache " << fcic_name << " = {0,NULL,NULL,NULL};\n"
		;
	}

	lir->pieces->push_back (new LIR::UNINTERPRETED (s(prologue.str())));
}

LIR::UNINTERPRETED*
Generate_LIR::clear_code_buffer ()
{
	// These is probably some code left in 'code'.
	LIR::UNINTERPRETED* result = new LIR::UNINTERPRETED(s (code.str()));
	code.str ("");

	assert (code.str().size () == 0);
	return result;
}


void Generate_LIR::post_php_script(PHP_script* in)
{
	LIR::UNINTERPRETED* end = clear_code_buffer ();
	lir->pieces->push_back (end);

	code << "// ArgInfo structures (necessary to support compile time pass-by-reference)\n";
	Signature_list* methods = in->attrs->get_list<Signature>("phc.codegen.compiled_functions");
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
	LIR::UNINTERPRETED* all = clear_code_buffer ();
	lir->pieces->push_back (all);
}

/*
 * Bookkeeping 
 */

Generate_LIR::Generate_LIR()
{
	lir = new LIR::C_file;
}
