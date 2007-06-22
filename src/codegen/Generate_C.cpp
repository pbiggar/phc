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

#include "Generate_C.h"
#include "process_ast/XML_unparser.h"
#include "lib/List.h"
#include "process_ast/PHP_unparser.h"

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

// Find the zval described by "var" and store it in "zvp"
// Scope only applies to the top-level variable! (i.e., the variable used
// to index a variable variable, or the variable used as an array index
// are always taken from the local scope)
void index_st(Scope scope, string zvp, AST_variable* var)
{
	// Variable variable or ordinary variable?
	Token_variable_name* name;
	name = dynamic_cast<Token_variable_name*>(var->variable_name);

	// TODO: deal with object indexing
	assert(var->target == NULL);

	string hash;
	if(scope == LOCAL)
		hash = "EG(active_symbol_table)";
	else
		hash = "&EG(symbol_table)";

	if(name != NULL)
	{
		// Ordinary variable
		cout
		<< zvp << " = index_ht(" << hash << ", "
		<< "\"" << *name->value << "\", "
		<< name->value->length() + 1 << ");\n"
		;
		
		if(var->array_indices->size() == 1)
		{
			String* ind = operand(var->array_indices->front());

			cout 
			<< "{\n"
			<< "HashTable* ht = extract_ht(" << zvp << ");"
			<< "zval* ind = index_ht(EG(active_symbol_table), "
			<< "\"" << *ind << "\", " << ind->length() + 1 << ");\n"
			<< zvp << " = index_ht_zval(ht, ind);\n"
			<< "}\n"
			;
		}
	}
	else
	{
		// Variable variable.
		// After shredder, a variable variable cannot have array indices
		assert(var->array_indices->size() == 0);

		AST_reflection* refl;
		refl = dynamic_cast<AST_reflection*>(var->variable_name);
		String* name = operand(refl->expr);

		cout 
		<< "{\n"
		<< "zval* name = index_ht(EG(active_symbol_table), "
		<< "\"" << *name << "\", " << name->length() + 1 << ");\n"
		<< zvp << " = index_ht_zval(" << hash << ", name);\n"
		<< "}\n"
		;
	}
}

// Update the variable "var" with "zvp", incrementing "zvp"'s refcount
// Scope only applies to the top-level variable! (i.e., the variable used
// to index a variable variable, or the variable used as an array index
// are always taken from the local scope)
void update_st(Scope scope, AST_variable* var, string zvp)
{
	string hash;
	if(scope == LOCAL)
		hash = "EG(active_symbol_table)";
	else
		hash = "&EG(symbol_table)";

	// Variable variable or ordinary variable?
	Token_variable_name* name;
	name = dynamic_cast<Token_variable_name*>(var->variable_name);

	cout << zvp << "->refcount++;\n";
	
	// Ordinary variable
	if(name != NULL)
	{
		if(var->array_indices->size() == 0)
		{
			cout 
			// Remove the old value from the hashtable
			// (reducing its refcount)
			<< "zend_hash_del(" << hash << ", "
			<< "\"" << *name->value << "\", "
			<< name->value->length() + 1 << ");\n"
			// Add the new value to the hashtable
			<< "zend_hash_add(" << hash << ", "
			<< "\"" << *name->value << "\", "
			<< name->value->length() + 1 << ", "
			<< "&" << zvp << ", sizeof(zval*), NULL);\n"
			;
		}
		else if(
			var->array_indices->size() == 1 &&
			var->array_indices->front() != NULL
			)
		{
			String* ind = operand(var->array_indices->front());

			cout 
			<< "{\n"
			<< "zval* arr = index_ht(" << hash << ", " 
			<< "\"" << *name->value << "\", "
			<< name->value->length() + 1 << ");\n"
			<< "HashTable* ht = extract_ht(arr);\n"
			<< "zval* ind = index_ht(EG(active_symbol_table), "
			<< "\"" << *ind << "\", " << ind->length() + 1 << ");\n"
			<< "update_ht(ht, ind, " << zvp << ");\n"
			<< "}\n"
			;
		}
		else if(
			var->array_indices->size() == 1 &&
			var->array_indices->front() == NULL
			)
		{
			// Assign to next available index
			cout 
			<< "{\n"
			<< "zval* arr = index_ht(" << hash << ", " 
			<< "\"" << *name->value << "\", "
			<< name->value->length() + 1 << ");\n"
			<< "HashTable* ht = extract_ht(arr);\n"
			<< "zend_hash_next_index_insert(ht, &" << zvp << ", sizeof(zval*), NULL);\n"
			<< "}\n"
			;
		}
		else
		{
			// Cannot happen after shredder
			assert(0);
		}
	}
	else
	{
		// After the shredder, this should be 0
		assert(var->array_indices->size() == 0);
	
		AST_reflection* refl;
		refl = dynamic_cast<AST_reflection*>(var->variable_name);
		String* ind = operand(refl->expr);

		cout
		<< "zval* ind = index_ht(EG(active_symbol_table), "
		<< "\"" << *ind << "\", " << ind->length() + 1 << ");\n"
		<< "update_ht(" << hash << ", ind, " << zvp << ");\n"
		;
	}
}
	
