/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience foreach function.
 */

#ifndef PHC_FOREACH
#define PHC_FOREACH

#include <boost/foreach.hpp>

#define foreach BOOST_FOREACH

// No const.
#define for_li(VAR, TYPE, ITER)										\
for (List<TYPE*>::iterator (ITER) = (VAR)->begin ();			\
									(ITER) != (VAR)->end ();			\
									(ITER)++)

#endif
