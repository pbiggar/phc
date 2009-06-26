<?php

/**
 * Parses and runs the keymaker.wr program using
 * the php Whirl parser, made by Jakob Westhoff
 * <jakob@westhoffswelt.de>
 */


chdir("tests/phpWhirl/");
include_once("classes/WhirlParser.php");
$filename = "keymaker.wr";
try {
    $whirl = new WhirlParser();
    $whirl->loadfile($filename);
    $whirl->parse();
} catch ( Exception $e ) {
    echo $e->getMessage(), "\n";
}


?>