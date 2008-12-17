/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Annotate MIR for code generation.
 */

#ifndef PHC_GENERATE_LIR_ANNOTATIONS_H
#define PHC_GENERATE_LIR_ANNOTATIONS_H

#include "MIR_visitor.h"
#include "lib/Set.h"

class Generate_LIR_annotations : public MIR::Visitor, virtual public GC_obj
{
	Set<string> var_names;
	Set<string> iterators;
	Set<string> called_functions;
	MIR::Signature_list* compiled_functions;

	// Literal.classid() -> (lit.value -> Literal*)
	Map<int, Map<string, MIR::Literal*> > pool_values;

	// Whole script analysis
	void pre_php_script (MIR::PHP_script* in);
	void post_php_script (MIR::PHP_script* in);
	void post_literal (MIR::Literal* in);
	void post_param_is_ref (MIR::Param_is_ref* in);
	void post_method_invocation (MIR::Method_invocation* in);

	// Method analysis
	void pre_method (MIR::Method* in);
	void post_method (MIR::Method* in);
	void post_variable_name (MIR::VARIABLE_NAME* in);
	void post_ht_iterator (MIR::HT_ITERATOR* in);
	void post_return (MIR::Return* in);
};

#endif // PHC_GENERATE_LIR_ANNOTATIONS_H
