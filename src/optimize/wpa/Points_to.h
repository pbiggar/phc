/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Points-to graph.
 *
 *
 */

#ifndef PHC_POINTS_TO
#define PHC_POINTS_TO

#include "lib/List.h"
#include "lib/String.h"
#include "MIR.h"

#define DECL(T) class T; typedef List<T*> T##_list;

DECL (PT_node);
DECL (Alias_pair);

/*DECL (Zval_node);
DECL (Storage_node);
DECL (Object_node);
DECL (Array_node);
*/

// A node in the graph (ie the abstract base of the components of an alias-pair).
class PT_node : virtual public GC_obj
{
};

/*
 * These represent Variables, array-indices and fields of storage nodes.
 *
 * This descriptor is a combination of their storage node and their index.
 *		Global var-vars: GST::*
 *		Local (to a()) variable 'x': a.ST::x
 *
 *	There is not a unique descriptor for this node. Any object with the same
 *	descriptor represents the same node, in any graph. So we cannot store
 *	attributes in here (they should be in the other analyses' lattices).
 */
class Index_node : public PT_node
{
};

// A known index node (ie a known variable, field or array index)
class Named_node : public Index_node
{
};

// An unknown index node (ie an array index not-by-name, a variable-variable, or variable-field.
class Unknown_node : public Index_node
{
};


// Represents class for arrays, objects and symtables
class Storage_node : public PT_node
{
public:
	// If true, its (outgoing) edges cannot be killed, as it represents more
	// than one run-time object. If false, represents just one run-time object,
	// meaning its edges can be killed. 
	bool is_abstract;
};

/*
 * Does this edge definitely exist? Between Index_nodes, this means may- or
 * must-alias. Between Storage_nodes and Index_nodes, it says whether there is
 * definitely an index with this name, or not.
 */
enum _existence { POSSIBLE, DEFINITE };
typedef enum _existence existence;

class Alias_pair : virtual public GC_obj
{
public:
	existence exist;
	PT_node* source;
	PT_node* target;
};


class Points_to : virtual public GC_obj
{
public:
	Points_to ();
	Alias_pair_list* pairs;

	void open_scope (string name);
	void close_scope (string name);

	void dump_graphviz (String* name);
};

#endif // PHC_POINTS_TO
