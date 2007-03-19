<?php
<<<INLINE_C
#line 4 "hashref.php"
/*
 * a = 5;
 * b[1] =& a;
 * b[1] = 6;
 */
zval *a;
MAKE_STD_ZVAL (a);
ZVAL_LONG (a, 5);
ZEND_SET_SYMBOL (EG (active_symbol_table), "a", a);

zval *b;
MAKE_STD_ZVAL (b);
array_init (b);
ZEND_SET_SYMBOL (EG (active_symbol_table), "b", b);

// Execute assignment
zval_add_ref (&a);
(a)->is_ref = 1;
add_index_zval(b, 1, a); 

// Extract the hashtable from the zval
zval **indexed0;
zend_hash_index_find (Z_ARRVAL_P(b), 1, (void **) &indexed0);
ZVAL_LONG(*indexed0, 6);
INLINE_C;
var_dump($a);
var_dump($b);
?>
