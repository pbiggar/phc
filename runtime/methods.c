
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
  Z_SET_ISREF_P(*p_arg);

  return p_arg;
}

/* Dont pass-by-ref */
static zval *
fetch_var_arg (zval * arg, int *is_arg_new)
{
  if (Z_ISREF_P(arg))
    {
      // We dont separate since we don't own one of ARG's references.
      arg = zvp_clone_ex (arg);
      *is_arg_new = 1;

      // It seems we get incorrect refcounts without this.
      // TODO This decreases the refcount to zero, which seems wrong,
      // but gives the right answer. We should look at how zend does
      // this.

      Z_DELREF_P(arg);
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
      old_function = EG (current_execute_data)->function_state.function;
      // Put in our values
      CG (in_compilation) = 1;
      EG (in_execution) = 1;
      CG (compiled_filename) = filename;
      CG (zend_lineno) = line_number;
      if (function)
	EG (current_execute_data)->function_state.function = function;
    }
  else
    {
      CG (in_compilation) = old_in_compilation;
      EG (in_execution) = old_in_execution;
      CG (compiled_filename) = old_filename;
      CG (zend_lineno) = old_lineno;
      EG (current_execute_data)->function_state.function = old_function;
    }
}

static void
initialize_function_call (zend_fcall_info * fci, zend_fcall_info_cache * fcic,
			  char *function_name, char *filename,
			  int line_number TSRMLS_DC)
{
  if (fcic->initialized)
    return;

  zval * fn;
  MAKE_STD_ZVAL (fn);
  ZVAL_STRING (fn, function_name, 1);
  int result = zend_fcall_info_init (fn, 0, fci, fcic, NULL, NULL TSRMLS_CC);
  if (result != SUCCESS)
    {
      phc_setup_error (1, filename, line_number, NULL TSRMLS_CC);
      php_error_docref (NULL TSRMLS_CC, E_ERROR,
			"Call to undefined function %s()", function_name);
    }

}

static void
destroy_function_call (zend_fcall_info * fci)
{
  if (fci->function_name)
    zval_ptr_dtor (&fci->function_name);
}

/*
 * Initialize zend_fcall_info for a method lookup
 *
 * Implementation partly based on zend_call_method in Zend/zend_interfaces.c
 * Main difference is that we use Z_OBJ_HTT_PP(obj)->get_method to retrieve
 * the function handler for the method instead of looking it up directly;
 * this means that we correctly deal with __call.
 */

static void
initialize_method_call (zend_fcall_info * fci, zend_fcall_info_cache * fcic,
			zval ** obj, char *function_name,
			char *filename, int line_number TSRMLS_DC)
{
  if (fcic->initialized)
    return;

  zend_class_entry *obj_ce;
  obj_ce = Z_OBJCE_PP (obj);

  /*
   * we do not initialize fci.
   *   function_table  --  not initialized by zend_call_method
   *   function_name   --  zend_call_method initializes this to a pointer to
   *                       a zval 'z_fname', but does not initialize z_fname
   *                       in case of a method invocation
   *   retval_ptr_ptr  --  should be initialized by caller
   *   param_count     --  should be initialized by caller
   *   params          --  should be initialized by caller
   */
  fci->size = sizeof (*fci);
  Z_SET_OBJECT_PTR(fci, obj);
  fci->no_separation = 1;
  fci->symbol_table = NULL;

  fcic->initialized = 1;
  fcic->calling_scope = obj_ce;
  Z_SET_OBJECT_PTR(fcic, obj);
  fcic->function_handler
    = Z_OBJ_HT_PP (obj)->get_method (obj,
				     function_name,
				     strlen (function_name) TSRMLS_CC);

  if (fcic->function_handler == NULL)
    {
      phc_setup_error (1, filename, line_number, NULL TSRMLS_CC);
      php_error_docref (NULL TSRMLS_CC, E_ERROR,
			"Call to undefined method %s::%s",
			obj_ce->name, function_name);
    }
}

/*
 * Like initialize_method_call, but return 0 if no constructor is defined
 * rather than giving an error.
 */

static int 
initialize_constructor_call (zend_fcall_info * fci,
			     zend_fcall_info_cache * fcic, zval ** obj,
			     char *filename, int line_number TSRMLS_DC)
{
  if (fcic->initialized)
    return;

  zend_class_entry *obj_ce;
  obj_ce = Z_OBJCE_PP (obj);

  /*
   * we do not initialize fci.
   *   function_table  --  not initialized by zend_call_method
   *   function_name   --  zend_call_method initializes this to a pointer to
   *                       a zval 'z_fname', but does not initialize z_fname
   *                       in case of a method invocation
   *   retval_ptr_ptr  --  should be initialized by caller
   *   param_count     --  should be initialized by caller
   *   params          --  should be initialized by caller
   */
  fci->size = sizeof (*fci);
  Z_SET_OBJECT_PTR(fci, obj);
  fci->no_separation = 1;
  fci->symbol_table = NULL;

  fcic->initialized = 1;
  fcic->calling_scope = obj_ce;
  Z_SET_OBJECT_PTR(fcic, obj);
  fcic->function_handler
    = Z_OBJ_HT_PP (obj)->get_constructor (*obj TSRMLS_CC);

  return (fcic->function_handler != NULL);
}
// vi:set ts=8:
