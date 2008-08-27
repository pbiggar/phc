/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Wrap the embedded PHP run-time
 */

#ifndef PHC_EMBED_H
#define PHC_EMBED_H

class String;
namespace AST
{
	class Literal;
	class Expr;
}

class PHP
{
private:
	static bool is_started;
	
public:
	static bool is_available ();
	static void startup_php ();
	static void shutdown_php ();


	static AST::Literal* convert_token (AST::Literal* token);
	static unsigned long get_hash (String* string);
	static AST::Expr* fold_constant_expr (AST::Expr* in);
};

#endif // PHC_EMBED_H
