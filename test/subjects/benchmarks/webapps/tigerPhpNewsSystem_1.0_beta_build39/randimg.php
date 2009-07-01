<?php
/*
 * This software is part of the Tiger php news system
 * http://tpns.sourceforge.net
 * 
 * This software comes with ABSOLUTELY NO WARRANTY. For details, see
 * the enclosed file COPYING for license information (GPL). If you
 * did not receive this file, see http://www.gnu.org/licenses/gpl.txt.
 * 
 */
$string="";
$keylength=6;
for( $i=0;$i<$keylength;$i++)
{
    $type=rand(0,9);
     $string.=$type;
}

Header("Content-type: image/png");
session_start();
//$string=rand(10000,99999);
//$string="023456789abcdefghklmnpqrstuvxyzABCDEFGHKLMNPRSTUVXYZ";
$_SESSION['imgkey']=$string;
$font=5;
$width  = imagefontwidth($font) * (strlen($string)+2);
$fwidth=imagefontwidth($font);
$height = imagefontheight($font);
$im = ImageCreate($width, $height);
$white = ImageColorAllocate($im, 255, 255, 255);
$black = ImageColorAllocate($im, 0, 0, 0);
ImageFill($im, 0, 0, $white);

ImageString ($im, $font , $fwidth , 0, $string, $black); 

ImageLine($im, 0, ($height/6)*2 , $width,($height/6)*2 , $black);     
ImageLine($im, 0, ($height/6)*4 , $width, ($height/6)*4, $black);     

for($i = 1; $i <= strlen($string)+2; $i++) 
{
    ImageLine($im, ($fwidth*$i)-($fwidth/2), 0 , ($fwidth*$i)-($fwidth/2), $height, $black);     
}
ImagePNG($im);
?>
