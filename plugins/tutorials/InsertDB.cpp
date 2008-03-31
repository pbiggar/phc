/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "pass_manager/Plugin_pass.h"
#include "AST_visitor.h"
#include "process_ir/General.h"

using namespace AST;

class InsertDB : public Visitor
{
private:
   int uses_dbx;
   
public:
   void pre_method(Method* in)
   {
      uses_dbx = false;   
   }

   void post_method(Method* in)
   {
      if(uses_dbx)
         in->signature->method_name->value->append("_DB");
   }

   void post_method_invocation(Method_invocation* in)
   {
      Wildcard<METHOD_NAME>* pattern = new Wildcard<METHOD_NAME>;
      
      // Check for dbx_
      if(in->method_name->match(pattern) && 
         pattern->value->value->find("dbx_") == 0)
      {
         uses_dbx = true;
      }
   }
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("ast"));
}


extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
   in->visit (new InsertDB ());
}
