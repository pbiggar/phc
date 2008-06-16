import "src/analyse/base.clp".

session ast ().

% Forward declarations
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
type t_Foreign_expr.
type t_Foreign_statement.
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


type t_Node.
type t_Statement.
type t_Member.
type t_Foreign.
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
type t_INT ::= iNT_id { id }.
type t_REAL ::= rEAL_id { id }.
type t_STRING ::= sTRING_id { id }.
type t_BOOL ::= bOOL_id { id }.
type t_NIL ::= nIL_id { id }.
type t_OP ::= oP_id { id }.
type t_CAST ::= cAST_id { id }.
type t_CONSTANT_NAME ::= cONSTANT_NAME_id { id }.



% Types
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
type t_Foreign_expr ::= foreign_expr_id { id }.
type t_Foreign_statement ::= foreign_statement_id { id }.
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


type t_Source_rep ::= 
		  source_rep_INTERFACE_NAME { t_INTERFACE_NAME } 
		| source_rep_CLASS_NAME { t_CLASS_NAME } 
		| source_rep_METHOD_NAME { t_METHOD_NAME } 
		| source_rep_VARIABLE_NAME { t_VARIABLE_NAME } 
		| source_rep_CAST { t_CAST } 
		| source_rep_OP { t_OP } 
		| source_rep_CONSTANT_NAME { t_CONSTANT_NAME } 
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
		| commented_node_Foreign_statement { t_Foreign_statement } 
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
		| target_Foreign_expr { t_Foreign_expr } 
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
		| expr_Foreign_expr { t_Foreign_expr } 
		.
type t_Foreign ::= 
		  foreign_Foreign_expr { t_Foreign_expr } 
		| foreign_Foreign_statement { t_Foreign_statement } 
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
		| statement_Foreign_statement { t_Foreign_statement } 
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
		| node_Foreign_expr { t_Foreign_expr } 
		| node_Foreign_statement { t_Foreign_statement } 
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
		| node_Switch_case { t_Switch_case } 
		| node_Catch { t_Catch } 
		| node_INTERFACE_NAME { t_INTERFACE_NAME } 
		| node_CAST { t_CAST } 
		| node_OP { t_OP } 
		| node_CONSTANT_NAME { t_CONSTANT_NAME } 
		| node_DIRECTIVE_NAME { t_DIRECTIVE_NAME } 
		.



