/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Move dynamic class definitions to the top-level, and replace them with
 * run-time aliases.
 */

#ifndef PHC_LOWER_DYNAMIC_DEFINITIONS_H
#define PHC_LOWER_DYNAMIC_DEFINITIONS_H

#include "HIR_transform.h"
#include "MIR.h"

class Lower_dynamic_definitions : public HIR::Transform, public virtual GC_obj
{
	HIR::Statement_list* new_defs;

public:
	void children_php_script(HIR::PHP_script* in);
	void post_statement (HIR::Statement* in, HIR::Statement_list* out);
	void post_class_def (HIR::Class_def* in, HIR::Statement_list* out);
	void post_interface_def (HIR::Interface_def* in, HIR::Statement_list* out);
};

#endif // PHC_LOWER_DYNAMIC_DEFINITIONS_H
