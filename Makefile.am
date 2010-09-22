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
	$(BOOST_CPPFLAGS) $(LTDLINCL) $(XERCES_CPPFLAGS) 															\
	-I$(srcdir)/src -I$(srcdir) -I$(srcdir)/3rdparty/getopt -I$(srcdir)/src/generated		\
	@libphp_headers@																				\
	-DDATADIR=\"$(datadir)\" -DPKGLIBDIR=\"$(pkglibdir)\"								\
	-Wall

AM_LDFLAGS = $(BOOST_LDFLAGS) $(XERCES_LDFLAGS)

lib_LTLIBRARIES = libphc.la
bin_PROGRAMS = src/phc

# By using CXXFLAGS we avoid warnings in generated_src, which we dont want to
# hear about. 
AM_CXXFLAGS = -Wextra -Wno-unused-parameter -Wno-write-strings -Wno-deprecated

ACLOCAL_AMFLAGS = -I m4 -I libltdl

# Note about warnings: automake does not support per-file flags. If they did,
# we could set -Wall -Wextra -Werror, and fix things as they came up. However,
# since we do not control some of our source (Zend headers, generated code from
# other tools), we cannot do this. There is an alternative (google for
# 'automake per-object flag emulation'), but this is cumbersome, since we have
# 5 or 6 files which require special rules.

# -export-dynammic: Special libtool flag for later plugin loading
src_phc_LDFLAGS = -export-dynamic

src_phc_LDADD = @gc_lib@ $(LIBLTDL) $(BOOST_REGEX_LIB) libphc.la $(XERCES_LIBS)

bin_SCRIPTS = src/phc_compile_plugin
libexec_SCRIPTS = libtool
# pkgdata_DATA = phc-1.0.xsd

src_phc_SOURCES =												\
	src/phc.cpp

