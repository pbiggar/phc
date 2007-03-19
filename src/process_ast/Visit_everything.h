/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Visit_everything redefines the pre_children methods of AST_visitor to
 * insert calls to "visit_marker" for each marker encountered, and to call
 * visit_null on NULLs. "visit_marker" takes two arguments, the name and the
 * value of the marker; "visit_null" takes a a single argument, which will be
 * set to the type of the argument. 
 *
 * This is useful for unparsers.
 */

#ifndef PHC_VISIT_EVERYTHING
#define PHC_VISIT_EVERYTHING

#include "AST_visitor.h"

class Visit_everything : public virtual AST_visitor
{
public:
	virtual void visit_marker(char* name, bool value) = 0;
	virtual void visit_null(char* type_id) = 0;

public:
	void children_class_def(AST_class_def* in);
	void children_class_mod(AST_class_mod* in);
	void children_signature(AST_signature* in);
	void children_method(AST_method* in);
	void children_method_mod(AST_method_mod* in);
	void children_formal_parameter(AST_formal_parameter* in);
	void children_type(AST_type* in);
	void children_attribute(AST_attribute* in);
	void children_attr_mod(AST_attr_mod* in);
	void children_for(AST_for* in);
	void children_foreach(AST_foreach* in);
	void children_switch_case(AST_switch_case* in);
	void children_break(AST_break* in);
	void children_continue(AST_continue* in);
	void children_return(AST_return* in);
	void children_static_declaration(AST_static_declaration* in);
	void children_assignment(AST_assignment* in);
	void children_variable(AST_variable* in);
	void children_array_elem(AST_array_elem* in);
	void children_actual_parameter(AST_actual_parameter* in);
	void visit_list_element_list(List<AST_list_element*> in);
	void visit_expr_list(List<AST_expr*> in);

};

#endif // PHC_VISIT_EVERYTHING
