#!/bin/tcsh

# Go back to RUBBoS root directory
cd ..

# Browse only

cp ./workload/browse_only_transitions.txt ./workload/user_transitions.txt
cp ./workload/browse_only_transitions.txt ./workload/author_transitions.txt

foreach i (rubbos.properties_100 rubbos.properties_200 rubbos.properties_300 rubbos.properties_400 rubbos.properties_500 rubbos.properties_600 rubbos.properties_700 rubbos.properties_800 rubbos.properties_900 rubbos.properties_1000) 
  cp bench/$i rubbos.properties
  flush_cache 490000
  rsh sci23 RUBBoS/flush_cache 880000 	# web server
  rsh sci22 RUBBoS/flush_cache 880000	# database
  rsh sci6 RUBBoS/flush_cache 490000	# remote client
  rsh sci7 RUBBoS/flush_cache 490000	# remote client
  rsh sci8 RUBBoS/flush_cache 490000	# remote client
  make emulator 
end

# Default

cp ./workload/user_default_transitions.txt ./workload/user_transitions.txt
cp ./workload/author_default_transitions.txt ./workload/author_transitions.txt

foreach i (rubbos.properties_100 rubbos.properties_200 rubbos.properties_300 rubbos.properties_400 rubbos.properties_500 rubbos.properties_600 rubbos.properties_700 rubbos.properties_800 rubbos.properties_900 rubbos.properties_1000) 
  cp bench/$i rubbos.properties
  flush_cache 490000
  rsh sci23 RUBBoS/flush_cache 880000 	# web server
  rsh sci22 RUBBoS/flush_cache 880000	# database
  rsh sci6 RUBBoS/flush_cache 490000	# remote client
  rsh sci7 RUBBoS/flush_cache 490000	# remote client
  rsh sci8 RUBBoS/flush_cache 490000	# remote client
  make emulator
end
