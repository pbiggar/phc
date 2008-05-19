session ast (PROG:string).

% Type not supplied by Saturn
type null.
type id = int.

% Forward declarations for conjunctive types
type t_ast_PHP_script.
type t_ast_Class_def.
type t_ast_Class_mod.
type t_ast_Interface_def.
type t_ast_Method.
type t_ast_Signature.
type t_ast_Method_mod.
type t_ast_Formal_parameter.
type t_ast_Type.
type t_ast_Attribute.
type t_ast_Attr_mod.
type t_ast_Name_with_default.
type t_ast_If.
type t_ast_Loop.
type t_ast_Foreach.
type t_ast_Break.
type t_ast_Continue.
type t_ast_Return.
type t_ast_Static_declaration.
type t_ast_Global.
type t_ast_Try.
type t_ast_Catch.
type t_ast_Throw.
type t_ast_Eval_expr.
type t_ast_Branch.
type t_ast_Goto.
type t_ast_Label.
type t_ast_Foreach_reset.
type t_ast_Foreach_next.
type t_ast_Foreach_end.
type t_ast_Foreach_has_key.
type t_ast_Foreach_get_key.
type t_ast_Foreach_get_val.
type t_ast_Assignment.
type t_ast_Op_assignment.
type t_ast_Cast.
type t_ast_Unary_op.
type t_ast_Bin_op.
type t_ast_Constant.
type t_ast_Instanceof.
type t_ast_Variable.
type t_ast_Reflection.
type t_ast_Pre_op.
type t_ast_Array.
type t_ast_Array_elem.
type t_ast_Method_invocation.
type t_ast_Actual_parameter.
type t_ast_New.


% Forward declarations for disjunctive types
type t_ast_Node.
type t_ast_Statement.
type t_ast_Member.
type t_ast_Expr.
type t_ast_Literal.
type t_ast_Variable_name.
type t_ast_Target.
type t_ast_Method_name.
type t_ast_Class_name.
type t_ast_Identifier.


% Token declarations
type t_ast_HT_ITERATOR ::= t_ast_HT_ITERATOR_id {id}.
type t_ast_CLASS_NAME ::= t_ast_CLASS_NAME_id {id}.
type t_ast_INTERFACE_NAME ::= t_ast_INTERFACE_NAME_id {id}.
type t_ast_METHOD_NAME ::= t_ast_METHOD_NAME_id {id}.
type t_ast_VARIABLE_NAME ::= t_ast_VARIABLE_NAME_id {id}.
type t_ast_LABEL_NAME ::= t_ast_LABEL_NAME_id {id}.
type t_ast_INT ::= t_ast_INT_id {id}.
type t_ast_REAL ::= t_ast_REAL_id {id}.
type t_ast_STRING ::= t_ast_STRING_id {id}.
type t_ast_BOOL ::= t_ast_BOOL_id {id}.
type t_ast_NIL ::= t_ast_NIL_id {id}.
type t_ast_OP ::= t_ast_OP_id {id}.
type t_ast_CAST ::= t_ast_CAST_id {id}.
type t_ast_CONSTANT_NAME ::= t_ast_CONSTANT_NAME_id {id}.


