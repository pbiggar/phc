static void
phc_builtin_eval (zval * arg, zval *result TSRMLS_DC)
{
  // If the user wrote "return ..", we need to store the
  // return value; however, in that case, zend_eval_string
  // will slap an extra "return" onto the front of the string,
  // so we must remove the "return" from the string the user
  // wrote. If the user did not write "return", he is not
  // interested in the return value, and we must pass NULL
  // instead or rhs to avoid zend_eval_string adding "return".

  // convert to a string
  // TODO avoid allocation
  zval *copy = arg;
  zvp_clone_ex (&copy);
  convert_to_string (copy);

  if (result && !strncmp (Z_STRVAL_P (copy), "return ", 7))
    {
      zend_eval_string (Z_STRVAL_P (copy) + 7, result,
			"eval'd code" TSRMLS_CC);
    }
  else
    {
      zend_eval_string (Z_STRVAL_P (copy), NULL, "eval'd code" TSRMLS_CC);
    }

  // cleanup
  assert (copy->refcount == 1);
  zval_ptr_dtor (&copy);
}

static void
phc_builtin_exit (zval * arg, zval* result TSRMLS_DC)
{
  if (Z_TYPE_P (arg) == IS_LONG)
    EG (exit_status) = Z_LVAL_P (arg);
  else
    zend_print_variable (arg);

  zend_bailout ();
}

static void
phc_builtin_die (zval * arg, zval* result TSRMLS_DC)
{
  phc_builtin_exit (arg, result TSRMLS_CC);
}

static void
phc_builtin_echo (zval* arg, zval* result TSRMLS_DC)
{
  zend_print_variable (arg);
}

static void
phc_builtin_print (zval* arg, zval* result TSRMLS_DC)
{
  phc_builtin_echo (arg, result TSRMLS_CC);

  if (result)
    ZVAL_LONG (result, 1);
}

// TODO is there a memory leak here is result has a value?
static void
phc_builtin_empty (zval* arg, zval* result TSRMLS_DC)
{
//   return (not_in_symbol_table || is_false (value))
  ZVAL_BOOL (result, !zend_is_true);
}
