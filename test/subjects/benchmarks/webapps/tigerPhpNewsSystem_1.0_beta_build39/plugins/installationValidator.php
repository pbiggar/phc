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
class installationValidator
{
    //{{{ installationValidator
    function installationValidator()
    {
        require_once( 'Main.php' );
    }
    //}}}
    //{{{ getAccess
    function getAccess()
    {
        return "4";
    }
    //}}}
    //{{{getName
    function getName()
    {
        return "Installation Validator";
    }
    //}}}
    //{{{ execute
    function execute($main)
    {
       include( 'config.php' );
       print "<span class=\"headline\"><b>".$this->getName()."</b></span><br />";
       print "php gd loaded: ";if ( in_array("gd",get_loaded_extensions())){$this->ok();}else{$this->fail();}
       print "php mysql loaded: ";if ( in_array("mysql",get_loaded_extensions())){$this->ok();}else{$this->fail();}
       print "ImageMagick path pk: ";if ( is_file($_convert_path) ){$this->ok();}else{$this->fail();}
       print "ImageMagick file is executable: ";if ( is_executable($_convert_path) ){$this->ok();}else{$this->fail();}
       print "thumb dir is writable: ";if ( is_writeable("./thumb") ){$this->ok();}else{$this->fail();}
       print "small dir is writable: ";if ( is_writeable("./small") ){$this->ok();}else{$this->fail();}
       print "img dir is writable: ";if ( is_writeable("./img") ){$this->ok();}else{$this->fail();}
       print "thumb/user dir is writable: ";if ( is_writeable("./thumb/user") ){$this->ok();}else{$this->fail();}
       print "small/user dir is writable: ";if ( is_writeable("./small/user") ){$this->ok();}else{$this->fail();}
       print "img/user dir is writable: ";if ( is_writeable("./img/user") ){$this->ok();}else{$this->fail();}
       print "thumb/news dir is writable: ";if ( is_writeable("./thumb/news") ){$this->ok();}else{$this->fail();}
       print "small/news dir is writable: ";if ( is_writeable("./small/news") ){$this->ok();}else{$this->fail();}
       print "img/news dir is writable: ";if ( is_writeable("./img/news") ){$this->ok();}else{$this->fail();}
       print "file upload dir exists: ";if ( is_dir($filepath) ){$this->ok();}else{$this->fail();}
       print "file upload dir is writable: ";if ( is_writeable($filepath) ){$this->ok();}else{$this->fail();}
       print "Can handle browser statistics: ";if ( ini_get("browscap") != "" ){$this->ok();}else{$this->fail();}
       
    }
    //}}}
    //{{{ ok
    function ok()
    {
        print "<span style=\"color:green\">OK</span><br />";
    }
    //}}}
    //{{{ fail
    function fail()
    {
        print "<span style=\"color:red\">FAILED</span><br />";
    }
    //}}}
}
?>