// Make a copy of zvp 
void clone(string zvp)
{
	cout
	<< "{\n"
	<< "zval* clone;\n"
	<< "MAKE_STD_ZVAL(clone);\n"
	<< "clone->refcount = 0;\n"
	<< "clone->value = " << zvp << "->value;\n"
	<< "clone->type = " << zvp << "->type;\n"
	<< "zval_copy_ctor(clone);\n"
	<< zvp << " = clone;\n"
	<< "}\n"
	;
}

// Implementation of "global" (used in various places)
void global(AST_variable_name* var_name, bool separate)
{
	AST_variable* var;
	var = new AST_variable(NULL, var_name, new List<AST_expr*>());

	cout << "{\n";
	cout << "zval* global_var;\n";
	index_st(GLOBAL, "global_var", var);
	
	// Separate RHS if necessary
	if(separate)
	{
		cout << "if(global_var->refcount > 1 && !global_var->is_ref) {\n";
		clone("global_var");
		update_st(GLOBAL, var, "global_var");
		cout << "}\n";
	}

	cout << "global_var->is_ref = 1;\n";
	update_st(LOCAL, var, "global_var");
	cout << "}\n";
}

// For convenience
void global(char* name)
{
	global(new Token_variable_name(new String(name)), false);
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
		cout <<
		"{\n"
		"void **p;\n"
		"int arg_count;\n"
		"zval *param_ptr;\n"
		"\n"
		"p = EG(argument_stack).top_element-2;\n"
		"arg_count = (ulong) *p;\n"
		"\n"
		"printf(\"\\nARGUMENT STACK\\n\");"
		"while (arg_count > 0) {\n"
		"	param_ptr = *(p-arg_count);\n"
		"	printf(\"addr = %08X, refcount = %d, is_ref = %d\\n\", (long)param_ptr, param_ptr->refcount, param_ptr->is_ref);\n"
		"	arg_count--;\n"
		"}\n"
		"printf(\"END ARGUMENT STACK\\n\");"
		"}\n"
		;
	}

	void method_entry()
	{
		cout
		// Function header
		<< "PHP_FUNCTION(" << *signature->method_name->value << ")\n"
		<< "{\n"
		;

		// __MAIN__ uses the global symbol table 
		if(*signature->method_name->value != "__MAIN__")
		{
			cout
			<< "// Setup locals array\n"
			<< "HashTable* locals;\n"
			<< "ALLOC_HASHTABLE(locals);\n"
			<< "zend_hash_init(locals, 64, NULL, ZVAL_PTR_DTOR, 0);\n"
			<< "HashTable* old_active_symbol_table = EG(active_symbol_table);\n"
			<< "EG(active_symbol_table) = locals;\n"
			;
		}

		// TODO: deal with all superglobals 
		global("GLOBALS");

		// debug_argument_stack();

		List<AST_formal_parameter*>* parameters = signature->formal_parameters;
		if(parameters && parameters->size() > 0)
		{
			cout 
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
//				cout << "printf(\"refcount = %d, is_ref = %d\\n\", params[" << index << "]->refcount, params[" << index << "]->is_ref);\n";
				cout << "// param " << index << "\n";

				// if a default value is available, then create code to
				// assign it if an argument is not provided at run time.
				// We model it as an assignment to the named variable,
				// and call on the code generator to generate the
				// default assignment for us.
				if ((*i)->expr)
				{
					cout 
						<< "if (num_args <= " << index << ")\n"
						<< "{\n";

					AST_statement* assign_default_values = 
						new AST_eval_expr (
								new AST_assignment (
									new AST_variable (
										NULL,
										(*i)->variable_name,
										new List<AST_expr*> ()),
									false, (*i)->expr));

					gen->children_statement (assign_default_values);
					cout << "} else {\n";
				}

				cout
					<< "params[" << index << "]->refcount++;\n"
					<< "zend_hash_add(EG(active_symbol_table), "
					<< "\"" << *(*i)->variable_name->value << "\", " 
					<< (*i)->variable_name->value->length() + 1  
					<< ", &params[" << index << "], sizeof(zval*), NULL);\n"
					;

				if ((*i)->expr)
					cout << "}\n";
			}
				
			cout << "}\n";

		}
		
		cout << "// Function body\n";
	}

	void method_exit()
	{
		cout
		// Labels are local to a function
		<< "// Method exit\n"
		<< "end_of_function:;\n"
		;

		if(*signature->method_name->value != "__MAIN__")
		{
			cout
			<< "// Destroy locals array\n"
			<< "zend_hash_destroy(locals);\n"
			<< "FREE_HASHTABLE(locals);\n"
			<< "EG(active_symbol_table) = old_active_symbol_table;\n"
			;
		}

		cout << "}\n";
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
		cout << *label->value->value << ":;\n";
	}

protected:
	Wildcard<Token_label_name>* label;
};

class Branch : public Pattern
{
public:
	bool match(AST_statement* that)
	{
		cond = new Wildcard<Token_variable_name>;
		iftrue = new Wildcard<Token_label_name>;
		iffalse = new Wildcard<Token_label_name>;
		return that->match(new AST_branch(
			new AST_variable(NULL, cond, new List<AST_expr*>),
			iftrue, 
			iffalse
			));
	}

