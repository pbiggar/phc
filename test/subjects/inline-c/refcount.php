<?php
<<<INLINE_C
#line 4 "refcount.php"
/*
 * \$a = 5;
 * \$b[1] =& \$a;
 */
zval* a;
MAKE_STD_ZVAL(a);
ZVAL_LONG(a, 5);
ZEND_SET_SYMBOL(EG(active_symbol_table), "a", a);

zval* b;
MAKE_STD_ZVAL(b);
array_init(b);
ZEND_SET_SYMBOL(EG(active_symbol_table), "b", b);

// Execute assignment
zval_add_ref (&a);
(a)->is_ref = 1;
add_index_zval(b, 1, a);
INLINE_C;
?>
