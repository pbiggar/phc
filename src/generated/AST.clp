import "src/analyse/base.clp".

session ast (PROG:string).

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
type t_Foreign.
type t_Branch.
type t_Goto.
type t_Label.
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
type t_CLASS_NAME ::= cLASS_NAME_id { id }.
type t_INTERFACE_NAME ::= iNTERFACE_NAME_id { id }.
type t_METHOD_NAME ::= mETHOD_NAME_id { id }.
type t_VARIABLE_NAME ::= vARIABLE_NAME_id { id }.
type t_DIRECTIVE_NAME ::= dIRECTIVE_NAME_id { id }.
type t_LABEL_NAME ::= lABEL_NAME_id { id }.
type t_INT ::= iNT_id { id }.
type t_REAL ::= rEAL_id { id }.
type t_STRING ::= sTRING_id { id }.
type t_BOOL ::= bOOL_id { id }.
type t_NIL ::= nIL_id { id }.
type t_OP ::= oP_id { id }.
type t_CAST ::= cAST_id { id }.
type t_CONSTANT_NAME ::= cONSTANT_NAME_id { id }.


% Conjunctive types
type t_PHP_script ::= pHP_script_id { id }.
type t_Class_def ::= class_def_id { id }.
type t_Class_mod ::= class_mod_id { id }.
type t_Interface_def ::= interface_def_id { id }.
type t_Method ::= method_id { id }.
type t_Signature ::= signature_id { id }.
type t_Method_mod ::= method_mod_id { id }.
type t_Formal_parameter ::= formal_parameter_id { id }.
type t_Type ::= type_id { id }.
type t_Attribute ::= attribute_id { id }.
type t_Attr_mod ::= attr_mod_id { id }.
type t_Name_with_default ::= name_with_default_id { id }.
type t_If ::= if_id { id }.
type t_While ::= while_id { id }.
type t_Do ::= do_id { id }.
type t_For ::= for_id { id }.
type t_Foreach ::= foreach_id { id }.
type t_Switch ::= switch_id { id }.
type t_Switch_case ::= switch_case_id { id }.
type t_Break ::= break_id { id }.
type t_Continue ::= continue_id { id }.
type t_Return ::= return_id { id }.
type t_Static_declaration ::= static_declaration_id { id }.
type t_Global ::= global_id { id }.
type t_Declare ::= declare_id { id }.
type t_Directive ::= directive_id { id }.
type t_Try ::= try_id { id }.
type t_Catch ::= catch_id { id }.
type t_Throw ::= throw_id { id }.
type t_Eval_expr ::= eval_expr_id { id }.
type t_Nop ::= nop_id { id }.
type t_Foreign ::= foreign_id { id }.
type t_Branch ::= branch_id { id }.
type t_Goto ::= goto_id { id }.
type t_Label ::= label_id { id }.
type t_Assignment ::= assignment_id { id }.
type t_Op_assignment ::= op_assignment_id { id }.
type t_List_assignment ::= list_assignment_id { id }.
type t_Nested_list_elements ::= nested_list_elements_id { id }.
type t_Cast ::= cast_id { id }.
type t_Unary_op ::= unary_op_id { id }.
type t_Bin_op ::= bin_op_id { id }.
type t_Conditional_expr ::= conditional_expr_id { id }.
type t_Ignore_errors ::= ignore_errors_id { id }.
type t_Constant ::= constant_id { id }.
type t_Instanceof ::= instanceof_id { id }.
type t_Variable ::= variable_id { id }.
type t_Reflection ::= reflection_id { id }.
type t_Pre_op ::= pre_op_id { id }.
type t_Post_op ::= post_op_id { id }.
type t_Array ::= array_id { id }.
type t_Array_elem ::= array_elem_id { id }.
type t_Method_invocation ::= method_invocation_id { id }.
type t_Actual_parameter ::= actual_parameter_id { id }.
type t_New ::= new_id { id }.


% Disjunctive types
type t_Source_rep ::= 
		  source_rep_INTERFACE_NAME { t_INTERFACE_NAME } 
		| source_rep_CLASS_NAME { t_CLASS_NAME } 
		| source_rep_METHOD_NAME { t_METHOD_NAME } 
		| source_rep_VARIABLE_NAME { t_VARIABLE_NAME } 
		| source_rep_CAST { t_CAST } 
		| source_rep_OP { t_OP } 
		| source_rep_CONSTANT_NAME { t_CONSTANT_NAME } 
		| source_rep_LABEL_NAME { t_LABEL_NAME } 
		| source_rep_DIRECTIVE_NAME { t_DIRECTIVE_NAME } 
		| source_rep_INT { t_INT } 
		| source_rep_REAL { t_REAL } 
		| source_rep_STRING { t_STRING } 
		| source_rep_BOOL { t_BOOL } 
		| source_rep_NIL { t_NIL } 
		.
