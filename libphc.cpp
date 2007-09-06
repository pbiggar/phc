/* The difference between zend_symtable_X and zend_hash_X is that the
 * symtable version will check if the key is a string of an integer, and if
 * so, use the int version instead. We can use the zend_symtable_X versions
 * safely for symbol tables, since variables cant be integer strings, but we
 * cant safely use zend_hash_X versions for hashtable. Well-named, they are.
 */


/* An important note of zval*s and zval**s. Frequently, zval** are fetched from arrays and symbol tables. The zval** will point into the array, and so updating it will update the relevant array entry. It is normally not the same to dereference it to a local varaible, and pass a reference to that */

// Some common functions
#include "php.h"

// Extract the hashtable from a hash-valued zval
HashTable *
extract_ht (zval * arr TSRMLS_DC)
{
  assert (arr != EG (uninitialized_zval_ptr));
  if (Z_TYPE_P (arr) == IS_NULL)
    array_init (arr);
  else if (Z_TYPE_P (arr) != IS_ARRAY)
    {
      php_error_docref (NULL TSRMLS_CC, E_WARNING,
			"Cannot use a scalar value as an array");
      array_init (arr);
    }
  return Z_ARRVAL_P (arr);
}

/* Using IND as a key to HT, call the appropriate zend_index_X
 * function with data as a parameter, and return its result. This
 * updates the zval** pointed to by DATA. */
int
ht_find (HashTable * ht, zval * ind, zval *** data)
{
  int result;
  if (Z_TYPE_P (ind) == IS_LONG || Z_TYPE_P (ind) == IS_BOOL)
    {
      result = zend_hash_index_find (ht, Z_LVAL_P (ind), (void **) data);
    }
  else if (Z_TYPE_P (ind) == IS_DOUBLE)
    {
      zval *index;
      MAKE_STD_ZVAL (index);
      index->value = ind->value;
      index->type = ind->type;
      convert_to_long (index);
      result = zend_hash_index_find (ht, Z_LVAL_P (index), (void **) data);
      zval_ptr_dtor (&index);
    }
  else if (Z_TYPE_P (ind) == IS_NULL)
    {
      result = zend_symtable_find (ht, "", sizeof (""), (void **)data);
    }
  else
    {
      // use a string index for other types
      zval *string_index;
      MAKE_STD_ZVAL (string_index);
      string_index->value = ind->value;
      string_index->type = ind->type;
      zval_copy_ctor (string_index);
      convert_to_string (string_index);

      result =
	zend_symtable_find (ht, Z_STRVAL_P (string_index),
			    Z_STRLEN_P (string_index) + 1, (void **) data);
      zval_ptr_dtor (&string_index);
    }
  return result;
}

// Update a hashtable using a zval* index
void
ht_update (HashTable * ht, zval * ind, zval * val)
{
  if (Z_TYPE_P (ind) == IS_LONG || Z_TYPE_P (ind) == IS_BOOL)
    {
      int result = zend_hash_index_update (ht, Z_LVAL_P
					   (ind), &val, sizeof (zval *),
					   NULL);
      assert (result == SUCCESS);
    }
  else if (Z_TYPE_P (ind) == IS_DOUBLE)
    {
      zval *index;
      MAKE_STD_ZVAL (index);
      index->value = ind->value;
      index->type = ind->type;
      convert_to_long (index);
      int result = zend_hash_index_update (ht, Z_LVAL_P (index),
					   &val, sizeof (zval *), NULL);
      assert (result == SUCCESS);
      zval_ptr_dtor (&index);
    }
  else if (Z_TYPE_P (ind) == IS_NULL)
    {
      int result =
	zend_hash_update (ht, "", sizeof (""), &val, sizeof (zval *), NULL);
      assert (result == SUCCESS);
    }
  else
    {
      zval *string_index;
      MAKE_STD_ZVAL (string_index);
      string_index->value = ind->value;
      string_index->type = ind->type;
      zval_copy_ctor (string_index);
      convert_to_string (string_index);
      int result = zend_symtable_update (ht, Z_STRVAL_P (string_index),
					 Z_STRLEN_P (string_index) + 1, &val,
					 sizeof (zval *), NULL);

      assert (result == SUCCESS);
      zval_ptr_dtor (&string_index);
    }
}

