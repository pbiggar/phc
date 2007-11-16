/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * List the passes the pass manager queue
 */

#ifndef PHC_LIST_PASSES_H
#define PHC_LIST_PASSES_H

#include "Pass.h"

class List_passes : public Pass
{
public:
	List_passes ()
	{
		this->name = new String ("lp");
	}

	void run (AST::AST_php_script* in, Pass_manager* pm)
	{
		pm->list_passes ();
	}

	bool pass_is_enabled (Pass_manager* pm)
	{
		return pm->args_info->list_passes_given;
	}
};

#endif // PHC_LIST_PASSES_H
