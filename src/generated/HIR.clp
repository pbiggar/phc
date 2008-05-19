session hir (PROG:string).

% Type not supplied by Saturn
type null.
type id = int.

% Forward declarations for conjunctive types
type t_hir_PHP_script.
type t_hir_Class_def.
type t_hir_Class_mod.
type t_hir_Interface_def.
type t_hir_Method.
type t_hir_Signature.
type t_hir_Method_mod.
type t_hir_Formal_parameter.
type t_hir_Type.
type t_hir_Attribute.
type t_hir_Attr_mod.
type t_hir_Name_with_default.
type t_hir_If.
type t_hir_Loop.
type t_hir_Foreach.
type t_hir_Break.
type t_hir_Continue.
type t_hir_Return.
type t_hir_Static_declaration.
type t_hir_Global.
type t_hir_Try.
type t_hir_Catch.
type t_hir_Throw.
type t_hir_Eval_expr.
type t_hir_Branch.
type t_hir_Goto.
type t_hir_Label.
type t_hir_Foreach_reset.
type t_hir_Foreach_next.
type t_hir_Foreach_end.
type t_hir_Foreach_has_key.
type t_hir_Foreach_get_key.
type t_hir_Foreach_get_val.
type t_hir_Assignment.
type t_hir_Op_assignment.
type t_hir_Cast.
type t_hir_Unary_op.
type t_hir_Bin_op.
type t_hir_Constant.
type t_hir_Instanceof.
type t_hir_Variable.
type t_hir_Reflection.
type t_hir_Pre_op.
type t_hir_Array.
type t_hir_Array_elem.
type t_hir_Method_invocation.
type t_hir_Actual_parameter.
type t_hir_New.


% Forward declarations for disjunctive types
type t_hir_Node.
type t_hir_Statement.
type t_hir_Member.
type t_hir_Expr.
type t_hir_Literal.
type t_hir_Variable_name.
type t_hir_Target.
type t_hir_Method_name.
type t_hir_Class_name.
type t_hir_Identifier.


% Token declarations
type t_hir_HT_ITERATOR ::= t_hir_HT_ITERATOR_id {id}.
type t_hir_CLASS_NAME ::= t_hir_CLASS_NAME_id {id}.
type t_hir_INTERFACE_NAME ::= t_hir_INTERFACE_NAME_id {id}.
type t_hir_METHOD_NAME ::= t_hir_METHOD_NAME_id {id}.
type t_hir_VARIABLE_NAME ::= t_hir_VARIABLE_NAME_id {id}.
type t_hir_LABEL_NAME ::= t_hir_LABEL_NAME_id {id}.
type t_hir_INT ::= t_hir_INT_id {id}.
type t_hir_REAL ::= t_hir_REAL_id {id}.
type t_hir_STRING ::= t_hir_STRING_id {id}.
type t_hir_BOOL ::= t_hir_BOOL_id {id}.
type t_hir_NIL ::= t_hir_NIL_id {id}.
type t_hir_OP ::= t_hir_OP_id {id}.
type t_hir_CAST ::= t_hir_CAST_id {id}.
type t_hir_CONSTANT_NAME ::= t_hir_CONSTANT_NAME_id {id}.


