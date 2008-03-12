
% Type not supplied by Saturn
type null.

% Forward declarations for conjunctive types
type php_php_script.
type php_class_def.
type php_class_mod.
type php_interface_def.
type php_method.
type php_signature.
type php_method_mod.
type php_formal_parameter.
type php_type.
type php_attribute.
type php_attr_mod.
type php_name_with_default.
type php_if.
type php_loop.
type php_foreach.
type php_switch.
type php_switch_case.
type php_break.
type php_continue.
type php_return.
type php_static_declaration.
type php_global.
type php_try.
type php_catch.
type php_throw.
type php_eval_expr.
type php_branch.
type php_goto.
type php_label.
type php_foreach_reset.
type php_foreach_next.
type php_foreach_end.
type php_foreach_has_key.
type php_foreach_get_key.
type php_foreach_get_val.
type php_assignment.
type php_op_assignment.
type php_list_assignment.
type php_nested_list_elements.
type php_cast.
type php_unary_op.
type php_bin_op.
type php_conditional_expr.
type php_ignore_errors.
type php_constant.
type php_instanceof.
type php_variable.
type php_reflection.
type php_pre_op.
type php_array.
type php_array_elem.
type php_method_invocation.
type php_actual_parameter.
type php_new.


% Forward declarations for disjunctive types
type php_node.
type php_statement.
type php_member.
type php_expr.
type php_literal.
type php_list_element.
type php_variable_name.
type php_target.
type php_method_name.
type php_class_name.
type php_commented_node.
type php_identifier.


% Token declarations
type php_t_ht_iterator ::= c_php_t_ht_iterator { int } .
type php_t_class_name ::= c_php_t_class_name { null } .
type php_t_interface_name ::= c_php_t_interface_name { null } .
type php_t_method_name ::= c_php_t_method_name { null } .
type php_t_variable_name ::= c_php_t_variable_name { null } .
type php_t_label_name ::= c_php_t_label_name { null } .
type php_t_int ::= c_php_t_int { int } .
type php_t_real ::= c_php_t_real { float } .
type php_t_string ::= c_php_t_string { string } .
type php_t_bool ::= c_php_t_bool { bool } .
type php_t_nil ::= c_php_t_nil { null } .
type php_t_op ::= c_php_t_op { null } .
type php_t_cast ::= c_php_t_cast { null } .
type php_t_constant_name ::= c_php_t_constant_name { null } .


