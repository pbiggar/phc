/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Use mark-initialized annotations to optimize the LIR.
 */

#ifndef PHC_USE_INITIALIZED
#define PHC_USE_INITIALIZED

#include "LIR_transform.h"

class Use_initialized : public LIR::Transform
{
	void pre_block (LIR::Block* in, LIR::Piece_list* out);
	void pre_if (LIR::If* in, LIR::Statement_list* out);
};

#endif // PHC_USE_INITIALIZED
