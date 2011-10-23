dnl phc -- the open source PHP compiler
dnl See doc/license/README.license for licensing information
dnl
dnl Process this file using autoconf to produce configure

# Running aclocal, automake and autoconf can produce errors. These are avoided by running aclocal:
#	$ aclocal -I /usr/share/autoconf-archive -I libltdl
# which adds the macros needed for libtool, boost, etc.

dnl Autoconf requirements
AC_INIT([phc], [0.3.0.1], [phc-general@phpcompiler.org])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])
AC_PREREQ(2.63) # 2.61 adds a warning. Pre-2.61 just doesnt work.

PHC_CHECK_SVN

dnl configure automake
AM_INIT_AUTOMAKE([foreign -Wall -Werror 1.10]) # 1.10 changed a lot of things.
AM_MAINTAINER_MODE


dnl checks for programs
AC_PROG_CC
AC_PROG_CXX

dnl Configure libtool and libltdl
LT_INIT([dlopen])
LT_CONFIG_LTDL_DIR([libltdl])
LTDL_INIT([convenience])


dnl check for other programs
AC_PATH_PROG([gengetopt], [gengetopt], [config/phc_missing gengetopt])
AC_PATH_PROG([gperf], [gperf], [config/phc_missing gperf])
AC_PATH_PROG([flex], [flex], [config/phc_missing flex])
AC_PATH_PROG([bison], [bison], [config/phc_missing bison])
AC_PATH_PROG([valgrind], [valgrind])
AC_PATH_PROG([dot], [dot])
AC_PATH_PROG([graphviz_gc], [gc])

AC_ARG_WITH([maketea], 
   AS_HELP_STRING([--with-maketea], [path to maketea (if installed)]),
  [AC_PATH_PROG([maketea], [maketea], [config/phc_missing maketea], [${withval}:${withval}/bin])],
  [AC_PATH_PROG([maketea], [maketea], [config/phc_missing maketea])]
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
AX_BOOST_BASE([1.35.0])
AX_BOOST_REGEX

dnl Xerces
AX_LIB_XERCES
AC_SUBST([HAVE_XERCES], [$HAVE_XERCES]) # for autovars.php
AS_IF([test "x$HAVE_XERCES" != xno],
      [AC_DEFINE([HAVE_XERCES], [1])]) # for config.h

dnl Boehm-gc
AC_ARG_ENABLE([gc],
	[AS_HELP_STRING([--disable-gc], [Link to the Boehm garbage collector @<:@default=enabled@:>@])])

# Use GC unless disabled
# libgccpp overrides ::new, which is required to collect the Boost Graph Library.
AS_IF([test "x$enable_gc" != xno],
		[
			AC_CHECK_HEADER([gc/gc_cpp.h], [], [AC_MSG_FAILURE(libgc required)])
			AC_CHECK_LIB([gc], [main], [], [AC_MSG_FAILURE(libgc required)])
			AC_CHECK_LIB([gccpp], [main], [], [AC_MSG_FAILURE(libgccpp required)])
			AC_SUBST([gc_lib], ["-lgc -lgccpp"])
		],
		[AC_DEFINE([DISABLE_GC], [1])])


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
