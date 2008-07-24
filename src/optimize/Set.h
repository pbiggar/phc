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
	// Out-of-place operations return new sets
	Set* oop_union (Set* other);
	Set* oop_intersection (Set* other);
	Set* oop_difference (Set* other);
	
	// In-place operations
	Set* ip_union (Set* other);
	Set* ip_intersection (Set* other);
	Set* ip_difference (Set* other);

public:
	void add (String* string);
};


#endif // PHC_SET
