/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Optimization oracle acts as a go-between for the Optimization passes and
 * Embed.
 */
 

#ifndef PHC_ORACLE
#define PHC_ORACLE

#include "MIR.h"
#include "embed/embed.h"
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

	// TODO: the oracle was supposed to be an interface which hid the difference
	// between information from the Embed SAPI, annotations of internals, and
	// analyses information. But some it is possible to change some of that
	// information, so its likely there need to be multiple instances of this.
	static void initialize (MIR::PHP_script*);

	static void add_method_info (Method_info* info);
	static Method_info* get_method_info (String* name);

	// Convert the signature into a Method_info, and add it.
	static void add_signature (MIR::Signature* sig);

	static Method_info_list* get_all_methods ();

	// TODO: Is 'const' the correct term?
	// This means that a function does not affect any global variables. No is
	// returned if we've never heard of the function (most likely because its
	// a user function).
	static bool is_const_function (MIR::METHOD_NAME* method_name);
	static bool is_pure_function (MIR::METHOD_NAME* method_name);
};

#endif // PHC_ORACLE
