/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Special-case for optimizing for-loops and do-while loops, as a result of
 * the strange tricks in Early_flow_control_flow.cpp. See much longer comment
 * in Remove_loop_booleans.cpp.
  */

#ifndef PHC_REMOVE_LOOP_BOOLEANS 
#define PHC_REMOVE_LOOP_BOOLEANS

#include "Visit_once.h"

class Remove_loop_booleans : public Visit_once
{
public:
	void visit_branch_block (Branch_block*);
	bool is_applicable_branch (Branch_block*);
};

#endif // PHC_REMOVE_LOOP_BOOLEANS