libphc_la_SOURCES= 											\
	3rdparty/getopt/getopt1.c								\
	3rdparty/getopt/getopt.c								\
	3rdparty/getopt/getopt.h								\
	src/ast_to_hir/AST_annotate.cpp						\
	src/ast_to_hir/AST_annotate.h							\
	src/ast_to_hir/AST_lower_expr.cpp					\
	src/ast_to_hir/AST_lower_expr.h						\
	src/ast_to_hir/AST_shredder.cpp						\
	src/ast_to_hir/AST_shredder.h							\
	src/ast_to_hir/AST_to_HIR.h							\
	src/ast_to_hir/Desugar.cpp								\
	src/ast_to_hir/Desugar.h								\
	src/ast_to_hir/Early_lower_control_flow.cpp		\
	src/ast_to_hir/Early_lower_control_flow.h			\
	src/ast_to_hir/Echo_split.cpp							\
	src/ast_to_hir/Echo_split.h							\
	src/ast_to_hir/List_shredder.cpp						\
	src/ast_to_hir/List_shredder.h						\
	src/ast_to_hir/Lower_expr_flow.cpp					\
	src/ast_to_hir/Lower_expr_flow.h						\
	src/ast_to_hir/Pre_post_op_shredder.cpp			\
	src/ast_to_hir/Pre_post_op_shredder.h				\
	src/ast_to_hir/Remove_solo_exprs.h					\
	src/ast_to_hir/Split_multiple_arguments.cpp		\
	src/ast_to_hir/Split_multiple_arguments.h			\
	src/ast_to_hir/Split_unset_isset.cpp				\
	src/ast_to_hir/Split_unset_isset.h					\
	src/ast_to_hir/Strip_comments.cpp					\
	src/ast_to_hir/Strip_comments.h						\
	src/ast_to_hir/Switch_bin_op.cpp						\
	src/ast_to_hir/Switch_bin_op.h						\
	src/codegen/Clarify.cpp									\
	src/codegen/Clarify.h									\
	src/codegen/Compile_C.cpp								\
	src/codegen/Compile_C.h									\
	src/codegen/Generate_C_annotations.cpp				\
	src/codegen/Generate_C_annotations.h				\
	src/codegen/Generate_C.cpp								\
	src/codegen/Generate_C.h								\
	src/codegen/Generate_C_pass.cpp						\
	src/codegen/Generate_C_pass.h							\
	src/codegen/Lift_functions_and_classes.cpp		\
	src/codegen/Lift_functions_and_classes.h			\
	src/codegen/MICG_checker.cpp							\
	src/codegen/MICG_checker.h								\
	src/codegen/MICG_gen.cpp								\
	src/codegen/MICG_gen.h									\
	src/embed/embed.cpp										\
	src/embed/embed.h											\
	src/embed/optimize.cpp									\
	src/embed/util.cpp										\
	src/embed/util.h											\
	src/generated/AST.cpp									\
	src/generated/AST_factory.cpp							\
	src/generated/AST_factory.h							\
	src/generated/AST_fold.h								\
	src/generated/AST.h										\
	src/generated/AST_transform.cpp						\
	src/generated/AST_transform.h							\
	src/generated/AST_user_defined.h						\
	src/generated/AST_visitor.cpp							\
	src/generated/AST_visitor.h							\
	src/generated/cmdline.c									\
	src/generated/cmdline.h									\
	src/generated/HIR.cpp									\
	src/generated/HIR_factory.cpp							\
	src/generated/HIR_factory.h							\
	src/generated/HIR_fold.h								\
	src/generated/HIR.h										\
	src/generated/HIR_transform.cpp						\
	src/generated/HIR_transform.h							\
	src/generated/HIR_user_defined.h						\
	src/generated/HIR_visitor.cpp							\
	src/generated/HIR_visitor.h							\
	src/generated/keywords.h								\
	src/generated/lex.yy.cc									\
	src/generated/MICG.cpp									\
	src/generated/MICG_factory.cpp						\
	src/generated/MICG_factory.h							\
	src/generated/MICG_fold.h								\
	src/generated/MICG.h										\
	src/generated/MICG_transform.cpp						\
	src/generated/MICG_transform.h						\
	src/generated/MICG_user_defined.h					\
	src/generated/MICG_visitor.cpp						\
	src/generated/MICG_visitor.h							\
	src/generated/MIR.cpp									\
	src/generated/MIR_factory.cpp							\
	src/generated/MIR_factory.h							\
	src/generated/MIR_fold.h								\
	src/generated/MIR.h										\
	src/generated/MIR_transform.cpp						\
	src/generated/MIR_transform.h							\
	src/generated/MIR_user_defined.h						\
	src/generated/MIR_visitor.cpp							\
	src/generated/MIR_visitor.h							\
	src/generated/php_dot.tab.cpp							\
	src/generated/php_dot.tab.hpp							\
	src/generated/php_parser.tab.cpp						\
	src/generated/php_parser.tab.hpp						\
	src/hir_to_mir/HIR_lower_expr.cpp					\
	src/hir_to_mir/HIR_lower_expr.h						\
	src/hir_to_mir/HIR_to_MIR.h							\
	src/hir_to_mir/Lower_control_flow.cpp				\
	src/hir_to_mir/Lower_control_flow.h					\
	src/hir_to_mir/Lower_dynamic_definitions.cpp		\
	src/hir_to_mir/Lower_dynamic_definitions.h		\
	src/hir_to_mir/Lower_method_invocations.cpp		\
	src/hir_to_mir/Lower_method_invocations.h			\
	src/lib/AttrMap.cpp										\
	src/lib/AttrMap.h											\
	src/lib/base64.cpp										\
	src/lib/base64.h											\
	src/lib/Boolean.cpp										\
	src/lib/Boolean.h											\
	src/lib/demangle.cpp										\
	src/lib/demangle.h										\
	src/lib/error.cpp											\
	src/lib/error.h											\
	src/lib/escape.cpp										\
	src/lib/escape.h											\
	src/lib/Integer.cpp										\
	src/lib/Integer.h											\
	src/lib/List.h												\
	src/lib/Map.cpp											\
	src/lib/Map.h												\
	src/lib/Object.cpp										\
	src/lib/Object.h											\
	src/lib/Set.h												\
	src/lib/Stack.h											\
	src/lib/String.cpp										\
	src/lib/String.h											\
	src/lib/Vector.h											\
	src/optimize/Abstract_value.cpp						\
	src/optimize/Abstract_value.h							\
	src/optimize/Alias_name.cpp							\
	src/optimize/Alias_name.h								\
	src/optimize/Basic_block.cpp							\
	src/optimize/Basic_block.h								\
	src/optimize/CFG.cpp										\
	src/optimize/CFG.h										\
	src/optimize/CFG_visitor.cpp							\
	src/optimize/CFG_visitor.h								\
	src/optimize/Class_info.cpp							\
	src/optimize/Class_info.h								\
	src/optimize/Dead_code_elimination.cpp				\
	src/optimize/Dead_code_elimination.h				\
	src/optimize/Def_use_web.cpp 							\
	src/optimize/Def_use_web.h								\
	src/optimize/Edge.cpp									\
	src/optimize/Edge.h										\
	src/optimize/Flow_visitor.cpp							\
	src/optimize/Flow_visitor.h							\
	src/optimize/If_simplification.cpp					\
	src/optimize/If_simplification.h						\
	src/optimize/Inlining.cpp								\
	src/optimize/Inlining.h									\
	src/optimize/Lattice.h									\
	src/optimize/Mark_initialized.cpp					\
	src/optimize/Mark_initialized.h						\
	src/optimize/Method_info.cpp							\
	src/optimize/Method_info.h								\
	src/optimize/Method_pruner.h							\
	src/optimize/Misc_annotations.cpp					\
	src/optimize/Misc_annotations.h						\
	src/optimize/Oracle.cpp									\
	src/optimize/Oracle.h									\
	src/optimize/Prune_symbol_table.cpp					\
	src/optimize/Prune_symbol_table.h					\
	src/optimize/Remove_loop_booleans.cpp				\
	src/optimize/Remove_loop_booleans.h					\
	src/optimize/hacks/Copy_propagation.cpp				\
	src/optimize/hacks/Copy_propagation.h				\
	src/optimize/hacks/Dead_temp_cleanup.cpp			\
	src/optimize/hacks/Dead_temp_cleanup.h				\
	src/optimize/hacks/Fix_point.cpp				\
	src/optimize/hacks/Fix_point.h				\
	src/optimize/hacks/Use_def_counter.cpp				\
	src/optimize/hacks/Use_def_counter.h				\
	src/optimize/ssa/Dominance.cpp						\
	src/optimize/ssa/Dominance.h							\
	src/optimize/ssa/HSSA.cpp								\
	src/optimize/ssa/HSSA.h									\
	src/optimize/ssa/Phi.cpp								\
	src/optimize/ssa/Phi.h									\
	src/optimize/ssa/SSA_name.cpp							\
	src/optimize/ssa/SSA_name.h							\
	src/optimize/ssa/SSA_ops.cpp							\
	src/optimize/ssa/SSA_ops.h								\
	src/optimize/ssi/ESSA.cpp								\
	src/optimize/ssi/ESSA.h								\
	src/optimize/ssi/Sigma.cpp								\
	src/optimize/ssi/Sigma.h								\
	src/optimize/ssi/SSI.cpp								\
	src/optimize/ssi/SSI.h								\
	src/optimize/ssi/SSI_ops.cpp								\
	src/optimize/ssi/SSI_ops.h								\
	src/optimize/Visit_once.cpp							\
	src/optimize/Visit_once.h								\
	src/optimize/wpa/Aliasing.cpp							\
	src/optimize/wpa/Aliasing.h							\
	src/optimize/wpa/Callgraph.cpp						\
	src/optimize/wpa/Callgraph.h							\
	src/optimize/wpa/Constant_state.cpp					\
	src/optimize/wpa/Constant_state.h					\
	src/optimize/wpa/Context.cpp							\
	src/optimize/wpa/Context.h								\
	src/optimize/wpa/Debug_WPA.cpp						\
	src/optimize/wpa/Debug_WPA.h							\
	src/optimize/wpa/Def_use.cpp							\
	src/optimize/wpa/Def_use.h								\
	src/optimize/wpa/Include_analysis.cpp				\
	src/optimize/wpa/Include_analysis.h					\
	src/optimize/wpa/Optimization_annotator.cpp		\
	src/optimize/wpa/Optimization_annotator.h			\
	src/optimize/wpa/Optimization_transformer.cpp	\
	src/optimize/wpa/Optimization_transformer.h		\
	src/optimize/wpa/Points_to.cpp						\
	src/optimize/wpa/Points_to.h							\
	src/optimize/wpa/Stat_collector.cpp	\
	src/optimize/wpa/Stat_collector.h	\
	src/optimize/wpa/Value_analysis.cpp					\
	src/optimize/wpa/Value_analysis.h					\
	src/optimize/wpa/VRP.cpp								\
	src/optimize/wpa/VRP.h									\
	src/optimize/wpa/Whole_program.cpp					\
	src/optimize/wpa/Whole_program.h						\
	src/optimize/wpa/Worklist.cpp							\
	src/optimize/wpa/Worklist.h							\
	src/optimize/wpa/WPA.cpp								\
	src/optimize/wpa/WPA.h									\
	src/optimize/wpa/WPA_lattice.h						\
	src/parsing/MICG_parser.cpp							\
	src/parsing/MICG_parser.h								\
	src/parsing/Parse_buffer.cpp							\
	src/parsing/Parse_buffer.h								\
	src/parsing/parse.cpp									\
	src/parsing/parse.h										\
	src/parsing/PHP_context.cpp							\
	src/parsing/PHP_context.h								\
	src/parsing/XML_parser.cpp								\
	src/parsing/XML_parser.h								\
	src/pass_manager/Fake_pass.h							\
	src/pass_manager/Optimization_pass.cpp				\
	src/pass_manager/Optimization_pass.h				\
	src/pass_manager/Pass.h									\
	src/pass_manager/Pass_manager.cpp					\
	src/pass_manager/Pass_manager.h						\
	src/pass_manager/Plugin_pass.cpp						\
	src/pass_manager/Plugin_pass.h						\
	src/pass_manager/Transform_pass.h					\
	src/pass_manager/Visitor_pass.h						\
	src/process_ast/AST_unparser.cpp						\
	src/process_ast/AST_unparser.h						\
	src/process_ast/Constant_folding.cpp				\
	src/process_ast/Constant_folding.h					\
	src/process_ast/DOT_unparser.cpp						\
	src/process_ast/DOT_unparser.h						\
	src/process_ast/Invalid_check.cpp					\
	src/process_ast/Invalid_check.h						\
	src/process_ast/Note_top_level_declarations.cpp	\
	src/process_ast/Note_top_level_declarations.h	\
	src/process_ast/Pretty_print.h						\
	src/process_ast/Process_includes.cpp				\
	src/process_ast/Process_includes.h					\
	src/process_ast/Remove_concat_null.cpp				\
	src/process_ast/Remove_concat_null.h				\
	src/process_ast/Remove_parser_temporaries.cpp	\
	src/process_ast/Remove_parser_temporaries.h		\
	src/process_ast/Strip_unparser_attributes.cpp	\
	src/process_ast/Strip_unparser_attributes.h		\
	src/process_ast/Token_conversion.cpp				\
	src/process_ast/Token_conversion.h					\
	src/process_hir/HIR_to_AST.h							\
	src/process_hir/HIR_unparser.cpp						\
	src/process_hir/HIR_unparser.h						\
	src/process_ir/Clone_blank_mixins.h					\
	src/process_ir/debug.cpp								\
	src/process_ir/debug.h									\
	src/process_ir/Foreach.h								\
	src/process_ir/fresh.cpp								\
	src/process_ir/fresh.h									\
	src/process_ir/General.cpp								\
	src/process_ir/General.h								\
	src/process_ir/IR.cpp									\
	src/process_ir/IR.h										\
	src/process_ir/PHP_unparser.cpp						\
	src/process_ir/PHP_unparser.h							\
	src/process_ir/stats.cpp								\
	src/process_ir/stats.h									\
	src/process_ir/XML_unparser.cpp						\
	src/process_ir/XML_unparser.h							\
	src/process_mir/Alias_uppering.cpp					\
	src/process_mir/Alias_uppering.h						\
	src/process_mir/Foreach_uppering.cpp				\
	src/process_mir/Foreach_uppering.h					\
	src/process_mir/Goto_uppering.cpp					\
	src/process_mir/Goto_uppering.h						\
	src/process_mir/Main_uppering.h						\
	src/process_mir/MIR_to_AST.h							\
	src/process_mir/MIR_unparser.cpp						\
	src/process_mir/MIR_unparser.h						\
	src/process_mir/Obfuscate.h							\
	src/process_mir/Param_is_ref_uppering.cpp			\
	src/process_mir/Param_is_ref_uppering.h

