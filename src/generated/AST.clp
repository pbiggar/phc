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
type t_CLASS_NAME ::= cLASS_NAME { ID:id, VALUE:string }.
type t_INTERFACE_NAME ::= iNTERFACE_NAME { ID:id, VALUE:string }.
type t_METHOD_NAME ::= mETHOD_NAME { ID:id, VALUE:string }.
type t_VARIABLE_NAME ::= vARIABLE_NAME { ID:id, VALUE:string }.
type t_DIRECTIVE_NAME ::= dIRECTIVE_NAME { ID:id, VALUE:string }.
type t_INT ::= iNT { ID:id, VALUE:int }.
type t_REAL ::= rEAL { ID:id, VALUE:float }.
type t_STRING ::= sTRING { ID:id, VALUE:string }.
type t_BOOL ::= bOOL { ID:id, VALUE:bool }.
type t_NIL ::= nIL { ID:id, VALUE:null }.
type t_OP ::= oP { ID:id, VALUE:string }.
type t_CAST ::= cAST { ID:id, VALUE:string }.
type t_CONSTANT_NAME ::= cONSTANT_NAME { ID:id, VALUE:string }.



% Types
type t_PHP_script ::= pHP_script { ID:id, STATEMENTS:list[t_Statement] }.
type t_Class_def ::= class_def { ID:id, CLASS_MOD:t_Class_mod, CLASS_NAME:t_CLASS_NAME, OPT_EXTENDS:maybe[t_CLASS_NAME], IMPLEMENTSS:list[t_INTERFACE_NAME], MEMBERS:list[t_Member] }.
type t_Class_mod ::= class_mod { ID:id, IS_ABSTRACT:bool, IS_FINAL:bool }.
type t_Interface_def ::= interface_def { ID:id, INTERFACE_NAME:t_INTERFACE_NAME, EXTENDSS:list[t_INTERFACE_NAME], MEMBERS:list[t_Member] }.
type t_Method ::= method { ID:id, SIGNATURE:t_Signature, OPT_STATEMENTS:maybe[list[t_Statement]] }.
type t_Signature ::= signature { ID:id, METHOD_MOD:t_Method_mod, IS_REF:bool, METHOD_NAME:t_METHOD_NAME, FORMAL_PARAMETERS:list[t_Formal_parameter] }.
type t_Method_mod ::= method_mod { ID:id, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_ABSTRACT:bool, IS_FINAL:bool }.
type t_Formal_parameter ::= formal_parameter { ID:id, TYPE:t_Type, IS_REF:bool, VAR:t_Name_with_default }.
type t_Type ::= t_type { ID:id, OPT_CLASS_NAME:maybe[t_CLASS_NAME] }.
type t_Attribute ::= attribute { ID:id, ATTR_MOD:t_Attr_mod, VARSS:list[t_Name_with_default] }.
type t_Attr_mod ::= attr_mod { ID:id, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_CONST:bool }.
type t_Name_with_default ::= name_with_default { ID:id, VARIABLE_NAME:t_VARIABLE_NAME, OPT_EXPR:maybe[t_Expr] }.
type t_If ::= if { ID:id, EXPR:t_Expr, IFTRUES:list[t_Statement], IFFALSES:list[t_Statement] }.
type t_While ::= while { ID:id, EXPR:t_Expr, STATEMENTS:list[t_Statement] }.
type t_Do ::= do { ID:id, STATEMENTS:list[t_Statement], EXPR:t_Expr }.
type t_For ::= for { ID:id, OPT_INIT:maybe[t_Expr], OPT_COND:maybe[t_Expr], OPT_INCR:maybe[t_Expr], STATEMENTS:list[t_Statement] }.
type t_Foreach ::= foreach { ID:id, EXPR:t_Expr, OPT_KEY:maybe[t_Variable], IS_REF:bool, VAL:t_Variable, STATEMENTS:list[t_Statement] }.
type t_Switch ::= switch { ID:id, EXPR:t_Expr, SWITCH_CASES:list[t_Switch_case] }.
type t_Switch_case ::= switch_case { ID:id, OPT_EXPR:maybe[t_Expr], STATEMENTS:list[t_Statement] }.
type t_Break ::= break { ID:id, OPT_EXPR:maybe[t_Expr] }.
type t_Continue ::= continue { ID:id, OPT_EXPR:maybe[t_Expr] }.
type t_Return ::= return { ID:id, OPT_EXPR:maybe[t_Expr] }.
type t_Static_declaration ::= static_declaration { ID:id, VARSS:list[t_Name_with_default] }.
type t_Global ::= global { ID:id, VARIABLE_NAMES:list[t_Variable_name] }.
type t_Declare ::= declare { ID:id, DIRECTIVES:list[t_Directive], STATEMENTS:list[t_Statement] }.
type t_Directive ::= directive { ID:id, DIRECTIVE_NAME:t_DIRECTIVE_NAME, EXPR:t_Expr }.
type t_Try ::= try { ID:id, STATEMENTS:list[t_Statement], CATCHESS:list[t_Catch] }.
type t_Catch ::= catch { ID:id, CLASS_NAME:t_CLASS_NAME, VARIABLE_NAME:t_VARIABLE_NAME, STATEMENTS:list[t_Statement] }.
type t_Throw ::= throw { ID:id, EXPR:t_Expr }.
type t_Eval_expr ::= eval_expr { ID:id, EXPR:t_Expr }.
type t_Nop ::= nop { ID:id }.
type t_Foreign_expr ::= foreign_expr { ID:id }.
type t_Foreign_statement ::= foreign_statement { ID:id }.
type t_Assignment ::= assignment { ID:id, VARIABLE:t_Variable, IS_REF:bool, EXPR:t_Expr }.
type t_Op_assignment ::= op_assignment { ID:id, VARIABLE:t_Variable, OP:t_OP, EXPR:t_Expr }.
type t_List_assignment ::= list_assignment { ID:id, LIST_ELEMENTS:list[maybe[t_List_element]], EXPR:t_Expr }.
type t_Nested_list_elements ::= nested_list_elements { ID:id, LIST_ELEMENTS:list[maybe[t_List_element]] }.
type t_Cast ::= cast { ID:id, CAST:t_CAST, EXPR:t_Expr }.
type t_Unary_op ::= unary_op { ID:id, OP:t_OP, EXPR:t_Expr }.
type t_Bin_op ::= bin_op { ID:id, LEFT:t_Expr, OP:t_OP, RIGHT:t_Expr }.
type t_Conditional_expr ::= conditional_expr { ID:id, COND:t_Expr, IFTRUE:t_Expr, IFFALSE:t_Expr }.
type t_Ignore_errors ::= ignore_errors { ID:id, EXPR:t_Expr }.
type t_Constant ::= constant { ID:id, OPT_CLASS_NAME:maybe[t_CLASS_NAME], CONSTANT_NAME:t_CONSTANT_NAME }.
type t_Instanceof ::= instanceof { ID:id, EXPR:t_Expr, CLASS_NAME:t_Class_name }.
type t_Variable ::= variable { ID:id, OPT_TARGET:maybe[t_Target], VARIABLE_NAME:t_Variable_name, ARRAY_INDICESS:list[maybe[t_Expr]] }.
type t_Reflection ::= reflection { ID:id, EXPR:t_Expr }.
type t_Pre_op ::= pre_op { ID:id, OP:t_OP, VARIABLE:t_Variable }.
type t_Post_op ::= post_op { ID:id, VARIABLE:t_Variable, OP:t_OP }.
type t_Array ::= array { ID:id, ARRAY_ELEMS:list[t_Array_elem] }.
type t_Array_elem ::= array_elem { ID:id, OPT_KEY:maybe[t_Expr], IS_REF:bool, VAL:t_Expr }.
type t_Method_invocation ::= method_invocation { ID:id, OPT_TARGET:maybe[t_Target], METHOD_NAME:t_Method_name, ACTUAL_PARAMETERS:list[t_Actual_parameter] }.
type t_Actual_parameter ::= actual_parameter { ID:id, IS_REF:bool, EXPR:t_Expr }.
type t_New ::= new { ID:id, CLASS_NAME:t_Class_name, ACTUAL_PARAMETERS:list[t_Actual_parameter] }.


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




