/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Use mark-initialized annotations to optimize the LIR.
 */


// TODO: add a pass (and annotations) which use alias information to say
// varaibles cannot be references.

#include "Use_initialized.h"
#include "process_ir/debug.h"
using namespace LIR;
using namespace std;

void
Use_initialized::pre_block(Block* in, Piece_list* out)
{
	out->push_back (in);

	//	reset everything
	init_zvps.clear ();

//	Map<string, opt_value> map;
//	map["phc.codegen.is_initialized"] = IS_INIT;
//	map["phc.codegen.is_uninitialized"] = IS_UNINIT;
}

void
Use_initialized::pre_opt (Opt* in, Statement_list* out)
{
	 // The becomes a comment
	out->push_back (in);

	// Record the annotation
	String* value = in->value->value;
	if (*value == "is_initialized")
	{
		if (ZVP* zvp = dynamic_cast<ZVP*> (in->param))
			init_zvps.insert (*zvp->value);

		if (ZVPP* zvpp = dynamic_cast<ZVPP*> (in->param))
			init_zvpps.insert (*zvpp->value);
	}

	if (*value == "is_uninitialized")
	{
		if (ZVP* zvp = dynamic_cast<ZVP*> (in->param))
			uninit_zvps.insert (*zvp->value);

		if (ZVPP* zvpp = dynamic_cast<ZVPP*> (in->param))
			uninit_zvpps.insert (*zvpp->value);
	}
}


void
Use_initialized::pre_if(If* in, Statement_list* out)
{
	// If we know a variable is initialized, remove the equals NULL check.
	// If we know a variable is not initialized, remove the equals NULL
	// check.
	Wildcard<ZVP> zvp;
	if (in->cond->match (new Equals (&zvp, new Null)))
	{
		if (init_zvps.has (*zvp.value->value))
		{
			out->push_back_all (in->iffalse);
			return;
		}

		if (uninit_zvps.has (*zvp.value->value))
		{
			out->push_back_all (in->iftrue);
			return;
		}
	}

	// Now the same for deref (ZVPP).

		// If we know a variable is not initialized, remove the is_ref check.
/*		if cond->match (zvpp->is_ref)
		{
			if opt_info[zvpp->variable_name] == is_uninit
				return iffalse;
		}
*/
	out->push_back (in);

}


