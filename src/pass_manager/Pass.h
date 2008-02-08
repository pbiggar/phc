/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Base class for Passes.
 */

#ifndef PHC_PASS_H
#define PHC_PASS_H

#include "process_ir/IR.h"
#include "lib/String.h"

class Pass_manager;

class Pass
{
public:
	Pass () : name (NULL), description(NULL), enabled(true) { }
	String* name;
	String* description;

public:

	virtual void run (IR* in, Pass_manager* pm) = 0;
	virtual void post_process () { }

private:
	bool enabled;

public:
	bool is_enabled (Pass_manager* pm) { return enabled && pass_is_enabled (pm); }
	void set_enabled (bool e) { enabled = e; }

	// Used for passes should use this
	virtual bool pass_is_enabled (Pass_manager* pm) { return true; }

	void run_pass (IR* in, Pass_manager* pm)
	{
		if (is_enabled (pm))
			run (in, pm);
	}

public:

	virtual ~Pass () {}

	// not sure how this should work
	Pass* clone () { assert (0); }
};

#endif // PHC_PASS_H
