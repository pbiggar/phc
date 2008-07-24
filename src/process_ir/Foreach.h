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

/* lci stand for List const iterator. VAR is the list, TYPE is the type
 * contained in the list, and ITER is the name of the iterator, which the macro
 * declares for you */
#define for_lci(VAR, TYPE, ITER)										\
for (List<TYPE*>::const_iterator (ITER) = (VAR)->begin ();	\
											(ITER) != (VAR)->end ();	\
											(ITER)++)

// No const.
#define for_li(VAR, TYPE, ITER)										\
for (List<TYPE*>::iterator (ITER) = (VAR)->begin ();			\
									(ITER) != (VAR)->end ();			\
									(ITER)++)

// Templates may need the typename keyworkd
#define tfor_lci(VAR, TYPE, ITER)												\
for (typename List<TYPE*>::const_iterator (ITER) = (VAR)->begin ();	\
														(ITER) != (VAR)->end ();	\
														(ITER)++)

#endif
