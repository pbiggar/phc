#ifndef PHC_ORACLE
#define PHC_ORACLE

#include "MIR.h"

// The optimization oracle. This is a layer between the PHP:: embed functions
// and the optimizer, in order to allow the optimizer update the information.
//
// TODO: though currently a singleton, we may want to make this instantiable
// (and clonable presumably) to handle context-sensitivity, or speculative
// optimizations.
class Oracle : virtual public GC_obj
{
private:
	Oracle ();
	static Map<string, MIR::Signature*> sigs;
public:

	static void initialize ();

	// Returns NULL if none is available
	static MIR::Signature* get_signature (MIR::METHOD_NAME* method_name);

	// If signature is not already added, add it.
	static void add_signature (MIR::Signature* sig);

	// TODO: Is 'const' the correct term?
	// This means that a function does not affect any global variables. No is
	// returned if we've never heard of the function (most likely because its
	// a user function).
	static bool is_const_function (MIR::METHOD_NAME* method_name);
	static bool is_pure_function (MIR::METHOD_NAME* method_name);
};

#endif // PHC_ORACLE
