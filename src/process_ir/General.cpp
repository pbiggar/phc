/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generic utilities for which the need is ubiquitous.
 */

#include "process_ir/General.h"

String* s (string str)
{
	return new String (str);
}
