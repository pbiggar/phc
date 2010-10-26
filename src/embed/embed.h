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
#include "lib/Set.h"

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
	class VARIABLE_NAME;
	typedef List<VARIABLE_NAME*> VARIABLE_NAME_list;
}

class Method_info;

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
	static Set<std::string> altered_ini_entries;

	static String* max_execution_time;

	static void set_ini_entry (String* key, String* value);
	static String* get_ini_entry (String* key);

	static String_list* get_altered_ini_entries ();

	/* Expose include behaviour 
	 * TODO:
	 *		mention these at compile-time.
	 */
	static void add_include (String* full_path);
	static bool is_included (String* full_path);
	static String_list* get_include_paths ();

	/* Superglobals */
	static MIR::VARIABLE_NAME_list* get_superglobals ();

	/*
	 * Optimization (defined in optimize.cpp)
	 */

	// Folding
	static MIR::Literal* fold_unary_op (MIR::OP* op, MIR::Literal* literal);
	static bool is_true (MIR::Literal* literal);
	static MIR::Literal* cast_to (MIR::CAST* cast, MIR::Literal* literal);
	static String* get_string_value (MIR::Literal* lit);
	static MIR::Literal* fold_bin_op (MIR::Literal* left, MIR::OP* op, MIR::Literal* right);
	static MIR::Literal* fold_pre_op (MIR::Literal* literal, MIR::OP* op);
	static MIR::Literal* fold_constant (MIR::Constant* constant);
	static MIR::Literal* fold_string_index (MIR::Literal* array, MIR::Literal* index);

	// Functions
	static Method_info* get_method_info (String* name);
	static MIR::Literal* call_function (MIR::METHOD_NAME* in, MIR::Literal_list* params);
};

#endif // PHC_EMBED_H