	void generate_code(Generate_C* gen)
	{
		cout
		<< "{\n"
		<< "zval* cond = index_ht(EG(active_symbol_table), "
		<< "\"" << *cond->value->value << "\", "
		<< cond->value->value->length() + 1 << ");\n"
		<< "if(zend_is_true(cond)) "
		<< "goto " << *iftrue->value->value << ";\n"
		<< "else "
		<< "goto " << *iffalse->value->value << ";\n"
		<< "}\n"
		;
	}

protected:
	Wildcard<Token_variable_name>* cond;
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
		cout << "goto " << *label->value->value << ";\n";
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

public:
	bool match(AST_statement* that)
	{
		lhs = new Wildcard<AST_variable>;
		agn = new AST_assignment(lhs, /* ignored */ false, rhs_pattern());
		return that->match(new AST_eval_expr(agn));
	}

	// Get the LHS from the hashtable 
	void index_lhs()
	{
		cout << "// Index LHS\n";
		index_st(LOCAL, "lhs", lhs->value);
	}

	// Make the LHS point to the RHS (copy-on-write)
	void copy_on_write()
	{
		cout << "// Copy-on-write\n";
		update_st(LOCAL, lhs->value, "rhs");
	}

	// Overwrite the LHS with the RHS
	void overwrite_lhs()
	{
		cout
		<< "// First, call the destructor to remove any data structures\n"
		<< "// associated with lhs that will now be overwritten\n"
		<< "zval_dtor(lhs);\n"
		<< "// Overwrite LHS\n"
		<< "lhs->value = rhs->value;\n"
		<< "lhs->type = rhs->type;\n"
		<< "zval_copy_ctor(lhs);\n"
		<< "// Delete RHS if it is a temp;\n"
		<< "if(rhs->refcount == 0)\n"
		<< "{\n"
		<< "// zval_ptr_dtor decrements refcount and deletes the zval when 0\n"
		<< "rhs->refcount = 1;\n"
		<< "zval_ptr_dtor(&rhs);\n"
		<< "}\n"
		;
	}

	// Separate the RHS (that is, make a copy *and update the hashtable*)
	// See "Separation anxiety" in the PHP book
	void separate_rhs()
	{
		Wildcard<AST_variable>* rhs;
		rhs = dynamic_cast<Wildcard<AST_variable>*>(agn->expr);

		// Make a copy of the RHS
		clone("rhs");

		if(rhs != NULL)
		{
			// First, make a copy, then update the hashtable
			update_st(LOCAL, rhs->value, "rhs");
		}
		else
		{
			// TODO 

			// I *think* the need for separation can only ever arise when the
			// RHS is a variable. However, the decision to run seperate_rhs
			// is based on runtime information, hence the runtime assert
		//	cout << "assert(0);\n";
		//	
		}
	}

	// Make the LHS reference the RHS (assume seperation has been done)
	void reference_rhs()
	{
		cout << "// Change-on-write\n";
		cout << "rhs->is_ref = 1;\n";
		update_st(LOCAL, lhs->value, "rhs");
	}

	void generate_code(Generate_C* gen)
	{
		// Open local scope and create a zval* to hold the RHS result
		cout << "{\n";
		cout << "zval* rhs;\n";

		// Generate code for the RHS
		generate_rhs();

		// Make a copy of the pointer to the RHS so that we can reduce its
		// refcount when we're done ("rhs" itself may be overwritten by a 
		// call to clone)
		cout << "zval* rhs_orig = rhs;\n";

		if(!agn->is_ref)
		{
			cout 
			<< "// Normal assignment\n"
			<< "zval* lhs;\n"
			;
			
			index_lhs();

			// if the LHS is_ref, then we must overwrite it. otherwise,
			// we make the LHS point to the RHS (copy-on-write)
			cout << "if(!lhs->is_ref) {\n";
			// If the RHS is_ref, we must first clone it
			cout << "if(rhs->is_ref) {\n";
			clone("rhs");
			cout << "}\n";
			copy_on_write();
			cout << "} else {\n";
			overwrite_lhs();
			cout << "}\n";
		}
		else
		{
			cout << "// Reference assignment\n";

			// For a reference assignment, the LHS is always updated to 
			// point to the RHS (even if the LHS is currently is_ref)
			// However, if the RHS is in a copy-on-write set (refcount > 1
			// but not is_ref), it must be seperated first

			cout << "if(rhs->refcount > 1 && !rhs->is_ref) {\n";
			separate_rhs();
			cout << "}\n";
			reference_rhs();
		}

		// Reduce refcount of RHS and garbage collect if necessary
		cout << "zval_ptr_dtor(&rhs_orig);\n";

		// close local scope
		cout << "}\n"; 	
	}

protected:
	AST_assignment* agn;
	Wildcard<AST_variable>* lhs;
};

/*
 * Assign_literal is another virtual class, and corresponds to assignming an
 * int, bool, etc. all of which inherit from Assign_literal.
 */

template<class T>
class Assign_literal : public Assignment
{
public:
	AST_expr* rhs_pattern()
	{
		rhs = new Wildcard<T>;
		return rhs;
	}

