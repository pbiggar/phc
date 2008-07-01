import "src/analyse/base.clp".

session mir ().

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
type t_Return.
type t_Static_declaration.
type t_Global.
type t_Try.
type t_Catch.
type t_Throw.
type t_Assign_var.
type t_Assign_target.
type t_Assign_array.
type t_Assign_var_var.
type t_Push_array.
type t_Pre_op.
type t_Eval_expr.
type t_Target_expr.
type t_Variable.
type t_Variable_variable.
type t_Index_array.
type t_Cast.
type t_Unary_op.
type t_Bin_op.
type t_Constant.
type t_Instanceof.
type t_Reflection.
type t_Method_invocation.
type t_Actual_parameter.
type t_New.
type t_Static_array.
type t_Static_array_elem.
type t_Branch.
type t_Goto.
type t_Label.
type t_Foreach_reset.
type t_Foreach_next.
type t_Foreach_end.
type t_Foreach_has_key.
type t_Foreach_get_key.
type t_Foreach_get_val.
type t_Foreign_statement.
type t_Foreign_expr.


type t_Node.
type t_Statement.
type t_Member.
type t_Expr.
type t_Literal.
type t_Variable_name.
type t_Target.
type t_Method_name.
type t_Class_name.
type t_Static_value.
type t_Static_array_key.
type t_Identifier.
type t_Foreign.



% Token declarations
type t_HT_ITERATOR ::= hT_ITERATOR { ID:id, VALUE:int }.
type t_CLASS_NAME ::= cLASS_NAME { ID:id, VALUE:string }.
type t_INTERFACE_NAME ::= iNTERFACE_NAME { ID:id, VALUE:string }.
type t_METHOD_NAME ::= mETHOD_NAME { ID:id, VALUE:string }.
type t_VARIABLE_NAME ::= vARIABLE_NAME { ID:id, VALUE:string }.
type t_OP ::= oP { ID:id, VALUE:string }.
type t_INT ::= iNT { ID:id, VALUE:int }.
type t_REAL ::= rEAL { ID:id, VALUE:float }.
type t_STRING ::= sTRING { ID:id, VALUE:string }.
type t_BOOL ::= bOOL { ID:id, VALUE:bool }.
type t_NIL ::= nIL { ID:id, VALUE:null }.
type t_CAST ::= cAST { ID:id, VALUE:string }.
type t_CONSTANT_NAME ::= cONSTANT_NAME { ID:id, VALUE:string }.
type t_LABEL_NAME ::= lABEL_NAME { ID:id, VALUE:string }.



% Types
type t_PHP_script ::= pHP_script { ID:id, STATEMENTS:list[t_Statement] }.
type t_Class_def ::= class_def { ID:id, CLASS_MOD:t_Class_mod, CLASS_NAME:t_CLASS_NAME, OPT_EXTENDS:maybe[t_CLASS_NAME], IMPLEMENTSS:list[t_INTERFACE_NAME], MEMBERS:list[t_Member] }.
type t_Class_mod ::= class_mod { ID:id, IS_ABSTRACT:bool, IS_FINAL:bool }.
type t_Interface_def ::= interface_def { ID:id, INTERFACE_NAME:t_INTERFACE_NAME, EXTENDSS:list[t_INTERFACE_NAME], MEMBERS:list[t_Member] }.
type t_Method ::= method { ID:id, SIGNATURE:t_Signature, OPT_STATEMENTS:maybe[list[t_Statement]] }.
type t_Signature ::= signature { ID:id, METHOD_MOD:t_Method_mod, IS_REF:bool, METHOD_NAME:t_METHOD_NAME, FORMAL_PARAMETERS:list[t_Formal_parameter] }.
type t_Method_mod ::= method_mod { ID:id, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_ABSTRACT:bool, IS_FINAL:bool }.
type t_Formal_parameter ::= formal_parameter { ID:id, TYPE:t_Type, IS_REF:bool, VAR:t_Name_with_default }.
type t_Type ::= c_type { ID:id, OPT_CLASS_NAME:maybe[t_CLASS_NAME] }.
type t_Attribute ::= attribute { ID:id, ATTR_MOD:t_Attr_mod, VAR:t_Name_with_default }.
type t_Attr_mod ::= attr_mod { ID:id, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_CONST:bool }.
type t_Name_with_default ::= name_with_default { ID:id, VARIABLE_NAME:t_VARIABLE_NAME, OPT_DEFAULT_VALUE:maybe[t_Static_value] }.
type t_Return ::= return { ID:id, EXPR:t_Expr }.
type t_Static_declaration ::= static_declaration { ID:id, VAR:t_Name_with_default }.
type t_Global ::= global { ID:id, VARIABLE_NAME:t_Variable_name }.
type t_Try ::= try { ID:id, STATEMENTS:list[t_Statement], CATCHESS:list[t_Catch] }.
type t_Catch ::= catch { ID:id, CLASS_NAME:t_CLASS_NAME, VARIABLE_NAME:t_VARIABLE_NAME, STATEMENTS:list[t_Statement] }.
type t_Throw ::= throw { ID:id, VARIABLE_NAME:t_VARIABLE_NAME }.
type t_Assign_var ::= assign_var { ID:id, LHS:t_VARIABLE_NAME, IS_REF:bool, RHS:t_Expr }.
type t_Assign_target ::= assign_target { ID:id, TARGET:t_Target, LHS:t_Variable_name, IS_REF:bool, RHS:t_VARIABLE_NAME }.
type t_Assign_array ::= assign_array { ID:id, LHS:t_VARIABLE_NAME, INDEX:t_VARIABLE_NAME, IS_REF:bool, RHS:t_VARIABLE_NAME }.
type t_Assign_var_var ::= assign_var_var { ID:id, LHS:t_VARIABLE_NAME, IS_REF:bool, RHS:t_VARIABLE_NAME }.
type t_Push_array ::= push_array { ID:id, LHS:t_VARIABLE_NAME, IS_REF:bool, RHS:t_VARIABLE_NAME }.
type t_Pre_op ::= pre_op { ID:id, OP:t_OP, VARIABLE_NAME:t_VARIABLE_NAME }.
type t_Eval_expr ::= eval_expr { ID:id, EXPR:t_Expr }.
type t_Target_expr ::= target_expr { ID:id, TARGET:t_Target, VARIABLE_NAME:t_Variable_name }.
type t_Variable ::= variable { ID:id, VARIABLE_NAME:t_VARIABLE_NAME }.
type t_Variable_variable ::= variable_variable { ID:id, VARIABLE_NAME:t_VARIABLE_NAME }.
type t_Index_array ::= index_array { ID:id, VARIABLE_NAME:t_VARIABLE_NAME, INDEX:t_VARIABLE_NAME }.
type t_Cast ::= cast { ID:id, CAST:t_CAST, VARIABLE_NAME:t_VARIABLE_NAME }.
type t_Unary_op ::= unary_op { ID:id, OP:t_OP, VARIABLE_NAME:t_VARIABLE_NAME }.
type t_Bin_op ::= bin_op { ID:id, LEFT:t_VARIABLE_NAME, OP:t_OP, RIGHT:t_VARIABLE_NAME }.
type t_Constant ::= constant { ID:id, OPT_CLASS_NAME:maybe[t_CLASS_NAME], CONSTANT_NAME:t_CONSTANT_NAME }.
type t_Instanceof ::= instanceof { ID:id, VARIABLE_NAME:t_VARIABLE_NAME, CLASS_NAME:t_Class_name }.
type t_Reflection ::= reflection { ID:id, VARIABLE_NAME:t_VARIABLE_NAME }.
type t_Method_invocation ::= method_invocation { ID:id, OPT_TARGET:maybe[t_Target], METHOD_NAME:t_Method_name, ACTUAL_PARAMETERS:list[t_Actual_parameter] }.
type t_Actual_parameter ::= actual_parameter { ID:id, IS_REF:bool, OPT_TARGET:maybe[t_Target], VARIABLE_NAME:t_Variable_name, ARRAY_INDICESS:list[t_VARIABLE_NAME] }.
type t_New ::= new { ID:id, CLASS_NAME:t_Class_name, ACTUAL_PARAMETERS:list[t_Actual_parameter] }.
type t_Static_array ::= static_array { ID:id, STATIC_ARRAY_ELEMS:list[t_Static_array_elem] }.
type t_Static_array_elem ::= static_array_elem { ID:id, OPT_KEY:maybe[t_Static_array_key], IS_REF:bool, VAL:t_Static_value }.
type t_Branch ::= branch { ID:id, VARIABLE_NAME:t_VARIABLE_NAME, IFTRUE:t_LABEL_NAME, IFFALSE:t_LABEL_NAME }.
type t_Goto ::= goto { ID:id, LABEL_NAME:t_LABEL_NAME }.
type t_Label ::= label { ID:id, LABEL_NAME:t_LABEL_NAME }.
type t_Foreach_reset ::= foreach_reset { ID:id, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR }.
type t_Foreach_next ::= foreach_next { ID:id, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR }.
type t_Foreach_end ::= foreach_end { ID:id, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR }.
type t_Foreach_has_key ::= foreach_has_key { ID:id, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR }.
type t_Foreach_get_key ::= foreach_get_key { ID:id, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR }.
type t_Foreach_get_val ::= foreach_get_val { ID:id, ARRAY:t_VARIABLE_NAME, KEY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR }.
type t_Foreign_statement ::= foreign_statement { ID:id }.
type t_Foreign_expr ::= foreign_expr { ID:id }.


