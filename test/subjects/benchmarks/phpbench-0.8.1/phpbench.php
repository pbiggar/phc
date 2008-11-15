#! /usr/bin/env php
<?php

ignore_user_abort(TRUE);
error_reporting(E_ALL);
set_time_limit(0);
ob_implicit_flush(1);

define('PHPBENCH_VERSION', '0.8.1');
define('CSV_SEP', ',');
define('CSV_NL', "\n");
define('DEFAULT_BASE', 100000);
define('MIN_BASE', 50);

$TESTS_DIRS = array('/usr/local/lib/phpbench/tests',
		    '/usr/local/share/phpbench/tests',
		    '/usr/lib/phpbench/tests',
		    '/usr/share/phpbench/tests',
		    '/opt/phpbench/tests',		    
		    'tests',
		    'test/subjects/3rdparty/benchmarks/phpbench-0.8.1/tests',
		    '.');

function test_start($func) {
    global $GLOBAL_TEST_FUNC;
    global $GLOBAL_TEST_START_TIME;    

    $GLOBAL_TEST_FUNC = $func;
    echo sprintf('%34s', $func) . "\t";
    flush();
    list($usec, $sec) = explode(' ', microtime());
    $GLOBAL_TEST_START_TIME = $usec + $sec;    
}

function test_end($func) {
    global $GLOBAL_TEST_FUNC;
    global $GLOBAL_TEST_START_TIME;    

    list($usec, $sec) = explode(' ', microtime());
    $now = $usec + $sec;
    if ($func !== $GLOBAL_TEST_FUNC) {
	trigger_error('Wrong func: [' . $func . '] ' .
		      'vs ' . $GLOBAL_TEST_FUNC);
	return FALSE;
    }
    if ($now < $GLOBAL_TEST_START_TIME) {
	trigger_error('Wrong func: [' . $func . '] ' .
		      'vs ' . $GLOBAL_TEST_FUNC);
	return FALSE;
    }
    $duration = $now - $GLOBAL_TEST_START_TIME;
    echo sprintf('%9.04f', $duration) . ' seconds.' . "\n";
    
    return $duration;
}

function test_regression($func) {
    trigger_error('* REGRESSION * [' . $func . ']' . "\n");
    die();
}

function do_tests($base, &$tests_list, &$results) {
    foreach ($tests_list as $test) {
	$results[$test] = call_user_func($test, $base, $results);	
    }
}

// since we're not able to really detect these, we need to copy it in manually
include_once ("tests/test_arithmetic.php");
include_once ("tests/test_array_operators.php");
include_once ("tests/test_bitwise.php");
include_once ("tests/test_casting.php");
include_once ("tests/test_chr_fixed.php");
include_once ("tests/test_chr_hardcoded.php");
include_once ("tests/test_chr_var.php");
include_once ("tests/test_comment_loop.php");
include_once ("tests/test_compare.php");
include_once ("tests/test_compare_false.php");
include_once ("tests/test_compare_invert.php");
include_once ("tests/test_compare_strict.php");
include_once ("tests/test_compare_unstrict.php");
include_once ("tests/test_constants.php");
include_once ("tests/test_crc32.php");
include_once ("tests/test_do_while.php");
include_once ("tests/test_do_while_break.php");
include_once ("tests/test_empty.php");
include_once ("tests/test_empty_loop.php");
include_once ("tests/test_ereg.php");
include_once ("tests/test_foreach.php");
include_once ("tests/test_get_class.php");
include_once ("tests/test_global_scalar_assign.php");
include_once ("tests/test_global_string_assign.php");
include_once ("tests/test_if_constant.php");
include_once ("tests/test_increment.php");
include_once ("tests/test_is_array.php");
include_once ("tests/test_is_object.php");
include_once ("tests/test_is_type.php");
include_once ("tests/test_isset.php");
include_once ("tests/test_line.php");
include_once ("tests/test_local_array_assign.php");
include_once ("tests/test_local_boolean_assign.php");
include_once ("tests/test_local_float_assign.php");
include_once ("tests/test_local_hash_assign.php");
include_once ("tests/test_local_integer_assign.php");
include_once ("tests/test_local_object_assign.php");
include_once ("tests/test_local_scalar_assign.php");
include_once ("tests/test_local_string_assign.php");
include_once ("tests/test_md5.php");
include_once ("tests/test_microtime.php");
include_once ("tests/test_mt_rand.php");
include_once ("tests/test_ord.php");
include_once ("tests/test_ordered_functions.php");
include_once ("tests/test_ordered_functions_references.php");
include_once ("tests/test_preg_match.php");
include_once ("tests/test_rand.php");
include_once ("tests/test_references.php");
include_once ("tests/test_sha1.php");
include_once ("tests/test_string_append.php");
include_once ("tests/test_strlen.php");
include_once ("tests/test_switch.php");
include_once ("tests/test_time.php");
include_once ("tests/test_unordered_functions.php");
include_once ("tests/test_variable_variables.php");
include_once ("tests/test_while.php");

