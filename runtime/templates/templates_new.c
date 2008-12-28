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
 *	 TODO: move the 'properties' to callbacks.
 *	 Supported properties:
 *	    hash - a string's hash value (including the 'u' suffix
 *	    length - a string's length
 *	    TODO: maybe attrs.name? to reduce the number of parameters
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
  zval** p_lhs = &local_$L;
  \read_rvalue ("rhs", RHS);
  \write_var ("p_lhs", "rhs", LHS, RHS);
@@@

assign_expr_var (token LHS, token RHS)
@@@
  \get_st_entry ("LOCAL", "lhs", LHS);
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
  sep_copy_on_write ("p_rhs");
  copy_into_ref ("p_lhs", "p_rhs");
@@@

/*
 * Casts
 */
assign_expr_cast (token LHS, token RHS, string TYPE)
@@@
  \assign_expr_var (LHS, RHS);
  cast_var (p_lhs, $TYPE);
@@@

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

  p_lhs = &local_$L;
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

  zval* old = **p_lhs;
  int result_is_operand = (*p_lhs == left || *p_lhs == right);
  $OP_FN (*p_lhs, left, right TSRMLS_CC);

  // If the result is one of the operands, the operator function
  // will already have cleaned up the result
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
      local_$VAR = EG (uninitialized~_zval_ptr);
      local_$VAR->refcount++;
    }
  zval** $ZVP = &local_$VAR;
@@@

// TODO: inline better
get_st_entry (string SCOPE, string ZVP, token VAR)
@@@
  zval** $ZVP = get_st_entry (\scope(scope);, "$VAR", ${VAR.length} + 1, ${VAR.hash});
@@@

scope (string SCOPE) where SCOPE == "LOCAL" @@@EG(active_symbol_table)@@@
scope (string SCOPE) where SCOPE == "GLOBAL" @@@&EG(symbol_table)@@@


/*
 * read_value
 */

read_rvalue (string ZVP, token LIT)
   where LIT.type == "Literal"
   where LIT.pool_name
@@@
  zval* $ZVP = ${LIT.pool_name};
@@@

read_rvalue (string ZVP, token LIT)
   where LIT.type == "Literal"
@@@
  zval* lit_tmp_$ZVP;
  INIT_ZVAL (lit_tmp_$ZVP);
  zval* $ZVP = &lit_tmp_$ZVP;
  \cb:write_literal_directly_into_zval (ZVP, LIT);
@@@

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

read_rvalue (string ZVP, token VAR)
@@@
  zval* $ZVP = read_var (\scope("LOCAL"), "$VAR", ${VAR.length} + 1, ${VAR.hash} TSRMLS_CC);
@@@


/*
 * write_var
 */

write_var (token LHS, token RHS)
   where LHS.is_uninitialized
@@@
  \write_var_inner (L, R, RHS);
@@@

write_var (token LHS, token RHS)
@@@
  if ((*$LHS)->is_ref)
      overwrite_lhs (*$LHS, $RHS);
  else
    {
      zval_ptr_dtor ($LHS);
      \write_var_inner (LHS, RHS);
    }
@@@

write_var_inner (token LHS, token RHS)
   where RHS.is_uninitialized
@@@
  // Share a copy
  $RHS->refcount++;
  *$LHS = $RHS;
@@@


write_var_inner (token LHS, token RHS)
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

