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
Debug_WPA::init (Context* outer)
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
Debug_WPA::forward_bind (Context* caller, Context* entry)
{
	DEBUG (__FUNCTION__ << caller << " to " << entry);
}

void
Debug_WPA::backward_bind (Context* caller, Context* exit)
{
	DEBUG (__FUNCTION__ << caller << " from " << exit);
}

void
Debug_WPA::pre_invoke_method (Context* caller)
{
	if (caller)
		DEBUG (__FUNCTION__ << " in " << caller);
	else
		DEBUG (__FUNCTION__ << " in outer scope" );
}

void
Debug_WPA::post_invoke_method (Context* caller)
{
	if (caller)
		DEBUG (__FUNCTION__ << " in " << caller);
	else
		DEBUG (__FUNCTION__ << " in outer scope" );
}


void
Debug_WPA::create_reference (Context* cx, const Index_node* lhs,
									  const Index_node* rhs, Certainty cert)
{
	DEBUG (__FUNCTION__
			<< ": " << lhs->str ()
			<< ", " << rhs->str ()
			<< ", " << cert_to_string (cert));
}

void
Debug_WPA::set_scalar (Context* cx, const Value_node* storage, const Abstract_value* val)
{
	CHECK_DEBUG ();

	cdebug
	<< __FUNCTION__
	<< ": " << storage->str ()
	<< ", ";

	val->dump();

	cdebug << endl;
}

void
Debug_WPA::set_storage (Context* cx, const Storage_node* storage, const Types* types)
{
	CHECK_DEBUG ();

	cdebug
	<< __FUNCTION__
	<< ": " << storage->str ()
	<< ", (";

	Type_info::dump_types (cdebug, types);

	cdebug << "), " << endl;
}

void
Debug_WPA::assign_value (Context* cx, const Index_node* lhs, const Storage_node* storage)
{
	DEBUG (__FUNCTION__
	<< ": " << lhs->str ()
	<< ", " << storage->str ()
	);
}


void
Debug_WPA::kill_value (Context* cx, const Index_node* lhs, bool also_kill_refs)
{
	DEBUG (__FUNCTION__
	<< (also_kill_refs ? " (and refs)" : "")
	<< ": " << lhs->str ());
}

void
Debug_WPA::record_use (Context* cx, const Index_node* use, Certainty cert)
{
	DEBUG (__FUNCTION__
	<< ": " << use->str ()
	<< ", " << cert_to_string (cert));
}


void
Debug_WPA::pull_init (Context* cx)
{
	DEBUG (__FUNCTION__ << " " << cx);
}

void
Debug_WPA::pull_first_pred (Context* cx, Context* pred)
{
	DEBUG (__FUNCTION__ << " from " << pred);
}

void
Debug_WPA::pull_pred (Context* cx, Context* pred)
{
	DEBUG (__FUNCTION__ << " from " << pred);
}

void
Debug_WPA::pull_possible_null (Context* cx, const Index_node* node)
{
	DEBUG (__FUNCTION__ << " for " << node->str());
}

void
Debug_WPA::pull_finish (Context* cx)
{
	DEBUG (__FUNCTION__ << " " << cx);
}


void
Debug_WPA::finish_block (Context* cx)
{
	DEBUG (__FUNCTION__ << " " << cx);
}

bool
Debug_WPA::solution_changed (Context* cx) const
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
Debug_WPA::dump (Context* cx, Result_state state, string comment) const
{
}


void
Debug_WPA::dump_everything (string comment) const
{
}

bool
Debug_WPA::has_analysis_result (Context* cx, Result_state) const
{
	return false;
}

void
Debug_WPA::merge_contexts ()
{
	DEBUG (__FUNCTION__);
}
