#include "AST_visitor.h"

class Rename_foo_to_bar : public AST_visitor
{
   void pre_method_name(Token_method_name* in)
   {
      if(*in->value == "foo")
         in->value = new String("bar");
   }
};

extern "C" void process_ast(AST_php_script* php_script)
{
	Rename_foo_to_bar f2b;
	php_script->visit(&f2b);
}
