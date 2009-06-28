/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Try to model functions as accurately as possible.
 */

#include "Method_info.h"
#include "Class_info.h"
#include "Basic_block.h"
#include "MIR.h"

using namespace MIR;

Method_info::Method_info (String* name)
: name (name)
, cfg (NULL)
{
	this->lc_name = name->to_lower ();
}


/*
 * User methods -- Internal methods are defined in optimize.cpp
 */

User_method_info::User_method_info (Method* method)
: Method_info (method->signature->method_name->value)
, class_info (NULL)
, method (method)
, side_effecting (true)
, has_self_parameter (false)
{
}

User_method_info::User_method_info (User_class_info* class_info, Method* method)
: Method_info (method->signature->method_name->value)
, class_info (class_info)
, method (method)
, side_effecting (true)
, has_self_parameter (false)
{
}

bool
User_method_info::has_implementation ()
{
	return true;
}

void
User_method_info::add_self_parameter ()
{
	this->has_self_parameter = true;

	method->signature->formal_parameters->push_front (
		new Formal_parameter (
			NULL,
			false,
			new Name_with_default (
				new VARIABLE_NAME ("this"),
				NULL)));
}

bool
User_method_info::return_by_ref ()
{
	return method->signature->return_by_ref;
}

bool
User_method_info::param_by_ref (int param_index)
{
	if ((unsigned int)(param_index+1)
			> method->signature->formal_parameters->size())
	{
		// TODO: remove pass_rest_by_ref
		return false;
	}
	else
	{
		return method->signature->formal_parameters->at (param_index)->is_ref;
	}
}

VARIABLE_NAME*
User_method_info::param_name (int param_index)
{
	if ((unsigned int)(param_index+1)
			> method->signature->formal_parameters->size())
	{
		return unnamed_param (param_index);
	}
	else
	{
		return method->signature->formal_parameters->at (
			param_index)->var->variable_name;
	}
}

Static_value*
User_method_info::default_param (int param_index)
{
	if ((unsigned int)(param_index+1) 
			> method->signature->formal_parameters->size())
		return NULL;
	else
	{
		return method->signature->formal_parameters->at (
			param_index)->var->default_value;
	}
}


void
User_method_info::set_side_effecting (bool side_effecting)
{
	this->side_effecting = side_effecting;
}

bool
User_method_info::get_side_effecting ()
{
	return side_effecting;
}

String*
UNNAMED (int param_index)
{
	return s ("__UNNAMED__" + lexical_cast<string> (param_index));
}


VARIABLE_NAME*
unnamed_param (int param_index)
{
	return new VARIABLE_NAME (UNNAMED (param_index));
}

int
User_method_info::formal_param_count ()
{
	return method->signature->formal_parameters->size ();
}

Method*
User_method_info::get_method ()
{
	if (this->has_self_parameter)
	{
		Formal_parameter_list* params = this->method->signature->formal_parameters;

		// Check the SELF parameter is there.
		assert (params->size () >= 1);
		assert (*params->front ()->var->variable_name->value == "this");

		// Remove it
		params->pop_front ();
	}

	return method;
}

Class_info*
User_method_info::get_class_info ()
{
	return class_info;
}

CFG*
User_method_info::get_cfg ()
{
	if (this->cfg == NULL)
		this->cfg = new CFG (this, this->method);

	return this->cfg;
}


/*
 * Summary methods
 */

Summary_method_info::Summary_method_info (String* name)
: Method_info (name)
{
}

CFG*
Summary_method_info::get_cfg ()
{
	if (this->cfg == NULL)
	{
		// We want to use the same BB every time, or else our analyses will
		// have different keys, and never converge.

		// This fakes the infrastructure we've built everything on.
		Method* method = 
			new Method (
					new Signature (
						this->name->c_str ()),
					new Statement_list);

		this->cfg = new CFG (this, method);

		// We use our summaries to apply on this block. We want to make sure
		// the forward_bind results are available, and that the backward_bind
		// ones are aggregated normally using the exit_block.
		Basic_block* fake = new Empty_block (this->cfg);
		this->cfg->replace_bb (
				this->cfg->get_exit_bb (), 
				new BB_list (fake, this->cfg->get_exit_bb ()));
	}

	return this->cfg;
}

Basic_block*
Summary_method_info::get_fake_bb ()
{
	assert (this->cfg);
	return this->cfg->get_entry_bb ()->get_successors ()->front();
}

Class_info*
Summary_method_info::get_class_info ()
{
	phc_TODO ();
}



/*
 * Builtins
 */


Builtin_method_info::Builtin_method_info (String* name)
: Summary_method_info (name)
{
}


bool
Builtin_method_info::has_implementation ()
{
	return false;
}

bool
Builtin_method_info::return_by_ref ()
{
	// I think this is true in all cases.
	return false;
}

bool
Builtin_method_info::param_by_ref (int param_index)
{
	// I think this is true in all cases.
	return false;
}

MIR::VARIABLE_NAME*
Builtin_method_info::param_name (int param_index)
{
	return unnamed_param (param_index);
}

MIR::Static_value*
Builtin_method_info::default_param (int param_index)
{
	return NULL;
}

bool
Builtin_method_info::get_side_effecting ()
{
	return true;
}

int
Builtin_method_info::formal_param_count ()
{
	return 0;
}


Class_info*
Builtin_method_info::get_class_info ()
{
	return NULL;
}
