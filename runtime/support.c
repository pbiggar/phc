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
 * variable, and pass a reference to that.
 */



// Some common functions
#include "php.h"

/*
 * The runtime needs its own initialization and finalization.  phc is
 * responsible for generating calls to these functions.
 */

//Support macros for PHP 5.3 compatibility
#if PHP_VERSION_ID < 50300
	#define zend_fcall_info_init(fn, i, fci, fcic, p1, p2) zend_fcall_info_init(fn, fci, fcic TSRMLS_CC);
	#define Z_SET_OBJECT_PTR(lhs, rhs) (lhs)->object_pp = rhs
	#define Z_ISREF_P(p) (p)->is_ref
	#define Z_SET_ISREF_P(p) (p)->is_ref = 1
	#define Z_REFCOUNT_P(p) (p)->refcount
	#define Z_ADDREF_P(p) (p)->refcount++
	#define Z_DELREF_P(p) (p)->refcount--
  #define Z_SET_REFCOUNT_P(p, val) (p)->refcount=val
#else
	#define Z_SET_OBJECT_PTR(lhs, rhs) lhs->object_ptr = *rhs
#endif

void
init_runtime ()
{
}

void
finalize_runtime ()
{
}
