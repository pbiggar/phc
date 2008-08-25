#include <algorithm>
#include <iterator>
#include "assert.h"

#include "process_ir/General.h"
#include "Set.h"

Set::Set()
: full (false)
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
				insert_iterator<set<string> > (*result, result->begin ()));
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
				insert_iterator<set<string> > (*result, result->begin ()));
	}
	else if (other->full)
	{
		std::copy (
				other->begin (), other->end(),
				insert_iterator<set<string> > (*result, result->begin ()));
	}
	else
	{
		std::set_intersection (
				begin (), end(),
				other->begin (), other->end (),
				insert_iterator<set<string> > (*result, result->begin ()));
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
		insert_iterator<set<string> > (*result, result->begin ()));

	return result;
}

void
Set::insert (String* name)
{
	this->insert (*name);
}

bool
Set::contains (String* name)
{
	return full || (find (*name) != end());
}

void
Set::dump(ostream& out)
{
	foreach (string str, *this)
	{
		out << str << ", ";
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

	foreach (string name, *this)
	{
		result->insert (name);
	}

	return result;
}