type t_Foreign ::= 
		  foreign_Foreign_statement { t_Foreign_statement } 
		| foreign_Foreign_expr { t_Foreign_expr } 
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
		.
type t_Static_array_key ::= 
		  static_array_key_INT { t_INT } 
		| static_array_key_REAL { t_REAL } 
		| static_array_key_STRING { t_STRING } 
		| static_array_key_BOOL { t_BOOL } 
		| static_array_key_NIL { t_NIL } 
		| static_array_key_Constant { t_Constant } 
		.
type t_Static_value ::= 
		  static_value_INT { t_INT } 
		| static_value_REAL { t_REAL } 
		| static_value_STRING { t_STRING } 
		| static_value_BOOL { t_BOOL } 
		| static_value_NIL { t_NIL } 
		| static_value_Static_array { t_Static_array } 
		| static_value_Constant { t_Constant } 
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
		  target_VARIABLE_NAME { t_VARIABLE_NAME } 
		| target_CLASS_NAME { t_CLASS_NAME } 
		.
type t_Variable_name ::= 
		  variable_name_VARIABLE_NAME { t_VARIABLE_NAME } 
		| variable_name_Reflection { t_Reflection } 
		.
type t_Literal ::= 
		  literal_INT { t_INT } 
		| literal_REAL { t_REAL } 
		| literal_STRING { t_STRING } 
		| literal_BOOL { t_BOOL } 
		| literal_NIL { t_NIL } 
		.
type t_Expr ::= 
		  expr_Cast { t_Cast } 
		| expr_Unary_op { t_Unary_op } 
		| expr_Bin_op { t_Bin_op } 
		| expr_Constant { t_Constant } 
		| expr_Instanceof { t_Instanceof } 
		| expr_Method_invocation { t_Method_invocation } 
		| expr_New { t_New } 
		| expr_INT { t_INT } 
		| expr_REAL { t_REAL } 
		| expr_STRING { t_STRING } 
		| expr_BOOL { t_BOOL } 
		| expr_NIL { t_NIL } 
		| expr_Foreach_has_key { t_Foreach_has_key } 
		| expr_Foreach_get_key { t_Foreach_get_key } 
		| expr_Foreach_get_val { t_Foreach_get_val } 
		| expr_Foreign_expr { t_Foreign_expr } 
		| expr_Variable { t_Variable } 
		| expr_Index_array { t_Index_array } 
		| expr_Variable_variable { t_Variable_variable } 
		| expr_Target_expr { t_Target_expr } 
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
		| statement_Label { t_Label } 
		| statement_Goto { t_Goto } 
		| statement_Branch { t_Branch } 
		| statement_Foreach_next { t_Foreach_next } 
		| statement_Foreach_reset { t_Foreach_reset } 
		| statement_Foreach_end { t_Foreach_end } 
		| statement_Assign_var { t_Assign_var } 
		| statement_Assign_var_var { t_Assign_var_var } 
		| statement_Assign_array { t_Assign_array } 
		| statement_Push_array { t_Push_array } 
		| statement_Assign_target { t_Assign_target } 
		| statement_Eval_expr { t_Eval_expr } 
		| statement_Pre_op { t_Pre_op } 
		| statement_Foreign_statement { t_Foreign_statement } 
		.
type t_Node ::= 
		  node_PHP_script { t_PHP_script } 
		| node_Class_def { t_Class_def } 
		| node_Interface_def { t_Interface_def } 
		| node_Method { t_Method } 
		| node_Return { t_Return } 
		| node_Static_declaration { t_Static_declaration } 
		| node_Global { t_Global } 
		| node_Try { t_Try } 
		| node_Throw { t_Throw } 
		| node_Label { t_Label } 
		| node_Goto { t_Goto } 
		| node_Branch { t_Branch } 
		| node_Foreach_next { t_Foreach_next } 
		| node_Foreach_reset { t_Foreach_reset } 
		| node_Foreach_end { t_Foreach_end } 
		| node_Assign_var { t_Assign_var } 
		| node_Assign_var_var { t_Assign_var_var } 
		| node_Assign_array { t_Assign_array } 
		| node_Push_array { t_Push_array } 
		| node_Assign_target { t_Assign_target } 
		| node_Eval_expr { t_Eval_expr } 
		| node_Pre_op { t_Pre_op } 
		| node_Foreign_statement { t_Foreign_statement } 
		| node_Class_mod { t_Class_mod } 
		| node_Attribute { t_Attribute } 
		| node_Signature { t_Signature } 
		| node_Method_mod { t_Method_mod } 
		| node_Formal_parameter { t_Formal_parameter } 
		| node_Type { t_Type } 
		| node_Attr_mod { t_Attr_mod } 
		| node_Name_with_default { t_Name_with_default } 
		| node_Catch { t_Catch } 
		| node_Cast { t_Cast } 
		| node_Unary_op { t_Unary_op } 
		| node_Bin_op { t_Bin_op } 
		| node_Constant { t_Constant } 
		| node_Instanceof { t_Instanceof } 
		| node_Method_invocation { t_Method_invocation } 
		| node_New { t_New } 
		| node_INT { t_INT } 
		| node_REAL { t_REAL } 
		| node_STRING { t_STRING } 
		| node_BOOL { t_BOOL } 
		| node_NIL { t_NIL } 
		| node_Foreach_has_key { t_Foreach_has_key } 
		| node_Foreach_get_key { t_Foreach_get_key } 
		| node_Foreach_get_val { t_Foreach_get_val } 
		| node_Foreign_expr { t_Foreign_expr } 
		| node_Variable { t_Variable } 
		| node_Index_array { t_Index_array } 
		| node_Variable_variable { t_Variable_variable } 
		| node_Target_expr { t_Target_expr } 
		| node_VARIABLE_NAME { t_VARIABLE_NAME } 
		| node_Reflection { t_Reflection } 
		| node_CLASS_NAME { t_CLASS_NAME } 
		| node_METHOD_NAME { t_METHOD_NAME } 
		| node_Actual_parameter { t_Actual_parameter } 
		| node_Static_array { t_Static_array } 
		| node_Static_array_elem { t_Static_array_elem } 
		| node_INTERFACE_NAME { t_INTERFACE_NAME } 
		| node_CAST { t_CAST } 
		| node_OP { t_OP } 
		| node_CONSTANT_NAME { t_CONSTANT_NAME } 
		| node_LABEL_NAME { t_LABEL_NAME } 
		| node_HT_ITERATOR { t_HT_ITERATOR } 
		.




