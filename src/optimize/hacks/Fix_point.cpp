/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Iterate over visitors and transforms until they complete.
 *
 * TODO maybe better to do this at the pass level?
 */

#include "Fix_point.h"
#include "process_ir/General.h"

Fix_point::Fix_point ()
: iterations (0)
, iterate_again (true) 
{
}

// Overriding 
void Fix_point::visit_php_script (HIR::PHP_script* in)
{
	while (iterate_again && iterations < 10)
	{
		DEBUG ("Iteration: " << iterations);
		iterate_again = false;
		iterations++;

		// call the overridden method
		HIR::Visitor::visit_php_script (in);
	}
}


// Overriding 
void Fix_point::children_php_script (HIR::PHP_script* in)
{
	while (iterate_again && iterations < 10)
	{
		DEBUG ("Iteration: " << iterations);
		iterate_again = false;
		iterations++;


		// call the overridden method
		HIR::Transform::children_php_script (in);
	}
}
