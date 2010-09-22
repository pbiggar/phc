/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Once a constant is defined, it cannot be redefined or undefined. Keep a list
 * of constants defined before this point.
 *
 * PHP presents two different behaviors for constants defined as case insensitive.
 * When checking it for constant redefinition, it does not consider all constant
 * name variations. For the "defined" function and when a constant is translated
 * to its value, it considers all variations. To cope with this, we used two functions:
 *   - can_constant_be_defined -> does not check all variations (should be used before set_constant).
 *   - is_constant_defined -> checks all variations (should be used in all other situations).
 *
 * To understand better, consider the following example:
 * <?php
 *   define("Def", "value1", true); // defined as case insensitive (stored as "def" - lowercase).
 *   define("def", "value2"); // cannot be defined, because "def" (lowercase) is already stored.
 *   define("Def", "value3"); // can be defined, since "Def" isn't stored.
 *   define("dEf", "value4", true); // cannot be defined, since "def" (lowercase) is already stored.
 * ?>
 *
 * PS: Current behavior of precedence for constants:
 *   check for case sensitive constants first, then for case insensitive.
 *
 * TODO: Conditional constants are not working.
 * TODO: Handle unknown constants key name.
 * TODO: Handle unknown value of case insensitive.
 *
 */

#include "Constant_state.h"
#include "Value_analysis.h"
#include <boost/algorithm/string.hpp> // to_lower

using namespace MIR;

Constant_state::Constant_state (Whole_program* wp)
: WPA_lattice <string, const Absval_cell> (wp)
{
}

// TODO: can be case-insensitive
string
Constant_state::context_merge_key (string key) const
{
	// Constant keys have context in them.
	return key;
}

// TODO: for conditionally defined constants, this might return true, even
// though its unknown.
bool
Constant_state::can_constant_be_defined (Context* cx, Result_state state, string name, bool case_insensitive) const
{
	if (case_insensitive)
		boost::to_lower(name);

	if (lattices[state][cx].has (name))
		return false;
 
	Literal* constant = PHP::fold_constant (new Constant (NULL, new CONSTANT_NAME (s(name))));
	if (constant)
		return false;

	return true;
}

void
Constant_state::set_constant (Context* cx, string name, const Abstract_value* value, bool case_insensitive)
{
	// Should be handled in Whole_program.
	assert (can_constant_be_defined (cx, R_WORKING, name, case_insensitive));

	if (case_insensitive)
		boost::to_lower(name);

	working[cx][name] = new Absval_cell (value, case_insensitive);
}

void
Constant_state::set_unknown_constant (Context* cx, const Abstract_value* value, bool case_insensitive)
{
	phc_TODO ();
  phc_optimization_exception ("Adding a new value from a new target unsupported during alias analysis");
}

// TODO: for conditionally defined constants, this might return true, even
// though its unknown.
bool
Constant_state::is_constant_defined (Context* cx, Result_state state, string name) const
{
	if (lattices[state][cx].has (name))
		return true;

	Literal* constant = PHP::fold_constant (new Constant (NULL, new CONSTANT_NAME (s(name))));
	if (constant)
		return true;

	// Try to obtain the case-insensitive constant.
	string iname = name;
	boost::to_lower(iname);

	string key;
	const Absval_cell *absval;

	foreach (tie(key, absval), lattices[state][cx]) {
		if (absval->case_insensitive && key == iname)
			return true;
	}

	return false;
}

const Abstract_value*
Constant_state::get_constant (Context* cx, Result_state state, string name) const
{
	if (lattices[state][cx].has (name))
		return lattices[state][cx][name]->value;

	Literal* constant = PHP::fold_constant (new Constant (NULL, new CONSTANT_NAME (s(name))));
	if (constant)
		return new Abstract_value (constant);

	// Try to obtain the case-insensitive constant.
	string iname = name;
	boost::to_lower(iname);

	string key;
	const Absval_cell *absval;
	foreach (tie(key, absval), lattices[state][cx]) {
		if (absval->case_insensitive && key == iname)
			return absval->value;
	}

	return new Abstract_value (new STRING (s(name)));
}
