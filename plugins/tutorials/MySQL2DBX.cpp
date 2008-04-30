/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "pass_manager/Plugin_pass.h"
#include "AST_visitor.h"
#include "process_ir/General.h"

using namespace AST;

class MySQL2DBX : public Visitor
{
public:
   void post_method_invocation(Method_invocation* in)
   {
      List<Actual_parameter*>::iterator pos;
      CONSTANT_NAME* module_name;
      Constant* module_constant;
      Actual_parameter* param;
 
      if(in->method_name->match(new METHOD_NAME(new String("mysql_connect"))))
      {
         // Check for too many parameters
         if(in->actual_parameters->size() > 3)
         {
            printf("Error: unable to translate call "
               "to mysql_connect on line %d\n", in->get_line_number());
            return;
         }
      
         // Modify name
         in->method_name = new METHOD_NAME(new String("dbx_connect"));
		
         // Modify parameters
         module_name = new CONSTANT_NAME(new String("DBX_MYSQL"));
         module_constant = new Constant(NULL, module_name);
         
		 pos = in->actual_parameters->begin();
         param = new Actual_parameter(false, module_constant);
         in->actual_parameters->insert(pos, param); pos++;
         /* Skip host */ pos++;
         param = new Actual_parameter(false, new NIL());
         in->actual_parameters->insert(pos, param); 
      }
   }
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, s("ast"));
}

extern "C" void run_ast (PHP_script* in, Pass_manager* pm, String* option)
{
	in->visit (new MySQL2DBX ());
}
