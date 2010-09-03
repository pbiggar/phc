/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * The lowering passes introduce a lot of unnecessary copies, which
 * add extra reference counts, resulting in extra copying and poor
 * performance.
 *
 * This removes assignments from simple variables to compiler-generated
 * temporaries, so long as the temporary is never used.
 *
 * HACK TODO: Remove.
 * This is exactly the sort of hacky thing we wanted
 * to remove. This would be much better done with a data-flow
 * framework, but is much easier than cleaning up the passes, which
 * would otherwise be necessary.
 *
 */

#ifndef PHC_DEAD_TEMP_CLEANUP
#define PHC_DEAD_TEMP_CLEANUP

#include "Fix_point.h"

class Dead_temp_cleanup : public Fix_point
{
public:
	Dead_temp_cleanup ();

	void children_php_script (HIR::PHP_script* in);
	void pre_assign_var (HIR::Assign_var* in, HIR::Statement_list* out);
};

#endif // PHC_DEAD_TEMP_CLEANUP
