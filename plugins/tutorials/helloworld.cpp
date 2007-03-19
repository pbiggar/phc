/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "AST.h"
#include <iostream>

using namespace std;

extern "C" void process_ast(AST_php_script* php_script)
{
	cout << "Hello world (I'm a phc plugin!)" << endl;
}
