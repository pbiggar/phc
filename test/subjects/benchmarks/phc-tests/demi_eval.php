<?php
/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Adds debug_zval_dump after each statement, then compared the outputs of the
 * compiled and interpreted code.
 */


array_push($tests, new Demi_eval ("true"));
array_push($tests, new Demi_eval ("false"));
class Demi_eval extends CompiledVsInterpreted
{
	function __construct ($init)
	{
		$this->init = $init;
		parent::__construct ();
	}

	function get_dependent_test_names ()
	{
		return array ("CompiledVsInterpreted");
	}

	function get_name ()
	{
		$init = $this->init;
		return "Demi_eval_$init";
	}

	function get_php_command ($subject)
	{
		global $phc, $plugin_dir;
		$init = $this->init;
		return "$phc --run $plugin_dir/tools/demi_eval.la --r-option=\"$init\" --convert-uppered --dump=$plugin_dir/tools/demi_eval.la $subject | ". get_php_command_line ($subject, "pipe");
	}

	function get_phc_command ($subject, $exe_name)
	{
		global $plugin_dir;

		$init = $this->init;
		return get_phc_command_line ($subject) . " -c --run $plugin_dir/tools/demi_eval.la --r-option=\"$init\" -o $exe_name";
	}

	function homogenize_output ($string, $bundle)
	{
		$string = parent::homogenize_output ($string, $bundle);
		$string = preg_replace ("/in __FILENAME__\(\d+\) : eval\(\)'d code/m", "in eval'd code", $string);
		return $string;
	}
}

?>
