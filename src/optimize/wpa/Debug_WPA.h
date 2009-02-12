/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A simple pass printing debugging information. The idea is that you can use
 * --debug=debug-wpa to see what Whole_program is calling.
 */

#ifndef PHC_DEBUG_WPA
#define PHC_DEBUG_WPA

#include "WPA.h"

class Debug_WPA : public WPA
{
public:

	Debug_WPA (Whole_program* wp);

	void forward_bind (Basic_block* bb, CFG* callee_cfg,
										MIR::Actual_parameter_list* actuals,
										MIR::VARIABLE_NAME* retval);

	void backward_bind (Basic_block* bb, CFG* callee_cfg);

	void assign_unknown (Basic_block* bb, Alias_name name, certainty cert);

	void assign_unknown_typed (Basic_block* bb, Alias_name name,
									   Types types, certainty cert);

	void assign_scalar (Basic_block* bb, Alias_name lhs,
							 MIR::Literal* rhs, certainty cert);

	void assign_empty_array (Basic_block* bb, Alias_name lhs,
									string unique_name, certainty cert);

	void assign_value (Basic_block* bb, Alias_name lhs,
							 Alias_name rhs, certainty cert);


	void assign_by_ref (Basic_block* bb, Alias_name lhs,
							 Alias_name rhs, certainty cert);

	void assign_by_copy (Basic_block* bb, Alias_name lhs,
							  Alias_name rhs, certainty cert);

	void kill_value (Basic_block* bb, Alias_name name);

	void kill_by_copy (Basic_block* bb, Alias_name name);

	void kill_by_ref (Basic_block* bb, Alias_name name);
	
	void record_use (Basic_block* bb, Alias_name use,
									 certainty cert);

	void pull_results (Basic_block* bb);

	void aggregate_results (Basic_block* bb);

	bool solution_changed (Basic_block* bb);

	bool equals (WPA* other);
	void dump (Basic_block* bb);
};


#endif // DEBUG_WPA