	void generate_rhs()
	{
		cout << "MAKE_STD_ZVAL(rhs);\n";
		init_rhs();
	}

	virtual void init_rhs() = 0;

protected:
	Wildcard<T>* rhs;
};

// TODO not sure if we want to use ->source_rep or ->value here; using
// zend_eval_string with source_rep currently to avoid losing precision
// Anyone who things he/she knows a better solution, be sure to run all tests!
class Assign_int : public Assign_literal<Token_int> 
{
	void init_rhs()
	{
		cout << "zend_eval_string(\"" << *rhs->value->source_rep << ";\", rhs, \"literal\" TSRMLS_CC);\n";
	}
};

class Assign_real : public Assign_literal<Token_real> 
{
	void init_rhs()
	{
		cout << "zend_eval_string(\"" << *rhs->value->source_rep << ";\", rhs, \"literal\" TSRMLS_CC);\n";
	}
};

class Assign_bool : public Assign_literal<Token_bool> 
{
	void init_rhs()
	{
		cout << "ZVAL_BOOL(rhs, " << rhs->value->value << ");\n";
	}
};

class Assign_null : public Assign_literal<Token_null> 
{
	void init_rhs()
	{
		cout << "ZVAL_NULL(rhs);\n";
	}
};

class Assign_string : public Assign_literal<Token_string> 
{
	void init_rhs()
	{
		cout 
		<< "ZVAL_STRINGL(rhs, " 
		<< "\"" << escape(rhs->value->value) << "\", "
		<< rhs->value->value->length() << ", 1);\n"
		;
	}

public:
	static string escape(String* s)
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
				ss << resetiosflags(cout.flags());
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
		index_st(LOCAL, "rhs", rhs->value);
		// We now have two references to the RHS
		cout << "rhs->refcount++;\n";
	}

protected:
	Wildcard<AST_variable>* rhs;
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
		global(rhs->value, true);
	}

protected:
	Wildcard<AST_variable_name>* rhs;
};

