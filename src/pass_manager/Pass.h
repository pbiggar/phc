/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Base class for Passes.
 */

#ifndef PHC_PASS_H
#define PHC_PASS_H

#include "lib/String.h"
#include "process_ir/IR.h"

class Pass_manager;

class Pass : virtual public GC_obj
{
public:
	Pass () : name (NULL), description(NULL), enabled(true) { }
	String* name;
	String* description;

public:

	virtual void run (IR::PHP_script* in, Pass_manager* pm) = 0;
	virtual void post_process () { }

private:
	// Passes should not play with this, and should instead use pass_is_enabled ().
	bool enabled;

public:
	bool is_enabled (Pass_manager* pm) { return enabled && pass_is_enabled (pm); }
	void set_enabled (bool e) { enabled = e; }

	// Passes should use this to control their activation
	virtual bool pass_is_enabled (Pass_manager* pm) { return true; }

	virtual void run_pass (IR::PHP_script* in, Pass_manager* pm, bool main)
	{
		if (is_enabled (pm))
			run (in, pm);
	}

public:

	virtual ~Pass () {}
};

#endif // PHC_PASS_H
