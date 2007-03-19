<?php
/*
 * Bug report submitted by Matthias Kleine.
 * Unparsed output appears to be missing braces.
 */

class Testclass {
	public $logicalKey;

	public function getLogicalKey()
	{
		return isset($this->{$this->logicalKey}) ? $this->{$this->logicalKey} : null;
	}
}

$test = new Testclass();
$test->logicalKey = "testkeyname";

echo $test->getLogicalKey();
?>