% Conjunctive types
type php_php_script ::= c_php_php_script {list[php_statement]}.
type php_class_def ::= c_php_class_def {php_class_mod, php_t_class_name, php_t_class_name, list[php_t_interface_name], list[php_member]}.
type php_class_mod ::= c_php_class_mod {bool, bool}.
type php_interface_def ::= c_php_interface_def {php_t_interface_name, list[php_t_interface_name], list[php_member]}.
type php_method ::= c_php_method {php_signature, list[php_statement]}.
type php_signature ::= c_php_signature {php_method_mod, bool, php_t_method_name, list[php_formal_parameter]}.
type php_method_mod ::= c_php_method_mod {bool, bool, bool, bool, bool, bool}.
type php_formal_parameter ::= c_php_formal_parameter {php_type, bool, php_name_with_default}.
type php_type ::= c_php_type {php_t_class_name}.
type php_attribute ::= c_php_attribute {php_attr_mod, list[php_name_with_default]}.
type php_attr_mod ::= c_php_attr_mod {bool, bool, bool, bool, bool}.
type php_name_with_default ::= c_php_name_with_default {php_t_variable_name, php_expr}.
type php_if ::= c_php_if {php_expr, list[php_statement], list[php_statement]}.
type php_loop ::= c_php_loop {list[php_statement]}.
type php_foreach ::= c_php_foreach {php_expr, php_variable, bool, php_variable, list[php_statement]}.
type php_switch ::= c_php_switch {php_expr, list[php_switch_case]}.
type php_switch_case ::= c_php_switch_case {php_expr, list[php_statement]}.
type php_break ::= c_php_break {php_expr}.
type php_continue ::= c_php_continue {php_expr}.
type php_return ::= c_php_return {php_expr}.
type php_static_declaration ::= c_php_static_declaration {list[php_name_with_default]}.
type php_global ::= c_php_global {list[php_variable_name]}.
type php_try ::= c_php_try {list[php_statement], list[php_catch]}.
type php_catch ::= c_php_catch {php_t_class_name, php_t_variable_name, list[php_statement]}.
type php_throw ::= c_php_throw {php_expr}.
type php_eval_expr ::= c_php_eval_expr {php_expr}.
type php_branch ::= c_php_branch {php_expr, php_t_label_name, php_t_label_name}.
type php_goto ::= c_php_goto {php_t_label_name}.
type php_label ::= c_php_label {php_t_label_name}.
type php_foreach_reset ::= c_php_foreach_reset {php_variable, php_t_ht_iterator}.
type php_foreach_next ::= c_php_foreach_next {php_variable, php_t_ht_iterator}.
type php_foreach_end ::= c_php_foreach_end {php_variable, php_t_ht_iterator}.
type php_foreach_has_key ::= c_php_foreach_has_key {php_variable, php_t_ht_iterator}.
type php_foreach_get_key ::= c_php_foreach_get_key {php_variable, php_t_ht_iterator}.
type php_foreach_get_val ::= c_php_foreach_get_val {php_variable, php_t_ht_iterator}.
type php_assignment ::= c_php_assignment {php_variable, bool, php_expr}.
type php_op_assignment ::= c_php_op_assignment {php_variable, php_t_op, php_expr}.
type php_list_assignment ::= c_php_list_assignment {list[php_list_element], php_expr}.
type php_nested_list_elements ::= c_php_nested_list_elements {list[php_list_element]}.
type php_cast ::= c_php_cast {php_t_cast, php_expr}.
type php_unary_op ::= c_php_unary_op {php_t_op, php_expr}.
type php_bin_op ::= c_php_bin_op {php_expr, php_t_op, php_expr}.
type php_conditional_expr ::= c_php_conditional_expr {php_expr, php_expr, php_expr}.
type php_ignore_errors ::= c_php_ignore_errors {php_expr}.
type php_constant ::= c_php_constant {php_t_class_name, php_t_constant_name}.
type php_instanceof ::= c_php_instanceof {php_expr, php_class_name}.
type php_variable ::= c_php_variable {php_target, php_variable_name, list[php_expr]}.
type php_reflection ::= c_php_reflection {php_expr}.
type php_pre_op ::= c_php_pre_op {php_t_op, php_variable}.
type php_array ::= c_php_array {list[php_array_elem]}.
type php_array_elem ::= c_php_array_elem {php_expr, bool, php_expr}.
type php_method_invocation ::= c_php_method_invocation {php_target, php_method_name, list[php_actual_parameter]}.
type php_actual_parameter ::= c_php_actual_parameter {bool, php_expr}.
type php_new ::= c_php_new {php_class_name, list[php_actual_parameter]}.


% Disjunctive types
type php_identifier ::= 
		  c_php_identifier_php_t_interface_name { php_t_interface_name } 
		| c_php_identifier_php_t_class_name { php_t_class_name } 
		| c_php_identifier_php_t_method_name { php_t_method_name } 
		| c_php_identifier_php_t_variable_name { php_t_variable_name } 
		| c_php_identifier_php_t_cast { php_t_cast } 
		| c_php_identifier_php_t_op { php_t_op } 
		| c_php_identifier_php_t_constant_name { php_t_constant_name } 
		| c_php_identifier_php_t_label_name { php_t_label_name } 
		.
