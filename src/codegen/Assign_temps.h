/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Assign temporaries 
 */

#ifndef PHC_ASSIGN_TEMPS_H
#define PHC_ASSIGN_TEMPS_H

#include "AST_visitor.h"

class Assign_temps : public AST_visitor
{
public:
	Assign_temps();

public:
	void pre_expr(AST_expr* in);

protected:
	int nextFresh;
	String* fresh();
};

#endif // PHC_ASSIGN_TEMPS_H
