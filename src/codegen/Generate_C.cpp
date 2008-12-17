/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate C from the LIR
 */

#include "process_ir/General.h"
#include "process_ir/XML_unparser.h"
#include "process_lir/LIR_unparser.h"
#include "pass_manager/Pass_manager.h"

#include "Generate_C.h"
#include "embed/embed.h"

using namespace std;
using namespace boost;

// These probably wont clash.
using namespace LIR;

bool Generate_C::pass_is_enabled (Pass_manager* pm)
{
	return pm->args_info->generate_c_flag or pm->args_info->compile_flag;
}

void Generate_C::run (IR::PHP_script* in, Pass_manager* pm)
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
	LIR_unparser* lup = new LIR_unparser (ss);
	lup->unparse (in->as_LIR ());

	if (pm->args_info->generate_c_flag)
	{
		cout << ss.str ();
	}

	os << ss.str ();
}

/*
 * Bookkeeping 
 */

Generate_C::Generate_C(ostream& os) : os (os)
{
	name = new String ("generate-c");
	description = new String ("Generate C code from the MIR");
}
