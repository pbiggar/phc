/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * As much information as we can possibly say about a method.
 */

#ifndef PHC_METHOD_INFORMATION
#define PHC_METHOD_INFORMATION


// There is a ton of information here, and we don't want to extend the
// MIR::Signature and MIR::Formal_parameters with it, since they're used in
// lots of other places.
class Parameter_info : virtual public GC_obj
{
public:
	Parameter_info (bool pass_by_reference, bool is_callback, String_list* magic_methods)
	: pass_by_reference (pass_by_reference)
	, is_callback (is_callback)
	, can_touch_objects (can_touch_objects)
	, magic_methods (magic_methods)
	{
		assert (magic_methods != NULL);
	}

	// Is the parameter passed by reference (compile-time-pass-by-ref)
	bool pass_by_reference;
	bool is_callback;

	// While scalars and arrays are pass-by-copy, and object which is passed
	// by value may still have its fields touched, and methods called.
	bool can_touch_objects;

	// TODO: there may be more complicated aliasing, esp with array_*
	// functions or the like.

	// List of magic methods which may be called on this parameter;
	String_list* magic_methods;
};

typedef List<Parameter_info*> Parameter_info_list;

/*
 * TODO: this is intended to provide information when there is no definition available. When there is information available, it should use the Method* instead.
 */
class Method_info : virtual public GC_obj
{
public:
	Method_info (String* method_name, Parameter_info_list* params, bool can_touch_globals, bool can_touch_locals, bool return_by_ref)
	: method_name (method_name)
	, implementation (NULL)
	, params (params)
	, can_touch_globals (can_touch_globals)
	, can_touch_locals (can_touch_locals)
	, return_by_ref (return_by_ref)
	{
		assert (params != NULL);
	}

	Method_info (String* method_name, MIR::Method* implementation)
	: method_name (method_name)
	, implementation (implementation)
	{
	}

	String* method_name;
	MIR::Method* implementation;

	/*
	 * Summary information:
	 *		Useless if IMPLEMENTATION is set.
	 *
	 *		TODO: might be useful to cache this - although the design is to
	 *		annotate statements with whatever information might be useful later
	 *		on.
	 *
	 *		TODO: A better way to do this might be to write a PHP function which
	 *		'bakes' the result.
	 */

	Parameter_info_list* params;

	// The following properties do not take into account callbacks or magic
	// methods. So if (CAN_TOUCH_GLOBALS == false), a parameter can still be a
	// callback to eval. Parameters are via Parameter_info.

	// TODO: we'd probably prefer a list of globals that can be affected
	bool can_touch_globals;
	bool can_touch_locals;

	// TODO: model more of the return - types, values
	bool return_by_ref;




	bool has_implementation ()
	{
		return implementation != NULL;
	}

	bool has_parameters ()
	{
		if (implementation)
			return implementation->signature->formal_parameters->size () != 0;
		else
			return params->size () != 0;
	}

};


typedef List<Method_info*> Method_info_list;

#endif // PHC_METHOD_INFORMATION
