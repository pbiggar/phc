/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Value-range propagation.
 *
 * Based mostly on
 * Accurate static branch prediction by value range propagation,
 * Jason Patterson,
 * PLDI95.
 *
 * We need this to help determine when integers overflow into doubles.
 *
 */

#include "VRP.h"

VRP::VRP (Whole_program* wp)
: WPA (wp)
{
}
