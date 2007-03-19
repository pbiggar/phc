/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Traversal to collect all pointers in an AST.
 */

#ifndef PHC_COLLECT_ALL_POINTERS
#define PHC_COLLECT_ALL_POINTERS

#include <algorithm>
#include <set>
#include "AST_visitor.h"

class Collect_all_pointers : virtual public AST_visitor 
{
public:
	list<Object*> all_pointers;
	set<Object*> unique_pointers;

public:
	void pre_node(AST_node* in)
	{
		all_pointers.push_back(in);
		unique_pointers.insert(in);

		// Push back all the pointer in attrs, too
		// (We ignore keys) 
		AttrMap::const_iterator i;
		for(i = in->attrs->begin(); i != in->attrs->end(); i++)
		{
			if((*i).second == NULL)
				continue;

			all_pointers.push_back((*i).second);			
			unique_pointers.insert((*i).second);			
		}
	}
};

#endif
