/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Mark variables as definitely initialized, or definitely uninitialized, or maybe initialized.
 *
 * When we generate code, we wish to know if the variable was are
 * using/defining in already initialized. We wish to know:
 *		is the variable being defined already initialized?
 *		is the variable being used initialized?
 *
 *	Though SSA form guarantees that a variable only has a single initialization,
 *	we do not generate code in SSA form. Rather, we drop SSA indices and operate
 *	on the base names. So we need to propagate whether or not the _base_name_
 *	has been initialized, to each SSA name being defined.
 *
 *	When we drop SSA form, we lose PHI nodes. So we must not include PHI nodes
 *	as definitions. But we must propagate information through the phi nodes, or
 *	else uses in loops will not be correct.
 *
 *	So for each SSA NAME, we must know:
 *		at definition: (init,uninit,dont_know)
 *		at use: (init,uninit,dont_know)
 *
 *
 * Using the SCCP algorithm, we have a number of lattices maps:
 *		at-def: SSA_NAME -> (TOP/UNINIT | INIT | BOTTOM)
 *		at-use: SSA_NAME -> (TOP/UNINIT | INIT | BOTTOM)
 *
 * DEF and USE have different information. A USE that has a real (not a PHI or
 * CHI) definition will always be INIT. OTHERWISE, a DEF or USE receives
 * information the same way, through propagation.
 *
 * The lattice is TOP/UNINIT -> INIT -> BOTTOM. There are a lot of cases where
 * the same base_name may be UNINIT, then INIT, then BOTTOM, the UNINIT/INIT
 * again. However, this does not defy the lattice or break the monotinicty. The
 * lattice models the SSA_NAME, not the base_name, so different values for the
 * base_name are not a problem (also, they are not modelled directly).
 *
 * TODO: what about going through CHIs?
 *
 * TODO: this is another place that would benefit from splitting branches with
 * multiple predecessors (though it might be turned off in the case of space
 * constaints).
 *
 * TODO: it may be useful to initialize variables to ensure we know this in all
 * cases.
 */

#ifndef PHC_MARK_INITIALIZED
#define PHC_MARK_INITIALIZED


#include "Visit_once.h"

class Mark_initialized : public Visit_once
{
public:
//	void visit_assign_array (Statement_block* sb, MIR::Assign_array*);
//	void visit_assign_field (Statement_block* sb, MIR::Assign_field*);
	void visit_assign_var (Statement_block* sb, MIR::Assign_var*);
/*	void visit_assign_var_var (Statement_block* sb, MIR::Assign_var_var*);
	void visit_eval_expr (Statement_block* sb, MIR::Eval_expr*);
	void visit_global (Statement_block* sb, MIR::Global*);
	void visit_assign_next (Statement_block* sb, MIR::Assign_next*);
	void visit_return (Statement_block* sb, MIR::Return*);
	void visit_static_declaration (Statement_block* sb, MIR::Static_declaration*);
	void visit_try (Statement_block* sb, MIR::Try*);
	void visit_throw (Statement_block* sb, MIR::Throw*);

	void visit_array_access (Statement_block* bb, MIR::Array_access* in);
	void visit_field_access (Statement_block* bb, MIR::Field_access* in);
	void visit_foreach_get_key (Statement_block* bb, MIR::Foreach_get_key* in);
	void visit_foreach_get_val (Statement_block* bb, MIR::Foreach_get_val* in);
	void visit_foreach_has_key (Statement_block* bb, MIR::Foreach_has_key* in);
	void visit_instanceof (Statement_block* bb, MIR::Instanceof* in);
	void visit_isset (Statement_block* bb, MIR::Isset* in);
	void visit_method_invocation (Statement_block* bb, MIR::Method_invocation* in);
	void visit_new (Statement_block* bb, MIR::New* in);
	void visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in);
*/


};

#endif // PHC_ADDRESS_TAKEN
