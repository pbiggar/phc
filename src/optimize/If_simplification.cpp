#include "If_simplification.h"
#include "process_ir/General.h"
#include "Def_use_web.h"
#include "wpa/Context.h"
#include "wpa/Def_use.h"
#include "wpa/Points_to.h"
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

	Context* cx = Context::non_contextual (bb);
	string ns = cx->symtable_name ();

	// Extract the correct use from the branch
	SSA_use* use = NULL;
	bool simplify = false;
	foreach (SSA_use* temp, *bb->cfg->duw->get_block_uses (bb))
	{
		if (temp->type_flag != SSA_PHI)
		{
			string s = temp->name->get_name ();
			Index_node name (ns, *bb->branch->variable_name->value);
			if (s == name.get_starred_name()->str())
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

								// Fix def-use information. We won't fix Def_use_web since it will be
								// destroyed after this pass.
								Def_use *du = bb->cfg->duw->get_def_use();

								foreach (const Index_node *use, *du->get_uses(bb))
									du->remove_use(bb, use);

								Basic_block *correct_bb = defs->front()->bb;
								Index_node *correct_index = IN(ns, *un_op->variable_name->value);

								// FIXME: Could I add the correct index node directly?
								// du->insert_use(bb, correct_index);

								// Let's be conservative and add the previously known Index_node pointer.
								foreach (const Index_node *use, *du->get_uses(correct_bb)) {
									if (*use == *correct_index)
										du->insert_use(bb, use);
								}
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