% Generics

% Type Casts
to_node (any{pHP_script{ID, STATEMENTS}},
	node_PHP_script{pHP_script{ID, STATEMENTS}}) :- .
to_node (any{class_def{ID, CLASS_MOD, CLASS_NAME, OPT_EXTENDS, IMPLEMENTSS, MEMBERS}},
	node_Class_def{class_def{ID, CLASS_MOD, CLASS_NAME, OPT_EXTENDS, IMPLEMENTSS, MEMBERS}}) :- .
to_node (any{class_mod{ID, IS_ABSTRACT, IS_FINAL}},
	node_Class_mod{class_mod{ID, IS_ABSTRACT, IS_FINAL}}) :- .
to_node (any{interface_def{ID, INTERFACE_NAME, EXTENDSS, MEMBERS}},
	node_Interface_def{interface_def{ID, INTERFACE_NAME, EXTENDSS, MEMBERS}}) :- .
to_node (any{method{ID, SIGNATURE, OPT_STATEMENTS}},
	node_Method{method{ID, SIGNATURE, OPT_STATEMENTS}}) :- .
to_node (any{signature{ID, METHOD_MOD, IS_REF, METHOD_NAME, FORMAL_PARAMETERS}},
	node_Signature{signature{ID, METHOD_MOD, IS_REF, METHOD_NAME, FORMAL_PARAMETERS}}) :- .
to_node (any{method_mod{ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_ABSTRACT, IS_FINAL}},
	node_Method_mod{method_mod{ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_ABSTRACT, IS_FINAL}}) :- .
to_node (any{formal_parameter{ID, TYPE, IS_REF, VAR}},
	node_Formal_parameter{formal_parameter{ID, TYPE, IS_REF, VAR}}) :- .
to_node (any{t_type{ID, OPT_CLASS_NAME}},
	node_Type{t_type{ID, OPT_CLASS_NAME}}) :- .
to_node (any{attribute{ID, ATTR_MOD, VARSS}},
	node_Attribute{attribute{ID, ATTR_MOD, VARSS}}) :- .
to_node (any{attr_mod{ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_CONST}},
	node_Attr_mod{attr_mod{ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_CONST}}) :- .
to_node (any{name_with_default{ID, VARIABLE_NAME, OPT_EXPR}},
	node_Name_with_default{name_with_default{ID, VARIABLE_NAME, OPT_EXPR}}) :- .
to_node (any{if{ID, EXPR, IFTRUES, IFFALSES}},
	node_If{if{ID, EXPR, IFTRUES, IFFALSES}}) :- .
to_node (any{while{ID, EXPR, STATEMENTS}},
	node_While{while{ID, EXPR, STATEMENTS}}) :- .
to_node (any{do{ID, STATEMENTS, EXPR}},
	node_Do{do{ID, STATEMENTS, EXPR}}) :- .
to_node (any{for{ID, OPT_INIT, OPT_COND, OPT_INCR, STATEMENTS}},
	node_For{for{ID, OPT_INIT, OPT_COND, OPT_INCR, STATEMENTS}}) :- .
to_node (any{foreach{ID, EXPR, OPT_KEY, IS_REF, VAL, STATEMENTS}},
	node_Foreach{foreach{ID, EXPR, OPT_KEY, IS_REF, VAL, STATEMENTS}}) :- .
to_node (any{switch{ID, EXPR, SWITCH_CASES}},
	node_Switch{switch{ID, EXPR, SWITCH_CASES}}) :- .
to_node (any{switch_case{ID, OPT_EXPR, STATEMENTS}},
	node_Switch_case{switch_case{ID, OPT_EXPR, STATEMENTS}}) :- .
to_node (any{break{ID, OPT_EXPR}},
	node_Break{break{ID, OPT_EXPR}}) :- .
to_node (any{continue{ID, OPT_EXPR}},
	node_Continue{continue{ID, OPT_EXPR}}) :- .
to_node (any{return{ID, OPT_EXPR}},
	node_Return{return{ID, OPT_EXPR}}) :- .
to_node (any{static_declaration{ID, VARSS}},
	node_Static_declaration{static_declaration{ID, VARSS}}) :- .
to_node (any{global{ID, VARIABLE_NAMES}},
	node_Global{global{ID, VARIABLE_NAMES}}) :- .
to_node (any{declare{ID, DIRECTIVES, STATEMENTS}},
	node_Declare{declare{ID, DIRECTIVES, STATEMENTS}}) :- .
to_node (any{directive{ID, DIRECTIVE_NAME, EXPR}},
	node_Directive{directive{ID, DIRECTIVE_NAME, EXPR}}) :- .
to_node (any{try{ID, STATEMENTS, CATCHESS}},
	node_Try{try{ID, STATEMENTS, CATCHESS}}) :- .
to_node (any{catch{ID, CLASS_NAME, VARIABLE_NAME, STATEMENTS}},
	node_Catch{catch{ID, CLASS_NAME, VARIABLE_NAME, STATEMENTS}}) :- .
to_node (any{throw{ID, EXPR}},
	node_Throw{throw{ID, EXPR}}) :- .
to_node (any{eval_expr{ID, EXPR}},
	node_Eval_expr{eval_expr{ID, EXPR}}) :- .
to_node (any{nop{ID}},
	node_Nop{nop{ID}}) :- .
to_node (any{foreign_expr{ID}},
	node_Foreign_expr{foreign_expr{ID}}) :- .
to_node (any{foreign_statement{ID}},
	node_Foreign_statement{foreign_statement{ID}}) :- .
to_node (any{assignment{ID, VARIABLE, IS_REF, EXPR}},
	node_Assignment{assignment{ID, VARIABLE, IS_REF, EXPR}}) :- .
to_node (any{op_assignment{ID, VARIABLE, OP, EXPR}},
	node_Op_assignment{op_assignment{ID, VARIABLE, OP, EXPR}}) :- .
to_node (any{list_assignment{ID, LIST_ELEMENTS, EXPR}},
	node_List_assignment{list_assignment{ID, LIST_ELEMENTS, EXPR}}) :- .
to_node (any{nested_list_elements{ID, LIST_ELEMENTS}},
	node_Nested_list_elements{nested_list_elements{ID, LIST_ELEMENTS}}) :- .