% Generics

to_node (any{pHP_script{ID, STATEMENTS}},
	node_PHP_script{pHP_script{ID, STATEMENTS}}) :- .
get_id (node_PHP_script{pHP_script{ID, STATEMENTS}}, ID) :- .

to_node (any{class_def{ID, CLASS_MOD, CLASS_NAME, OPT_EXTENDS, IMPLEMENTSS, MEMBERS}},
	node_Class_def{class_def{ID, CLASS_MOD, CLASS_NAME, OPT_EXTENDS, IMPLEMENTSS, MEMBERS}}) :- .
get_id (node_Class_def{class_def{ID, CLASS_MOD, CLASS_NAME, OPT_EXTENDS, IMPLEMENTSS, MEMBERS}}, ID) :- .

to_node (any{class_mod{ID, IS_ABSTRACT, IS_FINAL}},
	node_Class_mod{class_mod{ID, IS_ABSTRACT, IS_FINAL}}) :- .
get_id (node_Class_mod{class_mod{ID, IS_ABSTRACT, IS_FINAL}}, ID) :- .

to_node (any{interface_def{ID, INTERFACE_NAME, EXTENDSS, MEMBERS}},
	node_Interface_def{interface_def{ID, INTERFACE_NAME, EXTENDSS, MEMBERS}}) :- .
get_id (node_Interface_def{interface_def{ID, INTERFACE_NAME, EXTENDSS, MEMBERS}}, ID) :- .

to_node (any{method{ID, SIGNATURE, OPT_STATEMENTS}},
	node_Method{method{ID, SIGNATURE, OPT_STATEMENTS}}) :- .
get_id (node_Method{method{ID, SIGNATURE, OPT_STATEMENTS}}, ID) :- .

to_node (any{signature{ID, METHOD_MOD, IS_REF, METHOD_NAME, FORMAL_PARAMETERS}},
	node_Signature{signature{ID, METHOD_MOD, IS_REF, METHOD_NAME, FORMAL_PARAMETERS}}) :- .
get_id (node_Signature{signature{ID, METHOD_MOD, IS_REF, METHOD_NAME, FORMAL_PARAMETERS}}, ID) :- .

to_node (any{method_mod{ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_ABSTRACT, IS_FINAL}},
	node_Method_mod{method_mod{ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_ABSTRACT, IS_FINAL}}) :- .
get_id (node_Method_mod{method_mod{ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_ABSTRACT, IS_FINAL}}, ID) :- .

to_node (any{formal_parameter{ID, TYPE, IS_REF, VAR}},
	node_Formal_parameter{formal_parameter{ID, TYPE, IS_REF, VAR}}) :- .
get_id (node_Formal_parameter{formal_parameter{ID, TYPE, IS_REF, VAR}}, ID) :- .

to_node (any{c_type{ID, OPT_CLASS_NAME}},
	node_Type{c_type{ID, OPT_CLASS_NAME}}) :- .
get_id (node_Type{c_type{ID, OPT_CLASS_NAME}}, ID) :- .

to_node (any{attribute{ID, ATTR_MOD, VAR}},
	node_Attribute{attribute{ID, ATTR_MOD, VAR}}) :- .
get_id (node_Attribute{attribute{ID, ATTR_MOD, VAR}}, ID) :- .

to_node (any{attr_mod{ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_CONST}},
	node_Attr_mod{attr_mod{ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_CONST}}) :- .
get_id (node_Attr_mod{attr_mod{ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_CONST}}, ID) :- .

to_node (any{name_with_default{ID, VARIABLE_NAME, OPT_DEFAULT_VALUE}},
	node_Name_with_default{name_with_default{ID, VARIABLE_NAME, OPT_DEFAULT_VALUE}}) :- .
get_id (node_Name_with_default{name_with_default{ID, VARIABLE_NAME, OPT_DEFAULT_VALUE}}, ID) :- .

to_node (any{return{ID, EXPR}},
	node_Return{return{ID, EXPR}}) :- .
get_id (node_Return{return{ID, EXPR}}, ID) :- .

to_node (any{static_declaration{ID, VAR}},
	node_Static_declaration{static_declaration{ID, VAR}}) :- .
get_id (node_Static_declaration{static_declaration{ID, VAR}}, ID) :- .

to_node (any{global{ID, VARIABLE_NAME}},
	node_Global{global{ID, VARIABLE_NAME}}) :- .
get_id (node_Global{global{ID, VARIABLE_NAME}}, ID) :- .

to_node (any{try{ID, STATEMENTS, CATCHESS}},
	node_Try{try{ID, STATEMENTS, CATCHESS}}) :- .
get_id (node_Try{try{ID, STATEMENTS, CATCHESS}}, ID) :- .

to_node (any{catch{ID, CLASS_NAME, VARIABLE_NAME, STATEMENTS}},
	node_Catch{catch{ID, CLASS_NAME, VARIABLE_NAME, STATEMENTS}}) :- .
get_id (node_Catch{catch{ID, CLASS_NAME, VARIABLE_NAME, STATEMENTS}}, ID) :- .

to_node (any{throw{ID, VARIABLE_NAME}},
	node_Throw{throw{ID, VARIABLE_NAME}}) :- .
get_id (node_Throw{throw{ID, VARIABLE_NAME}}, ID) :- .

to_node (any{assign_var{ID, LHS, IS_REF, RHS}},
	node_Assign_var{assign_var{ID, LHS, IS_REF, RHS}}) :- .
get_id (node_Assign_var{assign_var{ID, LHS, IS_REF, RHS}}, ID) :- .

to_node (any{assign_target{ID, TARGET, LHS, IS_REF, RHS}},
	node_Assign_target{assign_target{ID, TARGET, LHS, IS_REF, RHS}}) :- .
get_id (node_Assign_target{assign_target{ID, TARGET, LHS, IS_REF, RHS}}, ID) :- .

to_node (any{assign_array{ID, LHS, INDEX, IS_REF, RHS}},
	node_Assign_array{assign_array{ID, LHS, INDEX, IS_REF, RHS}}) :- .
get_id (node_Assign_array{assign_array{ID, LHS, INDEX, IS_REF, RHS}}, ID) :- .

to_node (any{assign_var_var{ID, LHS, IS_REF, RHS}},
	node_Assign_var_var{assign_var_var{ID, LHS, IS_REF, RHS}}) :- .
get_id (node_Assign_var_var{assign_var_var{ID, LHS, IS_REF, RHS}}, ID) :- .