% Conjunctive types
type t_hir_PHP_script ::= t_hir_PHP_script_id {id}.
type t_hir_Class_def ::= t_hir_Class_def_id {id}.
type t_hir_Class_mod ::= t_hir_Class_mod_id {id}.
type t_hir_Interface_def ::= t_hir_Interface_def_id {id}.
type t_hir_Method ::= t_hir_Method_id {id}.
type t_hir_Signature ::= t_hir_Signature_id {id}.
type t_hir_Method_mod ::= t_hir_Method_mod_id {id}.
type t_hir_Formal_parameter ::= t_hir_Formal_parameter_id {id}.
type t_hir_Type ::= t_hir_Type_id {id}.
type t_hir_Attribute ::= t_hir_Attribute_id {id}.
type t_hir_Attr_mod ::= t_hir_Attr_mod_id {id}.
type t_hir_Name_with_default ::= t_hir_Name_with_default_id {id}.
type t_hir_If ::= t_hir_If_id {id}.
type t_hir_Loop ::= t_hir_Loop_id {id}.
type t_hir_Foreach ::= t_hir_Foreach_id {id}.
type t_hir_Break ::= t_hir_Break_id {id}.
type t_hir_Continue ::= t_hir_Continue_id {id}.
type t_hir_Return ::= t_hir_Return_id {id}.
type t_hir_Static_declaration ::= t_hir_Static_declaration_id {id}.
type t_hir_Global ::= t_hir_Global_id {id}.
type t_hir_Try ::= t_hir_Try_id {id}.
type t_hir_Catch ::= t_hir_Catch_id {id}.
type t_hir_Throw ::= t_hir_Throw_id {id}.
type t_hir_Eval_expr ::= t_hir_Eval_expr_id {id}.
type t_hir_Branch ::= t_hir_Branch_id {id}.
type t_hir_Goto ::= t_hir_Goto_id {id}.
type t_hir_Label ::= t_hir_Label_id {id}.
type t_hir_Foreach_reset ::= t_hir_Foreach_reset_id {id}.
type t_hir_Foreach_next ::= t_hir_Foreach_next_id {id}.
type t_hir_Foreach_end ::= t_hir_Foreach_end_id {id}.
type t_hir_Foreach_has_key ::= t_hir_Foreach_has_key_id {id}.
type t_hir_Foreach_get_key ::= t_hir_Foreach_get_key_id {id}.
type t_hir_Foreach_get_val ::= t_hir_Foreach_get_val_id {id}.
type t_hir_Assignment ::= t_hir_Assignment_id {id}.
type t_hir_Op_assignment ::= t_hir_Op_assignment_id {id}.
type t_hir_Cast ::= t_hir_Cast_id {id}.
type t_hir_Unary_op ::= t_hir_Unary_op_id {id}.
type t_hir_Bin_op ::= t_hir_Bin_op_id {id}.
type t_hir_Constant ::= t_hir_Constant_id {id}.
type t_hir_Instanceof ::= t_hir_Instanceof_id {id}.
type t_hir_Variable ::= t_hir_Variable_id {id}.
type t_hir_Reflection ::= t_hir_Reflection_id {id}.
type t_hir_Pre_op ::= t_hir_Pre_op_id {id}.
type t_hir_Array ::= t_hir_Array_id {id}.
type t_hir_Array_elem ::= t_hir_Array_elem_id {id}.
type t_hir_Method_invocation ::= t_hir_Method_invocation_id {id}.
type t_hir_Actual_parameter ::= t_hir_Actual_parameter_id {id}.
type t_hir_New ::= t_hir_New_id {id}.


% Disjunctive types
type t_hir_Identifier ::= 
		  t_hir_Identifier_t_hir_INTERFACE_NAME_id { t_hir_INTERFACE_NAME } 
		| t_hir_Identifier_t_hir_CLASS_NAME_id { t_hir_CLASS_NAME } 
		| t_hir_Identifier_t_hir_METHOD_NAME_id { t_hir_METHOD_NAME } 
		| t_hir_Identifier_t_hir_VARIABLE_NAME_id { t_hir_VARIABLE_NAME } 
		| t_hir_Identifier_t_hir_CAST_id { t_hir_CAST } 
		| t_hir_Identifier_t_hir_OP_id { t_hir_OP } 
		| t_hir_Identifier_t_hir_CONSTANT_NAME_id { t_hir_CONSTANT_NAME } 
		| t_hir_Identifier_t_hir_LABEL_NAME_id { t_hir_LABEL_NAME } 
		.
type t_hir_Class_name ::= 
		  t_hir_Class_name_t_hir_CLASS_NAME_id { t_hir_CLASS_NAME } 
		| t_hir_Class_name_t_hir_Reflection_id { t_hir_Reflection } 
		.
type t_hir_Method_name ::= 
		  t_hir_Method_name_t_hir_METHOD_NAME_id { t_hir_METHOD_NAME } 
		| t_hir_Method_name_t_hir_Reflection_id { t_hir_Reflection } 
		.