BUILT_SOURCES = 												\
	src/generated/AST.cpp									\
	src/generated/AST_factory.cpp							\
	src/generated/AST_factory.h							\
	src/generated/AST_fold.h								\
	src/generated/AST.h										\
	src/generated/AST_transform.cpp						\
	src/generated/AST_transform.h							\
	src/generated/AST_user_defined.h						\
	src/generated/AST_visitor.cpp							\
	src/generated/AST_visitor.h							\
	src/generated/cmdline.c									\
	src/generated/cmdline.h									\
	src/generated/HIR.cpp									\
	src/generated/HIR_factory.cpp							\
	src/generated/HIR_factory.h							\
	src/generated/HIR_fold.h								\
	src/generated/HIR.h										\
	src/generated/HIR_transform.cpp						\
	src/generated/HIR_transform.h							\
	src/generated/HIR_user_defined.h						\
	src/generated/HIR_visitor.cpp							\
	src/generated/HIR_visitor.h							\
	src/generated/keywords.h								\
	src/generated/lex.yy.cc									\
	src/generated/MICG.cpp									\
	src/generated/MICG_factory.cpp						\
	src/generated/MICG_factory.h							\
	src/generated/MICG_fold.h								\
	src/generated/MICG.h										\
	src/generated/MICG_transform.cpp						\
	src/generated/MICG_transform.h						\
	src/generated/MICG_user_defined.h					\
	src/generated/MICG_visitor.cpp						\
	src/generated/MICG_visitor.h							\
	src/generated/MIR.cpp									\
	src/generated/MIR_factory.cpp							\
	src/generated/MIR_factory.h							\
	src/generated/MIR_fold.h								\
	src/generated/MIR.h										\
	src/generated/MIR_transform.cpp						\
	src/generated/MIR_transform.h							\
	src/generated/MIR_user_defined.h						\
	src/generated/MIR_visitor.cpp							\
	src/generated/MIR_visitor.h							\
	src/generated/php_parser.tab.cpp						\
	src/generated/php_parser.tab.hpp						\
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
strangephc_HEADERS =							\
	config.h										\
	src/generated/AST_factory.h			\
	src/generated/AST_fold.h				\
	src/generated/AST.h						\
	src/generated/AST_transform.h			\
	src/generated/AST_user_defined.h		\
	src/generated/AST_visitor.h			\
	src/generated/cmdline.h					\
	src/generated/HIR_factory.h			\
	src/generated/HIR_fold.h				\
	src/generated/HIR.h						\
	src/generated/HIR_transform.h			\
	src/generated/HIR_user_defined.h		\
	src/generated/HIR_visitor.h			\
	src/generated/MIR_factory.h			\
	src/generated/MIR_fold.h				\
	src/generated/MIR.h						\
	src/generated/MIR_transform.h			\
	src/generated/MIR_user_defined.h		\
	src/generated/MIR_visitor.h

