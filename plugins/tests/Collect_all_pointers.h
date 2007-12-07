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
#include "HIR_visitor.h"
#include "process_ir/General.h"


class Collect_all_pointers : virtual public AST::Visitor, public HIR::Visitor
{
public:
	list<Object*> all_pointers;
	set<Object*> unique_pointers;

public:
	void pre_node (AST::Node* in) { collect (in, in->attrs); }
	void pre_node (HIR::Node* in) { collect (in, in->attrs); }

	void collect (Object* obj, AttrMap* attrs)
	{
		all_pointers.push_back (obj);
		unique_pointers.insert (obj);

		// Push back all the pointer obj attrs, too
		// (We ignore keys) 
		AttrMap::const_iterator i;
		for(i = attrs->begin(); i != attrs->end(); i++)
		{
			if ((*i).second == NULL)
				continue;

			all_pointers.push_back ((*i).second);			
			unique_pointers.insert ((*i).second);			
		}
	}

};

#endif