type t_hir_Target ::= 
		  t_hir_Target_t_hir_Assignment_id { t_hir_Assignment } 
		| t_hir_Target_t_hir_Cast_id { t_hir_Cast } 
		| t_hir_Target_t_hir_Unary_op_id { t_hir_Unary_op } 
		| t_hir_Target_t_hir_Bin_op_id { t_hir_Bin_op } 
		| t_hir_Target_t_hir_Constant_id { t_hir_Constant } 
		| t_hir_Target_t_hir_Instanceof_id { t_hir_Instanceof } 
		| t_hir_Target_t_hir_Variable_id { t_hir_Variable } 
		| t_hir_Target_t_hir_Pre_op_id { t_hir_Pre_op } 
		| t_hir_Target_t_hir_Method_invocation_id { t_hir_Method_invocation } 
		| t_hir_Target_t_hir_New_id { t_hir_New } 
		| t_hir_Target_t_hir_INT_id { t_hir_INT } 
		| t_hir_Target_t_hir_REAL_id { t_hir_REAL } 
		| t_hir_Target_t_hir_STRING_id { t_hir_STRING } 
		| t_hir_Target_t_hir_BOOL_id { t_hir_BOOL } 
		| t_hir_Target_t_hir_NIL_id { t_hir_NIL } 
		| t_hir_Target_t_hir_Op_assignment_id { t_hir_Op_assignment } 
		| t_hir_Target_t_hir_Array_id { t_hir_Array } 
		| t_hir_Target_t_hir_Foreach_has_key_id { t_hir_Foreach_has_key } 
		| t_hir_Target_t_hir_Foreach_get_key_id { t_hir_Foreach_get_key } 
		| t_hir_Target_t_hir_Foreach_get_val_id { t_hir_Foreach_get_val } 
		| t_hir_Target_t_hir_CLASS_NAME_id { t_hir_CLASS_NAME } 
		.
type t_hir_Variable_name ::= 
		  t_hir_Variable_name_t_hir_VARIABLE_NAME_id { t_hir_VARIABLE_NAME } 
		| t_hir_Variable_name_t_hir_Reflection_id { t_hir_Reflection } 
		.
type t_hir_Literal ::= 
		  t_hir_Literal_t_hir_INT_id { t_hir_INT } 
		| t_hir_Literal_t_hir_REAL_id { t_hir_REAL } 
		| t_hir_Literal_t_hir_STRING_id { t_hir_STRING } 
		| t_hir_Literal_t_hir_BOOL_id { t_hir_BOOL } 
		| t_hir_Literal_t_hir_NIL_id { t_hir_NIL } 
		.
type t_hir_Expr ::= 
		  t_hir_Expr_t_hir_Assignment_id { t_hir_Assignment } 
		| t_hir_Expr_t_hir_Cast_id { t_hir_Cast } 
		| t_hir_Expr_t_hir_Unary_op_id { t_hir_Unary_op } 
		| t_hir_Expr_t_hir_Bin_op_id { t_hir_Bin_op } 
		| t_hir_Expr_t_hir_Constant_id { t_hir_Constant } 
		| t_hir_Expr_t_hir_Instanceof_id { t_hir_Instanceof } 
		| t_hir_Expr_t_hir_Variable_id { t_hir_Variable } 
		| t_hir_Expr_t_hir_Pre_op_id { t_hir_Pre_op } 
		| t_hir_Expr_t_hir_Method_invocation_id { t_hir_Method_invocation } 
		| t_hir_Expr_t_hir_New_id { t_hir_New } 
		| t_hir_Expr_t_hir_INT_id { t_hir_INT } 
		| t_hir_Expr_t_hir_REAL_id { t_hir_REAL } 
		| t_hir_Expr_t_hir_STRING_id { t_hir_STRING } 
		| t_hir_Expr_t_hir_BOOL_id { t_hir_BOOL } 
		| t_hir_Expr_t_hir_NIL_id { t_hir_NIL } 
		| t_hir_Expr_t_hir_Op_assignment_id { t_hir_Op_assignment } 
		| t_hir_Expr_t_hir_Array_id { t_hir_Array } 
		| t_hir_Expr_t_hir_Foreach_has_key_id { t_hir_Foreach_has_key } 
		| t_hir_Expr_t_hir_Foreach_get_key_id { t_hir_Foreach_get_key } 
		| t_hir_Expr_t_hir_Foreach_get_val_id { t_hir_Foreach_get_val } 
		.
