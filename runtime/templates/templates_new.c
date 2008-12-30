/* Quick intro:
 * Each pattern is matched in the order it appears. If it matches, code is
 * generated based on its template. If nothing matches, there is an error.
 *
 * Matching:
 *    To match, it must match with the correct name and rules. (its an error to
 *    have multiple patterns with different signatures).
 *
 * Signature:
 *    A name, followed by a list of parameters, followed by a list of rules.
 *
 * Parameters:
 *    A type and a name.
 *
 * Allowed types:
 *    attrs: attributes, taken directly from the MIR::Node's attributes.
 *    bool: boolean. To pass, use the name, or true|false
 *    string: quoted string. To pass, use the name or a quoted string.
 *    node: like an attr, but has a type field
 *    token: a special node with a value field. It can be interpolated, which uses the value field.
 *
 * Rules:
 *    Each rule is a boolean condition, preceeded by 'where '. Their evaluation is based on their type:
 *	 attrs: where attr.some_attribute_name
 *	 string: where param == "some string"
 *	 bool: where param == true|false
 *	 node: where node.type == Literal
 *	 token: where node.value = "STRING"
 *    Rules are all ANDed together. There is no way to OR two rules together.
 *
 * Templates:
 *    A template is basically C code, with two types of interpolation:
 *	 To use a parameter PARAM, use $PARAM (even in quoted strings).
 *	 To call another template, use \other_template (param0, ... );
 *	 To use a property of a PARAM, use ${PARAM.propname}.
 *	 To do a callback to the code generator, use \cb:callback_name (param0, ...);.
 *	 The callback must be registered.
 *
 * Comments:
 *    Comment are allowed outside patterns. Comments inside templates are C
 *    comments, and will appear in the generated code.
 */


/*
 * Simple assignments
 * $x = $y;
 */

assign_expr_var (token LHS, token RHS)
   where LHS.st_entry_not_required
   where LHS.is_uninitialized
@@@
  zval** p_lhs = &local_$LHS;
  \read_rvalue ("rhs", RHS);
  \write_var ("p_lhs", "rhs", LHS, RHS);
@@@

assign_expr_var (token LHS, token RHS)
@@@
  \get_st_entry ("LOCAL", "p_lhs", LHS);
  \read_rvalue ("rhs", RHS);
  if (*p_lhs != rhs)
    {
      \write_var ("p_lhs", "rhs", LHS, RHS);
    }
@@@



/*
 * $x =& $y;
 */
assign_expr_ref_var (token LHS, token RHS)
@@@
  \get_st_entry ("LOCAL", "p_lhs", LHS);
  \get_st_entry ("LOCAL", "p_rhs", RHS);
  sep_copy_on_write (p_rhs);
  copy_into_ref (p_lhs, p_rhs);
@@@

/*
 * Casts
 */
assign_expr_cast (token LHS, token RHS, string TYPE)
@@@
  \assign_expr_var (LHS, RHS);
  \cast_var ("p_lhs", TYPE);
@@@

cast_var (string LHS, string TYPE)
@@@
  assert ($TYPE >= 0 && $TYPE <= 6);
  if ((*$LHS)->type != $TYPE)
  {
    sep_copy_on_write ($LHS);
    \convert_to (TYPE) (*$LHS);
  }
@@@

convert_to (string TYPE) where TYPE == "IS_ARRAY" @@@convert_to_array@@@
convert_to (string TYPE) where TYPE == "IS_BOOL" @@@convert_to_boolean@@@
convert_to (string TYPE) where TYPE == "IS_DOUBLE" @@@convert_to_double@@@
convert_to (string TYPE) where TYPE == "IS_LONG" @@@convert_to_long@@@
convert_to (string TYPE) where TYPE == "IS_NULL" @@@convert_to_null@@@
convert_to (string TYPE) where TYPE == "IS_STRING" @@@convert_to_string@@@
convert_to (string TYPE) where TYPE == "IS_OBJECT" @@@convert_to_object@@@

/*
 * Bin-ops
 */

// We could do this for non-LOCAL, but we'd only be saving an refcount++ and a refcount--.
assign_expr_bin_op (token LHS, node LEFT, node RIGHT, string OP_FN)
   where LHS.st_entry_not_required
   where LHS.is_uninitialized
@@@
  \read_rvalue ("left", LEFT);
  \read_rvalue ("right", RIGHT);

  zval** p_lhs = &local_$LHS;
  ALLOC_INIT_ZVAL (*p_lhs);

  $OP_FN (*p_lhs, left, right TSRMLS_CC);
@@@

