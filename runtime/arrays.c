// Extract the hashtable from a hash-valued zval
static HashTable *
extract_ht_ex (zval * arr TSRMLS_DC)
{
  // TODO: this likely should be inlined somewhere.
  assert (!in_copy_on_write (arr));
  if (Z_TYPE_P (arr) == IS_NULL)
    {
      array_init (arr);
    }
  else if (Z_TYPE_P (arr) != IS_ARRAY)
    {
      php_error_docref (NULL TSRMLS_CC, E_WARNING,
			"Cannot use a scalar value as an array");
      array_init (arr);
    }
  return Z_ARRVAL_P (arr);
}


/* P_VAR points into a symbol table, at a variable which we wish to index as a hashtable. */
static HashTable *
extract_ht (zval ** p_var TSRMLS_DC)
{
  sep_copy_on_write (p_var);

  return extract_ht_ex (*p_var TSRMLS_CC);
}

/* Using IND as a key to HT, call the appropriate zend_index_X
 * function with data as a parameter, and return its result. This
 * updates the zval** pointed to by DATA. */
static int
ht_find (HashTable * ht, zval * ind, zval *** data)
{
  int result;
  if (Z_TYPE_P (ind) == IS_LONG || Z_TYPE_P (ind) == IS_BOOL)
    {
      result = zend_hash_index_find (ht, Z_LVAL_P (ind), (void **) data);
    }
  else if (Z_TYPE_P (ind) == IS_DOUBLE)
    {
      result = zend_hash_index_find (ht, (long) Z_DVAL_P (ind),
				     (void **) data);
    }
  else if (Z_TYPE_P (ind) == IS_NULL)
    {
      result = zend_hash_find (ht, "", sizeof (""), (void **)data);
    }
  else if (Z_TYPE_P (ind) == IS_STRING)
    {
      result = zend_symtable_find (ht, Z_STRVAL_P (ind),
				   Z_STRLEN_P (ind) + 1, (void **) data);
    }
  else
    {
      // TODO: I believe this might need a warning.

      // TODO avoid alloc
      // use a string index for other types
      zval *string_index;
      MAKE_STD_ZVAL (string_index);
      string_index->value = ind->value;
      string_index->type = ind->type;
      zval_copy_ctor (string_index);
      convert_to_string (string_index);

      result = zend_symtable_find (ht, Z_STRVAL_P (string_index),
				   Z_STRLEN_P (string_index) + 1,
				   (void **) data);
      zval_ptr_dtor (&string_index);
    }
  return result;
}


static int
check_array_index_type (zval * ind TSRMLS_DC)
{
  if (Z_TYPE_P (ind) == IS_OBJECT || Z_TYPE_P (ind) == IS_ARRAY)
    {
      php_error_docref (NULL TSRMLS_CC, E_WARNING, "Illegal offset type");
      return 0;
    }

  return 1;
}

// Update a hashtable using a zval* index
static void
ht_update (HashTable * ht, zval * ind, zval * val, zval *** dest)
{
  int result;
  if (Z_TYPE_P (ind) == IS_LONG || Z_TYPE_P (ind) == IS_BOOL)
    {
      result = zend_hash_index_update (ht, Z_LVAL_P (ind), &val,
				       sizeof (zval *), (void **) dest);
    }
  else if (Z_TYPE_P (ind) == IS_DOUBLE)
    {
      result = zend_hash_index_update (ht, (long) Z_DVAL_P (ind),
				       &val, sizeof (zval *), (void **) dest);
    }
  else if (Z_TYPE_P (ind) == IS_NULL)
    {
      result = zend_hash_update (ht, "", sizeof (""), &val,
				 sizeof (zval *), (void **) dest);
    }
  else if (Z_TYPE_P (ind) == IS_STRING)
    {
      result = zend_symtable_update (ht, Z_STRVAL_P (ind),
				     Z_STRLEN_P (ind) + 1,
				     &val, sizeof (zval *), (void **) dest);
    }
  else
    {
      // TODO avoid alloc
      zval *string_index;
      MAKE_STD_ZVAL (string_index);
      string_index->value = ind->value;
      string_index->type = ind->type;
      zval_copy_ctor (string_index);
      convert_to_string (string_index);
      result = zend_symtable_update (ht, Z_STRVAL_P (string_index),
				     Z_STRLEN_P (string_index) + 1,
				     &val, sizeof (zval *), (void **) dest);

      zval_ptr_dtor (&string_index);
    }
  assert (result == SUCCESS);
}