// Delete from a hashtable using a zval* index
void
ht_delete (HashTable * ht, zval * ind)
{
  if (Z_TYPE_P (ind) == IS_LONG || Z_TYPE_P (ind) == IS_BOOL)
    {
      int result = zend_hash_index_del (ht, Z_LVAL_P (ind));
      assert (result == SUCCESS);
    }
  else if (Z_TYPE_P (ind) == IS_DOUBLE)
    {
      zval *index;
      MAKE_STD_ZVAL (index);
      index->value = ind->value;
      index->type = ind->type;
      convert_to_long (index);

      int result = zend_hash_index_del (ht, Z_LVAL_P (index));
      assert (result == SUCCESS);

      zval_ptr_dtor (&index);
    }
  else if (Z_TYPE_P (ind) == IS_NULL)
    {
      int result = zend_hash_del (ht, "", sizeof (""));
      assert (result == SUCCESS);
    }
  else
    {
      zval *string_index;
      MAKE_STD_ZVAL (string_index);
      string_index->value = ind->value;
      string_index->type = ind->type;
      zval_copy_ctor (string_index);
      convert_to_string (string_index);
      int result = zend_hash_del (ht, Z_STRVAL_P (string_index),
				  Z_STRLEN_P (string_index) + 1);

      assert (result == SUCCESS);
      zval_ptr_dtor (&string_index);
    }
}


void
ht_debug (HashTable * ht)
{
  printf ("\nHASH\n");
  if (ht == NULL)
    {
      printf ("NULL\n");
      return;
    }
  for (zend_hash_internal_pointer_reset (ht);
       zend_hash_has_more_elements (ht) == SUCCESS;
       zend_hash_move_forward (ht))
    {
      char *key;
      unsigned keylen;
      unsigned long idx;
      int type;
      zval **ppzval;
      zval *zvp;

      type = zend_hash_get_current_key_ex (ht, &key, &keylen, &idx, 0, NULL);
      zend_hash_get_current_data (ht, (void **) &ppzval);

      zvp = *ppzval;

      if (type == HASH_KEY_IS_STRING)
	{
	  printf (key);
	}
      else
	{
	  printf ("%ld", idx);
	}

      printf (": addr = %08lX, refcount = %d, is_ref = %d ",
	      (long unsigned int) (*ppzval), (*ppzval)->refcount,
	      (*ppzval)->is_ref);
      switch (Z_TYPE_P (zvp))
	{
	case IS_NULL:
	  printf ("(NULL)");
	  break;
	case IS_LONG:
	  printf ("(%ldL)", Z_LVAL_P (zvp));
	  break;
	case IS_DOUBLE:
	  printf ("(%lff)", Z_DVAL_P (zvp));
	  break;
	case IS_BOOL:
	  printf (Z_BVAL_P (zvp) ? "(true)" : "(false)");
	  break;
	case IS_ARRAY:
	  printf ("(array(%d))", Z_ARRVAL_P (zvp)->nNumOfElements);
	  break;
	case IS_OBJECT:
	  printf ("(Object)");
	  break;
	case IS_STRING:
	  printf ("(\"%s\")", Z_STRVAL_P (zvp));
	  break;
	case IS_RESOURCE:
	  printf ("(Resource)");
	  break;
	default:
	  printf ("(Invalid: %d)", Z_TYPE_P (zvp));
	}

      printf ("\n");

    }
  printf ("END HASH\n");
}


// Call ht_debug on the named var in the given symbol table
void
ht_var_debug (HashTable * st, char *name)
{
  zval **p_zvp;
  if (zend_symtable_find (st, name, strlen (name) + 1,
			  (void **) &p_zvp) != SUCCESS)
    {
      printf ("VAR NOT IN SYMBOL TABLE: '%s'\n", name);
      return;
    }

  if (Z_TYPE_P (*p_zvp) != IS_ARRAY)
    {
      printf ("NOT HASH\n");
      return;
    }

  ht_debug ((*p_zvp)->value.ht);
}



// Make a copy of a zval*
void
zvp_clone (zval ** p_zvp, int *is_zvp_new TSRMLS_DC)
{
  zval *clone;
  MAKE_STD_ZVAL (clone);
  clone->value = (*p_zvp)->value;
  clone->type = (*p_zvp)->type;
  zval_copy_ctor (clone);
  assert (is_zvp_new);
  if (*is_zvp_new)
	  zval_ptr_dtor (p_zvp);
  *is_zvp_new = 1;
  *p_zvp = clone;
}

// Overwrite one zval with another
void
overwrite_lhs (zval * lhs, zval * rhs)
{
  // First, call the destructor to remove any data structures
  // associated with lhs that will now be overwritten
  zval_dtor (lhs);
  // Overwrite LHS
  lhs->value = rhs->value;
  lhs->type = rhs->type;
  zval_copy_ctor (lhs);
}

// TODO dont overwrite line numbers if we're compiling an extension
void
phc_setup_error (int init, char *filename, int line_number,
		 zend_function * function TSRMLS_DC)
{
  static int old_in_compilation;
  static int old_in_execution;
  static char *old_filename;
  static int old_lineno;
  static zend_function *old_function;
  if (init)
    {
      if (filename == NULL)
	filename = "[phc_compiled_file]";
      // Save old values
      old_in_compilation = CG (in_compilation);
      old_in_execution = EG (in_execution);
      old_filename = CG (compiled_filename);
      old_lineno = CG (zend_lineno);
      old_function = EG (function_state_ptr)->function;
      // Put in our values
      CG (in_compilation) = 1;
      EG (in_execution) = 1;
      CG (compiled_filename) = filename;
      CG (zend_lineno) = line_number;
      if (function)
	EG (function_state_ptr)->function = function;
    }
  else
    {
      CG (in_compilation) = old_in_compilation;
      EG (in_execution) = old_in_execution;
      CG (compiled_filename) = old_filename;
      CG (zend_lineno) = old_lineno;
      EG (function_state_ptr)->function = old_function;
    }
}