// TODO remove duplicate code
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

		cout
			<< "MAKE_STD_ZVAL (rhs);\n"
			<< "int result = zend_get_constant ( \"" << *name << "\""
			<< ", " << name->length() // exclude NULL-terminator
			<< ", rhs TSRMLS_CC);\n" // the book say _DC, but that doesnt compile
			;

		// check for missing constant
		cout 
			<< "if (!result)\n"
			<<	"ZVAL_STRINGL (rhs, \"" << *name << "\", " << name->length () << ", 1);\n";
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
			new Token_method_name(new String("eval")),
			new List<AST_actual_parameter*>(
				new AST_actual_parameter(false, eval_arg)
				)
			);
	}

	void generate_rhs()	
	{
		String* arg = operand(eval_arg->value);

		// cout << "debug_hash(EG(active_symbol_table));\n";

		cout
		<< "// Call eval\n"
		<< "{\n"
		<< "zval eval_arg;\n"
		<< "INIT_ZVAL(eval_arg);\n"
		<< "eval_arg = *index_ht(EG(active_symbol_table), "
		<< "\"" << *arg << "\", " << arg->length() + 1 << ");\n"
		<< "convert_to_string(&eval_arg);\n"
		// TODO this is very ugly
		// If the user wrote "return ..", we need to store the return value;
		// however, in that case, zend_eval_string will slap an extra
		// "return" onto the front of the string, so we must remove the 
		// "return" from the string the user wrote. If the user did not
		// write "return", he is not interested in the return value,
		// and we must pass NULL instead or rhs to avoid zend_eval_string
		// adding "return".
		<< "MAKE_STD_ZVAL(rhs);\n"
		<< "if(!strncmp(Z_STRVAL(eval_arg), \"return \", 7))"
		<< "{\n"
		<< "zend_eval_string(Z_STRVAL(eval_arg) + 7, rhs, "
		<< "\"eval'd code\" TSRMLS_CC);\n"
		<< "}\n"
		<< "else\n"
		<< "{\n"
		<< "zend_eval_string(Z_STRVAL(eval_arg), NULL, "
		<< "\"eval'd code\" TSRMLS_CC);\n"
		<< "ZVAL_NULL(rhs);\n"
		<< "}\n"
		<< "}\n"
		;
		
		// cout << "debug_hash(EG(active_symbol_table));\n";
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
		String* op = operand (exit_arg->value);

		// Fetch the parameter
		cout
			<< "// call exit ()\n{\n"
			<< "zval* arg = index_ht(EG(active_symbol_table), "
			<< "\"" << *op << "\", " << op->length() + 1 << ");\n"
			;

		// if its a long, return with exit code
		cout 
			<< "if (Z_TYPE_P (arg) == IS_LONG)\n"
			<< "exit (Z_LVAL_P (arg));\n"
			;

		// otherwise print the argument. Generally convert_to_string
		// should be avoided, since it destroys the data already
		// there, but we're about to exit () anyway.
		cout 
			<< "convert_to_string (arg);\n"
			<< "PHPWRITE (Z_STRVAL_P (arg), Z_STRLEN_P (arg));\n"
			<< "exit (0);\n}\n"
			;

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
		
		// cout << "debug_hash(EG(active_symbol_table));\n";

		// Variable function or ordinary function?
		Token_method_name* name;
		name = dynamic_cast<Token_method_name*>(rhs->value->method_name);

		if(name != NULL)
		{
			cout
			<< "// Create zval to hold function name\n"
			<< "zval function_name;\n"
			<< "INIT_PZVAL(&function_name);\n"
			<< "ZVAL_STRING(&function_name, "
			<< "\"" << *name->value << "\", "
			<< "0);\n"
			<< "zval* function_name_ptr;\n"
			<< "function_name_ptr = &function_name;\n"
			;
		}
		else
		{
			assert(0);
		}
	
		// TODO: better error reporting. Either use or duplicate PHP's
		// mechanism for error reporting. We might be safe sticking with
		// this for fatal errors, however, since they can'y be caught by
		// error handlers

		// Figure out which parameters need to be passed by reference
		cout
		<< "zend_function* signature;\n"
		<< "zend_is_callable_ex(function_name_ptr, 0, NULL, NULL, NULL, &signature, NULL TSRMLS_CC);\n"

		// check for non-existant functions
		<< "if (signature == NULL) {"
		<< "printf (\"\\nFatal error: Call to undefined function " << *name->value << "()"
		<< " in " << name->get_filename () 
		<< " on line " << name->get_line_number () 
		<< "\\n\"); "
		<< "exit (-1);"
		<<	"}\n"

		<< "zend_arg_info* arg_info = signature->common.arg_info;\n"
		<< "int by_ref[" << rhs->value->actual_parameters->size() << "];\n"
		;

		// TODO: Not 100% this is fully correct; in particular, 
		// pass_rest_by_reference does not seem to work.
		// cout << "printf(\"\\ncalling %s\\n\", signature->common.function_name);\n";
		for(
			i = rhs->value->actual_parameters->begin(), index = 0; 
			i != rhs->value->actual_parameters->end(); 
			i++, index++)
		{
			// cout << "printf(\"argument '%s' \", arg_info ? arg_info->name : \"(unknown)\");\n";
			
			cout
			<< "if(arg_info)\n"
			<< "{\n"
			<< "by_ref[" << index << "] = arg_info->pass_by_reference;\n"
			<< "arg_info++;\n"
			<< "}\n"
			<< "else\n"
			<< "{\n"
			<< "by_ref[" << index << "] = signature->common.pass_rest_by_reference;"
			<< "}\n"
			;
			
			if((*i)->is_ref) cout << "by_ref[" << index << "] = 1;";
			
			// cout << "printf(\"by reference: %d\\n\", by_ref[" << index << "]);\n";
		}

		cout 
		<< "// Setup array of arguments\n"
		<< "zval* args[" << rhs->value->actual_parameters->size() << "];\n"
		<< "zval** args_ind[" << rhs->value->actual_parameters->size() << "];\n"
		;

		for(
			i = rhs->value->actual_parameters->begin(), index = 0; 
			i != rhs->value->actual_parameters->end(); 
			i++, index++)
		{
			String* op = operand((*i)->expr);

			cout
			<< "{\n"
			<< "zval* arg = index_ht(EG(active_symbol_table), "
			<< "\"" << *op << "\", " << op->length() + 1 << ");\n"
			;
	
			// Separate argument if it is part of a copy-on-write set, 
			// and we are passing by reference
			cout << "if(arg->refcount > 1 && !arg->is_ref && by_ref[" << index << "]) {\n";
			AST_variable* var = dynamic_cast<AST_variable*>((*i)->expr);
			if(var != NULL)
			{
				clone("arg");
				update_st(LOCAL, var, "arg");
			}
			else
			{
				cout << "assert(0);\n";
			}
			cout << "}\n";

			// Clone argument if it is part of a change-on-write set, 
			// and we are *not* passing by reference
			cout << "if(arg->is_ref && !by_ref[" << index << "]) {\n";
			clone("arg");
			cout << "}\n";

			// We don't need to restore ->is_ref afterwards, because the 
			// called function will reduce the refcount of arg on return,
			// and will reset is_ref to 0 when refcount drops to 1.
			// If the refcount does not drop to 1 when the function returns,
			// but we did set is_ref to 1 here, that means that is_ref must
			// already have been 1 to start with (since if it had not, that
			// means that the variable would have been in a copy-on-write set,
			// and would have been seperated above).
			cout << "if(by_ref[" << index << "]) arg->is_ref = 1;\n";

			cout 
			<< "args[" << index << "] = arg;\n"
			<< "args_ind[" << index << "] = &args[" << index << "];\n"
			<< "}\n"
			;
		}
	
		cout
		<< "// Call the function\n"
		<< "int success;\n"	
		//<< "MAKE_STD_ZVAL(rhs);\n"
		<< "success = call_user_function_ex(EG(function_table), " 
		<< "NULL, function_name_ptr, &rhs, " 
		<< rhs->value->actual_parameters->size() << ", args_ind, "
		<< "0, NULL TSRMLS_CC);\n"
		<< "assert(success == SUCCESS);\n"
		;

		// Workaround a bug (feature?) of the Zend API that I don't know how to
		// solve otherwise. It seems that Zend resets the refcount and is_ref
		// fields of the return value after the function returns. That is okay
		// if the function does not return a reference (because it will have
		// created a fresh zval to hold the result), but obviously garbage
		// collector problems when the function returned a reference to an
		// existing zval. Hence, we increment the refcount here, and set is_ref
		// to true if the function signature declares the function to return a
		// reference. This causes memory leaks, but that's better than a
		// segfault :) (Note that this will cause memory leaks only when 
		// calling eval'd functions, because they do in fact return the proper
		// refcount, which will be one too many after we've incremented them).
		cout 
		<< "if(signature->common.return_reference)\n"
		<< "{\n"
		<< "rhs->refcount++;\n"
		<< "rhs->is_ref = 1;\n"
		<< "}"
		;
		
		// cout << "debug_hash(EG(active_symbol_table));\n";
	}

