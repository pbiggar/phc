/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * 
 * Wrap the STL stack
 */
 
#ifndef PHC_STACK_H
#define PHC_STACK_H

#include <stack>
#include "lib/Object.h"

// This is a little different, since stack actually wraps another container, by
// default a deque.

template<typename _Tp, typename _Sequence = std::deque<_Tp, phc_allocator<_Tp> > >
class Stack : public std::stack<_Tp, _Sequence>, virtual public GC_obj
{
public:
	Stack() : std::stack<_Tp, _Sequence>() {}
	virtual ~Stack() {}
};

#endif // PHC_STACK_H
