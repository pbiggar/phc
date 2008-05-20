session ast (PROG:string).

% Type not supplied by Saturn
type null.
type id = int.

% Forward declarations for conjunctive types
type t_PHP_script.
type t_Class_def.
type t_Class_mod.
type t_Interface_def.
type t_Method.
type t_Signature.
type t_Method_mod.
type t_Formal_parameter.
type t_Type.
type t_Attribute.
type t_Attr_mod.
type t_Name_with_default.
type t_If.
type t_While.
type t_Do.
type t_For.
type t_Foreach.
type t_Switch.
type t_Switch_case.
type t_Break.
type t_Continue.
type t_Return.
type t_Static_declaration.
type t_Global.
type t_Declare.
type t_Directive.
type t_Try.
type t_Catch.
type t_Throw.
type t_Eval_expr.
type t_Nop.
type t_Branch.
type t_Goto.
type t_Label.
type t_Foreach_reset.
type t_Foreach_next.
type t_Foreach_end.
type t_Foreach_has_key.
type t_Foreach_get_key.
type t_Foreach_get_val.
type t_Assignment.
type t_Op_assignment.
type t_List_assignment.
type t_Nested_list_elements.
type t_Cast.
type t_Unary_op.
type t_Bin_op.
type t_Conditional_expr.
type t_Ignore_errors.
type t_Constant.
type t_Instanceof.
type t_Variable.
type t_Reflection.
type t_Pre_op.
type t_Post_op.
type t_Array.
type t_Array_elem.
type t_Method_invocation.
type t_Actual_parameter.
type t_New.


% Forward declarations for disjunctive types
type t_Node.
type t_Statement.
type t_Member.
type t_Expr.
type t_Literal.
type t_List_element.
type t_Variable_name.
type t_Target.
type t_Method_name.
type t_Class_name.
type t_Commented_node.
type t_Identifier.
type t_Source_rep.


% Token declarations
type t_HT_ITERATOR ::= t_HT_ITERATOR_id {id}.
type t_CLASS_NAME ::= t_CLASS_NAME_id {id}.
type t_INTERFACE_NAME ::= t_INTERFACE_NAME_id {id}.
type t_METHOD_NAME ::= t_METHOD_NAME_id {id}.
type t_VARIABLE_NAME ::= t_VARIABLE_NAME_id {id}.
type t_DIRECTIVE_NAME ::= t_DIRECTIVE_NAME_id {id}.
type t_LABEL_NAME ::= t_LABEL_NAME_id {id}.
type t_INT ::= t_INT_id {id}.
type t_REAL ::= t_REAL_id {id}.
type t_STRING ::= t_STRING_id {id}.
type t_BOOL ::= t_BOOL_id {id}.
type t_NIL ::= t_NIL_id {id}.
type t_OP ::= t_OP_id {id}.
type t_CAST ::= t_CAST_id {id}.
type t_CONSTANT_NAME ::= t_CONSTANT_NAME_id {id}.


