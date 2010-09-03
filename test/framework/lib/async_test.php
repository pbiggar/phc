<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Allows a test to run programs asynchronously
 */

// Allow the number of processes to be specified locally

require_once ("test.php");

if (isset($_ENV["PHC_NUM_PROCS"]))
	define ("PHC_NUM_PROCS", (int)($_ENV["PHC_NUM_PROCS"]));
else
	define ("PHC_NUM_PROCS", 1);

function inst ($string)
{
#	print "\n" . microtime () . " $string\n";
}

class AsyncBundle
{
	function __construct ($object, $subject)
	{
		$this->object = $object;
		$this->subject = $subject;
		$this->state = 0;
	}

	function start ()
	{
		$this->object->start_new_program ($this);
	}

	function get_command ()
	{
		return $this->commands[$this->state];
	}

	function get_in ()
	{
		if (isset ($this->ins))
			return $this->ins[$this->state];

		return NULL;
	}

	function continuation ()
	{
		inst ("continuing from state {$this->state} of {$this->subject}\n");

		$state = $this->state; // state is just an int
		$this->outs[$state] = $this->out; // copy
		$this->errs[$state] = $this->err; // copy
		$this->exits[$state] = $this->exit; // copy
		unset ($this->out);
		unset ($this->err);
		unset ($this->exit);
		$object = $this->object;

		// Handlers let you modify the stdout, stderr or the exit
		// code. They return FALSE for failure.
		if (isset ($this->out_handlers[$state]))
		{
			$handler = $this->out_handlers[$state];
			$result = $object->$handler ($this->outs[$state], $this);
			if ($result === false)
				return;
			$this->outs[$state] = $result;
		}

		if (isset ($this->err_handlers[$state]))
		{
			$handler = $this->err_handlers[$state];
			$result = $object->$handler ($this->errs[$state], $this);
			if ($result === false)
				return;
			$this->errs[$state] = $result;
		}

		if (isset ($this->exit_handlers[$state]))
		{
			$handler = $this->exit_handlers[$state];
			$result = $object->$handler ($this->exits[$state], $this);
			if ($result === false)
				return;
			$this->exits[$state] = $result;
		}

		// The callback doesnt modify, just calls a function given
		// stdout, stderr and exit_code.
		if (isset ($this->callbacks [$state]))
		{
			$callback = $this->callbacks [$state];
			$result = $object->$callback ($this->outs[$state], $this->errs[$state], $this->exits[$state], $this);
			if ($result === false)
				return;
		}


		$this->state += 1;
		$state = $this->state;

		if (isset ($this->commands[$state]))
		{
			inst ("Start next program: {$this->commands[$state]}");
			$object->start_program ($this);
		}
		elseif (isset ($this->final))
		{
			inst ("Finalize");
			$object->{$this->final} ($this);
		}
		else
		{
			die ("uhoh\n");
		}
	}

	function read_streams ()
	{
		$this->out .= stream_get_contents ($this->pipes[1]);
		$this->err .= stream_get_contents ($this->pipes[2]);
	}

}

/* In order to take advantage of multiple cores, and to avoid
 * wasting a lot of time waiting for sequential programs to
 * run, we instead try to run programs in parallel.  Once it
 * has started the program, it will check if any programs
 * have finished execution, and if so, it will continue the
 * next part of their test.
 *
 * This also adds a nice abstraction level to the test suite.
 * Nearly all the tests can be described using a very simple
 * data description language, so this provides it.
 */
abstract class AsyncTest extends Test
{
	function __construct ()
	{
		$this->waiting_procs = array ();
		$this->running_procs = array ();

		$this->reductions = array ();
		$this->reduction_result = array ();
		$this->is_special_reduction = array ();

		parent::__construct ();
	}

	/*
	 * This is the best place to handle reduce
	 */

	function reduce_run_function ($command, $stdin)
	{
		$result = complete_exec ($command, $stdin, 3);
		if ($result[0] == "Timeout")
			return array ("", "", 0);

		return $result;
	}

