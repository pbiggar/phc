/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate C code
 *
 * Currently, the C code is generated directly from the AST; once we have an
 * IR, the C code will be generated from the IR instead.
 */

#include "Generate_C.h"
#include "process_ast/XML_unparser.h"
#include "lib/List.h"
#include "process_ast/PHP_unparser.h"

/*
 * Map of the Zend functions that implement the binary operators
 * The map also contains entries for ++ and --, which are identical to the
 * entries for + and -, but obviously need to be invoked slightly differently.
 */

static class Bin_op_functions : public map<string,string>
{
public:
	Bin_op_functions() : map<string,string>()
	{
		(*this)["+"] = "add_function";	
		(*this)["-"] = "sub_function";	
		(*this)["*"] = "mul_function";	
		(*this)["/"] = "div_function";	
		(*this)["%"] = "mod_function";	
		(*this)["xor"] = "boolean_xor_function";
		(*this)["!"] = "boolean_not_function";
		(*this)["not"] = "boolean_not_function";
		(*this)["~"] = "bitwise_not_function";
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
		(*this)[">="] = "is_smaller_function"; // This one looks wrong, but we reverse the operands to make this
		(*this)[">"] = "is_smaller_or_equal_function"; // This one too
		(*this)["++"] = "add_function";
		(*this)["--"] = "sub_function";
	}
} bin_op_functions;

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
		signature = pattern->value->signature;
		gen->methods->push_back(signature->method_name->value);

		method_entry();	
		gen->visit_statement_list(pattern->value->statements);
		method_exit();
	}

protected:
	Wildcard<AST_method>* pattern;
	AST_signature* signature;

protected:
	void method_entry()
	{
		cout
		// Function header
		<< "PHP_FUNCTION(" << *signature->method_name->value << ")\n"
		<< "{\n"
		/**/
		<< "// Setup locals array\n"
		<< "HashTable* locals;\n"
		<< "ALLOC_HASHTABLE(locals);\n"
		<< "zend_hash_init(locals, 64, NULL, ZVAL_PTR_DTOR, 0);\n"
		/**/
		<< "// Function body\n"
		;
	}

	void method_exit()
	{
		cout
		<< "// Destroy locals array\n"
		<< "zend_hash_destroy(locals);\n"
		<< "FREE_HASHTABLE(locals);\n"
		<< "}\n"
		;
	}
};

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
		return that->match(
			new AST_eval_expr(new AST_assignment(
				lhs,
				/* ignored */ false,
				rhs_pattern()
			)));
	}

	void generate_code(Generate_C* gen)
	{
		// Open local scope and create a zval* to hold the RHS result
		cout << "{\n";
		cout << "zval* rhs;\n";

		// Generate code for the RHS
		generate_rhs();

		// Variable variable or ordinary variable?
		Token_variable_name* name;
		name = dynamic_cast<Token_variable_name*>(lhs->value->variable_name);

		// Ordinary variable
		if(name != NULL)
		{
			cout 
			// Remove theold value from the hashtable
			// (reducing its refcount)
			<< "zend_hash_del(locals, "
			<< "\"" << *name->value << "\", "
			<< name->value->length() << ");\n"
			// Add the new value to the hashtable
			<< "zend_hash_add(locals, "
			<< "\"" << *name->value << "\", "
			<< name->value->length() << ", "
			<< "&rhs, sizeof(zval*), NULL);\n"
			;
		}
		else
		{
			assert(0);
		}

		cout << "}\n"; 				// close local scope
	}

protected:
	Wildcard<AST_variable>* lhs;
};

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

class Assign_int : public Assign_literal<Token_int> 
{
	void init_rhs()
	{
		cout << "ZVAL_LONG(rhs, " << rhs->value->value << ");\n"; 
	}
};

