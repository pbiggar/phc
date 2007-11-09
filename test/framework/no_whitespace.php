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
		$async = new Async_steps ($this, $subject);

		$async->commands[0]		= "$phc $subject --pretty-print";
		$async->out_handlers[0] = "strip_whitespace";
		$async->err_handlers[0] = "fail_on_output";

		$async->commands[1]		= "cat $subject";
		$async->out_handlers[1] = "strip_whitespace";
		$async->err_handlers[1] = "fail_on_output";

		$async->final = "finish";
		$async->start ();
	}

	function finish ($async)
	{
		if ($async->outs[0] !== $async->outs[1])
			$this->mark_failure ("Whitespace free output doesnt match", $async);
		else
			$this->mark_success ($async->subject);

	}

	// this strings whitespace from strings, so it wont be perfect, but thats a minor, but very difficult to avoid, problem
	function strip_whitespace ($out, $async)
	{
		return preg_replace ("/\s+/", "", $out);
	}
}
?>
