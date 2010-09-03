/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * 
 */

#include <iostream>
#include "AST_visitor.h"
#include "process_ast/AST_unparser.h"
#include "pass_manager/Plugin_pass.h"
#include "lib/List.h"
#include "process_ir/General.h"
#include <boost/algorithm/string.hpp>

using namespace AST;
using namespace std;
using namespace boost;

class Replace_include_constants : virtual public GC_obj, public Visitor
{
public:

	Map<string, string> def_dictionary;

	Replace_include_constants (String* option)
	{
		list<string> dict;	// List (capital 'L') doesn't support the necessary constructors for boost split
		string delim("|");
		split (dict, *option, is_any_of(delim));
		foreach (string entry, dict)
		{
			list<string> parsed_entry;
			split (parsed_entry, entry, is_any_of(","));
			def_dictionary[parsed_entry.front ()] = parsed_entry.back ();
		}
	}


	void post_bin_op (Bin_op* bop)
	{
		if (true || bop->op->value == s("."))
		{
			Constant* con;
			if ((con = dynamic_cast<Constant*> (bop->left)))
			{
				if (def_dictionary.has (*con->constant_name->value))
					bop->left = new STRING (s(def_dictionary[*con->constant_name->value]));			
			}
		
			if ((con = dynamic_cast<Constant*> (bop->right)))
			{
				if (def_dictionary.has (*con->constant_name->value))
					bop->right = new STRING (s(def_dictionary[*con->constant_name->value]));			
			}
		}
	}
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("incl1"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Replace_include_constants (option));
}