to_node (any{cast{ID, CAST, EXPR}},
	node_Cast{cast{ID, CAST, EXPR}}) :- .
to_node (any{unary_op{ID, OP, EXPR}},
	node_Unary_op{unary_op{ID, OP, EXPR}}) :- .
to_node (any{bin_op{ID, LEFT, OP, RIGHT}},
	node_Bin_op{bin_op{ID, LEFT, OP, RIGHT}}) :- .
to_node (any{conditional_expr{ID, COND, IFTRUE, IFFALSE}},
	node_Conditional_expr{conditional_expr{ID, COND, IFTRUE, IFFALSE}}) :- .
to_node (any{ignore_errors{ID, EXPR}},
	node_Ignore_errors{ignore_errors{ID, EXPR}}) :- .
to_node (any{constant{ID, OPT_CLASS_NAME, CONSTANT_NAME}},
	node_Constant{constant{ID, OPT_CLASS_NAME, CONSTANT_NAME}}) :- .
to_node (any{instanceof{ID, EXPR, CLASS_NAME}},
	node_Instanceof{instanceof{ID, EXPR, CLASS_NAME}}) :- .
to_node (any{variable{ID, OPT_TARGET, VARIABLE_NAME, ARRAY_INDICESS}},
	node_Variable{variable{ID, OPT_TARGET, VARIABLE_NAME, ARRAY_INDICESS}}) :- .
to_node (any{reflection{ID, EXPR}},
	node_Reflection{reflection{ID, EXPR}}) :- .
to_node (any{pre_op{ID, OP, VARIABLE}},
	node_Pre_op{pre_op{ID, OP, VARIABLE}}) :- .
to_node (any{post_op{ID, VARIABLE, OP}},
	node_Post_op{post_op{ID, VARIABLE, OP}}) :- .
to_node (any{array{ID, ARRAY_ELEMS}},
	node_Array{array{ID, ARRAY_ELEMS}}) :- .
to_node (any{array_elem{ID, OPT_KEY, IS_REF, VAL}},
	node_Array_elem{array_elem{ID, OPT_KEY, IS_REF, VAL}}) :- .
to_node (any{method_invocation{ID, OPT_TARGET, METHOD_NAME, ACTUAL_PARAMETERS}},
	node_Method_invocation{method_invocation{ID, OPT_TARGET, METHOD_NAME, ACTUAL_PARAMETERS}}) :- .
to_node (any{actual_parameter{ID, IS_REF, EXPR}},
	node_Actual_parameter{actual_parameter{ID, IS_REF, EXPR}}) :- .
to_node (any{new{ID, CLASS_NAME, ACTUAL_PARAMETERS}},
	node_New{new{ID, CLASS_NAME, ACTUAL_PARAMETERS}}) :- .



