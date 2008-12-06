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
typedef List<String*> String_list;

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
	class Constant;
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

	/* Set INI behaviour */
	static void set_ini_entry (std::string key, std::string value);
	static String_list* get_include_paths ();

};

#endif // PHC_EMBED_H
