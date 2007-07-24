<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Run the tests
 */

// when dealing with the manual, we need more space
ini_set("memory_limit","256M");
ini_set("include_path","test/framework/external/:".ini_get("include_path"));

// check version of php
if (substr (phpversion (), 0, 1) < 5)
{
	die("Tests skipped (PHP version 5 required)\n");
}

$support_dir =		"test/support_files";
$plugin_dir = "plugins";

require_once ("lib/startup.php");
require_once ("lib/header.php");

$log_directory =	"test/logs/".date_string ();

if ($opt_clean)
{
	echo "rm -Rf ./test/logs/*\n";
	`rm -Rf ./test/logs/*`;
	exit (0);
}
else
{
	mkdir ($log_directory);
	@unlink ("test/logs/latest");
	symlink ($log_directory, "test/logs/latest");
}


$phc = get_phc ();
$php = get_php ();
$phc_compile_plugin = get_phc_compile_plugin ();

require_once ("lib/test.php");
require_once ("lib/plugin_test.php");
require_once ("lib/two_command_test.php");
require_once ("lib/compare_with_php_test.php");
require_once ("lib/regression.php");

if ($opt_long)
{
	set_time_limit (300); // 5 mins for long tests should be grand. Note, this is system time, so time spent waiting for blocking external processes doesnt count
}

if ($opt_installed)
{
	$phc = "$bindir/phc";
	$plugin_dir = "$pkglibdir/plugins";
	$phc_compile_plugin = "$bindir/phc_compile_plugin";
	$trunk_CPPFLAGS = ""; // we use these for compiling plugins with phc_compile_plugin
}

$tests = array ();

require_once ("basic_parse_test.php");
$tests[] = new CompareWithPHP ("InterpretUnparsed", "--pretty-print", "BasicParseTest");
$tests[] = new CompareWithPHP ("InterpretCanonicalUnparsed", "--run plugins/tests/canonical_unparser.la", "BasicParseTest"); // not necessarily dependent of InterpretUnparsed
$tests[] = new CompareWithPHP ("InterpretStrippedIncludes", "--udump=hir --run plugins/tests/strip_includes.la", "BasicParseTest");
$tests[] = new CompareWithPHP ("InterpretLoweredCF", "--udump=lcf", "InterpretUnparsed");
$tests[] = new CompareWithPHP ("InterpretLoweredExpr", "--udump=lef", "InterpretLoweredCF");
$tests[] = new CompareWithPHP ("InterpretShredded", "--udump=shred", "InterpretLoweredExpr");
$tests[] = new CompareWithPHP ("InterpretObfuscated", "--obfuscate", "InterpretShredded");
require_once ("generate_c.php");
require_once ("compiled_vs_interpreted.php");
require_once ("refcounts.php");
$tests[] = new PluginTest ("linear");
$tests[] = new PluginTest ("cloning");
$tests[] = new PluginTest ("pre_vs_post_count");
require_once ("reparse_unparsed.php");
require_once ("source_vs_semantic_values.php"); // dont use plugin_test here
require_once ("xml_roundtrip.php"); // dont use plugin_test here
require_once ("compile_plugin_test.php");
require_once ("line_numbers.php");
require_once ("parse_ast_dot.php");
$tests[] = new RegressionTest ("regression_dump_ast", "--ddump=ast", "dot");
$tests[] = new RegressionTest ("regression_dump_php", "--pretty-print --tab=\"   \"", "unparsed");
require_once ("zend_benchmark.php");
#require_once ("roadsend_benchmark.php");
#require_once ("phpbench_benchmark.php");
#require_once ("php_bs_benchmark.php");
#require_once ("shootout_benchmark.php");

require_once ("lib/labels.php");
open_status_files ();

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
