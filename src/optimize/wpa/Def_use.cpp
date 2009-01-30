/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 *
 * Def-use information.
 *
 * Gather the def-use information while the alias analysis is running.
 *
 */

#include "Def_use.h"

using namespace std;
using namespace boost;
using namespace MIR;

Def_use::Def_use (Whole_program* wp)
: WPA (wp)
{
}


void
Def_use::dump(Basic_block* bb)
{
	CHECK_DEBUG ();

	long id = bb->ID;
	cdebug << "Dumping Def_use (" << id << endl;


	// Print out the results for existing BBs (done this way so that IN and OUT
	// results are presented together).
#define SET_DUMP(SET,NAME)														\
	if (SET.has (id))																\
	{																					\
		cdebug << id << ": " << NAME " list: ";							\
		foreach (string str, SET[id])											\
			cdebug << str << ", ";												\
		cdebug << endl;															\
	}																					\
	else																				\
		cdebug << id << ": No " NAME " results" << endl;

	SET_DUMP (defs, "DEF");
	SET_DUMP (uses, "USE");
	SET_DUMP (may_defs, "MAY_DEF");
	SET_DUMP (may_uses, "MAY_USE");
#undef SET_DUMP
}

void
Def_use::set_value (Basic_block* bb, string lhs, Literal* lit, certainty cert)
{
	if (cert == DEFINITE)
		defs[bb->ID].insert (lhs);
	else if (cert == POSSIBLE)
		may_defs[bb->ID].insert (lhs);
}


void
Def_use::set_value_from (Basic_block* bb, string lhs, string rhs, certainty cert)
{
	// TODO: the certainty here isnt hugely precise. A must-def can be put in as
	// a may-def if there are multiple possible RHSs.
	if (cert == DEFINITE)
	{
		defs[bb->ID].insert (lhs);
		uses[bb->ID].insert (rhs);
	}
	else if (cert == POSSIBLE)
	{
		may_defs[bb->ID].insert (lhs);
		may_uses[bb->ID].insert (rhs);
	}
}

void
Def_use::pull_results (Basic_block* bb)
{
	// We are only interested in block local results
}

void
Def_use::aggregate_results (Basic_block* bb)
{
}

