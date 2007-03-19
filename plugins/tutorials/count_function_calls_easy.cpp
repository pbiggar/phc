/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "AST_visitor.h"

class Count_function_calls : public AST_visitor
{
private:
   int num_function_calls;

public:
   // Set num_function_calls to zero before we begin
   void pre_php_script(AST_php_script* in)
   {
      num_function_calls = 0;
   }

   // Print the number of function calls when we are done
   void post_php_script(AST_php_script* in)
   {
      printf("%d function calls found\n", num_function_calls);
   }
   
   // Count the number of function calls
   void post_method_invocation(AST_method_invocation* in)
   {
      num_function_calls++;
   }
};

extern "C" void process_ast(AST_php_script* php_script)
{
	Count_function_calls cfc;
	php_script->visit(&cfc);
}
