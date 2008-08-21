/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience functions and headers
 */

#ifndef PHC_GENERAL
#define PHC_GENERAL

#include "lib/String.h"

// 'new String' must be the most typed function in phc
String* s (string s);

#include "debug.h"
#include "Foreach.h"
#include "fresh.h"
#include "boost/lexical_cast.hpp"

using boost::lexical_cast;
using std::string;

#endif // PHC_GENERAL
