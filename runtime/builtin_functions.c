static void
phc_builtin_eval (zval * arg, zval ** p_result, char *filename TSRMLS_DC)
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
  zval *copy = zvp_clone_ex (arg);
  convert_to_string (copy);

  if (*p_result && !strncmp (Z_STRVAL_P (copy), "return ", 7))
    {
      zend_eval_string (Z_STRVAL_P (copy) + 7, *p_result,
			"eval'd code" TSRMLS_CC);
    }
  else
    {
      zend_eval_string (Z_STRVAL_P (copy), NULL, "eval'd code" TSRMLS_CC);
    }

  // cleanup
  assert (Z_REFCOUNT_P(copy) == 1);
  zval_ptr_dtor (&copy);
}

static void
phc_builtin_exit (zval * arg, zval ** p_result, char *filename TSRMLS_DC)
{
  if (Z_TYPE_P (arg) == IS_LONG)
    EG (exit_status) = Z_LVAL_P (arg);
  else
    zend_print_variable (arg);

  zend_bailout ();
}

static void
phc_builtin_die (zval * arg, zval ** p_result, char *filename TSRMLS_DC)
{
  phc_builtin_exit (arg, p_result, filename TSRMLS_CC);
}

static void
phc_builtin_echo (zval * arg, zval ** p_result TSRMLS_DC)
{
  assert (*p_result == NULL);
  zend_print_variable (arg);
}

static void
phc_builtin_print (zval * arg, zval ** p_result, char *filename TSRMLS_DC)
{
  zval *echo_arg = NULL;
  phc_builtin_echo (arg, &echo_arg TSRMLS_CC);

  if (*p_result)
    ZVAL_LONG (*p_result, 1);
}

// TODO is there a memory leak here is result has a value?
// TOOD isnt this just the same as isset
static void
phc_builtin_empty (zval * arg, zval ** p_result, char *filename TSRMLS_DC)
{
  assert (*p_result);
  ZVAL_BOOL (*p_result, !zend_is_true (arg));
}

// For require, include, require_once and include_once.

// Include:
//    return 1 for success
//    Warning, and return false for failure
// Require:
//    return 1 for success
//    Fail for failure
// Include_once
//    Return true if already included
//    Return 1 for success
//    Warning and return false for failure
// Require_once:
//    Return true if already included
//    return 1 for success
//    Fail for failure
//
static void
include_backend (zval * arg, zval ** p_result, char *filename, int type, int is_once, char* error, char* error_function TSRMLS_DC)
{
  // In the event that the Zend engine cannot find the file, after checking the
  // include path, it tries the current directory. It does this only if the
  // interpreter is executing, and it checks the interpreters opcodes for a
  // filename (see streams/plain_wrapper.c:1352)

  // An alternative is to add the directory to include_path, but its
  // semantically incorrect (get_included_path() would give the wrong answer),
  // and error prone (if people overwrite include_path).
  // TODO: though we could add it for this function only

  assert (EG (active_op_array) == NULL);
  assert (filename != NULL);

  zval *arg_file = arg;
  // Check we have a string
  if (Z_TYPE_P (arg_file) != IS_STRING)
    {
      arg_file = zvp_clone_ex (arg_file);
      convert_to_string (arg_file);
    }

  zend_file_handle handle;
  zend_op_array* new_op_array;
  zend_function zf;

  // Check the _ONCE varieties (based on zend_vm_def.h)
   if (is_once)
     {
       if (IS_ABSOLUTE_PATH (Z_STRVAL_P (arg_file), Z_STRLEN_P (arg_file)))
	 {
	   // Get the proper path name for require
	   cwd_state state;

	   state.cwd_length = 0;
	   state.cwd = malloc(1);
	   state.cwd[0] = 0;
	   int success = !virtual_file_ex(&state, Z_STRVAL_P(arg_file), NULL, 1)
	     && zend_hash_exists(&EG(included_files), state.cwd,
				 state.cwd_length+1);

	   free (state.cwd);

	   if (!success)
	     goto cleanup;
	 }
     }


   // Compile the file
   // Pretend the interpreter is running
   EG (in_execution) = 1;

   int success = zend_stream_open (Z_STRVAL_P (arg_file), &handle TSRMLS_CC);

   // Stop pretending
   EG (in_execution) = 0;
   EG (active_op_array) = NULL;

   if (success != SUCCESS)
     goto fail;


   if (is_once)
     {
       // Check it hadnt been included already
       int once_success = zend_hash_add_empty_element(&EG(included_files),
						      handle.opened_path,
						      strlen (handle.opened_path)+1);
       // Return true 
       if (once_success != SUCCESS)
	 {
	   ZVAL_BOOL (*p_result, 1);
	   goto cleanup;
	 }
     }

   if (!handle.opened_path)
     handle.opened_path = estrndup (Z_STRVAL_P(arg_file), Z_STRLEN_P (arg_file));

   // run it
   success = zend_execute_scripts (type TSRMLS_CC, p_result, 1, &handle);
   assert (success == SUCCESS);
   zend_file_handle_dtor (&handle);

   // Success
   if (*p_result)
       ZVAL_LONG (*p_result, 1);


   goto cleanup;


fail:

   php_error_docref (error_function
		     TSRMLS_CC, 
		     (type == ZEND_INCLUDE) ? E_WARNING : E_ERROR,
		     error,
		     php_strip_url_passwd (Z_STRVAL_P (arg_file)),
		     STR_PRINT (PG (include_path)));


   // Failure
   if (*p_result)
     ZVAL_BOOL (*p_result, 0);

cleanup:

   if (handle.opened_path)
     efree (handle.opened_path);
   zend_destroy_file_handle (&handle TSRMLS_CC);


  if (arg != arg_file)
    zval_ptr_dtor (&arg_file);
}

static void
phc_builtin_include (zval * arg, zval ** p_result, char *filename TSRMLS_DC)
{
  include_backend ( arg,
		    p_result,
		    filename,
		    ZEND_INCLUDE,
		    0,
		    "Failed opening '%s' for inclusion (include_path='%s')",
		    "function.include"
		    TSRMLS_CC);
}

static void
phc_builtin_require (zval * arg, zval ** p_result, char *filename TSRMLS_DC)
{
  include_backend ( arg,
		    p_result,
		    filename,
		    ZEND_REQUIRE,
		    0,
		    "Failed opening required '%s' (include_path='%s')",
		    "function.require"
		    TSRMLS_CC);
}

static void
phc_builtin_include_once (zval * arg, zval ** p_result, char *filename TSRMLS_DC)
{
  include_backend ( arg,
		    p_result,
		    filename,
		    ZEND_INCLUDE,
		    1,
		    "Failed opening '%s' for inclusion (include_path='%s')",
		    "function.include_once"
		    TSRMLS_CC);
}

static void
phc_builtin_require_once (zval * arg, zval ** p_result, char *filename TSRMLS_DC)
{
  include_backend ( arg,
		    p_result,
		    filename,
		    ZEND_REQUIRE,
		    1,
		    "Failed opening required '%s' (include_path='%s')",
		    "function.require_once"
		    TSRMLS_CC);
}
