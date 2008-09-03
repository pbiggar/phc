
#include "MIR_visitor.h"
#include "process_ir/debug.h"

#include "Def_use.h"

using namespace MIR;

class Def_use_visitor : public MIR::Visitor
{
public:
	Set* defs;
	Set* uses;
	bool handled;
public:
	Def_use_visitor ()
	{
		defs = new Set;
		uses = new Set;
		handled = false;
	}

	void use (Rvalue* in)
	{
		if (isa<VARIABLE_NAME> (in))
			uses->insert (dyc<VARIABLE_NAME> (in));
	}

	void pre_pre_op (Pre_op* in)
	{
		defs->insert (in->variable_name);
		uses->insert (in->ssa_use);
		handled = true;
	}

	void pre_actual_parameter (Actual_parameter* in)
	{
		use (in->rvalue);
		handled = true;
	}

	void pre_assign_var (Assign_var* in)
	{
		defs->insert (in->lhs);
		if (isa<VARIABLE_NAME> (in->rhs) || isa<Literal> (in->rhs))
			handled = true;
	}

	void pre_bin_op (Bin_op* in)
	{
		use (in->left);
		use (in->right);
		handled = true;
	}

	void pre_unary_op (Unary_op* in)
	{
		use (in->variable_name);
		handled = true;
	}

	void pre_global (Global* in)
	{
		
		if (VARIABLE_NAME* vn = dynamic_cast<VARIABLE_NAME*> (in->variable_name))
			defs->insert (vn);
		else
		{
			// what's defined here?
			uses->insert (dyc<Variable_variable> (in)->variable_name);
		}

		handled = true;
	}

	/* Leave this in until this works */
	void post_statement (Statement* in)
	{
		if (!handled)
		{
			debug (in);
			xdebug (in);
		}
		assert (handled);
	}
};

Set*
Def_use::get_defs (Statement* in)
{
	Def_use_visitor* duv = new Def_use_visitor;
	in->visit (duv);
	return duv->defs;
}

Set*
Def_use::get_uses (Statement* in)
{
	Def_use_visitor* duv = new Def_use_visitor;
	in->visit (duv);
	return duv->uses;
}
