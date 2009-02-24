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

string
cert_to_string (certainty cert)
{
	if (cert == DEFINITE)
		return "DEFINITE";
	else if (cert == POSSIBLE)
		return "POSSIBLE";

	phc_unreachable ();
}

void
Debug_WPA::forward_bind (Basic_block* caller, Entry_block* entry)
{
	string bb_name = "__none__";
	if (caller)
		bb_name = ST (caller);

	DEBUG ("forward bind " << bb_name << " to " << ST (entry));
}

void
Debug_WPA::backward_bind (Basic_block* caller, Exit_block* exit)
{
	DEBUG (__FUNCTION__);
}


void
Debug_WPA::create_reference (Basic_block* bb, Index_node* lhs,
									  Index_node* rhs, certainty cert)
{
	DEBUG (__FUNCTION__
			<< ": " << lhs->name().str ()
			<< ", " << rhs->name().str ()
			<< ", " << cert_to_string (cert));
}

void
Debug_WPA::set_scalar (Basic_block* bb, Abstract_node* storage, Abstract_value* val)
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
Debug_WPA::set_storage (Basic_block* bb, Storage_node* storage, Types types)
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
Debug_WPA::assign_value (Basic_block* bb, Index_node* lhs, Storage_node* storage, certainty cert)
{
	DEBUG (__FUNCTION__
	<< ": " << lhs->name().str ()
	<< ", " << storage->name().str ()
	<< ", " << cert_to_string (cert));
}


void
Debug_WPA::kill_value (Basic_block* bb, Index_node* lhs)
{
	DEBUG (__FUNCTION__
	<< ": " << lhs->name().str ());
}

void
Debug_WPA::kill_reference (Basic_block* bb, Index_node* lhs)
{
	DEBUG (__FUNCTION__
	<< ": " << lhs->name().str ());
}
	
void
Debug_WPA::record_use (Basic_block* bb, Index_node* use, certainty cert)
{
	DEBUG (__FUNCTION__
	<< ": " << use->name().str ()
	<< ", " << cert_to_string (cert));
}


void
Debug_WPA::pull_init (Basic_block* bb)
{
	DEBUG (__FUNCTION__ << " " << bb->ID);
}

void
Debug_WPA::pull_first_pred (Basic_block* bb, Basic_block* pred)
{
	DEBUG (__FUNCTION__ << " from " << pred->ID);
}

void
Debug_WPA::pull_pred (Basic_block* bb, Basic_block* pred)
{
	DEBUG (__FUNCTION__ << " from " << pred->ID);
}

void
Debug_WPA::pull_finish (Basic_block* bb)
{
	DEBUG (__FUNCTION__ << " " << bb->ID);
}


void
Debug_WPA::aggregate_results (Basic_block* bb)
{
	DEBUG (__FUNCTION__ << " " << bb->ID);
}

bool
Debug_WPA::solution_changed (Basic_block* bb)
{
	DEBUG (__FUNCTION__ << " " << bb->ID);
	return false;
}

bool
Debug_WPA::equals (WPA* other)
{
	DEBUG (__FUNCTION__);
	return true;
}

void
Debug_WPA::dump (Basic_block* bb, string comment)
{
}
