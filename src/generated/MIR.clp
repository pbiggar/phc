session mir (PROG:string).

% Type not supplied by Saturn
type null.
type id = int.

% Forward declarations for conjunctive types
type t_mir_PHP_script.
type t_mir_Class_def.
type t_mir_Class_mod.
type t_mir_Interface_def.
type t_mir_Method.
type t_mir_Signature.
type t_mir_Method_mod.
type t_mir_Formal_parameter.
type t_mir_Type.
type t_mir_Attribute.
type t_mir_Attr_mod.
type t_mir_Name_with_default.
type t_mir_Return.
type t_mir_Static_declaration.
type t_mir_Global.
type t_mir_Try.
type t_mir_Catch.
type t_mir_Throw.
type t_mir_Eval_expr.
type t_mir_Branch.
type t_mir_Goto.
type t_mir_Label.
type t_mir_Foreach_reset.
type t_mir_Foreach_next.
type t_mir_Foreach_end.
type t_mir_Foreach_has_key.
type t_mir_Foreach_get_key.
type t_mir_Foreach_get_val.
type t_mir_Assignment.
type t_mir_Cast.
type t_mir_Unary_op.
type t_mir_Bin_op.
type t_mir_Constant.
type t_mir_Instanceof.
type t_mir_Variable.
type t_mir_Reflection.
type t_mir_Pre_op.
type t_mir_Array.
type t_mir_Array_elem.
type t_mir_Method_invocation.
type t_mir_Actual_parameter.
type t_mir_New.


% Forward declarations for disjunctive types
type t_mir_Node.
type t_mir_Statement.
type t_mir_Member.
type t_mir_Expr.
type t_mir_Literal.
type t_mir_Variable_name.
type t_mir_Target.
type t_mir_Method_name.
type t_mir_Class_name.
type t_mir_Identifier.


% Token declarations
type t_mir_HT_ITERATOR ::= t_mir_HT_ITERATOR_id {id}.
type t_mir_CLASS_NAME ::= t_mir_CLASS_NAME_id {id}.
type t_mir_INTERFACE_NAME ::= t_mir_INTERFACE_NAME_id {id}.
type t_mir_METHOD_NAME ::= t_mir_METHOD_NAME_id {id}.
type t_mir_VARIABLE_NAME ::= t_mir_VARIABLE_NAME_id {id}.
type t_mir_LABEL_NAME ::= t_mir_LABEL_NAME_id {id}.
type t_mir_INT ::= t_mir_INT_id {id}.
type t_mir_REAL ::= t_mir_REAL_id {id}.
type t_mir_STRING ::= t_mir_STRING_id {id}.
type t_mir_BOOL ::= t_mir_BOOL_id {id}.
type t_mir_NIL ::= t_mir_NIL_id {id}.
type t_mir_CAST ::= t_mir_CAST_id {id}.
type t_mir_OP ::= t_mir_OP_id {id}.
type t_mir_CONSTANT_NAME ::= t_mir_CONSTANT_NAME_id {id}.