to_node (any{push_array{ID, LHS, IS_REF, RHS}},
	node_Push_array{push_array{ID, LHS, IS_REF, RHS}}) :- .
get_id (node_Push_array{push_array{ID, LHS, IS_REF, RHS}}, ID) :- .

to_node (any{pre_op{ID, OP, VARIABLE_NAME}},
	node_Pre_op{pre_op{ID, OP, VARIABLE_NAME}}) :- .
get_id (node_Pre_op{pre_op{ID, OP, VARIABLE_NAME}}, ID) :- .

to_node (any{eval_expr{ID, EXPR}},
	node_Eval_expr{eval_expr{ID, EXPR}}) :- .
get_id (node_Eval_expr{eval_expr{ID, EXPR}}, ID) :- .

to_node (any{target_expr{ID, TARGET, VARIABLE_NAME}},
	node_Target_expr{target_expr{ID, TARGET, VARIABLE_NAME}}) :- .
get_id (node_Target_expr{target_expr{ID, TARGET, VARIABLE_NAME}}, ID) :- .

to_node (any{variable{ID, VARIABLE_NAME}},
	node_Variable{variable{ID, VARIABLE_NAME}}) :- .
get_id (node_Variable{variable{ID, VARIABLE_NAME}}, ID) :- .

to_node (any{variable_variable{ID, VARIABLE_NAME}},
	node_Variable_variable{variable_variable{ID, VARIABLE_NAME}}) :- .
get_id (node_Variable_variable{variable_variable{ID, VARIABLE_NAME}}, ID) :- .

to_node (any{index_array{ID, VARIABLE_NAME, INDEX}},
	node_Index_array{index_array{ID, VARIABLE_NAME, INDEX}}) :- .
get_id (node_Index_array{index_array{ID, VARIABLE_NAME, INDEX}}, ID) :- .

to_node (any{cast{ID, CAST, VARIABLE_NAME}},
	node_Cast{cast{ID, CAST, VARIABLE_NAME}}) :- .
get_id (node_Cast{cast{ID, CAST, VARIABLE_NAME}}, ID) :- .

to_node (any{unary_op{ID, OP, VARIABLE_NAME}},
	node_Unary_op{unary_op{ID, OP, VARIABLE_NAME}}) :- .
get_id (node_Unary_op{unary_op{ID, OP, VARIABLE_NAME}}, ID) :- .

to_node (any{bin_op{ID, LEFT, OP, RIGHT}},
	node_Bin_op{bin_op{ID, LEFT, OP, RIGHT}}) :- .
get_id (node_Bin_op{bin_op{ID, LEFT, OP, RIGHT}}, ID) :- .

to_node (any{constant{ID, OPT_CLASS_NAME, CONSTANT_NAME}},
	node_Constant{constant{ID, OPT_CLASS_NAME, CONSTANT_NAME}}) :- .
get_id (node_Constant{constant{ID, OPT_CLASS_NAME, CONSTANT_NAME}}, ID) :- .

to_node (any{instanceof{ID, VARIABLE_NAME, CLASS_NAME}},
	node_Instanceof{instanceof{ID, VARIABLE_NAME, CLASS_NAME}}) :- .
get_id (node_Instanceof{instanceof{ID, VARIABLE_NAME, CLASS_NAME}}, ID) :- .

to_node (any{reflection{ID, VARIABLE_NAME}},
	node_Reflection{reflection{ID, VARIABLE_NAME}}) :- .
get_id (node_Reflection{reflection{ID, VARIABLE_NAME}}, ID) :- .

to_node (any{method_invocation{ID, OPT_TARGET, METHOD_NAME, ACTUAL_PARAMETERS}},
	node_Method_invocation{method_invocation{ID, OPT_TARGET, METHOD_NAME, ACTUAL_PARAMETERS}}) :- .
get_id (node_Method_invocation{method_invocation{ID, OPT_TARGET, METHOD_NAME, ACTUAL_PARAMETERS}}, ID) :- .

to_node (any{actual_parameter{ID, IS_REF, OPT_TARGET, VARIABLE_NAME, ARRAY_INDICESS}},
	node_Actual_parameter{actual_parameter{ID, IS_REF, OPT_TARGET, VARIABLE_NAME, ARRAY_INDICESS}}) :- .
get_id (node_Actual_parameter{actual_parameter{ID, IS_REF, OPT_TARGET, VARIABLE_NAME, ARRAY_INDICESS}}, ID) :- .

to_node (any{new{ID, CLASS_NAME, ACTUAL_PARAMETERS}},
	node_New{new{ID, CLASS_NAME, ACTUAL_PARAMETERS}}) :- .
get_id (node_New{new{ID, CLASS_NAME, ACTUAL_PARAMETERS}}, ID) :- .

to_node (any{static_array{ID, STATIC_ARRAY_ELEMS}},
	node_Static_array{static_array{ID, STATIC_ARRAY_ELEMS}}) :- .
get_id (node_Static_array{static_array{ID, STATIC_ARRAY_ELEMS}}, ID) :- .

to_node (any{static_array_elem{ID, OPT_KEY, IS_REF, VAL}},
	node_Static_array_elem{static_array_elem{ID, OPT_KEY, IS_REF, VAL}}) :- .
get_id (node_Static_array_elem{static_array_elem{ID, OPT_KEY, IS_REF, VAL}}, ID) :- .

to_node (any{branch{ID, VARIABLE_NAME, IFTRUE, IFFALSE}},
	node_Branch{branch{ID, VARIABLE_NAME, IFTRUE, IFFALSE}}) :- .
get_id (node_Branch{branch{ID, VARIABLE_NAME, IFTRUE, IFFALSE}}, ID) :- .

to_node (any{goto{ID, LABEL_NAME}},
	node_Goto{goto{ID, LABEL_NAME}}) :- .
get_id (node_Goto{goto{ID, LABEL_NAME}}, ID) :- .

to_node (any{label{ID, LABEL_NAME}},
	node_Label{label{ID, LABEL_NAME}}) :- .
get_id (node_Label{label{ID, LABEL_NAME}}, ID) :- .

to_node (any{foreach_reset{ID, ARRAY, ITER}},
	node_Foreach_reset{foreach_reset{ID, ARRAY, ITER}}) :- .
get_id (node_Foreach_reset{foreach_reset{ID, ARRAY, ITER}}, ID) :- .

to_node (any{foreach_next{ID, ARRAY, ITER}},
	node_Foreach_next{foreach_next{ID, ARRAY, ITER}}) :- .
get_id (node_Foreach_next{foreach_next{ID, ARRAY, ITER}}, ID) :- .

to_node (any{foreach_end{ID, ARRAY, ITER}},
	node_Foreach_end{foreach_end{ID, ARRAY, ITER}}) :- .
get_id (node_Foreach_end{foreach_end{ID, ARRAY, ITER}}, ID) :- .

to_node (any{foreach_has_key{ID, ARRAY, ITER}},
	node_Foreach_has_key{foreach_has_key{ID, ARRAY, ITER}}) :- .
get_id (node_Foreach_has_key{foreach_has_key{ID, ARRAY, ITER}}, ID) :- .

to_node (any{foreach_get_key{ID, ARRAY, ITER}},
	node_Foreach_get_key{foreach_get_key{ID, ARRAY, ITER}}) :- .
get_id (node_Foreach_get_key{foreach_get_key{ID, ARRAY, ITER}}, ID) :- .

