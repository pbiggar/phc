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
static void
zvp_clone_ex (zval ** p_zvp)
{
  zval *clone;
  MAKE_STD_ZVAL (clone);
  clone->value = (*p_zvp)->value;
  clone->type = (*p_zvp)->type;
  zval_copy_ctor (clone);
  *p_zvp = clone;
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

  zvp_clone_ex (p_zvp);

  zval_ptr_dtor (&old);
}

/* If *P_ZVP is in a copy-on-write set, separate it by overwriting
 * *P_ZVP with a clone of itself, and lowering the refcount on the
 * original. */
static void
sep_change_on_write (zval ** p_zvp)
{
  if (!in_change_on_write (*p_zvp))
    return;

  zval *old = *p_zvp;

  zvp_clone_ex (p_zvp);

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
  int result;
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
  int result;
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

  zvp_clone_ex (p_zvp);

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


/* Write P_RHS into the symbol table as a variable named VAR_NAME */
static void
write_var (zval ** p_lhs, zval ** p_rhs, int *is_rhs_new TSRMLS_DC)
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
get_var_var (HashTable * st, zval * var_var, int update_st,
	     int *is_new TSRMLS_DC)
{
  zval *string_index;
  int index_found, deallocate_string_index = 0;

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
  index_found = zend_hash_find (st, Z_STRVAL_P (string_index),
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
	  *is_new = 1;
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
isset_array (zval ** p_var, zval * ind TSRMLS_DC)
{
  if (Z_TYPE_P (*p_var) == IS_STRING)
    {
      zvp_clone_ex (&ind);
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

  zval **data;
  if (ht_find (ht, ind, &data) == SUCCESS)
    {
      return !ZVAL_IS_NULL (*data);
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

static void
phc_builtin_eval (zval * arg, zval * result, char *filename TSRMLS_DC)
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
phc_builtin_exit (zval * arg, zval * result, char *filename TSRMLS_DC)
{
  if (Z_TYPE_P (arg) == IS_LONG)
    EG (exit_status) = Z_LVAL_P (arg);
  else
    zend_print_variable (arg);

  zend_bailout ();
}

static void
phc_builtin_die (zval * arg, zval * result, char *filename TSRMLS_DC)
{
  phc_builtin_exit (arg, result, filename TSRMLS_CC);
}

static void
phc_builtin_echo (zval * arg, zval * result TSRMLS_DC)
{
  zend_print_variable (arg);
}

static void
phc_builtin_print (zval * arg, zval * result, char *filename TSRMLS_DC)
{
  phc_builtin_echo (arg, result TSRMLS_CC);

  if (result)
    ZVAL_LONG (result, 1);
}

// TODO is there a memory leak here is result has a value?
// TOOD isnt this just the same as isset
static void
phc_builtin_empty (zval * arg, zval * result, char *filename TSRMLS_DC)
{
  ZVAL_BOOL (result, !zend_is_true (arg));
}

static void
phc_builtin_include (zval * arg, zval * result, char *filename TSRMLS_DC)
{
  // TODO: php_execute_script does some additional work which we need to
  // emulate. However, we cant call it directly. And why not?

  // TODO: we expect a string, but it could be anything.
  // TODO: the file might not exist.
  //

  // In the event that the Zend engine cannot find the file, after checking the
  // include path, it tries the current directory. It does this only if the
  // interpreter is executing, and it checks the interpreters opcodes for a
  // filename (see streams/plain_wrapper.c:1352)

  // TODO since PHP does this hack all over the place, do we need to pretend
  // the entire program is executing?

  // An alternative is to add the directory to include_path, but its
  // semantically incorrect (get_included_path() would give the wrong answer),
  // and error prone (if people overwrite include_path).

  assert (EG (in_execution) == 0);
  assert (EG (active_op_array) == NULL);
  assert (filename != NULL);

  // Check we have a string
  if (Z_TYPE_P (arg) != IS_STRING)
    {
      zvp_clone_ex (&arg);
      convert_to_string (arg);
    }

  // Pretend the interpreter is running
  EG (in_execution) = 1;
  zend_op_array ops;
  ops.filename = filename;
  EG (active_op_array) = &ops;

  // Open the file
  zend_file_handle handle;
  int success = zend_stream_open (Z_STRVAL_P (arg), &handle TSRMLS_CC);

  // Stop pretending
  EG (in_execution) = 0;
  EG (active_op_array) = NULL;

  if (success == SUCCESS)
    {
      // run it
      success =
	zend_execute_scripts (ZEND_INCLUDE TSRMLS_CC, &result, 1, &handle);
      assert (success == SUCCESS);
      zend_stream_close (&handle);
    }
  else
    {
      php_error_docref ("function.include" TSRMLS_CC, E_WARNING,
			"Failed opening '%s' for inclusion (include_path='%s')",
			php_strip_url_passwd (Z_STRVAL_P (arg)),
			STR_PRINT (PG (include_path)));
    }



  //TODO 
  // What happens in zend_vm_def.h, in the include's handler function:

/*  if (is_once_variety)
    {
      if (is_absolutepath (arg))
	failure = !path_ok (arg) || zend_hash_exists (EG(included_files))

      if (failure)
	; // do nothing
      else if (file_open(arg) == success)
	 compile_file
	 zend_hash_add_empty_element (EG(included_files), arg)
      else
	 error
      }
  else
    compile_file
*/
}

zval *phc_const_pool_int_0;
zval *phc_const_pool_int_1;
static zend_fcall_info hallo_fci;
static zend_fcall_info_cache hallo_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_0;
static zend_fcall_info hallo2_fci;
static zend_fcall_info_cache hallo2_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_int_2;
zval *phc_const_pool_int_3;
zval *phc_const_pool_real_0;
zval *phc_const_pool_real_1;
zval *phc_const_pool_int_4;
zval *phc_const_pool_int_5;
zval *phc_const_pool_real_2;
zval *phc_const_pool_int_6;
zval *phc_const_pool_int_7;
zval *phc_const_pool_int_8;
zval *phc_const_pool_string_1;
zval *phc_const_pool_string_2;
zval *phc_const_pool_string_3;
static zend_fcall_info flush_fci;
static zend_fcall_info_cache flush_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_4;
zval *phc_const_pool_int_9;
static zend_fcall_info printf_fci;
static zend_fcall_info_cache printf_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_5;
zval *phc_const_pool_real_3;
zval *phc_const_pool_real_4;
zval *phc_const_pool_real_5;
zval *phc_const_pool_int_10;
zval *phc_const_pool_int_11;
zval *phc_const_pool_int_12;
zval *phc_const_pool_int_13;
static zend_fcall_info Ack_fci;
static zend_fcall_info_cache Ack_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_int_14;
zval *phc_const_pool_string_6;
zval *phc_const_pool_string_7;
zval *phc_const_pool_string_8;
zval *phc_const_pool_string_9;
static zend_fcall_info fibo_r_fci;
static zend_fcall_info_cache fibo_r_fcic = { 0, NULL, NULL, NULL };

static zend_fcall_info dechex_fci;
static zend_fcall_info_cache dechex_fcic = { 0, NULL, NULL, NULL };

static zend_fcall_info is_array_fci;
static zend_fcall_info_cache is_array_fcic = { 0, NULL, NULL, NULL };

static zend_fcall_info trigger_error_fci;
static zend_fcall_info_cache trigger_error_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_10;
zval *phc_const_pool_int_15;
zval *phc_const_pool_string_11;
zval *phc_const_pool_string_12;
zval *phc_const_pool_null_0;
static zend_fcall_info define_fci;
static zend_fcall_info_cache define_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_13;
zval *phc_const_pool_int_16;
zval *phc_const_pool_string_14;
zval *phc_const_pool_int_17;
zval *phc_const_pool_string_15;
zval *phc_const_pool_int_18;
zval *phc_const_pool_int_19;
static zend_fcall_info heapsort_r_fci;
static zend_fcall_info_cache heapsort_r_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_16;
static zend_fcall_info gen_random_fci;
static zend_fcall_info_cache gen_random_fcic = { 0, NULL, NULL, NULL };

static zend_fcall_info mkmatrix_fci;
static zend_fcall_info_cache mkmatrix_fcic = { 0, NULL, NULL, NULL };

static zend_fcall_info mmult_fci;
static zend_fcall_info_cache mmult_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_int_20;
static zend_fcall_info range_fci;
static zend_fcall_info_cache range_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_int_21;
zval *phc_const_pool_int_22;
zval *phc_const_pool_string_17;
static zend_fcall_info strlen_fci;
static zend_fcall_info_cache strlen_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_18;
static zend_fcall_info gettimeofday_fci;
static zend_fcall_info_cache gettimeofday_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_19;
zval *phc_const_pool_string_20;
static zend_fcall_info ob_start_fci;
static zend_fcall_info_cache ob_start_fcic = { 0, NULL, NULL, NULL };

static zend_fcall_info getmicrotime_fci;
static zend_fcall_info_cache getmicrotime_fcic = { 0, NULL, NULL, NULL };

static zend_fcall_info ob_end_clean_fci;
static zend_fcall_info_cache ob_end_clean_fcic = { 0, NULL, NULL, NULL };

static zend_fcall_info number_format_fci;
static zend_fcall_info_cache number_format_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_int_23;
static zend_fcall_info str_repeat_fci;
static zend_fcall_info_cache str_repeat_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_21;
zval *phc_const_pool_int_24;
zval *phc_const_pool_string_22;
static zend_fcall_info date_default_timezone_set_fci;
static zend_fcall_info_cache date_default_timezone_set_fcic =
  { 0, NULL, NULL, NULL };
zval *phc_const_pool_string_23;
static zend_fcall_info start_test_fci;
static zend_fcall_info_cache start_test_fcic = { 0, NULL, NULL, NULL };

static zend_fcall_info simple_fci;
static zend_fcall_info_cache simple_fcic = { 0, NULL, NULL, NULL };

static zend_fcall_info end_test_fci;
static zend_fcall_info_cache end_test_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_24;
static zend_fcall_info simplecall_fci;
static zend_fcall_info_cache simplecall_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_25;
static zend_fcall_info simpleucall_fci;
static zend_fcall_info_cache simpleucall_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_26;
static zend_fcall_info simpleudcall_fci;
static zend_fcall_info_cache simpleudcall_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_27;
static zend_fcall_info mandel_fci;
static zend_fcall_info_cache mandel_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_28;
static zend_fcall_info mandel2_fci;
static zend_fcall_info_cache mandel2_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_29;
static zend_fcall_info ackermann_fci;
static zend_fcall_info_cache ackermann_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_int_25;
zval *phc_const_pool_string_30;
static zend_fcall_info ary_fci;
static zend_fcall_info_cache ary_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_int_26;
zval *phc_const_pool_string_31;
static zend_fcall_info ary2_fci;
static zend_fcall_info_cache ary2_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_32;
static zend_fcall_info ary3_fci;
static zend_fcall_info_cache ary3_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_int_27;
zval *phc_const_pool_string_33;
static zend_fcall_info fibo_fci;
static zend_fcall_info_cache fibo_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_34;
static zend_fcall_info hash1_fci;
static zend_fcall_info_cache hash1_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_35;
static zend_fcall_info hash2_fci;
static zend_fcall_info_cache hash2_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_int_28;
zval *phc_const_pool_string_36;
static zend_fcall_info heapsort_fci;
static zend_fcall_info_cache heapsort_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_int_29;
zval *phc_const_pool_string_37;
static zend_fcall_info matrix_fci;
static zend_fcall_info_cache matrix_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_int_30;
zval *phc_const_pool_string_38;
static zend_fcall_info nestedloop_fci;
static zend_fcall_info_cache nestedloop_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_39;
static zend_fcall_info sieve_fci;
static zend_fcall_info_cache sieve_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_string_40;
static zend_fcall_info strcat_fci;
static zend_fcall_info_cache strcat_fcic = { 0, NULL, NULL, NULL };

zval *phc_const_pool_int_31;
zval *phc_const_pool_string_41;
static zend_fcall_info total_fci;
static zend_fcall_info_cache total_fcic = { 0, NULL, NULL, NULL };


// function mandel()
// {
// \011$y = 0;
// \011L836:
// \011$TLE63 = ($y <= 50);
// \011if (TLE63) goto L838 else goto L833;
// \011L838:
// \011$TLE64 = ($y - 12);
// \011$TLE65 = (0.027999999999999997113 * $TLE64);
// \011$imc = ($TLE65 + 0.0);
// \011$x = 0;
// \011L843:
// \011$TLE67 = ($x <= 150);
// \011if (TLE67) goto L845 else goto L872;
// \011L845:
// \011$TLE68 = ($x - 40);
// \011$TLE69 = (0.027999999999999997113 * $TLE68);
// \011$rec = ($TLE69 + -0.4500000000000000111);
// \011$re = $rec;
// \011$im = $imc;
// \011$color = 1000;
// \011$re2 = ($re * $re);
// \011$im2 = ($im * $im);
// \011L853:
// \011$TLE70 = ($re2 + $im2);
// \011$TLE35 = ($TLE70 < 1000000);
// \011if (TLE35) goto L856 else goto L857;
// \011L857:
// \011$TEF36 = $TLE35;
// \011L858:
// \011$TLE73 = (bool) $TEF36;
// \011if (TLE73) goto L860 else goto L868;
// \011L860:
// \011$TLE75 = ($re * $im);
// \011$TLE77 = ($TLE75 * 2);
// \011$im = ($TLE77 + $imc);
// \011$TLE78 = ($re2 - $im2);
// \011$re = ($TLE78 + $rec);
// \011$re2 = ($re * $re);
// \011$im2 = ($im * $im);
// \011$color = ($color - 1);
// \011goto L853;
// \011L868:
// \011$TLE81 = ($color == 0);
// \011if (TLE81) goto L870 else goto L871;
// \011L870:
// \011print('_');
// \011L842:
// \011$x = ($x + 1);
// \011goto L843;
// \011L871:
// \011print('#');
// \011goto L842;
// \011L856:
// \011$TEF36 = ($color > 0);
// \011goto L858;
// \011L872:
// \011print('<br>');
// \011flush();
// \011$y = ($y + 1);
// \011goto L836;
// \011L833:
// }
PHP_FUNCTION (mandel)
{
// Function body
// $y = 0;
   int y = 0;
// L836:
L836:;
// $TLE63 = ($y <= 50);
  int TLE63 = y <= 50;
  
// if (TLE63) goto L838 else goto L833;
    if (TLE63)
      goto L838;
    else
      goto L833;
// L838:
L838:;
// $TLE64 = ($y - 12);
  int TLE64 = y - 12;
  
// $TLE65 = (0.027999999999999997113 * $TLE64);
  double TLE65 = (0.027999999999999997113 * TLE64);
// $imc = ($TLE65 + 0.0);
  double imc = TLE65 = 0.0;
// $x = 0;
  int x = 0;
// L843:
L843:;
// $TLE67 = ($x <= 150);
  int TLE67 = x <= 150;
  
// if (TLE67) goto L845 else goto L872;
    if (TLE67)
      goto L845;
    else
      goto L872;
// L845:
L845:;
// $TLE68 = ($x - 40);
  int TLE68 = x - 40;
// $TLE69 = (0.027999999999999997113 * $TLE68);
  int TLE69 = (0.027999999999999997113 * TLE68);
// $rec = ($TLE69 + -0.4500000000000000111);
  double rec = (TLE69 + -0.4500000000000000111);
  
// $re = $rec;
  double re = rec;
  
// $im = $imc;
  double im = imc;
  
// $color = 1000;
  int color = 1000;
// $re2 = ($re * $re);
  double re2 = re * re;
  
// $im2 = ($im * $im);
  double im2 = im * im;
// L853:
L853:;
// $TLE70 = ($re2 + $im2);
  double TLE70 = re2 + im2;
// $TLE35 = ($TLE70 < 1000000);
  int TLE35 = TLE70 < 1000000;
// if (TLE35) goto L856 else goto L857;
    if (TLE35)
      goto L856;
    else
      goto L857;
// L857:
L857:;
// $TEF36 = $TLE35;
  int TEF36 = TLE35;
// L858:
L858:;
// $TLE73 = (bool) $TEF36;
  int TLE73 = TEF36;
// if (TLE73) goto L860 else goto L868;
    if (TLE73)
      goto L860;
    else
      goto L868;
// L860:
L860:;
// $TLE75 = ($re * $im);
  double TLE75 = re * im;
  
// $TLE77 = ($TLE75 * 2);
  double TLE77 = TLE75 * 2;
// $im = ($TLE77 + $imc);
  im = TLE77 * imc;
// $TLE78 = ($re2 - $im2);
  double TLE78 = re2 - im2;
// $re = ($TLE78 + $rec);
  re = TLE78 + rec;
  
// $re2 = ($re * $re);
  re2 = re * re;
  
// $im2 = ($im * $im);
  im2 = im * im;
// $color = ($color - 1);
  color = color - 1;
// goto L853;
    goto L853;
// L868:
L868:;
  int TLE81 = color == 0;
// $TLE81 = ($color == 0);
  
// if (TLE81) goto L870 else goto L871;
    if (TLE81)
      goto L870;
    else
      goto L871;
// L870:
L870:;
// print('_');
  {
    zval *p_arg = phc_const_pool_string_1;
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
  }
// L842:
L842:;
// $x = ($x + 1);
  x = x + 1;
// goto L843;
    goto L843;
// L871:
L871:;
// print('#');
  {
    zval *p_arg = phc_const_pool_string_2;
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
  }
// goto L842;
    goto L842;
// L856:
L856:;
// $TEF36 = ($color > 0);
  TEF36 = color > 0;
// goto L858;
    goto L858;
// L872:
L872:;
// print('<br>');
  {
    zval *p_arg = phc_const_pool_string_3;
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
  }
// flush();
  {
    initialize_function_call (&flush_fci, &flush_fcic, "flush",
			      "test/subjects/benchmarks/zend/bench.php",
			      77 TSRMLS_CC);
    zend_function *signature = flush_fcic.function_handler;
    zval **args_ind[0];
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = flush_fci.param_count;
    zval ***params_save = flush_fci.params;
    zval **retval_save = flush_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    flush_fci.params = args_ind;
    flush_fci.param_count = 0;
    flush_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&flush_fci, &flush_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    flush_fci.params = params_save;
    flush_fci.param_count = param_count_save;
    flush_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $y = ($y + 1);
    y = y + 1;
// goto L836;
  {
    goto L836;
  }
// L833:
L833:;
// Method exit
}

// function mandel2()
// {
// \011$b = ' .:,;!/>)|&IH%*#';
// \011$y = 30;
// \011L878:
// \011printf('
// ');
// \011$TLE87 = ($y * 0.10000000000000000555);
// \011$C = ($TLE87 - 1.5);
// \011$TS40 = $y;
// \011--$y;
// \011if (TS40) goto L884 else goto L875;
// \011L884:
// \011$x = 0;
// \011L885:
// \011$TLE90 = ($x * 0.040000000000000000833);
// \011$c = ($TLE90 - 2);
// \011$z = 0;
// \011$Z = 0;
// \011$TS41 = $x;
// \011++$x;
// \011$TLE93 = ($TS41 < 75);
// \011if (TLE93) goto L893 else goto L878;
// \011L893:
// \011$r = $c;
// \011$i = $C;
// \011$k = 0;
// \011L897:
// \011$TLE94 = ($z * $z);
// \011$TLE95 = ($Z * $Z);
// \011$TLE96 = ($TLE94 - $TLE95);
// \011$t = ($TLE96 + $r);
// \011$TLE98 = (2 * $z);
// \011$TLE99 = ($TLE98 * $Z);
// \011$Z = ($TLE99 + $i);
// \011$z = $t;
// \011$TLE101 = ($k < 5000);
// \011if (TLE101) goto L907 else goto L912;
// \011L907:
// \011$TLE102 = ($z * $z);
// \011$TLE103 = ($Z * $Z);
// \011$TLE104 = ($TLE102 + $TLE103);
// \011$TLE106 = ($TLE104 > 500000);
// \011if (TLE106) goto L912 else goto L896;
// \011L896:
// \011++$k;
// \011goto L897;
// \011L912:
// \011$TLE108 = ($k % 16);
// \011$TMIi438 = $b[$TLE108];
// \011print($TMIi438);
// \011goto L885;
// \011L875:
// }
PHP_FUNCTION (mandel2)
{
// Function body
// $b = ' .:,;!/>)|&IH%*#';
 char* b = " .:,;!/>)|&IH%*#";
// $y = 30;
 int y = 30;
// L878:
L878:;
// printf('
// ');
  {
    initialize_function_call (&printf_fci, &printf_fcic, "printf",
			      "test/subjects/benchmarks/zend/bench.php",
			      86 TSRMLS_CC);
    zend_function *signature = printf_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_string_5;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = printf_fci.param_count;
    zval ***params_save = printf_fci.params;
    zval **retval_save = printf_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    printf_fci.params = args_ind;
    printf_fci.param_count = 1;
    printf_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&printf_fci, &printf_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    printf_fci.params = params_save;
    printf_fci.param_count = param_count_save;
    printf_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE87 = ($y * 0.10000000000000000555);
  double TLE87 = y * 0.1;
  
// $C = ($TLE87 - 1.5);
  double C = TLE87 - 1.5;
  
// $TS40 = $y;
 int TS40 = y;
// --$y;
  --y;
  
// if (TS40) goto L884 else goto L875;

    if (TS40)
      goto L884;
    else
      goto L875;
// L884:
L884:;
// $x = 0;
  int x = 0;
// L885:
L885:;
// $TLE90 = ($x * 0.040000000000000000833);
  double TLE90 = x * 0.4;
// $c = ($TLE90 - 2);
  double c = TLE90 - 2;
  
// $z = 0;
  int z = 0;
// $Z = 0;
 int Z = 0;
// $TS41 = $x;
 int TS41 = x;
// ++$x;
 ++x;
// $TLE93 = ($TS41 < 75);
 int TLE93 = TS41 < 75;
// if (TLE93) goto L893 else goto L878;
    if (TLE93)
      goto L893;
    else
      goto L878;
// L893:
L893:;
// $r = $c;
  double r = c;
// $i = $C;
  double i = C;
// $k = 0;
  int k = 0;
// L897:
L897:;
// $TLE94 = ($z * $z);
  double TLE94 = z * z;
// $TLE95 = ($Z * $Z);
   double TLE95 = (Z * Z);
  
// $TLE96 = ($TLE94 - $TLE95);
  double TLE96 = (TLE94 - TLE95);
  
// $t = ($TLE96 + $r);
  double t = (TLE96 + r);
  
// $TLE98 = (2 * $z);
  double TLE98 = (2 * z);
  
// $TLE99 = ($TLE98 * $Z);
  double TLE99 = (TLE98 * Z);
  
// $Z = ($TLE99 + $i);
  Z = (TLE99 + i);
  
// $z = $t;
  z = t;
// $TLE101 = ($k < 5000);
  int TLE101 = (k < 5000);
  
// if (TLE101) goto L907 else goto L912;

    if (TLE101)
      goto L907;
    else
      goto L912;
// L907:
L907:;
// $TLE102 = ($z * $z);
    double TLE102 = (z * z);
  
// $TLE103 = ($Z * $Z);
    double TLE103 = (Z * Z);
  
// $TLE104 = ($TLE102 + $TLE103);
   double  TLE104 = (TLE102 + TLE103);
  
// $TLE106 = ($TLE104 > 500000);
   int TLE106 = (TLE104 > 500000);
  
// if (TLE106) goto L912 else goto L896;
    if (TLE106)
      goto L912;
    else
      goto L896;
// L896:
L896:;
// ++$k;
     ++k;
  
// goto L897;
  {
    goto L897;
    phc_check_invariants (TSRMLS_C);
  }
// L912:
L912:;
// $TLE108 = ($k % 16);
    int TLE108 = (k % 16);
  
// $TMIi438 = $b[$TLE108];
   char TMIi438[2];
   TMIi438[0] = b[TLE108];
   TMIi438[1] = '\0';

// print($TMIi438);
  {
    zval arg;
    INIT_ZVAL (arg);
    ZVAL_STRING (&arg, TMIi438, 2);
zval*	p_arg = &arg;
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// goto L885;
  {
    goto L885;
    phc_check_invariants (TSRMLS_C);
  }
// L875:
L875:;
// Method exit
end_of_function:__attribute__ ((unused));
}

// function Ack($m, $n)
// {
// \011$TLE110 = ($m == 0);
// \011if (TLE110) goto L919 else goto L921;
// \011L919:
// \011$TLE112 = ($n + 1);
// \011return $TLE112;
// \011goto L916;
// \011L921:
// \011$TLE114 = ($n == 0);
// \011if (TLE114) goto L923 else goto L926;
// \011L923:
// \011$TLE116 = ($m - 1);
// \011$TLE118 = Ack($TLE116, 1);
// \011return $TLE118;
// \011goto L916;
// \011L926:
// \011$TLE120 = ($m - 1);
// \011$TLE122 = ($n - 1);
// \011$TLE123 = Ack($m, $TLE122);
// \011$TLE124 = Ack($TLE120, $TLE123);
// \011return $TLE124;
// \011L916:
// }
PHP_FUNCTION (Ack)
{
  zval *local_TLE110 = NULL;
  zval *local_TLE112 = NULL;
  zval *local_TLE114 = NULL;
  zval *local_TLE116 = NULL;
  zval *local_TLE118 = NULL;
  zval *local_TLE120 = NULL;
  zval *local_TLE122 = NULL;
  zval *local_TLE123 = NULL;
  zval *local_TLE124 = NULL;
  zval *local_m = NULL;
  zval *local_n = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[2];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_m = params[0];
// param 1
    params[1]->refcount++;
    local_n = params[1];
  }
   int m = Z_LVAL_P (local_m);
   int n = Z_LVAL_P (local_n);
// Function body
// $TLE110 = ($m == 0);
   int TLE110 = (m == 0);
  
// if (TLE110) goto L919 else goto L921;

    if (TLE110)
      goto L919;
    else
      goto L921;
// L919:
L919:;
// $TLE112 = ($n + 1);
     int TLE112 = (n + 1);
  
// return $TLE112;

      RETVAL_LONG (TLE112);
    goto end_of_function;
    phc_check_invariants (TSRMLS_C);
// goto L916;
  {
    goto L916;
    phc_check_invariants (TSRMLS_C);
  }
// L921:
L921:;
// $TLE114 = ($n == 0);
     int TLE114 = (n == 0);
// if (TLE114) goto L923 else goto L926;
      if (TLE114)
      goto L923;
    else
      goto L926;
    phc_check_invariants (TSRMLS_C);
// L923:
L923:;
// $TLE116 = ($m - 1);
     int TLE116 = (m - 1);
  
// $TLE118 = Ack($TLE116, 1);
  int TLE118;
  {
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    zval arg1;
    INIT_ZVAL (arg1);
    ZVAL_LONG (&arg1, TLE116);

    destruct[0] = 0;
    {
      args[0] = &arg1;
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_int_8;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = Ack_fci.param_count;
    zval ***params_save = Ack_fci.params;
    zval **retval_save = Ack_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    Ack_fci.params = args_ind;
    Ack_fci.param_count = 2;
    Ack_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&Ack_fci, &Ack_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    Ack_fci.params = params_save;
    Ack_fci.param_count = param_count_save;
    Ack_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    TLE118 = Z_LVAL_PP (p_rhs);
  }
// return $TLE118;
  {
    zval *rhs;
    RETVAL_LONG (TLE118);
    zval_copy_ctor (return_value);
    goto end_of_function;
    phc_check_invariants (TSRMLS_C);
  }
// goto L916;
  {
    goto L916;
    phc_check_invariants (TSRMLS_C);
  }
// L926:
L926:;
// $TLE120 = ($m - 1);
     int TLE120 = (m - 1);
  
// $TLE122 = ($n - 1);
     int TLE122 = (n - 1);
  
// $TLE123 = Ack($m, $TLE122);
    int TLE123;
  {

// Setup array of arguments
    zval *args[2];
    zval **args_ind[2];
    zval arg0;
    INIT_ZVAL (arg0);
    ZVAL_LONG (&arg0, m);
    {
      args[0] = &arg0;
      args_ind[0] = &args[0];
    }
    zval arg1;
    INIT_ZVAL (arg1);
    ZVAL_LONG (&arg1, TLE122);
    {
      args[1] = &arg1;
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = Ack_fci.param_count;
    zval ***params_save = Ack_fci.params;
    zval **retval_save = Ack_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    Ack_fci.params = args_ind;
    Ack_fci.param_count = 2;
    Ack_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&Ack_fci, &Ack_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    Ack_fci.params = params_save;
    Ack_fci.param_count = param_count_save;
    Ack_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    TLE123 = Z_LVAL_PP (p_rhs);
  }
// $TLE124 = Ack($TLE120, $TLE123);
    int TLE124;
  {
    zval *args[2];
    zval **args_ind[2];
    zval arg0;
    INIT_ZVAL (arg0);
    ZVAL_LONG (&arg0, TLE120);
    {
      args[0] = &arg0;
      args_ind[0] = &args[0];
    }
    zval arg1;
    INIT_ZVAL (arg1);
    ZVAL_LONG (&arg1, TLE123);
    {
      args[1] = &arg1;
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = Ack_fci.param_count;
    zval ***params_save = Ack_fci.params;
    zval **retval_save = Ack_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    Ack_fci.params = args_ind;
    Ack_fci.param_count = 2;
    Ack_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&Ack_fci, &Ack_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    Ack_fci.params = params_save;
    Ack_fci.param_count = param_count_save;
    Ack_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    TLE124 = Z_LVAL_PP (p_rhs);
  }
// return $TLE124;
  {
    RETVAL_LONG (TLE124);
    goto end_of_function;
    phc_check_invariants (TSRMLS_C);
  }
// L916:
L916:;
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE110 != NULL)
    {
      zval_ptr_dtor (&local_TLE110);
    }
  if (local_TLE112 != NULL)
    {
      zval_ptr_dtor (&local_TLE112);
    }
  if (local_TLE114 != NULL)
    {
      zval_ptr_dtor (&local_TLE114);
    }
  if (local_TLE116 != NULL)
    {
      zval_ptr_dtor (&local_TLE116);
    }
  if (local_TLE118 != NULL)
    {
      zval_ptr_dtor (&local_TLE118);
    }
  if (local_TLE120 != NULL)
    {
      zval_ptr_dtor (&local_TLE120);
    }
  if (local_TLE122 != NULL)
    {
      zval_ptr_dtor (&local_TLE122);
    }
  if (local_TLE123 != NULL)
    {
      zval_ptr_dtor (&local_TLE123);
    }
  if (local_TLE124 != NULL)
    {
      zval_ptr_dtor (&local_TLE124);
    }
  if (local_m != NULL)
    {
      zval_ptr_dtor (&local_m);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
}

// function ackermann($n)
// {
// \011$r = Ack(3, $n);
// \011$TLE127 = ('Ack(3,' . $n);
// \011$TLE129 = ($TLE127 . '): ');
// \011$TLE130 = ($TLE129 . $r);
// \011$TLE132 = ($TLE130 . '
// ');
// \011print($TLE132);
// }
PHP_FUNCTION (ackermann)
{
  zval *local_TLE127 = NULL;
  zval *local_TLE129 = NULL;
  zval *local_TLE130 = NULL;
  zval *local_TLE132 = NULL;
  zval *local_n = NULL;
  zval *local_r = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// $r = Ack(3, $n);
  {
    if (local_r == NULL)
      {
	local_r = EG (uninitialized_zval_ptr);
	local_r->refcount++;
      }
    zval **p_lhs = &local_r;
    initialize_function_call (&Ack_fci, &Ack_fcic, "Ack",
			      "test/subjects/benchmarks/zend/bench.php",
			      104 TSRMLS_CC);
    zend_function *signature = Ack_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_14;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg;
      if (local_n == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_n;
	}
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = Ack_fci.param_count;
    zval ***params_save = Ack_fci.params;
    zval **retval_save = Ack_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    Ack_fci.params = args_ind;
    Ack_fci.param_count = 2;
    Ack_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&Ack_fci, &Ack_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    Ack_fci.params = params_save;
    Ack_fci.param_count = param_count_save;
    Ack_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE127 = ('Ack(3,' . $n);
  {
    if (local_TLE127 == NULL)
      {
	local_TLE127 = EG (uninitialized_zval_ptr);
	local_TLE127->refcount++;
      }
    zval **p_lhs = &local_TLE127;
    zval *left = phc_const_pool_string_6;
    zval *right;
    if (local_n == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_n;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE129 = ($TLE127 . '): ');
  {
    if (local_TLE129 == NULL)
      {
	local_TLE129 = EG (uninitialized_zval_ptr);
	local_TLE129->refcount++;
      }
    zval **p_lhs = &local_TLE129;
    zval *left;
    if (local_TLE127 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE127;
      }
    zval *right = phc_const_pool_string_7;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE130 = ($TLE129 . $r);
  {
    if (local_TLE130 == NULL)
      {
	local_TLE130 = EG (uninitialized_zval_ptr);
	local_TLE130->refcount++;
      }
    zval **p_lhs = &local_TLE130;
    zval *left;
    if (local_TLE129 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE129;
      }
    zval *right;
    if (local_r == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_r;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE132 = ($TLE130 . '
// ');
  {
    if (local_TLE132 == NULL)
      {
	local_TLE132 = EG (uninitialized_zval_ptr);
	local_TLE132->refcount++;
      }
    zval **p_lhs = &local_TLE132;
    zval *left;
    if (local_TLE130 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE130;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE132);
  {
    zval *p_arg;
    if (local_TLE132 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE132;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE127 != NULL)
    {
      zval_ptr_dtor (&local_TLE127);
    }
  if (local_TLE129 != NULL)
    {
      zval_ptr_dtor (&local_TLE129);
    }
  if (local_TLE130 != NULL)
    {
      zval_ptr_dtor (&local_TLE130);
    }
  if (local_TLE132 != NULL)
    {
      zval_ptr_dtor (&local_TLE132);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
  if (local_r != NULL)
    {
      zval_ptr_dtor (&local_r);
    }
}

// function ary($n)
// {
// \011$i = 0;
// \011L943:
// \011$TLE133 = ($i < $n);
// \011if (TLE133) goto L945 else goto L946;
// \011L945:
// \011$X[$i] = $i;
// \011++$i;
// \011goto L943;
// \011L946:
// \011$i = ($n - 1);
// \011L948:
// \011$TLE136 = ($i >= 0);
// \011if (TLE136) goto L950 else goto L952;
// \011L950:
// \011$TSi137 = $X[$i];
// \011$Y[$i] = $TSi137;
// \011--$i;
// \011goto L948;
// \011L952:
// \011$last = ($n - 1);
// \011$TSi140 = $Y[$last];
// \011$TLE141 = ('' . $TSi140);
// \011$TLE143 = ($TLE141 . '
// ');
// \011print($TLE143);
// }
PHP_FUNCTION (ary)
{
  zval *local_TLE133 = NULL;
  zval *local_TLE136 = NULL;
  zval *local_TLE141 = NULL;
  zval *local_TLE143 = NULL;
  zval *local_TSi137 = NULL;
  zval *local_TSi140 = NULL;
  zval *local_X = NULL;
  zval *local_Y = NULL;
  zval *local_i = NULL;
  zval *local_last = NULL;
  zval *local_n = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// $i = 0;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L943:
L943:;
// $TLE133 = ($i < $n);
  {
    if (local_TLE133 == NULL)
      {
	local_TLE133 = EG (uninitialized_zval_ptr);
	local_TLE133->refcount++;
      }
    zval **p_lhs = &local_TLE133;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right;
    if (local_n == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_n;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE133) goto L945 else goto L946;
  {
    zval *p_cond;
    if (local_TLE133 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE133;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L945;
    else
      goto L946;
    phc_check_invariants (TSRMLS_C);
  }
// L945:
L945:;
// $X[$i] = $i;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L943;
  {
    goto L943;
    phc_check_invariants (TSRMLS_C);
  }
// L946:
L946:;
// $i = ($n - 1);
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    zval *left;
    if (local_n == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_n;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// L948:
L948:;
// $TLE136 = ($i >= 0);
  {
    if (local_TLE136 == NULL)
      {
	local_TLE136 = EG (uninitialized_zval_ptr);
	local_TLE136->refcount++;
      }
    zval **p_lhs = &local_TLE136;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right = phc_const_pool_int_0;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_or_equal_function (*p_lhs, right, left TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE136) goto L950 else goto L952;
  {
    zval *p_cond;
    if (local_TLE136 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE136;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L950;
    else
      goto L952;
    phc_check_invariants (TSRMLS_C);
  }
// L950:
L950:;
// $TSi137 = $X[$i];
  {
    if (local_TSi137 == NULL)
      {
	local_TSi137 = EG (uninitialized_zval_ptr);
	local_TSi137->refcount++;
      }
    zval **p_lhs = &local_TSi137;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $Y[$i] = $TSi137;
  {
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_lhs_var = &local_Y;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi137 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi137;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L948;
  {
    goto L948;
    phc_check_invariants (TSRMLS_C);
  }
// L952:
L952:;
// $last = ($n - 1);
  {
    if (local_last == NULL)
      {
	local_last = EG (uninitialized_zval_ptr);
	local_last->refcount++;
      }
    zval **p_lhs = &local_last;
    zval *left;
    if (local_n == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_n;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi140 = $Y[$last];
  {
    if (local_TSi140 == NULL)
      {
	local_TSi140 = EG (uninitialized_zval_ptr);
	local_TSi140->refcount++;
      }
    zval **p_lhs = &local_TSi140;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_Y == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_Y;
      }
    zval *ra_index;
    if (local_last == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_last;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE141 = ('' . $TSi140);
  {
    if (local_TLE141 == NULL)
      {
	local_TLE141 = EG (uninitialized_zval_ptr);
	local_TLE141->refcount++;
      }
    zval **p_lhs = &local_TLE141;
    zval *left = phc_const_pool_string_8;
    zval *right;
    if (local_TSi140 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi140;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE143 = ($TLE141 . '
// ');
  {
    if (local_TLE143 == NULL)
      {
	local_TLE143 = EG (uninitialized_zval_ptr);
	local_TLE143->refcount++;
      }
    zval **p_lhs = &local_TLE143;
    zval *left;
    if (local_TLE141 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE141;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE143);
  {
    zval *p_arg;
    if (local_TLE143 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE143;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE133 != NULL)
    {
      zval_ptr_dtor (&local_TLE133);
    }
  if (local_TLE136 != NULL)
    {
      zval_ptr_dtor (&local_TLE136);
    }
  if (local_TLE141 != NULL)
    {
      zval_ptr_dtor (&local_TLE141);
    }
  if (local_TLE143 != NULL)
    {
      zval_ptr_dtor (&local_TLE143);
    }
  if (local_TSi137 != NULL)
    {
      zval_ptr_dtor (&local_TSi137);
    }
  if (local_TSi140 != NULL)
    {
      zval_ptr_dtor (&local_TSi140);
    }
  if (local_X != NULL)
    {
      zval_ptr_dtor (&local_X);
    }
  if (local_Y != NULL)
    {
      zval_ptr_dtor (&local_Y);
    }
  if (local_i != NULL)
    {
      zval_ptr_dtor (&local_i);
    }
  if (local_last != NULL)
    {
      zval_ptr_dtor (&local_last);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
}

// function ary2($n)
// {
// \011$i = 0;
// \011L960:
// \011$TLE144 = ($i < $n);
// \011if (TLE144) goto L962 else goto L982;
// \011L962:
// \011$X[$i] = $i;
// \011++$i;
// \011$X[$i] = $i;
// \011++$i;
// \011$X[$i] = $i;
// \011++$i;
// \011$X[$i] = $i;
// \011++$i;
// \011$X[$i] = $i;
// \011++$i;
// \011$X[$i] = $i;
// \011++$i;
// \011$X[$i] = $i;
// \011++$i;
// \011$X[$i] = $i;
// \011++$i;
// \011$X[$i] = $i;
// \011++$i;
// \011$X[$i] = $i;
// \011++$i;
// \011goto L960;
// \011L982:
// \011$i = ($n - 1);
// \011L983:
// \011$TLE147 = ($i >= 0);
// \011if (TLE147) goto L985 else goto L1015;
// \011L985:
// \011$TSi148 = $X[$i];
// \011$Y[$i] = $TSi148;
// \011--$i;
// \011$TSi149 = $X[$i];
// \011$Y[$i] = $TSi149;
// \011--$i;
// \011$TSi150 = $X[$i];
// \011$Y[$i] = $TSi150;
// \011--$i;
// \011$TSi151 = $X[$i];
// \011$Y[$i] = $TSi151;
// \011--$i;
// \011$TSi152 = $X[$i];
// \011$Y[$i] = $TSi152;
// \011--$i;
// \011$TSi153 = $X[$i];
// \011$Y[$i] = $TSi153;
// \011--$i;
// \011$TSi154 = $X[$i];
// \011$Y[$i] = $TSi154;
// \011--$i;
// \011$TSi155 = $X[$i];
// \011$Y[$i] = $TSi155;
// \011--$i;
// \011$TSi156 = $X[$i];
// \011$Y[$i] = $TSi156;
// \011--$i;
// \011$TSi157 = $X[$i];
// \011$Y[$i] = $TSi157;
// \011--$i;
// \011goto L983;
// \011L1015:
// \011$last = ($n - 1);
// \011$TSi160 = $Y[$last];
// \011$TLE161 = ('' . $TSi160);
// \011$TLE163 = ($TLE161 . '
// ');
// \011print($TLE163);
// }
PHP_FUNCTION (ary2)
{
  zval *local_TLE144 = NULL;
  zval *local_TLE147 = NULL;
  zval *local_TLE161 = NULL;
  zval *local_TLE163 = NULL;
  zval *local_TSi148 = NULL;
  zval *local_TSi149 = NULL;
  zval *local_TSi150 = NULL;
  zval *local_TSi151 = NULL;
  zval *local_TSi152 = NULL;
  zval *local_TSi153 = NULL;
  zval *local_TSi154 = NULL;
  zval *local_TSi155 = NULL;
  zval *local_TSi156 = NULL;
  zval *local_TSi157 = NULL;
  zval *local_TSi160 = NULL;
  zval *local_X = NULL;
  zval *local_Y = NULL;
  zval *local_i = NULL;
  zval *local_last = NULL;
  zval *local_n = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// $i = 0;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L960:
L960:;
// $TLE144 = ($i < $n);
  {
    if (local_TLE144 == NULL)
      {
	local_TLE144 = EG (uninitialized_zval_ptr);
	local_TLE144->refcount++;
      }
    zval **p_lhs = &local_TLE144;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right;
    if (local_n == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_n;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE144) goto L962 else goto L982;
  {
    zval *p_cond;
    if (local_TLE144 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE144;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L962;
    else
      goto L982;
    phc_check_invariants (TSRMLS_C);
  }
// L962:
L962:;
// $X[$i] = $i;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $X[$i] = $i;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $X[$i] = $i;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $X[$i] = $i;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $X[$i] = $i;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $X[$i] = $i;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $X[$i] = $i;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $X[$i] = $i;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $X[$i] = $i;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $X[$i] = $i;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L960;
  {
    goto L960;
    phc_check_invariants (TSRMLS_C);
  }
// L982:
L982:;
// $i = ($n - 1);
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    zval *left;
    if (local_n == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_n;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// L983:
L983:;
// $TLE147 = ($i >= 0);
  {
    if (local_TLE147 == NULL)
      {
	local_TLE147 = EG (uninitialized_zval_ptr);
	local_TLE147->refcount++;
      }
    zval **p_lhs = &local_TLE147;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right = phc_const_pool_int_0;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_or_equal_function (*p_lhs, right, left TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE147) goto L985 else goto L1015;
  {
    zval *p_cond;
    if (local_TLE147 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE147;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L985;
    else
      goto L1015;
    phc_check_invariants (TSRMLS_C);
  }
// L985:
L985:;
// $TSi148 = $X[$i];
  {
    if (local_TSi148 == NULL)
      {
	local_TSi148 = EG (uninitialized_zval_ptr);
	local_TSi148->refcount++;
      }
    zval **p_lhs = &local_TSi148;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $Y[$i] = $TSi148;
  {
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_lhs_var = &local_Y;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi148 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi148;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi149 = $X[$i];
  {
    if (local_TSi149 == NULL)
      {
	local_TSi149 = EG (uninitialized_zval_ptr);
	local_TSi149->refcount++;
      }
    zval **p_lhs = &local_TSi149;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $Y[$i] = $TSi149;
  {
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_lhs_var = &local_Y;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi149 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi149;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi150 = $X[$i];
  {
    if (local_TSi150 == NULL)
      {
	local_TSi150 = EG (uninitialized_zval_ptr);
	local_TSi150->refcount++;
      }
    zval **p_lhs = &local_TSi150;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $Y[$i] = $TSi150;
  {
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_lhs_var = &local_Y;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi150 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi150;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi151 = $X[$i];
  {
    if (local_TSi151 == NULL)
      {
	local_TSi151 = EG (uninitialized_zval_ptr);
	local_TSi151->refcount++;
      }
    zval **p_lhs = &local_TSi151;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $Y[$i] = $TSi151;
  {
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_lhs_var = &local_Y;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi151 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi151;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi152 = $X[$i];
  {
    if (local_TSi152 == NULL)
      {
	local_TSi152 = EG (uninitialized_zval_ptr);
	local_TSi152->refcount++;
      }
    zval **p_lhs = &local_TSi152;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $Y[$i] = $TSi152;
  {
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_lhs_var = &local_Y;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi152 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi152;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi153 = $X[$i];
  {
    if (local_TSi153 == NULL)
      {
	local_TSi153 = EG (uninitialized_zval_ptr);
	local_TSi153->refcount++;
      }
    zval **p_lhs = &local_TSi153;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $Y[$i] = $TSi153;
  {
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_lhs_var = &local_Y;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi153 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi153;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi154 = $X[$i];
  {
    if (local_TSi154 == NULL)
      {
	local_TSi154 = EG (uninitialized_zval_ptr);
	local_TSi154->refcount++;
      }
    zval **p_lhs = &local_TSi154;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $Y[$i] = $TSi154;
  {
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_lhs_var = &local_Y;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi154 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi154;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi155 = $X[$i];
  {
    if (local_TSi155 == NULL)
      {
	local_TSi155 = EG (uninitialized_zval_ptr);
	local_TSi155->refcount++;
      }
    zval **p_lhs = &local_TSi155;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $Y[$i] = $TSi155;
  {
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_lhs_var = &local_Y;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi155 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi155;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi156 = $X[$i];
  {
    if (local_TSi156 == NULL)
      {
	local_TSi156 = EG (uninitialized_zval_ptr);
	local_TSi156->refcount++;
      }
    zval **p_lhs = &local_TSi156;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $Y[$i] = $TSi156;
  {
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_lhs_var = &local_Y;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi156 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi156;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi157 = $X[$i];
  {
    if (local_TSi157 == NULL)
      {
	local_TSi157 = EG (uninitialized_zval_ptr);
	local_TSi157->refcount++;
      }
    zval **p_lhs = &local_TSi157;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $Y[$i] = $TSi157;
  {
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_lhs_var = &local_Y;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi157 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi157;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L983;
  {
    goto L983;
    phc_check_invariants (TSRMLS_C);
  }
// L1015:
L1015:;
// $last = ($n - 1);
  {
    if (local_last == NULL)
      {
	local_last = EG (uninitialized_zval_ptr);
	local_last->refcount++;
      }
    zval **p_lhs = &local_last;
    zval *left;
    if (local_n == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_n;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi160 = $Y[$last];
  {
    if (local_TSi160 == NULL)
      {
	local_TSi160 = EG (uninitialized_zval_ptr);
	local_TSi160->refcount++;
      }
    zval **p_lhs = &local_TSi160;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_Y == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_Y;
      }
    zval *ra_index;
    if (local_last == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_last;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE161 = ('' . $TSi160);
  {
    if (local_TLE161 == NULL)
      {
	local_TLE161 = EG (uninitialized_zval_ptr);
	local_TLE161->refcount++;
      }
    zval **p_lhs = &local_TLE161;
    zval *left = phc_const_pool_string_8;
    zval *right;
    if (local_TSi160 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi160;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE163 = ($TLE161 . '
// ');
  {
    if (local_TLE163 == NULL)
      {
	local_TLE163 = EG (uninitialized_zval_ptr);
	local_TLE163->refcount++;
      }
    zval **p_lhs = &local_TLE163;
    zval *left;
    if (local_TLE161 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE161;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE163);
  {
    zval *p_arg;
    if (local_TLE163 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE163;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE144 != NULL)
    {
      zval_ptr_dtor (&local_TLE144);
    }
  if (local_TLE147 != NULL)
    {
      zval_ptr_dtor (&local_TLE147);
    }
  if (local_TLE161 != NULL)
    {
      zval_ptr_dtor (&local_TLE161);
    }
  if (local_TLE163 != NULL)
    {
      zval_ptr_dtor (&local_TLE163);
    }
  if (local_TSi148 != NULL)
    {
      zval_ptr_dtor (&local_TSi148);
    }
  if (local_TSi149 != NULL)
    {
      zval_ptr_dtor (&local_TSi149);
    }
  if (local_TSi150 != NULL)
    {
      zval_ptr_dtor (&local_TSi150);
    }
  if (local_TSi151 != NULL)
    {
      zval_ptr_dtor (&local_TSi151);
    }
  if (local_TSi152 != NULL)
    {
      zval_ptr_dtor (&local_TSi152);
    }
  if (local_TSi153 != NULL)
    {
      zval_ptr_dtor (&local_TSi153);
    }
  if (local_TSi154 != NULL)
    {
      zval_ptr_dtor (&local_TSi154);
    }
  if (local_TSi155 != NULL)
    {
      zval_ptr_dtor (&local_TSi155);
    }
  if (local_TSi156 != NULL)
    {
      zval_ptr_dtor (&local_TSi156);
    }
  if (local_TSi157 != NULL)
    {
      zval_ptr_dtor (&local_TSi157);
    }
  if (local_TSi160 != NULL)
    {
      zval_ptr_dtor (&local_TSi160);
    }
  if (local_X != NULL)
    {
      zval_ptr_dtor (&local_X);
    }
  if (local_Y != NULL)
    {
      zval_ptr_dtor (&local_Y);
    }
  if (local_i != NULL)
    {
      zval_ptr_dtor (&local_i);
    }
  if (local_last != NULL)
    {
      zval_ptr_dtor (&local_last);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
}

// function ary3($n)
// {
// \011$i = 0;
// \011L1024:
// \011$TLE164 = ($i < $n);
// \011if (TLE164) goto L1026 else goto L1029;
// \011L1029:
// \011$k = 0;
// \011L1031:
// \011$TLE169 = ($k < 1000);
// \011if (TLE169) goto L1033 else goto L1040;
// \011L1033:
// \011$i = ($n - 1);
// \011L1035:
// \011$TLE172 = ($i >= 0);
// \011if (TLE172) goto L1037 else goto L1030;
// \011L1037:
// \011$TSi173 =& $Y[$i];
// \011$TSi174 = $X[$i];
// \011$TSi173 = ($TSi173 + $TSi174);
// \011--$i;
// \011goto L1035;
// \011L1030:
// \011++$k;
// \011goto L1031;
// \011L1040:
// \011$last = ($n - 1);
// \011$TSi178 = $Y[0];
// \011$TLE179 = ('' . $TSi178);
// \011$TLE181 = ($TLE179 . ' ');
// \011$TSi182 = $Y[$last];
// \011$TLE183 = ($TLE181 . $TSi182);
// \011$TLE185 = ($TLE183 . '
// ');
// \011print($TLE185);
// \011goto L1021;
// \011L1026:
// \011$TLE166 = ($i + 1);
// \011$X[$i] = $TLE166;
// \011$Y[$i] = 0;
// \011++$i;
// \011goto L1024;
// \011L1021:
// }
PHP_FUNCTION (ary3)
{
  zval *local_TLE164 = NULL;
  zval *local_TLE166 = NULL;
  zval *local_TLE169 = NULL;
  zval *local_TLE172 = NULL;
  zval *local_TLE179 = NULL;
  zval *local_TLE181 = NULL;
  zval *local_TLE183 = NULL;
  zval *local_TLE185 = NULL;
  zval *local_TSi173 = NULL;
  zval *local_TSi174 = NULL;
  zval *local_TSi178 = NULL;
  zval *local_TSi182 = NULL;
  zval *local_X = NULL;
  zval *local_Y = NULL;
  zval *local_i = NULL;
  zval *local_k = NULL;
  zval *local_last = NULL;
  zval *local_n = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// $i = 0;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1024:
L1024:;
// $TLE164 = ($i < $n);
  {
    if (local_TLE164 == NULL)
      {
	local_TLE164 = EG (uninitialized_zval_ptr);
	local_TLE164->refcount++;
      }
    zval **p_lhs = &local_TLE164;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right;
    if (local_n == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_n;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE164) goto L1026 else goto L1029;
  {
    zval *p_cond;
    if (local_TLE164 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE164;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1026;
    else
      goto L1029;
    phc_check_invariants (TSRMLS_C);
  }
// L1029:
L1029:;
// $k = 0;
  {
    if (local_k == NULL)
      {
	local_k = EG (uninitialized_zval_ptr);
	local_k->refcount++;
      }
    zval **p_lhs = &local_k;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1031:
L1031:;
// $TLE169 = ($k < 1000);
  {
    if (local_TLE169 == NULL)
      {
	local_TLE169 = EG (uninitialized_zval_ptr);
	local_TLE169->refcount++;
      }
    zval **p_lhs = &local_TLE169;
    zval *left;
    if (local_k == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_k;
      }
    zval *right = phc_const_pool_int_6;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE169) goto L1033 else goto L1040;
  {
    zval *p_cond;
    if (local_TLE169 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE169;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1033;
    else
      goto L1040;
    phc_check_invariants (TSRMLS_C);
  }
// L1033:
L1033:;
// $i = ($n - 1);
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    zval *left;
    if (local_n == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_n;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// L1035:
L1035:;
// $TLE172 = ($i >= 0);
  {
    if (local_TLE172 == NULL)
      {
	local_TLE172 = EG (uninitialized_zval_ptr);
	local_TLE172->refcount++;
      }
    zval **p_lhs = &local_TLE172;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right = phc_const_pool_int_0;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_or_equal_function (*p_lhs, right, left TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE172) goto L1037 else goto L1030;
  {
    zval *p_cond;
    if (local_TLE172 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE172;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1037;
    else
      goto L1030;
    phc_check_invariants (TSRMLS_C);
  }
// L1037:
L1037:;
// $TSi173 =& $Y[$i];
  {
    if (local_TSi173 == NULL)
      {
	local_TSi173 = EG (uninitialized_zval_ptr);
	local_TSi173->refcount++;
      }
    zval **p_lhs = &local_TSi173;
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_rhs_var = &local_Y;
    zval *p_rhs_index;
    if (local_i == NULL)
      {
	p_rhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_index = local_i;
      }
    zval **p_rhs = get_ht_entry (p_rhs_var, p_rhs_index TSRMLS_CC);
    copy_into_ref (p_lhs, p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi174 = $X[$i];
  {
    if (local_TSi174 == NULL)
      {
	local_TSi174 = EG (uninitialized_zval_ptr);
	local_TSi174->refcount++;
      }
    zval **p_lhs = &local_TSi174;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi173 = ($TSi173 + $TSi174);
  {
    if (local_TSi173 == NULL)
      {
	local_TSi173 = EG (uninitialized_zval_ptr);
	local_TSi173->refcount++;
      }
    zval **p_lhs = &local_TSi173;
    zval *left;
    if (local_TSi173 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TSi173;
      }
    zval *right;
    if (local_TSi174 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi174;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1035;
  {
    goto L1035;
    phc_check_invariants (TSRMLS_C);
  }
// L1030:
L1030:;
// ++$k;
  {
    if (local_k == NULL)
      {
	local_k = EG (uninitialized_zval_ptr);
	local_k->refcount++;
      }
    zval **p_var = &local_k;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1031;
  {
    goto L1031;
    phc_check_invariants (TSRMLS_C);
  }
// L1040:
L1040:;
// $last = ($n - 1);
  {
    if (local_last == NULL)
      {
	local_last = EG (uninitialized_zval_ptr);
	local_last->refcount++;
      }
    zval **p_lhs = &local_last;
    zval *left;
    if (local_n == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_n;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi178 = $Y[0];
  {
    if (local_TSi178 == NULL)
      {
	local_TSi178 = EG (uninitialized_zval_ptr);
	local_TSi178->refcount++;
      }
    zval **p_lhs = &local_TSi178;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_Y == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_Y;
      }
    zval *ra_index = phc_const_pool_int_0;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE179 = ('' . $TSi178);
  {
    if (local_TLE179 == NULL)
      {
	local_TLE179 = EG (uninitialized_zval_ptr);
	local_TLE179->refcount++;
      }
    zval **p_lhs = &local_TLE179;
    zval *left = phc_const_pool_string_8;
    zval *right;
    if (local_TSi178 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi178;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE181 = ($TLE179 . ' ');
  {
    if (local_TLE181 == NULL)
      {
	local_TLE181 = EG (uninitialized_zval_ptr);
	local_TLE181->refcount++;
      }
    zval **p_lhs = &local_TLE181;
    zval *left;
    if (local_TLE179 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE179;
      }
    zval *right = phc_const_pool_string_9;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi182 = $Y[$last];
  {
    if (local_TSi182 == NULL)
      {
	local_TSi182 = EG (uninitialized_zval_ptr);
	local_TSi182->refcount++;
      }
    zval **p_lhs = &local_TSi182;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_Y == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_Y;
      }
    zval *ra_index;
    if (local_last == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_last;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE183 = ($TLE181 . $TSi182);
  {
    if (local_TLE183 == NULL)
      {
	local_TLE183 = EG (uninitialized_zval_ptr);
	local_TLE183->refcount++;
      }
    zval **p_lhs = &local_TLE183;
    zval *left;
    if (local_TLE181 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE181;
      }
    zval *right;
    if (local_TSi182 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi182;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE185 = ($TLE183 . '
// ');
  {
    if (local_TLE185 == NULL)
      {
	local_TLE185 = EG (uninitialized_zval_ptr);
	local_TLE185->refcount++;
      }
    zval **p_lhs = &local_TLE185;
    zval *left;
    if (local_TLE183 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE183;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE185);
  {
    zval *p_arg;
    if (local_TLE185 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE185;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1021;
  {
    goto L1021;
    phc_check_invariants (TSRMLS_C);
  }
// L1026:
L1026:;
// $TLE166 = ($i + 1);
  {
    if (local_TLE166 == NULL)
      {
	local_TLE166 = EG (uninitialized_zval_ptr);
	local_TLE166->refcount++;
      }
    zval **p_lhs = &local_TLE166;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $X[$i] = $TLE166;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TLE166 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TLE166;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $Y[$i] = 0;
  {
    if (local_Y == NULL)
      {
	local_Y = EG (uninitialized_zval_ptr);
	local_Y->refcount++;
      }
    zval **p_lhs_var = &local_Y;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var = phc_const_pool_int_0;
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1024;
  {
    goto L1024;
    phc_check_invariants (TSRMLS_C);
  }
// L1021:
L1021:;
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE164 != NULL)
    {
      zval_ptr_dtor (&local_TLE164);
    }
  if (local_TLE166 != NULL)
    {
      zval_ptr_dtor (&local_TLE166);
    }
  if (local_TLE169 != NULL)
    {
      zval_ptr_dtor (&local_TLE169);
    }
  if (local_TLE172 != NULL)
    {
      zval_ptr_dtor (&local_TLE172);
    }
  if (local_TLE179 != NULL)
    {
      zval_ptr_dtor (&local_TLE179);
    }
  if (local_TLE181 != NULL)
    {
      zval_ptr_dtor (&local_TLE181);
    }
  if (local_TLE183 != NULL)
    {
      zval_ptr_dtor (&local_TLE183);
    }
  if (local_TLE185 != NULL)
    {
      zval_ptr_dtor (&local_TLE185);
    }
  if (local_TSi173 != NULL)
    {
      zval_ptr_dtor (&local_TSi173);
    }
  if (local_TSi174 != NULL)
    {
      zval_ptr_dtor (&local_TSi174);
    }
  if (local_TSi178 != NULL)
    {
      zval_ptr_dtor (&local_TSi178);
    }
  if (local_TSi182 != NULL)
    {
      zval_ptr_dtor (&local_TSi182);
    }
  if (local_X != NULL)
    {
      zval_ptr_dtor (&local_X);
    }
  if (local_Y != NULL)
    {
      zval_ptr_dtor (&local_Y);
    }
  if (local_i != NULL)
    {
      zval_ptr_dtor (&local_i);
    }
  if (local_k != NULL)
    {
      zval_ptr_dtor (&local_k);
    }
  if (local_last != NULL)
    {
      zval_ptr_dtor (&local_last);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
}

// function fibo_r($n)
// {
// \011$TLE187 = ($n < 2);
// \011if (TLE187) goto L1052 else goto L1053;
// \011L1052:
// \011$TEF37 = 1;
// \011L1058:
// \011return $TEF37;
// \011goto L1049;
// \011L1053:
// \011$TLE189 = ($n - 2);
// \011$TLE190 = fibo_r($TLE189);
// \011$TLE192 = ($n - 1);
// \011$TLE193 = fibo_r($TLE192);
// \011$TEF37 = ($TLE190 + $TLE193);
// \011goto L1058;
// \011L1049:
// }
PHP_FUNCTION (fibo_r)
{
  zval *local_TEF37 = NULL;
  zval *local_TLE187 = NULL;
  zval *local_TLE189 = NULL;
  zval *local_TLE190 = NULL;
  zval *local_TLE192 = NULL;
  zval *local_TLE193 = NULL;
  zval *local_n = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// $TLE187 = ($n < 2);
  {
    if (local_TLE187 == NULL)
      {
	local_TLE187 = EG (uninitialized_zval_ptr);
	local_TLE187->refcount++;
      }
    zval **p_lhs = &local_TLE187;
    zval *left;
    if (local_n == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_n;
      }
    zval *right = phc_const_pool_int_7;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE187) goto L1052 else goto L1053;
  {
    zval *p_cond;
    if (local_TLE187 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE187;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1052;
    else
      goto L1053;
    phc_check_invariants (TSRMLS_C);
  }
// L1052:
L1052:;
// $TEF37 = 1;
  {
    if (local_TEF37 == NULL)
      {
	local_TEF37 = EG (uninitialized_zval_ptr);
	local_TEF37->refcount++;
      }
    zval **p_lhs = &local_TEF37;
    if (phc_const_pool_int_8 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_8, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1058:
L1058:;
// return $TEF37;
  {
    zval *rhs;
    if (local_TEF37 == NULL)
      {
	rhs = EG (uninitialized_zval_ptr);
      }
    else
      {
	rhs = local_TEF37;
      }
    return_value->value = rhs->value;
    return_value->type = rhs->type;
    zval_copy_ctor (return_value);
    goto end_of_function;
    phc_check_invariants (TSRMLS_C);
  }
// goto L1049;
  {
    goto L1049;
    phc_check_invariants (TSRMLS_C);
  }
// L1053:
L1053:;
// $TLE189 = ($n - 2);
  {
    if (local_TLE189 == NULL)
      {
	local_TLE189 = EG (uninitialized_zval_ptr);
	local_TLE189->refcount++;
      }
    zval **p_lhs = &local_TLE189;
    zval *left;
    if (local_n == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_n;
      }
    zval *right = phc_const_pool_int_7;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE190 = fibo_r($TLE189);
  {
    if (local_TLE190 == NULL)
      {
	local_TLE190 = EG (uninitialized_zval_ptr);
	local_TLE190->refcount++;
      }
    zval **p_lhs = &local_TLE190;
    initialize_function_call (&fibo_r_fci, &fibo_r_fcic, "fibo_r",
			      "test/subjects/benchmarks/zend/bench.php",
			      173 TSRMLS_CC);
    zend_function *signature = fibo_r_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_TLE189 == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_TLE189;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = fibo_r_fci.param_count;
    zval ***params_save = fibo_r_fci.params;
    zval **retval_save = fibo_r_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    fibo_r_fci.params = args_ind;
    fibo_r_fci.param_count = 1;
    fibo_r_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&fibo_r_fci, &fibo_r_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    fibo_r_fci.params = params_save;
    fibo_r_fci.param_count = param_count_save;
    fibo_r_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE192 = ($n - 1);
  {
    if (local_TLE192 == NULL)
      {
	local_TLE192 = EG (uninitialized_zval_ptr);
	local_TLE192->refcount++;
      }
    zval **p_lhs = &local_TLE192;
    zval *left;
    if (local_n == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_n;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE193 = fibo_r($TLE192);
  {
    if (local_TLE193 == NULL)
      {
	local_TLE193 = EG (uninitialized_zval_ptr);
	local_TLE193->refcount++;
      }
    zval **p_lhs = &local_TLE193;
    initialize_function_call (&fibo_r_fci, &fibo_r_fcic, "fibo_r",
			      "test/subjects/benchmarks/zend/bench.php",
			      173 TSRMLS_CC);
    zend_function *signature = fibo_r_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_TLE192 == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_TLE192;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = fibo_r_fci.param_count;
    zval ***params_save = fibo_r_fci.params;
    zval **retval_save = fibo_r_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    fibo_r_fci.params = args_ind;
    fibo_r_fci.param_count = 1;
    fibo_r_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&fibo_r_fci, &fibo_r_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    fibo_r_fci.params = params_save;
    fibo_r_fci.param_count = param_count_save;
    fibo_r_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TEF37 = ($TLE190 + $TLE193);
  {
    if (local_TEF37 == NULL)
      {
	local_TEF37 = EG (uninitialized_zval_ptr);
	local_TEF37->refcount++;
      }
    zval **p_lhs = &local_TEF37;
    zval *left;
    if (local_TLE190 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE190;
      }
    zval *right;
    if (local_TLE193 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE193;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1058;
  {
    goto L1058;
    phc_check_invariants (TSRMLS_C);
  }
// L1049:
L1049:;
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TEF37 != NULL)
    {
      zval_ptr_dtor (&local_TEF37);
    }
  if (local_TLE187 != NULL)
    {
      zval_ptr_dtor (&local_TLE187);
    }
  if (local_TLE189 != NULL)
    {
      zval_ptr_dtor (&local_TLE189);
    }
  if (local_TLE190 != NULL)
    {
      zval_ptr_dtor (&local_TLE190);
    }
  if (local_TLE192 != NULL)
    {
      zval_ptr_dtor (&local_TLE192);
    }
  if (local_TLE193 != NULL)
    {
      zval_ptr_dtor (&local_TLE193);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
}

// function fibo($n)
// {
// \011$r = fibo_r($n);
// \011$TLE195 = ('' . $r);
// \011$TLE197 = ($TLE195 . '
// ');
// \011print($TLE197);
// }
PHP_FUNCTION (fibo)
{
  zval *local_TLE195 = NULL;
  zval *local_TLE197 = NULL;
  zval *local_n = NULL;
  zval *local_r = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// $r = fibo_r($n);
  {
    if (local_r == NULL)
      {
	local_r = EG (uninitialized_zval_ptr);
	local_r->refcount++;
      }
    zval **p_lhs = &local_r;
    initialize_function_call (&fibo_r_fci, &fibo_r_fcic, "fibo_r",
			      "test/subjects/benchmarks/zend/bench.php",
			      177 TSRMLS_CC);
    zend_function *signature = fibo_r_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_n == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_n;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = fibo_r_fci.param_count;
    zval ***params_save = fibo_r_fci.params;
    zval **retval_save = fibo_r_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    fibo_r_fci.params = args_ind;
    fibo_r_fci.param_count = 1;
    fibo_r_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&fibo_r_fci, &fibo_r_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    fibo_r_fci.params = params_save;
    fibo_r_fci.param_count = param_count_save;
    fibo_r_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE195 = ('' . $r);
  {
    if (local_TLE195 == NULL)
      {
	local_TLE195 = EG (uninitialized_zval_ptr);
	local_TLE195->refcount++;
      }
    zval **p_lhs = &local_TLE195;
    zval *left = phc_const_pool_string_8;
    zval *right;
    if (local_r == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_r;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE197 = ($TLE195 . '
// ');
  {
    if (local_TLE197 == NULL)
      {
	local_TLE197 = EG (uninitialized_zval_ptr);
	local_TLE197->refcount++;
      }
    zval **p_lhs = &local_TLE197;
    zval *left;
    if (local_TLE195 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE195;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE197);
  {
    zval *p_arg;
    if (local_TLE197 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE197;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE195 != NULL)
    {
      zval_ptr_dtor (&local_TLE195);
    }
  if (local_TLE197 != NULL)
    {
      zval_ptr_dtor (&local_TLE197);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
  if (local_r != NULL)
    {
      zval_ptr_dtor (&local_r);
    }
}

// function hash1($n)
// {
// \011$i = 1;
// \011L1069:
// \011$TLE198 = ($i <= $n);
// \011if (TLE198) goto L1071 else goto L1073;
// \011L1071:
// \011$TLE199 = dechex($i);
// \011$X[$TLE199] = $i;
// \011++$i;
// \011goto L1069;
// \011L1073:
// \011$c = 0;
// \011$i = $n;
// \011L1076:
// \011$TLE201 = ($i > 0);
// \011if (TLE201) goto L1078 else goto L1082;
// \011L1078:
// \011$TLE202 = dechex($i);
// \011$TSi203 = $X[$TLE202];
// \011if (TSi203) goto L1081 else goto L1075;
// \011L1081:
// \011++$c;
// \011L1075:
// \011--$i;
// \011goto L1076;
// \011L1082:
// \011$TLE205 = ('' . $c);
// \011$TLE207 = ($TLE205 . '
// ');
// \011print($TLE207);
// }
PHP_FUNCTION (hash1)
{
  zval *local_TLE198 = NULL;
  zval *local_TLE199 = NULL;
  zval *local_TLE201 = NULL;
  zval *local_TLE202 = NULL;
  zval *local_TLE205 = NULL;
  zval *local_TLE207 = NULL;
  zval *local_TSi203 = NULL;
  zval *local_X = NULL;
  zval *local_c = NULL;
  zval *local_i = NULL;
  zval *local_n = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// $i = 1;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    if (phc_const_pool_int_8 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_8, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1069:
L1069:;
// $TLE198 = ($i <= $n);
  {
    if (local_TLE198 == NULL)
      {
	local_TLE198 = EG (uninitialized_zval_ptr);
	local_TLE198->refcount++;
      }
    zval **p_lhs = &local_TLE198;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right;
    if (local_n == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_n;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_or_equal_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE198) goto L1071 else goto L1073;
  {
    zval *p_cond;
    if (local_TLE198 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE198;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1071;
    else
      goto L1073;
    phc_check_invariants (TSRMLS_C);
  }
// L1071:
L1071:;
// $TLE199 = dechex($i);
  {
    if (local_TLE199 == NULL)
      {
	local_TLE199 = EG (uninitialized_zval_ptr);
	local_TLE199->refcount++;
      }
    zval **p_lhs = &local_TLE199;
    initialize_function_call (&dechex_fci, &dechex_fcic, "dechex",
			      "test/subjects/benchmarks/zend/bench.php",
			      185 TSRMLS_CC);
    zend_function *signature = dechex_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_i == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_i;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = dechex_fci.param_count;
    zval ***params_save = dechex_fci.params;
    zval **retval_save = dechex_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    dechex_fci.params = args_ind;
    dechex_fci.param_count = 1;
    dechex_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&dechex_fci, &dechex_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    dechex_fci.params = params_save;
    dechex_fci.param_count = param_count_save;
    dechex_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $X[$TLE199] = $i;
  {
    if (local_X == NULL)
      {
	local_X = EG (uninitialized_zval_ptr);
	local_X->refcount++;
      }
    zval **p_lhs_var = &local_X;
    zval *p_lhs_index;
    if (local_TLE199 == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_TLE199;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1069;
  {
    goto L1069;
    phc_check_invariants (TSRMLS_C);
  }
// L1073:
L1073:;
// $c = 0;
  {
    if (local_c == NULL)
      {
	local_c = EG (uninitialized_zval_ptr);
	local_c->refcount++;
      }
    zval **p_lhs = &local_c;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// $i = $n;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_n == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_n;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// L1076:
L1076:;
// $TLE201 = ($i > 0);
  {
    if (local_TLE201 == NULL)
      {
	local_TLE201 = EG (uninitialized_zval_ptr);
	local_TLE201->refcount++;
      }
    zval **p_lhs = &local_TLE201;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right = phc_const_pool_int_0;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, right, left TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE201) goto L1078 else goto L1082;
  {
    zval *p_cond;
    if (local_TLE201 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE201;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1078;
    else
      goto L1082;
    phc_check_invariants (TSRMLS_C);
  }
// L1078:
L1078:;
// $TLE202 = dechex($i);
  {
    if (local_TLE202 == NULL)
      {
	local_TLE202 = EG (uninitialized_zval_ptr);
	local_TLE202->refcount++;
      }
    zval **p_lhs = &local_TLE202;
    initialize_function_call (&dechex_fci, &dechex_fcic, "dechex",
			      "test/subjects/benchmarks/zend/bench.php",
			      189 TSRMLS_CC);
    zend_function *signature = dechex_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_i == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_i;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = dechex_fci.param_count;
    zval ***params_save = dechex_fci.params;
    zval **retval_save = dechex_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    dechex_fci.params = args_ind;
    dechex_fci.param_count = 1;
    dechex_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&dechex_fci, &dechex_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    dechex_fci.params = params_save;
    dechex_fci.param_count = param_count_save;
    dechex_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi203 = $X[$TLE202];
  {
    if (local_TSi203 == NULL)
      {
	local_TSi203 = EG (uninitialized_zval_ptr);
	local_TSi203->refcount++;
      }
    zval **p_lhs = &local_TSi203;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_X == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_X;
      }
    zval *ra_index;
    if (local_TLE202 == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_TLE202;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// if (TSi203) goto L1081 else goto L1075;
  {
    zval *p_cond;
    if (local_TSi203 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TSi203;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1081;
    else
      goto L1075;
    phc_check_invariants (TSRMLS_C);
  }
// L1081:
L1081:;
// ++$c;
  {
    if (local_c == NULL)
      {
	local_c = EG (uninitialized_zval_ptr);
	local_c->refcount++;
      }
    zval **p_var = &local_c;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// L1075:
L1075:;
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1076;
  {
    goto L1076;
    phc_check_invariants (TSRMLS_C);
  }
// L1082:
L1082:;
// $TLE205 = ('' . $c);
  {
    if (local_TLE205 == NULL)
      {
	local_TLE205 = EG (uninitialized_zval_ptr);
	local_TLE205->refcount++;
      }
    zval **p_lhs = &local_TLE205;
    zval *left = phc_const_pool_string_8;
    zval *right;
    if (local_c == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_c;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE207 = ($TLE205 . '
// ');
  {
    if (local_TLE207 == NULL)
      {
	local_TLE207 = EG (uninitialized_zval_ptr);
	local_TLE207->refcount++;
      }
    zval **p_lhs = &local_TLE207;
    zval *left;
    if (local_TLE205 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE205;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE207);
  {
    zval *p_arg;
    if (local_TLE207 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE207;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE198 != NULL)
    {
      zval_ptr_dtor (&local_TLE198);
    }
  if (local_TLE199 != NULL)
    {
      zval_ptr_dtor (&local_TLE199);
    }
  if (local_TLE201 != NULL)
    {
      zval_ptr_dtor (&local_TLE201);
    }
  if (local_TLE202 != NULL)
    {
      zval_ptr_dtor (&local_TLE202);
    }
  if (local_TLE205 != NULL)
    {
      zval_ptr_dtor (&local_TLE205);
    }
  if (local_TLE207 != NULL)
    {
      zval_ptr_dtor (&local_TLE207);
    }
  if (local_TSi203 != NULL)
    {
      zval_ptr_dtor (&local_TSi203);
    }
  if (local_X != NULL)
    {
      zval_ptr_dtor (&local_X);
    }
  if (local_c != NULL)
    {
      zval_ptr_dtor (&local_c);
    }
  if (local_i != NULL)
    {
      zval_ptr_dtor (&local_i);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
}

// function hash2($n)
// {
// \011$i = 0;
// \011L1089:
// \011$TLE208 = ($i < $n);
// \011if (TLE208) goto L1091 else goto L1097;
// \011L1097:
// \011$i = $n;
// \011L1099:
// \011$TLE219 = ($i > 0);
// \011if (TLE219) goto L1101 else goto L1115;
// \011L1101:
// \011$TLE639 = is_array($hash1);
// \011if (TLE639) goto L1105 else goto L1103;
// \011L1105:
// \011$LF638 = $hash1;
// \011L1106:
// \011foreach_reset($LF638, ht_iterator646);
// \011L1107:
// \011$THK648 = foreach_has_key($LF638, ht_iterator646)
// \011;
// \011if (THK648) goto L1109 else goto L1114;
// \011L1109:
// \011$key = foreach_get_key($LF638, ht_iterator646)
// \011;
// \011$value = foreach_get_val($LF638, ht_iterator646)
// \011;
// \011$TSi220 =& $hash2[$key];
// \011$TSi220 = ($TSi220 + $value);
// \011foreach_next($LF638, ht_iterator646);
// \011goto L1107;
// \011L1114:
// \011foreach_end($LF638, ht_iterator646);
// \011--$i;
// \011goto L1099;
// \011L1103:
// \011trigger_error('Invalid argument supplied for foreach()', 512);
// \011$LF638 = (array) $hash1;
// \011goto L1106;
// \011L1115:
// \011$TLE223 = ($n - 1);
// \011$last = ('foo_' . $TLE223);
// \011$TSi225 = $hash1['foo_0'];
// \011$TLE226 = ('' . $TSi225);
// \011$TLE228 = ($TLE226 . ' ');
// \011$TSi229 = $hash1[$last];
// \011$TLE230 = ($TLE228 . $TSi229);
// \011$TLE232 = ($TLE230 . ' ');
// \011$TSi233 = $hash2['foo_0'];
// \011$TLE234 = ($TLE232 . $TSi233);
// \011$TLE236 = ($TLE234 . ' ');
// \011$TSi237 = $hash2[$last];
// \011$TLE238 = ($TLE236 . $TSi237);
// \011$TLE240 = ($TLE238 . '
// ');
// \011print($TLE240);
// \011goto L1086;
// \011L1091:
// \011$TLE210 = ('foo_' . $i);
// \011$TLE212 = ($TLE210 . '');
// \011$hash1[$TLE212] = $i;
// \011$TLE214 = ('foo_' . $i);
// \011$TLE216 = ($TLE214 . '');
// \011$hash2[$TLE216] = 0;
// \011++$i;
// \011goto L1089;
// \011L1086:
// }
PHP_FUNCTION (hash2)
{
  zval *local_LF638 = NULL;
  zval *local_THK648 = NULL;
  zval *local_TLE208 = NULL;
  zval *local_TLE210 = NULL;
  zval *local_TLE212 = NULL;
  zval *local_TLE214 = NULL;
  zval *local_TLE216 = NULL;
  zval *local_TLE219 = NULL;
  zval *local_TLE223 = NULL;
  zval *local_TLE226 = NULL;
  zval *local_TLE228 = NULL;
  zval *local_TLE230 = NULL;
  zval *local_TLE232 = NULL;
  zval *local_TLE234 = NULL;
  zval *local_TLE236 = NULL;
  zval *local_TLE238 = NULL;
  zval *local_TLE240 = NULL;
  zval *local_TLE639 = NULL;
  zval *local_TSi220 = NULL;
  zval *local_TSi225 = NULL;
  zval *local_TSi229 = NULL;
  zval *local_TSi233 = NULL;
  zval *local_TSi237 = NULL;
  zval *local_hash1 = NULL;
  zval *local_hash2 = NULL;
  zval *local_i = NULL;
  zval *local_key = NULL;
  zval *local_last = NULL;
  zval *local_n = NULL;
  zval *local_value = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// $i = 0;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1089:
L1089:;
// $TLE208 = ($i < $n);
  {
    if (local_TLE208 == NULL)
      {
	local_TLE208 = EG (uninitialized_zval_ptr);
	local_TLE208->refcount++;
      }
    zval **p_lhs = &local_TLE208;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right;
    if (local_n == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_n;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE208) goto L1091 else goto L1097;
  {
    zval *p_cond;
    if (local_TLE208 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE208;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1091;
    else
      goto L1097;
    phc_check_invariants (TSRMLS_C);
  }
// L1097:
L1097:;
// $i = $n;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_n == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_n;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// L1099:
L1099:;
// $TLE219 = ($i > 0);
  {
    if (local_TLE219 == NULL)
      {
	local_TLE219 = EG (uninitialized_zval_ptr);
	local_TLE219->refcount++;
      }
    zval **p_lhs = &local_TLE219;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right = phc_const_pool_int_0;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, right, left TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE219) goto L1101 else goto L1115;
  {
    zval *p_cond;
    if (local_TLE219 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE219;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1101;
    else
      goto L1115;
    phc_check_invariants (TSRMLS_C);
  }
// L1101:
L1101:;
// $TLE639 = is_array($hash1);
  {
    if (local_TLE639 == NULL)
      {
	local_TLE639 = EG (uninitialized_zval_ptr);
	local_TLE639->refcount++;
      }
    zval **p_lhs = &local_TLE639;
    initialize_function_call (&is_array_fci, &is_array_fcic, "is_array",
			      "test/subjects/benchmarks/zend/bench.php",
			      202 TSRMLS_CC);
    zend_function *signature = is_array_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_hash1 == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_hash1;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = is_array_fci.param_count;
    zval ***params_save = is_array_fci.params;
    zval **retval_save = is_array_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    is_array_fci.params = args_ind;
    is_array_fci.param_count = 1;
    is_array_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&is_array_fci, &is_array_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    is_array_fci.params = params_save;
    is_array_fci.param_count = param_count_save;
    is_array_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE639) goto L1105 else goto L1103;
  {
    zval *p_cond;
    if (local_TLE639 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE639;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1105;
    else
      goto L1103;
    phc_check_invariants (TSRMLS_C);
  }
// L1105:
L1105:;
// $LF638 = $hash1;
  {
    if (local_LF638 == NULL)
      {
	local_LF638 = EG (uninitialized_zval_ptr);
	local_LF638->refcount++;
      }
    zval **p_lhs = &local_LF638;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_hash1 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_hash1;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// L1106:
L1106:;
// foreach_reset($LF638, ht_iterator646);
  HashPosition ht_iterator646;
  {
    zval *fe_array;
    if (local_LF638 == NULL)
      {
	fe_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	fe_array = local_LF638;
      }
    zend_hash_internal_pointer_reset_ex (fe_array->value.ht, &ht_iterator646);
  }
// L1107:
L1107:;
// $THK648 = foreach_has_key($LF638, ht_iterator646)
// ;
  {
    if (local_THK648 == NULL)
      {
	local_THK648 = EG (uninitialized_zval_ptr);
	local_THK648->refcount++;
      }
    zval **p_lhs = &local_THK648;
    if ((*p_lhs)->is_ref)
      {
	// Always overwrite the current value
	zval *value = *p_lhs;
	zval_dtor (value);
	zval *fe_array;
	if (local_LF638 == NULL)
	  {
	    fe_array = EG (uninitialized_zval_ptr);
	  }
	else
	  {
	    fe_array = local_LF638;
	  }
	int type =
	  zend_hash_get_current_key_type_ex (fe_array->value.ht,
					     &ht_iterator646);
	ZVAL_BOOL (value, type != HASH_KEY_NON_EXISTANT);
      }
    else
      {
	zval *value;
	ALLOC_INIT_ZVAL (value);
	zval *fe_array;
	if (local_LF638 == NULL)
	  {
	    fe_array = EG (uninitialized_zval_ptr);
	  }
	else
	  {
	    fe_array = local_LF638;
	  }
	int type =
	  zend_hash_get_current_key_type_ex (fe_array->value.ht,
					     &ht_iterator646);
	ZVAL_BOOL (value, type != HASH_KEY_NON_EXISTANT);
	zval_ptr_dtor (p_lhs);
	*p_lhs = value;
      }
    phc_check_invariants (TSRMLS_C);
  }
// if (THK648) goto L1109 else goto L1114;
  {
    zval *p_cond;
    if (local_THK648 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_THK648;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1109;
    else
      goto L1114;
    phc_check_invariants (TSRMLS_C);
  }
// L1109:
L1109:;
// $key = foreach_get_key($LF638, ht_iterator646)
// ;
  {
    if (local_key == NULL)
      {
	local_key = EG (uninitialized_zval_ptr);
	local_key->refcount++;
      }
    zval **p_lhs = &local_key;
    if ((*p_lhs)->is_ref)
      {
	// Always overwrite the current value
	zval *value = *p_lhs;
	zval_dtor (value);
	zval *fe_array;
	if (local_LF638 == NULL)
	  {
	    fe_array = EG (uninitialized_zval_ptr);
	  }
	else
	  {
	    fe_array = local_LF638;
	  }
	char *str_index = NULL;
	uint str_length;
	ulong num_index;
	int result =
	  zend_hash_get_current_key_ex (fe_array->value.ht, &str_index,
					&str_length, &num_index, 0,
					&ht_iterator646);
	if (result == HASH_KEY_IS_LONG)
	  {
	    ZVAL_LONG (value, num_index);
	  }
	else
	  {
	    ZVAL_STRINGL (value, str_index, str_length - 1, 1);
	  }
      }
    else
      {
	zval *value;
	ALLOC_INIT_ZVAL (value);
	zval *fe_array;
	if (local_LF638 == NULL)
	  {
	    fe_array = EG (uninitialized_zval_ptr);
	  }
	else
	  {
	    fe_array = local_LF638;
	  }
	char *str_index = NULL;
	uint str_length;
	ulong num_index;
	int result =
	  zend_hash_get_current_key_ex (fe_array->value.ht, &str_index,
					&str_length, &num_index, 0,
					&ht_iterator646);
	if (result == HASH_KEY_IS_LONG)
	  {
	    ZVAL_LONG (value, num_index);
	  }
	else
	  {
	    ZVAL_STRINGL (value, str_index, str_length - 1, 1);
	  }
	zval_ptr_dtor (p_lhs);
	*p_lhs = value;
      }
    phc_check_invariants (TSRMLS_C);
  }
// $value = foreach_get_val($LF638, ht_iterator646)
// ;
  {
    if (local_value == NULL)
      {
	local_value = EG (uninitialized_zval_ptr);
	local_value->refcount++;
      }
    zval **p_lhs = &local_value;
    zval *fe_array;
    if (local_LF638 == NULL)
      {
	fe_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	fe_array = local_LF638;
      }
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    int result =
      zend_hash_get_current_data_ex (fe_array->value.ht, (void **) (&p_rhs),
				     &ht_iterator646);
    assert (result == SUCCESS);
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi220 =& $hash2[$key];
  {
    if (local_TSi220 == NULL)
      {
	local_TSi220 = EG (uninitialized_zval_ptr);
	local_TSi220->refcount++;
      }
    zval **p_lhs = &local_TSi220;
    if (local_hash2 == NULL)
      {
	local_hash2 = EG (uninitialized_zval_ptr);
	local_hash2->refcount++;
      }
    zval **p_rhs_var = &local_hash2;
    zval *p_rhs_index;
    if (local_key == NULL)
      {
	p_rhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_index = local_key;
      }
    zval **p_rhs = get_ht_entry (p_rhs_var, p_rhs_index TSRMLS_CC);
    copy_into_ref (p_lhs, p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi220 = ($TSi220 + $value);
  {
    if (local_TSi220 == NULL)
      {
	local_TSi220 = EG (uninitialized_zval_ptr);
	local_TSi220->refcount++;
      }
    zval **p_lhs = &local_TSi220;
    zval *left;
    if (local_TSi220 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TSi220;
      }
    zval *right;
    if (local_value == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_value;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// foreach_next($LF638, ht_iterator646);
  {
    zval *fe_array;
    if (local_LF638 == NULL)
      {
	fe_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	fe_array = local_LF638;
      }
    int result =
      zend_hash_move_forward_ex (fe_array->value.ht, &ht_iterator646);
    assert (result == SUCCESS);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1107;
  {
    goto L1107;
    phc_check_invariants (TSRMLS_C);
  }
// L1114:
L1114:;
// foreach_end($LF638, ht_iterator646);
  {
    zval *fe_array;
    if (local_LF638 == NULL)
      {
	fe_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	fe_array = local_LF638;
      }
    zend_hash_internal_pointer_end_ex (fe_array->value.ht, &ht_iterator646);
    phc_check_invariants (TSRMLS_C);
  }
// --$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1099;
  {
    goto L1099;
    phc_check_invariants (TSRMLS_C);
  }
// L1103:
L1103:;
// trigger_error('Invalid argument supplied for foreach()', 512);
  {
    initialize_function_call (&trigger_error_fci, &trigger_error_fcic,
			      "trigger_error",
			      "test/subjects/benchmarks/zend/bench.php",
			      202 TSRMLS_CC);
    zend_function *signature = trigger_error_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_string_10;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_int_15;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = trigger_error_fci.param_count;
    zval ***params_save = trigger_error_fci.params;
    zval **retval_save = trigger_error_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    trigger_error_fci.params = args_ind;
    trigger_error_fci.param_count = 2;
    trigger_error_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&trigger_error_fci, &trigger_error_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    trigger_error_fci.params = params_save;
    trigger_error_fci.param_count = param_count_save;
    trigger_error_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $LF638 = (array) $hash1;
  {
    if (local_LF638 == NULL)
      {
	local_LF638 = EG (uninitialized_zval_ptr);
	local_LF638->refcount++;
      }
    zval **p_lhs = &local_LF638;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_hash1 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_hash1;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    cast_var (p_lhs, IS_ARRAY);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1106;
  {
    goto L1106;
    phc_check_invariants (TSRMLS_C);
  }
// L1115:
L1115:;
// $TLE223 = ($n - 1);
  {
    if (local_TLE223 == NULL)
      {
	local_TLE223 = EG (uninitialized_zval_ptr);
	local_TLE223->refcount++;
      }
    zval **p_lhs = &local_TLE223;
    zval *left;
    if (local_n == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_n;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $last = ('foo_' . $TLE223);
  {
    if (local_last == NULL)
      {
	local_last = EG (uninitialized_zval_ptr);
	local_last->refcount++;
      }
    zval **p_lhs = &local_last;
    zval *left = phc_const_pool_string_11;
    zval *right;
    if (local_TLE223 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE223;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi225 = $hash1['foo_0'];
  {
    if (local_TSi225 == NULL)
      {
	local_TSi225 = EG (uninitialized_zval_ptr);
	local_TSi225->refcount++;
      }
    zval **p_lhs = &local_TSi225;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_hash1 == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_hash1;
      }
    zval *ra_index = phc_const_pool_string_12;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE226 = ('' . $TSi225);
  {
    if (local_TLE226 == NULL)
      {
	local_TLE226 = EG (uninitialized_zval_ptr);
	local_TLE226->refcount++;
      }
    zval **p_lhs = &local_TLE226;
    zval *left = phc_const_pool_string_8;
    zval *right;
    if (local_TSi225 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi225;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE228 = ($TLE226 . ' ');
  {
    if (local_TLE228 == NULL)
      {
	local_TLE228 = EG (uninitialized_zval_ptr);
	local_TLE228->refcount++;
      }
    zval **p_lhs = &local_TLE228;
    zval *left;
    if (local_TLE226 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE226;
      }
    zval *right = phc_const_pool_string_9;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi229 = $hash1[$last];
  {
    if (local_TSi229 == NULL)
      {
	local_TSi229 = EG (uninitialized_zval_ptr);
	local_TSi229->refcount++;
      }
    zval **p_lhs = &local_TSi229;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_hash1 == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_hash1;
      }
    zval *ra_index;
    if (local_last == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_last;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE230 = ($TLE228 . $TSi229);
  {
    if (local_TLE230 == NULL)
      {
	local_TLE230 = EG (uninitialized_zval_ptr);
	local_TLE230->refcount++;
      }
    zval **p_lhs = &local_TLE230;
    zval *left;
    if (local_TLE228 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE228;
      }
    zval *right;
    if (local_TSi229 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi229;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE232 = ($TLE230 . ' ');
  {
    if (local_TLE232 == NULL)
      {
	local_TLE232 = EG (uninitialized_zval_ptr);
	local_TLE232->refcount++;
      }
    zval **p_lhs = &local_TLE232;
    zval *left;
    if (local_TLE230 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE230;
      }
    zval *right = phc_const_pool_string_9;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi233 = $hash2['foo_0'];
  {
    if (local_TSi233 == NULL)
      {
	local_TSi233 = EG (uninitialized_zval_ptr);
	local_TSi233->refcount++;
      }
    zval **p_lhs = &local_TSi233;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_hash2 == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_hash2;
      }
    zval *ra_index = phc_const_pool_string_12;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE234 = ($TLE232 . $TSi233);
  {
    if (local_TLE234 == NULL)
      {
	local_TLE234 = EG (uninitialized_zval_ptr);
	local_TLE234->refcount++;
      }
    zval **p_lhs = &local_TLE234;
    zval *left;
    if (local_TLE232 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE232;
      }
    zval *right;
    if (local_TSi233 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi233;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE236 = ($TLE234 . ' ');
  {
    if (local_TLE236 == NULL)
      {
	local_TLE236 = EG (uninitialized_zval_ptr);
	local_TLE236->refcount++;
      }
    zval **p_lhs = &local_TLE236;
    zval *left;
    if (local_TLE234 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE234;
      }
    zval *right = phc_const_pool_string_9;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi237 = $hash2[$last];
  {
    if (local_TSi237 == NULL)
      {
	local_TSi237 = EG (uninitialized_zval_ptr);
	local_TSi237->refcount++;
      }
    zval **p_lhs = &local_TSi237;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_hash2 == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_hash2;
      }
    zval *ra_index;
    if (local_last == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_last;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE238 = ($TLE236 . $TSi237);
  {
    if (local_TLE238 == NULL)
      {
	local_TLE238 = EG (uninitialized_zval_ptr);
	local_TLE238->refcount++;
      }
    zval **p_lhs = &local_TLE238;
    zval *left;
    if (local_TLE236 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE236;
      }
    zval *right;
    if (local_TSi237 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi237;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE240 = ($TLE238 . '
// ');
  {
    if (local_TLE240 == NULL)
      {
	local_TLE240 = EG (uninitialized_zval_ptr);
	local_TLE240->refcount++;
      }
    zval **p_lhs = &local_TLE240;
    zval *left;
    if (local_TLE238 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE238;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE240);
  {
    zval *p_arg;
    if (local_TLE240 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE240;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1086;
  {
    goto L1086;
    phc_check_invariants (TSRMLS_C);
  }
// L1091:
L1091:;
// $TLE210 = ('foo_' . $i);
  {
    if (local_TLE210 == NULL)
      {
	local_TLE210 = EG (uninitialized_zval_ptr);
	local_TLE210->refcount++;
      }
    zval **p_lhs = &local_TLE210;
    zval *left = phc_const_pool_string_11;
    zval *right;
    if (local_i == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_i;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE212 = ($TLE210 . '');
  {
    if (local_TLE212 == NULL)
      {
	local_TLE212 = EG (uninitialized_zval_ptr);
	local_TLE212->refcount++;
      }
    zval **p_lhs = &local_TLE212;
    zval *left;
    if (local_TLE210 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE210;
      }
    zval *right = phc_const_pool_string_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $hash1[$TLE212] = $i;
  {
    if (local_hash1 == NULL)
      {
	local_hash1 = EG (uninitialized_zval_ptr);
	local_hash1->refcount++;
      }
    zval **p_lhs_var = &local_hash1;
    zval *p_lhs_index;
    if (local_TLE212 == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_TLE212;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE214 = ('foo_' . $i);
  {
    if (local_TLE214 == NULL)
      {
	local_TLE214 = EG (uninitialized_zval_ptr);
	local_TLE214->refcount++;
      }
    zval **p_lhs = &local_TLE214;
    zval *left = phc_const_pool_string_11;
    zval *right;
    if (local_i == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_i;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE216 = ($TLE214 . '');
  {
    if (local_TLE216 == NULL)
      {
	local_TLE216 = EG (uninitialized_zval_ptr);
	local_TLE216->refcount++;
      }
    zval **p_lhs = &local_TLE216;
    zval *left;
    if (local_TLE214 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE214;
      }
    zval *right = phc_const_pool_string_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $hash2[$TLE216] = 0;
  {
    if (local_hash2 == NULL)
      {
	local_hash2 = EG (uninitialized_zval_ptr);
	local_hash2->refcount++;
      }
    zval **p_lhs_var = &local_hash2;
    zval *p_lhs_index;
    if (local_TLE216 == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_TLE216;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var = phc_const_pool_int_0;
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1089;
  {
    goto L1089;
    phc_check_invariants (TSRMLS_C);
  }
// L1086:
L1086:;
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_LF638 != NULL)
    {
      zval_ptr_dtor (&local_LF638);
    }
  if (local_THK648 != NULL)
    {
      zval_ptr_dtor (&local_THK648);
    }
  if (local_TLE208 != NULL)
    {
      zval_ptr_dtor (&local_TLE208);
    }
  if (local_TLE210 != NULL)
    {
      zval_ptr_dtor (&local_TLE210);
    }
  if (local_TLE212 != NULL)
    {
      zval_ptr_dtor (&local_TLE212);
    }
  if (local_TLE214 != NULL)
    {
      zval_ptr_dtor (&local_TLE214);
    }
  if (local_TLE216 != NULL)
    {
      zval_ptr_dtor (&local_TLE216);
    }
  if (local_TLE219 != NULL)
    {
      zval_ptr_dtor (&local_TLE219);
    }
  if (local_TLE223 != NULL)
    {
      zval_ptr_dtor (&local_TLE223);
    }
  if (local_TLE226 != NULL)
    {
      zval_ptr_dtor (&local_TLE226);
    }
  if (local_TLE228 != NULL)
    {
      zval_ptr_dtor (&local_TLE228);
    }
  if (local_TLE230 != NULL)
    {
      zval_ptr_dtor (&local_TLE230);
    }
  if (local_TLE232 != NULL)
    {
      zval_ptr_dtor (&local_TLE232);
    }
  if (local_TLE234 != NULL)
    {
      zval_ptr_dtor (&local_TLE234);
    }
  if (local_TLE236 != NULL)
    {
      zval_ptr_dtor (&local_TLE236);
    }
  if (local_TLE238 != NULL)
    {
      zval_ptr_dtor (&local_TLE238);
    }
  if (local_TLE240 != NULL)
    {
      zval_ptr_dtor (&local_TLE240);
    }
  if (local_TLE639 != NULL)
    {
      zval_ptr_dtor (&local_TLE639);
    }
  if (local_TSi220 != NULL)
    {
      zval_ptr_dtor (&local_TSi220);
    }
  if (local_TSi225 != NULL)
    {
      zval_ptr_dtor (&local_TSi225);
    }
  if (local_TSi229 != NULL)
    {
      zval_ptr_dtor (&local_TSi229);
    }
  if (local_TSi233 != NULL)
    {
      zval_ptr_dtor (&local_TSi233);
    }
  if (local_TSi237 != NULL)
    {
      zval_ptr_dtor (&local_TSi237);
    }
  if (local_hash1 != NULL)
    {
      zval_ptr_dtor (&local_hash1);
    }
  if (local_hash2 != NULL)
    {
      zval_ptr_dtor (&local_hash2);
    }
  if (local_i != NULL)
    {
      zval_ptr_dtor (&local_i);
    }
  if (local_key != NULL)
    {
      zval_ptr_dtor (&local_key);
    }
  if (local_last != NULL)
    {
      zval_ptr_dtor (&local_last);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
  if (local_value != NULL)
    {
      zval_ptr_dtor (&local_value);
    }
}

// function gen_random($n)
// {
// \011global $LAST;
// \011$TLE241 = IA;
// \011$TLE242 = ($LAST * $TLE241);
// \011$TLE243 = IC;
// \011$TLE244 = ($TLE242 + $TLE243);
// \011$TLE245 = IM;
// \011$LAST = ($TLE244 % $TLE245);
// \011$TLE246 = $LAST;
// \011$TLE247 = ($n * $TLE246);
// \011$TLE248 = IM;
// \011$TLE249 = ($TLE247 / $TLE248);
// \011return $TLE249;
// }
PHP_FUNCTION (gen_random)
{
  zval *local_LAST = NULL;
  zval *local_TLE241 = NULL;
  zval *local_TLE242 = NULL;
  zval *local_TLE243 = NULL;
  zval *local_TLE244 = NULL;
  zval *local_TLE245 = NULL;
  zval *local_TLE246 = NULL;
  zval *local_TLE247 = NULL;
  zval *local_TLE248 = NULL;
  zval *local_TLE249 = NULL;
  zval *local_n = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// global $LAST;
  {
// Normal global
    if (local_LAST == NULL)
      {
	local_LAST = EG (uninitialized_zval_ptr);
	local_LAST->refcount++;
      }
    zval **p_local_global_var = &local_LAST;
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "LAST", 5, 210680108793u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE241 = IA;
  {
    if (local_TLE241 == NULL)
      {
	local_TLE241 = EG (uninitialized_zval_ptr);
	local_TLE241->refcount++;
      }
    zval **p_lhs = &local_TLE241;
    if (!(*p_lhs)->is_ref)
      {
	zval_ptr_dtor (p_lhs);
	get_constant ("IA", 2, p_lhs TSRMLS_CC);
      }
    else
      {
	zval *constant;
	get_constant ("IA", 2, &constant TSRMLS_CC);
	overwrite_lhs_no_copy (*p_lhs, constant);
	safe_free_zval_ptr (constant);
      }
    phc_check_invariants (TSRMLS_C);
  }
// $TLE242 = ($LAST * $TLE241);
  {
    if (local_TLE242 == NULL)
      {
	local_TLE242 = EG (uninitialized_zval_ptr);
	local_TLE242->refcount++;
      }
    zval **p_lhs = &local_TLE242;
    zval *left;
    if (local_LAST == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_LAST;
      }
    zval *right;
    if (local_TLE241 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE241;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    mul_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE243 = IC;
  {
    if (local_TLE243 == NULL)
      {
	local_TLE243 = EG (uninitialized_zval_ptr);
	local_TLE243->refcount++;
      }
    zval **p_lhs = &local_TLE243;
    if (!(*p_lhs)->is_ref)
      {
	zval_ptr_dtor (p_lhs);
	get_constant ("IC", 2, p_lhs TSRMLS_CC);
      }
    else
      {
	zval *constant;
	get_constant ("IC", 2, &constant TSRMLS_CC);
	overwrite_lhs_no_copy (*p_lhs, constant);
	safe_free_zval_ptr (constant);
      }
    phc_check_invariants (TSRMLS_C);
  }
// $TLE244 = ($TLE242 + $TLE243);
  {
    if (local_TLE244 == NULL)
      {
	local_TLE244 = EG (uninitialized_zval_ptr);
	local_TLE244->refcount++;
      }
    zval **p_lhs = &local_TLE244;
    zval *left;
    if (local_TLE242 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE242;
      }
    zval *right;
    if (local_TLE243 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE243;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE245 = IM;
  {
    if (local_TLE245 == NULL)
      {
	local_TLE245 = EG (uninitialized_zval_ptr);
	local_TLE245->refcount++;
      }
    zval **p_lhs = &local_TLE245;
    if (!(*p_lhs)->is_ref)
      {
	zval_ptr_dtor (p_lhs);
	get_constant ("IM", 2, p_lhs TSRMLS_CC);
      }
    else
      {
	zval *constant;
	get_constant ("IM", 2, &constant TSRMLS_CC);
	overwrite_lhs_no_copy (*p_lhs, constant);
	safe_free_zval_ptr (constant);
      }
    phc_check_invariants (TSRMLS_C);
  }
// $LAST = ($TLE244 % $TLE245);
  {
    if (local_LAST == NULL)
      {
	local_LAST = EG (uninitialized_zval_ptr);
	local_LAST->refcount++;
      }
    zval **p_lhs = &local_LAST;
    zval *left;
    if (local_TLE244 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE244;
      }
    zval *right;
    if (local_TLE245 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE245;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    mod_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE246 = $LAST;
  {
    if (local_TLE246 == NULL)
      {
	local_TLE246 = EG (uninitialized_zval_ptr);
	local_TLE246->refcount++;
      }
    zval **p_lhs = &local_TLE246;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_LAST == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_LAST;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE247 = ($n * $TLE246);
  {
    if (local_TLE247 == NULL)
      {
	local_TLE247 = EG (uninitialized_zval_ptr);
	local_TLE247->refcount++;
      }
    zval **p_lhs = &local_TLE247;
    zval *left;
    if (local_n == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_n;
      }
    zval *right;
    if (local_TLE246 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE246;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    mul_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE248 = IM;
  {
    if (local_TLE248 == NULL)
      {
	local_TLE248 = EG (uninitialized_zval_ptr);
	local_TLE248->refcount++;
      }
    zval **p_lhs = &local_TLE248;
    if (!(*p_lhs)->is_ref)
      {
	zval_ptr_dtor (p_lhs);
	get_constant ("IM", 2, p_lhs TSRMLS_CC);
      }
    else
      {
	zval *constant;
	get_constant ("IM", 2, &constant TSRMLS_CC);
	overwrite_lhs_no_copy (*p_lhs, constant);
	safe_free_zval_ptr (constant);
      }
    phc_check_invariants (TSRMLS_C);
  }
// $TLE249 = ($TLE247 / $TLE248);
  {
    if (local_TLE249 == NULL)
      {
	local_TLE249 = EG (uninitialized_zval_ptr);
	local_TLE249->refcount++;
      }
    zval **p_lhs = &local_TLE249;
    zval *left;
    if (local_TLE247 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE247;
      }
    zval *right;
    if (local_TLE248 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE248;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    div_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// return $TLE249;
  {
    zval *rhs;
    if (local_TLE249 == NULL)
      {
	rhs = EG (uninitialized_zval_ptr);
      }
    else
      {
	rhs = local_TLE249;
      }
    return_value->value = rhs->value;
    return_value->type = rhs->type;
    zval_copy_ctor (return_value);
    goto end_of_function;
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_LAST != NULL)
    {
      zval_ptr_dtor (&local_LAST);
    }
  if (local_TLE241 != NULL)
    {
      zval_ptr_dtor (&local_TLE241);
    }
  if (local_TLE242 != NULL)
    {
      zval_ptr_dtor (&local_TLE242);
    }
  if (local_TLE243 != NULL)
    {
      zval_ptr_dtor (&local_TLE243);
    }
  if (local_TLE244 != NULL)
    {
      zval_ptr_dtor (&local_TLE244);
    }
  if (local_TLE245 != NULL)
    {
      zval_ptr_dtor (&local_TLE245);
    }
  if (local_TLE246 != NULL)
    {
      zval_ptr_dtor (&local_TLE246);
    }
  if (local_TLE247 != NULL)
    {
      zval_ptr_dtor (&local_TLE247);
    }
  if (local_TLE248 != NULL)
    {
      zval_ptr_dtor (&local_TLE248);
    }
  if (local_TLE249 != NULL)
    {
      zval_ptr_dtor (&local_TLE249);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
}

// function heapsort_r($n, &$ra)
// {
// \011$TLE251 = ($n >> 1);
// \011$l = ($TLE251 + 1);
// \011$ir = $n;
// \011L1149:
// \011$TLE256 = ($l > 1);
// \011if (TLE256) goto L1151 else goto L1154;
// \011L1151:
// \011--$l;
// \011$TSi257 = $ra[$l];
// \011$rra = $TSi257;
// \011L1164:
// \011$i = $l;
// \011$j = ($l << 1);
// \011L1166:
// \011$TLE266 = ($j <= $ir);
// \011if (TLE266) goto L1168 else goto L1187;
// \011L1168:
// \011$TLE38 = ($j < $ir);
// \011if (TLE38) goto L1170 else goto L1174;
// \011L1170:
// \011$TSi268 = $ra[$j];
// \011$TLE270 = ($j + 1);
// \011$TSi271 = $ra[$TLE270];
// \011$TEF39 = ($TSi268 < $TSi271);
// \011L1175:
// \011$TLE272 = (bool) $TEF39;
// \011if (TLE272) goto L1177 else goto L1178;
// \011L1177:
// \011++$j;
// \011L1178:
// \011$TSi273 = $ra[$j];
// \011$TLE274 = ($rra < $TSi273);
// \011if (TLE274) goto L1181 else goto L1186;
// \011L1181:
// \011$TSi275 = $ra[$j];
// \011$ra[$i] = $TSi275;
// \011$i = $j;
// \011$TLE276 = $i;
// \011$j = ($j + $TLE276);
// \011goto L1166;
// \011L1186:
// \011$j = ($ir + 1);
// \011goto L1166;
// \011L1174:
// \011$TEF39 = $TLE38;
// \011goto L1175;
// \011L1187:
// \011$ra[$i] = $rra;
// \011goto L1149;
// \011L1154:
// \011$TSi258 = $ra[$ir];
// \011$rra = $TSi258;
// \011$TSi260 = $ra[1];
// \011$ra[$ir] = $TSi260;
// \011--$ir;
// \011$TLE262 = ($ir == 1);
// \011if (TLE262) goto L1161 else goto L1164;
// \011L1161:
// \011$ra[1] = $rra;
// \011$TLE264 = NULL;
// \011return $TLE264;
// }
PHP_FUNCTION (heapsort_r)
{
  zval *local_TEF39 = NULL;
  zval *local_TLE251 = NULL;
  zval *local_TLE256 = NULL;
  zval *local_TLE262 = NULL;
  zval *local_TLE264 = NULL;
  zval *local_TLE266 = NULL;
  zval *local_TLE270 = NULL;
  zval *local_TLE272 = NULL;
  zval *local_TLE274 = NULL;
  zval *local_TLE276 = NULL;
  zval *local_TLE38 = NULL;
  zval *local_TSi257 = NULL;
  zval *local_TSi258 = NULL;
  zval *local_TSi260 = NULL;
  zval *local_TSi268 = NULL;
  zval *local_TSi271 = NULL;
  zval *local_TSi273 = NULL;
  zval *local_TSi275 = NULL;
  zval *local_i = NULL;
  zval *local_ir = NULL;
  zval *local_j = NULL;
  zval *local_l = NULL;
  zval *local_n = NULL;
  zval *local_ra = NULL;
  zval *local_rra = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[2];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
// param 1
    params[1]->refcount++;
    local_ra = params[1];
  }
// Function body
// $TLE251 = ($n >> 1);
  {
    if (local_TLE251 == NULL)
      {
	local_TLE251 = EG (uninitialized_zval_ptr);
	local_TLE251->refcount++;
      }
    zval **p_lhs = &local_TLE251;
    zval *left;
    if (local_n == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_n;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    shift_right_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $l = ($TLE251 + 1);
  {
    if (local_l == NULL)
      {
	local_l = EG (uninitialized_zval_ptr);
	local_l->refcount++;
      }
    zval **p_lhs = &local_l;
    zval *left;
    if (local_TLE251 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE251;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $ir = $n;
  {
    if (local_ir == NULL)
      {
	local_ir = EG (uninitialized_zval_ptr);
	local_ir->refcount++;
      }
    zval **p_lhs = &local_ir;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_n == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_n;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// L1149:
L1149:;
// $TLE256 = ($l > 1);
  {
    if (local_TLE256 == NULL)
      {
	local_TLE256 = EG (uninitialized_zval_ptr);
	local_TLE256->refcount++;
      }
    zval **p_lhs = &local_TLE256;
    zval *left;
    if (local_l == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_l;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, right, left TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE256) goto L1151 else goto L1154;
  {
    zval *p_cond;
    if (local_TLE256 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE256;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1151;
    else
      goto L1154;
    phc_check_invariants (TSRMLS_C);
  }
// L1151:
L1151:;
// --$l;
  {
    if (local_l == NULL)
      {
	local_l = EG (uninitialized_zval_ptr);
	local_l->refcount++;
      }
    zval **p_var = &local_l;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi257 = $ra[$l];
  {
    if (local_TSi257 == NULL)
      {
	local_TSi257 = EG (uninitialized_zval_ptr);
	local_TSi257->refcount++;
      }
    zval **p_lhs = &local_TSi257;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_ra == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_ra;
      }
    zval *ra_index;
    if (local_l == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_l;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $rra = $TSi257;
  {
    if (local_rra == NULL)
      {
	local_rra = EG (uninitialized_zval_ptr);
	local_rra->refcount++;
      }
    zval **p_lhs = &local_rra;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_TSi257 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi257;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// L1164:
L1164:;
// $i = $l;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_l == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_l;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $j = ($l << 1);
  {
    if (local_j == NULL)
      {
	local_j = EG (uninitialized_zval_ptr);
	local_j->refcount++;
      }
    zval **p_lhs = &local_j;
    zval *left;
    if (local_l == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_l;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    shift_left_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// L1166:
L1166:;
// $TLE266 = ($j <= $ir);
  {
    if (local_TLE266 == NULL)
      {
	local_TLE266 = EG (uninitialized_zval_ptr);
	local_TLE266->refcount++;
      }
    zval **p_lhs = &local_TLE266;
    zval *left;
    if (local_j == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_j;
      }
    zval *right;
    if (local_ir == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_ir;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_or_equal_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE266) goto L1168 else goto L1187;
  {
    zval *p_cond;
    if (local_TLE266 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE266;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1168;
    else
      goto L1187;
    phc_check_invariants (TSRMLS_C);
  }
// L1168:
L1168:;
// $TLE38 = ($j < $ir);
  {
    if (local_TLE38 == NULL)
      {
	local_TLE38 = EG (uninitialized_zval_ptr);
	local_TLE38->refcount++;
      }
    zval **p_lhs = &local_TLE38;
    zval *left;
    if (local_j == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_j;
      }
    zval *right;
    if (local_ir == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_ir;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE38) goto L1170 else goto L1174;
  {
    zval *p_cond;
    if (local_TLE38 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE38;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1170;
    else
      goto L1174;
    phc_check_invariants (TSRMLS_C);
  }
// L1170:
L1170:;
// $TSi268 = $ra[$j];
  {
    if (local_TSi268 == NULL)
      {
	local_TSi268 = EG (uninitialized_zval_ptr);
	local_TSi268->refcount++;
      }
    zval **p_lhs = &local_TSi268;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_ra == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_ra;
      }
    zval *ra_index;
    if (local_j == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_j;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE270 = ($j + 1);
  {
    if (local_TLE270 == NULL)
      {
	local_TLE270 = EG (uninitialized_zval_ptr);
	local_TLE270->refcount++;
      }
    zval **p_lhs = &local_TLE270;
    zval *left;
    if (local_j == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_j;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi271 = $ra[$TLE270];
  {
    if (local_TSi271 == NULL)
      {
	local_TSi271 = EG (uninitialized_zval_ptr);
	local_TSi271->refcount++;
      }
    zval **p_lhs = &local_TSi271;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_ra == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_ra;
      }
    zval *ra_index;
    if (local_TLE270 == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_TLE270;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TEF39 = ($TSi268 < $TSi271);
  {
    if (local_TEF39 == NULL)
      {
	local_TEF39 = EG (uninitialized_zval_ptr);
	local_TEF39->refcount++;
      }
    zval **p_lhs = &local_TEF39;
    zval *left;
    if (local_TSi268 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TSi268;
      }
    zval *right;
    if (local_TSi271 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi271;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// L1175:
L1175:;
// $TLE272 = (bool) $TEF39;
  {
    if (local_TLE272 == NULL)
      {
	local_TLE272 = EG (uninitialized_zval_ptr);
	local_TLE272->refcount++;
      }
    zval **p_lhs = &local_TLE272;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_TEF39 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TEF39;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    cast_var (p_lhs, IS_BOOL);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE272) goto L1177 else goto L1178;
  {
    zval *p_cond;
    if (local_TLE272 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE272;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1177;
    else
      goto L1178;
    phc_check_invariants (TSRMLS_C);
  }
// L1177:
L1177:;
// ++$j;
  {
    if (local_j == NULL)
      {
	local_j = EG (uninitialized_zval_ptr);
	local_j->refcount++;
      }
    zval **p_var = &local_j;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// L1178:
L1178:;
// $TSi273 = $ra[$j];
  {
    if (local_TSi273 == NULL)
      {
	local_TSi273 = EG (uninitialized_zval_ptr);
	local_TSi273->refcount++;
      }
    zval **p_lhs = &local_TSi273;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_ra == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_ra;
      }
    zval *ra_index;
    if (local_j == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_j;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE274 = ($rra < $TSi273);
  {
    if (local_TLE274 == NULL)
      {
	local_TLE274 = EG (uninitialized_zval_ptr);
	local_TLE274->refcount++;
      }
    zval **p_lhs = &local_TLE274;
    zval *left;
    if (local_rra == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_rra;
      }
    zval *right;
    if (local_TSi273 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi273;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE274) goto L1181 else goto L1186;
  {
    zval *p_cond;
    if (local_TLE274 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE274;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1181;
    else
      goto L1186;
    phc_check_invariants (TSRMLS_C);
  }
// L1181:
L1181:;
// $TSi275 = $ra[$j];
  {
    if (local_TSi275 == NULL)
      {
	local_TSi275 = EG (uninitialized_zval_ptr);
	local_TSi275->refcount++;
      }
    zval **p_lhs = &local_TSi275;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_ra == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_ra;
      }
    zval *ra_index;
    if (local_j == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_j;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $ra[$i] = $TSi275;
  {
    if (local_ra == NULL)
      {
	local_ra = EG (uninitialized_zval_ptr);
	local_ra->refcount++;
      }
    zval **p_lhs_var = &local_ra;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi275 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi275;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $i = $j;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_j == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_j;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE276 = $i;
  {
    if (local_TLE276 == NULL)
      {
	local_TLE276 = EG (uninitialized_zval_ptr);
	local_TLE276->refcount++;
      }
    zval **p_lhs = &local_TLE276;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_i == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_i;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $j = ($j + $TLE276);
  {
    if (local_j == NULL)
      {
	local_j = EG (uninitialized_zval_ptr);
	local_j->refcount++;
      }
    zval **p_lhs = &local_j;
    zval *left;
    if (local_j == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_j;
      }
    zval *right;
    if (local_TLE276 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE276;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1166;
  {
    goto L1166;
    phc_check_invariants (TSRMLS_C);
  }
// L1186:
L1186:;
// $j = ($ir + 1);
  {
    if (local_j == NULL)
      {
	local_j = EG (uninitialized_zval_ptr);
	local_j->refcount++;
      }
    zval **p_lhs = &local_j;
    zval *left;
    if (local_ir == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_ir;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1166;
  {
    goto L1166;
    phc_check_invariants (TSRMLS_C);
  }
// L1174:
L1174:;
// $TEF39 = $TLE38;
  {
    if (local_TEF39 == NULL)
      {
	local_TEF39 = EG (uninitialized_zval_ptr);
	local_TEF39->refcount++;
      }
    zval **p_lhs = &local_TEF39;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_TLE38 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TLE38;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1175;
  {
    goto L1175;
    phc_check_invariants (TSRMLS_C);
  }
// L1187:
L1187:;
// $ra[$i] = $rra;
  {
    if (local_ra == NULL)
      {
	local_ra = EG (uninitialized_zval_ptr);
	local_ra->refcount++;
      }
    zval **p_lhs_var = &local_ra;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_rra == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_rra;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1149;
  {
    goto L1149;
    phc_check_invariants (TSRMLS_C);
  }
// L1154:
L1154:;
// $TSi258 = $ra[$ir];
  {
    if (local_TSi258 == NULL)
      {
	local_TSi258 = EG (uninitialized_zval_ptr);
	local_TSi258->refcount++;
      }
    zval **p_lhs = &local_TSi258;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_ra == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_ra;
      }
    zval *ra_index;
    if (local_ir == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_ir;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $rra = $TSi258;
  {
    if (local_rra == NULL)
      {
	local_rra = EG (uninitialized_zval_ptr);
	local_rra->refcount++;
      }
    zval **p_lhs = &local_rra;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_TSi258 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi258;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi260 = $ra[1];
  {
    if (local_TSi260 == NULL)
      {
	local_TSi260 = EG (uninitialized_zval_ptr);
	local_TSi260->refcount++;
      }
    zval **p_lhs = &local_TSi260;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_ra == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_ra;
      }
    zval *ra_index = phc_const_pool_int_8;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $ra[$ir] = $TSi260;
  {
    if (local_ra == NULL)
      {
	local_ra = EG (uninitialized_zval_ptr);
	local_ra->refcount++;
      }
    zval **p_lhs_var = &local_ra;
    zval *p_lhs_index;
    if (local_ir == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_ir;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TSi260 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSi260;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$ir;
  {
    if (local_ir == NULL)
      {
	local_ir = EG (uninitialized_zval_ptr);
	local_ir->refcount++;
      }
    zval **p_var = &local_ir;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE262 = ($ir == 1);
  {
    if (local_TLE262 == NULL)
      {
	local_TLE262 = EG (uninitialized_zval_ptr);
	local_TLE262->refcount++;
      }
    zval **p_lhs = &local_TLE262;
    zval *left;
    if (local_ir == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_ir;
      }
    zval *right = phc_const_pool_int_8;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_equal_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE262) goto L1161 else goto L1164;
  {
    zval *p_cond;
    if (local_TLE262 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE262;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1161;
    else
      goto L1164;
    phc_check_invariants (TSRMLS_C);
  }
// L1161:
L1161:;
// $ra[1] = $rra;
  {
    if (local_ra == NULL)
      {
	local_ra = EG (uninitialized_zval_ptr);
	local_ra->refcount++;
      }
    zval **p_lhs_var = &local_ra;
    zval *p_lhs_index = phc_const_pool_int_8;
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_rra == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_rra;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE264 = NULL;
  {
    if (local_TLE264 == NULL)
      {
	local_TLE264 = EG (uninitialized_zval_ptr);
	local_TLE264->refcount++;
      }
    zval **p_lhs = &local_TLE264;
    if (phc_const_pool_null_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_null_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// return $TLE264;
  {
    zval *rhs;
    if (local_TLE264 == NULL)
      {
	rhs = EG (uninitialized_zval_ptr);
      }
    else
      {
	rhs = local_TLE264;
      }
    return_value->value = rhs->value;
    return_value->type = rhs->type;
    zval_copy_ctor (return_value);
    goto end_of_function;
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TEF39 != NULL)
    {
      zval_ptr_dtor (&local_TEF39);
    }
  if (local_TLE251 != NULL)
    {
      zval_ptr_dtor (&local_TLE251);
    }
  if (local_TLE256 != NULL)
    {
      zval_ptr_dtor (&local_TLE256);
    }
  if (local_TLE262 != NULL)
    {
      zval_ptr_dtor (&local_TLE262);
    }
  if (local_TLE264 != NULL)
    {
      zval_ptr_dtor (&local_TLE264);
    }
  if (local_TLE266 != NULL)
    {
      zval_ptr_dtor (&local_TLE266);
    }
  if (local_TLE270 != NULL)
    {
      zval_ptr_dtor (&local_TLE270);
    }
  if (local_TLE272 != NULL)
    {
      zval_ptr_dtor (&local_TLE272);
    }
  if (local_TLE274 != NULL)
    {
      zval_ptr_dtor (&local_TLE274);
    }
  if (local_TLE276 != NULL)
    {
      zval_ptr_dtor (&local_TLE276);
    }
  if (local_TLE38 != NULL)
    {
      zval_ptr_dtor (&local_TLE38);
    }
  if (local_TSi257 != NULL)
    {
      zval_ptr_dtor (&local_TSi257);
    }
  if (local_TSi258 != NULL)
    {
      zval_ptr_dtor (&local_TSi258);
    }
  if (local_TSi260 != NULL)
    {
      zval_ptr_dtor (&local_TSi260);
    }
  if (local_TSi268 != NULL)
    {
      zval_ptr_dtor (&local_TSi268);
    }
  if (local_TSi271 != NULL)
    {
      zval_ptr_dtor (&local_TSi271);
    }
  if (local_TSi273 != NULL)
    {
      zval_ptr_dtor (&local_TSi273);
    }
  if (local_TSi275 != NULL)
    {
      zval_ptr_dtor (&local_TSi275);
    }
  if (local_i != NULL)
    {
      zval_ptr_dtor (&local_i);
    }
  if (local_ir != NULL)
    {
      zval_ptr_dtor (&local_ir);
    }
  if (local_j != NULL)
    {
      zval_ptr_dtor (&local_j);
    }
  if (local_l != NULL)
    {
      zval_ptr_dtor (&local_l);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
  if (local_ra != NULL)
    {
      zval_ptr_dtor (&local_ra);
    }
  if (local_rra != NULL)
    {
      zval_ptr_dtor (&local_rra);
    }
}

// function heapsort($N)
// {
// \011global $LAST;
// \011define('IM', 139968);
// \011define('IA', 3877);
// \011define('IC', 29573);
// \011$LAST = 42;
// \011$i = 1;
// \011L1197:
// \011$TLE284 = ($i <= $N);
// \011if (TLE284) goto L1199 else goto L1201;
// \011L1201:
// \011heapsort_r($N, $ary);
// \011$TLE441 = param_is_ref (NULL, \"printf\", 0);
// \011;
// \011if (TLE441) goto L1204 else goto L1205;
// \011L1204:
// \011$TMIi440 =& $ary[$N];
// \011L1206:
// \011printf('%.10f
// ', $TMIi440);
// \011goto L1189;
// \011L1205:
// \011$TMIi440 = $ary[$N];
// \011goto L1206;
// \011L1199:
// \011$TLE286 = gen_random(1);
// \011$ary[$i] = $TLE286;
// \011++$i;
// \011goto L1197;
// \011L1189:
// }
PHP_FUNCTION (heapsort)
{
  zval *local_LAST = NULL;
  zval *local_N = NULL;
  zval *local_TLE284 = NULL;
  zval *local_TLE286 = NULL;
  zval *local_TLE441 = NULL;
  zval *local_TMIi440 = NULL;
  zval *local_ary = NULL;
  zval *local_i = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_N = params[0];
  }
// Function body
// global $LAST;
  {
// Normal global
    if (local_LAST == NULL)
      {
	local_LAST = EG (uninitialized_zval_ptr);
	local_LAST->refcount++;
      }
    zval **p_local_global_var = &local_LAST;
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "LAST", 5, 210680108793u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// define('IM', 139968);
  {
    initialize_function_call (&define_fci, &define_fcic, "define",
			      "test/subjects/benchmarks/zend/bench.php",
			      251 TSRMLS_CC);
    zend_function *signature = define_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_string_13;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_int_16;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = define_fci.param_count;
    zval ***params_save = define_fci.params;
    zval **retval_save = define_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    define_fci.params = args_ind;
    define_fci.param_count = 2;
    define_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&define_fci, &define_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    define_fci.params = params_save;
    define_fci.param_count = param_count_save;
    define_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// define('IA', 3877);
  {
    initialize_function_call (&define_fci, &define_fcic, "define",
			      "test/subjects/benchmarks/zend/bench.php",
			      252 TSRMLS_CC);
    zend_function *signature = define_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_string_14;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_int_17;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = define_fci.param_count;
    zval ***params_save = define_fci.params;
    zval **retval_save = define_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    define_fci.params = args_ind;
    define_fci.param_count = 2;
    define_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&define_fci, &define_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    define_fci.params = params_save;
    define_fci.param_count = param_count_save;
    define_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// define('IC', 29573);
  {
    initialize_function_call (&define_fci, &define_fcic, "define",
			      "test/subjects/benchmarks/zend/bench.php",
			      253 TSRMLS_CC);
    zend_function *signature = define_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_string_15;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_int_18;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = define_fci.param_count;
    zval ***params_save = define_fci.params;
    zval **retval_save = define_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    define_fci.params = args_ind;
    define_fci.param_count = 2;
    define_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&define_fci, &define_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    define_fci.params = params_save;
    define_fci.param_count = param_count_save;
    define_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $LAST = 42;
  {
    if (local_LAST == NULL)
      {
	local_LAST = EG (uninitialized_zval_ptr);
	local_LAST->refcount++;
      }
    zval **p_lhs = &local_LAST;
    if (phc_const_pool_int_19 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_19, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// $i = 1;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    if (phc_const_pool_int_8 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_8, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1197:
L1197:;
// $TLE284 = ($i <= $N);
  {
    if (local_TLE284 == NULL)
      {
	local_TLE284 = EG (uninitialized_zval_ptr);
	local_TLE284->refcount++;
      }
    zval **p_lhs = &local_TLE284;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right;
    if (local_N == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_N;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_or_equal_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE284) goto L1199 else goto L1201;
  {
    zval *p_cond;
    if (local_TLE284 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE284;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1199;
    else
      goto L1201;
    phc_check_invariants (TSRMLS_C);
  }
// L1201:
L1201:;
// heapsort_r($N, $ary);
  {
    initialize_function_call (&heapsort_r_fci, &heapsort_r_fcic, "heapsort_r",
			      "test/subjects/benchmarks/zend/bench.php",
			      259 TSRMLS_CC);
    zend_function *signature = heapsort_r_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_N == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_N;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      if (local_ary == NULL)
	{
	  local_ary = EG (uninitialized_zval_ptr);
	  local_ary->refcount++;
	}
      zval **p_arg = &local_ary;
      args_ind[1] = fetch_var_arg_by_ref (p_arg);
      assert (!in_copy_on_write (*args_ind[1]));
      args[1] = *args_ind[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = heapsort_r_fci.param_count;
    zval ***params_save = heapsort_r_fci.params;
    zval **retval_save = heapsort_r_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    heapsort_r_fci.params = args_ind;
    heapsort_r_fci.param_count = 2;
    heapsort_r_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&heapsort_r_fci, &heapsort_r_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    heapsort_r_fci.params = params_save;
    heapsort_r_fci.param_count = param_count_save;
    heapsort_r_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE441 = param_is_ref (NULL, \"printf\", 0);
// ;
  {
    if (local_TLE441 == NULL)
      {
	local_TLE441 = EG (uninitialized_zval_ptr);
	local_TLE441->refcount++;
      }
    zval **p_lhs = &local_TLE441;
    initialize_function_call (&printf_fci, &printf_fcic, "printf",
			      "<unknown>", 0 TSRMLS_CC);
    zend_function *signature = printf_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int count = 0;
    while (arg_info && count < 0)
      {
	count++;
	arg_info++;
      }
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    p_rhs = p_lhs;
    zvp_clone (p_rhs, &is_p_rhs_new);
    if (count == 0)
      {
	ZVAL_BOOL (*p_rhs, arg_info->pass_by_reference);
      }
    else
      {
	ZVAL_BOOL (*p_rhs, signature->common.pass_rest_by_reference);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE441) goto L1204 else goto L1205;
  {
    zval *p_cond;
    if (local_TLE441 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE441;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1204;
    else
      goto L1205;
    phc_check_invariants (TSRMLS_C);
  }
// L1204:
L1204:;
// $TMIi440 =& $ary[$N];
  {
    if (local_TMIi440 == NULL)
      {
	local_TMIi440 = EG (uninitialized_zval_ptr);
	local_TMIi440->refcount++;
      }
    zval **p_lhs = &local_TMIi440;
    if (local_ary == NULL)
      {
	local_ary = EG (uninitialized_zval_ptr);
	local_ary->refcount++;
      }
    zval **p_rhs_var = &local_ary;
    zval *p_rhs_index;
    if (local_N == NULL)
      {
	p_rhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_index = local_N;
      }
    zval **p_rhs = get_ht_entry (p_rhs_var, p_rhs_index TSRMLS_CC);
    copy_into_ref (p_lhs, p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// L1206:
L1206:;
// printf('%.10f
// ', $TMIi440);
  {
    initialize_function_call (&printf_fci, &printf_fcic, "printf",
			      "test/subjects/benchmarks/zend/bench.php",
			      260 TSRMLS_CC);
    zend_function *signature = printf_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_string_16;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg;
      if (local_TMIi440 == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_TMIi440;
	}
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = printf_fci.param_count;
    zval ***params_save = printf_fci.params;
    zval **retval_save = printf_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    printf_fci.params = args_ind;
    printf_fci.param_count = 2;
    printf_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&printf_fci, &printf_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    printf_fci.params = params_save;
    printf_fci.param_count = param_count_save;
    printf_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1189;
  {
    goto L1189;
    phc_check_invariants (TSRMLS_C);
  }
// L1205:
L1205:;
// $TMIi440 = $ary[$N];
  {
    if (local_TMIi440 == NULL)
      {
	local_TMIi440 = EG (uninitialized_zval_ptr);
	local_TMIi440->refcount++;
      }
    zval **p_lhs = &local_TMIi440;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_ary == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_ary;
      }
    zval *ra_index;
    if (local_N == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_N;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1206;
  {
    goto L1206;
    phc_check_invariants (TSRMLS_C);
  }
// L1199:
L1199:;
// $TLE286 = gen_random(1);
  {
    if (local_TLE286 == NULL)
      {
	local_TLE286 = EG (uninitialized_zval_ptr);
	local_TLE286->refcount++;
      }
    zval **p_lhs = &local_TLE286;
    initialize_function_call (&gen_random_fci, &gen_random_fcic, "gen_random",
			      "test/subjects/benchmarks/zend/bench.php",
			      257 TSRMLS_CC);
    zend_function *signature = gen_random_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_8;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = gen_random_fci.param_count;
    zval ***params_save = gen_random_fci.params;
    zval **retval_save = gen_random_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    gen_random_fci.params = args_ind;
    gen_random_fci.param_count = 1;
    gen_random_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&gen_random_fci, &gen_random_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    gen_random_fci.params = params_save;
    gen_random_fci.param_count = param_count_save;
    gen_random_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $ary[$i] = $TLE286;
  {
    if (local_ary == NULL)
      {
	local_ary = EG (uninitialized_zval_ptr);
	local_ary->refcount++;
      }
    zval **p_lhs_var = &local_ary;
    zval *p_lhs_index;
    if (local_i == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_i;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TLE286 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TLE286;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1197;
  {
    goto L1197;
    phc_check_invariants (TSRMLS_C);
  }
// L1189:
L1189:;
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_LAST != NULL)
    {
      zval_ptr_dtor (&local_LAST);
    }
  if (local_N != NULL)
    {
      zval_ptr_dtor (&local_N);
    }
  if (local_TLE284 != NULL)
    {
      zval_ptr_dtor (&local_TLE284);
    }
  if (local_TLE286 != NULL)
    {
      zval_ptr_dtor (&local_TLE286);
    }
  if (local_TLE441 != NULL)
    {
      zval_ptr_dtor (&local_TLE441);
    }
  if (local_TMIi440 != NULL)
    {
      zval_ptr_dtor (&local_TMIi440);
    }
  if (local_ary != NULL)
    {
      zval_ptr_dtor (&local_ary);
    }
  if (local_i != NULL)
    {
      zval_ptr_dtor (&local_i);
    }
}

// function mkmatrix($rows, $cols)
// {
// \011$count = 1;
// \011unset($TSa288);
// \011$TSa288 = (array) $TSa288;
// \011$mx = $TSa288;
// \011$i = 0;
// \011L1215:
// \011$TLE289 = ($i < $rows);
// \011if (TLE289) goto L1217 else goto L1225;
// \011L1217:
// \011$j = 0;
// \011L1219:
// \011$TLE290 = ($j < $cols);
// \011if (TLE290) goto L1221 else goto L1214;
// \011L1221:
// \011$TS42 = $count;
// \011++$count;
// \011$TSi291 =& $mx[$i];
// \011$TSi291[$j] = $TS42;
// \011++$j;
// \011goto L1219;
// \011L1214:
// \011++$i;
// \011goto L1215;
// \011L1225:
// \011return $mx;
// }
PHP_FUNCTION (mkmatrix)
{
  zval *local_TLE289 = NULL;
  zval *local_TLE290 = NULL;
  zval *local_TS42 = NULL;
  zval *local_TSa288 = NULL;
  zval *local_TSi291 = NULL;
  zval *local_cols = NULL;
  zval *local_count = NULL;
  zval *local_i = NULL;
  zval *local_j = NULL;
  zval *local_mx = NULL;
  zval *local_rows = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[2];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_rows = params[0];
// param 1
    params[1]->refcount++;
    local_cols = params[1];
  }
// Function body
// $count = 1;
  {
    if (local_count == NULL)
      {
	local_count = EG (uninitialized_zval_ptr);
	local_count->refcount++;
      }
    zval **p_lhs = &local_count;
    if (phc_const_pool_int_8 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_8, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// unset($TSa288);
  {
    if (local_TSa288 != NULL)
      {
	zval_ptr_dtor (&local_TSa288);
	local_TSa288 = NULL;
      }
    phc_check_invariants (TSRMLS_C);
  }
// $TSa288 = (array) $TSa288;
  {
    if (local_TSa288 == NULL)
      {
	local_TSa288 = EG (uninitialized_zval_ptr);
	local_TSa288->refcount++;
      }
    zval **p_lhs = &local_TSa288;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_TSa288 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSa288;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    cast_var (p_lhs, IS_ARRAY);
    phc_check_invariants (TSRMLS_C);
  }
// $mx = $TSa288;
  {
    if (local_mx == NULL)
      {
	local_mx = EG (uninitialized_zval_ptr);
	local_mx->refcount++;
      }
    zval **p_lhs = &local_mx;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_TSa288 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSa288;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $i = 0;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1215:
L1215:;
// $TLE289 = ($i < $rows);
  {
    if (local_TLE289 == NULL)
      {
	local_TLE289 = EG (uninitialized_zval_ptr);
	local_TLE289->refcount++;
      }
    zval **p_lhs = &local_TLE289;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right;
    if (local_rows == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_rows;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE289) goto L1217 else goto L1225;
  {
    zval *p_cond;
    if (local_TLE289 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE289;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1217;
    else
      goto L1225;
    phc_check_invariants (TSRMLS_C);
  }
// L1217:
L1217:;
// $j = 0;
  {
    if (local_j == NULL)
      {
	local_j = EG (uninitialized_zval_ptr);
	local_j->refcount++;
      }
    zval **p_lhs = &local_j;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1219:
L1219:;
// $TLE290 = ($j < $cols);
  {
    if (local_TLE290 == NULL)
      {
	local_TLE290 = EG (uninitialized_zval_ptr);
	local_TLE290->refcount++;
      }
    zval **p_lhs = &local_TLE290;
    zval *left;
    if (local_j == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_j;
      }
    zval *right;
    if (local_cols == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_cols;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE290) goto L1221 else goto L1214;
  {
    zval *p_cond;
    if (local_TLE290 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE290;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1221;
    else
      goto L1214;
    phc_check_invariants (TSRMLS_C);
  }
// L1221:
L1221:;
// $TS42 = $count;
  {
    if (local_TS42 == NULL)
      {
	local_TS42 = EG (uninitialized_zval_ptr);
	local_TS42->refcount++;
      }
    zval **p_lhs = &local_TS42;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_count == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_count;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$count;
  {
    if (local_count == NULL)
      {
	local_count = EG (uninitialized_zval_ptr);
	local_count->refcount++;
      }
    zval **p_var = &local_count;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi291 =& $mx[$i];
  {
    if (local_TSi291 == NULL)
      {
	local_TSi291 = EG (uninitialized_zval_ptr);
	local_TSi291->refcount++;
      }
    zval **p_lhs = &local_TSi291;
    if (local_mx == NULL)
      {
	local_mx = EG (uninitialized_zval_ptr);
	local_mx->refcount++;
      }
    zval **p_rhs_var = &local_mx;
    zval *p_rhs_index;
    if (local_i == NULL)
      {
	p_rhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_index = local_i;
      }
    zval **p_rhs = get_ht_entry (p_rhs_var, p_rhs_index TSRMLS_CC);
    copy_into_ref (p_lhs, p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi291[$j] = $TS42;
  {
    if (local_TSi291 == NULL)
      {
	local_TSi291 = EG (uninitialized_zval_ptr);
	local_TSi291->refcount++;
      }
    zval **p_lhs_var = &local_TSi291;
    zval *p_lhs_index;
    if (local_j == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_j;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_TS42 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TS42;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$j;
  {
    if (local_j == NULL)
      {
	local_j = EG (uninitialized_zval_ptr);
	local_j->refcount++;
      }
    zval **p_var = &local_j;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1219;
  {
    goto L1219;
    phc_check_invariants (TSRMLS_C);
  }
// L1214:
L1214:;
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1215;
  {
    goto L1215;
    phc_check_invariants (TSRMLS_C);
  }
// L1225:
L1225:;
// return $mx;
  {
    zval *rhs;
    if (local_mx == NULL)
      {
	rhs = EG (uninitialized_zval_ptr);
      }
    else
      {
	rhs = local_mx;
      }
    return_value->value = rhs->value;
    return_value->type = rhs->type;
    zval_copy_ctor (return_value);
    goto end_of_function;
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE289 != NULL)
    {
      zval_ptr_dtor (&local_TLE289);
    }
  if (local_TLE290 != NULL)
    {
      zval_ptr_dtor (&local_TLE290);
    }
  if (local_TS42 != NULL)
    {
      zval_ptr_dtor (&local_TS42);
    }
  if (local_TSa288 != NULL)
    {
      zval_ptr_dtor (&local_TSa288);
    }
  if (local_TSi291 != NULL)
    {
      zval_ptr_dtor (&local_TSi291);
    }
  if (local_cols != NULL)
    {
      zval_ptr_dtor (&local_cols);
    }
  if (local_count != NULL)
    {
      zval_ptr_dtor (&local_count);
    }
  if (local_i != NULL)
    {
      zval_ptr_dtor (&local_i);
    }
  if (local_j != NULL)
    {
      zval_ptr_dtor (&local_j);
    }
  if (local_mx != NULL)
    {
      zval_ptr_dtor (&local_mx);
    }
  if (local_rows != NULL)
    {
      zval_ptr_dtor (&local_rows);
    }
}

// function mmult($rows, $cols, $m1, $m2)
// {
// \011unset($TSa292);
// \011$TSa292 = (array) $TSa292;
// \011$m3 = $TSa292;
// \011$i = 0;
// \011L1233:
// \011$TLE293 = ($i < $rows);
// \011if (TLE293) goto L1235 else goto L1252;
// \011L1235:
// \011$j = 0;
// \011L1237:
// \011$TLE294 = ($j < $cols);
// \011if (TLE294) goto L1239 else goto L1232;
// \011L1239:
// \011$x = 0;
// \011$k = 0;
// \011L1242:
// \011$TLE295 = ($k < $cols);
// \011if (TLE295) goto L1244 else goto L1250;
// \011L1244:
// \011$TSi296 = $m1[$i];
// \011$TSi297 = $TSi296[$k];
// \011$TSi298 = $m2[$k];
// \011$TSi299 = $TSi298[$j];
// \011$TLE300 = ($TSi297 * $TSi299);
// \011$x = ($x + $TLE300);
// \011++$k;
// \011goto L1242;
// \011L1250:
// \011$TSi301 =& $m3[$i];
// \011$TSi301[$j] = $x;
// \011++$j;
// \011goto L1237;
// \011L1232:
// \011++$i;
// \011goto L1233;
// \011L1252:
// \011return $m3;
// }
PHP_FUNCTION (mmult)
{
  zval *local_TLE293 = NULL;
  zval *local_TLE294 = NULL;
  zval *local_TLE295 = NULL;
  zval *local_TLE300 = NULL;
  zval *local_TSa292 = NULL;
  zval *local_TSi296 = NULL;
  zval *local_TSi297 = NULL;
  zval *local_TSi298 = NULL;
  zval *local_TSi299 = NULL;
  zval *local_TSi301 = NULL;
  zval *local_cols = NULL;
  zval *local_i = NULL;
  zval *local_j = NULL;
  zval *local_k = NULL;
  zval *local_m1 = NULL;
  zval *local_m2 = NULL;
  zval *local_m3 = NULL;
  zval *local_rows = NULL;
  zval *local_x = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[4];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_rows = params[0];
// param 1
    params[1]->refcount++;
    local_cols = params[1];
// param 2
    params[2]->refcount++;
    local_m1 = params[2];
// param 3
    params[3]->refcount++;
    local_m2 = params[3];
  }
// Function body
// unset($TSa292);
  {
    if (local_TSa292 != NULL)
      {
	zval_ptr_dtor (&local_TSa292);
	local_TSa292 = NULL;
      }
    phc_check_invariants (TSRMLS_C);
  }
// $TSa292 = (array) $TSa292;
  {
    if (local_TSa292 == NULL)
      {
	local_TSa292 = EG (uninitialized_zval_ptr);
	local_TSa292->refcount++;
      }
    zval **p_lhs = &local_TSa292;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_TSa292 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSa292;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    cast_var (p_lhs, IS_ARRAY);
    phc_check_invariants (TSRMLS_C);
  }
// $m3 = $TSa292;
  {
    if (local_m3 == NULL)
      {
	local_m3 = EG (uninitialized_zval_ptr);
	local_m3->refcount++;
      }
    zval **p_lhs = &local_m3;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_TSa292 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TSa292;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $i = 0;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1233:
L1233:;
// $TLE293 = ($i < $rows);
  {
    if (local_TLE293 == NULL)
      {
	local_TLE293 = EG (uninitialized_zval_ptr);
	local_TLE293->refcount++;
      }
    zval **p_lhs = &local_TLE293;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right;
    if (local_rows == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_rows;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE293) goto L1235 else goto L1252;
  {
    zval *p_cond;
    if (local_TLE293 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE293;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1235;
    else
      goto L1252;
    phc_check_invariants (TSRMLS_C);
  }
// L1235:
L1235:;
// $j = 0;
  {
    if (local_j == NULL)
      {
	local_j = EG (uninitialized_zval_ptr);
	local_j->refcount++;
      }
    zval **p_lhs = &local_j;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1237:
L1237:;
// $TLE294 = ($j < $cols);
  {
    if (local_TLE294 == NULL)
      {
	local_TLE294 = EG (uninitialized_zval_ptr);
	local_TLE294->refcount++;
      }
    zval **p_lhs = &local_TLE294;
    zval *left;
    if (local_j == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_j;
      }
    zval *right;
    if (local_cols == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_cols;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE294) goto L1239 else goto L1232;
  {
    zval *p_cond;
    if (local_TLE294 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE294;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1239;
    else
      goto L1232;
    phc_check_invariants (TSRMLS_C);
  }
// L1239:
L1239:;
// $x = 0;
  {
    if (local_x == NULL)
      {
	local_x = EG (uninitialized_zval_ptr);
	local_x->refcount++;
      }
    zval **p_lhs = &local_x;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// $k = 0;
  {
    if (local_k == NULL)
      {
	local_k = EG (uninitialized_zval_ptr);
	local_k->refcount++;
      }
    zval **p_lhs = &local_k;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1242:
L1242:;
// $TLE295 = ($k < $cols);
  {
    if (local_TLE295 == NULL)
      {
	local_TLE295 = EG (uninitialized_zval_ptr);
	local_TLE295->refcount++;
      }
    zval **p_lhs = &local_TLE295;
    zval *left;
    if (local_k == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_k;
      }
    zval *right;
    if (local_cols == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_cols;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE295) goto L1244 else goto L1250;
  {
    zval *p_cond;
    if (local_TLE295 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE295;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1244;
    else
      goto L1250;
    phc_check_invariants (TSRMLS_C);
  }
// L1244:
L1244:;
// $TSi296 = $m1[$i];
  {
    if (local_TSi296 == NULL)
      {
	local_TSi296 = EG (uninitialized_zval_ptr);
	local_TSi296->refcount++;
      }
    zval **p_lhs = &local_TSi296;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_m1 == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_m1;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi297 = $TSi296[$k];
  {
    if (local_TSi297 == NULL)
      {
	local_TSi297 = EG (uninitialized_zval_ptr);
	local_TSi297->refcount++;
      }
    zval **p_lhs = &local_TSi297;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_TSi296 == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_TSi296;
      }
    zval *ra_index;
    if (local_k == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_k;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi298 = $m2[$k];
  {
    if (local_TSi298 == NULL)
      {
	local_TSi298 = EG (uninitialized_zval_ptr);
	local_TSi298->refcount++;
      }
    zval **p_lhs = &local_TSi298;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_m2 == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_m2;
      }
    zval *ra_index;
    if (local_k == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_k;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi299 = $TSi298[$j];
  {
    if (local_TSi299 == NULL)
      {
	local_TSi299 = EG (uninitialized_zval_ptr);
	local_TSi299->refcount++;
      }
    zval **p_lhs = &local_TSi299;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_TSi298 == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_TSi298;
      }
    zval *ra_index;
    if (local_j == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_j;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE300 = ($TSi297 * $TSi299);
  {
    if (local_TLE300 == NULL)
      {
	local_TLE300 = EG (uninitialized_zval_ptr);
	local_TLE300->refcount++;
      }
    zval **p_lhs = &local_TLE300;
    zval *left;
    if (local_TSi297 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TSi297;
      }
    zval *right;
    if (local_TSi299 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi299;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    mul_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $x = ($x + $TLE300);
  {
    if (local_x == NULL)
      {
	local_x = EG (uninitialized_zval_ptr);
	local_x->refcount++;
      }
    zval **p_lhs = &local_x;
    zval *left;
    if (local_x == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_x;
      }
    zval *right;
    if (local_TLE300 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE300;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// ++$k;
  {
    if (local_k == NULL)
      {
	local_k = EG (uninitialized_zval_ptr);
	local_k->refcount++;
      }
    zval **p_var = &local_k;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1242;
  {
    goto L1242;
    phc_check_invariants (TSRMLS_C);
  }
// L1250:
L1250:;
// $TSi301 =& $m3[$i];
  {
    if (local_TSi301 == NULL)
      {
	local_TSi301 = EG (uninitialized_zval_ptr);
	local_TSi301->refcount++;
      }
    zval **p_lhs = &local_TSi301;
    if (local_m3 == NULL)
      {
	local_m3 = EG (uninitialized_zval_ptr);
	local_m3->refcount++;
      }
    zval **p_rhs_var = &local_m3;
    zval *p_rhs_index;
    if (local_i == NULL)
      {
	p_rhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_index = local_i;
      }
    zval **p_rhs = get_ht_entry (p_rhs_var, p_rhs_index TSRMLS_CC);
    copy_into_ref (p_lhs, p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi301[$j] = $x;
  {
    if (local_TSi301 == NULL)
      {
	local_TSi301 = EG (uninitialized_zval_ptr);
	local_TSi301->refcount++;
      }
    zval **p_lhs_var = &local_TSi301;
    zval *p_lhs_index;
    if (local_j == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_j;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var;
    if (local_x == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_x;
      }
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ++$j;
  {
    if (local_j == NULL)
      {
	local_j = EG (uninitialized_zval_ptr);
	local_j->refcount++;
      }
    zval **p_var = &local_j;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1237;
  {
    goto L1237;
    phc_check_invariants (TSRMLS_C);
  }
// L1232:
L1232:;
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1233;
  {
    goto L1233;
    phc_check_invariants (TSRMLS_C);
  }
// L1252:
L1252:;
// return $m3;
  {
    zval *rhs;
    if (local_m3 == NULL)
      {
	rhs = EG (uninitialized_zval_ptr);
      }
    else
      {
	rhs = local_m3;
      }
    return_value->value = rhs->value;
    return_value->type = rhs->type;
    zval_copy_ctor (return_value);
    goto end_of_function;
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE293 != NULL)
    {
      zval_ptr_dtor (&local_TLE293);
    }
  if (local_TLE294 != NULL)
    {
      zval_ptr_dtor (&local_TLE294);
    }
  if (local_TLE295 != NULL)
    {
      zval_ptr_dtor (&local_TLE295);
    }
  if (local_TLE300 != NULL)
    {
      zval_ptr_dtor (&local_TLE300);
    }
  if (local_TSa292 != NULL)
    {
      zval_ptr_dtor (&local_TSa292);
    }
  if (local_TSi296 != NULL)
    {
      zval_ptr_dtor (&local_TSi296);
    }
  if (local_TSi297 != NULL)
    {
      zval_ptr_dtor (&local_TSi297);
    }
  if (local_TSi298 != NULL)
    {
      zval_ptr_dtor (&local_TSi298);
    }
  if (local_TSi299 != NULL)
    {
      zval_ptr_dtor (&local_TSi299);
    }
  if (local_TSi301 != NULL)
    {
      zval_ptr_dtor (&local_TSi301);
    }
  if (local_cols != NULL)
    {
      zval_ptr_dtor (&local_cols);
    }
  if (local_i != NULL)
    {
      zval_ptr_dtor (&local_i);
    }
  if (local_j != NULL)
    {
      zval_ptr_dtor (&local_j);
    }
  if (local_k != NULL)
    {
      zval_ptr_dtor (&local_k);
    }
  if (local_m1 != NULL)
    {
      zval_ptr_dtor (&local_m1);
    }
  if (local_m2 != NULL)
    {
      zval_ptr_dtor (&local_m2);
    }
  if (local_m3 != NULL)
    {
      zval_ptr_dtor (&local_m3);
    }
  if (local_rows != NULL)
    {
      zval_ptr_dtor (&local_rows);
    }
  if (local_x != NULL)
    {
      zval_ptr_dtor (&local_x);
    }
}

// function matrix($n)
// {
// \011$m1 = mkmatrix(30, 30);
// \011$m2 = mkmatrix(30, 30);
// \011L1257:
// \011$TS43 = $n;
// \011--$n;
// \011if (TS43) goto L1260 else goto L1261;
// \011L1260:
// \011$mm = mmult(30, 30, $m1, $m2);
// \011goto L1257;
// \011L1261:
// \011$TSi306 = $mm[0];
// \011$TSi307 = $TSi306[0];
// \011$TLE308 = ('' . $TSi307);
// \011$TLE310 = ($TLE308 . ' ');
// \011$TSi313 = $mm[2];
// \011$TSi314 = $TSi313[3];
// \011$TLE315 = ($TLE310 . $TSi314);
// \011$TLE317 = ($TLE315 . ' ');
// \011$TSi320 = $mm[3];
// \011$TSi321 = $TSi320[2];
// \011$TLE322 = ($TLE317 . $TSi321);
// \011$TLE324 = ($TLE322 . ' ');
// \011$TSi327 = $mm[4];
// \011$TSi328 = $TSi327[4];
// \011$TLE329 = ($TLE324 . $TSi328);
// \011$TLE331 = ($TLE329 . '
// ');
// \011print($TLE331);
// }
PHP_FUNCTION (matrix)
{
  zval *local_TLE308 = NULL;
  zval *local_TLE310 = NULL;
  zval *local_TLE315 = NULL;
  zval *local_TLE317 = NULL;
  zval *local_TLE322 = NULL;
  zval *local_TLE324 = NULL;
  zval *local_TLE329 = NULL;
  zval *local_TLE331 = NULL;
  zval *local_TS43 = NULL;
  zval *local_TSi306 = NULL;
  zval *local_TSi307 = NULL;
  zval *local_TSi313 = NULL;
  zval *local_TSi314 = NULL;
  zval *local_TSi320 = NULL;
  zval *local_TSi321 = NULL;
  zval *local_TSi327 = NULL;
  zval *local_TSi328 = NULL;
  zval *local_m1 = NULL;
  zval *local_m2 = NULL;
  zval *local_mm = NULL;
  zval *local_n = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// $m1 = mkmatrix(30, 30);
  {
    if (local_m1 == NULL)
      {
	local_m1 = EG (uninitialized_zval_ptr);
	local_m1->refcount++;
      }
    zval **p_lhs = &local_m1;
    initialize_function_call (&mkmatrix_fci, &mkmatrix_fcic, "mkmatrix",
			      "test/subjects/benchmarks/zend/bench.php",
			      292 TSRMLS_CC);
    zend_function *signature = mkmatrix_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_9;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_int_9;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = mkmatrix_fci.param_count;
    zval ***params_save = mkmatrix_fci.params;
    zval **retval_save = mkmatrix_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    mkmatrix_fci.params = args_ind;
    mkmatrix_fci.param_count = 2;
    mkmatrix_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&mkmatrix_fci, &mkmatrix_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    mkmatrix_fci.params = params_save;
    mkmatrix_fci.param_count = param_count_save;
    mkmatrix_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $m2 = mkmatrix(30, 30);
  {
    if (local_m2 == NULL)
      {
	local_m2 = EG (uninitialized_zval_ptr);
	local_m2->refcount++;
      }
    zval **p_lhs = &local_m2;
    initialize_function_call (&mkmatrix_fci, &mkmatrix_fcic, "mkmatrix",
			      "test/subjects/benchmarks/zend/bench.php",
			      293 TSRMLS_CC);
    zend_function *signature = mkmatrix_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_9;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_int_9;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = mkmatrix_fci.param_count;
    zval ***params_save = mkmatrix_fci.params;
    zval **retval_save = mkmatrix_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    mkmatrix_fci.params = args_ind;
    mkmatrix_fci.param_count = 2;
    mkmatrix_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&mkmatrix_fci, &mkmatrix_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    mkmatrix_fci.params = params_save;
    mkmatrix_fci.param_count = param_count_save;
    mkmatrix_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// L1257:
L1257:;
// $TS43 = $n;
  {
    if (local_TS43 == NULL)
      {
	local_TS43 = EG (uninitialized_zval_ptr);
	local_TS43->refcount++;
      }
    zval **p_lhs = &local_TS43;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_n == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_n;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$n;
  {
    if (local_n == NULL)
      {
	local_n = EG (uninitialized_zval_ptr);
	local_n->refcount++;
      }
    zval **p_var = &local_n;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// if (TS43) goto L1260 else goto L1261;
  {
    zval *p_cond;
    if (local_TS43 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TS43;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1260;
    else
      goto L1261;
    phc_check_invariants (TSRMLS_C);
  }
// L1260:
L1260:;
// $mm = mmult(30, 30, $m1, $m2);
  {
    if (local_mm == NULL)
      {
	local_mm = EG (uninitialized_zval_ptr);
	local_mm->refcount++;
      }
    zval **p_lhs = &local_mm;
    initialize_function_call (&mmult_fci, &mmult_fcic, "mmult",
			      "test/subjects/benchmarks/zend/bench.php",
			      295 TSRMLS_CC);
    zend_function *signature = mmult_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[4];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[2] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[2] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[3] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[3] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[4];		// set to 1 if the arg is new
    zval *args[4];
    zval **args_ind[4];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_9;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_int_9;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    destruct[2] = 0;
    {
      zval *arg;
      if (local_m1 == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_m1;
	}
      args[2] = fetch_var_arg (arg, &destruct[2]);
      args_ind[2] = &args[2];
    }
    destruct[3] = 0;
    {
      zval *arg;
      if (local_m2 == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_m2;
	}
      args[3] = fetch_var_arg (arg, &destruct[3]);
      args_ind[3] = &args[3];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = mmult_fci.param_count;
    zval ***params_save = mmult_fci.params;
    zval **retval_save = mmult_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    mmult_fci.params = args_ind;
    mmult_fci.param_count = 4;
    mmult_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&mmult_fci, &mmult_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    mmult_fci.params = params_save;
    mmult_fci.param_count = param_count_save;
    mmult_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    if (destruct[2])
      {
	assert (destruct[2] == 1);
	zval_ptr_dtor (args_ind[2]);
      }
    if (destruct[3])
      {
	assert (destruct[3] == 1);
	zval_ptr_dtor (args_ind[3]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1257;
  {
    goto L1257;
    phc_check_invariants (TSRMLS_C);
  }
// L1261:
L1261:;
// $TSi306 = $mm[0];
  {
    if (local_TSi306 == NULL)
      {
	local_TSi306 = EG (uninitialized_zval_ptr);
	local_TSi306->refcount++;
      }
    zval **p_lhs = &local_TSi306;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_mm == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_mm;
      }
    zval *ra_index = phc_const_pool_int_0;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi307 = $TSi306[0];
  {
    if (local_TSi307 == NULL)
      {
	local_TSi307 = EG (uninitialized_zval_ptr);
	local_TSi307->refcount++;
      }
    zval **p_lhs = &local_TSi307;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_TSi306 == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_TSi306;
      }
    zval *ra_index = phc_const_pool_int_0;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE308 = ('' . $TSi307);
  {
    if (local_TLE308 == NULL)
      {
	local_TLE308 = EG (uninitialized_zval_ptr);
	local_TLE308->refcount++;
      }
    zval **p_lhs = &local_TLE308;
    zval *left = phc_const_pool_string_8;
    zval *right;
    if (local_TSi307 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi307;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE310 = ($TLE308 . ' ');
  {
    if (local_TLE310 == NULL)
      {
	local_TLE310 = EG (uninitialized_zval_ptr);
	local_TLE310->refcount++;
      }
    zval **p_lhs = &local_TLE310;
    zval *left;
    if (local_TLE308 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE308;
      }
    zval *right = phc_const_pool_string_9;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi313 = $mm[2];
  {
    if (local_TSi313 == NULL)
      {
	local_TSi313 = EG (uninitialized_zval_ptr);
	local_TSi313->refcount++;
      }
    zval **p_lhs = &local_TSi313;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_mm == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_mm;
      }
    zval *ra_index = phc_const_pool_int_7;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi314 = $TSi313[3];
  {
    if (local_TSi314 == NULL)
      {
	local_TSi314 = EG (uninitialized_zval_ptr);
	local_TSi314->refcount++;
      }
    zval **p_lhs = &local_TSi314;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_TSi313 == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_TSi313;
      }
    zval *ra_index = phc_const_pool_int_14;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE315 = ($TLE310 . $TSi314);
  {
    if (local_TLE315 == NULL)
      {
	local_TLE315 = EG (uninitialized_zval_ptr);
	local_TLE315->refcount++;
      }
    zval **p_lhs = &local_TLE315;
    zval *left;
    if (local_TLE310 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE310;
      }
    zval *right;
    if (local_TSi314 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi314;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE317 = ($TLE315 . ' ');
  {
    if (local_TLE317 == NULL)
      {
	local_TLE317 = EG (uninitialized_zval_ptr);
	local_TLE317->refcount++;
      }
    zval **p_lhs = &local_TLE317;
    zval *left;
    if (local_TLE315 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE315;
      }
    zval *right = phc_const_pool_string_9;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi320 = $mm[3];
  {
    if (local_TSi320 == NULL)
      {
	local_TSi320 = EG (uninitialized_zval_ptr);
	local_TSi320->refcount++;
      }
    zval **p_lhs = &local_TSi320;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_mm == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_mm;
      }
    zval *ra_index = phc_const_pool_int_14;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi321 = $TSi320[2];
  {
    if (local_TSi321 == NULL)
      {
	local_TSi321 = EG (uninitialized_zval_ptr);
	local_TSi321->refcount++;
      }
    zval **p_lhs = &local_TSi321;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_TSi320 == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_TSi320;
      }
    zval *ra_index = phc_const_pool_int_7;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE322 = ($TLE317 . $TSi321);
  {
    if (local_TLE322 == NULL)
      {
	local_TLE322 = EG (uninitialized_zval_ptr);
	local_TLE322->refcount++;
      }
    zval **p_lhs = &local_TLE322;
    zval *left;
    if (local_TLE317 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE317;
      }
    zval *right;
    if (local_TSi321 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi321;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE324 = ($TLE322 . ' ');
  {
    if (local_TLE324 == NULL)
      {
	local_TLE324 = EG (uninitialized_zval_ptr);
	local_TLE324->refcount++;
      }
    zval **p_lhs = &local_TLE324;
    zval *left;
    if (local_TLE322 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE322;
      }
    zval *right = phc_const_pool_string_9;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi327 = $mm[4];
  {
    if (local_TSi327 == NULL)
      {
	local_TSi327 = EG (uninitialized_zval_ptr);
	local_TSi327->refcount++;
      }
    zval **p_lhs = &local_TSi327;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_mm == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_mm;
      }
    zval *ra_index = phc_const_pool_int_20;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi328 = $TSi327[4];
  {
    if (local_TSi328 == NULL)
      {
	local_TSi328 = EG (uninitialized_zval_ptr);
	local_TSi328->refcount++;
      }
    zval **p_lhs = &local_TSi328;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_TSi327 == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_TSi327;
      }
    zval *ra_index = phc_const_pool_int_20;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE329 = ($TLE324 . $TSi328);
  {
    if (local_TLE329 == NULL)
      {
	local_TLE329 = EG (uninitialized_zval_ptr);
	local_TLE329->refcount++;
      }
    zval **p_lhs = &local_TLE329;
    zval *left;
    if (local_TLE324 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE324;
      }
    zval *right;
    if (local_TSi328 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TSi328;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE331 = ($TLE329 . '
// ');
  {
    if (local_TLE331 == NULL)
      {
	local_TLE331 = EG (uninitialized_zval_ptr);
	local_TLE331->refcount++;
      }
    zval **p_lhs = &local_TLE331;
    zval *left;
    if (local_TLE329 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE329;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE331);
  {
    zval *p_arg;
    if (local_TLE331 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE331;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE308 != NULL)
    {
      zval_ptr_dtor (&local_TLE308);
    }
  if (local_TLE310 != NULL)
    {
      zval_ptr_dtor (&local_TLE310);
    }
  if (local_TLE315 != NULL)
    {
      zval_ptr_dtor (&local_TLE315);
    }
  if (local_TLE317 != NULL)
    {
      zval_ptr_dtor (&local_TLE317);
    }
  if (local_TLE322 != NULL)
    {
      zval_ptr_dtor (&local_TLE322);
    }
  if (local_TLE324 != NULL)
    {
      zval_ptr_dtor (&local_TLE324);
    }
  if (local_TLE329 != NULL)
    {
      zval_ptr_dtor (&local_TLE329);
    }
  if (local_TLE331 != NULL)
    {
      zval_ptr_dtor (&local_TLE331);
    }
  if (local_TS43 != NULL)
    {
      zval_ptr_dtor (&local_TS43);
    }
  if (local_TSi306 != NULL)
    {
      zval_ptr_dtor (&local_TSi306);
    }
  if (local_TSi307 != NULL)
    {
      zval_ptr_dtor (&local_TSi307);
    }
  if (local_TSi313 != NULL)
    {
      zval_ptr_dtor (&local_TSi313);
    }
  if (local_TSi314 != NULL)
    {
      zval_ptr_dtor (&local_TSi314);
    }
  if (local_TSi320 != NULL)
    {
      zval_ptr_dtor (&local_TSi320);
    }
  if (local_TSi321 != NULL)
    {
      zval_ptr_dtor (&local_TSi321);
    }
  if (local_TSi327 != NULL)
    {
      zval_ptr_dtor (&local_TSi327);
    }
  if (local_TSi328 != NULL)
    {
      zval_ptr_dtor (&local_TSi328);
    }
  if (local_m1 != NULL)
    {
      zval_ptr_dtor (&local_m1);
    }
  if (local_m2 != NULL)
    {
      zval_ptr_dtor (&local_m2);
    }
  if (local_mm != NULL)
    {
      zval_ptr_dtor (&local_mm);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
}

// function nestedloop($n)
// {
// \011$x = 0;
// \011$a = 0;
// \011L1283:
// \011$TLE332 = ($a < $n);
// \011if (TLE332) goto L1285 else goto L1306;
// \011L1285:
// \011$b = 0;
// \011L1287:
// \011$TLE333 = ($b < $n);
// \011if (TLE333) goto L1289 else goto L1282;
// \011L1289:
// \011$c = 0;
// \011L1291:
// \011$TLE334 = ($c < $n);
// \011if (TLE334) goto L1293 else goto L1286;
// \011L1293:
// \011$d = 0;
// \011L1295:
// \011$TLE335 = ($d < $n);
// \011if (TLE335) goto L1297 else goto L1290;
// \011L1297:
// \011$e = 0;
// \011L1299:
// \011$TLE336 = ($e < $n);
// \011if (TLE336) goto L1301 else goto L1294;
// \011L1301:
// \011$f = 0;
// \011L1303:
// \011$TLE337 = ($f < $n);
// \011if (TLE337) goto L1305 else goto L1298;
// \011L1305:
// \011++$x;
// \011++$f;
// \011goto L1303;
// \011L1298:
// \011++$e;
// \011goto L1299;
// \011L1294:
// \011++$d;
// \011goto L1295;
// \011L1290:
// \011++$c;
// \011goto L1291;
// \011L1286:
// \011++$b;
// \011goto L1287;
// \011L1282:
// \011++$a;
// \011goto L1283;
// \011L1306:
// \011$TLE339 = ('' . $x);
// \011$TLE341 = ($TLE339 . '
// ');
// \011print($TLE341);
// }
PHP_FUNCTION (nestedloop)
{
  zval *local_TLE332 = NULL;
  zval *local_TLE333 = NULL;
  zval *local_TLE334 = NULL;
  zval *local_TLE335 = NULL;
  zval *local_TLE336 = NULL;
  zval *local_TLE337 = NULL;
  zval *local_TLE339 = NULL;
  zval *local_TLE341 = NULL;
  zval *local_a = NULL;
  zval *local_b = NULL;
  zval *local_c = NULL;
  zval *local_d = NULL;
  zval *local_e = NULL;
  zval *local_f = NULL;
  zval *local_n = NULL;
  zval *local_x = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// $x = 0;
  {
    if (local_x == NULL)
      {
	local_x = EG (uninitialized_zval_ptr);
	local_x->refcount++;
      }
    zval **p_lhs = &local_x;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// $a = 0;
  {
    if (local_a == NULL)
      {
	local_a = EG (uninitialized_zval_ptr);
	local_a->refcount++;
      }
    zval **p_lhs = &local_a;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1283:
L1283:;
// $TLE332 = ($a < $n);
  {
    if (local_TLE332 == NULL)
      {
	local_TLE332 = EG (uninitialized_zval_ptr);
	local_TLE332->refcount++;
      }
    zval **p_lhs = &local_TLE332;
    zval *left;
    if (local_a == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_a;
      }
    zval *right;
    if (local_n == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_n;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE332) goto L1285 else goto L1306;
  {
    zval *p_cond;
    if (local_TLE332 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE332;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1285;
    else
      goto L1306;
    phc_check_invariants (TSRMLS_C);
  }
// L1285:
L1285:;
// $b = 0;
  {
    if (local_b == NULL)
      {
	local_b = EG (uninitialized_zval_ptr);
	local_b->refcount++;
      }
    zval **p_lhs = &local_b;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1287:
L1287:;
// $TLE333 = ($b < $n);
  {
    if (local_TLE333 == NULL)
      {
	local_TLE333 = EG (uninitialized_zval_ptr);
	local_TLE333->refcount++;
      }
    zval **p_lhs = &local_TLE333;
    zval *left;
    if (local_b == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_b;
      }
    zval *right;
    if (local_n == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_n;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE333) goto L1289 else goto L1282;
  {
    zval *p_cond;
    if (local_TLE333 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE333;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1289;
    else
      goto L1282;
    phc_check_invariants (TSRMLS_C);
  }
// L1289:
L1289:;
// $c = 0;
  {
    if (local_c == NULL)
      {
	local_c = EG (uninitialized_zval_ptr);
	local_c->refcount++;
      }
    zval **p_lhs = &local_c;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1291:
L1291:;
// $TLE334 = ($c < $n);
  {
    if (local_TLE334 == NULL)
      {
	local_TLE334 = EG (uninitialized_zval_ptr);
	local_TLE334->refcount++;
      }
    zval **p_lhs = &local_TLE334;
    zval *left;
    if (local_c == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_c;
      }
    zval *right;
    if (local_n == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_n;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE334) goto L1293 else goto L1286;
  {
    zval *p_cond;
    if (local_TLE334 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE334;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1293;
    else
      goto L1286;
    phc_check_invariants (TSRMLS_C);
  }
// L1293:
L1293:;
// $d = 0;
  {
    if (local_d == NULL)
      {
	local_d = EG (uninitialized_zval_ptr);
	local_d->refcount++;
      }
    zval **p_lhs = &local_d;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1295:
L1295:;
// $TLE335 = ($d < $n);
  {
    if (local_TLE335 == NULL)
      {
	local_TLE335 = EG (uninitialized_zval_ptr);
	local_TLE335->refcount++;
      }
    zval **p_lhs = &local_TLE335;
    zval *left;
    if (local_d == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_d;
      }
    zval *right;
    if (local_n == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_n;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE335) goto L1297 else goto L1290;
  {
    zval *p_cond;
    if (local_TLE335 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE335;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1297;
    else
      goto L1290;
    phc_check_invariants (TSRMLS_C);
  }
// L1297:
L1297:;
// $e = 0;
  {
    if (local_e == NULL)
      {
	local_e = EG (uninitialized_zval_ptr);
	local_e->refcount++;
      }
    zval **p_lhs = &local_e;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1299:
L1299:;
// $TLE336 = ($e < $n);
  {
    if (local_TLE336 == NULL)
      {
	local_TLE336 = EG (uninitialized_zval_ptr);
	local_TLE336->refcount++;
      }
    zval **p_lhs = &local_TLE336;
    zval *left;
    if (local_e == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_e;
      }
    zval *right;
    if (local_n == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_n;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE336) goto L1301 else goto L1294;
  {
    zval *p_cond;
    if (local_TLE336 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE336;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1301;
    else
      goto L1294;
    phc_check_invariants (TSRMLS_C);
  }
// L1301:
L1301:;
// $f = 0;
  {
    if (local_f == NULL)
      {
	local_f = EG (uninitialized_zval_ptr);
	local_f->refcount++;
      }
    zval **p_lhs = &local_f;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1303:
L1303:;
// $TLE337 = ($f < $n);
  {
    if (local_TLE337 == NULL)
      {
	local_TLE337 = EG (uninitialized_zval_ptr);
	local_TLE337->refcount++;
      }
    zval **p_lhs = &local_TLE337;
    zval *left;
    if (local_f == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_f;
      }
    zval *right;
    if (local_n == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_n;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE337) goto L1305 else goto L1298;
  {
    zval *p_cond;
    if (local_TLE337 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE337;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1305;
    else
      goto L1298;
    phc_check_invariants (TSRMLS_C);
  }
// L1305:
L1305:;
// ++$x;
  {
    if (local_x == NULL)
      {
	local_x = EG (uninitialized_zval_ptr);
	local_x->refcount++;
      }
    zval **p_var = &local_x;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// ++$f;
  {
    if (local_f == NULL)
      {
	local_f = EG (uninitialized_zval_ptr);
	local_f->refcount++;
      }
    zval **p_var = &local_f;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1303;
  {
    goto L1303;
    phc_check_invariants (TSRMLS_C);
  }
// L1298:
L1298:;
// ++$e;
  {
    if (local_e == NULL)
      {
	local_e = EG (uninitialized_zval_ptr);
	local_e->refcount++;
      }
    zval **p_var = &local_e;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1299;
  {
    goto L1299;
    phc_check_invariants (TSRMLS_C);
  }
// L1294:
L1294:;
// ++$d;
  {
    if (local_d == NULL)
      {
	local_d = EG (uninitialized_zval_ptr);
	local_d->refcount++;
      }
    zval **p_var = &local_d;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1295;
  {
    goto L1295;
    phc_check_invariants (TSRMLS_C);
  }
// L1290:
L1290:;
// ++$c;
  {
    if (local_c == NULL)
      {
	local_c = EG (uninitialized_zval_ptr);
	local_c->refcount++;
      }
    zval **p_var = &local_c;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1291;
  {
    goto L1291;
    phc_check_invariants (TSRMLS_C);
  }
// L1286:
L1286:;
// ++$b;
  {
    if (local_b == NULL)
      {
	local_b = EG (uninitialized_zval_ptr);
	local_b->refcount++;
      }
    zval **p_var = &local_b;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1287;
  {
    goto L1287;
    phc_check_invariants (TSRMLS_C);
  }
// L1282:
L1282:;
// ++$a;
  {
    if (local_a == NULL)
      {
	local_a = EG (uninitialized_zval_ptr);
	local_a->refcount++;
      }
    zval **p_var = &local_a;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1283;
  {
    goto L1283;
    phc_check_invariants (TSRMLS_C);
  }
// L1306:
L1306:;
// $TLE339 = ('' . $x);
  {
    if (local_TLE339 == NULL)
      {
	local_TLE339 = EG (uninitialized_zval_ptr);
	local_TLE339->refcount++;
      }
    zval **p_lhs = &local_TLE339;
    zval *left = phc_const_pool_string_8;
    zval *right;
    if (local_x == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_x;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE341 = ($TLE339 . '
// ');
  {
    if (local_TLE341 == NULL)
      {
	local_TLE341 = EG (uninitialized_zval_ptr);
	local_TLE341->refcount++;
      }
    zval **p_lhs = &local_TLE341;
    zval *left;
    if (local_TLE339 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE339;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE341);
  {
    zval *p_arg;
    if (local_TLE341 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE341;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE332 != NULL)
    {
      zval_ptr_dtor (&local_TLE332);
    }
  if (local_TLE333 != NULL)
    {
      zval_ptr_dtor (&local_TLE333);
    }
  if (local_TLE334 != NULL)
    {
      zval_ptr_dtor (&local_TLE334);
    }
  if (local_TLE335 != NULL)
    {
      zval_ptr_dtor (&local_TLE335);
    }
  if (local_TLE336 != NULL)
    {
      zval_ptr_dtor (&local_TLE336);
    }
  if (local_TLE337 != NULL)
    {
      zval_ptr_dtor (&local_TLE337);
    }
  if (local_TLE339 != NULL)
    {
      zval_ptr_dtor (&local_TLE339);
    }
  if (local_TLE341 != NULL)
    {
      zval_ptr_dtor (&local_TLE341);
    }
  if (local_a != NULL)
    {
      zval_ptr_dtor (&local_a);
    }
  if (local_b != NULL)
    {
      zval_ptr_dtor (&local_b);
    }
  if (local_c != NULL)
    {
      zval_ptr_dtor (&local_c);
    }
  if (local_d != NULL)
    {
      zval_ptr_dtor (&local_d);
    }
  if (local_e != NULL)
    {
      zval_ptr_dtor (&local_e);
    }
  if (local_f != NULL)
    {
      zval_ptr_dtor (&local_f);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
  if (local_x != NULL)
    {
      zval_ptr_dtor (&local_x);
    }
}

// function sieve($n)
// {
// \011$count = 0;
// \011L1312:
// \011$TS44 = $n;
// \011--$n;
// \011$TLE343 = ($TS44 > 0);
// \011if (TLE343) goto L1316 else goto L1331;
// \011L1316:
// \011$count = 0;
// \011$flags = range(0, 8192);
// \011$i = 2;
// \011L1320:
// \011$TLE348 = ($i < 8193);
// \011if (TLE348) goto L1322 else goto L1312;
// \011L1322:
// \011$TSi349 = $flags[$i];
// \011$TLE351 = ($TSi349 > 0);
// \011if (TLE351) goto L1325 else goto L1319;
// \011L1325:
// \011$k = ($i + $i);
// \011L1327:
// \011$TLE353 = ($k <= 8192);
// \011if (TLE353) goto L1329 else goto L1330;
// \011L1330:
// \011++$count;
// \011L1319:
// \011++$i;
// \011goto L1320;
// \011L1329:
// \011$flags[$k] = 0;
// \011$k = ($k + $i);
// \011goto L1327;
// \011L1331:
// \011$TLE356 = ('Count: ' . $count);
// \011$TLE358 = ($TLE356 . '
// ');
// \011print($TLE358);
// }
PHP_FUNCTION (sieve)
{
  zval *local_TLE343 = NULL;
  zval *local_TLE348 = NULL;
  zval *local_TLE351 = NULL;
  zval *local_TLE353 = NULL;
  zval *local_TLE356 = NULL;
  zval *local_TLE358 = NULL;
  zval *local_TS44 = NULL;
  zval *local_TSi349 = NULL;
  zval *local_count = NULL;
  zval *local_flags = NULL;
  zval *local_i = NULL;
  zval *local_k = NULL;
  zval *local_n = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// $count = 0;
  {
    if (local_count == NULL)
      {
	local_count = EG (uninitialized_zval_ptr);
	local_count->refcount++;
      }
    zval **p_lhs = &local_count;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1312:
L1312:;
// $TS44 = $n;
  {
    if (local_TS44 == NULL)
      {
	local_TS44 = EG (uninitialized_zval_ptr);
	local_TS44->refcount++;
      }
    zval **p_lhs = &local_TS44;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_n == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_n;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$n;
  {
    if (local_n == NULL)
      {
	local_n = EG (uninitialized_zval_ptr);
	local_n->refcount++;
      }
    zval **p_var = &local_n;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE343 = ($TS44 > 0);
  {
    if (local_TLE343 == NULL)
      {
	local_TLE343 = EG (uninitialized_zval_ptr);
	local_TLE343->refcount++;
      }
    zval **p_lhs = &local_TLE343;
    zval *left;
    if (local_TS44 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TS44;
      }
    zval *right = phc_const_pool_int_0;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, right, left TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE343) goto L1316 else goto L1331;
  {
    zval *p_cond;
    if (local_TLE343 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE343;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1316;
    else
      goto L1331;
    phc_check_invariants (TSRMLS_C);
  }
// L1316:
L1316:;
// $count = 0;
  {
    if (local_count == NULL)
      {
	local_count = EG (uninitialized_zval_ptr);
	local_count->refcount++;
      }
    zval **p_lhs = &local_count;
    if (phc_const_pool_int_0 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_0, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// $flags = range(0, 8192);
  {
    if (local_flags == NULL)
      {
	local_flags = EG (uninitialized_zval_ptr);
	local_flags->refcount++;
      }
    zval **p_lhs = &local_flags;
    initialize_function_call (&range_fci, &range_fcic, "range",
			      "test/subjects/benchmarks/zend/bench.php",
			      320 TSRMLS_CC);
    zend_function *signature = range_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_0;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_int_21;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = range_fci.param_count;
    zval ***params_save = range_fci.params;
    zval **retval_save = range_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    range_fci.params = args_ind;
    range_fci.param_count = 2;
    range_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&range_fci, &range_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    range_fci.params = params_save;
    range_fci.param_count = param_count_save;
    range_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $i = 2;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_lhs = &local_i;
    if (phc_const_pool_int_7 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_int_7, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1320:
L1320:;
// $TLE348 = ($i < 8193);
  {
    if (local_TLE348 == NULL)
      {
	local_TLE348 = EG (uninitialized_zval_ptr);
	local_TLE348->refcount++;
      }
    zval **p_lhs = &local_TLE348;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right = phc_const_pool_int_22;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE348) goto L1322 else goto L1312;
  {
    zval *p_cond;
    if (local_TLE348 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE348;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1322;
    else
      goto L1312;
    phc_check_invariants (TSRMLS_C);
  }
// L1322:
L1322:;
// $TSi349 = $flags[$i];
  {
    if (local_TSi349 == NULL)
      {
	local_TSi349 = EG (uninitialized_zval_ptr);
	local_TSi349->refcount++;
      }
    zval **p_lhs = &local_TSi349;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_flags == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_flags;
      }
    zval *ra_index;
    if (local_i == NULL)
      {
	ra_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	ra_index = local_i;
      }
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE351 = ($TSi349 > 0);
  {
    if (local_TLE351 == NULL)
      {
	local_TLE351 = EG (uninitialized_zval_ptr);
	local_TLE351->refcount++;
      }
    zval **p_lhs = &local_TLE351;
    zval *left;
    if (local_TSi349 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TSi349;
      }
    zval *right = phc_const_pool_int_0;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, right, left TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE351) goto L1325 else goto L1319;
  {
    zval *p_cond;
    if (local_TLE351 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE351;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1325;
    else
      goto L1319;
    phc_check_invariants (TSRMLS_C);
  }
// L1325:
L1325:;
// $k = ($i + $i);
  {
    if (local_k == NULL)
      {
	local_k = EG (uninitialized_zval_ptr);
	local_k->refcount++;
      }
    zval **p_lhs = &local_k;
    zval *left;
    if (local_i == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_i;
      }
    zval *right;
    if (local_i == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_i;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// L1327:
L1327:;
// $TLE353 = ($k <= 8192);
  {
    if (local_TLE353 == NULL)
      {
	local_TLE353 = EG (uninitialized_zval_ptr);
	local_TLE353->refcount++;
      }
    zval **p_lhs = &local_TLE353;
    zval *left;
    if (local_k == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_k;
      }
    zval *right = phc_const_pool_int_21;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_or_equal_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE353) goto L1329 else goto L1330;
  {
    zval *p_cond;
    if (local_TLE353 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE353;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1329;
    else
      goto L1330;
    phc_check_invariants (TSRMLS_C);
  }
// L1330:
L1330:;
// ++$count;
  {
    if (local_count == NULL)
      {
	local_count = EG (uninitialized_zval_ptr);
	local_count->refcount++;
      }
    zval **p_var = &local_count;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// L1319:
L1319:;
// ++$i;
  {
    if (local_i == NULL)
      {
	local_i = EG (uninitialized_zval_ptr);
	local_i->refcount++;
      }
    zval **p_var = &local_i;
    sep_copy_on_write_ex (p_var);
    increment_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1320;
  {
    goto L1320;
    phc_check_invariants (TSRMLS_C);
  }
// L1329:
L1329:;
// $flags[$k] = 0;
  {
    if (local_flags == NULL)
      {
	local_flags = EG (uninitialized_zval_ptr);
	local_flags->refcount++;
      }
    zval **p_lhs_var = &local_flags;
    zval *p_lhs_index;
    if (local_k == NULL)
      {
	p_lhs_index = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_lhs_index = local_k;
      }
    zval **p_lhs = get_ht_entry (p_lhs_var, p_lhs_index TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    zval *p_rhs_var = phc_const_pool_int_0;
// Read normal variable
    p_rhs = &p_rhs_var;

    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $k = ($k + $i);
  {
    if (local_k == NULL)
      {
	local_k = EG (uninitialized_zval_ptr);
	local_k->refcount++;
      }
    zval **p_lhs = &local_k;
    zval *left;
    if (local_k == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_k;
      }
    zval *right;
    if (local_i == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_i;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1327;
  {
    goto L1327;
    phc_check_invariants (TSRMLS_C);
  }
// L1331:
L1331:;
// $TLE356 = ('Count: ' . $count);
  {
    if (local_TLE356 == NULL)
      {
	local_TLE356 = EG (uninitialized_zval_ptr);
	local_TLE356->refcount++;
      }
    zval **p_lhs = &local_TLE356;
    zval *left = phc_const_pool_string_17;
    zval *right;
    if (local_count == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_count;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE358 = ($TLE356 . '
// ');
  {
    if (local_TLE358 == NULL)
      {
	local_TLE358 = EG (uninitialized_zval_ptr);
	local_TLE358->refcount++;
      }
    zval **p_lhs = &local_TLE358;
    zval *left;
    if (local_TLE356 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE356;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE358);
  {
    zval *p_arg;
    if (local_TLE358 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE358;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE343 != NULL)
    {
      zval_ptr_dtor (&local_TLE343);
    }
  if (local_TLE348 != NULL)
    {
      zval_ptr_dtor (&local_TLE348);
    }
  if (local_TLE351 != NULL)
    {
      zval_ptr_dtor (&local_TLE351);
    }
  if (local_TLE353 != NULL)
    {
      zval_ptr_dtor (&local_TLE353);
    }
  if (local_TLE356 != NULL)
    {
      zval_ptr_dtor (&local_TLE356);
    }
  if (local_TLE358 != NULL)
    {
      zval_ptr_dtor (&local_TLE358);
    }
  if (local_TS44 != NULL)
    {
      zval_ptr_dtor (&local_TS44);
    }
  if (local_TSi349 != NULL)
    {
      zval_ptr_dtor (&local_TSi349);
    }
  if (local_count != NULL)
    {
      zval_ptr_dtor (&local_count);
    }
  if (local_flags != NULL)
    {
      zval_ptr_dtor (&local_flags);
    }
  if (local_i != NULL)
    {
      zval_ptr_dtor (&local_i);
    }
  if (local_k != NULL)
    {
      zval_ptr_dtor (&local_k);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
}

// function strcat($n)
// {
// \011$str = '';
// \011L1337:
// \011$TS45 = $n;
// \011--$n;
// \011$TLE360 = ($TS45 > 0);
// \011if (TLE360) goto L1341 else goto L1342;
// \011L1342:
// \011$len = strlen($str);
// \011$TLE364 = ('' . $len);
// \011$TLE366 = ($TLE364 . '
// ');
// \011print($TLE366);
// \011goto L1335;
// \011L1341:
// \011$str = ($str . 'hello
// ');
// \011goto L1337;
// \011L1335:
// }
PHP_FUNCTION (strcat)
{
  zval *local_TLE360 = NULL;
  zval *local_TLE364 = NULL;
  zval *local_TLE366 = NULL;
  zval *local_TS45 = NULL;
  zval *local_len = NULL;
  zval *local_n = NULL;
  zval *local_str = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[1];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_n = params[0];
  }
// Function body
// $str = '';
  {
    if (local_str == NULL)
      {
	local_str = EG (uninitialized_zval_ptr);
	local_str->refcount++;
      }
    zval **p_lhs = &local_str;
    if (phc_const_pool_string_8 != *p_lhs)
      write_var (p_lhs, &phc_const_pool_string_8, NULL TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// L1337:
L1337:;
// $TS45 = $n;
  {
    if (local_TS45 == NULL)
      {
	local_TS45 = EG (uninitialized_zval_ptr);
	local_TS45->refcount++;
      }
    zval **p_lhs = &local_TS45;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_n == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_n;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// --$n;
  {
    if (local_n == NULL)
      {
	local_n = EG (uninitialized_zval_ptr);
	local_n->refcount++;
      }
    zval **p_var = &local_n;
    sep_copy_on_write_ex (p_var);
    decrement_function (*p_var);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE360 = ($TS45 > 0);
  {
    if (local_TLE360 == NULL)
      {
	local_TLE360 = EG (uninitialized_zval_ptr);
	local_TLE360->refcount++;
      }
    zval **p_lhs = &local_TLE360;
    zval *left;
    if (local_TS45 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TS45;
      }
    zval *right = phc_const_pool_int_0;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    is_smaller_function (*p_lhs, right, left TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// if (TLE360) goto L1341 else goto L1342;
  {
    zval *p_cond;
    if (local_TLE360 == NULL)
      {
	p_cond = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_cond = local_TLE360;
      }
    zend_bool bcond = zend_is_true (p_cond);
    if (bcond)
      goto L1341;
    else
      goto L1342;
    phc_check_invariants (TSRMLS_C);
  }
// L1342:
L1342:;
// $len = strlen($str);
  {
    if (local_len == NULL)
      {
	local_len = EG (uninitialized_zval_ptr);
	local_len->refcount++;
      }
    zval **p_lhs = &local_len;
    initialize_function_call (&strlen_fci, &strlen_fcic, "strlen",
			      "test/subjects/benchmarks/zend/bench.php",
			      340 TSRMLS_CC);
    zend_function *signature = strlen_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_str == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_str;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = strlen_fci.param_count;
    zval ***params_save = strlen_fci.params;
    zval **retval_save = strlen_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    strlen_fci.params = args_ind;
    strlen_fci.param_count = 1;
    strlen_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&strlen_fci, &strlen_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    strlen_fci.params = params_save;
    strlen_fci.param_count = param_count_save;
    strlen_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE364 = ('' . $len);
  {
    if (local_TLE364 == NULL)
      {
	local_TLE364 = EG (uninitialized_zval_ptr);
	local_TLE364->refcount++;
      }
    zval **p_lhs = &local_TLE364;
    zval *left = phc_const_pool_string_8;
    zval *right;
    if (local_len == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_len;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE366 = ($TLE364 . '
// ');
  {
    if (local_TLE366 == NULL)
      {
	local_TLE366 = EG (uninitialized_zval_ptr);
	local_TLE366->refcount++;
      }
    zval **p_lhs = &local_TLE366;
    zval *left;
    if (local_TLE364 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE364;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE366);
  {
    zval *p_arg;
    if (local_TLE366 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE366;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1335;
  {
    goto L1335;
    phc_check_invariants (TSRMLS_C);
  }
// L1341:
L1341:;
// $str = ($str . 'hello
// ');
  {
    if (local_str == NULL)
      {
	local_str = EG (uninitialized_zval_ptr);
	local_str->refcount++;
      }
    zval **p_lhs = &local_str;
    zval *left;
    if (local_str == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_str;
      }
    zval *right = phc_const_pool_string_18;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// goto L1337;
  {
    goto L1337;
    phc_check_invariants (TSRMLS_C);
  }
// L1335:
L1335:;
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE360 != NULL)
    {
      zval_ptr_dtor (&local_TLE360);
    }
  if (local_TLE364 != NULL)
    {
      zval_ptr_dtor (&local_TLE364);
    }
  if (local_TLE366 != NULL)
    {
      zval_ptr_dtor (&local_TLE366);
    }
  if (local_TS45 != NULL)
    {
      zval_ptr_dtor (&local_TS45);
    }
  if (local_len != NULL)
    {
      zval_ptr_dtor (&local_len);
    }
  if (local_n != NULL)
    {
      zval_ptr_dtor (&local_n);
    }
  if (local_str != NULL)
    {
      zval_ptr_dtor (&local_str);
    }
}

// function getmicrotime()
// {
// \011$t = gettimeofday();
// \011$TSi368 = $t['sec'];
// \011$TSi370 = $t['usec'];
// \011$TLE372 = ($TSi370 / 1000000);
// \011$TLE373 = ($TSi368 + $TLE372);
// \011return $TLE373;
// }
PHP_FUNCTION (getmicrotime)
{
  zval *local_TLE372 = NULL;
  zval *local_TLE373 = NULL;
  zval *local_TSi368 = NULL;
  zval *local_TSi370 = NULL;
  zval *local_t = NULL;
// Function body
// $t = gettimeofday();
  {
    if (local_t == NULL)
      {
	local_t = EG (uninitialized_zval_ptr);
	local_t->refcount++;
      }
    zval **p_lhs = &local_t;
    initialize_function_call (&gettimeofday_fci, &gettimeofday_fcic,
			      "gettimeofday",
			      "test/subjects/benchmarks/zend/bench.php",
			      348 TSRMLS_CC);
    zend_function *signature = gettimeofday_fcic.function_handler;
    zval **args_ind[0];
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = gettimeofday_fci.param_count;
    zval ***params_save = gettimeofday_fci.params;
    zval **retval_save = gettimeofday_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    gettimeofday_fci.params = args_ind;
    gettimeofday_fci.param_count = 0;
    gettimeofday_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&gettimeofday_fci, &gettimeofday_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    gettimeofday_fci.params = params_save;
    gettimeofday_fci.param_count = param_count_save;
    gettimeofday_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi368 = $t['sec'];
  {
    if (local_TSi368 == NULL)
      {
	local_TSi368 = EG (uninitialized_zval_ptr);
	local_TSi368->refcount++;
      }
    zval **p_lhs = &local_TSi368;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_t == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_t;
      }
    zval *ra_index = phc_const_pool_string_19;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TSi370 = $t['usec'];
  {
    if (local_TSi370 == NULL)
      {
	local_TSi370 = EG (uninitialized_zval_ptr);
	local_TSi370->refcount++;
      }
    zval **p_lhs = &local_TSi370;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read array variable
    zval *r_array;
    if (local_t == NULL)
      {
	r_array = EG (uninitialized_zval_ptr);
      }
    else
      {
	r_array = local_t;
      }
    zval *ra_index = phc_const_pool_string_20;
    read_array (p_rhs, r_array, ra_index, &is_p_rhs_new TSRMLS_CC);
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE372 = ($TSi370 / 1000000);
  {
    if (local_TLE372 == NULL)
      {
	local_TLE372 = EG (uninitialized_zval_ptr);
	local_TLE372->refcount++;
      }
    zval **p_lhs = &local_TLE372;
    zval *left;
    if (local_TSi370 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TSi370;
      }
    zval *right = phc_const_pool_int_1;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    div_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE373 = ($TSi368 + $TLE372);
  {
    if (local_TLE373 == NULL)
      {
	local_TLE373 = EG (uninitialized_zval_ptr);
	local_TLE373->refcount++;
      }
    zval **p_lhs = &local_TLE373;
    zval *left;
    if (local_TSi368 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TSi368;
      }
    zval *right;
    if (local_TLE372 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE372;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// return $TLE373;
  {
    zval *rhs;
    if (local_TLE373 == NULL)
      {
	rhs = EG (uninitialized_zval_ptr);
      }
    else
      {
	rhs = local_TLE373;
      }
    return_value->value = rhs->value;
    return_value->type = rhs->type;
    zval_copy_ctor (return_value);
    goto end_of_function;
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE372 != NULL)
    {
      zval_ptr_dtor (&local_TLE372);
    }
  if (local_TLE373 != NULL)
    {
      zval_ptr_dtor (&local_TLE373);
    }
  if (local_TSi368 != NULL)
    {
      zval_ptr_dtor (&local_TSi368);
    }
  if (local_TSi370 != NULL)
    {
      zval_ptr_dtor (&local_TSi370);
    }
  if (local_t != NULL)
    {
      zval_ptr_dtor (&local_t);
    }
}

// function start_test()
// {
// \011ob_start();
// \011$TLE374 = getmicrotime();
// \011return $TLE374;
// }
PHP_FUNCTION (start_test)
{
  zval *local_TLE374 = NULL;
// Function body
// ob_start();
  {
    initialize_function_call (&ob_start_fci, &ob_start_fcic, "ob_start",
			      "test/subjects/benchmarks/zend/bench.php",
			      354 TSRMLS_CC);
    zend_function *signature = ob_start_fcic.function_handler;
    zval **args_ind[0];
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = ob_start_fci.param_count;
    zval ***params_save = ob_start_fci.params;
    zval **retval_save = ob_start_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    ob_start_fci.params = args_ind;
    ob_start_fci.param_count = 0;
    ob_start_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&ob_start_fci, &ob_start_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    ob_start_fci.params = params_save;
    ob_start_fci.param_count = param_count_save;
    ob_start_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE374 = getmicrotime();
  {
    if (local_TLE374 == NULL)
      {
	local_TLE374 = EG (uninitialized_zval_ptr);
	local_TLE374->refcount++;
      }
    zval **p_lhs = &local_TLE374;
    initialize_function_call (&getmicrotime_fci, &getmicrotime_fcic,
			      "getmicrotime",
			      "test/subjects/benchmarks/zend/bench.php",
			      355 TSRMLS_CC);
    zend_function *signature = getmicrotime_fcic.function_handler;
    zval **args_ind[0];
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = getmicrotime_fci.param_count;
    zval ***params_save = getmicrotime_fci.params;
    zval **retval_save = getmicrotime_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    getmicrotime_fci.params = args_ind;
    getmicrotime_fci.param_count = 0;
    getmicrotime_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&getmicrotime_fci, &getmicrotime_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    getmicrotime_fci.params = params_save;
    getmicrotime_fci.param_count = param_count_save;
    getmicrotime_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// return $TLE374;
  {
    zval *rhs;
    if (local_TLE374 == NULL)
      {
	rhs = EG (uninitialized_zval_ptr);
      }
    else
      {
	rhs = local_TLE374;
      }
    return_value->value = rhs->value;
    return_value->type = rhs->type;
    zval_copy_ctor (return_value);
    goto end_of_function;
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE374 != NULL)
    {
      zval_ptr_dtor (&local_TLE374);
    }
}

// function end_test($start, $name)
// {
// \011global $total;
// \011$end = getmicrotime();
// \011ob_end_clean();
// \011$TLE375 = ($end - $start);
// \011$total = ($total + $TLE375);
// \011$TLE376 = ($end - $start);
// \011$num = number_format($TLE376, 3);
// \011$TLE380 = strlen($name);
// \011$TLE381 = (24 - $TLE380);
// \011$TLE382 = strlen($num);
// \011$TLE383 = ($TLE381 - $TLE382);
// \011$pad = str_repeat(' ', $TLE383);
// \011$TLE384 = ($name . $pad);
// \011$TLE385 = ($TLE384 . $num);
// \011$TLE387 = ($TLE385 . '
// ');
// \011print($TLE387);
// \011ob_start();
// \011$TLE388 = getmicrotime();
// \011return $TLE388;
// }
PHP_FUNCTION (end_test)
{
  zval *local_TLE375 = NULL;
  zval *local_TLE376 = NULL;
  zval *local_TLE380 = NULL;
  zval *local_TLE381 = NULL;
  zval *local_TLE382 = NULL;
  zval *local_TLE383 = NULL;
  zval *local_TLE384 = NULL;
  zval *local_TLE385 = NULL;
  zval *local_TLE387 = NULL;
  zval *local_TLE388 = NULL;
  zval *local_end = NULL;
  zval *local_name = NULL;
  zval *local_num = NULL;
  zval *local_pad = NULL;
  zval *local_start = NULL;
  zval *local_total = NULL;
// Add all parameters as local variables
  {
    int num_args = ZEND_NUM_ARGS ();
    zval *params[2];
    zend_get_parameters_array (0, num_args, params);
// param 0
    params[0]->refcount++;
    local_start = params[0];
// param 1
    params[1]->refcount++;
    local_name = params[1];
  }
// Function body
// global $total;
  {
// Normal global
    if (local_total == NULL)
      {
	local_total = EG (uninitialized_zval_ptr);
	local_total->refcount++;
      }
    zval **p_local_global_var = &local_total;
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "total", 6, 6954064761897u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// $end = getmicrotime();
  {
    if (local_end == NULL)
      {
	local_end = EG (uninitialized_zval_ptr);
	local_end->refcount++;
      }
    zval **p_lhs = &local_end;
    initialize_function_call (&getmicrotime_fci, &getmicrotime_fcic,
			      "getmicrotime",
			      "test/subjects/benchmarks/zend/bench.php",
			      361 TSRMLS_CC);
    zend_function *signature = getmicrotime_fcic.function_handler;
    zval **args_ind[0];
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = getmicrotime_fci.param_count;
    zval ***params_save = getmicrotime_fci.params;
    zval **retval_save = getmicrotime_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    getmicrotime_fci.params = args_ind;
    getmicrotime_fci.param_count = 0;
    getmicrotime_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&getmicrotime_fci, &getmicrotime_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    getmicrotime_fci.params = params_save;
    getmicrotime_fci.param_count = param_count_save;
    getmicrotime_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ob_end_clean();
  {
    initialize_function_call (&ob_end_clean_fci, &ob_end_clean_fcic,
			      "ob_end_clean",
			      "test/subjects/benchmarks/zend/bench.php",
			      362 TSRMLS_CC);
    zend_function *signature = ob_end_clean_fcic.function_handler;
    zval **args_ind[0];
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = ob_end_clean_fci.param_count;
    zval ***params_save = ob_end_clean_fci.params;
    zval **retval_save = ob_end_clean_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    ob_end_clean_fci.params = args_ind;
    ob_end_clean_fci.param_count = 0;
    ob_end_clean_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&ob_end_clean_fci, &ob_end_clean_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    ob_end_clean_fci.params = params_save;
    ob_end_clean_fci.param_count = param_count_save;
    ob_end_clean_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE375 = ($end - $start);
  {
    if (local_TLE375 == NULL)
      {
	local_TLE375 = EG (uninitialized_zval_ptr);
	local_TLE375->refcount++;
      }
    zval **p_lhs = &local_TLE375;
    zval *left;
    if (local_end == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_end;
      }
    zval *right;
    if (local_start == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_start;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $total = ($total + $TLE375);
  {
    if (local_total == NULL)
      {
	local_total = EG (uninitialized_zval_ptr);
	local_total->refcount++;
      }
    zval **p_lhs = &local_total;
    zval *left;
    if (local_total == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_total;
      }
    zval *right;
    if (local_TLE375 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE375;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    add_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE376 = ($end - $start);
  {
    if (local_TLE376 == NULL)
      {
	local_TLE376 = EG (uninitialized_zval_ptr);
	local_TLE376->refcount++;
      }
    zval **p_lhs = &local_TLE376;
    zval *left;
    if (local_end == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_end;
      }
    zval *right;
    if (local_start == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_start;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $num = number_format($TLE376, 3);
  {
    if (local_num == NULL)
      {
	local_num = EG (uninitialized_zval_ptr);
	local_num->refcount++;
      }
    zval **p_lhs = &local_num;
    initialize_function_call (&number_format_fci, &number_format_fcic,
			      "number_format",
			      "test/subjects/benchmarks/zend/bench.php",
			      364 TSRMLS_CC);
    zend_function *signature = number_format_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_TLE376 == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_TLE376;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_int_14;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = number_format_fci.param_count;
    zval ***params_save = number_format_fci.params;
    zval **retval_save = number_format_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    number_format_fci.params = args_ind;
    number_format_fci.param_count = 2;
    number_format_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&number_format_fci, &number_format_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    number_format_fci.params = params_save;
    number_format_fci.param_count = param_count_save;
    number_format_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE380 = strlen($name);
  {
    if (local_TLE380 == NULL)
      {
	local_TLE380 = EG (uninitialized_zval_ptr);
	local_TLE380->refcount++;
      }
    zval **p_lhs = &local_TLE380;
    initialize_function_call (&strlen_fci, &strlen_fcic, "strlen",
			      "test/subjects/benchmarks/zend/bench.php",
			      365 TSRMLS_CC);
    zend_function *signature = strlen_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_name == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_name;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = strlen_fci.param_count;
    zval ***params_save = strlen_fci.params;
    zval **retval_save = strlen_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    strlen_fci.params = args_ind;
    strlen_fci.param_count = 1;
    strlen_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&strlen_fci, &strlen_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    strlen_fci.params = params_save;
    strlen_fci.param_count = param_count_save;
    strlen_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE381 = (24 - $TLE380);
  {
    if (local_TLE381 == NULL)
      {
	local_TLE381 = EG (uninitialized_zval_ptr);
	local_TLE381->refcount++;
      }
    zval **p_lhs = &local_TLE381;
    zval *left = phc_const_pool_int_23;
    zval *right;
    if (local_TLE380 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE380;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE382 = strlen($num);
  {
    if (local_TLE382 == NULL)
      {
	local_TLE382 = EG (uninitialized_zval_ptr);
	local_TLE382->refcount++;
      }
    zval **p_lhs = &local_TLE382;
    initialize_function_call (&strlen_fci, &strlen_fcic, "strlen",
			      "test/subjects/benchmarks/zend/bench.php",
			      365 TSRMLS_CC);
    zend_function *signature = strlen_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_num == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_num;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = strlen_fci.param_count;
    zval ***params_save = strlen_fci.params;
    zval **retval_save = strlen_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    strlen_fci.params = args_ind;
    strlen_fci.param_count = 1;
    strlen_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&strlen_fci, &strlen_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    strlen_fci.params = params_save;
    strlen_fci.param_count = param_count_save;
    strlen_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE383 = ($TLE381 - $TLE382);
  {
    if (local_TLE383 == NULL)
      {
	local_TLE383 = EG (uninitialized_zval_ptr);
	local_TLE383->refcount++;
      }
    zval **p_lhs = &local_TLE383;
    zval *left;
    if (local_TLE381 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE381;
      }
    zval *right;
    if (local_TLE382 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE382;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $pad = str_repeat(' ', $TLE383);
  {
    if (local_pad == NULL)
      {
	local_pad = EG (uninitialized_zval_ptr);
	local_pad->refcount++;
      }
    zval **p_lhs = &local_pad;
    initialize_function_call (&str_repeat_fci, &str_repeat_fcic, "str_repeat",
			      "test/subjects/benchmarks/zend/bench.php",
			      365 TSRMLS_CC);
    zend_function *signature = str_repeat_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_string_9;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg;
      if (local_TLE383 == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_TLE383;
	}
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = str_repeat_fci.param_count;
    zval ***params_save = str_repeat_fci.params;
    zval **retval_save = str_repeat_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    str_repeat_fci.params = args_ind;
    str_repeat_fci.param_count = 2;
    str_repeat_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&str_repeat_fci, &str_repeat_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    str_repeat_fci.params = params_save;
    str_repeat_fci.param_count = param_count_save;
    str_repeat_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE384 = ($name . $pad);
  {
    if (local_TLE384 == NULL)
      {
	local_TLE384 = EG (uninitialized_zval_ptr);
	local_TLE384->refcount++;
      }
    zval **p_lhs = &local_TLE384;
    zval *left;
    if (local_name == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_name;
      }
    zval *right;
    if (local_pad == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_pad;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE385 = ($TLE384 . $num);
  {
    if (local_TLE385 == NULL)
      {
	local_TLE385 = EG (uninitialized_zval_ptr);
	local_TLE385->refcount++;
      }
    zval **p_lhs = &local_TLE385;
    zval *left;
    if (local_TLE384 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE384;
      }
    zval *right;
    if (local_num == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_num;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE387 = ($TLE385 . '
// ');
  {
    if (local_TLE387 == NULL)
      {
	local_TLE387 = EG (uninitialized_zval_ptr);
	local_TLE387->refcount++;
      }
    zval **p_lhs = &local_TLE387;
    zval *left;
    if (local_TLE385 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE385;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE387);
  {
    zval *p_arg;
    if (local_TLE387 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE387;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// ob_start();
  {
    initialize_function_call (&ob_start_fci, &ob_start_fcic, "ob_start",
			      "test/subjects/benchmarks/zend/bench.php",
			      368 TSRMLS_CC);
    zend_function *signature = ob_start_fcic.function_handler;
    zval **args_ind[0];
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = ob_start_fci.param_count;
    zval ***params_save = ob_start_fci.params;
    zval **retval_save = ob_start_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    ob_start_fci.params = args_ind;
    ob_start_fci.param_count = 0;
    ob_start_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&ob_start_fci, &ob_start_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    ob_start_fci.params = params_save;
    ob_start_fci.param_count = param_count_save;
    ob_start_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE388 = getmicrotime();
  {
    if (local_TLE388 == NULL)
      {
	local_TLE388 = EG (uninitialized_zval_ptr);
	local_TLE388->refcount++;
      }
    zval **p_lhs = &local_TLE388;
    initialize_function_call (&getmicrotime_fci, &getmicrotime_fcic,
			      "getmicrotime",
			      "test/subjects/benchmarks/zend/bench.php",
			      369 TSRMLS_CC);
    zend_function *signature = getmicrotime_fcic.function_handler;
    zval **args_ind[0];
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = getmicrotime_fci.param_count;
    zval ***params_save = getmicrotime_fci.params;
    zval **retval_save = getmicrotime_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    getmicrotime_fci.params = args_ind;
    getmicrotime_fci.param_count = 0;
    getmicrotime_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&getmicrotime_fci, &getmicrotime_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    getmicrotime_fci.params = params_save;
    getmicrotime_fci.param_count = param_count_save;
    getmicrotime_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// return $TLE388;
  {
    zval *rhs;
    if (local_TLE388 == NULL)
      {
	rhs = EG (uninitialized_zval_ptr);
      }
    else
      {
	rhs = local_TLE388;
      }
    return_value->value = rhs->value;
    return_value->type = rhs->type;
    zval_copy_ctor (return_value);
    goto end_of_function;
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE375 != NULL)
    {
      zval_ptr_dtor (&local_TLE375);
    }
  if (local_TLE376 != NULL)
    {
      zval_ptr_dtor (&local_TLE376);
    }
  if (local_TLE380 != NULL)
    {
      zval_ptr_dtor (&local_TLE380);
    }
  if (local_TLE381 != NULL)
    {
      zval_ptr_dtor (&local_TLE381);
    }
  if (local_TLE382 != NULL)
    {
      zval_ptr_dtor (&local_TLE382);
    }
  if (local_TLE383 != NULL)
    {
      zval_ptr_dtor (&local_TLE383);
    }
  if (local_TLE384 != NULL)
    {
      zval_ptr_dtor (&local_TLE384);
    }
  if (local_TLE385 != NULL)
    {
      zval_ptr_dtor (&local_TLE385);
    }
  if (local_TLE387 != NULL)
    {
      zval_ptr_dtor (&local_TLE387);
    }
  if (local_TLE388 != NULL)
    {
      zval_ptr_dtor (&local_TLE388);
    }
  if (local_end != NULL)
    {
      zval_ptr_dtor (&local_end);
    }
  if (local_name != NULL)
    {
      zval_ptr_dtor (&local_name);
    }
  if (local_num != NULL)
    {
      zval_ptr_dtor (&local_num);
    }
  if (local_pad != NULL)
    {
      zval_ptr_dtor (&local_pad);
    }
  if (local_start != NULL)
    {
      zval_ptr_dtor (&local_start);
    }
  if (local_total != NULL)
    {
      zval_ptr_dtor (&local_total);
    }
}

// function total()
// {
// \011global $total;
// \011print('------------------------
// ');
// \011$num = number_format($total, 3);
// \011$TLE399 = strlen($num);
// \011$TLE400 = (19 - $TLE399);
// \011$pad = str_repeat(' ', $TLE400);
// \011$TLE402 = ('Total' . $pad);
// \011$TLE403 = ($TLE402 . $num);
// \011$TLE405 = ($TLE403 . '
// ');
// \011print($TLE405);
// }
PHP_FUNCTION (total)
{
  zval *local_TLE399 = NULL;
  zval *local_TLE400 = NULL;
  zval *local_TLE402 = NULL;
  zval *local_TLE403 = NULL;
  zval *local_TLE405 = NULL;
  zval *local_num = NULL;
  zval *local_pad = NULL;
  zval *local_total = NULL;
// Function body
// global $total;
  {
// Normal global
    if (local_total == NULL)
      {
	local_total = EG (uninitialized_zval_ptr);
	local_total->refcount++;
      }
    zval **p_local_global_var = &local_total;
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "total", 6, 6954064761897u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// print('------------------------
// ');
  {
    zval *p_arg = phc_const_pool_string_21;
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// $num = number_format($total, 3);
  {
    if (local_num == NULL)
      {
	local_num = EG (uninitialized_zval_ptr);
	local_num->refcount++;
      }
    zval **p_lhs = &local_num;
    initialize_function_call (&number_format_fci, &number_format_fcic,
			      "number_format",
			      "test/subjects/benchmarks/zend/bench.php",
			      377 TSRMLS_CC);
    zend_function *signature = number_format_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_total == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_total;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_int_14;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = number_format_fci.param_count;
    zval ***params_save = number_format_fci.params;
    zval **retval_save = number_format_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    number_format_fci.params = args_ind;
    number_format_fci.param_count = 2;
    number_format_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&number_format_fci, &number_format_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    number_format_fci.params = params_save;
    number_format_fci.param_count = param_count_save;
    number_format_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE399 = strlen($num);
  {
    if (local_TLE399 == NULL)
      {
	local_TLE399 = EG (uninitialized_zval_ptr);
	local_TLE399->refcount++;
      }
    zval **p_lhs = &local_TLE399;
    initialize_function_call (&strlen_fci, &strlen_fcic, "strlen",
			      "test/subjects/benchmarks/zend/bench.php",
			      378 TSRMLS_CC);
    zend_function *signature = strlen_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg;
      if (local_num == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_num;
	}
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = strlen_fci.param_count;
    zval ***params_save = strlen_fci.params;
    zval **retval_save = strlen_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    strlen_fci.params = args_ind;
    strlen_fci.param_count = 1;
    strlen_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&strlen_fci, &strlen_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    strlen_fci.params = params_save;
    strlen_fci.param_count = param_count_save;
    strlen_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE400 = (19 - $TLE399);
  {
    if (local_TLE400 == NULL)
      {
	local_TLE400 = EG (uninitialized_zval_ptr);
	local_TLE400->refcount++;
      }
    zval **p_lhs = &local_TLE400;
    zval *left = phc_const_pool_int_24;
    zval *right;
    if (local_TLE399 == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_TLE399;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    sub_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $pad = str_repeat(' ', $TLE400);
  {
    if (local_pad == NULL)
      {
	local_pad = EG (uninitialized_zval_ptr);
	local_pad->refcount++;
      }
    zval **p_lhs = &local_pad;
    initialize_function_call (&str_repeat_fci, &str_repeat_fcic, "str_repeat",
			      "test/subjects/benchmarks/zend/bench.php",
			      378 TSRMLS_CC);
    zend_function *signature = str_repeat_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_string_9;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg;
      if (local_TLE400 == NULL)
	{
	  arg = EG (uninitialized_zval_ptr);
	}
      else
	{
	  arg = local_TLE400;
	}
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = str_repeat_fci.param_count;
    zval ***params_save = str_repeat_fci.params;
    zval **retval_save = str_repeat_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    str_repeat_fci.params = args_ind;
    str_repeat_fci.param_count = 2;
    str_repeat_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&str_repeat_fci, &str_repeat_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    str_repeat_fci.params = params_save;
    str_repeat_fci.param_count = param_count_save;
    str_repeat_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE402 = ('Total' . $pad);
  {
    if (local_TLE402 == NULL)
      {
	local_TLE402 = EG (uninitialized_zval_ptr);
	local_TLE402->refcount++;
      }
    zval **p_lhs = &local_TLE402;
    zval *left = phc_const_pool_string_22;
    zval *right;
    if (local_pad == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_pad;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE403 = ($TLE402 . $num);
  {
    if (local_TLE403 == NULL)
      {
	local_TLE403 = EG (uninitialized_zval_ptr);
	local_TLE403->refcount++;
      }
    zval **p_lhs = &local_TLE403;
    zval *left;
    if (local_TLE402 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE402;
      }
    zval *right;
    if (local_num == NULL)
      {
	right = EG (uninitialized_zval_ptr);
      }
    else
      {
	right = local_num;
      }
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE405 = ($TLE403 . '
// ');
  {
    if (local_TLE405 == NULL)
      {
	local_TLE405 = EG (uninitialized_zval_ptr);
	local_TLE405->refcount++;
      }
    zval **p_lhs = &local_TLE405;
    zval *left;
    if (local_TLE403 == NULL)
      {
	left = EG (uninitialized_zval_ptr);
      }
    else
      {
	left = local_TLE403;
      }
    zval *right = phc_const_pool_string_5;
    if (in_copy_on_write (*p_lhs))
      {
	zval_ptr_dtor (p_lhs);
	ALLOC_INIT_ZVAL (*p_lhs);
      }
    zval old = **p_lhs;
    int result_is_operand = (*p_lhs == left || *p_lhs == right);
    concat_function (*p_lhs, left, right TSRMLS_CC);
    if (!result_is_operand)
      zval_dtor (&old);
    phc_check_invariants (TSRMLS_C);
  }
// print($TLE405);
  {
    zval *p_arg;
    if (local_TLE405 == NULL)
      {
	p_arg = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_arg = local_TLE405;
      }
    phc_builtin_print (p_arg, NULL,
		       "test/subjects/benchmarks/zend/bench.php" TSRMLS_CC);
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE399 != NULL)
    {
      zval_ptr_dtor (&local_TLE399);
    }
  if (local_TLE400 != NULL)
    {
      zval_ptr_dtor (&local_TLE400);
    }
  if (local_TLE402 != NULL)
    {
      zval_ptr_dtor (&local_TLE402);
    }
  if (local_TLE403 != NULL)
    {
      zval_ptr_dtor (&local_TLE403);
    }
  if (local_TLE405 != NULL)
    {
      zval_ptr_dtor (&local_TLE405);
    }
  if (local_num != NULL)
    {
      zval_ptr_dtor (&local_num);
    }
  if (local_pad != NULL)
    {
      zval_ptr_dtor (&local_pad);
    }
  if (local_total != NULL)
    {
      zval_ptr_dtor (&local_total);
    }
}

// function __MAIN__()
// {
// \011global $HTTP_REQUEST_VARS;
// \011global $_REQUEST;
// \011global $HTTP_FILES_VARS;
// \011global $_FILES;
// \011global $HTTP_COOKIE_VARS;
// \011global $_COOKIE;
// \011global $HTTP_GET_VARS;
// \011global $_GET;
// \011global $HTTP_POST_VARS;
// \011global $_POST;
// \011global $HTTP_ENV_VARS;
// \011global $_ENV;
// \011global $GLOBALS;
// \011date_default_timezone_set('UTC');
// \011$t = start_test();
// \011$TLE406 = $t;
// \011$t0 = $TLE406;
// \011simple();
// \011$t = end_test($t, 'simple');
// \011simplecall();
// \011$t = end_test($t, 'simplecall');
// \011simpleucall();
// \011$t = end_test($t, 'simpleucall');
// \011simpleudcall();
// \011$t = end_test($t, 'simpleudcall');
// \011mandel();
// \011$t = end_test($t, 'mandel');
// \011mandel2();
// \011$t = end_test($t, 'mandel2');
// \011ackermann(7);
// \011$t = end_test($t, 'ackermann(7)');
// \011ary(50000);
// \011$t = end_test($t, 'ary(50000)');
// \011ary2(50000);
// \011$t = end_test($t, 'ary2(50000)');
// \011ary3(2000);
// \011$t = end_test($t, 'ary3(2000)');
// \011fibo(30);
// \011$t = end_test($t, 'fibo(30)');
// \011hash1(50000);
// \011$t = end_test($t, 'hash1(50000)');
// \011hash2(500);
// \011$t = end_test($t, 'hash2(500)');
// \011heapsort(20000);
// \011$t = end_test($t, 'heapsort(20000)');
// \011matrix(20);
// \011$t = end_test($t, 'matrix(20)');
// \011nestedloop(12);
// \011$t = end_test($t, 'nestedloop(12)');
// \011sieve(30);
// \011$t = end_test($t, 'sieve(30)');
// \011strcat(200000);
// \011$t = end_test($t, 'strcat(200000)');
// \011total($t0, 'Total');
// }
PHP_FUNCTION (__MAIN__)
{
  zval *local_TLE406 = NULL;
// Function body
// global $HTTP_REQUEST_VARS;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "HTTP_REQUEST_VARS", 18,
		    14546357509836879752u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "HTTP_REQUEST_VARS", 18,
		    14546357509836879752u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// global $_REQUEST;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "_REQUEST", 9,
		    249877393482598893u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "_REQUEST", 9,
		    249877393482598893u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// global $HTTP_FILES_VARS;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "HTTP_FILES_VARS", 16,
		    10531313393322008242u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "HTTP_FILES_VARS", 16,
		    10531313393322008242u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// global $_FILES;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "_FILES", 7,
		    229455359975127u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "_FILES", 7,
		    229455359975127u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// global $HTTP_COOKIE_VARS;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "HTTP_COOKIE_VARS", 17,
		    15349659020743581081u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "HTTP_COOKIE_VARS", 17,
		    15349659020743581081u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// global $_COOKIE;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "_COOKIE", 8,
		    7572023243352414u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "_COOKIE", 8,
		    7572023243352414u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// global $HTTP_GET_VARS;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "HTTP_GET_VARS", 14,
		    17677214637803008831u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "HTTP_GET_VARS", 14,
		    17677214637803008831u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// global $_GET;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "_GET", 5,
		    210702841668u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "_GET", 5, 210702841668u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// global $HTTP_POST_VARS;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "HTTP_POST_VARS", 15,
		    11499448473500914277u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "HTTP_POST_VARS", 15,
		    11499448473500914277u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// global $_POST;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "_POST", 6,
		    6953204809386u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "_POST", 6, 6953204809386u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// global $HTTP_ENV_VARS;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "HTTP_ENV_VARS", 14,
		    17677212211134695080u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "HTTP_ENV_VARS", 14,
		    17677212211134695080u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// global $_ENV;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "_ENV", 5,
		    210702779661u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "_ENV", 5, 210702779661u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// global $GLOBALS;
  {
// Normal global
    zval **p_local_global_var =
      get_st_entry (EG (active_symbol_table), "GLOBALS", 8,
		    7571012008160073u TSRMLS_CC);
// Normal global
    zval **p_global_var =
      get_st_entry (&EG (symbol_table), "GLOBALS", 8,
		    7571012008160073u TSRMLS_CC);
    copy_into_ref (p_local_global_var, p_global_var);
    phc_check_invariants (TSRMLS_C);
  }
// date_default_timezone_set('UTC');
  {
    initialize_function_call (&date_default_timezone_set_fci,
			      &date_default_timezone_set_fcic,
			      "date_default_timezone_set",
			      "test/subjects/benchmarks/zend/bench.php",
			      2 TSRMLS_CC);
    zend_function *signature =
      date_default_timezone_set_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_string_23;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = date_default_timezone_set_fci.param_count;
    zval ***params_save = date_default_timezone_set_fci.params;
    zval **retval_save = date_default_timezone_set_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    date_default_timezone_set_fci.params = args_ind;
    date_default_timezone_set_fci.param_count = 1;
    date_default_timezone_set_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&date_default_timezone_set_fci,
			  &date_default_timezone_set_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    date_default_timezone_set_fci.params = params_save;
    date_default_timezone_set_fci.param_count = param_count_save;
    date_default_timezone_set_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = start_test();
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&start_test_fci, &start_test_fcic, "start_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      382 TSRMLS_CC);
    zend_function *signature = start_test_fcic.function_handler;
    zval **args_ind[0];
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = start_test_fci.param_count;
    zval ***params_save = start_test_fci.params;
    zval **retval_save = start_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    start_test_fci.params = args_ind;
    start_test_fci.param_count = 0;
    start_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&start_test_fci, &start_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    start_test_fci.params = params_save;
    start_test_fci.param_count = param_count_save;
    start_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $TLE406 = $t;
  {
    if (local_TLE406 == NULL)
      {
	local_TLE406 = EG (uninitialized_zval_ptr);
	local_TLE406->refcount++;
      }
    zval **p_lhs = &local_TLE406;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var =
      read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t0 = $TLE406;
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t0", 3, 193504905u TSRMLS_CC);
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
// Read normal variable
    zval *p_rhs_var;
    if (local_TLE406 == NULL)
      {
	p_rhs_var = EG (uninitialized_zval_ptr);
      }
    else
      {
	p_rhs_var = local_TLE406;
      }
    p_rhs = &p_rhs_var;
    if (*p_lhs != *p_rhs)
      write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// simple();
  
// $t = end_test($t, 'simple');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      384 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_24;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// simplecall();
  
// $t = end_test($t, 'simplecall');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      386 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_25;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// simpleucall();
  
// $t = end_test($t, 'simpleucall');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      388 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_26;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// simpleudcall();
  
// $t = end_test($t, 'simpleudcall');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      390 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_27;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// mandel();
  {
    initialize_function_call (&mandel_fci, &mandel_fcic, "mandel",
			      "test/subjects/benchmarks/zend/bench.php",
			      391 TSRMLS_CC);
    zend_function *signature = mandel_fcic.function_handler;
    zval **args_ind[0];
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = mandel_fci.param_count;
    zval ***params_save = mandel_fci.params;
    zval **retval_save = mandel_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    mandel_fci.params = args_ind;
    mandel_fci.param_count = 0;
    mandel_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&mandel_fci, &mandel_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    mandel_fci.params = params_save;
    mandel_fci.param_count = param_count_save;
    mandel_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'mandel');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      392 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_28;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// mandel2();
  {
    initialize_function_call (&mandel2_fci, &mandel2_fcic, "mandel2",
			      "test/subjects/benchmarks/zend/bench.php",
			      393 TSRMLS_CC);
    zend_function *signature = mandel2_fcic.function_handler;
    zval **args_ind[0];
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = mandel2_fci.param_count;
    zval ***params_save = mandel2_fci.params;
    zval **retval_save = mandel2_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    mandel2_fci.params = args_ind;
    mandel2_fci.param_count = 0;
    mandel2_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&mandel2_fci, &mandel2_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    mandel2_fci.params = params_save;
    mandel2_fci.param_count = param_count_save;
    mandel2_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'mandel2');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      394 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_29;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ackermann(7);
  {
    initialize_function_call (&ackermann_fci, &ackermann_fcic, "ackermann",
			      "test/subjects/benchmarks/zend/bench.php",
			      395 TSRMLS_CC);
    zend_function *signature = ackermann_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_25;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = ackermann_fci.param_count;
    zval ***params_save = ackermann_fci.params;
    zval **retval_save = ackermann_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    ackermann_fci.params = args_ind;
    ackermann_fci.param_count = 1;
    ackermann_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&ackermann_fci, &ackermann_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    ackermann_fci.params = params_save;
    ackermann_fci.param_count = param_count_save;
    ackermann_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'ackermann(7)');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      396 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_30;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ary(50000);
  {
    initialize_function_call (&ary_fci, &ary_fcic, "ary",
			      "test/subjects/benchmarks/zend/bench.php",
			      397 TSRMLS_CC);
    zend_function *signature = ary_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_26;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = ary_fci.param_count;
    zval ***params_save = ary_fci.params;
    zval **retval_save = ary_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    ary_fci.params = args_ind;
    ary_fci.param_count = 1;
    ary_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&ary_fci, &ary_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    ary_fci.params = params_save;
    ary_fci.param_count = param_count_save;
    ary_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'ary(50000)');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      398 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_31;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ary2(50000);
  {
    initialize_function_call (&ary2_fci, &ary2_fcic, "ary2",
			      "test/subjects/benchmarks/zend/bench.php",
			      399 TSRMLS_CC);
    zend_function *signature = ary2_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_26;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = ary2_fci.param_count;
    zval ***params_save = ary2_fci.params;
    zval **retval_save = ary2_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    ary2_fci.params = args_ind;
    ary2_fci.param_count = 1;
    ary2_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&ary2_fci, &ary2_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    ary2_fci.params = params_save;
    ary2_fci.param_count = param_count_save;
    ary2_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'ary2(50000)');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      400 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_32;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// ary3(2000);
  {
    initialize_function_call (&ary3_fci, &ary3_fcic, "ary3",
			      "test/subjects/benchmarks/zend/bench.php",
			      401 TSRMLS_CC);
    zend_function *signature = ary3_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_27;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = ary3_fci.param_count;
    zval ***params_save = ary3_fci.params;
    zval **retval_save = ary3_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    ary3_fci.params = args_ind;
    ary3_fci.param_count = 1;
    ary3_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&ary3_fci, &ary3_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    ary3_fci.params = params_save;
    ary3_fci.param_count = param_count_save;
    ary3_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'ary3(2000)');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      402 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_33;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// fibo(30);
  {
    initialize_function_call (&fibo_fci, &fibo_fcic, "fibo",
			      "test/subjects/benchmarks/zend/bench.php",
			      403 TSRMLS_CC);
    zend_function *signature = fibo_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_9;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = fibo_fci.param_count;
    zval ***params_save = fibo_fci.params;
    zval **retval_save = fibo_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    fibo_fci.params = args_ind;
    fibo_fci.param_count = 1;
    fibo_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&fibo_fci, &fibo_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    fibo_fci.params = params_save;
    fibo_fci.param_count = param_count_save;
    fibo_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'fibo(30)');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      404 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_34;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// hash1(50000);
  {
    initialize_function_call (&hash1_fci, &hash1_fcic, "hash1",
			      "test/subjects/benchmarks/zend/bench.php",
			      405 TSRMLS_CC);
    zend_function *signature = hash1_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_26;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = hash1_fci.param_count;
    zval ***params_save = hash1_fci.params;
    zval **retval_save = hash1_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    hash1_fci.params = args_ind;
    hash1_fci.param_count = 1;
    hash1_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&hash1_fci, &hash1_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    hash1_fci.params = params_save;
    hash1_fci.param_count = param_count_save;
    hash1_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'hash1(50000)');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      406 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_35;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// hash2(500);
  {
    initialize_function_call (&hash2_fci, &hash2_fcic, "hash2",
			      "test/subjects/benchmarks/zend/bench.php",
			      407 TSRMLS_CC);
    zend_function *signature = hash2_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_28;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = hash2_fci.param_count;
    zval ***params_save = hash2_fci.params;
    zval **retval_save = hash2_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    hash2_fci.params = args_ind;
    hash2_fci.param_count = 1;
    hash2_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&hash2_fci, &hash2_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    hash2_fci.params = params_save;
    hash2_fci.param_count = param_count_save;
    hash2_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'hash2(500)');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      408 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_36;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// heapsort(20000);
  {
    initialize_function_call (&heapsort_fci, &heapsort_fcic, "heapsort",
			      "test/subjects/benchmarks/zend/bench.php",
			      409 TSRMLS_CC);
    zend_function *signature = heapsort_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_29;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = heapsort_fci.param_count;
    zval ***params_save = heapsort_fci.params;
    zval **retval_save = heapsort_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    heapsort_fci.params = args_ind;
    heapsort_fci.param_count = 1;
    heapsort_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&heapsort_fci, &heapsort_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    heapsort_fci.params = params_save;
    heapsort_fci.param_count = param_count_save;
    heapsort_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'heapsort(20000)');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      410 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_37;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// matrix(20);
  {
    initialize_function_call (&matrix_fci, &matrix_fcic, "matrix",
			      "test/subjects/benchmarks/zend/bench.php",
			      411 TSRMLS_CC);
    zend_function *signature = matrix_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_30;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = matrix_fci.param_count;
    zval ***params_save = matrix_fci.params;
    zval **retval_save = matrix_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    matrix_fci.params = args_ind;
    matrix_fci.param_count = 1;
    matrix_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&matrix_fci, &matrix_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    matrix_fci.params = params_save;
    matrix_fci.param_count = param_count_save;
    matrix_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'matrix(20)');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      412 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_38;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// nestedloop(12);
  {
    initialize_function_call (&nestedloop_fci, &nestedloop_fcic, "nestedloop",
			      "test/subjects/benchmarks/zend/bench.php",
			      413 TSRMLS_CC);
    zend_function *signature = nestedloop_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_3;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = nestedloop_fci.param_count;
    zval ***params_save = nestedloop_fci.params;
    zval **retval_save = nestedloop_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    nestedloop_fci.params = args_ind;
    nestedloop_fci.param_count = 1;
    nestedloop_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&nestedloop_fci, &nestedloop_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    nestedloop_fci.params = params_save;
    nestedloop_fci.param_count = param_count_save;
    nestedloop_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'nestedloop(12)');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      414 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_39;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// sieve(30);
  {
    initialize_function_call (&sieve_fci, &sieve_fcic, "sieve",
			      "test/subjects/benchmarks/zend/bench.php",
			      415 TSRMLS_CC);
    zend_function *signature = sieve_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_9;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = sieve_fci.param_count;
    zval ***params_save = sieve_fci.params;
    zval **retval_save = sieve_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    sieve_fci.params = args_ind;
    sieve_fci.param_count = 1;
    sieve_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&sieve_fci, &sieve_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    sieve_fci.params = params_save;
    sieve_fci.param_count = param_count_save;
    sieve_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'sieve(30)');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      416 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_40;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// strcat(200000);
  {
    initialize_function_call (&strcat_fci, &strcat_fcic, "strcat",
			      "test/subjects/benchmarks/zend/bench.php",
			      417 TSRMLS_CC);
    zend_function *signature = strcat_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[1];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[1];		// set to 1 if the arg is new
    zval *args[1];
    zval **args_ind[1];
    destruct[0] = 0;
    {
      zval *arg = phc_const_pool_int_31;
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = strcat_fci.param_count;
    zval ***params_save = strcat_fci.params;
    zval **retval_save = strcat_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    strcat_fci.params = args_ind;
    strcat_fci.param_count = 1;
    strcat_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&strcat_fci, &strcat_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    strcat_fci.params = params_save;
    strcat_fci.param_count = param_count_save;
    strcat_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// $t = end_test($t, 'strcat(200000)');
  {
    zval **p_lhs =
      get_st_entry (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
    initialize_function_call (&end_test_fci, &end_test_fcic, "end_test",
			      "test/subjects/benchmarks/zend/bench.php",
			      418 TSRMLS_CC);
    zend_function *signature = end_test_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t", 2, 5863737u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_41;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = end_test_fci.param_count;
    zval ***params_save = end_test_fci.params;
    zval **retval_save = end_test_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    end_test_fci.params = args_ind;
    end_test_fci.param_count = 2;
    end_test_fci.retval_ptr_ptr = p_rhs;
    int success =
      zend_call_function (&end_test_fci, &end_test_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    end_test_fci.params = params_save;
    end_test_fci.param_count = param_count_save;
    end_test_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    write_var (p_lhs, p_rhs, &is_p_rhs_new TSRMLS_CC);
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// total($t0, 'Total');
  {
    initialize_function_call (&total_fci, &total_fcic, "total",
			      "test/subjects/benchmarks/zend/bench.php",
			      419 TSRMLS_CC);
    zend_function *signature = total_fcic.function_handler;
    zend_arg_info *arg_info = signature->common.arg_info;
    int by_ref[2];
    if (arg_info)
      {
	by_ref[0] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[0] = signature->common.pass_rest_by_reference;
      }
    if (arg_info)
      {
	by_ref[1] = arg_info->pass_by_reference;
	arg_info++;
      }
    else
      {
	by_ref[1] = signature->common.pass_rest_by_reference;
      }
// Setup array of arguments
    int destruct[2];		// set to 1 if the arg is new
    zval *args[2];
    zval **args_ind[2];
    destruct[0] = 0;
    {
      zval *arg =
	read_var (EG (active_symbol_table), "t0", 3, 193504905u TSRMLS_CC);
      args[0] = fetch_var_arg (arg, &destruct[0]);
      args_ind[0] = &args[0];
    }
    destruct[1] = 0;
    {
      zval *arg = phc_const_pool_string_22;
      args[1] = fetch_var_arg (arg, &destruct[1]);
      args_ind[1] = &args[1];
    }
    phc_setup_error (1, "<unknown>", 0, NULL TSRMLS_CC);
    int param_count_save = total_fci.param_count;
    zval ***params_save = total_fci.params;
    zval **retval_save = total_fci.retval_ptr_ptr;
    zval *p_rhs_temp = NULL;
    zval **p_rhs;
    p_rhs = &p_rhs_temp;
    int is_p_rhs_new = 0;
    total_fci.params = args_ind;
    total_fci.param_count = 2;
    total_fci.retval_ptr_ptr = p_rhs;
    int success = zend_call_function (&total_fci, &total_fcic TSRMLS_CC);
    assert (success == SUCCESS);
    total_fci.params = params_save;
    total_fci.param_count = param_count_save;
    total_fci.retval_ptr_ptr = retval_save;
    phc_setup_error (0, NULL, 0, NULL TSRMLS_CC);
    is_p_rhs_new = 1;
    if (destruct[0])
      {
	assert (destruct[0] == 1);
	zval_ptr_dtor (args_ind[0]);
      }
    if (destruct[1])
      {
	assert (destruct[1] == 1);
	zval_ptr_dtor (args_ind[1]);
      }
    if (is_p_rhs_new)
      zval_ptr_dtor (p_rhs);
    phc_check_invariants (TSRMLS_C);
  }
// Method exit
end_of_function:__attribute__ ((unused));
  if (local_TLE406 != NULL)
    {
      zval_ptr_dtor (&local_TLE406);
    }
}

// ArgInfo structures (necessary to support compile time pass-by-reference)
ZEND_BEGIN_ARG_INFO_EX (simple_arg_info, 0, 0, 0)
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (simplecall_arg_info, 0, 0, 0)
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (hallo_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "a")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (simpleucall_arg_info, 0, 0, 0)
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (simpleudcall_arg_info, 0, 0, 0)
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (hallo2_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "a")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (mandel_arg_info, 0, 0, 0)
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (mandel2_arg_info, 0, 0, 0)
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (Ack_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "m")
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (ackermann_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (ary_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (ary2_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (ary3_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (fibo_r_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (fibo_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (hash1_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (hash2_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (gen_random_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (heapsort_r_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_ARG_INFO (1, "ra")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (heapsort_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "N")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (mkmatrix_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "rows")
ZEND_ARG_INFO (0, "cols")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (mmult_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "rows")
ZEND_ARG_INFO (0, "cols")
ZEND_ARG_INFO (0, "m1")
ZEND_ARG_INFO (0, "m2")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (matrix_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (nestedloop_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (sieve_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (strcat_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "n")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (getmicrotime_arg_info, 0, 0, 0)
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (start_test_arg_info, 0, 0, 0)
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (end_test_arg_info, 0, 0, 0)
ZEND_ARG_INFO (0, "start")
ZEND_ARG_INFO (0, "name")
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (total_arg_info, 0, 0, 0)
ZEND_END_ARG_INFO ()ZEND_BEGIN_ARG_INFO_EX (__MAIN___arg_info, 0, 0, 0)
ZEND_END_ARG_INFO ()
// Register all functions with PHP
     static function_entry app_functions[] = {
	 PHP_FE (mandel, mandel_arg_info)
	 PHP_FE (mandel2, mandel2_arg_info)
	 PHP_FE (Ack, Ack_arg_info)
	 PHP_FE (ackermann, ackermann_arg_info)
	 PHP_FE (ary, ary_arg_info)
	 PHP_FE (ary2, ary2_arg_info)
	 PHP_FE (ary3, ary3_arg_info)
	 PHP_FE (fibo_r, fibo_r_arg_info)
	 PHP_FE (fibo, fibo_arg_info)
	 PHP_FE (hash1, hash1_arg_info)
	 PHP_FE (hash2, hash2_arg_info)
	 PHP_FE (gen_random, gen_random_arg_info)
	 PHP_FE (heapsort_r, heapsort_r_arg_info)
	 PHP_FE (heapsort, heapsort_arg_info)
	 PHP_FE (mkmatrix, mkmatrix_arg_info)
	 PHP_FE (mmult, mmult_arg_info)
	 PHP_FE (matrix, matrix_arg_info)
	 PHP_FE (nestedloop, nestedloop_arg_info)
	 PHP_FE (sieve, sieve_arg_info)
	 PHP_FE (strcat, strcat_arg_info)
	 PHP_FE (getmicrotime, getmicrotime_arg_info)
	 PHP_FE (start_test, start_test_arg_info)
	 PHP_FE (end_test, end_test_arg_info)
	 PHP_FE (total, total_arg_info)
	 PHP_FE (__MAIN__, __MAIN___arg_info) {NULL, NULL, NULL}
     };

// Register the module itself with PHP
zend_module_entry app_module_entry = {
  STANDARD_MODULE_HEADER,
  "app",
  app_functions,
  NULL,				/* MINIT */
  NULL,				/* MSHUTDOWN */
  NULL,				/* RINIT */
  NULL,				/* RSHUTDOWN */
  NULL,				/* MINFO */
  "1.0",
  STANDARD_MODULE_PROPERTIES
};

#include <sapi/embed/php_embed.h>
#include <signal.h>

void
sighandler (int signum)
{
  switch (signum)
    {
    case SIGABRT:
      printf ("SIGABRT received!\n");
      break;
    case SIGSEGV:
      printf ("SIGSEGV received!\n");
      break;
    default:
      printf ("Unknown signal received!\n");
      break;
    }

  printf ("This could be a bug in phc. If you suspect it is, please email\n");
  printf ("a bug report to phc-general@phpcompiler.org.\n");
  exit (-1);
}

int
main (int argc, char *argv[])
{
  int phc_exit_status;
  signal (SIGABRT, sighandler);
  signal (SIGSEGV, sighandler);

  TSRMLS_D;
  int dealloc_pools = 1;
  php_embed_init (argc, argv PTSRMLS_CC);
  zend_first_try
  {

    // initialize the phc runtime
    init_runtime ();

    // load the compiled extension
    zend_startup_module (&app_module_entry);

    zval main_name;
    ZVAL_STRING (&main_name, "__MAIN__", NULL);

    zval retval;

    // Use standard errors, on stdout
    zend_alter_ini_entry ("report_zend_debug", sizeof ("report_zend_debug"),
			  "0", sizeof ("0") - 1, PHP_INI_ALL,
			  PHP_INI_STAGE_RUNTIME);
    zend_alter_ini_entry ("display_startup_errors",
			  sizeof ("display_startup_errors"), "1",
			  sizeof ("1") - 1, PHP_INI_ALL,
			  PHP_INI_STAGE_RUNTIME);

    // initialize all the constants
    ALLOC_INIT_ZVAL (phc_const_pool_int_0);
    ZVAL_LONG (phc_const_pool_int_0, 0);
    ALLOC_INIT_ZVAL (phc_const_pool_int_1);
    ZVAL_LONG (phc_const_pool_int_1, 1000000);
    ALLOC_INIT_ZVAL (phc_const_pool_string_0);
    ZVAL_STRINGL (phc_const_pool_string_0, "hallo", 5, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_2);
    ZVAL_LONG (phc_const_pool_int_2, 50);
    ALLOC_INIT_ZVAL (phc_const_pool_int_3);
    ZVAL_LONG (phc_const_pool_int_3, 12);
    ALLOC_INIT_ZVAL (phc_const_pool_real_0);
    {
      unsigned char val[] = { 120, 233, 38, 49, 8, 172, 156, 63, };
      ZVAL_DOUBLE (phc_const_pool_real_0, *(double *) (val));
    }
    ALLOC_INIT_ZVAL (phc_const_pool_real_1);
    {
      unsigned char val[] = { 0, 0, 0, 0, 0, 0, 0, 0, };
      ZVAL_DOUBLE (phc_const_pool_real_1, *(double *) (val));
    }
    ALLOC_INIT_ZVAL (phc_const_pool_int_4);
    ZVAL_LONG (phc_const_pool_int_4, 150);
    ALLOC_INIT_ZVAL (phc_const_pool_int_5);
    ZVAL_LONG (phc_const_pool_int_5, 40);
    ALLOC_INIT_ZVAL (phc_const_pool_real_2);
    {
      unsigned char val[] = { 205, 204, 204, 204, 204, 204, 220, 191, };
      ZVAL_DOUBLE (phc_const_pool_real_2, *(double *) (val));
    }
    ALLOC_INIT_ZVAL (phc_const_pool_int_6);
    ZVAL_LONG (phc_const_pool_int_6, 1000);
    ALLOC_INIT_ZVAL (phc_const_pool_int_7);
    ZVAL_LONG (phc_const_pool_int_7, 2);
    ALLOC_INIT_ZVAL (phc_const_pool_int_8);
    ZVAL_LONG (phc_const_pool_int_8, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_1);
    ZVAL_STRINGL (phc_const_pool_string_1, "_", 1, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_2);
    ZVAL_STRINGL (phc_const_pool_string_2, "#", 1, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_3);
    ZVAL_STRINGL (phc_const_pool_string_3, "<br>", 4, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_4);
    ZVAL_STRINGL (phc_const_pool_string_4, " .:,;!/>)|&IH%*#", 16, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_9);
    ZVAL_LONG (phc_const_pool_int_9, 30);
    ALLOC_INIT_ZVAL (phc_const_pool_string_5);
    ZVAL_STRINGL (phc_const_pool_string_5, "\012", 1, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_real_3);
    {
      unsigned char val[] = { 154, 153, 153, 153, 153, 153, 185, 63, };
      ZVAL_DOUBLE (phc_const_pool_real_3, *(double *) (val));
    }
    ALLOC_INIT_ZVAL (phc_const_pool_real_4);
    {
      unsigned char val[] = { 0, 0, 0, 0, 0, 0, 248, 63, };
      ZVAL_DOUBLE (phc_const_pool_real_4, *(double *) (val));
    }
    ALLOC_INIT_ZVAL (phc_const_pool_real_5);
    {
      unsigned char val[] = { 123, 20, 174, 71, 225, 122, 164, 63, };
      ZVAL_DOUBLE (phc_const_pool_real_5, *(double *) (val));
    }
    ALLOC_INIT_ZVAL (phc_const_pool_int_10);
    ZVAL_LONG (phc_const_pool_int_10, 75);
    ALLOC_INIT_ZVAL (phc_const_pool_int_11);
    ZVAL_LONG (phc_const_pool_int_11, 5000);
    ALLOC_INIT_ZVAL (phc_const_pool_int_12);
    ZVAL_LONG (phc_const_pool_int_12, 500000);
    ALLOC_INIT_ZVAL (phc_const_pool_int_13);
    ZVAL_LONG (phc_const_pool_int_13, 16);
    ALLOC_INIT_ZVAL (phc_const_pool_int_14);
    ZVAL_LONG (phc_const_pool_int_14, 3);
    ALLOC_INIT_ZVAL (phc_const_pool_string_6);
    ZVAL_STRINGL (phc_const_pool_string_6, "Ack(3,", 6, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_7);
    ZVAL_STRINGL (phc_const_pool_string_7, "): ", 3, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_8);
    ZVAL_STRINGL (phc_const_pool_string_8, "", 0, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_9);
    ZVAL_STRINGL (phc_const_pool_string_9, " ", 1, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_10);
    ZVAL_STRINGL (phc_const_pool_string_10,
		  "Invalid argument supplied for foreach()", 39, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_15);
    ZVAL_LONG (phc_const_pool_int_15, 512);
    ALLOC_INIT_ZVAL (phc_const_pool_string_11);
    ZVAL_STRINGL (phc_const_pool_string_11, "foo_", 4, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_12);
    ZVAL_STRINGL (phc_const_pool_string_12, "foo_0", 5, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_null_0);
    ZVAL_NULL (phc_const_pool_null_0);
    ALLOC_INIT_ZVAL (phc_const_pool_string_13);
    ZVAL_STRINGL (phc_const_pool_string_13, "IM", 2, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_16);
    ZVAL_LONG (phc_const_pool_int_16, 139968);
    ALLOC_INIT_ZVAL (phc_const_pool_string_14);
    ZVAL_STRINGL (phc_const_pool_string_14, "IA", 2, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_17);
    ZVAL_LONG (phc_const_pool_int_17, 3877);
    ALLOC_INIT_ZVAL (phc_const_pool_string_15);
    ZVAL_STRINGL (phc_const_pool_string_15, "IC", 2, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_18);
    ZVAL_LONG (phc_const_pool_int_18, 29573);
    ALLOC_INIT_ZVAL (phc_const_pool_int_19);
    ZVAL_LONG (phc_const_pool_int_19, 42);
    ALLOC_INIT_ZVAL (phc_const_pool_string_16);
    ZVAL_STRINGL (phc_const_pool_string_16, "%.10f\012", 6, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_20);
    ZVAL_LONG (phc_const_pool_int_20, 4);
    ALLOC_INIT_ZVAL (phc_const_pool_int_21);
    ZVAL_LONG (phc_const_pool_int_21, 8192);
    ALLOC_INIT_ZVAL (phc_const_pool_int_22);
    ZVAL_LONG (phc_const_pool_int_22, 8193);
    ALLOC_INIT_ZVAL (phc_const_pool_string_17);
    ZVAL_STRINGL (phc_const_pool_string_17, "Count: ", 7, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_18);
    ZVAL_STRINGL (phc_const_pool_string_18, "hello\012", 6, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_19);
    ZVAL_STRINGL (phc_const_pool_string_19, "sec", 3, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_20);
    ZVAL_STRINGL (phc_const_pool_string_20, "usec", 4, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_23);
    ZVAL_LONG (phc_const_pool_int_23, 24);
    ALLOC_INIT_ZVAL (phc_const_pool_string_21);
    ZVAL_STRINGL (phc_const_pool_string_21, "------------------------\012",
		  25, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_24);
    ZVAL_LONG (phc_const_pool_int_24, 19);
    ALLOC_INIT_ZVAL (phc_const_pool_string_22);
    ZVAL_STRINGL (phc_const_pool_string_22, "Total", 5, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_23);
    ZVAL_STRINGL (phc_const_pool_string_23, "UTC", 3, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_24);
    ZVAL_STRINGL (phc_const_pool_string_24, "simple", 6, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_25);
    ZVAL_STRINGL (phc_const_pool_string_25, "simplecall", 10, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_26);
    ZVAL_STRINGL (phc_const_pool_string_26, "simpleucall", 11, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_27);
    ZVAL_STRINGL (phc_const_pool_string_27, "simpleudcall", 12, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_28);
    ZVAL_STRINGL (phc_const_pool_string_28, "mandel", 6, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_29);
    ZVAL_STRINGL (phc_const_pool_string_29, "mandel2", 7, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_25);
    ZVAL_LONG (phc_const_pool_int_25, 7);
    ALLOC_INIT_ZVAL (phc_const_pool_string_30);
    ZVAL_STRINGL (phc_const_pool_string_30, "ackermann(7)", 12, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_26);
    ZVAL_LONG (phc_const_pool_int_26, 50000);
    ALLOC_INIT_ZVAL (phc_const_pool_string_31);
    ZVAL_STRINGL (phc_const_pool_string_31, "ary(50000)", 10, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_32);
    ZVAL_STRINGL (phc_const_pool_string_32, "ary2(50000)", 11, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_27);
    ZVAL_LONG (phc_const_pool_int_27, 2000);
    ALLOC_INIT_ZVAL (phc_const_pool_string_33);
    ZVAL_STRINGL (phc_const_pool_string_33, "ary3(2000)", 10, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_34);
    ZVAL_STRINGL (phc_const_pool_string_34, "fibo(30)", 8, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_35);
    ZVAL_STRINGL (phc_const_pool_string_35, "hash1(50000)", 12, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_28);
    ZVAL_LONG (phc_const_pool_int_28, 500);
    ALLOC_INIT_ZVAL (phc_const_pool_string_36);
    ZVAL_STRINGL (phc_const_pool_string_36, "hash2(500)", 10, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_29);
    ZVAL_LONG (phc_const_pool_int_29, 20000);
    ALLOC_INIT_ZVAL (phc_const_pool_string_37);
    ZVAL_STRINGL (phc_const_pool_string_37, "heapsort(20000)", 15, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_30);
    ZVAL_LONG (phc_const_pool_int_30, 20);
    ALLOC_INIT_ZVAL (phc_const_pool_string_38);
    ZVAL_STRINGL (phc_const_pool_string_38, "matrix(20)", 10, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_39);
    ZVAL_STRINGL (phc_const_pool_string_39, "nestedloop(12)", 14, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_string_40);
    ZVAL_STRINGL (phc_const_pool_string_40, "sieve(30)", 9, 1);
    ALLOC_INIT_ZVAL (phc_const_pool_int_31);
    ZVAL_LONG (phc_const_pool_int_31, 200000);
    ALLOC_INIT_ZVAL (phc_const_pool_string_41);
    ZVAL_STRINGL (phc_const_pool_string_41, "strcat(200000)", 14, 1);

    // call __MAIN__
    int success = call_user_function (EG (function_table),
				      NULL,
				      &main_name,
				      &retval,
				      0,
				      NULL TSRMLS_CC);

    assert (success == SUCCESS);

    // finalize the runtime
    finalize_runtime ();

  }
  zend_catch
  {
    dealloc_pools = 0;
  }
  zend_end_try ();
  if (dealloc_pools)
    {
      zval_ptr_dtor (&phc_const_pool_int_0);
      zval_ptr_dtor (&phc_const_pool_int_1);
      zval_ptr_dtor (&phc_const_pool_string_0);
      zval_ptr_dtor (&phc_const_pool_int_2);
      zval_ptr_dtor (&phc_const_pool_int_3);
      zval_ptr_dtor (&phc_const_pool_real_0);
      zval_ptr_dtor (&phc_const_pool_real_1);
      zval_ptr_dtor (&phc_const_pool_int_4);
      zval_ptr_dtor (&phc_const_pool_int_5);
      zval_ptr_dtor (&phc_const_pool_real_2);
      zval_ptr_dtor (&phc_const_pool_int_6);
      zval_ptr_dtor (&phc_const_pool_int_7);
      zval_ptr_dtor (&phc_const_pool_int_8);
      zval_ptr_dtor (&phc_const_pool_string_1);
      zval_ptr_dtor (&phc_const_pool_string_2);
      zval_ptr_dtor (&phc_const_pool_string_3);
      zval_ptr_dtor (&phc_const_pool_string_4);
      zval_ptr_dtor (&phc_const_pool_int_9);
      zval_ptr_dtor (&phc_const_pool_string_5);
      zval_ptr_dtor (&phc_const_pool_real_3);
      zval_ptr_dtor (&phc_const_pool_real_4);
      zval_ptr_dtor (&phc_const_pool_real_5);
      zval_ptr_dtor (&phc_const_pool_int_10);
      zval_ptr_dtor (&phc_const_pool_int_11);
      zval_ptr_dtor (&phc_const_pool_int_12);
      zval_ptr_dtor (&phc_const_pool_int_13);
      zval_ptr_dtor (&phc_const_pool_int_14);
      zval_ptr_dtor (&phc_const_pool_string_6);
      zval_ptr_dtor (&phc_const_pool_string_7);
      zval_ptr_dtor (&phc_const_pool_string_8);
      zval_ptr_dtor (&phc_const_pool_string_9);
      zval_ptr_dtor (&phc_const_pool_string_10);
      zval_ptr_dtor (&phc_const_pool_int_15);
      zval_ptr_dtor (&phc_const_pool_string_11);
      zval_ptr_dtor (&phc_const_pool_string_12);
      zval_ptr_dtor (&phc_const_pool_null_0);
      zval_ptr_dtor (&phc_const_pool_string_13);
      zval_ptr_dtor (&phc_const_pool_int_16);
      zval_ptr_dtor (&phc_const_pool_string_14);
      zval_ptr_dtor (&phc_const_pool_int_17);
      zval_ptr_dtor (&phc_const_pool_string_15);
      zval_ptr_dtor (&phc_const_pool_int_18);
      zval_ptr_dtor (&phc_const_pool_int_19);
      zval_ptr_dtor (&phc_const_pool_string_16);
      zval_ptr_dtor (&phc_const_pool_int_20);
      zval_ptr_dtor (&phc_const_pool_int_21);
      zval_ptr_dtor (&phc_const_pool_int_22);
      zval_ptr_dtor (&phc_const_pool_string_17);
      zval_ptr_dtor (&phc_const_pool_string_18);
      zval_ptr_dtor (&phc_const_pool_string_19);
      zval_ptr_dtor (&phc_const_pool_string_20);
      zval_ptr_dtor (&phc_const_pool_int_23);
      zval_ptr_dtor (&phc_const_pool_string_21);
      zval_ptr_dtor (&phc_const_pool_int_24);
      zval_ptr_dtor (&phc_const_pool_string_22);
      zval_ptr_dtor (&phc_const_pool_string_23);
      zval_ptr_dtor (&phc_const_pool_string_24);
      zval_ptr_dtor (&phc_const_pool_string_25);
      zval_ptr_dtor (&phc_const_pool_string_26);
      zval_ptr_dtor (&phc_const_pool_string_27);
      zval_ptr_dtor (&phc_const_pool_string_28);
      zval_ptr_dtor (&phc_const_pool_string_29);
      zval_ptr_dtor (&phc_const_pool_int_25);
      zval_ptr_dtor (&phc_const_pool_string_30);
      zval_ptr_dtor (&phc_const_pool_int_26);
      zval_ptr_dtor (&phc_const_pool_string_31);
      zval_ptr_dtor (&phc_const_pool_string_32);
      zval_ptr_dtor (&phc_const_pool_int_27);
      zval_ptr_dtor (&phc_const_pool_string_33);
      zval_ptr_dtor (&phc_const_pool_string_34);
      zval_ptr_dtor (&phc_const_pool_string_35);
      zval_ptr_dtor (&phc_const_pool_int_28);
      zval_ptr_dtor (&phc_const_pool_string_36);
      zval_ptr_dtor (&phc_const_pool_int_29);
      zval_ptr_dtor (&phc_const_pool_string_37);
      zval_ptr_dtor (&phc_const_pool_int_30);
      zval_ptr_dtor (&phc_const_pool_string_38);
      zval_ptr_dtor (&phc_const_pool_string_39);
      zval_ptr_dtor (&phc_const_pool_string_40);
      zval_ptr_dtor (&phc_const_pool_int_31);
      zval_ptr_dtor (&phc_const_pool_string_41);
    }
  phc_exit_status = EG (exit_status);
  php_embed_shutdown (TSRMLS_C);

  return phc_exit_status;
}
