/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Remove a given number of statements, from a given offset, to help reduce the problem size.
 */

#include "AST_transform.h"
#include "HIR_transform.h"
#include "MIR_transform.h"
#include "pass_manager/Plugin_pass.h"
#include "lib/List.h"

using namespace std;

/* After removing statements, we may be left with gotos and branches to
 * statements which dont exist, which will cause compiler errors. Labels will
 * leave warnings for unused labels, which also trip us up. Unfortunately,
 * those errors are percieved to be the sort of thing we want to isolate, which
 * they arent. So if we remove something that involves a label, we want to
 * remove other stuff with that label in them. (this is the sort of thing you
 * do if you dont have data-flow :().
 */

class Strip_labels : public MIR::Transform
{
public:
	Map<string, bool>* labels;

	Strip_labels (Map<string, bool>* labels)
	{
		this->labels = labels;
	}

	void post_branch (MIR::Branch* in, List<MIR::Statement*>* out)
	{
		if (!remove_label (in->iftrue) && !remove_label (in->iffalse))
		{
			out->push_back (in);
		}
	}

	void post_goto (MIR::Goto* in, List<MIR::Statement*>* out)
	{
		if (!remove_label (in->label_name))
		{
			out->push_back (in);
		}
	}


	void post_label (MIR::Label* in, List<MIR::Statement*>* out)
	{
		if (!remove_label (in->label_name))
		{
			out->push_back (in);
		}
	}

	// return true if the label should be removed
	bool remove_label (MIR::LABEL_NAME* in)
	{
		return (labels->find (*in->value) != labels->end ());
	}

};

#define REMOVABLE(TYPE,type)									\
	void post_##type (TYPE* in, List<Statement*>* out)	\
	{																	\
	}
#define REMOVABLE_CONTENTS(TYPE,type,CONTENT_NAME)		\
	void post_##type (TYPE* in, List<Statement*>* out)	\
	{																	\
		if (in->CONTENT_NAME->size() != 0)					\
			out->push_back (in);									\
	}

template <class Transform, class Statement>
class Reduce : public Transform
{
	// Common base - anything in the AST, HIR and MIR.
protected:
	int start;
	int length;
	int index;

public:
	Reduce (int start, int length)
	{
		this->start = start;
		this->length = length;
		this->index = 0;
	}

	// Things which can be removed
	void post_statement (Statement *in, List<Statement*>* out)
	{
		if (index >= start && index < (start + length))
			Transform::post_statement(in, out);
		else
			out->push_back (in);

		this->index++;
	}
};

class AST_reduce : public Reduce<AST::Transform, AST::Statement>
{
public:
	AST_reduce (int start, int length)
	: Reduce<AST::Transform, AST::Statement>(start, length)
	{
	}

	// Control-flow with sub-statements
	void pre_if (AST::If* in, AST::Statement_list* out)
	{
		if (in->iftrue->size () > 0 || in->iffalse->size () > 0)
			out->push_back (in);
	}
	void pre_switch_cases (AST::Switch_case* in, AST::Switch_case_list* cases)
	{
		if (in->statements->size () > 0)
			cases->push_back (in);
	}

	typedef AST::Statement Statement;
	REMOVABLE_CONTENTS (AST::Class_def, class_def, members);
	REMOVABLE_CONTENTS (AST::Declare, declare, statements);
	REMOVABLE_CONTENTS (AST::Do, do, statements);
	REMOVABLE_CONTENTS (AST::For, for, statements);
	REMOVABLE_CONTENTS (AST::Foreach, foreach, statements);
	REMOVABLE_CONTENTS (AST::Interface_def, interface_def, members);
	REMOVABLE_CONTENTS (AST::Method, method, statements);
	REMOVABLE_CONTENTS (AST::Switch, switch, switch_cases);
	REMOVABLE_CONTENTS (AST::Try, try, statements);
	REMOVABLE_CONTENTS (AST::While, while, statements);
	REMOVABLE (AST::Break, break);
	REMOVABLE (AST::Continue, continue);
	REMOVABLE (AST::Eval_expr, eval_expr);
	REMOVABLE (AST::Global, global);
	REMOVABLE (AST::Nop, nop);
	REMOVABLE (AST::Return, return);
	REMOVABLE (AST::Static_declaration, static_declaration);
	REMOVABLE (AST::Throw, throw);
};

class HIR_reduce : public Reduce <HIR::Transform, HIR::Statement>
{
public:
	HIR_reduce (int start, int length)
	: Reduce <HIR::Transform, HIR::Statement> (start, length)
	{
	}

	void pre_if (HIR::If* in, HIR::Statement_list* out)
	{
		if (in->iftrue->size () > 0 || in->iffalse->size () > 0)
			out->push_back (in);
	}

