##
# Authors:
#   Ryan Propper   <rpropper@stanford.edu>
#   Brian Hackett  <bhackett@stanford.edu>
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

package SaturnReport;

use strict;
use XMLParser;
use URI::Escape;

sub ppformat {
  my($text,$origtext,$format) = @_;

  my $result = "";
  my $prespace;
  if ($origtext =~ /^(\s*)/) {
      $result = $1;
      $prespace = "\t$1  " if ($format eq "");
      $prespace = $1 if ($format ne "");
  }
  else {
      $prespace = "\t  " if ($format eq "");
  }

  my $open_braces = 0;
  my $insnewline = 0;
  while ($text ne "") {
    $text =~ s/^\s*([^\,\;\{\}\(\)]*)//;
    my $linetext = $1;

    $result .= "\n$prespace" . ("  " x $open_braces) if ($insnewline == 1);

    $result .= $linetext;
    if ($text =~ s/^([\,\;])//) {
      $result .= $1;
      $insnewline = 1;
      $insnewline = 0 if ($1 eq "," && $open_braces == 0);
    }
    elsif ($text =~ s/^([\{\(])//) {
      my $open = $1;
      my $match = "";
      my $mini_open = 1;
      while (($mini_open > 0) && ($text ne "") && (length($match) < 40 || ($open eq "(" && not ($match =~ /[\{]/)))) {
        if ($text =~ s/^([^\{\}\(\)]*[\{\(])//) {
          $match .= $1;
          $mini_open++;
        }
        elsif ($text =~ s/^([^\{\}\(\)]*[\}\)][\,\;]?)//) {
          $match .= $1;
          $mini_open--;
        }
        else {
          $match .= $text;
          $text = "";
        }
      }
      $insnewline = 1;
      if (length($match) < 40 || $open eq "(") {
        $result .= "$open$match";
        if ($match =~ /\)[\,]?$/) {
          $result .= " ";
          $insnewline = 0;
        }
      }
      else {
        $open_braces++;
        $result .= $open;
        $text = $match . $text;
      }
    }
    elsif ($text =~ s/^([\}\)][\,\;]?)//) {
      my $term = $1;
      if ($open_braces > 0 && ($linetext =~ /[^\s]/ || $insnewline == 0)) {
        $result .= "\n$prespace" . ("  " x ($open_braces - 1)) . $term;
        $insnewline = 1;
      }
      elsif ($open_braces == 0) {
        $result =~ s/  $//;
        $result .= $term;
        $insnewline = 0;
      }
      else {
        $result =~ s/  $//;
        $result .= $term;
        $insnewline = 1;
      }
      $open_braces-- if ($open_braces > 0);
    }
    else {
      last;
    }
  }

  return $result;
}

