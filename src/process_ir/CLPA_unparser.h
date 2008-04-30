/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Generate syntax databases for the Calypso interpreter.
 */

#ifndef PHC_CLPA_UNPARSER
#define PHC_CLPA_UNPARSER

#include <iostream>
#include <stack>
#include "lib/base64.h"
#include "lib/demangle.h"
#include "lib/error.h"
#include "lib/String.h"
#include "lib/List.h"

template
<
	class Script,
	class Node,
	class Literal,
	class Identifier,
	class Visitor
>
class CLPA_unparser : public Visitor 
{
protected:
	stack<Object*> ids;

public:

/*	void visit_marker(char const* name, bool value)
	{
		ids.push (new Boolean (value));
	}
*/
	void pre_list(char const* type_id, int size)
	{
		cout << "LIST" << endl;
		cout << "<" << type_id << "_list>" << endl;
	}

	void post_list(char const* type_id, int size)
	{
		cout << "POST_LIST" << endl;
		cout << "</" << type_id << "_list>" << endl;
	}

	/* Get an id for this node, and add it to the stack. The magic
	 * happens in post_node. */
	void pre_node(Node* in)
	{
		cdebug << "Adding: " << demangle(in, true);
		debug(in);
		cdebug << endl;
		in->attrs->set ("phc.clpa.id", get_id (in));
		ids.push (in);
	}

	void pre_identifier (Identifier* in)
	{
		cdebug << "Adding value: " << demangle(in, true);
		cdebug << endl;
		ids.push (in->get_value_as_string ());
	}

	void pre_literal (Literal* in)
	{
		cdebug << "Adding value: " << demangle(in, true);
		cdebug << endl;
		ids.push (in->get_value_as_string ());
	}



	/* If we search backwards down the stack until we find our own
	 * node, then all subnodes will be parameters to this node. */
	void post_node(Node* in)
	{
		cout << "phc_" << demangle(in, false) << " (";

		
		// The params are either IDs or literals
		List<String*>* params = new List<String*>;
		while (ids.top () != in)
		{
			Object* obj = ids.top();
			cdebug << "Removing: " << demangle(obj, true);

			// Get IDs for nodes
			if (dynamic_cast<Literal*> (obj))
			{
				Literal* lit = dynamic_cast<Literal*> (obj);
				debug (lit);
				cdebug << endl;
				params->push_back (lit->get_value_as_string ());
			}
			else if (dynamic_cast<Node*> (obj))
			{
				Node* node = dynamic_cast<Node*> (obj);
				debug (node);
				cdebug << endl;
				params->push_back (node->attrs->get_string ("phc.clpa.id"));
			}
/*			else if (dynamic_cast<Boolean*> (obj))
			{
				Boolean* b = dynamic_cast<Boolean*> (obj);
				params->push_back (s(b->value() ? "true" : "false"));
			}
*/			else if (dynamic_cast<String*> (obj))
			{
				String* b = dynamic_cast<String*> (obj);
				params->push_back (b);
			}
			else
			{
				cout << "TODO" << endl;
				assert (0);
			}

			ids.pop ();
		}

		List<String*>::const_iterator i = params->begin ();
		while (i != params->end ())
		{
			cout << **i;
			i++;

			// no comma on final iteration
			if (i != params->end ())
				cout << ", ";

		}
		cout << ")" << endl;
	}

protected:

	String* get_id (Node* node)
	{
		static int id = 0;
		String* string_id;

		if (node->attrs->has ("phc.clpa.id"))
			string_id = node->attrs->get_string ("phc.clpa.id");
		else
		{
			stringstream ss;
			ss << "#" << id;
			string_id = new String(ss.str());
			node->attrs->set ("phc.clpa.id", string_id);
			id++;
		}
		return string_id;
	}


	void print_attributes(Node* in)
	{
		if(in->attrs->size() == 0)
		{
			cout << "<attrs />" << endl;
		}
		else
		{
			cout << "<attrs>" << endl;

			AttrMap::const_iterator i;
			for(i = in->attrs->begin(); i != in->attrs->end(); i++)
			{
//				print_attribute((*i).first, (*i).second);
			}

			cout << "</attrs>" << endl;
		}
	}

	void print_attribute(string name, Object* attr)
	{
		if(String* str = dynamic_cast<String*>(attr))
		{
			cout << "<attr key=\"" << name << "\">";
//			maybe_encode ("string", str);
			cout << "</attr>" << endl;
		}
		else if(Integer* i = dynamic_cast<Integer*>(attr))
		{
			cout << "<attr key=\"" << name << "\"><integer>" << i->value () << "</integer></attr>" << endl;
		}
		else if(Boolean* b = dynamic_cast<Boolean*>(attr))
		{
			cout << "<attr key=\"" << name << "\"><bool>" << (b->value() ? "true" : "false") << "</bool></attr>" << endl;
		}
		else if(List<String*>* ls = dynamic_cast<List<String*>*>(attr))
		{
			cout << "<attr key=\"" << name << "\"><string_list>" << endl;

			List<String*>::const_iterator j;
			for(j = ls->begin(); j != ls->end(); j++)
			{
//				maybe_encode ("string", *j);
			}

			cout << "</string_list></attr>" << endl;
		}
		else if (attr == NULL)
		{
			cout << "<!-- skipping NULL attribute " << name << " -->" << endl;
		}
		else
			phc_warning ("Don't know how to deal with attribute '%s' of type '%s'", name.c_str(), demangle(attr, false));	
	}

};

#include "AST_visitor.h"
class AST_CLPA_unparser : public CLPA_unparser
<
	AST::PHP_script,
	AST::Node,
	AST::Literal,
	AST::Identifier,
	AST::Visitor
>
{

};

#include "HIR_visitor.h"
class HIR_CLPA_unparser : public CLPA_unparser
<
	HIR::PHP_script,
	HIR::Node,
	HIR::Literal,
	HIR::Identifier,
	HIR::Visitor
>
{
};

#include "MIR_visitor.h"
class MIR_CLPA_unparser : public CLPA_unparser
<
	MIR::PHP_script,
	MIR::Node,
	MIR::Literal,
	MIR::Identifier,
	MIR::Visitor
>
{
};

#endif // PHC_CLPA_UNPARSER
