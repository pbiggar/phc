<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 */

abstract class SupportFileTest extends Test
{
	abstract function get_support_filename ($subject);
	abstract function generate_support_file ($subject);

	function generate_support_files ()
	{
		if (!$this->check_prerequisites ())
		{
			$this->mark_skipped ("All");
			return false;
		}

		$files = $this->get_test_subjects ();
		$this->ready_progress_bar (count ($files));

		foreach ($files as $subject)
		{
			if (!$this->check_test_prerequisites ($subject))
			{
				$this->mark_skipped ($subject, "Test prerequisites failed");
			}
			else
			{
				$this->generate_support_file ($subject);
			}
		}

		$this->finish_test ();
	}

	function write_support_file ($out, $subject)
	{
		$filename = $this->get_support_filename ($subject);

		// make sure theres a directory to write it to
		$dirname = dirname ($filename);
		if (!is_dir($dirname))
		{
			@mkdir($dirname, 0755, true);
		}

		file_put_contents($filename, $out);
	}

}

?>
