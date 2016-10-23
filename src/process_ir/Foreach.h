/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience foreach function.
 */

#ifndef PHC_FOREACH
#define PHC_FOREACH

#include <boost/foreach.hpp>
#include <boost/version.hpp>

namespace boost {

#if BOOST_VERSION != 104900
  namespace BOOST_FOREACH = foreach;
#endif

} // namespace boost

#define foreach BOOST_FOREACH

// No const.
#define for_li(VAR, TYPE, ITER)										\
for (List<TYPE*>::iterator (ITER) = (VAR)->begin ();			\
									(ITER) != (VAR)->end ();			\
									(ITER)++)

#endif