% Conjunctive types
type t_ast_PHP_script ::= t_ast_PHP_script_id {id}.
type t_ast_Class_def ::= t_ast_Class_def_id {id}.
type t_ast_Class_mod ::= t_ast_Class_mod_id {id}.
type t_ast_Interface_def ::= t_ast_Interface_def_id {id}.
type t_ast_Method ::= t_ast_Method_id {id}.
type t_ast_Signature ::= t_ast_Signature_id {id}.
type t_ast_Method_mod ::= t_ast_Method_mod_id {id}.
type t_ast_Formal_parameter ::= t_ast_Formal_parameter_id {id}.
type t_ast_Type ::= t_ast_Type_id {id}.
type t_ast_Attribute ::= t_ast_Attribute_id {id}.
type t_ast_Attr_mod ::= t_ast_Attr_mod_id {id}.
type t_ast_Name_with_default ::= t_ast_Name_with_default_id {id}.
type t_ast_If ::= t_ast_If_id {id}.
type t_ast_Loop ::= t_ast_Loop_id {id}.
type t_ast_Foreach ::= t_ast_Foreach_id {id}.
type t_ast_Break ::= t_ast_Break_id {id}.
type t_ast_Continue ::= t_ast_Continue_id {id}.
type t_ast_Return ::= t_ast_Return_id {id}.
type t_ast_Static_declaration ::= t_ast_Static_declaration_id {id}.
type t_ast_Global ::= t_ast_Global_id {id}.
type t_ast_Try ::= t_ast_Try_id {id}.
type t_ast_Catch ::= t_ast_Catch_id {id}.
type t_ast_Throw ::= t_ast_Throw_id {id}.
type t_ast_Eval_expr ::= t_ast_Eval_expr_id {id}.
type t_ast_Branch ::= t_ast_Branch_id {id}.
type t_ast_Goto ::= t_ast_Goto_id {id}.
type t_ast_Label ::= t_ast_Label_id {id}.
type t_ast_Foreach_reset ::= t_ast_Foreach_reset_id {id}.
type t_ast_Foreach_next ::= t_ast_Foreach_next_id {id}.
type t_ast_Foreach_end ::= t_ast_Foreach_end_id {id}.
type t_ast_Foreach_has_key ::= t_ast_Foreach_has_key_id {id}.
type t_ast_Foreach_get_key ::= t_ast_Foreach_get_key_id {id}.
type t_ast_Foreach_get_val ::= t_ast_Foreach_get_val_id {id}.
type t_ast_Assignment ::= t_ast_Assignment_id {id}.
type t_ast_Op_assignment ::= t_ast_Op_assignment_id {id}.
type t_ast_Cast ::= t_ast_Cast_id {id}.
type t_ast_Unary_op ::= t_ast_Unary_op_id {id}.
type t_ast_Bin_op ::= t_ast_Bin_op_id {id}.
type t_ast_Constant ::= t_ast_Constant_id {id}.
type t_ast_Instanceof ::= t_ast_Instanceof_id {id}.
type t_ast_Variable ::= t_ast_Variable_id {id}.
type t_ast_Reflection ::= t_ast_Reflection_id {id}.
type t_ast_Pre_op ::= t_ast_Pre_op_id {id}.
type t_ast_Array ::= t_ast_Array_id {id}.
type t_ast_Array_elem ::= t_ast_Array_elem_id {id}.
type t_ast_Method_invocation ::= t_ast_Method_invocation_id {id}.
type t_ast_Actual_parameter ::= t_ast_Actual_parameter_id {id}.
type t_ast_New ::= t_ast_New_id {id}.


% Disjunctive types
type t_ast_Identifier ::= 
		  t_ast_Identifier_t_ast_INTERFACE_NAME_id { t_ast_INTERFACE_NAME } 
		| t_ast_Identifier_t_ast_CLASS_NAME_id { t_ast_CLASS_NAME } 
		| t_ast_Identifier_t_ast_METHOD_NAME_id { t_ast_METHOD_NAME } 
		| t_ast_Identifier_t_ast_VARIABLE_NAME_id { t_ast_VARIABLE_NAME } 
		| t_ast_Identifier_t_ast_CAST_id { t_ast_CAST } 
		| t_ast_Identifier_t_ast_OP_id { t_ast_OP } 
		| t_ast_Identifier_t_ast_CONSTANT_NAME_id { t_ast_CONSTANT_NAME } 
		| t_ast_Identifier_t_ast_LABEL_NAME_id { t_ast_LABEL_NAME } 
		.
type t_ast_Class_name ::= 
		  t_ast_Class_name_t_ast_CLASS_NAME_id { t_ast_CLASS_NAME } 
		| t_ast_Class_name_t_ast_Reflection_id { t_ast_Reflection } 
		.
type t_ast_Method_name ::= 
		  t_ast_Method_name_t_ast_METHOD_NAME_id { t_ast_METHOD_NAME } 
		| t_ast_Method_name_t_ast_Reflection_id { t_ast_Reflection } 
		.
type t_ast_Target ::= 
		  t_ast_Target_t_ast_Assignment_id { t_ast_Assignment } 
		| t_ast_Target_t_ast_Cast_id { t_ast_Cast } 
		| t_ast_Target_t_ast_Unary_op_id { t_ast_Unary_op } 
		| t_ast_Target_t_ast_Bin_op_id { t_ast_Bin_op } 
		| t_ast_Target_t_ast_Constant_id { t_ast_Constant } 
		| t_ast_Target_t_ast_Instanceof_id { t_ast_Instanceof } 
		| t_ast_Target_t_ast_Variable_id { t_ast_Variable } 
		| t_ast_Target_t_ast_Pre_op_id { t_ast_Pre_op } 
		| t_ast_Target_t_ast_Method_invocation_id { t_ast_Method_invocation } 
		| t_ast_Target_t_ast_New_id { t_ast_New } 
		| t_ast_Target_t_ast_INT_id { t_ast_INT } 
		| t_ast_Target_t_ast_REAL_id { t_ast_REAL } 
		| t_ast_Target_t_ast_STRING_id { t_ast_STRING } 
		| t_ast_Target_t_ast_BOOL_id { t_ast_BOOL } 
		| t_ast_Target_t_ast_NIL_id { t_ast_NIL } 
		| t_ast_Target_t_ast_Op_assignment_id { t_ast_Op_assignment } 
		| t_ast_Target_t_ast_Array_id { t_ast_Array } 
		| t_ast_Target_t_ast_Foreach_has_key_id { t_ast_Foreach_has_key } 
		| t_ast_Target_t_ast_Foreach_get_key_id { t_ast_Foreach_get_key } 
		| t_ast_Target_t_ast_Foreach_get_val_id { t_ast_Foreach_get_val } 
		| t_ast_Target_t_ast_CLASS_NAME_id { t_ast_CLASS_NAME } 
		.
type t_ast_Variable_name ::= 
		  t_ast_Variable_name_t_ast_VARIABLE_NAME_id { t_ast_VARIABLE_NAME } 
		| t_ast_Variable_name_t_ast_Reflection_id { t_ast_Reflection } 
		.
type t_ast_Literal ::= 
		  t_ast_Literal_t_ast_INT_id { t_ast_INT } 
		| t_ast_Literal_t_ast_REAL_id { t_ast_REAL } 
		| t_ast_Literal_t_ast_STRING_id { t_ast_STRING } 
		| t_ast_Literal_t_ast_BOOL_id { t_ast_BOOL } 
		| t_ast_Literal_t_ast_NIL_id { t_ast_NIL } 
		.
type t_ast_Expr ::= 
		  t_ast_Expr_t_ast_Assignment_id { t_ast_Assignment } 
		| t_ast_Expr_t_ast_Cast_id { t_ast_Cast } 
		| t_ast_Expr_t_ast_Unary_op_id { t_ast_Unary_op } 
		| t_ast_Expr_t_ast_Bin_op_id { t_ast_Bin_op } 
		| t_ast_Expr_t_ast_Constant_id { t_ast_Constant } 
		| t_ast_Expr_t_ast_Instanceof_id { t_ast_Instanceof } 
		| t_ast_Expr_t_ast_Variable_id { t_ast_Variable } 
		| t_ast_Expr_t_ast_Pre_op_id { t_ast_Pre_op } 
		| t_ast_Expr_t_ast_Method_invocation_id { t_ast_Method_invocation } 
		| t_ast_Expr_t_ast_New_id { t_ast_New } 
		| t_ast_Expr_t_ast_INT_id { t_ast_INT } 
		| t_ast_Expr_t_ast_REAL_id { t_ast_REAL } 
		| t_ast_Expr_t_ast_STRING_id { t_ast_STRING } 
		| t_ast_Expr_t_ast_BOOL_id { t_ast_BOOL } 
		| t_ast_Expr_t_ast_NIL_id { t_ast_NIL } 
		| t_ast_Expr_t_ast_Op_assignment_id { t_ast_Op_assignment } 
		| t_ast_Expr_t_ast_Array_id { t_ast_Array } 
		| t_ast_Expr_t_ast_Foreach_has_key_id { t_ast_Foreach_has_key } 
		| t_ast_Expr_t_ast_Foreach_get_key_id { t_ast_Foreach_get_key } 
		| t_ast_Expr_t_ast_Foreach_get_val_id { t_ast_Foreach_get_val } 
		.
