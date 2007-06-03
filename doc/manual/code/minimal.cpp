#include <AST.h>

extern "C" void process_ast(AST_php_script* php_script)
{
   cout << "Hello world (I'm a phc plugin!)" << endl;
}