sub genReport {
  my($self, $linkType, $config, $reportName, $fullFile, $format) = @_;
  my($returnHTML);

  my $dbFile = SaturnConf->queryConfig($config,"display");
  my $rootPath = SaturnConf->queryConfig($config,"srcpath"); $rootPath .= "/";
  my $cssURL = SaturnConf->queryConfig($config,"style");
  my $bdbUtilPath = SaturnConf->queryConfig($config,"binpath");
  my $ppdbFile = SaturnConf->maybeConfig($config,"ppfile");
  my $auxDisplay = SaturnConf->maybeConfig($config,"auxdisplay");

  #############################
  # Parse the specified path. #
  #############################

  my $parsedXML = XMLParser->parseDBEntry($bdbUtilPath, $dbFile, $auxDisplay, $reportName);
  if (!(defined $parsedXML)) {
    $returnHTML .= "<html><body>\n";
    $returnHTML .= "<h2><b>Invalid report</b></h2>\n";
    $returnHTML .= "<p>Return <a href=\"search.pl\">home.</a>\n";
    $returnHTML .= "</body></html>\n";
    print $returnHTML;
    exit 1;
  }

  ##############################
  # Extract source code lines. #
  ##############################

  my $fileName = $parsedXML->{$reportName}->{"fileName"};
  $fileName =~ s/\/export\/sc1\/bhackett\/openssh-4.3p2\///;

  if (not ($fileName =~ /^\//)) {
    $fileName = $rootPath . $fileName;
  }
  if (not (-e $fileName)) {
    print "Could not find file: $fileName\n";
    exit 1;
  }

  my @wc = split(/\s/, `wc -l $fileName`);
  my $totalLines = $wc[0];

  my $lineStart = $parsedXML->{$reportName}->{"lineStart"};
  my $lineEnd = $parsedXML->{$reportName}->{"lineEnd"};
  if ($fullFile == 1) {
      $lineStart = 1;
      $lineEnd = $totalLines;
  }

  if ($lineEnd > $totalLines) {
    $lineEnd = $totalLines;
  }

  my $lineCount = $lineEnd - $lineStart + 1;
  my $counter = $lineStart;

  my $cmd = "head -$lineEnd $fileName | tail -$lineCount";
  my @sourceFileLines = `$cmd`;

  #####################################
  # Extract preprocessed source code. #
  #####################################

  my @ppFileLines;
  if (defined $ppdbFile) {
      my $basefile = $parsedXML->{$reportName}->{"fileName"};
      my $ppCmd = "$bdbUtilPath/dbfind $ppdbFile $basefile";

      my @wc = split(/\s/, `$ppCmd | wc -l`);
      my $ppTotalLines = $wc[0];

      my $ppLineStart = $parsedXML->{$reportName}->{"lineStart"};
      my $ppLineEnd = $parsedXML->{$reportName}->{"lineEnd"};
      if ($fullFile == 1) {
          $ppLineStart = 1;
          $ppLineEnd = $ppTotalLines;
      }

      if ($ppLineEnd > $ppTotalLines) {
          $ppLineEnd = $ppTotalLines;
      }

      my $ppLineCount = $ppLineEnd - $ppLineStart + 1;
      my $ppcmd = "$ppCmd | head -$ppLineEnd | tail -$ppLineCount";
      @ppFileLines = `$ppcmd`;

      # match up ppFileLines and sourceFileLines
      while ($ppLineCount < $lineCount) {
          push(@ppFileLines,"\n");
          $ppLineCount++;
      }
  }

  ##############################
  # Start printing the output. #
  ##############################

  my $title = $parsedXML->{$reportName}->{"title"};

  $returnHTML .= "<html>\n";
  $returnHTML .= "<head>\n";
  $returnHTML .= "<link rel=\"stylesheet\" type=\"text/css\" href=\"$cssURL\" /><title>Saturn report: $title</title>\n";
  $returnHTML .= "</head>\n";
  $returnHTML .= "<body>\n";

  my $linkReport = uri_escape($reportName);
  if ($format ne "") {
      $returnHTML .= "<pre>";
  }
  else {
      my $fileName = $parsedXML->{$reportName}->{"fileName"};
      my $focusLine = $parsedXML->{$reportName}->{"focusLine"};
      $returnHTML .= "<h2>Report: $title, <code>$fileName</code>, line $focusLine</h2>\n";
      $returnHTML .= "<blockquote><table class=\"display\" cellspacing=\"0\" cellpadding=\"0\">\n";
  }

  foreach my $sourceFileLine (@sourceFileLines) {
    chomp $sourceFileLine;
    my $ppFileLine;

    my $leftText = "";
    my $rightText = "";
    my $bottomText = "";
    my $topText = "";

    my $curOutput;
    if (defined $ppdbFile) {
      $ppFileLine = shift @ppFileLines;
      chomp $ppFileLine;

#      $ppFileLine =~ s/\;(\s*[^\s])/\;\n\t $1/g;
#      $ppFileLine =~ s/\{/\{\n\t /g;
#      $ppFileLine =~ s/\}/\n\t \}/g;
      $ppFileLine = ppformat($ppFileLine,$sourceFileLine,$format);

      my $disabled = "";
#      $disabled = " disabled " if ($ppFileLine eq $sourceFileLine);

      $sourceFileLine =~ s/\&/\&amp\;/g;
      $sourceFileLine =~ s/\</\&lt\;/g;
      $sourceFileLine =~ s/\>/\&gt\;/g;

      $ppFileLine =~ s/\&/\&amp\;/g;
      $ppFileLine =~ s/\</\&lt\;/g;
      $ppFileLine =~ s/\>/\&gt\;/g;

      $curOutput = "<input $disabled type=\"checkbox\" class=\"ppbox\"/>" .
          "<span class=\"basecode\">$counter:\t$sourceFileLine</span>" .
          "<span class=\"ppcode\">$counter:\t$ppFileLine</span>";
    }
    else {
        $sourceFileLine =~ s/\&/\&amp\;/g;
        $sourceFileLine =~ s/\</\&lt\;/g;
        $sourceFileLine =~ s/\>/\&gt\;/g;

        $curOutput = "$counter:\t$sourceFileLine";
    }

    if (defined $parsedXML->{$reportName}->{"lineStyles"}->{$counter}) {
      my $curHash = $parsedXML->{$reportName}->{"lineStyles"}->{$counter};
      my $cssClass = $curHash->{"cssClass"};

      $curOutput = "<td class=\"$cssClass\">$curOutput</td>";
    } else {
      $curOutput = "<td>$curOutput</td>";
    }

    my $hashes = $parsedXML->{$reportName}->{"lineTexts"}->{$counter} or ();
    foreach my $curHash (@{$hashes}) {
      my $textOutput = $curHash->{"text"};

      my $links = $curHash->{"links"} or ();
      foreach my $curLinkHash (@{$links}) {
          my $text = $curLinkHash->{"linkText"};
          my $path = $curLinkHash->{"linkPath"};

          if ($linkType eq "-static") {
            $path =~ s/\W/_/g;
            $textOutput .= " [<a href=\"$path.html\">$text</a>]";
          } else {
            $textOutput .= " [<a href=\"report.pl?db=" . $linkType . "&report=" . uri_escape($path) . "\">$text</a>]";
          }
      }

      my $cssClass = $curHash->{"cssClass"};
      $textOutput = "<td class=\"$cssClass\">$textOutput</td>";

      my $position = $curHash->{"position"};
      if ($position eq "left") {
        $leftText = $textOutput;
      }
      elsif ($position eq "right") {
        $rightText .= $textOutput;
      }
      elsif ($position eq "top") {
        $topText .= "<tr><td></td>$textOutput</tr>\n";
      }
      elsif ($position eq "bottom") {
        $bottomText .= "<tr><td></td>$textOutput</tr>\n";
      }
      else {
        next;
      }
    }

    if ($format eq "plain") {
        $returnHTML .= "$sourceFileLine\n";
    }
    elsif ($format eq "plainpp") {
        $returnHTML .= "$ppFileLine\n";
    }
    else {
        $returnHTML .= $topText;
        $returnHTML .= "<tr><td>$leftText</td>$curOutput$rightText</tr>\n";
        $returnHTML .= $bottomText;
    }

    $counter++;
  }

  if ($format ne "") {
      $returnHTML .= "</pre>";
  }
  else {
      $returnHTML .= "</table></blockquote>\n";
      if ($linkType ne "-static") {
          if ($fullFile != 1) {
              $returnHTML .= " [<a href=\"report.pl?db=$linkType&report=$linkReport&fullfile=1\">View Entire File</a>]";
          }
          my $full;
          $full = "&fullfile=1" if ($fullFile == 1);
          $returnHTML .= " [<a href=\"report.pl?db=$linkType&report=$linkReport$full&newformat=plain\">View Plain Code</a>]";
          if (defined $ppdbFile) {
              $returnHTML .= " [<a href=\"report.pl?db=$linkType&report=$linkReport$full&newformat=plainpp\">View Preprocessed Code</a>]";
          }
      }
  }
  $returnHTML .= "</body>\n";
  $returnHTML .= "</html>\n";

  return $returnHTML;
}

1;
__END__
