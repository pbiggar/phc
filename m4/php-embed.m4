dnl Takes a single parameter - where to look.
AC_DEFUN([AC_CHECK_PHP], [
	AC_PATH_PROG([php], [php], [], ["$1/bin"])
	# For config.h:
	AC_DEFINE_UNQUOTED([PHP_INSTALL_PATH], ["$1"])
	# For autovars.php.in:
	AC_SUBST([php_install_path], ["$1"])
	# For use below:
	PHP_INSTALL_PATH=$1

	dnl To check if the PHP embed SAPI has been installed, we temporarily add the
	dnl PHP installation path to LDFLAGS and CFLAGS, and restore it later (since 
	dnl we do not need that path to build phc itself).
	AS_VAR_SET(found_embed_sapi, yes)
	OLD_LDFLAGS=$LDFLAGS
	OLD_CFLAGS=$CFLAGS
	LDFLAGS="-L${PHP_INSTALL_PATH}/lib $LDFLAGS"	
	CFLAGS="-isystem${PHP_INSTALL_PATH}/include/php -isystem${PHP_INSTALL_PATH}/include/php/main -isystem${PHP_INSTALL_PATH}/include/php/TSRM -isystem${PHP_INSTALL_PATH}/include/php/Zend $CFLAGS"
	AC_CHECK_LIB(
		[php5], 
		[zend_eval_string], 
		[
			AS_VAR_SET(found_embed_sapi, yes)
			AC_DEFINE(HAVE_EMBED, 1)
			AC_SUBST([libphp_headers], ["-isystem${PHP_INSTALL_PATH}/include/php -isystem${PHP_INSTALL_PATH}/include/php/main -isystem${PHP_INSTALL_PATH}/include/php/TSRM -isystem${PHP_INSTALL_PATH}/include/php/Zend"])
			LIBS="-lphp5 -L${PHP_INSTALL_PATH}/lib -R${PHP_INSTALL_PATH}/lib $LIBS"
		], 
		[
			AS_VAR_SET(found_embed_sapi, no)
		], 
		[]
		)
	AC_CHECK_HEADER(
		[sapi/embed/php_embed.h], 
		[], 
		[AS_VAR_SET(found_embed_sapi, no)],
		[]
		)
	CFLAGS=$OLD_CFLAGS
	LDFLAGS=$OLD_LDFLAGS
])



