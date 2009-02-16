/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Try to model functions as accurately as possible.
 */

#include "MIR.h"
#include "Basic_block.h"

#include "Class_info.h"

using namespace MIR;

Class_info::Class_info (String* name)
: name (name)
{
}


/*
 * User methods -- Internal methods are defined in optimize.cpp
 */

User_class_info::User_class_info (Class_def* class_def)
: Class_info (class_def->class_name->value)
, class_def (class_def)
{
}

bool
User_class_info::has_implementation ()
{
	return true;
}


/*
 * Summary methods
 */

Summary_class_info::Summary_class_info (String* name)
: Class_info (name)
{
}


/*
 * Builtins
 */


Builtin_class_info::Builtin_class_info (String* name)
: Summary_class_info (name)
{
}


bool
Builtin_class_info::has_implementation ()
{
	return false;
}