to_node (any{statement_Class_def{ID}}, node_Class_def{ID}) :- .
to_node (any{statement_Interface_def{ID}}, node_Interface_def{ID}) :- .
to_node (any{statement_Method{ID}}, node_Method{ID}) :- .
to_node (any{statement_Return{ID}}, node_Return{ID}) :- .
to_node (any{statement_Static_declaration{ID}}, node_Static_declaration{ID}) :- .
to_node (any{statement_Global{ID}}, node_Global{ID}) :- .
to_node (any{statement_Try{ID}}, node_Try{ID}) :- .
to_node (any{statement_Throw{ID}}, node_Throw{ID}) :- .
to_node (any{statement_Eval_expr{ID}}, node_Eval_expr{ID}) :- .
to_node (any{statement_If{ID}}, node_If{ID}) :- .
to_node (any{statement_While{ID}}, node_While{ID}) :- .
to_node (any{statement_Do{ID}}, node_Do{ID}) :- .
to_node (any{statement_For{ID}}, node_For{ID}) :- .
to_node (any{statement_Foreach{ID}}, node_Foreach{ID}) :- .
to_node (any{statement_Switch{ID}}, node_Switch{ID}) :- .
to_node (any{statement_Break{ID}}, node_Break{ID}) :- .
to_node (any{statement_Continue{ID}}, node_Continue{ID}) :- .
to_node (any{statement_Declare{ID}}, node_Declare{ID}) :- .
to_node (any{statement_Nop{ID}}, node_Nop{ID}) :- .
to_node (any{statement_Foreign_statement{ID}}, node_Foreign_statement{ID}) :- .
to_node (any{member_Method{ID}}, node_Method{ID}) :- .
to_node (any{member_Attribute{ID}}, node_Attribute{ID}) :- .
to_node (any{foreign_Foreign_expr{ID}}, node_Foreign_expr{ID}) :- .
to_node (any{foreign_Foreign_statement{ID}}, node_Foreign_statement{ID}) :- .
to_node (any{expr_Assignment{ID}}, node_Assignment{ID}) :- .
to_node (any{expr_Cast{ID}}, node_Cast{ID}) :- .
to_node (any{expr_Unary_op{ID}}, node_Unary_op{ID}) :- .
to_node (any{expr_Bin_op{ID}}, node_Bin_op{ID}) :- .
to_node (any{expr_Constant{ID}}, node_Constant{ID}) :- .
to_node (any{expr_Instanceof{ID}}, node_Instanceof{ID}) :- .
to_node (any{expr_Variable{ID}}, node_Variable{ID}) :- .
to_node (any{expr_Pre_op{ID}}, node_Pre_op{ID}) :- .
to_node (any{expr_Method_invocation{ID}}, node_Method_invocation{ID}) :- .
to_node (any{expr_New{ID}}, node_New{ID}) :- .
to_node (any{expr_INT{ID}}, node_INT{ID}) :- .
to_node (any{expr_REAL{ID}}, node_REAL{ID}) :- .
to_node (any{expr_STRING{ID}}, node_STRING{ID}) :- .
to_node (any{expr_BOOL{ID}}, node_BOOL{ID}) :- .
to_node (any{expr_NIL{ID}}, node_NIL{ID}) :- .
to_node (any{expr_Op_assignment{ID}}, node_Op_assignment{ID}) :- .
to_node (any{expr_List_assignment{ID}}, node_List_assignment{ID}) :- .
to_node (any{expr_Post_op{ID}}, node_Post_op{ID}) :- .
to_node (any{expr_Array{ID}}, node_Array{ID}) :- .
to_node (any{expr_Conditional_expr{ID}}, node_Conditional_expr{ID}) :- .
to_node (any{expr_Ignore_errors{ID}}, node_Ignore_errors{ID}) :- .
to_node (any{expr_Foreign_expr{ID}}, node_Foreign_expr{ID}) :- .
to_node (any{literal_INT{ID}}, node_INT{ID}) :- .
to_node (any{literal_REAL{ID}}, node_REAL{ID}) :- .
to_node (any{literal_STRING{ID}}, node_STRING{ID}) :- .
to_node (any{literal_BOOL{ID}}, node_BOOL{ID}) :- .
to_node (any{literal_NIL{ID}}, node_NIL{ID}) :- .
to_node (any{list_element_Variable{ID}}, node_Variable{ID}) :- .
to_node (any{list_element_Nested_list_elements{ID}}, node_Nested_list_elements{ID}) :- .
to_node (any{variable_name_VARIABLE_NAME{ID}}, node_VARIABLE_NAME{ID}) :- .
to_node (any{variable_name_Reflection{ID}}, node_Reflection{ID}) :- .
to_node (any{target_Assignment{ID}}, node_Assignment{ID}) :- .
to_node (any{target_Cast{ID}}, node_Cast{ID}) :- .
to_node (any{target_Unary_op{ID}}, node_Unary_op{ID}) :- .
to_node (any{target_Bin_op{ID}}, node_Bin_op{ID}) :- .
to_node (any{target_Constant{ID}}, node_Constant{ID}) :- .
to_node (any{target_Instanceof{ID}}, node_Instanceof{ID}) :- .
to_node (any{target_Variable{ID}}, node_Variable{ID}) :- .
to_node (any{target_Pre_op{ID}}, node_Pre_op{ID}) :- .
to_node (any{target_Method_invocation{ID}}, node_Method_invocation{ID}) :- .
to_node (any{target_New{ID}}, node_New{ID}) :- .
to_node (any{target_INT{ID}}, node_INT{ID}) :- .
to_node (any{target_REAL{ID}}, node_REAL{ID}) :- .
to_node (any{target_STRING{ID}}, node_STRING{ID}) :- .
to_node (any{target_BOOL{ID}}, node_BOOL{ID}) :- .
to_node (any{target_NIL{ID}}, node_NIL{ID}) :- .
to_node (any{target_Op_assignment{ID}}, node_Op_assignment{ID}) :- .
to_node (any{target_List_assignment{ID}}, node_List_assignment{ID}) :- .
to_node (any{target_Post_op{ID}}, node_Post_op{ID}) :- .
to_node (any{target_Array{ID}}, node_Array{ID}) :- .
to_node (any{target_Conditional_expr{ID}}, node_Conditional_expr{ID}) :- .
to_node (any{target_Ignore_errors{ID}}, node_Ignore_errors{ID}) :- .
to_node (any{target_Foreign_expr{ID}}, node_Foreign_expr{ID}) :- .
to_node (any{target_CLASS_NAME{ID}}, node_CLASS_NAME{ID}) :- .
to_node (any{method_name_METHOD_NAME{ID}}, node_METHOD_NAME{ID}) :- .
to_node (any{method_name_Reflection{ID}}, node_Reflection{ID}) :- .
to_node (any{class_name_CLASS_NAME{ID}}, node_CLASS_NAME{ID}) :- .
to_node (any{class_name_Reflection{ID}}, node_Reflection{ID}) :- .
to_node (any{commented_node_Method{ID}}, node_Method{ID}) :- .
to_node (any{commented_node_Attribute{ID}}, node_Attribute{ID}) :- .
to_node (any{commented_node_Class_def{ID}}, node_Class_def{ID}) :- .
to_node (any{commented_node_Interface_def{ID}}, node_Interface_def{ID}) :- .
to_node (any{commented_node_Return{ID}}, node_Return{ID}) :- .
to_node (any{commented_node_Static_declaration{ID}}, node_Static_declaration{ID}) :- .
to_node (any{commented_node_Global{ID}}, node_Global{ID}) :- .
to_node (any{commented_node_Try{ID}}, node_Try{ID}) :- .
to_node (any{commented_node_Throw{ID}}, node_Throw{ID}) :- .
to_node (any{commented_node_Eval_expr{ID}}, node_Eval_expr{ID}) :- .
to_node (any{commented_node_If{ID}}, node_If{ID}) :- .
to_node (any{commented_node_While{ID}}, node_While{ID}) :- .
to_node (any{commented_node_Do{ID}}, node_Do{ID}) :- .
to_node (any{commented_node_For{ID}}, node_For{ID}) :- .
to_node (any{commented_node_Foreach{ID}}, node_Foreach{ID}) :- .
to_node (any{commented_node_Switch{ID}}, node_Switch{ID}) :- .
to_node (any{commented_node_Break{ID}}, node_Break{ID}) :- .
to_node (any{commented_node_Continue{ID}}, node_Continue{ID}) :- .
to_node (any{commented_node_Declare{ID}}, node_Declare{ID}) :- .
to_node (any{commented_node_Nop{ID}}, node_Nop{ID}) :- .
to_node (any{commented_node_Foreign_statement{ID}}, node_Foreign_statement{ID}) :- .
to_node (any{commented_node_Switch_case{ID}}, node_Switch_case{ID}) :- .
to_node (any{commented_node_Catch{ID}}, node_Catch{ID}) :- .
to_node (any{identifier_INTERFACE_NAME{ID}}, node_INTERFACE_NAME{ID}) :- .
to_node (any{identifier_CLASS_NAME{ID}}, node_CLASS_NAME{ID}) :- .
to_node (any{identifier_METHOD_NAME{ID}}, node_METHOD_NAME{ID}) :- .
to_node (any{identifier_VARIABLE_NAME{ID}}, node_VARIABLE_NAME{ID}) :- .
to_node (any{identifier_CAST{ID}}, node_CAST{ID}) :- .
to_node (any{identifier_OP{ID}}, node_OP{ID}) :- .
to_node (any{identifier_CONSTANT_NAME{ID}}, node_CONSTANT_NAME{ID}) :- .
to_node (any{identifier_DIRECTIVE_NAME{ID}}, node_DIRECTIVE_NAME{ID}) :- .
to_node (any{source_rep_INTERFACE_NAME{ID}}, node_INTERFACE_NAME{ID}) :- .
to_node (any{source_rep_CLASS_NAME{ID}}, node_CLASS_NAME{ID}) :- .
to_node (any{source_rep_METHOD_NAME{ID}}, node_METHOD_NAME{ID}) :- .
to_node (any{source_rep_VARIABLE_NAME{ID}}, node_VARIABLE_NAME{ID}) :- .
to_node (any{source_rep_CAST{ID}}, node_CAST{ID}) :- .
to_node (any{source_rep_OP{ID}}, node_OP{ID}) :- .
to_node (any{source_rep_CONSTANT_NAME{ID}}, node_CONSTANT_NAME{ID}) :- .
to_node (any{source_rep_DIRECTIVE_NAME{ID}}, node_DIRECTIVE_NAME{ID}) :- .
to_node (any{source_rep_INT{ID}}, node_INT{ID}) :- .
to_node (any{source_rep_REAL{ID}}, node_REAL{ID}) :- .
to_node (any{source_rep_STRING{ID}}, node_STRING{ID}) :- .
to_node (any{source_rep_BOOL{ID}}, node_BOOL{ID}) :- .
to_node (any{source_rep_NIL{ID}}, node_NIL{ID}) :- .


