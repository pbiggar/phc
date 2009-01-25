/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Annotate MIR for code generation.
 *
 * The phc.codegen.compiled_functions on the PHP script is a list of 
 * all functions in the global scope, but excluding function definitions
 * inside classes; they are stored in a similar attribute on the class def.
 */

#ifndef PHC_GENERATE_C_ANNOTATIONS_H
#define PHC_GENERATE_C_ANNOTATIONS_H

#include "MIR_visitor.h"
#include "lib/Set.h"
#include "lib/Stack.h"

class Generate_C_annotations : public MIR::Visitor, virtual public GC_obj
{
protected:
	Set<string> var_names;
	Set<string> iterators;
	Set<string> cached_functions;
	Stack<MIR::Signature_list*> compiled_functions;
	Stack<String*> class_name;

	// Literal.classid() -> (lit.value -> Literal*)
	Map<int, Map<string, MIR::Literal*> > pool_values;

public:
	// Whole script analysis
	void pre_php_script (MIR::PHP_script* in);
	void post_php_script (MIR::PHP_script* in);
	void post_literal (MIR::Literal* in);
	void post_param_is_ref (MIR::Param_is_ref* in);
	void post_method_invocation (MIR::Method_invocation* in);

	// OO
	void pre_class_def(MIR::Class_def* in);
	void post_class_def(MIR::Class_def* in);

	// Method analysis
	void pre_method (MIR::Method* in);
	void post_method (MIR::Method* in);
	void post_variable_name (MIR::VARIABLE_NAME* in);
	void post_ht_iterator (MIR::HT_ITERATOR* in);
	void post_return (MIR::Return* in);

// Declare Generate_C as a friend so that it can access var_names
// (necessary in compile_static_value)
	friend class Generate_C;
};

#endif // PHC_GENERATE_C_ANNOTATIONS_H
