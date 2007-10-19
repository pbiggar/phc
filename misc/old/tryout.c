#include <php.h>
#include <sapi/embed/php_embed.h>

/*
 * Debugging
 */

void dump_zval(zval* zv)
{
	printf("<zval 0x%lX>\n", (long) zv);
	printf("\trefcount: %d\n", zv->refcount);
	printf("\tis_ref: %d\n", zv->is_ref);
	switch(zv->type)
	{
		case IS_NULL:
			printf("\ttype: NULL\n");
			break;
		case IS_BOOL:
			printf("\ttype: BOOL\n");
			printf("\tvalue: %ld\n", zv->value.lval);
			break;
		case IS_LONG:
			printf("\ttype: LONG\n");
			printf("\tvalue: %ld\n", zv->value.lval);
			break;
		case IS_DOUBLE:
			printf("\ttype: DOUBLE\n");
			printf("\tvalue: %lf\n", zv->value.dval);
			break;
		case IS_STRING:
			printf("\ttype: STRING\n");
			printf("\tvalue: \"%s\"\n", zv->value.str.val);
			printf("\tlength: %d\n", zv->value.str.len);
			break;
		default:
			printf("\tunknown type\n");
			break;

	}
	printf("</zval>\n");
}

/*
 * Test 1
 *
 * Create a zval, add it to a hashtable, then destroy the hashtable
 *
 * Demonstrates that adding a zval to a hashtable does not automatically
 * increase its refcount; destroying the hashtable will destroy the zval
 * if ZVAL_PTR_DTOR has been specified as a destructor.
 */

PHP_FUNCTION(test1)
{
	php_printf("\n**** test1 ****\n");

	// Create a new zval
	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Create a hashtable
	HashTable* locals;
	ALLOC_HASHTABLE(locals);
	zend_hash_init(locals, 50, NULL, ZVAL_PTR_DTOR, 0);

	// Store "a" in the hashtable
	zend_hash_add(locals, "a", sizeof("a"), &a, sizeof(zval*), NULL);

	// Retrieve "a" from the hashtable
	zval** a_from_locals;
	zend_hash_find(locals, "a", sizeof("a"), (void**)&a_from_locals); 
	dump_zval(*a_from_locals);

	// Destroy locals
	zend_hash_destroy(locals);
	FREE_HASHTABLE(locals);

	// Does "a" still exist after destroying the hashtable? NO!
	dump_zval(a);

	// zval_ptr_dtor(&a); // No need for a destructor
}

/*
 * Test 2
 *
 * Same setup as test 1, but specifies NULL for the destructor. Shows that
 * in that case, destroying the hash table does not affect the zval.
 */

PHP_FUNCTION(test2)
{
	php_printf("\n**** test2 ****\n");

	// Create a new zval
	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Create a hashtable
	HashTable* locals;
	ALLOC_HASHTABLE(locals);
	zend_hash_init(locals, 50, NULL, NULL, 0);

	// Store "a" in the hashtable
	zend_hash_add(locals, "a", sizeof("a"), &a, sizeof(zval*), NULL);

	// Retrieve "a" from the hashtable
	zval** a_from_locals;
	zend_hash_find(locals, "a", sizeof("a"), (void**)&a_from_locals); 
	dump_zval(*a_from_locals);

	// Destroy locals
	zend_hash_destroy(locals);
	FREE_HASHTABLE(locals);

	// Does "a" still exist after destroying the hashtable? YES!
	dump_zval(a);

	// Not calling the destructor here will result in a memory leak
	zval_ptr_dtor(&a);
}

/*
 * Test 3
 *
 * Same setup as test 2, but use ZEND_SET_SYMBOL instead of zend_hash_add
 * Shows that ZEND_SET_SYMBOL has the same affect as zend_hash_add
 */

PHP_FUNCTION(test3)
{
	php_printf("\n**** test3 ****\n");

	// Create a new zval
	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Create a hashtable
	HashTable* locals;
	ALLOC_HASHTABLE(locals);
	zend_hash_init(locals, 50, NULL, NULL, 0);

	// Store "a" in the hashtable
	ZEND_SET_SYMBOL(locals, "a", a);

	// Retrieve "a" from the hashtable
	zval** a_from_locals;
	zend_hash_find(locals, "a", sizeof("a"), (void**)&a_from_locals); 
	dump_zval(*a_from_locals);

	// Destroy locals
	zend_hash_destroy(locals);
	FREE_HASHTABLE(locals);

	// Does "a" still exist after destroying the hashtable? YES!
	dump_zval(a);

	// Not calling the destructor here will result in a memory leak
	zval_ptr_dtor(&a);
}

/*
 * Test 4
 *
 * Create a zval, pass it to a function
 */

