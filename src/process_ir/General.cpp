/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generic utilities for which the need is ubiquitous.
 */

#include "HIR.h"
#include "process_ir/General.h"
#include "pass_manager/Pass_manager.h"
#include "parsing/parse.h"

extern Pass_manager* pm;

List<HIR::Statement*>* lower_hir (String* name, HIR::Statement* in)
{
	HIR::PHP_script* script = new HIR::PHP_script (
			new List<HIR::Statement*> (in));

	assert (pm->has_pass_named (name));

	IR::PHP_script* new_script = pm->run_from_until (s("hir"), name, script);

	// TODO the typing is here is quite poor
	return dynamic_cast<HIR::PHP_script*>(new_script)->statements;
}

List<AST::Statement*>* lower_ast (String* name, AST::Statement* in)
{
	return lower_ast (name, new List<AST::Statement*> (in));
}

List<AST::Statement*>* lower_ast (String* name, List<AST::Statement*>* in)
{
	AST::PHP_script* script = new AST::PHP_script (in);

	assert (pm->has_pass_named (name));

	IR::PHP_script* new_script = pm->run_from_until (s("ast"), name, script);

	// TODO the typing is here is quite poor
	return dynamic_cast<AST::PHP_script*>(new_script)->statements;
}



List<HIR::Statement*>* parse_to_hir (String* code_string, HIR::Node* node)
{
	AST::PHP_script* ast = parse_code (code_string, node->get_filename (), node->get_line_number ());

	HIR::PHP_script* hir = pm->run_until (new String ("hir"), ast)->as_HIR ();

	return hir->statements;
}

List<AST::Statement*>* parse_to_ast (String* code_string, AST::Node* node)
{
	AST::PHP_script* ast = parse_code (code_string, node->get_filename (), node->get_line_number ());

	ast = pm->run_until (new String ("ast"), ast)->as_AST ();

	return ast->statements;
}

String* s (string str)
{
	return new String (str);
}
