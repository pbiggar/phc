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

#function inst ($string)
#{
#	print "\n" . microtime () . " $string\n";
#}

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
#		inst ("continuing from state {$this->state} of {$this->subject}\n");

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
#			inst ("Start next program: {$this->commands[$state]}");
			$object->start_program ($this);
		}
		elseif (isset ($this->final))
		{
#			inst ("Finalize");
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
		parent::__construct ();
	}

	function async_failure ($reason, $bundle)
	{
		$this->mark_failure (
					$bundle->subject, 
					$bundle->commands,
					$bundle->outs,
					$bundle->errs,
					$bundle->exits,
					$reason);
	}

	function async_timeout ($reason, $bundle)
	{
		$this->mark_timeout (
					$bundle->subject, 
					$bundle->commands,
					$bundle->outs,
					$bundle->errs,
					$bundle->exits);
	}

	function async_success ($bundle)
	{
		$this->mark_success (
					$bundle->subject, 
					$bundle->commands,
					$bundle->outs,
					$bundle->errs,
					$bundle->exits);
	}

	function async_skipped ($bundle)
	{
		$this->mark_skipped (
					$bundle->subject, 
					$bundle->commands,
					$bundle->outs,
					$bundle->errs,
					$bundle->exits);
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
		while (count ($this->running_procs) or count ($this->waiting_procs))
		{
			usleep (30000);
			$this->run_waiting_procs ();
			$this->check_running_procs ();
		}
		parent::finish_test ();
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

			if ($status["running"] !== true)
			{
				$bundle->read_streams ();
				$bundle->exit = $status["exitcode"];
				unset ($this->running_procs [$index]); // remove from the running list
				$bundle->continuation (); // start the next bit straight away
			}
			else if (time () > $bundle->start_time + $this->max_time)
			{
				$bundle->read_streams ();

				kill_properly ($bundle->handle, $bundle->pipes);

				$bundle->exits[] = "Timeout";
				$bundle->out .= "\n--- TIMEOUT ---";
				$bundle->outs[] = $bundle->out;
				$bundle->errs[] = $bundle->err;
				$this->async_timeout ("Timeout", $bundle);

				unset ($this->running_procs [$index]); // remove from the running list
			}
			else
			{
				// let it keep running, but read the streams in case they block
				$bundle->read_streams ();
			}
		}
	}

	function run_waiting_procs ()
	{
		while (count ($this->running_procs) 
				< ($this->get_num_procs () / $this->get_phc_num_procs_divisor()))
		{
#			inst ("Poll waiting");
			if (count ($this->waiting_procs) == 0)
			{
#				inst ("No procs waiting");
				break;
			}

			$bundle = array_shift ($this->waiting_procs);
			$this->run_program ($bundle);
		}
	}

	function run_program ($bundle)
	{
		$command = $bundle->get_command ();
		$command = "ulimit -v 262144 && $command";
		global $opt_verbose;
		if ($opt_verbose)
			print "Running command: $command\n";

#		inst ("Running prog: $command");

		// now start this process and add it to the list
		$descriptorspec = array(1 => array("pipe", "w"),
										2 => array("pipe", "w"));

		$in = $bundle-> get_in ();
		if ($in)
			$descriptorspec[0] = array ("pipe", "r");
		$pipes = array();
		$handle = proc_open ($command, $descriptorspec, &$pipes);
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
