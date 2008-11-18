#include "Oracle.h"
#include "embed/embed.h"

using namespace MIR;


Map<string, Signature*> Oracle::sigs;

Signature*
Oracle::get_signature (METHOD_NAME* method_name)
{
	// Cached
	if (Oracle::sigs.has (*method_name->value))
		return Oracle::sigs[*method_name->value];

	// Lookup the embed SAPI
	Signature* sig = PHP::get_signature (method_name);

	// Cache it
	if (sig)
		add_signature (method_name, sig);

	return sig;
}

void
Oracle::add_signature (METHOD_NAME* method_name, Signature* sig)
{
	if (Oracle::sigs.has (*method_name->value))
		assert (0);
	
	sigs[*method_name->value] = sig;
}
