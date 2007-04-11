## phc -- the open source PHP compiler
## See doc/license/README.license for licensing information
##
## Process this file with automake to produce Makefile.in

# A lot of what's going on in explained in:
# automake manual - http://sources.redhat.com/automake/automake.html
# autoconf manual - http://www.gnu.org/software/autoconf/manual/autoconf.htm
# autotools tutorial - http://autotoolset.sourceforge.net/tutorial.html
# autotools book - http://sources.redhat.com/autobook/autobook/autobook.html (consult this last)

# TODO install autoreconf?

SUBDIRS = libltdl

# Note the preprocessor supports -Wall, so we put that here, rather than a seperate CXX_FLAGS
AM_CPPFLAGS = \
	$(LTDLINCL) -I$(srcdir)/src -I$(srcdir)/3rdparty/getopt -I$(srcdir)/3rdparty/flex \
	-I$(srcdir)/src/generated \
	-DDATADIR=\"$(datadir)\" -DPKGLIBDIR=\"$(pkglibdir)\" -Wall

bin_PROGRAMS = src/phc

# By using CXXFLAGS we avoid warnings in generated_src, which we dont want to
# hear about. 
AM_CXXFLAGS = -Wextra -Wno-unused-parameter

# Special libtool flag for later plugin loading
src_phc_LDFLAGS = -export-dynamic

# We leave out -dlopen" self "-dlopen" since its built-in to later automakes,
# and we dont want this feature anyway
src_phc_LDADD = @gc_lib@ $(LIBLTDL)

src_phc_DEPENDENCIES = $(LIBLTDL)

bin_SCRIPTS = src/phc_compile_plugin
libexec_SCRIPTS = libtool
# pkgdata_DATA = phc-1.0.xsd

src_phc_SOURCES =												\
	3rdparty/getopt/getopt1.c								\
	3rdparty/getopt/getopt.c								\
	3rdparty/getopt/getopt.h								\
	src/codegen/Generate_C.cpp								\
	src/codegen/Generate_C.h								\
	src/codegen/Lower_control_flow.cpp					\
	src/codegen/Lower_control_flow.h						\
	src/codegen/Shredder.cpp								\
	src/codegen/Shredder.h									\
	src/codegen/Lift_functions_and_classes.cpp		\
	src/codegen/Lift_functions_and_classes.h			\
	src/codegen/fresh.cpp									\
	src/codegen/fresh.h										\
	src/codegen/Prep.cpp										\
	src/codegen/Prep.h										\
	src/generated/AST.cpp									\
	src/generated/AST.h										\
	src/generated/cmdline.c									\
	src/generated/cmdline.h									\
	src/generated/keywords.h								\
	src/generated/lex.yy.cc									\
	src/generated/php_parser.tab.cpp						\
	src/generated/AST_transform.cpp						\
	src/generated/AST_transform.h							\
	src/generated/AST_visitor.cpp							\
	src/generated/AST_visitor.h							\
	src/lib/AttrMap.cpp										\
	src/lib/AttrMap.h											\
	src/lib/base64.cpp										\
	src/lib/base64.h											\
	src/lib/Boolean.h											\
	src/lib/Boolean.cpp										\
	src/lib/demangle.cpp										\
	src/lib/demangle.h										\
	src/lib/error.cpp											\
	src/lib/error.h											\
	src/lib/Integer.h											\
	src/lib/Integer.cpp										\
	src/lib/List.h												\
	src/lib/Object.h											\
	src/lib/Object.cpp										\
	src/lib/String.cpp										\
	src/lib/String.h											\
	src/parsing/parse.cpp									\
	src/parsing/parse.h										\
	src/parsing/PHP_context.cpp							\
	src/parsing/PHP_context.h								\
	src/parsing/XML_parser.cpp								\
	src/parsing/XML_parser.h								\
	src/phc.cpp													\
	src/process_ast/DOT_unparser.cpp						\
	src/process_ast/DOT_unparser.h						\
	src/process_ast/Invocation_targets.cpp				\
	src/process_ast/Invocation_targets.h				\
	src/process_ast/PHP_unparser.cpp						\
	src/process_ast/PHP_unparser.h						\
	src/process_ast/process_ast.cpp						\
	src/process_ast/process_ast.h							\
	src/process_ast/Remove_concat_null.cpp				\
	src/process_ast/Remove_concat_null.h				\
	src/process_ast/Remove_parser_temporaries.cpp	\
	src/process_ast/Remove_parser_temporaries.h		\
	src/process_ast/Token_conversion.cpp				\
	src/process_ast/Token_conversion.h					\
	src/process_ast/Variable_targets.cpp				\
	src/process_ast/Variable_targets.h					\
	src/process_ast/XML_unparser.cpp						\
	src/process_ast/XML_unparser.h						\
	src/process_ast/Process_includes.cpp				\
	src/process_ast/Process_includes.h