to_node (any{cLASS_NAME{ID, VALUE}}, node_CLASS_NAME{cLASS_NAME{ID, VALUE}}) :- .
to_node (any{iNTERFACE_NAME{ID, VALUE}}, node_INTERFACE_NAME{iNTERFACE_NAME{ID, VALUE}}) :- .
to_node (any{mETHOD_NAME{ID, VALUE}}, node_METHOD_NAME{mETHOD_NAME{ID, VALUE}}) :- .
to_node (any{vARIABLE_NAME{ID, VALUE}}, node_VARIABLE_NAME{vARIABLE_NAME{ID, VALUE}}) :- .
to_node (any{dIRECTIVE_NAME{ID, VALUE}}, node_DIRECTIVE_NAME{dIRECTIVE_NAME{ID, VALUE}}) :- .
to_node (any{iNT{ID, VALUE}}, node_INT{iNT{ID, VALUE}}) :- .
to_node (any{rEAL{ID, VALUE}}, node_REAL{rEAL{ID, VALUE}}) :- .
to_node (any{sTRING{ID, VALUE}}, node_STRING{sTRING{ID, VALUE}}) :- .
to_node (any{bOOL{ID, VALUE}}, node_BOOL{bOOL{ID, VALUE}}) :- .
to_node (any{nIL{ID, VALUE}}, node_NIL{nIL{ID, VALUE}}) :- .
to_node (any{oP{ID, VALUE}}, node_OP{oP{ID, VALUE}}) :- .
to_node (any{cAST{ID, VALUE}}, node_CAST{cAST{ID, VALUE}}) :- .
to_node (any{cONSTANT_NAME{ID, VALUE}}, node_CONSTANT_NAME{cONSTANT_NAME{ID, VALUE}}) :- .



% Data visitors
to_generic (node_PHP_script{NODE}, GENERIC) :-
	NODE = pHP_script { _, STATEMENTS } ,
	list_to_generic_list ("Statement", STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{node_PHP_script{NODE}, "PHP_script", [GEN_STATEMENTS]}.

to_generic (node_Class_def{NODE}, GENERIC) :-
	NODE = class_def { _, CLASS_MOD, CLASS_NAME, OPT_EXTENDS, IMPLEMENTSS, MEMBERS } ,
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
	list_to_generic_list ("INTERFACE_NAME", IMPLEMENTSS, GEN_IMPLEMENTSS),
	list_to_generic_list ("Member", MEMBERS, GEN_MEMBERS),
	GENERIC = gnode{node_Class_def{NODE}, "Class_def", [GEN_CLASS_MOD, GEN_CLASS_NAME, GEN_OPT_EXTENDS, GEN_IMPLEMENTSS, GEN_MEMBERS]}.

to_generic (node_Class_mod{NODE}, GENERIC) :-
	NODE = class_mod { _, IS_ABSTRACT, IS_FINAL } ,
	GEN_IS_ABSTRACT = gmarker {"is_abstract", IS_ABSTRACT},
	GEN_IS_FINAL = gmarker {"is_final", IS_FINAL},
	GENERIC = gnode{node_Class_mod{NODE}, "Class_mod", [GEN_IS_ABSTRACT, GEN_IS_FINAL]}.

to_generic (node_Interface_def{NODE}, GENERIC) :-
	NODE = interface_def { _, INTERFACE_NAME, EXTENDSS, MEMBERS } ,
	to_node (any{INTERFACE_NAME}, NODE_INTERFACE_NAME),
	to_generic (NODE_INTERFACE_NAME, GEN_INTERFACE_NAME),
	list_to_generic_list ("INTERFACE_NAME", EXTENDSS, GEN_EXTENDSS),
	list_to_generic_list ("Member", MEMBERS, GEN_MEMBERS),
	GENERIC = gnode{node_Interface_def{NODE}, "Interface_def", [GEN_INTERFACE_NAME, GEN_EXTENDSS, GEN_MEMBERS]}.

to_generic (node_Method{NODE}, GENERIC) :-
	NODE = method { _, SIGNATURE, OPT_STATEMENTS } ,
	to_node (any{SIGNATURE}, NODE_SIGNATURE),
	to_generic (NODE_SIGNATURE, GEN_SIGNATURE),
	((OPT_STATEMENTS = yes{STATEMENTS},
	list_to_generic_list ("Statement", STATEMENTS, GEN_STATEMENTS),
	GEN_OPT_STATEMENTS = gmaybe{"Statement", yes{GEN_STATEMENTS}})
	;
	(OPT_STATEMENTS \= yes{_},
	GEN_OPT_STATEMENTS = gmaybe{"Statement", no})),
	GENERIC = gnode{node_Method{NODE}, "Method", [GEN_SIGNATURE, GEN_OPT_STATEMENTS]}.

to_generic (node_Signature{NODE}, GENERIC) :-
	NODE = signature { _, METHOD_MOD, IS_REF, METHOD_NAME, FORMAL_PARAMETERS } ,
	to_node (any{METHOD_MOD}, NODE_METHOD_MOD),
	to_generic (NODE_METHOD_MOD, GEN_METHOD_MOD),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{METHOD_NAME}, NODE_METHOD_NAME),
	to_generic (NODE_METHOD_NAME, GEN_METHOD_NAME),
	list_to_generic_list ("Formal_parameter", FORMAL_PARAMETERS, GEN_FORMAL_PARAMETERS),
	GENERIC = gnode{node_Signature{NODE}, "Signature", [GEN_METHOD_MOD, GEN_IS_REF, GEN_METHOD_NAME, GEN_FORMAL_PARAMETERS]}.

to_generic (node_Method_mod{NODE}, GENERIC) :-
	NODE = method_mod { _, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_ABSTRACT, IS_FINAL } ,
	GEN_IS_PUBLIC = gmarker {"is_public", IS_PUBLIC},
	GEN_IS_PROTECTED = gmarker {"is_protected", IS_PROTECTED},
	GEN_IS_PRIVATE = gmarker {"is_private", IS_PRIVATE},
	GEN_IS_STATIC = gmarker {"is_static", IS_STATIC},
	GEN_IS_ABSTRACT = gmarker {"is_abstract", IS_ABSTRACT},
	GEN_IS_FINAL = gmarker {"is_final", IS_FINAL},
	GENERIC = gnode{node_Method_mod{NODE}, "Method_mod", [GEN_IS_PUBLIC, GEN_IS_PROTECTED, GEN_IS_PRIVATE, GEN_IS_STATIC, GEN_IS_ABSTRACT, GEN_IS_FINAL]}.

to_generic (node_Formal_parameter{NODE}, GENERIC) :-
	NODE = formal_parameter { _, TYPE, IS_REF, VAR } ,
	to_node (any{TYPE}, NODE_TYPE),
	to_generic (NODE_TYPE, GEN_TYPE),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{VAR}, NODE_VAR),
	to_generic (NODE_VAR, GEN_VAR),
	GENERIC = gnode{node_Formal_parameter{NODE}, "Formal_parameter", [GEN_TYPE, GEN_IS_REF, GEN_VAR]}.

to_generic (node_Type{NODE}, GENERIC) :-
	NODE = t_type { _, OPT_CLASS_NAME } ,
	((OPT_CLASS_NAME = yes{CLASS_NAME},
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	GEN_OPT_CLASS_NAME = gmaybe{"CLASS_NAME", yes{GEN_CLASS_NAME}})
	;
	(OPT_CLASS_NAME \= yes{_},
	GEN_OPT_CLASS_NAME = gmaybe{"CLASS_NAME", no})),
	GENERIC = gnode{node_Type{NODE}, "Type", [GEN_OPT_CLASS_NAME]}.

to_generic (node_Attribute{NODE}, GENERIC) :-
	NODE = attribute { _, ATTR_MOD, VARSS } ,
	to_node (any{ATTR_MOD}, NODE_ATTR_MOD),
	to_generic (NODE_ATTR_MOD, GEN_ATTR_MOD),
	list_to_generic_list ("Name_with_default", VARSS, GEN_VARSS),
	GENERIC = gnode{node_Attribute{NODE}, "Attribute", [GEN_ATTR_MOD, GEN_VARSS]}.