% Predicates
predicate pHP_script (ID:t_PHP_script, STATEMENTS:list[t_Statement]).
predicate class_def (ID:t_Class_def, CLASS_MOD:t_Class_mod, CLASS_NAME:t_CLASS_NAME, OPT_EXTENDS:maybe[t_CLASS_NAME], IMPLEMENTSS:list[t_INTERFACE_NAME], MEMBERS:list[t_Member]).
predicate class_mod (ID:t_Class_mod, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate interface_def (ID:t_Interface_def, INTERFACE_NAME:t_INTERFACE_NAME, EXTENDSS:list[t_INTERFACE_NAME], MEMBERS:list[t_Member]).
predicate method (ID:t_Method, SIGNATURE:t_Signature, OPT_STATEMENTS:maybe[list[t_Statement]]).
predicate signature (ID:t_Signature, METHOD_MOD:t_Method_mod, IS_REF:bool, METHOD_NAME:t_METHOD_NAME, FORMAL_PARAMETERS:list[t_Formal_parameter]).
predicate method_mod (ID:t_Method_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate formal_parameter (ID:t_Formal_parameter, TYPE:t_Type, IS_REF:bool, VAR:t_Name_with_default).
predicate p_type (ID:t_Type, OPT_CLASS_NAME:maybe[t_CLASS_NAME]).
predicate attribute (ID:t_Attribute, ATTR_MOD:t_Attr_mod, VARSS:list[t_Name_with_default]).
predicate attr_mod (ID:t_Attr_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_CONST:bool).
predicate name_with_default (ID:t_Name_with_default, VARIABLE_NAME:t_VARIABLE_NAME, OPT_EXPR:maybe[t_Expr]).
predicate if (ID:t_If, EXPR:t_Expr, IFTRUES:list[t_Statement], IFFALSES:list[t_Statement]).
predicate while (ID:t_While, EXPR:t_Expr, STATEMENTS:list[t_Statement]).
predicate do (ID:t_Do, STATEMENTS:list[t_Statement], EXPR:t_Expr).
predicate for (ID:t_For, OPT_INIT:maybe[t_Expr], OPT_COND:maybe[t_Expr], OPT_INCR:maybe[t_Expr], STATEMENTS:list[t_Statement]).
predicate foreach (ID:t_Foreach, EXPR:t_Expr, OPT_KEY:maybe[t_Variable], IS_REF:bool, VAL:t_Variable, STATEMENTS:list[t_Statement]).
predicate switch (ID:t_Switch, EXPR:t_Expr, SWITCH_CASES:list[t_Switch_case]).
predicate switch_case (ID:t_Switch_case, OPT_EXPR:maybe[t_Expr], STATEMENTS:list[t_Statement]).
predicate break (ID:t_Break, OPT_EXPR:maybe[t_Expr]).
predicate continue (ID:t_Continue, OPT_EXPR:maybe[t_Expr]).
predicate return (ID:t_Return, OPT_EXPR:maybe[t_Expr]).
predicate static_declaration (ID:t_Static_declaration, VARSS:list[t_Name_with_default]).
predicate global (ID:t_Global, VARIABLE_NAMES:list[t_Variable_name]).
predicate declare (ID:t_Declare, DIRECTIVES:list[t_Directive], STATEMENTS:list[t_Statement]).
predicate directive (ID:t_Directive, DIRECTIVE_NAME:t_DIRECTIVE_NAME, EXPR:t_Expr).
predicate try (ID:t_Try, STATEMENTS:list[t_Statement], CATCHESS:list[t_Catch]).
predicate catch (ID:t_Catch, CLASS_NAME:t_CLASS_NAME, VARIABLE_NAME:t_VARIABLE_NAME, STATEMENTS:list[t_Statement]).
predicate throw (ID:t_Throw, EXPR:t_Expr).
predicate eval_expr (ID:t_Eval_expr, EXPR:t_Expr).
predicate nop (ID:t_Nop).
predicate foreign_expr (ID:t_Foreign_expr).
predicate foreign_statement (ID:t_Foreign_statement).
predicate assignment (ID:t_Assignment, VARIABLE:t_Variable, IS_REF:bool, EXPR:t_Expr).
predicate op_assignment (ID:t_Op_assignment, VARIABLE:t_Variable, OP:t_OP, EXPR:t_Expr).
predicate list_assignment (ID:t_List_assignment, LIST_ELEMENTS:list[maybe[t_List_element]], EXPR:t_Expr).
predicate nested_list_elements (ID:t_Nested_list_elements, LIST_ELEMENTS:list[maybe[t_List_element]]).
predicate cast (ID:t_Cast, CAST:t_CAST, EXPR:t_Expr).
predicate unary_op (ID:t_Unary_op, OP:t_OP, EXPR:t_Expr).
predicate bin_op (ID:t_Bin_op, LEFT:t_Expr, OP:t_OP, RIGHT:t_Expr).
predicate conditional_expr (ID:t_Conditional_expr, COND:t_Expr, IFTRUE:t_Expr, IFFALSE:t_Expr).
predicate ignore_errors (ID:t_Ignore_errors, EXPR:t_Expr).
predicate constant (ID:t_Constant, OPT_CLASS_NAME:maybe[t_CLASS_NAME], CONSTANT_NAME:t_CONSTANT_NAME).
predicate instanceof (ID:t_Instanceof, EXPR:t_Expr, CLASS_NAME:t_Class_name).
predicate variable (ID:t_Variable, OPT_TARGET:maybe[t_Target], VARIABLE_NAME:t_Variable_name, ARRAY_INDICESS:list[maybe[t_Expr]]).
predicate reflection (ID:t_Reflection, EXPR:t_Expr).
predicate pre_op (ID:t_Pre_op, OP:t_OP, VARIABLE:t_Variable).
predicate post_op (ID:t_Post_op, VARIABLE:t_Variable, OP:t_OP).
predicate array (ID:t_Array, ARRAY_ELEMS:list[t_Array_elem]).
predicate array_elem (ID:t_Array_elem, OPT_KEY:maybe[t_Expr], IS_REF:bool, VAL:t_Expr).
predicate method_invocation (ID:t_Method_invocation, OPT_TARGET:maybe[t_Target], METHOD_NAME:t_Method_name, ACTUAL_PARAMETERS:list[t_Actual_parameter]).
predicate actual_parameter (ID:t_Actual_parameter, IS_REF:bool, EXPR:t_Expr).
predicate new (ID:t_New, CLASS_NAME:t_Class_name, ACTUAL_PARAMETERS:list[t_Actual_parameter]).


predicate cLASS_NAME (ID:t_CLASS_NAME, VALUE:string).
predicate iNTERFACE_NAME (ID:t_INTERFACE_NAME, VALUE:string).
predicate mETHOD_NAME (ID:t_METHOD_NAME, VALUE:string).
predicate vARIABLE_NAME (ID:t_VARIABLE_NAME, VALUE:string).
predicate dIRECTIVE_NAME (ID:t_DIRECTIVE_NAME, VALUE:string).
predicate iNT (ID:t_INT, VALUE:int).
predicate rEAL (ID:t_REAL, VALUE:float).
predicate sTRING (ID:t_STRING, VALUE:string).
predicate bOOL (ID:t_BOOL, VALUE:bool).
predicate nIL (ID:t_NIL, VALUE:null).
predicate oP (ID:t_OP, VALUE:string).
predicate cAST (ID:t_CAST, VALUE:string).
predicate cONSTANT_NAME (ID:t_CONSTANT_NAME, VALUE:string).



% Generics

% Type Casts
to_node (ANY, NODE) :- 
	ANY = any{pHP_script_id{ID}},
	NODE = node_PHP_script{pHP_script_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{class_def_id{ID}},
	NODE = node_Class_def{class_def_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{class_mod_id{ID}},
	NODE = node_Class_mod{class_mod_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{interface_def_id{ID}},
	NODE = node_Interface_def{interface_def_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{method_id{ID}},
	NODE = node_Method{method_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{signature_id{ID}},
	NODE = node_Signature{signature_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{method_mod_id{ID}},
	NODE = node_Method_mod{method_mod_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{formal_parameter_id{ID}},
	NODE = node_Formal_parameter{formal_parameter_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{type_id{ID}},
	NODE = node_Type{type_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{attribute_id{ID}},
	NODE = node_Attribute{attribute_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{attr_mod_id{ID}},
	NODE = node_Attr_mod{attr_mod_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{name_with_default_id{ID}},
	NODE = node_Name_with_default{name_with_default_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{if_id{ID}},
	NODE = node_If{if_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{while_id{ID}},
	NODE = node_While{while_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{do_id{ID}},
	NODE = node_Do{do_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{for_id{ID}},
	NODE = node_For{for_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{foreach_id{ID}},
	NODE = node_Foreach{foreach_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{switch_id{ID}},
	NODE = node_Switch{switch_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{switch_case_id{ID}},
	NODE = node_Switch_case{switch_case_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{break_id{ID}},
	NODE = node_Break{break_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{continue_id{ID}},
	NODE = node_Continue{continue_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{return_id{ID}},
	NODE = node_Return{return_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{static_declaration_id{ID}},
	NODE = node_Static_declaration{static_declaration_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{global_id{ID}},
	NODE = node_Global{global_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{declare_id{ID}},
	NODE = node_Declare{declare_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{directive_id{ID}},
	NODE = node_Directive{directive_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{try_id{ID}},
	NODE = node_Try{try_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{catch_id{ID}},
	NODE = node_Catch{catch_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{throw_id{ID}},
	NODE = node_Throw{throw_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{eval_expr_id{ID}},
	NODE = node_Eval_expr{eval_expr_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{nop_id{ID}},
	NODE = node_Nop{nop_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{foreign_expr_id{ID}},
	NODE = node_Foreign_expr{foreign_expr_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{foreign_statement_id{ID}},
	NODE = node_Foreign_statement{foreign_statement_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{assignment_id{ID}},
	NODE = node_Assignment{assignment_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{op_assignment_id{ID}},
	NODE = node_Op_assignment{op_assignment_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{list_assignment_id{ID}},
	NODE = node_List_assignment{list_assignment_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{nested_list_elements_id{ID}},
	NODE = node_Nested_list_elements{nested_list_elements_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{cast_id{ID}},
	NODE = node_Cast{cast_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{unary_op_id{ID}},
	NODE = node_Unary_op{unary_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{bin_op_id{ID}},
	NODE = node_Bin_op{bin_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{conditional_expr_id{ID}},
	NODE = node_Conditional_expr{conditional_expr_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{ignore_errors_id{ID}},
	NODE = node_Ignore_errors{ignore_errors_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{constant_id{ID}},
	NODE = node_Constant{constant_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{instanceof_id{ID}},
	NODE = node_Instanceof{instanceof_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{variable_id{ID}},
	NODE = node_Variable{variable_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{reflection_id{ID}},
	NODE = node_Reflection{reflection_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{pre_op_id{ID}},
	NODE = node_Pre_op{pre_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{post_op_id{ID}},
	NODE = node_Post_op{post_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{array_id{ID}},
	NODE = node_Array{array_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{array_elem_id{ID}},
	NODE = node_Array_elem{array_elem_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{method_invocation_id{ID}},
	NODE = node_Method_invocation{method_invocation_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{actual_parameter_id{ID}},
	NODE = node_Actual_parameter{actual_parameter_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{new_id{ID}},
	NODE = node_New{new_id{ID}}.



to_node (ANY, NODE) :- 
	ANY = any{node_PHP_script{pHP_script_id{ID}}},
	NODE = node_PHP_script{pHP_script_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Class_mod{class_mod_id{ID}}},
	NODE = node_Class_mod{class_mod_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Signature{signature_id{ID}}},
	NODE = node_Signature{signature_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Method_mod{method_mod_id{ID}}},
	NODE = node_Method_mod{method_mod_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Formal_parameter{formal_parameter_id{ID}}},
	NODE = node_Formal_parameter{formal_parameter_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Type{type_id{ID}}},
	NODE = node_Type{type_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Attr_mod{attr_mod_id{ID}}},
	NODE = node_Attr_mod{attr_mod_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Name_with_default{name_with_default_id{ID}}},
	NODE = node_Name_with_default{name_with_default_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Directive{directive_id{ID}}},
	NODE = node_Directive{directive_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Foreign_expr{foreign_expr_id{ID}}},
	NODE = node_Foreign_expr{foreign_expr_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Foreign_statement{foreign_statement_id{ID}}},
	NODE = node_Foreign_statement{foreign_statement_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Variable{variable_id{ID}}},
	NODE = node_Variable{variable_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Nested_list_elements{nested_list_elements_id{ID}}},
	NODE = node_Nested_list_elements{nested_list_elements_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_VARIABLE_NAME{vARIABLE_NAME_id{ID}}},
	NODE = node_VARIABLE_NAME{vARIABLE_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Reflection{reflection_id{ID}}},
	NODE = node_Reflection{reflection_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Assignment{assignment_id{ID}}},
	NODE = node_Assignment{assignment_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Cast{cast_id{ID}}},
	NODE = node_Cast{cast_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Unary_op{unary_op_id{ID}}},
	NODE = node_Unary_op{unary_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Bin_op{bin_op_id{ID}}},
	NODE = node_Bin_op{bin_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Constant{constant_id{ID}}},
	NODE = node_Constant{constant_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Instanceof{instanceof_id{ID}}},
	NODE = node_Instanceof{instanceof_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Pre_op{pre_op_id{ID}}},
	NODE = node_Pre_op{pre_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Method_invocation{method_invocation_id{ID}}},
	NODE = node_Method_invocation{method_invocation_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_New{new_id{ID}}},
	NODE = node_New{new_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_INT{iNT_id{ID}}},
	NODE = node_INT{iNT_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_REAL{rEAL_id{ID}}},
	NODE = node_REAL{rEAL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_STRING{sTRING_id{ID}}},
	NODE = node_STRING{sTRING_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_BOOL{bOOL_id{ID}}},
	NODE = node_BOOL{bOOL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_NIL{nIL_id{ID}}},
	NODE = node_NIL{nIL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Op_assignment{op_assignment_id{ID}}},
	NODE = node_Op_assignment{op_assignment_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_List_assignment{list_assignment_id{ID}}},
	NODE = node_List_assignment{list_assignment_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Post_op{post_op_id{ID}}},
	NODE = node_Post_op{post_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Array{array_id{ID}}},
	NODE = node_Array{array_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Conditional_expr{conditional_expr_id{ID}}},
	NODE = node_Conditional_expr{conditional_expr_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Ignore_errors{ignore_errors_id{ID}}},
	NODE = node_Ignore_errors{ignore_errors_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_CLASS_NAME{cLASS_NAME_id{ID}}},
	NODE = node_CLASS_NAME{cLASS_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Array_elem{array_elem_id{ID}}},
	NODE = node_Array_elem{array_elem_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_METHOD_NAME{mETHOD_NAME_id{ID}}},
	NODE = node_METHOD_NAME{mETHOD_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Actual_parameter{actual_parameter_id{ID}}},
	NODE = node_Actual_parameter{actual_parameter_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Method{method_id{ID}}},
	NODE = node_Method{method_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Attribute{attribute_id{ID}}},
	NODE = node_Attribute{attribute_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Class_def{class_def_id{ID}}},
	NODE = node_Class_def{class_def_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Interface_def{interface_def_id{ID}}},
	NODE = node_Interface_def{interface_def_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Return{return_id{ID}}},
	NODE = node_Return{return_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Static_declaration{static_declaration_id{ID}}},
	NODE = node_Static_declaration{static_declaration_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Global{global_id{ID}}},
	NODE = node_Global{global_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Try{try_id{ID}}},
	NODE = node_Try{try_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Throw{throw_id{ID}}},
	NODE = node_Throw{throw_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Eval_expr{eval_expr_id{ID}}},
	NODE = node_Eval_expr{eval_expr_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_If{if_id{ID}}},
	NODE = node_If{if_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_While{while_id{ID}}},
	NODE = node_While{while_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Do{do_id{ID}}},
	NODE = node_Do{do_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_For{for_id{ID}}},
	NODE = node_For{for_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Foreach{foreach_id{ID}}},
	NODE = node_Foreach{foreach_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Switch{switch_id{ID}}},
	NODE = node_Switch{switch_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Break{break_id{ID}}},
	NODE = node_Break{break_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Continue{continue_id{ID}}},
	NODE = node_Continue{continue_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Declare{declare_id{ID}}},
	NODE = node_Declare{declare_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Nop{nop_id{ID}}},
	NODE = node_Nop{nop_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Switch_case{switch_case_id{ID}}},
	NODE = node_Switch_case{switch_case_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_Catch{catch_id{ID}}},
	NODE = node_Catch{catch_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_INTERFACE_NAME{iNTERFACE_NAME_id{ID}}},
	NODE = node_INTERFACE_NAME{iNTERFACE_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_CAST{cAST_id{ID}}},
	NODE = node_CAST{cAST_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_OP{oP_id{ID}}},
	NODE = node_OP{oP_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_CONSTANT_NAME{cONSTANT_NAME_id{ID}}},
	NODE = node_CONSTANT_NAME{cONSTANT_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{node_DIRECTIVE_NAME{dIRECTIVE_NAME_id{ID}}},
	NODE = node_DIRECTIVE_NAME{dIRECTIVE_NAME_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{statement_Class_def{class_def_id{ID}}},
	NODE = node_Class_def{class_def_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Interface_def{interface_def_id{ID}}},
	NODE = node_Interface_def{interface_def_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Method{method_id{ID}}},
	NODE = node_Method{method_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Return{return_id{ID}}},
	NODE = node_Return{return_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Static_declaration{static_declaration_id{ID}}},
	NODE = node_Static_declaration{static_declaration_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Global{global_id{ID}}},
	NODE = node_Global{global_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Try{try_id{ID}}},
	NODE = node_Try{try_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Throw{throw_id{ID}}},
	NODE = node_Throw{throw_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Eval_expr{eval_expr_id{ID}}},
	NODE = node_Eval_expr{eval_expr_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_If{if_id{ID}}},
	NODE = node_If{if_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_While{while_id{ID}}},
	NODE = node_While{while_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Do{do_id{ID}}},
	NODE = node_Do{do_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_For{for_id{ID}}},
	NODE = node_For{for_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Foreach{foreach_id{ID}}},
	NODE = node_Foreach{foreach_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Switch{switch_id{ID}}},
	NODE = node_Switch{switch_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Break{break_id{ID}}},
	NODE = node_Break{break_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Continue{continue_id{ID}}},
	NODE = node_Continue{continue_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Declare{declare_id{ID}}},
	NODE = node_Declare{declare_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Nop{nop_id{ID}}},
	NODE = node_Nop{nop_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{statement_Foreign_statement{foreign_statement_id{ID}}},
	NODE = node_Foreign_statement{foreign_statement_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{member_Method{method_id{ID}}},
	NODE = node_Method{method_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{member_Attribute{attribute_id{ID}}},
	NODE = node_Attribute{attribute_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{foreign_Foreign_expr{foreign_expr_id{ID}}},
	NODE = node_Foreign_expr{foreign_expr_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{foreign_Foreign_statement{foreign_statement_id{ID}}},
	NODE = node_Foreign_statement{foreign_statement_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{expr_Assignment{assignment_id{ID}}},
	NODE = node_Assignment{assignment_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Cast{cast_id{ID}}},
	NODE = node_Cast{cast_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Unary_op{unary_op_id{ID}}},
	NODE = node_Unary_op{unary_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Bin_op{bin_op_id{ID}}},
	NODE = node_Bin_op{bin_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Constant{constant_id{ID}}},
	NODE = node_Constant{constant_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Instanceof{instanceof_id{ID}}},
	NODE = node_Instanceof{instanceof_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Variable{variable_id{ID}}},
	NODE = node_Variable{variable_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Pre_op{pre_op_id{ID}}},
	NODE = node_Pre_op{pre_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Method_invocation{method_invocation_id{ID}}},
	NODE = node_Method_invocation{method_invocation_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_New{new_id{ID}}},
	NODE = node_New{new_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_INT{iNT_id{ID}}},
	NODE = node_INT{iNT_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_REAL{rEAL_id{ID}}},
	NODE = node_REAL{rEAL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_STRING{sTRING_id{ID}}},
	NODE = node_STRING{sTRING_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_BOOL{bOOL_id{ID}}},
	NODE = node_BOOL{bOOL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_NIL{nIL_id{ID}}},
	NODE = node_NIL{nIL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Op_assignment{op_assignment_id{ID}}},
	NODE = node_Op_assignment{op_assignment_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_List_assignment{list_assignment_id{ID}}},
	NODE = node_List_assignment{list_assignment_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Post_op{post_op_id{ID}}},
	NODE = node_Post_op{post_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Array{array_id{ID}}},
	NODE = node_Array{array_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Conditional_expr{conditional_expr_id{ID}}},
	NODE = node_Conditional_expr{conditional_expr_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Ignore_errors{ignore_errors_id{ID}}},
	NODE = node_Ignore_errors{ignore_errors_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{expr_Foreign_expr{foreign_expr_id{ID}}},
	NODE = node_Foreign_expr{foreign_expr_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{literal_INT{iNT_id{ID}}},
	NODE = node_INT{iNT_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{literal_REAL{rEAL_id{ID}}},
	NODE = node_REAL{rEAL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{literal_STRING{sTRING_id{ID}}},
	NODE = node_STRING{sTRING_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{literal_BOOL{bOOL_id{ID}}},
	NODE = node_BOOL{bOOL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{literal_NIL{nIL_id{ID}}},
	NODE = node_NIL{nIL_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{list_element_Variable{variable_id{ID}}},
	NODE = node_Variable{variable_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{list_element_Nested_list_elements{nested_list_elements_id{ID}}},
	NODE = node_Nested_list_elements{nested_list_elements_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{variable_name_VARIABLE_NAME{vARIABLE_NAME_id{ID}}},
	NODE = node_VARIABLE_NAME{vARIABLE_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{variable_name_Reflection{reflection_id{ID}}},
	NODE = node_Reflection{reflection_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{target_Assignment{assignment_id{ID}}},
	NODE = node_Assignment{assignment_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Cast{cast_id{ID}}},
	NODE = node_Cast{cast_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Unary_op{unary_op_id{ID}}},
	NODE = node_Unary_op{unary_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Bin_op{bin_op_id{ID}}},
	NODE = node_Bin_op{bin_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Constant{constant_id{ID}}},
	NODE = node_Constant{constant_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Instanceof{instanceof_id{ID}}},
	NODE = node_Instanceof{instanceof_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Variable{variable_id{ID}}},
	NODE = node_Variable{variable_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Pre_op{pre_op_id{ID}}},
	NODE = node_Pre_op{pre_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Method_invocation{method_invocation_id{ID}}},
	NODE = node_Method_invocation{method_invocation_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_New{new_id{ID}}},
	NODE = node_New{new_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_INT{iNT_id{ID}}},
	NODE = node_INT{iNT_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_REAL{rEAL_id{ID}}},
	NODE = node_REAL{rEAL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_STRING{sTRING_id{ID}}},
	NODE = node_STRING{sTRING_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_BOOL{bOOL_id{ID}}},
	NODE = node_BOOL{bOOL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_NIL{nIL_id{ID}}},
	NODE = node_NIL{nIL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Op_assignment{op_assignment_id{ID}}},
	NODE = node_Op_assignment{op_assignment_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_List_assignment{list_assignment_id{ID}}},
	NODE = node_List_assignment{list_assignment_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Post_op{post_op_id{ID}}},
	NODE = node_Post_op{post_op_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Array{array_id{ID}}},
	NODE = node_Array{array_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Conditional_expr{conditional_expr_id{ID}}},
	NODE = node_Conditional_expr{conditional_expr_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Ignore_errors{ignore_errors_id{ID}}},
	NODE = node_Ignore_errors{ignore_errors_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_Foreign_expr{foreign_expr_id{ID}}},
	NODE = node_Foreign_expr{foreign_expr_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{target_CLASS_NAME{cLASS_NAME_id{ID}}},
	NODE = node_CLASS_NAME{cLASS_NAME_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{method_name_METHOD_NAME{mETHOD_NAME_id{ID}}},
	NODE = node_METHOD_NAME{mETHOD_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{method_name_Reflection{reflection_id{ID}}},
	NODE = node_Reflection{reflection_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{class_name_CLASS_NAME{cLASS_NAME_id{ID}}},
	NODE = node_CLASS_NAME{cLASS_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{class_name_Reflection{reflection_id{ID}}},
	NODE = node_Reflection{reflection_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{commented_node_Method{method_id{ID}}},
	NODE = node_Method{method_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Attribute{attribute_id{ID}}},
	NODE = node_Attribute{attribute_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Class_def{class_def_id{ID}}},
	NODE = node_Class_def{class_def_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Interface_def{interface_def_id{ID}}},
	NODE = node_Interface_def{interface_def_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Return{return_id{ID}}},
	NODE = node_Return{return_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Static_declaration{static_declaration_id{ID}}},
	NODE = node_Static_declaration{static_declaration_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Global{global_id{ID}}},
	NODE = node_Global{global_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Try{try_id{ID}}},
	NODE = node_Try{try_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Throw{throw_id{ID}}},
	NODE = node_Throw{throw_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Eval_expr{eval_expr_id{ID}}},
	NODE = node_Eval_expr{eval_expr_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_If{if_id{ID}}},
	NODE = node_If{if_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_While{while_id{ID}}},
	NODE = node_While{while_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Do{do_id{ID}}},
	NODE = node_Do{do_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_For{for_id{ID}}},
	NODE = node_For{for_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Foreach{foreach_id{ID}}},
	NODE = node_Foreach{foreach_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Switch{switch_id{ID}}},
	NODE = node_Switch{switch_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Break{break_id{ID}}},
	NODE = node_Break{break_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Continue{continue_id{ID}}},
	NODE = node_Continue{continue_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Declare{declare_id{ID}}},
	NODE = node_Declare{declare_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Nop{nop_id{ID}}},
	NODE = node_Nop{nop_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Foreign_statement{foreign_statement_id{ID}}},
	NODE = node_Foreign_statement{foreign_statement_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Switch_case{switch_case_id{ID}}},
	NODE = node_Switch_case{switch_case_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{commented_node_Catch{catch_id{ID}}},
	NODE = node_Catch{catch_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{identifier_INTERFACE_NAME{iNTERFACE_NAME_id{ID}}},
	NODE = node_INTERFACE_NAME{iNTERFACE_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{identifier_CLASS_NAME{cLASS_NAME_id{ID}}},
	NODE = node_CLASS_NAME{cLASS_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{identifier_METHOD_NAME{mETHOD_NAME_id{ID}}},
	NODE = node_METHOD_NAME{mETHOD_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{identifier_VARIABLE_NAME{vARIABLE_NAME_id{ID}}},
	NODE = node_VARIABLE_NAME{vARIABLE_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{identifier_CAST{cAST_id{ID}}},
	NODE = node_CAST{cAST_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{identifier_OP{oP_id{ID}}},
	NODE = node_OP{oP_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{identifier_CONSTANT_NAME{cONSTANT_NAME_id{ID}}},
	NODE = node_CONSTANT_NAME{cONSTANT_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{identifier_DIRECTIVE_NAME{dIRECTIVE_NAME_id{ID}}},
	NODE = node_DIRECTIVE_NAME{dIRECTIVE_NAME_id{ID}}.
to_node (ANY, NODE) :- 
	ANY = any{source_rep_INTERFACE_NAME{iNTERFACE_NAME_id{ID}}},
	NODE = node_INTERFACE_NAME{iNTERFACE_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{source_rep_CLASS_NAME{cLASS_NAME_id{ID}}},
	NODE = node_CLASS_NAME{cLASS_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{source_rep_METHOD_NAME{mETHOD_NAME_id{ID}}},
	NODE = node_METHOD_NAME{mETHOD_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{source_rep_VARIABLE_NAME{vARIABLE_NAME_id{ID}}},
	NODE = node_VARIABLE_NAME{vARIABLE_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{source_rep_CAST{cAST_id{ID}}},
	NODE = node_CAST{cAST_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{source_rep_OP{oP_id{ID}}},
	NODE = node_OP{oP_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{source_rep_CONSTANT_NAME{cONSTANT_NAME_id{ID}}},
	NODE = node_CONSTANT_NAME{cONSTANT_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{source_rep_DIRECTIVE_NAME{dIRECTIVE_NAME_id{ID}}},
	NODE = node_DIRECTIVE_NAME{dIRECTIVE_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{source_rep_INT{iNT_id{ID}}},
	NODE = node_INT{iNT_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{source_rep_REAL{rEAL_id{ID}}},
	NODE = node_REAL{rEAL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{source_rep_STRING{sTRING_id{ID}}},
	NODE = node_STRING{sTRING_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{source_rep_BOOL{bOOL_id{ID}}},
	NODE = node_BOOL{bOOL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{source_rep_NIL{nIL_id{ID}}},
	NODE = node_NIL{nIL_id{ID}}.


to_node (ANY, NODE) :- 
	ANY = any{cLASS_NAME_id{ID}},
	NODE = node_CLASS_NAME{cLASS_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{iNTERFACE_NAME_id{ID}},
	NODE = node_INTERFACE_NAME{iNTERFACE_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{mETHOD_NAME_id{ID}},
	NODE = node_METHOD_NAME{mETHOD_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{vARIABLE_NAME_id{ID}},
	NODE = node_VARIABLE_NAME{vARIABLE_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{dIRECTIVE_NAME_id{ID}},
	NODE = node_DIRECTIVE_NAME{dIRECTIVE_NAME_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{iNT_id{ID}},
	NODE = node_INT{iNT_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{rEAL_id{ID}},
	NODE = node_REAL{rEAL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{sTRING_id{ID}},
	NODE = node_STRING{sTRING_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{bOOL_id{ID}},
	NODE = node_BOOL{bOOL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{nIL_id{ID}},
	NODE = node_NIL{nIL_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{oP_id{ID}},
	NODE = node_OP{oP_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{cAST_id{ID}},
	NODE = node_CAST{cAST_id{ID}}.

to_node (ANY, NODE) :- 
	ANY = any{cONSTANT_NAME_id{ID}},
	NODE = node_CONSTANT_NAME{cONSTANT_NAME_id{ID}}.




% Data visitors
to_generic (NODE, GENERIC) :-
	ast()->pHP_script(ID, STATEMENTS),
	to_node (any{ID}, NODE),
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{NODE, "PHP_script", [GEN_STATEMENTS]}.

to_generic (NODE, GENERIC) :-
	ast()->class_def(ID, CLASS_MOD, CLASS_NAME, OPT_EXTENDS, IMPLEMENTSS, MEMBERS),
	to_node (any{ID}, NODE),
	to_node (any{CLASS_MOD}, NODE_CLASS_MOD),
	to_generic (NODE_CLASS_MOD, GEN_CLASS_MOD),
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	((OPT_EXTENDS = yes{EXTENDS},
	to_node (any{EXTENDS}, NODE_EXTENDS),
	to_generic (NODE_EXTENDS, GEN_EXTENDS),
	GEN_OPT_EXTENDS = gmaybe{"CLASS_NAME", yes{GEN_EXTENDS}})
	;
	(OPT_EXTENDS \= yes{_},
	GEN_OPT_EXTENDS = gmaybe{"CLASS_NAME", no})),
	list_to_generic_list (IMPLEMENTSS, GEN_IMPLEMENTSS),
	list_to_generic_list (MEMBERS, GEN_MEMBERS),
	GENERIC = gnode{NODE, "Class_def", [GEN_CLASS_MOD, GEN_CLASS_NAME, GEN_OPT_EXTENDS, GEN_IMPLEMENTSS, GEN_MEMBERS]}.

to_generic (NODE, GENERIC) :-
	ast()->class_mod(ID, IS_ABSTRACT, IS_FINAL),
	to_node (any{ID}, NODE),
	GEN_IS_ABSTRACT = gmarker {"abstract", IS_ABSTRACT},
	GEN_IS_FINAL = gmarker {"final", IS_FINAL},
	GENERIC = gnode{NODE, "Class_mod", [GEN_IS_ABSTRACT, GEN_IS_FINAL]}.

to_generic (NODE, GENERIC) :-
	ast()->interface_def(ID, INTERFACE_NAME, EXTENDSS, MEMBERS),
	to_node (any{ID}, NODE),
	to_node (any{INTERFACE_NAME}, NODE_INTERFACE_NAME),
	to_generic (NODE_INTERFACE_NAME, GEN_INTERFACE_NAME),
	list_to_generic_list (EXTENDSS, GEN_EXTENDSS),
	list_to_generic_list (MEMBERS, GEN_MEMBERS),
	GENERIC = gnode{NODE, "Interface_def", [GEN_INTERFACE_NAME, GEN_EXTENDSS, GEN_MEMBERS]}.

to_generic (NODE, GENERIC) :-
	ast()->method(ID, SIGNATURE, OPT_STATEMENTS),
	to_node (any{ID}, NODE),
	to_node (any{SIGNATURE}, NODE_SIGNATURE),
	to_generic (NODE_SIGNATURE, GEN_SIGNATURE),
	((OPT_STATEMENTS = yes{STATEMENTS},
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	GEN_OPT_STATEMENTS = gmaybe{"Statement", yes{GEN_STATEMENTS}})
	;
	(OPT_STATEMENTS \= yes{_},
	GEN_OPT_STATEMENTS = gmaybe{"Statement", no})),
	GENERIC = gnode{NODE, "Method", [GEN_SIGNATURE, GEN_OPT_STATEMENTS]}.

to_generic (NODE, GENERIC) :-
	ast()->signature(ID, METHOD_MOD, IS_REF, METHOD_NAME, FORMAL_PARAMETERS),
	to_node (any{ID}, NODE),
	to_node (any{METHOD_MOD}, NODE_METHOD_MOD),
	to_generic (NODE_METHOD_MOD, GEN_METHOD_MOD),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{METHOD_NAME}, NODE_METHOD_NAME),
	to_generic (NODE_METHOD_NAME, GEN_METHOD_NAME),
	list_to_generic_list (FORMAL_PARAMETERS, GEN_FORMAL_PARAMETERS),
	GENERIC = gnode{NODE, "Signature", [GEN_METHOD_MOD, GEN_IS_REF, GEN_METHOD_NAME, GEN_FORMAL_PARAMETERS]}.

to_generic (NODE, GENERIC) :-
	ast()->method_mod(ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_ABSTRACT, IS_FINAL),
	to_node (any{ID}, NODE),
	GEN_IS_PUBLIC = gmarker {"public", IS_PUBLIC},
	GEN_IS_PROTECTED = gmarker {"protected", IS_PROTECTED},
	GEN_IS_PRIVATE = gmarker {"private", IS_PRIVATE},
	GEN_IS_STATIC = gmarker {"static", IS_STATIC},
	GEN_IS_ABSTRACT = gmarker {"abstract", IS_ABSTRACT},
	GEN_IS_FINAL = gmarker {"final", IS_FINAL},
	GENERIC = gnode{NODE, "Method_mod", [GEN_IS_PUBLIC, GEN_IS_PROTECTED, GEN_IS_PRIVATE, GEN_IS_STATIC, GEN_IS_ABSTRACT, GEN_IS_FINAL]}.

to_generic (NODE, GENERIC) :-
	ast()->formal_parameter(ID, TYPE, IS_REF, VAR),
	to_node (any{ID}, NODE),
	to_node (any{TYPE}, NODE_TYPE),
	to_generic (NODE_TYPE, GEN_TYPE),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{VAR}, NODE_VAR),
	to_generic (NODE_VAR, GEN_VAR),
	GENERIC = gnode{NODE, "Formal_parameter", [GEN_TYPE, GEN_IS_REF, GEN_VAR]}.

to_generic (NODE, GENERIC) :-
	ast()->p_type(ID, OPT_CLASS_NAME),
	to_node (any{ID}, NODE),
	((OPT_CLASS_NAME = yes{CLASS_NAME},
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	GEN_OPT_CLASS_NAME = gmaybe{"CLASS_NAME", yes{GEN_CLASS_NAME}})
	;
	(OPT_CLASS_NAME \= yes{_},
	GEN_OPT_CLASS_NAME = gmaybe{"CLASS_NAME", no})),
	GENERIC = gnode{NODE, "Type", [GEN_OPT_CLASS_NAME]}.

to_generic (NODE, GENERIC) :-
	ast()->attribute(ID, ATTR_MOD, VARSS),
	to_node (any{ID}, NODE),
	to_node (any{ATTR_MOD}, NODE_ATTR_MOD),
	to_generic (NODE_ATTR_MOD, GEN_ATTR_MOD),
	list_to_generic_list (VARSS, GEN_VARSS),
	GENERIC = gnode{NODE, "Attribute", [GEN_ATTR_MOD, GEN_VARSS]}.

to_generic (NODE, GENERIC) :-
	ast()->attr_mod(ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_CONST),
	to_node (any{ID}, NODE),
	GEN_IS_PUBLIC = gmarker {"public", IS_PUBLIC},
	GEN_IS_PROTECTED = gmarker {"protected", IS_PROTECTED},
	GEN_IS_PRIVATE = gmarker {"private", IS_PRIVATE},
	GEN_IS_STATIC = gmarker {"static", IS_STATIC},
	GEN_IS_CONST = gmarker {"const", IS_CONST},
	GENERIC = gnode{NODE, "Attr_mod", [GEN_IS_PUBLIC, GEN_IS_PROTECTED, GEN_IS_PRIVATE, GEN_IS_STATIC, GEN_IS_CONST]}.

to_generic (NODE, GENERIC) :-
	ast()->name_with_default(ID, VARIABLE_NAME, OPT_EXPR),
	to_node (any{ID}, NODE),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	((OPT_EXPR = yes{EXPR},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GEN_OPT_EXPR = gmaybe{"Expr", yes{GEN_EXPR}})
	;
	(OPT_EXPR \= yes{_},
	GEN_OPT_EXPR = gmaybe{"Expr", no})),
	GENERIC = gnode{NODE, "Name_with_default", [GEN_VARIABLE_NAME, GEN_OPT_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->if(ID, EXPR, IFTRUES, IFFALSES),
	to_node (any{ID}, NODE),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	list_to_generic_list (IFTRUES, GEN_IFTRUES),
	list_to_generic_list (IFFALSES, GEN_IFFALSES),
	GENERIC = gnode{NODE, "If", [GEN_EXPR, GEN_IFTRUES, GEN_IFFALSES]}.

to_generic (NODE, GENERIC) :-
	ast()->while(ID, EXPR, STATEMENTS),
	to_node (any{ID}, NODE),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{NODE, "While", [GEN_EXPR, GEN_STATEMENTS]}.

to_generic (NODE, GENERIC) :-
	ast()->do(ID, STATEMENTS, EXPR),
	to_node (any{ID}, NODE),
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Do", [GEN_STATEMENTS, GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->for(ID, OPT_INIT, OPT_COND, OPT_INCR, STATEMENTS),
	to_node (any{ID}, NODE),
	((OPT_INIT = yes{INIT},
	to_node (any{INIT}, NODE_INIT),
	to_generic (NODE_INIT, GEN_INIT),
	GEN_OPT_INIT = gmaybe{"Expr", yes{GEN_INIT}})
	;
	(OPT_INIT \= yes{_},
	GEN_OPT_INIT = gmaybe{"Expr", no})),
	((OPT_COND = yes{COND},
	to_node (any{COND}, NODE_COND),
	to_generic (NODE_COND, GEN_COND),
	GEN_OPT_COND = gmaybe{"Expr", yes{GEN_COND}})
	;
	(OPT_COND \= yes{_},
	GEN_OPT_COND = gmaybe{"Expr", no})),
	((OPT_INCR = yes{INCR},
	to_node (any{INCR}, NODE_INCR),
	to_generic (NODE_INCR, GEN_INCR),
	GEN_OPT_INCR = gmaybe{"Expr", yes{GEN_INCR}})
	;
	(OPT_INCR \= yes{_},
	GEN_OPT_INCR = gmaybe{"Expr", no})),
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{NODE, "For", [GEN_OPT_INIT, GEN_OPT_COND, GEN_OPT_INCR, GEN_STATEMENTS]}.

to_generic (NODE, GENERIC) :-
	ast()->foreach(ID, EXPR, OPT_KEY, IS_REF, VAL, STATEMENTS),
	to_node (any{ID}, NODE),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	((OPT_KEY = yes{KEY},
	to_node (any{KEY}, NODE_KEY),
	to_generic (NODE_KEY, GEN_KEY),
	GEN_OPT_KEY = gmaybe{"Variable", yes{GEN_KEY}})
	;
	(OPT_KEY \= yes{_},
	GEN_OPT_KEY = gmaybe{"Variable", no})),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{VAL}, NODE_VAL),
	to_generic (NODE_VAL, GEN_VAL),
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{NODE, "Foreach", [GEN_EXPR, GEN_OPT_KEY, GEN_IS_REF, GEN_VAL, GEN_STATEMENTS]}.

to_generic (NODE, GENERIC) :-
	ast()->switch(ID, EXPR, SWITCH_CASES),
	to_node (any{ID}, NODE),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	list_to_generic_list (SWITCH_CASES, GEN_SWITCH_CASES),
	GENERIC = gnode{NODE, "Switch", [GEN_EXPR, GEN_SWITCH_CASES]}.

to_generic (NODE, GENERIC) :-
	ast()->switch_case(ID, OPT_EXPR, STATEMENTS),
	to_node (any{ID}, NODE),
	((OPT_EXPR = yes{EXPR},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GEN_OPT_EXPR = gmaybe{"Expr", yes{GEN_EXPR}})
	;
	(OPT_EXPR \= yes{_},
	GEN_OPT_EXPR = gmaybe{"Expr", no})),
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{NODE, "Switch_case", [GEN_OPT_EXPR, GEN_STATEMENTS]}.

to_generic (NODE, GENERIC) :-
	ast()->break(ID, OPT_EXPR),
	to_node (any{ID}, NODE),
	((OPT_EXPR = yes{EXPR},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GEN_OPT_EXPR = gmaybe{"Expr", yes{GEN_EXPR}})
	;
	(OPT_EXPR \= yes{_},
	GEN_OPT_EXPR = gmaybe{"Expr", no})),
	GENERIC = gnode{NODE, "Break", [GEN_OPT_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->continue(ID, OPT_EXPR),
	to_node (any{ID}, NODE),
	((OPT_EXPR = yes{EXPR},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GEN_OPT_EXPR = gmaybe{"Expr", yes{GEN_EXPR}})
	;
	(OPT_EXPR \= yes{_},
	GEN_OPT_EXPR = gmaybe{"Expr", no})),
	GENERIC = gnode{NODE, "Continue", [GEN_OPT_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->return(ID, OPT_EXPR),
	to_node (any{ID}, NODE),
	((OPT_EXPR = yes{EXPR},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GEN_OPT_EXPR = gmaybe{"Expr", yes{GEN_EXPR}})
	;
	(OPT_EXPR \= yes{_},
	GEN_OPT_EXPR = gmaybe{"Expr", no})),
	GENERIC = gnode{NODE, "Return", [GEN_OPT_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->static_declaration(ID, VARSS),
	to_node (any{ID}, NODE),
	list_to_generic_list (VARSS, GEN_VARSS),
	GENERIC = gnode{NODE, "Static_declaration", [GEN_VARSS]}.

to_generic (NODE, GENERIC) :-
	ast()->global(ID, VARIABLE_NAMES),
	to_node (any{ID}, NODE),
	list_to_generic_list (VARIABLE_NAMES, GEN_VARIABLE_NAMES),
	GENERIC = gnode{NODE, "Global", [GEN_VARIABLE_NAMES]}.

to_generic (NODE, GENERIC) :-
	ast()->declare(ID, DIRECTIVES, STATEMENTS),
	to_node (any{ID}, NODE),
	list_to_generic_list (DIRECTIVES, GEN_DIRECTIVES),
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{NODE, "Declare", [GEN_DIRECTIVES, GEN_STATEMENTS]}.

to_generic (NODE, GENERIC) :-
	ast()->directive(ID, DIRECTIVE_NAME, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{DIRECTIVE_NAME}, NODE_DIRECTIVE_NAME),
	to_generic (NODE_DIRECTIVE_NAME, GEN_DIRECTIVE_NAME),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Directive", [GEN_DIRECTIVE_NAME, GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->try(ID, STATEMENTS, CATCHESS),
	to_node (any{ID}, NODE),
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	list_to_generic_list (CATCHESS, GEN_CATCHESS),
	GENERIC = gnode{NODE, "Try", [GEN_STATEMENTS, GEN_CATCHESS]}.

to_generic (NODE, GENERIC) :-
	ast()->catch(ID, CLASS_NAME, VARIABLE_NAME, STATEMENTS),
	to_node (any{ID}, NODE),
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{NODE, "Catch", [GEN_CLASS_NAME, GEN_VARIABLE_NAME, GEN_STATEMENTS]}.

to_generic (NODE, GENERIC) :-
	ast()->throw(ID, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Throw", [GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->eval_expr(ID, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Eval_expr", [GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->nop(ID),
	to_node (any{ID}, NODE),
	GENERIC = gnode{NODE, "Nop", []}.

to_generic (NODE, GENERIC) :-
	ast()->foreign_expr(ID),
	to_node (any{ID}, NODE),
	GENERIC = gnode{NODE, "Foreign_expr", []}.

to_generic (NODE, GENERIC) :-
	ast()->foreign_statement(ID),
	to_node (any{ID}, NODE),
	GENERIC = gnode{NODE, "Foreign_statement", []}.

to_generic (NODE, GENERIC) :-
	ast()->assignment(ID, VARIABLE, IS_REF, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{VARIABLE}, NODE_VARIABLE),
	to_generic (NODE_VARIABLE, GEN_VARIABLE),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Assignment", [GEN_VARIABLE, GEN_IS_REF, GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->op_assignment(ID, VARIABLE, OP, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{VARIABLE}, NODE_VARIABLE),
	to_generic (NODE_VARIABLE, GEN_VARIABLE),
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Op_assignment", [GEN_VARIABLE, GEN_OP, GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->list_assignment(ID, LIST_ELEMENTS, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{LIST_ELEMENTS}, NODE_LIST_ELEMENTS),
	to_generic (NODE_LIST_ELEMENTS, GEN_LIST_ELEMENTS),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "List_assignment", [GEN_LIST_ELEMENTS, GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->nested_list_elements(ID, LIST_ELEMENTS),
	to_node (any{ID}, NODE),
	to_node (any{LIST_ELEMENTS}, NODE_LIST_ELEMENTS),
	to_generic (NODE_LIST_ELEMENTS, GEN_LIST_ELEMENTS),
	GENERIC = gnode{NODE, "Nested_list_elements", [GEN_LIST_ELEMENTS]}.

to_generic (NODE, GENERIC) :-
	ast()->cast(ID, CAST, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{CAST}, NODE_CAST),
	to_generic (NODE_CAST, GEN_CAST),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Cast", [GEN_CAST, GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->unary_op(ID, OP, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Unary_op", [GEN_OP, GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->bin_op(ID, LEFT, OP, RIGHT),
	to_node (any{ID}, NODE),
	to_node (any{LEFT}, NODE_LEFT),
	to_generic (NODE_LEFT, GEN_LEFT),
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{RIGHT}, NODE_RIGHT),
	to_generic (NODE_RIGHT, GEN_RIGHT),
	GENERIC = gnode{NODE, "Bin_op", [GEN_LEFT, GEN_OP, GEN_RIGHT]}.

to_generic (NODE, GENERIC) :-
	ast()->conditional_expr(ID, COND, IFTRUE, IFFALSE),
	to_node (any{ID}, NODE),
	to_node (any{COND}, NODE_COND),
	to_generic (NODE_COND, GEN_COND),
	to_node (any{IFTRUE}, NODE_IFTRUE),
	to_generic (NODE_IFTRUE, GEN_IFTRUE),
	to_node (any{IFFALSE}, NODE_IFFALSE),
	to_generic (NODE_IFFALSE, GEN_IFFALSE),
	GENERIC = gnode{NODE, "Conditional_expr", [GEN_COND, GEN_IFTRUE, GEN_IFFALSE]}.

to_generic (NODE, GENERIC) :-
	ast()->ignore_errors(ID, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Ignore_errors", [GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->constant(ID, OPT_CLASS_NAME, CONSTANT_NAME),
	to_node (any{ID}, NODE),
	((OPT_CLASS_NAME = yes{CLASS_NAME},
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	GEN_OPT_CLASS_NAME = gmaybe{"CLASS_NAME", yes{GEN_CLASS_NAME}})
	;
	(OPT_CLASS_NAME \= yes{_},
	GEN_OPT_CLASS_NAME = gmaybe{"CLASS_NAME", no})),
	to_node (any{CONSTANT_NAME}, NODE_CONSTANT_NAME),
	to_generic (NODE_CONSTANT_NAME, GEN_CONSTANT_NAME),
	GENERIC = gnode{NODE, "Constant", [GEN_OPT_CLASS_NAME, GEN_CONSTANT_NAME]}.

to_generic (NODE, GENERIC) :-
	ast()->instanceof(ID, EXPR, CLASS_NAME),
	to_node (any{ID}, NODE),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	GENERIC = gnode{NODE, "Instanceof", [GEN_EXPR, GEN_CLASS_NAME]}.

to_generic (NODE, GENERIC) :-
	ast()->variable(ID, OPT_TARGET, VARIABLE_NAME, ARRAY_INDICESS),
	to_node (any{ID}, NODE),
	((OPT_TARGET = yes{TARGET},
	to_node (any{TARGET}, NODE_TARGET),
	to_generic (NODE_TARGET, GEN_TARGET),
	GEN_OPT_TARGET = gmaybe{"Target", yes{GEN_TARGET}})
	;
	(OPT_TARGET \= yes{_},
	GEN_OPT_TARGET = gmaybe{"Target", no})),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	to_node (any{ARRAY_INDICESS}, NODE_ARRAY_INDICESS),
	to_generic (NODE_ARRAY_INDICESS, GEN_ARRAY_INDICESS),
	GENERIC = gnode{NODE, "Variable", [GEN_OPT_TARGET, GEN_VARIABLE_NAME, GEN_ARRAY_INDICESS]}.

to_generic (NODE, GENERIC) :-
	ast()->reflection(ID, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Reflection", [GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->pre_op(ID, OP, VARIABLE),
	to_node (any{ID}, NODE),
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{VARIABLE}, NODE_VARIABLE),
	to_generic (NODE_VARIABLE, GEN_VARIABLE),
	GENERIC = gnode{NODE, "Pre_op", [GEN_OP, GEN_VARIABLE]}.

to_generic (NODE, GENERIC) :-
	ast()->post_op(ID, VARIABLE, OP),
	to_node (any{ID}, NODE),
	to_node (any{VARIABLE}, NODE_VARIABLE),
	to_generic (NODE_VARIABLE, GEN_VARIABLE),
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	GENERIC = gnode{NODE, "Post_op", [GEN_VARIABLE, GEN_OP]}.

to_generic (NODE, GENERIC) :-
	ast()->array(ID, ARRAY_ELEMS),
	to_node (any{ID}, NODE),
	list_to_generic_list (ARRAY_ELEMS, GEN_ARRAY_ELEMS),
	GENERIC = gnode{NODE, "Array", [GEN_ARRAY_ELEMS]}.

to_generic (NODE, GENERIC) :-
	ast()->array_elem(ID, OPT_KEY, IS_REF, VAL),
	to_node (any{ID}, NODE),
	((OPT_KEY = yes{KEY},
	to_node (any{KEY}, NODE_KEY),
	to_generic (NODE_KEY, GEN_KEY),
	GEN_OPT_KEY = gmaybe{"Expr", yes{GEN_KEY}})
	;
	(OPT_KEY \= yes{_},
	GEN_OPT_KEY = gmaybe{"Expr", no})),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{VAL}, NODE_VAL),
	to_generic (NODE_VAL, GEN_VAL),
	GENERIC = gnode{NODE, "Array_elem", [GEN_OPT_KEY, GEN_IS_REF, GEN_VAL]}.

to_generic (NODE, GENERIC) :-
	ast()->method_invocation(ID, OPT_TARGET, METHOD_NAME, ACTUAL_PARAMETERS),
	to_node (any{ID}, NODE),
	((OPT_TARGET = yes{TARGET},
	to_node (any{TARGET}, NODE_TARGET),
	to_generic (NODE_TARGET, GEN_TARGET),
	GEN_OPT_TARGET = gmaybe{"Target", yes{GEN_TARGET}})
	;
	(OPT_TARGET \= yes{_},
	GEN_OPT_TARGET = gmaybe{"Target", no})),
	to_node (any{METHOD_NAME}, NODE_METHOD_NAME),
	to_generic (NODE_METHOD_NAME, GEN_METHOD_NAME),
	list_to_generic_list (ACTUAL_PARAMETERS, GEN_ACTUAL_PARAMETERS),
	GENERIC = gnode{NODE, "Method_invocation", [GEN_OPT_TARGET, GEN_METHOD_NAME, GEN_ACTUAL_PARAMETERS]}.

to_generic (NODE, GENERIC) :-
	ast()->actual_parameter(ID, IS_REF, EXPR),
	to_node (any{ID}, NODE),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Actual_parameter", [GEN_IS_REF, GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	ast()->new(ID, CLASS_NAME, ACTUAL_PARAMETERS),
	to_node (any{ID}, NODE),
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	list_to_generic_list (ACTUAL_PARAMETERS, GEN_ACTUAL_PARAMETERS),
	GENERIC = gnode{NODE, "New", [GEN_CLASS_NAME, GEN_ACTUAL_PARAMETERS]}.



to_generic (NODE, GENERIC) :-
	ast()->cLASS_NAME(ID, CLASS_NAME),
	to_node (any{ID}, NODE),
	GEN_CLASS_NAME = gstring {CLASS_NAME},
	GENERIC = gnode{NODE, "CLASS_NAME", [GEN_CLASS_NAME]}.

to_generic (NODE, GENERIC) :-
	ast()->iNTERFACE_NAME(ID, INTERFACE_NAME),
	to_node (any{ID}, NODE),
	GEN_INTERFACE_NAME = gstring {INTERFACE_NAME},
	GENERIC = gnode{NODE, "INTERFACE_NAME", [GEN_INTERFACE_NAME]}.

to_generic (NODE, GENERIC) :-
	ast()->mETHOD_NAME(ID, METHOD_NAME),
	to_node (any{ID}, NODE),
	GEN_METHOD_NAME = gstring {METHOD_NAME},
	GENERIC = gnode{NODE, "METHOD_NAME", [GEN_METHOD_NAME]}.

to_generic (NODE, GENERIC) :-
	ast()->vARIABLE_NAME(ID, VARIABLE_NAME),
	to_node (any{ID}, NODE),
	GEN_VARIABLE_NAME = gstring {VARIABLE_NAME},
	GENERIC = gnode{NODE, "VARIABLE_NAME", [GEN_VARIABLE_NAME]}.

to_generic (NODE, GENERIC) :-
	ast()->dIRECTIVE_NAME(ID, DIRECTIVE_NAME),
	to_node (any{ID}, NODE),
	GEN_DIRECTIVE_NAME = gstring {DIRECTIVE_NAME},
	GENERIC = gnode{NODE, "DIRECTIVE_NAME", [GEN_DIRECTIVE_NAME]}.

to_generic (NODE, GENERIC) :-
	ast()->iNT(ID, INT),
	to_node (any{ID}, NODE),
	GEN_INT = gint {INT},
	GENERIC = gnode{NODE, "INT", [GEN_INT]}.

to_generic (NODE, GENERIC) :-
	ast()->rEAL(ID, REAL),
	to_node (any{ID}, NODE),
	GEN_REAL = gfloat {REAL},
	GENERIC = gnode{NODE, "REAL", [GEN_REAL]}.

to_generic (NODE, GENERIC) :-
	ast()->sTRING(ID, STRING),
	to_node (any{ID}, NODE),
	GEN_STRING = gstring {STRING},
	GENERIC = gnode{NODE, "STRING", [GEN_STRING]}.

to_generic (NODE, GENERIC) :-
	ast()->bOOL(ID, BOOL),
	to_node (any{ID}, NODE),
	GEN_BOOL = gbool {BOOL},
	GENERIC = gnode{NODE, "BOOL", [GEN_BOOL]}.

to_generic (NODE, GENERIC) :-
	ast()->nIL(ID, NIL),
	to_node (any{ID}, NODE),
	GEN_NIL = gnull {NIL},
	GENERIC = gnode{NODE, "NIL", [GEN_NIL]}.

to_generic (NODE, GENERIC) :-
	ast()->oP(ID, OP),
	to_node (any{ID}, NODE),
	GEN_OP = gstring {OP},
	GENERIC = gnode{NODE, "OP", [GEN_OP]}.

to_generic (NODE, GENERIC) :-
	ast()->cAST(ID, CAST),
	to_node (any{ID}, NODE),
	GEN_CAST = gstring {CAST},
	GENERIC = gnode{NODE, "CAST", [GEN_CAST]}.

to_generic (NODE, GENERIC) :-
	ast()->cONSTANT_NAME(ID, CONSTANT_NAME),
	to_node (any{ID}, NODE),
	GEN_CONSTANT_NAME = gstring {CONSTANT_NAME},
	GENERIC = gnode{NODE, "CONSTANT_NAME", [GEN_CONSTANT_NAME]}.



