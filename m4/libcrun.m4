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