to_generic (node_Attr_mod{NODE}, GENERIC) :-
	NODE = attr_mod { _, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_CONST } ,
	GEN_IS_PUBLIC = gmarker {"is_public", IS_PUBLIC},
	GEN_IS_PROTECTED = gmarker {"is_protected", IS_PROTECTED},
	GEN_IS_PRIVATE = gmarker {"is_private", IS_PRIVATE},
	GEN_IS_STATIC = gmarker {"is_static", IS_STATIC},
	GEN_IS_CONST = gmarker {"is_const", IS_CONST},
	GENERIC = gnode{node_Attr_mod{NODE}, "Attr_mod", [GEN_IS_PUBLIC, GEN_IS_PROTECTED, GEN_IS_PRIVATE, GEN_IS_STATIC, GEN_IS_CONST]}.

to_generic (node_Name_with_default{NODE}, GENERIC) :-
	NODE = name_with_default { _, VARIABLE_NAME, OPT_EXPR } ,
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	((OPT_EXPR = yes{EXPR},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GEN_OPT_EXPR = gmaybe{"Expr", yes{GEN_EXPR}})
	;
	(OPT_EXPR \= yes{_},
	GEN_OPT_EXPR = gmaybe{"Expr", no})),
	GENERIC = gnode{node_Name_with_default{NODE}, "Name_with_default", [GEN_VARIABLE_NAME, GEN_OPT_EXPR]}.

to_generic (node_If{NODE}, GENERIC) :-
	NODE = if { _, EXPR, IFTRUES, IFFALSES } ,
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	list_to_generic_list ("Statement", IFTRUES, GEN_IFTRUES),
	list_to_generic_list ("Statement", IFFALSES, GEN_IFFALSES),
	GENERIC = gnode{node_If{NODE}, "If", [GEN_EXPR, GEN_IFTRUES, GEN_IFFALSES]}.

to_generic (node_While{NODE}, GENERIC) :-
	NODE = while { _, EXPR, STATEMENTS } ,
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	list_to_generic_list ("Statement", STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{node_While{NODE}, "While", [GEN_EXPR, GEN_STATEMENTS]}.

to_generic (node_Do{NODE}, GENERIC) :-
	NODE = do { _, STATEMENTS, EXPR } ,
	list_to_generic_list ("Statement", STATEMENTS, GEN_STATEMENTS),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Do{NODE}, "Do", [GEN_STATEMENTS, GEN_EXPR]}.

to_generic (node_For{NODE}, GENERIC) :-
	NODE = for { _, OPT_INIT, OPT_COND, OPT_INCR, STATEMENTS } ,
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
	list_to_generic_list ("Statement", STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{node_For{NODE}, "For", [GEN_OPT_INIT, GEN_OPT_COND, GEN_OPT_INCR, GEN_STATEMENTS]}.

to_generic (node_Foreach{NODE}, GENERIC) :-
	NODE = foreach { _, EXPR, OPT_KEY, IS_REF, VAL, STATEMENTS } ,
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
	list_to_generic_list ("Statement", STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{node_Foreach{NODE}, "Foreach", [GEN_EXPR, GEN_OPT_KEY, GEN_IS_REF, GEN_VAL, GEN_STATEMENTS]}.

to_generic (node_Switch{NODE}, GENERIC) :-
	NODE = switch { _, EXPR, SWITCH_CASES } ,
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	list_to_generic_list ("Switch_case", SWITCH_CASES, GEN_SWITCH_CASES),
	GENERIC = gnode{node_Switch{NODE}, "Switch", [GEN_EXPR, GEN_SWITCH_CASES]}.

to_generic (node_Switch_case{NODE}, GENERIC) :-
	NODE = switch_case { _, OPT_EXPR, STATEMENTS } ,
	((OPT_EXPR = yes{EXPR},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GEN_OPT_EXPR = gmaybe{"Expr", yes{GEN_EXPR}})
	;
	(OPT_EXPR \= yes{_},
	GEN_OPT_EXPR = gmaybe{"Expr", no})),
	list_to_generic_list ("Statement", STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{node_Switch_case{NODE}, "Switch_case", [GEN_OPT_EXPR, GEN_STATEMENTS]}.

to_generic (node_Break{NODE}, GENERIC) :-
	NODE = break { _, OPT_EXPR } ,
	((OPT_EXPR = yes{EXPR},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GEN_OPT_EXPR = gmaybe{"Expr", yes{GEN_EXPR}})
	;
	(OPT_EXPR \= yes{_},
	GEN_OPT_EXPR = gmaybe{"Expr", no})),
	GENERIC = gnode{node_Break{NODE}, "Break", [GEN_OPT_EXPR]}.

to_generic (node_Continue{NODE}, GENERIC) :-
	NODE = continue { _, OPT_EXPR } ,
	((OPT_EXPR = yes{EXPR},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GEN_OPT_EXPR = gmaybe{"Expr", yes{GEN_EXPR}})
	;
	(OPT_EXPR \= yes{_},
	GEN_OPT_EXPR = gmaybe{"Expr", no})),
	GENERIC = gnode{node_Continue{NODE}, "Continue", [GEN_OPT_EXPR]}.

to_generic (node_Return{NODE}, GENERIC) :-
	NODE = return { _, OPT_EXPR } ,
	((OPT_EXPR = yes{EXPR},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GEN_OPT_EXPR = gmaybe{"Expr", yes{GEN_EXPR}})
	;
	(OPT_EXPR \= yes{_},
	GEN_OPT_EXPR = gmaybe{"Expr", no})),
	GENERIC = gnode{node_Return{NODE}, "Return", [GEN_OPT_EXPR]}.

to_generic (node_Static_declaration{NODE}, GENERIC) :-
	NODE = static_declaration { _, VARSS } ,
	list_to_generic_list ("Name_with_default", VARSS, GEN_VARSS),
	GENERIC = gnode{node_Static_declaration{NODE}, "Static_declaration", [GEN_VARSS]}.

to_generic (node_Global{NODE}, GENERIC) :-
	NODE = global { _, VARIABLE_NAMES } ,
	list_to_generic_list ("Variable_name", VARIABLE_NAMES, GEN_VARIABLE_NAMES),
	GENERIC = gnode{node_Global{NODE}, "Global", [GEN_VARIABLE_NAMES]}.

to_generic (node_Declare{NODE}, GENERIC) :-
	NODE = declare { _, DIRECTIVES, STATEMENTS } ,
	list_to_generic_list ("Directive", DIRECTIVES, GEN_DIRECTIVES),
	list_to_generic_list ("Statement", STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{node_Declare{NODE}, "Declare", [GEN_DIRECTIVES, GEN_STATEMENTS]}.

to_generic (node_Directive{NODE}, GENERIC) :-
	NODE = directive { _, DIRECTIVE_NAME, EXPR } ,
	to_node (any{DIRECTIVE_NAME}, NODE_DIRECTIVE_NAME),
	to_generic (NODE_DIRECTIVE_NAME, GEN_DIRECTIVE_NAME),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Directive{NODE}, "Directive", [GEN_DIRECTIVE_NAME, GEN_EXPR]}.

to_generic (node_Try{NODE}, GENERIC) :-
	NODE = try { _, STATEMENTS, CATCHESS } ,
	list_to_generic_list ("Statement", STATEMENTS, GEN_STATEMENTS),
	list_to_generic_list ("Catch", CATCHESS, GEN_CATCHESS),
	GENERIC = gnode{node_Try{NODE}, "Try", [GEN_STATEMENTS, GEN_CATCHESS]}.

to_generic (node_Catch{NODE}, GENERIC) :-
	NODE = catch { _, CLASS_NAME, VARIABLE_NAME, STATEMENTS } ,
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	list_to_generic_list ("Statement", STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{node_Catch{NODE}, "Catch", [GEN_CLASS_NAME, GEN_VARIABLE_NAME, GEN_STATEMENTS]}.

to_generic (node_Throw{NODE}, GENERIC) :-
	NODE = throw { _, EXPR } ,
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Throw{NODE}, "Throw", [GEN_EXPR]}.

to_generic (node_Eval_expr{NODE}, GENERIC) :-
	NODE = eval_expr { _, EXPR } ,
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Eval_expr{NODE}, "Eval_expr", [GEN_EXPR]}.

to_generic (node_Nop{NODE}, GENERIC) :-
	NODE = nop { _ } ,
	GENERIC = gnode{node_Nop{NODE}, "Nop", []}.

to_generic (node_Foreign_expr{NODE}, GENERIC) :-
	NODE = foreign_expr { _ } ,
	GENERIC = gnode{node_Foreign_expr{NODE}, "Foreign_expr", []}.

to_generic (node_Foreign_statement{NODE}, GENERIC) :-
	NODE = foreign_statement { _ } ,
	GENERIC = gnode{node_Foreign_statement{NODE}, "Foreign_statement", []}.

to_generic (node_Assignment{NODE}, GENERIC) :-
	NODE = assignment { _, VARIABLE, IS_REF, EXPR } ,
	to_node (any{VARIABLE}, NODE_VARIABLE),
	to_generic (NODE_VARIABLE, GEN_VARIABLE),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Assignment{NODE}, "Assignment", [GEN_VARIABLE, GEN_IS_REF, GEN_EXPR]}.

to_generic (node_Op_assignment{NODE}, GENERIC) :-
	NODE = op_assignment { _, VARIABLE, OP, EXPR } ,
	to_node (any{VARIABLE}, NODE_VARIABLE),
	to_generic (NODE_VARIABLE, GEN_VARIABLE),
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Op_assignment{NODE}, "Op_assignment", [GEN_VARIABLE, GEN_OP, GEN_EXPR]}.

