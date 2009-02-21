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

	void forward_bind (Basic_block* bb, Entry_block* entry);
	void backward_bind (Basic_block* bb, Exit_block* exit);


	void create_reference (Basic_block* bb, Alias_name lhs,
								  Alias_name rhs, certainty cert);

	void assign_scalar (Basic_block* bb, Alias_name lhs, Alias_name lhs_storage,
							 Abstract_value* val, certainty cert);

	void assign_storage (Basic_block* bb, Alias_name lhs,
								Alias_name storage, certainty cert);

	void assign_empty_array (Basic_block* bb, Alias_name lhs,
									string unique_name, certainty cert);

	void kill_value (Basic_block* bb, Alias_name name);

	void kill_reference (Basic_block* bb, Alias_name name);
	
	void record_use (Basic_block* bb, Alias_name use,
									 certainty cert);

	void pull_init (Basic_block* bb);
	void pull_first_pred (Basic_block* bb, Basic_block* pred);
	void pull_pred (Basic_block* bb, Basic_block* pred);
	void pull_finish (Basic_block* bb);

	void aggregate_results (Basic_block* bb);

	bool solution_changed (Basic_block* bb);

	bool equals (WPA* other);
	void dump (Basic_block* bb, string comment);
};


#endif // DEBUG_WPA
