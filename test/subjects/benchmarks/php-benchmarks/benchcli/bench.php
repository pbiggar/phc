<?php
// +----------------------------------------------------------------------+
// | PHP Version 5                                                        |
// +----------------------------------------------------------------------+
// | Copyright (c) 2009 The PHP Group                                     |
// +----------------------------------------------------------------------+
// | This source file is subject to version 3.0 of the PHP license,       |
// | that is available through the world-wide-web at the following url:   |
// | http://www.php.net/license/3_0.txt.                                  |
// | If you were unable to obtain it  though the world-wide-web, please   |
// | send a note to license@php.net so we can mail you a copy immediately |
// +----------------------------------------------------------------------+
// | Author: Alexander Hjalmarsson <hjalle@php.net>                       |
// +----------------------------------------------------------------------+
//

/**
 * This benchmark measures the performance of PHP
 * Example of usage:
 * bench.php --log log.txt -d -m 256
 *
 * @author    Alexander Hjalmarsson <hjalle@php.net>
 * @copyright 2009
 * @license   http://www.php.net/license/3_0.txt PHP License 3.0
 */


error_reporting(E_ALL | E_NOTICE);
set_time_limit(0);
/**
 * This is the main class of the benchmark script
 */
class Benchmark
{
    /**
     * Maximum memory usage for php test files.
     * @var int
     */
    var $memory_limit;

    /**
     * Debug switch
     * @var boolean
     */
    var $debug;

    /**
     * Directories to search for php test files.
     * @var array
     */
    var $include;

    /**
     * Path to the php binary
     * @var string
     */
    var $php;

    /**
     * The config for command line arguments
     * @var array
     */
    var $config;

    /**
     * The log file for output
     * @var string
     */
    var $log_file;

    /**
     * Produce output or not
     */
    var $quite;

    /**
     * Holds the test files that will be tested
     * @var array
     */
    var $test_files;


    /**
     * Whether cachegrind should be used or not
     * @var boolean
     */
    var $cachegrind;

    /**
     * Class for parsing and sorting Smaps-files
     * @var object
     */
    var $smapsparser;

    /**
     * Switch for showing memory usage or not
     * @var boolean
     */
    var $mem_usage;

    /**
     * Constructor for the benchmark class. Uses the PEAR package
     * Console_getargs for command line handling.
     *
     * @return void
     */
    function Benchmark()
    {
        include_once 'misc/getargs.php';
        include_once 'misc/timer.php';
        include_once 'misc/smapsparser.php';
        include_once 'misc/cachegrindparser.php';
        $this->setConfig();
        $args              = &Console_Getargs::factory($this->config);
        $this->smapsparser = new Smapsparser();
        if (PEAR::isError($args) || $args->getValue('help')) {
            $this->printHelp($args);
            exit;
        }

        $this->debug        = $args->getValue('debug');
        $this->memory_limit = $args->getValue('memory-limit');
        if ($this->memory_limit == "") {
            $this->memory_limit = 128;
        }
        $this->include = $args->getValue('include');
        if (is_array($this->include)) {
            $this->include[] = "tests"; // Append default directory
        } else {
            //user has one directory as input, therefore
            //$this->include is recognized as a string
            $tmpdir          = $this->include;
            $this->include   = array();
            $this->include[] = $tmpdir;
            $this->include[] = "tests";
        }
        $this->php = $args->getValue('php');
        if ($this->php == "") {
            $this->php = "php";
        }
        $this->log_file = $args->getValue('log');
        if ($this->log_file == "") {
            $this->log_file = false;
        }
        $this->quite      = $args->getValue('quite');
        $this->mem_usage  = $args->getValue('memory-usage');
        $this->cachegrind = $args->getValue('cachegrind');
        $this->setTestFiles();
    }
    /**
     * Prints message to the screen
     *
     * @param string $msg   The message to print
     * @param bool   $print Whether to print or not print
     *
     * @return void
     */
    function console($msg, $print=true)
    {
        if (!$this->quite) {
            if ($print) {
                echo $msg;
            }
        }
        if ($this->log_file && $print) {
            file_put_contents($this->log_file, $msg, FILE_APPEND);
        }
    }

