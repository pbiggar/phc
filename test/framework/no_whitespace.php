<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * When the PHP unparser is able to input what the user put in, we should test
 * that. For now, we dont replicate the exact placement of text, but by
 * removing all the whitespace, we are able to replicate it.
 */


array_push($tests, new NoWhitespace ());
class NoWhitespace extends AsyncTest
{
	function get_test_subjects ()
	{
		return get_all_scripts ();
	}

	function get_dependent_test_names ()
	{
		return array ("BasicParseTest");
	}

	function run_test ($subject)
	{
		global $phc;
		$bundle = new AsyncBundle ($this, $subject);

		$bundle->commands[0] = get_phc_command_line ($subject). " --pretty-print";
		$bundle->out_handlers[0] = "strip_whitespace";
		$bundle->err_handlers[0] = "fail_on_output";

		$bundle->commands[1]		= "cat $subject";
		$bundle->out_handlers[1] = "strip_whitespace";
		$bundle->err_handlers[1] = "fail_on_output";

		$bundle->final = "two_command_finish";
		$bundle->start ();
	}

	// This strings whitespace from strings, so it wont be perfect, but thats
	// a minor, but very difficult to avoid, problem
	function strip_whitespace ($out, $bundle)
	{
		$out = preg_replace ("/\s+/", "", $out);
		// replace <?php by <? so that we don't report differences when the
		// input uses <? but the output uses <?php
		$out = preg_replace ("/<\?php/", "<?", $out);
		return $out;
	}
}
?>