BUILT_SOURCES = \
	src/generated/AST.cpp									\
	src/generated/AST.h										\
	src/generated/cmdline.c									\
	src/generated/cmdline.h									\
	src/generated/keywords.h								\
	src/generated/lex.yy.cc									\
	src/generated/php_parser.tab.cpp						\
	src/generated/AST_transform.cpp						\
	src/generated/AST_transform.h							\
	src/generated/AST_visitor.cpp							\
	src/generated/AST_visitor.h							\
	test/framework/lib/autovars.php

# - The magic to accomplish this is described cryptically in the last few
#   paragraphs of section 7.3 of the automake manual.
# - We use the 'stange' prefix because the macro expansion is unpredictable,
#   and using 'phc' or 'lib' or 'processast' might end up with strange results.
# - Stuff in lib/ is installed in /usr/include/phc/lib, stuff in process_ast/
#   is installed in /usr/include/phc/process_ast, and some random stuff is
#   installed in /usr/include/phc (ast.h, parse.h, AST_transform.h and 
#   AST_visitor.h)
strangephcdir = $(pkgincludedir)
strangephc_HEADERS =						\
	config.h									\
	src/generated/AST.h					\
	src/generated/AST_transform.h		\
	src/generated/AST_visitor.h

strangeparsingdir = $(pkgincludedir)/parsing
strangeparsing_HEADERS =				\
	src/parsing/parse.h

strangeprocessastdir = $(pkgincludedir)/process_ast
strangeprocessast_HEADERS =					\
	src/process_ast/DOT_unparser.h			\
	src/process_ast/PHP_unparser.h			\
	src/process_ast/Remove_concat_null.h	\
	src/process_ast/XML_unparser.h			\
	src/process_ast/Process_includes.h

strangelibdir = $(pkgincludedir)/lib
strangelib_HEADERS =		\
	src/lib/AttrMap.h		\
	src/lib/base64.h		\
	src/lib/Boolean.h		\
	src/lib/demangle.h	\
	src/lib/error.h		\
	src/lib/Integer.h		\
	src/lib/List.h			\
	src/lib/Object.h		\
	src/lib/String.h

## TODO prepend dist onto those we distribute
nobase_pkglib_LTLIBRARIES = 
PLUGIN_LDFLAGS = -module -avoid-version

nobase_pkglib_LTLIBRARIES += plugins/tests/canonical_unparser.la
plugins_tests_canonical_unparser_la_SOURCES = plugins/tests/canonical_unparser.cpp
plugins_tests_canonical_unparser_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/goto_uppering.la
plugins_tests_goto_uppering_la_SOURCES = plugins/tests/goto_uppering.cpp
plugins_tests_goto_uppering_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/cloning.la
plugins_tests_cloning_la_SOURCES = plugins/tests/cloning.cpp
plugins_tests_cloning_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/linear.la
plugins_tests_linear_la_SOURCES = plugins/tests/linear.cpp
plugins_tests_linear_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/line_numbers.la
plugins_tests_line_numbers_la_SOURCES = plugins/tests/line_numbers.cpp
plugins_tests_line_numbers_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/pre_vs_post_count.la
plugins_tests_pre_vs_post_count_la_SOURCES = plugins/tests/pre_vs_post_count.cpp
plugins_tests_pre_vs_post_count_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/source_vs_semantic_values.la
plugins_tests_source_vs_semantic_values_la_SOURCES = plugins/tests/source_vs_semantic_values.cpp
plugins_tests_source_vs_semantic_values_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/xml_roundtrip.la
plugins_tests_xml_roundtrip_la_SOURCES = plugins/tests/xml_roundtrip.cpp
plugins_tests_xml_roundtrip_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/purity_test.la
plugins_tools_purity_test_la_SOURCES = plugins/tools/purity_test.cpp
plugins_tools_purity_test_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tutorials/Comment_ifs.la
plugins_tutorials_Comment_ifs_la_SOURCES = plugins/tutorials/Comment_ifs.cpp
plugins_tutorials_Comment_ifs_la_LDFLAGS = ${PLUGIN_LDFLAGS}

