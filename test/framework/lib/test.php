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
		$this->timers = array();
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

	function homogenize_xml ($string)
	{
		$string = preg_replace("/(<attr key=\"phc.line_number\">)\d+(<\/attr>)/", "$1$2", $string);
		$string = preg_replace("/(<attr key=\"phc.filename\">).*?(<\/attr>)/", "$1$2", $string);
		return $string;
	}

	function homogenize_filenames ($string)
	{
		$string = preg_replace("/(Warning: .* in ).* on line \d+/", "$1", $string);
		$string = preg_replace("/(Fatal error: .* in ).* on line \d+/", "$1", $string);
		$string = preg_replace("/(Catchable fatal error:) .* in .* on line \d+/", "$1", $string);
		return $string;
	}

	function homogenize_line_numbers ($string)
	{
		$string = preg_replace("/(Warning: .* in .* on line )\d+/", "$1", $string);
		$string = preg_replace("/(Fatal error: .* in .* on line )\d+/", "$1", $string);
		$string = preg_replace("/(Catchable fatal error: .* in .* on line )\d+/", "$1", $string);
		return $string;
	}

	function homogenize_break_levels ($string)
	{
		$string = preg_replace(	"/Fatal error: Cannot break\/continue \d+ level(s)? in .*/",
										"Fatal error: Too many break/continue levels", $string);
		return $string;
	}

	function check_global_prerequisites ()
	{
		global $php_exe;
		return check_for_program ($php_exe);
	}

	function check_prerequisites ()
	{
		return true;
	}

	function check_test_prerequisites ($subject)
	{
		return true;
	}

	abstract function run_test ($subject);
	abstract function get_test_subjects ();

	function print_numbered ()
	{
		$files = $this->get_test_subjects();
		$i = 0;
		foreach ($files as $file)
		{
			print "$i. $file\n";
			$i++;
		}
	}

	function run()
	{
		// do this first so that the progress bar is ready
		$files = $this->get_test_subjects ();
		$this->ready_progress_bar (count ($files));


		if (!$this->check_prerequisites () || !$this->check_global_prerequisites ())
		{
			$this->mark_skipped ("All", "Test prerequisties failed");
			$this->finish_test ();
			return false;
		}

		foreach ($files as $subject)
		{
			if (!$this->check_test_prerequisites ($subject))
			{
				$this->mark_skipped ($subject, "Individual prerequsite failed");
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
		}

		$this->finish_test ();
	}

	function start_timer ($subject)
	{
		$this->timer_start = microtime(true);
	}

	function end_timer ($subject)
	{
		$number = 0;
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

/*
		var_dump($max_key);
		var_dump($max_val);
		var_dump($med_key);
		var_dump($med_val);
		var_dump($mean);
		var_dump($std_dev);
*/
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
		$this->successes++;
		$this->total++;
		$this->update_count ();
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
		note_in_skipped_file ($this->get_name(), $subject, $reason);
		$this->update_count ();
	}

	function mark_failure ($subject, $commands, $return_values = "Not relevent", $output = "Not relevent")
	{
		global $log_directory, $opt_verbose;
		$red = red_string();
		$reset = reset_string();
		if (is_array ($commands))
		{
			if ($return_values == "Not relevent")
			{
				$command_string = "";
				foreach ($commands as $command)
				{
					$command_string .= "{$red}Command:$reset $command\n";
				}
			}
			else
			{
				phc_assert (is_array ($return_values), "Expected array of return values");
				phc_assert (count ($return_values) == count ($commands), 
					"Expected same number of commands and return values");
				$command_string = "";
				for ($i = 0; $i < count ($commands); $i++)
				{
					$command = $commands[$i];
					$return_value = $return_values[$i];
					$command_string .= "{$red}Command$reset ($return_value): $command\n";
				}
			}

		}
		else
		{
			$command_string = "{$red}Command$reset ($return_values): $commands\n";
		}

		// dump it to a file
		$file_header = 
			"Failure in test $subject:\n".
			$command_string.
			"Output:\n"; // this is added below to avoid the massive memory usage

		log_failure ($this->get_name(), $subject, $command_string, $output);
		$this->erase_progress_bar();

		if ($opt_verbose)
		{
			if ($this->failures < 2)
			{
				$script_name = adjusted_name($subject);
				printf("{$this->get_name()} failure with %-56s\n", $script_name);
				print
					"$red----------- The script failed as follows: ------------------------$reset\n".
					$command_string.
					"{$red}Output:$reset ". substr (preg_replace ("/\n/", "", $output), 0, 70).
					"...$reset\n".
					"$red---------------- End of failure notice ---------------------------$reset\n\n";
			}
			elseif ($this->failures == 2)
			{
				print "{$red}Too many failures, restricting output...                              $reset\n\n";
			}
		}
		$this->display_progress_bar ();

		$this->failures++;
		$this->total++;
		$this->update_count ();
	}

	function update_count ()
	{
		global $opt_no_progress_bar;
		if (! $opt_no_progress_bar)
		{
			$this->erase_progress_bar ();
			$this->progress_bar->reset(
					"{$this->get_name()} %bar% %fraction% done ({$this->failures} failed)", 
					"#", "-", 80, $this->num_files);
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
		if ($this->successes == 0)
		{
			$string = $this->get_failure_string ();
		}
		elseif ($this->failures == 0)
		{
			if ($this->successes > 0)
			{ 
				$string = $this->get_success_string ();
			}
			else
			{
				phc_unreachable ();
			}
		}
		else
		{
			$string = $this->get_failure_string ();
		}
		print "$string\n";
	}

	function get_success_string()
	{
		$test = $this->get_name();
		$blue = blue_string ();
		$reset = blue_string ();
		$timing = $this->get_timing_string ();
		$skipped_count = $this->skipped;
		$success_count = sprintf("%3s", $this->successes);
		if ($skipped_count > 0)
		{
			return sprintf("%-30s %-21s    ", $test, $timing)
				. green_string()."Success ($success_count/$success_count passed; "
				. blue_string() . "$skipped_count skipped)"
				. reset_string();
		}
		else
		{
			return sprintf("%-30s %-21s    ", $test, $timing)
				. green_string()."Success ($success_count/$success_count passed)"
				. reset_string();
		}
	}

	function get_skipped_string ()
	{
		$skipped_count = $this->skipped;
		$test = $this->get_name ();
		return sprintf("%-30s %-21s    ", $test, $timing)
			. blue_string()
			. "$skipped_count skipped"
			. reset_string();
	}

	function get_failure_string ()
	{
		$test = $this->get_name ();
		$success_count = sprintf("%3s", $this->successes);
		$failure_count = sprintf("%3s", $this->failures);
		$skipped_count = $this->skipped;
		$total_count = sprintf("%3s", $this->total);

		if ($skipped_count == $this->total and $this->check_prerequisites() == false)
		{
			return sprintf("%-30s %-21s    ", $test, "")
				. red_string().  "Failure ( Prerequisites) "
				. reset_string();
		}

		$timing = $this->get_timing_string ();

		if ($skipped_count > 0)
		{
			return sprintf("%-30s %-21s    ", $test, $timing)
				. red_string().  "Failure ($failure_count/".($total_count)." failed; "
				. blue_string() . "$skipped_count skipped)"
				. reset_string();
		}
		elseif ($total_count == 0)
		{
			return sprintf("%-30s %-21s    ", $test, $timing)
				. red_string().  "Failure (No tests run)"
				. reset_string();
		}
		
		else
		{
			return sprintf("%-30s %-21s    ", $test, $timing)
				. red_string().  "Failure ($failure_count/".($total_count)." failed)"
				. reset_string();
		}
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
