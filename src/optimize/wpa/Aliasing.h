/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Flow-, field-, and context-sensitive alias analysis, in a similar fashion to
 *
 * Michael Hind and Michael Burke and Paul Carini and Jong-Deok Choi,
 * Interprocedural pointer alias analysis
 * ACM Trans. Program. Lang. Syst., 1999
 *
 * We use an infinite call-string approach, and assume that other peoples
 * research can be used to constrain the memory usage at a later date. There
 * is one points-to graph per program point (which corresponds to a basic
 * block for us).
 */

#ifndef PHC_ALIASING
#define PHC_ALIASING

#include "WPA.h"

class Path;
class Points_to;
DECL (Index_node);
DECL (Storage_node);
DECL (Value_node);

class Aliasing : public WPA
{
	// Record 1 per program-point.
	Map<long, Points_to*> ins;
	Map<long, Points_to*> outs;

public:
	Aliasing (Whole_program*);

	// WPA interface
	void forward_bind (Basic_block* caller, Entry_block* entry);

	void backward_bind (Basic_block* caller, Exit_block* exit);

	void create_reference (Basic_block* bb, Index_node* lhs,
								 Index_node* rhs, certainty cert);

	void assign_value (Basic_block* bb, Index_node* lhs,
							 Storage_node* storage, certainty cert);

	// Create STORAGE, with the gives TYPES.
	void set_storage (Basic_block* bb, Storage_node* storage,
							Types types);

	// Create STORAGE, an abstract value with the given types.
	void set_scalar (Basic_block* bb, Value_node* storage,
						  Abstract_value* val);


	void kill_value (Basic_block* bb, Index_node* lhs);

	void kill_reference (Basic_block* bb, Index_node* lhs);


	void pull_init (Basic_block* bb);
	void pull_first_pred (Basic_block* bb, Basic_block* pred);
	void pull_pred (Basic_block* bb, Basic_block* pred);
	void pull_finish (Basic_block* bb);


	void aggregate_results (Basic_block* bb);

	bool equals (WPA* other);
	void dump (Basic_block* bb, string comment);

public:
	/*
	 * Take information from Alias results
	 */

	Index_node_list* get_references (Basic_block*, Index_node* index,
												certainty cert);

	Index_node_list* get_indices (Basic_block*, Storage_node* storage);

	Storage_node_list* get_values (Basic_block*, Index_node* index);

private:
	// TODO: i think i'll be removing this...
	void add_all_points_to_edges (Basic_block* bb, Index_node* lhs,
											Index_node* rhs, certainty cert);

};

/* A Path is a way of representing some dereferencing. See Aliasing.cpp. */
class Path : virtual public GC_obj
{
public:
	virtual void dump (std::ostream& os = cdebug) = 0;
};

Path* P (string st, MIR::Node* node);
Path* P (string st, string ind);

class Indexing : public Path 
{
public:
	Indexing (Path* lhs, Path* rhs);
	Path* lhs;
	Path* rhs;
	void dump (std::ostream& os = cdebug);
};

class ST_path : public Path
{
public:
	string name;
	ST_path (string name);
	void dump (std::ostream& os = cdebug);
};

class Index_path : public Path
{
public:
	Index_path (string name);
	string name;
	void dump (std::ostream& os = cdebug);
};



#endif // PHC_ALIASING
