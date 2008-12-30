/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate C from the LIR
 */

#include "process_ir/General.h"
#include "pass_manager/Pass_manager.h"

#include "Generate_C_pass.h"
#include "Generate_C.h"
#include "embed/embed.h"

using namespace std;
using namespace boost;

// These probably wont clash.
using namespace MIR;

bool Generate_C_pass::pass_is_enabled (Pass_manager* pm)
{
	return pm->args_info->generate_c_flag or pm->args_info->compile_flag;
}

void Generate_C_pass::run (IR::PHP_script* in, Pass_manager* pm)
{
	if (not PHP::is_available ())
	{
		// TODO would be better if we checked for these at run-time if they
		// werent available at compile time.
		phc_error (	"phc requires PHP to be avaiable for compilation. " 
						"Please install the PHP embed SAPI, "
						"and run 'configure' on phc again");

		// TODO more information perhaps? Or integrate with configure warning?
	}

	stringstream ss;
	Generate_C* gen = new Generate_C (ss);
	in->visit (gen);

	if (pm->args_info->generate_c_flag)
	{
		cout << ss.str ();
	}

	os << ss.str ();
}

/*
 * Bookkeeping 
 */

Generate_C_pass::Generate_C_pass (ostream& os) : os (os)
{
	name = new String ("generate-c");
	description = new String ("Generate C code from the LIR");
}
