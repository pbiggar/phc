#ifndef PHC_SET
#define PHC_SET

#include <set>
#include <lib/String.h>

class Set
{
public:
	// Backing store
	set<string> bs;

public:
	Set();

public:
	// Out-of-place operations return new sets. We only consider out-of-place
	// versions since the STL includes only out-of-place versions. In-place
	// versions could be created in some cases, however, possibly with lower
	// complexity.
	Set* set_union (Set* other);
	Set* set_intersection (Set* other);
	Set* set_difference (Set* other);
	bool operator!=(Set& other);
	bool operator==(Set& other);
	
public:
	void insert (String* string);
	bool contains (String* string);
	void dump(ostream&);
};


#endif // PHC_SET