type php_commented_node ::= 
		  c_php_commented_node_php_method { php_method } 
		| c_php_commented_node_php_attribute { php_attribute } 
		| c_php_commented_node_php_class_def { php_class_def } 
		| c_php_commented_node_php_interface_def { php_interface_def } 
		| c_php_commented_node_php_return { php_return } 
		| c_php_commented_node_php_static_declaration { php_static_declaration } 
		| c_php_commented_node_php_global { php_global } 
		| c_php_commented_node_php_try { php_try } 
		| c_php_commented_node_php_throw { php_throw } 
		| c_php_commented_node_php_eval_expr { php_eval_expr } 
		| c_php_commented_node_php_if { php_if } 
		| c_php_commented_node_php_loop { php_loop } 
		| c_php_commented_node_php_foreach { php_foreach } 
		| c_php_commented_node_php_switch { php_switch } 
		| c_php_commented_node_php_break { php_break } 
		| c_php_commented_node_php_continue { php_continue } 
		| c_php_commented_node_php_label { php_label } 
		| c_php_commented_node_php_goto { php_goto } 
		| c_php_commented_node_php_branch { php_branch } 
		| c_php_commented_node_php_foreach_next { php_foreach_next } 
		| c_php_commented_node_php_foreach_reset { php_foreach_reset } 
		| c_php_commented_node_php_foreach_end { php_foreach_end } 
		| c_php_commented_node_php_switch_case { php_switch_case } 
		| c_php_commented_node_php_catch { php_catch } 
		.
type php_class_name ::= 
		  c_php_class_name_php_t_class_name { php_t_class_name } 
		| c_php_class_name_php_reflection { php_reflection } 
		.
type php_method_name ::= 
		  c_php_method_name_php_t_method_name { php_t_method_name } 
		| c_php_method_name_php_reflection { php_reflection } 
		.
type php_target ::= 
		  c_php_target_php_assignment { php_assignment } 
		| c_php_target_php_cast { php_cast } 
		| c_php_target_php_unary_op { php_unary_op } 
		| c_php_target_php_bin_op { php_bin_op } 
		| c_php_target_php_constant { php_constant } 
		| c_php_target_php_instanceof { php_instanceof } 
		| c_php_target_php_variable { php_variable } 
		| c_php_target_php_pre_op { php_pre_op } 
		| c_php_target_php_method_invocation { php_method_invocation } 
		| c_php_target_php_new { php_new } 
		| c_php_target_php_t_int { php_t_int } 
		| c_php_target_php_t_real { php_t_real } 
		| c_php_target_php_t_string { php_t_string } 
		| c_php_target_php_t_bool { php_t_bool } 
		| c_php_target_php_t_nil { php_t_nil } 
		| c_php_target_php_op_assignment { php_op_assignment } 
		| c_php_target_php_list_assignment { php_list_assignment } 
		| c_php_target_php_array { php_array } 
		| c_php_target_php_ignore_errors { php_ignore_errors } 
		| c_php_target_php_foreach_has_key { php_foreach_has_key } 
		| c_php_target_php_foreach_get_key { php_foreach_get_key } 
		| c_php_target_php_foreach_get_val { php_foreach_get_val } 
		| c_php_target_php_t_class_name { php_t_class_name } 
		.
type php_variable_name ::= 
		  c_php_variable_name_php_t_variable_name { php_t_variable_name } 
		| c_php_variable_name_php_reflection { php_reflection } 
		.
type php_list_element ::= 
		  c_php_list_element_php_variable { php_variable } 
		| c_php_list_element_php_nested_list_elements { php_nested_list_elements } 
		.
type php_literal ::= 
		  c_php_literal_php_t_int { php_t_int } 
		| c_php_literal_php_t_real { php_t_real } 
		| c_php_literal_php_t_string { php_t_string } 
		| c_php_literal_php_t_bool { php_t_bool } 
		| c_php_literal_php_t_nil { php_t_nil } 
		.