% Conjunctive types
type t_mir_PHP_script ::= t_mir_PHP_script_id {id}.
type t_mir_Class_def ::= t_mir_Class_def_id {id}.
type t_mir_Class_mod ::= t_mir_Class_mod_id {id}.
type t_mir_Interface_def ::= t_mir_Interface_def_id {id}.
type t_mir_Method ::= t_mir_Method_id {id}.
type t_mir_Signature ::= t_mir_Signature_id {id}.
type t_mir_Method_mod ::= t_mir_Method_mod_id {id}.
type t_mir_Formal_parameter ::= t_mir_Formal_parameter_id {id}.
type t_mir_Type ::= t_mir_Type_id {id}.
type t_mir_Attribute ::= t_mir_Attribute_id {id}.
type t_mir_Attr_mod ::= t_mir_Attr_mod_id {id}.
type t_mir_Name_with_default ::= t_mir_Name_with_default_id {id}.
type t_mir_Return ::= t_mir_Return_id {id}.
type t_mir_Static_declaration ::= t_mir_Static_declaration_id {id}.
type t_mir_Global ::= t_mir_Global_id {id}.
type t_mir_Try ::= t_mir_Try_id {id}.
type t_mir_Catch ::= t_mir_Catch_id {id}.
type t_mir_Throw ::= t_mir_Throw_id {id}.
type t_mir_Eval_expr ::= t_mir_Eval_expr_id {id}.
type t_mir_Branch ::= t_mir_Branch_id {id}.
type t_mir_Goto ::= t_mir_Goto_id {id}.
type t_mir_Label ::= t_mir_Label_id {id}.
type t_mir_Foreach_reset ::= t_mir_Foreach_reset_id {id}.
type t_mir_Foreach_next ::= t_mir_Foreach_next_id {id}.
type t_mir_Foreach_end ::= t_mir_Foreach_end_id {id}.
type t_mir_Foreach_has_key ::= t_mir_Foreach_has_key_id {id}.
type t_mir_Foreach_get_key ::= t_mir_Foreach_get_key_id {id}.
type t_mir_Foreach_get_val ::= t_mir_Foreach_get_val_id {id}.
type t_mir_Assignment ::= t_mir_Assignment_id {id}.
type t_mir_Cast ::= t_mir_Cast_id {id}.
type t_mir_Unary_op ::= t_mir_Unary_op_id {id}.
type t_mir_Bin_op ::= t_mir_Bin_op_id {id}.
type t_mir_Constant ::= t_mir_Constant_id {id}.
type t_mir_Instanceof ::= t_mir_Instanceof_id {id}.
type t_mir_Variable ::= t_mir_Variable_id {id}.
type t_mir_Reflection ::= t_mir_Reflection_id {id}.
type t_mir_Pre_op ::= t_mir_Pre_op_id {id}.
type t_mir_Array ::= t_mir_Array_id {id}.
type t_mir_Array_elem ::= t_mir_Array_elem_id {id}.
type t_mir_Method_invocation ::= t_mir_Method_invocation_id {id}.
type t_mir_Actual_parameter ::= t_mir_Actual_parameter_id {id}.
type t_mir_New ::= t_mir_New_id {id}.


% Disjunctive types
type t_mir_Identifier ::= 
		  t_mir_Identifier_t_mir_INTERFACE_NAME_id { t_mir_INTERFACE_NAME } 
		| t_mir_Identifier_t_mir_CLASS_NAME_id { t_mir_CLASS_NAME } 
		| t_mir_Identifier_t_mir_METHOD_NAME_id { t_mir_METHOD_NAME } 
		| t_mir_Identifier_t_mir_VARIABLE_NAME_id { t_mir_VARIABLE_NAME } 
		| t_mir_Identifier_t_mir_CAST_id { t_mir_CAST } 
		| t_mir_Identifier_t_mir_OP_id { t_mir_OP } 
		| t_mir_Identifier_t_mir_CONSTANT_NAME_id { t_mir_CONSTANT_NAME } 
		| t_mir_Identifier_t_mir_LABEL_NAME_id { t_mir_LABEL_NAME } 
		.
type t_mir_Class_name ::= 
		  t_mir_Class_name_t_mir_CLASS_NAME_id { t_mir_CLASS_NAME } 
		| t_mir_Class_name_t_mir_Reflection_id { t_mir_Reflection } 
		.
type t_mir_Method_name ::= 
		  t_mir_Method_name_t_mir_METHOD_NAME_id { t_mir_METHOD_NAME } 
		| t_mir_Method_name_t_mir_Reflection_id { t_mir_Reflection } 
		.
type t_mir_Target ::= 
		  t_mir_Target_t_mir_Assignment_id { t_mir_Assignment } 
		| t_mir_Target_t_mir_Cast_id { t_mir_Cast } 
		| t_mir_Target_t_mir_Unary_op_id { t_mir_Unary_op } 
		| t_mir_Target_t_mir_Bin_op_id { t_mir_Bin_op } 
		| t_mir_Target_t_mir_Constant_id { t_mir_Constant } 
		| t_mir_Target_t_mir_Instanceof_id { t_mir_Instanceof } 
		| t_mir_Target_t_mir_Variable_id { t_mir_Variable } 
		| t_mir_Target_t_mir_Pre_op_id { t_mir_Pre_op } 
		| t_mir_Target_t_mir_Method_invocation_id { t_mir_Method_invocation } 
		| t_mir_Target_t_mir_New_id { t_mir_New } 
		| t_mir_Target_t_mir_INT_id { t_mir_INT } 
		| t_mir_Target_t_mir_REAL_id { t_mir_REAL } 
		| t_mir_Target_t_mir_STRING_id { t_mir_STRING } 
		| t_mir_Target_t_mir_BOOL_id { t_mir_BOOL } 
		| t_mir_Target_t_mir_NIL_id { t_mir_NIL } 
		| t_mir_Target_t_mir_Array_id { t_mir_Array } 
		| t_mir_Target_t_mir_Foreach_has_key_id { t_mir_Foreach_has_key } 
		| t_mir_Target_t_mir_Foreach_get_key_id { t_mir_Foreach_get_key } 
		| t_mir_Target_t_mir_Foreach_get_val_id { t_mir_Foreach_get_val } 
		| t_mir_Target_t_mir_CLASS_NAME_id { t_mir_CLASS_NAME } 
		.
