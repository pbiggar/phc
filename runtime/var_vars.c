/*
 * Lookup variable whose name is var_var in st. We do not call
 * ht_find because ht_find uses zend_symtable_find to search for strings
 * rather than zend_hash_find. The difference is that zend_symtable_find
 * will convert strings to integers where possible: arrays are always
 * integer-indexed if at all possible. Variable names however should
 * _always_ be treated as strings.
 * 
 */

/*
 * If the parameter is a string, returns the parameter, with the refcount
 * incremented. If its not a string, returns a new zval, with a refcount of
 * 1. Either way, zval_dtor_ptr must be run by the caller on the return
 * value.
 */
zval*
get_string_val (zval* zvp)
{
  if (Z_TYPE_P (zvp) == IS_STRING)
    {
      Z_ADDREF_P(zvp);
      return zvp;
    }
  else
    {
      zval* clone = zvp_clone_ex (zvp);
      convert_to_string (clone);
      return clone;
    }
}

zval **
get_var_var (HashTable * st, zval * index TSRMLS_DC)
{
  zval* str_index = get_string_val (index);
  char* name = Z_STRVAL_P (str_index);
  int length = Z_STRLEN_P (str_index) + 1;
  unsigned long hash = zend_get_hash_value (name, length);

  zval** result = get_st_entry (st, name, length, hash TSRMLS_CC);
  zval_ptr_dtor (&str_index);
  return result;
}

/* 
 * Read the variable described by var_var from symbol table st
 * See comments for get_var_var
 */
zval *
read_var_var (HashTable * st, zval * index TSRMLS_DC)
{
  zval* str_index = get_string_val (index);
  char* name = Z_STRVAL_P (str_index);
  int length = Z_STRLEN_P (str_index) + 1;
  unsigned long hash = zend_get_hash_value (name, length);

  zval* result = read_var (st, name, length, hash TSRMLS_CC);
  zval_ptr_dtor (&str_index);
  return result;
}
