/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "pass_manager/Pass_manager.h"

using namespace AST;

class MySQL2DBX : public AST_visitor
{
public:
   void post_method_invocation(AST_method_invocation* in)
   {
      List<AST_actual_parameter*>::iterator pos;
      Token_constant_name* module_name;
      AST_constant* module_constant;
      AST_actual_parameter* param;
 
      if(in->method_name->match(new Token_method_name(new String("mysql_connect"))))
      {
         // Check for too many parameters
         if(in->actual_parameters->size() > 3)
         {
            printf("Error: unable to translate call "
               "to mysql_connect on line %d\n", in->get_line_number());
            return;
         }
      
         // Modify name
         in->method_name = new Token_method_name(new String("dbx_connect"));
		
         // Modify parameters
         module_name = new Token_constant_name(new String("DBX_MYSQL"));
         module_constant = new AST_constant(NULL, module_name);
         
		 pos = in->actual_parameters->begin();
         param = new AST_actual_parameter(false, module_constant);
         in->actual_parameters->insert(pos, param); pos++;
         /* Skip host */ pos++;
         param = new AST_actual_parameter(false, new Token_null(new String("NULL")));
         in->actual_parameters->insert(pos, param); 
      }
   }
};

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	pm->add_after_named_pass (pass, "ast");
}

extern "C" void run (AST_php_script* in, Pass_manager* pm)
{
	in->visit (new MySQL2DBX ());
}
