<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Base class for tests
 */

abstract class Test
{
	function __construct ()
	{
		$this->successes = 0;
		$this->failures = 0;
		$this->skipped = 0;
		$this->total = 0;
		$this->expected_failure_count = 0;
		$this->timers = array();
	}

	// override this function if your test takes ages
	function get_time_limit ()
	{
		// basic_parse_tests take 20 seconds on my machine.
		return 120;
	}

	function get_name ()
	{
		return get_class($this);
	}

	function ready_progress_bar ($num_files)
	{
		global $opt_no_progress_bar;
		$this->num_files = $num_files;
		if (!$opt_no_progress_bar)
		{
			// this line is irrelevent, since it's reset below 
			$this->progress_bar = new Console_ProgressBar (
				$this->get_name()."%bar% Testing (%fraction%)",
				"#", "-", 80, $num_files); 
		}
		$this->update_count(0);
	}

	function homogenize_output ($string)
	{
		return $string;
	}

	function check_global_prerequisites ()
	{
		global $php;
		return check_for_program ($php);
	}

	function check_prerequisites ()
	{
		return true;
	}

	function check_test_prerequisites ($subject)
	{
		return true;
	}

	function get_dependent_test_names ()
	{
		return array ();
	}

	// we dont want this to be overridden
	function get_builtin_dependent_test_names ()
	{
		if (!isset($this->dependencies))
			return array ();

		return (array) ($this->dependencies);
	}

	function calculate_all_dependencies ()
	{
		global $tests;
		$dependencies = $this->get_builtin_dependent_test_names () 
				+ $this->get_dependent_test_names ();

		# we want deep dependencies here, so get the parent dependencies too
		$all_dependencies = array ();
		foreach ($dependencies as $dependency)
		{
			$all_dependencies[] = $dependency;
			foreach ($tests as $test) # find it in the set of tests
			{
				if ($test->get_name () == $dependency)
				{
					foreach ($test->get_all_dependencies() as $new_dependency)
						$all_dependencies[] = $new_dependency;
					break;
				}
			}
		}
		$this->all_dependencies = $all_dependencies;
	}

	function get_all_dependencies ()
	{
		if (isset($this->all_dependencies))
			return $this->all_dependencies;

		$this->calculate_all_dependencies ();
		return $this->all_dependencies;
	}

	function passed_test_dependencies ($subject)
	{
		$shallow_dependencies = $this->get_all_dependencies ();

		# we want deep dependencies here, so get the parent dependencies too
		$dependencies = array ();
		global $tests;
		while ($shallow_dependencies)
		{
			$dependency = array_pop ($shallow_dependencies);
			$dependencies[] = $dependency;
			foreach ($tests as $test) # find it in the set of tests
			{
				if ($test->get_name () == $dependency)
				{
					foreach ($test->get_all_dependencies() as $new_dependency)
						$shallow_dependencies[] = $new_dependency;
					break;
				}
			}
		}

		foreach ($dependencies as $dependency)
		{
			$depend = read_dependency ($dependency, $subject);
			if ($depend == "Fail")
				return false;
			elseif ($depend == "missing")
				$this->missing_dependency = $dependency;
		}
		return true;
	}

	abstract function run_test ($subject);
	abstract function get_test_subjects ();

	function print_numbered ()
	{
		$files = $this->get_test_subjects();
		$i = 1;
		foreach ($files as $file)
		{
			print "$i. $file\n";
			$i++;
		}
	}

	function run()
	{
		// increase the timelimit
		$time_limit = ini_get('max_execution_time');
		set_time_limit ($time_limit + $this->get_time_limit ());

		// do this first so that the progress bar is ready
		$files = $this->get_test_subjects ();
		$this->ready_progress_bar (count ($files));


		if (!$this->check_prerequisites () || !$this->check_global_prerequisites ())
		{
			$this->mark_skipped ("All", "Test prerequisties failed");
			$this->finish_test ();
			return false;
		}

		// end early if specified
		global $opt_quick;
		$count = 0;

		foreach ($files as $subject)
		{
			if (!$this->check_test_prerequisites ($subject))
			{
				$this->mark_skipped ($subject, "Individual prerequsite failed");
			}
			elseif (!$this->passed_test_dependencies ($subject))
			{
				$this->mark_skipped ($subject, "Test failed dependency");
			}
			elseif ($this->check_exception ($subject))
			{
				$this->mark_skipped ($subject, "Test excepted");
			}
			else
			{
				$this->start_timer ($subject);
				$this->run_test ($subject);
				$this->end_timer ($subject);
			}
			$count ++;

			if ($opt_quick && $count >= 10)
				break;
		}

		$this->finish_test ();
	}

