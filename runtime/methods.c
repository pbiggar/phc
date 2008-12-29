
static zval **
fetch_var_arg_by_ref (zval ** p_arg)
{
  // We are passing by reference
  sep_copy_on_write (p_arg);

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
      arg = zvp_clone_ex (arg);
      *is_arg_new = 1;

      // It seems we get incorrect refcounts without this.
      // TODO This decreases the refcount to zero, which seems wrong,
      // but gives the right answer. We should look at how zend does
      // this.

      arg->refcount--;
    }
  return arg;
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


/*
 * To initialize a method call, we need to look up the method in the tables
 * associated with the object. zend_fcall_info_init will do this for us if
 * we set up an array of the form
 *
 * array( 0 => the target object (zval* IS_OBJECT)
 *      , 1 => the name of the function to be called (zval* IS_STRING)
 *      )
 *
 * However, when zend_fcall_info_init then uses zend_hash_index_find to
 * find a zval** to the object, and stores this zval** in the function info
 * cache (zend_is_callable_ex in zend_API.c, case for IS_ARRAY(callable) and
 * IS_OBJECT(obj)). The zval** however points to some memory that is part
 * of the hashtable itself (allocated by zend_hash_index_update) and will
 * therefore be freed once we free the hashtable. Hence, it is important
 * that we only free the hashtable once the function info cache structure
 * is no longer required.
 *
 * We could avoid this if we could set up a bucket manually and maintain
 * resposibility for the data memory for the bucket ourselves. However, the
 * zend hash API does not seem to offer this functionality.
 */
static zval *
initialize_method_call (zend_fcall_info * fci, zend_fcall_info_cache * fcic,
			zval * obj, char *function_name, char *filename,
			int line_number TSRMLS_DC)
{
  // We don't cache the results for object lookups
  assert (!fcic->initialized);

  zval *callable;
  MAKE_STD_ZVAL (callable);
  array_init (callable);

  add_index_zval (callable, 0, obj);
  add_index_string (callable, 1, function_name, 1);

  int result = zend_fcall_info_init (callable, fci, fcic TSRMLS_CC);
  if (result != SUCCESS)
    {
      phc_setup_error (1, filename, line_number, NULL TSRMLS_CC);
      php_error_docref (NULL TSRMLS_CC, E_ERROR,
			"Call to undefined function %s()", function_name);
    }

  return callable;
}

// vi:set ts=8:
