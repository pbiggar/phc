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



abstract class WhirlRing {
    private $_value;
    private $_position;
    private $_direction;
    protected $_commands;

    public function __construct() {
        $this->_init( );
        $this->initCommandsArray();
    }

    private function _init( ) {
        $this->_value = 0;
        $this->_position = 0;
        $this->_direction = 1; //forward
    }
    
    abstract protected function initCommandsArray();
    
    protected function _setValue($value) {
        $this->_value = $value;
    }

    protected function _getValue() {
        return $this->_value;
    }

    public function reverseDirection() {
        if ($this->_direction === 1) {
            $this->_direction = -1;
        } else {
            $this->_direction = 1;
        }
        if (defined('DEBUG')) 
            echo "reversed direction to: ", $this->_direction, "\n";
    }

    public function rotate() {
        $this->_position += $this->_direction;
        if ($this->_position < 0) {
            $this->_position = count( $this->_commands ) - 1;
        } else if ($this->_position > count( $this->_commands ) - 1) {
            $this->_position = 0;
        }
        if (defined('DEBUG'))
            echo "rotated to: ", $this->_position, "\n";
    }

    public function execute() {
        $functionToCall = "RINGFUNC_" . $this->_commands[$this->_position];
        if (!method_exists($this, $functionToCall)) {
            throw new Exception("Ring Function could not be called, because it wasn't defined: $functionToCall undefined.");
        }
        call_user_func(array($this,$functionToCall));
        if (defined('DEBUG'))
            echo "executed func: ", $functionToCall,", Value: ", $this->_value, "\n";
    }

}

?>
