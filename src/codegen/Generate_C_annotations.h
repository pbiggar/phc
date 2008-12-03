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

	void pre_method (MIR::Method* in);
	void post_method (MIR::Method* in);
	void post_variable_name (MIR::VARIABLE_NAME* in);
};

# endif // PHC_GENERATE_C_ANNOTATIONS_H
