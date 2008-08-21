/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Dead-code elimination
 */

#include "Flow_visitor.h"

#ifndef PHC_DEAD_CODE_ELIMINATION 
#define PHC_DEAD_CODE_ELIMINATION

class Dead_code_elimination : public Forward_flow_visitor
{
public:

	void transform_statement_block (Statement_block*, list<Basic_block*>*);
};

#endif // PHC_DEAD_CODE_ELIMINATION
