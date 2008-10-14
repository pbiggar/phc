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
#include "process_ir/General.h"

template <class Node, class Visitor>
class Collect_all_pointers : virtual public Visitor
{
public:
	List<Node*> all_nodes;
	std::set<Node*> unique_nodes;

	List<Object*> all_attrs;
	std::set<Object*> unique_attrs;

	List<Object*> all_pointers;
	std::set<Object*> unique_pointers;
public:
	void pre_node (Node* in) { collect (in, in->attrs); }

	void collect (Node* in, AttrMap* attrs)
	{
		all_nodes.push_back (in);
		all_pointers.push_back (in);

		unique_nodes.insert (in);
		unique_pointers.insert (in);

		// Push back all the pointer obj attrs, too
		// (We ignore keys) 
		AttrMap::const_iterator i;
		for(i = attrs->begin(); i != attrs->end(); i++)
		{
			all_attrs.push_back ((*i).second);
			all_pointers.push_back ((*i).second);

			unique_attrs.insert ((*i).second);
			unique_pointers.insert ((*i).second);
		}
	}

};

#endif
