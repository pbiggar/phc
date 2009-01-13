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
	void use_summary_results (Method_info* info);

	void dump ();

	// TODO: I'm not sure how well this will work
	// Type-inference just follows the points-to graph to get the possible
	// types of a method.
	String_list* get_types (Var_node* node);
};


#endif // PHC_TYPE_INFERENCE
