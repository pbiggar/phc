/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * After each statement, add a debug_zval_dump call to each variable in the statement.
 */

#include "AST_transform.h"
#include "process_ast/XML_unparser.h"
#include "process_ast/PHP_unparser.h"
#include "pass_manager/Pass_manager.h"
#include "lib/List.h"

/* After removing statements, we may be left with gotos and branches
 * to statements which dont exist, which will cause compiler errors.
 * Labels will leave warnings for unused labels, which also trip us
 * up. Unfortunately, those errors are percieved to be the sort of
 * thing we want to isolate, which they arent. So if we remove
 * something that involves a label, we want to remove other stuff
 * with that label in them. (this is the sort of thing you do if you
 * dont have data-flow :(). */
class Strip_labels : public AST_transform
{
	public:
		map<string, bool>* labels;

	Strip_labels (map<string, bool>* labels)
	{
		this->labels = labels;
	}

	void post_branch (AST_branch* in, List<AST_statement*>* out)
	{
		if (!remove_label (in->iftrue) && !remove_label (in->iffalse))
		{
			out->push_back (in);
		}
	}

	void post_goto (AST_goto* in, List<AST_statement*>* out)
	{
		if (!remove_label (in->label_name))
		{
			out->push_back (in);
		}
	}


	void post_label (AST_label* in, List<AST_statement*>* out)
	{
		if (!remove_label (in->label_name))
		{
			out->push_back (in);
		}
	}

	/* return true if the label should be removed */
	bool remove_label (Token_label_name* in)
	{
		return (labels->find (*in->value) != labels->end ());
	}

};

class Reduce : public AST_transform
{
	private:
		int start;
		int length;
		int index;

	public:
		map<string, bool>* labels;

	public:
		Reduce (int start, int length)
		{
			this->start = start;
			this->length = length;
			this->index = 0;
			this->labels = new map<string, bool> ();
		}

		// Only remove statements where its sub-statements have been removed
		// Declarations
		bool should_remove (AST_class_def* in)
		{
			return in->members->size () == 0;
		}

		bool should_remove (AST_interface_def* in)
		{
			return in->members->size () == 0;
		}

		bool should_remove (AST_method* in)
		{
			return in->statements->size () == 0;
		}

		// Control-flow with sub-statements
		bool should_remove (AST_if* in)
		{
			return in->iftrue->size () == 0 && in->iffalse->size () == 0;
		}

		bool should_remove (AST_while* in)
		{
			return in->statements->size () == 0;
		}

		bool should_remove (AST_do* in)
		{
			return in->statements->size () == 0;
		}

		bool should_remove (AST_for* in)
		{
			return in->statements->size () == 0;
		}
		
		bool should_remove (AST_foreach* in)
		{
			return in->statements->size () == 0;
		}

		bool should_remove (AST_switch* in)
		{
			return in->switch_cases->size () == 0;
		}

		bool should_remove (AST_switch_case* in)
		{
			return in->statements->size () == 0;
		}

		bool should_remove (AST_try* in)
		{
			return in->statements->size () == 0 && in->catches->size () == 0;
		}

		bool should_remove (AST_catch* in)
		{
			return in->statements->size () == 0;
		}



		// Catch everything else
		bool should_remove (AST_statement* in)
		{
			return true;
		}


		// Things which can be removed
		void post_statement (AST_statement *in, List<AST_statement*>* out)
		{
			potentially_remove<AST_statement> (in, out);

			// If we remove a label, remove everything associated with that label.
			// Otherwise we'll get compiler warnings and errors.
			if (AST_goto* go = dynamic_cast <AST_goto*> (in))
			{
				mark_label (go->label_name);
			}
			else if (AST_branch* branch = dynamic_cast <AST_branch*> (in))
			{
				mark_label (branch->iftrue);
				mark_label (branch->iffalse);
			}
			else if (AST_label* label = dynamic_cast <AST_label*> (in))
			{
				mark_label (label->label_name);
			}
		}

		void post_switch_case (AST_switch_case *in, List<AST_switch_case*>* out)
		{
			potentially_remove<AST_switch_case> (in, out);
		}

		void post_catch (AST_catch *in, List<AST_catch*>* out)
		{
			potentially_remove<AST_catch> (in, out);
		}



		template <class T>
		void potentially_remove (T* in, List<T*>* out)
		{
			if (!(index >= start && index < (start + length)) 
					|| !should_remove (in))
			{
				out->push_back (in);
			}

			this->index++;
		}


		void mark_label (Token_label_name* name)
		{
			(*labels)[*name->value] = true;
		}
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	// We arent interested in running any other passes on this.
	pm->clear ();
	pm->add_pass (pass);
}

extern "C" void run (AST_node* in, Pass_manager* pm, String* option)
{
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


	int start = 0;
	stringstream sss (start_string);
	sss >> start;

	int length = 0;
	stringstream lss (length_string);
	lss >> length;

	Reduce* red = new Reduce (start, length);
	in->transform_children (red);
	in->transform_children (new Strip_labels (red->labels));
}