# TODO: probably replace by another tutorial
#nobase_pkglib_LTLIBRARIES += plugins/tutorials/count_classes.la
#plugins_tutorials_count_classes_la_SOURCES = plugins/tutorials/count_classes.cpp
#plugins_tutorials_count_classes_la_LDFLAGS = ${PLUGIN_LDFLAGS}

# TODO: probably replace by another tutorial
#nobase_pkglib_LTLIBRARIES += plugins/tutorials/count_function_calls_difficult.la
#plugins_tutorials_count_function_calls_difficult_la_SOURCES = plugins/tutorials/count_function_calls_difficult.cpp
#plugins_tutorials_count_function_calls_difficult_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tutorials/count_function_calls_easy.la
plugins_tutorials_count_function_calls_easy_la_SOURCES = plugins/tutorials/count_function_calls_easy.cpp
plugins_tutorials_count_function_calls_easy_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tutorials/count_statements.la
plugins_tutorials_count_statements_la_SOURCES = plugins/tutorials/count_statements.cpp
plugins_tutorials_count_statements_la_LDFLAGS = ${PLUGIN_LDFLAGS}

# TODO: probably replace by another tutorial
#nobase_pkglib_LTLIBRARIES += plugins/tutorials/Expand_includes.la
#plugins_tutorials_Expand_includes_la_SOURCES = plugins/tutorials/Expand_includes.cpp
#plugins_tutorials_Expand_includes_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tutorials/helloworld.la
plugins_tutorials_helloworld_la_SOURCES = plugins/tutorials/helloworld.cpp
plugins_tutorials_helloworld_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tutorials/InsertDB.la
plugins_tutorials_InsertDB_la_SOURCES = plugins/tutorials/InsertDB.cpp
plugins_tutorials_InsertDB_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tutorials/MySQL2DBX.la
plugins_tutorials_MySQL2DBX_la_SOURCES = plugins/tutorials/MySQL2DBX.cpp
plugins_tutorials_MySQL2DBX_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tutorials/show_traversal_order.la
plugins_tutorials_show_traversal_order_la_SOURCES = plugins/tutorials/show_traversal_order.cpp
plugins_tutorials_show_traversal_order_la_LDFLAGS = ${PLUGIN_LDFLAGS}


## generate special files
# - In order to have separate build directories (aka VPATH), we would prepend
#   $(srcdir) onto all these dependencies, targets, etc. However, after
#   spending a few hours trying to see how this would go, it's probably better
#   to require people to build in directory, until there is a need to do
#   otherwise.
# - According to section 27.9 of the automake manual, this is not the correct
#   way to handle multiple files being dependant on a single command. However,
#   the correct way is so onerous, that this way seems much better.
# - sed (also rm, mv and echo, below) are amongst the allowed programs to use
#   in a Makefile. See GNU coding standards 7.2.2.
src/generated/AST.cpp \
src/generated/AST.h \
src/generated/AST_transform.cpp \
src/generated/AST_transform.h \
src/generated/AST_visitor.cpp \
src/generated/AST_visitor.h: src/generated_src/phc.tea
	@maketea@ src/generated_src/phc.tea
	mv AST.cpp src/generated/
	mv AST.h src/generated/
	mv AST_transform.cpp src/generated/
	mv AST_transform.h src/generated/
	mv AST_visitor.cpp src/generated/
	mv AST_visitor.h src/generated/
	mv AST-contexts src/generated/
#	mv schema.xsd src/generated/phc-1.0.xsd

src/generated/keywords.h: src/generated_src/php.gperf 
	@gperf@ --language=ANSI-C --includes --readonly-tables --struct-type --ignore-case --output-file=src/generated/keywords.h src/generated_src/php.gperf

