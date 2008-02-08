/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Manage all aspects of the pass queue
 */

#ifndef PHC_PASS_MANAGER_H
#define PHC_PASS_MANAGER_H

#include "Pass.h"
#include "lib/List.h"

#include "cmdline.h"
#include "ltdl.h"

class Pass;
class IR;

class Pass_manager
{

public:
	gengetopt_args_info* args_info;
	bool check; // check IR after each pass

	Pass_manager (gengetopt_args_info* args_info);

	// Remove passes
	void remove_all ();
	void remove_after_named_pass (const char* name);

	// Add single passes
	void add_plugin (lt_dlhandle handle, const char* name, String* option);
	void add_pass (Pass* pass, List<Pass*>* queue);

	// Add AST passes
	void add_ast_pass (Pass* pass);
	void add_ast_visitor (AST::Visitor* visitor, const char* name);
	void add_ast_transform (AST::Transform* transform, const char* name);
	void add_after_each_ast_pass (Pass* pass);
	bool is_ast_pass (String* name);

	// Add HIR passes
	void add_hir_pass (Pass* pass);
	void add_hir_visitor (HIR::Visitor* visitor, const char* name);
	void add_hir_transform (HIR::Transform* transform, const char* name);
	void add_after_each_hir_pass (Pass* pass);
	bool is_hir_pass (String* name);

	// Add MIR passes
	void add_mir_pass (Pass* pass);
	void add_mir_visitor (MIR::Visitor* visitor, const char* name);
	void add_mir_transform (MIR::Transform* transform, const char* name);
	void add_after_each_mir_pass (Pass* pass);
	bool is_mir_pass (String* name);

	// Add passes of any kind
	void add_after_each_pass (Pass* pass);
	void add_after_named_pass (Pass* pass, const char* name);
	void add_before_named_pass (Pass* pass, const char* name);
	void add_after_each_pass (Pass* pass, List<Pass*>*);

	bool has_pass_named (String *);
	Pass* get_pass_named (String* name);

	// Run (returns passed IR, or new IR if lowered
	IR* run_from (String* from, IR* in, bool dump = false);
	IR* run_from_until (String* from, String* to, IR* in, bool dump = false);
	IR* run_until (String* to, IR* in, bool dump = false);

	void run (IR* in, bool dump = false);
	void run_pass (Pass* pass, IR* in, bool dump = false);
	void post_process ();


	void list_passes ();
	void dump (IR* in, Pass* pass);

protected:
	List<Pass*>* ast_queue;
	List<Pass*>* hir_queue;
	List<Pass*>* mir_queue;
	List< List<Pass*>* >* queues;
	

};


#endif // PHC_PASS_MANAGER_H
