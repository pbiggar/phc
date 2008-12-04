/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Annotate MIR for code generation.
 */

#ifndef PHC_GENERATE_C_ANNOTATIONS_H
#define PHC_GENERATE_C_ANNOTATIONS_H

#include "MIR_visitor.h"
#include "lib/Set.h"

class Generate_C_annotations : public MIR::Visitor, virtual public GC_obj
{
	Set<string> var_names;
	Set<string> iterators;
	Map<int, Map<string, String*> > literal_pools;

	// Whole script analysis
	void pre_php_script (MIR::PHP_script* in);
	void post_php_script (MIR::PHP_script* in);
	void post_literal (MIR::Literal* in);

	// Method analysis
	void pre_method (MIR::Method* in);
	void post_method (MIR::Method* in);
	void post_variable_name (MIR::VARIABLE_NAME* in);
	void post_ht_iterator (MIR::HT_ITERATOR* in);
};

# endif // PHC_GENERATE_C_ANNOTATIONS_H
