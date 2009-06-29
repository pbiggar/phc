#!/usr/bin/php
<?php  

/***
 * 
 * PhpWhirl - A Whirl Interpreter written in PHP
 * Copyright (C) 2005 Jakob Westhoff - http://www.WesthoffsWelt.de (German)
 * 
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 2 of the License, or (at 
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA. 
 * 
 * You may contact the author by mail:
 * jakob@westhoffswelt.de
 *
 * Or write to:
 * Jakob Westhoff
 * Kleiner Floraweg 35
 * 44229 Dortmund
 * Germany
 *
 * The latest version of PhpWhirl can be obtained from:
 * http://www.westhoffswelt.de/
 *
 **/



    include_once("classes/WhirlParser.php");

    echo "PHP Whirl Interpreter by Jakob Westhoff <jakob@westhoffswelt.de> V1.0","\n";
   
    if ($argc < 2) {
        echo "Usage: ", $argv[0], " [-debug] Whirlfile.wrl", "\n";   
        die();
    }

    if (!strcasecmp($argv[1], "-debug")) {
        define("DEBUG", true);
        $filename = $argv[2];
    } else {
        $filename = $argv[1];
    }
    
    echo "Loading and parsing the program...", "\n";
        $whirl = new WhirlParser();
        $whirl->loadfile($filename);
        $whirl->parse();

?>
