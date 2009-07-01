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
class createThemes 
{
    //{{{ createThemes
    function createThemes()
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
        return "Create Themes";
    }
    //}}}
    //{{{ execute
    function execute($main)
    {
        print "<span class=\"headline\"><b>".$this->getName()."</b></span><br /><br /><b>Creating/Updating the following themes:</b><br />";
        
        $d=dir("plugins/createThemes/themes");
        while($entry = $d->read()) 
        {
            $entry=str_replace(".php","" ,$entry);
            if( is_file("plugins/createThemes/themes/$entry.php") )
            {
                print "$entry<br />";
                $this->buildcss($entry);

            }
        }
    }
        //}}}
        //{{{ buildcss
        function buildcss($file)
        {
            include("plugins/createThemes/themes/$file.php");
            $fp = fopen("plugins/createThemes/site_template.css", "r");
            $css="";
            while (!feof($fp)) 
            {
                $css .= fread($fp, 1024);
            }

            // Close the file
            fclose($fp);
            if (!is_dir("themes") ){mkdir("themes");}
            if (!is_dir("themes/$file") ){mkdir("themes/$file");}
            if (!is_dir("themes/$file/images") ){mkdir("themes/$file/images");}
            if (!isset($textlinkcolor)){$textlinkcolor=$textcolor;}
            $css = str_replace("margintop", $margintop,$css);
            $css = str_replace("framecornerbgcolor", $framecornerbgcolor,$css);
            $css = str_replace("tablebordercolor", $tablebordercolor,$css);
            $css = str_replace("headertextcolor", $headertextcolor,$css);
            $css = str_replace("tableborderwhith", $tableborderwhith,$css);
            $css = str_replace("titletextcolor", $titletextcolor,$css);
            $css = str_replace("titlebgcolor", $titlebgcolor,$css);
            $css = str_replace("backgroundcolor", $backgroundcolor,$css);
            $css = str_replace("framebgcolor", $framebgcolor,$css);
            $css = str_replace("lightbgcolor", $lightbgcolor,$css);
            $css = str_replace("textbgcolor", $textbgcolor,$css);
            $css = str_replace("textcolor", $textcolor,$css);
            $css = str_replace("textlinkcolor", $textlinkcolor,$css);
            $css = str_replace("framethicknes", $framethicknes,$css);
            $css = str_replace("frameheight", $frameheight,$css);
            $css = str_replace("framewith", $framewith,$css);
            if ($framespace == "0px" ){$framespace="border-spacing: 0px;border-collapse: collapse";}else{$framespace="border-spacing: $framespace;border-collapse: separate";}
            $css = str_replace("framespace", $framespace,$css);

            if ( $tlimage != "" ){$tlimage=" background-image: url(images/$tlimage);";}$css = str_replace("tlimage", $tlimage,$css);
            if ( $timage != "" ){$timage=" background-image: url(images/$timage);";}$css = str_replace("timage", $timage,$css);
            if ( $trimage != "" ){$trimage=" background-image: url(images/$trimage);";}$css = str_replace("trimage", $trimage,$css);

            if ( $blimage != "" ){$blimage=" background-image: url(images/$blimage);";}$css = str_replace("blimage", $blimage,$css);
            if ( $bimage != "" ){$bimage=" background-image: url(images/$bimage);";}$css = str_replace("bimage", $bimage,$css);
            if ( $brimage != "" ){$brimage=" background-image: url(images/$brimage);";}$css = str_replace("brimage", $brimage,$css);

            if ( $limage != "" ){$limage=" background-image: url(images/$limage);";}$css = str_replace("limage", $limage,$css);
            if ( $rimage != "" ){$rimage=" background-image: url(images/$rimage);";}$css = str_replace("rimage", $rimage,$css);

            if ( $rtitleimage != "" ){$rtitleimage=" background-image: url(images/$rtitleimage);";}$css = str_replace("rtitleimage", $rtitleimage,$css);
            if ( $ltitleimage != "" ){$ltitleimage=" background-image: url(images/$ltitleimage);";}$css = str_replace("ltitleimage", $ltitleimage,$css);
            if ( $usefont == "" ){$usefont="sans, \"trebuchet ms\", Arial, \"Bitstream Vera Sans\", Cursor, Dingbats, FreeSans, sans-serif";}

            if ( $headlinefontsize  == "" ){ $headlinefontsize="180%";}
            $css = str_replace("headlinefontsize", $headlinefontsize,$css);

            if ( $smallfontsize == "" ){ $smallfontsize="80%";}
            $css = str_replace("smallfontsize", $smallfontsize,$css);

            if ( $smallerfontsize == "" ){ $smallerfontsize="70%";}
            $css = str_replace("smallerfontsize", $smallerfontsize,$css);

            if ( $largefontsize == "" ){ $largefontsize="120%";}
            $css = str_replace("largefontsize", $largefontsize,$css);

            if ( $bacefontsize == "" ){ $bacefontsize="14px";}
            $css = str_replace("bacefontsize", $bacefontsize,$css);
            
            if ( $bacefontlargesize == "" ){ $bacefontlargesize="18px";}
            $css = str_replace("bacefontlargesize", $bacefontlargesize,$css);
            
            if ( $bacefontsmallsize == "" ){ $bacefontsmallsize="10px";}
            $css = str_replace("bacefontsmallsize", $bacefontsmallsize,$css);
            
            $css = str_replace("usefont", $usefont,$css);
            // Reopen the file and erase the contents
            $fp = fopen("themes/$file/site.css", "w");

            // Write the new count to the file
            fwrite($fp, $css);

            // Close the file
            fclose($fp);
        }

        //}}}
}
?>                        
