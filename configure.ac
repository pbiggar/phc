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
AC_PATH_PROG([gengetopt], [gengetopt])
AC_PATH_PROG([gperf], [gperf])
AC_PATH_PROG([flex], [flex])
AC_PATH_PROG([bison], [bison])
AC_PATH_PROG([patch], [patch])
AC_PATH_PROG([diff], [diff])
AC_PATH_PROG([valgrind], [valgrind])
AC_PATH_PROG([dot], [dot])
AC_PATH_PROG([graphviz_gc], [gc])

AC_ARG_WITH([maketea], 
   AS_HELP_STRING([--with-maketea], [path to maketea (if installed)]),
  [AC_PATH_PROG([maketea], [maketea], [], [${withval}:${withval}/bin])],
  [AC_PATH_PROG([maketea], [maketea])]
  )

dnl This seems like more of a --enable/disable option, but the maketea and php options both use --with/without
dnl AC_CHECK_LIB_XERCES
AC_ARG_WITH([xerces],
	[AS_HELP_STRING([--with-xerces], [support XML input @<:@default=check@:>@])],
	[], # with_xerces is set to true false anyway
	[with_xerces=check]
	)

# check PHP path
AC_ARG_WITH([php], 
	AS_HELP_STRING([--with-php=PATH], [PHP installation path (defaults to /usr/local)]), 
	[
		AS_IF([test "x$with_php" != xno], 
			[AC_CHECK_PHP([$withval])], [AS_VAR_SET([found_embed_sapi], [no])])
	], 
	[
		AC_CHECK_PHP([/usr/local])
	])


dnl checks for libraries
AC_LANG([C++])
AC_CHECK_COVARIANCE
AC_CHECK_LIB_CRUN
AC_CHECK_LIB([gc], [main], [AC_DEFINE([HAVE_GC_LIB], [1])])
dnl check xerces unless disabled
AS_IF([test "x$with_xerces" != xno], [AC_CHECK_LIB_XERCES], [])

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
* but make sure to pass the --enable-embed option to the PHP configure        *
* script.                                                                     *
*******************************************************************************]
	)])
