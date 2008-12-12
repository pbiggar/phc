
static int
check_unset_index_type (zval * ind TSRMLS_DC)
{
  if (Z_TYPE_P (ind) == IS_OBJECT || Z_TYPE_P (ind) == IS_ARRAY)
    {
      php_error_docref (NULL TSRMLS_CC, E_WARNING,
			"Illegal offset type in unset");
      return 0;
    }

  return 1;
}



/*
 * unset
 */

static void
unset_var (HashTable * st, char *name, int length)
{
  zend_hash_del (st, name, length);
}

static void
unset_array (zval ** p_var, zval * ind TSRMLS_DC)
{
  // NO error required
  if (Z_TYPE_PP (p_var) != IS_ARRAY)
    {
      if (Z_TYPE_PP (p_var) == IS_STRING)
	{
	  php_error_docref (NULL TSRMLS_CC, E_ERROR,
			    "Cannot unset string offsets");
	}
      else if (Z_TYPE_PP (p_var) != IS_NULL)
	{
	  php_error_docref (NULL TSRMLS_CC, E_WARNING,
			    "Cannot unset offsets in a non-array variable");
	}

      return;
    }

  // if its not an array, make it an array
  HashTable *ht = Z_ARRVAL_P (*p_var);

  ht_delete (ht, ind);
}