src/generated/cmdline.c \
src/generated/cmdline.h: src/generated_src/phc.ggo
	@gengetopt@ --unamed-opts --input=src/generated_src/phc.ggo --file-name=src/generated/cmdline

src/generated/lex.yy.cc: src/generated_src/php_scanner.lex
	@flex@ -s -osrc/generated/lex.yy.cc src/generated_src/php_scanner.lex

src/generated/php_parser.tab.cpp src/generated/php_parser.tab.hpp: src/generated_src/php_parser.ypp
	@bison@ -o src/generated/php_parser.tab.cpp -d src/generated_src/php_parser.ypp

# - Without the second \@, autoconf with replace the @CFLAGS\@ etc
src/phc_compile_plugin: Makefile src/phc_compile_plugin.in
	sed -e 's,@includedir\@,$(includedir),g; s,@CXX\@,$(CXX),g; s,@CFLAGS\@,$(CFLAGS),g; s,@LDFLAGS\@,$(LDFLAGS),g; s,@libexecdir\@,$(libexecdir),g; s,@pkglibdir\@,$(pkglibdir),g;' $(srcdir)/src/phc_compile_plugin.in > src/phc_compile_plugin
	chmod 755 src/phc_compile_plugin

test/framework/lib/autovars.php: Makefile test/framework/lib/autovars.php.in
	sed -e 's,@valgrind\@,$(valgrind),g; s,@graphviz_gc\@,$(graphviz_gc),g;s,@dot\@,$(dot),g; s,@php\@,$(php),g; s,@CC\@,$(CC),g; s,@diff\@,$(diff),g;s,@php_install_path\@,$(php_install_path),g; s,@bindir\@,$(bindir),g; s,@EXEEXT\@,$(EXEEXT),g; s,@pkglibdir\@,$(pkglibdir),g; s,@xerces_compiled_in\@,$(use_libXerces),g;' $(srcdir)/test/framework/lib/autovars.php.in > test/framework/lib/autovars.php


## Clean files

# Files can be specified by the variables. Directories must be removed using rules.
# These comments are copied from automake manual, section 13.
# Files built using generated_src are in maintainer-clean.

# - If make built it, and it is commonly something that one would want to
#   rebuild (for instance, a .o file), then mostlyclean should delete it.
MOSTLYCLEANFILES =

# - Otherwise, if make built it, then clean should delete it.
CLEANFILES =  src/phc_compile_plugin test/framework/lib/autovars.php
# Just delete the contents - the directory is in svn
clean-local:
	rm -rf test/logs/* 

# - If configure built it, then distclean should delete it.
DISTCLEANFILES = aclocal.m4
distclean-local:
	rm -rf autom4te.cache

# - If the maintainer built it (for instance, a .info file), then
#   maintainer-clean should delete it. However maintainer-clean should not
#   delete anything that needs to exist in order to run ./configure && make. 
MAINTAINERCLEANFILES = Makefile.in src/generated/README.TreeTransform
# Just delete the contents - the directory is in svn
maintainerclean-local:
	rm -rf src/generated/*


## Run the tests
check-local: test
installcheck-local: installtest

test: all test/framework/lib/autovars.php
	@if [ -n "@php@" ]; \
		then echo @php@ -Cq $(srcdir)/test/framework/driver.php; \
		@php@ -Cq $(srcdir)/test/framework/driver.php; \
		else echo PHP support required for test; \
	fi

installtest: install test/framework/lib/autovars.php
	@if [ -n "@php@" ]; \
		then echo @php@ -Cq $(srcdir)/test/framework/driver.php -i; \
		@php@ -Cq $(srcdir)/test/framework/driver.php -i;  \
		else echo PHP support required for test; \
	fi

long-test: all test/framework/lib/autovars.php
	@if [ -n "@php@" ]; \
		then echo @php@ -Cq $(srcdir)/test/framework/driver.php -l; \
		@php@ -Cq $(srcdir)/test/framework/driver.php -l; \
		else echo PHP support required for test; \
	fi

generate-test-files: all test/framework/lib/autovars.php
	@if [ -n "@php@" ]; \
		then echo @php@ -Cq $(srcdir)/test/framework/driver.php -s -l regression BasicParseTest; \
		@php@ -Cq $(srcdir)/test/framework/driver.php -s -l regression BasicParseTest; \
		else echo PHP support required for test; \
	fi

