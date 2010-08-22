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
	      (long unsigned int) (*ppzval), Z_REFCOUNT_P(*ppzval),
	      Z_ISREF_P(*ppzval));
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

static zval* counters;

static void init_counters ()
{
  ALLOC_INIT_ZVAL (counters);
  array_init (counters);
}

// Dump and cleanup memory
static void finalize_counters ()
{
  HashTable* ht = Z_ARRVAL_P (counters);
  for (zend_hash_internal_pointer_reset (ht);
       zend_hash_has_more_elements (ht) == SUCCESS;
       zend_hash_move_forward (ht))
    {
      char *key;
      zval **p_zvp;

      zend_hash_get_current_key_ex (ht, &key, NULL, NULL, 0, NULL);
      zend_hash_get_current_data (ht, (void **) &p_zvp);

      fprintf (stderr, "COUNTER:%s:%ld\n", key, Z_LVAL_P (*p_zvp));
    }

  zval_ptr_dtor (&counters);
}

static void increment_counter (char* name, int length, ulong hashval)
{
  zval** p_zvp;
  int success = zend_hash_quick_find (Z_ARRVAL_P (counters),
				      name,
				      length,
				      hashval,
				      (void **) &p_zvp);

  if (success == SUCCESS)
    {
      Z_LVAL_PP (p_zvp)++;
    }
  else
    {

      zval* new_val;
      ALLOC_INIT_ZVAL (new_val);
      ZVAL_LONG (new_val, 1);

      zend_hash_quick_add (Z_ARRVAL_P (counters),
			   name,
			   length,
			   hashval,
			   &new_val,
			   sizeof (zval *),
			   NULL);
    }
}
