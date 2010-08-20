/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Manage all aspects of the pass queue
 */

#ifndef PHC_PASS_MANAGER_H
#define PHC_PASS_MANAGER_H

#include "ltdl.h"

#include "cmdline.h"
#include "lib/List.h"

class CFG;
class CFG_visitor;
class Optimization_pass;
class Whole_program;
class Pass;
class String;

typedef List<Pass*> Pass_queue;
namespace AST { class Visitor; class Transform; }
namespace HIR { class Visitor; class Transform; }
namespace MIR { class Visitor; class Transform; class Method; }
namespace IR { class PHP_script; }

class Pass_manager : virtual public GC_obj
{
public:

	// TODO: this is getting out of hand. It might be best to turn this into an
	// iterable data structure, with [] operators etc. If it could be done with
	// two maps, name -> pass and index -> name, that would be ideal.
	gengetopt_args_info* args_info;
	bool check; // check IR after each pass

	Pass_manager (gengetopt_args_info* args_info);

	// Remove passes
	void remove_all ();
	void remove_pass_named (String* name);
	void remove_after_named_pass (String* name);

	// Add single passes
	void add_plugin (lt_dlhandle handle, String* name, String* option);
	void add_pass (Pass* pass, Pass_queue* queue);

	// Add AST passes
	void add_ast_pass (Pass* pass);
	void add_ast_visitor (AST::Visitor* visitor, String* name, String* description);
	void add_ast_transform (AST::Transform* transform, String* name, String* description);
	void add_after_each_ast_pass (Pass* pass);

	// Add HIR passes
	void add_hir_pass (Pass* pass);
	void add_hir_visitor (HIR::Visitor* visitor, String* name, String* description);
	void add_hir_transform (HIR::Transform* transform, String* name, String* description);
	void add_after_each_hir_pass (Pass* pass);

	// Add MIR passes
	void add_mir_pass (Pass* pass);
	void add_mir_visitor (MIR::Visitor* visitor, String* name, String* description);
	void add_mir_transform (MIR::Transform* transform, String* name, String* description);
	void add_after_each_mir_pass (Pass* pass);

	// Add Optimization passes
	void optimize (MIR::PHP_script* in);
	void run_optimization_pass (Pass* pass, Whole_program* wp, CFG* cfg);

	void run_local_optimization_passes (Whole_program* wp, CFG* cfg);
	void add_local_optimization (CFG_visitor* visitor, String* name, String* description, bool require_ssa = false, bool require_ssi = false);
	void add_local_optimization_pass (Pass*);

	void run_ipa_passes (Whole_program* wp, CFG* cfg);
	void add_ipa_optimization (CFG_visitor* visitor, String* name, String* description, bool require_ssa = false, bool require_ssi = false);
	void add_ipa_optimization_pass (Pass*);

	// Add codegen passes
	void add_codegen_pass (Pass* pass);
	void add_codegen_visitor (MIR::Visitor* visitor, String* name, String* description);
	void add_codegen_transform (MIR::Transform* transform, String* name, String* description);
	void add_after_each_codegen_pass (Pass* pass);


	// Add passes of any kind
	void add_after_each_pass (Pass* pass);
	void add_after_named_pass (Pass* pass, String* name);
	void add_before_named_pass (Pass* pass, String* name);
	void add_after_each_pass (Pass* pass, Pass_queue*);

	bool has_pass_named (String *);
	Pass* get_pass_named (String* name);

	// Run (returns passed IR, or new IR if lowered
	IR::PHP_script* run_from (String* from, IR::PHP_script* in, bool main = false);
	IR::PHP_script* run_from_until (String* from, String* to, IR::PHP_script* in, bool main = false);
	IR::PHP_script* run_until (String* to, IR::PHP_script* in, bool main = false);

	void run (IR::PHP_script* in, bool main = false);
	void run_pass (Pass* pass, IR::PHP_script* in, bool main = false);
	void post_process ();


	void list_passes ();
	void dump (IR::PHP_script* in, String* passname);
	void maybe_enable_debug (String* passname);

	// HACK: debugging for optimization passes.
	void cfg_dump (CFG* cfg, String* passname, String* comment);

protected:
	Pass_queue* ast_queue;
	Pass_queue* hir_queue;
	Pass_queue* mir_queue;
	Pass_queue* wpa_queue;
	Pass_queue* opt_queue;
	Pass_queue* ipa_queue;
	Pass_queue* codegen_queue;
	List<Pass_queue*>* queues;
};

#endif // PHC_PASS_MANAGER_H