strangeoptimizedir = $(pkgincludedir)/optimize
strangeoptimize_HEADERS =					\
	src/optimize/Abstract_value.h		\
	src/optimize/Alias_name.h		\
	src/optimize/Basic_block.h		\
	src/optimize/CFG.h		\
	src/optimize/CFG_visitor.h		\
	src/optimize/Class_info.h		\
	src/optimize/Dead_code_elimination.h		\
	src/optimize/Def_use_web.h		\
	src/optimize/Edge.h		\
	src/optimize/Flow_visitor.h		\
	src/optimize/If_simplification.h		\
	src/optimize/Inlining.h		\
	src/optimize/Lattice.h		\
	src/optimize/Mark_initialized.h		\
	src/optimize/Method_info.h		\
	src/optimize/Method_pruner.h		\
	src/optimize/Misc_annotations.h		\
	src/optimize/Oracle.h		\
	src/optimize/Prune_symbol_table.h		\
	src/optimize/Remove_loop_booleans.h		\
	src/optimize/Visit_once.h

strangeoptimizehacksdir = $(pkgincludedir)/optimize/hacks
strangeoptimizehacks_HEADERS =					\
	src/optimize/hacks/Copy_propagation.h		\
	src/optimize/hacks/Dead_temp_cleanup.h		\
	src/optimize/hacks/Fix_point.h		\
	src/optimize/hacks/Use_def_counter.h

