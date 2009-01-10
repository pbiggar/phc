/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Conditional constant propagation.
 *
 * In theory this is Wegbreits conditional constant propagation, but I'm just
 * going to steal the implementation from SCCP, so its a step forward, and then
 * one back, which will probably land in about the same place.
 *
 */

#ifndef PHC_CCP
#define PHC_CCP

#include "WPA.h"

class CCP : public WPA
{
public:
	CCP ();
	void eval_bb (Basic_block* bb);
};

#endif // PHC_CPP
