/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lift functions and classes to the global scope, and introduce "__MAIN__"
 */

#ifndef PHC_LIFT_FUNCTIONS_AND_CLASSES_H
#define PHC_LIFT_FUNCTIONS_AND_CLASSES_H

#include "MIR_transform.h"

class Lift_functions_and_classes : public MIR::Transform, virtual public GC_obj
{
	void children_php_script(MIR::PHP_script* in);
};

#endif // PHC_LIFT_FUNCTIONS_AND_CLASSES