// Separate the RHS (that is, make a copy *and update the hashtable*)
// See "Separation anxiety" in the PHP book
void
separate_var (HashTable * st, char *name, int length, zval ** p_zvp,
	      int *is_zvp_new TSRMLS_DC)
{
  /* For a reference assignment, the LHS is always updated
   * to point to the RHS (even if the LHS is currently
   * is_ref) However, if the RHS is in a copy-on-write set
   * (refcount > 1 but not is_ref), it must be seperated
   * first */
  if (!((*p_zvp)->refcount > 1 && !(*p_zvp)->is_ref))
    return;

  zvp_clone (p_zvp, is_zvp_new TSRMLS_CC);

  (*p_zvp)->refcount++;
  int result = zend_hash_update (st,
				 name, length,
				 p_zvp,
				 sizeof (zval *), NULL);
  assert (result == SUCCESS);
}

/* Assuming that p_zvp points into a hashtable, we decrease the
 * refcount of the currently pointed to object, then clone it, and
 * insert it into the hashtable */
// TODO Separation writes into the array, which automatically calls
// the zval_ptr_dtor. However, if the array doesnt have a registered
// destructor, then we shouldnt be calling this.
//
void
separate_zvpp (zval ** p_zvp, int *is_zvp_new TSRMLS_DC)
{
  zval *old = *p_zvp;
  assert (p_zvp != &EG(uninitialized_zval_ptr));
  if (old == EG (uninitialized_zval_ptr))
  {
	  ALLOC_INIT_ZVAL (*p_zvp);
	  *is_zvp_new = 0;
  }
  else
  {
	  zvp_clone (p_zvp, is_zvp_new TSRMLS_CC);
	  zval_ptr_dtor (&old);
  }
}

// Separate the variable at an index of the hashtable (that is, make a copy, and update the hashtable. The symbol table is unaffect, except if the array doesnt exist, in which case it gets created.)
// See "Separation anxiety" in the PHP book
void
separate_array_entry (HashTable * st, char *var_name, int var_length,
		      char *ind_name, int ind_length, zval ** p_zvp,
		      int *is_zvp_new TSRMLS_DC)
{
  /* For a reference assignment, the LHS is always updated
   * to point to the RHS (even if the LHS is currently
   * is_ref) However, if the RHS is in a copy-on-write set
   * (refcount > 1 but not is_ref), it must be seperated
   * first */
  if ((*p_zvp) != EG (uninitialized_zval_ptr)
      && !((*p_zvp)->refcount > 1 && !(*p_zvp)->is_ref))
    return;

  zvp_clone (p_zvp, is_zvp_new TSRMLS_CC);

  zval *var = NULL;
  zval **p_var = &var;

  zval *ind = NULL;
  zval **p_ind = &ind;

  zval *zvp = *p_zvp;

  int var_exists = (zend_symtable_find (st, var_name, var_length,
					(void **) &p_var) == SUCCESS);
  if (var_exists)
    //  if (var_exists && *p_var != EG(uninitialized_zval_ptr)) // perhaps
    var = *p_var;
  else
    {
      // if no var, create it and add it to the symbol table
      ALLOC_INIT_ZVAL (var);
      zend_symtable_update (st, var_name, var_length,
			    &var, sizeof (zval *), NULL);
    }

  // if its not an array, make it an array
  HashTable *ht = extract_ht (var TSRMLS_CC);

  // find the index
  int ind_exists = (zend_symtable_find (st, ind_name, ind_length,
					(void **) &p_ind) == SUCCESS);
  if (ind_exists)
    ind = *p_ind;
  else
    {
      ALLOC_INIT_ZVAL (ind);
    }

  zvp->refcount++;
  ht_update (ht, ind, zvp);

  if (!ind_exists)
    zval_ptr_dtor (&ind);
}


/* Write P_RHS into the symbol table as a variable named VAR_NAME */
void
write_var (HashTable * st, char *var_name, int var_length, zval ** p_rhs,
	   int *is_rhs_new TSRMLS_DC)
{
  zval *lhs = NULL;
  zval **p_lhs = &lhs;
  zval *rhs = *p_rhs;

  int lhs_exists = (zend_symtable_find (st, var_name, var_length,
					(void **) &p_lhs) == SUCCESS);

  if (lhs_exists)
    lhs = *p_lhs;

  if (!lhs_exists || !lhs->is_ref)
    {
      if (rhs->is_ref)
	{
	  zvp_clone (p_rhs, is_rhs_new TSRMLS_CC);
	  rhs = *p_rhs;
	}

      rhs->refcount++;

      int result = zend_hash_update (st, var_name, var_length,
				     &rhs,
				     sizeof (zval *), NULL);
      assert (result == SUCCESS);
    }
  else
    {
      overwrite_lhs (lhs, rhs);
    }
}


