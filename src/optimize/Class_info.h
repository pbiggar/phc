/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Try to model classes as accurately as possible.
 */

#ifndef PHC_CLASS_INFO_H
#define PHC_CLASS_INFO_H

DECL (Class_info);
DECL (Method_info);

class Whole_program;
class String;

class Class_info : virtual public GC_obj
{
public:
	String* name;

	// TODO: what would we use this for?
	virtual bool has_implementation () = 0;

	virtual Method_info* get_method_info (String* name, bool search = true) = 0;

	// TODO: the most important thing to model is handlers

protected:
	Class_info (String* name);
};

class User_class_info : public Class_info
{
public:
	MIR::Class_def* class_def;

private:

	Map<string, Method_info*> methods;


public:
	User_class_info (MIR::Class_def* implementation);

	virtual Method_info* get_method_info (String* name, bool search = true);

	bool has_implementation ();

};

class Summary_class_info : public Class_info
{
public:
	Summary_class_info (String* name);
};

/*
 * TODO: we may not need builtins if stdClass can be handled by Internal
 */
class Builtin_class_info : public Summary_class_info
{
public:
	Builtin_class_info (String* name);

	bool has_implementation ();
};

#endif // PHC_CLASS_INFO_H