strangeoptimizessadir = $(pkgincludedir)/optimize/ssa
strangeoptimizessa_HEADERS =					\
	src/optimize/ssa/Dominance.h		\
	src/optimize/ssa/HSSA.h		\
	src/optimize/ssa/Phi.h		\
	src/optimize/ssa/SSA_name.h		\
	src/optimize/ssa/SSA_ops.h

strangeoptimizessidir = $(pkgincludedir)/optimize/ssi
strangeoptimizessi_HEADERS =					\
	src/optimize/ssi/ESSA.h		\
	src/optimize/ssi/Sigma.h		\
	src/optimize/ssi/SSI.h		\
	src/optimize/ssi/SSI_ops.h

strangeoptimizewpadir = $(pkgincludedir)/optimize/wpa
strangeoptimizewpa_HEADERS =					\
	src/optimize/wpa/Aliasing.h		\
	src/optimize/wpa/Callgraph.h		\
	src/optimize/wpa/Constant_state.h		\
	src/optimize/wpa/Context.h		\
	src/optimize/wpa/Debug_WPA.h		\
	src/optimize/wpa/Def_use.h		\
	src/optimize/wpa/Include_analysis.h		\
	src/optimize/wpa/Optimization_annotator.h		\
	src/optimize/wpa/Optimization_transformer.h		\
	src/optimize/wpa/Points_to.h		\
	src/optimize/wpa/Stat_collector.h		\
	src/optimize/wpa/Value_analysis.h		\
	src/optimize/wpa/VRP.h		\
	src/optimize/wpa/Whole_program.h		\
	src/optimize/wpa/Worklist.h		\
	src/optimize/wpa/WPA.h		\
	src/optimize/wpa/WPA_lattice.h

strangeparsingdir = $(pkgincludedir)/parsing
strangeparsing_HEADERS =					\
	src/parsing/parse.h						\
	src/parsing/Parse_buffer.h				\
	src/parsing/XML_parser.h

strangeprocessastdir = $(pkgincludedir)/process_ast
strangeprocessast_HEADERS =					\
	src/process_ast/AST_unparser.h			\
	src/process_ast/DOT_unparser.h			\
	src/process_ast/Invalid_check.h			\
	src/process_ast/Pretty_print.h

strangeprocesshirdir = $(pkgincludedir)/process_hir
strangeprocesshir_HEADERS =					\
	src/process_hir/HIR_unparser.h

strangeprocessmirdir = $(pkgincludedir)/process_mir
strangeprocessmir_HEADERS =					\
	src/process_mir/MIR_unparser.h

strangeprocessirdir = $(pkgincludedir)/process_ir
strangeprocessir_HEADERS =						\
	src/process_ir/Clone_blank_mixins.h		\
	src/process_ir/debug.h						\
	src/process_ir/Foreach.h					\
	src/process_ir/fresh.h						\
	src/process_ir/General.h					\
	src/process_ir/IR.h							\
	src/process_ir/PHP_unparser.h				\
	src/process_ir/stats.h						\
	src/process_ir/XML_unparser.h

strangepassmanagerdir = $(pkgincludedir)/pass_manager
strangepassmanager_HEADERS =					\
	src/pass_manager/Optimization_pass.h		\
	src/pass_manager/Pass.h						\
	src/pass_manager/Pass_manager.h			\
	src/pass_manager/Plugin_pass.h


strangelibdir = $(pkgincludedir)/lib
strangelib_HEADERS =		\
	src/lib/AttrMap.h		\
	src/lib/base64.h		\
	src/lib/Boolean.h		\
	src/lib/demangle.h	\
	src/lib/error.h		\
	src/lib/escape.h		\
	src/lib/Integer.h		\
	src/lib/List.h			\
	src/lib/Map.h			\
	src/lib/Object.h		\
	src/lib/Set.h			\
	src/lib/Stack.h		\
	src/lib/String.h		\
	src/lib/Vector.h