/* Read the variable named VAR_NAME from the local symbol table and return
 * it. If the variable doent exist, a new one is created and *IS_NEW is set.
 * */
zval *
read_var (HashTable * st, char *var_name, int var_length,
	  int *is_new TSRMLS_DC)
{
  zval **p_zvp;
  if (zend_symtable_find
      (st, var_name, var_length, (void **) &p_zvp) == SUCCESS)
    {
      *is_new = 0;
      return *p_zvp;
    }

  // The function call mechanism deals specially with
  // EG(uninitialize_zval_ptr) (or sometime EG(uninitialize_zval)), so
  // we need to use this too. This particular zval can also be set, so
  // theres no guarantee that it's NULL, that its refcount is 1, or
  // that is_ref is 0. So it needs to be treated carefully.
  zval *zvp = EG (uninitialized_zval_ptr);
  //  ALLOC_INIT_ZVAL (zvp);
  //  *is_new = 1;
  return zvp;
}

/* Read the variable named VAR_NAME from the local symbol table, and
 * find the variable which it refers to and return it. If the variable
 * doent exist, a new one is created and *IS_NEW is set.
 * */
zval *
read_var_var (HashTable * st, char *var_name, int var_length,
	  int *is_new TSRMLS_DC)
{
	zval **p_zvp;
	zval **p_result;
	if (zend_symtable_find
			(st, var_name, var_length, (void **) &p_zvp) != SUCCESS)
	{
		return EG (uninitialized_zval_ptr);
	}

	if (ht_find (st, *p_zvp, &p_result) != SUCCESS)
	{
		return EG (uninitialized_zval_ptr);
	}

	return *p_result;

}

zval *
read_array (HashTable * st, char *var_name, int var_length, char *ind_name,
	    int ind_length, int *is_new TSRMLS_DC)
{
  zval *var = NULL;
  zval **p_var = &var;

  zval *ind = NULL;
  zval **p_ind = &ind;

  zval *result = NULL;
  zval **p_result = &ind;

  int var_exists = (zend_symtable_find (st, var_name, var_length,
					(void **) &p_var) == SUCCESS);
  if (!var_exists)
    {
      return EG (uninitialized_zval_ptr);
    }

  var = *p_var;

  if (Z_TYPE_P (var) != IS_ARRAY)	// TODO IS_STRING
    {
      // TODO does this need an error, if so, use extract_ht
      return EG (uninitialized_zval_ptr);
    }

  // if its not an array, make it an array
  HashTable *ht = extract_ht (var TSRMLS_CC);

  // find the index
  int ind_exists = (zend_symtable_find (st, ind_name, ind_length,
					(void **) &p_ind) == SUCCESS);
  if (ind_exists)
    ind = *p_ind;
  else
    {
      // do not remove these curlies, as this expands to 2 statements
      ALLOC_INIT_ZVAL (ind);
    }

  // find the var
  int result_exists = (ht_find (ht, ind, &p_result) == SUCCESS);
  if (result_exists)
    result = *p_result;
  else
    {
      //      *is_new = 1;
      //      ALLOC_INIT_ZVAL (result);
      result = EG (uninitialized_zval_ptr);
    }

  if (!ind_exists)
    zval_ptr_dtor (&ind);

  return result;
}

zval *
read_var_array (HashTable * st, char *var_name, int var_length, char *ind_name,
	    int ind_length, int *is_new TSRMLS_DC)
{
  zval *var = NULL;
  zval **p_var = &var;

  zval *refl = NULL;
  zval **p_refl = &var;

  zval *ind = NULL;
  zval **p_ind = &ind;

  zval *result = NULL;
  zval **p_result = &ind;

	// read the reflector
  if (zend_symtable_find (st, var_name, var_length,
			  (void **) &p_refl) != SUCCESS)
  {
	  return EG (uninitialized_zval_ptr);
  }

  refl = *p_refl;

	// read the variable itself
  if (ht_find (st, *p_refl, &p_var) != SUCCESS)
  {
	  return EG (uninitialized_zval_ptr);
  }

  var = *p_var;

  if (Z_TYPE_P (var) != IS_ARRAY)	// TODO IS_STRING
    {
      // TODO does this need an error, if so, use extract_ht
      return EG (uninitialized_zval_ptr);
    }

  // if its not an array, make it an array
  HashTable *ht = extract_ht (var TSRMLS_CC);

  // find the index
  int ind_exists = (zend_symtable_find (st, ind_name, ind_length,
					(void **) &p_ind) == SUCCESS);
  if (ind_exists)
    ind = *p_ind;
  else
    {
      // do not remove these curlies, as this expands to 2 statements
      ALLOC_INIT_ZVAL (ind);
    }

  // find the var
  int result_exists = (ht_find (ht, ind, &p_result) == SUCCESS);
  if (result_exists)
    result = *p_result;
  else
    {
      //      *is_new = 1;
      //      ALLOC_INIT_ZVAL (result);
      result = EG (uninitialized_zval_ptr);
    }

  if (!ind_exists)
    zval_ptr_dtor (&ind);

  return result;
}