type php_expr ::= 
		  c_php_expr_php_assignment { php_assignment } 
		| c_php_expr_php_cast { php_cast } 
		| c_php_expr_php_unary_op { php_unary_op } 
		| c_php_expr_php_bin_op { php_bin_op } 
		| c_php_expr_php_constant { php_constant } 
		| c_php_expr_php_instanceof { php_instanceof } 
		| c_php_expr_php_variable { php_variable } 
		| c_php_expr_php_pre_op { php_pre_op } 
		| c_php_expr_php_method_invocation { php_method_invocation } 
		| c_php_expr_php_new { php_new } 
		| c_php_expr_php_t_int { php_t_int } 
		| c_php_expr_php_t_real { php_t_real } 
		| c_php_expr_php_t_string { php_t_string } 
		| c_php_expr_php_t_bool { php_t_bool } 
		| c_php_expr_php_t_nil { php_t_nil } 
		| c_php_expr_php_op_assignment { php_op_assignment } 
		| c_php_expr_php_list_assignment { php_list_assignment } 
		| c_php_expr_php_array { php_array } 
		| c_php_expr_php_ignore_errors { php_ignore_errors } 
		| c_php_expr_php_foreach_has_key { php_foreach_has_key } 
		| c_php_expr_php_foreach_get_key { php_foreach_get_key } 
		| c_php_expr_php_foreach_get_val { php_foreach_get_val } 
		.
type php_member ::= 
		  c_php_member_php_method { php_method } 
		| c_php_member_php_attribute { php_attribute } 
		.
type php_statement ::= 
		  c_php_statement_php_class_def { php_class_def } 
		| c_php_statement_php_interface_def { php_interface_def } 
		| c_php_statement_php_method { php_method } 
		| c_php_statement_php_return { php_return } 
		| c_php_statement_php_static_declaration { php_static_declaration } 
		| c_php_statement_php_global { php_global } 
		| c_php_statement_php_try { php_try } 
		| c_php_statement_php_throw { php_throw } 
		| c_php_statement_php_eval_expr { php_eval_expr } 
		| c_php_statement_php_if { php_if } 
		| c_php_statement_php_loop { php_loop } 
		| c_php_statement_php_foreach { php_foreach } 
		| c_php_statement_php_switch { php_switch } 
		| c_php_statement_php_break { php_break } 
		| c_php_statement_php_continue { php_continue } 
		| c_php_statement_php_label { php_label } 
		| c_php_statement_php_goto { php_goto } 
		| c_php_statement_php_branch { php_branch } 
		| c_php_statement_php_foreach_next { php_foreach_next } 
		| c_php_statement_php_foreach_reset { php_foreach_reset } 
		| c_php_statement_php_foreach_end { php_foreach_end } 
		.
