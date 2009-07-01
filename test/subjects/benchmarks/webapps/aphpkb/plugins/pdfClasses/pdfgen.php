<?php
include_once('../../config/config.php');
include_once('../../functions.php');
include_once('../../config/dbsettings.php');
$pdfaquery = "SELECT Title, Articledata FROM articles WHERE FileID='$_REQUEST[pdfa]'";

     $pdfaresult = mysql_query($pdfaquery); 
	while ($row = mysql_fetch_array ($pdfaresult, MYSQL_ASSOC)) { 
 	$title = $row['Title'];
	$articledata = $row['Articledata'];
}
$pdfa = $title . "\n\n" . ereg_replace("<br />", "\n", $articledata);
$pdfa = strip_tags($pdfa);
include ('class.ezpdf.php');
$pdf =& new Cezpdf();
$pdf ->selectFont('./fonts/Helvetica.afm');
$pdf ->ezText($pdfa,12);
$pdf ->ezStream();
?>