type t_ast_Member ::= 
		  t_ast_Member_t_ast_Method_id { t_ast_Method } 
		| t_ast_Member_t_ast_Attribute_id { t_ast_Attribute } 
		.
type t_ast_Statement ::= 
		  t_ast_Statement_t_ast_Class_def_id { t_ast_Class_def } 
		| t_ast_Statement_t_ast_Interface_def_id { t_ast_Interface_def } 
		| t_ast_Statement_t_ast_Method_id { t_ast_Method } 
		| t_ast_Statement_t_ast_Return_id { t_ast_Return } 
		| t_ast_Statement_t_ast_Static_declaration_id { t_ast_Static_declaration } 
		| t_ast_Statement_t_ast_Global_id { t_ast_Global } 
		| t_ast_Statement_t_ast_Try_id { t_ast_Try } 
		| t_ast_Statement_t_ast_Throw_id { t_ast_Throw } 
		| t_ast_Statement_t_ast_Eval_expr_id { t_ast_Eval_expr } 
		| t_ast_Statement_t_ast_If_id { t_ast_If } 
		| t_ast_Statement_t_ast_Loop_id { t_ast_Loop } 
		| t_ast_Statement_t_ast_Foreach_id { t_ast_Foreach } 
		| t_ast_Statement_t_ast_Break_id { t_ast_Break } 
		| t_ast_Statement_t_ast_Continue_id { t_ast_Continue } 
		| t_ast_Statement_t_ast_Label_id { t_ast_Label } 
		| t_ast_Statement_t_ast_Goto_id { t_ast_Goto } 
		| t_ast_Statement_t_ast_Branch_id { t_ast_Branch } 
		| t_ast_Statement_t_ast_Foreach_next_id { t_ast_Foreach_next } 
		| t_ast_Statement_t_ast_Foreach_reset_id { t_ast_Foreach_reset } 
		| t_ast_Statement_t_ast_Foreach_end_id { t_ast_Foreach_end } 
		.
