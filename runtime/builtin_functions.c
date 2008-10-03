static void
phc_builtin_eval (zval * arg, zval *result, char* filename TSRMLS_DC)
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
phc_builtin_exit (zval * arg, zval* result, char* filename TSRMLS_DC)
{
  if (Z_TYPE_P (arg) == IS_LONG)
    EG (exit_status) = Z_LVAL_P (arg);
  else
    zend_print_variable (arg);

  zend_bailout ();
}

static void
phc_builtin_die (zval * arg, zval* result, char* filename TSRMLS_DC)
{
  phc_builtin_exit (arg, result, filename TSRMLS_CC);
}

static void
phc_builtin_echo (zval* arg, zval* result TSRMLS_DC)
{
  zend_print_variable (arg);
}

static void
phc_builtin_print (zval* arg, zval* result, char* filename TSRMLS_DC)
{
  phc_builtin_echo (arg, result TSRMLS_CC);

  if (result)
    ZVAL_LONG (result, 1);
}

// TODO is there a memory leak here is result has a value?
// TOOD isnt this just the same as isset
static void
phc_builtin_empty (zval* arg, zval* result, char* filename TSRMLS_DC)
{
  ZVAL_BOOL (result, !zend_is_true (arg));
}

static void
phc_builtin_include (zval* arg, zval* result, char* filename TSRMLS_DC)
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

  assert (EG(in_execution) == 0);
  assert (EG(active_op_array) == NULL);
  assert (filename != NULL);

  // Check we have a string
  if (Z_TYPE_P (arg) != IS_STRING)
    {
      zvp_clone_ex (&arg);
      convert_to_string (arg);
    }

  // Pretend the interpreter is running
  EG(in_execution) = 1;
  zend_op_array ops;
  ops.filename = filename;
  EG(active_op_array) = &ops;

  // Open the file
  zend_file_handle handle;
  int success = zend_stream_open (Z_STRVAL_P (arg), &handle TSRMLS_CC);

  // Stop pretending
  EG(in_execution) = 0;
  EG(active_op_array) = NULL;

  if (success == SUCCESS)
    {
      // run it
      success = zend_execute_scripts (ZEND_INCLUDE TSRMLS_CC, &result, 1, &handle);
      assert (success == SUCCESS);
      zend_stream_close (&handle);
   }
  else
    {
      php_error_docref("function.include" TSRMLS_CC, E_WARNING, "Failed opening '%s' for inclusion (include_path='%s')", php_strip_url_passwd(Z_STRVAL_P (arg)), STR_PRINT(PG(include_path)));
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
