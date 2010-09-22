/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate C code
 *
 * We define a virtual class "Pattern" which corresponds to a particular kind
 * of statement that we can generate code for. We inherit from Pattern to 
 * define the various statements we can translate, create instances of each
 * of these classes, and then for every statement in the input, cycle through
 * all the patterns to find one that matches, and then call "generate" on that
 * pattern.
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
#include "codegen/Generate_C_annotations.h"
#include "process_mir/MIR_to_AST.h"
#include "pass_manager/Pass_manager.h"

#include "Generate_C.h"
#include "parsing/MICG_parser.h"
#include "embed/embed.h"

using namespace boost;
using namespace MIR;
using namespace std;

// Label supported features
void phc_unsupported (Node* node, const char* feature)
{
	cerr << "Not yet supported in code generation: " << feature << endl;
	(new MIR_unparser (cerr, true))->unparse (node);
	cerr << endl;
	xml_unparse (node, cerr);
	exit (-1);
}

// A single pass isnt really sufficient, but we can hack around it
// with a prologue;
static stringstream minit;

// TODO this is here for constant pooling. This should not be global.
extern struct gengetopt_args_info args_info;

// we need access to the pass manager in compile_static_value
extern Pass_manager* pm;


/* While its tough to remove these, we can at least limit them so that they
 * arent usable from patterns. */
static stringstream prologue;
static stringstream initializations;
static stringstream embed_initializations;
static stringstream finalizations;

/*
 * Helper functions
 */

#define INST(BUF, NAME, ...)												\
	do																				\
	{																				\
		Object* __obj_array[] = {__VA_ARGS__};							\
		Object_list* __obj_list = new Object_list;					\
																					\
		foreach (Object* __obj, __obj_array)							\
			__obj_list->push_back (__obj);								\
																					\
		BUF << gen->micg.instantiate (NAME, __obj_list);			\
	} while (0)


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

/*
 * Callbacks
 */
string cb_get_hash (Object_list* params)
{
	Object* name = params->front ();
	assert (isa<Identifier> (name) || isa<String> (name));
	return (get_hash (MICG_gen::convert_to_string (name)));
}

string cb_get_length (Object_list* params)
{
	Object* name = params->front ();
	assert (isa<Identifier> (name) || isa<String> (name));
	return lexical_cast<string> (MICG_gen::convert_to_string (name)->size ());
}

string cb_is_literal (Object_list* params)
{
	Object* obj = params->front ();
	assert (isa<Rvalue> (obj));

	if (isa<MIR::Literal> (obj))
		return MICG_TRUE;
	else
		return MICG_FALSE;
}

string write_literal_directly_into_zval (string, Literal*);
string cb_write_literal_directly_into_zval (Object_list* params)
{
	String* name = dyc<String> (params->front ());
	Literal* lit = dyc<Literal> (params->back());

	return write_literal_directly_into_zval (*name, lit);
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

// Declare and fetch a zval* containing the value for RVALUE. The value can be
// changed, but the symbol-table entry cannot be affected through this.
string read_rvalue (string zvp, Rvalue* rvalue)
{
	stringstream ss;
	if (isa<Literal> (rvalue))
	{
		Literal* lit = dyc<Literal> (rvalue);
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
				<< write_literal_directly_into_zval (zvp, lit)
				;
		}
		return ss.str();
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
		<<		"Z_ADDREF_P(" << name << ");\n"
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
	<< "zval** " << zvp << " = get_var_var (" 
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
		(*this)["<"] = "is_smaller_function";
		(*this)["<="] = "is_smaller_or_equal_function";
		// Unary functions
		(*this)["!"] = "boolean_not_function";
		(*this)["not"] = "boolean_not_function";
		(*this)["~"] = "bitwise_not_function";
		// Post- functions
		(*this)["++"] = "increment_function";
		(*this)["--"] = "decrement_function";
	}
} op_functions;

/*
 * Pattern definitions for statements
 */

#define RTS(STR) buf << increment_stat (STR);
string init_stats () 
{
	if (args_info.rt_stats_flag)
		return "init_counters ();\n";
	else
		return "";
}

string finalize_stats ()
{
	if (args_info.rt_stats_flag)
		return "finalize_counters ();\n";
	else
		return "";
}

string increment_stat (string name)
{
	if (!args_info.rt_stats_flag)
		return "";

	stringstream ss;
	ss 
	<< "increment_counter (\""
	<< name << "\", "
	<< name.size () + 1 << ", "
	<< get_hash (s(name))
	<< ");\n"
	;

	return ss.str ();
}

class Pattern : virtual public GC_obj
{
public:
	Pattern () : use_scope (true) {}
	virtual bool match(Statement* that) = 0;
	virtual void generate_code(Generate_C* gen) = 0;
	virtual ~Pattern() {}
	bool use_scope;
	stringstream buf;

	string generate (String* comment, Generate_C* gen)
	{
		// clear the buffer
		buf.str ("");

		buf << *comment;

		// Unless its a class, method or string, it should be wrapped in a scope.
		if (this->use_scope)
			buf << "{\n";

		RTS (demangle (this));

		this->generate_code (gen);

		if (this->use_scope)
		{
			buf
			<<		"phc_check_invariants (TSRMLS_C);\n"
			<< "}\n";
		}

		return buf.str();
	}
};

string method_mod_flags(Method_mod* mod)
{
	stringstream flags;

	if(mod->is_public)
	{
		flags << "ZEND_ACC_PUBLIC";
		assert(!mod->is_protected);
		assert(!mod->is_private);
	}
	else if(mod->is_protected)
	{
		flags << "ZEND_ACC_PROTECTED";
		assert(!mod->is_public);
		assert(!mod->is_private);
	}
	else if(mod->is_private)
	{
		flags << "ZEND_ACC_PRIVATE";
		assert(!mod->is_public);
		assert(!mod->is_protected);
	}
	else
	{
		// No access modifiers specified; assume public
		flags << "ZEND_ACC_PUBLIC";
	}

	if(mod->is_static)   flags << " | ZEND_ACC_STATIC";
	if(mod->is_abstract) flags << " | ZEND_ACC_ABSTRACT";
	if(mod->is_final)    flags << " | ZEND_ACC_FINAL";

	return flags.str();
}

string attr_mod_flags(Attr_mod* mod)
{
	stringstream flags;

	if(mod->is_public)
	{
		flags << "ZEND_ACC_PUBLIC";
		assert(!mod->is_protected);
		assert(!mod->is_private);
	}
	else if(mod->is_protected)
	{
		flags << "ZEND_ACC_PROTECTED";
		assert(!mod->is_public);
		assert(!mod->is_private);
	}
	else if(mod->is_private)
	{
		flags << "ZEND_ACC_PRIVATE";
		assert(!mod->is_public);
		assert(!mod->is_protected);
	}
	else
	{
		// No access modifiers specified; assume public
		flags << "ZEND_ACC_PUBLIC";
	}

	if(mod->is_static) flags << " | ZEND_ACC_STATIC";
	// const is not an access modifier

	return flags.str();
}

void function_declaration_block(ostream& buf, Signature_list* methods, String* block_name)
{
	buf << "// ArgInfo structures (necessary to support compile time pass-by-reference)\n";
	foreach (Signature* s, *methods)
	{
		String* name = s->method_name->value;

		// TODO: pass by reference only works for PHP>5.1.0. Do we care?
		buf 
		<< "ZEND_BEGIN_ARG_INFO_EX(" << *block_name << "_" << *name << "_arg_info, 0, "
		<< (s->return_by_ref ? "1" : "0")
		<< ", 0)\n"
		;

		// TODO: deal with type hinting

		foreach (Formal_parameter* fp, *s->formal_parameters)
		{
			buf 
			<< "ZEND_ARG_INFO("
			<< (fp->is_ref ? "1" : "0")
			<< ", \"" << *fp->var->variable_name->value << "\")\n"; 
		}

		buf << "ZEND_END_ARG_INFO()\n\n";
	}

	buf 
		<< "static function_entry " << *block_name << "_functions[] = {\n"
		;

	foreach (Signature* s, *methods)
	{
		String* name = s->method_name->value;

		String* class_name = NULL;
		if(s->attrs->has("phc.codegen.class_name"))
			class_name = s->attrs->get_string("phc.codegen.class_name");

		if(class_name == NULL)
		{
			buf << "PHP_FE(" << *name << ", " << *block_name << "_" << *name << "_arg_info)\n";
		}
		else
		{
			// TODO: deal with visibility flags
			buf << "PHP_ME(" << *class_name << ", " << *name << ", " << *block_name << "_" << *name << "_arg_info, " << method_mod_flags(s->method_mod) << ")\n";
		}
	}

	buf << "{ NULL, NULL, NULL }\n";
	buf << "};\n";
}

// Compile a static value and leave the result in a (newly declared)
// zval called result 
void Generate_C::compile_static_value(string result, ostream& os, Static_value* sv)
{
	assert(sv != NULL);

	// Declare all variables in a local scope except the result
	os 
	<< "zval* " << result << ";\n" 
	<< "{\n";

	// Make the result variable as st_entry_not_required so that the code
	// generator creates a local C variable to hold the result rather than
	// trying to store it in EG(active_symbol_table)
	AST::VARIABLE_NAME* def = new AST::VARIABLE_NAME(s("__static_value__"));
	def->attrs->set_true("phc.codegen.st_entry_not_required");

	// Create an AST script to create the default
	MIR_to_AST* mir_to_ast = new MIR_to_AST;
	AST::Expr* expr = mir_to_ast->fold_static_value(sv);
	AST::PHP_script* create_default_ast 
		= new AST::PHP_script(
				new AST::Statement_list(
					new AST::Eval_expr(
						new AST::Assignment(
							new AST::Variable(
								NULL, // target
							 	def,	
								new AST::Expr_list()
							),
							false, // is_ref
						  expr	
						))));
					
	// compile to MIR
	MIR::PHP_script* create_default_mir = dynamic_cast<MIR::PHP_script*>(pm->run_until(s("mir"), create_default_ast, false));

	// We need to know the temps
	Generate_C_annotations* gen_ann;
	gen_ann = new Generate_C_annotations();
	gen_ann->visit_statement_list(create_default_mir->statements);

	// Declare all required temps
	foreach (string temp, gen_ann->var_names)
		os << "zval* " << get_non_st_name(s(temp)) << " = NULL;\n";

	// Generate C code the the MIR
	foreach (Statement* s, *create_default_mir->statements)
	{
		os << compile_statement(s);
	}

	// Create a copy of the result in default_value, and increase its refcount
	// so that it does not get cleaned up with the rest of the temps
	os 
	<< result << " = local___static_value__;\n" 
	<< "assert(!Z_ISREF_P(" << result << "));\n" 
	<< "Z_ADDREF_P(" << result << ");\n";

	// Clean up the temps again
	foreach (string temp, gen_ann->var_names)
	{
		string name = get_non_st_name (s(temp));
		os	
		<< "if (" << name << " != NULL)\n"
		<< "{\n"
		<<		"zval_ptr_dtor (&" << name << ");\n"
		<< "}\n"
		;
	}

	// Close the scope
	os << "}\n";
}

class Pattern_class_def : public Pattern
{
public:
	bool match(Statement* that)
	{
		use_scope = false;
		pattern = new Wildcard<Class_def>;
		return that->match(pattern);
	}

