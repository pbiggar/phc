<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * We cant test that the MIR unparser works, but we can test that it doesn't
 * segfault (which can happen due to MIR_to_AST having bugs).
 */


class Parse_clp extends AsyncTest
{
	function __construct ($pass)
	{
		$this->pass = $pass;
		parent::__construct ();
	}

	function get_name ()
	{
		return "Parse_{$this->pass}_clp";
	}

	function get_test_subjects ()
	{
		return get_all_scripts ();
	}

	function get_dependencies ()
	{
		return array ("BasicParseTest");
	}

	function run_test ($subject)
	{
		global $phc;
		$async = new AsyncBundle ($this, $subject);

		$clp_name = wd_name ("$subject.out." . $this->get_name ());
		$async->commands[0]		= "$phc $subject --sdump={$this->pass} > $clp_name";
		$async->err_handlers[0] = "fail_on_output";
		$async->out_handlers[0] = "fail_on_output";

		$async->commands[1]		= "3rdparty/clpa/bin/clpa $clp_name";
		$async->err_handlers[1] = "expect_parse_error";
		$async->out_handlers[1] = "expect_analysis_warning";
		$async->clp_name = $clp_name;

		$async->final = "async_success";
		$async->start ();
	}

	function expect_parse_error (&$stream, $bundle)
	{
		if ($stream === "parse error: Warnings treated as errors\n")
			return $stream;

		$this->async_failure ("Parse error not present", $bundle);
		return false;
	}

	function expect_analysis_warning (&$stream, $bundle)
	{
		if (preg_match ("!^.*saturn: 3rdparty/clpa/bin/clpa {$bundle->clp_name}\nanalysis: warning: No 'analyze session_name\(...\)' directive supplied; using empty session.\n$!m", $stream))
			return $stream;

		$this->async_failure ("Warning not present", $bundle);
		return false;
	}

}
?>