/* Write P_RHS into the symbol table as a variable named VAR_NAME */
void
write_array (HashTable * st, char *var_name, int var_length, char *ind_name,
	     int ind_length, zval ** p_rhs, int *is_rhs_new TSRMLS_DC)
{
  zval *var = NULL;
  zval **p_var = &var;

  zval *lhs = NULL;
  zval **p_lhs = &lhs;

  zval *ind = NULL;
  zval **p_ind = &ind;

  zval *rhs = *p_rhs;

  int var_exists = (zend_symtable_find (st, var_name, var_length,
					(void **) &p_var) == SUCCESS);
  if (var_exists && *p_var != EG (uninitialized_zval_ptr))
    {
      // Note that we delibrately use separate_var, and not separate_array.
      int is_var_new = 0;
      var = *p_var;
      // if we use p_var instead of &var, zend_hash_update throws
      // an error and returns failure.
      separate_var (st, var_name, var_length, &var, &is_var_new TSRMLS_CC);
      if (is_var_new)
	zval_ptr_dtor (p_var);
    }
  else
    {
      // if no var, create it and add it to the symbol table
      ALLOC_INIT_ZVAL (var);
      zend_symtable_update (st, var_name, var_length,
			    &var, sizeof (zval *), NULL);
    }

  // TODO this makes it an array
  // if its not an array, make it an array
  HashTable *ht = extract_ht (var TSRMLS_CC);

  // find the index
  int ind_exists = (zend_symtable_find (st, ind_name, ind_length,
					(void **) &p_ind) == SUCCESS);
  if (ind_exists)
    ind = *p_ind;
  else
    {
      // do not remove these curlies, as this expands to 2 statements
      ALLOC_INIT_ZVAL (ind);
    }


  // find the var
  int lhs_exists = (ht_find (ht, ind, &p_lhs) == SUCCESS);
  if (lhs_exists)
    lhs = *p_lhs;


  if (!lhs_exists || !lhs->is_ref)
    {
      if (rhs->is_ref)
	{
	  zvp_clone (p_rhs, is_rhs_new TSRMLS_CC);
	  rhs = *p_rhs;
	}

      rhs->refcount++;

      ht_update (ht, ind, rhs);
    }
  else
    {
      // TODO not sure if this is possible
      overwrite_lhs (lhs, rhs);
    }

  if (!ind_exists)
    zval_ptr_dtor (&ind);
}


/* Write P_RHS into the symbol table as a variable named VAR_NAME */
void
push_var (HashTable * st, char *var_name, int var_length, zval ** p_rhs,
	  int *is_rhs_new TSRMLS_DC)
{
  zval *var = NULL;
  zval **p_var = &var;

  zval *rhs = *p_rhs;

  int var_exists = (zend_symtable_find (st, var_name, var_length,
					(void **) &p_var) == SUCCESS);
  if (var_exists && *p_var != EG (uninitialized_zval_ptr))
    {
      int is_var_new = 0;
      var = *p_var;
      // if we use p_var instead of &var, zend_has_update throws
      // an error and returns failure.
      separate_var (st, var_name, var_length, &var, &is_var_new TSRMLS_CC);
      if (is_var_new)
	zval_ptr_dtor (p_var);
    }
  else
    {
      // if no var, create it and add it to the symbol table
      ALLOC_INIT_ZVAL (var);
      zend_symtable_update (st, var_name, var_length,
			    &var, sizeof (zval *), NULL);
    }

  if (Z_TYPE_P (var) == IS_STRING)
    {
      php_error_docref (NULL TSRMLS_CC, E_ERROR, "[] operator not supported for strings");
    }

  // if its not an array, make it an array
  HashTable *ht = extract_ht (var TSRMLS_CC);

  rhs->refcount++;
  zend_hash_next_index_insert (ht, &rhs, sizeof (zval *), NULL);

}

/* Potentially change-on-write VAR_NAME1, contained in
 * the variable P_VAR1. If P_VAR1 is in the copy-on-write
 * set, separate it, and write it back as VAR_NAME2,
 * which should be its original name */
void
write_var_reference (HashTable * st, char *name, int length, zval ** p_zvp,
		     int *is_zvp_new TSRMLS_DC)
{
  // Change-on-write
  (*p_zvp)->is_ref = 1;
  (*p_zvp)->refcount++;
  int result = zend_hash_update (st, name, length, p_zvp,
				 sizeof (zval *), NULL);
  assert (result == SUCCESS);
}