	function reduce_checking_function ($program)
	{
		global $working_directory;
		$filename = tempnam ($working_directory, "reduce_");
		file_put_contents ($filename, $program);

		$this->is_special_reduction[$filename] = true;

		$this->run_test ($filename);

		$this->run_out_all_procs ();

		return $this->reduction_result[$filename];
	}

	function reduce_debug_function ($level, $message)
	{
		// Do nothing
	}

	function reduce_failure ($reason, $bundle)
	{
		inst ("reduce failure: $reason, $bundle->subject");
		global $phc;
		$subject = $bundle->subject;

		if (isset ($this->is_special_reduction[$subject]))
		{
			// Found: we're already reducing, and the bug is kept in
			$this->reduction_result[$subject] = true;
		}
		else
		{
			// Start reducing
			try
			{
				$reduce = new Reduce ();
				$this->reductions[$subject] = $reduce;
				$reduce->set_checking_function (array ($this, "reduce_checking_function"));
				$reduce->set_run_command_function (array ($this, "reduce_run_function"));
				$reduce->set_phc ($phc);
				$reduce->set_debug_function (array ($this, "reduce_debug_function"));

				// Get the file, and send it to the reducer
				$contents = file_get_contents ($subject);

				if (!$reduce->has_syntax_errors ($contents))
				{
					$final_contents = $reduce->run_on_php ($contents);
					file_put_contents ("$subject.{$this->get_name ()}_reduced", $final_contents);
				}
			}
			catch (ReduceException $e)
			{
				// There can be lots of reasons for this, many benign. Ignore it.
			}

			$this->mark_failure (
					$bundle->subject, 
					$bundle->commands,
					$bundle->outs,
					$bundle->errs,
					$bundle->exits,
					$reason);
		}
	}

	function reduce_success ($bundle)
	{
		inst ("reduce success: $bundle->subject");
		if (isset ($this->is_special_reduction[$bundle->subject]))
		{
			// The bug has been eliminated.
			$this->reduction_result[$bundle->subject] = false;
		}
		else
		{
			$this->mark_success (
					$bundle->subject, 
					$bundle->commands,
					$bundle->outs,
					$bundle->errs,
					$bundle->exits);
		}
	}

	function reduce_timeout ($reason, $bundle)
	{
		if (isset ($this->is_special_reduction[$bundle->subject]))
		{
			// Don't know if this has helped. Lets say it hasn't (ie say 'dont
			// remove that line').
			$this->reduction_result[$bundle->subject] = false;
		}
		else
		{
			$this->mark_timeout (
					$bundle->subject, 
					$bundle->commands,
					$bundle->outs,
					$bundle->errs,
					$bundle->exits);
		}
	}




	function async_failure ($reason, $bundle)
	{
		global $opt_reduce;
		if ($opt_reduce)
			$this->reduce_failure ($reason, $bundle);
		else
		{
			$this->mark_failure (
					$bundle->subject, 
					$bundle->commands,
					$bundle->outs,
					$bundle->errs,
					$bundle->exits,
					$reason);
		}
	}

	function async_timeout ($reason, $bundle)
	{
		global $opt_reduce;
		if ($opt_reduce)
			$this->reduce_timeout ($reason, $bundle);
		else
		{
			$this->mark_timeout (
					$bundle->subject, 
					$bundle->commands,
					$bundle->outs,
					$bundle->errs,
					$bundle->exits);
		}
	}

	function async_success ($bundle)
	{
		global $opt_reduce;
		if ($opt_reduce)
			$this->reduce_success ($bundle);
		else
		{
			$this->mark_success (
					$bundle->subject, 
					$bundle->commands,
					$bundle->outs,
					$bundle->errs,
					$bundle->exits);
		}
	}

	function fail_on_output (&$stream, $bundle)
	{
		if ($stream === 0 or $stream === "")
			return $stream;

		$this->async_failure ("exit or err not clear", $bundle);
		return false;
	}

	# Put this program to the front of the queue, and start waiting progs
	function start_program ($bundle)
	{
		array_unshift ($this->waiting_procs, $bundle);

		$this->check_capacity ();
	}