PHP_FUNCTION(test4_fn)
{
	php_printf("**** test4_fn ****\n");
}

PHP_FUNCTION(test4)
{
	php_printf("\n**** test4 ****\n");

	// Create a new zval
	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Pass the zval as an argument to a function
	zval fn_name;
	ZVAL_STRING(&fn_name, "test4_fn", 0);
	zval ret_val;
	zval* args[1];
	args[0] = a;

	call_user_function(EG(function_table), NULL, &fn_name, &ret_val, 1, args TSRMLS_CC);

	// Show the zval 
	dump_zval(a);

	// Free
	zval_ptr_dtor(&a);
}

/*
 * Test 5
 *
 * Like test 4, but extract the parameter in test5_fn and display it.
 * Demonstrates that the refcount has automatically been increased.
 */

PHP_FUNCTION(test5_fn)
{
	php_printf("**** test5_fn ****\n");

	zval* a_param;

	zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &a_param);
	dump_zval(a_param);
}

PHP_FUNCTION(test5)
{
	php_printf("\n**** test5 ****\n");

	// Create a new zval
	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Pass the zval as an argument to a function
	zval fn_name;
	ZVAL_STRING(&fn_name, "test5_fn", 0);
	zval ret_val;
	zval* args[1];
	args[0] = a;

	call_user_function(EG(function_table), NULL, &fn_name, &ret_val, 1, args TSRMLS_CC);

	// Show the zval 
	dump_zval(a);

	// Free
	zval_ptr_dtor(&a);
}

/*
 * Test 6
 *
 * Like test 5, but use zend_get_parameters instead. 
 * a_param here will be a brand new zval.
 */

PHP_FUNCTION(test6_fn)
{
	php_printf("**** test6_fn ****\n");

	zval* a_param;

	zend_get_parameters(ZEND_NUM_ARGS(), 1, &a_param);
	dump_zval(a_param);
}

PHP_FUNCTION(test6)
{
	php_printf("\n**** test6 ****\n");

	// Create a new zval
	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Pass the zval as an argument to a function
	zval fn_name;
	ZVAL_STRING(&fn_name, "test6_fn", 0);
	zval ret_val;
	zval* args[1];
	args[0] = a;

	call_user_function(EG(function_table), NULL, &fn_name, &ret_val, 1, args TSRMLS_CC);

	// Show the zval 
	dump_zval(a);

	// Free
	zval_ptr_dtor(&a);
}

/*
 * Test 7
 *
 * Like test 6, but using zend_get_paramers_ex.
 * This doesn't work at all! Not sure why.
 */

PHP_FUNCTION(test7_fn)
{
	php_printf("**** test7_fn ****\n");

	zval* a_param;

	zend_get_parameters_ex(1, &a_param);
	dump_zval(a_param);
}

PHP_FUNCTION(test7)
{
	php_printf("\n**** test7 ****\n");

	// Create a new zval
	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Pass the zval as an argument to a function
	zval fn_name;
	ZVAL_STRING(&fn_name, "test7_fn", 0);
	zval ret_val;
	zval* args[1];
	args[0] = a;

	call_user_function(EG(function_table), NULL, &fn_name, &ret_val, 1, args TSRMLS_CC);

	// Show the zval 
	dump_zval(a);

	// Free
	zval_ptr_dtor(&a);
}

/*
 * Test 8
 *
 * Create a zval, pass it as an argument to a function, then add it to the
 * locals array (but do nothing else). Shows that the zval is destroyed when
 * the hash table is destroyed; ZVAL_PTR_DTOR ignores the refcount!
 */

PHP_FUNCTION(test8_fn)
{
	php_printf("**** test8_fn ****\n");

	zval* a_param;

	zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &a_param);

	dump_zval(a_param);

	// Create a locals array
	HashTable* locals;
	ALLOC_HASHTABLE(locals);
	zend_hash_init(locals, 50, NULL, ZVAL_PTR_DTOR, 0);

	// Add a_param to the hashtable
	ZEND_SET_SYMBOL(locals, "a", a_param); 

	// Destroy locals
	zend_hash_destroy(locals);
	FREE_HASHTABLE(locals);
}

PHP_FUNCTION(test8)
{
	php_printf("\n**** test8 ****\n");

	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Pass the zval as an argument to a function
	zval fn_name;
	ZVAL_STRING(&fn_name, "test8_fn", 0);
	zval ret_val;
	zval* args[1];
	args[0] = a;

	call_user_function(EG(function_table), NULL, &fn_name, &ret_val, 1, args TSRMLS_CC);
	
	// Display the zval after calling the function
	dump_zval(a);

	// Free it
	zval_ptr_dtor(&a);
}

