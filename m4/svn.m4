AC_DEFUN([PHC_CHECK_SVN],
	[
		AS_IF([test -d .svn], [AC_MSG_WARN([
***********************************************
* You are using the phc svn repository. Read  *
* README.svn or you may experience problems.  *
***********************************************]
	)])
	])
}
