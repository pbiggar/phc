/* The difference between zend_symtable_X and zend_hash_X is that
 * the _symtable version will check if the key is a string of an
 * integer, and if so, use the int version instead. We can use the
 * zend_hash_X versions safely for symbol tables, since
 * variables cant be integer strings, but we cant safely use
 * zend_hash_X versions for hashtable lookups. Well-named, they are.
 */

/* An important note of zval*s and zval**s. Frequently, zval** are
 * fetched from arrays and symbol tables. The zval** will point into
 * the array, and so updating it will update the relevant array
 * entry. It is normally not the same to dereference it to a local
 * variable, and pass a reference to that */

/* The function call mechanism deals specially with
 * EG(uninitialize_zval_ptr) (or sometime EG(uninitialize_zval)), so
 * we need to use this too. This particular zval can also be set, so
 * theres no guarantee that it's NULL, that its refcount is 1, or that
 * is_ref is 0. So it needs to be treated carefully. */


// Some common functions
#include "php.h"

/*
 * The runtime needs its own initialization and finalization
 * phc is responsible for calling these functions
 */

void
init_runtime ()
{
}

void
finalize_runtime ()
{
}

/* Make a copy of *P_ZVP, storing it in *P_ZVP. */
static zval*
zvp_clone_ex (zval * zvp)
{
  // TODO: use INIT_PZVAL_COPY
  zval *clone;
  MAKE_STD_ZVAL (clone);
  clone->value = zvp->value;
  clone->type = zvp->type;
  zval_copy_ctor (clone);
  return clone;
}

static inline int
in_copy_on_write (zval * zvp)
{
  return (zvp->refcount > 1 && !zvp->is_ref);
}

static inline int
in_change_on_write (zval * zvp)
{
  return (zvp->refcount > 1 && zvp->is_ref);
}

/* If *P_ZVP is in a copy-on-write set, separate it by overwriting
 * *P_ZVP with a clone of itself, and lowering the refcount on the
 * original. */
static void
sep_copy_on_write_ex (zval ** p_zvp)
{
  if (!in_copy_on_write (*p_zvp))
    return;

  zval *old = *p_zvp;

  *p_zvp = zvp_clone_ex (*p_zvp);

  zval_ptr_dtor (&old);
}

/* If *P_ZVP is in a copy-on-write set, separate it by overwriting
 * *P_ZVP with a clone of itself, and lowering the refcount on the
 * original. */
static void
sep_change_on_write (zval ** p_zvp)
{
  assert (in_change_on_write (*p_zvp));

  zval *old = *p_zvp;

  *p_zvp = zvp_clone_ex (*p_zvp);

  zval_ptr_dtor (&old);
}