type t_Identifier ::= 
		  identifier_INTERFACE_NAME { t_INTERFACE_NAME } 
		| identifier_CLASS_NAME { t_CLASS_NAME } 
		| identifier_METHOD_NAME { t_METHOD_NAME } 
		| identifier_VARIABLE_NAME { t_VARIABLE_NAME } 
		| identifier_CAST { t_CAST } 
		| identifier_OP { t_OP } 
		| identifier_CONSTANT_NAME { t_CONSTANT_NAME } 
		| identifier_LABEL_NAME { t_LABEL_NAME } 
		| identifier_DIRECTIVE_NAME { t_DIRECTIVE_NAME } 
		.
type t_Commented_node ::= 
		  commented_node_Method { t_Method } 
		| commented_node_Attribute { t_Attribute } 
		| commented_node_Class_def { t_Class_def } 
		| commented_node_Interface_def { t_Interface_def } 
		| commented_node_Return { t_Return } 
		| commented_node_Static_declaration { t_Static_declaration } 
		| commented_node_Global { t_Global } 
		| commented_node_Try { t_Try } 
		| commented_node_Throw { t_Throw } 
		| commented_node_Eval_expr { t_Eval_expr } 
		| commented_node_If { t_If } 
		| commented_node_While { t_While } 
		| commented_node_Do { t_Do } 
		| commented_node_For { t_For } 
		| commented_node_Foreach { t_Foreach } 
		| commented_node_Switch { t_Switch } 
		| commented_node_Break { t_Break } 
		| commented_node_Continue { t_Continue } 
		| commented_node_Declare { t_Declare } 
		| commented_node_Nop { t_Nop } 
		| commented_node_Label { t_Label } 
		| commented_node_Goto { t_Goto } 
		| commented_node_Branch { t_Branch } 
		| commented_node_Foreign { t_Foreign } 
		| commented_node_Switch_case { t_Switch_case } 
		| commented_node_Catch { t_Catch } 
		.
type t_Class_name ::= 
		  class_name_CLASS_NAME { t_CLASS_NAME } 
		| class_name_Reflection { t_Reflection } 
		.
type t_Method_name ::= 
		  method_name_METHOD_NAME { t_METHOD_NAME } 
		| method_name_Reflection { t_Reflection } 
		.
type t_Target ::= 
		  target_Assignment { t_Assignment } 
		| target_Cast { t_Cast } 
		| target_Unary_op { t_Unary_op } 
		| target_Bin_op { t_Bin_op } 
		| target_Constant { t_Constant } 
		| target_Instanceof { t_Instanceof } 
		| target_Variable { t_Variable } 
		| target_Pre_op { t_Pre_op } 
		| target_Method_invocation { t_Method_invocation } 
		| target_New { t_New } 
		| target_INT { t_INT } 
		| target_REAL { t_REAL } 
		| target_STRING { t_STRING } 
		| target_BOOL { t_BOOL } 
		| target_NIL { t_NIL } 
		| target_Op_assignment { t_Op_assignment } 
		| target_List_assignment { t_List_assignment } 
		| target_Post_op { t_Post_op } 
		| target_Array { t_Array } 
		| target_Conditional_expr { t_Conditional_expr } 
		| target_Ignore_errors { t_Ignore_errors } 
		| target_Foreign { t_Foreign } 
		| target_CLASS_NAME { t_CLASS_NAME } 
		.
type t_Variable_name ::= 
		  variable_name_VARIABLE_NAME { t_VARIABLE_NAME } 
		| variable_name_Reflection { t_Reflection } 
		.
type t_List_element ::= 
		  list_element_Variable { t_Variable } 
		| list_element_Nested_list_elements { t_Nested_list_elements } 
		.
type t_Literal ::= 
		  literal_INT { t_INT } 
		| literal_REAL { t_REAL } 
		| literal_STRING { t_STRING } 
		| literal_BOOL { t_BOOL } 
		| literal_NIL { t_NIL } 
		.
type t_Expr ::= 
		  expr_Assignment { t_Assignment } 
		| expr_Cast { t_Cast } 
		| expr_Unary_op { t_Unary_op } 
		| expr_Bin_op { t_Bin_op } 
		| expr_Constant { t_Constant } 
		| expr_Instanceof { t_Instanceof } 
		| expr_Variable { t_Variable } 
		| expr_Pre_op { t_Pre_op } 
		| expr_Method_invocation { t_Method_invocation } 
		| expr_New { t_New } 
		| expr_INT { t_INT } 
		| expr_REAL { t_REAL } 
		| expr_STRING { t_STRING } 
		| expr_BOOL { t_BOOL } 
		| expr_NIL { t_NIL } 
		| expr_Op_assignment { t_Op_assignment } 
		| expr_List_assignment { t_List_assignment } 
		| expr_Post_op { t_Post_op } 
		| expr_Array { t_Array } 
		| expr_Conditional_expr { t_Conditional_expr } 
		| expr_Ignore_errors { t_Ignore_errors } 
		| expr_Foreign { t_Foreign } 
		.
type t_Member ::= 
		  member_Method { t_Method } 
		| member_Attribute { t_Attribute } 
		.
type t_Statement ::= 
		  statement_Class_def { t_Class_def } 
		| statement_Interface_def { t_Interface_def } 
		| statement_Method { t_Method } 
		| statement_Return { t_Return } 
		| statement_Static_declaration { t_Static_declaration } 
		| statement_Global { t_Global } 
		| statement_Try { t_Try } 
		| statement_Throw { t_Throw } 
		| statement_Eval_expr { t_Eval_expr } 
		| statement_If { t_If } 
		| statement_While { t_While } 
		| statement_Do { t_Do } 
		| statement_For { t_For } 
		| statement_Foreach { t_Foreach } 
		| statement_Switch { t_Switch } 
		| statement_Break { t_Break } 
		| statement_Continue { t_Continue } 
		| statement_Declare { t_Declare } 
		| statement_Nop { t_Nop } 
		| statement_Label { t_Label } 
		| statement_Goto { t_Goto } 
		| statement_Branch { t_Branch } 
		| statement_Foreign { t_Foreign } 
		.
type t_Node ::= 
		  node_PHP_script { t_PHP_script } 
		| node_Class_mod { t_Class_mod } 
		| node_Signature { t_Signature } 
		| node_Method_mod { t_Method_mod } 
		| node_Formal_parameter { t_Formal_parameter } 
		| node_Type { t_Type } 
		| node_Attr_mod { t_Attr_mod } 
		| node_Name_with_default { t_Name_with_default } 
		| node_Directive { t_Directive } 
		| node_Variable { t_Variable } 
		| node_Nested_list_elements { t_Nested_list_elements } 
		| node_VARIABLE_NAME { t_VARIABLE_NAME } 
		| node_Reflection { t_Reflection } 
		| node_Assignment { t_Assignment } 
		| node_Cast { t_Cast } 
		| node_Unary_op { t_Unary_op } 
		| node_Bin_op { t_Bin_op } 
		| node_Constant { t_Constant } 
		| node_Instanceof { t_Instanceof } 
		| node_Pre_op { t_Pre_op } 
		| node_Method_invocation { t_Method_invocation } 
		| node_New { t_New } 
		| node_INT { t_INT } 
		| node_REAL { t_REAL } 
		| node_STRING { t_STRING } 
		| node_BOOL { t_BOOL } 
		| node_NIL { t_NIL } 
		| node_Op_assignment { t_Op_assignment } 
		| node_List_assignment { t_List_assignment } 
		| node_Post_op { t_Post_op } 
		| node_Array { t_Array } 
		| node_Conditional_expr { t_Conditional_expr } 
		| node_Ignore_errors { t_Ignore_errors } 
		| node_Foreign { t_Foreign } 
		| node_CLASS_NAME { t_CLASS_NAME } 
		| node_Array_elem { t_Array_elem } 
		| node_METHOD_NAME { t_METHOD_NAME } 
		| node_Actual_parameter { t_Actual_parameter } 
		| node_Method { t_Method } 
		| node_Attribute { t_Attribute } 
		| node_Class_def { t_Class_def } 
		| node_Interface_def { t_Interface_def } 
		| node_Return { t_Return } 
		| node_Static_declaration { t_Static_declaration } 
		| node_Global { t_Global } 
		| node_Try { t_Try } 
		| node_Throw { t_Throw } 
		| node_Eval_expr { t_Eval_expr } 
		| node_If { t_If } 
		| node_While { t_While } 
		| node_Do { t_Do } 
		| node_For { t_For } 
		| node_Foreach { t_Foreach } 
		| node_Switch { t_Switch } 
		| node_Break { t_Break } 
		| node_Continue { t_Continue } 
		| node_Declare { t_Declare } 
		| node_Nop { t_Nop } 
		| node_Label { t_Label } 
		| node_Goto { t_Goto } 
		| node_Branch { t_Branch } 
		| node_Switch_case { t_Switch_case } 
		| node_Catch { t_Catch } 
		| node_INTERFACE_NAME { t_INTERFACE_NAME } 
		| node_CAST { t_CAST } 
		| node_OP { t_OP } 
		| node_CONSTANT_NAME { t_CONSTANT_NAME } 
		| node_LABEL_NAME { t_LABEL_NAME } 
		| node_DIRECTIVE_NAME { t_DIRECTIVE_NAME } 
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
predicate p_type (ID:t_Type, CLASS_NAME:maybe[t_CLASS_NAME]).
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
predicate foreign (ID:t_Foreign).
predicate branch (ID:t_Branch, EXPR:t_Expr, IFTRUE:t_LABEL_NAME, IFFALSE:t_LABEL_NAME).
predicate goto (ID:t_Goto, LABEL_NAME:t_LABEL_NAME).
predicate label (ID:t_Label, LABEL_NAME:t_LABEL_NAME).
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