/*
 * Test 8b
 *
 * Like test 8, but use zend_hash_add instead of ZEND_SET_SYMBOL.
 * Fails the same way.
 *
 * Ah, I see. ZVAL_PTR_DTOR does in fact take the refcount into account;
 * and reduces it by one. So, when the function exists, the 
 * "function destructor" reduces it further by one, and then destroys it.
 */

PHP_FUNCTION(test8b_fn)
{
	php_printf("**** test8b_fn ****\n");

	zval* a_param;

	zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &a_param);

	dump_zval(a_param);

	// Create a locals array
	HashTable* locals;
	ALLOC_HASHTABLE(locals);
	zend_hash_init(locals, 50, NULL, ZVAL_PTR_DTOR, 0);

	// Add a_param to the hashtable
	zend_hash_add(locals, "a", sizeof("a"), &a_param, sizeof(zval*), NULL);

	// Destroy locals
	zend_hash_destroy(locals);
	FREE_HASHTABLE(locals);
	
	dump_zval(a_param);
}

PHP_FUNCTION(test8b)
{
	php_printf("\n**** test8b ****\n");

	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Pass the zval as an argument to a function
	zval fn_name;
	ZVAL_STRING(&fn_name, "test8b_fn", 0);
	zval ret_val;
	zval* args[1];
	args[0] = a;

	call_user_function(EG(function_table), NULL, &fn_name, &ret_val, 1, args TSRMLS_CC);
	
	// Display the zval after calling the function
	dump_zval(a);

	// Free it
	zval_ptr_dtor(&a);
}

/*
 * Test 8c
 *
 * Like test 8b, but explicitely up the refcount before adding it to the locals
 * array. This works correctly.
 */

PHP_FUNCTION(test8c_fn)
{
	php_printf("**** test8c_fn ****\n");

	zval* a_param;

	zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &a_param);

	dump_zval(a_param);

	// Create a locals array
	HashTable* locals;
	ALLOC_HASHTABLE(locals);
	zend_hash_init(locals, 50, NULL, ZVAL_PTR_DTOR, 0);

	// Add a_param to the hashtable
	zval_add_ref(&a_param);
	zend_hash_add(locals, "a", sizeof("a"), &a_param, sizeof(zval*), NULL);

	// Destroy locals
	zend_hash_destroy(locals);
	FREE_HASHTABLE(locals);
	
	dump_zval(a_param);
}

PHP_FUNCTION(test8c)
{
	php_printf("\n**** test8c ****\n");

	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Pass the zval as an argument to a function
	zval fn_name;
	ZVAL_STRING(&fn_name, "test8c_fn", 0);
	zval ret_val;
	zval* args[1];
	args[0] = a;

	call_user_function(EG(function_table), NULL, &fn_name, &ret_val, 1, args TSRMLS_CC);
	
	// Display the zval after calling the function
	dump_zval(a);

	// Free it
	zval_ptr_dtor(&a);
}


/*
 * Test 9
 *
 * Like test 8, but use a hashtable without a destructor. 
 * This is a strange one; it has the same result as test 8!
 */

PHP_FUNCTION(test9_fn)
{
	php_printf("**** test9_fn ****\n");

	zval* a_param;

	zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &a_param);

	dump_zval(a_param);

	// Create a locals array
	HashTable* locals;
	ALLOC_HASHTABLE(locals);
	zend_hash_init(locals, 50, NULL, NULL, 0);

	// Add a_param to the hashtable
	ZEND_SET_SYMBOL(locals, "a", a_param); 

	// Destroy locals
	zend_hash_destroy(locals);
	FREE_HASHTABLE(locals);
}

PHP_FUNCTION(test9)
{
	php_printf("\n**** test9 ****\n");

	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Pass the zval as an argument to a function
	zval fn_name;
	ZVAL_STRING(&fn_name, "test9_fn", 0);
	zval ret_val;
	zval* args[1];
	args[0] = a;

	call_user_function(EG(function_table), NULL, &fn_name, &ret_val, 1, args TSRMLS_CC);
	
	// Display the zval after calling the function
	dump_zval(a);

	// Free it
	zval_ptr_dtor(&a);
}

/*
 * Test 10 
 *
 * Like test 9, but using zend_hash_add instead of ZEND_SET_SYMBOL.
 * This one does work as expected! ZEND_SET_SYMBOL must do some magic after all
 */

PHP_FUNCTION(test10_fn)
{
	php_printf("**** test10_fn ****\n");

	zval* a_param;

	zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &a_param);

	dump_zval(a_param);

	// Create a locals array
	HashTable* locals;
	ALLOC_HASHTABLE(locals);
	zend_hash_init(locals, 50, NULL, NULL, 0);

	// Add a_param to the hashtable
	zend_hash_add(locals, "a", sizeof("a"), &a_param, sizeof(zval*), NULL);

	// Destroy locals
	zend_hash_destroy(locals);
	FREE_HASHTABLE(locals);
}

