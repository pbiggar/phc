#include <algorithm>
#include <iterator>
#include "assert.h"

#include "Set.h"

Set::Set()
: bs()
{
}

// Out-of-place operations return new sets
Set*
Set::set_union (Set* other)
{
	Set* result = new Set;

	std::set_union (
		bs.begin (), bs.end(),
		other->bs.begin (), other->bs.end (),
		insert_iterator<set<string> > (result->bs, result->bs.begin ()));

	return result;
}

Set*
Set::set_intersection (Set* other)
{
	Set* result = new Set;

	std::set_intersection (
		bs.begin (), bs.end(),
		other->bs.begin (), other->bs.end (),
		insert_iterator<set<string> > (result->bs, result->bs.begin ()));

	return result;
}

Set*
Set::set_difference (Set* other)
{
	Set* result = new Set;

	std::set_difference (
		bs.begin (), bs.end(),
		other->bs.begin (), other->bs.end (),
		insert_iterator<set<string> > (result->bs, result->bs.begin ()));

	return result;
}

void
Set::insert (String* string)
{
	bs.insert (*string);
}

