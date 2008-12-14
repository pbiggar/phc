/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Unparse the LIR back to C
 */

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include "LIR_unparser.h"
#include "embed/embed.h"

using namespace LIR;
using namespace std;
using namespace boost;

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

/*
 * In alphabetical order
 */

void
LIR_unparser::children_allocate (LIR::Allocate* in)
{
	assert (0);
}

void
LIR_unparser::children_api_call (LIR::API_CALL* in)
{
	assert (0);
}

void
LIR_unparser::children_assign_zvp (LIR::Assign_zvp* in)
{
	visit_zvp (in->lhs);
	echo (" = ");
	visit_zvp (in->rhs);
	echo (";");
}

void
LIR_unparser::children_assign_zvpp (LIR::Assign_zvpp* in)
{
	visit_zvpp (in->lhs);
	echo (" = ");
	visit_zvpp (in->rhs);
	echo (";");
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
LIR_unparser::children_clone (LIR::Clone* in)
{
	assert (0);
}

void
LIR_unparser::children_code (LIR::CODE* in)
{
//	echo ("{");
//	inc_indent ();
	echo (in->value);
//	dec_indent ();
//	echo_nl ("}");
}

void
LIR_unparser::children_comment (LIR::COMMENT* in)
{
	echo (in->value);
}

void
LIR_unparser::children_dec_ref (LIR::Dec_ref* in)
{
	assert (0);
}


void
LIR_unparser::children_declare (LIR::Declare* in)
{
	echo ("zval* ");
	visit_zvp (in->zvp);
	echo (";");
}

void
LIR_unparser::children_declare_p (LIR::Declare_p* in)
{
	echo ("zval** ");
	visit_zvpp (in->zvpp);
	echo (";");
}

void
LIR_unparser::children_deref (LIR::Deref* in)
{
	echo ("*(");
	visit_zvpp (in->zvpp);
	echo (")");
}

void
LIR_unparser::children_destruct (LIR::Destruct* in)
{
	assert (0);
}

void
LIR_unparser::children_equals (LIR::Equals* in)
{
	visit_zvp (in->lhs);
	echo (" == ");
	visit_zvp (in->rhs);
}

void
LIR_unparser::children_equals_p (LIR::Equals_p* in)
{
	visit_zvpp (in->lhs);
	echo (" == ");
	visit_zvpp (in->rhs);
}

void
LIR_unparser::children_if (LIR::If* in)
{
	echo ("if (");
	visit_cond (in->cond);
	echo (")");
	visit_statement_list (in->iftrue);
	if (in->iffalse->size ())
	{
		echo ("else");
		visit_statement_list (in->iffalse);
	}
}

void
LIR_unparser::children_inc_ref (LIR::Inc_ref* in)
{
	// TODO: use ADD_REF
	echo ("(");
	visit_zvp (in->zvp);
	echo (")->refcount++;");
}

void
LIR_unparser::children_intrinsic (LIR::INTRINSIC* in)
{
	assert (0);
}

void
LIR_unparser::children_is_ref (LIR::Is_ref* in)
{
	assert (0);
}

void
LIR_unparser::children_literal (LIR::LITERAL* in)
{
	assert (0);
}

void
LIR_unparser::children_not (LIR::Not* in)
{
	echo ("!(");
	visit_cond (in->cond);
	echo (")");
}

void
LIR_unparser::children_null (LIR::Null* in)
{
	echo ("NULL");
}

void
LIR_unparser::children_ref (LIR::Ref* in)
{
	echo ("&(");
	visit_zvp (in->zvp);
	echo (")");
}

void
LIR_unparser::children_separate (LIR::Separate* in)
{
	assert (0);
}

void
LIR_unparser::visit_statement_list (LIR::Statement_list* in)
{
	echo ("{");
	foreach (Statement* s, *in)
		visit_statement (s);
	echo ("}");
}

void
LIR_unparser::children_string (LIR::STRING* in)
{
	echo ("\"");
	echo (in->value);
	echo ("\"");
}

void
LIR_unparser::children_symtable (LIR::SYMTABLE* in)
{
	if (*in->value == "local")
		echo ("EG(active_symbol_table)");
	else
		echo ("&EG(symbol_table)");
}

void
LIR_unparser::children_symtable_fetch (LIR::Symtable_fetch* in)
{
	echo ("{");
	inc_indent ();

	echo ("int success = zend_hash_quick_find (");
	visit_symtable (in->symtable);
	echo (", ");
	visit_string (in->name);
	echo (", ");
	echo (lexical_cast<string> (in->name->value->size() + 1));
	echo (", ");
	echo (lexical_cast<string> (PHP::get_hash (in->name->value)));
	echo ("u, ");
	echo ("(void**) &(");
	visit_zvpp (in->zvpp);
	echo ("));\n");
	echo ("if (success != SUCCESS)");
	inc_indent ();
	echo ("{");
	visit_zvpp (in->zvpp);
	echo (" = NULL;");
	echo ("}");
	dec_indent ();

	dec_indent ();
	echo ("}");
}

void
LIR_unparser::children_symtable_insert (LIR::Symtable_insert* in)
{
	// TODO: Symtable_insert overwrites its ZVPP with a pointer into the
	// symtable. It looks desired, but could go wrong.
	echo ("{");
	inc_indent ();

	echo ("int success = zend_hash_quick_add (");
	visit_symtable (in->symtable);
	echo (", ");
	visit_string (in->name);
	echo (", ");
	echo (lexical_cast<string> (in->name->value->size() + 1));
	echo (", ");
	echo (lexical_cast<string> (PHP::get_hash (in->name->value)));
	echo ("u, ");
	visit_zvpp (in->zvpp);
	echo (", ");
	echo ("sizeof (zval*), ");
	echo ("(void**) &(");
	visit_zvpp (in->zvpp);
	echo ("));\n");
	echo ("assert (success == SUCCESS);");

	dec_indent ();
	echo ("}");
}

void
LIR_unparser::children_uninterpreted (LIR::UNINTERPRETED* in)
{
//	echo ("{");
//	inc_indent ();
	echo (in->value);
	echo_nl ("");
//	dec_indent ();
//	echo_nl ("}");
}

void
LIR_unparser::children_uninit (LIR::Uninit* in)
{
	echo ("EG(uninitialized_zval_ptr)");
}

void
LIR_unparser::children_zvp (LIR::ZVP* in)
{
	echo (in->value);
}

void
LIR_unparser::children_zvpp (LIR::ZVPP* in)
{
  echo ("p_");
  echo (in->value);
}

