AC_DEFUN([PHP_EMBED],
[
    AC_ARG_WITH([php-config],
        AS_HELP_STRING([--with-php-config=@<:@ARG@:>@],
            [path to php-config (ARG=path)]
        ),
        [
        if test -f "$withval"; then
            php_config="$withval"
        elif test -d "$withval"; then
            if test -f "$withval/php-config"; then
                php_config="$withval/php-config"
            fi
        else
            php_config="php-config"
        fi
        ],
        [
        dnl Default behavior is implicit yes
            php_config="php-config"
        ]
    )

    if test -z "$php_config"; then
        AC_MSG_ERROR([Cannot find php-config. Please use --with-php-config=PATH])
    fi

    dnl For BC
    PHP_CONFIG=$php_config
    PHP_INSTALL_PATH=`$PHP_CONFIG --prefix 2>/dev/null`
    PHP_INCLUDES_PATH=`$PHP_CONFIG --include-dir 2>/dev/null`
    PHP_INCLUDES=`$PHP_CONFIG --includes 2>/dev/null`
    PHP_EXECUTABLE=`$PHP_CONFIG --php-binary 2>/dev/null`

    for php_embed_path in ${PHP_INSTALL_PATH}/lib ${PHP_INSTALL_PATH}/lib/php ${PHP_INSTALL_PATH}/lib/php5; do
        for libext in so dylib a; do
            if test -f ${php_embed_path}/libphp5.${libext}; then
                PHP_EMBED_PATH=${php_embed_path};
            fi
        done
    done

	if test -z "$PHP_EMBED_PATH"; then
	  AC_MSG_ERROR([Cannot find libphp5 embed.])
	fi

    AC_PATH_PROG([php], [php], [${PHP_EXECUTABLE}], [$PATH])
    # For config.h:
    AC_DEFINE_UNQUOTED([PHP_INSTALL_PATH], ["${PHP_INSTALL_PATH}"])
    AC_DEFINE_UNQUOTED([PHP_INSTALL_PATH], ["${PHP_INSTALL_PATH}"])
    AC_DEFINE_UNQUOTED([PHP_INCLUDES_PATH], ["${PHP_INCLUDES_PATH}"])
    AC_DEFINE_UNQUOTED([PHP_EMBED_PATH], ["${PHP_EMBED_PATH}"])
    # For autovars.php.in:
    AC_SUBST([php_install_path], ["${PHP_INSTALL_PATH}"])

	dnl To check if the PHP embed SAPI has been installed, we temporarily add the
	dnl PHP installation path to LDFLAGS and CFLAGS, and restore it later (since 
	dnl we do not need that path to build phc itself).
	AS_VAR_SET(found_embed_sapi, yes)
	OLD_LDFLAGS=$LDFLAGS
	OLD_CPPFLAGS=$CPPFLAGS
	LDFLAGS="-L${PHP_EMBED_PATH} $LDFLAGS"	
	CPPFLAGS="${PHP_INCLUDES} $CPPFLAGS"
	AC_CHECK_LIB(
		[php5], 
		[zend_eval_string], 
		[
			AS_VAR_SET(found_embed_sapi, yes)
			AC_DEFINE(HAVE_EMBED, 1)
			AC_SUBST([libphp_headers], ["${PHP_INCLUDES}"])
			LIBS="-lphp5 -L${PHP_EMBED_PATH} -R${PHP_EMBED_PATH} $LIBS"
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
	CPPFLAGS=$OLD_CPPFLAGS
	LDFLAGS=$OLD_LDFLAGS
])
