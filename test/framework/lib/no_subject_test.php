<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 * A base test for tests which do not use php files as test subjects
 */

abstract class NoSubjectTest extends Test
{
	function get_test_subjects ()
	{
		return array ("All");
	}

	function run ()
	{
		$this->ready_progress_bar (1);
		if (!$this->check_prerequisites () || !$this->check_global_prerequisites ())
		{
			$this->mark_skipped ("All", "Test prerequisties failed");
			$this->finish_test ();
			return false;
		}

		$this->start_timer ("All");
		$this->run_test ("All");
		$this->end_timer ("All");
		$this->finish_test ();
	}
}

?>