% Conjunctive types
type t_PHP_script ::= t_PHP_script_id {id}.
type t_Class_def ::= t_Class_def_id {id}.
type t_Class_mod ::= t_Class_mod_id {id}.
type t_Interface_def ::= t_Interface_def_id {id}.
type t_Method ::= t_Method_id {id}.
type t_Signature ::= t_Signature_id {id}.
type t_Method_mod ::= t_Method_mod_id {id}.
type t_Formal_parameter ::= t_Formal_parameter_id {id}.
type t_Type ::= t_Type_id {id}.
type t_Attribute ::= t_Attribute_id {id}.
type t_Attr_mod ::= t_Attr_mod_id {id}.
type t_Name_with_default ::= t_Name_with_default_id {id}.
type t_If ::= t_If_id {id}.
type t_While ::= t_While_id {id}.
type t_Do ::= t_Do_id {id}.
type t_For ::= t_For_id {id}.
type t_Foreach ::= t_Foreach_id {id}.
type t_Switch ::= t_Switch_id {id}.
type t_Switch_case ::= t_Switch_case_id {id}.
type t_Break ::= t_Break_id {id}.
type t_Continue ::= t_Continue_id {id}.
type t_Return ::= t_Return_id {id}.
type t_Static_declaration ::= t_Static_declaration_id {id}.
type t_Global ::= t_Global_id {id}.
type t_Declare ::= t_Declare_id {id}.
type t_Directive ::= t_Directive_id {id}.
type t_Try ::= t_Try_id {id}.
type t_Catch ::= t_Catch_id {id}.
type t_Throw ::= t_Throw_id {id}.
type t_Eval_expr ::= t_Eval_expr_id {id}.
type t_Nop ::= t_Nop_id {id}.
type t_Branch ::= t_Branch_id {id}.
type t_Goto ::= t_Goto_id {id}.
type t_Label ::= t_Label_id {id}.
type t_Foreach_reset ::= t_Foreach_reset_id {id}.
type t_Foreach_next ::= t_Foreach_next_id {id}.
type t_Foreach_end ::= t_Foreach_end_id {id}.
type t_Foreach_has_key ::= t_Foreach_has_key_id {id}.
type t_Foreach_get_key ::= t_Foreach_get_key_id {id}.
type t_Foreach_get_val ::= t_Foreach_get_val_id {id}.
type t_Assignment ::= t_Assignment_id {id}.
type t_Op_assignment ::= t_Op_assignment_id {id}.
type t_List_assignment ::= t_List_assignment_id {id}.
type t_Nested_list_elements ::= t_Nested_list_elements_id {id}.
type t_Cast ::= t_Cast_id {id}.
type t_Unary_op ::= t_Unary_op_id {id}.
type t_Bin_op ::= t_Bin_op_id {id}.
type t_Conditional_expr ::= t_Conditional_expr_id {id}.
type t_Ignore_errors ::= t_Ignore_errors_id {id}.
type t_Constant ::= t_Constant_id {id}.
type t_Instanceof ::= t_Instanceof_id {id}.
type t_Variable ::= t_Variable_id {id}.
type t_Reflection ::= t_Reflection_id {id}.
type t_Pre_op ::= t_Pre_op_id {id}.
type t_Post_op ::= t_Post_op_id {id}.
type t_Array ::= t_Array_id {id}.
type t_Array_elem ::= t_Array_elem_id {id}.
type t_Method_invocation ::= t_Method_invocation_id {id}.
type t_Actual_parameter ::= t_Actual_parameter_id {id}.
type t_New ::= t_New_id {id}.


% Disjunctive types
type t_Source_rep ::= 
		  source_rep_INTERFACE_NAME_id { t_INTERFACE_NAME } 
		| source_rep_CLASS_NAME_id { t_CLASS_NAME } 
		| source_rep_METHOD_NAME_id { t_METHOD_NAME } 
		| source_rep_VARIABLE_NAME_id { t_VARIABLE_NAME } 
		| source_rep_CAST_id { t_CAST } 
		| source_rep_OP_id { t_OP } 
		| source_rep_CONSTANT_NAME_id { t_CONSTANT_NAME } 
		| source_rep_LABEL_NAME_id { t_LABEL_NAME } 
		| source_rep_DIRECTIVE_NAME_id { t_DIRECTIVE_NAME } 
		| source_rep_INT_id { t_INT } 
		| source_rep_REAL_id { t_REAL } 
		| source_rep_STRING_id { t_STRING } 
		| source_rep_BOOL_id { t_BOOL } 
		| source_rep_NIL_id { t_NIL } 
		.