// OP_FN: for example "add_function"
// The caller must sort out the order of LEFT and RIGHT for > and >=
// We use NODE for LEFT and RIGHT, since they might be literals
assign_expr_bin_op (token LHS, node LEFT, node RIGHT, string OP_FN)
@@@
  \get_st_entry ("LOCAL", "p_lhs", LHS);
  \read_rvalue ("left", LEFT);
  \read_rvalue ("right", RIGHT);
  if (in_copy_on_write (*p_lhs))
    {
      zval_ptr_dtor (p_lhs);
      ALLOC_INIT_ZVAL (*p_lhs);
    }

  zval old = **p_lhs;
  int result_is_operand = (*p_lhs == left || *p_lhs == right);
  $OP_FN (*p_lhs, left, right TSRMLS_CC);

  // If the result is one of the operands, the operator function
  // will already have cleaned up the result
  if (!result_is_operand)
    zval_dtor (&old);
@@@

/*
 * Unary-ops
 */
assign_expr_unary_op (token LHS, node RHS, string OP_FN)
@@@
   \get_st_entry ("LOCAL", "p_lhs", LHS);
   \read_rvalue ("rhs", RHS);
   if (in_copy_on_write (*p_lhs))
   {
     zval_ptr_dtor (p_lhs);
     ALLOC_INIT_ZVAL (*p_lhs);
   }

   zval old = **p_lhs;
   int result_is_operand = (*p_lhs == rhs);
   $OP_FN (*p_lhs, rhs TSRMLS_CC);
   if (!result_is_operand)
	zval_dtor (&old);
@@@


/*
 * Var-vars
 */
assign_expr_var_var (token LHS, token INDEX)
@@@
  \get_st_entry ("LOCAL", "p_lhs", LHS);
  \read_rvalue ("index", INDEX);
  zval* rhs;
  \read_var_var ("rhs", "index");
  if (*p_lhs != rhs)
    {
      \write_var ("p_lhs", "rhs", LHS, INDEX);
    }
@@@

assign_expr_ref_var_var (token LHS, token INDEX)
@@@
  \get_st_entry ("LOCAL", "p_lhs", LHS);
  \read_rvalue ("index", INDEX);
  zval** p_rhs;
  \get_var_var ("LOCAL", "p_rhs", "index");
  sep_copy_on_write (p_rhs);
  copy_into_ref (p_lhs, p_rhs);
@@@

/*
 * Array access
 */
assign_expr_array_access (token LHS, token ARRAY, token INDEX)
@@@
   \get_st_entry ("LOCAL", "p_lhs", LHS);
   \read_rvalue ("r_array", ARRAY);
   \read_rvalue ("r_index", INDEX);

   zval* rhs;
   int is_rhs_new = 0;
    if (Z_TYPE_P (r_array) != IS_ARRAY)
    {
      if (Z_TYPE_P (r_array) == IS_STRING)
	{
	  is_rhs_new = 1;
	  rhs = read_string_index (r_array, r_index TSRMLS_CC);
	}
      else
	// TODO: warning here?
	rhs = EG (uninitialized_zval_ptr);
    }
    else
    {
      if (check_array_index_type (r_index TSRMLS_CC))
	{
	  // Read array variable
	  read_array (&rhs, r_array, r_index TSRMLS_CC);
	}
      else
	rhs = *p_lhs; // HACK to fail  *p_lhs != rhs
    }

   if (*p_lhs != rhs)
      write_var (p_lhs, rhs);

   if (is_rhs_new) zval_ptr_dtor (&rhs);
@@@

assign_expr_ref_array_access (token LHS, token ARRAY, token INDEX)
@@@
   \get_st_entry ("LOCAL", "p_lhs", LHS);
   \get_st_entry ("LOCAL", "p_r_array", ARRAY);
   \read_rvalue ("r_index", INDEX);
   check_array_type (p_r_array TSRMLS_CC);
   zval** p_rhs = get_ht_entry (p_r_array, r_index TSRMLS_CC);
   sep_copy_on_write (p_rhs);
   copy_into_ref (p_lhs, p_rhs);
@@@

/*
 * Constants
 */
assign_expr_constant (token LHS, string CONSTANT)
@@@
   // No null-terminator in length for get_constant.
   // zend_get_constant always returns a copy of the constant.
   \get_st_entry ("LOCAL", "p_lhs", LHS);
   if (!(*p_lhs)->is_ref)
   {
     zval_ptr_dtor (p_lhs);
     get_constant ("$CONSTANT", \cb:length(CONSTANT), p_lhs TSRMLS_CC);
   }
   else
   {
     zval* constant;
     get_constant ("$CONSTANT", \cb:length(CONSTANT), p_lhs TSRMLS_CC);
     overwrite_lhs_no_copy (*p_lhs, constant);
     safe_free_zval_ptr (constant);
   }
@@@



/*
 * SCOPE: LOCAL/GLOBAL
 * NAME: A name for the zvpp.
 * VAR: Attribute map
 */
get_st_entry (string SCOPE, string ZVP, token VAR)
   where SCOPE == "LOCAL"
   where VAR.st_entry_not_required
@@@
  if (local_$VAR == NULL)
    {
      local_$VAR = EG (uninitialized_zval_ptr);
      local_$VAR->refcount++;
    }
  zval** $ZVP = &local_$VAR;