protected:
	Wildcard<AST_method_invocation>* rhs;
};

class Bin_op : public Assignment
{
public:
	AST_expr* rhs_pattern()
	{
		left = new Wildcard<Token_variable_name>;
		op = new Wildcard<Token_op>;
		right = new Wildcard<Token_variable_name>;

		return new AST_bin_op(
			new AST_variable(NULL, left, new List<AST_expr*>),
			op, 
			new AST_variable(NULL, right, new List<AST_expr*>)
			); 
	}

	void generate_rhs()
	{
		assert(
			op_functions.find(*op->value->value) != 
			op_functions.end());
		string op_fn = op_functions[*op->value->value]; 

		cout 
		<< "zval* left = index_ht(EG(active_symbol_table), "
		<< "\"" << *left->value->value << "\", "
		<< left->value->value->length() + 1 << ");\n"
		<< "zval* right = index_ht(EG(active_symbol_table), "
		<< "\"" << *right->value->value << "\", "
		<< right->value->value->length() + 1 << ");\n"
		<< "MAKE_STD_ZVAL(rhs);\n"
		;

		// some operators need the operands to be reversed (since we call the
		// opposite function). This is accounted for in the binops table.
		if(*op->value->value == ">" || *op->value->value == ">=")
			cout << op_fn << "(rhs, right, left TSRMLS_CC);\n";
		else
			cout << op_fn << "(rhs, left, right TSRMLS_CC);\n";
	}

protected:
	Wildcard<Token_variable_name>* left;
	Wildcard<Token_op>* op;
	Wildcard<Token_variable_name>* right;
};

class Unary_op : public Assignment
{
public:
	AST_expr* rhs_pattern()
	{
		op = new Wildcard<Token_op>;
		expr = new Wildcard<Token_variable_name>;

		return new AST_unary_op(op,
			new AST_variable(NULL, expr, new List<AST_expr*>)); 
	}

	void generate_rhs()
	{
		assert(
			op_functions.find(*op->value->value) != 
			op_functions.end());
		string op_fn = op_functions[*op->value->value]; 

		cout 
		<< "zval* expr = index_ht(EG(active_symbol_table), "
		<< "\"" << *expr->value->value << "\", "
		<< expr->value->value->length() + 1 << ");\n"
		<< "MAKE_STD_ZVAL(rhs);\n"
		<< op_fn << "(rhs, expr TSRMLS_CC);\n"
		;
	}

protected:
	Wildcard<Token_op>* op;
	Wildcard<Token_variable_name>* expr;
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
		String* op = operand(expr->value);
			
		cout 
		<< "{\n"
		<< "zval* rhs = index_ht(EG(active_symbol_table), "
		<< "\"" << *op << "\", " << op->length() + 1 << ");\n"
		;

		if(!gen->return_by_reference)
		{
			cout 
			<< "return_value->value = rhs->value;\n"
			<< "return_value->type = rhs->type;\n"
			<< "zval_copy_ctor(return_value);\n"
			;
		}
		else
		{
			// TODO separate if necessary
			// (May not be necessary due to the shredder)

			cout
			<< "zval_ptr_dtor(return_value_ptr);\n"
			<< "rhs->is_ref = 1;\n"
			<< "rhs->refcount++;\n"
			<< "*return_value_ptr = rhs;\n"
			;
//		cout << "printf(\"<<< rhs (%08X) %08X %d %d >>>\\n\", return_value_ptr, rhs, rhs->refcount, rhs->is_ref);\n";

		}

		cout 
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
		// TODO: deal with object indexing
		assert(var->value->target == NULL);

		Token_variable_name* name;
		name = dynamic_cast<Token_variable_name*>(var->value->variable_name);

