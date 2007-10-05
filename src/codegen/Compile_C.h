/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Compile generated C code
 */

#include "process_ast/Pass_manager.h"

class Compile_C : public Pass
{
public:
	stringstream& os;

	Compile_C (stringstream& os);
	void run (AST::AST_php_script* in, Pass_manager* pm);
};