function load_test($tests_dir, &$tests_list) {
    if (($dir = @opendir($tests_dir)) === FALSE) {
	return FALSE;
    }
    $matches = array();
    while (($entry = readdir($dir)) !== FALSE) {
	if (preg_match('/^(test_.+)[.]php$/i', $entry, $matches) <= 0) {
	    continue;
	}
	$test_name = $matches[1];
//	include_once($tests_dir . '/' . $entry);
// load them elsewhere
	echo 'Test [' . $test_name . '] ';
	flush();
	if (!function_exists($test_name . '_enabled')) {
	    echo 'INVALID !' . "\n";	    
	    continue;
	}
	if (call_user_func($test_name . '_enabled') !== TRUE) {
	    echo 'disabled.' . "\n";
	    continue;
	}
	if (!function_exists($test_name)) {
	    echo 'BROKEN !' . "\n";
	    continue;
	}
	array_push($tests_list, $test_name);	
	echo 'enabled.' . "\n";
    }
    closedir($dir);
    
    return TRUE;	  
}

function load_tests(&$tests_dirs, &$tests_list) {
    $ret = FALSE;
    
    foreach ($tests_dirs as $tests_dir) {
	if (load_test($tests_dir, $tests_list) === TRUE) {
	    $ret = TRUE;
	}
    }
    if (count($tests_list) <= 0) {
	return FALSE;
    }
    asort($tests_list);
    
    return $ret;
}

function csv_escape($str) {
    if (strchr($str, CSV_SEP) !== FALSE) {
	return '"' . str_replace('"', '\'', $str) . '"';
    }
    return $str;
}

function export_csv($csv_file, &$results, &$percentile_times) {
    if (empty($csv_file)) {
	return TRUE;
    }
    if (($fp = fopen($csv_file, 'w')) === FALSE) {
	return FALSE;
    }
    if (fputs($fp, csv_escape('Test') . CSV_SEP . csv_escape('Time') . CSV_SEP .
	      csv_escape('Percentile') . CSV_NL)
	=== FALSE) {
	@fclose($fp);
	unlink($csv_file);
	return FALSE;
    }
    foreach ($results as $test => $time) {
	if (fputs($fp, csv_escape($test) . CSV_SEP .
		  csv_escape(sprintf('%.04f', $time)) . CSV_SEP .
		  csv_escape(sprintf('%.03f', $percentile_times[$test])) .
		  CSV_NL) === FALSE) {
	    @fclose($fp);
	    unlink($csv_file);
	    return FALSE;
	}
    }
    if (fclose($fp) === FALSE) {
	return FALSE;
    }    
    return TRUE;
}

function show_summary($base, &$results, $csv_file) {
    $total_time = 0.0;
    foreach ($results as $test => $time) {
	$total_time += $time;
    }
    if ($total_time <= 0.0) {
	die('Not enough iterations, please try with more.' . "\n");
    }
    $percentile_times = array();
    foreach ($results as $test => $time) {
	$percentile_times[$test] = $time * 100.0 / $total_time;
    }
    $score = (float) $base * 10.0 / $total_time;
    if (function_exists('php_uname')) {
	echo 'System     : ' . php_uname() . "\n";
    }
    if (function_exists('phpversion')) {
	echo 'PHP version: ' . phpversion() . "\n";
    }
    echo
      'PHPBench   : ' . PHPBENCH_VERSION . "\n" .
      'Date       : ' . date('F j, Y, g:i a') . "\n" .
      'Tests      : ' . count($results) . "\n" .
      'Iterations : ' . $base . "\n" .
      'Total time : ' . round($total_time) . ' seconds' . "\n" .
      'Score      : ' . round($score) . ' (higher is better)' . "\n";
    
    if ($csv_file !== FALSE) {
	export_csv($csv_file, $results, $percentile_times);
    }
}

function help() {
    global $TESTS_DIRS;
    
    echo
      "\n" . 'PHPBench version ' . PHPBENCH_VERSION . "\n\n" .
      '-f <file name> : Output a summary as a CSV file.' . "\n" .
      '-h             : Help.' . "\n" .
      '-i <number>    : Number of iterations (default=' . DEFAULT_BASE . ').' .
      "\n\n" .
      'Scripts are loaded from the following directories: ' . "\n";    
    foreach ($TESTS_DIRS as $tests_dir) {
	echo '  - ' . $tests_dir . "\n";
    }
    echo "\n";
}

$base = DEFAULT_BASE;
$csv_file = FALSE;

$options = getopt('f:hi:');
if (isset($options['h'])) {
    help();
    exit;
}
if (!empty($options['f'])) {
    $csv_file = $options['f'];
    if (preg_match('/[.]csv$/i', $csv_file) <= 0) {
	$csv_file .= '.csv';
    }
}
if (!empty($options['i']) && is_numeric($options['i'])) {
    $base = $options['i'];
}
if ($base < MIN_BASE) {
    die('Min iterations = ' . MIN_BASE . "\n");
}
if (empty($options)) {
    help();
}
echo 'Starting the benchmark with ' . $base . ' iterations.' . "\n\n";
$tests_list = array();
$results = array();
if (load_tests($TESTS_DIRS, $tests_list) === FALSE) {
    die('Unable to load tests');
}
echo "\n";
do_tests($base, $tests_list, $results);
echo "\n";
show_summary($base, $results, $csv_file);
echo "\n";

?>
