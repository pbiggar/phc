##
# Authors:
#   Ryan Propper   <rpropper@stanford.edu>
#
# Copyright (c) 2006,
#   The Board of Trustees of The Leland Stanford Junior University
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
# 
# 3. The names of the contributors may not be used to endorse or promote
# products derived from this software without specific prior written
# permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
##

package XMLParser;

use strict;

sub new {
  my $package = shift;
  return bless({}, $package);
}

sub trim {
  my($string) = @_;

  $string =~ s/^\s+//;
  $string =~ s/\s+$//;

  return $string;
}

sub xml_error {
  print "Error parsing XML data\n";
  exit 1;
}

sub parseXMLData {
	my($self, $lines) = @_;
	my($parsedXML);

	while($lines =~ /\<display\>(.*?)\<\/display\>/) {
		my $curDisplay = $1;

		$curDisplay =~ /\<name\>(.*?)\<\/name\>/ or xml_error();
		my $displayName = trim($1);

		$curDisplay =~ /\<category\>(.*?)\<\/category\>/ or xml_error();
		$parsedXML->{$displayName}->{"category"} = trim($1);

		$curDisplay =~ /\<title\>(.*?)\<\/title\>/ or xml_error();
		$parsedXML->{$displayName}->{"title"} = trim($1);

		$curDisplay =~ /\<function\>(.*?)\<\/function\>/ or xml_error();
		$parsedXML->{$displayName}->{"function"} = trim($1);

		$curDisplay =~ /\<file\>(.*?)\<\/file\>/ or xml_error();
		$parsedXML->{$displayName}->{"fileName"} = trim($1);

		$curDisplay =~ /\<minline\>(.*?)\<\/minline\>/ or xml_error();
		$parsedXML->{$displayName}->{"lineStart"} = trim($1);

		$curDisplay =~ /\<maxline\>(.*?)\<\/maxline\>/ or xml_error();
		$parsedXML->{$displayName}->{"lineEnd"} = trim($1);

		$curDisplay =~ /\<focusline\>(.*?)\<\/focusline\>/ or xml_error();
		$parsedXML->{$displayName}->{"focusLine"} = trim($1);

		while(1) {
      if ($curDisplay =~ /\<linestyle\>(.*?)\<\/linestyle\>/) {
        my $curItem = trim($1);
        my $curHash;

        $curItem =~ /\<line\>(.*?)\<\/line\>/ or xml_error();
        my $curLine = trim($1);

        $curItem =~ /\<cssclass\>(.*?)\<\/cssclass\>/ or xml_error();
        $curHash->{"cssClass"} = trim($1);

        $parsedXML->{$displayName}->{"lineStyles"}->{$curLine} = $curHash;
        $curDisplay =~ s/\<linestyle\>.*?\<\/linestyle\>//;
      } elsif ($curDisplay =~ /\<linetext\>(.*?)\<\/linetext\>/) {
        my $curItem = trim($1);
        my $curHash;

        $curItem =~ /\<line\>(.*?)\<\/line\>/ or xml_error();
        my $curLine = trim($1);

        $curItem =~ /\<cssclass\>(.*?)\<\/cssclass\>/ or xml_error();
        $curHash->{"cssClass"} = trim($1);

        $curItem =~ /\<position\>(.*?)\<\/position\>/ or xml_error();
        $curHash->{"position"} = trim($1);

        $curItem =~ /\<text\>(.*?)\<\/text\>/ or xml_error();
        $curHash->{"text"} = trim($1);

        while($curItem =~ /\<link\>(.*?)\<\/link\>/) {
          my $curLink = trim($1);
          my $curLinkHash;

          $curLink =~ /\<text\>(.*?)\<\/text\>/ or xml_error();
          $curLinkHash->{"linkText"} = trim($1);

          $curLink =~ /\<name\>(.*?)\<\/name\>/ or xml_error();
          $curLinkHash->{"linkPath"} = trim($1);

          push(@{$curHash->{"links"}},$curLinkHash);
          $curItem =~ s/\<link\>(.*?)\<\/link\>//;
        }

        push(@{$parsedXML->{$displayName}->{"lineTexts"}->{$curLine}}, $curHash);
        $curDisplay =~ s/\<linetext\>.*?\<\/linetext\>//;
      } else {
        last;
      }
		}

		$lines =~ s/\<display\>.*?\<\/display\>//;
	}

	return $parsedXML;
}

sub parseDBEntry {
  my($self, $bdbUtilPath, $dbFile, $auxDisplay, $reportName) = @_;

  my $lines = "";
  if (-f $dbFile) {
      $lines = join("", `$bdbUtilPath/dbfind $dbFile '$reportName'`);
  }

  if ($lines eq "" && defined $auxDisplay) {
      system("$auxDisplay '$reportName'");
      $lines = join("", `$bdbUtilPath/dbfind $dbFile '$reportName'`);
  }

  $lines =~ s/\n//g;
  return XMLParser->parseXMLData($lines);
}


1;
__END__
