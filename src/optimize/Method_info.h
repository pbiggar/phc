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
DECL (Class_info);
DECL (User_class_info);

String* UNNAMED (int param_index);
MIR::VARIABLE_NAME* unnamed_param (int param_index);

class Method_info : virtual public GC_obj
{
public:
	String* name;
	String* lc_name;

protected:
	CFG* cfg; // If there is no implementation, a fake CFG is provided.
	Method_info (String* name);


public:
	virtual bool has_implementation () = 0;

	/* 
	 * Model signature (an MIR::Signature isnt really good enough, and is very
	 * annoying to use).
	 */
	virtual bool return_by_ref () = 0;

	virtual MIR::VARIABLE_NAME* param_name (int param_index) = 0;
	virtual bool param_by_ref (int param_index) = 0;

	// Returns NULL if there is a default parameter for this index
	virtual MIR::Static_value* default_param (int param_index) = 0;

	virtual int formal_param_count () = 0;

	virtual Class_info* get_class_info () = 0;

	virtual CFG* get_cfg () = 0;

	/*
	 * Annotations for optimizations
	 */
	virtual bool get_side_effecting () = 0;
};

class User_method_info : public Method_info
{
private:
	User_class_info* class_info;
	MIR::Method* method;
	MIR::Signature* signature;
	bool side_effecting;


public:
	User_method_info (MIR::Method* implementation);
	User_method_info (User_class_info* class_info, MIR::Method* method);

	bool has_implementation ();

	bool return_by_ref ();
	MIR::VARIABLE_NAME* param_name (int param_index);
	bool param_by_ref (int param_index);
	MIR::Static_value* default_param (int param_index);
	int formal_param_count ();

	bool get_side_effecting ();
	void set_side_effecting (bool);

	MIR::Method* get_method ();
	virtual Class_info* get_class_info ();
	virtual CFG* get_cfg ();

};

class Summary_method_info : public Method_info
{
public:
	// Creates fake CFGs for summary analysis
	Summary_method_info (String* name);

	virtual Class_info* get_class_info ();
	virtual CFG* get_cfg ();
	Basic_block* get_fake_bb ();
};

/*
 * Model builtin functions. The modelling is actually in Whole_program.cpp, for
 * now.
 */
class Builtin_method_info : public Summary_method_info
{
public:
	Builtin_method_info (String* name);

	bool has_implementation ();

	bool return_by_ref ();
	MIR::VARIABLE_NAME* param_name (int param_index);
	bool param_by_ref (int param_index);
	MIR::Static_value* default_param (int param_index);
	int formal_param_count ();

	bool get_side_effecting ();
	virtual Class_info* get_class_info ();

};

#endif // PHC_METHOD_INFORMATION
