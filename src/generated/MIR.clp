import "src/analyse/base.clp".

session mir ().

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
type t_Return.
type t_Static_declaration.
type t_Global.
type t_Try.
type t_Catch.
type t_Throw.
type t_Eval_expr.
type t_Foreign.
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


% Forward declarations for disjunctive types
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


% Token declarations
type t_HT_ITERATOR ::= hT_ITERATOR_id { id }.
type t_CLASS_NAME ::= cLASS_NAME_id { id }.
type t_INTERFACE_NAME ::= iNTERFACE_NAME_id { id }.
type t_METHOD_NAME ::= mETHOD_NAME_id { id }.
type t_VARIABLE_NAME ::= vARIABLE_NAME_id { id }.
type t_LABEL_NAME ::= lABEL_NAME_id { id }.
type t_INT ::= iNT_id { id }.
type t_REAL ::= rEAL_id { id }.
type t_STRING ::= sTRING_id { id }.
type t_BOOL ::= bOOL_id { id }.
type t_NIL ::= nIL_id { id }.
type t_CAST ::= cAST_id { id }.
type t_OP ::= oP_id { id }.
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
type t_Return ::= return_id { id }.
type t_Static_declaration ::= static_declaration_id { id }.
type t_Global ::= global_id { id }.
type t_Try ::= try_id { id }.
type t_Catch ::= catch_id { id }.
type t_Throw ::= throw_id { id }.
type t_Eval_expr ::= eval_expr_id { id }.
type t_Foreign ::= foreign_id { id }.
type t_Branch ::= branch_id { id }.
type t_Goto ::= goto_id { id }.
type t_Label ::= label_id { id }.
type t_Foreach_reset ::= foreach_reset_id { id }.
type t_Foreach_next ::= foreach_next_id { id }.
type t_Foreach_end ::= foreach_end_id { id }.
type t_Foreach_has_key ::= foreach_has_key_id { id }.
type t_Foreach_get_key ::= foreach_get_key_id { id }.
type t_Foreach_get_val ::= foreach_get_val_id { id }.
type t_Assignment ::= assignment_id { id }.
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


