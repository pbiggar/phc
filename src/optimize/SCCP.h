#ifndef PHC_SCCP_H_
#define PHC_SCCP_H_

#include "CFG.h"
#include "Lattice.h"

class SCCP
{
	CFG* cfg;
	Lattice lattice;
public:
	SCCP (CFG* cfg);
	void execute ();
	void visit_phi (Phi* phi);
	void visit_statement (MIR::Statement* in);
	void visit_branch (MIR::Branch* in);

 };


#endif // PHC_SCCP_H
