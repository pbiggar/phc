/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the LIR to C
 */

#ifndef PHC_LIR_UNPARSER
#define PHC_LIR_UNPARSER

#include "LIR_visitor.h"
#include "process_ir/PHP_unparser.h"

class LIR_unparser : public virtual PHP_unparser, public virtual LIR::Visitor
{
public:
	LIR_unparser (std::ostream& os = std::cout);
	LIR_unparser (Unparser_state* ups);

	void unparse (IR::Node* in);

public:

	void children_allocate (LIR::Allocate* in);
	void children_api_call (LIR::API_CALL* in);
	void children_assign_zvp (LIR::Assign_zvp* in);
	void children_assign_zvpp (LIR::Assign_zvpp* in);
	void children_block (LIR::Block* in);
	void children_clone (LIR::Clone* in);
	void children_code (LIR::CODE* in);
	void children_comment (LIR::COMMENT* in);
	void children_declare (LIR::Declare* in);
	void children_declare_p (LIR::Declare_p* in);
	void children_dec_ref (LIR::Dec_ref* in);
	void children_deref (LIR::Deref* in);
	void children_destruct (LIR::Destruct* in);
	void children_equals (LIR::Equals* in);
	void children_equals_p (LIR::Equals_p* in);
	void children_if (LIR::If* in);
	void children_inc_ref (LIR::Inc_ref* in);
	void children_int (LIR::INT* in);
	void children_intrinsic (LIR::INTRINSIC* in);
	void children_in_change_on_write (LIR::In_change_on_write* in);
	void children_in_copy_on_write (LIR::In_copy_on_write* in);
	void children_is_ref (LIR::Is_ref* in);
	void children_literal (LIR::LITERAL* in);
	void children_not (LIR::Not* in);
	void children_null (LIR::Null* in);
	void children_overwrite (LIR::Overwrite* in);
	void children_profile (LIR::Profile* in);
	void children_ref (LIR::Ref* in);
	void children_separate (LIR::Separate* in);
	void children_set_is_ref (LIR::Set_is_ref* in);
	void children_string (LIR::STRING* in);
	void children_symtable_fetch (LIR::Symtable_fetch * in);
	void children_symtable_insert (LIR::Symtable_insert* in);
	void children_symtable (LIR::SYMTABLE* in);
	void children_uninit (LIR::Uninit* in);
	void children_uninterpreted (LIR::UNINTERPRETED* in);
	void children_zvp (LIR::ZVP* in);
	void children_zvpp (LIR::ZVPP* in);
	void visit_statement_list (LIR::Statement_list* in);
	void visit_null (const char* ns, const char* type_id)
	{
		assert (0);
	}

};

#endif // PHC_LIR_UNPARSER 
