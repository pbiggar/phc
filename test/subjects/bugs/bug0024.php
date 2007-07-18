<?

	// reported by Gary Wassermann
	// July 17, 2007
	// This segfaults in Token_conversion

//    $diary_directory = opendir(".");
 while($filename = readdir($diary_directory))
{
   $filesplit = explode(".", $filename);
//    $check_filename = $filesplit[0];
      if(ereg("[0-9]{6}", $check_filename))
     {
        $check_filename .= ".$filesplit[1]";
//         $valid_filename[] = $check_filename;
     }
 }
//closedir($diary_directory);
//for($index = 0; $index < count($valid_filename); $index++)
//{
//  print("$valid_filename[$index]<br>");
//}
?>