	void generate_code(Generate_C* gen)
	{
		// Compile the class members
		foreach (Member* member, *pattern->value->members)
		{
			Method* method = dynamic_cast<Method*>(member);

			if(method != NULL)
			{
				buf << gen->compile_statement(method);
			} 
		}

		// Declare all class members
		function_declaration_block(buf, pattern->value->attrs->get_list<Signature>("phc.codegen.compiled_functions"), pattern->value->class_name->value);

		// Create the class entry in MINIT
		minit
		<< "{\n"
		<< "zend_class_entry ce; // temp\n"
		<< "zend_class_entry* ce_reg; // once registered, ce_ptr should be used\n"
		<< "INIT_CLASS_ENTRY(ce, " 
		<< "\"" << *pattern->value->class_name->value << "\", " 
		<< *pattern->value->class_name->value << "_functions);\n"
		;

		// Register the class
		CLASS_NAME* parent = pattern->value->extends;
		if(parent != NULL)
		{
			minit 
			<< "zend_class_entry* parent;\n"
			<< "parent = zend_fetch_class(\"" << *parent->value << "\", " << parent->value->length() << ", ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);\n"
			<< "ce_reg = zend_register_internal_class_ex(&ce, parent, \"" << *parent->value << "\" TSRMLS_CC);\n";
			;
		}
		else
		{
			minit << "ce_reg = zend_register_internal_class(&ce TSRMLS_CC);\n";
		}

		// Clear the ZEND_INTERNAL_CLASS flag so that we can add complex zvals
		// as class attributes. TODO: not sure what the consequences of this are.
		minit << "ce_reg->type &= ~ZEND_INTERNAL_CLASS;\n";

		// Compile attributes
		foreach (Member* member, *pattern->value->members)
		{
			Attribute* attr = dynamic_cast<Attribute*>(member);

			if(attr != NULL)
			{
				minit << "{\n";
				
				// We must have a default value
				assert(attr->var->default_value != NULL);
				gen->compile_static_value("default_value", minit, attr->var->default_value);

				if(!attr->attr_mod->is_const)
				{
					minit 
					<< "phc_declare_property(ce_reg, "
					<< "\"" << *attr->var->variable_name->value << "\", " 
					<< attr->var->variable_name->value->size() << ", "
					<< "default_value, "
					<< attr_mod_flags(attr->attr_mod) << " " 
					<< "TSRMLS_CC);"
					;
				}
				else if(attr->attr_mod->is_const)
				{
					// TODO: implement
					// (Const attributes must be added using a different API)
					phc_unsupported (attr, "const attribute");
				}

				minit << "}";
			}
		}

		minit << "}";
	}

protected:
	Wildcard<Class_def>* pattern;
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

	void generate_code (Generate_C* gen)
	{
		signature = pattern->value->signature;

		method_entry(gen);
		RTS (demangle (this));

		// Use a different gen for the nested function
		Generate_C* new_gen = new Generate_C(buf);
		new_gen->micg = gen->micg;
		new_gen->visit_statement_list (pattern->value->statements);
		buf << new_gen->body.str ();

		method_exit();
	}


protected:
	Wildcard<Method>* pattern;
	Signature* signature;

protected:
	void debug_argument_stack()
	{
		buf	
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
		<<		"	printf(\"addr = %08X, refcount = %d, is_ref = %d\\n\", (long)param_ptr, Z_REFCOUNT_P(param_ptr), Z_ISREF_P(param_ptr));\n"
		<<		"	arg_count--;\n"
		<<		"}\n"
		<<		"printf(\"END ARGUMENT STACK\\n\");\n"
		<< "}\n"
		;
	}