	function start_timer ($subject)
	{
		$this->timer_start = microtime(true);
	}

	function end_timer ($subject)
	{
		$time = microtime (true) - $this->timer_start;
		$this->timers[$subject] = $time;
	}

	function get_timing_string ()
	{
		if (count ($this->timers) == 0) return "";
		$blue = blue_string();
		$red = red_string();
		$reset = reset_string ();
		asort($this->timers, SORT_NUMERIC);
		$numbers = array();

		// need the number to address it
		$i = 0;
		$files = $this->get_test_subjects ();
		foreach ($files as $file)
		{
			$numbers{$file} = $i;
			$i++;
		}

		// get the median (you cant just index with ints)
		$i = 0;
		foreach ($this->timers as $key => $value)
		{
			if ($i++ >= count($this->timers) / 2)
			{
				$med_val = $value;
				$med_key = $numbers{$key};
				break;
			}
		}

		// get the mean
		$total = 0;
		foreach ($this->timers as $key => $value)
		{
			$total += $value;
		}
		$mean = $total / count ($this->timers);

		// get the std dev
		$total = 0;
		foreach ($this->timers as $key => $value)
		{
			$dev = $value - $mean;
			$total += ($dev * $dev);
		}
		$std_dev = sqrt ($total / (count ($this->timers)));

		// get the max
		$max_val = array_pop(array_values($this->timers));
		$max_key = $numbers{array_pop(array_keys($this->timers))};

		// more than a second apart, and 2 std deviations above average
		if (($max_val > ($mean + 2*$std_dev))
				and ($max_val > $mean + 1))
		{
			return sprintf ("{$blue}avg %2ss; {$red}max%5s%3ss$reset", 
					floor($mean), "($max_key)", floor($max_val));
		}
		else
		{
			return sprintf ("{$blue}avg %2ss$reset              ", floor($mean));
		}

	}

	function mark_success ($subject)
	{
		write_dependencies ($this->get_name (), $subject, true);

		$this->successes++;
		$this->total++;
		$this->update_count ();
		log_status ("success", $this->get_name(), $subject, "");
	}

	function mark_skipped ($subject, $reason)
	{
		if ($subject == "All")
		{
			$this->skipped += count($this->get_test_subjects ());
			$this->total = $this->skipped;
		}
		else
		{
			$this->skipped++;
			$this->total++;
		}
		write_dependencies ($this->get_name (), $subject, false);
		log_status ("skipped", $this->get_name(), $subject, $reason);
		$this->update_count ();
	}

	function mark_failure ($subject, $commands, $exits = "Not relevent", $out = "Not relevent", $errs = "Not relevent")
	{
		$reason = "TODO";
		global $log_directory;

		write_dependencies ($this->get_name (), $subject, false);
		$dependency_string = "";
		if (isset ($this->missing_dependency))
		{
			$dependency_string = "NOTE: dependency {$this->missing_dependency} is missing. This may be the cause of this failure\n";
		}

		$red = red_string();
		$reset = reset_string();

		// we have 1 or more outputs, only 1 error, and 1 or more commands, with the same number of error codes as commands
		$err_string = "";
		if (is_array ($commands))
		{
			if ($exits == "Not relevent")
			{
				$command_string = "";
				foreach ($commands as $command)
				{
					$command_string .= "{$red}Command:$reset $command\n";
				}
			}
			else
			{
				phc_assert (is_array ($exits), "Expected array of return values");
				phc_assert (count ($exits) == count ($errs), 
					"Expected same number of exits as exit codes");
				$command_string = "";
				$err_string = "";
				foreach ($exits as $i => $exit)
				{
					$command = $commands[$i];
					$err = $errs [$i];
					$command_string .= "{$red}Command $i$reset ($exit): $command\n";
					if ($err)
						$err_string .= "{$red}Error $i$reset: $err\n";
				}
			}

		}
		else
		{
			$command_string = "{$red}Command$reset ($exits): $commands\n";
			if ($errs)
				$err_string = "{$red}Error$reset: $errs\n";
		}

		$command_string = $dependency_string.$command_string.$err_string;
		if (is_array ($out))
		{
			$out = join ("\n", $out);
		}

		log_failure ($this->get_name(), $subject, $command_string, $out);
		log_status ("failure", $this->get_name(), $subject, $reason);
		$this->erase_progress_bar();

		$this->display_progress_bar ();

		$this->failures++;
		$this->total++;
		$this->update_count ();
	}