type t_ast_Node ::= 
		  t_ast_Node_t_ast_PHP_script_id { t_ast_PHP_script } 
		| t_ast_Node_t_ast_Class_def_id { t_ast_Class_def } 
		| t_ast_Node_t_ast_Interface_def_id { t_ast_Interface_def } 
		| t_ast_Node_t_ast_Method_id { t_ast_Method } 
		| t_ast_Node_t_ast_Return_id { t_ast_Return } 
		| t_ast_Node_t_ast_Static_declaration_id { t_ast_Static_declaration } 
		| t_ast_Node_t_ast_Global_id { t_ast_Global } 
		| t_ast_Node_t_ast_Try_id { t_ast_Try } 
		| t_ast_Node_t_ast_Throw_id { t_ast_Throw } 
		| t_ast_Node_t_ast_Eval_expr_id { t_ast_Eval_expr } 
		| t_ast_Node_t_ast_If_id { t_ast_If } 
		| t_ast_Node_t_ast_Loop_id { t_ast_Loop } 
		| t_ast_Node_t_ast_Foreach_id { t_ast_Foreach } 
		| t_ast_Node_t_ast_Break_id { t_ast_Break } 
		| t_ast_Node_t_ast_Continue_id { t_ast_Continue } 
		| t_ast_Node_t_ast_Label_id { t_ast_Label } 
		| t_ast_Node_t_ast_Goto_id { t_ast_Goto } 
		| t_ast_Node_t_ast_Branch_id { t_ast_Branch } 
		| t_ast_Node_t_ast_Foreach_next_id { t_ast_Foreach_next } 
		| t_ast_Node_t_ast_Foreach_reset_id { t_ast_Foreach_reset } 
		| t_ast_Node_t_ast_Foreach_end_id { t_ast_Foreach_end } 
		| t_ast_Node_t_ast_Class_mod_id { t_ast_Class_mod } 
		| t_ast_Node_t_ast_Attribute_id { t_ast_Attribute } 
		| t_ast_Node_t_ast_Signature_id { t_ast_Signature } 
		| t_ast_Node_t_ast_Method_mod_id { t_ast_Method_mod } 
		| t_ast_Node_t_ast_Formal_parameter_id { t_ast_Formal_parameter } 
		| t_ast_Node_t_ast_Type_id { t_ast_Type } 
		| t_ast_Node_t_ast_Attr_mod_id { t_ast_Attr_mod } 
		| t_ast_Node_t_ast_Name_with_default_id { t_ast_Name_with_default } 
		| t_ast_Node_t_ast_Catch_id { t_ast_Catch } 
		| t_ast_Node_t_ast_VARIABLE_NAME_id { t_ast_VARIABLE_NAME } 
		| t_ast_Node_t_ast_Reflection_id { t_ast_Reflection } 
		| t_ast_Node_t_ast_Assignment_id { t_ast_Assignment } 
		| t_ast_Node_t_ast_Cast_id { t_ast_Cast } 
		| t_ast_Node_t_ast_Unary_op_id { t_ast_Unary_op } 
		| t_ast_Node_t_ast_Bin_op_id { t_ast_Bin_op } 
		| t_ast_Node_t_ast_Constant_id { t_ast_Constant } 
		| t_ast_Node_t_ast_Instanceof_id { t_ast_Instanceof } 
		| t_ast_Node_t_ast_Variable_id { t_ast_Variable } 
		| t_ast_Node_t_ast_Pre_op_id { t_ast_Pre_op } 
		| t_ast_Node_t_ast_Method_invocation_id { t_ast_Method_invocation } 
		| t_ast_Node_t_ast_New_id { t_ast_New } 
		| t_ast_Node_t_ast_INT_id { t_ast_INT } 
		| t_ast_Node_t_ast_REAL_id { t_ast_REAL } 
		| t_ast_Node_t_ast_STRING_id { t_ast_STRING } 
		| t_ast_Node_t_ast_BOOL_id { t_ast_BOOL } 
		| t_ast_Node_t_ast_NIL_id { t_ast_NIL } 
		| t_ast_Node_t_ast_Op_assignment_id { t_ast_Op_assignment } 
		| t_ast_Node_t_ast_Array_id { t_ast_Array } 
		| t_ast_Node_t_ast_Foreach_has_key_id { t_ast_Foreach_has_key } 
		| t_ast_Node_t_ast_Foreach_get_key_id { t_ast_Foreach_get_key } 
		| t_ast_Node_t_ast_Foreach_get_val_id { t_ast_Foreach_get_val } 
		| t_ast_Node_t_ast_CLASS_NAME_id { t_ast_CLASS_NAME } 
		| t_ast_Node_t_ast_Array_elem_id { t_ast_Array_elem } 
		| t_ast_Node_t_ast_METHOD_NAME_id { t_ast_METHOD_NAME } 
		| t_ast_Node_t_ast_Actual_parameter_id { t_ast_Actual_parameter } 
		| t_ast_Node_t_ast_INTERFACE_NAME_id { t_ast_INTERFACE_NAME } 
		| t_ast_Node_t_ast_CAST_id { t_ast_CAST } 
		| t_ast_Node_t_ast_OP_id { t_ast_OP } 
		| t_ast_Node_t_ast_CONSTANT_NAME_id { t_ast_CONSTANT_NAME } 
		| t_ast_Node_t_ast_LABEL_NAME_id { t_ast_LABEL_NAME } 
		| t_ast_Node_t_ast_HT_ITERATOR_id { t_ast_HT_ITERATOR } 
		.