strangeruntimedir = $(pkgdatadir)/runtime
strangeruntime_DATA =						\
	runtime/arrays.c							\
	runtime/builtin_functions.c			\
	runtime/debug.c							\
	runtime/isset.c							\
	runtime/methods.c							\
	runtime/misc.c								\
	runtime/string.c							\
	runtime/support.c							\
	runtime/unset.c							\
	runtime/var_vars.c						\
	runtime/oop.c								\
	runtime/zval.c

# TODO: rename templates_new.c (and use 'macro')
strangeruntimetemplatesdir = $(strangeruntimedir)/templates
strangeruntimetemplates_DATA =			\
	runtime/templates/templates_new.c



## TODO prepend dist onto those we distribute
nobase_pkglib_LTLIBRARIES = 
PLUGIN_LDFLAGS = -module -avoid-version

nobase_pkglib_LTLIBRARIES += plugins/tests/canonical_unparser.la
plugins_tests_canonical_unparser_la_SOURCES = plugins/tests/canonical_unparser.cpp
plugins_tests_canonical_unparser_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/cloning.la
plugins_tests_cloning_la_SOURCES = plugins/tests/cloning.cpp plugins/tests/Collect_all_pointers.h
plugins_tests_cloning_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/run_once.la
plugins_tests_run_once_la_SOURCES = plugins/tests/run_once.cpp
plugins_tests_run_once_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/inconsistent_st_attr.la
plugins_tests_inconsistent_st_attr_la_SOURCES = plugins/tests/inconsistent_st_attr.cpp
plugins_tests_inconsistent_st_attr_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/linear.la
plugins_tests_linear_la_SOURCES = plugins/tests/linear.cpp plugins/tests/Collect_all_pointers.h
plugins_tests_linear_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/line_numbers.la
plugins_tests_line_numbers_la_SOURCES = plugins/tests/line_numbers.cpp
plugins_tests_line_numbers_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/raise_globals.la
plugins_tests_raise_globals_la_SOURCES = plugins/tests/raise_globals.cpp
plugins_tests_raise_globals_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/pre_vs_post_count.la
plugins_tests_pre_vs_post_count_la_SOURCES = plugins/tests/pre_vs_post_count.cpp
plugins_tests_pre_vs_post_count_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/source_vs_semantic_values.la
plugins_tests_source_vs_semantic_values_la_SOURCES = plugins/tests/source_vs_semantic_values.cpp
plugins_tests_source_vs_semantic_values_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tests/strip_includes.la
plugins_tests_strip_includes_la_SOURCES = plugins/tests/strip_includes.cpp
plugins_tests_strip_includes_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/add_comment.la
plugins_tools_add_comment_la_SOURCES = plugins/tools/add_comment.cpp
plugins_tools_add_comment_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/C_unparser.la
plugins_tools_C_unparser_la_SOURCES = plugins/tools/C_unparser.cpp
plugins_tools_C_unparser_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/debug_zval.la
plugins_tools_debug_zval_la_SOURCES = plugins/tools/debug_zval.cpp
plugins_tools_debug_zval_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/demi_eval.la
plugins_tools_demi_eval_la_SOURCES = plugins/tools/demi_eval.cpp
plugins_tools_demi_eval_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/purity_test.la
plugins_tools_purity_test_la_SOURCES = plugins/tools/purity_test.cpp
plugins_tools_purity_test_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/function_finder.la
plugins_tools_function_finder_la_SOURCES = plugins/tools/function_finder.cpp
plugins_tools_function_finder_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/dynamic_things.la
plugins_tools_dynamic_things_la_SOURCES = plugins/tools/dynamic_things.cpp
plugins_tools_dynamic_things_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/get_defines.la
plugins_tools_get_defines_la_SOURCES = plugins/tools/get_defines.cpp
plugins_tools_get_defines_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/reduce_statements.la
plugins_tools_reduce_statements_la_SOURCES = plugins/tools/reduce_statements.cpp
plugins_tools_reduce_statements_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/remove_all.la
plugins_tools_remove_all_la_SOURCES = plugins/tools/remove_all.cpp
plugins_tools_remove_all_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/replace_include_constants.la
plugins_tools_replace_include_constants_la_SOURCES = plugins/tools/replace_include_constants.cpp
plugins_tools_replace_include_constants_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tools/test_ssi.la
plugins_tools_test_ssi_la_SOURCES = plugins/tools/test_ssi.cpp
plugins_tools_test_ssi_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tutorials/Comment_ifs.la
plugins_tutorials_Comment_ifs_la_SOURCES = plugins/tutorials/Comment_ifs.cpp
plugins_tutorials_Comment_ifs_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tutorials/count_statements_difficult.la
plugins_tutorials_count_statements_difficult_la_SOURCES = plugins/tutorials/count_statements_difficult.cpp
plugins_tutorials_count_statements_difficult_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tutorials/count_statements_easy.la
plugins_tutorials_count_statements_easy_la_SOURCES = plugins/tutorials/count_statements_easy.cpp
plugins_tutorials_count_statements_easy_la_LDFLAGS = ${PLUGIN_LDFLAGS}

