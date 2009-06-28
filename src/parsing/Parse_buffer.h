/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Provide convenience operators for parsing code.
 *
 * TODO:
 *		After parsing, there are a list of new nodes. Each one needs a line
 *		number and a filename. Each node that was passed to the parsing needs to
 *		be searched for, and needs attributes copied. It isnt sufficient by a
 *		long way to copy attributes from the top-level to nodes without attributes.
 */

#ifndef PHC_PARSE_BUFFER
#define PHC_PARSE_BUFFER

#include "process_ir/General.h"
#include "process_ast/AST_unparser.h"
#include "process_hir/HIR_unparser.h"
#include "process_mir/MIR_unparser.h"
#include "process_ir/Clone_blank_mixins.h"
#include "pass_manager/Pass_manager.h"
#include "lib/demangle.h"

#include "parsing/parse.h"

extern Pass_manager* pm;

// TODO: figure out how to get rid of these nasty hacks
template <
	class Node,
	class Statement,
	class PHP_script,
	class Visitor>
class Parse_buffer : public virtual GC_obj
{
	/* TODO: make these private and give protected access to << via */
	/* a friend declaration. */
public:
	List<Statement*>* stmts;
	stringstream ss;

	/* These nodes are unparsed into the stream, so we need to find
	 * matching statements into which to copy their attributes. */
	List<Node*> used_nodes;

public:

	void finish (Node* anchor)
	{
		// Get the namespace - a hack, but avoids the nastiness with macros
		// otherwise.
		String* pass = s (demangle (anchor, true));
		pass = s (pass->substr (0, 3));
		pass = pass->to_lower ();
		assert (*pass == "ast" || *pass == "hir" || *pass == "mir");
		if (*pass == "ast")
			pass = s ("sua");

		return to_pass (pass, anchor);
	}

	void to_pass (String* pass, Node* anchor)
	{
		DEBUG ("Parsing:\n" << ss.str ());
		AST::PHP_script* ast = parse_code (s(ss.str ()), NULL, 0);
		IR::PHP_script* ir = pm->run_until (pass, ast);
		PHP_script* script = NULL;

		// Sigh. Another hack. Anytime we try to do anything generic it ends up
		// like this.
		if (ir->is_AST ())
			script = dynamic_cast<PHP_script*> (ir->as_AST ());
		else if (ir->is_HIR ())
			script = dynamic_cast<PHP_script*> (ir->as_HIR ());
		else
			script = dynamic_cast<PHP_script*> (ir->as_MIR ());

		script->visit (new Clone_blank_mixins<Node, Visitor> (anchor, &used_nodes));
		stmts->push_back_all (script->statements);
	}
};

#define create_parse_buffer_declaration(NS)											\
class NS##_parse_buffer :																	\
	public Parse_buffer<NS::Node, NS::Statement, NS::PHP_script, NS::Visitor>\
{																									\
};																									\
/* These can start the buffer */															\
NS##_parse_buffer& operator<<(List<NS::Statement*>& stmts, string in);		\
NS##_parse_buffer& operator<<(List<NS::Statement*>& stmts, NS::Node* in);	\
																									\
/* These can continue the stream */														\
NS##_parse_buffer& operator<<(NS##_parse_buffer& out, NS::Node* in);			\
NS##_parse_buffer& operator<<(NS##_parse_buffer& out, string in);				\
NS##_parse_buffer& operator<<(NS##_parse_buffer& out, String* in);			\
NS##_parse_buffer& operator<<(NS##_parse_buffer& out, int in);

create_parse_buffer_declaration(AST);
create_parse_buffer_declaration(HIR);
create_parse_buffer_declaration(MIR);

#endif // PHC_PARSE_BUFFER
