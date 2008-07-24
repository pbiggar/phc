#ifndef PHC_SET
#define PHC_SET

#include <set>
#include <lib/String.h>

class Set
{
private:
	// Backing store
	set<string> bs;

public:
	Set();

public:
	// Out-of-place operations return new sets. We only consider out-of-place
	// versions since the STL includes only out-of-place versions. In-place
	// versions can be created in a lot of cases, however, possibly with lower
	// complexity.
	Set* set_union (Set* other);
	Set* set_intersection (Set* other);
	Set* set_difference (Set* other);
	
public:
	void insert (String* string);
};


#endif // PHC_SET