/* Potentially change-on-write VAR_NAME1, contained in
 * the variable P_VAR1. If P_VAR1 is in the copy-on-write
 * set, separate it, and write it back as VAR_NAME2,
 * which should be its original name */
void				// TODO change function and update 
write_array_reference (HashTable * st, char *var_name, int var_length,
		       char *ind_name, int ind_length, zval ** p_zvp,
		       int *is_zvp_new TSRMLS_DC)
{
  // Change-on-write
  (*p_zvp)->is_ref = 1;
  (*p_zvp)->refcount++;

  zval *var = NULL;
  zval **p_var = &var;

  zval *ind = NULL;
  zval **p_ind = &ind;

  zval *zvp = *p_zvp;

  int var_exists = (zend_symtable_find (st, var_name, var_length,
					(void **) &p_var) == SUCCESS);
  if (var_exists)
    //  if (var_exists && *p_var != EG(uninitialized_zval_ptr)) // perhaps
    var = *p_var;
  else
    {
      // if no var, create it and add it to the symbol table
      ALLOC_INIT_ZVAL (var);
      zend_symtable_update (st, var_name, var_length,
			    &var, sizeof (zval *), NULL);
    }

  if (Z_TYPE_P (var) == IS_STRING)
  {
	  php_error_docref (NULL TSRMLS_CC, E_ERROR, "Cannot create references to/from string offsets nor overloaded objects");
  }

  // if its not an array, make it an array
  HashTable *ht = extract_ht (var TSRMLS_CC);

  // find the index
  int ind_exists = (zend_symtable_find (st, ind_name, ind_length,
					(void **) &p_ind) == SUCCESS);
  if (ind_exists)
    ind = *p_ind;
  else
    {
      ALLOC_INIT_ZVAL (ind);
    }

  ht_update (ht, ind, zvp);

  if (!ind_exists)
    zval_ptr_dtor (&ind);
}

zval **
fetch_var_arg_by_ref (HashTable * st, char *name, int name_length,
		      int *is_arg_new TSRMLS_DC)
{
  zval **p_arg = NULL;
  if (zend_symtable_find (st, name, name_length, (void **) &p_arg) != SUCCESS)
  {
	  // we want to pass a reference into the symbol table, so we create a value, save it, find it, then return it.
	  zval *arg;
	  ALLOC_INIT_ZVAL (arg);
	  arg->is_ref = 1;
	  int result = zend_hash_update (st,
			  name, name_length,
			  &arg,
			  sizeof (zval *), NULL);
	  assert (result == SUCCESS);

	  /* Set p_arg to point into the symbol table. */
	  result = zend_hash_find (st, name, name_length, (void **) &p_arg);
	  assert (result == SUCCESS);
	  return p_arg;
  }

  // Separate argument if it is part of a copy-on-write
  // set, and we are passing by reference
  if ((*p_arg)->refcount > 1 && !(*p_arg)->is_ref)
  {
    separate_zvpp (p_arg, is_arg_new TSRMLS_CC);
	 *is_arg_new = 0;
  }

  // We don't need to restore ->is_ref afterwards,
  // because the called function will reduce the
  // refcount of arg on return, and will reset is_ref to
  // 0 when refcount drops to 1.  If the refcount does
  // not drop to 1 when the function returns, but we did
  // set is_ref to 1 here, that means that is_ref must
  // already have been 1 to start with (since if it had
  // not, that means that the variable would have been
  // in a copy-on-write set, and would have been
  // seperated above).
  (*p_arg)->is_ref = 1;

  return p_arg;
}

/* Dont pass-by-ref */
zval *
fetch_var_arg (HashTable * st, char *name, int name_length,
	       int *is_arg_new TSRMLS_DC)
{
  zval **p_arg;
  if (zend_symtable_find (st, name, name_length, (void **) &p_arg) != SUCCESS)
    {
      // we only do this for variables to be passed to function calls
      p_arg = &EG (uninitialized_zval_ptr);
    }

  if (p_arg == &EG (uninitialized_zval_ptr))
    return *p_arg;

  zval *arg = *p_arg;

  // Since we dont pass by ref, we only need to separate if we have a
  // ref. Otherwise, it will be separated later.
  // TODO It should be separated later no matter what, no?

  // Clone argument if it is part of a change-on-write
  // set, and we are *not* passing by reference
  if (arg->is_ref)
    {
      // Dont update the original, make a copy
      assert (arg != EG (uninitialized_zval_ptr));
      zvp_clone (&arg, is_arg_new TSRMLS_CC);

      // It seems we get incorrect refcounts without this
      // TODO This decreases the refcount to zero, which seems wrong,
      // but gives the right answer. We should look at how zend does
      // this.
      arg->refcount--;
    }

  return arg;
}

