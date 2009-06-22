/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
* */

#ifndef PHC_STAT_COLLECTOR
#define PHC_STAT_COLLECTOR

class Whole_program;
class Index_node;

class Stat_collector : public CFG_visitor
{
public:
	Whole_program* wp;
	Stat_collector (Whole_program*);

	void run (CFG* cfg);

	// for passing between visit_assign_var and visit_expr
	Index_node* lhs;
	bool assign_var_is_ref;


	Abstract_value* get_abstract_value (Basic_block* bb, MIR::Rvalue* rval);

	void visit_entry_block (Entry_block* bb);
	void visit_basic_block (Basic_block* bb);
	void visit_statement_block (Statement_block* bb);

	DECLARE_STATEMENT_CFG_VISITORS
	DECLARE_EXPR_CFG_VISITORS

	void collect_type_stats (Basic_block* bb, MIR::Rvalue* rval,string statname );
private:
	String last_assignment_lhs;
};

#endif // PHC_STAT_COLLECTOR
