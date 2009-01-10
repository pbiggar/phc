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

class Type_inference : public WPA
{
public:
	Type_inference ();
	void eval_bb (Basic_block* bb);
};


#endif // PHC_TYPE_INFERENCE
