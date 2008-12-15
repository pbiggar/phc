
static void
cast_var (zval ** p_zvp, int type)
{
  assert (type >= 0 && type <= 6);
  if ((*p_zvp)->type == type)
    return;

  sep_copy_on_write (p_zvp);
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

/* The function call mechanism deals specially with EG(uninitialize_zval_ptr)
 * (or sometime EG(uninitialize_zval)), so we need to use this too. This
 * particular zval can also be set, but there is an implicit guarantee 
 * of the information below.
 *
 * If assertions are off, this should be inlined to nothing.
 */
static void
phc_check_invariants (TSRMLS_D)
{
  assert (EG (uninitialized_zval_ptr) == &EG (uninitialized_zval));
  assert (EG (uninitialized_zval).refcount >= 1);
  assert (EG (uninitialized_zval).value.lval == 0);
  assert (EG (uninitialized_zval).type == IS_NULL);
  assert (EG (uninitialized_zval).is_ref == 0);
}
