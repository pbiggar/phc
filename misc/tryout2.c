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
 * Create a zval but do not deallocate one.
 * One memory leak of 16 bytes 
 */

PHP_FUNCTION(test1)
{
	php_printf("\n**** test1 ****\n");

	zval* a;
	MAKE_STD_ZVAL(a);
}

/*
 * Test 2
 *
 * Create a zval, and initialise it with a 12 byte string (to be copied)
 * Two memory leaks of 16 and 12 bytes
 */

PHP_FUNCTION(test2)
{
	php_printf("\n**** test2 ****\n");

	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_STRING(a, "Hello world", 1);
}

/*
 * Test 3
 *
 * Like test 2, but call zval_dtor to free the string
 * One memory leak of 16 bytes
 */

PHP_FUNCTION(test3)
{
	php_printf("\n**** test3 ****\n");

	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_STRING(a, "Hello world", 1);
	zval_dtor(a);
}

/*
 * Test 4
 *
 * Like test 3, but call zval_ptr_dtor. No memory leaks.
 */

PHP_FUNCTION(test4)
{
	php_printf("\n**** test4 ****\n");

	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_STRING(a, "Hello world", 1);
	zval_ptr_dtor(&a);
}

/*
 * Test 5
 *
 * Call concat_function on a created (but not instantiated) zval
 * (Calling concat_function with a NULL target segfaults)
 *
 * No memory leaks.
 */

PHP_FUNCTION(test5)
{
	php_printf("\n**** test5 ****\n");

	zval* a;
	MAKE_STD_ZVAL(a);
	ZVAL_STRING(a, "Hello", 1);
	
	zval* b;
	MAKE_STD_ZVAL(b);
	ZVAL_STRING(b, " world", 1);

	zval* c;
	MAKE_STD_ZVAL(c);
	concat_function(c, a, b TSRMLS_CC);

	zval_ptr_dtor(&a);
	zval_ptr_dtor(&b);
	zval_ptr_dtor(&c);
}

/*
 * Test 6
 *
 * Create two zvals (rather than zval*s). No memory leaks. 
 */

PHP_FUNCTION(test6)
{
	php_printf("\n**** test6 ****\n");

	zval a;
	INIT_ZVAL(a);
	ZVAL_STRING(&a, "Hello", 0);
	
	zval b;
	INIT_ZVAL(b);
	ZVAL_STRING(&b, " world", 0);
}

/*
 * Test 7
 *
 * Create two zvals (rather than zval*s). Use ZVAL(.., 1)
 * Two memory leaks of 6 and 7 bytes.
 */

PHP_FUNCTION(test7)
{
	php_printf("\n**** test7 ****\n");

	zval a;
	INIT_ZVAL(a);
	ZVAL_STRING(&a, "Hello", 1);
	
	zval b;
	INIT_ZVAL(b);
	ZVAL_STRING(&b, " world", 1);
}

/*
 * Test 8
 *
 * Like test 7, but call zval_dtor. No memory leaks.
 */

PHP_FUNCTION(test8)
{
	php_printf("\n**** test8 ****\n");

	zval a;
	INIT_ZVAL(a);
	ZVAL_STRING(&a, "Hello", 1);
	
	zval b;
	INIT_ZVAL(b);
	ZVAL_STRING(&b, " world", 1);

	zval_dtor(&a);
	zval_dtor(&b);
}

/*
 * Test 9
 *
 * Like test 5, but using zvals rather than zval*s. No memory leaks.
 */

PHP_FUNCTION(test9)
{
	php_printf("\n**** test9 ****\n");

	zval a;
	INIT_ZVAL(a);
	ZVAL_STRING(&a, "Hello", 1);
	
	zval b;
	INIT_ZVAL(b);
	ZVAL_STRING(&b, " world", 1);

	zval c;
	INIT_ZVAL(c);
	concat_function(&c, &a, &b TSRMLS_CC);

	zval_dtor(&a);
	zval_dtor(&b);
	zval_dtor(&c);
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
	PHP_FE(test5, NULL)
	PHP_FE(test6, NULL)
	PHP_FE(test7, NULL)
	PHP_FE(test8, NULL)
	PHP_FE(test9, NULL)
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
	call(argc, argv, "test9");

	return 0;
}
