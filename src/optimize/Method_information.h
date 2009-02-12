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
class Parameter_info : virtual public GC_obj
{
public:
	Parameter_info (bool pass_by_reference, bool is_callback, String_list* magic_methods)
	: pass_by_reference (pass_by_reference)
	, is_callback (is_callback)
	, can_change_value (can_change_value)
	, magic_methods (magic_methods)
	{
		assert (magic_methods != NULL);
	}

	// Is the parameter passed by reference (compile-time-pass-by-ref)
	bool pass_by_reference;
	bool is_callback;

	// If an object is passed, can its fields be changed.
	// or
	// If something is passed by reference, does it value change
	bool can_change_value;


	// PHP functions might not have any parameters modelled. In that case,
	// they have fields which say whether the rest are passed by reference,
	// etc. If USE_FOR_REST is set, this Parameter_info models all the rest of
	// the parameters.
	bool use_for_rest;

	// TODO: there may be more complicated aliasing, esp with array_*
	// functions or the like.

	// List of magic methods which may be called on this parameter;
	String_list* magic_methods;
};

typedef List<Parameter_info*> Parameter_info_list;

class Method_info : virtual public GC_obj
{
public:
	Method_info (String* name, Parameter_info_list* params, bool can_touch_globals, bool can_touch_locals, bool return_by_ref)
	: name (name)
	, implementation (NULL)
	, cfg (NULL)
	, params (params)
	, can_touch_globals (can_touch_globals)
	, can_touch_locals (can_touch_locals)
	, return_by_ref (return_by_ref)
	, is_side_effecting (true)
	{
		assert (params != NULL);
	}

	Method_info (String* name)
	: name (name)
	, implementation (NULL)
	, cfg (NULL)
	, can_touch_globals (true)
	, can_touch_locals (true)
	, return_by_ref (true)
	, is_side_effecting (true)
	{
		params = new Parameter_info_list;
	}

	Method_info (String* name, MIR::Method* implementation)
	: name (name)
	, implementation (implementation)
	, is_side_effecting (true)
	{
		cfg = new CFG (implementation);
	}

	String* name;
	MIR::Method* implementation;
	CFG* cfg;

	/*
	 * Summary information:
	 *		Unused if IMPLEMENTATION is set.
	 *
	 *		TODO: A better way to do this might be to write a PHP function which
	 *		'bakes' the result.
	 */
private:
	// The last paramater might represent the remainder, so it might be
	// returned.
	Parameter_info_list* params;
public:
	Parameter_info* param_at (int i);
	void add_param (Parameter_info*);

	// The following properties do not take into account callbacks or magic
	// methods. So if (CAN_TOUCH_GLOBALS == false), a parameter can still be a
	// callback to eval. Parameters are via Parameter_info.

	// TODO: we'd probably prefer a list of globals that can be affected
	bool can_touch_globals;
	bool can_touch_locals;

	// TODO: model more of the return - types, values
	// TODO: I was thinking about using abstract values before. This would be somewhat ideal here.
	bool return_by_ref;


	bool is_side_effecting;



	bool has_implementation ();
	bool has_parameters ();
};


typedef List<Method_info*> Method_info_list;

#endif // PHC_METHOD_INFORMATION