static zval *
read_string_index (zval * var, zval * ind TSRMLS_DC)
{
  // This must always allocate memory, since we cant return the
  // passed string.
  assert (Z_TYPE_P (var) == IS_STRING);
  long index;
  switch (Z_TYPE_P (ind))
    {
    case IS_DOUBLE:
      index = (long) Z_DVAL_P (ind);
      break;

    case IS_LONG:
    case IS_BOOL:
      index = Z_LVAL_P (ind);
      break;

    default:
      php_error_docref (NULL TSRMLS_CC, E_WARNING, "Illegal offset type");

    case IS_NULL:
      index = 0;
      break;
    }

  zval *result;
  ALLOC_INIT_ZVAL (result);

  if (index >= Z_STRLEN_P (var))
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

// Extract the hashtable from a hash-valued zval
static HashTable *
extract_ht_ex (zval * arr TSRMLS_DC)
{
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
  sep_copy_on_write_ex (p_var);

  return extract_ht_ex (*p_var TSRMLS_CC);
}

/* Assign RHS into LHS, by reference. After this, LHS will point to the same
 * zval* as RHS. */
static void
copy_into_ref (zval ** lhs, zval ** rhs)
{
  sep_copy_on_write_ex (rhs);

  (*rhs)->is_ref = 1;
  (*rhs)->refcount++;
  zval_ptr_dtor (lhs);
  *lhs = *rhs;
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

static void
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
	  printf ("%s", key);
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
static void
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


/* Make a copy of *P_ZVP and store it in *P_ZVP. If *IS_ZVP_NEW is
 * set, call the destructor on *P_ZVP before copying. *IS_ZVP_NEW is
 * set to true. */
static void
zvp_clone (zval ** p_zvp, int *is_zvp_new)
{
  zval *old = *p_zvp;

  *p_zvp = zvp_clone_ex (*p_zvp);

  if (*is_zvp_new)
    zval_ptr_dtor (&old);
  *is_zvp_new = 1;
}


// Overwrite one zval with another
static void
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

// Overwrite one zval with another
static void
overwrite_lhs_no_copy (zval * lhs, zval * rhs)
{
  // First, call the destructor to remove any data structures
  // associated with lhs that will now be overwritten
  zval_dtor (lhs);
  // Overwrite LHS
  lhs->value = rhs->value;
  lhs->type = rhs->type;
}

// TODO dont overwrite line numbers if we're compiling an extension
static void
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


/* Assuming that p_zvp points into a hashtable, we decrease the
 * refcount of the currently pointed to object, then clone it, and
 * insert it into the hashtable */
// TODO Separation writes into the array, which automatically calls
// the zval_ptr_dtor. However, if the array doesnt have a registered
// destructor, then we shouldnt be calling this.
//
static void
sep_copy_on_write (zval ** p_zvp, int *is_zvp_new)
{
  if (!in_copy_on_write (*p_zvp))
    return;

  zvp_clone (p_zvp, is_zvp_new);
}

/* We're trying to get rid of is_rhs_new */
static void
write_var_TODO (zval ** p_lhs, zval ** p_rhs, int *is_rhs_new)
{
  if (!(*p_lhs)->is_ref)
    {
      if ((*p_rhs)->is_ref)
	{
	  zvp_clone (p_rhs, is_rhs_new);
	}

      (*p_rhs)->refcount++;

      zval_ptr_dtor (p_lhs);
      *p_lhs = *p_rhs;
    }
  else
    {
      overwrite_lhs (*p_lhs, *p_rhs);
    }
}
/* Write P_RHS into the symbol table as a variable named VAR_NAME. */
// NOTE: We do not alter p_rhs's refcount, unless p_lhs joins its
// Copy-on-write set.
static void
write_var (zval ** p_lhs, zval ** p_rhs)
{
  if (!(*p_lhs)->is_ref)
    {
      zval_ptr_dtor (p_lhs);
      // Take a copy of RHS for LHS.
      if ((*p_rhs)->is_ref)
	{
	  *p_lhs = zvp_clone_ex (*p_rhs);
	}
      else // share a copy
	{
	  (*p_rhs)->refcount++;
	  *p_lhs = *p_rhs;
	}
    }
  else
    {
      overwrite_lhs (*p_lhs, *p_rhs);
    }
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
      else
	{
	  zval_ptr_dtor (p_var);
	  ALLOC_INIT_ZVAL (*p_var);
	  array_init (*p_var);
	}
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
  EG (uninitialized_zval_ptr)->refcount++;
  ht_update (ht, ind, EG (uninitialized_zval_ptr), &data);

  assert (data != NULL);

  return data;
}

static zval **
get_st_entry (HashTable * st, char *name, int length, ulong hashval TSRMLS_DC)
{
  zval **p_zvp;
  if (zend_hash_quick_find
      (st, name, length, hashval, (void **) &p_zvp) == SUCCESS)
    {
      assert (p_zvp != NULL);
      return p_zvp;
    }

  // If we dont find it, put EG (uninitialized_zval_ptr) into the
  // hashtable, and return a pointer to its container.
  EG (uninitialized_zval_ptr)->refcount++;
  int result = zend_hash_quick_add (st, name, length, hashval,
				    &EG (uninitialized_zval_ptr),
				    sizeof (zval *), (void **) &p_zvp);
  assert (result == SUCCESS);
  assert (p_zvp != NULL);

  return p_zvp;
}

/* Read the variable named VAR_NAME from the local symbol table and
 * return it. If the variable doent exist, a new one is created and
 * *IS_NEW is set.  */
static zval *
read_var (HashTable * st, char *name, int length, ulong hashval TSRMLS_DC)
{
  zval **p_zvp;
  if (zend_hash_quick_find
      (st, name, length, hashval, (void **) &p_zvp) == SUCCESS)
    return *p_zvp;

  return EG (uninitialized_zval_ptr);
}

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
get_var_var (HashTable * st, zval * var_var, int update_st, int* is_new TSRMLS_DC)
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
	  // My theory is that since we add it to the hashtable, we dont need to mark it is_new.
//          *is_new = 1;
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
  return get_var_var (st, var_var, 0, NULL TSRMLS_CC);
}

void
read_array (zval ** result, zval * var, zval * ind,
	    int *is_result_new TSRMLS_DC)
{
  // Memory can be allocated in read_string_index
  if (var == EG (uninitialized_zval_ptr))
    {
      *result = var;
      return;
    }

  if (Z_TYPE_P (var) != IS_ARRAY)
    {
      if (Z_TYPE_P (var) == IS_STRING)
	{
	  *is_result_new = 1;
	  *result = read_string_index (var, ind TSRMLS_CC);
	  return;
	}
      *result = EG (uninitialized_zval_ptr);
      return;
    }


  // Since we know its an array, and we dont write to it, we dont need
  // to separate it.
  HashTable *ht = Z_ARRVAL_P (var);

  // find the result
  zval **p_result;
  if (ht_find (ht, ind, &p_result) == SUCCESS)
    {
      *result = *p_result;
      return;
    }

  *result = EG (uninitialized_zval_ptr);
}

void
read_var_array (HashTable * st, zval ** result, zval * refl,
		zval * ind TSRMLS_DC)
{
  // TODO add an is_x_new parameter
  zval **p_var = read_var_var (st, refl TSRMLS_CC);
  read_array (result, *p_var, ind, NULL TSRMLS_CC);
}

/* Push EG (uninitialized_zval_ptr) and return a pointer into the ht
 * for it */
static zval **
push_and_index_ht (zval ** p_var TSRMLS_DC)
{
  if (Z_TYPE_P (*p_var) == IS_STRING)
    {
      if (Z_STRLEN_PP (p_var) > 0)
	{
	  php_error_docref (NULL TSRMLS_CC, E_ERROR,
			    "[] operator not supported for strings");
	}
      else
	{
	  zval_ptr_dtor (p_var);
	  ALLOC_INIT_ZVAL (*p_var);
	  array_init (*p_var);
	}
    }

  if (Z_TYPE_P (*p_var) == IS_BOOL && Z_BVAL_PP (p_var))
    {
      php_error_docref (NULL TSRMLS_CC, E_WARNING,
			"Cannot use a scalar value as an array");
      return NULL;
    }

  // if its not an array, make it an array
  HashTable *ht = extract_ht (p_var TSRMLS_CC);
  zval **data;

  EG (uninitialized_zval_ptr)->refcount++;
  int result = zend_hash_next_index_insert (ht, &EG (uninitialized_zval_ptr),
					    sizeof (zval *), (void **) &data);
  assert (result == SUCCESS);

  assert (data);

  return data;
}


static zval **
fetch_var_arg_by_ref (zval ** p_arg)
{
  // We are passing by reference
  sep_copy_on_write_ex (p_arg);

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
static zval *
fetch_var_arg (zval * arg, int *is_arg_new)
{
  if (arg->is_ref)
    {
      // We dont separate since we don't own one of ARG's references.
      zvp_clone (&arg, is_arg_new);

      // It seems we get incorrect refcounts without this.
      // TODO This decreases the refcount to zero, which seems wrong,
      // but gives the right answer. We should look at how zend does
      // this.

      arg->refcount--;
    }
  return arg;
}

static void
cast_var (zval ** p_zvp, int type)
{
  assert (type >= 0 && type <= 6);
  if ((*p_zvp)->type == type)
    return;

  sep_copy_on_write_ex (p_zvp);
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
    default:
      assert (0);		// TODO unimplemented
      break;
    }
}

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
      assert (ind->refcount == 1);
      zval_ptr_dtor (&ind);
      return result;
    }

  // NO error required; return false
  if (Z_TYPE_P (*p_var) != IS_ARRAY)
    return 0;

  // if its not an array, make it an array
  HashTable *ht = Z_ARRVAL_P (*p_var);

  zval** data;
  if (ht_find (ht, ind, &data) == SUCCESS)
  {
    return !ZVAL_IS_NULL(*data);
  }
  else
    return 0;
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
  if (Z_TYPE_P (*p_var) == IS_STRING)
    {
      php_error_docref (NULL TSRMLS_CC, E_ERROR,
			"Cannot unset string offsets");
    }

  // NO error required
  if (Z_TYPE_P (*p_var) != IS_ARRAY)
    return;

  // if its not an array, make it an array
  HashTable *ht = Z_ARRVAL_P (*p_var);

  ht_delete (ht, ind);
}

