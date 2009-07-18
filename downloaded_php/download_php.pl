#!/usr/bin/perl

use WWW::Mechanize

$mech = new WWW::Mechanize ();
$mech->proxy (['https', 'http'], 'http://www-proxy.cs.tcd.ie:8080');

$mech->get ('http://sourceforge.net/search/?words=php&type_of_search=soft&pmode=0&limit=100');

do
{
	$current_url = $mech->uri ();
	
	@links = $mech->find_all_links (text => 'Download Now!');

	foreach $link (@links)
	{
		print ("Navigating to ");
		print ($link->url ());	
		print ("\n");
		$mech->get ($link->url ());
		if ($mech->find_link (text => 'direct link'))
		{
			$mech->follow_link (text => 'direct link');
			$mech->uri () =~ m/.*\/(.*)$/;
			$filename = $1;
			print ("Downloading $filename\n");
			$filename =~ m/(.*)\..*/;
			$dirname = $1;
		#	if (! -e "downloaded_php\/downloads\/$dirname")
		#	{
				`mkdir downloaded_php\/downloads\/$dirname\/`;
				$mech->save_content ("downloaded_php\/downloads\/$dirname\/$filename");
				`tar -C downloaded_php\/downloads\/$dirname\/ -xvf downloaded_php\/downloads\/$dirname\/$filename 2>/dev/null`;
				if (!$?)
				{
					`rm downloaded_php\/downloads\/$dirname\/$filename`;
				}
				else
				{
					`unzip downloaded_php\/downloads\/$dirname\/$filename -ddownloaded_php\/downloads\/$dirname`;
					if (!$?)
					{
						`rm downloaded_php\/downloads\/$dirname\/$filename`;
					}
				}
			}
	#	}
		$mech->get ($current_url);
	}


	$test = $mech->find_link (text_regex => qr/Next ./);
	if ($test)
	{
		$mech->follow_link (text_regex => qr/Next ./);
	}

}
while ($test);
