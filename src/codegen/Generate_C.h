/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate C code
 *
 * Currently, the C code is generated directly from the AST; once we have an
 * IR, the C code will be generated from the IR instead.
 */

#ifndef GENERATE_C
#define GENERATE_C

#include "AST_visitor.h"

class Generate_C : public AST_visitor
{
public:
	// use NULL to compile as an extension
	Generate_C(String* extension_name);

public:
	void children_statement(AST_statement* in);
	void pre_php_script(AST_php_script* in);
	void post_php_script(AST_php_script* in);

public:
	String* extension_name;
	bool is_extension;
	List<AST_signature*>* methods;	// List of all methods compiled	

/*
private:
	String* extension_name;
	bool is_extension;
	void driver();
	String* fresh(string prefix);
	String* addr(String* var);
	String* deref(String* var);
	String* quote(String* str);
	void escape(String* s);
	void update_hash(AST_variable* var, String* val);
	void index_hash(AST_variable* in);
	void separate(AST_variable* var);

public:
	// use NULL to compile as an extension
	Generate_C(String* extension_name);

public:
	void post_string(Token_string* in);	
	void post_int(Token_int* in);
	void post_bool(Token_bool* in);
	void post_null(Token_null* in);
	void post_method_invocation(AST_method_invocation* in);
	void post_return(AST_return* in);
	void children_bin_op(AST_bin_op* in);
	void post_pre_op(AST_pre_op* in);
	void post_post_op(AST_post_op* in);
	void post_unset(AST_unset* in);
	void post_assignment(AST_assignment* in);
	void children_if(AST_if* in);
	void children_branch(AST_branch* in);
	void children_for(AST_for* in);
	void post_variable(AST_variable* in);
	void pre_method(AST_method* in);
	void post_method(AST_method* in);
	void pre_php_script(AST_php_script* in);
	void post_php_script(AST_php_script* in);
	void children_eval_expr(AST_eval_expr* in);
	void children_goto (AST_goto* in);
	void children_label (AST_label* in);
*/
};

#endif // GENERATE_C
