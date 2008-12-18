/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Use mark-initialized annotations to optimize the LIR.
 */


// TODO: add a pass (and annotations) which use alias information to say
// varaibles cannot be references.

#include "Use_initialized.h"
using namespace LIR;

void
Use_initialized::pre_block(Block* in, Piece_list* out)
{
//	Map<string, opt_value> map;
//	map["phc.codegen.is_initialized"] = IS_INIT;
//	map["phc.codegen.is_uninitialized"] = IS_UNINIT;

//	reset everything
//	process optimization data
	foreach (Statement* s, *in->statements)
	{
//		if (!isa<Opt_data> (s))
			break;

//		Opt_data* opt = dyc<Opt_data> (s);

//		if (ZVP* zvp = dynamic_cast<ZVPP*> (opt->variable_name))
//			zvps[*zvp->value] = IS_INIT;
	}
}


void
Use_initialized::pre_if(If* in, Statement_list* out)
{
/*
		// If we know a variable is initialized, remove the equals NULL check.
		// If we know a variable is not initialized, remove the equals NULL
		// check.
		if cond->match (zvpp == NULL)
		{
			if opt_info[zvpp->varaible_name] == is_init
				return iffalse;
			else if opt_info[zvpp->varaible_name] == is_uninit
				return iftrue;
		}

		// If we know a variable is not initialized, remove the is_ref check.
		if cond->match (zvpp->is_ref)
		{
			if opt_info[zvpp->variable_name] == is_uninit
				return iffalse;
		}
*/
}


