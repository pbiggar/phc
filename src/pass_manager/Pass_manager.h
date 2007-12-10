/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Manage all aspects of the pass queue
 */

#ifndef PHC_PASS_MANAGER_H
#define PHC_PASS_MANAGER_H

#include "Pass.h"
#include "AST_visitor.h"
#include "MIR_visitor.h"
#include "AST_transform.h"
#include "MIR_transform.h"
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

	void add_plugin (lt_dlhandle handle, const char* name, String* option);

	// Remove all passes from all queues
	void remove_all ();

	void add_pass (Pass* pass, List<Pass*>* ast_queue);

	// Add AST passes
	void add_ast_pass (Pass* pass);
	void add_ast_visitor (AST::Visitor* visitor, const char* name);
	void add_ast_transform (AST::Transform* transform, const char* name);
	void add_after_each_ast_pass (Pass* pass);

	// Add HIR passes
	void add_hir_pass (Pass* pass);
	void add_hir_visitor (HIR::Visitor* visitor, const char* name);
	void add_hir_transform (HIR::Transform* transform, const char* name);
	void add_after_each_hir_pass (Pass* pass);

	// Add MIR passes
	void add_mir_pass (Pass* pass);
	void add_mir_visitor (MIR::Visitor* visitor, const char* name);
	void add_mir_transform (MIR::Transform* transform, const char* name);
	void add_after_each_mir_pass (Pass* pass);

	// Add passes of any kind
	void add_after_each_pass (Pass* pass);
	void add_after_named_pass (Pass* pass, const char* name);
	void add_before_named_pass (Pass* pass, const char* name);
	void add_after_each_pass (Pass* pass, List<Pass*>*);

	// Run (returns passed IR, or new IR if lowered
	IR* run_from_until (String* from, String* to, IR* in, bool dump = false);
	IR* run_until (String* to, IR* in, bool dump = false);
	IR* run (IR* in, bool dump = false);
	void run_pass (Pass* pass, IR* in, bool dump = false);
	void post_process ();


	void list_passes ();
	bool has_pass_named (String *);
	void dump (IR* in, Pass* pass);

protected:
	List<Pass*>* ast_queue;
	List<Pass*>* hir_queue;
	List<Pass*>* mir_queue;
	List< List<Pass*>* >* queues;
	

};


#endif // PHC_PASS_MANAGER_H
