/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Iterate over visitors and transforms until they complete.
 *
 * TODO maybe better to do this at the pass level?
 */

#ifndef PHC_FIX_POINT
#define PHC_FIX_POINT

#include "HIR_transform.h"
#include "HIR_visitor.h"

class Fix_point : public HIR::Visitor, public HIR::Transform, public virtual GC_obj
{
public:
	int iterations;
	bool iterate_again;

public:

	Fix_point ();
	void visit_php_script (HIR::PHP_script* in);
	void children_php_script (HIR::PHP_script* in);
};

#endif // PHC_FIX_POINT
