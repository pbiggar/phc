/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Move statements from the main function into the global statement list.
 * Without this, uppered code will not work, since assignments to locals in
 * main will not update globals.
 */

#ifndef PHC_MAIN_UPPERING
#define PHC_MAIN_UPPERING

#include "MIR_visitor.h"

class Main_uppering : public MIR::Visitor, virtual public GC_obj
{
public:
	void post_php_script (MIR::PHP_script* in)
	{
		if (in->statements->size () > 0
			&& in->statements->back()->match (new MIR::Method (
				new MIR::Signature (
					new MIR::Wildcard<MIR::Method_mod>,
					false,
					false,
					new MIR::METHOD_NAME (s ("__MAIN__")),
					NULL),
				NULL)))
		{
			MIR::Method* main = dyc<MIR::Method> (in->statements->back());
			in->statements->pop_back ();

			in->statements->push_back_all (main->statements);
		}
	}
};

#endif // PHC_MAIN_UPPERING