// Delete from a hashtable using a zval* index
static void
ht_delete (HashTable * ht, zval * ind)
{
  // This may fail if the index doesnt exist, which is fine.
  if (Z_TYPE_P (ind) == IS_LONG || Z_TYPE_P (ind) == IS_BOOL)
    {
      zend_hash_index_del (ht, Z_LVAL_P (ind));
    }
  else if (Z_TYPE_P (ind) == IS_DOUBLE)
    {
      zend_hash_index_del (ht, (long) Z_DVAL_P (ind));
    }
  else if (Z_TYPE_P (ind) == IS_NULL)
    {
      zend_hash_del (ht, "", sizeof (""));
    }
  else if (Z_TYPE_P (ind) == IS_STRING)
    {
      zend_hash_del (ht, Z_STRVAL_P (ind), Z_STRLEN_P (ind) + 1);
    }
  else
    {
      // TODO avoid alloc
      zval *string_index;
      MAKE_STD_ZVAL (string_index);
      string_index->value = ind->value;
      string_index->type = ind->type;
      zval_copy_ctor (string_index);
      convert_to_string (string_index);
      zend_hash_del (ht, Z_STRVAL_P (string_index),
		     Z_STRLEN_P (string_index) + 1);

      zval_ptr_dtor (&string_index);
    }
}

// Check if a key exists in a hashtable 
static int
ht_exists (HashTable * ht, zval * ind)
{
  if (Z_TYPE_P (ind) == IS_LONG || Z_TYPE_P (ind) == IS_BOOL)
    {
      return zend_hash_index_exists (ht, Z_LVAL_P (ind));
    }
  else if (Z_TYPE_P (ind) == IS_DOUBLE)
    {
      return zend_hash_index_exists (ht, (long) Z_DVAL_P (ind));
    }
  else if (Z_TYPE_P (ind) == IS_NULL)
    {
      return zend_hash_exists (ht, "", sizeof (""));
    }
  else if (Z_TYPE_P (ind) == IS_STRING)
    {
      return zend_hash_exists (ht, Z_STRVAL_P (ind), Z_STRLEN_P (ind) + 1);
    }
  else
    {
      // TODO avoid alloc
      int result;
      zval *string_index;
      MAKE_STD_ZVAL (string_index);
      string_index->value = ind->value;
      string_index->type = ind->type;
      zval_copy_ctor (string_index);
      convert_to_string (string_index);
      result = zend_hash_exists (ht, Z_STRVAL_P (string_index),
				 Z_STRLEN_P (string_index) + 1);
      zval_ptr_dtor (&string_index);
      return result;
    }
  assert (0);
}

static zval **
get_ht_entry (zval ** p_var, zval * ind TSRMLS_DC)
{
  if (Z_TYPE_P (*p_var) == IS_STRING)
    {
      if (Z_STRLEN_PP (p_var) > 0)
	{
	  php_error_docref (NULL TSRMLS_CC, E_ERROR,
			    "Cannot create references to/from string offsets nor overloaded objects");
	}
    }

  if (Z_TYPE_P (*p_var) != IS_ARRAY)
    {
      zval_ptr_dtor (p_var);
      ALLOC_INIT_ZVAL (*p_var);
      array_init (*p_var);
    }

  HashTable *ht = extract_ht (p_var TSRMLS_CC);

  zval **data;
  if (ht_find (ht, ind, &data) == SUCCESS)
    {
      assert (data != NULL);
      return data;
    }

  // If we dont find it, put EG (uninitialized_zval_ptr) into the
  // hashtable, and return a pointer to its container.
  Z_ADDREF_P(EG(uninitialized_zval_ptr));
  ht_update (ht, ind, EG (uninitialized_zval_ptr), &data);

  assert (data != NULL);

  return data;
}


// Like extract_ht_ex, but for objects 
static HashTable *
extract_field_ex (zval * obj TSRMLS_DC)
{
  // TODO: this likely should be inlined somewhere.
  assert (!in_copy_on_write (obj));
  if (Z_TYPE_P (obj) == IS_NULL)
    {
      assert (0);
      // TODO: implement initialization
    }
  else if (Z_TYPE_P (obj) != IS_OBJECT)
    {
      // TODO: test if this is the right error message
      php_error_docref (NULL TSRMLS_CC, E_WARNING,
			"Cannot use a scalar value as an object");
      // TODO: implement initialization
      assert (0);
    }
  return Z_OBJPROP_P (obj);
}

// Like extract_ht, but for objects
static HashTable *
extract_field (zval ** p_var TSRMLS_DC)
{
  sep_copy_on_write (p_var);

  return extract_field_ex (*p_var TSRMLS_CC);
}