type t_hir_Member ::= 
		  t_hir_Member_t_hir_Method_id { t_hir_Method } 
		| t_hir_Member_t_hir_Attribute_id { t_hir_Attribute } 
		.
type t_hir_Statement ::= 
		  t_hir_Statement_t_hir_Class_def_id { t_hir_Class_def } 
		| t_hir_Statement_t_hir_Interface_def_id { t_hir_Interface_def } 
		| t_hir_Statement_t_hir_Method_id { t_hir_Method } 
		| t_hir_Statement_t_hir_Return_id { t_hir_Return } 
		| t_hir_Statement_t_hir_Static_declaration_id { t_hir_Static_declaration } 
		| t_hir_Statement_t_hir_Global_id { t_hir_Global } 
		| t_hir_Statement_t_hir_Try_id { t_hir_Try } 
		| t_hir_Statement_t_hir_Throw_id { t_hir_Throw } 
		| t_hir_Statement_t_hir_Eval_expr_id { t_hir_Eval_expr } 
		| t_hir_Statement_t_hir_If_id { t_hir_If } 
		| t_hir_Statement_t_hir_Loop_id { t_hir_Loop } 
		| t_hir_Statement_t_hir_Foreach_id { t_hir_Foreach } 
		| t_hir_Statement_t_hir_Break_id { t_hir_Break } 
		| t_hir_Statement_t_hir_Continue_id { t_hir_Continue } 
		| t_hir_Statement_t_hir_Label_id { t_hir_Label } 
		| t_hir_Statement_t_hir_Goto_id { t_hir_Goto } 
		| t_hir_Statement_t_hir_Branch_id { t_hir_Branch } 
		| t_hir_Statement_t_hir_Foreach_next_id { t_hir_Foreach_next } 
		| t_hir_Statement_t_hir_Foreach_reset_id { t_hir_Foreach_reset } 
		| t_hir_Statement_t_hir_Foreach_end_id { t_hir_Foreach_end } 
		.
