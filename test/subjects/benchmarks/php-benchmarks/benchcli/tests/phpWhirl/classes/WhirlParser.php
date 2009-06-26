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



    include_once("WhirlMemory.php");
    include_once("WhirlOpsRing.php");
    include_once("WhirlMathRing.php");

    class WhirlParser {
        
        private $_LANGUAGE = array("0", "1");

        
        private static $_instance;
        private $_WhirlMemory;
        private $_program;
        private $_currentPosition;
        private $_rings;
        private $_currentRing;

        public function __construct() {
            $this->_init( );
            if (!isset(self::$_instance)) {
                self::$_instance = $this;
            } else {
                throw new Exception("WhirlParser is a Singleton, you can only instantiate one object of this class. Please use instance() instead.");
            }
        }

        private function _init() {
            $ringClasses = array("WhirlOpsRing", "WhirlMathRing");
            
            $this->_WhirlMemory = WhirlMemory::instance();
            $this->_program = array();
            foreach ( $ringClasses as $ring ) {
                $this->_rings[] = new $ring;
            }           
            $this->_currentRing = 0;
            $this->_currentPosition = 0;
        }

        public static function instance( ) {
            if (!isset(self::$_instance)) {
                self::$_instance = new WhirlParser();
            } 
            return self::$_instance;
        }

        private function _setNextRingActive() {
            $this->_currentRing++;
            if ($this->_currentRing > count($this->_rings) -1) {
                $this->_currentRing = 0;
            }
            if (defined('DEBUG'))
                echo "changed to ring: ", $this->_currentRing, "\n";
        }

        private function _cleanCode( $code ) {
            //strip out everything which is not part of the LANGUAGE
            return preg_replace('/[^'.$this->_LANGUAGE[0].$this->_LANGUAGE[1].']/','', $code);
        }

        private function _prepareCode( $code ) {
            $preparedCode = array();
            foreach (preg_split('//', $code) as $instruction) {
                if ($instruction === $this->_LANGUAGE[0]) {
                    $preparedCode[] = false;
                } else if ($instruction === $this->_LANGUAGE[1]) {
                    $preparedCode[] = true;
                }
            }
            return $preparedCode;
        }

        public function load ($code) {
            $this->_program = $this->_prepareCode( $this->_cleanCode( $code ) );
        }

        public function loadFile( $filename ) {
            if (!file_exists($filename)) {
                throw new Exception("An Error occured while loading a source file: The file $filename does not exist.");
            }
            if (!is_readable($filename)) {
                throw new Exception("An Error occured while loading a source file: The file $filename is not readable.");
            }
            $this->_program = $this->_prepareCode( $this->_cleanCode( file_get_contents($filename) ) );
        }

        public function parse() {
            if (count($this->_program) === 0) {
                throw new Exception("An Error occured while parsing: No program code has been supplied.");
            }
           
            if (defined('DEBUG')) {
                echo "Executing the following Code:\n";
                foreach( $this->_program as $instruction ) {
                    if ($instruction) 
                        echo $this->_LANGUAGE[1];
                    else 
                        echo $this->_LANGUAGE[0];
                }
                echo "\n";
            }
           
            //some variables we need during the loop
            $execute = false;
            
            //Enter main loop for parsing the file
            while ($this->_currentPosition < count($this->_program)) {
                if ($this->_program[$this->_currentPosition]) { 
                    //We have a 1 as instruction
                    $this->_rings[$this->_currentRing]->rotate();
                    $execute = false;
                } else {
                    //We have a 0 as instruction
                    $this->_rings[$this->_currentRing]->reverseDirection();
                    if ($execute) {
                        $this->_rings[$this->_currentRing]->execute();
                        $this->_setNextRingActive();
                        $execute = false;
                    } else {
                        $execute = true;
                    }
                }
                $this->_currentPosition++;
            }
            //parsing is complete
        }

        public function programExit() {
            //jump to the end of the program
            $this->_currentPosition = count($this->_program);
        }

        public function PAdd($count) {
            //jump to the wanted program position -1, because the position counter will be incremented by one after the execution.
            $this->_currentPosition += $count -1;
            if ($this->_currentPosition < -1) {
                throw new Exception("Error in Instruction " . $this->getInstructionNumber() . ": Program position out of Bounds. The program position was decreased beyond zero.");
            } else if ($this->_currentPosition > count($this->_program)) {
                throw new Exception("Error in Instruction " . $this->getInstructionNumber() . ": Program position out of Bounds. The program position was increased beyond the end of file.");
            }
        }

        public function getInstructionNumber() {
            return $this->_currentPosition + 1;
        }

        public function input() {
           return trim(fgets(STDIN)); 
        }

        public function output($output) {
            print($output);
        }
    }
?>