% Disjunctive types
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
		| target_Array { t_Array } 
		| target_Foreach_has_key { t_Foreach_has_key } 
		| target_Foreach_get_key { t_Foreach_get_key } 
		| target_Foreach_get_val { t_Foreach_get_val } 
		| target_Foreign { t_Foreign } 
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
		| expr_Array { t_Array } 
		| expr_Foreach_has_key { t_Foreach_has_key } 
		| expr_Foreach_get_key { t_Foreach_get_key } 
		| expr_Foreach_get_val { t_Foreach_get_val } 
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
		| statement_Label { t_Label } 
		| statement_Goto { t_Goto } 
		| statement_Branch { t_Branch } 
		| statement_Foreach_next { t_Foreach_next } 
		| statement_Foreach_reset { t_Foreach_reset } 
		| statement_Foreach_end { t_Foreach_end } 
		| statement_Foreign { t_Foreign } 
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
		| node_Eval_expr { t_Eval_expr } 
		| node_Label { t_Label } 
		| node_Goto { t_Goto } 
		| node_Branch { t_Branch } 
		| node_Foreach_next { t_Foreach_next } 
		| node_Foreach_reset { t_Foreach_reset } 
		| node_Foreach_end { t_Foreach_end } 
		| node_Foreign { t_Foreign } 
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
		| node_Assignment { t_Assignment } 
		| node_Cast { t_Cast } 
		| node_Unary_op { t_Unary_op } 
		| node_Bin_op { t_Bin_op } 
		| node_Constant { t_Constant } 
		| node_Instanceof { t_Instanceof } 
		| node_Variable { t_Variable } 
		| node_Pre_op { t_Pre_op } 
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
predicate class_def (ID:t_Class_def, CLASS_MOD:t_Class_mod, CLASS_NAME:t_CLASS_NAME, EXTENDS:maybe[t_CLASS_NAME], IMPLEMENTS:list[t_INTERFACE_NAME], MEMBERS:list[t_Member]).
predicate class_mod (ID:t_Class_mod, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate interface_def (ID:t_Interface_def, INTERFACE_NAME:t_INTERFACE_NAME, EXTENDS:list[t_INTERFACE_NAME], MEMBERS:list[t_Member]).
predicate method (ID:t_Method, SIGNATURE:t_Signature, STATEMENTS:maybe[list[t_Statement]]).
predicate signature (ID:t_Signature, METHOD_MOD:t_Method_mod, IS_REF:bool, METHOD_NAME:t_METHOD_NAME, FORMAL_PARAMETERS:list[t_Formal_parameter]).
predicate method_mod (ID:t_Method_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate formal_parameter (ID:t_Formal_parameter, TYPE:t_Type, IS_REF:bool, VAR:t_Name_with_default).
predicate p_type (ID:t_Type, CLASS_NAME:maybe[t_CLASS_NAME]).
predicate attribute (ID:t_Attribute, ATTR_MOD:t_Attr_mod, VAR:t_Name_with_default).
predicate attr_mod (ID:t_Attr_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_CONST:bool).
predicate name_with_default (ID:t_Name_with_default, VARIABLE_NAME:t_VARIABLE_NAME, EXPR:maybe[t_Expr]).
predicate return (ID:t_Return, EXPR:maybe[t_Expr]).
predicate static_declaration (ID:t_Static_declaration, VAR:t_Name_with_default).
predicate global (ID:t_Global, VARIABLE_NAME:t_Variable_name).
predicate try (ID:t_Try, STATEMENTS:list[t_Statement], CATCHES:list[t_Catch]).
predicate catch (ID:t_Catch, CLASS_NAME:t_CLASS_NAME, VARIABLE_NAME:t_VARIABLE_NAME, STATEMENTS:list[t_Statement]).
predicate throw (ID:t_Throw, EXPR:t_Expr).
predicate eval_expr (ID:t_Eval_expr, EXPR:t_Expr).
predicate foreign (ID:t_Foreign).
predicate branch (ID:t_Branch, VARIABLE_NAME:t_VARIABLE_NAME, IFTRUE:t_LABEL_NAME, IFFALSE:t_LABEL_NAME).
predicate goto (ID:t_Goto, LABEL_NAME:t_LABEL_NAME).
predicate label (ID:t_Label, LABEL_NAME:t_LABEL_NAME).
predicate foreach_reset (ID:t_Foreach_reset, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_next (ID:t_Foreach_next, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_end (ID:t_Foreach_end, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_has_key (ID:t_Foreach_has_key, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_get_key (ID:t_Foreach_get_key, ARRAY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate foreach_get_val (ID:t_Foreach_get_val, ARRAY:t_VARIABLE_NAME, KEY:t_VARIABLE_NAME, ITER:t_HT_ITERATOR).
predicate assignment (ID:t_Assignment, VARIABLE:t_Variable, IS_REF:bool, EXPR:t_Expr).
predicate cast (ID:t_Cast, CAST:t_CAST, VARIABLE_NAME:t_VARIABLE_NAME).
predicate unary_op (ID:t_Unary_op, OP:t_OP, VARIABLE_NAME:t_VARIABLE_NAME).
predicate bin_op (ID:t_Bin_op, LEFT:t_VARIABLE_NAME, OP:t_OP, RIGHT:t_VARIABLE_NAME).
predicate constant (ID:t_Constant, CLASS_NAME:maybe[t_CLASS_NAME], CONSTANT_NAME:t_CONSTANT_NAME).
predicate instanceof (ID:t_Instanceof, VARIABLE_NAME:t_VARIABLE_NAME, CLASS_NAME:t_Class_name).
predicate variable (ID:t_Variable, TARGET:maybe[t_Target], VARIABLE_NAME:t_Variable_name, ARRAY_INDICES:list[maybe[t_VARIABLE_NAME]]).
predicate reflection (ID:t_Reflection, VARIABLE_NAME:t_VARIABLE_NAME).
predicate pre_op (ID:t_Pre_op, OP:t_OP, VARIABLE:t_Variable).
predicate array (ID:t_Array, ARRAY_ELEMS:list[t_Array_elem]).
predicate array_elem (ID:t_Array_elem, KEY:maybe[t_Expr], IS_REF:bool, VAL:t_Expr).
predicate method_invocation (ID:t_Method_invocation, TARGET:maybe[t_Target], METHOD_NAME:t_Method_name, ACTUAL_PARAMETERS:list[t_Actual_parameter]).
predicate actual_parameter (ID:t_Actual_parameter, IS_REF:bool, TARGET:maybe[t_Target], VARIABLE_NAME:t_Variable_name, ARRAY_INDICES:list[maybe[t_VARIABLE_NAME]]).
predicate new (ID:t_New, CLASS_NAME:t_Class_name, ACTUAL_PARAMETERS:list[t_Actual_parameter]).

predicate hT_ITERATOR (ID:t_HT_ITERATOR, VALUE:int).
predicate cLASS_NAME (ID:t_CLASS_NAME, VALUE:string).
predicate iNTERFACE_NAME (ID:t_INTERFACE_NAME, VALUE:string).
predicate mETHOD_NAME (ID:t_METHOD_NAME, VALUE:string).
predicate vARIABLE_NAME (ID:t_VARIABLE_NAME, VALUE:string).
predicate lABEL_NAME (ID:t_LABEL_NAME, VALUE:string).
predicate iNT (ID:t_INT, VALUE:int).
predicate rEAL (ID:t_REAL, VALUE:float).
predicate sTRING (ID:t_STRING, VALUE:string).
predicate bOOL (ID:t_BOOL, VALUE:bool).
predicate nIL (ID:t_NIL, VALUE:null).
predicate cAST (ID:t_CAST, VALUE:string).
predicate oP (ID:t_OP, VALUE:string).
predicate cONSTANT_NAME (ID:t_CONSTANT_NAME, VALUE:string).

