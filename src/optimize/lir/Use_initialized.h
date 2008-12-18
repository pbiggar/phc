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
	Map<string, Set<string> > zvp_map;
	Map<string, Set<string> > zvpp_map;

	void pre_block (LIR::Block* in, LIR::Piece_list* out);
	void pre_opt (LIR::Opt* in, LIR::Statement_list* out);
	void post_if (LIR::If* in, LIR::Statement_list* out);
	LIR::Cond* post_cond (LIR::Cond* in);
};

#endif // PHC_USE_INITIALIZED
