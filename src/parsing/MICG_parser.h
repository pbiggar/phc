/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Parser for the Macro inline code generator.
 */

#ifndef PHC_MICG_PARSER
#define PHC_MICG_PARSER

#include "lib/String.h"

class MICG_parser : virtual public GC_obj
{
public:
	MICG_parser ();

	void parse (string str);
};


#endif // PHC_MICG_PARSER
