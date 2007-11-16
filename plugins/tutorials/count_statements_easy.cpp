/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "pass_manager/Plugin_pass.h"

using namespace AST; 

class Count_statements : public AST_visitor
{
private:
   int num_statements;

public:
   // Set num_statements to zero before we begin
   void pre_php_script(AST_php_script* in)
   {
      num_statements = 0;
   }

   // Print the number of function calls when we are done
   void post_php_script(AST_php_script* in)
   {
      cout << num_statements << " statements found" << endl;
   }
   
   // Count the number of function calls
   void post_statement(AST_statement* in)
   {
      num_statements++;
   }
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, "ast");
}

extern "C" void run (AST_php_script* in, Pass_manager* pm)
{
	in->visit (new Count_statements ());
}
