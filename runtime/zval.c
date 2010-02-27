

/* Make a copy of *P_ZVP, storing it in *P_ZVP. */
static zval *
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
  return (Z_REFCOUNT_P(zvp) > 1 && !Z_ISREF_P(zvp));
}

static inline int
in_change_on_write (zval * zvp)
{
  return (Z_REFCOUNT_P(zvp) > 1 && Z_ISREF_P(zvp));
}

/* If *P_ZVP is in a copy-on-write set, separate it by overwriting
 * *P_ZVP with a clone of itself, and lowering the refcount on the
 * original. */
static void
sep_copy_on_write (zval ** p_zvp)
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

/* Assign RHS into LHS, by reference. After this, LHS will point to the same
 * zval* as RHS. */
static void
copy_into_ref (zval ** lhs, zval ** rhs)
{
  Z_SET_ISREF_P(*rhs);
  Z_ADDREF_P(*rhs);
  zval_ptr_dtor (lhs);
  *lhs = *rhs;
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

/* Write P_RHS into the symbol table as a variable named VAR_NAME. */
// NOTE: We do not alter p_rhs's refcount, unless p_lhs joins its
// Copy-on-write set.
// TODO: this is crying out to be inlined.
static void
write_var (zval ** p_lhs, zval * rhs)
{
  if (!Z_ISREF_P(*p_lhs))
    {
      zval_ptr_dtor (p_lhs);
      // Take a copy of RHS for LHS.
      if (Z_ISREF_P(rhs))
	{
	  *p_lhs = zvp_clone_ex (rhs);
	}
      else			// share a copy
	{
	  Z_ADDREF_P(rhs);
	  *p_lhs = rhs;
	}
    }
  else
    {
      overwrite_lhs (*p_lhs, rhs);
    }
}

// TODO: this functino does too much, and much might be redundant
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
  Z_ADDREF_P(EG(uninitialized_zval_ptr));
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
