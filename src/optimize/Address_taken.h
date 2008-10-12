/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Simple alias analysis using address-taken semantics. If any variable is, or
 * may be, passed by reference, consider it part of the alias-set, all members
 * of which alias each other.
 */

#ifndef PHC_ADDRESS_TAKEN
#define PHC_ADDRESS_TAKEN


#include "Visit_once.h"

/*
 * Address-taken alias analysis on virtual variables. Aliases are created for two purposes:
 *		1) They are (or can be) involved in an addressing operation (ie & appears).
 *		2) They can refer to abstract variables (say, $a[$i] or $x->f)
 *
 *	For simplicity, we create virtual variables in both cases. This means all
 *	alias-analysis is on virtuals.
 *
 *	In C, you would include scalars and virtuals, virtuals for constructs
 *	which do not have a variable representation (ie *p or a[i]), and scalars
 *	in cases where scalars have their addresses taken (ie x in p = &x).
 *
 *	We have that option for PHP too, as we really only need virtuals for
 *	things we dont have a syntactic representation for. If theres a good
 *	reason, we'll switch back to this representation.
 */

class Address_taken : public Visit_once
{
public:
	Address_taken ();

	Set* aliases;

public:
	void alias_expr (Basic_block* bb, MIR::Expr*);
	void alias_bottom (Basic_block* bb);
	void aliased (Basic_block* bb, MIR::Variable_name*);
	void aliased (Basic_block* bb, MIR::Rvalue*);
	void aliased (Basic_block* bb, MIR::VARIABLE_NAME*);

	void visit_entry_block (Entry_block*);

	void visit_assign_array (Statement_block* sb, MIR::Assign_array*);
	void visit_assign_field (Statement_block* sb, MIR::Assign_field*);
	void visit_assign_var (Statement_block* sb, MIR::Assign_var*);
	void visit_assign_var_var (Statement_block* sb, MIR::Assign_var_var*);
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
	void visit_param_is_ref (Statement_block* bb, MIR::Param_is_ref* in);
	void visit_variable_variable (Statement_block* bb, MIR::Variable_variable* in);



};

#endif // PHC_ADDRESS_TAKEN
