<?php

/**
 * Parses and runs the keymaker.wr program using
 * the php Whirl parser, made by Jakob Westhoff
 * <jakob@westhoffswelt.de>
 */


include_once("phpWhirl/classes/WhirlParser.php");
$filename = "test/subjects/benchmarks/php-benchmarks/benchcli/tests/phpWhirl/keymaker.wr";

$whirl = new WhirlParser();
$whirl->loadfile($filename);
$whirl->parse();


?>
