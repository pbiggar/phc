<?php
	eval("\$a = 5;");
	eval("\$b[1] =& \$a;");
	eval("\$b[1] = 6;");
?>
<?php
<<<INLINE_C
#line 9 "hashref2.php"
zval** a;
zval** b;
zval** b_1;

zend_hash_find(EG(active_symbol_table), "a", sizeof("a"), (void**) &a);
zend_hash_find(EG(active_symbol_table), "b", sizeof("b"), (void**) &b);
zend_hash_index_find(Z_ARRVAL_PP(b), 1, (void**) &b_1);

printf("a: %08X, b[1]: %08X\\n", (unsigned) *a, (unsigned) *b_1);
printf("a->is_ref = %d\\n", (*a)->is_ref);
printf("a->refcount = %d\\n", (*a)->refcount);
printf("a->type == IS_LONG == %d\\n", (*a)->type == IS_LONG);
printf("a->value->lval = %d\\n", (*a)->value.lval);

INLINE_C;
?>
