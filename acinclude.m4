AC_DEFUN([AC_CHECK_LIB_CRUN], [
	AC_MSG_CHECKING([for /usr/lib/libCrun.so.1])
	check_libcrun_save_LIBS=$LIBS
	LIBS="/usr/lib/libCrun.so.1 $LIBS"
	AC_LINK_IFELSE(
		[AC_LANG_CALL([], [main])],
		[AS_VAR_SET(use_libCrun, yes)
		 AC_MSG_RESULT(yes) 
		],
		[AS_VAR_SET(use_libCrun, no)
		 AC_MSG_RESULT(no)
		])
	LIBS=$check_libcrun_save_LIBS
	AS_IF(
		[test AS_VAR_GET(use_libCrun) = yes], 
		[LIBS="/usr/lib/libCrun.so.1 $LIBS"])
])

AC_DEFUN([AC_CHECK_COVARIANCE], [
	AC_MSG_CHECKING([whether compiler supports covariant returns])
	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM(
			[
				class A { public: virtual A* x() { return new A(); } };
				class B { public: virtual B* y() { return new B(); } };
				class C : public A, B {
					public: C* x() { return new C(); }
							C* y() { return new C(); }
				};
			],
			[]
		)],
		[
		 AC_MSG_RESULT(yes)
		],
		[
		 AC_MSG_FAILURE(use g++ >3.4)
		]
	)
])

AC_DEFUN([AC_CHECK_LIB_XERCES], [
	AC_MSG_CHECKING([for -lxerces-c])
	check_lib_xerces_LIBS=$LIBS
	LIBS="-lxerces-c $LIBS"
	AC_LINK_IFELSE(
		[AC_LANG_PROGRAM(
			[#include <xercesc/util/PlatformUtils.hpp>
			 XERCES_CPP_NAMESPACE_USE
			],
			[XMLPlatformUtils::Initialize();]
		)],
		[AS_VAR_SET(use_libXerces, yes)
		 AC_MSG_RESULT(yes)
		 AC_DEFINE(HAVE_XERCES, 1)
		],
		[AS_VAR_SET(use_libXerces, no)
		 AC_MSG_RESULT(no)
		])
	LIBS=$check_lib_xerces_LIBS
	AS_IF(
		[test AS_VAR_GET(use_libXerces) = yes],
		[LIBS="-lxerces-c $LIBS"])
	AC_SUBST([use_libXerces])
])
