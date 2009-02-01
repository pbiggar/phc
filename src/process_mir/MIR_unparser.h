/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the MIR back to PHP syntax
 */

#ifndef PHC_MIR_UNPARSER
#define PHC_MIR_UNPARSER

#include "MIR_visitor.h"
#include "process_ast/AST_unparser.h"

class MIR_to_AST;

string unparse (MIR::Node* in);

class MIR_unparser : public virtual PHP_unparser, public virtual MIR::Visitor
{
	AST_unparser ast_unparser;

public:
	MIR_unparser (std::ostream& os = std::cout, bool in_php = false);
	MIR_unparser (Unparser_state* ups);

	void unparse (IR::Node* in);
	void unparse_uppered (IR::PHP_script* in);

	MIR_to_AST* folder;

public:
	void pre_foreign(MIR::FOREIGN* in);

	// handle MIR-only contructs here
	void children_foreach_reset(MIR::Foreach_reset* in);
	void children_foreach_next(MIR::Foreach_next* in);
	void children_foreach_end(MIR::Foreach_end* in);
	void children_foreach_has_key(MIR::Foreach_has_key* in);
	void children_foreach_get_key(MIR::Foreach_get_key* in);
	void children_foreach_get_val(MIR::Foreach_get_val* in);
	void children_ht_iterator(MIR::HT_ITERATOR* in);
	void children_variable_name (MIR::VARIABLE_NAME* in);


	void children_branch (MIR::Branch* in);
	void children_goto (MIR::Goto* in);
	void children_label (MIR::Label* in);
	void children_label_name(MIR::LABEL_NAME* in);
	void children_param_is_ref (MIR::Param_is_ref* in);
	void children_class_alias (MIR::Class_alias* in);
	void children_interface_alias (MIR::Interface_alias* in);
	void children_method_alias (MIR::Method_alias* in);
};

#endif // PHC_MIR_UNPARSER 