to_node (any{foreach_get_val{ID, ARRAY, KEY, ITER}},
	node_Foreach_get_val{foreach_get_val{ID, ARRAY, KEY, ITER}}) :- .
get_id (node_Foreach_get_val{foreach_get_val{ID, ARRAY, KEY, ITER}}, ID) :- .

to_node (any{foreign_statement{ID}},
	node_Foreign_statement{foreign_statement{ID}}) :- .
get_id (node_Foreign_statement{foreign_statement{ID}}, ID) :- .

to_node (any{foreign_expr{ID}},
	node_Foreign_expr{foreign_expr{ID}}) :- .
get_id (node_Foreign_expr{foreign_expr{ID}}, ID) :- .




to_node (any{statement_Class_def{ID}}, node_Class_def{ID}) :- .
to_node (any{statement_Interface_def{ID}}, node_Interface_def{ID}) :- .
to_node (any{statement_Method{ID}}, node_Method{ID}) :- .
to_node (any{statement_Return{ID}}, node_Return{ID}) :- .
to_node (any{statement_Static_declaration{ID}}, node_Static_declaration{ID}) :- .
to_node (any{statement_Global{ID}}, node_Global{ID}) :- .
to_node (any{statement_Try{ID}}, node_Try{ID}) :- .
to_node (any{statement_Throw{ID}}, node_Throw{ID}) :- .
to_node (any{statement_Label{ID}}, node_Label{ID}) :- .
to_node (any{statement_Goto{ID}}, node_Goto{ID}) :- .
to_node (any{statement_Branch{ID}}, node_Branch{ID}) :- .
to_node (any{statement_Foreach_next{ID}}, node_Foreach_next{ID}) :- .
to_node (any{statement_Foreach_reset{ID}}, node_Foreach_reset{ID}) :- .
to_node (any{statement_Foreach_end{ID}}, node_Foreach_end{ID}) :- .
to_node (any{statement_Assign_var{ID}}, node_Assign_var{ID}) :- .
to_node (any{statement_Assign_var_var{ID}}, node_Assign_var_var{ID}) :- .
to_node (any{statement_Assign_array{ID}}, node_Assign_array{ID}) :- .
to_node (any{statement_Push_array{ID}}, node_Push_array{ID}) :- .
to_node (any{statement_Assign_target{ID}}, node_Assign_target{ID}) :- .
to_node (any{statement_Eval_expr{ID}}, node_Eval_expr{ID}) :- .
to_node (any{statement_Pre_op{ID}}, node_Pre_op{ID}) :- .
to_node (any{statement_Foreign_statement{ID}}, node_Foreign_statement{ID}) :- .
to_node (any{member_Method{ID}}, node_Method{ID}) :- .
to_node (any{member_Attribute{ID}}, node_Attribute{ID}) :- .
to_node (any{expr_Cast{ID}}, node_Cast{ID}) :- .
to_node (any{expr_Unary_op{ID}}, node_Unary_op{ID}) :- .
to_node (any{expr_Bin_op{ID}}, node_Bin_op{ID}) :- .
to_node (any{expr_Constant{ID}}, node_Constant{ID}) :- .
to_node (any{expr_Instanceof{ID}}, node_Instanceof{ID}) :- .
to_node (any{expr_Method_invocation{ID}}, node_Method_invocation{ID}) :- .
to_node (any{expr_New{ID}}, node_New{ID}) :- .
to_node (any{expr_INT{ID}}, node_INT{ID}) :- .
to_node (any{expr_REAL{ID}}, node_REAL{ID}) :- .
to_node (any{expr_STRING{ID}}, node_STRING{ID}) :- .
to_node (any{expr_BOOL{ID}}, node_BOOL{ID}) :- .
to_node (any{expr_NIL{ID}}, node_NIL{ID}) :- .
to_node (any{expr_Foreach_has_key{ID}}, node_Foreach_has_key{ID}) :- .
to_node (any{expr_Foreach_get_key{ID}}, node_Foreach_get_key{ID}) :- .
to_node (any{expr_Foreach_get_val{ID}}, node_Foreach_get_val{ID}) :- .
to_node (any{expr_Foreign_expr{ID}}, node_Foreign_expr{ID}) :- .
to_node (any{expr_Variable{ID}}, node_Variable{ID}) :- .
to_node (any{expr_Index_array{ID}}, node_Index_array{ID}) :- .
to_node (any{expr_Variable_variable{ID}}, node_Variable_variable{ID}) :- .
to_node (any{expr_Target_expr{ID}}, node_Target_expr{ID}) :- .
to_node (any{literal_INT{ID}}, node_INT{ID}) :- .
to_node (any{literal_REAL{ID}}, node_REAL{ID}) :- .
to_node (any{literal_STRING{ID}}, node_STRING{ID}) :- .
to_node (any{literal_BOOL{ID}}, node_BOOL{ID}) :- .
to_node (any{literal_NIL{ID}}, node_NIL{ID}) :- .
to_node (any{variable_name_VARIABLE_NAME{ID}}, node_VARIABLE_NAME{ID}) :- .
to_node (any{variable_name_Reflection{ID}}, node_Reflection{ID}) :- .
to_node (any{target_VARIABLE_NAME{ID}}, node_VARIABLE_NAME{ID}) :- .
to_node (any{target_CLASS_NAME{ID}}, node_CLASS_NAME{ID}) :- .
to_node (any{method_name_METHOD_NAME{ID}}, node_METHOD_NAME{ID}) :- .
to_node (any{method_name_Reflection{ID}}, node_Reflection{ID}) :- .
to_node (any{class_name_CLASS_NAME{ID}}, node_CLASS_NAME{ID}) :- .
to_node (any{class_name_Reflection{ID}}, node_Reflection{ID}) :- .
to_node (any{static_value_INT{ID}}, node_INT{ID}) :- .
to_node (any{static_value_REAL{ID}}, node_REAL{ID}) :- .
to_node (any{static_value_STRING{ID}}, node_STRING{ID}) :- .
to_node (any{static_value_BOOL{ID}}, node_BOOL{ID}) :- .
to_node (any{static_value_NIL{ID}}, node_NIL{ID}) :- .
to_node (any{static_value_Static_array{ID}}, node_Static_array{ID}) :- .
to_node (any{static_value_Constant{ID}}, node_Constant{ID}) :- .
to_node (any{static_array_key_INT{ID}}, node_INT{ID}) :- .
to_node (any{static_array_key_REAL{ID}}, node_REAL{ID}) :- .
to_node (any{static_array_key_STRING{ID}}, node_STRING{ID}) :- .
to_node (any{static_array_key_BOOL{ID}}, node_BOOL{ID}) :- .
to_node (any{static_array_key_NIL{ID}}, node_NIL{ID}) :- .
to_node (any{static_array_key_Constant{ID}}, node_Constant{ID}) :- .
to_node (any{identifier_INTERFACE_NAME{ID}}, node_INTERFACE_NAME{ID}) :- .
to_node (any{identifier_CLASS_NAME{ID}}, node_CLASS_NAME{ID}) :- .
to_node (any{identifier_METHOD_NAME{ID}}, node_METHOD_NAME{ID}) :- .
to_node (any{identifier_VARIABLE_NAME{ID}}, node_VARIABLE_NAME{ID}) :- .
to_node (any{identifier_CAST{ID}}, node_CAST{ID}) :- .
to_node (any{identifier_OP{ID}}, node_OP{ID}) :- .
to_node (any{identifier_CONSTANT_NAME{ID}}, node_CONSTANT_NAME{ID}) :- .
to_node (any{identifier_LABEL_NAME{ID}}, node_LABEL_NAME{ID}) :- .
to_node (any{foreign_Foreign_statement{ID}}, node_Foreign_statement{ID}) :- .
to_node (any{foreign_Foreign_expr{ID}}, node_Foreign_expr{ID}) :- .


