#include "process_ir/General.h"
#include "process_mir/MIR_unparser.h"
#include "MIR.h"

#include "Basic_block.h"
#include "Def_use.h"

using namespace std;
using namespace MIR;

/* Constructors */

Basic_block::Basic_block(CFG* cfg)
: cfg(cfg)
, vertex (NULL)
, defs (NULL)
, uses (NULL)
, live_in (NULL)
, live_out (NULL)
, changed (false)
, aliases (NULL)
{
}

Branch_block::Branch_block (CFG* cfg, MIR::Branch* b)
: Basic_block (cfg)
, branch (b) 
{
}

Statement_block::Statement_block (CFG* cfg, MIR::Statement* s) 
: Basic_block (cfg)
, statement(s)
{
}

Empty_block::Empty_block (CFG* cfg)
: Basic_block (cfg)
{
}

Entry_block::Entry_block (CFG* cfg, Method* method)
: Basic_block (cfg)
, method (method)
{
}

Exit_block::Exit_block (CFG* cfg, Method* method)
: Basic_block (cfg)
, method (method)
{
}

list<pair<String*,String*> >*
Basic_block::get_graphviz_properties ()
{
	list<pair<String*,String*> >* result = new list<pair<String*,String*> >;
	result->push_back (make_pair (s("shape"), s("box")));
	return result;
}


/*
 * Labels for graphviz
 */
String*
Entry_block::get_graphviz_label ()
{
	return s("ENTRY");
}

String* Exit_block::get_graphviz_label ()
{
	return s("EXIT");
}

String* Empty_block::get_graphviz_label ()
{
	return s("");
}

String* Branch_block::get_graphviz_label ()
{
	return branch->variable_name->get_ssa_var_name ();
}

String*
Statement_block::get_graphviz_label ()
{
	stringstream ss;
	MIR_unparser mup(ss, true);
	mup.unparse(statement);
	return s(ss.str());
}

list<pair<String*,String*> >*
Branch_block::get_graphviz_properties ()
{
	list<pair<String*,String*> >* result =
		Basic_block::get_graphviz_properties ();

	result->push_back (make_pair (s("shape"), s("diamond")));

	return result;
}


list<std::pair<String*,Set*> >*
Basic_block::get_graphviz_bb_properties ()
{
	list<pair<String*,Set*> >* result = new list<std::pair<String*,Set*> >;
	if (defs)
		result->push_back (pair<String*, Set*> (s("defs"), defs));
	if (uses)
		result->push_back (pair<String*, Set*> (s("uses"), uses));
	if (aliases && dynamic_cast<Entry_block*> (this))
		result->push_back (pair<String*, Set*> (s("aliases"), aliases));
	return result;
}

list<std::pair<String*,Set*> >*
Basic_block::get_graphviz_head_properties ()
{
	list<std::pair<String*,Set*> >* result = new list<std::pair<String*,Set*> >;
	// Phi nodes
	foreach (Phi* phi, *get_phi_nodes ())
	{
		Set* set = new Set;
		foreach (VARIABLE_NAME* arg, *phi->get_args ())
			set->insert (arg);

		result->push_back (
			pair<String*, Set*> (phi->lhs->get_ssa_var_name (), set));
	}

	if (live_in)
		result->push_back (pair<String*, Set*> (s("IN"), live_in));
	return result;
}

list<std::pair<String*,Set*> >*
Basic_block::get_graphviz_tail_properties ()
{
	list<std::pair<String*,Set*> >* result = new list<std::pair<String*,Set*> >;
	if (live_out)
		result->push_back (pair<String*, Set*> (s("OUT"), live_out));
	return result;
}

/*
 * SSA
 */

void
Basic_block::add_phi_function (VARIABLE_NAME* var_name)
{
	// We only want 1 phi node per variable name, regardless of the number of
	// versions.
	assert (not has_phi_function (var_name));
	phi_nodes[*var_name->value] = new Phi (var_name->clone ());
}

bool
Basic_block::has_phi_function (VARIABLE_NAME* var_name)
{
	return phi_nodes.has (*var_name->value);
}

/* Merge the phi nodes from OTHER into this BB. */
void
Basic_block::merge_phi_nodes (Basic_block* other)
{
	assert (get_phi_nodes ()->size () == 0);
	assert (other->get_phi_nodes ()->size () == 0);
}

void
Basic_block::remove_phi_nodes ()
{
	phi_nodes.clear ();
}

BB_list*
Basic_block::get_predecessors ()
{
	return cfg->get_bb_predecessors (this);
}

BB_list*
Basic_block::get_successors ()
{
	return cfg->get_bb_successors (this);
}

Basic_block*
Basic_block::get_successor ()
{
	BB_list* succs = get_successors ();
	assert (succs->size() == 1);
	return succs->front ();
}

Edge_list*
Basic_block::get_predecessor_edges ()
{
	return cfg->get_edge_predecessors (this);
}

Edge_list*
Basic_block::get_successor_edges ()
{
	return cfg->get_edge_successors (this);
}


Edge*
Basic_block::get_successor_edge ()
{
	Edge_list* succs = get_successor_edges ();
	assert (succs->size() == 1);
	return succs->front ();
}

Basic_block*
Branch_block::get_true_successor ()
{
	BB_list* succs = get_successors ();
	assert (succs->size() == 2);

	foreach (Basic_block* succ, *succs)
		if (cfg->is_true_edge (cfg->get_edge (this, succ)))
			return succ;

	assert (0);
}

Basic_block*
Branch_block::get_false_successor ()
{
	BB_list* succs = get_successors ();
	assert (succs->size() == 2);

	foreach (Basic_block* succ, *succs)
		if (not cfg->is_true_edge (cfg->get_edge (this, succ)))
			return succ;

	assert (0);
}

void
Basic_block::remove ()
{
	cfg->replace_bb (this, new BB_list);
}

void
Basic_block::replace (BB_list* replacements)
{
	cfg->replace_bb (this, replacements);

}

BB_list*
Basic_block::get_dominance_frontier ()
{
	return cfg->dominance->get_bb_dominance_frontier (this);
}

Basic_block*
Basic_block::get_immediate_dominator ()
{
	return cfg->dominance->get_bb_immediate_dominator (this);
}

void
Basic_block::add_to_dominance_frontier (Basic_block* bb)
{
	cfg->dominance->add_to_bb_dominance_frontier (this, bb);
}

BB_list*
Basic_block::get_dominated_blocks ()
{
	return cfg->dominance->get_blocks_dominated_by_bb (this);
}

Set*
Basic_block::get_ssa_defs ()
{
	return new Set ();
}

Set*
Basic_block::get_ssa_uses ()
{
	return new Set ();
}

Set*
Branch_block::get_ssa_uses ()
{
	return new Set (branch->variable_name);
}

Set*
Statement_block::get_ssa_uses ()
{
	return Def_use::get_uses (statement);
}

Set*
Statement_block::get_ssa_defs ()
{
	return Def_use::get_defs (statement);
}

List<Phi*>*
Basic_block::get_phi_nodes ()
{
	List<Phi*>* result = new List<Phi*>;

	pair<string, Phi*> pair;
	foreach (pair, phi_nodes)
		result->push_back (pair.second);

	return result;
}

int
Basic_block::get_index ()
{
	return cfg->index[vertex];
}