zval **
fetch_array_arg_by_ref (HashTable * st, char *name, int name_length,
			char *ind_name, int ind_length,
			int *is_arg_new TSRMLS_DC)
{
  zval **p_var;
  zval **p_ind;
  zval **p_arg;

  int var_exists = (zend_symtable_find (st, name, name_length,
					(void **) &p_var) == SUCCESS);
  if (!var_exists || *p_var == EG (uninitialized_zval_ptr))
  {
	  // We want to create a new array, which the passed var
	  // would be part of. Additionally, the var needs to be
	  // written back after creation.
	  zval *var;
	  ALLOC_INIT_ZVAL (var);
	  int result = zend_hash_update (st,
			  name, name_length,
			  &var,
			  sizeof (zval *), NULL);
	  assert (result == SUCCESS);

	  /* Set p_var to point into the symbol table. */
	  result = zend_hash_find (st, name, name_length, (void **) &p_var);
	  assert (result == SUCCESS);
  }
  else
    {
      // Since we'll be passing a pointer into this hashtable, we
      // need to separate it now.
      if (!(*p_var)->is_ref)
	{
	  // p_var already points into the symtable, so we dont need to
	  // write back.
	  int is_var_new = 0;
	  if ((*p_var)->refcount > 1 && !(*p_var)->is_ref)
	    separate_zvpp (p_var, &is_var_new TSRMLS_CC);
	}
    }

  // if its not an array, make it an array
  HashTable *ht = extract_ht (*p_var TSRMLS_CC);


  // find the index
  int ind_exists = (zend_symtable_find (st, ind_name, ind_length,
					(void **) &p_ind) == SUCCESS);
  if (!ind_exists)
    p_ind = &EG (uninitialized_zval_ptr);


  // find the var
  int arg_exists = (ht_find (ht, *p_ind, &p_arg) == SUCCESS);
  if (!arg_exists)
    {
      // The argument needs to be put into the array. Add it, and set
      // p_arg to point to the bucket containing it.
      ht_update (ht, *p_ind, EG (uninitialized_zval_ptr));
      int result = ht_find (ht, *p_ind, &p_arg);
      assert (result == SUCCESS);
      return p_arg;
    }

  // Separate argument if it is part of a copy-on-write
  // set, and we are passing by reference

  // We know that p_arg points into the hashtable. Therefore we can
  // just clone it, and dont need to update the hashtable.
  if ((*p_arg)->refcount > 1 && !(*p_arg)->is_ref)
    separate_zvpp (p_arg, is_arg_new TSRMLS_CC);

  // We don't need to restore ->is_ref afterwards,
  // because the called function will reduce the
  // refcount of arg on return, and will reset is_ref to
  // 0 when refcount drops to 1.  If the refcount does
  // not drop to 1 when the function returns, but we did
  // set is_ref to 1 here, that means that is_ref must
  // already have been 1 to start with (since if it had
  // not, that means that the variable would have been
  // in a copy-on-write set, and would have been
  // seperated above).
  (*p_arg)->is_ref = 1;

  return p_arg;
}

/* Dont pass-by-ref */
zval *
fetch_array_arg (HashTable * st, char *name, int name_length, char *ind_name,
		 int ind_length, int *is_arg_new TSRMLS_DC)
{
  zval **p_var;
  zval **p_ind;
  zval **p_arg;

  int var_exists = (zend_symtable_find (st, name, name_length,
					(void **) &p_var) == SUCCESS);
  if (!var_exists || *p_var == EG (uninitialized_zval_ptr))
    {
      return EG (uninitialized_zval_ptr);
    }
  else
    {
      // !pass_by_ref and var->is_ref - do nothing
      // !pass_by_ref and !var->is_ref - if not array, return uninit

      if (Z_TYPE_P (*p_var) != IS_ARRAY)
	{
	  return EG (uninitialized_zval_ptr);
	}
    }

  // if its not an array, make it an array
  HashTable *ht = extract_ht (*p_var TSRMLS_CC);

  // find the index
  int ind_exists = (zend_symtable_find (st, ind_name, ind_length,
					(void **) &p_ind) == SUCCESS);
  if (!ind_exists)
    p_ind = &EG (uninitialized_zval_ptr);

  // find the var
  int arg_exists = (ht_find (ht, *p_ind, &p_arg) == SUCCESS);
  if (!arg_exists)
    return EG (uninitialized_zval_ptr);

  if (*p_arg == EG (uninitialized_zval_ptr))
    {
      return EG (uninitialized_zval_ptr);
      // after the find, p_arg is the address of the ht entry, which contains a zval*. This can be updated by the function call.
      //      ht_update (ht, *p_ind, *p_arg);
      //    int result = ht_find (ht, *p_ind, &p_arg);
      //    assert (result == SUCCESS);
      //   return p_arg;
    }
  zval *arg = *p_arg;

  // Clone argument if it is part of a change-on-write
  // set, and we are *not* passing by reference

  if (arg->is_ref)
    {
      // Dont update the original, make a copy
      assert (arg != EG (uninitialized_zval_ptr));
      zvp_clone (&arg, is_arg_new TSRMLS_CC);

      // It seems we get incorrect refcounts without this
      // TODO This decreases the refcount to zero, which seems wrong,
      // but gives the right answer. We should look at how zend does
      // this.
      arg->refcount--;
    }

  return arg;
}

