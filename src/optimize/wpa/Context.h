/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Context-sensitivity
 */

#ifndef PHC_CONTEXT
#define PHC_CONTEXT

#include <ostream>

#include "optimize/Lattice.h"
#include "optimize/CFG_visitor.h"

class Storage_node;

DECL (Context);
class Context : virtual public GC_obj
{
	BB_list BBs;

	// We want to be able to use caller() accurately, meaning we want to leave
	// the BBs unbounded. So we need to be able to keep track of the amount of
	// BBs. The first BB (from the bottom) that has a count > 1 leads to an R.
	// We update this in caller() and contextual().
	Map<Basic_block*, int> BB_counts;

	bool use_caller;

	mutable String* cached_name;

public:
	friend std::ostream& operator<<(std::ostream&, const Context*);
	Context ();

	static Context* outer (Basic_block* outer);
	static Context* non_contextual (Basic_block* bb);
	static Context* contextual (Context* caller, Basic_block* bb);
	static Context* as_peer (Context* peer, Basic_block* bb);

	Context* caller () const;
	Context* get_non_contextual () const;

	bool empty () const;
	Basic_block* get_bb () const;
	bool is_outer () const; // Is it the caller of __MAIN__

	bool operator== (const Context &other) const;
	string name () const;
	string full_name () const;

	Storage_node* array_node () const;
	Storage_node* symtable_node () const;
	Storage_node* storage_node (string type) const;

	string symtable_name () const;
	string array_name () const;
	string storage_name (string type) const;

	// Apply the HACK rules for new context names.
	static string convert_context_name (string);

	bool is_recursive () const;

};

std::ostream &operator<< (std::ostream &out, const Context* cx);


class CX_map_equals : virtual public GC_obj
{
public:
	bool operator() (Context* cx1, Context* cx2) const
	{
		return *cx1 == *cx2;
	}
};

class CX_map_hash : virtual public GC_obj
{
public:
	size_t operator() (Context* cx1) const
	{
		return std::tr1::hash<string>() (cx1->name ());
	}
};

template <class _Tp>
class CX_map : public Map<Context*, _Tp, CX_map_hash, CX_map_equals>
{
};

template <class Key_type, class Cell_type>
class CX_lattices : public CX_map<Lattice_map<Key_type, Cell_type> >
{
public:
	void dump (Context* cx, string name) const
	{
		if (this->has (cx))
		{
			cdebug << name << " Lattice for BB: " << cx << std::endl;
			this->operator[](cx).dump();
			cdebug << std::endl;
		}
		else
			cdebug << "No " << name << " results for BB: " << cx << std::endl;
	}

	void dump_everything (string name) const
	{
		foreach (Context* cx, *this->keys())
		{
			dump (cx, name);
		}
	}
};


#endif // PHC_CONTEXT
