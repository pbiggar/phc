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
DECL (Reference);

class Aliasing : public WPA
{
	Map<Result_state, CX_map<Points_to*> > ptgs;
	// Record 1 per program-point.
	CX_map<Points_to*>& outs;
	CX_map<Points_to*>& ins;
	CX_map<Points_to*>& working;

	// This allows the bind results to be combined before being put back into
	// working.
	CX_map<Points_to*>& post_bind;

private:
	void init_block_results (Context* cx);

public:
	Aliasing (Whole_program*);

	// WPA interface
	void init (Context* outer);
	void forward_bind (Context* caller, Context* entry);

	void backward_bind (Context* caller, Context* exit);
	void post_invoke_method (Context* caller);

	void create_reference (Context* cx, Index_node* lhs,
								  Index_node* rhs, Certainty cert);

	void assign_value (Context* cx, Index_node* lhs, Storage_node* storage);

	// Create STORAGE, with the gives TYPES.
	void set_storage (Context* cx, Storage_node* storage, Types* types);

	// Create STORAGE, an abstract value with the given types.
	void set_scalar (Context* cx, Value_node* storage, Abstract_value* val);


	void kill_value (Context* cx, Index_node* lhs, bool also_kill_refs = true);


	void pull_init (Context* cx);
	void pull_first_pred (Context* cx, Context* pred);
	void pull_pred (Context* cx, Context* pred);
	void pull_possible_null (Context* cx, Index_node* node);
	void pull_finish (Context* cx);


	void finish_block (Context* cx);

	bool equals (WPA* other);
	void dump (Context* cx, Result_state state, string comment);
	void dump_everything (string comment);

	void merge_contexts ();

public:
	/*
	 * Take information from Alias results
	 */

	Reference_list* get_references (Context* cx, Result_state state, Index_node* index, Certainty cert);
	Index_node_list* get_fields (Context* cx, Result_state state, Storage_node* storage);
	Storage_node_list* get_points_to (Context* cx, Result_state state, Index_node* index);

	bool is_abstract (Context* cx, Result_state state, Storage_node* st);
	bool is_abstract_field (Context* cx, Result_state state, Index_node* st);

	bool has_storage_node (Context* cx, Result_state state, Storage_node* st);
	bool has_field (Context* cx, Result_state state, Index_node* ind);

	Storage_node_list* get_storage_nodes (Context* cx, Result_state state);

	Storage_node* get_owner (Context* cx, Result_state state, Index_node* index);
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
	ST_path (string name);
	string name;
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