@@@

// TODO: inline better
get_st_entry (string SCOPE, string ZVP, token VAR)
@@@
  zval** $ZVP = get_st_entry (\scope(SCOPE), "$VAR", \cb:length(VAR) + 1, \cb:hash(VAR) TSRMLS_CC);
@@@

scope (string SCOPE) where SCOPE == "LOCAL" @@@EG(active_symbol_table)@@@
scope (string SCOPE) where SCOPE == "GLOBAL" @@@&EG(symbol_table)@@@


/*
 * read_value
 */

// For literals
read_rvalue (string ZVP, node LIT)
   where \cb:is_literal(LIT) == "TRUE"
   where LIT.pool_name
@@@
  zval* $ZVP = ${LIT.pool_name};
@@@

read_rvalue (string ZVP, node LIT)
   where \cb:is_literal(LIT) == "TRUE"
@@@
  zval* lit_tmp_$ZVP;
  INIT_ZVAL (lit_tmp_$ZVP);
  zval* $ZVP = &lit_tmp_$ZVP;
  \cb:write_literal_directly_into_zval (ZVP, LIT);
@@@

// Not for literals (not that the signature changes here - thats intentional)
read_rvalue (string ZVP, token VAR)
   where VAR.st_entry_not_required
   where VAR.is_uninitialized
@@@
  zval* $ZVP = EG (uninitialized_zval_ptr);
@@@

read_rvalue (string ZVP, token VAR)
   where VAR.st_entry_not_required
   where VAR.is_initialized
@@@
  zval* $ZVP = local_$VAR;
@@@

read_rvalue (string ZVP, token VAR)
   where VAR.st_entry_not_required
@@@
  zval* $ZVP;
  if (local_$VAR == NULL)
    $ZVP = EG (uninitialized_zval_ptr);
  else
    $ZVP = local_$VAR;
@@@

read_rvalue (string ZVP, token TVAR)
@@@
  zval* $ZVP = read_var (\scope("LOCAL");, "$TVAR", \cb:length(TVAR) + 1, \cb:hash(TVAR) TSRMLS_CC);
@@@


/*
 * write_var
 */

write_var (string LHS, string RHS, token TLHS, token TRHS)
   where TLHS.is_uninitialized
@@@
  \write_var_inner (LHS, RHS, TLHS, TRHS);
@@@

write_var (string LHS, string RHS, token TLHS, token TRHS)
@@@
  if ((*$LHS)->is_ref)
      overwrite_lhs (*$LHS, $RHS);
  else
    {
      zval_ptr_dtor ($LHS);
      \write_var_inner (LHS, RHS, TLHS, TRHS);
    }
@@@

write_var_inner (string LHS, string RHS, token TLHS, token TRHS)
   where TRHS.is_uninitialized
@@@
  // Share a copy
  $RHS->refcount++;
  *$LHS = $RHS;
@@@


write_var_inner (string LHS, string RHS, token TLHS, token TRHS)
@@@
  if ($RHS->is_ref)
    {
      // Take a copy of RHS for LHS
      *$LHS = zvp_clone_ex ($RHS);
    }
  else
    {
      // Share a copy
      $RHS->refcount++;
      *$LHS = $RHS;
    }
@@@

/*
 * var-vars
 */

read_var_var (string ZVP, string INDEX)
@@@
   $ZVP = read_var_var (\scope("LOCAL"), $INDEX TSRMLS_CC);
@@@

get_var_var (string ST, string ZVP, string INDEX)
@@@
   $ZVP = get_var_var (\scope(ST), $INDEX TSRMLS_CC);
@@@



/*
 * Foreach
 */

// TODO: Find a nice way to avoid this duplication
assign_expr_ref_foreach_get_val (token LHS, token ARRAY, string ITERATOR)
@@@
   \get_st_entry ("LOCAL", "p_lhs", LHS);
   // TODO: we know this is an array
   \read_rvalue ("fe_array", ARRAY);

   zval** p_rhs = NULL;
   int result = zend_hash_get_current_data_ex (
					       fe_array->value.ht,
					       (void**)(&p_rhs),
					       &$ITERATOR);
   assert (result == SUCCESS);

   sep_copy_on_write (p_rhs);
   copy_into_ref (p_lhs, p_rhs);
@@@

assign_expr_foreach_get_val (token LHS, token ARRAY, string ITERATOR)
@@@
   \get_st_entry ("LOCAL", "p_lhs", LHS);
   // TODO: we know this is an array
   \read_rvalue ("fe_array", ARRAY);

   zval** p_rhs = NULL;
   int result = zend_hash_get_current_data_ex (
					       fe_array->value.ht,
					       (void**)(&p_rhs),
					       &$ITERATOR);
   assert (result == SUCCESS);

   if (*p_lhs != *p_rhs)
      write_var (p_lhs, *p_rhs);
@@@


