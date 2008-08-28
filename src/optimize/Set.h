#ifndef PHC_SET
#define PHC_SET

#include <set>
#include <lib/String.h>

bool
variable_name_ptr_comparison (MIR::VARIABLE_NAME* p1, MIR::VARIABLE_NAME* p2);

class Set 
: public set<
	MIR::VARIABLE_NAME*, 
	bool (*)(MIR::VARIABLE_NAME*, MIR::VARIABLE_NAME*)>
, virtual public Object
{
	typedef set<
		MIR::VARIABLE_NAME*,
		bool (*)(MIR::VARIABLE_NAME*,
		MIR::VARIABLE_NAME*)
	> parent;

public:
	// If true, the SET holds every possbible variable.
	bool full;

public:
	Set();
	Set(MIR::VARIABLE_NAME*);

public:
	// Out-of-place operations return new sets. We only consider out-of-place
	// versions since the STL includes only out-of-place versions. In-place
	// versions could be created in some cases, however, possibly with lower
	// complexity.
	Set* set_union (Set* other);
	Set* set_intersection (Set* other);
	Set* set_difference (Set* other);
	
public:
	// The set is the set of all possible strings.
	void insert_all ();

	bool has (MIR::VARIABLE_NAME* string);
	void dump(ostream&);

	Set* clone ();
	
public:
	// TODO when using iterators, assert (!full). We cant iterate through the
	// full set.
};


#endif // PHC_SET