		if(name != NULL)
		{
			if(var->value->array_indices->size() == 0)
			{
				cout
				<< "zend_hash_del(EG(active_symbol_table), "
				<< "\"" << *name->value << "\", "
				<< name->value->length() + 1 << ");"
				;
			}
			else 
			{
				assert(var->value->array_indices->size() == 1);
				String* ind = operand(var->value->array_indices->front());

				cout
				<< "{\n"
				<< "zval* arr = index_ht(EG(active_symbol_table), "
				<< "\"" << *name->value << "\", " 
				<< name->value->length() + 1 << ");"
				<< "HashTable* ht = extract_ht(arr);"
				<< "zval* ind = index_ht(EG(active_symbol_table), "
				<< "\"" << *ind << "\", " << ind->length() + 1 << ");"
				// Numeric index?
				<< "if(Z_TYPE_P(ind) == IS_LONG)\n"
				<< "{\n"
				<< "zend_hash_index_del(ht, Z_LVAL_P(ind));\n"
				<< "}\n"
				// String index 
				<< "else\n"
				<< "{\n"
				// TODO Code duplication
				<< "zval* string_index;\n"
				<< "MAKE_STD_ZVAL(string_index);\n"
				<< "string_index->value = ind->value;\n"
				<< "string_index->type = ind->type;\n"
				<< "zval_copy_ctor(string_index);\n"
				<< "convert_to_string(string_index);\n"
				<< "zend_hash_del(ht, Z_STRVAL_P(string_index), Z_STRLEN_P(string_index) + 1);\n"
				<< "zval_ptr_dtor(&string_index);\n"
				<< "}\n"
				<< "}\n"
				;
			}
		}
		else
		{
			// Variable variable
			// TODO
			assert(0);
		}
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
	Pattern* patterns[] = 
	{
		new Method_definition()
	,	new Assign_string()
	,	new Assign_int()
	,	new Assign_null()
	,	new Assign_bool()
	,	new Assign_real()
	,	new Assign_constant ()
	,	new Copy()
	,	new Global()
	,	new Eval()
	,	new Exit()
	,	new Method_invocation()
	,	new Bin_op()
	,	new Unary_op()
	,	new Label()
	,	new Branch()
	,	new Goto()
	,	new Return()
	,	new Unset()
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
	// Some common functions
	cout 
	<< "#include \"php.h\"\n"
	// Index a hashtable
	<< "zval* index_ht(HashTable* ht, char* key, int len)\n" 
	<< "{\n"
	<< "zval** zvpp;\n"
	<< "if(zend_hash_find(ht, key, len, (void**)&zvpp) != SUCCESS)\n"
	<< "{\n"
	<< "zval* zvp;\n"
	<< "ALLOC_INIT_ZVAL(zvp);\n"
	<< "zend_hash_add(ht, key, len, &zvp, sizeof(zval*), NULL);\n"
	<< "zend_hash_find(ht, key, len, (void**)&zvpp);\n"
	<< "}\n"
	<< "return *zvpp;\n"
	<< "}\n"

	// Index a hashtable using a zval*
	<< "zval* index_ht_zval(HashTable* ht, zval* ind)\n"
	<< "{\n"
	<< "zval* result;\n"
	// Numeric index
	<< "if(Z_TYPE_P(ind) == IS_LONG)\n"
	<< "{\n"
	<< "zval** zvpp;\n"
	<< "if(zend_hash_index_find(ht, Z_LVAL_P(ind), (void**)&zvpp) != SUCCESS)\n"
	<< "{\n"
	<< "zval* zvp;\n"
	<< "ALLOC_INIT_ZVAL(zvp);\n"
	<< "zend_hash_index_update(ht, Z_LVAL_P(ind), &zvp, sizeof(zval*), NULL);\n"
	<< "zend_hash_index_find(ht, Z_LVAL_P(ind), (void**)&zvpp);\n"
	<< "}\n"
	<< "result = *zvpp;\n"
	<< "}\n"
	// String index. 
	<< "else\n"
	<< "{\n"
	<< "zval* string_index;\n"
	<< "MAKE_STD_ZVAL(string_index);\n"
	<< "string_index->value = ind->value;\n"
	<< "string_index->type = ind->type;\n"
	<< "zval_copy_ctor(string_index);\n"
	<< "convert_to_string(string_index);\n"
	<< "result = index_ht(ht, Z_STRVAL_P(string_index), Z_STRLEN_P(string_index) + 1);\n"
	<< "zval_ptr_dtor(&string_index);\n"
	<< "}\n"
	<< "return result;\n"
	<< "}\n"

	// Extract the hashtable from a hash-valued zval
	<< "HashTable* extract_ht(zval* arr)\n"
	<< "{\n"
	<< "if(Z_TYPE_P(arr) == IS_NULL)\n"
	<< "array_init(arr);\n"
	<< "else if(Z_TYPE_P(arr) != IS_ARRAY)\n"
	// TODO: proper error message
	<< "assert(0);\n"
	<< "return Z_ARRVAL_P(arr);\n"
	<< "}\n"
	
	// Update a hashtable using a zval* index
	<< "void update_ht(HashTable* ht, zval* ind, zval* val)\n"
	<< "{\n"
	<< "if(Z_TYPE_P(ind) == IS_LONG)\n" 
	<< "{\n"
	// Remove the old value from the hashtable (this will
	// automatically reduce its refcount)
	<< "zend_hash_index_del(ht, Z_LVAL_P(ind));\n"
	// Add the new value to the hashtable
	<< "zend_hash_index_update(ht, Z_LVAL_P(ind), "
	<< "&val, sizeof(zval*), NULL);\n"
	<< "}\n"
	// String index.
	<< "else\n"
	<< "{\n"
	// Convert to the argument to a string 
	// TODO: if we know it's a string, we don't need to convert
	<< "zval* string_index;\n"
	<< "MAKE_STD_ZVAL(string_index);\n"
	<< "string_index->value = ind->value;\n"
	<< "string_index->type = ind->type;\n"
	<< "zval_copy_ctor(string_index);\n"
	<< "convert_to_string(string_index);\n"
	// Remove the old value from the hashtable
	<< "zend_hash_del(ht, Z_STRVAL_P(string_index), Z_STRLEN_P(string_index) + 1);\n"
	// Add the new value to the hashtable
	<< "zend_hash_add(ht, Z_STRVAL_P(string_index), Z_STRLEN_P(string_index) + 1, &val, sizeof(zval*), NULL);\n"
	<< "zval_ptr_dtor(&string_index);\n"
	<< "}\n"
	<< "}\n"
	
	<< "void debug_hash(HashTable* ht)\n"
	<< "{\n"
	<< "printf(\"\\nHASH\\n\");\n"
	<< "for(\n"
	<< "	zend_hash_internal_pointer_reset(ht);\n"
	<< "	zend_hash_has_more_elements(ht) == SUCCESS;\n"
	<< "	zend_hash_move_forward(ht)\n"
	<< "	)\n"
	<< "{\n"
	<< "	char *key;\n"
	<< "	unsigned keylen;\n"
	<< "	unsigned long idx;\n"
	<< "	int type;\n"
	<< "	zval** ppzval;\n"
	<< "	zval tmpcopy;\n"
	<< "\n"
	<< "	type = zend_hash_get_current_key_ex(ht, &key, &keylen, &idx, 0, NULL);\n"
	<< "	zend_hash_get_current_data(ht, (void**)&ppzval);\n"
	<< "\n"
	<< "	tmpcopy = **ppzval;\n"
	<< "	zval_copy_ctor(&tmpcopy);\n"
	<< "	INIT_PZVAL(&tmpcopy);\n"
	<< "	convert_to_string(&tmpcopy);\n"
	<< "\n"
	<< "	if(type == HASH_KEY_IS_STRING)\n"
	<< "	{\n"
	<< "		printf(key);\n"	
	<< "	}\n"
	<< "	else\n"
	<< "	{\n"
	<< "		printf(\"%d\", idx);\n"	
	<< "	}\n"
	<< "\n"
	<< "	printf(\": addr = %08lX, refcount = %d, is_ref = %d (%s)\\n\", *ppzval, (*ppzval)->refcount, (*ppzval)->is_ref, Z_STRVAL(tmpcopy));\n"
	<< "\n"
	<< "	zval_dtor(&tmpcopy);\n"
	<< "}\n"
	<< "printf(\"END HASH\\n\");\n"
	<< "}"
	;
}

void Generate_C::post_php_script(AST_php_script* in)
{
	List<AST_signature*>::const_iterator i;

	cout << "// ArgInfo structures (necessary to support compile time pass-by-reference)\n";
	for(i = methods->begin(); i != methods->end(); i++)
	{
		String* name = (*i)->method_name->value;

		// TODO: pass by reference only works for PHP>5.1.0. Do we care?
		cout 
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
			cout 
			<< "ZEND_ARG_INFO("
			<< ((*j)->is_ref ? "1" : "0")
			<< ", \"" << *(*j)->variable_name->value << "\")\n"; 
		}

		cout << "ZEND_END_ARG_INFO()\n";
	}

