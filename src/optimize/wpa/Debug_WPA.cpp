#include "Debug_WPA.h"

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
Debug_WPA::forward_bind (Basic_block* bb, CFG* callee_cfg,
										MIR::Actual_parameter_list* actuals,
										MIR::VARIABLE_NAME* retval)
{
	string bb_name = "__none__";
	if (bb)
		bb_name = ST (bb);

	DEBUG ("forward bind " << bb_name
				<< " to " << CFG_ST (callee_cfg));
}

void
Debug_WPA::backward_bind (Basic_block* bb, CFG* callee_cfg)
{
	DEBUG (__FUNCTION__);
}

void
Debug_WPA::assign_unknown (Basic_block* bb, Alias_name lhs, certainty cert)
{
	DEBUG (__FUNCTION__
			<< ": " << lhs.str ()
			<< ", " << cert_to_string (cert));
}

void
Debug_WPA::assign_unknown_typed (Basic_block* bb, Alias_name lhs,
									  string type, certainty cert)
{
	DEBUG (__FUNCTION__
			<< ": " << lhs.str ()
			<< ", " << type
			<< ", " << cert_to_string (cert));
}

void
Debug_WPA::assign_scalar (Basic_block* bb, Alias_name lhs,
							 MIR::Literal* rhs, certainty cert)
{
	DEBUG (__FUNCTION__
			<< ": " << lhs.str ()
			<< ", " << *rhs->get_value_as_string ()
			<< ", " << cert_to_string (cert));
}

void
Debug_WPA::assign_empty_array (Basic_block* bb, Alias_name lhs,
									string unique_name, certainty cert)
{
	DEBUG (__FUNCTION__
			<< ": " << lhs.str ()
			<< ", " << unique_name
			<< ", " << cert_to_string (cert));
}

void
Debug_WPA::assign_value (Basic_block* bb, Alias_name lhs,
							 Alias_name rhs, certainty cert)
{
	DEBUG (__FUNCTION__
			<< ": " << lhs.str ()
			<< ", " << rhs.str ()
			<< ", " << cert_to_string (cert));
}


void
Debug_WPA::assign_by_ref (Basic_block* bb, Alias_name lhs,
						 Alias_name rhs, certainty cert)
{
	DEBUG (__FUNCTION__
			<< ": " << lhs.str ()
			<< ", " << rhs.str ()
			<< ", " << cert_to_string (cert));
}

void
Debug_WPA::assign_by_copy (Basic_block* bb, Alias_name lhs,
							  Alias_name rhs, certainty cert)
{
	DEBUG (__FUNCTION__
			<< ": " << lhs.str ()
			<< ", " << rhs.str ()
			<< ", " << cert_to_string (cert));
}

void
Debug_WPA::kill_value (Basic_block* bb, Alias_name lhs)
{
	DEBUG (__FUNCTION__
		<< ": " << lhs.str ());
}

void
Debug_WPA::kill_by_copy (Basic_block* bb, Alias_name lhs)
{
	DEBUG (__FUNCTION__
		<< ": " << lhs.str ());
}

void
Debug_WPA::kill_by_ref (Basic_block* bb, Alias_name lhs)
{
	DEBUG (__FUNCTION__
		<< ": " << lhs.str ());
}
	
void
Debug_WPA::record_use (Basic_block* bb, Alias_name use,
									 certainty cert)
{
	DEBUG (__FUNCTION__
		<< ": " << use.str ()
		<< cert_to_string (cert));
}

void
Debug_WPA::pull_results (Basic_block* bb)
{
	DEBUG (__FUNCTION__);
}

void
Debug_WPA::aggregate_results (Basic_block* bb)
{
	DEBUG (__FUNCTION__);
}

bool
Debug_WPA::solution_changed (Basic_block* bb)
{
	DEBUG (__FUNCTION__);
	return false;
}

void
Debug_WPA::dump (Basic_block* bb)
{
	DEBUG (__FUNCTION__);
}
