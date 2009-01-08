/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience functions and headers
 */

#ifndef PHC_GENERAL
#define PHC_GENERAL

#include "lib/String.h"


#include "debug.h"
#include "stats.h"
#include "Foreach.h"
#include "fresh.h"
#include "parsing/Parse_buffer.h"
#include "boost/lexical_cast.hpp"

#define PUNT do { throw "punting"; } while (0)
#define OPT_ASSERT(A) do { if (A) throw "punting"; } while (0)

using boost::lexical_cast;

#endif // PHC_GENERAL
