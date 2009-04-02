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

#define SYM(CX) ((CX).caller().name())

class Context : virtual public GC_obj
{
	List<Basic_block*> BBs;
	bool use_caller;

public:
	friend std::ostream &operator<<(std::ostream&, const Context&);

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
};

std::ostream &operator<< (std::ostream &out, const Context &num);


string CX_array_name (Context cx);
string CX_object_name (Context cx);


#include "optimize/Lattice.h"

class CX_lattices : public Map<Context, Lattice_map>
{
public:
	void dump (Context cx, string name);
};


#endif // PHC_CONTEXT
