/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Make implicit parts of a script explicit for the Code Generator.
 */

#ifndef PHC_CLARIFY_H
#define PHC_CLARIFY_H

#include "AST_visitor.h"

class Clarify : public AST::Visitor
{
	// TODO: deal with all superglobals 
	// TODO: _ENV
	// TODO: HTTP_ENV_VARS
	// TODO: _POST
	// TODO: HTTP_POST_VARS
	// TODO: _GET
	// TODO: HTTP_GET_VARS
	// TODO: _COOKIE
	// TODO: HTTP_COOKIE_VARS
	// TODO: _FILES
	// TODO: HTTP_POST_FILES
	// TODO: _REQUEST

	void post_method (AST::Method* in)
	{
		AST::Global* global = 
			new AST::Global (
				new List<AST::Variable_name*> (
					new AST::VARIABLE_NAME (
						new String ("GLOBALS"))));

		if (in->statements)
			in->statements->push_front (global);
		else
			in->statements = new List<AST::Statement*> (global);
	}
};


#endif // PHC_CLARIFY_H
