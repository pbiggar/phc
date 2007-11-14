/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Make note of top-level function, class and interface declarations
 */

#ifndef NOTE_TOP_LEVEL_DECLARATIONS_H
#define NOTE_TOP_LEVEL_DECLARATIONS_H

#include "AST_visitor.h"

class Note_top_level_declarations : public virtual AST::AST_visitor
{
	void pre_php_script (AST::AST_php_script* in);
};

#endif // NOTE_TOP_LEVEL_DECLARATIONS_H