class Assign_real : public Assign_literal<Token_real> 
{
	void init_rhs()
	{
		cout << "ZVAL_DOUBLE(rhs, " << rhs->value->value << ");\n";
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
		<< "ZVAL_STRING(rhs, " 
		<< "\"" << escape(rhs->value->value) << "\", "
		<< "1);\n"
		;
	}

public:
	static string escape(String* s)
	{
		stringstream ss;
	
		String::const_iterator i;
		for(i = s->begin(); i != s->end(); i++)
		{
			if(*i == '"')
			{
				ss << "\\\"";
			}
			else if(*i >= 32 && *i < 127)
			{
				ss << *i;
			}
			else
			{
				ss << "\\x" << setw(2) << setfill('0') << hex << uppercase << (unsigned long int)(unsigned char) *i;
				ss << resetiosflags(cout.flags());
			}
		}
	
		return ss.str();
	}
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
			;
		}
		else
		{
			assert(0);
		}
		
		cout
		<< "zval* function_name_ptr;\n"
		<< "function_name_ptr = &function_name;\n"
		;

		cout 
		<< "// Setup array of arguments\n"
		<< "zval* args[" << rhs->value->actual_parameters->size() << "];\n"
		;

		List<AST_actual_parameter*>::const_iterator i;
		unsigned index = 0;
		for(
			i = rhs->value->actual_parameters->begin(); 
			i != rhs->value->actual_parameters->end(); 
			i++, index++)
		{
			// After the shredder, all arguments must be simple variables
			AST_variable* arg;
			Token_variable_name* arg_name;
			arg = dynamic_cast<AST_variable*>((*i)->expr);
			arg_name = dynamic_cast<Token_variable_name*>(arg->variable_name);

			cout
			<< "{\n"
			<< "zval** arg;\n"
			<< "zend_hash_find(locals, "
			<< "\"" << *arg_name->value << "\", "
			<< arg_name->value->length() << ", "
			<< "(void**)&arg);\n"
			<< "args[" << index << "] = *arg;\n"
			<< "}\n"
			;
		}
	
		cout
		<< "// Call the function\n"
		<< "int success;\n"	
		<< "MAKE_STD_ZVAL(rhs);\n"
		<< "success = call_user_function(EG(function_table), " 
		<< "NULL, function_name_ptr, rhs, " 
		<< rhs->value->actual_parameters->size() << ", args TSRMLS_CC);\n"
		<< "assert(success == SUCCESS);\n"
		;
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
			bin_op_functions.find(*op->value->value) != 
			bin_op_functions.end());
		string op_fn = bin_op_functions[*op->value->value]; 

		cout 
		<< "zval* left;\n"
		<< "zval* right;\n"
		// Find left argument
		<< "{\n"
		<< "zval** arg;\n"
		<< "zend_hash_find(locals, "
		<< "\"" << *left->value->value << "\", "
		<< left->value->value->length() << ", "
		<< "(void**)&arg);\n"
		<< "left = *arg;\n"
		<< "}\n"
		// Find right argument
		<< "{\n"
		<< "zval** arg;\n"
		<< "zend_hash_find(locals, "
		<< "\"" << *right->value->value << "\", "
		<< right->value->value->length() << ", "
		<< "(void**)&arg);\n"
		<< "right = *arg;\n"
		<< "}\n"
		// Execute the binary operator
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
	,	new Method_invocation()
	,	new Bin_op()
	};

	bool matched = false;
	for(unsigned i = 0; i < sizeof(patterns) / sizeof(Pattern*); i++)
	{
		if(patterns[i]->match(in))
		{
			patterns[i]->generate_code(this);
			matched = true;
		}
	}

	if(not matched)
	{
		PHP_unparser pup;
		cout << "// could not generate code for ";
		in->visit(&pup);
	}
}

void Generate_C::pre_php_script(AST_php_script* in)
{
	cout << "#include \"php.h\"\n";
}

