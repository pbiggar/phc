#ifndef PHC_ORACLE
#define PHC_ORACLE

#include "MIR.h"

// The optimization oracle. This is a layer between the PHP:: embed functions
// and the optimizer, in order to allow the optimizer update the information.
//
// TODO: though currently a singleton, we may want to make this instantiable
// (and clonable presumably) to handle context-sensitivity, or speculative
// optimizations.
class Oracle
{
private:
	Oracle ();
public:
	static Map<string, MIR::Signature*> sigs;

	// Returns NULL if none is available
	static MIR::Signature* get_signature (MIR::METHOD_NAME* method_name);

	static void add_signature (MIR::METHOD_NAME* method_name, MIR::Signature* sig);
};

#endif // PHC_ORACLE