type t_Identifier ::= 
		  identifier_INTERFACE_NAME_id { t_INTERFACE_NAME } 
		| identifier_CLASS_NAME_id { t_CLASS_NAME } 
		| identifier_METHOD_NAME_id { t_METHOD_NAME } 
		| identifier_VARIABLE_NAME_id { t_VARIABLE_NAME } 
		| identifier_CAST_id { t_CAST } 
		| identifier_OP_id { t_OP } 
		| identifier_CONSTANT_NAME_id { t_CONSTANT_NAME } 
		| identifier_LABEL_NAME_id { t_LABEL_NAME } 
		| identifier_DIRECTIVE_NAME_id { t_DIRECTIVE_NAME } 
		.
type t_Commented_node ::= 
		  commented_node_Method_id { t_Method } 
		| commented_node_Attribute_id { t_Attribute } 
		| commented_node_Class_def_id { t_Class_def } 
		| commented_node_Interface_def_id { t_Interface_def } 
		| commented_node_Return_id { t_Return } 
		| commented_node_Static_declaration_id { t_Static_declaration } 
		| commented_node_Global_id { t_Global } 
		| commented_node_Try_id { t_Try } 
		| commented_node_Throw_id { t_Throw } 
		| commented_node_Eval_expr_id { t_Eval_expr } 
		| commented_node_If_id { t_If } 
		| commented_node_While_id { t_While } 
		| commented_node_Do_id { t_Do } 
		| commented_node_For_id { t_For } 
		| commented_node_Foreach_id { t_Foreach } 
		| commented_node_Switch_id { t_Switch } 
		| commented_node_Break_id { t_Break } 
		| commented_node_Continue_id { t_Continue } 
		| commented_node_Declare_id { t_Declare } 
		| commented_node_Nop_id { t_Nop } 
		| commented_node_Label_id { t_Label } 
		| commented_node_Goto_id { t_Goto } 
		| commented_node_Branch_id { t_Branch } 
		| commented_node_Foreach_next_id { t_Foreach_next } 
		| commented_node_Foreach_reset_id { t_Foreach_reset } 
		| commented_node_Foreach_end_id { t_Foreach_end } 
		| commented_node_Switch_case_id { t_Switch_case } 
		| commented_node_Catch_id { t_Catch } 
		.
type t_Class_name ::= 
		  class_name_CLASS_NAME_id { t_CLASS_NAME } 
		| class_name_Reflection_id { t_Reflection } 
		.
type t_Method_name ::= 
		  method_name_METHOD_NAME_id { t_METHOD_NAME } 
		| method_name_Reflection_id { t_Reflection } 
		.
type t_Target ::= 
		  target_Assignment_id { t_Assignment } 
		| target_Cast_id { t_Cast } 
		| target_Unary_op_id { t_Unary_op } 
		| target_Bin_op_id { t_Bin_op } 
		| target_Constant_id { t_Constant } 
		| target_Instanceof_id { t_Instanceof } 
		| target_Variable_id { t_Variable } 
		| target_Pre_op_id { t_Pre_op } 
		| target_Method_invocation_id { t_Method_invocation } 
		| target_New_id { t_New } 
		| target_INT_id { t_INT } 
		| target_REAL_id { t_REAL } 
		| target_STRING_id { t_STRING } 
		| target_BOOL_id { t_BOOL } 
		| target_NIL_id { t_NIL } 
		| target_Op_assignment_id { t_Op_assignment } 
		| target_List_assignment_id { t_List_assignment } 
		| target_Post_op_id { t_Post_op } 
		| target_Array_id { t_Array } 
		| target_Conditional_expr_id { t_Conditional_expr } 
		| target_Ignore_errors_id { t_Ignore_errors } 
		| target_Foreach_has_key_id { t_Foreach_has_key } 
		| target_Foreach_get_key_id { t_Foreach_get_key } 
		| target_Foreach_get_val_id { t_Foreach_get_val } 
		| target_CLASS_NAME_id { t_CLASS_NAME } 
		.
type t_Variable_name ::= 
		  variable_name_VARIABLE_NAME_id { t_VARIABLE_NAME } 
		| variable_name_Reflection_id { t_Reflection } 
		.
