static long
get_integer_index (zval * ind TSRMLS_DC)
{
  long index;
  switch (Z_TYPE_P (ind))
    {
    case IS_DOUBLE:
      return (long) Z_DVAL_P (ind);

    case IS_LONG:
    case IS_BOOL:
      return Z_LVAL_P (ind);

    case IS_NULL:
      return 0;

    default:
      php_error_docref (NULL TSRMLS_CC, E_WARNING, "Illegal offset type");
    }
}

static zval *
read_string_index (zval * var, zval * ind TSRMLS_DC)
{
  // This must always allocate memory, since we cant return the
  // passed string.
  assert (Z_TYPE_P (var) == IS_STRING);
  long index = get_integer_index (ind TSRMLS_CC);

  zval *result;
  ALLOC_INIT_ZVAL (result);

  if (index >= Z_STRLEN_P (var) || index < 0)
    {
      // this is 1 byte long, must be copied
      ZVAL_STRINGL (result, "", 0, 1);
    }
  else
    {
      char *string = Z_STRVAL_P (var);
      ZVAL_STRINGL (result, &string[index], 1, 1);
    }

  return result;
}

/* Given a string (p_lhs), write into it for $x[i] = $y; */
void
write_string_index (zval ** p_lhs, zval * ind, zval * rhs TSRMLS_DC)
{
  assert (Z_TYPE_P (*p_lhs) == IS_STRING);

  long index = get_integer_index (ind TSRMLS_CC);

  // Get the appropriate character
  char new_char;
  if (Z_TYPE_P (rhs) != IS_STRING)
    {
      // TODO: remove allocate
      zval *copy = zvp_clone_ex (rhs);
      convert_to_string (copy);
      new_char = Z_STRVAL_P (copy)[0];
      zval_ptr_dtor (&copy);
    }
  else
    {
      new_char = Z_STRVAL_P (rhs)[0];
    }

  // Bounds check
  if (index < 0)
    {
      php_error_docref (NULL TSRMLS_CC, E_WARNING,
			"Illegal string offset:  %ld", index);
      return;
    }

  // We overwrite if it's change-on-write
  sep_copy_on_write (p_lhs);

  if (index > Z_STRLEN_PP (p_lhs))
    {
      // Extend to fix new
      int len = Z_STRLEN_PP (p_lhs);
      int new_length = index + 1;	// space for the new character
      Z_STRVAL_PP (p_lhs) = erealloc (Z_STRVAL_PP (p_lhs), new_length + 1);

      // pad with ' '
      memset (&Z_STRVAL_PP (p_lhs)[len], ' ', index - len);

      // change the strlen
      Z_STRLEN_PP (p_lhs) = new_length;

      // add a null terminator
      Z_STRVAL_PP (p_lhs)[new_length] = '\0';
    }

  // write in the first character of the new value
  Z_STRVAL_PP (p_lhs)[index] = new_char;


  // index < 0: E_WARNING illegal string offset
}