type t_mir_Variable_name ::= 
		  t_mir_Variable_name_t_mir_VARIABLE_NAME_id { t_mir_VARIABLE_NAME } 
		| t_mir_Variable_name_t_mir_Reflection_id { t_mir_Reflection } 
		.
type t_mir_Literal ::= 
		  t_mir_Literal_t_mir_INT_id { t_mir_INT } 
		| t_mir_Literal_t_mir_REAL_id { t_mir_REAL } 
		| t_mir_Literal_t_mir_STRING_id { t_mir_STRING } 
		| t_mir_Literal_t_mir_BOOL_id { t_mir_BOOL } 
		| t_mir_Literal_t_mir_NIL_id { t_mir_NIL } 
		.
type t_mir_Expr ::= 
		  t_mir_Expr_t_mir_Assignment_id { t_mir_Assignment } 
		| t_mir_Expr_t_mir_Cast_id { t_mir_Cast } 
		| t_mir_Expr_t_mir_Unary_op_id { t_mir_Unary_op } 
		| t_mir_Expr_t_mir_Bin_op_id { t_mir_Bin_op } 
		| t_mir_Expr_t_mir_Constant_id { t_mir_Constant } 
		| t_mir_Expr_t_mir_Instanceof_id { t_mir_Instanceof } 
		| t_mir_Expr_t_mir_Variable_id { t_mir_Variable } 
		| t_mir_Expr_t_mir_Pre_op_id { t_mir_Pre_op } 
		| t_mir_Expr_t_mir_Method_invocation_id { t_mir_Method_invocation } 
		| t_mir_Expr_t_mir_New_id { t_mir_New } 
		| t_mir_Expr_t_mir_INT_id { t_mir_INT } 
		| t_mir_Expr_t_mir_REAL_id { t_mir_REAL } 
		| t_mir_Expr_t_mir_STRING_id { t_mir_STRING } 
		| t_mir_Expr_t_mir_BOOL_id { t_mir_BOOL } 
		| t_mir_Expr_t_mir_NIL_id { t_mir_NIL } 
		| t_mir_Expr_t_mir_Array_id { t_mir_Array } 
		| t_mir_Expr_t_mir_Foreach_has_key_id { t_mir_Foreach_has_key } 
		| t_mir_Expr_t_mir_Foreach_get_key_id { t_mir_Foreach_get_key } 
		| t_mir_Expr_t_mir_Foreach_get_val_id { t_mir_Foreach_get_val } 
		.
type t_mir_Member ::= 
		  t_mir_Member_t_mir_Method_id { t_mir_Method } 
		| t_mir_Member_t_mir_Attribute_id { t_mir_Attribute } 
		.
type t_mir_Statement ::= 
		  t_mir_Statement_t_mir_Class_def_id { t_mir_Class_def } 
		| t_mir_Statement_t_mir_Interface_def_id { t_mir_Interface_def } 
		| t_mir_Statement_t_mir_Method_id { t_mir_Method } 
		| t_mir_Statement_t_mir_Return_id { t_mir_Return } 
		| t_mir_Statement_t_mir_Static_declaration_id { t_mir_Static_declaration } 
		| t_mir_Statement_t_mir_Global_id { t_mir_Global } 
		| t_mir_Statement_t_mir_Try_id { t_mir_Try } 
		| t_mir_Statement_t_mir_Throw_id { t_mir_Throw } 
		| t_mir_Statement_t_mir_Eval_expr_id { t_mir_Eval_expr } 
		| t_mir_Statement_t_mir_Label_id { t_mir_Label } 
		| t_mir_Statement_t_mir_Goto_id { t_mir_Goto } 
		| t_mir_Statement_t_mir_Branch_id { t_mir_Branch } 
		| t_mir_Statement_t_mir_Foreach_next_id { t_mir_Foreach_next } 
		| t_mir_Statement_t_mir_Foreach_reset_id { t_mir_Foreach_reset } 
		| t_mir_Statement_t_mir_Foreach_end_id { t_mir_Foreach_end } 
		.