type t_List_element ::= 
		  list_element_Variable_id { t_Variable } 
		| list_element_Nested_list_elements_id { t_Nested_list_elements } 
		.
type t_Literal ::= 
		  literal_INT_id { t_INT } 
		| literal_REAL_id { t_REAL } 
		| literal_STRING_id { t_STRING } 
		| literal_BOOL_id { t_BOOL } 
		| literal_NIL_id { t_NIL } 
		.
type t_Expr ::= 
		  expr_Assignment_id { t_Assignment } 
		| expr_Cast_id { t_Cast } 
		| expr_Unary_op_id { t_Unary_op } 
		| expr_Bin_op_id { t_Bin_op } 
		| expr_Constant_id { t_Constant } 
		| expr_Instanceof_id { t_Instanceof } 
		| expr_Variable_id { t_Variable } 
		| expr_Pre_op_id { t_Pre_op } 
		| expr_Method_invocation_id { t_Method_invocation } 
		| expr_New_id { t_New } 
		| expr_INT_id { t_INT } 
		| expr_REAL_id { t_REAL } 
		| expr_STRING_id { t_STRING } 
		| expr_BOOL_id { t_BOOL } 
		| expr_NIL_id { t_NIL } 
		| expr_Op_assignment_id { t_Op_assignment } 
		| expr_List_assignment_id { t_List_assignment } 
		| expr_Post_op_id { t_Post_op } 
		| expr_Array_id { t_Array } 
		| expr_Conditional_expr_id { t_Conditional_expr } 
		| expr_Ignore_errors_id { t_Ignore_errors } 
		| expr_Foreach_has_key_id { t_Foreach_has_key } 
		| expr_Foreach_get_key_id { t_Foreach_get_key } 
		| expr_Foreach_get_val_id { t_Foreach_get_val } 
		.
type t_Member ::= 
		  member_Method_id { t_Method } 
		| member_Attribute_id { t_Attribute } 
		.
type t_Statement ::= 
		  statement_Class_def_id { t_Class_def } 
		| statement_Interface_def_id { t_Interface_def } 
		| statement_Method_id { t_Method } 
		| statement_Return_id { t_Return } 
		| statement_Static_declaration_id { t_Static_declaration } 
		| statement_Global_id { t_Global } 
		| statement_Try_id { t_Try } 
		| statement_Throw_id { t_Throw } 
		| statement_Eval_expr_id { t_Eval_expr } 
		| statement_If_id { t_If } 
		| statement_While_id { t_While } 
		| statement_Do_id { t_Do } 
		| statement_For_id { t_For } 
		| statement_Foreach_id { t_Foreach } 
		| statement_Switch_id { t_Switch } 
		| statement_Break_id { t_Break } 
		| statement_Continue_id { t_Continue } 
		| statement_Declare_id { t_Declare } 
		| statement_Nop_id { t_Nop } 
		| statement_Label_id { t_Label } 
		| statement_Goto_id { t_Goto } 
		| statement_Branch_id { t_Branch } 
		| statement_Foreach_next_id { t_Foreach_next } 
		| statement_Foreach_reset_id { t_Foreach_reset } 
		| statement_Foreach_end_id { t_Foreach_end } 
		.
