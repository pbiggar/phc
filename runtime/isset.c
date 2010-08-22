
/*
 * isset
 */
static int
isset_var (HashTable * st, char *name, int length)
{
  return zend_hash_exists (st, name, length);
}

static int
isset_array (zval ** p_var, zval * ind)
{
  if (Z_TYPE_P (*p_var) == IS_STRING)
    {
      ind = zvp_clone_ex (ind);
      convert_to_long (ind);
      int result = (Z_LVAL_P (ind) >= 0
		    && Z_LVAL_P (ind) < Z_STRLEN_PP (p_var));
      assert (Z_REFCOUNT_P(ind) == 1);
      zval_ptr_dtor (&ind);
      return result;
    }

  // NO error required; return false
  if (Z_TYPE_P (*p_var) != IS_ARRAY)
    return 0;

  // if its not an array, make it an array
  HashTable *ht = Z_ARRVAL_P (*p_var);

  zval **data;
  if (ht_find (ht, ind, &data) == SUCCESS)
    {
      return !ZVAL_IS_NULL (*data);
    }
  else
    return 0;
}
