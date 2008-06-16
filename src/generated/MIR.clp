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
type t_Assign_array.
type t_Assign_var_var.
type t_Push_array.
type t_Eval_expr.
type t_Cast.
type t_Unary_op.
type t_Bin_op.
type t_Constant.
type t_Instanceof.
type t_Variable.
type t_Reflection.
type t_Pre_op.
type t_Array.
type t_Array_elem.
type t_Method_invocation.
type t_Actual_parameter.
type t_New.
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
type t_Identifier.
type t_Foreign.



% Token declarations
type t_HT_ITERATOR ::= hT_ITERATOR_id { id }.
type t_CLASS_NAME ::= cLASS_NAME_id { id }.
type t_INTERFACE_NAME ::= iNTERFACE_NAME_id { id }.
type t_METHOD_NAME ::= mETHOD_NAME_id { id }.
type t_VARIABLE_NAME ::= vARIABLE_NAME_id { id }.
type t_INT ::= iNT_id { id }.
type t_REAL ::= rEAL_id { id }.
type t_STRING ::= sTRING_id { id }.
type t_BOOL ::= bOOL_id { id }.
type t_NIL ::= nIL_id { id }.
type t_CAST ::= cAST_id { id }.
type t_OP ::= oP_id { id }.
type t_CONSTANT_NAME ::= cONSTANT_NAME_id { id }.
type t_LABEL_NAME ::= lABEL_NAME_id { id }.



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
type t_Return ::= return_id { id }.
type t_Static_declaration ::= static_declaration_id { id }.
type t_Global ::= global_id { id }.
type t_Try ::= try_id { id }.
type t_Catch ::= catch_id { id }.
type t_Throw ::= throw_id { id }.
type t_Assign_var ::= assign_var_id { id }.
type t_Assign_array ::= assign_array_id { id }.
type t_Assign_var_var ::= assign_var_var_id { id }.
type t_Push_array ::= push_array_id { id }.
type t_Eval_expr ::= eval_expr_id { id }.
type t_Cast ::= cast_id { id }.
type t_Unary_op ::= unary_op_id { id }.
type t_Bin_op ::= bin_op_id { id }.
type t_Constant ::= constant_id { id }.
type t_Instanceof ::= instanceof_id { id }.
type t_Variable ::= variable_id { id }.
type t_Reflection ::= reflection_id { id }.
type t_Pre_op ::= pre_op_id { id }.
type t_Array ::= array_id { id }.
type t_Array_elem ::= array_elem_id { id }.
type t_Method_invocation ::= method_invocation_id { id }.
type t_Actual_parameter ::= actual_parameter_id { id }.
type t_New ::= new_id { id }.
type t_Branch ::= branch_id { id }.
type t_Goto ::= goto_id { id }.
type t_Label ::= label_id { id }.
type t_Foreach_reset ::= foreach_reset_id { id }.
type t_Foreach_next ::= foreach_next_id { id }.
type t_Foreach_end ::= foreach_end_id { id }.
type t_Foreach_has_key ::= foreach_has_key_id { id }.
type t_Foreach_get_key ::= foreach_get_key_id { id }.
type t_Foreach_get_val ::= foreach_get_val_id { id }.
type t_Foreign_statement ::= foreign_statement_id { id }.
type t_Foreign_expr ::= foreign_expr_id { id }.


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
type t_Class_name ::= 
		  class_name_CLASS_NAME { t_CLASS_NAME } 
		| class_name_Reflection { t_Reflection } 
		.
type t_Method_name ::= 
		  method_name_METHOD_NAME { t_METHOD_NAME } 
		| method_name_Reflection { t_Reflection } 
		.