type t_Node ::= 
		  node_PHP_script_id { t_PHP_script } 
		| node_Class_mod_id { t_Class_mod } 
		| node_Signature_id { t_Signature } 
		| node_Method_mod_id { t_Method_mod } 
		| node_Formal_parameter_id { t_Formal_parameter } 
		| node_Type_id { t_Type } 
		| node_Attr_mod_id { t_Attr_mod } 
		| node_Name_with_default_id { t_Name_with_default } 
		| node_Directive_id { t_Directive } 
		| node_Variable_id { t_Variable } 
		| node_Nested_list_elements_id { t_Nested_list_elements } 
		| node_VARIABLE_NAME_id { t_VARIABLE_NAME } 
		| node_Reflection_id { t_Reflection } 
		| node_Assignment_id { t_Assignment } 
		| node_Cast_id { t_Cast } 
		| node_Unary_op_id { t_Unary_op } 
		| node_Bin_op_id { t_Bin_op } 
		| node_Constant_id { t_Constant } 
		| node_Instanceof_id { t_Instanceof } 
		| node_Pre_op_id { t_Pre_op } 
		| node_Method_invocation_id { t_Method_invocation } 
		| node_New_id { t_New } 
		| node_INT_id { t_INT } 
		| node_REAL_id { t_REAL } 
		| node_STRING_id { t_STRING } 
		| node_BOOL_id { t_BOOL } 
		| node_NIL_id { t_NIL } 
		| node_Op_assignment_id { t_Op_assignment } 
		| node_List_assignment_id { t_List_assignment } 
		| node_Post_op_id { t_Post_op } 
		| node_Array_id { t_Array } 
		| node_Conditional_expr_id { t_Conditional_expr } 
		| node_Ignore_errors_id { t_Ignore_errors } 
		| node_Foreach_has_key_id { t_Foreach_has_key } 
		| node_Foreach_get_key_id { t_Foreach_get_key } 
		| node_Foreach_get_val_id { t_Foreach_get_val } 
		| node_CLASS_NAME_id { t_CLASS_NAME } 
		| node_Array_elem_id { t_Array_elem } 
		| node_METHOD_NAME_id { t_METHOD_NAME } 
		| node_Actual_parameter_id { t_Actual_parameter } 
		| node_Method_id { t_Method } 
		| node_Attribute_id { t_Attribute } 
		| node_Class_def_id { t_Class_def } 
		| node_Interface_def_id { t_Interface_def } 
		| node_Return_id { t_Return } 
		| node_Static_declaration_id { t_Static_declaration } 
		| node_Global_id { t_Global } 
		| node_Try_id { t_Try } 
		| node_Throw_id { t_Throw } 
		| node_Eval_expr_id { t_Eval_expr } 
		| node_If_id { t_If } 
		| node_While_id { t_While } 
		| node_Do_id { t_Do } 
		| node_For_id { t_For } 
		| node_Foreach_id { t_Foreach } 
		| node_Switch_id { t_Switch } 
		| node_Break_id { t_Break } 
		| node_Continue_id { t_Continue } 
		| node_Declare_id { t_Declare } 
		| node_Nop_id { t_Nop } 
		| node_Label_id { t_Label } 
		| node_Goto_id { t_Goto } 
		| node_Branch_id { t_Branch } 
		| node_Foreach_next_id { t_Foreach_next } 
		| node_Foreach_reset_id { t_Foreach_reset } 
		| node_Foreach_end_id { t_Foreach_end } 
		| node_Switch_case_id { t_Switch_case } 
		| node_Catch_id { t_Catch } 
		| node_INTERFACE_NAME_id { t_INTERFACE_NAME } 
		| node_CAST_id { t_CAST } 
		| node_OP_id { t_OP } 
		| node_CONSTANT_NAME_id { t_CONSTANT_NAME } 
		| node_LABEL_NAME_id { t_LABEL_NAME } 
		| node_DIRECTIVE_NAME_id { t_DIRECTIVE_NAME } 
		| node_HT_ITERATOR_id { t_HT_ITERATOR } 
		.


% Predicates
predicate pHP_script (ID:t_PHP_script, STATEMENTS:list[t_Statement]).
predicate class_def (ID:t_Class_def, CLASS_MOD:t_Class_mod, CLASS_NAME:t_CLASS_NAME, EXTENDS:maybe[t_CLASS_NAME], IMPLEMENTS:list[t_INTERFACE_NAME], MEMBERS:list[t_Member]).
predicate class_mod (ID:t_Class_mod, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate interface_def (ID:t_Interface_def, INTERFACE_NAME:t_INTERFACE_NAME, EXTENDS:list[t_INTERFACE_NAME], MEMBERS:list[t_Member]).
predicate method (ID:t_Method, SIGNATURE:t_Signature, STATEMENTS:maybe[list[t_Statement]]).
predicate signature (ID:t_Signature, METHOD_MOD:t_Method_mod, IS_REF:bool, METHOD_NAME:t_METHOD_NAME, FORMAL_PARAMETERS:list[t_Formal_parameter]).
predicate method_mod (ID:t_Method_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate formal_parameter (ID:t_Formal_parameter, TYPE:t_Type, IS_REF:bool, VAR:t_Name_with_default).
predicate type (ID:t_Type, CLASS_NAME:maybe[t_CLASS_NAME]).
predicate attribute (ID:t_Attribute, ATTR_MOD:t_Attr_mod, VARS:list[t_Name_with_default]).
predicate attr_mod (ID:t_Attr_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_CONST:bool).
predicate name_with_default (ID:t_Name_with_default, VARIABLE_NAME:t_VARIABLE_NAME, EXPR:maybe[t_Expr]).
predicate if (ID:t_If, EXPR:t_Expr, IFTRUE:list[t_Statement], IFFALSE:list[t_Statement]).
predicate while (ID:t_While, EXPR:t_Expr, STATEMENTS:list[t_Statement]).
predicate do (ID:t_Do, STATEMENTS:list[t_Statement], EXPR:t_Expr).
predicate for (ID:t_For, INIT:maybe[t_Expr], COND:maybe[t_Expr], INCR:maybe[t_Expr], STATEMENTS:list[t_Statement]).
predicate foreach (ID:t_Foreach, EXPR:t_Expr, KEY:maybe[t_Variable], IS_REF:bool, VAL:t_Variable, STATEMENTS:list[t_Statement]).
predicate switch (ID:t_Switch, EXPR:t_Expr, SWITCH_CASES:list[t_Switch_case]).
predicate switch_case (ID:t_Switch_case, EXPR:maybe[t_Expr], STATEMENTS:list[t_Statement]).
predicate break (ID:t_Break, EXPR:maybe[t_Expr]).
predicate continue (ID:t_Continue, EXPR:maybe[t_Expr]).
predicate return (ID:t_Return, EXPR:maybe[t_Expr]).
predicate static_declaration (ID:t_Static_declaration, VARS:list[t_Name_with_default]).
predicate global (ID:t_Global, VARIABLE_NAMES:list[t_Variable_name]).
predicate declare (ID:t_Declare, DIRECTIVES:list[t_Directive], STATEMENTS:list[t_Statement]).
predicate directive (ID:t_Directive, DIRECTIVE_NAME:t_DIRECTIVE_NAME, EXPR:t_Expr).
predicate try (ID:t_Try, STATEMENTS:list[t_Statement], CATCHES:list[t_Catch]).
predicate catch (ID:t_Catch, CLASS_NAME:t_CLASS_NAME, VARIABLE_NAME:t_VARIABLE_NAME, STATEMENTS:list[t_Statement]).
predicate throw (ID:t_Throw, EXPR:t_Expr).
predicate eval_expr (ID:t_Eval_expr, EXPR:t_Expr).
predicate nop (ID:t_Nop).
predicate branch (ID:t_Branch, EXPR:t_Expr, IFTRUE:t_LABEL_NAME, IFFALSE:t_LABEL_NAME).
predicate goto (ID:t_Goto, LABEL_NAME:t_LABEL_NAME).
predicate label (ID:t_Label, LABEL_NAME:t_LABEL_NAME).
predicate foreach_reset (ID:t_Foreach_reset, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_next (ID:t_Foreach_next, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_end (ID:t_Foreach_end, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_has_key (ID:t_Foreach_has_key, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_get_key (ID:t_Foreach_get_key, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_get_val (ID:t_Foreach_get_val, ARRAY:t_VARIABLE_NAME, KEY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate assignment (ID:t_Assignment, VARIABLE:t_Variable, IS_REF:bool, EXPR:t_Expr).
predicate op_assignment (ID:t_Op_assignment, VARIABLE:t_Variable, OP:t_OP, EXPR:t_Expr).
predicate list_assignment (ID:t_List_assignment, LIST_ELEMENTS:list[maybe[t_List_element]], EXPR:t_Expr).
predicate nested_list_elements (ID:t_Nested_list_elements, LIST_ELEMENTS:list[maybe[t_List_element]]).
predicate cast (ID:t_Cast, CAST:t_CAST, EXPR:t_Expr).
predicate unary_op (ID:t_Unary_op, OP:t_OP, EXPR:t_Expr).
predicate bin_op (ID:t_Bin_op, LEFT:t_Expr, OP:t_OP, RIGHT:t_Expr).
predicate conditional_expr (ID:t_Conditional_expr, COND:t_Expr, IFTRUE:t_Expr, IFFALSE:t_Expr).
predicate ignore_errors (ID:t_Ignore_errors, EXPR:t_Expr).
predicate constant (ID:t_Constant, CLASS_NAME:maybe[t_CLASS_NAME], CONSTANT_NAME:t_CONSTANT_NAME).
predicate instanceof (ID:t_Instanceof, EXPR:t_Expr, CLASS_NAME:t_Class_name).
predicate variable (ID:t_Variable, TARGET:maybe[t_Target], VARIABLE_NAME:t_Variable_name, ARRAY_INDICES:list[maybe[t_Expr]]).
predicate reflection (ID:t_Reflection, EXPR:t_Expr).
predicate pre_op (ID:t_Pre_op, OP:t_OP, VARIABLE:t_Variable).
predicate post_op (ID:t_Post_op, VARIABLE:t_Variable, OP:t_OP).
predicate array (ID:t_Array, ARRAY_ELEMS:list[t_Array_elem]).
predicate array_elem (ID:t_Array_elem, KEY:maybe[t_Expr], IS_REF:bool, VAL:t_Expr).
predicate method_invocation (ID:t_Method_invocation, TARGET:maybe[t_Target], METHOD_NAME:t_Method_name, ACTUAL_PARAMETERS:list[t_Actual_parameter]).
predicate actual_parameter (ID:t_Actual_parameter, IS_REF:bool, EXPR:t_Expr).
predicate new (ID:t_New, CLASS_NAME:t_Class_name, ACTUAL_PARAMETERS:list[t_Actual_parameter]).

predicate hT_ITERATOR (ID:t_HT_ITERATOR, VALUE:int).
predicate cLASS_NAME (ID:t_CLASS_NAME, VALUE:string).
predicate iNTERFACE_NAME (ID:t_INTERFACE_NAME, VALUE:string).
predicate mETHOD_NAME (ID:t_METHOD_NAME, VALUE:string).
predicate vARIABLE_NAME (ID:t_VARIABLE_NAME, VALUE:string).
predicate dIRECTIVE_NAME (ID:t_DIRECTIVE_NAME, VALUE:string).
predicate lABEL_NAME (ID:t_LABEL_NAME, VALUE:string).
predicate iNT (ID:t_INT, VALUE:int).
predicate rEAL (ID:t_REAL, VALUE:float).
predicate sTRING (ID:t_STRING, VALUE:string).
predicate bOOL (ID:t_BOOL, VALUE:bool).
predicate nIL (ID:t_NIL, VALUE:null).
predicate oP (ID:t_OP, VALUE:string).
predicate cAST (ID:t_CAST, VALUE:string).
predicate cONSTANT_NAME (ID:t_CONSTANT_NAME, VALUE:string).

