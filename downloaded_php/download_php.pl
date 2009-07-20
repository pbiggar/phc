#!/usr/bin/perl

use WWW::Mechanize

#Set up Meachanize object and proxy
$mech = new WWW::Mechanize ();
$mech->proxy (['https', 'http'], 'http://www-proxy.cs.tcd.ie:8080');

#Go to first page of results for "php" on sourceforge
$mech->get ('http://sourceforge.net/search/?words=php&type_of_search=soft&pmode=0&limit=100&offset=0');

do
{
	# $current_url is the url of the current search results page, update this and find all download links
	$current_url = $mech->uri ();
	@links = $mech->find_all_links (text => 'Download Now!');
	
	# loop through all download links and download where there is a 'direct link'
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
			`mkdir downloaded_php\/downloads\/$dirname\/`;
			$mech->save_content ("downloaded_php\/downloads\/$dirname\/$filename");
			
			# Attempt to untar, if that fails, attempt to unzip.  Remove file if either op succeeds.
			`tar -C downloaded_php\/downloads\/$dirname\/ -xvf downloaded_php\/downloads\/$dirname\/$filename`;
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
		$mech->get ($current_url);
	}

	#Follow link to next page
	$test = $mech->find_link (text_regex => qr/Next ./);
	if ($test)
	{
		$mech->follow_link (text_regex => qr/Next ./);
	}

}
while ($test);
