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
 *    a type and a name.
 *    Allowed types:
 *	 attrs: attributes, taken directly from the MIR::Node's attributes. To passname.
 *	 bool: boolean. To pass, use the name, or true|false
 *	 string: quoted string. To pass, use the name or a quoted string.
 *	 enum: symbol. To pass, use the name or symbol name (TODO: prevent ambiguity)
 *
 * Rules:
 *    Each rule is a boolean condition, preceeded by 'where '. Their evaluation is based on their type:
 *	 attrs: where attr.some_attribute_name
 *	 string: where param == "some string"
 *	 bool: where param == true|false
 *	 enum where param == SYMBOL_NAME
 *    Rules are all ANDed together. There is no way to OR two rules together.
 *
 * Templates:
 *    A template is basically C code, with two types of interpolation:
 *	 To use a parameter PARAM, use $PARAM (even in quoted strings).
 *	 To call another template, use \other_template (params, ... );
 *
 * Comments:
 *    Comment are allowed outside patterns. Comments inside templates are C
 *    comments, and will appear in the generated code.
 *    TODO: interpolate variables in Comments?
 *
 */


/*
 * Simple assignments
 * $x = $y;
 */

assign_expr_var (string L, string R, attrs LHS, attrs RHS)
   where scope == LOCAL
   where VAR.st_entry_not_required
   where LHS.is_uninitialized
{
  zval** p_lhs = &local_$L;
  \read_rvalue ("rhs", R, RHS);
  \write_var ("p_lhs", "rhs", LHS, RHS);
}

assign_expr_var (string L, string R, attrs LHS, attrs RHS)
{
  \get_st_entry (LOCAL, "lhs", L, LHS);
  \read_rvalue ("rhs", R, RHS);
  \write_var ("p_lhs", "rhs", LHS, RHS);
}



/*
 * $x =& $y;
 */
assign_expr_ref_var (string L, string R, attrs LHS, attrs RHS)
{
  \get_st_entry (LOCAL, "lhs", L, LHS);
  \get_st_entry (LOCAL, "rhs", R, RHS);
  \sep_copy_on_write ("rhs");
  \copy_into_ref ("lhs", "rhs");
}

/*
 * Casts
 */
assign_expr_cast (string L, string R, attrs LHS, attrs RHS, string TYPE)
{
  \assign_expr_var (L, R, LHS, RHS, false);
  cast_var (p_lhs, $TYPE);
}

/*
 * Bin-ops
 */

// OP_FN: for example "add_function"
// The caller must sort out the order of LEFT and RIGHT for > and >=
assign_expr_bin_op (string LHS_NAME, string LE, string RI, string OP_FN, attrs LHS, attrs LEFT, attrs RIGHT)
{
  \get_st_entry (LOCAL, "p_lhs", L, LHS);
  \read_rvalue ("left", LE, LEFT);
  \read_rvalue ("right", RI, RIGHT);
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
}

// We could do this for non-LOCAL, but we'd only be saving an refcount++ and a refcount--.
assign_expr_bin_op (string L, string LE, string RI, string OP_FN, attrs LHS, attrs LEFT, attrs RIGHT)
   where scope == LOCAL
   where VAR.st_entry_not_required
   where LHS.is_uninitialized
{
  \read_rvalue ("left", LE, LEFT);
  \read_rvalue ("right", RI, RIGHT);

  p_lhs = &local_$L;
  ALLOC_INIT_ZVAL (*p_lhs);

  $OP_FN (*p_lhs, left, right TSRMLS_CC);
}



/*
 * SCOPE: LOCAL/GLOBAL
 * NAME: A name for the zvpp.
 * VAR: Attribute map
 */
get_st_entry (enum SCOPE, string ZVP, string NAME, attrs VAR)
   where scope == LOCAL
   where VAR.st_entry_not_required
{
  if (local_$NAME == NULL)
    {
      local_$NAME = EG (uninitialized~_zval_ptr);
      local_$NAME->refcount++;
    }
  zval** $ZVP = &local_$NAME;
}

// TODO: inline better
get_st_entry (enum SCOPE, string ZVP, string NAME, attrs VAR)
{
  zval** $ZVP = get_st_entry (\scope(scope);, "$NAME", ${NAME.length} + 1, ${NAME.hash});
}

scope (enum SCOPE) where SCOPE = LOCAL {EG(active_symbol_table)}
scope (enum SCOPE) where SCOPE = GLOBAL {&EG(symbol_table)}


/*
 * TODO: what about literals
 * read_value
 */


read_rvalue (string ZVP, string NAME, attrs VAR)
   where scope == LOCAL
   where VAR.st_entry_not_required
   where VAR.is_uninitialized
{
  zval* $ZVP = EG (uninitialized_zval_ptr);
}

read_rvalue (string ZVP, string NAME, attrs VAR)
   where scope == LOCAL
   where VAR.st_entry_not_required
   where VAR.is_initialized
{
  zval* $ZVP = local_$NAME;
}

read_rvalue (string ZVP, string NAME, attrs VAR)
   where scope == LOCAL
   where VAR.st_entry_not_required
{
  zval* $ZVP;
  if (local_$NAME == NULL)
    $ZVP = EG (uninitialized_zval_ptr);
  else
    $ZVP = local_$NAME;
}

read_rvalue (string ZVP, string NAME, attrs VAR)
{
  zval* $ZVP = read_var (\scope(LOCAL), "$NAME", ${NAME.length} + 1, ${NAME.hash} TSRMLS_CC);
}


/*
 * write_var
 */
write_var (string L, string R, attrs LHS, attrs RHS)
{
  if ((*$L)->is_ref)
      overwrite_lhs (*$L, $R);
  else
    {
      zval_ptr_dtor ($L);
      \write_var_inner (L, R, RHS);
    }
}

write_var (string L, string R, attrs LHS, attrs RHS)
   where LHS.is_uninitialized
{
  \write_var_inner (L, R, RHS);
}

write_var_inner (string L, string R, attrs RHS)
{
  if ($R->is_ref)
    {
      // Take a copy of RHS for LHS
      *$L = zvp_clone_ex ($R);
    }
  else
    {
      // Share a copy
      $R->refcount++;
      *$L = $R;
    }
}

write_var_inner (string L, string R, attrs RHS)
   where RHS.is_uninitialized == true
{
  // Share a copy
  $R->refcount++;
  *$L = $R;
}


