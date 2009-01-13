/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Type-inference.
 *
 */

#ifndef PHC_TYPE_INFERENCE
#define PHC_TYPE_INFERENCE

#include "WPA.h"
#include "Points_to.h"

class Type_inference : public WPA
{
public:
	Type_inference (Whole_program* wp);

	void use_summary_results (Method_info* info, MIR::Actual_parameter_list* in, MIR::VARIABLE_NAME* lhs);

	void initialize_function ( MIR::Method* in, MIR::Actual_parameter_list* actuals, MIR::VARIABLE_NAME* lhs);
	void finalize_function (MIR::Method* in);

	void dump ();

	// TODO: I'm not sure how well this will work
	// Type-inference just follows the points-to graph to get the possible
	// types of a method.
	String_list* get_types (Var_node* node);

	bool is_basic_type (String* name);
};


#endif // PHC_TYPE_INFERENCE