/* Copies a constant into ZVP. Note that LENGTH does not include the NULL-terminating byte. */
static void
get_constant (char *name, int length, zval ** p_zvp TSRMLS_DC)
{
  MAKE_STD_ZVAL (*p_zvp);
  // zend_get_constant returns 1 for success, not SUCCESS
  int result = zend_get_constant (name, length, *p_zvp TSRMLS_CC);
  if (result == 0)
    ZVAL_STRINGL (*p_zvp, name, length, 1);
}

/* If assertions are off, this should be inlined to nothing */
static void
phc_check_invariants (TSRMLS_D)
{
  assert (EG (uninitialized_zval_ptr) == &EG (uninitialized_zval));
  assert (EG (uninitialized_zval).refcount >= 1);
  assert (EG (uninitialized_zval).value.lval == 0);
  assert (EG (uninitialized_zval).type == IS_NULL);
  assert (EG (uninitialized_zval).is_ref == 0);
}

static void
initialize_function_call (zend_fcall_info * fci, zend_fcall_info_cache * fcic,
			  char *function_name, char *filename,
			  int line_number TSRMLS_DC)
{
  if (!fcic->initialized)	// check for missing function
    {
      zval fn;
      INIT_PZVAL (&fn);
      ZVAL_STRING (&fn, function_name, 0);
      int result = zend_fcall_info_init (&fn, fci, fcic TSRMLS_CC);
      if (result != SUCCESS)
	{
	  phc_setup_error (1, filename, line_number, NULL TSRMLS_CC);
	  php_error_docref (NULL TSRMLS_CC, E_ERROR,
			    "Call to undefined function %s()", function_name);
	}
    }
}
