/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Dead-code elimination
 */

#ifndef PHC_DEAD_CODE_ELIMINATION 
#define PHC_DEAD_CODE_ELIMINATION

#include "Visit_once.h"

/*
 * The Cooper/Torczon lecture notes:
 *		http://www.cs.rice.edu/~keith/512/Lectures/10DeadCprop.pdf
 *
 *	Has a mark-sweep-style DCE algorithm:
 *
 *	Mark:
 *		foreach statement S
 *			if S is critical:  // involved in side-effecting operation
 *				mark S
 *				add S to worklist
 *
 *		while (!worklist.empty())
 *			remove S from worklist
 *			foreach U in s.uses
 *				mark U.def
 *				add U.def to worklist
 *
 *			foreach bb in RDF (S): // reverse dominance frontier
 *				mark branch at end of block BB // hmmmm
 *				add branch to worklist
 *
 *	Sweep:
 *		foreach statement S
 *			if S not marked:
 *				if S is a branch:
 *					rewrite with jmp to S' 'nearest useful post-dominator'
 *				else
 *					remove S // this assumes 'normal' BBs, which we dont use.
 *			
 *
 *
 *	However, it is much simpler to just iterate through the analysis list,
 *	using this analysis:
 *
 * foreach v in all_program_variables:
 *		if (v.uses.size() == 0)
 *			remove (s)
 *
 *	Since it doesnt involve updating the SSA information, which can be hard.
 *	However, the 'aggressive' DCE is better. For example, it _should_ (I
 *	think) remove Phi nodes which are only used in the same phi node (or other
 *	cyclic problems).
 *
 *	Note, if you remove a block, the edge should go to its post-dominator.
 */

class DCE : public Visit_once
{
public:
	void transform_assign_var (Statement_block*, MIR::Assign_var* in, BB_list* out);

	void transform_phi_node (Basic_block* bb, Phi* in, Phi_list* out);

	void transform_eval_expr (Statement_block* bb, MIR::Eval_expr* in, BB_list* out);
};

#endif // PHC_DEAD_CODE_ELIMINATION
