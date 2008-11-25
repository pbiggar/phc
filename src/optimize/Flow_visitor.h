/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Base class for data-flow analyses.
 */

#ifndef PHC_FLOW_VISITOR
#define PHC_FLOW_VISITOR

#include "process_ir/General.h"

#include "CFG.h"
#include "CFG_visitor.h"
#include "Basic_block.h"

/* Direction chooses whether the worklist operates from backwards from Exit,
 * or forwards from Entry. */
enum Flow_visitor_direction { FORWARD_FLOW, BACKWARD_FLOW };

class Flow_visitor : public CFG_visitor
{
private:
	Flow_visitor_direction direction;

protected:
	Flow_visitor (Flow_visitor_direction direction);

public:
	/* Public interface for analyses */
	void run (CFG* cfg);
	virtual void init_block (Basic_block*) {}
	virtual bool solution_has_changed (Basic_block*) { return false; }
	virtual void post_pass (CFG* cfg);

	/* Transfer functions */
	virtual void transfer_in (Basic_block*, BB_list*) {};
	virtual void transfer_out (Basic_block*, BB_list*) {};

private:
	/* Calculate the local solution */
	BB_list* get_next_cfg_nodes (Basic_block* bb, CFG* cfg);
	void visit_transfer_functions (Basic_block* bb, CFG* cfg);
	BB_list* get_initial_worklist (CFG* cfg);
};

class Forward_flow_visitor : public Flow_visitor
{
public:
	Forward_flow_visitor () : Flow_visitor (FORWARD_FLOW) {}
};

class Backward_flow_visitor : public Flow_visitor
{
public:
	Backward_flow_visitor  () : Flow_visitor (BACKWARD_FLOW) {}
};


#endif // PHC_FLOW_VISITOR