	void method_entry(Generate_C* gen)
	{
		String* class_name = NULL;
		if(signature->attrs->has("phc.codegen.class_name"))
			class_name = signature->attrs->get_string("phc.codegen.class_name");
	
		// Function header
		if(class_name != NULL)
		{
			buf
			<< "PHP_METHOD(" << *class_name << ", "
			<< *signature->method_name->value << ")\n";
		}
		else
		{
			buf
			<< "PHP_FUNCTION"
			<< "(" << *signature->method_name->value << ")\n";
		}
		
		buf << "{\n";

		// __MAIN__ uses the global symbol table. Dont allocate for
		// functions which dont need a symbol table.
		if (*signature->method_name->value != "__MAIN__" 
			&& not signature->method_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
		{
			buf
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
		{
			if(*var == "this") 
				buf << "zval* " << get_non_st_name (var) << " = getThis();\n";
			else
				buf << "zval* " << get_non_st_name (var) << " = NULL;\n";
		}

		// Declare hashtable iterators for the function
		String_list* iterators = dyc<String_list> (pattern->value->attrs->get ("phc.codegen.ht_iterators"));
		foreach (String* iter, *iterators)
			buf << "HashPosition " << *iter << ";\n";

		// debug_argument_stack();

		// TODO: the same variable may be used twice in the signature. This leads to a memory leak.
		Formal_parameter_list* parameters = signature->formal_parameters;
		if(parameters && parameters->size() > 0)
		{
			buf 
			<< "// Add all parameters as local variables\n"
			<< "{\n"
			<< "int num_args = MIN(ZEND_NUM_ARGS (), " << parameters->size() << ");\n"
			<< "zval* params[" << parameters->size() << "];\n"
			// First parameter to zend_get_parameters_array does not appear
			// to be used (by looking at the source)
			<< "zend_get_parameters_array(0, num_args, params);\n"
			;

			int index = 0;
			foreach (Formal_parameter* param, *parameters)
			{
//				buf << "printf(\"refcount = %d, is_ref = %d\\n\", Z_REFCOUNT_P(params[" << index << "]), Z_ISREF_P(params[" << index << "]));\n";
				buf << "// param " << index << "\n";

				// if a default value is available, then create code to
				// assign it if an argument is not provided at run time.
				// We model it as an assignment to the named variable,
				// and call on the code generator to generate the
				// default assignment for us.
				if (param->var->default_value)
				{
					buf 
					<< "if (num_args <= " << index << ")\n"
					<< "{\n"
					;

					gen->compile_static_value ("default_value", buf, param->var->default_value);

					buf
					<< "Z_DELREF_P(default_value);\n"
					<<	"	params[" << index << "] = default_value;\n"
					<< "}\n"
					;
				}

				buf
				<< "Z_ADDREF_P(params[" << index << "]);\n";

				// TODO this should be abstactable, but it work now, so
				// leave it.
				
				// We can have multiple parameters with the same name. In that
				// case, destroy the predecessor (the second is not deemed to
				// assign to the first, so references etc are moot).
				if (param->var->variable_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
				{
					string name = get_non_st_name (param->var->variable_name);
					buf 
					<< "if (" << name << " != NULL)\n"
					<< "{\n"
					<< "	zval_ptr_dtor (&" << name << ");\n"
					<< "}\n"
					<< name << " = params[" << index << "];\n";
				}
				else
				{
					buf
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

				index++;
			}
				
			buf << "}\n";

		}
		
		buf << "// Function body\n";
	}

	void method_exit()
	{
		buf
		// Labels are local to a function
		<< "// Method exit\n"
		<< "end_of_function:__attribute__((unused));\n"
		;


		if (*signature->method_name->value != "__MAIN__"
			&& not signature->method_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
		{
			buf
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
			// don't destroy $this
			if(*var_name == "this") continue;

			string name = get_non_st_name (var_name);
			buf
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
		if (signature->return_by_ref)
		{
			buf
			<< "if (*return_value_ptr)\n"
			<< "	saved_refcount = Z_REFCOUNT_P(*return_value_ptr);\n"
			;
		}

		if (*signature->method_name->value == "__MAIN__")
		{
			buf << finalizations.str ();
		}

		buf << "}\n" ;
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
 * $x = new C(..);
 */

class Pattern_assign_expr_new : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<New>;
		return rhs;
	}

	void generate_code(Generate_C* gen)
	{
		CLASS_NAME* class_name;
		Variable_class* variable_class;

		New* nw = rhs->value;

		class_name = dynamic_cast<CLASS_NAME*>(nw->class_name);
		variable_class = dynamic_cast<Variable_class*>(nw->class_name);

		if(class_name != NULL)
		{
			if(!agn->is_ref)
				INST (buf, "assign_expr_new", lhs->value, class_name);
			else
				INST (buf, "assign_expr_new_ref", lhs->value, class_name);
		}
		else
		{
			assert (variable_class);
			VARIABLE_NAME* vcn = variable_class->variable_name;

			if(!agn->is_ref)
				INST (buf, "assign_expr_var_new", lhs->value, vcn);
			else
				INST (buf, "assign_expr_var_new_ref", lhs->value, vcn);
		}

		// See comment in expr_method_invocation
		Object_list* params = new Object_list;
		foreach (Actual_parameter* ap, *rhs->value->actual_parameters)
		{
			params->push_back (ap->rvalue);
			if (ap->is_ref)
				ap->rvalue->attrs->set_true ("phc.codegen.is_ref");
		}


		INST (buf, "constructor_invocation",
        rhs->value,
				params,
				rhs->value->get_filename (),
				s(lexical_cast<string>(rhs->value->get_line_number())),
				s(lexical_cast<string>(rhs->value->actual_parameters->size())),
				lhs->value);
	}

protected:
	Wildcard<New>* rhs;
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
		if (!agn->is_ref)
			INST (buf, "assign_expr_var", lhs->value, rhs->value);
		else
			INST (buf, "assign_expr_ref_var", lhs->value, rhs->value);
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
		VARIABLE_NAME* lhs_var = lhs->value;
		VARIABLE_NAME* index_var = rhs->value->variable_name;

		if (!agn->is_ref)
			INST (buf, "assign_expr_var_var", lhs_var, index_var);
		else
			INST (buf, "assign_expr_ref_var_var", lhs_var, index_var);
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
		if (!agn->is_ref)
		{
			INST (buf, "assign_expr_array_access", 
				lhs->value, rhs->value->variable_name, rhs->value->index);
		}
		else
		{
			INST (buf, "assign_expr_ref_array_access", 
				lhs->value, rhs->value->variable_name, rhs->value->index);
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
		Map<string, string> symnames;
		symnames["array"]		= "IS_ARRAY";
		symnames["bool"]		= "IS_BOOL";
		symnames["int"]		= "IS_LONG";
		symnames["object"]	= "IS_OBJECT";
		symnames["real"]		= "IS_DOUBLE";
		symnames["string"]	= "IS_STRING";
		symnames["unset"]		= "IS_NULL";

		// No other casts are allowed.
		assert (symnames.has (*cast->value->value));


		INST (buf, "assign_expr_cast",
				lhs->value, rhs->value, s(symnames[*cast->value->value]));
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

		INST (buf, "assign_expr_constant",
				lhs->value, name);
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
		assert (!agn->is_ref);

		string op_fn = op_functions[*op->value->value];

		INST (buf, "assign_expr_bin_op",
				lhs->value, left->value, right->value, s(op_fn));
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
		rhs = new Wildcard<VARIABLE_NAME>;

		return new Unary_op(op, rhs);
	}

	void generate_code (Generate_C* gen)
	{
		assert (!agn->is_ref);
		assert (op_functions.has (*op->value->value));

		string op_fn = op_functions[*op->value->value]; 

		INST (buf, "assign_expr_unary_op",
				lhs->value, rhs->value, s(op_fn));
	}

protected:
	Wildcard<OP>* op;
	Wildcard<VARIABLE_NAME>* rhs;
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
		buf
		<< get_st_entry (LOCAL, "p_lhs", lhs->value)
		<< "zval* value;\n"
		<< "if (Z_ISREF_P(*p_lhs))\n"
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

		initialize ("value");
	}

	virtual void initialize (string var) = 0;
};

string
write_literal_directly_into_zval (string var, Literal* lit)
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
	else if (/* NIL* value = */ dynamic_cast<NIL*> (lit))
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

class Pattern_assign_literal : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<Literal>;
		return rhs;
	}

	void generate_code (Generate_C* gen)
	{
		assert (!agn->is_ref);
		INST (buf, "assign_expr_literal", lhs->value, rhs->value);
	}

public:
	Wildcard<Literal>* rhs;
};



// Isset uses Pattern_assign_value, as it only has a boolean value. It puts the
// BOOL into the ready made zval.
class Pattern_assign_expr_isset : public Pattern_assign_value
{
	Expr* rhs_pattern()
	{
		isset = new Wildcard<Isset>;
		return isset;
	}

	void initialize(string lhs)
	{
		VARIABLE_NAME* var_name = dynamic_cast<VARIABLE_NAME*> (isset->value->variable_name);

		if (var_name)
		{
			if (isset->value->array_indices->size() == 0)
			{
				if (var_name->attrs->is_true ("phc.codegen.st_entry_not_required"))
				{
					string name = get_non_st_name (var_name);
					buf 
					<< "ZVAL_BOOL(" << lhs << ", " 
					<< name << " != NULL && !ZVAL_IS_NULL(" << name << "));\n"; 
				}
				else
				{
					buf
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

				buf
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

			buf
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

class Pattern_assign_expr_foreach_has_key : public Pattern_assign_var
{
	Expr* rhs_pattern()
	{
		has_key = new Wildcard<Foreach_has_key>;
		return has_key;
	}

	void generate_code (Generate_C* gen)
	{
		INST (buf, "assign_expr_foreach_has_key",
			lhs->value, has_key->value->array, has_key->value->iter->value);
	}

protected:
	Wildcard<Foreach_has_key>* has_key;
};

class Pattern_assign_expr_foreach_get_key : public Pattern_assign_var
{
	Expr* rhs_pattern()
	{
		get_key = new Wildcard<Foreach_get_key>;
		return get_key;
	}

	void generate_code (Generate_C* gen)
	{
		INST (buf, "assign_expr_foreach_get_key",
			lhs->value, get_key->value->array, get_key->value->iter->value);
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
		if (!agn->is_ref)
			INST (buf, "assign_expr_foreach_get_val",
					lhs->value, get_val->value->array,
					get_val->value->iter->value);
		else
			INST (buf, "assign_expr_ref_foreach_get_val",
					lhs->value, get_val->value->array,
					get_val->value->iter->value);
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

		return is_builtin_function (method_name->value->value);
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
		assert (!arg->is_ref);

		if (lhs)
		{
			assert (!agn->is_ref);
			INST (buf, "builtin_with_lhs",
					lhs->value, arg->value->rvalue,
					method_name->value->value, arg->value->get_filename ());
		}
		else
		{
			INST (buf, "builtin_no_lhs",
					arg->value->rvalue,
					method_name->value->value, arg->value->get_filename ());
		}
	}

protected:
	Wildcard<METHOD_NAME>* method_name;
	Wildcard<Actual_parameter>* arg;
};

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
		string function_name = *dyc<METHOD_NAME> (rhs->value->method_name)->value;
		string fci_name = suffix (function_name, "fci");
		string fcic_name = suffix (function_name, "fcic");


		if (rhs->value->target != NULL)
		{
			VARIABLE_NAME* object_name = dynamic_cast<VARIABLE_NAME*>(rhs->value->target);
			CLASS_NAME* class_name  = dynamic_cast<CLASS_NAME*>(rhs->value->target);

			if(object_name != NULL)
			{
				// TODO: if we statically knew the type of the object that is
				// invoked (type inference) then we should be able to use
				// the cached function info. As it stands, we have to
				// lookup the function every time since the variable can be
				// bound to a different class every time we encounter this
				// statement
		
				INST (buf, "assign_param_is_ref_method", 
						s(function_name),
						rhs->value->get_filename (),
						s(lexical_cast<string> (rhs->value->get_line_number ())),
						s(lexical_cast<string> (rhs->value->param_index->value)),
						object_name,
						lhs->value);

				return;
			}
			else
			{
				assert (class_name != NULL);

				fci_name  = suffix (suffix(*class_name->value, function_name), "fci");
				fcic_name = suffix (suffix(*class_name->value, function_name), "fcic");
				function_name = *class_name->value + "::" + function_name;
			}
		}

		INST (buf,
				"assign_param_is_ref_function", 
				s(function_name),
				rhs->value->get_filename (),
				s(lexical_cast<string> (rhs->value->get_line_number ())),
				s(fci_name),
				s(fcic_name),
				s(lexical_cast<string> (rhs->value->param_index->value)),
				lhs->value);
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
		// The macros are paramatrized for the LHS. This descriptor says whether
		// the is no LHS, or, if there is, whether or not the assignment is
		// by-ref.
		String* lhs_descriptor;
		VARIABLE_NAME* lhs_var = NULL;
		if (lhs)
		{
			if (agn->is_ref)
				lhs_descriptor = s("REF");
			else
				lhs_descriptor = s("NO_REF");

			lhs_var = lhs->value;
		}
		else
		{
			lhs_descriptor = s("NONE");
		}

		// We want a list of rvalues here, not actual parameters. But we need
		// to communicate the is_ref field of the actual_parameter if its
		// there.
		Object_list* params = new Object_list;
		foreach (Actual_parameter* ap, *rhs->value->actual_parameters)
		{
			params->push_back (ap->rvalue);
			if (ap->is_ref)
				ap->rvalue->attrs->set_true ("phc.codegen.is_ref");
		}

		
		// buf << "debug_hash(EG(active_symbol_table));\n";

		// Variable function or ordinary function?
		METHOD_NAME* name = dynamic_cast<METHOD_NAME*>(rhs->value->method_name);
		if (name == NULL) phc_unsupported (rhs->value, "variable function");

		// Names of the runtime variables that will hold the (potentially
		// cached) location of the function
		string fci_name;
		string fcic_name;

		string function_name;

		// Global function or class member?
		if (rhs->value->target != NULL)
		{
			VARIABLE_NAME* object_name = dynamic_cast<VARIABLE_NAME*>(rhs->value->target);
			CLASS_NAME* class_name  = dynamic_cast<CLASS_NAME*>(rhs->value->target);

			if(object_name != NULL)
			{
				// TODO: if we statically knew the type of the object that is
				// invoked (type inference) then we should be able to use
				// the cached function info. As it stands, we have to
				// lookup the function every time since the variable can be
				// bound to a different class every time we encounter this
				// statement
		
				function_name = *name->value;

				INST (buf, "method_invocation",
						rhs->value,
						s(function_name),
						params,
						rhs->value->get_filename (),
						s(lexical_cast<string> (rhs->value->get_line_number ())),
						s(lexical_cast<string>(rhs->value->actual_parameters->size ())),
						object_name,
						lhs_descriptor,
						lhs ? lhs->value : NULL);

				return;
			}
			else
			{
				assert (class_name != NULL);

				stringstream fqn;
				fqn << *class_name->value << "::" << *name->value;
				
				fci_name  = suffix (suffix(*class_name->value, *name->value), "fci");
				fcic_name = suffix (suffix(*class_name->value, *name->value), "fcic");
				function_name = fqn.str();
			}
		}
		else
		{
			fci_name  = suffix (*name->value, "fci");
			fcic_name = suffix (*name->value, "fcic");
			function_name = *name->value;
		}

		INST (buf, "function_invocation",
				rhs->value,
				s(function_name),
				params,
				rhs->value->get_filename (),
				s(lexical_cast<string> (rhs->value->get_line_number ())),
				s(fci_name),
				s(fcic_name),
				s(lexical_cast<string>(rhs->value->actual_parameters->size ())),
				lhs_descriptor,
				lhs ? lhs->value : NULL);
	}

protected:
	Wildcard<Method_invocation>* rhs;
};


/*
 * OOP Field access
 */

class Pattern_assign_field : public Pattern
{
public:
	bool match(Statement* that)
	{
		pattern = new Wildcard<Assign_field>;
		return that->match(pattern);
	}

	void generate_code(Generate_C* gen)
	{
		VARIABLE_NAME* object_name;
		CLASS_NAME* class_name;
		FIELD_NAME* field_name;
		Variable_field* var_field;
 		
		object_name = dynamic_cast<VARIABLE_NAME*>(pattern->value->target);
 		class_name  = dynamic_cast<CLASS_NAME*>(pattern->value->target);
		field_name  = dynamic_cast<FIELD_NAME*>(pattern->value->field_name);
		var_field   = dynamic_cast<Variable_field*>(pattern->value->field_name);

		bool is_ref = pattern->value->is_ref;
		Rvalue* rhs = pattern->value->rhs;

		if (field_name != NULL)
		{
			if (object_name != NULL)
			{
				if (!is_ref)
					INST (buf, "assign_field", object_name, field_name, rhs);
				else
					INST (buf, "assign_field_ref", object_name, field_name, rhs);
			}
			else
			{
				assert (class_name);
				if (!is_ref)
					INST (buf, "assign_static_field", class_name, field_name, rhs);
				else
					INST (buf, "assign_static_field_ref", class_name, field_name, rhs);
			}
		}
		else if (var_field != NULL)
		{
			assert (var_field);
			VARIABLE_NAME* var_field_name = var_field->variable_name;

			if (object_name != NULL)
			{
				if (!is_ref)
					INST (buf, "assign_var_field", object_name, var_field_name, rhs);
				else
					INST (buf, "assign_var_field_ref", object_name, var_field_name, rhs);
			}
			else
			{
				assert (class_name);
				if (!is_ref)
					INST (buf, "assign_var_static_field", class_name, var_field_name, rhs);
				else
					INST (buf, "assign_var_static_field_ref", class_name, var_field_name, rhs);
			}
		}
	}

protected:
	Wildcard<Assign_field>* pattern;
};

class Pattern_assign_expr_field_access : public Pattern_assign_var
{
public:
	Expr* rhs_pattern()
	{
		rhs = new Wildcard<Field_access>;
		return rhs;
	}

	void generate_code (Generate_C* gen)
	{
		VARIABLE_NAME* object_name;
		CLASS_NAME* class_name;
		FIELD_NAME* field_name;
		Variable_field* var_field;
 		
		object_name = dynamic_cast<VARIABLE_NAME*>(rhs->value->target);
 		class_name  = dynamic_cast<CLASS_NAME*>(rhs->value->target);
		field_name  = dynamic_cast<FIELD_NAME*>(rhs->value->field_name);
		var_field   = dynamic_cast<Variable_field*>(rhs->value->field_name);

		bool is_ref = agn->is_ref;
		VARIABLE_NAME* lhs = Pattern_assign_var::lhs->value;

		if (field_name != NULL)
		{
			if (object_name != NULL)
			{
				if (!is_ref)
					INST (buf, "field_access", lhs, object_name, field_name);
				else
					INST (buf, "field_access_ref", lhs, object_name, field_name);
			}
			else
			{
				assert (class_name);
				if (!is_ref)
					INST (buf, "static_field_access", lhs, class_name, field_name);
				else
					INST (buf, "static_field_access_ref", lhs, class_name, field_name);
			}
		}
		else
		{
			assert (var_field);
			VARIABLE_NAME* var_field_name = var_field->variable_name;

			if (object_name != NULL)
			{
				if (!is_ref)
					INST (buf, "var_field_access", lhs, object_name, var_field_name);
				else
					INST (buf, "var_field_access_ref", lhs, object_name, var_field_name);
			}
			else
			{
				assert (class_name);
				if (!is_ref)
					INST (buf, "var_static_field_access", lhs, class_name, var_field_name);
				else
					INST (buf, "var_static_field_access_ref", lhs, class_name, var_field_name);
			}
		}
	}

protected:
	Wildcard<Field_access>* rhs;
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

	void generate_code(Generate_C* gen)
	{
		if (!agn->is_ref)
			INST (buf, "assign_array", lhs->value, index->value, rhs->value);
		else
			INST (buf, "assign_array_ref", lhs->value, index->value, rhs->value);
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
		if (!agn->is_ref)
			INST (buf, "assign_next", lhs->value, rhs->value);
		else
			INST (buf, "assign_next_ref", lhs->value, rhs->value);
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
		index = new Wildcard<VARIABLE_NAME>;
		rhs = new Wildcard<Rvalue>;
		agn = new Assign_var_var(index, false, rhs);
		return(that->match(agn));	
	}

	void generate_code(Generate_C* gen)
	{
		if(!agn->is_ref)
			INST (buf, "assign_var_var",
				index->value, rhs->value);
		else
			INST (buf, "assign_var_var_ref",
				index->value, rhs->value);
	}

	Assign_var_var* agn;
	Wildcard<VARIABLE_NAME>* index;
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
		if (isa<VARIABLE_NAME> (var_name->value))
			INST (buf, "global_var", var_name->value);
		else
			INST (buf, "global_var_var",
				dyc<Variable_variable> (var_name->value)->variable_name);
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
		buf << *label->value->value << ":;\n";
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
		INST (buf, "branch",
			cond->value, iftrue->value->value, iffalse->value->value);
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
		buf << "goto " << *label->value->value << ";\n";
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

	void generate_code(Generate_C* gen)
	{
		INST (buf, "return", ret->value->rvalue, ret->value);
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
					buf
					<< "if (" << name << " != NULL)\n"
					<< "{\n"
					<<		"zval_ptr_dtor (&" << name << ");\n"
					<<		name << " = NULL;\n"
					<< "}\n";
				}
				else
				{
					String* name = var_name->value;
					buf
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
				buf
				<< "do\n"
				<< "{\n"
				;

				buf
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
					buf
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
				buf
				<< read_rvalue ("index", back_index)
				<< "if (Z_TYPE_P (array) == IS_ARRAY)\n"
				<<	"	if (!check_unset_index_type (index TSRMLS_CC)) break;\n"

				<< "unset_array ("
				<<    "&array, "
				<<    "index "
				<<		" TSRMLS_CC);\n"
				;

				buf
				<< "}\n"
				<< "while (0);\n"
				;
			}
		}
		else
		{
			// Variable variable
			phc_unsupported (unset->value, "unset variable variable");
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

		INST (buf, "pre_op",
			var->value, s(op_fn));
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
		String alias_name = *alias->value->alias->value->to_lower ();
		String method_name = *alias->value->method_name->value->to_lower ();

		buf
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
			phc_unreachable ();

		alias_name = alias_name->to_lower ();
		aliased_name = aliased_name->to_lower ();

		buf
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
		<<		"sizeof(zend_class_entry),"
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
		reset = new Wildcard<Foreach_reset>;
		return that->match (reset);
	}

	void generate_code(Generate_C* gen)
	{
		INST (buf, "foreach_reset",
			reset->value->array, reset->value->iter->value);
	}

protected:
	Wildcard<Foreach_reset>* reset;
};

class Pattern_foreach_next : public Pattern
{
	bool match (Statement* that)
	{
		next = new Wildcard<Foreach_next>;
		return that->match (next);
	}

	void generate_code (Generate_C* gen)
	{
		INST (buf, "foreach_next",
			next->value->array, next->value->iter->value);
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
		INST (buf, "foreach_end",
			end->value->array, end->value->iter->value);
	}

protected:
	Wildcard<Foreach_end>* end;
};



/*
 * Visitor methods to generate C code
 * Visitor for statements uses the patterns defined above.
 */

string Generate_C::compile_statement(Statement* in)
{
	// TODO: this should be static, but making it static causes a segfault
	// TODO: possibly due to a pattern assuming all of its local state is reset?
	Pattern* patterns[] = 
	{
	// Top-level constructs
		new Pattern_method_definition ()
	,  new Pattern_class_def ()
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
	// OOP
	, new Pattern_assign_field()
	, new Pattern_assign_expr_field_access()
	, new Pattern_assign_expr_new()
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

	foreach (Pattern* pattern, patterns)
	{
		if(pattern->match(in))
		{
			return pattern->generate (s(comment.str()), this);
		}
	}
	phc_unsupported (in, "unknown construct");
	phc_unreachable ();
}

void Generate_C::children_statement(Statement* in)
{
	body << compile_statement(in);
}

string read_file (String* filename)
{
	// For now, we simply include this.
	ifstream file;

	stringstream ss1, ss2;
	ss1 << "runtime/" << *filename;
	ss2 << DATADIR << "/phc/runtime/" << *filename;

	// Check the current directory first. This means we can change the file without recompiling or installing.
	file.open (ss1.str ().c_str ());

	// Check the installed directory.
	if (!file.is_open())
		file.open (ss2.str ().c_str ());

	if (!file.is_open ())
		phc_internal_error ("Expected file missing: %s (expected at %s or %s)",
			filename->c_str(),
			ss2.str().c_str(),
			ss1.str().c_str());

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

void Generate_C::pre_php_script(PHP_script* in)
{
	micg.add_macro_def (read_file (s("templates/templates_new.c")), "templates/templates_new.c");

	prologue << "// BEGIN INCLUDED FILES" << endl;

	include_file (prologue, s("support.c"));
	include_file (prologue, s("debug.c"));
	include_file (prologue, s("zval.c"));
	include_file (prologue, s("string.c"));
	include_file (prologue, s("arrays.c"));
	include_file (prologue, s("isset.c"));
	include_file (prologue, s("methods.c"));
	include_file (prologue, s("oop.c"));
	include_file (prologue, s("misc.c"));
	include_file (prologue, s("unset.c"));
	include_file (prologue, s("var_vars.c"));

	include_file (prologue, s("builtin_functions.c"));

	prologue << "// END INCLUDED FILES" << endl;

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
			<< write_literal_directly_into_zval (*var, lit);
		}
	}

	
	// Add .ini settings
	// We only want to alter the ones given to us at the command-line
	foreach (String* key, *PHP::get_altered_ini_entries ())
	{
		String* value = PHP::get_ini_entry (key);
		embed_initializations
		<< "zend_alter_ini_entry ("
		<< "\"" << *key << "\", "
		<< (key->size () + 1) << ", " // include NULL byte
		<< "\"" << *value << "\", "
		<< value->size () << ", " // don't include NULL byte
		<< "PHP_INI_ALL, PHP_INI_STAGE_RUNTIME);\n"
		;
	}

	// Add function cache declarations
	String_list* cached_functions = dyc<String_list> (in->attrs->get ("phc.codegen.cached_functions"));
	foreach (String* name, *cached_functions)
	{
		string fci_name = suffix (*name, "fci");
		string fcic_name = suffix (*name, "fcic");

		prologue
		<< "static zend_fcall_info " << fci_name << ";\n"
		<< "static zend_fcall_info_cache " << fcic_name << ";\n"
		;

    initializations
    << "memset (&" << fci_name << ", 0, sizeof (zend_fcall_info));\n"
    << "memset (&" << fcic_name << ", 0, sizeof (zend_fcall_info_cache));\n"
    ;

    finalizations
    << "destroy_function_call (&" << fci_name << ");\n"
    ;
	}

}

void Generate_C::post_php_script(PHP_script* in)
{
	os << prologue.str ();
	os << body.str();

	// MINIT
	os << "// Module initialization\n"
		<< "PHP_MINIT_FUNCTION(" << *extension_name << ")\n{\n"

		<< "	// initialize the phc runtime\n"
		<< "	init_runtime();\n"
		<< "\n"
		<< "	// initialize the module\n"
		<<		minit.str()
		<< "\n"
		<< "	// initialize the stats\n"
		<<		init_stats ()
		<< "\n"
		<<	"	// Other initializations\n"
		<<		initializations.str ()
		<< "\n"
		<< "return SUCCESS;\n"
		<< "}\n";

	// MSHUTDOWN
	os << "// Module finalization\n"
		<< "PHP_MSHUTDOWN_FUNCTION(" << *extension_name << ")\n{\n"
		<< "\n"
		<<	"	// Other finalizations occur at the end of __MAIN__\n"
		<< "\n"
		<<	"	// finalize the stats\n"
		<<		finalize_stats ()
		<< "\n"
		<< "	// Finalize the runtime\n"
		<<	"	finalize_runtime();\n"
		<< "\n"
		<< "return SUCCESS;\n"
		<< "}";


	function_declaration_block(os, in->attrs->get_list<Signature>("phc.codegen.compiled_functions"), extension_name);

	os
	<< "// Register the module itself with PHP\n"
	<< "zend_module_entry " << *extension_name << "_module_entry = {\n"
	<< "STANDARD_MODULE_HEADER, \n"
	<< "\"" << *extension_name << "\",\n"
	<< *extension_name << "_functions,\n"
	<< "PHP_MINIT(" << *extension_name << "), /* MINIT */\n"
	<< "PHP_MSHUTDOWN(" << *extension_name << "), /* MSHUTDOWN */\n"
	<< "NULL, /* RINIT */\n"
	<< "NULL, /* RSHUTDOWN */\n"
	<< "NULL, /* MINFO */\n"
	<< "\"1.0\",\n"
	<< "STANDARD_MODULE_PROPERTIES\n"
	<< "};\n"
	;

	if(is_extension)
	{
		os << "ZEND_GET_MODULE(" << *extension_name << ")\n";
	}
	else
	{
		os << 
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
		"   php_embed_init (argc, argv PTSRMLS_CC);\n"
		"   zend_first_try\n"
		"   {\n"
		"\n"
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
		<<	embed_initializations.str () <<
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

Generate_C::Generate_C (ostream& os)
: os(os)
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


	micg.register_callback ("length", &cb_get_length, 1);
	micg.register_callback ("hash", &cb_get_hash, 1);
	micg.register_callback ("is_literal", &cb_is_literal, 1);
	micg.register_callback ("write_literal_directly_into_zval", &cb_write_literal_directly_into_zval, 2);
}
