/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "pass_manager/Plugin_pass.h"
#include "AST_visitor.h"
#include "process_ir/General.h"

using namespace std;

template <class Visitor, class PHP_script, class Statement>
class Count_statements : public Visitor
{
private:
   int num_statements;

public:
   // Set num_statements to zero before we begin
   void pre_php_script(PHP_script* in)
   {
      num_statements = 0;
   }

   // Print the number of function calls when we are done
   void post_php_script(PHP_script* in)
   {
      cout << num_statements << " statements found" << endl;
		exit (0);
   }
   
   // Count the number of function calls
   void post_statement(Statement* in)
   {
      num_statements++;
   }
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_each_pass (pass);
}

extern "C" void run_ast (AST::PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Count_statements<AST::Visitor, AST::PHP_script, AST::Statement> ());
}

extern "C" void run_hir (HIR::PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Count_statements<HIR::Visitor, HIR::PHP_script, HIR::Statement> ());
}

extern "C" void run_mir (MIR::PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Count_statements<MIR::Visitor, MIR::PHP_script, MIR::Statement> ());
}
