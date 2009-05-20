/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * A simple pass printing debugging information. The idea is that you can use
 * --debug=debug-wpa to see what Whole_program is calling.
 */


#include "Debug_WPA.h"
#include "optimize/Abstract_value.h"
#include "Points_to.h"

using namespace std;


Debug_WPA::Debug_WPA (Whole_program* wp)
: WPA (wp)
{
	DEBUG (__FUNCTION__);
}


void
Debug_WPA::init (Context outer)
{
	DEBUG (__FUNCTION__ << ": " << outer);
}

string
cert_to_string (Certainty cert)
{
	if (cert == DEFINITE)
		return "DEFINITE";
	else if (cert == POSSIBLE)
		return "POSSIBLE";

	phc_unreachable ();
}

void
Debug_WPA::forward_bind (Context caller, Context entry)
{
	DEBUG ("forward bind " << caller << " to " << entry);
}

void
Debug_WPA::backward_bind (Context caller, Context exit)
{
	DEBUG (__FUNCTION__);
}


void
Debug_WPA::create_reference (Context cx, Index_node* lhs,
									  Index_node* rhs, Certainty cert)
{
	DEBUG (__FUNCTION__
			<< ": " << lhs->name().str ()
			<< ", " << rhs->name().str ()
			<< ", " << cert_to_string (cert));
}

void
Debug_WPA::set_scalar (Context cx, Value_node* storage, Abstract_value* val)
{
	CHECK_DEBUG ();

	cdebug
	<< __FUNCTION__
	<< ": " << storage->name().str ()
	<< ", ";

	val->dump();

	cdebug << endl;
}

void
Debug_WPA::set_storage (Context cx, Storage_node* storage, Types types)
{
	CHECK_DEBUG ();

	cdebug
	<< __FUNCTION__
	<< ": " << storage->name().str ()
	<< ", (";

	(new Type_cell(types))->dump (cdebug);

	cdebug << "), " << endl;
}

void
Debug_WPA::assign_value (Context cx, Index_node* lhs, Storage_node* storage, Certainty cert)
{
	DEBUG (__FUNCTION__
	<< ": " << lhs->name().str ()
	<< ", " << storage->name().str ()
	<< ", " << cert_to_string (cert));
}


void
Debug_WPA::kill_value (Context cx, Index_node* lhs)
{
	DEBUG (__FUNCTION__
	<< ": " << lhs->name().str ());
}

void
Debug_WPA::kill_reference (Context cx, Index_node* lhs)
{
	DEBUG (__FUNCTION__
	<< ": " << lhs->name().str ());
}
	
void
Debug_WPA::record_use (Context cx, Index_node* use, Certainty cert)
{
	DEBUG (__FUNCTION__
	<< ": " << use->name().str ()
	<< ", " << cert_to_string (cert));
}


void
Debug_WPA::pull_init (Context cx)
{
	DEBUG (__FUNCTION__ << " " << cx);
}

void
Debug_WPA::pull_first_pred (Context cx, Context pred)
{
	DEBUG (__FUNCTION__ << " from " << pred);
}

void
Debug_WPA::pull_pred (Context cx, Context pred)
{
	DEBUG (__FUNCTION__ << " from " << pred);
}

void
Debug_WPA::pull_possible_null (Context cx, Index_node* node)
{
	DEBUG (__FUNCTION__ << " for " << node->name().str());
}

void
Debug_WPA::pull_finish (Context cx)
{
	DEBUG (__FUNCTION__ << " " << cx);
}


void
Debug_WPA::aggregate_results (Context cx)
{
	DEBUG (__FUNCTION__ << " " << cx);
}

bool
Debug_WPA::solution_changed (Context cx)
{
	DEBUG (__FUNCTION__ << " " << cx);
	return false;
}

bool
Debug_WPA::equals (WPA* other)
{
	DEBUG (__FUNCTION__);
	return true;
}

void
Debug_WPA::dump (Context cx, string comment)
{
}


void
Debug_WPA::dump_everything (string comment)
{
}


void
Debug_WPA::merge_contexts ()
{
	DEBUG (__FUNCTION__);
}