type t_Target ::= 
		  target_Cast { t_Cast } 
		| target_Unary_op { t_Unary_op } 
		| target_Bin_op { t_Bin_op } 
		| target_Constant { t_Constant } 
		| target_Instanceof { t_Instanceof } 
		| target_Variable { t_Variable } 
		| target_Method_invocation { t_Method_invocation } 
		| target_New { t_New } 
		| target_INT { t_INT } 
		| target_REAL { t_REAL } 
		| target_STRING { t_STRING } 
		| target_BOOL { t_BOOL } 
		| target_NIL { t_NIL } 
		| target_Array { t_Array } 
		| target_Foreach_has_key { t_Foreach_has_key } 
		| target_Foreach_get_key { t_Foreach_get_key } 
		| target_Foreach_get_val { t_Foreach_get_val } 
		| target_Foreign_expr { t_Foreign_expr } 
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
		| expr_Variable { t_Variable } 
		| expr_Method_invocation { t_Method_invocation } 
		| expr_New { t_New } 
		| expr_INT { t_INT } 
		| expr_REAL { t_REAL } 
		| expr_STRING { t_STRING } 
		| expr_BOOL { t_BOOL } 
		| expr_NIL { t_NIL } 
		| expr_Array { t_Array } 
		| expr_Foreach_has_key { t_Foreach_has_key } 
		| expr_Foreach_get_key { t_Foreach_get_key } 
		| expr_Foreach_get_val { t_Foreach_get_val } 
		| expr_Foreign_expr { t_Foreign_expr } 
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
		| node_VARIABLE_NAME { t_VARIABLE_NAME } 
		| node_Reflection { t_Reflection } 
		| node_Cast { t_Cast } 
		| node_Unary_op { t_Unary_op } 
		| node_Bin_op { t_Bin_op } 
		| node_Constant { t_Constant } 
		| node_Instanceof { t_Instanceof } 
		| node_Variable { t_Variable } 
		| node_Method_invocation { t_Method_invocation } 
		| node_New { t_New } 
		| node_INT { t_INT } 
		| node_REAL { t_REAL } 
		| node_STRING { t_STRING } 
		| node_BOOL { t_BOOL } 
		| node_NIL { t_NIL } 
		| node_Array { t_Array } 
		| node_Foreach_has_key { t_Foreach_has_key } 
		| node_Foreach_get_key { t_Foreach_get_key } 
		| node_Foreach_get_val { t_Foreach_get_val } 
		| node_Foreign_expr { t_Foreign_expr } 
		| node_CLASS_NAME { t_CLASS_NAME } 
		| node_Array_elem { t_Array_elem } 
		| node_METHOD_NAME { t_METHOD_NAME } 
		| node_Actual_parameter { t_Actual_parameter } 
		| node_INTERFACE_NAME { t_INTERFACE_NAME } 
		| node_CAST { t_CAST } 
		| node_OP { t_OP } 
		| node_CONSTANT_NAME { t_CONSTANT_NAME } 
		| node_LABEL_NAME { t_LABEL_NAME } 
		| node_HT_ITERATOR { t_HT_ITERATOR } 
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
predicate attribute (ID:t_Attribute, ATTR_MOD:t_Attr_mod, VAR:t_Name_with_default).
predicate attr_mod (ID:t_Attr_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_CONST:bool).
predicate name_with_default (ID:t_Name_with_default, VARIABLE_NAME:t_VARIABLE_NAME, OPT_EXPR:maybe[t_Expr]).
predicate return (ID:t_Return, EXPR:t_Expr).
predicate static_declaration (ID:t_Static_declaration, VAR:t_Name_with_default).
predicate global (ID:t_Global, VARIABLE_NAME:t_Variable_name).
predicate try (ID:t_Try, STATEMENTS:list[t_Statement], CATCHESS:list[t_Catch]).
predicate catch (ID:t_Catch, CLASS_NAME:t_CLASS_NAME, VARIABLE_NAME:t_VARIABLE_NAME, STATEMENTS:list[t_Statement]).
predicate throw (ID:t_Throw, EXPR:t_Expr).
predicate assign_var (ID:t_Assign_var, OPT_TARGET:maybe[t_Target], LHS:t_VARIABLE_NAME, IS_REF:bool, RHS:t_Expr).
predicate assign_array (ID:t_Assign_array, OPT_TARGET:maybe[t_Target], LHS:t_VARIABLE_NAME, INDEX:t_VARIABLE_NAME, IS_REF:bool, RHS:t_VARIABLE_NAME).
predicate assign_var_var (ID:t_Assign_var_var, OPT_TARGET:maybe[t_Target], LHS:t_VARIABLE_NAME, IS_REF:bool, RHS:t_VARIABLE_NAME).
predicate push_array (ID:t_Push_array, OPT_TARGET:maybe[t_Target], LHS:t_VARIABLE_NAME, IS_REF:bool, RHS:t_VARIABLE_NAME).
predicate eval_expr (ID:t_Eval_expr, EXPR:t_Expr).
predicate cast (ID:t_Cast, CAST:t_CAST, VARIABLE_NAME:t_VARIABLE_NAME).
predicate unary_op (ID:t_Unary_op, OP:t_OP, VARIABLE_NAME:t_VARIABLE_NAME).
predicate bin_op (ID:t_Bin_op, LEFT:t_VARIABLE_NAME, OP:t_OP, RIGHT:t_VARIABLE_NAME).
predicate constant (ID:t_Constant, OPT_CLASS_NAME:maybe[t_CLASS_NAME], CONSTANT_NAME:t_CONSTANT_NAME).
predicate instanceof (ID:t_Instanceof, VARIABLE_NAME:t_VARIABLE_NAME, CLASS_NAME:t_Class_name).
predicate variable (ID:t_Variable, OPT_TARGET:maybe[t_Target], VARIABLE_NAME:t_Variable_name, ARRAY_INDICESS:list[t_VARIABLE_NAME]).
predicate reflection (ID:t_Reflection, VARIABLE_NAME:t_VARIABLE_NAME).
predicate pre_op (ID:t_Pre_op, OP:t_OP, VARIABLE:t_Variable).
predicate array (ID:t_Array, ARRAY_ELEMS:list[t_Array_elem]).
predicate array_elem (ID:t_Array_elem, OPT_KEY:maybe[t_Expr], IS_REF:bool, VAL:t_Expr).
predicate method_invocation (ID:t_Method_invocation, OPT_TARGET:maybe[t_Target], METHOD_NAME:t_Method_name, ACTUAL_PARAMETERS:list[t_Actual_parameter]).
predicate actual_parameter (ID:t_Actual_parameter, IS_REF:bool, OPT_TARGET:maybe[t_Target], VARIABLE_NAME:t_Variable_name, ARRAY_INDICESS:list[t_VARIABLE_NAME]).
predicate new (ID:t_New, CLASS_NAME:t_Class_name, ACTUAL_PARAMETERS:list[t_Actual_parameter]).
predicate branch (ID:t_Branch, VARIABLE_NAME:t_VARIABLE_NAME, IFTRUE:t_LABEL_NAME, IFFALSE:t_LABEL_NAME).
predicate goto (ID:t_Goto, LABEL_NAME:t_LABEL_NAME).
predicate label (ID:t_Label, LABEL_NAME:t_LABEL_NAME).
predicate foreach_reset (ID:t_Foreach_reset, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_next (ID:t_Foreach_next, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_end (ID:t_Foreach_end, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_has_key (ID:t_Foreach_has_key, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_get_key (ID:t_Foreach_get_key, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_get_val (ID:t_Foreach_get_val, ARRAY:t_VARIABLE_NAME, KEY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreign_statement (ID:t_Foreign_statement).
predicate foreign_expr (ID:t_Foreign_expr).


predicate hT_ITERATOR (ID:t_HT_ITERATOR, VALUE:int).
predicate cLASS_NAME (ID:t_CLASS_NAME, VALUE:string).
predicate iNTERFACE_NAME (ID:t_INTERFACE_NAME, VALUE:string).
predicate mETHOD_NAME (ID:t_METHOD_NAME, VALUE:string).
predicate vARIABLE_NAME (ID:t_VARIABLE_NAME, VALUE:string).
predicate iNT (ID:t_INT, VALUE:int).
predicate rEAL (ID:t_REAL, VALUE:float).
predicate sTRING (ID:t_STRING, VALUE:string).
predicate bOOL (ID:t_BOOL, VALUE:bool).
predicate nIL (ID:t_NIL, VALUE:null).
predicate cAST (ID:t_CAST, VALUE:string).
predicate oP (ID:t_OP, VALUE:string).
predicate cONSTANT_NAME (ID:t_CONSTANT_NAME, VALUE:string).
predicate lABEL_NAME (ID:t_LABEL_NAME, VALUE:string).



% Generics

% Type Casts
to_node (any{pHP_script_id{ID}}, node_PHP_script{pHP_script_id{ID}}) :- .
to_node (any{class_def_id{ID}}, node_Class_def{class_def_id{ID}}) :- .
to_node (any{class_mod_id{ID}}, node_Class_mod{class_mod_id{ID}}) :- .
to_node (any{interface_def_id{ID}}, node_Interface_def{interface_def_id{ID}}) :- .
to_node (any{method_id{ID}}, node_Method{method_id{ID}}) :- .
to_node (any{signature_id{ID}}, node_Signature{signature_id{ID}}) :- .
to_node (any{method_mod_id{ID}}, node_Method_mod{method_mod_id{ID}}) :- .
to_node (any{formal_parameter_id{ID}}, node_Formal_parameter{formal_parameter_id{ID}}) :- .
to_node (any{type_id{ID}}, node_Type{type_id{ID}}) :- .
to_node (any{attribute_id{ID}}, node_Attribute{attribute_id{ID}}) :- .
to_node (any{attr_mod_id{ID}}, node_Attr_mod{attr_mod_id{ID}}) :- .
to_node (any{name_with_default_id{ID}}, node_Name_with_default{name_with_default_id{ID}}) :- .
to_node (any{return_id{ID}}, node_Return{return_id{ID}}) :- .
to_node (any{static_declaration_id{ID}}, node_Static_declaration{static_declaration_id{ID}}) :- .
to_node (any{global_id{ID}}, node_Global{global_id{ID}}) :- .
to_node (any{try_id{ID}}, node_Try{try_id{ID}}) :- .
to_node (any{catch_id{ID}}, node_Catch{catch_id{ID}}) :- .
to_node (any{throw_id{ID}}, node_Throw{throw_id{ID}}) :- .
to_node (any{assign_var_id{ID}}, node_Assign_var{assign_var_id{ID}}) :- .
to_node (any{assign_array_id{ID}}, node_Assign_array{assign_array_id{ID}}) :- .
to_node (any{assign_var_var_id{ID}}, node_Assign_var_var{assign_var_var_id{ID}}) :- .
to_node (any{push_array_id{ID}}, node_Push_array{push_array_id{ID}}) :- .
to_node (any{eval_expr_id{ID}}, node_Eval_expr{eval_expr_id{ID}}) :- .
to_node (any{cast_id{ID}}, node_Cast{cast_id{ID}}) :- .
to_node (any{unary_op_id{ID}}, node_Unary_op{unary_op_id{ID}}) :- .
to_node (any{bin_op_id{ID}}, node_Bin_op{bin_op_id{ID}}) :- .
to_node (any{constant_id{ID}}, node_Constant{constant_id{ID}}) :- .
to_node (any{instanceof_id{ID}}, node_Instanceof{instanceof_id{ID}}) :- .
to_node (any{variable_id{ID}}, node_Variable{variable_id{ID}}) :- .
to_node (any{reflection_id{ID}}, node_Reflection{reflection_id{ID}}) :- .
to_node (any{pre_op_id{ID}}, node_Pre_op{pre_op_id{ID}}) :- .
to_node (any{array_id{ID}}, node_Array{array_id{ID}}) :- .
to_node (any{array_elem_id{ID}}, node_Array_elem{array_elem_id{ID}}) :- .
to_node (any{method_invocation_id{ID}}, node_Method_invocation{method_invocation_id{ID}}) :- .
to_node (any{actual_parameter_id{ID}}, node_Actual_parameter{actual_parameter_id{ID}}) :- .
to_node (any{new_id{ID}}, node_New{new_id{ID}}) :- .
to_node (any{branch_id{ID}}, node_Branch{branch_id{ID}}) :- .
to_node (any{goto_id{ID}}, node_Goto{goto_id{ID}}) :- .
to_node (any{label_id{ID}}, node_Label{label_id{ID}}) :- .
to_node (any{foreach_reset_id{ID}}, node_Foreach_reset{foreach_reset_id{ID}}) :- .
to_node (any{foreach_next_id{ID}}, node_Foreach_next{foreach_next_id{ID}}) :- .
to_node (any{foreach_end_id{ID}}, node_Foreach_end{foreach_end_id{ID}}) :- .
to_node (any{foreach_has_key_id{ID}}, node_Foreach_has_key{foreach_has_key_id{ID}}) :- .
to_node (any{foreach_get_key_id{ID}}, node_Foreach_get_key{foreach_get_key_id{ID}}) :- .
to_node (any{foreach_get_val_id{ID}}, node_Foreach_get_val{foreach_get_val_id{ID}}) :- .
to_node (any{foreign_statement_id{ID}}, node_Foreign_statement{foreign_statement_id{ID}}) :- .
to_node (any{foreign_expr_id{ID}}, node_Foreign_expr{foreign_expr_id{ID}}) :- .



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
to_node (any{expr_Variable{ID}}, node_Variable{ID}) :- .
to_node (any{expr_Method_invocation{ID}}, node_Method_invocation{ID}) :- .
to_node (any{expr_New{ID}}, node_New{ID}) :- .
to_node (any{expr_INT{ID}}, node_INT{ID}) :- .
to_node (any{expr_REAL{ID}}, node_REAL{ID}) :- .
to_node (any{expr_STRING{ID}}, node_STRING{ID}) :- .
to_node (any{expr_BOOL{ID}}, node_BOOL{ID}) :- .
to_node (any{expr_NIL{ID}}, node_NIL{ID}) :- .
to_node (any{expr_Array{ID}}, node_Array{ID}) :- .
to_node (any{expr_Foreach_has_key{ID}}, node_Foreach_has_key{ID}) :- .
to_node (any{expr_Foreach_get_key{ID}}, node_Foreach_get_key{ID}) :- .
to_node (any{expr_Foreach_get_val{ID}}, node_Foreach_get_val{ID}) :- .
to_node (any{expr_Foreign_expr{ID}}, node_Foreign_expr{ID}) :- .
to_node (any{literal_INT{ID}}, node_INT{ID}) :- .
to_node (any{literal_REAL{ID}}, node_REAL{ID}) :- .
to_node (any{literal_STRING{ID}}, node_STRING{ID}) :- .
to_node (any{literal_BOOL{ID}}, node_BOOL{ID}) :- .
to_node (any{literal_NIL{ID}}, node_NIL{ID}) :- .
to_node (any{variable_name_VARIABLE_NAME{ID}}, node_VARIABLE_NAME{ID}) :- .
to_node (any{variable_name_Reflection{ID}}, node_Reflection{ID}) :- .
to_node (any{target_Cast{ID}}, node_Cast{ID}) :- .
to_node (any{target_Unary_op{ID}}, node_Unary_op{ID}) :- .
to_node (any{target_Bin_op{ID}}, node_Bin_op{ID}) :- .
to_node (any{target_Constant{ID}}, node_Constant{ID}) :- .
to_node (any{target_Instanceof{ID}}, node_Instanceof{ID}) :- .
to_node (any{target_Variable{ID}}, node_Variable{ID}) :- .
to_node (any{target_Method_invocation{ID}}, node_Method_invocation{ID}) :- .
to_node (any{target_New{ID}}, node_New{ID}) :- .
to_node (any{target_INT{ID}}, node_INT{ID}) :- .
to_node (any{target_REAL{ID}}, node_REAL{ID}) :- .
to_node (any{target_STRING{ID}}, node_STRING{ID}) :- .
to_node (any{target_BOOL{ID}}, node_BOOL{ID}) :- .
to_node (any{target_NIL{ID}}, node_NIL{ID}) :- .
to_node (any{target_Array{ID}}, node_Array{ID}) :- .
to_node (any{target_Foreach_has_key{ID}}, node_Foreach_has_key{ID}) :- .
to_node (any{target_Foreach_get_key{ID}}, node_Foreach_get_key{ID}) :- .
to_node (any{target_Foreach_get_val{ID}}, node_Foreach_get_val{ID}) :- .
to_node (any{target_Foreign_expr{ID}}, node_Foreign_expr{ID}) :- .
to_node (any{target_CLASS_NAME{ID}}, node_CLASS_NAME{ID}) :- .
to_node (any{method_name_METHOD_NAME{ID}}, node_METHOD_NAME{ID}) :- .
to_node (any{method_name_Reflection{ID}}, node_Reflection{ID}) :- .
to_node (any{class_name_CLASS_NAME{ID}}, node_CLASS_NAME{ID}) :- .
to_node (any{class_name_Reflection{ID}}, node_Reflection{ID}) :- .
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


to_node (any{hT_ITERATOR_id{ID}}, node_HT_ITERATOR{hT_ITERATOR_id{ID}}) :- .
to_node (any{cLASS_NAME_id{ID}}, node_CLASS_NAME{cLASS_NAME_id{ID}}) :- .
to_node (any{iNTERFACE_NAME_id{ID}}, node_INTERFACE_NAME{iNTERFACE_NAME_id{ID}}) :- .
to_node (any{mETHOD_NAME_id{ID}}, node_METHOD_NAME{mETHOD_NAME_id{ID}}) :- .
to_node (any{vARIABLE_NAME_id{ID}}, node_VARIABLE_NAME{vARIABLE_NAME_id{ID}}) :- .
to_node (any{iNT_id{ID}}, node_INT{iNT_id{ID}}) :- .
to_node (any{rEAL_id{ID}}, node_REAL{rEAL_id{ID}}) :- .
to_node (any{sTRING_id{ID}}, node_STRING{sTRING_id{ID}}) :- .
to_node (any{bOOL_id{ID}}, node_BOOL{bOOL_id{ID}}) :- .
to_node (any{nIL_id{ID}}, node_NIL{nIL_id{ID}}) :- .
to_node (any{cAST_id{ID}}, node_CAST{cAST_id{ID}}) :- .
to_node (any{oP_id{ID}}, node_OP{oP_id{ID}}) :- .
to_node (any{cONSTANT_NAME_id{ID}}, node_CONSTANT_NAME{cONSTANT_NAME_id{ID}}) :- .
to_node (any{lABEL_NAME_id{ID}}, node_LABEL_NAME{lABEL_NAME_id{ID}}) :- .



% Data visitors
to_generic (NODE, GENERIC) :-
	mir()->pHP_script(ID, STATEMENTS),
	to_node (any{ID}, NODE),
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{NODE, "PHP_script", [GEN_STATEMENTS]}.

to_generic (NODE, GENERIC) :-
	mir()->class_def(ID, CLASS_MOD, CLASS_NAME, OPT_EXTENDS, IMPLEMENTSS, MEMBERS),
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
	mir()->class_mod(ID, IS_ABSTRACT, IS_FINAL),
	to_node (any{ID}, NODE),
	GEN_IS_ABSTRACT = gmarker {"abstract", IS_ABSTRACT},
	GEN_IS_FINAL = gmarker {"final", IS_FINAL},
	GENERIC = gnode{NODE, "Class_mod", [GEN_IS_ABSTRACT, GEN_IS_FINAL]}.

to_generic (NODE, GENERIC) :-
	mir()->interface_def(ID, INTERFACE_NAME, EXTENDSS, MEMBERS),
	to_node (any{ID}, NODE),
	to_node (any{INTERFACE_NAME}, NODE_INTERFACE_NAME),
	to_generic (NODE_INTERFACE_NAME, GEN_INTERFACE_NAME),
	list_to_generic_list (EXTENDSS, GEN_EXTENDSS),
	list_to_generic_list (MEMBERS, GEN_MEMBERS),
	GENERIC = gnode{NODE, "Interface_def", [GEN_INTERFACE_NAME, GEN_EXTENDSS, GEN_MEMBERS]}.

to_generic (NODE, GENERIC) :-
	mir()->method(ID, SIGNATURE, OPT_STATEMENTS),
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
	mir()->signature(ID, METHOD_MOD, IS_REF, METHOD_NAME, FORMAL_PARAMETERS),
	to_node (any{ID}, NODE),
	to_node (any{METHOD_MOD}, NODE_METHOD_MOD),
	to_generic (NODE_METHOD_MOD, GEN_METHOD_MOD),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{METHOD_NAME}, NODE_METHOD_NAME),
	to_generic (NODE_METHOD_NAME, GEN_METHOD_NAME),
	list_to_generic_list (FORMAL_PARAMETERS, GEN_FORMAL_PARAMETERS),
	GENERIC = gnode{NODE, "Signature", [GEN_METHOD_MOD, GEN_IS_REF, GEN_METHOD_NAME, GEN_FORMAL_PARAMETERS]}.

to_generic (NODE, GENERIC) :-
	mir()->method_mod(ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_ABSTRACT, IS_FINAL),
	to_node (any{ID}, NODE),
	GEN_IS_PUBLIC = gmarker {"public", IS_PUBLIC},
	GEN_IS_PROTECTED = gmarker {"protected", IS_PROTECTED},
	GEN_IS_PRIVATE = gmarker {"private", IS_PRIVATE},
	GEN_IS_STATIC = gmarker {"static", IS_STATIC},
	GEN_IS_ABSTRACT = gmarker {"abstract", IS_ABSTRACT},
	GEN_IS_FINAL = gmarker {"final", IS_FINAL},
	GENERIC = gnode{NODE, "Method_mod", [GEN_IS_PUBLIC, GEN_IS_PROTECTED, GEN_IS_PRIVATE, GEN_IS_STATIC, GEN_IS_ABSTRACT, GEN_IS_FINAL]}.

to_generic (NODE, GENERIC) :-
	mir()->formal_parameter(ID, TYPE, IS_REF, VAR),
	to_node (any{ID}, NODE),
	to_node (any{TYPE}, NODE_TYPE),
	to_generic (NODE_TYPE, GEN_TYPE),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{VAR}, NODE_VAR),
	to_generic (NODE_VAR, GEN_VAR),
	GENERIC = gnode{NODE, "Formal_parameter", [GEN_TYPE, GEN_IS_REF, GEN_VAR]}.

to_generic (NODE, GENERIC) :-
	mir()->p_type(ID, OPT_CLASS_NAME),
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
	mir()->attribute(ID, ATTR_MOD, VAR),
	to_node (any{ID}, NODE),
	to_node (any{ATTR_MOD}, NODE_ATTR_MOD),
	to_generic (NODE_ATTR_MOD, GEN_ATTR_MOD),
	to_node (any{VAR}, NODE_VAR),
	to_generic (NODE_VAR, GEN_VAR),
	GENERIC = gnode{NODE, "Attribute", [GEN_ATTR_MOD, GEN_VAR]}.

to_generic (NODE, GENERIC) :-
	mir()->attr_mod(ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_CONST),
	to_node (any{ID}, NODE),
	GEN_IS_PUBLIC = gmarker {"public", IS_PUBLIC},
	GEN_IS_PROTECTED = gmarker {"protected", IS_PROTECTED},
	GEN_IS_PRIVATE = gmarker {"private", IS_PRIVATE},
	GEN_IS_STATIC = gmarker {"static", IS_STATIC},
	GEN_IS_CONST = gmarker {"const", IS_CONST},
	GENERIC = gnode{NODE, "Attr_mod", [GEN_IS_PUBLIC, GEN_IS_PROTECTED, GEN_IS_PRIVATE, GEN_IS_STATIC, GEN_IS_CONST]}.

to_generic (NODE, GENERIC) :-
	mir()->name_with_default(ID, VARIABLE_NAME, OPT_EXPR),
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
	mir()->return(ID, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Return", [GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	mir()->static_declaration(ID, VAR),
	to_node (any{ID}, NODE),
	to_node (any{VAR}, NODE_VAR),
	to_generic (NODE_VAR, GEN_VAR),
	GENERIC = gnode{NODE, "Static_declaration", [GEN_VAR]}.

to_generic (NODE, GENERIC) :-
	mir()->global(ID, VARIABLE_NAME),
	to_node (any{ID}, NODE),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{NODE, "Global", [GEN_VARIABLE_NAME]}.

to_generic (NODE, GENERIC) :-
	mir()->try(ID, STATEMENTS, CATCHESS),
	to_node (any{ID}, NODE),
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	list_to_generic_list (CATCHESS, GEN_CATCHESS),
	GENERIC = gnode{NODE, "Try", [GEN_STATEMENTS, GEN_CATCHESS]}.

to_generic (NODE, GENERIC) :-
	mir()->catch(ID, CLASS_NAME, VARIABLE_NAME, STATEMENTS),
	to_node (any{ID}, NODE),
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	list_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{NODE, "Catch", [GEN_CLASS_NAME, GEN_VARIABLE_NAME, GEN_STATEMENTS]}.

to_generic (NODE, GENERIC) :-
	mir()->throw(ID, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Throw", [GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	mir()->assign_var(ID, OPT_TARGET, LHS, IS_REF, RHS),
	to_node (any{ID}, NODE),
	((OPT_TARGET = yes{TARGET},
	to_node (any{TARGET}, NODE_TARGET),
	to_generic (NODE_TARGET, GEN_TARGET),
	GEN_OPT_TARGET = gmaybe{"Target", yes{GEN_TARGET}})
	;
	(OPT_TARGET \= yes{_},
	GEN_OPT_TARGET = gmaybe{"Target", no})),
	to_node (any{LHS}, NODE_LHS),
	to_generic (NODE_LHS, GEN_LHS),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{RHS}, NODE_RHS),
	to_generic (NODE_RHS, GEN_RHS),
	GENERIC = gnode{NODE, "Assign_var", [GEN_OPT_TARGET, GEN_LHS, GEN_IS_REF, GEN_RHS]}.

to_generic (NODE, GENERIC) :-
	mir()->assign_array(ID, OPT_TARGET, LHS, INDEX, IS_REF, RHS),
	to_node (any{ID}, NODE),
	((OPT_TARGET = yes{TARGET},
	to_node (any{TARGET}, NODE_TARGET),
	to_generic (NODE_TARGET, GEN_TARGET),
	GEN_OPT_TARGET = gmaybe{"Target", yes{GEN_TARGET}})
	;
	(OPT_TARGET \= yes{_},
	GEN_OPT_TARGET = gmaybe{"Target", no})),
	to_node (any{LHS}, NODE_LHS),
	to_generic (NODE_LHS, GEN_LHS),
	to_node (any{INDEX}, NODE_INDEX),
	to_generic (NODE_INDEX, GEN_INDEX),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{RHS}, NODE_RHS),
	to_generic (NODE_RHS, GEN_RHS),
	GENERIC = gnode{NODE, "Assign_array", [GEN_OPT_TARGET, GEN_LHS, GEN_INDEX, GEN_IS_REF, GEN_RHS]}.

to_generic (NODE, GENERIC) :-
	mir()->assign_var_var(ID, OPT_TARGET, LHS, IS_REF, RHS),
	to_node (any{ID}, NODE),
	((OPT_TARGET = yes{TARGET},
	to_node (any{TARGET}, NODE_TARGET),
	to_generic (NODE_TARGET, GEN_TARGET),
	GEN_OPT_TARGET = gmaybe{"Target", yes{GEN_TARGET}})
	;
	(OPT_TARGET \= yes{_},
	GEN_OPT_TARGET = gmaybe{"Target", no})),
	to_node (any{LHS}, NODE_LHS),
	to_generic (NODE_LHS, GEN_LHS),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{RHS}, NODE_RHS),
	to_generic (NODE_RHS, GEN_RHS),
	GENERIC = gnode{NODE, "Assign_var_var", [GEN_OPT_TARGET, GEN_LHS, GEN_IS_REF, GEN_RHS]}.

to_generic (NODE, GENERIC) :-
	mir()->push_array(ID, OPT_TARGET, LHS, IS_REF, RHS),
	to_node (any{ID}, NODE),
	((OPT_TARGET = yes{TARGET},
	to_node (any{TARGET}, NODE_TARGET),
	to_generic (NODE_TARGET, GEN_TARGET),
	GEN_OPT_TARGET = gmaybe{"Target", yes{GEN_TARGET}})
	;
	(OPT_TARGET \= yes{_},
	GEN_OPT_TARGET = gmaybe{"Target", no})),
	to_node (any{LHS}, NODE_LHS),
	to_generic (NODE_LHS, GEN_LHS),
	GEN_IS_REF = gmarker {"is_ref", IS_REF},
	to_node (any{RHS}, NODE_RHS),
	to_generic (NODE_RHS, GEN_RHS),
	GENERIC = gnode{NODE, "Push_array", [GEN_OPT_TARGET, GEN_LHS, GEN_IS_REF, GEN_RHS]}.

to_generic (NODE, GENERIC) :-
	mir()->eval_expr(ID, EXPR),
	to_node (any{ID}, NODE),
	to_node (any{EXPR}, NODE_EXPR),
	to_generic (NODE_EXPR, GEN_EXPR),
	GENERIC = gnode{NODE, "Eval_expr", [GEN_EXPR]}.

to_generic (NODE, GENERIC) :-
	mir()->cast(ID, CAST, VARIABLE_NAME),
	to_node (any{ID}, NODE),
	to_node (any{CAST}, NODE_CAST),
	to_generic (NODE_CAST, GEN_CAST),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{NODE, "Cast", [GEN_CAST, GEN_VARIABLE_NAME]}.

to_generic (NODE, GENERIC) :-
	mir()->unary_op(ID, OP, VARIABLE_NAME),
	to_node (any{ID}, NODE),
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{NODE, "Unary_op", [GEN_OP, GEN_VARIABLE_NAME]}.

to_generic (NODE, GENERIC) :-
	mir()->bin_op(ID, LEFT, OP, RIGHT),
	to_node (any{ID}, NODE),
	to_node (any{LEFT}, NODE_LEFT),
	to_generic (NODE_LEFT, GEN_LEFT),
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{RIGHT}, NODE_RIGHT),
	to_generic (NODE_RIGHT, GEN_RIGHT),
	GENERIC = gnode{NODE, "Bin_op", [GEN_LEFT, GEN_OP, GEN_RIGHT]}.

to_generic (NODE, GENERIC) :-
	mir()->constant(ID, OPT_CLASS_NAME, CONSTANT_NAME),
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
	mir()->instanceof(ID, VARIABLE_NAME, CLASS_NAME),
	to_node (any{ID}, NODE),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	GENERIC = gnode{NODE, "Instanceof", [GEN_VARIABLE_NAME, GEN_CLASS_NAME]}.

to_generic (NODE, GENERIC) :-
	mir()->variable(ID, OPT_TARGET, VARIABLE_NAME, ARRAY_INDICESS),
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
	list_to_generic_list (ARRAY_INDICESS, GEN_ARRAY_INDICESS),
	GENERIC = gnode{NODE, "Variable", [GEN_OPT_TARGET, GEN_VARIABLE_NAME, GEN_ARRAY_INDICESS]}.

to_generic (NODE, GENERIC) :-
	mir()->reflection(ID, VARIABLE_NAME),
	to_node (any{ID}, NODE),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	GENERIC = gnode{NODE, "Reflection", [GEN_VARIABLE_NAME]}.

to_generic (NODE, GENERIC) :-
	mir()->pre_op(ID, OP, VARIABLE),
	to_node (any{ID}, NODE),
	to_node (any{OP}, NODE_OP),
	to_generic (NODE_OP, GEN_OP),
	to_node (any{VARIABLE}, NODE_VARIABLE),
	to_generic (NODE_VARIABLE, GEN_VARIABLE),
	GENERIC = gnode{NODE, "Pre_op", [GEN_OP, GEN_VARIABLE]}.

to_generic (NODE, GENERIC) :-
	mir()->array(ID, ARRAY_ELEMS),
	to_node (any{ID}, NODE),
	list_to_generic_list (ARRAY_ELEMS, GEN_ARRAY_ELEMS),
	GENERIC = gnode{NODE, "Array", [GEN_ARRAY_ELEMS]}.

to_generic (NODE, GENERIC) :-
	mir()->array_elem(ID, OPT_KEY, IS_REF, VAL),
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
	mir()->method_invocation(ID, OPT_TARGET, METHOD_NAME, ACTUAL_PARAMETERS),
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
	mir()->actual_parameter(ID, IS_REF, OPT_TARGET, VARIABLE_NAME, ARRAY_INDICESS),
	to_node (any{ID}, NODE),
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
	list_to_generic_list (ARRAY_INDICESS, GEN_ARRAY_INDICESS),
	GENERIC = gnode{NODE, "Actual_parameter", [GEN_IS_REF, GEN_OPT_TARGET, GEN_VARIABLE_NAME, GEN_ARRAY_INDICESS]}.

to_generic (NODE, GENERIC) :-
	mir()->new(ID, CLASS_NAME, ACTUAL_PARAMETERS),
	to_node (any{ID}, NODE),
	to_node (any{CLASS_NAME}, NODE_CLASS_NAME),
	to_generic (NODE_CLASS_NAME, GEN_CLASS_NAME),
	list_to_generic_list (ACTUAL_PARAMETERS, GEN_ACTUAL_PARAMETERS),
	GENERIC = gnode{NODE, "New", [GEN_CLASS_NAME, GEN_ACTUAL_PARAMETERS]}.

to_generic (NODE, GENERIC) :-
	mir()->branch(ID, VARIABLE_NAME, IFTRUE, IFFALSE),
	to_node (any{ID}, NODE),
	to_node (any{VARIABLE_NAME}, NODE_VARIABLE_NAME),
	to_generic (NODE_VARIABLE_NAME, GEN_VARIABLE_NAME),
	to_node (any{IFTRUE}, NODE_IFTRUE),
	to_generic (NODE_IFTRUE, GEN_IFTRUE),
	to_node (any{IFFALSE}, NODE_IFFALSE),
	to_generic (NODE_IFFALSE, GEN_IFFALSE),
	GENERIC = gnode{NODE, "Branch", [GEN_VARIABLE_NAME, GEN_IFTRUE, GEN_IFFALSE]}.

to_generic (NODE, GENERIC) :-
	mir()->goto(ID, LABEL_NAME),
	to_node (any{ID}, NODE),
	to_node (any{LABEL_NAME}, NODE_LABEL_NAME),
	to_generic (NODE_LABEL_NAME, GEN_LABEL_NAME),
	GENERIC = gnode{NODE, "Goto", [GEN_LABEL_NAME]}.

to_generic (NODE, GENERIC) :-
	mir()->label(ID, LABEL_NAME),
	to_node (any{ID}, NODE),
	to_node (any{LABEL_NAME}, NODE_LABEL_NAME),
	to_generic (NODE_LABEL_NAME, GEN_LABEL_NAME),
	GENERIC = gnode{NODE, "Label", [GEN_LABEL_NAME]}.

to_generic (NODE, GENERIC) :-
	mir()->foreach_reset(ID, ARRAY, ITER),
	to_node (any{ID}, NODE),
	to_node (any{ARRAY}, NODE_ARRAY),
	to_generic (NODE_ARRAY, GEN_ARRAY),
	to_node (any{ITER}, NODE_ITER),
	to_generic (NODE_ITER, GEN_ITER),
	GENERIC = gnode{NODE, "Foreach_reset", [GEN_ARRAY, GEN_ITER]}.

to_generic (NODE, GENERIC) :-
	mir()->foreach_next(ID, ARRAY, ITER),
	to_node (any{ID}, NODE),
	to_node (any{ARRAY}, NODE_ARRAY),
	to_generic (NODE_ARRAY, GEN_ARRAY),
	to_node (any{ITER}, NODE_ITER),
	to_generic (NODE_ITER, GEN_ITER),
	GENERIC = gnode{NODE, "Foreach_next", [GEN_ARRAY, GEN_ITER]}.

to_generic (NODE, GENERIC) :-
	mir()->foreach_end(ID, ARRAY, ITER),
	to_node (any{ID}, NODE),
	to_node (any{ARRAY}, NODE_ARRAY),
	to_generic (NODE_ARRAY, GEN_ARRAY),
	to_node (any{ITER}, NODE_ITER),
	to_generic (NODE_ITER, GEN_ITER),
	GENERIC = gnode{NODE, "Foreach_end", [GEN_ARRAY, GEN_ITER]}.

to_generic (NODE, GENERIC) :-
	mir()->foreach_has_key(ID, ARRAY, ITER),
	to_node (any{ID}, NODE),
	to_node (any{ARRAY}, NODE_ARRAY),
	to_generic (NODE_ARRAY, GEN_ARRAY),
	to_node (any{ITER}, NODE_ITER),
	to_generic (NODE_ITER, GEN_ITER),
	GENERIC = gnode{NODE, "Foreach_has_key", [GEN_ARRAY, GEN_ITER]}.

to_generic (NODE, GENERIC) :-
	mir()->foreach_get_key(ID, ARRAY, ITER),
	to_node (any{ID}, NODE),
	to_node (any{ARRAY}, NODE_ARRAY),
	to_generic (NODE_ARRAY, GEN_ARRAY),
	to_node (any{ITER}, NODE_ITER),
	to_generic (NODE_ITER, GEN_ITER),
	GENERIC = gnode{NODE, "Foreach_get_key", [GEN_ARRAY, GEN_ITER]}.

to_generic (NODE, GENERIC) :-
	mir()->foreach_get_val(ID, ARRAY, KEY, ITER),
	to_node (any{ID}, NODE),
	to_node (any{ARRAY}, NODE_ARRAY),
	to_generic (NODE_ARRAY, GEN_ARRAY),
	to_node (any{KEY}, NODE_KEY),
	to_generic (NODE_KEY, GEN_KEY),
	to_node (any{ITER}, NODE_ITER),
	to_generic (NODE_ITER, GEN_ITER),
	GENERIC = gnode{NODE, "Foreach_get_val", [GEN_ARRAY, GEN_KEY, GEN_ITER]}.

to_generic (NODE, GENERIC) :-
	mir()->foreign_statement(ID),
	to_node (any{ID}, NODE),
	GENERIC = gnode{NODE, "Foreign_statement", []}.

to_generic (NODE, GENERIC) :-
	mir()->foreign_expr(ID),
	to_node (any{ID}, NODE),
	GENERIC = gnode{NODE, "Foreign_expr", []}.



to_generic (NODE, GENERIC) :-
	mir()->hT_ITERATOR(ID, HT_ITERATOR),
	to_node (any{ID}, NODE),
	GEN_HT_ITERATOR = gint {HT_ITERATOR},
	GENERIC = gnode{NODE, "HT_ITERATOR", [GEN_HT_ITERATOR]}.

to_generic (NODE, GENERIC) :-
	mir()->cLASS_NAME(ID, CLASS_NAME),
	to_node (any{ID}, NODE),
	GEN_CLASS_NAME = gstring {CLASS_NAME},
	GENERIC = gnode{NODE, "CLASS_NAME", [GEN_CLASS_NAME]}.

to_generic (NODE, GENERIC) :-
	mir()->iNTERFACE_NAME(ID, INTERFACE_NAME),
	to_node (any{ID}, NODE),
	GEN_INTERFACE_NAME = gstring {INTERFACE_NAME},
	GENERIC = gnode{NODE, "INTERFACE_NAME", [GEN_INTERFACE_NAME]}.

to_generic (NODE, GENERIC) :-
	mir()->mETHOD_NAME(ID, METHOD_NAME),
	to_node (any{ID}, NODE),
	GEN_METHOD_NAME = gstring {METHOD_NAME},
	GENERIC = gnode{NODE, "METHOD_NAME", [GEN_METHOD_NAME]}.

to_generic (NODE, GENERIC) :-
	mir()->vARIABLE_NAME(ID, VARIABLE_NAME),
	to_node (any{ID}, NODE),
	GEN_VARIABLE_NAME = gstring {VARIABLE_NAME},
	GENERIC = gnode{NODE, "VARIABLE_NAME", [GEN_VARIABLE_NAME]}.

to_generic (NODE, GENERIC) :-
	mir()->iNT(ID, INT),
	to_node (any{ID}, NODE),
	GEN_INT = gint {INT},
	GENERIC = gnode{NODE, "INT", [GEN_INT]}.

to_generic (NODE, GENERIC) :-
	mir()->rEAL(ID, REAL),
	to_node (any{ID}, NODE),
	GEN_REAL = gfloat {REAL},
	GENERIC = gnode{NODE, "REAL", [GEN_REAL]}.

to_generic (NODE, GENERIC) :-
	mir()->sTRING(ID, STRING),
	to_node (any{ID}, NODE),
	GEN_STRING = gstring {STRING},
	GENERIC = gnode{NODE, "STRING", [GEN_STRING]}.

to_generic (NODE, GENERIC) :-
	mir()->bOOL(ID, BOOL),
	to_node (any{ID}, NODE),
	GEN_BOOL = gbool {BOOL},
	GENERIC = gnode{NODE, "BOOL", [GEN_BOOL]}.

to_generic (NODE, GENERIC) :-
	mir()->nIL(ID, NIL),
	to_node (any{ID}, NODE),
	GEN_NIL = gnull {NIL},
	GENERIC = gnode{NODE, "NIL", [GEN_NIL]}.

to_generic (NODE, GENERIC) :-
	mir()->cAST(ID, CAST),
	to_node (any{ID}, NODE),
	GEN_CAST = gstring {CAST},
	GENERIC = gnode{NODE, "CAST", [GEN_CAST]}.

to_generic (NODE, GENERIC) :-
	mir()->oP(ID, OP),
	to_node (any{ID}, NODE),
	GEN_OP = gstring {OP},
	GENERIC = gnode{NODE, "OP", [GEN_OP]}.

to_generic (NODE, GENERIC) :-
	mir()->cONSTANT_NAME(ID, CONSTANT_NAME),
	to_node (any{ID}, NODE),
	GEN_CONSTANT_NAME = gstring {CONSTANT_NAME},
	GENERIC = gnode{NODE, "CONSTANT_NAME", [GEN_CONSTANT_NAME]}.

to_generic (NODE, GENERIC) :-
	mir()->lABEL_NAME(ID, LABEL_NAME),
	to_node (any{ID}, NODE),
	GEN_LABEL_NAME = gstring {LABEL_NAME},
	GENERIC = gnode{NODE, "LABEL_NAME", [GEN_LABEL_NAME]}.