to_node (any{hT_ITERATOR{ID, VALUE}}, node_HT_ITERATOR{hT_ITERATOR{ID, VALUE}}) :- .
get_id (node_HT_ITERATOR{hT_ITERATOR{ID, _}}, ID) :- .

to_node (any{cLASS_NAME{ID, VALUE}}, node_CLASS_NAME{cLASS_NAME{ID, VALUE}}) :- .
get_id (node_CLASS_NAME{cLASS_NAME{ID, _}}, ID) :- .

to_node (any{iNTERFACE_NAME{ID, VALUE}}, node_INTERFACE_NAME{iNTERFACE_NAME{ID, VALUE}}) :- .
get_id (node_INTERFACE_NAME{iNTERFACE_NAME{ID, _}}, ID) :- .

to_node (any{mETHOD_NAME{ID, VALUE}}, node_METHOD_NAME{mETHOD_NAME{ID, VALUE}}) :- .
get_id (node_METHOD_NAME{mETHOD_NAME{ID, _}}, ID) :- .

to_node (any{vARIABLE_NAME{ID, VALUE}}, node_VARIABLE_NAME{vARIABLE_NAME{ID, VALUE}}) :- .
get_id (node_VARIABLE_NAME{vARIABLE_NAME{ID, _}}, ID) :- .

to_node (any{oP{ID, VALUE}}, node_OP{oP{ID, VALUE}}) :- .
get_id (node_OP{oP{ID, _}}, ID) :- .

to_node (any{iNT{ID, VALUE}}, node_INT{iNT{ID, VALUE}}) :- .
get_id (node_INT{iNT{ID, _}}, ID) :- .

to_node (any{rEAL{ID, VALUE}}, node_REAL{rEAL{ID, VALUE}}) :- .
get_id (node_REAL{rEAL{ID, _}}, ID) :- .

to_node (any{sTRING{ID, VALUE}}, node_STRING{sTRING{ID, VALUE}}) :- .
get_id (node_STRING{sTRING{ID, _}}, ID) :- .

to_node (any{bOOL{ID, VALUE}}, node_BOOL{bOOL{ID, VALUE}}) :- .
get_id (node_BOOL{bOOL{ID, _}}, ID) :- .

to_node (any{nIL{ID, VALUE}}, node_NIL{nIL{ID, VALUE}}) :- .
get_id (node_NIL{nIL{ID, _}}, ID) :- .

to_node (any{cAST{ID, VALUE}}, node_CAST{cAST{ID, VALUE}}) :- .
get_id (node_CAST{cAST{ID, _}}, ID) :- .

to_node (any{cONSTANT_NAME{ID, VALUE}}, node_CONSTANT_NAME{cONSTANT_NAME{ID, VALUE}}) :- .
get_id (node_CONSTANT_NAME{cONSTANT_NAME{ID, _}}, ID) :- .

to_node (any{lABEL_NAME{ID, VALUE}}, node_LABEL_NAME{lABEL_NAME{ID, VALUE}}) :- .
get_id (node_LABEL_NAME{lABEL_NAME{ID, _}}, ID) :- .




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
	NODE = c_type { _, OPT_CLASS_NAME } ,
	((OPT_CLASS_NAME = yes{CLASS_NAME},
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	GEN_OPT_CLASS_NAME = gmaybe{"CLASS_NAME", yes{GEN_CLASS_NAME}})
	;
	(OPT_CLASS_NAME \= yes{_},
	GEN_OPT_CLASS_NAME = gmaybe{"CLASS_NAME", no})),
	GENERIC = gnode{node_Type{NODE}, "Type", [GEN_OPT_CLASS_NAME]}.

to_generic (node_Attribute{NODE}, GENERIC) :-
	NODE = attribute { _, ATTR_MOD, VAR } ,
	to_node (any{ATTR_MOD}, NODE_ATTR_MOD),
	to_generic (NODE_ATTR_MOD, GEN_ATTR_MOD),
	to_node (any{VAR}, NODE_VAR),
	to_generic (NODE_VAR, GEN_VAR),
	GENERIC = gnode{node_Attribute{NODE}, "Attribute", [GEN_ATTR_MOD, GEN_VAR]}.

to_generic (node_Attr_mod{NODE}, GENERIC) :-
	NODE = attr_mod { _, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_CONST } ,
	GEN_IS_PUBLIC = gmarker {"is_public", IS_PUBLIC},
	GEN_IS_PROTECTED = gmarker {"is_protected", IS_PROTECTED},
	GEN_IS_PRIVATE = gmarker {"is_private", IS_PRIVATE},
	GEN_IS_STATIC = gmarker {"is_static", IS_STATIC},
	GEN_IS_CONST = gmarker {"is_const", IS_CONST},
	GENERIC = gnode{node_Attr_mod{NODE}, "Attr_mod", [GEN_IS_PUBLIC, GEN_IS_PROTECTED, GEN_IS_PRIVATE, GEN_IS_STATIC, GEN_IS_CONST]}.

to_generic (node_Name_with_default{NODE}, GENERIC) :-
	NODE = name_with_default { _, VARIABLE_NAME, OPT_DEFAULT_VALUE } ,
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	((OPT_DEFAULT_VALUE = yes{DEFAULT_VALUE},
	to_node (any{DEFAULT_VALUE}, NODE_DEFAULT_VALUE),
	to_generic (NODE_DEFAULT_VALUE, GEN_DEFAULT_VALUE),
	GEN_OPT_DEFAULT_VALUE = gmaybe{"Static_value", yes{GEN_DEFAULT_VALUE}})
	;
	(OPT_DEFAULT_VALUE \= yes{_},
	GEN_OPT_DEFAULT_VALUE = gmaybe{"Static_value", no})),
	GENERIC = gnode{node_Name_with_default{NODE}, "Name_with_default", [GEN_VARIABLE_NAME, GEN_OPT_DEFAULT_VALUE]}.

to_generic (node_Return{NODE}, GENERIC) :-
	NODE = return { _, EXPR } ,
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Return{NODE}, "Return", [GEN_EXPR]}.

to_generic (node_Static_declaration{NODE}, GENERIC) :-
	NODE = static_declaration { _, VAR } ,
	to_node (any{VAR}, NODE_VAR),
	to_generic (NODE_VAR, GEN_VAR),
	GENERIC = gnode{node_Static_declaration{NODE}, "Static_declaration", [GEN_VAR]}.

to_generic (node_Global{NODE}, GENERIC) :-
	NODE = global { _, VARIABLE_NAME } ,
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{node_Global{NODE}, "Global", [GEN_VARIABLE_NAME]}.

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
	NODE = throw { _, VARIABLE_NAME } ,
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{node_Throw{NODE}, "Throw", [GEN_VARIABLE_NAME]}.

to_generic (node_Assign_var{NODE}, GENERIC) :-
	NODE = assign_var { _, LHS, IS_REF, RHS } ,
	to_node (any{LHS}, NODE_LHS),
	to_generic (NODE_LHS, GEN_LHS),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{RHS}, NODE_RHS),
	to_generic (NODE_RHS, GEN_RHS),
	GENERIC = gnode{node_Assign_var{NODE}, "Assign_var", [GEN_LHS, GEN_IS_REF, GEN_RHS]}.

