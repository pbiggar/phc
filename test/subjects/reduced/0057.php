<?php

class A
{
	private $Name= NULL;

	public function __construct($Name)
	{
		$this->Name= $Name;
		echo 'A constructor: '.$this->Name."\n";
	}
}

class B extends A
{
	public function __construct($Name)
	{
		parent::__construct('B constructor: '.$Name);
	}
}

$b= new B('B object');

?>
