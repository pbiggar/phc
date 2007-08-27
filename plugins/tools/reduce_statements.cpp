/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * After each statement, add a debug_zval_dump call to each variable in the statement.
 */

#include "AST_transform.h"
#include "process_ast/XML_unparser.h"
#include "process_ast/PHP_unparser.h"
#include "process_ast/Pass_manager.h"
#include "codegen/Shredder.h"
#include "codegen/fresh.h"
#include "lib/List.h"

class Reduce : public AST_transform
{
	private:
		int start;
		int finish;
		int count;

	public:
		Reduce (int start, int finish)
		{
			this->start = start;
			this->finish = finish;
			this->count = 0;
		}

		void post_statement (AST_statement *in, List<AST_statement*>* out)
		{
			if (count < start || count > finish)
				out->push_back (in);

			this->count++;
		}
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_before_named_pass (pass, "hir");
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
	string finish_string = option->substr (colon_index, option->size () - colon_index);

	cout << start_string << "-" << finish_string << endl;

	in->transform_children (new Reduce (0, 0));
}
