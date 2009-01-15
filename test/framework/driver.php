<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Run the tests
 */

// when dealing with the manual, we need more space
ini_set("memory_limit","256M");
ini_set("include_path","test/framework/external/:". get_include_path());

// check version of php
if (substr (phpversion (), 0, 1) < 5)
{
	die("Tests skipped (PHP version 5 required)\n");
}

$support_dir =	"test/support_files";
$plugin_dir =	"plugins";

require_once ("lib/header.php");

// setup log dir
$log_directory =	"test/logs/".date_string ();
mkdir ($log_directory);
@unlink ("test/logs/latest");
symlink ($log_directory, "test/logs/latest");
print ("Logs in:      $log_directory\n");

//setup working dir
$working_directory =	"test/working/".date_string ();
mkdir ($working_directory);
@unlink ("test/working/latest");
symlink ($working_directory, "test/working/latest");
mkdir ("$working_directory/.libs"); // avoid 'File exists' errors
print ("Working from: $working_directory\n");

require_once ("lib/startup.php");
require_once ("lib/autovars.php");

if ($opt_clean)
{
	echo "rm -Rf ./test/logs/*\n";
	`rm -Rf ./test/logs/*`;
	echo "rm -Rf ./test/working/*\n";
	`rm -Rf ./test/working/*`;
	exit (0);
}

open_status_files ();

$php = get_php ();
$base_dir = getcwd();
if ($opt_installed)
{
	// Make it so we cant rely on anything that's installed
	$phc = "$bindir/phc";
	$plugin_dir = "$pkglibdir/plugins";
	$phc_compile_plugin = "$bindir/phc_compile_plugin";
	$trunk_CPPFLAGS = ""; // we use these for compiling plugins with phc_compile_plugin
	$pwd = getcwd ();
	$dir = sys_get_temp_dir()."/phc-test-".getmypid();
	echo `rm -Rf $dir`;
	mkdir ($dir);
	chdir ($dir);
	echo `ln -s $pwd/test test`;
	echo "Running from: ".getcwd()."\n";
}
else
{
	// setup globals
	$phc = get_phc ();
	$phc_compile_plugin = get_phc_compile_plugin ();
}

require_once ("lib/compare_with_php_test.php");
require_once ("lib/plugin_test.php");
require_once ("lib/regression.php");
require_once ("lib/compare_backwards.php");
require_once ("lib/pass_dump.php");

// Add tests to list
$tests = array ();

require_once ("annotated_test.php");
require_once ("basic_parse_test.php");
require_once ("no_whitespace.php");
$tests[] = new CompareBackwards ("ast");
$tests[] = new CompareBackwards ("sua",			"dump",	"cb_ast");
$tests[] = new CompareBackwards ("AST-to-HIR",	"dump",	"cb_sua");
$tests[] = new CompareBackwards ("hir",			"dump",	"cb_AST-to-HIR");
// if it needs to be uppered, check it doesnt segfault while dumping normally
$tests[] = new CompareBackwards ("mir",			"dump-uppered",	"cb_hir");
$tests[] = new Pass_dump (			"HIR-to-MIR",	"dump",	"cb_hir");
$tests[] = new Pass_dump (			"mir",			"dump",	"cb_mir");
$tests[] = new CompareWithPHP ("InterpretOptimized", "-O1 --dump-uppered=generate-c", "cb_mir");
$tests[] = new CompareWithPHP ("InterpretCanonicalUnparsed", "--run plugins/tests/canonical_unparser.la", "BasicParseTest"); // not necessarily dependent of InterpretUnparsed
$tests[] = new CompareWithPHP ("InterpretStrippedIncludes", "--include --dump=sua --run plugins/tests/strip_includes.la", "cb_sua");
$tests[] = new CompareWithPHP ("InterpretObfuscated", "--obfuscate", "cb_mir");
require_once ("generate_c.php");
require_once ("compiled_vs_interpreted.php");
require_once ("compile_optimized.php");
require_once ("refcounts.php");
require_once ("demi_eval.php");
$tests[] = new PluginTest ("inconsistent_st_attr");
$tests[] = new PluginTest ("linear");
$tests[] = new PluginTest ("cloning");
$tests[] = new PluginTest ("pre_vs_post_count");
require_once ("reparse_unparsed.php");
require_once ("source_vs_semantic_values.php"); // dont use plugin_test here
require_once ("xml_roundtrip.php"); // dont use plugin_test here
require_once ("compile_plugin_test.php");
require_once ("line_numbers.php");
require_once ("parse_ast_dot.php");
$tests[] = new RegressionTest ("regression_dump_ast", "--dump-dot=ast", "dot");
$tests[] = new RegressionTest ("regression_dump_php", "--pretty-print --tab=\"   \"", "unparsed");
$tests[] = new RegressionTest ("regression_dump_xml", "--dump-xml=ast --dump-xml=hir --dump-xml=mir", "unparsed");



// Run the tests
foreach ($tests as $test)
{
	$test_name = $test->get_name ();

	/* if there are regexes, check them, and skip tests not matching one of them */
	if (count ($arguments) > 0)
	{
		$match = false;
		foreach ($arguments as $regex)
		{
			if (preg_match ("/$regex/", $test_name)) $match = true;
		}

		if (!$match)
		{
			//	print "Skipping $test_name\n";
			continue;
		}
	}

	if ($opt_support)
	{ 
		if (method_exists ($test, "generate_support_files"))
		{
			$test->generate_support_files ();
		}
	}
	elseif ($opt_numbered)
	{
		$test->print_numbered ();
	}
	else $test->run ();
}
close_status_files ();

?>