to_generic (node_Assign_target{NODE}, GENERIC) :-
	NODE = assign_target { _, TARGET, LHS, IS_REF, RHS } ,
	to_node (any{TARGET}, NODE_TARGET),
	to_generic (NODE_TARGET, GEN_TARGET),
	to_node (any{LHS}, NODE_LHS),
	to_generic (NODE_LHS, GEN_LHS),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{RHS}, NODE_RHS),
	to_generic (NODE_RHS, GEN_RHS),
	GENERIC = gnode{node_Assign_target{NODE}, "Assign_target", [GEN_TARGET, GEN_LHS, GEN_IS_REF, GEN_RHS]}.

to_generic (node_Assign_array{NODE}, GENERIC) :-
	NODE = assign_array { _, LHS, INDEX, IS_REF, RHS } ,
	to_node (any{LHS}, NODE_LHS),
	to_generic (NODE_LHS, GEN_LHS),
	to_node (any{INDEX}, NODE_INDEX),
	to_generic (NODE_INDEX, GEN_INDEX),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{RHS}, NODE_RHS),
	to_generic (NODE_RHS, GEN_RHS),
	GENERIC = gnode{node_Assign_array{NODE}, "Assign_array", [GEN_LHS, GEN_INDEX, GEN_IS_REF, GEN_RHS]}.

to_generic (node_Assign_var_var{NODE}, GENERIC) :-
	NODE = assign_var_var { _, LHS, IS_REF, RHS } ,
	to_node (any{LHS}, NODE_LHS),
	to_generic (NODE_LHS, GEN_LHS),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{RHS}, NODE_RHS),
	to_generic (NODE_RHS, GEN_RHS),
	GENERIC = gnode{node_Assign_var_var{NODE}, "Assign_var_var", [GEN_LHS, GEN_IS_REF, GEN_RHS]}.

to_generic (node_Push_array{NODE}, GENERIC) :-
	NODE = push_array { _, LHS, IS_REF, RHS } ,
	to_node (any{LHS}, NODE_LHS),
	to_generic (NODE_LHS, GEN_LHS),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{RHS}, NODE_RHS),
	to_generic (NODE_RHS, GEN_RHS),
	GENERIC = gnode{node_Push_array{NODE}, "Push_array", [GEN_LHS, GEN_IS_REF, GEN_RHS]}.

to_generic (node_Pre_op{NODE}, GENERIC) :-
	NODE = pre_op { _, OP, VARIABLE_NAME } ,
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{node_Pre_op{NODE}, "Pre_op", [GEN_OP, GEN_VARIABLE_NAME]}.

to_generic (node_Eval_expr{NODE}, GENERIC) :-
	NODE = eval_expr { _, EXPR } ,
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{node_Eval_expr{NODE}, "Eval_expr", [GEN_EXPR]}.

to_generic (node_Target_expr{NODE}, GENERIC) :-
	NODE = target_expr { _, TARGET, VARIABLE_NAME } ,
	to_node (any{TARGET}, NODE_TARGET),
	to_generic (NODE_TARGET, GEN_TARGET),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{node_Target_expr{NODE}, "Target_expr", [GEN_TARGET, GEN_VARIABLE_NAME]}.

to_generic (node_Variable{NODE}, GENERIC) :-
	NODE = variable { _, VARIABLE_NAME } ,
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{node_Variable{NODE}, "Variable", [GEN_VARIABLE_NAME]}.

to_generic (node_Variable_variable{NODE}, GENERIC) :-
	NODE = variable_variable { _, VARIABLE_NAME } ,
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{node_Variable_variable{NODE}, "Variable_variable", [GEN_VARIABLE_NAME]}.

to_generic (node_Index_array{NODE}, GENERIC) :-
	NODE = index_array { _, VARIABLE_NAME, INDEX } ,
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	to_node (any{INDEX}, NODE_INDEX),
	to_generic (NODE_INDEX, GEN_INDEX),
	GENERIC = gnode{node_Index_array{NODE}, "Index_array", [GEN_VARIABLE_NAME, GEN_INDEX]}.

to_generic (node_Cast{NODE}, GENERIC) :-
	NODE = cast { _, CAST, VARIABLE_NAME } ,
	to_node (any{CAST}, NODE_CAST),
	to_generic (NODE_CAST, GEN_CAST),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{node_Cast{NODE}, "Cast", [GEN_CAST, GEN_VARIABLE_NAME]}.

to_generic (node_Unary_op{NODE}, GENERIC) :-
	NODE = unary_op { _, OP, VARIABLE_NAME } ,
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{node_Unary_op{NODE}, "Unary_op", [GEN_OP, GEN_VARIABLE_NAME]}.

to_generic (node_Bin_op{NODE}, GENERIC) :-
	NODE = bin_op { _, LEFT, OP, RIGHT } ,
	to_node (any{LEFT}, NODE_LEFT),
	to_generic (NODE_LEFT, GEN_LEFT),
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{RIGHT}, NODE_RIGHT),
	to_generic (NODE_RIGHT, GEN_RIGHT),
	GENERIC = gnode{node_Bin_op{NODE}, "Bin_op", [GEN_LEFT, GEN_OP, GEN_RIGHT]}.

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
	NODE = instanceof { _, VARIABLE_NAME, CLASS_NAME } ,
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	GENERIC = gnode{node_Instanceof{NODE}, "Instanceof", [GEN_VARIABLE_NAME, GEN_CLASS_NAME]}.

to_generic (node_Reflection{NODE}, GENERIC) :-
	NODE = reflection { _, VARIABLE_NAME } ,
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{node_Reflection{NODE}, "Reflection", [GEN_VARIABLE_NAME]}.

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
	NODE = actual_parameter { _, IS_REF, OPT_TARGET, VARIABLE_NAME, ARRAY_INDICESS } ,
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	((OPT_TARGET = yes{TARGET},
	to_node (any{TARGET}, NODE_TARGET),
	to_generic (NODE_TARGET, GEN_TARGET),
	GEN_OPT_TARGET = gmaybe{"Target", yes{GEN_TARGET}})
	;
	(OPT_TARGET \= yes{_},
	GEN_OPT_TARGET = gmaybe{"Target", no})),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	list_to_generic_list ("VARIABLE_NAME", ARRAY_INDICESS, GEN_ARRAY_INDICESS),
	GENERIC = gnode{node_Actual_parameter{NODE}, "Actual_parameter", [GEN_IS_REF, GEN_OPT_TARGET, GEN_VARIABLE_NAME, GEN_ARRAY_INDICESS]}.

to_generic (node_New{NODE}, GENERIC) :-
	NODE = new { _, CLASS_NAME, ACTUAL_PARAMETERS } ,
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	list_to_generic_list ("Actual_parameter", ACTUAL_PARAMETERS, GEN_ACTUAL_PARAMETERS),
	GENERIC = gnode{node_New{NODE}, "New", [GEN_CLASS_NAME, GEN_ACTUAL_PARAMETERS]}.

to_generic (node_Static_array{NODE}, GENERIC) :-
	NODE = static_array { _, STATIC_ARRAY_ELEMS } ,
	list_to_generic_list ("Static_array_elem", STATIC_ARRAY_ELEMS, GEN_STATIC_ARRAY_ELEMS),
	GENERIC = gnode{node_Static_array{NODE}, "Static_array", [GEN_STATIC_ARRAY_ELEMS]}.

