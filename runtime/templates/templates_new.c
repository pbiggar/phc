/* Quick intro, using this macro as an example:
 *
 * assign_expr_var (token LHS, token RHS)
 *    where LHS.st_entry_not_required
 *    where LHS.is_uninitialized
 * @@@
 *   zval** p_lhs = &local_$LHS;
 *   \read_rvalue ("rhs", RHS);
 *   \write_var ("p_lhs", "rhs", LHS, RHS);
 * @@@
 *
 * Macros are defined by their name, a list of argument, a list of rules, and a
 * body. Generate_C will attempt to 'instantiate' a macro with its name and
 * some arguments. Each macro of that name will be matched against in the order
 * it appears. When all of pattern's rules match the parameters, that macro
 * will be evaluated. If no macro matches, an error is given.
 *
 * Matching:
 *    Before we look at the rules, we need to look at the signature. The
 *    signature is a list of parameters, in capital letters (LHS and RHS), and
 *    types (token in both cases).
 *
 *    A rule is a line starting with 'where', and followed by a boolean expression. There are only two kinds of boolean expr:
 *	    Lookup:
 *	      Parameters which are 'node's (i.e. correspond to an MIR::Node*) can
 *	      have their attrs looked up. If they do not have the attribute, or
 *	      they have a Boolean false stored, the lookup fails.  Otherwise it
 *	      succeeds.
 *
 *	    Equals:
 *	      In the form 'LHS == RHS' - this does a string comparison between the
 *	      parameters, where they are coerced to strings. Coersions will be
 *	      explained in the type section later.
 *
 *	      The operands of an Equals are expressions: Parameters, strings, calls
 *	      to other macros or callbacks. Macro calls and callbacks are explained
 *	      later.
 *
 * Types:
 *    There are only 3 types, whose name must be used in a type signature:
 *       node: Can have attributes lookup up. Evaluating it is a evaluation-time error.
 *
 *       string: Represents a String* (or a quoted string when created in 'user code').
 *
 *	 token: A token is an MIR::Identifier*. Attributes can be looked up, or
 *	 it can be evaluated itself, which coerces it to its 'value' string.
 *	 Tokens can be used as either strings or nodes.
 *
 *    Evaluating a lookup can also produce a boolean, but these are always
 *    coerced to either "TRUE" or "FALSE".
 *
 *
 * Bodies:
 *    The body is simply a C string, interspersed with interpolations, macro
 *    calls and callbacks. It starts and ends with @@@. The evalutation of a
 *    macro is simply a string of its contents, with appropriate strings
 *    substituted in for interpolations etc.  Whitespace is preserved.
 *
 *    Bodies allow two kinds of interpolations:
 *      $LHS: coerces LHS into a string (which works for tokens and strings,
 *      and leads to evalutation-time error for nodes).
 *
 *       ${LHS.attr_name}: the same as a lookup.
 *
 * Macro calls:
 *    Rules and bodies both support macro calls. In the example above,
 *    \read_value (...) is  macro call. Parameters can be nodes, tokens, or
 *    strings. Strings are written as quoted strings: "rhs". Nodes and tokens
 *    must, of course, be passed using their name in the caller.
 *
 * Callbacks:
 *    Callbacks are the same as macros, except they call a c++ function, which
 *    must be registed in Generate_C. They are called using:
*     \cb:call_back_name (PARAM). For now, only 1 parameter is allowed, but its
*     easy to fix that.
 *
 * Comments:
 *    C or C++ comments, are allowed outside bodies. Comments inside bodies and
 *    will appear in the generated code.
 *
 *  Note: I may be wrong about some of the evaluation-time errors for node
 *  coersions. If you see some stray "TRUE"s in your code, this may be the
 *  problem.
 *
 * TODO: we use ZEND_FETCH_CLASS_DEFAULT to get class definitions for static
 * methods and attributes. Not sure that is correct.
 *
 * TODO: we might be able to cache zend_class_entry info for static vars,
 * calls to "new", etc.
 */

/*
 * Simple assignments
 * $x = $y;
 */

assign_expr_var (token LHS, node RHS)
   where LHS.st_entry_not_required
   where LHS.is_uninitialized
@@@
  zval** p_lhs = &local_$LHS;
  \read_rvalue ("rhs", RHS);
  \write_var ("p_lhs", "rhs", LHS, RHS);
@@@

assign_expr_var (token LHS, node RHS)
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
 * Pre-op
 */
pre_op (token VAR, string OP_FN)
@@@
   \get_st_entry ("LOCAL", "p_var", VAR);
   sep_copy_on_write (p_var);
   $OP_FN (*p_var);
@@@

/*
 * Return
 */

return (token RETVAL, node RET)
   where RET.return_by_ref
@@@
   \get_st_entry ("LOCAL", "p_rhs", RETVAL);
   sep_copy_on_write (p_rhs);
   zval_ptr_dtor (return_value_ptr);
   Z_SET_ISREF_P(*p_rhs);
   Z_ADDREF_P((*p_rhs));
   *return_value_ptr = *p_rhs;
   goto end_of_function;
