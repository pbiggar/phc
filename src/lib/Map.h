/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Wrap the STL map
 */
 
#ifndef PHC_MAP_H
#define PHC_MAP_H

#include <map>
#include "lib/Object.h"

template <
	typename _Key, 
	typename _Tp, 
	typename _Compare = std::less<_Key>,
	typename _Alloc = phc_allocator<std::pair<const _Key, _Tp> >
>
class Map : public std::map<_Key, _Tp, _Compare, _Alloc>, virtual public Object
{
public:
	Map() : std::map<_Key, _Tp, _Compare, _Alloc>() {}
	virtual ~Map() {}

	Map* clone() { assert (0); }
};

#endif // PHC_MAP_H
