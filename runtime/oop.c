/*
 * Creates a copy of *in using persistent memory, optionally destroying *in
 *
 * Does not work for objects/resources and will loop on self-recursive arrays.
 */

zval *
persistent_clone (zval * in, int destroy_in TSRMLS_DC)
{
  zval *out = pemalloc (sizeof (zval), 1);
  *out = *in;

  switch (Z_TYPE_P (in))
    {
    case IS_NULL:
    case IS_LONG:
    case IS_DOUBLE:
    case IS_BOOL:
      /* nothing more to be done */
      break;
    case IS_STRING:
      Z_STRVAL_P (out) = pemalloc (Z_STRLEN_P (in) + 1, 1);
      memcpy (Z_STRVAL_P (out), Z_STRVAL_P (in), Z_STRLEN_P (in) + 1);
      break;
    case IS_ARRAY:
      {
	HashTable *old_arr = Z_ARRVAL_P (in);
	HashTable *new_arr = pemalloc (sizeof (HashTable), 1);
	zend_hash_init (new_arr, old_arr->nNumOfElements, NULL, ZVAL_PTR_DTOR,
			/* persistent */ 1);

	for (zend_hash_internal_pointer_reset (old_arr);
	     zend_hash_has_more_elements (old_arr) == SUCCESS;
	     zend_hash_move_forward (old_arr))
	  {
	    char *key;
	    uint keylen;
	    ulong idx;
	    int type;
	    zval **old_elem, *new_elem;

	    type =
	      zend_hash_get_current_key_ex (old_arr, &key, &keylen, &idx, 0,
					    NULL);
	    assert (zend_hash_get_current_data
		    (old_arr, (void **) &old_elem) == SUCCESS);

	    new_elem = persistent_clone (*old_elem, destroy_in TSRMLS_CC);

	    if (type == HASH_KEY_IS_STRING)
	      zend_hash_add (new_arr, key, keylen, &new_elem, sizeof (zval *),
			     NULL);
	    else
	      zend_hash_index_update (new_arr, idx, &new_elem,
				      sizeof (zval *), NULL);

	  }

	Z_ARRVAL_P (out) = new_arr;
      }
      break;
    default:
      /* other types are not supported */
      assert (0);
    }

  zval_ptr_dtor (&in);
  return out;
}

/*
 * Wrapper around zend_declare_property which 
 *
 * - Asserts that the ZEND_INTERNAL_CLASS flag is cleared
 *   (otherwise we cannot add complex (i.e., array) properties)
 * - Creates a persistent clone of the property to be added before
 *   calling zend_declare_property, since the memory for this property
 *   should only be deallocated when the module is shut down
 *   (and not when the request finishes)
 * - Cleans up after zend_declare_property by re-allocating the name of 
 *   the property using persistent memory, for much the same reason
 */

static int
phc_declare_property (zend_class_entry * ce, char *name, int name_length,
		      zval * property, int access_type TSRMLS_DC)
{
  int rc;
  assert (!(ce->type & ZEND_INTERNAL_CLASS));
  rc = zend_declare_property
	  (ce, name, name_length, persistent_clone (property, 1 TSRMLS_CC),
	   access_type TSRMLS_CC);
  assert(rc == SUCCESS);

  zend_property_info *property_info;
  rc = zend_hash_find
	  (&ce->properties_info, name, name_length + 1,
	   (void **) &property_info);
  assert(rc == SUCCESS);
  efree (property_info->name);
  property_info->name = name;

  return SUCCESS;
}

// vi:set ts=8:
