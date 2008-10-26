/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Clone mixins from a particular node, avoiding precisely inserting
 * mixin following code everywhere.
 */

#ifndef PHC_CLONE_BLANK_MIXINS
#define PHC_CLONE_BLANK_MIXINS

#include "AST.h"
#include "HIR.h"
#include "MIR.h"
#include "AST_visitor.h"
#include "HIR_visitor.h"
#include "MIR_visitor.h"

// Derived from Collect_all_pointers.h. Collects all nodes in a tree.
template <class Node, class Visitor>
class Collect_all_nodes: virtual public Visitor, public virtual GC_obj
{
public:
	Collect_all_nodes (List<Node*>* container)
	: all_nodes (container) {};

   List<Node*>* all_nodes;
public:
   void pre_node (Node* in) { all_nodes->push_back (in); }
};


template
<
	class Node,
	class Visitor
>
class Clone_blank_mixins : public Visitor, public virtual GC_obj
{
private:
	// if a node matches nothing, clone_mixin from here
	Node* anchor; 

	// All the subnodes of the original nodes. We need to copy attributes not
	// only from a node, but all its children too (deeply).
	List<Node*>* deep_originals; 

public:
	Clone_blank_mixins (Node* anchor, List<Node*>* originals) 
	: anchor (anchor)
	{
		deep_originals = new List<Node*>;
		foreach (Node* n, *originals)
		{
			n->visit (new Collect_all_nodes<Node, Visitor> (deep_originals));
		}
	}

	void pre_node (Node* in)
	{
		foreach (Node* n, *deep_originals)
		{
			// TODO is there a problem with copying values markers here?
			if (n->match (in))
				in->clone_mixin_from (n);
			else
				in->clone_mixin_from (anchor);
		}
	}
};


#endif // PHC_CLONE_BLANK_MIXINS
