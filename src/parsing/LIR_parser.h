/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Provide convenience functions for parsing code represented as S-expressions (ish).
 */

// TODO: expand this so we can do it for any IR.
#ifndef PHC_LIR_PARSER
#define PHC_LIR_PARSER

class String;
namespace LIR
{
	class Node;
}

LIR::Node* parse_lir (String* s);

#endif // PHC_LIR_PARSER