type php_node ::= 
		  c_php_node_php_php_script { php_php_script } 
		| c_php_node_php_class_mod { php_class_mod } 
		| c_php_node_php_signature { php_signature } 
		| c_php_node_php_method_mod { php_method_mod } 
		| c_php_node_php_formal_parameter { php_formal_parameter } 
		| c_php_node_php_type { php_type } 
		| c_php_node_php_attr_mod { php_attr_mod } 
		| c_php_node_php_name_with_default { php_name_with_default } 
		| c_php_node_php_variable { php_variable } 
		| c_php_node_php_nested_list_elements { php_nested_list_elements } 
		| c_php_node_php_conditional_expr { php_conditional_expr } 
		| c_php_node_php_t_variable_name { php_t_variable_name } 
		| c_php_node_php_reflection { php_reflection } 
		| c_php_node_php_assignment { php_assignment } 
		| c_php_node_php_cast { php_cast } 
		| c_php_node_php_unary_op { php_unary_op } 
		| c_php_node_php_bin_op { php_bin_op } 
		| c_php_node_php_constant { php_constant } 
		| c_php_node_php_instanceof { php_instanceof } 
		| c_php_node_php_pre_op { php_pre_op } 
		| c_php_node_php_method_invocation { php_method_invocation } 
		| c_php_node_php_new { php_new } 
		| c_php_node_php_t_int { php_t_int } 
		| c_php_node_php_t_real { php_t_real } 
		| c_php_node_php_t_string { php_t_string } 
		| c_php_node_php_t_bool { php_t_bool } 
		| c_php_node_php_t_nil { php_t_nil } 
		| c_php_node_php_op_assignment { php_op_assignment } 
		| c_php_node_php_list_assignment { php_list_assignment } 
		| c_php_node_php_array { php_array } 
		| c_php_node_php_ignore_errors { php_ignore_errors } 
		| c_php_node_php_foreach_has_key { php_foreach_has_key } 
		| c_php_node_php_foreach_get_key { php_foreach_get_key } 
		| c_php_node_php_foreach_get_val { php_foreach_get_val } 
		| c_php_node_php_t_class_name { php_t_class_name } 
		| c_php_node_php_array_elem { php_array_elem } 
		| c_php_node_php_t_method_name { php_t_method_name } 
		| c_php_node_php_actual_parameter { php_actual_parameter } 
		| c_php_node_php_method { php_method } 
		| c_php_node_php_attribute { php_attribute } 
		| c_php_node_php_class_def { php_class_def } 
		| c_php_node_php_interface_def { php_interface_def } 
		| c_php_node_php_return { php_return } 
		| c_php_node_php_static_declaration { php_static_declaration } 
		| c_php_node_php_global { php_global } 
		| c_php_node_php_try { php_try } 
		| c_php_node_php_throw { php_throw } 
		| c_php_node_php_eval_expr { php_eval_expr } 
		| c_php_node_php_if { php_if } 
		| c_php_node_php_loop { php_loop } 
		| c_php_node_php_foreach { php_foreach } 
		| c_php_node_php_switch { php_switch } 
		| c_php_node_php_break { php_break } 
		| c_php_node_php_continue { php_continue } 
		| c_php_node_php_label { php_label } 
		| c_php_node_php_goto { php_goto } 
		| c_php_node_php_branch { php_branch } 
		| c_php_node_php_foreach_next { php_foreach_next } 
		| c_php_node_php_foreach_reset { php_foreach_reset } 
		| c_php_node_php_foreach_end { php_foreach_end } 
		| c_php_node_php_switch_case { php_switch_case } 
		| c_php_node_php_catch { php_catch } 
		| c_php_node_php_t_interface_name { php_t_interface_name } 
		| c_php_node_php_t_cast { php_t_cast } 
		| c_php_node_php_t_op { php_t_op } 
		| c_php_node_php_t_constant_name { php_t_constant_name } 
		| c_php_node_php_t_label_name { php_t_label_name } 
		| c_php_node_php_t_ht_iterator { php_t_ht_iterator } 
		.