nobase_pkglib_LTLIBRARIES += plugins/tutorials/Expand_includes.la
plugins_tutorials_Expand_includes_la_SOURCES = plugins/tutorials/Expand_includes.cpp
plugins_tutorials_Expand_includes_la_LDFLAGS = ${PLUGIN_LDFLAGS}

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
src/generated/AST.cpp: 					src/generated/AST.h
src/generated/AST_factory.cpp:		src/generated/AST.h
src/generated/AST_factory.h:			src/generated/AST.h
src/generated/AST_fold.h:				src/generated/AST.h
src/generated/AST_transform.cpp:		src/generated/AST.h
src/generated/AST_transform.h:		src/generated/AST.h
src/generated/AST_user_defined.h:	src/generated/AST.h
src/generated/AST_visitor.cpp:		src/generated/AST.h
src/generated/AST_visitor.h:			src/generated/AST.h
#src/generated/schema.xsd:				src/generated/AST.h

src/generated/AST.h: src/generated_src/ast.tea
	@maketea@ src/generated_src/ast.tea

src/generated/HIR.cpp: 					src/generated/HIR.h
src/generated/HIR_factory.cpp:		src/generated/HIR.h
src/generated/HIR_factory.h:			src/generated/HIR.h
src/generated/HIR_fold.h:				src/generated/HIR.h
src/generated/HIR_transform.cpp:		src/generated/HIR.h
src/generated/HIR_transform.h:		src/generated/HIR.h
src/generated/HIR_user_defined.h:	src/generated/HIR.h
src/generated/HIR_visitor.cpp:		src/generated/HIR.h
src/generated/HIR_visitor.h:			src/generated/HIR.h
#src/generated/schema.xsd:				src/generated/HIR.h

src/generated/HIR.h: src/generated_src/hir.tea
	@maketea@ src/generated_src/hir.tea

src/generated/MIR.cpp: 					src/generated/MIR.h
src/generated/MIR_factory.cpp:		src/generated/MIR.h
src/generated/MIR_factory.h:			src/generated/MIR.h
src/generated/MIR_fold.h:				src/generated/MIR.h
src/generated/MIR_transform.cpp:		src/generated/MIR.h
src/generated/MIR_transform.h:		src/generated/MIR.h
src/generated/MIR_user_defined.h:	src/generated/MIR.h
src/generated/MIR_visitor.cpp:		src/generated/MIR.h
src/generated/MIR_visitor.h:			src/generated/MIR.h
#src/generated/schema.xsd:				src/generated/MIR.h

src/generated/MIR.h: src/generated_src/mir.tea
	@maketea@ src/generated_src/mir.tea

src/generated/MICG.cpp: 				src/generated/MICG.h
src/generated/MICG_factory.cpp:		src/generated/MICG.h
src/generated/MICG_factory.h:			src/generated/MICG.h
src/generated/MICG_fold.h:				src/generated/MICG.h
src/generated/MICG_transform.cpp:	src/generated/MICG.h
src/generated/MICG_transform.h:		src/generated/MICG.h
src/generated/MICG_user_defined.h:	src/generated/MICG.h
src/generated/MICG_visitor.cpp:		src/generated/MICG.h
src/generated/MICG_visitor.h:			src/generated/MICG.h
#src/generated/schema.xsd:				src/generated/MICG.h

src/generated/MICG.h: src/generated_src/micg.tea
	@maketea@ src/generated_src/micg.tea


# Perfect minimal hashing via gperf
src/generated/keywords.h: src/generated_src/php.gperf 
	@gperf@ --language=ANSI-C --includes --readonly-tables --struct-type --ignore-case --output-file=src/generated/keywords.h src/generated_src/php.gperf

# Command line options via gengetopt
src/generated/cmdline.c: src/generated/cmdline.h
src/generated/cmdline.h: src/generated_src/phc.ggo
	@gengetopt@ --unamed-opts --input=src/generated_src/phc.ggo --file-name=src/generated/cmdline

# Lexer via flex
src/generated/lex.yy.cc: src/generated_src/php_scanner.lex
	@flex@ -s -osrc/generated/lex.yy.cc src/generated_src/php_scanner.lex

# PHP parser via bison
src/generated/php_parser.tab.hpp: src/generated/php_parser.tab.cpp
src/generated/php_parser.tab.cpp: src/generated_src/php_parser.ypp
	@bison@ -o src/generated/php_parser.tab.cpp -d src/generated_src/php_parser.ypp


# PHP grammar dot representation via bison
src/generated/php_dot.tab.hpp: src/generated/php_dot.tab.cpp
src/generated/php_dot.tab.cpp: src/generated_src/php_dot.ypp
	@bison@ -o src/generated/php_dot.tab.cpp -d src/generated_src/php_dot.ypp


