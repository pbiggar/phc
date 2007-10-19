#!/misc/csw/bin/php -q
<?php
/*
 * See post-commit.tmpl for an explanation
 */

append_log("Running post-commit $argv[1] $argv[2]");

$repos = $argv[1];
$rev = $argv[2];

$svnlook = "/opt/csw/bin/svnlook";

$sections = array("author", "changed", "diff", "log");

foreach($sections as $section)
{
	$$section = trim(`$svnlook $section $repos`);
}

if($author == "")
	$author = "[unknown author]";

$body = <<<END
$log

# Changed
$changed

# Diff
$diff
END;
	
$subject = "svn commit by $author (rev $rev)";

$success = mail("phc-internals@phpcompiler.org", $subject, $body, "From: svn@phpcompiler.org\r\n");

// Log the commit
if($success)
	append_log("mail delivery ok");
else
	append_log("mail delivery failed");
	
function append_log($string)
{
	$file = fopen("/misc/svn/post-commit.log", "a");
	fwrite($file, date("D M j G:i:s Y")); 
	fwrite($file, ": $string\n");
	fclose($file);
}
?>
