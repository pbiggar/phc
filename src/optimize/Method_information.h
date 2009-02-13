/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Try to model functions as accurately as possible.
 */

#ifndef PHC_METHOD_INFORMATION
#define PHC_METHOD_INFORMATION

#include "CFG.h"

// There is a ton of information here, and we don't want to extend the
// MIR::Signature and MIR::Formal_parameters with it, since they're used in
// lots of other places.

/*
 * What can go wrong, and what information do we get automatically:
 *
 * Parameters:
 *
 *		- parameters can be passed by reference (we can know this)
 *		- a parameter can be an object
 *			- the obj/reference can be modified by the callee
 *		- a parameter can be the name of a callback
 *			- the callback can be the result of create_function
 *		- a parameter can have a magic method called on it by the way it is
 *			accessed
 *		- a function can be called with the wrong number of parameters, so
 *		might do nothing and return NULL.
 *
 * Methods:
 *		- a method has paramters (see above)
 *		- a method may change global variables
 *		- a method may change local variables
 *		- a method can be side-effecting (we'd like to model if it is not, so
 *		that calls can be removed).
 *		- a method may return-by-ref.
 *
 *
 *	The only answer is to assume the worst in all cases, and to selectively
 *	model functions to not do so badly. However, we are able to model some
 *	things automatically:
 *
 *		- user code:
 *			- can determine by analysis:
 *				- is_side_effecting
 *			- can tell very easily
 *				- return-by-ref
 *				- pass-by-ref
 *
 *		- built-in-functions
 *			- return-by-ref
 *			- pass-by-ref
 *
 * 
 * Solution:
 *
 *		Remove all the information from method_info. The only thing that should
 *		be there is return-by-ref and pass-by-ref.
 *
 *		Add methods to Method_info allowing us to check for what we need. Add a
 *		function to automatically apply what we know when a function is called.
 *
 *		Method_info should have no public members. Remove Param_info.
 *
 *		Embed can provide hooks that take a method_name.
 *
 */

DECL (Method_info);

class Whole_program;

class Method_info : virtual public GC_obj
{
public:
	String* name;

protected:
	Method_info (String* name);

public:
	virtual bool has_implementation () = 0;

	// Trivial to generate
	virtual bool param_by_ref (int param_index) = 0;
	virtual bool return_by_ref () = 0;

	// Must be annotated
	virtual bool is_side_effecting () = 0;
};

class User_method_info : public Method_info
{
private:
	MIR::Method* method;
	bool side_effecting;

	friend class Whole_program;

public:
	User_method_info (MIR::Method* implementation);

	CFG* cfg;

	bool has_implementation ();

	bool param_by_ref (int param_index);
	bool return_by_ref ();

	bool is_side_effecting ();

};

#endif // PHC_METHOD_INFORMATION