type t_mir_Node ::= 
		  t_mir_Node_t_mir_PHP_script_id { t_mir_PHP_script } 
		| t_mir_Node_t_mir_Class_def_id { t_mir_Class_def } 
		| t_mir_Node_t_mir_Interface_def_id { t_mir_Interface_def } 
		| t_mir_Node_t_mir_Method_id { t_mir_Method } 
		| t_mir_Node_t_mir_Return_id { t_mir_Return } 
		| t_mir_Node_t_mir_Static_declaration_id { t_mir_Static_declaration } 
		| t_mir_Node_t_mir_Global_id { t_mir_Global } 
		| t_mir_Node_t_mir_Try_id { t_mir_Try } 
		| t_mir_Node_t_mir_Throw_id { t_mir_Throw } 
		| t_mir_Node_t_mir_Eval_expr_id { t_mir_Eval_expr } 
		| t_mir_Node_t_mir_Label_id { t_mir_Label } 
		| t_mir_Node_t_mir_Goto_id { t_mir_Goto } 
		| t_mir_Node_t_mir_Branch_id { t_mir_Branch } 
		| t_mir_Node_t_mir_Foreach_next_id { t_mir_Foreach_next } 
		| t_mir_Node_t_mir_Foreach_reset_id { t_mir_Foreach_reset } 
		| t_mir_Node_t_mir_Foreach_end_id { t_mir_Foreach_end } 
		| t_mir_Node_t_mir_Class_mod_id { t_mir_Class_mod } 
		| t_mir_Node_t_mir_Attribute_id { t_mir_Attribute } 
		| t_mir_Node_t_mir_Signature_id { t_mir_Signature } 
		| t_mir_Node_t_mir_Method_mod_id { t_mir_Method_mod } 
		| t_mir_Node_t_mir_Formal_parameter_id { t_mir_Formal_parameter } 
		| t_mir_Node_t_mir_Type_id { t_mir_Type } 
		| t_mir_Node_t_mir_Attr_mod_id { t_mir_Attr_mod } 
		| t_mir_Node_t_mir_Name_with_default_id { t_mir_Name_with_default } 
		| t_mir_Node_t_mir_Catch_id { t_mir_Catch } 
		| t_mir_Node_t_mir_VARIABLE_NAME_id { t_mir_VARIABLE_NAME } 
		| t_mir_Node_t_mir_Reflection_id { t_mir_Reflection } 
		| t_mir_Node_t_mir_Assignment_id { t_mir_Assignment } 
		| t_mir_Node_t_mir_Cast_id { t_mir_Cast } 
		| t_mir_Node_t_mir_Unary_op_id { t_mir_Unary_op } 
		| t_mir_Node_t_mir_Bin_op_id { t_mir_Bin_op } 
		| t_mir_Node_t_mir_Constant_id { t_mir_Constant } 
		| t_mir_Node_t_mir_Instanceof_id { t_mir_Instanceof } 
		| t_mir_Node_t_mir_Variable_id { t_mir_Variable } 
		| t_mir_Node_t_mir_Pre_op_id { t_mir_Pre_op } 
		| t_mir_Node_t_mir_Method_invocation_id { t_mir_Method_invocation } 
		| t_mir_Node_t_mir_New_id { t_mir_New } 
		| t_mir_Node_t_mir_INT_id { t_mir_INT } 
		| t_mir_Node_t_mir_REAL_id { t_mir_REAL } 
		| t_mir_Node_t_mir_STRING_id { t_mir_STRING } 
		| t_mir_Node_t_mir_BOOL_id { t_mir_BOOL } 
		| t_mir_Node_t_mir_NIL_id { t_mir_NIL } 
		| t_mir_Node_t_mir_Array_id { t_mir_Array } 
		| t_mir_Node_t_mir_Foreach_has_key_id { t_mir_Foreach_has_key } 
		| t_mir_Node_t_mir_Foreach_get_key_id { t_mir_Foreach_get_key } 
		| t_mir_Node_t_mir_Foreach_get_val_id { t_mir_Foreach_get_val } 
		| t_mir_Node_t_mir_CLASS_NAME_id { t_mir_CLASS_NAME } 
		| t_mir_Node_t_mir_Array_elem_id { t_mir_Array_elem } 
		| t_mir_Node_t_mir_METHOD_NAME_id { t_mir_METHOD_NAME } 
		| t_mir_Node_t_mir_Actual_parameter_id { t_mir_Actual_parameter } 
		| t_mir_Node_t_mir_INTERFACE_NAME_id { t_mir_INTERFACE_NAME } 
		| t_mir_Node_t_mir_CAST_id { t_mir_CAST } 
		| t_mir_Node_t_mir_OP_id { t_mir_OP } 
		| t_mir_Node_t_mir_CONSTANT_NAME_id { t_mir_CONSTANT_NAME } 
		| t_mir_Node_t_mir_LABEL_NAME_id { t_mir_LABEL_NAME } 
		| t_mir_Node_t_mir_HT_ITERATOR_id { t_mir_HT_ITERATOR } 
		.


