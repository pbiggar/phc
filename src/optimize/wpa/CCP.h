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

	void set_storage (Context cx, Storage_node* storage, Types types);

	void set_scalar (Context cx, Value_node* storage, Abstract_value* val);

	void pull_possible_null (Context cx, Index_node* node);


	// CCP-specific
	bool branch_known_true (Context cx, Alias_name cond);
	bool branch_known_false (Context cx, Alias_name cond);

	MIR::Literal* get_lit (Context cx, Alias_name name);

};

#endif // PHC_CCP
