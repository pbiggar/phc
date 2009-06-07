/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Context-sensitivity
 */

#ifndef PHC_CONTEXT
#define PHC_CONTEXT

#include <ostream>

#include "optimize/CFG_visitor.h"

class Context : virtual public GC_obj
{
	BB_list BBs;

	// We want to be able to use caller() accurately, meaning we want to leave
	// the BBs unbounded. So we need to be able to keep track of the amount of
	// BBs. The first BB (from the bottom) that has a count > 1 leads to an R.
	// We update this in caller() and contextual().
	Map<Basic_block*, int> BB_counts;

	bool use_caller;

	mutable string* cached_name;

public:
	friend std::ostream &operator<<(std::ostream&, const Context&);
	Context();

	static Context outer (Basic_block* outer);
	static Context non_contextual (Basic_block* bb);
	static Context contextual (Context caller, Basic_block* bb);
	static Context as_peer (Context peer, Basic_block* bb);

	Context caller ();
	Context get_non_contextual ();

	Basic_block* get_bb ();
	bool is_outer (); // Is it the caller of __MAIN__

	bool operator< (const Context &other) const;
	bool operator== (const Context &other) const;
	string name () const;
	string full_name () const;

	Storage_node* array_node ();
	Storage_node* object_node ();
	Storage_node* symtable_node ();

	string symtable_name ();
	string array_name ();
	string object_name ();

	// Apply the HACK rules for new context names.
	static string convert_context_name (string);

	bool is_recursive ();
};

std::ostream &operator<< (std::ostream &out, const Context &num);


#include "optimize/Lattice.h"

template <class Cell_type>
class CX_lattices : public Map<Context, Lattice_map<Cell_type> >
{
public:
	void dump (Context cx, string name)
	{
		if (this->has (cx))
		{
			cdebug << name << " Lattice for BB: " << cx << std::endl;
			(*this)[cx].dump();
			cdebug << std::endl;
		}
		else
			cdebug << "No " << name << " results for BB: " << cx << std::endl;
	}

	void dump_everything (string name)
	{
		foreach (Context cx, *this->keys())
		{
			dump (cx, name);
		}
	}
};


#endif // PHC_CONTEXT
