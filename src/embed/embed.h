/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap the embedded PHP run-time
 */

#ifndef PHC_EMBED_H
#define PHC_EMBED_H

#include "config.h"
#include "lib/List.h"

class String;

namespace AST
{
	class Literal;
	class Expr;
}

namespace MIR
{
	class Literal;
	typedef List<Literal*> Literal_list;
	class Expr;
	class METHOD_NAME;
	class OP;
	class CAST;
}

class PHP
{
private:
	static bool is_started;
	
public:
	static bool is_available ();
	static void startup_php ();
	static void shutdown_php ();

	/*
	 * Front-end (defined in embed.cpp)
	 * TODO: move to frontend.cpp
	 */
	static AST::Literal* convert_token (AST::Literal* token);
	static unsigned long get_hash (String* string);
	static AST::Expr* fold_constant_expr (AST::Expr* in);

	/*
	 * Optimization (defined in optimize.cpp)
	 */

	// Folding
	static MIR::Literal* fold_unary_op (MIR::OP* op, MIR::Literal* literal);
	static bool is_true (MIR::Literal* literal);
	static MIR::Literal* cast_to (MIR::CAST* cast, MIR::Literal* literal);
	static MIR::Literal* fold_bin_op (MIR::Literal* left, MIR::OP* op, MIR::Literal* right);

	// Functions
	static bool is_pure_function (MIR::METHOD_NAME* in);
	static MIR::Literal* call_function (MIR::METHOD_NAME* in, MIR::Literal_list* params);
};

#endif // PHC_EMBED_H
