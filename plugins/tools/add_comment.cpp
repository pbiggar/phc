/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * After each statement, add a debug_zval_dump call to each variable in the statement.
 */

#include "pass_manager/Plugin_pass.h"
#include "AST.h"
#include "process_ir/General.h"

using namespace AST;

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_pass (pass);
}

static bool already = false;
extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
{
	// Cant put comments into HIR
	if (already)
		exit (0); // just retuning means the pass is dumped many times.

	String* comment = new String ("// ");
	comment->append (*option);
	// Add a comment to the first statement
	if (in->statements->size () == 0)
	{
		// create a statement for the comment
		Nop* nop = new Nop ();
		nop->get_comments()->push_front (comment);
	}
	else
	{
		// attach the comment to the first statement
		in->statements->front ()->get_comments ()->push_front (comment);
	}
	already = true;
}


extern "C" void run_hir (HIR::PHP_script* in, Pass_manager* pm, String* option)
{
	// Cant put comments into HIR
	if (already)
		exit (0); // just retuning means the pass is dumped many times.

	already = true;
}


extern "C" void run_mir (MIR::PHP_script* in, Pass_manager* pm, String* option)
{
	// Cant put comments into MIR
	if (already)
		exit (0); // just retuning means the pass is dumped many times.

	already = true;
}