    /**
     *	Sets the config for command line arguments
     *
     *  @return void
     */
    function setConfig()
    {
        $this->config = array(
            'memory-limit' => array('short' => 'ml',
                     'min' => 0,
                     'max' => 1,
                 'default' => 128,
                    'desc' => 'Set the maximum memory usage.'),
            'debug'        => array('short' => 'd',
                     'max' => 0,
                    'desc' => 'Switch to debug mode.'),
            'include'      => array('min' => 0,
                     'max' => -1,
                    'desc' => 'Include additional test directories'),
            'help'         => array('short' => 'h',
                     'max' => 0,
                    'desc' => 'Print this help message'),
            'php'          => array('min' => 0,
                     'max' => 1,
                 'default' => 'php',
                    'desc' => 'PHP binary path'),
            'quite'        => array('short' => 'q',
                     'max' => 0,
                    'desc' => 'Don\'t produce any output'),
            'memory-usage' => array('short' => 'mu',
                     'max' => 0,
                    'desc' => 'Show memory statistics. This requires linux with kernel 2.6.14 or newer'),
            'cachegrind'   => array('max' => 0,
                    'desc' => 'Enable the valgrind tool that a cache simulation of the test'),
            'log'          => array('min' => 0,
                     'max' => 1,
                 'default' => 'benchlog.txt',
                    'desc' => 'Log file path')
        );
    }

    /**
     *	Prints the help message for the benchmark
     *
     *  @param array $args The arguments to be listed
     *
     *  @return void
     */
    function printHelp($args)
    {
        $header = "Php Benchmark Example\n".
              'Usage: '.basename($_SERVER['SCRIPT_NAME'])." [options]\n\n";
        if ($args->getCode() === CONSOLE_GETARGS_ERROR_USER) {
            echo Console_Getargs::getHelp($this->config, $header, $args->getMessage())."\n";
        } else if ($args->getCode() === CONSOLE_GETARGS_HELP) {
            echo Console_Getargs::getHelp($this->config, $header)."\n";
        }
    }
    /**
     * Return an array with all the paths to the test files found
     * from the array of directories to search. It searches for files
     * with the structure of test_*.php. It then strips the full path
     * so the elements in the returning array will hold both the full
     * path and the name of the script.
     * Example:
     *
     * A file called test_array.php that lies in /home/user/tests can
     * make the returning array look like this:
     *
     * array([0] => array (	 [filename] => "/home/user/tests/test_array.php",
     * 						 [name]	    => "array.php")
     * );
     *
     * @return void
     */
    function setTestFiles()
    {
        $files = array();
        foreach ($this->include as $dir) {
            foreach (glob("$dir/test_*.php") as $filename) {
                $t['filename'] = $filename;
                preg_match('/test_(.+)[.]php$/i', $filename, $matches);
                $t['name'] = $matches[1];
                $files[]   = $t;
            }
        }
        $this->test_files = $files;
    }

