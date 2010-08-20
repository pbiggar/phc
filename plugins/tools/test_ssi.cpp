/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include <AST.h>
#include <pass_manager/Optimization_pass.h>
#include <pass_manager/Plugin_pass.h>
#include <optimize/Basic_block.h>
#include <optimize/CFG.h>
#include <optimize/CFG_visitor.h>

class Test_SSI : public CFG_visitor {
public:
  Test_SSI() {}
  void run(CFG *cfg);
  void visit_sigma_node(Branch_block *brb, SSA_name sigma_rhs);
};

/*
 * Visit all basic blocks.
 */
void Test_SSI::run(CFG *cfg) {
  if (debugging_enabled)
    cfg->dump_graphviz(s("test-ssi"));

  foreach (Basic_block *bb, *cfg->get_all_bbs_top_down())
    visit_block(bb);
}

/*
 * Print sigma nodes.
 */
void Test_SSI::visit_sigma_node(Branch_block *brb, SSA_name sigma_rhs) {
  cout << "sigma(";
  bool first = true;
  foreach (SSA_name *sigma_lhs, *brb->get_sigma_args(sigma_rhs)) {
    cout << (first ? "" : ", ") << sigma_lhs->get_version();
    first = false;
  }
  cout << ") = " << sigma_rhs.str() << endl;
}

/*
 * Test SSI Plugin Handler.
 */
extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	// Insert the optimization.
	// TODO: Place it right after dce.
	Pass *opt = new Optimization_pass(new Test_SSI(), s("test-ssi"), s("Test SSI pass"), true, true);
	pm->add_after_named_pass (opt, new String ("dce"));
}
