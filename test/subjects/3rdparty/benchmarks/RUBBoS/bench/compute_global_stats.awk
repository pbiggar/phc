#!/bin/awk -f

# Caller must set nbscript and path values on the command line.
# Example: compute_global_stats.awk -v path=2001-10-10@14:55:23/ -v nbscript=2 2001-10-10@14:55:23/stat_client0.html

BEGIN {
  printf "Computing global stats for "nbscript" scripts in "path" ...";
  outputFile = path"perf.html";
  footer = 0;
  headerRow = 0;
  for (i = 1 ; i < nbscript ; i++)
    scriptName[i] = path"stat_client"i".html";
}
{
  # Read each line from all files to be synchronized between them
  line[0] = $0;
  for (i = 1 ; i < nbscript ; i++)
    getline line[i] < scriptName[i];

  # Compute the global results for the statistics of each ramp
  if (headerRow == 1)
    { 
      if ($0 ~ "<TR><TD><div align=left><B>Total</B></div>")
	{ # This is the total line, compute the percentages and print the table
	  totalCount = 0;
	  totalErrors = 0;
	  totalTime = 0;
	  for (i = 0 ; i < nbscript ; i++)
	    {
	      split(line[i], splited, "</div><TD>");
	      gsub(/<div align=right>|<B>|<\/B>/, "", splited[3]); # Get rid of the '<div align=right><B>' and </B>
	      totalCount += splited[3];
	      gsub(/<div align=right>|<B>|<\/B>/, "", splited[4]); # Get rid of the '<div align=right><B>' and </B>
	      totalErrors += splited[4];
	    }
	  if (totalCount == 0)
	    totalCount = 1000000000000000000000000; # make totalCount infinite so that division result will give 0.
	  for (i = 0 ; (i < stateNb) && (stateNb != 0); i++)
	    {
	      if (count[i] != 0)
		{
		  printf "%s</div><TD><div align=right>%.2f %%</div><TD><div align=right>%d</div><TD><div align=right>%d</div><TD><div align=right>%d ms</div><TD><div align=right>%d ms</div><TD><div align=right>%.0f ms</div>\n", stateName[i], 100*count[i]/totalCount, count[i], errors[i], minTime[i], maxTime[i], avgTime[i]/stateNb >> outputFile;
		  totalTime += avgTime[i];
		}
	    }
	  # Display the total
	  if (stateNb == 0)
	    stateNb = 1000000000000000000000000; # make stateNb infinite so that division result will give 0.
	  printf "<TR><TD><div align=left><B>Total</div></B><TD><div align=right><B>100 %</B></div><TD><div align=right><B>%d</B></div><TD><div align=right><B>%d</B></div><TD><div align=center>-</div><TD><div align=center>-</div><TD><div align=right><B>%.0f ms</B></div>", totalCount, totalErrors, totalTime/totalCount >> outputFile;
	}
      else if ($0 ~ "<TR><TD><div align=left><B>Average throughput</div>")
	{ # Average throughput
	  throughput = 0;
	  for (i = 0 ; i < nbscript ; i++)
	    {
	      split(line[i], splited, /<B>|<\/B>/);
	      gsub(/ req\/s/, "", splited[4]); # Get rid of the '< req/s>'
	      throughput += splited[4];
	    }
	  print "<TR><TD><div align=left><B>Average throughput</div></B><TD colspan=6><div align=center><B>"throughput" req/s</B></div>" >> outputFile;
	}
      else if ($0 ~ "<TR><TD><div align=left>Completed sessions</div>")
	{ # Completed sessions
	  sessions = 0;
	  for (i = 0 ; i < nbscript ; i++)
	    {
	      split(line[i], splited, /<div align=left>/);
	      gsub(/<\/div>/, "", splited[3]); # Get rid of the '</div>'
	      sessions += splited[3];
	    }
	  print "<TR><TD><div align=left>Completed sessions</div><TD colspan=6><div align=left>"sessions"</div>" >> outputFile;
	}
      else if ($0 ~ "<TR><TD><div align=left>Total time</div>")
	{ # Total time
	  time = 0;
	  for (i = 0 ; i < nbscript ; i++)
	    {
	      split(line[i], splited, /<div align=left>/);
	      gsub(/ seconds<\/div>/, "", splited[3]); # Get rid of the '</div>'
	      time += splited[3];
	    }
	  print "<TR><TD><div align=left>Total time</div><TD colspan=6><div align=left>"time" seconds</div>" >> outputFile;
	}
      else if ($0 ~ "<TR><TD><div align=left><B>Average session time</div>")
	{ # Average session time is the last stat of the table, we close the table here.
	  if (time == 0)
	    print "<TR><TD><div align=left><B>Average session time</div></B><TD colspan=6><div align=left><B>0 second</B></div>" >> outputFile;
	  else
	    print "<TR><TD><div align=left><B>Average session time</div></B><TD colspan=6><div align=left><B>"time/sessions" seconds</B></div>" >> outputFile;
	  print "</TABLE><p>" >> outputFile;
	  headerRow = 0;
	}
     else if ($0 ~ "align=right>")
	{ # We have to process a stat line, let's go !
	  count[stateNb]   = 0;
	  errors[stateNb]  = 0;
	  minTime[stateNb] = 1000000000000000;
	  maxTime[stateNb] = 0;
	  avgTime[stateNb] = 0;
	  for (i = 0 ; i < nbscript ; i++)
	    {
	      split(line[i], splited, "</div><TD><div align=right>");
	      if (i == 0)
		stateName[stateNb] = splited[1];
	      else if (splited[1] != stateName[stateNb])
		print "Error line "NR" in "path"stat_client"i".html: Bad state '"splited[1]"' does not match '"stateName[stateNb]"'";
	      # Skip percentage in splited[2], we'll have to compute that later
	      count[stateNb]    += splited[3];
	      gsub(/<B>|<\/B>/, "", splited[4]); # Get rid of the '<B>' and </B>
	      errors[stateNb]   += splited[4];
	      sub(/ ms/, "", splited[5]); # Get rid of the ' ms'
	      if (minTime[stateNb] > splited[5])
		minTime[stateNb] = splited[5];
	      sub(/ ms/, "", splited[6]); # Get rid of the ' ms'
	      if (maxTime[stateNb] < splited[6])
		maxTime[stateNb] = splited[6];
	      sub(/ ms<\/div>/, "", splited[7]); # Get rid of the ' ms</div>'
	      avgTime[stateNb]  += splited[7];
	    }
	  stateNb++;
	}
    }

  # Print the headers for ramps
  if ($0 ~ /stat\"><\/A>|statistics<\/h3><p>/)
    {
      print $0 >> outputFile;
      testTiming = 0;
    }

  # Print a summary of 'Test timing information' for all clients
  if ($0 ~ "<A NAME=\"time\"></A>")
    testTiming = 1;

  if (testTiming == 1)
    {
      if ($0 ~ "<TD>")
	{
	  printf $0 >> outputFile;
	  for (i = 1 ; i < nbscript ; i++)
	    {
	      split(line[i], splited, "<TD>");
	      printf "<TD>"splited[3] >> outputFile;
	    }
	  print "" >> outputFile;
	}
      else
	print $0 >> outputFile;
      if ($0 ~ "<TABLE")
	{
	  printf "<THEAD><TR><TH>Phase<TH>Main client" >> outputFile;
	  for (i = 1 ; i < nbscript ; i++)
	    printf "<TH>Remote client "i >> outputFile;
	  print "<TBODY>" >> outputFile;
	}
    }

  if ($0 ~ /State name/)
    { # Table header recognized !
      headerRow = 1;
      stateNb = 0;
      print "<TABLE BORDER=1>" >> outputFile;
      print $0 >> outputFile;
    }

  # Recopy the graph part which is common to every stat page
  if ($0 ~ /"cpu_graph"/)
    footer = 1;

  if (footer == 1)
    print $0 >> outputFile;

}
END {
  print " Done.";
}