// Like get_ht_entry, but for objects
static zval **
get_field (zval ** p_var, char *ind TSRMLS_DC)
{
  if (Z_TYPE_P (*p_var) != IS_OBJECT)
    {
      // TODO: implement initialization
      assert (0);
    }

  HashTable *ht = extract_field (p_var TSRMLS_CC);

  zval **data;
  if (zend_symtable_find (ht, ind, strlen (ind) + 1, (void **) &data) ==
      SUCCESS)
    {
      assert (data != NULL);
      return data;
    }

  // If we dont find it, put EG (uninitialized_zval_ptr) into the
  // hashtable, and return a pointer to its container.
  Z_ADDREF_P(EG(uninitialized_zval_ptr));
  zend_symtable_update (ht, ind, strlen (ind) + 1,
			&EG (uninitialized_zval_ptr), sizeof (zval *),
			(void **) &data);

  assert (data != NULL);

  return data;
}

void
read_array (zval ** result, zval * array, zval * ind TSRMLS_DC)
{
  // Memory can be allocated in read_string_index
  if (array == EG (uninitialized_zval_ptr))
    {
      *result = array;
      return;
    }

  // Since we know its an array, and we dont write to it, we dont need
  // to separate it.
  HashTable *ht = Z_ARRVAL_P (array);

  // find the result
  zval **p_result;
  if (ht_find (ht, ind, &p_result) == SUCCESS)
    {
      *result = *p_result;
      return;
    }

  *result = EG (uninitialized_zval_ptr);
}

/* If its not an array, convert it into an array. */
static void
check_array_type (zval ** p_var TSRMLS_DC)
{
  if ((Z_TYPE_P (*p_var) == IS_BOOL && !Z_BVAL_PP (p_var))
      || Z_TYPE_P (*p_var) == IS_NULL
      || (Z_TYPE_P (*p_var) == IS_STRING && Z_STRLEN_PP (p_var) == 0))
    {
      // Non ref use new values
      if (!PZVAL_IS_REF (*p_var))
	{
	  zval_ptr_dtor (p_var);
	  ALLOC_INIT_ZVAL (*p_var);
	}
      else
	// Refs are just replaced
	zval_dtor (*p_var);

      array_init (*p_var);
    }
  else if (Z_TYPE_PP (p_var) != IS_STRING && Z_TYPE_PP (p_var) != IS_ARRAY)
    {
      // TODO: why are these different types than pushing
      php_error_docref (NULL TSRMLS_CC, E_WARNING,
			"Cannot use a scalar value as an array");
    }
}

/* If its not an array, convert it into an object. */
static void
check_object_type (zval ** p_var TSRMLS_DC)
{
  // TODO: implement
}

/* Push EG (uninitialized_zval_ptr) and return a pointer into the ht
 * for it */
/*
 * Converted to array automatically:
 *    ""
 *    NULL
 *    false
 *
 * Warning, no conversion:
 *    ints
 *    floats
 *    true
 *
 * Error, no conversion:
 *    strings other than ""
 */
// TODO: objects, resources, etc
static zval **
push_and_index_ht (zval ** p_var TSRMLS_DC)
{
  // Check for errors conditions

  if (Z_TYPE_P (*p_var) == IS_STRING && Z_STRLEN_PP (p_var) > 0)
    {
      php_error_docref (NULL TSRMLS_CC, E_ERROR,
			"[] operator not supported for strings");
      assert (0);		// unreachable
    }

  if (Z_TYPE_P (*p_var) == IS_BOOL && Z_BVAL_PP (p_var)
      || Z_TYPE_P (*p_var) == IS_LONG || Z_TYPE_P (*p_var) == IS_DOUBLE)
    {
      php_error_docref (NULL TSRMLS_CC, E_WARNING,
			"Cannot use a scalar value as an array");
      return NULL;
    }

  if (Z_TYPE_P (*p_var) != IS_ARRAY)
    {
      zval_ptr_dtor (p_var);
      ALLOC_INIT_ZVAL (*p_var);
      array_init (*p_var);
    }

  // if its not an array, make it an array
  HashTable *ht = extract_ht (p_var TSRMLS_CC);
  zval **data;

  Z_ADDREF_P(EG(uninitialized_zval_ptr));
  int result = zend_hash_next_index_insert (ht, &EG (uninitialized_zval_ptr),
					    sizeof (zval *), (void **) &data);
  assert (result == SUCCESS);

  assert (data);

  return data;
}
