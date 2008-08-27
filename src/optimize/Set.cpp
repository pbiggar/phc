#include <algorithm>
#include <iterator>
#include "assert.h"

#include "process_ir/General.h"
#include "Set.h"

using namespace MIR;

Set::Set()
: parent(&variable_name_ptr_comparison)
, full (false)
{
}

// Out-of-place operations return new sets
Set*
Set::set_union (Set* other)
{
	Set* result = new Set;

	if (other->full or full)
		result->full = true;
	else
	{
		std::set_union (
				this->begin (), this->end(),
				other->begin (), other->end (),
				insert_iterator<parent> (*result, result->begin ()));
	}

	return result;
}

Set*
Set::set_intersection (Set* other)
{
	Set* result = new Set;

	if (this->full && other->full)
	{
		result->full = true;
	}
	else if (this->full)
	{
		std::copy (
				this->begin (), this->end(),
				insert_iterator<parent> (*result, result->begin ()));
	}
	else if (other->full)
	{
		std::copy (
				other->begin (), other->end(),
				insert_iterator<parent> (*result, result->begin ()));
	}
	else
	{
		std::set_intersection (
				begin (), end(),
				other->begin (), other->end (),
				insert_iterator<parent> (*result, result->begin ()));
	}

	return result;
}

Set*
Set::set_difference (Set* other)
{
	Set* result = new Set;

	if (other->full)
		return result;
	else if (this->full)
	{
		result->full = true;
		return result;
	}

	std::set_difference (
		begin (), end(),
		other->begin (), other->end (),
		insert_iterator<parent> (*result, result->begin ()));

	return result;
}

bool
Set::has (VARIABLE_NAME* var_name)
{
	return full || (find (var_name) != end());
}

void
Set::dump(ostream& out)
{
	foreach (VARIABLE_NAME* var_name, *this)
	{
		out << *var_name->value << ", ";
	}
	out << "\n";
}

void 
Set::insert_all ()
{
	full = true;
}

Set*
Set::clone ()
{
	Set* result = new Set ();
	if (full)
	{
		result->full = true;
		return result;
	}

	foreach (VARIABLE_NAME* var_name, *this)
	{
		result->insert (var_name);
	}

	return result;
}


bool
variable_name_ptr_comparison (MIR::VARIABLE_NAME* p1, MIR::VARIABLE_NAME* p2)
{
	assert (p1);
	assert (p2);

	// This needs to model '<', which must be transitive.
	return (*p1) < (*p2);
}