type t_hir_Node ::= 
		  t_hir_Node_t_hir_PHP_script_id { t_hir_PHP_script } 
		| t_hir_Node_t_hir_Class_def_id { t_hir_Class_def } 
		| t_hir_Node_t_hir_Interface_def_id { t_hir_Interface_def } 
		| t_hir_Node_t_hir_Method_id { t_hir_Method } 
		| t_hir_Node_t_hir_Return_id { t_hir_Return } 
		| t_hir_Node_t_hir_Static_declaration_id { t_hir_Static_declaration } 
		| t_hir_Node_t_hir_Global_id { t_hir_Global } 
		| t_hir_Node_t_hir_Try_id { t_hir_Try } 
		| t_hir_Node_t_hir_Throw_id { t_hir_Throw } 
		| t_hir_Node_t_hir_Eval_expr_id { t_hir_Eval_expr } 
		| t_hir_Node_t_hir_If_id { t_hir_If } 
		| t_hir_Node_t_hir_Loop_id { t_hir_Loop } 
		| t_hir_Node_t_hir_Foreach_id { t_hir_Foreach } 
		| t_hir_Node_t_hir_Break_id { t_hir_Break } 
		| t_hir_Node_t_hir_Continue_id { t_hir_Continue } 
		| t_hir_Node_t_hir_Label_id { t_hir_Label } 
		| t_hir_Node_t_hir_Goto_id { t_hir_Goto } 
		| t_hir_Node_t_hir_Branch_id { t_hir_Branch } 
		| t_hir_Node_t_hir_Foreach_next_id { t_hir_Foreach_next } 
		| t_hir_Node_t_hir_Foreach_reset_id { t_hir_Foreach_reset } 
		| t_hir_Node_t_hir_Foreach_end_id { t_hir_Foreach_end } 
		| t_hir_Node_t_hir_Class_mod_id { t_hir_Class_mod } 
		| t_hir_Node_t_hir_Attribute_id { t_hir_Attribute } 
		| t_hir_Node_t_hir_Signature_id { t_hir_Signature } 
		| t_hir_Node_t_hir_Method_mod_id { t_hir_Method_mod } 
		| t_hir_Node_t_hir_Formal_parameter_id { t_hir_Formal_parameter } 
		| t_hir_Node_t_hir_Type_id { t_hir_Type } 
		| t_hir_Node_t_hir_Attr_mod_id { t_hir_Attr_mod } 
		| t_hir_Node_t_hir_Name_with_default_id { t_hir_Name_with_default } 
		| t_hir_Node_t_hir_Catch_id { t_hir_Catch } 
		| t_hir_Node_t_hir_VARIABLE_NAME_id { t_hir_VARIABLE_NAME } 
		| t_hir_Node_t_hir_Reflection_id { t_hir_Reflection } 
		| t_hir_Node_t_hir_Assignment_id { t_hir_Assignment } 
		| t_hir_Node_t_hir_Cast_id { t_hir_Cast } 
		| t_hir_Node_t_hir_Unary_op_id { t_hir_Unary_op } 
		| t_hir_Node_t_hir_Bin_op_id { t_hir_Bin_op } 
		| t_hir_Node_t_hir_Constant_id { t_hir_Constant } 
		| t_hir_Node_t_hir_Instanceof_id { t_hir_Instanceof } 
		| t_hir_Node_t_hir_Variable_id { t_hir_Variable } 
		| t_hir_Node_t_hir_Pre_op_id { t_hir_Pre_op } 
		| t_hir_Node_t_hir_Method_invocation_id { t_hir_Method_invocation } 
		| t_hir_Node_t_hir_New_id { t_hir_New } 
		| t_hir_Node_t_hir_INT_id { t_hir_INT } 
		| t_hir_Node_t_hir_REAL_id { t_hir_REAL } 
		| t_hir_Node_t_hir_STRING_id { t_hir_STRING } 
		| t_hir_Node_t_hir_BOOL_id { t_hir_BOOL } 
		| t_hir_Node_t_hir_NIL_id { t_hir_NIL } 
		| t_hir_Node_t_hir_Op_assignment_id { t_hir_Op_assignment } 
		| t_hir_Node_t_hir_Array_id { t_hir_Array } 
		| t_hir_Node_t_hir_Foreach_has_key_id { t_hir_Foreach_has_key } 
		| t_hir_Node_t_hir_Foreach_get_key_id { t_hir_Foreach_get_key } 
		| t_hir_Node_t_hir_Foreach_get_val_id { t_hir_Foreach_get_val } 
		| t_hir_Node_t_hir_CLASS_NAME_id { t_hir_CLASS_NAME } 
		| t_hir_Node_t_hir_Array_elem_id { t_hir_Array_elem } 
		| t_hir_Node_t_hir_METHOD_NAME_id { t_hir_METHOD_NAME } 
		| t_hir_Node_t_hir_Actual_parameter_id { t_hir_Actual_parameter } 
		| t_hir_Node_t_hir_INTERFACE_NAME_id { t_hir_INTERFACE_NAME } 
		| t_hir_Node_t_hir_CAST_id { t_hir_CAST } 
		| t_hir_Node_t_hir_OP_id { t_hir_OP } 
		| t_hir_Node_t_hir_CONSTANT_NAME_id { t_hir_CONSTANT_NAME } 
		| t_hir_Node_t_hir_LABEL_NAME_id { t_hir_LABEL_NAME } 
		| t_hir_Node_t_hir_HT_ITERATOR_id { t_hir_HT_ITERATOR } 
		.