% Predicates
predicate phc_php_script (STATEMENTS:list[php_statement]).
predicate phc_class_def (CLASS_MOD:php_class_mod, CLASS_NAME:php_t_class_name, EXTENDS:php_t_class_name, IMPLEMENTS:list[php_t_interface_name], MEMBERS:list[php_member]).
predicate phc_class_mod (IS_ABSTRACT:bool, IS_FINAL:bool).
predicate phc_interface_def (INTERFACE_NAME:php_t_interface_name, EXTENDS:list[php_t_interface_name], MEMBERS:list[php_member]).
predicate phc_method (SIGNATURE:php_signature, STATEMENTS:list[php_statement]).
predicate phc_signature (METHOD_MOD:php_method_mod, IS_REF:bool, METHOD_NAME:php_t_method_name, FORMAL_PARAMETERS:list[php_formal_parameter]).
predicate phc_method_mod (IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_ABSTRACT:bool, IS_FINAL:bool).
predicate phc_formal_parameter (TYPE:php_type, IS_REF:bool, VAR:php_name_with_default).
predicate phc_type (CLASS_NAME:php_t_class_name).
predicate phc_attribute (ATTR_MOD:php_attr_mod, VARS:list[php_name_with_default]).
predicate phc_attr_mod (IS_PUBLIC:bool, IS_PROTECTED:bool, IS_PRIVATE:bool, IS_STATIC:bool, IS_CONST:bool).
predicate phc_name_with_default (VARIABLE_NAME:php_t_variable_name, EXPR:php_expr).
predicate phc_if (EXPR:php_expr, IFTRUE:list[php_statement], IFFALSE:list[php_statement]).
predicate phc_loop (STATEMENTS:list[php_statement]).
predicate phc_foreach (EXPR:php_expr, KEY:php_variable, IS_REF:bool, VAL:php_variable, STATEMENTS:list[php_statement]).
predicate phc_switch (EXPR:php_expr, SWITCH_CASES:list[php_switch_case]).
predicate phc_switch_case (EXPR:php_expr, STATEMENTS:list[php_statement]).
predicate phc_break (EXPR:php_expr).
predicate phc_continue (EXPR:php_expr).
predicate phc_return (EXPR:php_expr).
predicate phc_static_declaration (VARS:list[php_name_with_default]).
predicate phc_global (VARIABLE_NAMES:list[php_variable_name]).
predicate phc_try (STATEMENTS:list[php_statement], CATCHES:list[php_catch]).
predicate phc_catch (CLASS_NAME:php_t_class_name, VARIABLE_NAME:php_t_variable_name, STATEMENTS:list[php_statement]).
predicate phc_throw (EXPR:php_expr).
predicate phc_eval_expr (EXPR:php_expr).
predicate phc_branch (EXPR:php_expr, IFTRUE:php_t_label_name, IFFALSE:php_t_label_name).
predicate phc_goto (LABEL_NAME:php_t_label_name).
predicate phc_label (LABEL_NAME:php_t_label_name).
predicate phc_foreach_reset (VARIABLE:php_variable, HT_ITERATOR:php_t_ht_iterator).
predicate phc_foreach_next (VARIABLE:php_variable, HT_ITERATOR:php_t_ht_iterator).
predicate phc_foreach_end (VARIABLE:php_variable, HT_ITERATOR:php_t_ht_iterator).
predicate phc_foreach_has_key (VARIABLE:php_variable, HT_ITERATOR:php_t_ht_iterator).
predicate phc_foreach_get_key (VARIABLE:php_variable, HT_ITERATOR:php_t_ht_iterator).
predicate phc_foreach_get_val (VARIABLE:php_variable, HT_ITERATOR:php_t_ht_iterator).
predicate phc_assignment (VARIABLE:php_variable, IS_REF:bool, EXPR:php_expr).
predicate phc_op_assignment (VARIABLE:php_variable, OP:php_t_op, EXPR:php_expr).
predicate phc_list_assignment (LIST_ELEMENTS:list[php_list_element], EXPR:php_expr).
predicate phc_nested_list_elements (LIST_ELEMENTS:list[php_list_element]).
predicate phc_cast (CAST:php_t_cast, EXPR:php_expr).
predicate phc_unary_op (OP:php_t_op, EXPR:php_expr).
predicate phc_bin_op (LEFT:php_expr, OP:php_t_op, RIGHT:php_expr).
predicate phc_conditional_expr (COND:php_expr, IFTRUE:php_expr, IFFALSE:php_expr).
predicate phc_ignore_errors (EXPR:php_expr).
predicate phc_constant (CLASS_NAME:php_t_class_name, CONSTANT_NAME:php_t_constant_name).
predicate phc_instanceof (EXPR:php_expr, CLASS_NAME:php_class_name).
predicate phc_variable (TARGET:php_target, VARIABLE_NAME:php_variable_name, ARRAY_INDICES:list[php_expr]).
predicate phc_reflection (EXPR:php_expr).
predicate phc_pre_op (OP:php_t_op, VARIABLE:php_variable).
predicate phc_array (ARRAY_ELEMS:list[php_array_elem]).
predicate phc_array_elem (KEY:php_expr, IS_REF:bool, VAL:php_expr).
predicate phc_method_invocation (TARGET:php_target, METHOD_NAME:php_method_name, ACTUAL_PARAMETERS:list[php_actual_parameter]).
predicate phc_actual_parameter (IS_REF:bool, EXPR:php_expr).
predicate phc_new (CLASS_NAME:php_class_name, ACTUAL_PARAMETERS:list[php_actual_parameter]).