to_generic (node_List_assignment{NODE}, GENERIC) :-
	NODE = list_assignment { _, LIST_ELEMENTS, EXPR } ,
	to_node (any{LIST_ELEMENTS}, NODE_LIST_ELEMENTS),
	to_generic (NODE_LIST_ELEMENTS, GEN_LIST_ELEMENTS),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_List_assignment{NODE}, "List_assignment", [GEN_LIST_ELEMENTS, GEN_EXPR]}.

to_generic (node_Nested_list_elements{NODE}, GENERIC) :-
	NODE = nested_list_elements { _, LIST_ELEMENTS } ,
	to_node (any{LIST_ELEMENTS}, NODE_LIST_ELEMENTS),
	to_generic (NODE_LIST_ELEMENTS, GEN_LIST_ELEMENTS),
	GENERIC = gnode{node_Nested_list_elements{NODE}, "Nested_list_elements", [GEN_LIST_ELEMENTS]}.

to_generic (node_Cast{NODE}, GENERIC) :-
	NODE = cast { _, CAST, EXPR } ,
	to_node (any{CAST}, NODE_CAST),
	to_generic (NODE_CAST, GEN_CAST),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Cast{NODE}, "Cast", [GEN_CAST, GEN_EXPR]}.

to_generic (node_Unary_op{NODE}, GENERIC) :-
	NODE = unary_op { _, OP, EXPR } ,
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Unary_op{NODE}, "Unary_op", [GEN_OP, GEN_EXPR]}.

to_generic (node_Bin_op{NODE}, GENERIC) :-
	NODE = bin_op { _, LEFT, OP, RIGHT } ,
	to_node (any{LEFT}, NODE_LEFT),
	to_generic (NODE_LEFT, GEN_LEFT),
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{RIGHT}, NODE_RIGHT),
	to_generic (NODE_RIGHT, GEN_RIGHT),
	GENERIC = gnode{node_Bin_op{NODE}, "Bin_op", [GEN_LEFT, GEN_OP, GEN_RIGHT]}.

to_generic (node_Conditional_expr{NODE}, GENERIC) :-
	NODE = conditional_expr { _, COND, IFTRUE, IFFALSE } ,
	to_node (any{COND}, NODE_COND),
	to_generic (NODE_COND, GEN_COND),
	to_node (any{IFTRUE}, NODE_IFTRUE),
	to_generic (NODE_IFTRUE, GEN_IFTRUE),
	to_node (any{IFFALSE}, NODE_IFFALSE),
	to_generic (NODE_IFFALSE, GEN_IFFALSE),
	GENERIC = gnode{node_Conditional_expr{NODE}, "Conditional_expr", [GEN_COND, GEN_IFTRUE, GEN_IFFALSE]}.

to_generic (node_Ignore_errors{NODE}, GENERIC) :-
	NODE = ignore_errors { _, EXPR } ,
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Ignore_errors{NODE}, "Ignore_errors", [GEN_EXPR]}.

to_generic (node_Constant{NODE}, GENERIC) :-
	NODE = constant { _, OPT_CLASS_NAME, CONSTANT_NAME } ,
	((OPT_CLASS_NAME = yes{CLASS_NAME},
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	GEN_OPT_CLASS_NAME = gmaybe{"CLASS_NAME", yes{GEN_CLASS_NAME}})
	;
	(OPT_CLASS_NAME \= yes{_},
	GEN_OPT_CLASS_NAME = gmaybe{"CLASS_NAME", no})),
	to_node (any{CONSTANT_NAME}, NODE_CONSTANT_NAME),
	to_generic (NODE_CONSTANT_NAME, GEN_CONSTANT_NAME),
	GENERIC = gnode{node_Constant{NODE}, "Constant", [GEN_OPT_CLASS_NAME, GEN_CONSTANT_NAME]}.

to_generic (node_Instanceof{NODE}, GENERIC) :-
	NODE = instanceof { _, EXPR, CLASS_NAME } ,
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	GENERIC = gnode{node_Instanceof{NODE}, "Instanceof", [GEN_EXPR, GEN_CLASS_NAME]}.

to_generic (node_Variable{NODE}, GENERIC) :-
	NODE = variable { _, OPT_TARGET, VARIABLE_NAME, ARRAY_INDICESS } ,
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
	GENERIC = gnode{node_Variable{NODE}, "Variable", [GEN_OPT_TARGET, GEN_VARIABLE_NAME, GEN_ARRAY_INDICESS]}.

to_generic (node_Reflection{NODE}, GENERIC) :-
	NODE = reflection { _, EXPR } ,
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Reflection{NODE}, "Reflection", [GEN_EXPR]}.