% Predicates
predicate hir_PHP_script (ID:t_hir_PHP_script, STATEMENTS:list[t_hir_Statement]).
predicate hir_Class_def (ID:t_hir_Class_def, CLASS_MOD:t_hir_Class_mod, CLASS_NAME:t_hir_CLASS_NAME, EXTENDS:maybe[t_hir_CLASS_NAME], IMPLEMENTS:list[t_hir_INTERFACE_NAME], MEMBERS:list[t_hir_Member]).
predicate hir_Class_mod (ID:t_hir_Class_mod, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate hir_Interface_def (ID:t_hir_Interface_def, INTERFACE_NAME:t_hir_INTERFACE_NAME, EXTENDS:list[t_hir_INTERFACE_NAME], MEMBERS:list[t_hir_Member]).
predicate hir_Method (ID:t_hir_Method, SIGNATURE:t_hir_Signature, STATEMENTS:maybe[list[t_hir_Statement]]).
predicate hir_Signature (ID:t_hir_Signature, METHOD_MOD:t_hir_Method_mod, IS_REF:bool, METHOD_NAME:t_hir_METHOD_NAME, FORMAL_PARAMETERS:list[t_hir_Formal_parameter]).
predicate hir_Method_mod (ID:t_hir_Method_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate hir_Formal_parameter (ID:t_hir_Formal_parameter, TYPE:t_hir_Type, IS_REF:bool, VAR:t_hir_Name_with_default).
predicate hir_Type (ID:t_hir_Type, CLASS_NAME:maybe[t_hir_CLASS_NAME]).
predicate hir_Attribute (ID:t_hir_Attribute, ATTR_MOD:t_hir_Attr_mod, VAR:t_hir_Name_with_default).
predicate hir_Attr_mod (ID:t_hir_Attr_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_CONST:bool).
predicate hir_Name_with_default (ID:t_hir_Name_with_default, VARIABLE_NAME:t_hir_VARIABLE_NAME, EXPR:maybe[t_hir_Expr]).
predicate hir_If (ID:t_hir_If, VARIABLE_NAME:t_hir_VARIABLE_NAME, IFTRUE:list[t_hir_Statement], IFFALSE:list[t_hir_Statement]).
predicate hir_Loop (ID:t_hir_Loop, STATEMENTS:list[t_hir_Statement]).
predicate hir_Foreach (ID:t_hir_Foreach, VARIABLE_NAME:t_hir_VARIABLE_NAME, KEY:maybe[t_hir_Variable], IS_REF:bool, VAL:t_hir_Variable, STATEMENTS:list[t_hir_Statement]).
predicate hir_Break (ID:t_hir_Break, EXPR:maybe[t_hir_Expr]).
predicate hir_Continue (ID:t_hir_Continue, EXPR:maybe[t_hir_Expr]).
predicate hir_Return (ID:t_hir_Return, EXPR:maybe[t_hir_Expr]).
predicate hir_Static_declaration (ID:t_hir_Static_declaration, VAR:t_hir_Name_with_default).
predicate hir_Global (ID:t_hir_Global, VARIABLE_NAME:t_hir_Variable_name).
predicate hir_Try (ID:t_hir_Try, STATEMENTS:list[t_hir_Statement], CATCHES:list[t_hir_Catch]).
predicate hir_Catch (ID:t_hir_Catch, CLASS_NAME:t_hir_CLASS_NAME, VARIABLE_NAME:t_hir_VARIABLE_NAME, STATEMENTS:list[t_hir_Statement]).
predicate hir_Throw (ID:t_hir_Throw, EXPR:t_hir_Expr).
predicate hir_Eval_expr (ID:t_hir_Eval_expr, EXPR:t_hir_Expr).
predicate hir_Branch (ID:t_hir_Branch, VARIABLE_NAME:t_hir_VARIABLE_NAME, IFTRUE:t_hir_LABEL_NAME, IFFALSE:t_hir_LABEL_NAME).
predicate hir_Goto (ID:t_hir_Goto, LABEL_NAME:t_hir_LABEL_NAME).
predicate hir_Label (ID:t_hir_Label, LABEL_NAME:t_hir_LABEL_NAME).
predicate hir_Foreach_reset (ID:t_hir_Foreach_reset, ARRAY:t_hir_VARIABLE_NAME, ITER:t_hir_HT_ITERATOR).
predicate hir_Foreach_next (ID:t_hir_Foreach_next, ARRAY:t_hir_VARIABLE_NAME, ITER:t_hir_HT_ITERATOR).
predicate hir_Foreach_end (ID:t_hir_Foreach_end, ARRAY:t_hir_VARIABLE_NAME, ITER:t_hir_HT_ITERATOR).
predicate hir_Foreach_has_key (ID:t_hir_Foreach_has_key, ARRAY:t_hir_VARIABLE_NAME, ITER:t_hir_HT_ITERATOR).
predicate hir_Foreach_get_key (ID:t_hir_Foreach_get_key, ARRAY:t_hir_VARIABLE_NAME, ITER:t_hir_HT_ITERATOR).
predicate hir_Foreach_get_val (ID:t_hir_Foreach_get_val, ARRAY:t_hir_VARIABLE_NAME, KEY:t_hir_VARIABLE_NAME, ITER:t_hir_HT_ITERATOR).
predicate hir_Assignment (ID:t_hir_Assignment, VARIABLE:t_hir_Variable, IS_REF:bool, EXPR:t_hir_Expr).
predicate hir_Op_assignment (ID:t_hir_Op_assignment, VARIABLE:t_hir_Variable, OP:t_hir_OP, EXPR:t_hir_Expr).
predicate hir_Cast (ID:t_hir_Cast, CAST:t_hir_CAST, VARIABLE_NAME:t_hir_VARIABLE_NAME).
predicate hir_Unary_op (ID:t_hir_Unary_op, OP:t_hir_OP, VARIABLE_NAME:t_hir_VARIABLE_NAME).
predicate hir_Bin_op (ID:t_hir_Bin_op, LEFT:t_hir_VARIABLE_NAME, OP:t_hir_OP, RIGHT:t_hir_VARIABLE_NAME).
predicate hir_Constant (ID:t_hir_Constant, CLASS_NAME:maybe[t_hir_CLASS_NAME], CONSTANT_NAME:t_hir_CONSTANT_NAME).
predicate hir_Instanceof (ID:t_hir_Instanceof, VARIABLE_NAME:t_hir_VARIABLE_NAME, CLASS_NAME:t_hir_Class_name).
predicate hir_Variable (ID:t_hir_Variable, TARGET:maybe[t_hir_Target], VARIABLE_NAME:t_hir_Variable_name, ARRAY_INDICES:list[maybe[t_hir_VARIABLE_NAME]]).
predicate hir_Reflection (ID:t_hir_Reflection, VARIABLE_NAME:t_hir_VARIABLE_NAME).
predicate hir_Pre_op (ID:t_hir_Pre_op, OP:t_hir_OP, VARIABLE:t_hir_Variable).
predicate hir_Array (ID:t_hir_Array, ARRAY_ELEMS:list[t_hir_Array_elem]).
predicate hir_Array_elem (ID:t_hir_Array_elem, KEY:maybe[t_hir_Expr], IS_REF:bool, VAL:t_hir_Expr).
predicate hir_Method_invocation (ID:t_hir_Method_invocation, TARGET:maybe[t_hir_Target], METHOD_NAME:t_hir_Method_name, ACTUAL_PARAMETERS:list[t_hir_Actual_parameter]).
predicate hir_Actual_parameter (ID:t_hir_Actual_parameter, IS_REF:bool, EXPR:t_hir_Expr).
predicate hir_New (ID:t_hir_New, CLASS_NAME:t_hir_Class_name, ACTUAL_PARAMETERS:list[t_hir_Actual_parameter]).

predicate hir_HT_ITERATOR (ID:t_hir_HT_ITERATOR, VALUE:int).
predicate hir_CLASS_NAME (ID:t_hir_CLASS_NAME, VALUE:string).
predicate hir_INTERFACE_NAME (ID:t_hir_INTERFACE_NAME, VALUE:string).
predicate hir_METHOD_NAME (ID:t_hir_METHOD_NAME, VALUE:string).
predicate hir_VARIABLE_NAME (ID:t_hir_VARIABLE_NAME, VALUE:string).
predicate hir_LABEL_NAME (ID:t_hir_LABEL_NAME, VALUE:string).
predicate hir_INT (ID:t_hir_INT, VALUE:int).
predicate hir_REAL (ID:t_hir_REAL, VALUE:float).
predicate hir_STRING (ID:t_hir_STRING, VALUE:string).
predicate hir_BOOL (ID:t_hir_BOOL, VALUE:bool).
predicate hir_NIL (ID:t_hir_NIL, VALUE:null).
predicate hir_OP (ID:t_hir_OP, VALUE:string).
predicate hir_CAST (ID:t_hir_CAST, VALUE:string).
predicate hir_CONSTANT_NAME (ID:t_hir_CONSTANT_NAME, VALUE:string).