# - Without the second \@, autoconf with replace the @CFLAGS\@ etc
src/phc_compile_plugin: Makefile src/phc_compile_plugin.in
	sed -e 's!@includedir\@!$(includedir)!g; s!@CXX\@!$(CXX)!g; s!@CFLAGS\@!$(CFLAGS)!g; s!@LDFLAGS\@!$(LDFLAGS)!g; s!@libexecdir\@!$(libexecdir)!g; s!@pkglibdir\@!$(pkglibdir)!g;' $(srcdir)/src/phc_compile_plugin.in > src/phc_compile_plugin
	chmod 755 src/phc_compile_plugin

test/framework/lib/autovars.php: Makefile test/framework/lib/autovars.php.in
	sed -e 's!@valgrind\@!$(valgrind)!g; s!@graphviz_gc\@!$(graphviz_gc)!g;s!@dot\@!$(dot)!g; s!@php\@!$(php)!g; s!@CC\@!$(CC)!g; s!@diff\@!$(diff)!g;s!@php_install_path\@!$(php_install_path)!g; s!@bindir\@!$(bindir)!g; s!@EXEEXT\@!$(EXEEXT)!g; s!@pkglibdir\@!$(pkglibdir)!g; s!@xerces_compiled_in\@!$(HAVE_XERCES)!g; s!@AM_CPPFLAGS\@!$(AM_CPPFLAGS)!g;' $(srcdir)/test/framework/lib/autovars.php.in > test/framework/lib/autovars.php


## Clean files

# Files can be specified by the variables. Directories must be removed using rules.
# These comments are copied from automake manual, section 13.
# Files built using generated_src are in maintainer-clean.

# - If make built it, and it is commonly something that one would want to
#   rebuild (for instance, a .o file), then mostlyclean should delete it.
MOSTLYCLEANFILES =

# - Otherwise, if make built it, then clean should delete it.
CLEANFILES =  src/phc_compile_plugin test/framework/lib/autovars.php

# - If configure built it, then distclean should delete it.
DISTCLEANFILES = aclocal.m4
distclean-local:
	rm -rf autom4te.cache

# - If the maintainer built it (for instance, a .info file), then
#   maintainer-clean should delete it. However maintainer-clean should not
#   delete anything that needs to exist in order to run ./configure && make. 
MAINTAINERCLEANFILES = Makefile.in
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
	else \
		if [ -x "`which php`" ]; \
			then echo php -Cq $(srcdir)/test/framework/driver.php; \
			php -Cq $(srcdir)/test/framework/driver.php; \
		else \
			echo PHP support required for test; \
		fi \
	fi

installtest: install test/framework/lib/autovars.php
	@if [ -n "@php@" ]; \
		then echo @php@ -Cq $(srcdir)/test/framework/driver.php -i; \
		@php@ -Cq $(srcdir)/test/framework/driver.php -i; \
	else \
		if [ -x "`which php`" ]; \
			then echo php -Cq $(srcdir)/test/framework/driver.php -i; \
			php -Cq $(srcdir)/test/framework/driver.php -i; \
		else \
			echo PHP support required for test; \
		fi \
	fi


long-test: all test/framework/lib/autovars.php
	@if [ -n "@php@" ]; \
		then echo @php@ -Cq $(srcdir)/test/framework/driver.php -l; \
		@php@ -Cq $(srcdir)/test/framework/driver.php -l; \
	else \
		if [ -x "`which php`" ]; \
			then echo php -Cq $(srcdir)/test/framework/driver.php -l; \
			php -Cq $(srcdir)/test/framework/driver.php -l; \
		else \
			echo PHP support required for test; \
		fi \
	fi


generate-test-files: all test/framework/lib/autovars.php
	@if [ -n "@php@" ]; \
		then echo @php@ -Cq $(srcdir)/test/framework/driver.php -s regression; \
		@php@ -Cq $(srcdir)/test/framework/driver.php -s regression; \
	else \
		if [ -x "`which php`" ]; \
			then echo php -Cq $(srcdir)/test/framework/driver.php -s regression; \
			php -Cq $(srcdir)/test/framework/driver.php - regression; \
		else \
			echo PHP support required for test; \
		fi \
	fi

long-generate-test-files: all test/framework/lib/autovars.php
	@if [ -n "@php@" ]; \
		then echo @php@ -Cq $(srcdir)/test/framework/driver.php -s -l regression; \
		@php@ -Cq $(srcdir)/test/framework/driver.php -s -l regression; \
	else \
		if [ -x "`which php`" ]; \
			then echo php -Cq $(srcdir)/test/framework/driver.php -s -l regression; \
			php -Cq $(srcdir)/test/framework/driver.php -s -l regression; \
		else \
			echo PHP support required for test; \
		fi \
	fi

testclean: all test/framework/lib/autovars.php
	@if [ -n "@php@" ]; \
		then echo @php@ -Cq $(srcdir)/test/framework/driver.php -c; \
		@php@ -Cq $(srcdir)/test/framework/driver.php -c; \
	else \
		if [ -x "`which php`" ]; \
			then echo php -Cq $(srcdir)/test/framework/driver.php -c; \
			php -Cq $(srcdir)/test/framework/driver.php -c; \
		else \
			echo PHP support required for test; \
		fi \
	fi


# Generate tags for the test framework.
ETAGS_ARGS=--recurse test/framework
