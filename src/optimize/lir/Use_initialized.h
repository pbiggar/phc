/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Use mark-initialized annotations to optimize the LIR.
 */

#ifndef PHC_USE_INITIALIZED
#define PHC_USE_INITIALIZED

#include "LIR_transform.h"
#include "lib/Set.h"

class Use_initialized : public LIR::Transform
{
	Set<string> init_zvps;
	Set<string> init_zvpps;
	Set<string> uninit_zvps;
	Set<string> uninit_zvpps;
	void pre_block (LIR::Block* in, LIR::Piece_list* out);
	void pre_if (LIR::If* in, LIR::Statement_list* out);
	void pre_opt (LIR::Opt* in, LIR::Statement_list* out);
};

#endif // PHC_USE_INITIALIZED
