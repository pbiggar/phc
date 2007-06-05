<?php
echo "inc10.php";
/*********************************************************************
*  Roadsend SiteManager
*  Copyright (c) 2001-2003 Roadsend, Inc.(http://www.roadsend.com)
**********************************************************************
*
* This source file is subject to version 1.0 of the Roadsend Public
* License, that is bundled with this package in the file 
* LICENSE, and is available through the world wide web at 
* http://www.roadsend.com/license/rpl1.txt
*
**********************************************************************
* Author(s): weyrick
*
*/

/**
 * menu
 *
 */
class wFunctionMenu extends SM_module {
     
     /**
      * configure the module. run before moduleThink
      */
    function moduleConfig() {

        // declare use of menu module (contrib/modules/ngMenu.mod)
        // first parameter is a keyword, second is the module name
        $this->useModule('mainMenu','ngMenu');

    }

     /**
      * this function contains the core functionality entry point for the module.
      */
    function moduleThink() {
    

        // get the menu module, using keyword set in moduleConfig()
        $menu =& $this->getResource('mainMenu');

        // build menu

        // GCS TESTS
        $item =& $menu->addItem('Global Config System (GCS)');
        $item->addLinkItem('Test Suite','gcs.php');

        // SMOBJECT TESTS
        $item =& $menu->addItem('SM Objects');
        $item->addLinkItem('Test Suite','smObjects.php');
        
        // COMPONENTS
        $item =& $menu->addItem('Components');
        $item->addLinkItem('Test Suite','components.php');

        // INVARS
        $item =& $menu->addItem('InVars');
        $item->addLinkItem('Test Suite','inVars.php?t1=test&t2=201');

        // SMROOT
        $item =& $menu->addItem('SM Root');
        $item->addLinkItem('Test Suite','smRoot.php');
        
        // SESSIONS TESTS
        $item =& $menu->addItem('Sessions');
        $item->addLinkItem('Test Suite','sessions.php');
        
        // MEMBER TESTS
        $item =& $menu->addItem('Members');
        $item->addLinkItem('Test Suite','members.php');

        // TEMPLATE TESTS
        $item =& $menu->addItem('Templates/CodePlates');
        $item->addLinkItem('Test Suite','templates.php');

        // MODULE TESTS
        $item =& $menu->addItem('Modules');
        $item->addLinkItem('Test Suite','modules.php?modVar2=5&modVar1=pokey');

        // SMARTFORM TESTS
        $item =& $menu->addItem('SmartForms');
        $item->addLinkItem('Test Suite','smartForms.php');

        // CONTRIB TESTS
        $item =& $menu->addItem('Contrib Modules');
        $item->addLinkItem('Test Suite','contrib.php');

        // DEBUG TESTS
        $item =& $menu->addItem('Debug');
        $item->addLinkItem('Test Suite','debug.php');

        // output menu
        $this->say($menu->run());

    }
    
}


?>