	cout 
		<< "// Register all functions with PHP\n"
		<< "static function_entry " << *extension_name << "_functions[] = {\n"
		;
	for(i = methods->begin(); i != methods->end(); i++)
	{
		String* name = (*i)->method_name->value;
		cout << "PHP_FE(" << *name << ", " << *name << "_arg_info)\n";
	}

	cout << "{ NULL, NULL, NULL }\n";
	cout << "};\n";

	cout
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
		cout << "ZEND_GET_MODULE(" << *extension_name << ")\n";
	}
	else
	{
		cout << "#include <sapi/embed/php_embed.h>\n";
		cout << "#include <signal.h>\n\n";
	
		cout <<
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
	
		cout << 
		"\n"
		"int\n"
		"main (int argc, char* argv[])\n"
		"{\n"
		"    signal(SIGABRT, sighandler);\n"
		"    signal(SIGSEGV, sighandler);\n"
		"\n"
		"    PHP_EMBED_START_BLOCK (argc, argv)\n"
		"\n"
		"    // load the compiled extension\n"
		"    zend_startup_module (&" << *extension_name << "_module_entry);\n"
		"\n"
		"    zval main_name;\n"
		"    ZVAL_STRING (&main_name, \"__MAIN__\", NULL);\n"
		"\n"
		"    zval retval;\n"
		"\n"
		"    // call __MAIN__\n"
		"    int success = call_user_function( \n"
		"				     EG (function_table),\n"
		"				     NULL,\n"
		"				     &main_name,\n"
		"				     &retval,\n"
		"				     0,\n"
		"				     NULL\n"
		"				     TSRMLS_CC);\n"
		"	\n"
		"   PHP_EMBED_END_BLOCK()"
		"\n"
		"  return 0;\n"
		"}\n" ;
	}
}

/*
 * Bookkeeping 
 */

Generate_C::Generate_C(stringstream& os) : os (os)
{
	methods = new List<AST_signature*>;
	name = new String ("generate-c");
}