void Generate_C::post_php_script(AST_php_script* in)
{
	cout 
		<< "// Register all functions with PHP\n"
		<< "static function_entry " << *extension_name << "_functions[] = {\n"
		;

	List<String*>::const_iterator i;
	for(i = methods->begin(); i != methods->end(); i++)
		cout << "PHP_FE(" << **i << ", NULL)\n";

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
		"    // call %MAIN%::run\n"
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

Generate_C::Generate_C(String* extension_name)
{
	if(extension_name != NULL)
	{
		this->extension_name = extension_name;
		is_extension = true;
	}
	else
	{
		this->extension_name = new String("app");
		is_extension = false;
	}

	methods = new List<String*>;
}

#ifdef OBSOLETE

/*
 * Variabes set by the code generator
 *
 * Most nodes synthesize up the location of the result in LOC, which must be
 * a zval* (not a zval, nor a zval**). Variables also synthesize up the 
 * corresponding zval*; for example $a[x] indexes ACTIVE_SYMBOL_TABLE to find
 * $a, then indexes $a to find x, and then synthesizes up x. 
 * 
 * However, in some cases the (last) hash table should not be indexed, but
 * instead the name of the hashtable and the name of the index should be
 * synthesized up instead (this applies to lvalues in reference assignments,
 * and to the arguments of unset, for example). In that case, the name of the
 * hash table is synthesized up in HASH, and the name of the index in
 * STRIDX/STRLEN for string indexes, or ZVALIDX for zval* indexes. In the $a[x]
 * example, ACTIVE_SYMBOL_TABLE is indexed to find a, and a is then synthesized
 * up as HASH, STRIDX will be "x", and STRLEN will be sizeof("x") = 2.
 * The cases where this is appropriate are marked IS_ADDR by Prep. 
 *
 * HASH    HashTable*
 * STRIDX  char*
 * STRLEN  int
 * ZVALIDX zval* 
 */

#define LOC "phc.generate_c.location"
#define IS_ADDR "phc.generate_c.is_addr"
#define HASH "phc.generate_c.hash"
#define STRIDX "phc.generate_c.stridx"
#define STRLEN "phc.generate_c.strlen"
#define ZVALIDX "phc.generate_c.zvalidx"

static List<String*> methods;		// list of all methods compiled
static List<String*> eofn_labels;	// end of function labels


/* TODO we can support break's with computed gotos :) */

/*
 * Indexing and updating hashes
 */

// Index the hash (change from STRIDX/ZVALIDX to LOC)
void Generate_C::index_hash(AST_variable* var)
{
	String* indexed = fresh("indexed");
	var->attrs->set(LOC, deref(indexed));

	cout << "// Index the hash table..\n";
	cout << "zval **" << *indexed << ";\n";

	if(var->attrs->has(STRIDX))
	{
		String* hash = var->attrs->get_string(HASH);
		String* stridx = var->attrs->get_string(STRIDX);
		int strlen = var->attrs->get_integer(STRLEN)->value();

		cout 
		<< "// ..using a string index\n"
		<< "if(zend_hash_find(" << *hash << ", " 
		<< *stridx << ", " << strlen << ", " 
		<< "(void**)&" << *indexed << ") != SUCCESS)\n"
		<< "{\n"
		<< "zval* new_var;\n"
		<< "ALLOC_INIT_ZVAL(new_var);\n"
		<< "zend_hash_add(" << *hash << ", " 
		<< *stridx << ", " << strlen << ", "
		<< "&new_var, sizeof(zval*), NULL);\n"
		<< "// This must now succeed\n"
		<< "zend_hash_find(" << *hash << ", " 
		<< *stridx << ", " << strlen << ", "
		<< "(void**)&" << *indexed << ");\n"
		<< "}\n";
	}
	else
	{
		String* hash = var->attrs->get_string(HASH);
		String* zvalidx = var->attrs->get_string(ZVALIDX);

		cout
		<< "// ..using a numeric zval\n"
		<< "if(Z_TYPE_P(" << *zvalidx << ") == IS_LONG)\n"
		<< "{\n"
		<< "if(zend_hash_index_find(" << *hash << ", " 
		<< "Z_LVAL_P(" << *zvalidx << "), "
		<< "(void**)&" << *indexed << ") != SUCCESS)\n"
		<< "{\n"
		<< "zval* new_var;\n"
		<< "ALLOC_INIT_ZVAL(new_var);\n"
		<< "zend_hash_index_update(" << *hash << ", " 
		<< "Z_LVAL_P(" << *zvalidx << "), " 
		<< "&new_var, sizeof(zval*), NULL);\n" 
		<< "// This must now succeed\n"
		<< "zend_hash_index_find(" << *hash << ", " 
		<< "Z_LVAL_P(" << *zvalidx << "), " 
		<< "(void**)&" << *indexed << ");\n"
		<< "}\n"
		<< "}\n"
	
		/**/
		<< "// ..or using a string zval\n"
		<< "else\n"
		<< "{\n"
		<< "zval string_index;\n"
		<< "string_index = *" << *zvalidx << ";"
		<< "convert_to_string(&string_index);\n"
		<< "if(zend_hash_find(" << *hash << ", "
		<< "Z_STRVAL(string_index), Z_STRLEN(string_index) + 1, "
		<< "(void**)&" << *indexed << ") != SUCCESS)\n"
		<< "{\n"
		<< "zval* new_var;\n"
		<< "ALLOC_INIT_ZVAL(new_var);\n"
		<< "zend_hash_add(" << *hash << ", " 
		<< "Z_STRVAL(string_index), Z_STRLEN(string_index) + 1, "
		<< "&new_var, sizeof(zval*), NULL);\n"
		<< "// This must now succeed\n"
		<< "zend_hash_find(" << *hash << ", "
		<< "Z_STRVAL(string_index), Z_STRLEN(string_index) + 1, "
		<< "(void**)&" << *indexed << ");\n"
		<< "}\n"
		<< "}\n";
	}
}

// Separate (create a copy) 
void Generate_C::separate(AST_variable* in)
{
	String* separated = fresh("separated");
	String* loc = in->attrs->get_string(LOC);

	cout 
	<< "// separate if necessary\n"
	<< "zval* " << *separated << ";\n"
	<< "if("
	<< "(" << *loc << ")->refcount > 1 && " << "!(" << *loc << ")->is_ref)"
	<< "{\n"
	<< "MAKE_STD_ZVAL(" << *separated << ");\n"
	<< "*" << *separated << " = *" << *in->attrs->get_string(LOC) << ";\n"
	<< "zval_copy_ctor(" << *separated << ");\n"
	<< *separated << "->refcount = 1;\n"
	<< *separated << "->is_ref = 0;\n";
	
	cout
	<< "// Remove the old variable from the hashtable (decreasing its\n" 
	<< "// refcount), and insert the new separated variable\n";
	update_hash(dynamic_cast<AST_variable*>(in), separated);

	cout
	<< "}\n"
	<< "else\n"
	<< "{\n"
	<< *separated << " = " << *in->attrs->get_string(LOC) << ";\n"
	<< "}\n";

	in->attrs->set(LOC, separated);
}

// Replace the variable in the hash table with the new value (must be a zval*)	
void Generate_C::update_hash(AST_variable* var, String* val)
{
	if(var->attrs->has(STRIDX))
	{
		// Remove the old value from the hashtable (this will
		// automatically reduce its refcount)
		cout << "zend_hash_del(" ;
		cout << *var->attrs->get_string(HASH) << ", ";
		cout << *var->attrs->get_string(STRIDX) << ", ";
		cout << var->attrs->get_integer(STRLEN)->value() << ");\n";
		// Add the new value to the hashtable
		cout << "zend_hash_add(" ;
		cout << *var->attrs->get_string(HASH) << ", ";
		cout << *var->attrs->get_string(STRIDX) << ", ";
		cout << var->attrs->get_integer(STRLEN)->value() << ", ";
		cout << "&" << *val << ", ";
		cout << "sizeof(zval*), NULL);\n";;
	}
	else
	{
		assert(var->attrs->has(ZVALIDX));

		// Numeric index? 
		cout << "if(Z_TYPE_P(" ;
		cout << *var->attrs->get_string(ZVALIDX) ;
		cout << ") == IS_LONG)\n" ;
		cout << "{\n";
		// Remove the old value from the hashtable (this will
		// automatically reduce its refcount)
		cout << "zend_hash_index_del(";
		cout << *var->attrs->get_string(HASH) << ", ";
		cout << "Z_LVAL_P(" << *var->attrs->get_string(ZVALIDX) ;
		cout << "));\n";
		// Add the new value to the hashtable
		cout << "zend_hash_index_update(" ;
		cout << *var->attrs->get_string(HASH) << ", ";
		cout << "Z_LVAL_P(" << *var->attrs->get_string(ZVALIDX) << "), ";
		cout << "&" << *val << ", ";
		cout << "sizeof(zval*), NULL);\n";
		cout << "}\n";
		cout << "else\n";
		cout << "{\n";
		cout << "// TODO\n";
		cout << "}\n";
	}
}


/*
 * Tokens
 */

void Generate_C::post_string(Token_string* in)
{
	String* s = fresh("string");

	cout << "zval* " << *s << ";\n";
	cout << "MAKE_STD_ZVAL(" << *s << ");\n";
	cout << "ZVAL_STRING(" << *s << ", \"";
	escape(in->value);
	cout << "\", 1);\n";

	in->attrs->set(LOC, s);
	cout << "zend_hash_next_index_insert(temps, &" << *s << ", sizeof(zval*), NULL);\n";
}

void Generate_C::post_int(Token_int* in)
{
	String* i = fresh("int");

	cout << "zval* " << *i << ";\n";
	cout << "MAKE_STD_ZVAL(" << *i << ");\n";
	cout << "ZVAL_LONG(" << *i << ", " << in->value << ");\n";

	in->attrs->set(LOC, i);
	cout << "zend_hash_next_index_insert(temps, &" << *i << ", sizeof(zval*), NULL);\n";
}

void Generate_C::post_bool(Token_bool* in)
{
	String* b = fresh("bool");
	
	cout << "zval* " << *b << ";\n";
	cout << "MAKE_STD_ZVAL(" << *b << ");\n";
	
	if(in->value)
		cout << "ZVAL_TRUE(" << *b << ");";
	else
		cout << "ZVAL_FALSE(" << *b << ");";
	
	in->attrs->set(LOC, b);
	cout << "zend_hash_next_index_insert(temps, &" << *b << ", sizeof(zval*), NULL);\n";
}

void Generate_C::post_null(Token_null* in)
{
	String* n = fresh("null");
	
	cout << "zval*" << *n << ";\n";
	cout << "ALLOC_INIT_ZVAL(" << *n << ");\n";

	in->attrs->set(LOC, n);
	// TODO: should we up the refcount when interesting into the temps array?
	cout << "zend_hash_next_index_insert(temps, &" << *n << ", sizeof(zval*), NULL);\n";
}

/*
 * Method invocation
 */

void Generate_C::post_method_invocation(AST_method_invocation* in)
{
	// Special case for eval
	AST_method_invocation* pattern;
	Wildcard<AST_expr>* eval_arg = new Wildcard<AST_expr>;

	pattern = new AST_method_invocation(
		new Token_class_name(new String("%STDLIB%")),
		new Token_method_name(new String("eval")),
		new List<AST_actual_parameter*>(
			new AST_actual_parameter(false, eval_arg)
			)
		);

	if(in->match(pattern))
	{
		String* eval_retval = fresh("eval_retval");

		cout << "zval* " << *eval_retval << ";\n";
		cout << "MAKE_STD_ZVAL(" << *eval_retval << ");\n";
		cout << "zend_hash_next_index_insert(temps, &" << *eval_retval << ", sizeof(zval*), NULL);\n";
		cout << "{\n";
		cout << "zval eval_arg;\n";
		cout << "eval_arg = *" << *eval_arg->value->attrs->get_string(LOC) << ";\n";
		cout << "convert_to_string(&eval_arg);\n";
		cout << "zend_eval_string(Z_STRVAL(eval_arg), " << *eval_retval << ", ";
		cout << "\"" << *eval_arg->value->get_filename() << " eval'd code\" TSRMLS_CC);\n" ;
		cout << "}\n";;

		in->attrs->set(LOC, eval_retval);
		return;
	}

	// TODO: check target

	String* ret_val = fresh("ret_val");
	cout << "zval " << *ret_val << ";\n";

	cout << "{\n";

	/**/
	cout << "// Create a zval to contain the name of the function\n";

	Token_method_name* method_name = dynamic_cast<Token_method_name*>(in->method_name);
	if(method_name != NULL)
	{
		cout << "zval function_name_str;\n";
		cout << "INIT_PZVAL(&function_name_str);\n";
		cout << "ZVAL_STRING(&function_name_str, \"" << *method_name->value << "\", 0);\n";
		cout << "zval* function_name = &function_name_str;\n";
	}
	else
	{
		cout << "zval* function_name = " << *in->method_name->attrs->get_string(LOC) << "\n";
	}

	/**/
	cout << "// Setup array of arguments\n";
	cout << "zval* args[" << in->actual_parameters->size() << "];\n";

	List<AST_actual_parameter*>::const_iterator i;
	unsigned index = 0;
	for(i = in->actual_parameters->begin(); i != in->actual_parameters->end(); i++)
	{
		cout 
		<< "args[" << index << "] = " 
		<< *(*i)->expr->attrs->get_string(LOC) << ";\n";
		
		if(!(*i)->is_ref)
		{
			cout
			<< "// Clone function argument if necessary\n"
			<< "if(args[" << index << "]->is_ref)\n"
			<< "{\n"
			<< "zval* clone;\n"
			<< "MAKE_STD_ZVAL(clone);\n"
			<< "*clone = *args[" << index << "];\n" 
			<< "zval_copy_ctor(clone);\n"
			<< "clone->is_ref = 0;\n"
			<< "// refcount set to 0; call_user_function will add 1\n"
			<< "clone->refcount = 0;\n"
			<< "args[" << index << "] = clone;\n"
			<< "}\n";
		}
		else
		{
			// TODO: deal with passing by reference
		}

		index++;
	}

	/**/
	cout << "// Call the function\n";
	cout << "int success;\n";	
	cout << "success = call_user_function(EG(function_table), NULL, function_name, &" << *ret_val << ", " << in->actual_parameters->size() << ", args TSRMLS_CC);\n";
	cout << "assert(success == SUCCESS);\n";

	cout << "}\n";

	in->attrs->set(LOC, addr(ret_val));	
}

/*
 * Simple statements
 */

void Generate_C::post_return(AST_return* in)
{
	cout << "*return_value = *" << *in->expr->attrs->get_string(LOC) << ";\n";
	cout << "zval_copy_ctor(return_value);\n";
	cout << "goto " << *eofn_labels.back() << ";\n";
}

void Generate_C::children_bin_op(AST_bin_op* in)
{
	String* binop_result = fresh("binop_result");
	cout << "zval* " << *binop_result << ";\n";

	/**/
	cout << "// Evaluate left operand of " << *in->op->value << "\n";
	visit_expr(in->left);

	if(*in->op->value == "&&" || *in->op->value == "and")
	{
		String* after_binop = fresh("after_binop");
		// TODO: do we need to clone before assigning to binop_result?
		cout << *binop_result << " = " << *in->left->attrs->get_string(LOC) << ";\n";

		cout << "if(!zend_is_true(" << *in->left->attrs->get_string(LOC) << ")) goto " << *after_binop << ";\n";
		
		/**/
		cout << "// Evaluate right operand of " << *in->op->value << "\n";
		visit_expr(in->right);
		cout << *binop_result << " = " << *in->right->attrs->get_string(LOC) << ";\n"; 

		cout << *after_binop << ":;\n"; 
	}
	else if(*in->op->value == "||" || *in->op->value == "or")
	{
		String* after_binop = fresh("after_binop");
		// TODO: do we need to clone before assigning to binop_result?
		cout << *binop_result << " = " << *in->left->attrs->get_string(LOC) << ";\n";

		cout << "if(zend_is_true(" << *in->left->attrs->get_string(LOC) << ")) goto " << *after_binop << ";\n";
		
		/**/
		cout << "// Evaluate right operand of " << *in->op->value << "\n";
		visit_expr(in->right);
		cout << *binop_result << " = " << *in->right->attrs->get_string(LOC) << ";\n"; 

		cout << *after_binop << ":;\n"; 
	}
	else
	{
		cout << "// Evaluate right operand of " << *in->op->value << "\n";
		visit_expr(in->right);
		
		cout << "// Evaluate " << *in->op->value << "\n";	
		cout << "MAKE_STD_ZVAL(" << *binop_result << ");\n";

		assert (bin_op_functions.find(*in->op->value) != bin_op_functions.end());

		// some operators need the operands to be reversed (since we call the opposite function). This is accounted for in the binops table.
		if (*in->op->value == ">" || *in->op->value == ">=")
		{
			cout << bin_op_functions[*in->op->value] << "(" << *binop_result << ", "
				<< *in->right->attrs->get_string(LOC) << ", " 
				<< *in->left->attrs->get_string(LOC) << " TSRMLS_CC);\n";
		}
		else
		{
			cout << bin_op_functions[*in->op->value] << "(" << *binop_result << ", "
				<< *in->left->attrs->get_string(LOC) << ", " 
				<< *in->right->attrs->get_string(LOC) << " TSRMLS_CC);\n";
		}
	}

	in->attrs->set(LOC, binop_result);
	cout << "zend_hash_next_index_insert(temps, &" << *binop_result << ", sizeof(zval*), NULL);\n";
}

void Generate_C::post_pre_op(AST_pre_op* in)
{
	/**/
	cout << "// Evaluate pre-op\n";

	cout << "{";

	cout << "zval one;\n";
	cout << "INIT_ZVAL(one);\n";
	cout << "ZVAL_LONG(&one, 1);\n";

	cout << bin_op_functions[*in->op->value] << "("; 
	cout << *in->variable->attrs->get_string(LOC);
	cout << ", " << *in->variable->attrs->get_string(LOC);
	cout << ", &one TSRMLS_CC);\n";

	cout << "}";
	
	in->attrs->set(LOC, in->variable->attrs->get(LOC));
}

void Generate_C::post_post_op(AST_post_op* in)
{
	/**/
	cout << "// Evaluate post-op\n";

	String* before_post_op = fresh("before_post_op");
	cout << "zval* " << *before_post_op << ";\n";
	
	cout << "{";
	cout << "zval one;\n";
	cout << "INIT_ZVAL(one);\n";
	cout << "ZVAL_LONG(&one, 1);\n";

	cout << "MAKE_STD_ZVAL(" << *before_post_op << ");\n";
	cout << "*" << *before_post_op << " = *" << *in->variable->attrs->get_string(LOC) << ";\n";
	cout << "zval_copy_ctor(" << *before_post_op << ");\n";

	cout << bin_op_functions[*in->op->value] << "("; 
	cout << *in->variable->attrs->get_string(LOC);
	cout << ", " << *in->variable->attrs->get_string(LOC);
	cout << ", &one TSRMLS_CC);\n"; ;

	cout << "}";
	
	in->attrs->set(LOC, before_post_op);
	cout << "zend_hash_next_index_insert(temps, &" << *before_post_op << ", sizeof(zval*), NULL);\n";
}

void Generate_C::post_unset(AST_unset* in)
{
	/**/
	cout << "// Unset\n";

	if(in->variable->attrs->has(STRIDX))
	{
		cout << "zend_hash_del(";
		cout << *in->variable->attrs->get_string(HASH) << ", ";
		cout << *in->variable->attrs->get_string(STRIDX) << ", ";
		cout << in->variable->attrs->get_integer(STRLEN)->value() << ");\n";;
	}
	else
	{
		cout << "if(Z_TYPE_P(" ;
		cout << *in->variable->attrs->get_string(ZVALIDX) ;
		cout << ") == IS_LONG)\n";
		cout << "{\n";
		cout << "zend_hash_index_del(";
		cout << *in->variable->attrs->get_string(HASH) << ", ";
		cout << "Z_LVAL_P(" << *in->variable->attrs->get_string(ZVALIDX) ;
		cout << "));\n";
		cout << "}\n";
		cout << "else\n";
		cout << "{\n";
		cout << "zval string_index;\n" ;
		cout << "string_index = *" ;
		cout << *in->variable->attrs->get_string(ZVALIDX);
		cout << ";\n";
		cout << "convert_to_string(&string_index);\n";
		cout << "zend_hash_del(" ;
		cout << *in->variable->attrs->get_string(HASH) << ", ";
		cout << "Z_STRVAL(string_index), Z_STRLEN(string_index) + 1);\n";
		cout << "}\n";;
	}
}

/*
 * Assignment
 *
 * Prep will have marked the LHS as IS_ADDR, and will have marked the RHS as
 * IS_ADDR _if_ this is a reference assignment and the RHS is a variable
 */

void Generate_C::post_assignment(AST_assignment* in)
{
	String* rhs = in->expr->attrs->get_string(LOC);
	
	/**/
	cout << "// Execute assignment\n";

	if(!in->is_ref)
	{
		if(dynamic_cast<AST_variable*>(in->expr) != NULL)
		{
			cout 
			<< "// copy-on-write is possible if the RHS is not a reference\n"
			<< "if(!(" << *rhs << ")->is_ref)\n"
			<< "{\n"
			<< "// Up refcount, but don't mark as reference (copy-on-write)\n"
			<< "zval_add_ref(&" << *rhs << ");\n";
	
			update_hash(in->variable, rhs);
	
			cout 
			<< "}\n"
			<< "else\n"
			<< "{\n"
			<< "// copy now (separate)\n";
	
			index_hash(in->variable);
			separate(in->variable);
			String* lhs = in->variable->attrs->get_string(LOC);

			cout 
			<< "zval_dtor(" << *lhs << ");\n"
			// Copy over the value and type, ignoring refcount and is_ref
			<< "(" << *lhs << ")->value = " << "(" << *rhs << ")->value;\n"
			<< "(" << *lhs << ")->type = " << "(" << *rhs << ")->type;\n"
			<< "zval_copy_ctor(" << *lhs << ");\n"
			<< "}\n";
		}
		else
		{
			// If the RHS is not a variable, copy-on-write is not applicable
			index_hash(in->variable);
			separate(in->variable);
			String* lhs = in->variable->attrs->get_string(LOC);

			cout 
			<< "zval_dtor(" << *lhs << ");\n"
			// Copy over the value and type, ignoring refcount and is_ref
			<< "(" << *lhs << ")->value = " << "(" << *rhs << ")->value;\n"
			<< "(" << *lhs << ")->type = " << "(" << *rhs << ")->type;\n"
			<< "zval_copy_ctor(" << *lhs << ");\n";
		}
	}
	else
	{
		AST_variable* var = dynamic_cast<AST_variable*>(in->expr);

		if(var != NULL)
		{
			cout << "// Separate RHS if it is in a copy-on-write set\n";
			separate(var);
			rhs = var->attrs->get_string(LOC); 
		}
		
		// Up the refcount of the RHS and mark as a reference (change-on-write)
		cout
		<< "zval_add_ref(&" << *rhs << ");\n"
		<< "(" << *rhs << ")->is_ref = 1;\n";

		update_hash(in->variable, in->expr->attrs->get_string(LOC));
	}
}

/*
 * Control statements
 */

void Generate_C::children_if(AST_if* in)
{
	assert (0);
}

void Generate_C::children_branch(AST_branch* in)
{
	visit_expr(in->expr);
	cout << "if (zend_is_true(" << *in->expr->attrs->get_string(LOC) << ")) \n";
	cout << "	goto " << *(in->iftrue->value) << ";" << endl;
	cout << "else \n";
	cout << "	goto " << *(in->iffalse->value) << ";" << endl;
}

void Generate_C::children_for(AST_for* in)
{
	assert (0);
}

/*
 * Variable references
 */

void Generate_C::post_variable(AST_variable* in)
{
	// TODO: deal with target
	// TODO: deal with (string) indexing
	// TODO: deal with variable variables
	
	Token_variable_name* var_name;
	var_name = dynamic_cast<Token_variable_name*>(in->variable_name);
	assert(var_name);

	in->attrs->set(HASH, new String("EG(active_symbol_table)"));
	in->attrs->set(STRIDX, quote(var_name->value));
	in->attrs->set(STRLEN, new Integer(var_name->value->size() + 1));
	
	if(!in->attrs->is_true(IS_ADDR) || in->array_indices->size() > 0)
	{
		index_hash(in);
	}

	// Evaluate all array indices
	List<AST_expr*>::const_iterator i, end_1;
	end_1 = in->array_indices->end(); end_1--;
	for(i = in->array_indices->begin(); i != in->array_indices->end(); i++)
	{
		String* hash = fresh("hash");
		
		/**/
		cout << "// Make sure the hashtable is actually a hashtable (or NULL)\n";
		cout << "if(Z_TYPE_P(" << *in->attrs->get_string(LOC) << ") == IS_NULL)\n";
		cout << "{\n";
		cout << "array_init(" << *in->attrs->get_string(LOC) << ");\n";
		cout << "}\n";
		cout << "else ";
		cout << "if(Z_TYPE_P(" << *in->attrs->get_string(LOC) << ") != IS_ARRAY)\n";
		cout << "{\n";
		cout << "printf(\"variable is not an array\\n\");\n";
		cout << "abort();\n";
		cout << "}\n";

		/**/
		cout << "// Extract the hashtable from the zval\n";
		cout << "HashTable* " << *hash << ";\n";
		cout << *hash << " = Z_ARRVAL_P(" << *in->attrs->get_string(LOC) << ");\n";;

		in->attrs->set(HASH, hash);
		in->attrs->set(ZVALIDX, (*i)->attrs->get_string(LOC));
	
		if(!in->attrs->is_true(IS_ADDR) || i != end_1)
		{
			index_hash(in);
		}
	}
}

/*
 * Method definition
 */

void Generate_C::pre_method(AST_method* in)
{
	// We need a label to indicate where the end of the function is
	String* eofn = fresh("end_of_function");
	eofn_labels.push_back(eofn);

	cout << "PHP_FUNCTION(" << *in->signature->method_name->value << ")\n";
	methods.push_back(in->signature->method_name->value);

	cout << "{\n";

	/**/
	cout << "// Store a reference to the current active symbol table\n";
	cout << "HashTable* old_active_symbol_table;\n";
	cout << "old_active_symbol_table = EG(active_symbol_table);\n";

	/* TODO count the locals - growing hashtables is very expensiveg*/
	cout << "// Setup locals array\n";
	cout << "HashTable* locals;\n";
	cout << "ALLOC_HASHTABLE(locals);\n";
	cout << "zend_hash_init(locals, 64, NULL, ZVAL_PTR_DTOR, 0);\n";
	cout << "EG(active_symbol_table) = locals;\n";

	/* TODO count the temporaries - growing hashtables is very expensive */
	cout << "// We store all temporaries in an array so that they can be deallocated\n";
	cout << "HashTable* temps;\n";
	cout << "ALLOC_HASHTABLE(temps);\n";
	cout << "zend_hash_init(temps, 64, NULL, ZVAL_PTR_DTOR, 0);\n";

	/**/
	List<AST_formal_parameter*>* parameters = in->signature->formal_parameters;
	if(parameters && parameters->size() > 0)
	{
		cout << "// Add all parameters as local variables\n";
		stringstream zgp_format; 
		stringstream zgp_args; 
		cout << "{\n";
		cout << "zval* params[" << parameters->size() << "];\n";
		List<AST_formal_parameter*>::const_iterator i;
		int index;	
		for(i = parameters->begin(), index = 0;
			i != parameters->end();
			i++, index++)
		{
			// TODO: deal with default values
			// TODO: deal with type (although that should be dealt with
			// elsewhere)
			// TODO: deal with references
			zgp_format << "z";
			
			if (i != parameters->begin())
				zgp_args << ", ";
	
			zgp_args << "&params[" << index << "]";
		}
		cout << "zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, \"" << zgp_format.str() << "\", " << zgp_args.str() << ");\n";
		for(i = parameters->begin(), index = 0;
			i != parameters->end();
			i++, index++)
		{
			cout << "zval_add_ref(&params[" << index << "]);\n";
			cout << "zend_hash_add(EG(active_symbol_table), \"" << *(*i)->variable_name->value << "\", sizeof(\"" << *(*i)->variable_name->value << "\"), &params[" << index << "], sizeof(zval*), NULL);\n";
		}

		cout << "}\n";
	}

	cout << "// Function body\n";
}

void Generate_C::post_method(AST_method* in)
{
	String* eofn = eofn_labels.back();
	eofn_labels.pop_back();
	cout << *eofn << ":;\n";

	/**/
	cout << "// Free all temporaries\n";
	cout << "zend_hash_destroy(temps);\n";
	cout << "FREE_HASHTABLE(temps);\n";

	/**/
	cout << "// Destroy locals array\n";
	cout << "zend_hash_destroy(locals);\n";
	cout << "FREE_HASHTABLE(locals);\n";

	/**/
	cout << "// Restore previous active symbol table\n";
	cout << "EG(active_symbol_table) = old_active_symbol_table;\n";	

	cout << "}\n";
}


/*
 * Top-level structure
 */

void Generate_C::pre_php_script(AST_php_script* in)
{
	cout << "#include \"php.h\"\n";
}

void Generate_C::post_php_script(AST_php_script* in)
{
	/**/
	cout << "// Register all functions with PHP\n";
	cout << "static function_entry " << *extension_name << "_functions[] = {\n";

	List<String*>::const_iterator i;
	for(i = methods.begin(); i != methods.end(); i++)
		cout << "PHP_FE(" << **i << ", NULL)\n";

	cout << "{ NULL, NULL, NULL }\n";
	cout << "};\n";

	/**/
	cout << "// Register the module itself with PHP\n";
	cout << "zend_module_entry " << *extension_name << "_module_entry = {\n";
	cout << "STANDARD_MODULE_HEADER, \n";
	cout << "\"" << *extension_name << "\",\n";
	cout << *extension_name << "_functions,\n";
	cout << "NULL, /* MINIT */\n";
	cout << "NULL, /* MSHUTDOWN */\n";
	cout << "NULL, /* RINIT */\n";
	cout << "NULL, /* RSHUTDOWN */\n";
	cout << "NULL, /* MINFO */\n";
	cout << "\"1.0\",\n";
	cout << "STANDARD_MODULE_PROPERTIES\n";
	cout << "};\n";

	if(is_extension)
		cout << "ZEND_GET_MODULE(" << *extension_name << ")\n";
	else
		driver();
}

/*
 * Special cases
 */

void Generate_C::children_eval_expr(AST_eval_expr* in)
{
	// Check for inline C blocks
	List<String*>* comments = in->get_comments();
	if(!comments->empty() && *(comments->back()) == "// phc:inline-c")
	{
		Token_string* inline_c = dynamic_cast<Token_string*>(in->expr);
		if(inline_c == NULL)
		{
			phc_error(ERR_INVALID_INLINE_C, 
				in->expr->get_filename(), 
				in->expr->get_line_number());
		}
		else
		{
			cout << *inline_c->value << endl;
		}
	}
	else
	{
		visit_expr(in->expr);
	}
}

void
Generate_C::children_goto (AST_goto *in)
{
	cout << "goto " << *(in->label_name->value) << ";" << endl;
}

void
Generate_C::children_label (AST_label* in)
{
	// getting a few errors with this. I expect we are not allowed put a label
	// before another label, or before a declaration. Added semicolon to be sure
	cout << *(in->label_name->value) << ": ;" << endl;
}

/*
 * Driver (to turn the extension into a stand-alone application)
 */

void Generate_C::driver()
{
	cout << "#include <sapi/embed/php_embed.h>\n";
	cout << "#include <signal.h>\n\n";

	/* TODO this is always a bug in phc. If not, we'll post it to the FAQ or something. */

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
	"    // call %MAIN%::run\n"
	"    int success = call_user_function( \n"
	"				     EG (function_table),\n"
	"				     NULL,\n"
	"				     &main_name,\n"
	"				     &retval,\n"
	"				     0,\n"
	"				     NULL\n"
	"				     TSRMLS_CC);\n"
	"	\n"
	"  PHP_EMBED_END_BLOCK()\n"
	"\n"
	"  return 0;\n"
	"}\n" ;
}

/*
 * Various utility functions 
 */

void Generate_C::escape(String* s)
{
	String::const_iterator i;
	for(i = s->begin(); i != s->end(); i++)
	{
		if(*i == '"')
		{
			cout << "\\\"";
		}
		else if(*i >= 32 && *i < 127)
		{
			cout << *i;
		}
		else
		{
			cout << "\\x" << setw(2) << setfill('0') << hex << uppercase << (unsigned long int)(unsigned char) *i;
			cout << resetiosflags(cout.flags());
		}
	}
}

/* Generate a new temporary name, with the passed PREFIX */
String* Generate_C::fresh(string prefix)
{
	static map<string, int> temps;
	int t = temps[prefix]++;
	stringstream ss;
	ss << prefix << t;
	return new String(ss.str()); 
}

String* Generate_C::addr(String* var)
{
	stringstream ss;
	ss << "&" << *var;
	return new String(ss.str());
}

String* Generate_C::deref(String* var)
{
	stringstream ss;
	ss << "*" << *var;
	return new String(ss.str());
}

String* Generate_C::quote(String* str)
{
	stringstream ss;
	ss << '"' << *str << '"';
	return new String(ss.str());
}

#endif