to_generic (node_Pre_op{NODE}, GENERIC) :-
	NODE = pre_op { _, OP, VARIABLE } ,
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{VARIABLE}, NODE_VARIABLE),
	to_generic (NODE_VARIABLE, GEN_VARIABLE),
	GENERIC = gnode{node_Pre_op{NODE}, "Pre_op", [GEN_OP, GEN_VARIABLE]}.

to_generic (node_Post_op{NODE}, GENERIC) :-
	NODE = post_op { _, VARIABLE, OP } ,
	to_node (any{VARIABLE}, NODE_VARIABLE),
	to_generic (NODE_VARIABLE, GEN_VARIABLE),
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	GENERIC = gnode{node_Post_op{NODE}, "Post_op", [GEN_VARIABLE, GEN_OP]}.

to_generic (node_Array{NODE}, GENERIC) :-
	NODE = array { _, ARRAY_ELEMS } ,
	list_to_generic_list ("Array_elem", ARRAY_ELEMS, GEN_ARRAY_ELEMS),
	GENERIC = gnode{node_Array{NODE}, "Array", [GEN_ARRAY_ELEMS]}.

to_generic (node_Array_elem{NODE}, GENERIC) :-
	NODE = array_elem { _, OPT_KEY, IS_REF, VAL } ,
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
	GENERIC = gnode{node_Array_elem{NODE}, "Array_elem", [GEN_OPT_KEY, GEN_IS_REF, GEN_VAL]}.

to_generic (node_Method_invocation{NODE}, GENERIC) :-
	NODE = method_invocation { _, OPT_TARGET, METHOD_NAME, ACTUAL_PARAMETERS } ,
	((OPT_TARGET = yes{TARGET},
	to_node (any{TARGET}, NODE_TARGET),
	to_generic (NODE_TARGET, GEN_TARGET),
	GEN_OPT_TARGET = gmaybe{"Target", yes{GEN_TARGET}})
	;
	(OPT_TARGET \= yes{_},
	GEN_OPT_TARGET = gmaybe{"Target", no})),
	to_node (any{METHOD_NAME}, NODE_METHOD_NAME),
	to_generic (NODE_METHOD_NAME, GEN_METHOD_NAME),
	list_to_generic_list ("Actual_parameter", ACTUAL_PARAMETERS, GEN_ACTUAL_PARAMETERS),
	GENERIC = gnode{node_Method_invocation{NODE}, "Method_invocation", [GEN_OPT_TARGET, GEN_METHOD_NAME, GEN_ACTUAL_PARAMETERS]}.

to_generic (node_Actual_parameter{NODE}, GENERIC) :-
	NODE = actual_parameter { _, IS_REF, EXPR } ,
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Actual_parameter{NODE}, "Actual_parameter", [GEN_IS_REF, GEN_EXPR]}.

to_generic (node_New{NODE}, GENERIC) :-
	NODE = new { _, CLASS_NAME, ACTUAL_PARAMETERS } ,
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	list_to_generic_list ("Actual_parameter", ACTUAL_PARAMETERS, GEN_ACTUAL_PARAMETERS),
	GENERIC = gnode{node_New{NODE}, "New", [GEN_CLASS_NAME, GEN_ACTUAL_PARAMETERS]}.



to_generic (node_CLASS_NAME{NODE}, GENERIC) :-
	NODE = cLASS_NAME { _, CLASS_NAME } ,
	GEN_CLASS_NAME = gstring {CLASS_NAME},
	GENERIC = gnode{node_CLASS_NAME{NODE}, "CLASS_NAME", [GEN_CLASS_NAME]}.

to_generic (node_INTERFACE_NAME{NODE}, GENERIC) :-
	NODE = iNTERFACE_NAME { _, INTERFACE_NAME } ,
	GEN_INTERFACE_NAME = gstring {INTERFACE_NAME},
	GENERIC = gnode{node_INTERFACE_NAME{NODE}, "INTERFACE_NAME", [GEN_INTERFACE_NAME]}.

to_generic (node_METHOD_NAME{NODE}, GENERIC) :-
	NODE = mETHOD_NAME { _, METHOD_NAME } ,
	GEN_METHOD_NAME = gstring {METHOD_NAME},
	GENERIC = gnode{node_METHOD_NAME{NODE}, "METHOD_NAME", [GEN_METHOD_NAME]}.

to_generic (node_VARIABLE_NAME{NODE}, GENERIC) :-
	NODE = vARIABLE_NAME { _, VARIABLE_NAME } ,
	GEN_VARIABLE_NAME = gstring {VARIABLE_NAME},
	GENERIC = gnode{node_VARIABLE_NAME{NODE}, "VARIABLE_NAME", [GEN_VARIABLE_NAME]}.

to_generic (node_DIRECTIVE_NAME{NODE}, GENERIC) :-
	NODE = dIRECTIVE_NAME { _, DIRECTIVE_NAME } ,
	GEN_DIRECTIVE_NAME = gstring {DIRECTIVE_NAME},
	GENERIC = gnode{node_DIRECTIVE_NAME{NODE}, "DIRECTIVE_NAME", [GEN_DIRECTIVE_NAME]}.

to_generic (node_INT{NODE}, GENERIC) :-
	NODE = iNT { _, INT } ,
	GEN_INT = gint {INT},
	GENERIC = gnode{node_INT{NODE}, "INT", [GEN_INT]}.

to_generic (node_REAL{NODE}, GENERIC) :-
	NODE = rEAL { _, REAL } ,
	GEN_REAL = gfloat {REAL},
	GENERIC = gnode{node_REAL{NODE}, "REAL", [GEN_REAL]}.

to_generic (node_STRING{NODE}, GENERIC) :-
	NODE = sTRING { _, STRING } ,
	GEN_STRING = gstring {STRING},
	GENERIC = gnode{node_STRING{NODE}, "STRING", [GEN_STRING]}.

to_generic (node_BOOL{NODE}, GENERIC) :-
	NODE = bOOL { _, BOOL } ,
	GEN_BOOL = gbool {BOOL},
	GENERIC = gnode{node_BOOL{NODE}, "BOOL", [GEN_BOOL]}.

to_generic (node_NIL{NODE}, GENERIC) :-
	NODE = nIL { _, NIL } ,
	GEN_NIL = gnull {NIL},
	GENERIC = gnode{node_NIL{NODE}, "NIL", [GEN_NIL]}.

to_generic (node_OP{NODE}, GENERIC) :-
	NODE = oP { _, OP } ,
	GEN_OP = gstring {OP},
	GENERIC = gnode{node_OP{NODE}, "OP", [GEN_OP]}.

to_generic (node_CAST{NODE}, GENERIC) :-
	NODE = cAST { _, CAST } ,
	GEN_CAST = gstring {CAST},
	GENERIC = gnode{node_CAST{NODE}, "CAST", [GEN_CAST]}.

to_generic (node_CONSTANT_NAME{NODE}, GENERIC) :-
	NODE = cONSTANT_NAME { _, CONSTANT_NAME } ,
	GEN_CONSTANT_NAME = gstring {CONSTANT_NAME},
	GENERIC = gnode{node_CONSTANT_NAME{NODE}, "CONSTANT_NAME", [GEN_CONSTANT_NAME]}.



