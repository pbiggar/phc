/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

#include "pass_manager/Plugin_pass.h"
#include <iostream>

using namespace std;

extern "C" void load (Pass_manager* pm, Plugin_pass* pass)
{
	cout << "Hello world (I'm a phc plugin!)" << endl;
}
