/*
 * Lookup variable whose name is var_var in st. We do not call
 * ht_find because ht_find uses zend_symtable_find to search for strings
 * rather than zend_hash_find. The difference is that zend_symtable_find
 * will convert strings to integers where possible: arrays are always
 * integer-indexed if at all possible. Variable names however should
 * _always_ be treated as strings.
 * 
 * If the index is not found and update_st is set the index gets
 * added to the hashtable and a pointer to the new entry is returned;
 * *is_new is set to 1. 
 * Otherwise, the uninitialized zval is returned and is_new is untouched.
 */
zval **
get_var_var (HashTable * st, zval * var_var, int update_st TSRMLS_DC)
{
  zval *string_index;
  int deallocate_string_index = 0;

  if (Z_TYPE_P (var_var) == IS_STRING)
    {
      string_index = var_var;
    }
  else
    {
      MAKE_STD_ZVAL (string_index);
      string_index->value = var_var->value;
      string_index->type = var_var->type;
      zval_copy_ctor (string_index);
      convert_to_string (string_index);
      deallocate_string_index = 1;
    }

  zval **p_result;
  int index_found = zend_hash_find (st, Z_STRVAL_P (string_index),
				    Z_STRLEN_P (string_index) + 1,
				    (void **) &p_result);

  if (index_found != SUCCESS)
    {
      if (!update_st)
	{
	  p_result = &EG (uninitialized_zval_ptr);
	}
      else
	{
	  EG (uninitialized_zval_ptr)->refcount++;
	  zend_hash_update (st, Z_STRVAL_P (string_index),
			    Z_STRLEN_P (string_index) + 1,
			    &EG (uninitialized_zval_ptr), sizeof (zval *),
			    (void **) &p_result);
	}
    }

  if (deallocate_string_index)
    zval_ptr_dtor (&string_index);

  return p_result;
}

/* 
 * Read the variable described by var_var from symbol table st
 * See comments for get_var_var
 */
zval **
read_var_var (HashTable * st, zval * var_var TSRMLS_DC)
{
  return get_var_var (st, var_var, 0 TSRMLS_CC);
}
