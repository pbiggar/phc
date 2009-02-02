/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Once a constant is defined, it cannot be redefined or undefined. Keep a list
 * of constants defined before this point.
 */

#include "Constant_state.h"

Constant_state::Constant_state (Whole_program* wp)
: WPA(wp)
{
}
