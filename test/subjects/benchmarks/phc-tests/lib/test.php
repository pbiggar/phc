<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Base class for tests
 */

require_once ("labels.php");
abstract class Test
{
	function __construct ()
	{
		$this->successes = 0;
		$this->failures = 0;
		$this->skipped = 0;
		$this->timeouts = 0;
		$this->max_time = 20;
		$this->total = 0;
		$this->solo_tests = 0;
		$this->missing_dependencies = array ();
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
			if (in_array ($dependency, $dependencies))
				continue;

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
				$this->missing_dependencies[$subject] = $dependency;
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
				$this->run_test ($subject);
			}
			$count ++;

			if ($opt_quick && $count >= 10)
				break;
		}

		$this->finish_test ();
	}

	function mark_success ($subject)
	{
		write_dependencies ($this->get_name (), $subject, true);

		$this->successes++;
		$this->total++;
		$this->update_count ();
		log_status ("success", $this->get_name(), $subject, "");
	}

	function mark_timeout ($subject, $commands, $outs, $errs, $exits)
	{
		$this->timeouts++;
		$this->total++;
		$this->update_count ();
		log_status ("timeout", $this->get_name(), $subject, "");
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

	function mark_failure ($subject, $commands, $outs = "Not relevent", $errs = "Not relevent", $exits = "Not relevent", $reason = "TODO - no reason given")
	{
		write_dependencies ($this->get_name (), $subject, false);

		log_failure ($this->get_name(), $subject, $commands, $outs, $errs, $exits, isset ($this->missing_dependencies[$subject]) ? $this->missing_dependencies[$subject] : NULL, $reason);
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
		return ($this->failures == 0 and $this->successes == 0 and $this->timeouts == 0 and $this->skipped >= 0);
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
		$timedout = sprintf ("%5s", $this->timeouts ." T");
		$skipped = sprintf ("%5s", $this->skipped." S");
		if ($finished)
		{
			$colour = $this->get_appropriate_colour ();
			return "$colour$passed, $failed, $timedout, $skipped$reset";
		}
		else
		{
			$blue = blue_string ();
			$green = green_string ();
			$red = red_string ();
			$reset = reset_string ();
			return "$green$passed$reset, $red$failed$reset, $blue$timedout$reset, $blue$skipped$reset";
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
		$triple = $this->get_triple_string (true);

		$phrase = $this->get_appropriate_phrase ();
		$colour = $this->get_appropriate_colour ();
		$word = "$colour$phrase:$reset";

		// a color or a reset involves 6 characters, but gets displayed as zero.
		// Those 6 need to be taken into account for sprintf
		$string = sprintf("%-27s %20s %41s\n", $test, $word, $triple);
		print "$string";
		write_status ("results", strip_colour ($string));
	}

	// return true if the subject is marked as an exception
	function check_exception ($subject)
	{
		global $exceptions;

		if (!isset ($exceptions[$subject]))
			return false;

		foreach ($exceptions[$subject] as $exception)
		{
			if (preg_match ("/$exception/", $this->get_name ()))
				return true;
		}
		return false;
	}
}


?>
