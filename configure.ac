dnl phc -- the open source PHP compiler
dnl See doc/license/README.license for licensing information
dnl
dnl Process this file using autoconf to produce configure

dnl Autoconf requirements
AC_INIT([phc], [0.2.0rc1], [phc-general@phpcompiler.org])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([config])

dnl Package information
AC_ARG_ENABLE(
	[gc],
	[AS_HELP_STRING([--enable-gc], [Link to the Boehm garbage collector (EXPERIMENTAL; seems to lead to segfaults in some cases])],
	[AC_DEFINE([ENABLE_GC], [1]) 
	 AC_SUBST([gc_lib], [-lgc])
	])

dnl configure automake
AM_INIT_AUTOMAKE([foreign -Wall -Werror 1.9])
AM_MAINTAINER_MODE


dnl checks for programs
AC_PROG_CC
AC_PROG_CXX

dnl Configure libtool
AC_LIBLTDL_CONVENIENCE dnl build convenience library, and set LIBLTDL
AC_LIBTOOL_DLOPEN dnl check for dlopen support
AC_PROG_LIBTOOL dnl Configure libtool
AC_CONFIG_SUBDIRS([libltdl])
AC_SUBST([LTDLINCL])
AC_SUBST([LIBLTDL])

dnl check for other programs
AC_PATH_PROG([ghc], [ghc])
AC_PATH_PROG([gengetopt], [gengetopt])
AC_PATH_PROG([gperf], [gperf])
AC_PATH_PROG([flex], [flex])
AC_PATH_PROG([bison], [bison])
AC_PATH_PROG([patch], [patch])
AC_PATH_PROG([diff], [diff])
AC_PATH_PROG([valgrind], [valgrind])
AC_PATH_PROG([dot], [dot])
AC_PATH_PROG([graphviz_gc], [gc])
AC_PATH_PROG([maketea], [maketea])
 
AC_ARG_WITH([php], 
	AS_HELP_STRING([--with-php=PATH], [PHP installation path (defaults to /usr/local)]), 
	[
		AC_PATH_PROG([php], [php], [], [${withval}/bin])
		# For config.h:
		AC_DEFINE_UNQUOTED([PHP_INSTALL_PATH], ["$withval"])
		# For autovars.php.in:
		AC_SUBST([php_install_path], ["$withval"])
		# For use below:
		PHP_INSTALL_PATH=$withval
	], 
	[
		AC_PATH_PROG([php], [php], [], [/usr/local/bin])
		AC_DEFINE([PHP_INSTALL_PATH], ["/usr/local"])
		AC_SUBST([php_install_path], ["/usr/local"])
		PHP_INSTALL_PATH=["/usr/local"]
	])

dnl To check if the PHP embed SAPI has been installed, we temporarily add the
dnl PHP installation path to LDFLAGS and CFLAGS, and restore it later (since 
dnl we do not need that path to build phc itself).
OLD_LDFLAGS=$LDFLAGS
OLD_CFLAGS=$CFLAGS
LDFLAGS="-L${PHP_INSTALL_PATH}/lib $LDFLAGS"	
CFLAGS="-I${PHP_INSTALL_PATH}/include/php -I${PHP_INSTALL_PATH}/include/php/main -I${PHP_INSTALL_PATH}/include/php/TSRM -I${PHP_INSTALL_PATH}/include/php/Zend $CFLAGS"
AC_CHECK_LIB(
	[php5], 
	[zend_eval_string], 
	[AS_VAR_SET(found_embed_sapi, yes)], 
	[AS_VAR_SET(found_embed_sapi, no)], 
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

dnl checks for libraries
AC_LANG([C++])
AC_CHECK_COVARIANCE
AC_CHECK_LIB_CRUN
AC_CHECK_LIB_XERCES
AC_CHECK_LIB([gc], [main], [AC_DEFINE([HAVE_GC_LIB], [1])])

dnl checks for header files
AC_CHECK_HEADER([gc/gc_cpp.h], [AC_DEFINE([HAVE_GC_INC], [1])])

dnl checks for types
dnl checks for structures
dnl checks for compiler characteristics
dnl checks for library functions
dnl checks for system services

# Finishing
# phc_compile_plugin and test/scripts/lib/autovars.php are created using their
# own Make rules, as it's not possible to expand directory prefixes using this
# mechanism. See the autoconf manual, section "Installation Directory
# Variables".
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

# Warn if libphp5 wasn't found
AS_IF(
	[test AS_VAR_GET([found_embed_sapi]) = no],
	[AC_MSG_WARN(
		[
*******************************************************************************
* It seems the PHP embed SAPI has not been installed.                         *
*                                                                             *
* You will be able to compile and run phc, but you will not be able to        *
* compile PHP scripts with phc.                                               *
*                                                                             *
* To install the PHP embed SAPI, follow the PHP installation instructions,    *
* but make sure to pass the --embed-embed option to the PHP configure script. *
*******************************************************************************]
	)])
