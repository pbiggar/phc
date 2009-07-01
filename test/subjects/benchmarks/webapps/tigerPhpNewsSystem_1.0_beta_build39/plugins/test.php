<?
/*
 * This software is part of the Tiger php news system
 * http://tpns.k-na.se
 * 
 * This software comes with ABSOLUTELY NO WARRANTY. For details, see
 * the enclosed file COPYING for license information (GPL). If you
 * did not receive this file, see http://www.gnu.org/licenses/gpl.txt.
 * 
 */
class test
{
//{{{test    
function test()
{
    require_once( 'Main.php' );
}
//}}}
//{{{ getAccess
function getAccess()
{
    return "5";
}
//}}}
//{{{getName
function getName()
{
    return "Test plugin";
}
//}}}
//{{{execute
function execute($main)
{
    print "Test plugin <b>Worked!!!</b>";  
    //$result=$main->run_query("select * from category");
    //print "<pre>";
    //print_r($result);
    //print "</pre>";
}
//}}}
}
?>