@@@

// Return-by-value
return (node RETVAL, node RET)
@@@
   \read_rvalue ("rhs", RETVAL)
   // Run-time return by reference has different semantics to compile-time.
   // If the function has CTRBR and RTRBR, the the assignment will be
   // reference. If one or the other is return-by-copy, the result will be
   // by copy. Its a question of whether its separated at return-time (which
   // we do here) or at the call-site.
   return_value->value = rhs->value;
   return_value->type = rhs->type;
   zval_copy_ctor (return_value);
   goto end_of_function;
@@@


/*
 * Branch
 */
branch (token COND, string TRUE_TARGET, string FALSE_TARGET)
@@@
   \read_rvalue ("p_cond", COND);
   zend_bool bcond = zend_is_true (p_cond);
   if (bcond)
      goto $TRUE_TARGET;
   else
      goto $FALSE_TARGET;
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
  \get_var_var ("LOCAL", "p_rhs", "index");
  sep_copy_on_write (p_rhs);
  copy_into_ref (p_lhs, p_rhs);
@@@

/*
 * Array access
 */
assign_expr_array_access (token LHS, node ARRAY, node INDEX)
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

assign_expr_ref_array_access (token LHS, token ARRAY, node INDEX)
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
   if (\is_ref ("*p_lhs", LHS))
   {
      zval* constant;
      get_constant ("$CONSTANT", \cb:length(CONSTANT), &constant TSRMLS_CC);
      overwrite_lhs_no_copy (*p_lhs, constant);
      safe_free_zval_ptr (constant);
   }
   else
   {
      zval_ptr_dtor (p_lhs);
      get_constant ("$CONSTANT", \cb:length(CONSTANT), p_lhs TSRMLS_CC);
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
   where VAR.is_initialized
@@@
  zval** $ZVP = &local_$VAR;
@@@

get_st_entry (string SCOPE, string ZVP, token VAR)
   where SCOPE == "LOCAL"
   where VAR.st_entry_not_required
   where VAR.is_uninitialized
@@@
  local_$VAR = EG (uninitialized_zval_ptr);
  local_$VAR->refcount++;
  zval** $ZVP = &local_$VAR;
@@@

get_st_entry (string SCOPE, string ZVP, token VAR)
   where SCOPE == "LOCAL"
   where VAR.st_entry_not_required
@@@
  if (local_$VAR == NULL)
    {
      local_$VAR = EG (uninitialized_zval_ptr);
      Z_ADDREF_P(local_$VAR);
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
 * Assign from Literal - it seems like we could use assign_expr_var, and
 * rvalue, but we always want a new value for LHS, and read_rvalue generates a
 * zval, not a zval* (except when optimized, but we cant guarantee that).
 */
assign_expr_literal (token LHS, node LIT)
   where LIT.pool_name
@@@
   \assign_expr_var (LHS, LIT);
@@@

assign_expr_literal (token LHS, node LIT)
@@@
   \new_lhs (LHS, "value");
   \cb:write_literal_directly_into_zval ("value", LIT);
@@@


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
  zval lit_tmp_$ZVP;
  INIT_ZVAL (lit_tmp_$ZVP);
  zval* $ZVP = &lit_tmp_$ZVP;
  \cb:write_literal_directly_into_zval (ZVP, LIT);
@@@

// Not for literals (not that the signature changes here -- that's intentional
// -- the rules are checked before the signature is)
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

star (string VAR) @@@ (*$VAR) @@@

// Do IS_UNINITIALIZED before CANNOT_BE_REF, or else we'll have a segfault
// from the zval_ptr_dtor.
write_var (string LHS, string RHS, node TLHS, node TRHS)
   where TLHS.is_uninitialized
@@@
   \write_var_inner (LHS, RHS, TLHS, TRHS);
@@@

write_var (string LHS, string RHS, node TLHS, node TRHS)
@@@
  // Would be better with string interpolation, but what can you do.
  if (\is_ref (\star (LHS), TLHS))
      overwrite_lhs (*$LHS, $RHS);
  else
    {
      zval_ptr_dtor ($LHS);
      \write_var_inner (LHS, RHS, TLHS, TRHS);
    }
@@@

write_var_inner (string LHS, string RHS, node TLHS, node TRHS)
@@@
  if (\is_ref (RHS, TRHS))
    {
      // Take a copy of RHS for LHS
      *$LHS = zvp_clone_ex ($RHS);
    }
  else
    {
      // Share a copy
      Z_ADDREF_P($RHS);
      *$LHS = $RHS;
    }
@@@

/*
 * Var-vars
 */

read_var_var (string ZVP, string INDEX)
@@@
   $ZVP = read_var_var (\scope("LOCAL"), $INDEX TSRMLS_CC);
@@@

get_var_var (string ST, string ZVP, string INDEX)
@@@
   zval** $ZVP = get_var_var (\scope(ST), $INDEX TSRMLS_CC);
@@@

assign_var_var (token INDEX, node RHS)
@@@
   \read_rvalue ("index", INDEX);
   \get_var_var ("LOCAL", "p_lhs", "index");
   \read_rvalue ("rhs", RHS);
   if (*p_lhs != rhs)
   {
      // TODO: we dont have node for p_lhs to call \write_var
      write_var (p_lhs, rhs);
   }
@@@

assign_var_var_ref (token INDEX, node RHS)
@@@
   \read_rvalue ("index", INDEX);
   \get_var_var ("LOCAL", "p_lhs", "index");
   \get_st_entry ("LOCAL", "p_rhs", RHS);
   sep_copy_on_write (p_rhs);
   copy_into_ref (p_lhs, p_rhs);
@@@

/*
 * Assign_next
 * TODO: These are are more than a bit of a mess.
 */
assign_next (token LHS, node RHS)
@@@
   \get_st_entry ("LOCAL", "p_array", LHS);
   // Push EG(uninit) and get a pointer to the symtable entry
   zval** p_lhs = push_and_index_ht (p_array TSRMLS_CC);
   if (p_lhs != NULL)
   {
      \read_rvalue ("rhs", RHS);
      if (*p_lhs != rhs)
	 write_var (p_lhs, rhs);
   }
   // I think if this is NULL, then the LHS is a bool or similar, and you cant
   // push onto it.
@@@

assign_next_ref (token LHS, token RHS)
@@@
   \get_st_entry ("LOCAL", "p_array", LHS);
   // Push EG(uninit) and get a pointer to the symtable entry
   zval** p_lhs = push_and_index_ht (p_array TSRMLS_CC);
   if (p_lhs != NULL)
   {
      // TODO: this is wrong (further note, not sure why, I wrote that ages ago - pb)
      \get_st_entry ("LOCAL", "p_rhs", RHS);
      sep_copy_on_write (p_rhs);
      copy_into_ref (p_lhs, p_rhs);
   }
@@@


/*
 * Assign_array
 */

assign_array (token ARRAY, node INDEX, node RHS)
@@@
   \get_st_entry ("LOCAL", "p_array", ARRAY);
   check_array_type (p_array TSRMLS_CC);

   \read_rvalue ("index", INDEX);

   // String indexing
   if (Z_TYPE_PP (p_array) == IS_STRING && Z_STRLEN_PP (p_array) > 0)
   {
      \read_rvalue ("rhs", RHS);
      write_string_index (p_array, index, rhs TSRMLS_CC);
   }
   else if (Z_TYPE_PP (p_array) == IS_ARRAY)
   {
      zval** p_lhs = get_ht_entry (p_array, index TSRMLS_CC);
      \read_rvalue ("rhs", RHS);
      if (*p_lhs != rhs)
      {
	 write_var (p_lhs, rhs);
      }
   }
@@@

assign_array_ref (token ARRAY, node INDEX, token RHS)
@@@
   \get_st_entry ("LOCAL", "p_array", ARRAY);
   check_array_type (p_array TSRMLS_CC);

   \read_rvalue ("index", INDEX);

   // String indexing
   if (Z_TYPE_PP (p_array) == IS_STRING && Z_STRLEN_PP (p_array) > 0)
   {
      php_error_docref (NULL TSRMLS_CC, E_ERROR,
		       "Cannot create references to/from string offsets nor overloaded objects");
   }
   else if (Z_TYPE_PP (p_array) == IS_ARRAY)
   {
      zval** p_lhs = get_ht_entry (p_array, index TSRMLS_CC);
      \get_st_entry ("LOCAL", "p_rhs", RHS);
      sep_copy_on_write (p_rhs);
      copy_into_ref (p_lhs, p_rhs);
   }
@@@

/*
 * Globals
 */
global_var (token VAR)
@@@
   \get_st_entry ("LOCAL", "p_local", VAR);
   \get_st_entry ("GLOBAL", "p_global", VAR);
   sep_copy_on_write (p_global);
   copy_into_ref (p_local, p_global);
@@@

global_var_var (token INDEX)
@@@
   \read_rvalue ("index", INDEX);
   \get_var_var ("LOCAL", "p_local", "index");
   \get_var_var ("GLOBAL", "p_global", "index");
   sep_copy_on_write (p_global);
   copy_into_ref (p_local, p_global);
@@@

/*
 * Builtins
 */

builtin_with_lhs (token LHS, node ARG, string NAME, string FILENAME)
@@@
   \read_rvalue ("arg", ARG);

   \get_st_entry ("LOCAL", "p_lhs", LHS);
   zval* rhs;
   ALLOC_INIT_ZVAL (rhs);
   phc_builtin_$NAME (arg, &rhs, "$FILENAME" TSRMLS_CC);
   write_var (p_lhs, rhs);
   zval_ptr_dtor (&rhs);
@@@


builtin_no_lhs (node ARG, string NAME, string FILENAME)
@@@
   \read_rvalue ("arg", ARG);

   zval* rhs = NULL;
   phc_builtin_$NAME (arg, &rhs, "$FILENAME" TSRMLS_CC);
   if (rhs != NULL) zval_ptr_dtor (&rhs);
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

assign_expr_foreach_has_key (token LHS, token ARRAY, string ITERATOR)
@@@
   \new_lhs (LHS, "value");
   \read_rvalue ("fe_array", ARRAY);
   int type = zend_hash_get_current_key_type_ex (fe_array->value.ht, &$ITERATOR);
   ZVAL_BOOL (value, type != HASH_KEY_NON_EXISTANT);
@@@

assign_expr_foreach_get_key (token LHS, token ARRAY, string ITERATOR)
@@@
   \new_lhs (LHS, "value");
   \read_rvalue ("fe_array", ARRAY);

   char* str_index = NULL;
   uint str_length;
   ulong num_index;

   int result = zend_hash_get_current_key_ex (fe_array->value.ht, &str_index,
					      &str_length, &num_index, 0,
					      &$ITERATOR);
   if (result == HASH_KEY_IS_LONG)
   {
      ZVAL_LONG (value, num_index);
   }
   else
   {
      ZVAL_STRINGL (value, str_index, str_length - 1, 1);
   }
@@@

foreach_reset (token ARRAY, string ITERATOR)
@@@
   \read_rvalue ("fe_array", ARRAY);
   zend_hash_internal_pointer_reset_ex (fe_array->value.ht, &$ITERATOR);
@@@

foreach_next (token ARRAY, string ITERATOR)
@@@
   \read_rvalue ("fe_array", ARRAY);
   int result = zend_hash_move_forward_ex (fe_array->value.ht, &$ITERATOR);
   assert (result == SUCCESS);
@@@

foreach_end (token ARRAY, string ITERATOR)
@@@
   \read_rvalue ("fe_array", ARRAY);
   zend_hash_internal_pointer_end_ex (fe_array->value.ht, &$ITERATOR);
@@@

/*
 * Assign_field 
 *
 */

assign_field (token OBJ, token FIELD, node RHS)
@@@
	\get_st_entry ("LOCAL", "p_obj", OBJ);
	\read_rvalue ("rhs", RHS);
	\make_field_name ("field_name", FIELD);
	Z_OBJ_HT_PP(p_obj)->write_property(*p_obj, &field_name, rhs TSRMLS_CC);
@@@

assign_field_ref (token OBJ, token FIELD, node RHS)
@@@
	\get_st_entry ("LOCAL", "p_obj", OBJ);
	\get_st_entry ("LOCAL", "p_rhs", RHS);
	\make_field_name ("field_name", FIELD);
	zval** p_lhs;
	p_lhs = Z_OBJ_HT_PP(p_obj)->get_property_ptr_ptr(*p_obj, &field_name TSRMLS_CC);
	sep_copy_on_write (p_rhs);
	copy_into_ref (p_lhs, p_rhs);
@@@

assign_static_field (token CLASS, token FIELD, node RHS)
@@@
	\read_rvalue ("rhs", RHS);
	zend_class_entry* ce;
	ce = zend_fetch_class ("$CLASS", strlen("$CLASS"), ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);
	zend_update_static_property(ce, "$FIELD", strlen("$FIELD"), rhs TSRMLS_CC); 
@@@

assign_static_field_ref (token CLASS, token FIELD, node RHS)
@@@
	\get_st_entry ("LOCAL", "p_rhs", RHS);
	zend_class_entry* ce;
	ce = zend_fetch_class ("$CLASS", strlen("$CLASS"), ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);
	zval** p_lhs;
	p_lhs = zend_std_get_static_property(ce, "$FIELD", strlen("$FIELD"), 0 TSRMLS_CC);
	sep_copy_on_write (p_rhs);
	copy_into_ref (p_lhs, p_rhs);
@@@

assign_var_field (token OBJ, token VAR_FIELD, node RHS)
@@@
	\get_st_entry ("LOCAL", "p_obj", OBJ);
	\read_rvalue ("field_name", VAR_FIELD);
	\read_rvalue ("rhs", RHS);
	Z_OBJ_HT_PP(p_obj)->write_property(*p_obj, field_name, rhs TSRMLS_CC);
@@@

assign_var_field_ref (token OBJ, token VAR_FIELD, node RHS)
@@@
	\get_st_entry ("LOCAL", "p_obj", OBJ);
	\read_rvalue ("field_name", VAR_FIELD);
	\get_st_entry ("LOCAL", "p_rhs", RHS);
	zval** p_lhs;
	p_lhs = Z_OBJ_HT_PP(p_obj)->get_property_ptr_ptr(*p_obj, field_name TSRMLS_CC);
	sep_copy_on_write (p_rhs);
	copy_into_ref (p_lhs, p_rhs);
@@@

assign_var_static_field (token CLASS, token VAR_FIELD, node RHS)
@@@
	\read_rvalue ("field_name", VAR_FIELD);
	zval* field_name_str = get_string_val (field_name);
	\read_rvalue ("rhs", RHS);
	zend_class_entry* ce;
	ce = zend_fetch_class ("$CLASS", strlen("$CLASS"), ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);
	zend_update_static_property(ce, Z_STRVAL_P(field_name_str), Z_STRLEN_P(field_name_str), rhs TSRMLS_CC); 
	zval_ptr_dtor(&field_name_str);
@@@

assign_var_static_field_ref (token CLASS, token VAR_FIELD, node RHS)
@@@
	\read_rvalue ("field_name", VAR_FIELD);
	zval* field_name_str = get_string_val (field_name);
	\get_st_entry ("LOCAL", "p_rhs", RHS);
	zend_class_entry* ce;
	ce = zend_fetch_class ("$CLASS", strlen("$CLASS"), ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);
	zval** p_lhs;
	p_lhs = zend_std_get_static_property(ce, Z_STRVAL_P(field_name_str), Z_STRLEN_P(field_name_str), 0 TSRMLS_CC);
	sep_copy_on_write (p_rhs);
	copy_into_ref (p_lhs, p_rhs);
	zval_ptr_dtor(&field_name_str);
@@@

/*
 * Field_access
 */

// TODO: we use the C function write_var rather than the write_var macro,
// which is not general enough to handle this case 
field_access (token LHS, token OBJ, token FIELD)
@@@
	\get_st_entry ("LOCAL", "p_obj", OBJ);
	\make_field_name ("field_name", FIELD);
	// I *think* this is correct, but documentation of the Zend API is scarce :)
	zval* field = Z_OBJ_HT_PP(p_obj)->read_property(*p_obj, &field_name, BP_VAR_R TSRMLS_CC);
	\get_st_entry ("LOCAL", "p_lhs", LHS);
	write_var (p_lhs, field); 
@@@

field_access_ref (token LHS, token OBJ, token FIELD)
@@@
	\get_st_entry ("LOCAL", "p_obj", OBJ);
	\make_field_name ("field_name", FIELD);
	zval** field = Z_OBJ_HT_PP(p_obj)->get_property_ptr_ptr(*p_obj, &field_name TSRMLS_CC);
	sep_copy_on_write (field);
	\get_st_entry ("LOCAL", "p_lhs", LHS);
	copy_into_ref (p_lhs, field);
@@@

static_field_access (token LHS, token CLASS, token FIELD)
@@@
	zend_class_entry* ce;
	ce = zend_fetch_class ("$CLASS", strlen("$CLASS"), ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);
	zval* field = zend_read_static_property(ce, "$FIELD", strlen("$FIELD"), 0 TSRMLS_CC);
	\get_st_entry ("LOCAL", "p_lhs", LHS);
	write_var (p_lhs, field); 
@@@

static_field_access_ref (token LHS, token CLASS, token FIELD)
@@@
	zend_class_entry* ce;
	ce = zend_fetch_class ("$CLASS", strlen("$CLASS"), ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);
	zval** field = zend_std_get_static_property(ce, "$FIELD", strlen("$FIELD"), 0 TSRMLS_CC);
	sep_copy_on_write (field);
	\get_st_entry ("LOCAL", "p_lhs", LHS);
	copy_into_ref (p_lhs, field); 
@@@

var_field_access (token LHS, token OBJ, token VAR_FIELD)
@@@
	\get_st_entry ("LOCAL", "p_obj", OBJ);
	\read_rvalue ("field_name", VAR_FIELD);
	// I *think* this is correct, but documentation of the Zend API is scarce :)
	zval* field = Z_OBJ_HT_PP(p_obj)->read_property(*p_obj, field_name, BP_VAR_R TSRMLS_CC);
	\get_st_entry ("LOCAL", "p_lhs", LHS);
	write_var (p_lhs, field); 
@@@

var_field_access_ref (token LHS, token OBJ, token VAR_FIELD)
@@@
	\get_st_entry ("LOCAL", "p_obj", OBJ);
	\read_rvalue ("field_name", VAR_FIELD);
	zval** field = Z_OBJ_HT_PP(p_obj)->get_property_ptr_ptr(*p_obj, field_name TSRMLS_CC);
	sep_copy_on_write (field);
	\get_st_entry ("LOCAL", "p_lhs", LHS);
	copy_into_ref (p_lhs, field);
@@@

var_static_field_access (token LHS, token CLASS, token VAR_FIELD)
@@@
	\read_rvalue ("field_name", VAR_FIELD);
	zval* field_name_str = get_string_val (field_name);
	zend_class_entry* ce;
	ce = zend_fetch_class ("$CLASS", strlen("$CLASS"), ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);
	zval* field = zend_read_static_property(ce, Z_STRVAL_P(field_name_str), Z_STRLEN_P(field_name_str), 0 TSRMLS_CC);
	\get_st_entry ("LOCAL", "p_lhs", LHS);
	write_var (p_lhs, field); 
	zval_ptr_dtor(&field_name_str);
@@@

var_static_field_access_ref (token LHS, token CLASS, token VAR_FIELD)
@@@
	\read_rvalue ("field_name", VAR_FIELD);
	zval* field_name_str = get_string_val (field_name);
	zend_class_entry* ce;
	ce = zend_fetch_class ("$CLASS", strlen("$CLASS"), ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);
	zval** field = zend_std_get_static_property(ce, Z_STRVAL_P(field_name_str), Z_STRLEN_P(field_name_str), 0 TSRMLS_CC);
	sep_copy_on_write (field);
	\get_st_entry ("LOCAL", "p_lhs", LHS);
	copy_into_ref (p_lhs, field); 
	zval_ptr_dtor(&field_name_str);
@@@

// Takes a ZVP, so if passing a ZVPP, make sure to deref.
is_ref (string ZVP, node ATTRS) where ATTRS.cannot_be_ref @@@ 0 @@@
is_ref (string ZVP, node ATTRS) where ATTRS.pool_name @@@ 0 @@@
is_ref (string ZVP, node ATTRS) where \cb:is_literal (ATTRS) == "TRUE" @@@ 0 @@@
is_ref (string ZVP, node ATTRS) where ATTRS.is_uninitialized @@@ 0 @@@
is_ref (string ZVP, node ATTRS) @@@ Z_ISREF_P($ZVP) @@@

/*
 * Object creation
 */

assign_expr_new (token LHS, token CLASS)
@@@
	\new_lhs (LHS, "lhs");
	zend_class_entry* ce;
	ce = zend_fetch_class ("$CLASS", strlen("$CLASS"), ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);
	object_init_ex(lhs, ce); 
@@@

assign_expr_new_ref (token LHS, token CLASS)
@@@
  \get_st_entry ("LOCAL", "p_lhs", LHS);
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
	zend_class_entry* ce;
	ce = zend_fetch_class ("$CLASS", strlen("$CLASS"), ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);
	object_init_ex(*p_lhs, ce); 
@@@

assign_expr_var_new (token LHS, token VAR_CLASS)
@@@
	\read_rvalue("class_name", VAR_CLASS);
	zval* class_name_str = get_string_val (class_name);
	\new_lhs (LHS, "lhs");
	zend_class_entry* ce;
	ce = zend_fetch_class (Z_STRVAL_P(class_name_str), Z_STRLEN_P(class_name_str), ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);
	object_init_ex(lhs, ce); 
	zval_ptr_dtor(&class_name_str);
@@@

assign_expr_var_new_ref (token LHS, token VAR_CLASS)
@@@
	\read_rvalue("class_name", VAR_CLASS);
	zval* class_name_str = get_string_val (class_name);
  \get_st_entry ("LOCAL", "p_lhs", LHS);
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
	zend_class_entry* ce;
	ce = zend_fetch_class (Z_STRVAL_P(class_name_str), Z_STRLEN_P(class_name_str), ZEND_FETCH_CLASS_DEFAULT TSRMLS_CC);
	object_init_ex(*p_lhs, ce); 
	zval_ptr_dtor(&class_name_str);
@@@

/*
 * Lots of macros need to fetch the LHS, initialize/separate it, and add a
 * value. In Generate_C, this used to be Pattern_assign_var, but now they just
 * call this macro.
 */
new_lhs (token LHS, string VAL)
@@@
   \get_st_entry ("LOCAL", "p_lhs", LHS);
   zval* $VAL;
   if (\is_ref ("*p_lhs", LHS))
   {
     // Always overwrite the current value
     $VAL = *p_lhs;
     zval_dtor ($VAL);
   }
   else
   {
     ALLOC_INIT_ZVAL ($VAL);
     zval_ptr_dtor (p_lhs);
     *p_lhs = $VAL;
   }
@@@

/*
 * Method and function calls
 */

// If we know param_*_by_ref, then we don't need these results.
arg_by_ref (node ARG) where ARG.param_by_ref @@@ @@@
arg_by_ref (node ARG) where ARG.param_not_by_ref @@@ @@@

// This is taken into account for param*_by_ref, but we need it for the unoptimized case.
arg_by_ref (node ARG)
   where ARG.is_ref
@@@
   by_ref[abr_index] = 1;
   abr_index++;
@@@



arg_by_ref (node ARG)
@@@
   if (arg_info)
   {
      by_ref[abr_index] = arg_info->pass_by_reference;
      arg_info++;
   }
   else
      by_ref[abr_index] = signature->common.pass_rest_by_reference;

   abr_index++;
@@@

arg_fetch (node ARG)
   where ARG.param_not_by_ref
@@@
   destruct[af_index] = 0;
   {
      \read_rvalue ("arg", ARG);
      args[af_index] = fetch_var_arg (arg, &destruct[af_index]);
      args_ind[af_index] = &args[af_index];
   }
   af_index++;
@@@

// Literals cant be passed-by-ref
arg_fetch (node ARG)
   where \cb:is_literal(ARG) == "TRUE"
@@@
  \arg_fetch(ARG#param_not_by_ref)
@@@

arg_fetch (node ARG)
   where ARG.param_by_ref
@@@
   destruct[af_index] = 0;
   {
     \get_st_entry ("LOCAL", "p_arg", ARG);
     args_ind[af_index] = fetch_var_arg_by_ref (p_arg);
     assert (!in_copy_on_write (*args_ind[af_index]));
     args[af_index] = *args_ind[af_index];
   }
   af_index++;
@@@

// For literals, when not optimizing - we cant do get_st_entry on literal.
arg_fetch (node ARG) where ARG.pool_name @@@ \arg_fetch (ARG#param_not_by_ref); @@@

arg_fetch (node ARG)
@@@
   if (by_ref[af_index])
   {
     \arg_fetch (ARG#param_by_ref);
   }
   else
   {
     \arg_fetch (ARG#param_not_by_ref);
   }
@@@

call_function (node ATTRS, string MN, list ARGS, string FILENAME, string LINE, string FCI_NAME, string FCIC_NAME, string ARG_COUNT, string USE_REF, token LHS)
@@@
   zend_function* signature = $FCIC_NAME.function_handler;
   zend_arg_info* arg_info = signature->common.arg_info; // optional

   // Setup array of arguments
   // TODO: i think arrays of size 0 is an error
   int by_ref[$ARG_COUNT];
   int destruct [$ARG_COUNT];
   zval* args [$ARG_COUNT];
   zval** args_ind [$ARG_COUNT];

   int abr_index = 0;
   \arg_by_ref (ARGS);

   int af_index = 0;
   \arg_fetch (ARGS);

   phc_setup_error (1, "$FILENAME", $LINE, NULL TSRMLS_CC);

   // save existing parameters, in case of recursion
   int param_count_save = $FCI_NAME.param_count;
   zval*** params_save = $FCI_NAME.params;
   zval** retval_save = $FCI_NAME.retval_ptr_ptr;

   zval* rhs = NULL;

   // set up params
   $FCI_NAME.params = args_ind;
   $FCI_NAME.param_count = $ARG_COUNT;
   $FCI_NAME.retval_ptr_ptr = &rhs;

   // call the function
   int success = zend_call_function (&$FCI_NAME, &$FCIC_NAME TSRMLS_CC);
   assert(success == SUCCESS);

   // restore params
   $FCI_NAME.params = params_save;
   $FCI_NAME.param_count = param_count_save;
   $FCI_NAME.retval_ptr_ptr = retval_save;

   // unset the errors
   phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);

   int i;
   for (i = 0; i < $ARG_COUNT; i++)
   {
      if (destruct[i])
      {
	 assert (destruct[i]);
	 zval_ptr_dtor (args_ind[i]);
      }
   }

   // When the Zend engine returns by reference, it allocates a zval into
   // retval_ptr_ptr. To return by reference, the callee writes into the
   // retval_ptr_ptr, freeing the allocated value as it does.  (Note, it may
   // not actually return anything). So the zval returned - whether we return
   // it, or it is the allocated zval - has a refcount of 1.
 
   // The caller is responsible for cleaning that up (note, this is unaffected
   // by whether it is added to some COW set).

   // For reasons unknown, the Zend API resets the refcount and is_ref fields
   // of the return value after the function returns (unless the callee is
   // interpreted). If the function is supposed to return by reference, this
   // loses the refcount. This only happens when non-interpreted code is
   // called. We work around it, when compiled code is called, by saving the
   // refcount into SAVED_REFCOUNT, in the return statement. The downside is
   // that we may create an error if our code is called by a callback, and
   // returns by reference, and the callback returns by reference. At least
   // this is an obscure case.
   if(\return_reference_bug(ATTRS))
   {
      assert (rhs != EG(uninitialized_zval_ptr));
      Z_SET_ISREF_P(rhs);
      if (saved_refcount != 0)
      {
	 Z_SET_REFCOUNT_P(rhs, saved_refcount);
      }
      Z_ADDREF_P(rhs);
   }
   saved_refcount = 0; // for 'obscure cases'

   \function_lhs (USE_REF, LHS);

   zval_ptr_dtor (&rhs);
   if(\return_reference_bug(ATTRS))
      zval_ptr_dtor (&rhs);
@@@

// We can tell this at compile-time.
return_reference_bug (node ATTRS) where ATTRS.return_reference_bug @@@ 1 @@@
return_reference_bug (node ATTRS) where ATTRS.no_return_reference_bug @@@ 0 @@@
return_reference_bug (node ATTRS) @@@ signature->common.return_reference && signature->type != ZEND_USER_FUNCTION @@@


function_lhs (string USE_LHS, token LHS) where USE_LHS == "NONE" @@@@@@

function_lhs (string USE_LHS, token LHS)
   where USE_LHS == "REF"
@@@
   \get_st_entry ("LOCAL", "p_lhs", LHS);
   sep_copy_on_write (&rhs);
   copy_into_ref (p_lhs, &rhs);
@@@

function_lhs (string USE_LHS, token LHS)
   where USE_LHS == "NO_REF"
@@@
   \get_st_entry ("LOCAL", "p_lhs", LHS);
   write_var (p_lhs, rhs);
@@@

function_invocation (node ATTRS, string MN, list ARGS, string FILENAME, string LINE, string FCI_NAME, string FCIC_NAME, string ARG_COUNT, string LHS_REF, token LHS)
@@@
   initialize_function_call (&$FCI_NAME, &$FCIC_NAME, "$MN", "$FILENAME", $LINE TSRMLS_CC);
   \call_function (ATTRS, MN, ARGS, FILENAME, LINE, FCI_NAME, FCIC_NAME, ARG_COUNT, LHS_REF, LHS);
@@@


assign_param_is_ref_function (string MN, string FILENAME, string LINE, string FCI_NAME, string FCIC_NAME, string INDEX, token LHS)
@@@
   initialize_function_call (&$FCI_NAME, &$FCIC_NAME, "$MN", "$FILENAME", $LINE TSRMLS_CC);
	\assign_param_is_ref (MN, FILENAME, LINE, FCI_NAME, FCIC_NAME, INDEX, LHS);
@@@

assign_param_is_ref_method (string MN, string FILENAME, string LINE, string INDEX, token TARGET, token LHS)
@@@
   \get_st_entry ("LOCAL", "p_obj", TARGET);
   zend_fcall_info fci_object;
   zend_fcall_info_cache fcic_object = {0, NULL, NULL, NULL};
   initialize_method_call (&fci_object, &fcic_object, p_obj, "$MN", "$FILENAME", $LINE TSRMLS_CC);
	\assign_param_is_ref (MN, FILENAME, LINE, "fci_object", "fcic_object", INDEX, LHS);
@@@

assign_param_is_ref (string MN, string FILENAME, string LINE, string FCI_NAME, string FCIC_NAME, string INDEX, token LHS)
@@@
	zend_function* signature = $FCIC_NAME.function_handler;
	zend_arg_info* arg_info = signature->common.arg_info;
	int count = 0;
	while (arg_info && count < $INDEX)
	{
		count++;
		arg_info++;
	}

	\get_st_entry ("LOCAL", "p_lhs", LHS);
	zval* rhs;
	ALLOC_INIT_ZVAL (rhs);
	if (arg_info && count == $INDEX)
	{
		ZVAL_BOOL (rhs, arg_info->pass_by_reference);
	}
	else
	{
		ZVAL_BOOL (rhs, signature->common.pass_rest_by_reference);
	}
	write_var (p_lhs, rhs);
	zval_ptr_dtor (&rhs);
@@@


method_invocation (node ATTRS, string MN, list ARGS, string FILENAME, string LINE, string ARG_COUNT, node TARGET, string USE_REF, token LHS)
@@@
   \get_st_entry ("LOCAL", "p_obj", TARGET);
   zend_fcall_info fci_object;
   zend_fcall_info_cache fcic_object = {0, NULL, NULL, NULL};
   initialize_method_call (&fci_object, &fcic_object, p_obj, "$MN", "$FILENAME", $LINE TSRMLS_CC);
   \call_function (ATTRS, MN, ARGS, FILENAME, LINE, "fci_object", "fcic_object", ARG_COUNT, USE_REF, LHS);
@@@

constructor_invocation (node ATTRS, list ARGS, string FILENAME, string LINE, string ARG_COUNT, token LHS)
@@@
  \get_st_entry ("LOCAL", "p_obj", LHS);
   zend_fcall_info fci_object;
   zend_fcall_info_cache fcic_object = {0, NULL, NULL, NULL};
   int has_constructor = initialize_constructor_call (&fci_object, &fcic_object, p_obj, "$FILENAME", $LINE TSRMLS_CC);
   // TODO: We pass in __construct to call_function, but in general it may be a
   // a different name (the name of the class, for example).
   // However, \call_function does not actually use this name at all atm.
   if(has_constructor)
   {
     \call_function (ATTRS, "__construct", ARGS, FILENAME, LINE, "fci_object", "fcic_object", ARG_COUNT, "NONE", LHS);
   }
@@@

make_field_name (string VAR_NAME, token FIELD)
@@@
	zval $VAR_NAME;
	INIT_ZVAL ($VAR_NAME);
	ZVAL_STRING (&$VAR_NAME, "$FIELD", 0);
@@@
