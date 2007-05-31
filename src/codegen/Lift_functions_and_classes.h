/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Lift functions and classes to the global scope, and introduce "__MAIN__"
 */

#ifndef PHC_LIFT_FUNCTIONS_AND_CLASSES_H
#define PHC_LIFT_FUNCTIONS_AND_CLASSES_H

#include "AST_transform.h"

class Lift_functions_and_classes : public AST_transform
{
public:
	void children_php_script(AST_php_script* in);
};

#endif // PHC_LIFT_FUNCTIONS_AND_CLASSES
