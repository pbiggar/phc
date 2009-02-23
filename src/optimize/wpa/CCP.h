/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Conditional constant propagation.
 *
 * In theory this is Wegbreits conditional constant propagation, but I'm just
 * going to steal the implementation from SCCP, so its a step forward, and then
 * one back, which will probably land in about the same place.
 *
 */

#ifndef PHC_CCP
#define PHC_CCP

#include "WPA_lattice.h"

class CCP : public WPA_lattice
{
public:
	CCP (Whole_program* wp);

	void set_storage (Basic_block* bb, Storage_node* storage, Types types);

	void set_scalar (Basic_block* bb, Abstract_node* storage,
						  Abstract_value* val);



	// CCP-specific
	bool branch_known_true (Basic_block* bb, Alias_name cond);
	bool branch_known_false (Basic_block* bb, Alias_name cond);

	MIR::Literal* get_lit (Basic_block* bb, Alias_name name);

};

#endif // PHC_CCP
