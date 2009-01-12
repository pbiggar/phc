#ifndef PHC_ORACLE
#define PHC_ORACLE

#include "MIR.h"
#include "Method_information.h"

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
	static Map<string, Method_info*> infos;
public:

	static void initialize ();
	static void add_method_info (Method_info* info);
	static Method_info* get_method_info (String* name);

	// Convert the signature into a Method_info, and add it.
	static void add_signature (MIR::Signature* sig);

	// TODO: Is 'const' the correct term?
	// This means that a function does not affect any global variables. No is
	// returned if we've never heard of the function (most likely because its
	// a user function).
	static bool is_const_function (MIR::METHOD_NAME* method_name);
	static bool is_pure_function (MIR::METHOD_NAME* method_name);
};

#endif // PHC_ORACLE
