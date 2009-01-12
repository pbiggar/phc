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
	Parameter_info (bool is_ref, bool is_callback, String_list* magic_methods)
	: is_ref(is_ref)
	, is_callback (is_callback)
	, magic_methods (magic_methods)
	{
	}

	// Is the parameter passed by reference (compile-tim-pass-by-ref)
	bool is_ref;
	bool is_callback;

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
	Method_info (String* method_name, Parameter_info_list* params, bool is_pure, bool return_by_ref)
	: method_name (method_name)
	, implementation (NULL)
	, params (params)
	, return_by_ref (return_by_ref)
	, is_pure (is_pure)
	{
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
	bool return_by_ref;

	// This deliberately does not take magic methods into account. They are
	// modelled in Parameter_info.
	bool is_pure;

	/*
	 * Properties
	 */

	bool has_implementation ()
	{
		return implementation == NULL;
	}

	bool has_parameters ()
	{
		if (implementation)
			return implementation->signature->formal_parameters->size () == 0;
		else
			return params->size () == 0;
	}

};


typedef List<Method_info*> Method_info_list;

#endif // PHC_METHOD_INFORMATION
