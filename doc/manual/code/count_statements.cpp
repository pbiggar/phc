#include <AST.h>

extern "C" void process_ast(PHP_script* php_script)
{
   printf("%d statement(s) found\n", php_script->statements->size());
}
