#include "If_simplification.h"
#include "process_ir/General.h"
#include "Def_use_web.h"
#include <iostream>

using namespace MIR;

void
If_simplification::visit_branch_block (Branch_block* bb)
{
	/* Turn
	 *
	 *		if (!$x) goto L1; else goto L2;
	 *
	 *	into
	 *
	 *		if ($x) goto L2; else goto L1;
	 */


		Def_use_web* duw = bb->cfg->duw;

		bool simplify = false;
		SSA_use* use;

		// Check if the correct use is actually in the block
		foreach (SSA_use* temp, *duw->get_block_uses (bb))
		{	if (use->type_flag != SSA_PHI)
			{
				string v = *bb->branch->variable_name->value;
				string s = temp->name->get_name ();

				if (s == "*_"+v)
				{
					use = temp;
					simplify = true;
				}
			}
		}
		
		if (simplify)
		{
			SSA_def_list* defs = use->get_defs ();

			if (defs->size () == 1)
			{
				Statement_block* sb; 
				if ((sb = dynamic_cast<Statement_block*> (defs->front()->bb)))
				{
					Assign_var* ass_var;
					Unary_op* un_op;
					if ((ass_var = dynamic_cast<Assign_var*> (sb->statement)))
					{
						if ((un_op = dynamic_cast<Unary_op*> (ass_var->rhs)))
						{
							if (*un_op->op->value == "!")	
							{
								// I don't like this, I don't think I should need it....
								if (*un_op->variable_name->value != *bb->branch->variable_name->value)
								{	
									bb->branch->variable_name = un_op->variable_name->clone ();
									bb->switch_successors ();
								}
							}
						}
					}
				}
			}
			else
			{
				phc_unreachable ();
			}
			
		}

}
