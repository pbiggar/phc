/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the LIR back to C
 */

#include <boost/lexical_cast.hpp>

#include "LIR_unparser.h"

using namespace LIR;
using namespace std;

LIR_unparser::LIR_unparser (ostream& os, bool in_php)
: PHP_unparser (os, in_php)
{
}

LIR_unparser::LIR_unparser (Unparser_state* ups)
: PHP_unparser (ups)
{
}

void
LIR_unparser::unparse (IR::Node* in)
{
	Node* lir = dyc<Node> (in);
	lir->visit (this);
}

void
LIR_unparser::post_uninterpreted (LIR::UNINTERPRETED* in)
{
//	echo ("{");
//	inc_indent ();
	echo (in->value);
	echo_nl ("");
//	dec_indent ();
//	echo_nl ("}");
}

void
LIR_unparser::post_code (LIR::CODE* in)
{
//	echo ("{");
//	inc_indent ();
	echo (in->value);
//	dec_indent ();
//	echo_nl ("}");
}

void
LIR_unparser::pre_comment (LIR::COMMENT* in)
{
	echo (in->value);
}

void
LIR_unparser::children_block (LIR::Block* in)
{
	// TODO: brackets should depend on the pattern - maybe a Scope construct?
	// TODO: move the comment escaping here
	
	visit_comment (in->comment);
	echo ("{");
	inc_indent ();

	visit_statement_list (in->statements);
	echo_nl ("phc_check_invariants (TSRMLS_C);");

	dec_indent ();
	echo_nl ("}");
}

void
LIR_unparser::children_statement_list (Statement_list* in)
{
	echo ("{");
	foreach (Statement* s, *in)
		visit_statement (s);
	echo ("}");
}


void
LIR_unparser::children_if (LIR::If* in)
{
	echo ("if (");
	visit_cond (in->cond);
	echo (")");
	visit_statement_list (in->iftrue);
	visit_statement_list (in->iffalse);
}

void
LIR_unparser::children_equals (LIR::Equals* in)
{
	visit_zvp (in->lhs);
	echo (" == ");
	visit_zvp (in->rhs);
}

void
LIR_unparser::children_not_equals (LIR::Not_equals* in)
{
	visit_zvp (in->lhs);
	echo (" != ");
	visit_zvp (in->rhs);
}



void
LIR_unparser::children_zvp (LIR::ZVP* in)
{
	echo (in->value);
}

void
LIR_unparser::children_zvpp (LIR::ZVPP* in)
{
	echo (in->value);
}

void
LIR_unparser::children_deref (LIR::Deref* in)
{
	echo ("*(");
	visit_zvpp (in->zvpp);
	echo (")");
}


void
LIR_unparser::children_ref (LIR::Ref* in)
{
	echo ("&(");
	visit_zvp (in->zvp);
	echo (")");
}