    /**
     * Runs the benchmark
     *
     * @return void
     */
    function run()
    {
        $timer       = new Timer();
        $totaltime   = 0;
        $datetime    = date("Y-m-d H:i:s", time());
        $startstring = "";
        $this->console("--------------- Bench.php ".$datetime."--------------\n");

        foreach ($this->test_files as $test) {
            $output = array();
            if ($this->cachegrind) {
                $startstring = "valgrind --tool=cachegrind --branch-sim=yes";
            }
            $cmd = "$startstring {$this->php} -d memory_limit={$this->memory_limit}M ".$test['filename'];
            $this->console("$cmd\n", $this->debug);
            $timer->start();
            list($out, $err, $exit) = $this->completeExec($cmd, null, 0);
            if ($this->mem_usage) {
                if (!$this->quite) {
                    $this->smapsparser->printMaxUsage(10);
                }
                if ($this->log_file) {
                    $this->smapsparser->printMaxUsage(10, $this->log_file);
                }
                $this->smapsparser->clear();
            }
            if ($this->cachegrind) {
                $cacheparser = new Cachegrindparser();
                $result      = $cacheparser->parse($err);
                print_r($result);
            }
            $timer->stop();
            $this->console($out, $this->debug);
            $this->console("Results from ".$test['name'].": ".$timer->elapsed."\n");
            $totaltime += $timer->elapsed;
        }

        $this->console("Total time for the benchmark: ".$totaltime." seconds\n");

        $datetime = date("Y-m-d H:i:s", time());
        $this->console("-------------- END ".$datetime."---------------------\n");
    }
    /**
     * Executes a program in proper way. The function is borrowed 
     * the php compiler project, http://www.phpcompiler.org.
     *
     * @param string $command The command to be executed
     * @param string $stdin   stdin
     * @param int    $timeout Seconds until it timeouts
     *
     * @return array
     */
    function completeExec($command, $stdin = null, $timeout = 20)
    {
        $descriptorspec = array(0 => array("pipe", "r"),
        1 => array("pipe", "w"),
        2 => array("pipe", "w"));
        $pipes          = array();
        $handle         = proc_open($command, $descriptorspec, &$pipes, getcwd());

        // read stdin into the process
        if ($stdin !== null) {
            fwrite($pipes[0], $stdin);
        }
        fclose($pipes[0]);
        unset($pipes[0]);

        // set non blocking to avoid infinite loops on stuck programs
        stream_set_blocking($pipes[1], 0);
        stream_set_blocking($pipes[2], 0);

        $out = "";
        $err = "";

        $start_time = time();
        do {
            $status = proc_get_status($handle);
            // It seems that with a large amount fo output, the process
            // won't finish unless the buffers are periodically cleared.
            // (This doesn't seem to be the case is async_test. I don't
            // know why).
            $new_out = stream_get_contents($pipes[1]);
            $new_err = stream_get_contents($pipes[2]);
            $out    .= $new_out;
            $err    .= $new_err;
            $pid     = $this->getChildren($handle, $pipes);
            if ($this->mem_usage) {
                if ($data = $this->smapsparser->readSmapsData($pid[0])) {
                    $this->smapsparser->parseSmapsData($data);
                }
            }
            if ($timeout != 0 && time() > $start_time + $timeout) {
                $out = stream_get_contents($pipes[1]);
                $err = stream_get_contents($pipes[2]);

                $this->killProperly($handle, $pipes);

                return array("Timeout", $out, $err);
            }

            // Since we use non-blocking, the for loop could well take 100%
            // CPU. time of 1000 - 10000 seems OK. 100000 slows down the
            // program by 50%.
            usleep(7000);
        } while ($status["running"]);
        stream_set_blocking($pipes[1], 1);
        stream_set_blocking($pipes[2], 1);
        $out .= stream_get_contents($pipes[1]);
        $err .= stream_get_contents($pipes[2]);

        $exit_code = $status["exitcode"];
        $this->killProperly($handle, $pipes);

        return array($out, $err, $exit_code);

    }
    /**
     * Get's the child processes of a shell execution.
	 *
     * @param handler &$handle The handler
     * @param array   &$pipes  The pipes
     *
     * @return array  All children processes pid-number.
     */
    function getChildren(&$handle, &$pipes)
    {
        $status = proc_get_status($handle);
        $ppid = $status["pid"];
        $pids = preg_split("/\s+/", trim(`ps -o pid --no-heading --ppid $ppid`));
        return $pids;
    }
    /**
     * Kills a process properly
     *
     * @param handler &$handle The handler
     * @param array   &$pipes  The pipes
     *
     * @return void
     */
    function killProperly(&$handle, &$pipes)
    {
        
        // proc_terminate kills the shell process, but won't kill a runaway infinite
        // loop. Get the child processes using ps, before killing the parent.
        $pids = $this->getChildren($handle, $pipes);

        // if we dont close pipes, we can create deadlock, leaving zombie processes.
        foreach ($pipes as &$pipe) {
            fclose($pipe);
        }
        proc_terminate($handle);
        proc_close($handle);

        // Not necessarily available.
        if (function_exists("posix_kill")) {
            foreach ($pids as $pid) {
                if (is_numeric($pid)) {
                    posix_kill($pid, 9);
                }
            }
        }
    }


}

$bench = new Benchmark();
$bench->run();
?>
