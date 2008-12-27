/*
 * phc -- the open source php compiler
 * see doc/license/readme.license for licensing information
 *
 * Check the MICG - types and otherwise.
 */

#ifndef PHC_MICG_CHECKER
#define PHC_MICG_CHECKER

#include "MICG.h"
#include "MICG_visitor.h"

#include "lib/String.h"
#include "lib/Map.h"

class MICG_checker : public MICG::Visitor, public GC_obj
{
public:
	void pre_lookup (MICG::Lookup* lookup)
	{
		// Check the type is Token or Node
		assert (0);
	}

	void pre_param_name (MICG::PARAM_NAME* in)
	{
		// Check the param is declared
		assert (0);
	}

	void pre_interpolation (MICG::Interpolation* in)
	{
		// Check the type is a string or Token
		assert (0);
	}

	void pre_equals (MICG::Equals* in)
	{
		// Check the params arent nodes
		assert (0);
	}
};


#endif // PHC_MICG_CHECKER
