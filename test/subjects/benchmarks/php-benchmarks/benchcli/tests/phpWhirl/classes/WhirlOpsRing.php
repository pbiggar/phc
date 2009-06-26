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



include_once("WhirlRing.php");
include_once("WhirlParser.php");

class WhirlOpsRing extends WhirlRing {
    
    public function __construct() {
        parent::__construct();
    }

    protected function initCommandsArray() {
        $this->_commands = array("Noop", "Exit", "One", "Zero", "Load", "Store", "PAdd", "DAdd", "Logic", "If", "IntIO", "AscIO");
    }

    protected function RINGFUNC_Noop() {
        //simply do nothing here
    }

    protected function RINGFUNC_Exit() {
        WhirlParser::instance()->programExit();
    }

    protected function RINGFUNC_One() {
        $this->_setValue(1);
    }

    protected function RINGFUNC_Zero() {
        $this->_setValue(0);
    }

    protected function RINGFUNC_Load() {
        $this->_setValue(WhirlMemory::instance()->getValue());
    }
   
    protected function RINGFUNC_Store() {
        WhirlMemory::instance()->setValue($this->_getValue());
    }

    protected function RINGFUNC_PAdd() {
        WhirlParser::instance()->PAdd($this->_getValue());
    }

    protected function RINGFUNC_DAdd() {
        WhirlMemory::instance()->moveby($this->_getValue());
    }

    protected function RINGFUNC_Logic() {
        if (WhirlMemory::instance()->getValue() !== 0) {
            $this->_setValue((int)($this->_getValue() && 1));
        } else {
            $this->_setValue(0);
        }
        
    }

    protected function RINGFUNC_If() {
        if ( WhirlMemory::instance()->getValue() !== 0) {
            WhirlParser::instance()->PAdd($this->_getValue());
        }
    }

    protected function RINGFUNC_IntIO() {
        if ($this->_getValue() === 0) {
            WhirlMemory::instance()->setValue((int) WhirlParser::instance()->input());
        } else {
            WhirlParser::instance()->output((int) WhirlMemory::instance()->getValue());
        }
    }

    protected function RINGFUNC_AscIO() {
        if ($this->_getValue() === 0) {
            WhirlMemory::instance()->setValue((int) ord(WhirlParser::instance()->input()));
        } else {
            WhirlParser::instance()->output(chr(WhirlMemory::instance()->getValue()));
        }
    }
}


?>
