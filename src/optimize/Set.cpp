#include <algorithm>
#include <iterator>
#include "assert.h"

#include "process_ir/General.h"
#include "Set.h"

Set::Set()
: bs()
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
				this->bs.begin (), this->bs.end(),
				other->bs.begin (), other->bs.end (),
				insert_iterator<set<string> > (result->bs, result->bs.begin ()));
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
				this->bs.begin (), this->bs.end(),
				insert_iterator<set<string> > (result->bs, result->bs.begin ()));
	}
	else if (other->full)
	{
		std::copy (
				other->bs.begin (), other->bs.end(),
				insert_iterator<set<string> > (result->bs, result->bs.begin ()));
	}
	else
	{
		std::set_intersection (
				bs.begin (), bs.end(),
				other->bs.begin (), other->bs.end (),
				insert_iterator<set<string> > (result->bs, result->bs.begin ()));
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
		bs.begin (), bs.end(),
		other->bs.begin (), other->bs.end (),
		insert_iterator<set<string> > (result->bs, result->bs.begin ()));

	return result;
}

void
Set::insert (String* name)
{
	bs.insert (*name);
}

bool
Set::contains (String* name)
{
	return (bs.find (*name) != bs.end());
}

void
Set::dump(ostream& out)
{
	foreach (string str, bs)
	{
		out << str << ", ";
	}
	out << "\n";
}

bool
Set::operator==(Set& other)
{
	return (bs == other.bs);
}


bool
Set::operator!=(Set& other)
{
	return (bs != other.bs);
}

void Set::insert_all ()
{
}
