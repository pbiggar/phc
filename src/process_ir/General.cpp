/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generic utilities for which the need is ubiquitous.
 */

#include "process_ir/General.h"

bool is_builtin_function (String* name)
{
	return (
		   *name == "eval"
		|| *name == "exit"
		|| *name == "die"
		|| *name == "print"
		|| *name == "echo"
		|| *name == "include"
		|| *name == "include_once"
		|| *name == "require"
		|| *name == "require_once"
		|| *name == "empty");
}