	function is_successful ()
	{
		return ($this->failures == 0);
	}

	function is_completely_skipped ()
	{
		return ($this->failures == 0 and $this->successes == 0 and $this->skipped > 0);
	}

	function get_appropriate_colour ()
	{
		if ($this->is_completely_skipped ())
			return blue_string ();
		elseif ($this->is_successful ())
			return green_string ();
		else
			return red_string ();
	}

	function get_appropriate_phrase ()
	{
		if ($this->is_completely_skipped ())
			return "Skipped";
		elseif ($this->is_successful ())
			return "Success";
		else
			return "Failure";
	}

	function get_triple_string ($finished = false)
	{
		$reset = reset_string ();
		$passed = sprintf ("%5s", $this->successes." P");
		$failed = sprintf ("%5s", $this->failures." F");
		$skipped = sprintf ("%5s", $this->skipped." S");
		if ($finished)
		{
			$colour = $this->get_appropriate_colour ();
			return "$colour$passed, $failed, $skipped$reset";
		}
		else
		{
			$blue = blue_string ();
			$green = green_string ();
			$red = red_string ();
			$reset = reset_string ();
			return "$green$passed$reset, $red$failed$reset, $blue$skipped$reset";
		}
	}

	function update_count ()
	{
		global $opt_no_progress_bar;
		if (! $opt_no_progress_bar)
		{
			# check for divide by zero
			$target_num = $this->num_files;
			if ($target_num == 0) $target_num = 1;

			$this->erase_progress_bar ();
			$this->progress_bar->reset(
					"{$this->get_name()} %bar% %fraction%: {$this->get_triple_string ()}", 
					"#", "-", 112, $target_num); # i dont understand how this number works, but it includes control chars
			$this->progress_bar->update($this->total);
		}
	}

	function erase_progress_bar ()
	{
		global $opt_no_progress_bar;
		if (! $opt_no_progress_bar)
		{
			$this->progress_bar->erase();
		}
	}

	function display_progress_bar ()
	{
		global $opt_no_progress_bar;
		if (! $opt_no_progress_bar)
		{
			$this->progress_bar->display($this->total);
		}
	}

	function finish_test ()
	{
		$this->erase_progress_bar();

		$red = red_string ();
		$blue = blue_string ();
		$green = green_string ();
		$reset = reset_string ();

		$test = $this->get_name();
		$timing = $this->get_timing_string ();
		$triple = $this->get_triple_string (true);

		$phrase = $this->get_appropriate_phrase ();
		$colour = $this->get_appropriate_colour ();
		$word = "$colour$phrase:$reset";

		// a color or a reset involves 6 characters, but gets displayed as zero.
		// Those 6 need to be taken into account for sprintf
		$string = sprintf("%-27s %-22s %20s %28s", $test, $timing, $word, $triple);
		print "$string\n";
	}

	// return true if the subject is marked as an exception
	function check_exception ($subject)
	{
		global $exceptions;
		if (!isset($exceptions{$this->get_name()})) return false;
		$array = $exceptions{$this->get_name()};
		assert (is_array ($array));
		return (in_array ($subject, $array));
	}
}


?>