	# Put this program to the back of the queue, and start waiting progs
	function start_new_program ($bundle)
	{
		$this->waiting_procs[] = $bundle;

		$this->check_capacity ();
	}




	function finish_test ()
	{
		$this->run_out_all_procs ();
		parent::finish_test ();
	}

	function run_out_all_procs ()
	{
		while (count ($this->running_procs) or count ($this->waiting_procs))
		{
			usleep (30000);
			$this->run_waiting_procs ();
			$this->check_running_procs ();
		}
	}

	function check_capacity ()
	{
		if (count ($this->running_procs) 
				>= ($this->get_num_procs () / $this->get_phc_num_procs_divisor()))
		{
			// check each and see if we can remove some
			$this->check_running_procs ();
		}

		if (count ($this->waiting_procs) > 1)
		{
			// start some programs
			$this->run_waiting_procs ();
		}
		else
			; // return and carry on, adding programs to the queue

	}

	function check_running_procs ()
	{
		// try to keep this really lightweight
#		inst ("Check running");

		foreach ($this->running_procs as $index => $bundle)
		{
			$status = proc_get_status ($bundle->handle);

			// read the streams in case they block
			$bundle->read_streams ();

			if ($status["running"] !== true)
			{
				$bundle->exit = $status["exitcode"];
				unset ($this->running_procs [$index]); // remove from the running list
				$bundle->continuation (); // start the next bit straight away
			}
			else if ($this->max_time != 0
				&& time () > $bundle->start_time + $this->max_time)
			{
				kill_properly ($bundle->handle, $bundle->pipes);

				$bundle->exits[] = "Timeout";
				$bundle->out .= "\n--- TIMEOUT ---";
				$bundle->outs[] = $bundle->out;
				$bundle->errs[] = $bundle->err;
				unset ($this->running_procs [$index]); // remove from the running list
				$this->async_timeout ("Timeout", $bundle);
			}
			else
			{
				// let it keep running
			}
		}
	}

	function run_waiting_procs ()
	{
		while (count ($this->running_procs) 
				< ($this->get_num_procs () / $this->get_phc_num_procs_divisor()))
		{
			inst ("Poll waiting");
			if (count ($this->waiting_procs) == 0)
			{
				inst ("No procs waiting");
				break;
			}

			$bundle = array_shift ($this->waiting_procs);
			$this->run_program ($bundle);
		}
	}

	function run_program ($bundle)
	{
		$command = $bundle->get_command ();
		$command = "ulimit -v 262144 && ulimit -t 300 && $command";
		global $opt_verbose;
		if ($opt_verbose)
			print "Running command: $command\n";

		inst ("Running prog: $command");

		// now start this process and add it to the list
		$descriptorspec = array(1 => array("pipe", "w"),
										2 => array("pipe", "w"));

		$in = $bundle-> get_in ();
		if ($in)
			$descriptorspec[0] = array ("pipe", "r");
		$pipes = array();
		$handle = proc_open ($command, $descriptorspec, $pipes);
		stream_set_blocking ($pipes[1], 0);
		stream_set_blocking ($pipes[2], 0);
		if ($in)
		{
			fwrite ($pipes[0], $in);
			fclose ($pipes[0]);
		}


		$bundle->handle = $handle;
		$bundle->pipes = $pipes;
		$bundle->start_time = time ();
		$bundle->out = "";
		$bundle->err = "";
		unset ($bundle->exit);

		$this->running_procs[] = $bundle;
	}

	// We use this a lot.
	function two_command_finish ($async)
	{
		if ($async->outs[0] !== $async->outs[1]
			or $async->errs[0] !== $async->errs[1]
			or $async->exits[0] !== $async->exits[1])
		{
			$output = diff ($async->outs[0], $async->outs[1]);
			$async->outs = $output;
			$this->async_failure ("Outputs dont match", $async);
		}
		else
		{
			$this->async_success ($async);
		}
	}

	/* Some tests are very CPU intensive. Overriding this will reduce the
	 * number of tests run at once. */
	function get_phc_num_procs_divisor ()
	{
		return 1;
	}

	function get_num_procs ()
	{
		return PHC_NUM_PROCS;
	}
}

?>
