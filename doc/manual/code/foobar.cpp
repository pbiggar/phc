#include "AST_visitor.h"

class Rename_foo_to_bar : public Visitor
{
   void pre_method_name(METHOD_NAME* in)
   {
      if(*in->value == "foo")
         in->value = new String("bar");
   }
};

extern "C" void process_ast(PHP_script* php_script)
{
	Rename_foo_to_bar f2b;
	php_script->visit(&f2b);
}