% Predicates
predicate mir_PHP_script (ID:t_mir_PHP_script, STATEMENTS:list[t_mir_Statement]).
predicate mir_Class_def (ID:t_mir_Class_def, CLASS_MOD:t_mir_Class_mod, CLASS_NAME:t_mir_CLASS_NAME, EXTENDS:maybe[t_mir_CLASS_NAME], IMPLEMENTS:list[t_mir_INTERFACE_NAME], MEMBERS:list[t_mir_Member]).
predicate mir_Class_mod (ID:t_mir_Class_mod, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate mir_Interface_def (ID:t_mir_Interface_def, INTERFACE_NAME:t_mir_INTERFACE_NAME, EXTENDS:list[t_mir_INTERFACE_NAME], MEMBERS:list[t_mir_Member]).
predicate mir_Method (ID:t_mir_Method, SIGNATURE:t_mir_Signature, STATEMENTS:maybe[list[t_mir_Statement]]).
predicate mir_Signature (ID:t_mir_Signature, METHOD_MOD:t_mir_Method_mod, IS_REF:bool, METHOD_NAME:t_mir_METHOD_NAME, FORMAL_PARAMETERS:list[t_mir_Formal_parameter]).
predicate mir_Method_mod (ID:t_mir_Method_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate mir_Formal_parameter (ID:t_mir_Formal_parameter, TYPE:t_mir_Type, IS_REF:bool, VAR:t_mir_Name_with_default).
predicate mir_Type (ID:t_mir_Type, CLASS_NAME:maybe[t_mir_CLASS_NAME]).
predicate mir_Attribute (ID:t_mir_Attribute, ATTR_MOD:t_mir_Attr_mod, VAR:t_mir_Name_with_default).
predicate mir_Attr_mod (ID:t_mir_Attr_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_CONST:bool).
predicate mir_Name_with_default (ID:t_mir_Name_with_default, VARIABLE_NAME:t_mir_VARIABLE_NAME, EXPR:maybe[t_mir_Expr]).
predicate mir_Return (ID:t_mir_Return, EXPR:maybe[t_mir_Expr]).
predicate mir_Static_declaration (ID:t_mir_Static_declaration, VAR:t_mir_Name_with_default).
predicate mir_Global (ID:t_mir_Global, VARIABLE_NAME:t_mir_Variable_name).
predicate mir_Try (ID:t_mir_Try, STATEMENTS:list[t_mir_Statement], CATCHES:list[t_mir_Catch]).
predicate mir_Catch (ID:t_mir_Catch, CLASS_NAME:t_mir_CLASS_NAME, VARIABLE_NAME:t_mir_VARIABLE_NAME, STATEMENTS:list[t_mir_Statement]).
predicate mir_Throw (ID:t_mir_Throw, EXPR:t_mir_Expr).
predicate mir_Eval_expr (ID:t_mir_Eval_expr, EXPR:t_mir_Expr).
predicate mir_Branch (ID:t_mir_Branch, VARIABLE_NAME:t_mir_VARIABLE_NAME, IFTRUE:t_mir_LABEL_NAME, IFFALSE:t_mir_LABEL_NAME).
predicate mir_Goto (ID:t_mir_Goto, LABEL_NAME:t_mir_LABEL_NAME).
predicate mir_Label (ID:t_mir_Label, LABEL_NAME:t_mir_LABEL_NAME).
predicate mir_Foreach_reset (ID:t_mir_Foreach_reset, ARRAY:t_mir_VARIABLE_NAME, ITER:t_mir_HT_ITERATOR).
predicate mir_Foreach_next (ID:t_mir_Foreach_next, ARRAY:t_mir_VARIABLE_NAME, ITER:t_mir_HT_ITERATOR).
predicate mir_Foreach_end (ID:t_mir_Foreach_end, ARRAY:t_mir_VARIABLE_NAME, ITER:t_mir_HT_ITERATOR).
predicate mir_Foreach_has_key (ID:t_mir_Foreach_has_key, ARRAY:t_mir_VARIABLE_NAME, ITER:t_mir_HT_ITERATOR).
predicate mir_Foreach_get_key (ID:t_mir_Foreach_get_key, ARRAY:t_mir_VARIABLE_NAME, ITER:t_mir_HT_ITERATOR).
predicate mir_Foreach_get_val (ID:t_mir_Foreach_get_val, ARRAY:t_mir_VARIABLE_NAME, KEY:t_mir_VARIABLE_NAME, ITER:t_mir_HT_ITERATOR).
predicate mir_Assignment (ID:t_mir_Assignment, VARIABLE:t_mir_Variable, IS_REF:bool, EXPR:t_mir_Expr).
predicate mir_Cast (ID:t_mir_Cast, CAST:t_mir_CAST, VARIABLE_NAME:t_mir_VARIABLE_NAME).
predicate mir_Unary_op (ID:t_mir_Unary_op, OP:t_mir_OP, VARIABLE_NAME:t_mir_VARIABLE_NAME).
predicate mir_Bin_op (ID:t_mir_Bin_op, LEFT:t_mir_VARIABLE_NAME, OP:t_mir_OP, RIGHT:t_mir_VARIABLE_NAME).
predicate mir_Constant (ID:t_mir_Constant, CLASS_NAME:maybe[t_mir_CLASS_NAME], CONSTANT_NAME:t_mir_CONSTANT_NAME).
predicate mir_Instanceof (ID:t_mir_Instanceof, VARIABLE_NAME:t_mir_VARIABLE_NAME, CLASS_NAME:t_mir_Class_name).
predicate mir_Variable (ID:t_mir_Variable, TARGET:maybe[t_mir_Target], VARIABLE_NAME:t_mir_Variable_name, ARRAY_INDICES:list[maybe[t_mir_VARIABLE_NAME]]).
predicate mir_Reflection (ID:t_mir_Reflection, VARIABLE_NAME:t_mir_VARIABLE_NAME).
predicate mir_Pre_op (ID:t_mir_Pre_op, OP:t_mir_OP, VARIABLE:t_mir_Variable).
predicate mir_Array (ID:t_mir_Array, ARRAY_ELEMS:list[t_mir_Array_elem]).
predicate mir_Array_elem (ID:t_mir_Array_elem, KEY:maybe[t_mir_Expr], IS_REF:bool, VAL:t_mir_Expr).
predicate mir_Method_invocation (ID:t_mir_Method_invocation, TARGET:maybe[t_mir_Target], METHOD_NAME:t_mir_Method_name, ACTUAL_PARAMETERS:list[t_mir_Actual_parameter]).
predicate mir_Actual_parameter (ID:t_mir_Actual_parameter, IS_REF:bool, TARGET:maybe[t_mir_Target], VARIABLE_NAME:t_mir_Variable_name, ARRAY_INDICES:list[maybe[t_mir_VARIABLE_NAME]]).
predicate mir_New (ID:t_mir_New, CLASS_NAME:t_mir_Class_name, ACTUAL_PARAMETERS:list[t_mir_Actual_parameter]).

predicate mir_HT_ITERATOR (ID:t_mir_HT_ITERATOR, VALUE:int).
predicate mir_CLASS_NAME (ID:t_mir_CLASS_NAME, VALUE:string).
predicate mir_INTERFACE_NAME (ID:t_mir_INTERFACE_NAME, VALUE:string).
predicate mir_METHOD_NAME (ID:t_mir_METHOD_NAME, VALUE:string).
predicate mir_VARIABLE_NAME (ID:t_mir_VARIABLE_NAME, VALUE:string).
predicate mir_LABEL_NAME (ID:t_mir_LABEL_NAME, VALUE:string).
predicate mir_INT (ID:t_mir_INT, VALUE:int).
predicate mir_REAL (ID:t_mir_REAL, VALUE:float).
predicate mir_STRING (ID:t_mir_STRING, VALUE:string).
predicate mir_BOOL (ID:t_mir_BOOL, VALUE:bool).
predicate mir_NIL (ID:t_mir_NIL, VALUE:null).
predicate mir_CAST (ID:t_mir_CAST, VALUE:string).
predicate mir_OP (ID:t_mir_OP, VALUE:string).
predicate mir_CONSTANT_NAME (ID:t_mir_CONSTANT_NAME, VALUE:string).

