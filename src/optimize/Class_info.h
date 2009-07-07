/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Try to model classes as accurately as possible.
 */

#ifndef PHC_CLASS_INFO_H
#define PHC_CLASS_INFO_H

#include <MIR.h>

DECL (Class_info);
DECL (Method_info);

class Whole_program;
class String;

class Class_info : virtual public GC_obj
{
public:
	String* name;
	String* lc_name;

	// TODO: the most important thing to model is handlers
	Method_info* get_method_info (String* name, bool search = true);

	virtual MIR::Attribute_list* get_attributes () = 0;

	Class_info* get_parent ();
	void set_parent (Class_info* parent);

	Method_info_list* get_methods ();

protected:
	Class_info (String* name);
	Class_info* parent;
	Map<string, Method_info*> methods;
};

class User_class_info : public Class_info
{
public:
	MIR::Class_def* class_def;

public:
	User_class_info (MIR::Class_def* implementation);
	MIR::Attribute_list* get_attributes ();
};

class Summary_class_info : public Class_info
{
public:
	Summary_class_info (String* name);
};

#endif // PHC_CLASS_INFO_H
