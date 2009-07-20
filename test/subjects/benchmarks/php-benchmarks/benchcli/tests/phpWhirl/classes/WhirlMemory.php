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



class WhirlMemory {
    
    private $_values;
    private $_position;
    private static $_instance;
    
    public function __construct() {
        $this->_init( );
        if (!isset(self::$_instance)) {
            self::$_instance = $this;
        } else {
            die ("WhirlMemory is a Singleton, you can only instantiate one object of this class. Please use instance() instead.");
        }
    }
    
    private function _init( ) {
            $this->_values = array(0);
            $this->_position = 0;
    }

    public static function instance( ) {
        if (!isset(self::$_instance)) {
            self::$_instance = new WhirlMemory();
        } 
        return self::$_instance;
    }

    public function moveby( $count ) {
        $this->_position += $count;
        if ( $this->_position < 0 ) {
            die ("Error in instruction " . WhirlParser::instance()->getInstructionNumber() . ": Memory index out of bounds. The memory index was decreased beyond zero.");
        }
        if (!isset($this->_values[$this->_position])) {
            $this->_values[$this->_position] = 0;
        }
    }

    public function getValue( ) {
        //if(!isset($this->_values[$this->_position])) {
        //    throw new Exception("Error in instruction " . WhirlParser::instance()->getInstructionNumber() . ": Memory at index " . $this->_position . " was not set before retrieval.");
        //}
        return $this->_values[$this->_position];
    }

    public function setValue( $data ) {
        $this->_values[$this->_position] = $data;
    }
}


?>