	typedef HIR::Statement Statement;
	REMOVABLE_CONTENTS (HIR::Class_def, class_def, members);
	REMOVABLE_CONTENTS (HIR::Foreach, foreach, statements);
	REMOVABLE_CONTENTS (HIR::Interface_def, interface_def, members);
	REMOVABLE_CONTENTS (HIR::Loop, loop, statements);
	REMOVABLE_CONTENTS (HIR::Method, method, statements);
	REMOVABLE_CONTENTS (HIR::Try, try, statements);
	REMOVABLE (HIR::Assign_array, assign_array);
	REMOVABLE (HIR::Assign_field, assign_field);
	REMOVABLE (HIR::Assign_next, assign_next);
	REMOVABLE (HIR::Assign_var, assign_var);
	REMOVABLE (HIR::Assign_var_var, assign_var_var);
	REMOVABLE (HIR::Break, break);
	REMOVABLE (HIR::Continue, continue);
	REMOVABLE (HIR::Eval_expr, eval_expr);
	REMOVABLE (HIR::Global, global);
	REMOVABLE (HIR::Pre_op, pre_op);
	REMOVABLE (HIR::Return, return);
	REMOVABLE (HIR::Static_declaration, static_declaration);
	REMOVABLE (HIR::Throw, throw);
};




class MIR_reduce : public Reduce<MIR::Transform, MIR::Statement>
{
public:
	MIR_reduce (int start, int length)
	: Reduce <MIR::Transform, MIR::Statement> (start, length)
	{
		labels = new Map<string, bool>;
	}

public:
	Map<string, bool>* labels;


	// Things which can be removed
	void post_statement (MIR::Statement *in, List<MIR::Statement*>* out)
	{
		Reduce<MIR::Transform, MIR::Statement>::post_statement (in, out);

		if (out->size() == 0 || out->back () != in)
		{
			// If we remove a label, remove everything associated with that label.
			// Otherwise we'll get compiler warnings and errors.
			if (MIR::Goto* go = dynamic_cast <MIR::Goto*> (in))
			{
				mark_label (go->label_name);
			}
			else if (MIR::Branch* branch = dynamic_cast <MIR::Branch*> (in))
			{
				mark_label (branch->iftrue);
				mark_label (branch->iffalse);
			}
			else if (MIR::Label* label = dynamic_cast <MIR::Label*> (in))
			{
				mark_label (label->label_name);
			}
		}
	}

	void mark_label (MIR::LABEL_NAME* name)
	{
		(*labels)[*name->value] = true;
	}

	typedef MIR::Statement Statement;
	REMOVABLE_CONTENTS (MIR::Class_def, class_def, members);
	REMOVABLE_CONTENTS (MIR::Interface_def, interface_def, members);
	REMOVABLE_CONTENTS (MIR::Method, method, statements);
	REMOVABLE_CONTENTS (MIR::Try, try, statements);
	REMOVABLE (MIR::Assign_array, assign_array);
	REMOVABLE (MIR::Assign_field, assign_field);
	REMOVABLE (MIR::Assign_next, assign_next);
	REMOVABLE (MIR::Assign_var, assign_var);
	REMOVABLE (MIR::Assign_var_var, assign_var_var);
	REMOVABLE (MIR::Eval_expr, eval_expr);
	// Leave in foreach_reset, foreach_next and foreach_end
	// TODO: remove them all if you remove one.
	REMOVABLE (MIR::Global, global);
	REMOVABLE (MIR::Pre_op, pre_op);
	REMOVABLE (MIR::Return, return);
	REMOVABLE (MIR::Static_declaration, static_declaration);
	REMOVABLE (MIR::Throw, throw);
	REMOVABLE (MIR::Unset, unset);
};


extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	// We want to run this immediately after the XML is read in, so we add it after every pass.
	pm->add_after_each_pass (pass);
}

void get_options (String* option, int* start, int* length)
{
	// Read START and LENGTH from the option string (\d+:\d+)
	int colon_index = -1;
	for (unsigned int i = 0; i < option->size (); i++)
	{
		if (option->at (i) == ':')
		{	
			colon_index = i;
			break;
		}
	}
	assert (colon_index != -1);

	string start_string = option->substr (0, colon_index);
	string length_string = option->substr (
			colon_index+1, 
			option->size () - colon_index);


	stringstream sss (start_string);
	sss >> *start;

	stringstream lss (length_string);
	lss >> *length;
}

static bool already = false;
extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
{
	if (already)
		exit (0); // just retuning means the pass is dumped many times.

	already = true;

	int start;
	int length;
	get_options (option, &start, &length);
	in->transform_children (new AST_reduce (start, length));
}

extern "C" void run_hir (HIR::PHP_script* in, Pass_manager* pm, String* option)
{
	if (already)
		exit (0);

	already = true;

	int start;
	int length;
	get_options (option, &start, &length);
	in->transform_children (new HIR_reduce (start, length));
}

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager* pm, String* option)
{
	if (already)
		exit (0);

	already = true;

	int start;
	int length;
	get_options (option, &start, &length);
	MIR_reduce* red = new MIR_reduce (start, length);
	in->transform_children (red);
	in->transform_children (new Strip_labels (red->labels));
}
