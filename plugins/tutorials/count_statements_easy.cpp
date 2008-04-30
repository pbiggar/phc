/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "pass_manager/Plugin_pass.h"
#include "AST_visitor.h"
#include "process_ir/General.h"

using namespace AST; 

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
   }
   
   // Count the number of function calls
   void post_statement(Statement* in)
   {
      num_statements++;
   }
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->remove_after_named_pass (s("ast"));
	pm->add_after_named_pass (pass, s("ast"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new Count_statements ());
}
