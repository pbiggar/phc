<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * We cant test that the MIR unparser works, but we can test that it doesn't
 * segfault (which can happen due to MIR_to_AST having bugs).
 */


class Pass_dump extends AsyncTest
{
	function __construct ($pass, $dump = "dump", $dependency = "BasicParseTest")
	{
		$this->pass = $pass;

		// this might be dump-uppered
		$this->dump = $dump;

		$this->dependencies = array ($dependency);
		parent::__construct ();
	}

	function get_name ()
	{
		return "{$this->pass}_dump";
	}

	function get_test_subjects ()
	{
		return get_all_scripts ();
	}

	function run_test ($subject)
	{
		global $phc;
		$async = new AsyncBundle ($this, $subject);

		$async->commands[0]		= "$phc $subject --{$this->dump}={$this->pass}";
		$async->err_handlers[0] = "fail_on_output";

		$async->final = "async_success";
		$async->start ();
	}
}
?>
