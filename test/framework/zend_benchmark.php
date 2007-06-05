<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Test to run the zend benchmark
 */

$tests[] = new ZendBenchmark ();

class ZendBenchmark extends NoSubjectTest
{
	function run_test ($subject)
	{
		$filename = "test/subjects/3rdparty/benchmarks/zend/bench.php";

		// compile the benchmark with phc
		$name = basename ($filename);
		$this->start_benchmark_timer ("compile_$name");
		$command1 = "src/phc -c $filename";
		list ($out1, $err1, $exit1) = complete_exec ($command1);
		$this->end_benchmark_timer ("compile_$name");
		if ($err1 or $exit1 != 0)
			$this->mark_failure ("compile_$name", $command1, $exit1, $out1, $err1);

		$this->start_benchmark_timer ("php_$name");
		list ($out1, $err1, $exit1) = complete_exec ("php $filename");
		$this->end_benchmark_timer ("php_$name");

				// run the compiled benchmark
		$this->start_benchmark_timer ("a.out_$name");
		list ($out3, $err3, $exit3) = complete_exec ("./a.out");
		$this->end_benchmark_timer ("a.out_$name");
	}

	function start_benchmark_timer ($subject)
	{
		$this->benchmark_timer_start = microtime(true);
	}

	function end_benchmark_timer ($subject)
	{
		$this->benchmark_timers[$subject] = microtime(true) - $this->benchmark_timer_start;
	}
}