PHP_FUNCTION(test10)
{
	php_printf("\n**** test10 ****\n");

	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Pass the zval as an argument to a function
	zval fn_name;
	ZVAL_STRING(&fn_name, "test10_fn", 0);
	zval ret_val;
	zval* args[1];
	args[0] = a;

	call_user_function(EG(function_table), NULL, &fn_name, &ret_val, 1, args TSRMLS_CC);
	
	// Display the zval after calling the function
	dump_zval(a);

	// Free it
	zval_ptr_dtor(&a);
}

/*
 * Test 11 
 *
 * Like test 10, but retrieve the parameter from the locals array again and
 * display it.
 */

PHP_FUNCTION(test11_fn)
{
	php_printf("**** test11_fn ****\n");

	zval* a_param;

	zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &a_param);

	dump_zval(a_param);

	// Create a locals array
	HashTable* locals;
	ALLOC_HASHTABLE(locals);
	zend_hash_init(locals, 50, NULL, NULL, 0);

	// Add a_param to the hashtable
	zend_hash_add(locals, "a", sizeof("a"), &a_param, sizeof(zval*), NULL);

	// Retrieve the parameter
	zval** a_from_locals;
	zend_hash_find(locals, "a", sizeof("a"), (void**)&a_from_locals); 
	dump_zval(*a_from_locals);

	// Destroy locals
	zend_hash_destroy(locals);
	FREE_HASHTABLE(locals);
}

PHP_FUNCTION(test11)
{
	php_printf("\n**** test11 ****\n");

	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_LONG(a, 1234);
	dump_zval(a);

	// Pass the zval as an argument to a function
	zval fn_name;
	ZVAL_STRING(&fn_name, "test11_fn", 0);
	zval ret_val;
	zval* args[1];
	args[0] = a;

	call_user_function(EG(function_table), NULL, &fn_name, &ret_val, 1, args TSRMLS_CC);
	
	// Display the zval after calling the function
	dump_zval(a);

	// Free it
	zval_ptr_dtor(&a);
}

/* 
 * Register all functions with PHP
 */

static function_entry app_functions[] = 
{
	PHP_FE(test1, NULL)
	PHP_FE(test2, NULL)
	PHP_FE(test3, NULL)
	PHP_FE(test4, NULL)
	PHP_FE(test4_fn, NULL)
	PHP_FE(test5, NULL)
	PHP_FE(test5_fn, NULL)
	PHP_FE(test6, NULL)
	PHP_FE(test6_fn, NULL)
	PHP_FE(test7, NULL)
	PHP_FE(test7_fn, NULL)
	PHP_FE(test8, NULL)
	PHP_FE(test8_fn, NULL)
	PHP_FE(test8b, NULL)
	PHP_FE(test8b_fn, NULL)
	PHP_FE(test8c, NULL)
	PHP_FE(test8c_fn, NULL)
	PHP_FE(test9, NULL)
	PHP_FE(test9_fn, NULL)
	PHP_FE(test10, NULL)
	PHP_FE(test10_fn, NULL)
	PHP_FE(test11, NULL)
	PHP_FE(test11_fn, NULL)
	{ NULL, NULL, NULL }
};

/*
 * Register module
 */

zend_module_entry app_module_entry = 
{
	STANDARD_MODULE_HEADER, 
	"app",
	app_functions,
	NULL, /* MINIT */
	NULL, /* MSHUTDOWN */
	NULL, /* RINIT */
	NULL, /* RSHUTDOWN */
	NULL, /* MINFO */
	"1.0",
	STANDARD_MODULE_PROPERTIES
};

/*
 * Application driver
 */

void call(int argc, char** argv, char* name)
{
	// To reduce the influence the tests have on each other, 
	// we run each test in a separate instance of the SAPI
	
	PHP_EMBED_START_BLOCK(argc, argv)

		// Load the module
		zend_startup_module(&app_module_entry);
	
		zval ret_val;
		zval fn_name;
		
		// Call test1 
		ZVAL_STRING(&fn_name, name, NULL);
		call_user_function(EG(function_table), NULL, &fn_name, &ret_val, 0, NULL TSRMLS_CC);

	PHP_EMBED_END_BLOCK()
}

int main(int argc, char** argv)
{
	call(argc, argv, "test1");
	call(argc, argv, "test2");
	call(argc, argv, "test3");
	call(argc, argv, "test4");
	call(argc, argv, "test5");
	call(argc, argv, "test6");
	call(argc, argv, "test7");
	call(argc, argv, "test8");
	call(argc, argv, "test8b");
	call(argc, argv, "test8c");
	call(argc, argv, "test9");
	call(argc, argv, "test10");
	call(argc, argv, "test11");

	return 0;
}
