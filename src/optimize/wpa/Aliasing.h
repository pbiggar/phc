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
#include "Points_to.h"

class Path;

class Aliasing : public WPA
{
	// Record 1 per program-point.
	Map<long, Points_to*> ins;
	Map<long, Points_to*> outs;

public:
	Aliasing (Whole_program*);

	// WPA interface
	void kill_by_copy (Basic_block* bb, Alias_name index);
	void kill_by_ref (Basic_block* bb, Alias_name index);

	void assign_scalar (Basic_block* bb, Alias_name lhs,
							  MIR::Literal* rhs, certainty cert);

	void assign_empty_array (Basic_block* bb, Alias_name lhs,
									 string unique_name, certainty cert);

	void assign_unknown (Basic_block* bb, Alias_name lhs, certainty cert);
	
	void assign_by_ref (Basic_block* bb, Alias_name lhs,
	                    Alias_name rhs, certainty cert);

	void assign_by_copy (Basic_block* bb, Alias_name lhs,
							   Alias_name rhs, certainty cert);

	void forward_bind (Basic_block* bb, CFG* callee_cfg,
							 MIR::Actual_parameter_list* actuals,
							 MIR::VARIABLE_NAME* retval);

	void backward_bind (Basic_block* bb, CFG* callee_cfg);


	void pull_results (Basic_block* bb);
	void aggregate_results (Basic_block* bb);

	void dump (Basic_block* bb);


	// Give access to aliasing results
	Index_node_list* get_references (Basic_block*, Index_node* index,
												certainty cert);

	Storage_node_list* get_points_to (Basic_block*, Index_node* index,
												certainty cert);
};

/* A Path is a way of representing some dereferencing. See Aliasing.cpp. */
class Path : virtual public GC_obj
{
};

Path* P (string st, MIR::Node* node);

class Indexing : public Path 
{
public:
	Indexing (Path* lhs, Path* rhs);
	Path* lhs;
	Path* rhs;
};

class ST_path : public Path
{
public:
	string name;
	ST_path (string name);
};

class Index_path : public Path
{
public:
	Index_path (string name);
	string name;
};




#endif // PHC_ALIASING