to_generic (node_Static_array_elem{NODE}, GENERIC) :-
	NODE = static_array_elem { _, OPT_KEY, IS_REF, VAL } ,
	((OPT_KEY = yes{KEY},
	to_node (any{KEY}, NODE_KEY),
	to_generic (NODE_KEY, GEN_KEY),
	GEN_OPT_KEY = gmaybe{"Static_array_key", yes{GEN_KEY}})
	;
	(OPT_KEY \= yes{_},
	GEN_OPT_KEY = gmaybe{"Static_array_key", no})),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{VAL}, NODE_VAL),
	to_generic (NODE_VAL, GEN_VAL),
	GENERIC = gnode{node_Static_array_elem{NODE}, "Static_array_elem", [GEN_OPT_KEY, GEN_IS_REF, GEN_VAL]}.

to_generic (node_Branch{NODE}, GENERIC) :-
	NODE = branch { _, VARIABLE_NAME, IFTRUE, IFFALSE } ,
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	to_node (any{IFTRUE}, NODE_IFTRUE),
	to_generic (NODE_IFTRUE, GEN_IFTRUE),
	to_node (any{IFFALSE}, NODE_IFFALSE),
	to_generic (NODE_IFFALSE, GEN_IFFALSE),
	GENERIC = gnode{node_Branch{NODE}, "Branch", [GEN_VARIABLE_NAME, GEN_IFTRUE, GEN_IFFALSE]}.

to_generic (node_Goto{NODE}, GENERIC) :-
	NODE = goto { _, LABEL_NAME } ,
	to_node (any{LABEL_NAME}, NODE_LABEL_NAME),
	to_generic (NODE_LABEL_NAME, GEN_LABEL_NAME),
	GENERIC = gnode{node_Goto{NODE}, "Goto", [GEN_LABEL_NAME]}.

to_generic (node_Label{NODE}, GENERIC) :-
	NODE = label { _, LABEL_NAME } ,
	to_node (any{LABEL_NAME}, NODE_LABEL_NAME),
	to_generic (NODE_LABEL_NAME, GEN_LABEL_NAME),
	GENERIC = gnode{node_Label{NODE}, "Label", [GEN_LABEL_NAME]}.

to_generic (node_Foreach_reset{NODE}, GENERIC) :-
	NODE = foreach_reset { _, ARRAY, ITER } ,
	to_node (any{ARRAY}, NODE_ARRAY),
	to_generic (NODE_ARRAY, GEN_ARRAY),
	to_node (any{ITER}, NODE_ITER),
	to_generic (NODE_ITER, GEN_ITER),
	GENERIC = gnode{node_Foreach_reset{NODE}, "Foreach_reset", [GEN_ARRAY, GEN_ITER]}.

to_generic (node_Foreach_next{NODE}, GENERIC) :-
	NODE = foreach_next { _, ARRAY, ITER } ,
	to_node (any{ARRAY}, NODE_ARRAY),
	to_generic (NODE_ARRAY, GEN_ARRAY),
	to_node (any{ITER}, NODE_ITER),
	to_generic (NODE_ITER, GEN_ITER),
	GENERIC = gnode{node_Foreach_next{NODE}, "Foreach_next", [GEN_ARRAY, GEN_ITER]}.

to_generic (node_Foreach_end{NODE}, GENERIC) :-
	NODE = foreach_end { _, ARRAY, ITER } ,
	to_node (any{ARRAY}, NODE_ARRAY),
	to_generic (NODE_ARRAY, GEN_ARRAY),
	to_node (any{ITER}, NODE_ITER),
	to_generic (NODE_ITER, GEN_ITER),
	GENERIC = gnode{node_Foreach_end{NODE}, "Foreach_end", [GEN_ARRAY, GEN_ITER]}.

to_generic (node_Foreach_has_key{NODE}, GENERIC) :-
	NODE = foreach_has_key { _, ARRAY, ITER } ,
	to_node (any{ARRAY}, NODE_ARRAY),
	to_generic (NODE_ARRAY, GEN_ARRAY),
	to_node (any{ITER}, NODE_ITER),
	to_generic (NODE_ITER, GEN_ITER),
	GENERIC = gnode{node_Foreach_has_key{NODE}, "Foreach_has_key", [GEN_ARRAY, GEN_ITER]}.

to_generic (node_Foreach_get_key{NODE}, GENERIC) :-
	NODE = foreach_get_key { _, ARRAY, ITER } ,
	to_node (any{ARRAY}, NODE_ARRAY),
	to_generic (NODE_ARRAY, GEN_ARRAY),
	to_node (any{ITER}, NODE_ITER),
	to_generic (NODE_ITER, GEN_ITER),
	GENERIC = gnode{node_Foreach_get_key{NODE}, "Foreach_get_key", [GEN_ARRAY, GEN_ITER]}.

to_generic (node_Foreach_get_val{NODE}, GENERIC) :-
	NODE = foreach_get_val { _, ARRAY, KEY, ITER } ,
	to_node (any{ARRAY}, NODE_ARRAY),
	to_generic (NODE_ARRAY, GEN_ARRAY),
	to_node (any{KEY}, NODE_KEY),
	to_generic (NODE_KEY, GEN_KEY),
	to_node (any{ITER}, NODE_ITER),
	to_generic (NODE_ITER, GEN_ITER),
	GENERIC = gnode{node_Foreach_get_val{NODE}, "Foreach_get_val", [GEN_ARRAY, GEN_KEY, GEN_ITER]}.

to_generic (node_Foreign_statement{NODE}, GENERIC) :-
	NODE = foreign_statement { _ } ,
	GENERIC = gnode{node_Foreign_statement{NODE}, "Foreign_statement", []}.

to_generic (node_Foreign_expr{NODE}, GENERIC) :-
	NODE = foreign_expr { _ } ,
	GENERIC = gnode{node_Foreign_expr{NODE}, "Foreign_expr", []}.



to_generic (node_HT_ITERATOR{NODE}, GENERIC) :-
	NODE = hT_ITERATOR { _, HT_ITERATOR } ,
	GEN_HT_ITERATOR = gint {HT_ITERATOR},
	GENERIC = gnode{node_HT_ITERATOR{NODE}, "HT_ITERATOR", [GEN_HT_ITERATOR]}.

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

to_generic (node_OP{NODE}, GENERIC) :-
	NODE = oP { _, OP } ,
	GEN_OP = gstring {OP},
	GENERIC = gnode{node_OP{NODE}, "OP", [GEN_OP]}.

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

to_generic (node_CAST{NODE}, GENERIC) :-
	NODE = cAST { _, CAST } ,
	GEN_CAST = gstring {CAST},
	GENERIC = gnode{node_CAST{NODE}, "CAST", [GEN_CAST]}.

to_generic (node_CONSTANT_NAME{NODE}, GENERIC) :-
	NODE = cONSTANT_NAME { _, CONSTANT_NAME } ,
	GEN_CONSTANT_NAME = gstring {CONSTANT_NAME},
	GENERIC = gnode{node_CONSTANT_NAME{NODE}, "CONSTANT_NAME", [GEN_CONSTANT_NAME]}.

to_generic (node_LABEL_NAME{NODE}, GENERIC) :-
	NODE = lABEL_NAME { _, LABEL_NAME } ,
	GEN_LABEL_NAME = gstring {LABEL_NAME},
	GENERIC = gnode{node_LABEL_NAME{NODE}, "LABEL_NAME", [GEN_LABEL_NAME]}.



