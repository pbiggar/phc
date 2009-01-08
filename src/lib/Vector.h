/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Wrap the STL vector
 */
 
#ifndef PHC_VECTOR_H
#define PHC_VECTOR_H

#include <vector>
#include "lib/Object.h"

template<typename _Tp, typename _Alloc = phc_allocator<_Tp> >
class Vector : public std::vector<_Tp, _Alloc>, virtual public GC_obj
{
public:
	Vector () : std::vector<_Tp, _Alloc>() {}
	Vector (size_t n, const _Tp& value = _Tp(), const _Alloc& _a = _Alloc())
	: std::vector<_Tp, _Alloc> (n, value, _a)
	{
	}

	virtual ~Vector () {}
};

#endif // PHC_VECTOR_H
