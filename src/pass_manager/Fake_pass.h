/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A pass which does nothing when run () is called. This serves to add named
 * points in the Pass queue, so that, for example, you can use "--dump=ast", or
 * add_after_named_pass ("ast").
 */


#ifndef PHC_FAKE_PASS_H
#define PHC_FAKE_PASS_H

#include "pass_manager/Pass.h"

class Fake_pass : public Pass
{
	public:
	Fake_pass (String* name, String* description)
	{
		this->name = name;
		this->description = description;
	}

	void run (IR::PHP_script*, Pass_manager*) {}
};


#endif // PHC_FAKE_PASS_H