void
cast_var (zval ** p_zvp, int *is_zvp_new, int type TSRMLS_DC)
{
  assert (type >= 0 && type <= 6);
  if ((*p_zvp)->type == type)
    return;

  zvp_clone (p_zvp, is_zvp_new TSRMLS_CC);
  zval *zvp = *p_zvp;

  switch (type)
    {
    case IS_NULL:
      convert_to_null (zvp);
      break;
    case IS_BOOL:
      convert_to_boolean (zvp);
      break;
    case IS_LONG:
      convert_to_long (zvp);
      break;
    case IS_DOUBLE:
      convert_to_double (zvp);
      break;
    case IS_STRING:
      convert_to_string (zvp);
      break;
    case IS_ARRAY:
      convert_to_array (zvp);
      break;
    case IS_OBJECT:
      convert_to_object (zvp);
      break;
    }
}

void
unset_var (HashTable * st, char *name, int length TSRMLS_DC)
{
  zend_hash_del (st, name, length);
}

void
unset_array (HashTable * st, char *var_name, int var_length, char *ind_name,
	     int ind_length TSRMLS_DC)
{

  zval **p_var;
  zval **p_ind;

  int var_exists = (zend_symtable_find (st, var_name, var_length,
					(void **) &p_var) == SUCCESS);
  if (!var_exists)
    return;

  if (Z_TYPE_P (*p_var) == IS_STRING)
  {
	  php_error_docref (NULL TSRMLS_CC, E_ERROR, "Cannot unset string offsets");
  }

  if (Z_TYPE_P (*p_var) != IS_ARRAY)
    {
      // TODO does this need an error, if so, use extract_ht
      return;
    }

  // if its not an array, make it an array
  HashTable *ht = extract_ht (*p_var TSRMLS_CC);

  // find the index
  int ind_exists = (zend_symtable_find (st, ind_name, ind_length,
					(void **) &p_ind) == SUCCESS);
  if (!ind_exists)
    {
      // do not remove these curlies, as this expands to 2 statements
      ALLOC_INIT_ZVAL (*p_ind);
    }

  ht_delete (ht, *p_ind);

  if (!ind_exists)
    zval_ptr_dtor (p_ind);
}

void
eval (zval* zvp, zval** p_result, int* is_result_new TSRMLS_DC)
{
   // If the user wrote "return ..", we need to store the
   // return value; however, in that case, zend_eval_string
   // will slap an extra "return" onto the front of the string,
   // so we must remove the "return" from the string the user
   // wrote. If the user did not write "return", he is not
   // interested in the return value, and we must pass NULL
   // instead or rhs to avoid zend_eval_string adding "return".

   // convert to a string
   zval *copy;
   MAKE_STD_ZVAL (copy);
   copy->value = zvp->value;
   copy->type = zvp->type;
   zval_copy_ctor (copy);
   convert_to_string (copy);

   MAKE_STD_ZVAL (*p_result);
   *is_result_new = 1;
   if (!strncmp (Z_STRVAL_P (copy), "return ", 7))
   {
      zend_eval_string (Z_STRVAL_P (copy) + 7, *p_result,
	    "eval'd code" TSRMLS_CC);
   }
   else
   {
      zend_eval_string (Z_STRVAL_P (copy), NULL, "eval'd code" TSRMLS_CC);
      ZVAL_NULL (*p_result);
   }

   // cleanup
   zval_ptr_dtor (&copy);
}

void
phc_exit (char *arg_name, int arg_length TSRMLS_DC)
{
  int is_arg_new = 0;
  zval *arg = read_var (EG (active_symbol_table), arg_name, arg_length,
			&is_arg_new TSRMLS_CC);
  if (Z_TYPE_P (arg) == IS_LONG)
    EG (exit_status) = Z_LVAL_P (arg);
  else
    zend_print_variable (arg);

  zend_bailout ();
}

/* Copies a constant into ZVP. Note that LENGTH does not include the NULL-terminating byte. */
void
get_constant (char *name, int length, zval ** p_zvp,
	      int *is_zvp_new TSRMLS_DC)
{
  MAKE_STD_ZVAL (*p_zvp);
  // zend_get_constant returns 1 for success, not SUCCESS
  int result = zend_get_constant (name, length, *p_zvp TSRMLS_CC);
  if (result == 0)
    ZVAL_STRINGL (*p_zvp, name, length, 1);

  *is_zvp_new = 1;
}

void phc_check_invariants (TSRMLS_D)
{
	assert (EG(uninitialized_zval_ptr) == &EG(uninitialized_zval));
	assert (EG(uninitialized_zval).refcount >= 1);
	assert (EG(uninitialized_zval).value.lval == 0);
	assert (EG(uninitialized_zval).type == IS_NULL);
	assert (EG(uninitialized_zval).is_ref == 0);
}