% Predicates
predicate ast_PHP_script (ID:t_ast_PHP_script, STATEMENTS:list[t_ast_Statement]).
predicate ast_Class_def (ID:t_ast_Class_def, CLASS_MOD:t_ast_Class_mod, CLASS_NAME:t_ast_CLASS_NAME, EXTENDS:maybe[t_ast_CLASS_NAME], IMPLEMENTS:list[t_ast_INTERFACE_NAME], MEMBERS:list[t_ast_Member]).
predicate ast_Class_mod (ID:t_ast_Class_mod, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate ast_Interface_def (ID:t_ast_Interface_def, INTERFACE_NAME:t_ast_INTERFACE_NAME, EXTENDS:list[t_ast_INTERFACE_NAME], MEMBERS:list[t_ast_Member]).
predicate ast_Method (ID:t_ast_Method, SIGNATURE:t_ast_Signature, STATEMENTS:maybe[list[t_ast_Statement]]).
predicate ast_Signature (ID:t_ast_Signature, METHOD_MOD:t_ast_Method_mod, IS_REF:bool, METHOD_NAME:t_ast_METHOD_NAME, FORMAL_PARAMETERS:list[t_ast_Formal_parameter]).
predicate ast_Method_mod (ID:t_ast_Method_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate ast_Formal_parameter (ID:t_ast_Formal_parameter, TYPE:t_ast_Type, IS_REF:bool, VAR:t_ast_Name_with_default).
predicate ast_Type (ID:t_ast_Type, CLASS_NAME:maybe[t_ast_CLASS_NAME]).
predicate ast_Attribute (ID:t_ast_Attribute, ATTR_MOD:t_ast_Attr_mod, VAR:t_ast_Name_with_default).
predicate ast_Attr_mod (ID:t_ast_Attr_mod, IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_CONST:bool).
predicate ast_Name_with_default (ID:t_ast_Name_with_default, VARIABLE_NAME:t_ast_VARIABLE_NAME, EXPR:maybe[t_ast_Expr]).
predicate ast_If (ID:t_ast_If, VARIABLE_NAME:t_ast_VARIABLE_NAME, IFTRUE:list[t_ast_Statement], IFFALSE:list[t_ast_Statement]).
predicate ast_Loop (ID:t_ast_Loop, STATEMENTS:list[t_ast_Statement]).
predicate ast_Foreach (ID:t_ast_Foreach, VARIABLE_NAME:t_ast_VARIABLE_NAME, KEY:maybe[t_ast_Variable], IS_REF:bool, VAL:t_ast_Variable, STATEMENTS:list[t_ast_Statement]).
predicate ast_Break (ID:t_ast_Break, EXPR:maybe[t_ast_Expr]).
predicate ast_Continue (ID:t_ast_Continue, EXPR:maybe[t_ast_Expr]).
predicate ast_Return (ID:t_ast_Return, EXPR:maybe[t_ast_Expr]).
predicate ast_Static_declaration (ID:t_ast_Static_declaration, VAR:t_ast_Name_with_default).
predicate ast_Global (ID:t_ast_Global, VARIABLE_NAME:t_ast_Variable_name).
predicate ast_Try (ID:t_ast_Try, STATEMENTS:list[t_ast_Statement], CATCHES:list[t_ast_Catch]).
predicate ast_Catch (ID:t_ast_Catch, CLASS_NAME:t_ast_CLASS_NAME, VARIABLE_NAME:t_ast_VARIABLE_NAME, STATEMENTS:list[t_ast_Statement]).
predicate ast_Throw (ID:t_ast_Throw, EXPR:t_ast_Expr).
predicate ast_Eval_expr (ID:t_ast_Eval_expr, EXPR:t_ast_Expr).
predicate ast_Branch (ID:t_ast_Branch, VARIABLE_NAME:t_ast_VARIABLE_NAME, IFTRUE:t_ast_LABEL_NAME, IFFALSE:t_ast_LABEL_NAME).
predicate ast_Goto (ID:t_ast_Goto, LABEL_NAME:t_ast_LABEL_NAME).
predicate ast_Label (ID:t_ast_Label, LABEL_NAME:t_ast_LABEL_NAME).
predicate ast_Foreach_reset (ID:t_ast_Foreach_reset, ARRAY:t_ast_VARIABLE_NAME, ITER:t_ast_HT_ITERATOR).
predicate ast_Foreach_next (ID:t_ast_Foreach_next, ARRAY:t_ast_VARIABLE_NAME, ITER:t_ast_HT_ITERATOR).
predicate ast_Foreach_end (ID:t_ast_Foreach_end, ARRAY:t_ast_VARIABLE_NAME, ITER:t_ast_HT_ITERATOR).
predicate ast_Foreach_has_key (ID:t_ast_Foreach_has_key, ARRAY:t_ast_VARIABLE_NAME, ITER:t_ast_HT_ITERATOR).
predicate ast_Foreach_get_key (ID:t_ast_Foreach_get_key, ARRAY:t_ast_VARIABLE_NAME, ITER:t_ast_HT_ITERATOR).
predicate ast_Foreach_get_val (ID:t_ast_Foreach_get_val, ARRAY:t_ast_VARIABLE_NAME, KEY:t_ast_VARIABLE_NAME, ITER:t_ast_HT_ITERATOR).
predicate ast_Assignment (ID:t_ast_Assignment, VARIABLE:t_ast_Variable, IS_REF:bool, EXPR:t_ast_Expr).
predicate ast_Op_assignment (ID:t_ast_Op_assignment, VARIABLE:t_ast_Variable, OP:t_ast_OP, EXPR:t_ast_Expr).
predicate ast_Cast (ID:t_ast_Cast, CAST:t_ast_CAST, VARIABLE_NAME:t_ast_VARIABLE_NAME).
predicate ast_Unary_op (ID:t_ast_Unary_op, OP:t_ast_OP, VARIABLE_NAME:t_ast_VARIABLE_NAME).
predicate ast_Bin_op (ID:t_ast_Bin_op, LEFT:t_ast_VARIABLE_NAME, OP:t_ast_OP, RIGHT:t_ast_VARIABLE_NAME).
predicate ast_Constant (ID:t_ast_Constant, CLASS_NAME:maybe[t_ast_CLASS_NAME], CONSTANT_NAME:t_ast_CONSTANT_NAME).
predicate ast_Instanceof (ID:t_ast_Instanceof, VARIABLE_NAME:t_ast_VARIABLE_NAME, CLASS_NAME:t_ast_Class_name).
predicate ast_Variable (ID:t_ast_Variable, TARGET:maybe[t_ast_Target], VARIABLE_NAME:t_ast_Variable_name, ARRAY_INDICES:list[maybe[t_ast_VARIABLE_NAME]]).
predicate ast_Reflection (ID:t_ast_Reflection, VARIABLE_NAME:t_ast_VARIABLE_NAME).
predicate ast_Pre_op (ID:t_ast_Pre_op, OP:t_ast_OP, VARIABLE:t_ast_Variable).
predicate ast_Array (ID:t_ast_Array, ARRAY_ELEMS:list[t_ast_Array_elem]).
predicate ast_Array_elem (ID:t_ast_Array_elem, KEY:maybe[t_ast_Expr], IS_REF:bool, VAL:t_ast_Expr).
predicate ast_Method_invocation (ID:t_ast_Method_invocation, TARGET:maybe[t_ast_Target], METHOD_NAME:t_ast_Method_name, ACTUAL_PARAMETERS:list[t_ast_Actual_parameter]).
predicate ast_Actual_parameter (ID:t_ast_Actual_parameter, IS_REF:bool, EXPR:t_ast_Expr).
predicate ast_New (ID:t_ast_New, CLASS_NAME:t_ast_Class_name, ACTUAL_PARAMETERS:list[t_ast_Actual_parameter]).

predicate ast_HT_ITERATOR (ID:t_ast_HT_ITERATOR, VALUE:int).
predicate ast_CLASS_NAME (ID:t_ast_CLASS_NAME, VALUE:string).
predicate ast_INTERFACE_NAME (ID:t_ast_INTERFACE_NAME, VALUE:string).
predicate ast_METHOD_NAME (ID:t_ast_METHOD_NAME, VALUE:string).
predicate ast_VARIABLE_NAME (ID:t_ast_VARIABLE_NAME, VALUE:string).
predicate ast_LABEL_NAME (ID:t_ast_LABEL_NAME, VALUE:string).
predicate ast_INT (ID:t_ast_INT, VALUE:int).
predicate ast_REAL (ID:t_ast_REAL, VALUE:float).
predicate ast_STRING (ID:t_ast_STRING, VALUE:string).
predicate ast_BOOL (ID:t_ast_BOOL, VALUE:bool).
predicate ast_NIL (ID:t_ast_NIL, VALUE:null).
predicate ast_OP (ID:t_ast_OP, VALUE:string).
predicate ast_CAST (ID:t_ast_CAST, VALUE:string).
predicate ast_CONSTANT_NAME (ID:t_ast_CONSTANT_NAME, VALUE:string).

